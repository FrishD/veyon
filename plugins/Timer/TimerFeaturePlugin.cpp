/*
 * TimerFeaturePlugin.cpp - implementation of TimerFeature class
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

#include "TimerFeaturePlugin.h"

#include "VeyonMasterInterface.h"
#include "VeyonWorkerInterface.h"
#include "ComputerControlInterface.h"
#include "FeatureMessage.h"
#include "TimerDialog.h"

#include <QApplication>
#include <QTime>
#include <QMessageBox>

TimerFeaturePlugin::TimerFeaturePlugin( QObject* parent ) :
	QObject( parent ),
	m_timerFeature(
		Feature::Uid{ QStringLiteral("f2e6668b-9c12-4b29-9bfc-ff89f6604175") },
		tr( "Timer" ),
		tr( "Show a countdown timer to students" ),
		QIcon( QStringLiteral("qrc:/veyon/plugins/timer/dialog-information.png") ),
		Feature::Flags( Feature::Flag::SupportsCustomAction | Feature::Flag::SupportsStop )
	),
	m_features( { m_timerFeature } )
{
}

const FeatureList& TimerFeaturePlugin::featureList() const
{
	return m_features;
}

bool TimerFeaturePlugin::startFeature( VeyonMasterInterface& master, const Feature& /*feature*/,
									   const ComputerControlInterfaceList& computerControlInterfaces )
{
	TimerDialog dialog( QApplication::activeWindow() );
	if( dialog.exec() == QDialog::Accepted )
	{
		QVariantMap data;
		data.insert( QStringLiteral( "duration" ), dialog.duration().toString( "hh:mm:ss" ) );

		for( const auto& computerControlInterface : computerControlInterfaces )
		{
			computerControlInterface->sendFeatureMessage( m_timerFeature.uid, Commands::ShowTimer, data );
		}
		return true;
	}

	return false;
}

bool TimerFeaturePlugin::handleFeatureMessage( VeyonWorkerInterface& worker, const FeatureMessage& message )
{
	if( message.command() == Commands::ShowTimer )
	{
		QTime duration = QTime::fromString( message.data().value( "duration" ).toString(), "hh:mm:ss" );
		worker.showTimer( duration );
		return true;
	}
	else if( message.command() == Commands::StopTimer )
	{
		worker.hideTimer();
		return true;
	}

	return false;
}