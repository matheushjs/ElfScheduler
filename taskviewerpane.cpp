#include "taskviewerpane.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>

TaskViewerPane::TaskViewerPane(QWidget *parent)
	: QWidget(parent),
	  d_list(new QListWidget(this)),
	  d_button(new QPushButton("+", this))
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

	d_list->addItem("Hey");
	d_list->addItem("Hey2");

	setLayout(box);
}

