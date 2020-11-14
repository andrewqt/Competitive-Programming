#include <bits/stdc++.h>

using namespace std;

int N, D, C;
int cap[100005], fuel[100005], len[100005];
priority_queue<int> pq;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> D >> C;
    long long opt1 = 0, opt2 = 0;
    for(int i = 1; i<=N; i++){
        cin >> cap[i] >> fuel[i] >> len[i];
    }
    long long sum1 = 0, sum2 = 0;
    for(int i = 1; i<=N; i++){
        if(len[i] >= D){
            pq.push(fuel[i]);
            sum1 += fuel[i];
        }
        while(sum1 > C){
            sum1 -= pq.top();
            pq.pop();
        }
    }
    opt1 = pq.size();
    bool has = 0;
    long long tot = 0;
    int mini = INT_MAX;
    int idx = 0;
    for(int i = 1; i<=N; i++){
        if(cap[i] && fuel[i] <= C && len[i] >= D){
            has = 1;
        }
        if(cap[i]){
            tot += cap[i];
            if(len[i] >= D){
                mini = min(mini, fuel[i]);
                if(mini == fuel[i]){
                    idx = i;
                }
            }
        }
    }
    if(!has){
        cout << opt1 << " " << sum1 << endl;
        return 0;
    }
    C -= mini;
    while(pq.size()){
        pq.pop();
    }
    opt2 = tot + 1;
    for(int i = 1; i<=N; i++){
        if(len[i] >= D && i != idx){
            pq.push(fuel[i]);
            sum2 += fuel[i];
        }
        while(sum2 > C){
            sum2 -= pq.top();
            pq.pop();
        }
    }
    sum2 += mini;
    opt2 += (int) (pq.size());
    opt2 = min(N*1LL, opt2);
    //cout << opt1 << " " << sum1 << endl;
    //cout << opt2 << " " << sum2 << endl;
    if(opt1 == opt2){
        if(sum1 > sum2){
            cout << opt2 << " " << sum2 << endl;
        }
        else{
            cout << opt1 << " " << sum1 << endl;
        }
    }
    else if(opt1 > opt2){
        cout << opt1 << " " << sum1 << endl;
    }
    else{
        cout << opt2 << " " << sum2 << endl;
    }
}
