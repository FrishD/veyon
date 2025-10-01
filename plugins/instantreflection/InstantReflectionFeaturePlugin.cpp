/*
 * InstantReflectionFeaturePlugin.cpp - implementation of InstantReflectionFeaturePlugin class
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

#include "InstantReflectionFeaturePlugin.h"
#include "ReflectionWidget.h"
#include "ReflectionStatusDialog.h"
#include "FeatureWorkerManager.h"
#include "ComputerControlInterface.h"
#include "VeyonMasterInterface.h"
#include "VeyonServerInterface.h"
#include "VeyonWorkerInterface.h"
#include "MessageContext.h"


InstantReflectionFeaturePlugin::InstantReflectionFeaturePlugin( QObject* parent ) :
	QObject( parent ),
	m_instantReflectionFeature( Feature( QStringLiteral( "InstantReflection" ),
								   Feature::Flag::Action | Feature::Flag::AllComponents,
								   Feature::Uid( "d1a8c3c3-6b69-40de-8e69-537f0e69a53d" ),
								   Feature::Uid(),
								   tr( "Instant Reflection" ), {},
								   tr( "Allow students to send a reflection status to the teacher." ),
								   QStringLiteral(":/instantreflection/reflection.png") ) ),
	m_features( { m_instantReflectionFeature } )
{
}


InstantReflectionFeaturePlugin::~InstantReflectionFeaturePlugin()
{
	delete m_statusDialog;
}


const FeatureList &InstantReflectionFeaturePlugin::featureList() const
{
	return m_features;
}



bool InstantReflectionFeaturePlugin::controlFeature( Feature::Uid featureUid,
											  Operation operation,
											  const QVariantMap& arguments,
											  const ComputerControlInterfaceList& computerControlInterfaces )
{
	if( operation != Operation::Start || featureUid != m_instantReflectionFeature.uid() )
	{
		return false;
	}

	sendFeatureMessage( FeatureMessage{ featureUid, ShowReflectionButtons }, computerControlInterfaces );
	return true;
}



bool InstantReflectionFeaturePlugin::startFeature( VeyonMasterInterface& master, const Feature& feature,
											 const ComputerControlInterfaceList& computerControlInterfaces )
{
	if( feature.uid() != m_instantReflectionFeature.uid() )
	{
		return false;
	}

	if (m_statusDialog)
	{
		m_statusDialog->activateWindow();
		m_statusDialog->raise();
	}
	else
	{
		m_statusDialog = new ReflectionStatusDialog(master.mainWindow());
		connect(m_statusDialog, &QDialog::finished, this, [this]() {
			m_statusDialog = nullptr;
		});
		m_statusDialog->show();
		controlFeature(feature.uid(), Operation::Start, {}, computerControlInterfaces);
	}

	return true;
}




bool InstantReflectionFeaturePlugin::handleFeatureMessage( VeyonServerInterface& server,
													 const MessageContext& messageContext,
													 const FeatureMessage& message )
{
	if( m_instantReflectionFeature.uid() == message.featureUid() )
	{
		if (message.command() == ShowReflectionButtons)
		{
			server.featureWorkerManager().sendMessageToAllSessionWorkers( message );
		}
		else if (message.command() == ReflectionResponse)
		{
			server.sendMessageToMaster(messageContext.masterPeerId(), message);
		}
		return true;
	}

	return false;
}



bool InstantReflectionFeaturePlugin::handleFeatureMessage( VeyonWorkerInterface& worker, const FeatureMessage& message )
{
	Q_UNUSED(worker);

	if( message.featureUid() == m_instantReflectionFeature.uid() && message.command() == ShowReflectionButtons)
	{
		auto* reflectionWidget = new ReflectionWidget();
		connect(reflectionWidget, &ReflectionWidget::statusSelected, this, [this](Status status) {
			sendFeatureMessage( FeatureMessage{ m_instantReflectionFeature.uid(), ReflectionResponse }
										.addArgument( Argument::Status, static_cast<int>(status) ) );
		});
		reflectionWidget->show();
		return true;
	}

	return true;
}

bool InstantReflectionFeaturePlugin::handleFeatureMessage( VeyonMasterInterface& master, const MessageContext& messageContext, const FeatureMessage& message )
{
	Q_UNUSED(master);

	if( message.featureUid() == m_instantReflectionFeature.uid() && message.command() == ReflectionResponse)
	{
		if (m_statusDialog)
		{
			const auto status = static_cast<Status>(message.argument( Argument::Status ).toInt());
			m_statusDialog->updateStatus(messageContext.userName(), status);
		}
		return true;
	}

	return false;
}