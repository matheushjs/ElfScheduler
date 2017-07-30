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
	  d_but(new QPushButton("+", this)),
	  d_line(new QLineEdit(this)),
	  d_model(model),
	  d_taskId(taskId)
{
	setupUI();

	connect(d_but, &QPushButton::clicked, this, &EntryViewerPane::addInputTask);
}

void EntryViewerPane::setupUI(){
	QVBoxLayout *box = new QVBoxLayout(this);

	box->addWidget(d_header);
	box->addWidget(d_list);
	box->addWidget(d_line);
	box->addWidget(d_but, 0, Qt::AlignCenter);

	d_but->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

	d_header->setText(d_model.getTitle(d_taskId).c_str());
	for(string &str: d_model.getEntry(d_taskId)){
		d_list->addItem(QString(str.c_str()));
	}

	setLayout(box);
}

void EntryViewerPane::addInputTask(){
	string str = d_line->text().toStdString();
	if(str == "") return;

	// As soon as the model is changed, EntryPane will replace all EntryViewerPanes for new ones.
	d_model.addEntry(d_taskId, str);
}
