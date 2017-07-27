#include "taskpane.h"

#include "taskeditorpane.h"
#include "taskviewerpane.h"

#include <QVBoxLayout>

TaskPane::TaskPane(QWidget *parent)
	: QWidget(parent),
	  editPane(new QVBoxLayout),
	  viewPane(new QVBoxLayout)
{
	viewPane->addWidget(new TaskViewerPane(this));
	editPane->addWidget(new TaskEditorPane(this));

	setLayout(viewPane);
}

TaskPane::~TaskPane(){
	delete editPane;
	delete viewPane;
}
