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
	connect(&model, SIGNAL(dataChanged()), this, SLOT(makeView()));

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
