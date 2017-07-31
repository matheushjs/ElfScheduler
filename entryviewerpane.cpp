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


#include "entryviewerpane.h"

#include <QVBoxLayout>
#include <string>
#include <vector>

using std::string;
using std::vector;

EntryViewerPane::EntryViewerPane(int taskId, DataModel &model, QWidget *parent)
	: QWidget(parent),
	  d_header(new QLabel(this)),
	  d_list(new QListWidget(this)),
	  d_line(new QLineEdit(this)),
	  d_model(model),
	  d_taskId(taskId)
{
	setupUI();

	connect(d_line, SIGNAL(returnPressed()), this, SLOT(addInputTask()));
	connect(&d_model, SIGNAL(taskEdited(int)), this, SLOT(checkTaskChanged(int)));
}

void EntryViewerPane::setupUI(){
	QVBoxLayout *box = new QVBoxLayout(this);

	box->addWidget(d_header);
	box->addWidget(d_list);
	box->addWidget(d_line);

	d_header->setText(d_model.getTitle(d_taskId).c_str());
	for(string &str: d_model.getEntry(d_taskId)){
		d_list->addItem(QString(str.c_str()));
	}

	setFocusProxy(d_line);
	setFocusPolicy(Qt::StrongFocus);
	d_list->setFocusPolicy(Qt::NoFocus);

	setLayout(box);
}

void EntryViewerPane::addInputTask(){
	string str = d_line->text().toStdString();
	d_line->setText("");
	if(str == "") return;

	d_list->insertItem(0, str.c_str());
	d_model.addEntry(d_taskId, str);
}

void EntryViewerPane::checkTaskChanged(int taskId){
	if(d_taskId != taskId)
		return;

	d_header->setText(d_model.getTitle(taskId).c_str());
}

int EntryViewerPane::getId(){
	return d_taskId;
}
