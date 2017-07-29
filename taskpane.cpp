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
