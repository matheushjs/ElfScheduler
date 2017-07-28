#include "taskpane.h"

#include "taskeditorpane.h"
#include "taskviewerpane.h"

#include <QVBoxLayout>

TaskPane::TaskPane(QWidget *parent)
	: QWidget(parent),
	  d_editPane(new QVBoxLayout),
	  d_viewPane(new QVBoxLayout)
{
	d_viewPane->addWidget(new TaskViewerPane(this));
	d_editPane->addWidget(new TaskEditorPane(this));

	setLayout(d_viewPane);
}

TaskPane::~TaskPane(){
	delete d_editPane;
	delete d_viewPane;
}
