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
	int d_week;

	// Receives argument just as reminder that d_week should be initialized.
	void setupUI(int currentWeek);
	void initializeView();

public:
	explicit EntryPane(DataModel &model, QWidget *parent = 0);

signals:

private slots:
	void addTask(int taskId);
	void removeTask(int taskId);
	void checkEditedTask(int taskId);

public slots:
};

#endif // ENTRYPANE_H
