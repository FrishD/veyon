#pragma once

#include <QWidget>
#include <QStringList>

namespace Ui
{
	class PollWidget;
}

class PollWidget : public QWidget
{
	Q_OBJECT

public:
	explicit PollWidget(const QString& question, const QStringList& answers, QWidget* parent = nullptr);
	~PollWidget() override;

signals:
	void answered(const QString& answer);

private slots:
	void onAnswerClicked();

private:
	Ui::PollWidget* ui;
};