#include <bits/stdc++.h>

using namespace std;

struct triple{
    long long x, y, z;
    bool operator < (const triple &t) const{
        return -x < -t.x;
    }
};

priority_queue <triple> pq1, pq2;
int N;
long long T = 0;

int main(){
    cin >> N;
    for(int i = 1; i<=N; i++){
       triple t;
       t.y = (long long) i;
       cin >> t.x >> t.z;
       pq1.push(t);
    }
    long long ans = 0;
    while(!pq1.empty()){
        if(pq2.empty()){
            triple p = pq1.top();
            T = p.x;
            swap(p.x, p.y);
            pq2.push(p);
            pq1.pop();
        }
        else{
            while(!pq1.empty() && pq1.top().x <= T){
                triple p = pq1.top();
                swap(p.x, p.y);
                pq2.push(p);
                pq1.pop();
            }
        }
        triple p = pq2.top();
        ans = max(T-p.y, ans);
        T += p.z;
        pq2.pop();
        while(!pq1.empty() && pq1.top().x <= T){
            triple p = pq1.top();
            swap(p.x, p.y);
            pq2.push(p);
            pq1.pop();
        }
    }
    while(!pq2.empty()){
        triple p = pq2.top();
        ans = max(T-p.y, ans);
        T += p.z;
        pq2.pop();
    }
    cout << ans << endl;
}
