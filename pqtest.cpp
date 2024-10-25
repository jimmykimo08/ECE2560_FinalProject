#include <iostream>
#include <queue>
#include <chrono>
#include <vector>
using namespace std;

class PriorityQueue {
private :
priority_queue<int> pq;
vector<chrono::time_point<std::chrono::system_clock>> timers;
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
    //cout << "duration: " << wT << endl;
    if(wT > 5){
        //cout << wT << endl;
            return 1;
        }
    return 0;
}

void nPatients(){
int numPatients = (rand()%4);
        int arr[numPatients];
        cout << "Patient severities added: ";
        for(int i=0; i<numPatients; i++){ 
        arr[i] = (rand()%3+1);
        cout << arr[i] << " ";
        timers.push_back(std::chrono::system_clock::now());
        }
        cout << endl;
        int proceed = 0;
        for(int i=0; i<timers.size(); i++){
            proceed += maxTime(timers[i]);
        }
        if(proceed == 0){
            for (int i=0; i<numPatients; i++) {
                pq.push(arr[i]);
            }
        }
}

void servePatient(int code){
    if(code == 0){
        cout << "Serving patient with severity: " << pq.top() << endl;
        pq.pop();
    }
}

void dispLine(){
    priority_queue<int> copy = pq;
    cout << "Line: ";
    while (!copy.empty()) {
        cout << copy.top() << " ";
        copy.pop();
        }
        cout << endl;
}

};
// driver code
int main()
{
    chrono::time_point<std::chrono::system_clock> open = chrono::system_clock::now();
    double close;
    PriorityQueue patientLine;
    srand((unsigned)time(0));
    while (close < .003){ 
        patientLine.nPatients();
        patientLine.dispLine();
        patientLine.servePatient(0);


    chrono::time_point<std::chrono::system_clock> curtime = chrono::system_clock::now();
    chrono::duration<double> dur = curtime - open;
    close = dur.count();
    //cout << close << endl;
    }
    cout << "Window has closed, no new patients." << endl;
    while(!patientLine.isEmpty()) {
        patientLine.dispLine();
        patientLine.servePatient(0);
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