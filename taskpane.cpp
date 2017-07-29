#include "taskpane.h"

#include "taskeditorpane.h"
#include "taskviewerpane.h"

#include <QVBoxLayout>

TaskPane::TaskPane(DataModel &model, QWidget *parent)
	: QWidget(parent),
	  d_editPane(new QVBoxLayout),
	  d_viewPane(new QVBoxLayout),
	  d_model(model)
{
	d_viewPane->addWidget(new TaskViewerPane(model, this));
	d_editPane->addWidget(new TaskEditorPane(model, this));

	setLayout(d_viewPane);
}

TaskPane::~TaskPane(){
	delete d_editPane;
	delete d_viewPane;
}
