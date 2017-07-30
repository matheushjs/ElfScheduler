#include "mainwindow.h"
#include "taskpane.h"
#include "entrypane.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(DataModel &model, QWidget *parent) :
	QMainWindow(parent),
	d_model(model)
{
	setupUI();
}

void MainWindow::setupUI(){
	auto *centralWidget = new QWidget(this);
	auto *mainBox = new QHBoxLayout(centralWidget);

	auto *leftWid = new TaskPane(d_model, centralWidget);
	auto *rightWid = new EntryPane(d_model, centralWidget);

	leftWid->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
	rightWid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	mainBox->addWidget(leftWid);
	mainBox->addWidget(rightWid);
	centralWidget->setLayout(mainBox);

	this->setCentralWidget(centralWidget);
}
