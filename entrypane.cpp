#include "entrypane.h"
#include "entryviewerpane.h"

#include <QScrollArea>
#include <QDate>
#include <QTime>
#include <QVBoxLayout>
#include <string>

using std::string;

EntryPane::EntryPane(DataModel &model, QWidget *parent)
	: QWidget(parent),
	  d_box(new QHBoxLayout()),
	  d_model(model),
	  d_header(new QLabel(this))
{
	setupUI();
	makeView();
	connect(&model, &DataModel::dataChanged, this, &EntryPane::makeView);
}

void EntryPane::setupUI(){
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
}

void EntryPane::addTask(int taskId){
	EntryViewerPane *pane = new EntryViewerPane(taskId, d_model, this);
	d_panes.push_back(pane);

	pane->setMaximumWidth(300);
	pane->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

	d_box->addWidget(pane);
}

void EntryPane::makeView(){
	const static char weekdays[][20] = {
		"Sunday", "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday", "Saturday"
	};

	for(EntryViewerPane *p: d_panes)
		delete p;
	d_panes.clear();

	int week = QDate::currentDate().dayOfWeek() % 7; // Makes Sunday get 0
	int hour = QTime::currentTime().hour();

	if(hour < 6)
		week = (week != 0) ? week - 1 : 6 ;

	d_header->setText(weekdays[week]);

	for(int id: d_model.getIds()){
		string weekday = d_model.getDays(id);
		if(weekday.at(week) == 't')
			addTask(id);
	}
}
