#include <iostream>
#include <queue>
#include <chrono>
#include <vector>
#include <thread>
using namespace std;

class PriorityQueue {
private :
priority_queue<int> pq;
vector<chrono::time_point<std::chrono::system_clock>> timers;
vector<int> order;
public :

/*double wait(chrono::time_point<std::chrono::system_clock> str){
    chrono::time_point<std::chrono::system_clock> stp;
    stp = chrono::system_clock::now();
    chrono::duration<double> dur = stp - str;
    return dur.count();
}*/

bool isEmpty(){
    return pq.empty();
}

int maxTime(chrono::time_point<std::chrono::system_clock> str){
    chrono::time_point<std::chrono::system_clock> stp;
    stp = chrono::system_clock::now();
    chrono::duration<double> dur = stp - str;
    double wT = dur.count();
    if(wT > 1.5){
            for(int i=0; i<timers.size(); i++){
            if(timers[i] == str){
                return i;
            }
        }
        }
    return -1;
}


void nPatients(int code){
int numPatients = (rand()%4);
        int arr[numPatients];
        if(code == 0){
        cout << "Patient severities added: ";
        for(int i=0; i<numPatients; i++){ 
        arr[i] = (rand()%3+1);
        cout << arr[i] << " ";
        timers.push_back(std::chrono::system_clock::now());
        order.push_back(arr[i]);
        }
        cout << endl;}
        int proceed = 0;
        int timercheck = 0;
        while(timercheck<timers.size() && proceed == 0){
            proceed += maxTime(timers[timercheck]);
            timercheck += 1;
        }
        if(proceed == -1 || pq.empty()){
            if(code == 0){
            for (int i=0; i<numPatients; i++) {
                pq.push(arr[i]);
            }}
            servePatient(proceed);
        }
        else {
            servePatient(proceed-1);
            if(code == 0){
            for (int i=0; i<numPatients; i++) {
                pq.push(arr[i]);}
            }
        }
}

int matchOrderPrio(){
for(int i=0; i<order.size(); i++){
    if(order[i] == pq.top()){
        return i;
    }
}
return 0;
}

int matchPrioOrder(int index){
    priority_queue<int> copy = pq;
    int pos = 0;
while(!copy.empty()){
    // 2 1 1 1 | 2 1 1 1 return 0
    if(copy.top() == order.at(index)){
        return pos;
    }
    copy.pop();
    pos += 1;
}
return 0;
}
// THIS WORKS BECAUSE THE FIRST MATCH CAME FIRST

// FOR SAME VALUE, ONE THAT COMES FIRST IS CLOSER TO FRONT
void servePatient(int code){
    if(code == -1){
        cout << "Serving patient with severity: " << pq.top() << endl;
        order.erase(order.begin()+matchOrderPrio());
        timers.erase(timers.begin()+matchOrderPrio());
        pq.pop();
    }
    else {
        cout << "Max wait time reached. Serving patient with severity: ";
        cout << order[code] << " first." <<endl;
        // copy = 2 1 1 1
        // order = 2 1 1 1
        // temp = 1 1 1 2
        // code = 0
        priority_queue<int> copy = pq;
        priority_queue<int, vector<int>, greater<int>> temp;
        while(!copy.empty()){
        temp.push(copy.top());
        copy.pop();
    }
    int pos = matchPrioOrder(code); // pos = 0
    for(int i=0;i<pq.size() - pos;i++){ // 4 times, temp = 0
        temp.pop();
    }
    for(int i=0;i<pos+1;i++){ // 1 times, pq = 1 1 1
        pq.pop();
    }
    while(!temp.empty()){ // pq = 1 1 1
        pq.push(temp.top());
        temp.pop();
    }
    // [3 3 2 2 1 1 ]
    // [1 1 2 2 3 3]
    // pq.size - pos = 4
    // [3 3]
    // [2 1 1]
        //cout << "Serving patient with severity: " << pq.top() << endl;
        order.erase(order.begin()+code);
        timers.erase(timers.begin()+code);
        // implement method to identify and erase lower prio patient
    }
}

void dispLine(){
    priority_queue<int> copy = pq;
    if(copy.empty()){
        cout << "Line is empty." << endl;
    }
    else{
    cout << "Line: ";
    while (!copy.empty()) {
        cout << copy.top() << " ";
        copy.pop();
        }
        cout << endl;}
}

void dispOrder(){
    cout << "Order: ";
    if(order.empty()){
        cout << "Order is empty." << endl;
    }
    else{
    for (int i = 0; i < order.size(); i++){
        cout << order[i] << " ";}
    cout << endl;}
}

};
// driver code
int main()
{
    chrono::time_point<std::chrono::system_clock> open = chrono::system_clock::now();
    double close;
    PriorityQueue patientLine;
    srand((unsigned)time(0));
    while (close < 5){ 
        patientLine.nPatients(0);
        patientLine.dispLine();
        patientLine.dispOrder();


    chrono::time_point<std::chrono::system_clock> curtime = chrono::system_clock::now();
    chrono::duration<double> dur = curtime - open;
    close = dur.count();
    this_thread::sleep_for(chrono::seconds(1));
    //cout << close << endl;
    }
    cout << "Window has closed, no new patients." << endl;
    while(!patientLine.isEmpty()) {
        patientLine.nPatients(1);
        patientLine.dispLine();
        patientLine.dispOrder();
        this_thread::sleep_for(chrono::seconds(1));
    }
    /*int numPatients[5];
    int size = sizeof(arr) / sizeof(arr[0]);
    chrono::time_point<std::chrono::system_clock> timers[5];
    for(int i=0; i<size; i++){ 
        arr[i] = (rand()%5)+1;
        timers[i] = std::chrono::system_clock::now();
        }
    // array of patients with varying severity 1-5
    // defining priority queue
    
    // printing array
    cout << "Array: ";
    for (auto i : arr) {
        cout << i << ' ';
    }
    cout << endl;
    // pushing array sequentially one by one
    for (int i = 0; i < size; i++) {
        pq.push(arr[i]);
    }
    priority_queue<int> pqprint = pq;
    // printing priority queue
    int cnt = 0;
    double waitTimes[size];
    while (!pq.empty()) {
        cout << "Serving: " << pq.top()<< endl;
        for(int i=0; i<5; i++){
        waitTimes[i] = wait(timers[i]);
        }
        pq.pop();
        for(int j=cnt; j<5; j++){
            cout << "Time for patient " << j+1 << ": " << waitTimes[j] << endl;
        }
        cnt += 1;
    }*/

    return 0;
}