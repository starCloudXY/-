#include <iostream>
#include "vector"
#include <cmath>
using namespace std;
int MaxTime=0;
int MinTime=INFINITY;
int MinStartTime=0;
int MaxWaitTime=0;
class DynamicEdge{
public:
    int to=0;
    int upper=0;
    int lower=0;
    int step=0;
public:
    DynamicEdge(){
        to=0;
        upper=0;
        lower=0;
        step=0;
    }
    DynamicEdge(int to,int lower,int upper,int step):to(to),lower(lower),upper(upper),step(step){};
    int cur_distance(int current)const{
        int duration=upper-lower;
        if(duration==0)return upper;
        int times=(current*step)/duration;
        int left=(current*step)%duration;
        if(times%2 == 0){
            return upper - left;
        }
        else return lower+left;
    }
};


void DFS(vector<DynamicEdge> *d,int from,int to,int &cur_time,int &start_time){
    if(from==to){
        //遍历到最后
        if(cur_time < MinTime){
            MinTime = cur_time;//最小时间
            MinStartTime = start_time;
        }
        return;
    }
    int size=d[from].size();
    for(int i=0;i<size;i++){
        int dur=d[from][i].cur_distance(cur_time);
        cur_time += dur;
        if(cur_time < MinTime){
            DFS(d,d[from][i].to,to,cur_time,start_time);
        }
        cur_time-=dur;
    }
    return;
}
int main() {
    int N,M;
    int K;
    cin>>N>>M>>K;
    auto *init = new vector<DynamicEdge>[N];
    int from,to,lower,upper,step;
    for(int i=0;i<M;i++){
        cin>>from>>to>>lower>>upper>>step;
        init[from].emplace_back(to,lower,upper,step);
        MaxWaitTime+=upper-lower;
    }
    int startTime;
    for (int i = 0;; i++) {
        startTime = i * K;
        if(startTime >=MaxWaitTime||startTime>MinTime)break;
        int time = startTime;
        DFS(init,0, N - 1, time, startTime);
    }
    delete[] init;
    std::cout <<MinStartTime << ' ' << MinTime << std::endl;
    return 0;
}