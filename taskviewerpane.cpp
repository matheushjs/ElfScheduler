#include "taskviewerpane.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>

TaskViewerPane::TaskViewerPane(QWidget *parent)
	: QWidget(parent),
	  list(new QListWidget(this)),
	  button(new QPushButton("+", this))
{
	auto *box = new QVBoxLayout(this);
	auto *butBox = new QHBoxLayout();

	butBox->addStretch(1);
	butBox->addWidget(button);
	butBox->addStretch(1);

	QLabel *lbl = new QLabel("Your Tasks", this);
	box->addWidget(lbl, 0, Qt::AlignCenter);
	box->addWidget(list);
	box->addLayout(butBox);

	list->addItem("Hey");
	list->addItem("Hey2");

	setLayout(box);
}

