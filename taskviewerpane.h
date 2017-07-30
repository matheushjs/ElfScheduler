#ifndef TASKVIEWERPANE_H
#define TASKVIEWERPANE_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include "datamodel.h"

/* Inner widget of the left pane.
 * Parent widget should be TaskPane.
 * This widget presents the list of tasks the user currently have.
 * There is also a button for adding a new task.
 */
class TaskViewerPane : public QWidget
{
	Q_OBJECT

	QListWidget *d_list;
	QPushButton *d_button;
	DataModel &d_model;

	void setupUI();

public:
	explicit TaskViewerPane(DataModel &model, QWidget *parent = 0);

signals:
	void addClicked();
	void editClicked(int id);

public slots:
	void makeView();
};

#endif // TASKVIEWERPANE_H
