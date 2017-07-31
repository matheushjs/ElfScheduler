/*
This file is part of ElfScheduler.

Copyright (C) 2017  Matheus H. J. Saldanha

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


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
