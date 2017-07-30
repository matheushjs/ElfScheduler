#include "mainwindow.h"
#include "datamodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DataModel model;
	MainWindow w(model);

	w.setWindowTitle("Elf Scheduler");
	w.show();

	return a.exec();
}
