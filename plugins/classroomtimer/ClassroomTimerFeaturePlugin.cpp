/*
 * ClassroomTimerFeaturePlugin.cpp - implementation of ClassroomTimerFeaturePlugin class
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

#include "ClassroomTimerFeaturePlugin.h"
#include "ClassroomTimerDialog.h"
#include "FeatureWorkerManager.h"
#include "ComputerControlInterface.h"
#include "VeyonMasterInterface.h"
#include "VeyonServerInterface.h"
#include "VeyonWorkerInterface.h"
#include "TimerWidget.h"


ClassroomTimerFeaturePlugin::ClassroomTimerFeaturePlugin( QObject* parent ) :
	QObject( parent ),
	m_classroomTimerFeature( Feature( QStringLiteral( "ClassroomTimer" ),
								   Feature::Flag::Action | Feature::Flag::AllComponents,
								   Feature::Uid( "a732b26c-32b8-4af9-8a18-62a2c04e3f7b" ),
								   Feature::Uid(),
								   tr( "Classroom Timer" ), {},
								   tr( "Use this function to start a countdown timer for all students." ),
								   QStringLiteral(":/classroomtimer/timer.png") ) ),
	m_features( { m_classroomTimerFeature } )
{
}



const FeatureList &ClassroomTimerFeaturePlugin::featureList() const
{
	return m_features;
}



bool ClassroomTimerFeaturePlugin::controlFeature( Feature::Uid featureUid,
											  Operation operation,
											  const QVariantMap& arguments,
											  const ComputerControlInterfaceList& computerControlInterfaces )
{
	if( operation != Operation::Start )
	{
		return false;
	}

	if( featureUid == m_classroomTimerFeature.uid() )
	{
		const auto duration = arguments.value( argToString(Argument::DurationInSeconds) ).toInt();
		const auto lockOnFinish = arguments.value( argToString(Argument::LockOnFinish) ).toBool();

		sendFeatureMessage( FeatureMessage{ featureUid, StartTimer }
								.addArgument( Argument::DurationInSeconds, duration )
								.addArgument( Argument::LockOnFinish, lockOnFinish ), computerControlInterfaces );

		return true;
	}

	return false;
}



bool ClassroomTimerFeaturePlugin::startFeature( VeyonMasterInterface& master, const Feature& feature,
											 const ComputerControlInterfaceList& computerControlInterfaces )
{
	if( feature.uid() != m_classroomTimerFeature.uid() )
	{
		return false;
	}

	int durationInSeconds = 0;
	bool lockOnFinish = false;

	ClassroomTimerDialog( durationInSeconds, lockOnFinish, master.mainWindow() ).exec();

	if( durationInSeconds > 0 )
	{
		controlFeature( m_classroomTimerFeature.uid(), Operation::Start,
						{
							{ argToString(Argument::DurationInSeconds), durationInSeconds },
							{ argToString(Argument::LockOnFinish), lockOnFinish }
						},
						computerControlInterfaces );
	}

	return true;
}




bool ClassroomTimerFeaturePlugin::handleFeatureMessage( VeyonServerInterface& server,
													 const MessageContext& messageContext,
													 const FeatureMessage& message )
{
	Q_UNUSED(messageContext)

	if( m_classroomTimerFeature.uid() == message.featureUid() )
	{
		// forward message to worker
		server.featureWorkerManager().sendMessageToAllSessionWorkers( message );
		return true;
	}

	return false;
}



bool ClassroomTimerFeaturePlugin::handleFeatureMessage( VeyonWorkerInterface& worker, const FeatureMessage& message )
{
	Q_UNUSED(worker);

	if( message.featureUid() == m_classroomTimerFeature.uid() )
	{
		const auto duration = message.argument( Argument::DurationInSeconds ).toInt();
		const auto lockOnFinish = message.argument( Argument::LockOnFinish ).toBool();

		if (duration > 0)
		{
			auto* timerWidget = new TimerWidget(duration, lockOnFinish);
			timerWidget->show();
		}
		return true;
	}

	return true;
}