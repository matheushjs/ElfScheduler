#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>

#include <vector>
#include <string>
#include <map>

/* (id INT PRIMARY KEY, title VARCHAR, weekdays INT)
 *     is the list of tasks
 * (id INT PRIMARY KEY, taskId INT, text VARCHAR)
 *     each task's log item
 *
 * Functionalities desired:
 * - add new task
 * - remove task
 * - change task title
 * - add a log item to task
 * - clean old log items
 */

class DataModel : public QObject
{
	Q_OBJECT

	std::map<int,std::string> d_titles;
	std::map<int,std::vector<std::string> > d_logs;

public:
	explicit DataModel(QObject *parent = 0);

	int addTask(const std::string &title);
	void removeTask(int id);
	void editTask(int id, const std::string &newTitle);

	void addEntry(int taskId, const std::string &newLog);

	// Returns all IDs
	std::vector<int> getIds();

	// Returns a task titles
	std::string getTitle(int taskId);

	// Returns all entries for a task. Newer entries come first.
	std::vector<std::string> getEntry(int taskId);

	void printAll();

signals:
	void dataChanged();

public slots:
};

#endif // DATAMODEL_H
