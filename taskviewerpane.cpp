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
	  d_button(new QPushButton("+", this)),
	  d_model(model)
{
	auto *box = new QVBoxLayout(this);
	auto *butBox = new QHBoxLayout();

	butBox->addStretch(1);
	butBox->addWidget(d_button);
	butBox->addStretch(1);

	QLabel *lbl = new QLabel("Your Tasks", this);
	box->addWidget(lbl, 0, Qt::AlignCenter);
	box->addWidget(d_list);
	box->addLayout(butBox);

	for(int i: d_model.getIds()){
		new QListWidgetItem(d_model.getTitle(i).c_str(), d_list, i);
	}

	setLayout(box);
}

