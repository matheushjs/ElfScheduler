#ifndef TASKEDITORPANE_H
#define TASKEDITORPANE_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <vector>
#include "datamodel.h"

class TaskEditorPane : public QWidget
{
	Q_OBJECT

	QLineEdit *d_titleLine;
	std::vector<QCheckBox*> d_daysBox;
	QPushButton *d_delBut;
	QPushButton *d_finBut;
	DataModel &d_model;
	int d_subjectId;

	void processForm(int clickType);

public:
	const static int NEW_TASK;
	const static int NO_TASK;

	explicit TaskEditorPane(DataModel &model, QWidget *parent = 0);
	void setTask(int id);

signals:
	void finished();

public slots:
};

#endif // TASKEDITORPANE_H
