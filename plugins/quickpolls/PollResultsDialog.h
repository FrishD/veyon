#pragma once

#include <QDialog>
#include <QString>
#include <QMap>

namespace Ui
{
	class PollResultsDialog;
}

class PollResultsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PollResultsDialog(const QString& question, const QStringList& answers, QWidget* parent = nullptr);
	~PollResultsDialog() override;

public slots:
	void addResponse(const QString& answer);

private:
	void updateChart();

	Ui::PollResultsDialog* ui;
	QString m_question;
	QMap<QString, int> m_responses;
};