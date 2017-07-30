#include "mainwindow.h"
#include "datamodel.h"

#include <QApplication>
#include <string>

using std::string;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	DataModel model(argc > 1 ? argv[1] : "");
	MainWindow w(model);

	w.setWindowTitle(("Elf Scheduler (" + model.getName() + ")").c_str());
	w.showMaximized();

	return a.exec();
}
