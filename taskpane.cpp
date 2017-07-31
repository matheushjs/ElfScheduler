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


#include "taskpane.h"

#include "taskeditorpane.h"
#include "taskviewerpane.h"

#include <QVBoxLayout>

TaskPane::TaskPane(DataModel &model, QWidget *parent)
	: QWidget(parent),
	  d_editPane(new TaskEditorPane(model)),
	  d_viewPane(new TaskViewerPane(model)),
	  d_model(model)
{
	setupUI();

	connect(d_viewPane, &TaskViewerPane::addClicked,
			this, [this](){showEdit(TaskEditorPane::NEW_TASK);} );

	connect(d_viewPane, SIGNAL(editClicked(int)), this, SLOT(showEdit(int)));

	connect(d_editPane, SIGNAL(finished()), this, SLOT(showView()));
}

void TaskPane::setupUI(){
	setLayout(new QVBoxLayout(this));
	showView();
}

TaskPane::~TaskPane(){
	delete d_editPane;
	delete d_viewPane;
}

void TaskPane::showEdit(int id){
	d_editPane->setTask(id);
	layout()->addWidget(d_editPane);
	layout()->removeWidget(d_viewPane);
	d_editPane->show();
	d_viewPane->hide();
}

void TaskPane::showView(){
	layout()->addWidget(d_viewPane);
	layout()->removeWidget(d_editPane);
	d_viewPane->show();
	d_editPane->hide();
}
