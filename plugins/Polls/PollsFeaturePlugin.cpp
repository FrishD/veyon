/*
 * PollsFeaturePlugin.cpp - implementation of PollsFeature class
 *
 * Copyright (c) 2024-2025 Your Name
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

#include "PollsFeaturePlugin.h"

#include "VeyonMasterInterface.h"
#include "VeyonWorkerInterface.h"
#include "ComputerControlInterface.h"
#include "FeatureMessage.h"
#include "PollDialog.h"
#include "PollQuestionDialog.h"
#include "PollResultsDialog.h"

#include <QApplication>

PollsFeaturePlugin::PollsFeaturePlugin( QObject* parent ) :
	QObject( parent ),
	m_pollsFeature(
		Feature::Uid{ QStringLiteral("a3b4c5d6-e7f8-9a0b-1c2d-3e4f5a6b7c8d") },
		tr( "Run poll" ),
		tr( "Ask a question and get immediate feedback" ),
		QIcon( QStringLiteral("qrc:/veyon/plugins/polls/polls.png") ),
        Feature::Flags( Feature::Flag::SupportsCustomAction )
	),
	m_features( { m_pollsFeature } )
{
}

const FeatureList& PollsFeaturePlugin::featureList() const
{
	return m_features;
}

bool PollsFeaturePlugin::startFeature( VeyonMasterInterface& master, const Feature& /*feature*/,
                                       const ComputerControlInterfaceList& computerControlInterfaces )
{
    PollDialog dialog( QApplication::activeWindow() );
    if( dialog.exec() == QDialog::Accepted )
    {
        QVariantMap data;
        data.insert( QString::number(Arguments::Question), dialog.question() );
        data.insert( QString::number(Arguments::Answers), dialog.answers() );

        auto* resultsDialog = new PollResultsDialog( master, computerControlInterfaces.count(), dialog.question(), dialog.answers(), QApplication::activeWindow() );
        master.registerFeatureMessageHandler( this, m_pollsFeature.uid, resultsDialog );
        resultsDialog->show();

        for( const auto& computerControlInterface : computerControlInterfaces )
        {
            computerControlInterface->sendFeatureMessage( m_pollsFeature.uid, Commands::ShowPoll, data );
        }
        return true;
    }

    return false;
}

bool PollsFeaturePlugin::handleFeatureMessage( VeyonMasterInterface& /*master*/, const MessageContext& /*messageContext*/,
                                               const FeatureMessage& /*message*/ )
{
    // The results dialog handles the messages on the master side
    return true;
}

bool PollsFeaturePlugin::handleFeatureMessage( VeyonWorkerInterface& worker, const FeatureMessage& message )
{
    if( message.command() == Commands::ShowPoll )
    {
        QString question = message.data().value( QString::number(Arguments::Question) ).toString();
        QStringList answers = message.data().value( QString::number(Arguments::Answers) ).toStringList();

        PollQuestionDialog dialog( question, answers, QApplication::activeWindow() );
        if( dialog.exec() == QDialog::Accepted )
        {
            QVariantMap data;
            data.insert( "answer", dialog.selectedAnswer() );
            worker.sendFeatureMessage( m_pollsFeature.uid, Commands::SubmitAnswer, data );
        }
        return true;
    }

    return false;
}