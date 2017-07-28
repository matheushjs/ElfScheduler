#include "taskeditorpane.h"

#include <QFormLayout>
#include <QGridLayout>

TaskEditorPane::TaskEditorPane(QWidget *parent)
	: QWidget(parent),
	  d_titleLine(new QLineEdit(this)),
	  d_daysBox(7),
	  d_delBut(new QPushButton("Delete", this))
{
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
	form->addRow(d_delBut);

	form->setAlignment(d_delBut, Qt::AlignCenter);
	d_delBut->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	setLayout(form);
}
