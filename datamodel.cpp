/*
This file is part of ElfScheduler.

Copyright (C) 2017  Matheus H. J. Saldanha

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <QStringList>
#include <QDir>
#include <QFile>
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
using std::cin;

DataModel::DataModel(QString dbName, QObject *parent)
	: QObject(parent),
	  d_db(QSqlDatabase::addDatabase("QSQLITE"))
{
	// Ensure our directory at the HOME directory exists
	QDir dir;
	QString dirPath = QDir::homePath() + QDir::separator() + QString(".elfscheduler");
	dir.mkpath(dirPath);

	// Decide database name
	if(dbName == QString()){
		// Restore session
		QFile sessFile(dirPath + QDir::separator() + "savedsession.txt");
		if(sessFile.exists()){
			sessFile.open(QIODevice::ReadOnly);
			QTextStream stream(&sessFile);
			stream >> dbName;
			sessFile.close();
		} else {
			cout << "There is no saved session\n";
			exit(0);
		}
	} else {
		dbName += ".db";
		QFile sessFile(dirPath + QDir::separator() + dbName);
		if(!sessFile.exists()){
			cout << "Database '" << dbName.toStdString() << "' does not exist yet. Create it [y/N]? ";
			char input;
			cin >> input;
			if(input != 'y' && input != 'Y')
				exit(0);
		} else sessFile.close();
	}

	// Open database specified by the user.
	QString dbPath = dirPath + QDir::separator() + dbName;
	d_db.setDatabaseName(dbPath);
	d_db.open();
	cleanOld();

	// If database is empty, create the due tables
	QStringList list = d_db.tables();
	if(list.size() == 0){
		d_db.exec("CREATE TABLE tasks(id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT, weekdays TEXT[7]);");
		d_db.exec("CREATE TABLE entries(id INTEGER PRIMARY KEY AUTOINCREMENT, entry TEXT, taskId INTEGER);");
	}

	d_dbName = dbName;

	// Save current session
	QFile sessFile(dirPath + QDir::separator() + "savedsession.txt");
	sessFile.open(QIODevice::WriteOnly);
	QTextStream stream(&sessFile);
	stream << dbName;
	sessFile.close();
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

	emit taskAdded(id);

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

	emit taskRemoved(id);
}

void DataModel::editTask(int id, const string &newTitle, const string &days){
	QSqlQuery query;
	query.prepare("UPDATE tasks SET title = ?, weekdays = ? WHERE id = ?;");
	query.addBindValue(newTitle.c_str());
	query.addBindValue(days.c_str());
	query.addBindValue(id);
	query.exec();

	emit taskEdited(id);
}

void DataModel::editTask(int id, const string &newTitle){
	QSqlQuery query;
	query.prepare("UPDATE tasks SET title = ? WHERE id = ?;");
	query.addBindValue(newTitle.c_str());
	query.addBindValue(id);
	query.exec();

	emit taskEdited(id);
}

void DataModel::addEntry(int taskId, const string &newLog){
	QSqlQuery query;
	query.prepare("INSERT INTO entries(taskId, entry) VALUES (?, ?);");
	query.addBindValue(taskId);
	query.addBindValue(newLog.c_str());
	query.exec();

	emit entryAdded(taskId, newLog);
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

string DataModel::getName(){
	return d_dbName.toStdString();
}

void DataModel::cleanOld(){
	QSqlQuery query;
	// Leaves only the 500 oldest entries.
	query.exec("DELETE FROM entries WHERE id IN (SELECT id FROM entries ORDER BY id DESC LIMIT -1 OFFSET 500);");
}
