/*
 * PollResultsDialog.h - declaration of PollResultsDialog class
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

#include "FeatureMessageHandlerInterface.h"

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QMap>

namespace Ui {
class PollResultsDialog;
}

class VeyonMasterInterface;

class PollResultsDialog : public QDialog, public FeatureMessageHandlerInterface
{
	Q_OBJECT

public:
	explicit PollResultsDialog( VeyonMasterInterface& master, int totalStudents, const QString& question, const QStringList& answers, QWidget* parent = nullptr );
	~PollResultsDialog();

    bool handleFeatureMessage( const MessageContext& messageContext, const FeatureMessage& message ) override;

private slots:
    void updateResults();

private:
	Ui::PollResultsDialog* ui;
    VeyonMasterInterface& m_master;
    int m_totalStudents;
    QStringList m_answers;
    QMap<int, int> m_results; // answer index -> count
    int m_responses = 0;
};