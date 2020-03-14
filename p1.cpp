#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

using namespace std;

struct Student
{
    int estimated;
    int visited = 0;
    int onStack = 0;
    int id;
    int discovery = 0;
    int low = 0;
    vector <Student*> friends;

};

void dfs_recur(Student* student, Student* students, vector <Student*> stack, int time) {
    stack.push_back(student);
    student->onStack = 1;
    student->discovery = student->low = time++;

    for (auto &it : student->friends){
        if (it->visited == 0){
            it->visited = 1;
            cout << it->id + 1;
            cout << "\n";
            dfs_recur(it, students, stack, time);
        }
        if (it->onStack)
            student->low = min(student->low, it->low);  
    }
    if (student->discovery == student->low) {
        Student* q = stack.back();
        stack.pop_back();
        while (q != student) {
            q->onStack = 0;
            q->low = student->discovery;
            q = stack.back();
            stack.pop_back();
        }
    cout << "scc\n";
    }
}

void dfs(Student* students, int n_students){
    
    vector <Student*> stack;
    int time = 0;

    for(int i = 0; i < n_students; i++) {
        if(students[i].visited == 0){
            students[i].visited = 1;
            dfs_recur(&students[i], students, stack, time);
        }
    }
}

int main (){

   int n_students, n_friends;
  
    cin >> n_students;
    cin.get();
    cin >> n_friends;

    if(n_students < 2 || n_friends < 1){
        cout << "Incorrect arguments\n";
        exit(1);
    }

    Student* students = new Student[n_students];

    for(int i = 0; i < n_students; i++) {
        
        Student* student = new Student();
        cin >> student->estimated;
        student->id = i;
        students[i] = *student;
    }
 
    for(int i = 0; i < n_friends; i++){

        int student_temp, friend_temp;
        cin >> student_temp;
        cin >> friend_temp;

        students[student_temp - 1].friends.push_back(&students[friend_temp - 1]);
    }

/* prints friendships with student id [1:n_students]

    for(int i = 0; i < n_students; i++){
    cout << students[i].id +1;
            cout << ":";
        for (auto &it : students[i].friends){
            cout << " ";
            cout << it->id +1;
        }
        cout << "\n";
    }
*/

    dfs(students, n_students);

return 0;
}

