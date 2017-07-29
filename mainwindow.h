#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datamodel.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	DataModel &d_model;

public:
	explicit MainWindow(DataModel &model, QWidget *parent = 0);
};

#endif // MAINWINDOW_H
