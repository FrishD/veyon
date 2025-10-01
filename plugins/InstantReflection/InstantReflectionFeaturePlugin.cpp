/*
 * InstantReflectionFeaturePlugin.cpp - implementation of InstantReflectionFeature class
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

#include "InstantReflectionFeaturePlugin.h"

#include "VeyonMasterInterface.h"
#include "VeyonWorkerInterface.h"
#include "ComputerControlInterface.h"
#include "FeatureMessage.h"
#include "ReflectionStatusDialog.h"

#include <QApplication>
#include <QIcon>

InstantReflectionFeaturePlugin::InstantReflectionFeaturePlugin( QObject* parent ) :
	QObject( parent ),
	m_reflectionFeature(
		Feature::Uid{ QStringLiteral("b4c5d6e7-f89a-0b1c-2d3e-4f5a6b7c8d9e") },
		tr( "Instant Reflection" ),
		tr( "Allow students to provide instant feedback" ),
		QIcon( QStringLiteral("qrc:/veyon/plugins/instant-reflection/reflection.png") ),
		Feature::Flags( Feature::Flag::SupportsCustomAction )
	),
	m_features( { m_reflectionFeature } )
{
}

const FeatureList& InstantReflectionFeaturePlugin::featureList() const
{
	return m_features;
}

bool InstantReflectionFeaturePlugin::startFeature( VeyonMasterInterface& master, const Feature& /*feature*/,
                                                   const ComputerControlInterfaceList& computerControlInterfaces )
{
    // For this feature, "starting" it from the master simply enables it on the client.
    // The master is always listening for status updates.
    // We can, however, send a message to prompt the student.
    for( const auto& computerControlInterface : computerControlInterfaces )
    {
        computerControlInterface->sendFeatureMessage( m_reflectionFeature.uid, 0, {} );
    }
    master.registerFeatureMessageHandler( this, m_reflectionFeature.uid );
	return true;
}

bool InstantReflectionFeaturePlugin::handleFeatureMessage( VeyonMasterInterface& master, const MessageContext& messageContext,
                                                           const FeatureMessage& message )
{
    if( message.command() == Commands::SetReflectionStatus )
    {
        int status = message.data().value( QString::number(Arguments::Status) ).toInt();
        QString iconName;
        switch( status )
        {
            case 0: iconName = QStringLiteral("qrc:/veyon/plugins/instant-reflection/status-done.png"); break;
            case 1: iconName = QStringLiteral("qrc:/veyon/plugins/instant-reflection/status-help.png"); break;
            case 2: iconName = QStringLiteral("qrc:/veyon/plugins/instant-reflection/status-unclear.png"); break;
            default: iconName = QString(); break;
        }

        master.setComputerOverlayIcon( messageContext.computerUid(), QIcon( iconName ) );
        return true;
    }
    return false;
}

bool InstantReflectionFeaturePlugin::handleFeatureMessage( VeyonWorkerInterface& worker, const FeatureMessage& /*message*/ )
{
    ReflectionStatusDialog* dialog = new ReflectionStatusDialog( QApplication::activeWindow() );
    connect( dialog, &ReflectionStatusDialog::statusSelected, this, [=, &worker]( int status ) {
        QVariantMap data;
        data.insert( QString::number(Arguments::Status), status );
        worker.sendFeatureMessage( m_reflectionFeature.uid, Commands::SetReflectionStatus, data );
    });
    dialog->show();
    return true;
}