#include "ReflectionWidget.h"
#include "ui_ReflectionWidget.h"

ReflectionWidget::ReflectionWidget(QWidget* parent)
	: QWidget(parent),
	  ui(new Ui::ReflectionWidget)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);

	connect(ui->finishedButton, &QPushButton::clicked, this, &ReflectionWidget::onFinishedClicked);
	connect(ui->needHelpButton, &QPushButton::clicked, this, &ReflectionWidget::onNeedHelpClicked);
	connect(ui->unclearButton, &QPushButton::clicked, this, &ReflectionWidget::onUnclearClicked);
}

ReflectionWidget::~ReflectionWidget()
{
	delete ui;
}

void ReflectionWidget::onFinishedClicked()
{
	emit statusSelected(InstantReflectionFeaturePlugin::Status::Finished);
	close();
}

void ReflectionWidget::onNeedHelpClicked()
{
	emit statusSelected(InstantReflectionFeaturePlugin::Status::NeedHelp);
	close();
}

void ReflectionWidget::onUnclearClicked()
{
	emit statusSelected(InstantReflectionFeaturePlugin::Status::Unclear);
	close();
}