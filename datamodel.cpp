#include <QStringList>
#include <QDir>
#include <QDebug>
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "datamodel.h"

using std::string;
using std::map;
using std::vector;
using std::cout;

DataModel::DataModel(const QString &dbName, QObject *parent)
	: QObject(parent),
	  db(QSqlDatabase::addDatabase("QSQLITE"))
{
	// Ensure our directory at the HOME directory exists
	QDir dir;
	QString path = QDir::homePath() + QDir::separator() + QString(".elfscheduler");
	dir.mkpath(path);

	// Open database specified by the user.
	if(dbName == QString()){
		// TODO: Load last session
		path += QDir::separator() + QString("default.db");
		db.setDatabaseName(path);

	} else {
		path += QDir::separator() + dbName + QString(".db");
		db.setDatabaseName(path);
	}
	db.open();

	// If database is empty, create the due tables
	QStringList list = db.tables();
	if(list.size() == 0){
		db.exec("CREATE TABLE tasks(id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT, weekdays TEXT[7]);");
		db.exec("CREATE TABLE entries(id INTEGER PRIMARY KEY AUTOINCREMENT, entry TEXT, taskId INTEGER);");
	}

}

int DataModel::addTask(const string &title, const string &days){
	QSqlQuery query;
	query.prepare("INSERT INTO tasks(title, weekdays) VALUES (?,?);");
	query.addBindValue(title.c_str());
	query.addBindValue(days.c_str());
	query.exec();

	// Now get the inserted ID.
	query.exec("SELECT max(id) FROM tasks;");
	query.next();
	int id = query.value(0).toInt();

	return id;
}

int DataModel::addTask(const string &title){
	return addTask(title, "fffffff");
}

void DataModel::removeTask(int id){
	QSqlQuery query;
	query.prepare("DELETE FROM tasks WHERE id = ?;");
	query.addBindValue(id);
	query.exec();

	query.prepare("DELETE FROM entries WHERE taskId = ?;");
	query.addBindValue(id);
	query.exec();

	emit dataChanged();
}

void DataModel::editTask(int id, const string &newTitle, const string &days){
	QSqlQuery query;
	query.prepare("UPDATE tasks SET title = ?, weekdays = ? WHERE id = ?;");
	query.addBindValue(newTitle.c_str());
	query.addBindValue(days.c_str());
	query.addBindValue(id);
	query.exec();

	emit dataChanged();
}

void DataModel::editTask(int id, const string &newTitle){
	QSqlQuery query;
	query.prepare("UPDATE tasks SET title = ? WHERE id = ?;");
	query.addBindValue(newTitle.c_str());
	query.addBindValue(id);
	query.exec();

	emit dataChanged();
}

void DataModel::addEntry(int taskId, const string &newLog){
	QSqlQuery query;
	query.prepare("INSERT INTO entries(taskId, entry) VALUES (?, ?);");
	query.addBindValue(taskId);
	query.addBindValue(newLog.c_str());
	query.exec();

	emit dataChanged();
}

vector<int> DataModel::getIds(){
	QSqlQuery query;
	query.exec("SELECT id FROM tasks;");

	vector<int> result;
	while(query.next()){
		result.push_back(query.value(0).toInt());
	}

	return result;
}

string DataModel::getTitle(int taskId){
	QSqlQuery query;
	query.prepare("SELECT title FROM tasks WHERE id = ?;");
	query.addBindValue(taskId);
	query.exec();

	if(query.next()){
		return query.value(0).toString().toStdString();
	} else {
		return "";
	}
}

string DataModel::getDays(int taskId){
	QSqlQuery query;
	query.prepare("SELECT weekdays FROM tasks WHERE id = ?;");
	query.addBindValue(taskId);
	query.exec();

	if(query.next()){
		return query.value(0).toString().toStdString();
	} else {
		return "ffffff";
	}
}

vector<string> DataModel::getEntry(int taskId){
	QSqlQuery query;
	query.prepare("SELECT entry FROM entries WHERE taskId = ? ORDER BY id DESC;");
	query.addBindValue(taskId);
	query.exec();

	vector<string> result;
	while(query.next()){
		result.push_back(query.value(0).toString().toStdString());
	}

	return result;
}

void DataModel::printAll(){
	QSqlQuery query;
	query.exec("SELECT id, title, weekdays FROM tasks;");
	while(query.next()){
		int id = query.value(0).toInt();
		QString title = query.value(1).toString();
		QString days = query.value(2).toString();
		qDebug() << id << " " << title << " " << days << '\n';

		QSqlQuery subQuery;
		subQuery.prepare("SELECT entry FROM entries WHERE taskId = ? ORDER BY id DESC;");
		subQuery.addBindValue(id);
		subQuery.exec();

		while(subQuery.next()){
			qDebug() << '\t' << subQuery.value(0).toString() << '\n';
		}
	}
}
