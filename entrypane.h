#ifndef ENTRYPANE_H
#define ENTRYPANE_H

#include <QWidget>
#include <QHBoxLayout>
#include "datamodel.h"

class EntryPane : public QWidget
{
	Q_OBJECT

	QHBoxLayout *d_box;
	DataModel &d_model;

	void setupUI();
	void addTask(int taskId);

public:
	explicit EntryPane(DataModel &model, QWidget *parent = 0);

signals:

public slots:
};

#endif // ENTRYPANE_H
