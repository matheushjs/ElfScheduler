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
	addTask("Study 1");
	addTask("Study 2");
	//addEntry(0, "T1");
	//addEntry(0, "T2");
	//addEntry(1, "T3");
	//addEntry(1, "T4");
}

int DataModel::addTask(const string &title){
	static int id = 0;
	d_titles[id] = title;
	d_logs[id];
	id += 1;
	return id - 1;
}

void DataModel::removeTask(int id){
	d_titles.erase(id);
	d_logs.erase(id);
	emit dataChanged();
}

void DataModel::editTask(int id, const string &newTitle){
	if(d_titles.count(id) == 0) return;
	else {
		d_titles[id] = newTitle;
		emit dataChanged();
	}
}

void DataModel::addEntry(int taskId, const string &newLog){
	if(d_titles.count(taskId) == 0) return;
	else {
		d_logs[taskId].push_back(newLog);
		emit dataChanged();
	}
}

vector<int> DataModel::getIds(){
	vector<int> result;
	for(auto &kv: d_titles){
		result.push_back(kv.first);
	}
	return result;
}

string DataModel::getTitle(int taskId){
	if(d_titles.count(taskId) == 0) return "";
	else return d_titles[taskId];
}

vector<string> DataModel::getEntry(int taskId){
	if(d_titles.count(taskId)){
		return vector<string>();
	} else {
		vector<string> &vec = d_logs[taskId];
		vector<string> result;

		// Inverted copy
		for(int i = vec.size()-1; i >= 0; i--)
			result.push_back(vec[i]);
		return result;
	}
}

void DataModel::printAll(){
	for(auto &kv: d_titles){
		cout << kv.first << ": " << kv.second << '\n';

		vector<string> &vec = d_logs[kv.first];
		for(int i = vec.size() - 1; i >= 0; i--)
			cout << "\t" << vec[i] << "\n";
	}
}
