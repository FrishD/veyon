#pragma once

#include <QDialog>
#include <QMap>
#include "InstantReflectionFeaturePlugin.h"

namespace Ui
{
	class ReflectionStatusDialog;
}

class ReflectionStatusDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ReflectionStatusDialog(QWidget* parent = nullptr);
	~ReflectionStatusDialog() override;

public slots:
	void updateStatus(const QString& userName, InstantReflectionFeaturePlugin::Status status);

private:
	Ui::ReflectionStatusDialog* ui;
	QMap<QString, InstantReflectionFeaturePlugin::Status> m_studentStatus;
};