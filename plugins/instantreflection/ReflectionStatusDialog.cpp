#include "ReflectionStatusDialog.h"
#include "ui_ReflectionStatusDialog.h"

ReflectionStatusDialog::ReflectionStatusDialog(QWidget* parent)
	: QDialog(parent),
	  ui(new Ui::ReflectionStatusDialog)
{
	ui->setupUi(this);
	ui->statusTableWidget->setColumnCount(2);
	ui->statusTableWidget->setHorizontalHeaderLabels(QStringList() << "Student" << "Status");
}

ReflectionStatusDialog::~ReflectionStatusDialog()
{
	delete ui;
}

void ReflectionStatusDialog::updateStatus(const QString& userName, InstantReflectionFeaturePlugin::Status status)
{
	m_studentStatus[userName] = status;

	ui->statusTableWidget->setRowCount(0);
	for (auto it = m_studentStatus.constBegin(); it != m_studentStatus.constEnd(); ++it)
	{
		const int row = ui->statusTableWidget->rowCount();
		ui->statusTableWidget->insertRow(row);
		ui->statusTableWidget->setItem(row, 0, new QTableWidgetItem(it.key()));

		QString statusText;
		switch (it.value())
		{
			case InstantReflectionFeaturePlugin::Status::Finished:
				statusText = tr("Finished");
				break;
			case InstantReflectionFeaturePlugin::Status::NeedHelp:
				statusText = tr("Need Help");
				break;
			case InstantReflectionFeaturePlugin::Status::Unclear:
				statusText = tr("Unclear");
				break;
		}
		auto* statusItem = new QTableWidgetItem(statusText);
		ui->statusTableWidget->setItem(row, 1, statusItem);
	}
}