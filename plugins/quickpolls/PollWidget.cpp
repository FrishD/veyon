#include "PollWidget.h"
#include "ui_PollWidget.h"

#include <QPushButton>

PollWidget::PollWidget(const QString& question, const QStringList& answers, QWidget* parent)
	: QWidget(parent),
	  ui(new Ui::PollWidget)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);

	ui->questionLabel->setText(question);

	for (const auto& answer : answers)
	{
		auto* button = new QPushButton(answer, this);
		connect(button, &QPushButton::clicked, this, &PollWidget::onAnswerClicked);
		ui->answersLayout->addWidget(button);
	}
}

PollWidget::~PollWidget()
{
	delete ui;
}

void PollWidget::onAnswerClicked()
{
	auto* button = qobject_cast<QPushButton*>(sender());
	if (button)
	{
		emit answered(button->text());
		close();
	}
}