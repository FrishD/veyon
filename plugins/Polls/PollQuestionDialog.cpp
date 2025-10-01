/*
 * PollQuestionDialog.cpp - implementation of PollQuestionDialog class
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

#include "PollQuestionDialog.h"
#include "ui_PollQuestionDialog.h"

#include <QRadioButton>
#include <QPushButton>

PollQuestionDialog::PollQuestionDialog( const QString& question, const QStringList& answers, QWidget* parent ) :
	QDialog( parent ),
	ui( new Ui::PollQuestionDialog )
{
	ui->setupUi( this );
	ui->questionLabel->setText( question );

	QButtonGroup* buttonGroup = new QButtonGroup( this );

	for( int i = 0; i < answers.count(); ++i )
	{
		QRadioButton* radioButton = new QRadioButton( answers.at( i ), this );
		ui->answersLayout->addWidget( radioButton );
		buttonGroup->addButton( radioButton, i );
	}

    connect( buttonGroup, QOverload<int>::of(&QButtonGroup::idClicked), [this]( int id ) {
        m_selectedAnswer = id;
        ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( true );
    });

    ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );
}

PollQuestionDialog::~PollQuestionDialog()
{
	delete ui;
}

int PollQuestionDialog::selectedAnswer() const
{
	return m_selectedAnswer;
}