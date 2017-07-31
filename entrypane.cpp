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


#include "entrypane.h"
#include "entryviewerpane.h"

#include <QScrollArea>
#include <QDate>
#include <QTime>
#include <QVBoxLayout>
#include <string>

using std::string;

const static char g_weekdays[][20] = {
	"Sunday", "Monday", "Tuesday", "Wednesday",
	"Thursday", "Friday", "Saturday"
};

EntryPane::EntryPane(DataModel &model, QWidget *parent)
	: QWidget(parent),
	  d_box(new QHBoxLayout()),
	  d_model(model),
	  d_header(new QLabel(this))
{
	// Set up weekday
	d_week = QDate::currentDate().dayOfWeek() % 7; // Makes Sunday get 0
	int hour = QTime::currentTime().hour();
	if(hour < 6)
		d_week = (d_week != 0) ? d_week - 1 : 6 ;

	setupUI(d_week);

	initializeView();

	connect(&model, SIGNAL(taskAdded(int)), this, SLOT(addTask(int)));
	connect(&model, SIGNAL(taskRemoved(int)), this, SLOT(removeTask(int)));
	connect(&model, SIGNAL(taskEdited(int)), this, SLOT(checkEditedTask(int)));
}

void EntryPane::setupUI(int currentWeek){
	d_header->setFont(QFont("Liberation Sans", 14, 5, false));
	d_header->setMargin(5);

	QScrollArea *scroll = new QScrollArea(this);
	QVBoxLayout *outerLay = new QVBoxLayout(this);
	outerLay->addWidget(d_header, 0, Qt::AlignCenter);
	outerLay->addWidget(scroll);
	setLayout(outerLay);

	QWidget *wid = new QWidget(scroll);
	wid->setLayout(d_box);
	scroll->setWidget(wid);
	scroll->setWidgetResizable(true);

	d_header->setText(g_weekdays[currentWeek]);

	setFocusPolicy(Qt::StrongFocus);
}

void EntryPane::addTask(int taskId){
	// Check if the given task should be displayed today
	string weekdays = d_model.getDays(taskId);
	if(weekdays.at(d_week) != 't') return;

	// Add task
	EntryViewerPane *pane = new EntryViewerPane(taskId, d_model, this);
	d_panes.push_back(pane);

	pane->setMaximumWidth(300);
	pane->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	d_box->addWidget(pane);

	// Reset focus order
	for(unsigned int i = 1; i < d_panes.size(); i++){
		this->setTabOrder(d_panes[i-1], d_panes[i]);
	}

	d_panes[0]->setFocus();
}

void EntryPane::checkEditedTask(int taskId){
	bool found;
	string weekdays;

	// Find the due EntryViewerPane
	found = false;
	for(EntryViewerPane *pane: d_panes){
		if(pane->getId() == taskId){
			found = true;
			break;
		}
	}

	if(found){
		//If should not be shown, remove.
		weekdays = d_model.getDays(taskId);
		if(weekdays.at(d_week) == 'f')
			removeTask(taskId);
	} else {
		//addTask already checks weekdays.
		addTask(taskId);
	}
}

void EntryPane::removeTask(int taskId){
	// Find the due EntryViewerPane
	for(auto it = d_panes.begin(); it != d_panes.end(); it++){
		if(taskId == (*it)->getId()){
			delete *it;
			d_panes.erase(it);
			break;
		}
	}
}

void EntryPane::initializeView(){
	for(int id: d_model.getIds()){
		addTask(id);
	}
}
