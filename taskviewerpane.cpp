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


#include "taskviewerpane.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QListWidgetItem>

#include <string>
#include <iostream>

using std::string;

TaskViewerPane::TaskViewerPane(DataModel &model, QWidget *parent)
	: QWidget(parent),
	  d_list(new QListWidget(this)),
	  d_button(new QPushButton("New Task", this)),
	  d_model(model)
{
	setupUI();

	// Whenever the data is changed, fill the list widget again.
	makeView();
	connect(&model, SIGNAL(taskEdited(int)), this, SLOT(makeView()));
	connect(&model, SIGNAL(taskRemoved(int)), this, SLOT(makeView()));
	connect(&model, SIGNAL(taskAdded(int)), this, SLOT(makeView()));

	// Re-emit the button signal
	connect(d_button, SIGNAL(clicked(bool)), this, SIGNAL(addClicked()));

	// Emit the editing signal
	connect(d_list, &QListWidget::itemDoubleClicked,
			this, [this](QListWidgetItem *item){ emit this->editClicked(item->type());});
}

void TaskViewerPane::setupUI(){
	auto *box = new QVBoxLayout(this);
	auto *butBox = new QHBoxLayout();

	butBox->setAlignment(d_button, Qt::AlignCenter);
	butBox->addStretch(1);
	butBox->addWidget(d_button);
	butBox->addStretch(1);

	QLabel *lbl = new QLabel("Your Tasks", this);
	box->addWidget(lbl, 0, Qt::AlignCenter);
	box->addWidget(d_list);
	box->addLayout(butBox);

	setLayout(box);
}

void TaskViewerPane::makeView(){
	d_list->clear();
	for(int i: d_model.getIds()){
		new QListWidgetItem(d_model.getTitle(i).c_str(), d_list, i);
	}
}
