#include "TimerWidget.h"
#include "ui_TimerWidget.h"
#include <QScreen>
#include <QApplication>

TimerWidget::TimerWidget(int durationInSeconds, bool lockOnFinish, QWidget* parent)
	: QWidget(parent),
	  ui(new Ui::TimerWidget),
	  m_remainingSeconds(durationInSeconds),
	  m_lockOnFinish(lockOnFinish)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);

	connect(&m_timer, &QTimer::timeout, this, &TimerWidget::updateTimer);
	m_timer.start(1000);
	updateTimer();

	// Center the widget on the primary screen
	const auto primaryScreen = QGuiApplication::primaryScreen();
	if (primaryScreen)
	{
		const auto screenGeometry = primaryScreen->geometry();
		move(screenGeometry.center() - rect().center());
	}
}

TimerWidget::~TimerWidget()
{
	delete ui;
	delete m_lockWidget;
}

void TimerWidget::updateTimer()
{
	if (m_remainingSeconds <= 0)
	{
		m_timer.stop();
		if (m_lockOnFinish)
		{
			lockScreen();
		}
		close();
		return;
	}

	const auto minutes = m_remainingSeconds / 60;
	const auto seconds = m_remainingSeconds % 60;
	ui->timerLabel->setText(QStringLiteral("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0')));
	m_remainingSeconds--;
}

void TimerWidget::lockScreen()
{
	if(m_lockWidget)
	{
		return;
	}
	m_lockWidget = new LockWidget(LockWidget::BackgroundPixmap);
	m_lockWidget->showFullScreen();
}