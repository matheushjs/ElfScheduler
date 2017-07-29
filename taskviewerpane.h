#ifndef TASKVIEWERPANE_H
#define TASKVIEWERPANE_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include "datamodel.h"

class TaskViewerPane : public QWidget
{
	Q_OBJECT

	QListWidget *d_list;
	QPushButton *d_button;
	DataModel &d_model;

public:
	explicit TaskViewerPane(DataModel &model, QWidget *parent = 0);

signals:

public slots:
};

#endif // TASKVIEWERPANE_H
