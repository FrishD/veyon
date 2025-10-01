/*
 * ClassroomTimerDialog.cpp - implementation of classroom timer dialog class
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

#include "ClassroomTimerDialog.h"
#include "VeyonCore.h"

#include "ui_ClassroomTimerDialog.h"


ClassroomTimerDialog::ClassroomTimerDialog( int &durationInSeconds, bool &lockOnFinish, QWidget *parent ) :
	QDialog( parent ),
	ui( new Ui::ClassroomTimerDialog ),
	m_durationInSeconds( durationInSeconds ),
	m_lockOnFinish( lockOnFinish )
{
	ui->setupUi( this );

	VeyonCore::enforceBranding( this );
}



ClassroomTimerDialog::~ClassroomTimerDialog()
{
	delete ui;
}



void ClassroomTimerDialog::accept()
{
	const auto minutes = ui->minutesSpinBox->value();
	const auto seconds = ui->secondsSpinBox->value();
	m_durationInSeconds = (minutes * 60) + seconds;
	m_lockOnFinish = ui->lockOnFinishCheckBox->isChecked();
	QDialog::accept();
}