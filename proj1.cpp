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

void dfs_recur(Student* student, Student* students, vector <Student*> stack, int* time) {
    stack.push_back(student);
    student->onStack = 1;
    student->discovery = student->low = (*time)++;  

    for (auto &it : student->friends){
        student->estimated = max(it->estimated, student->estimated);
        if (it->visited == 0){
            it->visited = 1;
            
            dfs_recur(it, students, stack, time);
            student->low = min(student->low, it->low);
        }
        if (it->onStack) 
            student->low = min(student->low, it->low);
    }

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

    for(int i = 0; i < n_students; i++) {
        if(students[i].visited == 0){
            students[i].visited = 1;
            dfs_recur(&students[i], students, stack, time);
        }
    }
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

    // ir as conexoes com outros grupos buscar o maior estimated + atualizar low

    for(int i = 0; i < n_students; i++){
        vector <int> considered_lows;
        considered_lows.push_back(students[i].low);
        for(unsigned j=0; j < students[i].friends.size(); j++){
            
            if(find(considered_lows.begin(), considered_lows.end(), students[i].friends[j]->low) != considered_lows.end());
            else {
                considered_lows.push_back(students[i].friends[j]->low);
                students[i].estimated = max(students[i].friends[j]->estimated, students[i].estimated);
                if(total_lows[students[i].low] < students[i].estimated)
                    total_lows[students[i].low] = students[i].estimated;
            }
        }
        considered_lows.clear();
    }

    // ir aos amiguinhos com mesmo low e igualar novamente o estimated

    for(int i = 0; i < n_students; i++) {
        students[i].estimated = total_lows[students[i].low];
    }

    /*for(int i = 0; i < n_students; i++){
        vector <int> considered_lows;
        considered_lows.push_back(students[i].low);
        for(unsigned j=0; j < students[i].friends.size(); j++){  
            considered_lows.push_back(students[i].friends[j]->low);
            students[i].estimated = max(students[i].friends[j]->estimated, students[i].estimated);
            printf("%d : %d // %u : %d \n", i,students[i].estimated, j,  students[i].friends[j]->estimated );
        }
        considered_lows.clear();
    }*/

    for(int i = 0; i < n_students; i++) {
        cout << students[i].estimated;
        cout << "\n";
    }

return 0;
}
