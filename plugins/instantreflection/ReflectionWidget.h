#pragma once

#include <QWidget>
#include "InstantReflectionFeaturePlugin.h"

namespace Ui
{
	class ReflectionWidget;
}

class ReflectionWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ReflectionWidget(QWidget* parent = nullptr);
	~ReflectionWidget() override;

signals:
	void statusSelected(InstantReflectionFeaturePlugin::Status status);

private slots:
	void onFinishedClicked();
	void onNeedHelpClicked();
	void onUnclearClicked();

private:
	Ui::ReflectionWidget* ui;
};