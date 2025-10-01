/*
 * PollResultsDialog.cpp - implementation of PollResultsDialog class
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

#include "PollResultsDialog.h"
#include "ui_PollResultsDialog.h"
#include "VeyonMasterInterface.h"
#include "FeatureMessage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>

PollResultsDialog::PollResultsDialog( VeyonMasterInterface& master, int totalStudents, const QString& question, const QStringList& answers, QWidget* parent ) :
	QDialog( parent ),
	ui( new Ui::PollResultsDialog ),
    m_master( master ),
    m_totalStudents( totalStudents ),
    m_answers( answers )
{
	ui->setupUi( this );
    setAttribute( Qt::WA_DeleteOnClose );
	ui->questionLabel->setText( question );

    for( int i = 0; i < m_answers.count(); ++i )
    {
        m_results.insert( i, 0 );

        QHBoxLayout* layout = new QHBoxLayout();
        QLabel* answerLabel = new QLabel( m_answers.at(i), this );
        answerLabel->setMinimumWidth(100);
        QProgressBar* progressBar = new QProgressBar( this );
        progressBar->setMinimum(0);
        progressBar->setMaximum(m_totalStudents);
        progressBar->setValue(0);
        progressBar->setFormat( "%v" );
        layout->addWidget( answerLabel );
        layout->addWidget( progressBar );
        ui->resultsLayout->addLayout( layout );
    }

    updateResults();
}

PollResultsDialog::~PollResultsDialog()
{
    m_master.unregisterFeatureMessageHandler( this );
	delete ui;
}

bool PollResultsDialog::handleFeatureMessage( const MessageContext& /*messageContext*/, const FeatureMessage& message )
{
    if( message.command() == PollsFeaturePlugin::SubmitAnswer )
    {
        int answerIndex = message.data().value( "answer" ).toInt();
        if( m_results.contains( answerIndex ) )
        {
            m_results[answerIndex]++;
            m_responses++;
            QMetaObject::invokeMethod( this, "updateResults", Qt::QueuedConnection );
        }
        return true;
    }
    return false;
}

void PollResultsDialog::updateResults()
{
    for( int i = 0; i < m_answers.count(); ++i )
    {
        QLayout* layout = ui->resultsLayout->itemAt(i)->layout();
        QProgressBar* progressBar = qobject_cast<QProgressBar*>( layout->itemAt(1)->widget() );
        if( progressBar )
        {
            progressBar->setValue( m_results.value(i) );
        }
    }
    ui->responsesLabel->setText( tr( "%1 of %2 students have responded." ).arg( m_responses ).arg( m_totalStudents ) );
}