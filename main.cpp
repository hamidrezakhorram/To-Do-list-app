#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <windows.h>
using namespace std;
struct task {
    int id;
    string name;
    int deadLine;
    int priority;
    string explanation;
    string state;

};
struct plan {
    int id;
    string name;
    int deadline[2];
    task taskList[20];
};
struct user {
    string name;
    string userName;
    int password;
    plan planList[20];
};

task addTask(string name, int deadline, int priority, string explanation, int idTask);

int calculateTime();

int deleteTask(task *taskList, int id, int taskCount);

void editTask(task *taskList, string change, string editValue, int id, int taskCount);

plan addPlan(string name, int deadline[] , int id );

int deletePlane(plan *planList, int id, int planCount);

void editPlan(plan *planList, string change, string editValue, int id, int planCount ,int deadline[]);

int deleteUser(user *userList, string username, int userCount);

void editUser(user *userList, string change, string username, int userCount, string editValue, int editPassword);

int addTaskPlan(plan *planList, task *taskList, string planName, string taskName, int planCount, int taskCount);

int delTaskPlan(plan *planList, task *taskList, string planName, string taskName, int planCount);

int taskState(plan *planList, string state, string plnaName, string taskName, int planCount);

task *planning(plan planList[], string planName, string choose, int planCount);

vector<task> filter(plan planList[], int planCount, int date, string choose, string planName, int value);
void readSave(user *userList , int *userCount,plan *planList ,task *taskList,string action , int *planCount , int *taskCout , string username);
vector<plan> showplan(plan planlist[],int planCount);
vector<task> showTask(plan planlist[] , string planName ,int planCount);
void setColor(int Color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}
void resetColor() {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
user signup(string name, string username, int password) {
    user newUser;
    newUser.name = name;
    newUser.userName = username;
    newUser.password = password;
    return newUser;
}

void loginMenu(user *userlist, string usname, int userCount) {
    setColor(9);
    cout << "your are successfully login" << endl;
    resetColor();
    string action;
    int idTask = 0;
    task taskList[20];
    int planCount = 0;
    int planId = 101;
    plan planList[20];
    readSave(userlist ,&userCount,planList,taskList,"read",&planCount , &idTask ,usname);
    do {
        setColor(6);
        cout << "what action do you want to do? " << endl;
        cout << "task operations: addtask , deletetask ,edittask , taskhistory , showtask " << endl;
        cout << "plan operations: addplan , deleteplan ,editplan ,planhistory ,showplan" << endl;
        cout <<"task & plan managment: addtasktoplan ,deletetasktoplan, planning , taskstate, filter"<<endl;
        cout << "logout"<<endl;
        resetColor();
        cin >> action;
        if (action == "addtask") {
            string name;
            int deadLine;
            int priority;
            string explnation;
            cin.ignore();
            cout << "what is your task name?" << endl;
            getline(cin, name);
            cout << "what is your task explanation?" << endl;
            getline(cin, explnation);
            cout << "what is your task priority? (1 is most important)" << endl;
            cin >> priority;
            cout << "what is your task deadline ?" << endl;
            cin >> deadLine;
            taskList[idTask++] = addTask(name, deadLine, priority, explnation, idTask);
            setColor(2);
            cout<<"task successfully submited"<<endl;
            resetColor();
        } else if (action == "deletetask") {
            int id;
            cout << "what is your task id?" << endl;
            cin >> id;
            int check = deleteTask(taskList, id, idTask);
            if (check == 0) {
                setColor(2);
                cout << "task successfully deleted" << endl;
                resetColor();
                idTask--;
            } else {
                setColor(4);
                cout << "this task does't exict!" << endl;
                resetColor();
            }
        } else if (action == "edittask") {
            int id;
            string change;
            cout << "what is your task id?" << endl;
            cin >> id;
            cout << "what do you want to edit? (name , deadline , priority, explanation)" << endl;
            cin >> change;
            cin.ignore();
            if (change == "name") {
                cout << "please enter new name" << endl;
                string name;
                getline(cin, name);
                editTask(taskList, change, name, id, idTask);
                setColor(2);
                cout<<"changes submited"<<endl;
                resetColor();
            } else if (change == "deadline") {
                cout << "please enter new deadline" << endl;
                string deadline;
                cin >> deadline;
                editTask(taskList, change, deadline, id, idTask);
                setColor(2);
                cout<<"changes submited"<<endl;
                resetColor();
            } else if (change == "priority") {
                cout << "please enter new priority" << endl;
                string priority;
                getline(cin, priority);
                editTask(taskList, change, priority, id, idTask);
                setColor(2);
                cout<<"changes submited"<<endl;
                resetColor();
            } else if (change == "explanation") {
                cout << "please enter new explanation" << endl;
                string explanation;
                getline(cin, explanation);
                editTask(taskList, change, explanation, id, idTask);
                setColor(2);
                cout<<"changes submited"<<endl;
                resetColor();
            }
        } else if (action == "taskhistory") {
            cout << "task list: " << endl;

            for (int i = 0; i < idTask; ++i) {
               if (taskList[i].state=="finished"){
                   setColor(2);
                   cout << taskList[i].id<<".name: " << taskList[i].name << " ,deadline:" << taskList[i].deadLine << " ,priority: "
                        << taskList[i].priority << " "<<taskList[i].state<<endl;
                   resetColor();
               }else if (taskList[i].state=="unfinished"){
                   setColor(4);
                   cout << taskList[i].id<<".name: " << taskList[i].name << " ,deadline:" << taskList[i].deadLine << " ,priority: "
                        << taskList[i].priority <<" "<<taskList[i].state << endl;
                   resetColor();
               }else {
                   setColor(5);
                   cout << taskList[i].id<<".name: " << taskList[i].name << " ,deadline:" << taskList[i].deadLine << " ,priority: "
                        << taskList[i].priority << endl;
                   resetColor();
               }

            }

        } else if (action == "addplan") {
            string name;
            int deadline[2];
            cin.ignore();
            cout << "what is your plane name?" << endl;
            getline(cin, name);
            cout << "when this plan begin ?" << endl;
            cin>>deadline[0];
            cout<<"when this plan ends ? "<<endl;
            cin>>deadline[1];
            planList[planCount] = addPlan(name,  deadline,planId  );
            setColor(2);
            cout << planList[planCount].name << " added successfully" << endl;
            resetColor();
            planId++;
            planCount++;
        } else if (action == "deleteplan") {
            int id;
            cout << "What is your plan id?" << endl;
            cin >> id;
            int check = deletePlane(planList, id, planCount);
            if (check == 0) {
                setColor(2);
                cout << "plan deleted succesfully" << endl;
                planCount--;
                resetColor();
            } else {
                setColor(4);
                cout << "the plan doesn't exict!" << endl;
                resetColor();
            }
        } else if (action == "editplan") {
            int id;
            string change;
            int deadline[2];
            cout << "what is your plan id?" << endl;
            cin >> id;
            cout << "what do you want to edit? (name , deadline)" << endl;
            cin >> change;
            cin.ignore();
            if (change == "name") {
                cout << "please enter new name" << endl;
                string name;
                getline(cin, name);
                editPlan(planList, change, name, id, planCount,deadline);
                setColor(2);
                cout<<"changes submited"<<endl;
                resetColor();
            } else if (change == "deadline") {
                cout << "please enter begin of new deadline" << endl;
                 cin>>deadline[0];
                 cout<<"please enter end of new deadline"<<endl;
                 cin>>deadline[1];
                 editPlan(planList, change, "", id, planCount , deadline);
                setColor(2);
                cout<<"changes submited"<<endl;
                resetColor();
            }
        } else if (action == "planhistory") {
            setColor(5);
            for (int i = 0; i < planCount; ++i) {
                cout <<planList[i].id<<".name: " << planList[i].name << ",deadline: " << planList[i].deadline[0]<<"-"<<planList[i].deadline[1] << endl;

            }
            resetColor();
        } else if (action == "addtasktoplan") {
            string planName, taskName;
            cout << "enter the plan name" << endl;
            cin >> planName;
            cout << "enter the task name" << endl;
            cin.ignore();
            getline(cin, taskName);
            int check = addTaskPlan(planList, taskList, planName, taskName, planCount, idTask);
            if (check == 0) {
                setColor(2);
                cout << "task " << taskName << "sucssefullu added to " << planName << endl;
                resetColor();
            } else {
                setColor(4);
                cout << "task such task or plan doesn't exict" << endl;
                resetColor();
            }
        } else if (action == "deletetasktoplan") {
            string planName, taskName;
            cout << "enter the plan name" << endl;
            cin >> planName;
            cout << "enter the task name" << endl;
            cin.ignore();
            getline(cin, taskName);
            int check = delTaskPlan(planList, taskList, planName, taskName, planCount);
            if (check == 0) {
                setColor(2);
                cout << "task successfuly deleted" << endl;
                resetColor();
            } else {
                setColor(4);
                cout << "such plan or task doesn't exict" << endl;
                resetColor();
            }

        } else if (action == "planning") {
            string choose, planName;

            cout << "please choose your plan" << endl;
            cin >> planName;
            cout << "base on what planning should works? (deadline , priority)" << endl;
            cin >> choose;
            task *planningTask = planning(planList, planName, choose, planCount);
            setColor(5);
            for (int i = 0; i < 20 and planningTask[i].name != ""; ++i) {
                cout << planningTask[i].name << " deadline: " << planningTask[i].deadLine << " priority: "
                     << planningTask[i].priority << endl;
            } resetColor();

        } else if (action == "taskstate") {
            string taskName, state, planName;
            cout << "what is plan name?" << endl;
            cin >> planName;
            cout << "what is task name?" << endl;
            cin >> taskName;
            cout << "what is tast situation? (finished or unfinished)" << endl;
            cin >> state;
            int check = taskState(planList, state, planName, taskName, planCount);
            if (check == 0) {
                setColor(2);
                cout << "situation of task " << taskName << " changed to " << state << endl;
                resetColor();
            } else {
                setColor(4);
                cout << "such plan or task doesn't exict " << endl;
                resetColor();
            }
        } else if (action == "logout") {
            readSave(userlist ,&userCount,planList,taskList,"save",&planCount , &idTask ,usname);
        } else if (action == "filter") {
            string planName, choose;
            int date, value = 0;
            cout << "what is your plan name" << endl;
            cin >> planName;
            cout << "base on what do you want to make filter (finished or unfinished , date , priority)" << endl;
            cin >> choose;
            if (choose == "priority") {
                cout << "what priority do you want to filte? (1,2,3)" << endl;
                cin >> value;
            } else if (choose == "date") {
                cout << "what is the starting date?" << endl;
                cin >> value;
            }
            cout << "till when do you want to see records" << endl;
            cin >> date;
           vector<task> taskList = filter(planList, planCount, date, choose, planName, value);
            cout << "task list of " << choose << " untill" << date << endl;
            int lenth =taskList.size();
            setColor(5);
            for (int i = 0; i < lenth and taskList[i].name !=""; ++i) {
                cout << "name: " << taskList[i].name << " priority: " << taskList[i].priority << " deadline: "
                     << taskList[i].deadLine << endl;
            }
            resetColor();

        } else if(action=="showtask"){
            string planName;
            cout<<"what is your plan name?"<<endl;
            cin>>planName;
            vector<task> showtask = showTask(planList ,planName ,planCount);
            int lenght =showtask.size();
            setColor(5);
            for (int i = 0; i < lenght; ++i) {
                cout<<showtask[i].id <<". name: "<<showtask[i].name <<" deadline "<<showtask[i].deadLine
                <<" priority "<<showtask[i].priority<<endl;
            }
            resetColor();
        }else if (action=="showplan")
        {
          vector<plan> showPlan = showplan(planList ,planCount);
          int length =showPlan.size();
            setColor(5);
            for (int i = 0; i < length; ++i) {
                cout<<showPlan[i].id<<". name: "<<showPlan[i].name<<" deadline: "<<showPlan[i].deadline[0]<<
                "-"<<showPlan[i].deadline[1]<<endl;

            }
            resetColor();
        }

    } while (action != "logout");


}

void adminMenu(user *userList, int &userCount) {
    setColor(9);
    cout << "you are in admin page" << endl;
    resetColor();
    string action;
    do {
        setColor(6);
        cout << "what following order do you want to do?" << endl;
        cout << "adduser , deleteuser , showuser , edituser , usingapp ,logout" << endl;
        resetColor();
        cin >> action;
        if (action == "adduser") {
            string name, username;
            int password;
            cout << "what is user name?" << endl;
            cin >> name;
            cout << "what is user username?" << endl;
            cin >> username;
            cout << "what is user password?" << endl;
            cin >> password;
            userList[userCount] = signup(name, username, password);
            setColor(2);
            cout << " the user " << userList[userCount].name << " with username " << userList[userCount].userName
                 << " added successfully" << endl;
            resetColor();
            userCount++;
        } else if (action == "showuser") {
            setColor(5);
            for (int i = 0; i < userCount; ++i) {

                cout << "name: " << userList[i].name << ", username: " << userList[i].userName << endl;
            } resetColor();

        } else if (action == "deleteuser") {
            cout << "what is user username?" << endl;
            string username;
            cin >> username;
            int check = deleteUser(userList, username, userCount);
            if (check == 0) {
                setColor(2);
                cout << "user with username " << username << " deleted" << endl;
                resetColor();
                userCount--;
            } else {
                setColor(4);
                cout << "the user doesn't exict" << endl;
                resetColor();
            }

        } else if (action == "edituser") {
            string username;
            string change;
            cout << "what is the user username?" << endl;
            cin >> username;
            cout << "what do you want to edit? (name, username , password)" << endl;
            cin >> change;
            if (change == "name") {
                cout << "please enter new name" << endl;
                string name;
                cin >> name;
                editUser(userList, change, username, userCount, name, 0);
                setColor(2);
                cout<<"change submited"<<endl;
                resetColor();

            } else if (change == "username") {
                cout << "please enter new username" << endl;
                string changeUsername;
                cin >> changeUsername;
                editUser(userList, change, username, userCount, changeUsername, 0);
                setColor(2);
                cout<<"change submited"<<endl;
                resetColor();
            } else if (change == "password") {
                cout << "please enter new password" << endl;
                int password;
                cin >> password;
                editUser(userList, change, username, userCount, "", password);
                setColor(2);
                cout<<"change submited"<<endl;
                resetColor();
            }
        }else if (action=="usingapp"){
            loginMenu(userList,"admin", userCount);
        }
    } while (action != "logout");
}

int login(string username, int password, user userList[], int userCount) {
    for (int i = 0; i < userCount; ++i) {

        if (userList[i].userName == username and userList[i].password == password) {
            return 0;
        }
    }
    return -1;
}
void readSave(user *userList , int *userCount,plan *planList ,task *taskList,string action , int *planCount , int *taskCout , string username){
   if(action=="read"){

       for (int i = 0; i < *userCount; ++i) {
           if(userList[i].userName==username){
               for (int j = 0; !userList[i].planList[j].name.empty(); ++j) {
                   planList[(*planCount)++]=userList[i].planList[j];

               }
               for (int j = 0;j<*planCount ; ++j) {
                   for (int k = 0; !planList[j].taskList[k].name.empty(); ++k) {
                       taskList[(*taskCout)++]=planList[j].taskList[k];
                   }
               }
               break;
           }
       }
   } else if (action=="save"){
       for (int i = 0; i < *userCount; ++i) {
           if (userList[i].userName == username) {
               for (int j = 0; j < *planCount; ++j) {
                   userList[i].planList[j] = planList[j];
               }
               break;
           }
       }
   }
}

task addTask(string name, int deadline, int priority, string explanation, int idTask) {
    task newTask;
    newTask.id = idTask + 1;
    newTask.name = name;
    newTask.deadLine = deadline;
    newTask.priority = priority;
    newTask.explanation = explanation;
    idTask++;
    return newTask;
}

int deleteTask(task *taskList, int id, int taskCount) {
    for (int i = 0; i < taskCount; ++i) {
        if (taskList[i].id == id) {
            for (int j = i; j < taskCount; ++j) {
                taskList[j] = taskList[j + 1];
            }
            return 0;
        }
    }
    return -1;
}

void editTask(task *taskList, string change, string editValue, int id, int taskCount) {
    for (int i = 0; i < taskCount; ++i) {
        if (taskList[i].id == id) {
            if (change == "name") {
                taskList[i].name = editValue;
            } else if (change == "deadline") {
                taskList[i].deadLine = stoi(editValue);
            } else if (change == "priority") {
                taskList[i].priority = stoi(editValue);
            } else if (change == "explanation") {
                taskList[i].explanation = editValue;
            }
            break;
        }
    }
}

plan addPlan(string name, int deadline[], int id) {
    plan newPlane;
    newPlane.id = id;
    newPlane.name = name;
    newPlane.deadline[0] = deadline[0];
    newPlane.deadline[1]= deadline[1];
    return newPlane;
}

int deletePlane(plan *planList, int id, int planCount) {
    for (int i = 0; i < planCount; ++i) {
        if (planList[i].id == id) {
            for (int j = i; j < planCount; ++j) {
                planList[j] = planList[j + 1];
            }
            return 0;
        }
    }
    return -1;
}

void editPlan(plan *planList, string change, string editValue, int id, int planCount,int deadline[]) {
    for (int i = 0; i < planCount; ++i) {
        if (planList[i].id == id) {
            if (change == "name") {
                planList[i].name = editValue;
            } else if (change == "deadline") {
                planList[i].deadline[0] = deadline[0];
                planList[i].deadline[1] = deadline[1];
            }
            break;
        }
    }
}
vector<plan> showplan(plan planlist[],int planCount){
    vector<plan> showplan;
    for (int i = 0; i < planCount; ++i) {
        if(calculateTime()>=planlist[i].deadline[0] and calculateTime()<=planlist[i].deadline[1]){
            showplan.push_back(planlist[i]);
        }
    }
    return showplan;
}
vector<task> showTask(plan planlist[] , string planName ,int planCount){
    vector<task> showtask;
    for (int i = 0; i < planCount; ++i) {
        if (planlist[i].name ==planName){
            for (int j = 0; !planlist[i].taskList[j].name.empty() ; ++j) {
                if(planlist[i].taskList[j].deadLine<calculateTime() and planlist[i].taskList[j].state !="unfinished" ){
                    planlist[i].taskList[j].state="unfinished";
                }
                if (planlist[i].taskList[j].state !="unfinished" and planlist[i].taskList[j].state !="finished"){
                    showtask.push_back(planlist[i].taskList[j]);
                }
            }
            break;
        }
    }
    return showtask;
}
int deleteUser(user *userList, string username, int userCount) {
    for (int i = 0; i < userCount; ++i) {
        if (userList[i].userName == username) {
            for (int j = i; j < userCount; ++j) {
                userList[j] = userList[j + 1];
            }
            return 0;
        }
    }
    return -1;
}

void editUser(user *userList, string change, string username, int userCount, string editValue, int editPassword) {
    for (int i = 0; i < userCount; ++i) {
        if (userList[i].userName == username) {
            if (change == "name") {
                userList[i].name = editValue;
            } else if (change == "username") {
                userList[i].userName = editValue;
            } else if (change == "password") {
                userList[i].password = editPassword;
            }
            break;
        }
    }
}

int addTaskPlan(plan *planList, task *taskList, string planName, string taskName, int planCount, int taskCount) {
    for (int i = 0; i < planCount; ++i) {
        if (planList[i].name == planName) {
            for (int j = 0; j < taskCount; ++j) {
                if (taskList[j].name == taskName) {
                    int lengh = sizeof(planList[i].taskList) / sizeof(planList[i].taskList[0]);
                    for (int k = 0; k < lengh; ++k) {
                        if (planList[i].taskList[k].name == "") {
                            planList[i].taskList[k] = taskList[j];
                            return 0;
                        }
                    }
                    break;
                }
            }
        }
        return -1;
    }
}

int delTaskPlan(plan *planList, task *taskList, string planName, string taskName, int planCount) {
    for (int i = 0; i < planCount; ++i) {
        if (planList[i].name == planName) {
            for (int j = 0; !planList[i].taskList[j].name.empty(); ++j) {
                if (planList[i].taskList[j].name == taskName) {
                    for (int k = j; k < !planList[k].taskList[k].name.empty(); ++k) {
                        planList[i].taskList[k] = planList[i].taskList[k + 1];
                    }
                    return 0;
                }
            }
        }
    }
    return -1;
}

task *planning(plan planList[], string planName, string choose, int planCount) {
    int count = 0;
    for (int i = 0; i < planCount; ++i) {
        if (planList[i].name == planName) {
            while (planList[i].taskList[count].name != "") {
                count++;
            }

            if (choose == "deadline") {

                for (int j = 0; j < count; ++j) {
                    for (int k = 0; k < count - j - 1; ++k) {

                        if (planList[i].taskList[k].deadLine > planList[i].taskList[k + 1].deadLine) {
                            task temp = planList[i].taskList[k + 1];
                            planList[i].taskList[k + 1] = planList[i].taskList[k];
                            planList[i].taskList[k] = temp;
                        } else if (planList[i].taskList[k].deadLine == planList[i].taskList[k + 1].deadLine){
                            if (planList[i].taskList[k].priority > planList[i].taskList[k + 1].priority) {
                                task temp = planList[i].taskList[k + 1];
                                planList[i].taskList[k + 1] = planList[i].taskList[k];
                                planList[i].taskList[k] = temp;
                            }
                        }
                    }
                }
            } else if (choose == "priority") {
                for (int j = 0; j < count; ++j) {
                    for (int k = 0; k < count - j - 1; ++k) {
                        if (planList[i].taskList[k].priority > planList[i].taskList[k + 1].priority) {
                            task temp = planList[i].taskList[k + 1];
                            planList[i].taskList[k + 1] = planList[i].taskList[k];
                            planList[i].taskList[k] = temp;
                        }else if (planList[i].taskList[k].priority == planList[i].taskList[k + 1].priority){
                            if (planList[i].taskList[k].deadLine > planList[i].taskList[k + 1].deadLine) {
                                task temp = planList[i].taskList[k + 1];
                                planList[i].taskList[k + 1] = planList[i].taskList[k];
                                planList[i].taskList[k] = temp;}
                        }
                    }
                }
            }
            return planList[i].taskList;
        }
    }
}

int taskState(plan *planList, string state, string plnaName, string taskName, int planCount) {
    for (int i = 0; i < planCount; ++i) {
        if (planList[i].name == plnaName) {
            for (int j = 0; !planList[i].taskList[j].name.empty() ; ++j) {
                if (planList[i].taskList[j].name == taskName) {
                    planList[i].taskList[j].state = state;
                    return 0;
                }
            }
            break;
        }
    }
    return -1;
}

vector<task> filter(plan planList[], int planCount, int date, string choose, string planName, int value) {
    vector<task> filtertask;
    int filterCount = 0;
    for (int i = 0; i < planCount; ++i) {
        if (planList[i].name == planName) {
            int lenth = sizeof(planList[i].taskList) / sizeof(planList[i].taskList[0]);
            if (choose == "finished") {
                for (int j = 0; j < lenth; ++j) {
                    if (planList[i].taskList[j].state == "finished" and planList[i].taskList[j].deadLine <= date) {
                        filtertask.push_back(planList[i].taskList[j]);
                    }
                }
            } else if (choose == "unfinshed") {
                for (int j = 0; j < lenth; ++j) {
                    if (planList[i].taskList[j].state == "unfinished" and planList[i].taskList[j].deadLine <= date) {
                        filtertask.push_back(planList[i].taskList[j]);
                    }
                }
            } else if (choose == "priority") {
                for (int j = 0; j < lenth; ++j) {
                    if (planList[i].taskList[j].priority == value and planList[i].taskList[j].deadLine <= date) {
                        filtertask.push_back(planList[i].taskList[j]);
                    }
                }
            } else if (choose == "date") {
                for (int j = 0; j < lenth; ++j) {
                    if (planList[i].taskList[j].deadLine >= value and planList[i].taskList[j].deadLine <= date) {
                        filtertask.push_back(planList[i].taskList[j]);
                    }
                }

            }
            break;
        }
    }
    return filtertask;
}

int calculateTime() {
    string date;
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);
    ostringstream dateStream;
    dateStream << (localTime->tm_year + 1900)
               << setw(2) << setfill('0') << (localTime->tm_mon + 1)
               << setw(2) << setfill('0') << localTime->tm_mday
               << setw(2) << setfill('0') << localTime->tm_hour;

    date = dateStream.str();

    int intDate = stoi(date);
    return intDate;
}

int savefile(user userList[], int userCount) {
    ofstream fptr("tasks.txt");
    for (int i = 0; i < userCount; ++i) {
        fptr << userList[i].name << endl;
        fptr << userList[i].userName << endl;
        fptr << userList[i].password << endl;
        for (int j = 0; userList[i].planList[j].name != ""; ++j) {
            fptr << userList[i].planList[j].id << endl;
            fptr << userList[i].planList[j].name << endl;
            fptr << userList[i].planList[j].deadline[0] <<"-"<< userList[i].planList[j].deadline[1]<<endl;

            for (int k = 0; userList[i].planList[j].taskList[k].name != ""; ++k) {
                fptr << userList[i].planList[j].taskList[k].id << endl;
                fptr << userList[i].planList[j].taskList[k].name << endl;
                fptr << userList[i].planList[j].taskList[k].deadLine << endl;
                fptr << userList[i].planList[j].taskList[k].explanation << endl;
                fptr << userList[i].planList[j].taskList[k].priority << endl;
                fptr << userList[i].planList[j].taskList[k].state << endl;
                fptr << "thirdpart" << endl;

            }
            fptr << "secondpart" << endl;

        }
        fptr << "----" << endl;
    }
    fptr.close();
}

void readfile(user *userList, int &userCount) {
    int planCount = 0;
    int taskCount = 0;
    string line;
    ifstream fread("tasks.txt");
    while (getline(fread, line)) {
        if (line != "----") {
            if (userList[userCount].name.empty()) {
                userList[userCount].name = line;
            } else if (userList[userCount].userName.empty()) {
                userList[userCount].userName = line;
            } else if (userList[userCount].password == 0) {
                userList[userCount].password = stoi(line);
            } else if (line != "secondpart") {
                if (userList[userCount].planList[planCount].id == 0) {
                    userList[userCount].planList[planCount].id = stoi(line);
                } else if (userList[userCount].planList[planCount].name.empty()) {
                    userList[userCount].planList[planCount].name = line;
                } else if (userList[userCount].planList[planCount].deadline[0]==0) {
                    string strdeadline = line;
                    size_t pos = strdeadline.find('-');
                    string firstPart = strdeadline.substr(0, pos);
                    string secondPart = strdeadline.substr(pos + 1);
                    userList[userCount].planList[planCount].deadline[0] = stoi(firstPart);
                    userList[userCount].planList[planCount].deadline[1] = stoi(secondPart);
                } else if (line != "thirdpart") {
                    if (userList[userCount].planList[planCount].taskList[taskCount].id == 0) {
                        userList[userCount].planList[planCount].taskList[taskCount].id = stoi(line);
                    } else if (userList[userCount].planList[planCount].taskList[taskCount].name.empty()) {
                        userList[userCount].planList[planCount].taskList[taskCount].name = line;
                    } else if (userList[userCount].planList[planCount].taskList[taskCount].deadLine == 0) {
                        userList[userCount].planList[planCount].taskList[taskCount].deadLine = stoi(line);
                    } else if (userList[userCount].planList[planCount].taskList[taskCount].explanation.empty()) {
                        userList[userCount].planList[planCount].taskList[taskCount].explanation = line;
                    } else if (userList[userCount].planList[planCount].taskList[taskCount].priority == 0) {
                        userList[userCount].planList[planCount].taskList[taskCount].priority = stoi(line);
                    } else if (userList[userCount].planList[planCount].taskList[taskCount].state.empty()) {
                        userList[userCount].planList[planCount].taskList[taskCount].state = line;
                    }

                } else {
                    taskCount++;
                }

            } else {
                planCount++;
            }
        } else {
            userCount++;
            taskCount = 0;
            planCount = 0;
        }

    }
    fread.close();
}

int main() {
    string action;
    user userList[20];
    int userCount = 0;
    int time = calculateTime();
    setColor((1 << 4) | 14);
    cout << "Hi welcome to TODO LIST app" << endl;
    resetColor();
    do {
        cout << "what following action do you want to do ?" << endl;
        cout << "signup , login , savefile, readfile , exit" << endl;
        cin >> action;
        if (action == "signup") {
            string name, username;
            int password;
            cout << "Please enter your name" << endl;
            cin >> name;
            cout << "please enter your username" << endl;
            cin >> username;
            cout << "please enter your password" << endl;
            cin >> password;
            userList[userCount++] = signup(name, username, password);
            setColor(2);
            cout<<"you are successfully signup in this app"<<endl;
            resetColor();
        } else if (action == "login") {
            string username;
            int password;
            cout << "please enter your username" << endl;
            cin >> username;
            cout << "please enter your password" << endl;
            cin >> password;
            int valid = login(username, password, userList, userCount);
            if (username == "admin" and password == 12345) {
                adminMenu(userList, userCount);
            } else if (valid == -1) {
                setColor(4);
                cout << "your password or username is incorrect" << endl;
                resetColor();
            } else {
                loginMenu(userList, username, userCount);
            }
        } else if (action == "savefile") {
            savefile(userList, userCount);
            setColor(2);
            cout<<"tasks.txt successfully saved"<<endl;
            resetColor();
        } else if (action == "readfile") {
            readfile(userList, userCount);
            setColor(2);
            cout<<"tasks.txt successfully loaded"<<endl;
            resetColor();
        }

    } while (action != "exit");
    return 0;
}


