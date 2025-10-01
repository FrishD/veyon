/*
 * TimerDialog.cpp - implementation of TimerDialog class
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

#include "TimerDialog.h"
#include "ui_TimerDialog.h"

TimerDialog::TimerDialog( QWidget* parent ) :
	QDialog( parent ),
	ui( new Ui::TimerDialog )
{
	ui->setupUi( this );
	ui->timeEdit->setTime( QTime( 0, 5, 0 ) ); // Default to 5 minutes
}

TimerDialog::~TimerDialog()
{
	delete ui;
}

QTime TimerDialog::duration() const
{
	return ui->timeEdit->time();
}