#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datamodel.h"

/* Global parent widget
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

	DataModel &d_model;

	void setupUI();

public:
	explicit MainWindow(DataModel &model, QWidget *parent = 0);
};

#endif // MAINWINDOW_H
