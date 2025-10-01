/*
 * QuickPollsFeaturePlugin.cpp - implementation of QuickPollsFeaturePlugin class
 *
 * Copyright (c) 2024- Veyon Community
 *
 * This file is part of Veyon - https://veyon.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#include "QuickPollsFeaturePlugin.h"
#include "QuickPollsDialog.h"
#include "FeatureWorkerManager.h"
#include "ComputerControlInterface.h"
#include "VeyonMasterInterface.h"
#include "VeyonServerInterface.h"
#include "VeyonWorkerInterface.h"
#include "MessageContext.h"
#include "PollWidget.h"
#include "PollResultsDialog.h"


QuickPollsFeaturePlugin::QuickPollsFeaturePlugin( QObject* parent ) :
	QObject( parent ),
	m_quickPollsFeature( Feature( QStringLiteral( "QuickPolls" ),
								   Feature::Flag::Action | Feature::Flag::AllComponents,
								   Feature::Uid( "c1a8c3c3-6b69-40de-8e69-537f0e69a53c" ),
								   Feature::Uid(),
								   tr( "Quick Polls" ), {},
								   tr( "Use this function to ask students a question." ),
								   QStringLiteral(":/quickpolls/poll.png") ) ),
	m_features( { m_quickPollsFeature } )
{
}


QuickPollsFeaturePlugin::~QuickPollsFeaturePlugin()
{
	delete m_resultsDialog;
}


const FeatureList &QuickPollsFeaturePlugin::featureList() const
{
	return m_features;
}



bool QuickPollsFeaturePlugin::controlFeature( Feature::Uid featureUid,
											  Operation operation,
											  const QVariantMap& arguments,
											  const ComputerControlInterfaceList& computerControlInterfaces )
{
	if( operation != Operation::Start )
	{
		return false;
	}

	if( featureUid == m_quickPollsFeature.uid() )
	{
		const auto question = arguments.value( argToString(Argument::Question) ).toString();
		const auto answers = arguments.value( argToString(Argument::Answers) ).toStringList();

		sendFeatureMessage( FeatureMessage{ featureUid, ShowPoll }
								.addArgument( Argument::Question, question )
								.addArgument( Argument::Answers, answers ), computerControlInterfaces );

		return true;
	}

	return false;
}



bool QuickPollsFeaturePlugin::startFeature( VeyonMasterInterface& master, const Feature& feature,
											 const ComputerControlInterfaceList& computerControlInterfaces )
{
	if( feature.uid() != m_quickPollsFeature.uid() )
	{
		return false;
	}

	if (m_resultsDialog)
	{
		m_resultsDialog->activateWindow();
		m_resultsDialog->raise();
		return true;
	}

	QString question;
	QStringList answers;

	QuickPollsDialog dialog( question, answers, master.mainWindow() );
	if(dialog.exec() != QDialog::Accepted || question.isEmpty() || answers.isEmpty())
	{
		return true;
	}

	m_resultsDialog = new PollResultsDialog(question, answers, master.mainWindow());
	connect(m_resultsDialog, &QDialog::finished, this, [this]() {
		m_resultsDialog = nullptr;
	});
	m_resultsDialog->show();

	controlFeature( m_quickPollsFeature.uid(), Operation::Start,
					{
						{ argToString(Argument::Question), question },
						{ argToString(Argument::Answers), answers }
					},
					computerControlInterfaces );

	return true;
}




bool QuickPollsFeaturePlugin::handleFeatureMessage( VeyonServerInterface& server,
													 const MessageContext& messageContext,
													 const FeatureMessage& message )
{
	if( m_quickPollsFeature.uid() == message.featureUid() )
	{
		if (message.command() == ShowPoll)
		{
			// Forward message from master to all workers
			server.featureWorkerManager().sendMessageToAllSessionWorkers( message );
		}
		else if (message.command() == PollResponse)
		{
			// Forward message from worker to the master
			server.sendMessageToMaster(messageContext.masterPeerId(), message);
		}
		return true;
	}

	return false;
}



bool QuickPollsFeaturePlugin::handleFeatureMessage( VeyonWorkerInterface& worker, const FeatureMessage& message )
{
	Q_UNUSED(worker);

	if( message.featureUid() == m_quickPollsFeature.uid() )
	{
		if (message.command() == ShowPoll)
		{
			const auto question = message.argument( Argument::Question ).toString();
			const auto answers = message.argument( Argument::Answers ).toStringList();

			auto* pollWidget = new PollWidget(question, answers);
			connect(pollWidget, &PollWidget::answered, this, [this](const QString& answer) {
				sendFeatureMessage( FeatureMessage{ m_quickPollsFeature.uid(), PollResponse }
											.addArgument( Argument::Response, answer ) );
			});
			pollWidget->show();
		}
		return true;
	}

	return true;
}bool QuickPollsFeaturePlugin::handleFeatureMessage( VeyonMasterInterface& master, const FeatureMessage& message )
{
	Q_UNUSED(master);

	if( message.featureUid() == m_quickPollsFeature.uid() && message.command() == PollResponse)
	{
		if (m_resultsDialog)
		{
			const auto response = message.argument( Argument::Response ).toString();
			m_resultsDialog->addResponse(response);
		}
		return true;
	}

	return false;
}