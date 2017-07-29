#ifndef TASKPANE_H
#define TASKPANE_H

#include <QWidget>
#include <QVBoxLayout>
#include "datamodel.h"

class TaskPane : public QWidget
{
	Q_OBJECT

	QVBoxLayout *d_editPane;
	QVBoxLayout *d_viewPane;
	DataModel &d_model;

public:
	explicit TaskPane(DataModel &model, QWidget *parent = 0);
	~TaskPane();

signals:

public slots:
};

#endif // TASKPANE_H
