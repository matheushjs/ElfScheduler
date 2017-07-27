#ifndef TASKPANE_H
#define TASKPANE_H

#include <QWidget>
#include <QVBoxLayout>

class TaskPane : public QWidget
{
	Q_OBJECT

	QVBoxLayout *editPane;
	QVBoxLayout *viewPane;

public:
	explicit TaskPane(QWidget *parent = 0);
	~TaskPane();

signals:

public slots:
};

#endif // TASKPANE_H
