#include "mainwindow.h"
#include "taskpane.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(DataModel &model, QWidget *parent) :
	QMainWindow(parent),
	d_model(model)
{
	auto *centralWidget = new QWidget(this);
	auto *mainBox = new QHBoxLayout(centralWidget);

	auto *leftWid = new TaskPane(model);
	auto *but2 = new QPushButton("Hello", this);

	mainBox->addWidget(leftWid);
	mainBox->addWidget(but2);
	centralWidget->setLayout(mainBox);

	this->setCentralWidget(centralWidget);
}
