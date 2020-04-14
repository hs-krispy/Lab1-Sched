#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
#include <string.h>
using namespace std;

/* define process struct */
struct process {
    char processName; // 프로세스 번호, priority
    int serviceTime; // 동작시간
    int arriveTime; // 도착시간
    int waitTime; // 대기시간
    int turnaroundTime; // 반환시간
    /*for stride----*/
    int stride;
    int ticket;
    int passValue = 0; // initialize
    /*--------------*/
};
/* end of process struct */

/* perform 5 processes */
queue<pair<char, int>> result;
vector<process> v(5);
/* end of 5 processes */

/* for calculate and print performance */
float avgTurnaround = 0;
float avgWait = 0;
vector<int> turnaround(5, 0); // 5 processes
vector<int> pWait(5, -1); // 5 processes
/* end of calculate and print */



void SetInit() {
    v[0].arriveTime = 0, v[0].serviceTime = 3, v[0].processName = 'A';
    v[1].arriveTime = 2, v[1].serviceTime = 6, v[1].processName = 'B';
    v[2].arriveTime = 4, v[2].serviceTime = 4, v[2].processName = 'C';
    v[3].arriveTime = 6, v[3].serviceTime = 5, v[3].processName = 'D';
    v[4].arriveTime = 8, v[4].serviceTime = 2, v[4].processName = 'E';
}
// scheduling table ■ □
void Print() {
    char task[5] = {'A', 'B', 'C', 'D', 'E'};
    int time = 0;
    int size = result.size();
    vector<pair<char, int>> arr(size);
    for(int i = 0; i < size; i++) {
        arr[i].first = result.front().first;
        arr[i].second = result.front().second;
        time += result.front().second;
        result.pop();
    }
    for(int i = 0; i < 5; i++) {
        time = 0;
        cout << task[i] << " ";
        for(int j = 0; j < arr.size(); j++) {
            if(task[i] == arr[j].first) {
                for(int k = 0; k < arr[j].second; k++) {
                    cout << "■ ";
                }
            } else {
                time += arr[j].second;
                for(int k = 0; k < time; k++) {
                    cout << "□ ";
                }
                time = 0;
            }
        }
        cout << '\n';
    }
}
void calcWait(vector<process> p, int ts) 
{
    queue<pair<char, int>> copy;
    copy = result;
    int time = 0;
    while(!copy.empty())
    {
        for(int i = 0; i < p.size(); i++)
        {
            if(pWait[i] == -1 && copy.front().first == p[i].processName)
            {
                p[i].waitTime = pWait[i] = time - p[i].arriveTime;
                avgWait += p[i].waitTime;
            }
        }
        time += copy.front().second;
        copy.pop();
    }
    avgWait /= p.size();
} 
void calcTurnaround(vector<process> p, int ts)
{
    queue<pair<char, int>> copy;
    copy = result;
    int time = 0;
    while(!copy.empty())
    {
        time += copy.front().second;
        for(int i = 0; i < p.size(); i++)
        {
            if(copy.front().first == p[i].processName)
            {
                p[i].turnaroundTime = turnaround[i] = time;
                avgTurnaround += p[i].turnaroundTime;
            }
        }
        copy.pop();
    }
    avgTurnaround /= p.size();
}
void getPerformance(vector<process> p)
{
    calcWait(p, 4);
    calcTurnaround(p, 4);
    for(int i = 0; i < p.size(); i++)
    {
        cout<<"process : "<<p[i].processName<<"\tturnaroundTime : "<<turnaround[i]<<"\twaitTime : "<<pWait[i]<<"\n";
    }
    cout<<"Average turnaroundTime : "<<avgTurnaround<<" Average waitTime : "<<avgWait<<"\n";
} // print Performance
void MLFQ(vector<process> p) {
    queue<process> q[3]; // 3개의 큐,
    int ts[3] = {1, 2, 4};
    int time = 0;
    int nextIdx = 1;
    bool newProcess = false;
    int killedProcess = 0;
    int ready = 1;
    q[0].push(p[0]);
    while (killedProcess < p.size()) {
        while(!q[0].empty()) {
            newProcess = false;
            process temp = q[0].front();
            int restTime = temp.serviceTime - ts[0];
            if(restTime <= 0) { // 남은 시간이 없을 때,
                time += temp.serviceTime;
                result.push({temp.processName, q[0].front().serviceTime});
                q[0].pop();
                killedProcess++;
                for(int i = nextIdx; i < p.size(); i++) {
                    if(time >= p[i].arriveTime) {
                        q[0].push(p[i]);
                        nextIdx = i + 1;
                        newProcess = true;
                        ready++;
                    }
                }
            } else {
                time += ts[0];
                for(int i = nextIdx; i < p.size(); i++) {
                    if (time >= p[i].arriveTime) {
                        q[0].push(p[i]);
                        nextIdx = i + 1;
                        ready++;
                        newProcess = true;
                    }
                }
                temp.serviceTime -= ts[0];
                result.push({temp.processName, ts[0]});
                if(ready != 1) {
                    q[0].pop();
                    q[1].push(temp);
                } else {
                    q[0].pop();
                    q[0].push(temp);
                }
            }
            if(newProcess) {
                break;
            }
        }
        while (!q[1].empty()) {
            if(newProcess) {
                break;
            }
            newProcess = false;
            process temp = q[1].front();
            int restTime = temp.serviceTime - ts[1];
            if(restTime <= 0) { // 남은 시간이 없을 때,
                time += temp.serviceTime;
                result.push({temp.processName, q[1].front().serviceTime});
                q[1].pop();

                killedProcess++;
                for(int i = nextIdx; i < p.size(); i++) {
                    if(time >= p[i].arriveTime) {
                        q[0].push(p[i]);
                        nextIdx = i + 1;
                        newProcess = true;
                    }
                }
            } else {
                time += ts[1];
                for(int i = nextIdx; i < p.size(); i++) {
                    if(time >= p[i].arriveTime) {
                        q[0].push(p[i]);
                        nextIdx = i + 1;
                        newProcess = true;
                    }
                }
                temp.serviceTime -= ts[1];
                result.push({temp.processName, ts[1]});
                q[1].pop();
                q[2].push(temp);
            }
            if(newProcess) {
                break;
            }
        }
        while (!q[2].empty()) {
            if(newProcess) {
                break;
            }
            newProcess = false;
            process temp = q[2].front();
            int restTime = temp.serviceTime - ts[2];
            if(restTime <= 0) { // 남은 시간이 없을 때,
                time += temp.serviceTime;
                result.push({temp.processName, q[2].front().serviceTime});
                q[2].pop();
                killedProcess++;
                for(int i = nextIdx; i < p.size(); i++) {
                    if(time >= p[i].arriveTime) {
                        q[0].push(p[i]);
                        nextIdx = i + 1;
                        newProcess = true;
                    }
                }
            } else {
                time += ts[2];
                for(int i = nextIdx; i < p.size(); i++) {
                    if(time >= p[i].arriveTime) {
                        q[0].push(p[i]);
                        nextIdx = i + 1;
                        newProcess = true;
                    }
                }
                temp.serviceTime -= ts[2];
                result.push({temp.processName, ts[2]});
                q[2].pop();
                q[2].push(temp);
            }
            if(newProcess) {
                newProcess = false;
                break;
            }
        }
    }
}
int main() {
    SetInit();
    MLFQ(v);
    Print();
    return 0;
}