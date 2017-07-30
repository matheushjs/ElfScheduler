#include "entrypane.h"
#include "entryviewerpane.h"

#include <QScrollArea>

EntryPane::EntryPane(DataModel &model, QWidget *parent)
	: QWidget(parent),
	  d_box(new QHBoxLayout()),
	  d_model(model)
{
	setupUI();

	for(int id: d_model.getIds())
		addTask(id);
}

void EntryPane::setupUI(){
	QScrollArea *scroll = new QScrollArea(this);
	QHBoxLayout *scrollLay = new QHBoxLayout(this);
	scrollLay->addWidget(scroll);
	setLayout(scrollLay);

	QWidget *wid = new QWidget(scroll);
	wid->setLayout(d_box);
	scroll->setWidget(wid);
	scroll->setWidgetResizable(true);
}

void EntryPane::addTask(int taskId){
	EntryViewerPane *pane = new EntryViewerPane(taskId, d_model, this);

	pane->setMaximumWidth(300);
	pane->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

	d_box->addWidget(pane);
}
