#include "mainwindow.h"
#include "datamodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	DataModel model;
	model.addTask("Genki Studying");
	model.printAll();

	w.setWindowTitle("Elf Scheduler");
	w.resize(500, 500);
	w.show();

	return a.exec();
}
