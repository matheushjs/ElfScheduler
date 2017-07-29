#include "taskeditorpane.h"

#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>

const int TaskEditorPane::NEW_TASK = -1;
const int TaskEditorPane::NO_TASK = -2;

#define TYPE_FINISH 0
#define TYPE_DELETE 1

TaskEditorPane::TaskEditorPane(DataModel &model, QWidget *parent)
	: QWidget(parent),
	  d_titleLine(new QLineEdit(this)),
	  d_daysBox(7),
	  d_delBut(new QPushButton("Delete", this)),
	  d_finBut(new QPushButton("Finish", this)),
	  d_model(model),
	  d_subjectId(TaskEditorPane::NO_TASK)
{
	setupUI();

	connect(d_delBut, &QPushButton::clicked, this, [this]{processForm(TYPE_DELETE);});
	connect(d_finBut, &QPushButton::clicked, this, [this]{processForm(TYPE_FINISH);});
}

void TaskEditorPane::setupUI(){
	static const char dayStr[][4] = { "Sun", "Mon", "Tue",
								 "Wed", "Thu", "Fri",
								 "Sat" };

	QFormLayout *form = new QFormLayout(this);
	form->addRow("Title:", d_titleLine);

	QGridLayout *grid = new QGridLayout();
	for(int i = 0; i < 7; i++)
		d_daysBox[i] = new QCheckBox(QString(dayStr[i]), this);

	grid->addWidget(d_daysBox[0], 0, 0);
	grid->addWidget(d_daysBox[1], 0, 1);
	grid->addWidget(d_daysBox[2], 0, 2);
	grid->addWidget(d_daysBox[3], 1, 0);
	grid->addWidget(d_daysBox[4], 1, 1);
	grid->addWidget(d_daysBox[5], 1, 2);
	grid->addWidget(d_daysBox[6], 2, 1);

	form->addRow(grid);

	QHBoxLayout *buttons = new QHBoxLayout();
	buttons->addWidget(d_delBut);
	buttons->addWidget(d_finBut);
	form->addRow(buttons);

	form->setAlignment(buttons, Qt::AlignCenter);
	d_delBut->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	setLayout(form);
}

void TaskEditorPane::setTask(int id){
	d_subjectId = id;

	if(id == NEW_TASK){
		d_subjectId = d_model.addTask("");
	} else {
		d_titleLine->setText(d_model.getTitle(id).c_str());
	}
}

void TaskEditorPane::processForm(int clickType){
	if(clickType == TYPE_DELETE){
		d_model.removeTask(d_subjectId);
	} else {
		d_model.editTask(d_subjectId, d_titleLine->text().toStdString());
	}

	emit finished();
}
