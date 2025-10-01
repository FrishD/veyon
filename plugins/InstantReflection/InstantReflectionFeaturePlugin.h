/*
 * InstantReflectionFeaturePlugin.h - declaration of InstantReflectionFeature class
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

#pragma once

#include "Feature.h"
#include "FeatureProviderInterface.h"
#include "VeyonMasterInterface.h"

class InstantReflectionFeaturePlugin : public QObject, FeatureProviderInterface, PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "io.veyon.Veyon.Plugins.InstantReflection")
	Q_INTERFACES(PluginInterface FeatureProviderInterface)
public:
	explicit InstantReflectionFeaturePlugin( QObject* parent = nullptr );
	~InstantReflectionFeaturePlugin() override = default;

	Plugin::Uid uid() const override
	{
		return Plugin::Uid{ QStringLiteral("b4c5d6e7-f89a-0b1c-2d3e-4f5a6b7c8d9e") };
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
		return tr( "Allow students to provide instant feedback" );
	}

	QString vendor() const override
	{
		return QStringLiteral("Veyon Community");
	}

	QString copyright() const override
	{
		return QStringLiteral("Your Name");
	}

	const FeatureList& featureList() const override;

    bool startFeature( VeyonMasterInterface& master, const Feature& feature,
                       const ComputerControlInterfaceList& computerControlInterfaces ) override;

    bool handleFeatureMessage( VeyonMasterInterface& master, const MessageContext& messageContext,
                               const FeatureMessage& message ) override;

    bool handleFeatureMessage( VeyonWorkerInterface& worker, const FeatureMessage& message ) override;

private:
	enum Commands {
		SetReflectionStatus
	};

    enum Arguments {
        Status
    };

	const Feature m_reflectionFeature;
	const FeatureList m_features;
};