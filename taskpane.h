#ifndef TASKPANE_H
#define TASKPANE_H

#include <QWidget>
#include <QVBoxLayout>
#include "datamodel.h"
#include "taskeditorpane.h"
#include "taskviewerpane.h"

class TaskPane : public QWidget
{
	Q_OBJECT

	TaskEditorPane *d_editPane;
	TaskViewerPane *d_viewPane;
	DataModel &d_model;

	void setupUI();

public:
	explicit TaskPane(DataModel &model, QWidget *parent = 0);
	~TaskPane();

signals:

private slots:
	void showView();
	void showEdit(int id);

public slots:
};

#endif // TASKPANE_H
