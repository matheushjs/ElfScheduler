#ifndef ENTRYPANE_H
#define ENTRYPANE_H

#include <QWidget>
#include <QHBoxLayout>
#include <vector>
#include "datamodel.h"
#include "entryviewerpane.h"

class EntryPane : public QWidget
{
	Q_OBJECT

	QHBoxLayout *d_box;
	DataModel &d_model;
	std::vector<EntryViewerPane*> d_panes;
	QLabel *d_header;

	void setupUI();
	void addTask(int taskId);
	void makeView();

public:
	explicit EntryPane(DataModel &model, QWidget *parent = 0);

signals:

public slots:
};

#endif // ENTRYPANE_H
