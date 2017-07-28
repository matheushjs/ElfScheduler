#ifndef TASKVIEWERPANE_H
#define TASKVIEWERPANE_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>

class TaskViewerPane : public QWidget
{
	Q_OBJECT

	QListWidget *d_list;
	QPushButton *d_button;

public:
	explicit TaskViewerPane(QWidget *parent = 0);

signals:

public slots:
};

#endif // TASKVIEWERPANE_H
