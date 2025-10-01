#include "PollResultsDialog.h"
#include "ui_PollResultsDialog.h"

#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

PollResultsDialog::PollResultsDialog(const QString& question, const QStringList& answers, QWidget* parent)
	: QDialog(parent),
	  ui(new Ui::PollResultsDialog),
	  m_question(question)
{
	ui->setupUi(this);
	ui->questionLabel->setText(m_question);

	for (const auto& answer : answers)
	{
		m_responses.insert(answer, 0);
	}

	updateChart();
}

PollResultsDialog::~PollResultsDialog()
{
	delete ui;
}

void PollResultsDialog::addResponse(const QString& answer)
{
	if (m_responses.contains(answer))
	{
		m_responses[answer]++;
		updateChart();
	}
}

void PollResultsDialog::updateChart()
{
	auto* series = new QBarSeries(this);
	for (auto it = m_responses.constBegin(); it != m_responses.constEnd(); ++it)
	{
		auto* set = new QBarSet(it.key(), series);
		*set << it.value();
		series->append(set);
	}

	auto* chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("Poll Results");
	chart->setAnimationOptions(QChart::SeriesAnimations);

	QStringList categories;
	categories << ""; // Bar series are grouped by category, one empty category is enough

	auto* axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	auto* axisY = new QValueAxis();
	axisY->setLabelFormat("%i");
	axisY->setTitleText("Votes");
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	ui->chartView->setChart(chart);
	ui->chartView->setRenderHint(QPainter::Antialiasing);
}