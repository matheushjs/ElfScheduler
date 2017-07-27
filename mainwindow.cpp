#include "mainwindow.h"
#include "taskpane.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	auto *centralWidget = new QWidget(this);
	auto *mainBox = new QHBoxLayout(centralWidget);

	auto *leftWid = new TaskPane();
	auto *but2 = new QPushButton("Hello", this);

	mainBox->addWidget(leftWid);
	mainBox->addWidget(but2);
	centralWidget->setLayout(mainBox);

	this->setCentralWidget(centralWidget);
}
