#ifndef TASKEDITORPANE_H
#define TASKEDITORPANE_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <vector>

class TaskEditorPane : public QWidget
{
	Q_OBJECT

	QLineEdit *d_titleLine;
	std::vector<QCheckBox*> d_daysBox;
	QPushButton *d_delBut;

public:
	explicit TaskEditorPane(QWidget *parent = 0);

signals:

public slots:
};

#endif // TASKEDITORPANE_H
