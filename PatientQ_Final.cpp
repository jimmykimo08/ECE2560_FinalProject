#include <iostream>
#include <queue>
#include <chrono>
#include <vector>
#include <thread>
using namespace std;

class PriorityQueue {
private :
// priority queue for severity, timer vector for wait time
// order vector for preserving patient arrival order
// patientID vector for easier identification in output
priority_queue<int> pq;
vector<chrono::time_point<std::chrono::system_clock>> timers;
vector<int> order;
vector<int> patientID;
int lastPatient = 0;
public :

bool isEmpty(){
    return pq.empty();
}

int maxTime(chrono::time_point<std::chrono::system_clock> str){
    // calculate duration from start point
    chrono::time_point<std::chrono::system_clock> stp;
    stp = chrono::system_clock::now();
    chrono::duration<double> dur = stp - str;
    double wT = dur.count();
    // if duration is past threshold, find the position in timers
    // where duration is past threshold and return index
    // this index will match with order vector
    if(wT > 3){
            for(int i=0; i<timers.size(); i++){
            if(timers[i] == str){
                return i;
            }
        }
        }
    return -1;
}

void nPatients(int code){
    // random number (0-3) of new patients added
    // form severity array with n new patients
int numPatients = (rand()%4);
        int arr[numPatients];
        // code 0 indicates window is open: add new patients
        if(code == 0){
        cout << "Patients added: ";
        for(int i=0; i<numPatients; i++){ 
        // random severity 1-3 for each new patient
        arr[i] = (rand()%3+1);
        // record start time in timer vector + order that patients arrive
        timers.push_back(std::chrono::system_clock::now());
        order.push_back(arr[i]);
        patientID.push_back(lastPatient+i+1);
        cout << "P" << lastPatient+i+1 << "(" << arr[i] << ") ";
        }
        if(!patientID.empty()){
            lastPatient = patientID.back();
        }
        cout << endl;
        }
        int proceed = -1;
        // if patients need to be added or line is not empty call maxTime
        if(numPatients != 0 || !pq.empty()){
            // proceed will be -1 if wait time is not reached or 0
            // only the first timer needs to be checked as timers stores
            // time points in order of arrival, if first timer is not 
            // past wait time threshold the others are not either
            proceed = proceed = maxTime(timers[0]);
        }

        // proceed -1 indicates wait time not reached, add patients > serve
        if(proceed == -1){
            // if window is still open, add patients to pq
            if(code == 0){
            for (int i=0; i<numPatients; i++) {
                pq.push(arr[i]);
            }}
            servePatient(proceed);
        }
        // proceed 0 indicates wait time reached, serve > add new patients
        // note that proceed accepts index at which wait time passes
        // threshold, as timers vector is in order of arrival, the first
        // timer duration will always be the longest
        else {
            servePatient(proceed);
            if(code == 0){
            for (int i=0; i<numPatients; i++) {
                pq.push(arr[i]);}
            }
        }
}

int matchOrderPrio(){
    // pq generally does not preserve order, arrival order is only
    // preserved for two of the same element; if severity 3 is added while
    // 3 is already part of the pq, it will be added behind the existing
    // as such, the first match returns the correct index 
for(int i=0; i<order.size(); i++){
    if(order[i] == pq.top()){
        return i;
    }
}
return 0;
}

int matchPrioOrder(int index){
    // similarly to matching the order vector element with the severity
    // being served in pq, the same process is done by incrementing
    // pos until the first match of severity the patient at given index
    priority_queue<int> copy = pq;
    int pos = 0;
while(!copy.empty()){
    if(copy.top() == order.at(index)){
        return pos;
    }
    copy.pop();
    pos += 1;
}
return 0;
}

void servePatient(int code){
    // base case for no patients to be served
    if(pq.empty()){
        cout << "Waiting for customers..." << endl;
        return;
    }
    // for usual case -1, serve patients off of severity
    // pq automatically sorts in decreasing order
    if(code == -1){
        int ind = matchOrderPrio();
        cout << "Serving patient P" <<
        patientID[ind] << " with severity: " << pq.top() << endl;
        // erase patient served from order and timers vectors
        // this is done by calling the match function
        order.erase(order.begin()+ind);
        timers.erase(timers.begin()+ind);
        patientID.erase(patientID.begin()+ind);
        pq.pop();
    }
    // if wait time has been reached, pq is modified by creating a new pq
    // in increasing order
    else {
        cout << "Max wait time reached. Serving patient P" <<
        patientID[code] << " with severity: ";
        cout << order[code] << " first." <<endl;
        priority_queue<int> copy = pq;
        priority_queue<int, vector<int>, greater<int>> temp;
        while(!copy.empty()){
        temp.push(copy.top());
        copy.pop();
    }
    // when wait time reached, code is assigned to index of the patient
    // for which wait time has been reached in the order and timers vectors
    // this will be 0 as the first arriving customer has waited the longest
    int pos = matchPrioOrder(code); 
    // pop reverse pq up until and including patient being served
    for(int i=0;i<pq.size() - pos;i++){ 
        temp.pop();
    }
    // pop pq up until and including patient being served
    for(int i=0;i<pos+1;i++){ 
        pq.pop();
    }
    // add remaining reverse pq elements to pq 
    while(!temp.empty()){ 
        pq.push(temp.top());
        temp.pop();
    }
    // erase patient from order and timers vectors
        order.erase(order.begin()+code);
        timers.erase(timers.begin()+code);
        patientID.erase(patientID.begin()+code);
    }
}

void dispLine(){
    // copy pq and display all elements in order
    priority_queue<int> copy = pq;
    // base case if priority queue is empty
    if(copy.empty()){
        cout << "Line is empty." << endl;
    }
    // this function is used to print the severity order
    // and was used for testing and variable tracing
    // not used in final implementation
    else{
    cout << "Severity Order: ";
    while (!copy.empty()) {
        cout << copy.top() << " ";
        copy.pop();
        }
        cout << endl;}
}

void dispOrder(){
    // display patient arrival order
    // base case for empty line
    if(order.empty()){
        cout << "Line is empty." << endl;
    }
    else{
        cout << "Arrival Order: ";
    for(int i = 0; i < patientID.size(); i++){
        // output format P[ID] (severity)
        cout << "P" << patientID[i] << "(" << order[i] << ") ";}
    cout << endl;
    }


}

};

// driver code
int main() {
    // initizalize window open time point and patientLine, random seed
    chrono::time_point<std::chrono::system_clock> open = chrono::system_clock::now();
    double close;
    PriorityQueue patientLine;
    srand((unsigned)time(0));
    while (close < 5){ 
        patientLine.nPatients(0);
        //patientLine.dispLine();
        patientLine.dispOrder();

    // run window for 5 seconds before closing window to new patients
    // update duration since open and add second delay
    chrono::time_point<std::chrono::system_clock> curtime = chrono::system_clock::now();
    chrono::duration<double> dur = curtime - open;
    close = dur.count();
    this_thread::sleep_for(chrono::seconds(1));
    }
    // once window has closed, call nPatients with code 1, indicating
    // that new patients should not be added to the pq
    cout << "Window has closed, no new patients." << endl;
    while(!patientLine.isEmpty()) {
        patientLine.nPatients(1);
        //patientLine.dispLine();
        patientLine.dispOrder();
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}