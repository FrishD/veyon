/*
 * ReflectionStatusDialog.cpp - implementation of ReflectionStatusDialog class
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

#include "ReflectionStatusDialog.h"
#include "ui_ReflectionStatusDialog.h"

ReflectionStatusDialog::ReflectionStatusDialog( QWidget* parent ) :
	QDialog( parent ),
	ui( new Ui::ReflectionStatusDialog )
{
	ui->setupUi( this );
    setWindowFlags( Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
    setAttribute( Qt::WA_DeleteOnClose );
}

ReflectionStatusDialog::~ReflectionStatusDialog()
{
	delete ui;
}

void ReflectionStatusDialog::on_doneButton_clicked()
{
    emit statusSelected( 0 );
    close();
}

void ReflectionStatusDialog::on_helpButton_clicked()
{
    emit statusSelected( 1 );
    close();
}

void ReflectionStatusDialog::on_unclearButton_clicked()
{
    emit statusSelected( 2 );
    close();
}