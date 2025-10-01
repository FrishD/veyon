/*
 * PollsFeaturePlugin.h - declaration of PollsFeature class
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

class PollsFeaturePlugin : public QObject, FeatureProviderInterface, PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "io.veyon.Veyon.Plugins.Polls")
	Q_INTERFACES(PluginInterface FeatureProviderInterface)
public:
	explicit PollsFeaturePlugin( QObject* parent = nullptr );
	~PollsFeaturePlugin() override = default;

	Plugin::Uid uid() const override
	{
		return Plugin::Uid{ QStringLiteral("a3b4c5d6-e7f8-9a0b-1c2d-3e4f5a6b7c8d") };
	}

	QVersionNumber version() const override
	{
		return QVersionNumber( 1, 0 );
	}

	QString name() const override
	{
		return tr( "Polls" );
	}

	QString description() const override
	{
		return tr( "Ask a question and get immediate feedback" );
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
		ShowPoll,
        SubmitAnswer
	};

    enum Arguments {
        Question,
        Answers
    };

	const Feature m_pollsFeature;
	const FeatureList m_features;
};