/*
 * PollDialog.cpp - implementation of PollDialog class
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

#include "PollDialog.h"
#include "ui_PollDialog.h"

#include <QPushButton>

PollDialog::PollDialog( QWidget* parent ) :
	QDialog( parent ),
	ui( new Ui::PollDialog )
{
	ui->setupUi( this );
    connect( ui->questionEdit, &QLineEdit::textChanged, this, &PollDialog::updateButtonStates );
    connect( ui->answersEdit, &QPlainTextEdit::textChanged, this, &PollDialog::updateButtonStates );
    updateButtonStates();
}

PollDialog::~PollDialog()
{
	delete ui;
}

QString PollDialog::question() const
{
	return ui->questionEdit->text();
}

QStringList PollDialog::answers() const
{
	return ui->answersEdit->toPlainText().split( QChar('\n'), Qt::SkipEmptyParts );
}

void PollDialog::updateButtonStates()
{
    bool enabled = !ui->questionEdit->text().isEmpty() && !ui->answersEdit->toPlainText().isEmpty();
    ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( enabled );
}