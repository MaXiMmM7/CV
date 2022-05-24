//============================================================================
// Name        : trackerzadach.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
#include <iostream>
#include <map>
#include <string>
#include <tuple>
using namespace std;

//ѕеречислимый тип дл€ статуса задачи
enum class TaskStatus {
  NEW,          // нова€
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// ќбъ€вл€ем тип-синоним дл€ map<TaskStatus, int>,
// позвол€ющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

int TaskRunner(TaskStatus& state_current,TaskStatus& state_new,
		const string& person,TasksInfo& fresh,TasksInfo& old,int& task_count){
	 if(old[state_current]>0){
					  old[state_current]--;
					  fresh[state_new]++;
					  --task_count;
				  }
				  if(old[state_current]==0){
				  state_current=static_cast<TaskStatus>(static_cast<int>(state_current)+1);
				  state_new=static_cast<TaskStatus>(static_cast<int>(state_new)+1);
				  }
	return task_count;
}
/////////////
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}
/////////////
class TeamTasks {
public:
  // ѕолучить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const{

	  return staff.at(person);

  }

  // ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчитка
  void AddNewTask(const string& person){
	  staff[person][TaskStatus::NEW]++;
  }

  // ќбновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count){

	  TasksInfo fresh,old;
	  if(staff.count(person)==0){
		  return tie(fresh,old);
	  }
	  old=staff[person];
	  old[TaskStatus::DONE]=0;
	  TaskStatus state_current=TaskStatus::NEW;
	  TaskStatus state_new=TaskStatus::IN_PROGRESS;

	  while(task_count>0){
		  switch (state_current){
		  case TaskStatus::NEW:
		  {    if(task_count>0)
			  task_count=TaskRunner(state_current,state_new,person,fresh,old,task_count);
		  }break;
		  case TaskStatus::IN_PROGRESS:
		  {
			  task_count=TaskRunner(state_current,state_new,person,fresh,old,task_count);
		  }break;
		  case TaskStatus::TESTING:{
			  task_count=TaskRunner(state_current,state_new,person,fresh,old,task_count);
		  }break;
		  default:
			  task_count=0;
		 	  }
	  }
	for(int i=0;i<4;i++){
		state_current=static_cast<TaskStatus>(i);
		if(i!=3){
		staff[person][state_current]=fresh[state_current]+old[state_current];

		}else{
			staff[person][state_current]+=fresh[state_current];
		}
		if(fresh[state_current]==0){
			fresh.erase(state_current);
		}
		if(old[state_current]==0){
					old.erase(state_current);
				}
		if(staff[person][state_current]==0){
			staff[person].erase(state_current);
				}
	}
	  return tie(fresh,old);
  }

private:
  map<string,TasksInfo> staff;
};




int main() {


	  TeamTasks tasks;
	  tasks.AddNewTask("Ilia");
	  for (int i = 0; i < 3; ++i) {
	    tasks.AddNewTask("Ivan");
	  }
	  cout << "Ilia's tasks: ";
	  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	  cout << "Ivan's tasks: ";
	  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	  TasksInfo updated_tasks, untouched_tasks;

	  tie(updated_tasks, untouched_tasks) =
	      tasks.PerformPersonTasks("Ivan", 2);
	  cout << "Updated Ivan's tasks: ";
	  PrintTasksInfo(updated_tasks);
	  cout << "Untouched Ivan's tasks: ";
	  PrintTasksInfo(untouched_tasks);

	  tie(updated_tasks, untouched_tasks) =
	      tasks.PerformPersonTasks("Ivan", 2);
	  cout << endl;

	  cout << "Updated Ivan's tasks: ";
	 	  PrintTasksInfo(updated_tasks);
	 	  cout << "Untouched Ivan's tasks: ";
	 	  PrintTasksInfo(untouched_tasks);

	 	  tie(updated_tasks, untouched_tasks) =
	 	      tasks.PerformPersonTasks("Ivan", 2);
	 	  cout << endl;

	 	 cout << "Updated Ivan's tasks: ";
	 		  PrintTasksInfo(updated_tasks);
	 		  cout << "Untouched Ivan's tasks: ";
	 		  PrintTasksInfo(untouched_tasks);

	 		  cout << endl << endl;
	 updated_tasks=tasks.GetPersonTasksInfo("Ivan");
	 PrintTasksInfo(updated_tasks);
  return 0;
}
*/



#include <iostream>
#include <map>
#include <string>
#include <tuple>
using namespace std;



int TaskRunner(TaskStatus& state_current,TaskStatus& state_new,
		const string& person,TasksInfo& fresh,TasksInfo& old,int& task_count){
	 if(old[state_current]>0){
					  old[state_current]--;
					  fresh[state_new]++;
					  --task_count;
				  }
				  if(old[state_current]==0){
				  state_current=static_cast<TaskStatus>(static_cast<int>(state_current)+1);
				  state_new=static_cast<TaskStatus>(static_cast<int>(state_new)+1);
				  }
	return task_count;
}

class TeamTasks {
public:
  // ѕолучить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const{

	  return staff.at(person);

  }

  // ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчитка
  void AddNewTask(const string& person){
	  staff[person][TaskStatus::NEW]++;
  }

  // ќбновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count){

	  TasksInfo fresh,old;
	  if(staff.count(person)==0){
		  return tie(fresh,old);
	  }
	  old=staff[person];
	  old[TaskStatus::DONE]=0;
	  TaskStatus state_current=TaskStatus::NEW;
	  TaskStatus state_new=TaskStatus::IN_PROGRESS;

	  while(task_count>0){
		  switch (state_current){
		  case TaskStatus::NEW:
		  {    if(task_count>0)
			  task_count=TaskRunner(state_current,state_new,person,fresh,old,task_count);
		  }break;
		  case TaskStatus::IN_PROGRESS:
		  {
			  task_count=TaskRunner(state_current,state_new,person,fresh,old,task_count);
		  }break;
		  case TaskStatus::TESTING:{
			  task_count=TaskRunner(state_current,state_new,person,fresh,old,task_count);
		  }break;
		  default:
			  task_count=0;
		 	  }
	  }
	for(int i=0;i<4;i++){
		state_current=static_cast<TaskStatus>(i);
		if(i!=3){
		staff[person][state_current]=fresh[state_current]+old[state_current];
		}else{
			staff[person][state_current]+=fresh[state_current];
		}
		if(fresh[state_current]==0){
					fresh.erase(state_current);
				}
				if(old[state_current]==0){
							old.erase(state_current);
						}
				if(staff[person][state_current]==0){
					staff[person].erase(state_current);
						}
	}
	  return tie(fresh,old);
  }

private:
  map<string,TasksInfo> staff;
};



