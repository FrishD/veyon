#pragma once

#include <QWidget>
#include <QTimer>

#include "LockWidget.h"

namespace Ui
{
	class TimerWidget;
}

class TimerWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TimerWidget(int durationInSeconds, bool lockOnFinish, QWidget* parent = nullptr);
	~TimerWidget() override;

private slots:
	void updateTimer();

private:
	void lockScreen();

	Ui::TimerWidget* ui;
	QTimer m_timer;
	int m_remainingSeconds;
	bool m_lockOnFinish;
	LockWidget* m_lockWidget = nullptr;
};