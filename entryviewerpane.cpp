#include "entryviewerpane.h"

#include <QVBoxLayout>
#include <string>
#include <vector>

using std::string;
using std::vector;

EntryViewerPane::EntryViewerPane(int taskId, DataModel &model, QWidget *parent)
	: QWidget(parent),
	  d_header(new QLabel(this)),
	  d_list(new QListWidget(this)),
	  d_line(new QLineEdit(this)),
	  d_model(model),
	  d_taskId(taskId)
{
	setupUI();

	connect(d_line, SIGNAL(returnPressed()), this, SLOT(addInputTask()));
	connect(&d_model, SIGNAL(taskEdited(int)), this, SLOT(checkTaskChanged(int)));
}

void EntryViewerPane::setupUI(){
	QVBoxLayout *box = new QVBoxLayout(this);

	box->addWidget(d_header);
	box->addWidget(d_list);
	box->addWidget(d_line);

	d_header->setText(d_model.getTitle(d_taskId).c_str());
	for(string &str: d_model.getEntry(d_taskId)){
		d_list->addItem(QString(str.c_str()));
	}

	setFocusProxy(d_line);
	setFocusPolicy(Qt::StrongFocus);
	d_list->setFocusPolicy(Qt::NoFocus);

	setLayout(box);
}

void EntryViewerPane::addInputTask(){
	string str = d_line->text().toStdString();
	d_line->setText("");
	if(str == "") return;

	d_list->insertItem(0, str.c_str());
	d_model.addEntry(d_taskId, str);
}

void EntryViewerPane::checkTaskChanged(int taskId){
	if(d_taskId != taskId)
		return;

	d_header->setText(d_model.getTitle(taskId).c_str());
}

int EntryViewerPane::getId(){
	return d_taskId;
}
