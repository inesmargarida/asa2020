#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <map>

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

void dfs_recur(Student* student, Student* students, vector <Student*> stack, int* time, vector<vector<Student*>> paths) {
    stack.push_back(student);
    student->onStack = 1;
    student->discovery = student->low = (*time)++;  

    for (auto &it : student->friends){
        if (it->visited == 0){
            it->visited = 1;
            
            dfs_recur(it, students, stack, time, paths);
            student->low = min(student->low, it->low);
        }
        if (it->onStack) 
            student->low = min(student->low, it->low);
    }

    for (int i = stack.size() - 1; i > 0; i--)
        stack[i-1]->estimated = max(stack[i]->estimated, stack[i-1]->estimated);
    paths.push_back(stack);

    if (student->discovery == student->low) {
        Student* q = stack.back();
        stack.pop_back();
        q->onStack = 0;
        q->low = student->discovery;
        while (q != student) {
            
            q = stack.back();
            q->low = student->discovery;
            stack.pop_back();
            q->onStack = 0;
        }
    }
}

void dfs(Student* students, int n_students, int* time){
    
    vector <Student*> stack;
    vector<vector<Student*>> paths;

    for(int i = 0; i < n_students; i++) {
        if(students[i].visited == 0){
            students[i].visited = 1;
            dfs_recur(&students[i], students, stack, time, paths);
        }
    }

    for(auto path : paths)
        for(int i = path.size() - 1; i > 0; i--)
            path[i-1]->estimated = max(path[i]->estimated, path[i-1]->estimated);
    
}

int main (){

   int n_students, n_friends, time = 0;
  
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

    dfs(students, n_students, &time);

    // associar um maximo a cada low

    map<int, int> total_lows;

    for(int i = 0;i  < n_students; i++) 
        if(total_lows.find(students[i].low) == total_lows.end())
            total_lows.insert({students[i].low, -1});

    for(int i = 0; i < n_students; i++) {
        if(total_lows[students[i].low] < students[i].estimated)
            total_lows[students[i].low] = students[i].estimated;
    }

    //for (auto itr = total_lows.begin(); itr != total_lows.cend(); ++itr) { 
    //    cout << itr->first  << '\t' << itr->second << '\n';
    //}
    // colocar o maximo em cada estudante com esse low

    for(int i = 0; i < n_students; i++) {
        students[i].estimated = total_lows[students[i].low];
    }




    for(int i = 0; i < n_students; i++) {
        cout << students[i].estimated;
        cout << "\n";
    }

return 0;
}

