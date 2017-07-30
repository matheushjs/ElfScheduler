#ifndef ENTRYVIEWERPANE_H
#define ENTRYVIEWERPANE_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "datamodel.h"

class EntryViewerPane : public QWidget
{
	Q_OBJECT

	QLabel *d_header;
	QListWidget *d_list;
	QPushButton *d_but;
	QLineEdit *d_line;
	DataModel &d_model;
	int d_taskId;

	void setupUI();
	void addInputTask();

public:
	explicit EntryViewerPane(int taskId, DataModel &model, QWidget *parent = 0);

signals:

public slots:
};

#endif // ENTRYVIEWERPANE_H
