#ifndef ENTRYPANE_H
#define ENTRYPANE_H

#include <QWidget>
#include <QHBoxLayout>
#include <vector>
#include "datamodel.h"
#include "entryviewerpane.h"

/* Outer Widget on the left pane.
 * Manages a scroll pane that contains a bunch of EntryViewerPanes
 */
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
