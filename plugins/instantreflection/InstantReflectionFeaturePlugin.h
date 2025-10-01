/*
 * InstantReflectionFeaturePlugin.h - declaration of InstantReflectionFeature class
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

#pragma once

#include "Feature.h"
#include "FeatureProviderInterface.h"

class ReflectionStatusDialog;
class MessageContext;

class InstantReflectionFeaturePlugin : public QObject, FeatureProviderInterface, PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "io.veyon.Veyon.Plugins.InstantReflection")
	Q_INTERFACES(PluginInterface FeatureProviderInterface)
public:
	enum class Argument {
		Status
	};
	Q_ENUM(Argument)

	enum class Status {
		Finished,
		NeedHelp,
		Unclear
	};
	Q_ENUM(Status)

	explicit InstantReflectionFeaturePlugin( QObject* parent = nullptr );
	~InstantReflectionFeaturePlugin() override;

	Plugin::Uid uid() const override
	{
		return Plugin::Uid{ QStringLiteral("d1a8c3c3-6b69-40de-8e69-537f0e69a53d") };
	}

	QVersionNumber version() const override
	{
		return QVersionNumber( 1, 0 );
	}

	QString name() const override
	{
		return tr( "Instant Reflection" );
	}

	QString description() const override
	{
		return tr( "Allow students to send a reflection status to the teacher." );
	}

	QString vendor() const override
	{
		return QStringLiteral("Veyon Community");
	}

	QString copyright() const override
	{
		return QStringLiteral("Veyon Community");
	}

	const FeatureList& featureList() const override;

	bool controlFeature( Feature::Uid featureUid, Operation operation, const QVariantMap& arguments,
						const ComputerControlInterfaceList& computerControlInterfaces ) override;

	bool startFeature( VeyonMasterInterface& master, const Feature& feature,
					   const ComputerControlInterfaceList& computerControlInterfaces ) override;

	bool handleFeatureMessage( VeyonMasterInterface& master, const MessageContext& messageContext, const FeatureMessage& message );

	bool handleFeatureMessage( VeyonServerInterface& server,
							   const MessageContext& messageContext,
							   const FeatureMessage& message ) override;

	bool handleFeatureMessage( VeyonWorkerInterface& worker, const FeatureMessage& message ) override;

private:
	enum Commands {
		ShowReflectionButtons,
		ReflectionResponse
	};

	const Feature m_instantReflectionFeature;
	const FeatureList m_features;
	ReflectionStatusDialog* m_statusDialog = nullptr;
};