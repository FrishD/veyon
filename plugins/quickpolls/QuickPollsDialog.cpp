/*
 * QuickPollsDialog.cpp - implementation of quick polls dialog class
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

#include "QuickPollsDialog.h"
#include "VeyonCore.h"
#include "ui_QuickPollsDialog.h"
#include <QListWidgetItem>


QuickPollsDialog::QuickPollsDialog( QString &question, QStringList &answers, QWidget *parent ) :
	QDialog( parent ),
	ui( new Ui::QuickPollsDialog ),
	m_question( question ),
	m_answers( answers )
{
	ui->setupUi( this );

	connect(ui->addAnswerButton, &QPushButton::clicked, this, &QuickPollsDialog::addAnswer);
	connect(ui->removeAnswerButton, &QPushButton::clicked, this, &QuickPollsDialog::removeAnswer);

	VeyonCore::enforceBranding( this );
}



QuickPollsDialog::~QuickPollsDialog()
{
	delete ui;
}

void QuickPollsDialog::addAnswer()
{
	auto* item = new QListWidgetItem(ui->answersListWidget);
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	ui->answersListWidget->addItem(item);
	ui->answersListWidget->editItem(item);
}

void QuickPollsDialog::removeAnswer()
{
	qDeleteAll(ui->answersListWidget->selectedItems());
}


void QuickPollsDialog::accept()
{
	m_question = ui->questionLineEdit->text();
	m_answers.clear();
	for(int i = 0; i < ui->answersListWidget->count(); ++i)
	{
		m_answers.append(ui->answersListWidget->item(i)->text());
	}
	QDialog::accept();
}