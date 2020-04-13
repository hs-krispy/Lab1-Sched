#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
#include <string.h>
using namespace std;

queue<pair<char, int>> result;
struct process {
    char processName; // 프로세스 번호, priority
    int serviceTime; // 동작시간
    int arriveTime; // 도착시간
    int waitTime; // 대기시간
    /*for stride----*/
    int stride;
    int ticket;
    int passValue = 0; // initialize
    /*--------------*/
};
vector<process> v(5);
void SetInit() {
    v[0].arriveTime = 0, v[0].serviceTime = 3, v[0].processName = 'A';
    v[1].arriveTime = 2, v[1].serviceTime = 6, v[1].processName = 'B';
    v[2].arriveTime = 4, v[2].serviceTime = 4, v[2].processName = 'C';
    v[3].arriveTime = 6, v[3].serviceTime = 5, v[3].processName = 'D';
    v[4].arriveTime = 8, v[4].serviceTime = 2, v[4].processName = 'E';
}
void RR(vector<process> p, int ts) {
    int time = 0;
    int killedProcess = 0;
    int nextIdx = 1;
    queue<process> q;
    q.push(p[0]);
    while(killedProcess < p.size()) { // 모든 프로세스가 완료되면 종료
        process temp = q.front();
        int restTime = temp.serviceTime - ts; // 해당 프로세스의 남은 수행시간
        if(restTime <= 0) { // 프로세스의 남은 시간이 없을 때 (수행 종료)
            time += temp.serviceTime;
            result.push({temp.processName, q.front().serviceTime});
            q.pop();
            killedProcess++; // 완료된 프로세스 체크
            for(int i = nextIdx; i < p.size(); i++) { // 현재까지 시간보다 해당 프로세스의 도착시간이 같거나 작은 경우
                if(time >= p[i].arriveTime) {
                    q.push(p[i]);
                    nextIdx = i + 1;
                }
            }
        } else {
            time += ts;
            for(int i = nextIdx; i < p.size(); i++) { // 현재까지 시간보다 해당 프로세스의 도착시간이 같거나 작은 경우
                if(time >= p[i].arriveTime) {
                    q.push(p[i]);
                    nextIdx = i + 1;
                }
            }
            result.push({temp.processName, ts}); // 결과를 넣을 큐에 해당 프로세스 이름과, 타임슬라이스 넣어줌
            temp.serviceTime -= ts; // 수행시간 타임슬라이스 만큼 감소
            q.pop();
            q.push(temp); // 작업을 수행하고 다시 큐 안으로 들어옴
        }
    }
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
int main() {
    SetInit();
    RR(v, 4);
    Print();
    return 0;
}