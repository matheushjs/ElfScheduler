#ifndef ENTRYVIEWERPANE_H
#define ENTRYVIEWERPANE_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "datamodel.h"

/* Widget for viewing the log for a task.
 * Newer log items appear on top of the QListWidget
 */
class EntryViewerPane : public QWidget
{
	Q_OBJECT

	QLabel *d_header;
	QListWidget *d_list;
	QLineEdit *d_line;
	DataModel &d_model;
	int d_taskId;

	void setupUI();

public:
	explicit EntryViewerPane(int taskId, DataModel &model, QWidget *parent = 0);
	int getId();

signals:

private slots:
	void addInputTask();
	void checkTaskChanged(int taskId);

public slots:
};

#endif // ENTRYVIEWERPANE_H
