#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "datamodel.h"

using std::string;
using std::map;
using std::vector;
using std::cout;

DataModel::DataModel(QObject *parent) : QObject(parent)
{

}

int DataModel::addTask(const string &title){
	static int id = 0;
	d_titles[id] = title;
	id += 1;
}

void DataModel::removeTask(int id){
	d_titles.erase(id);
	d_logs.erase(id);
}

void DataModel::printAll(){
	for(map<int,string>::iterator it=d_titles.begin(); it != d_titles.end(); it++){
		cout << it->first << ": " << it->second << '\n';
	}
}
