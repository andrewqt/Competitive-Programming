#include <bits/stdc++.h>

using namespace std;

priority_queue<pair<int, int>> pq1, pq2;
int a[300000], b[300000];
int N;
long long ans = 0;

int main(){
    scanf("%d", &N);
    for(int i = 1; i<=N; i++){
        scanf("%d", &a[i]);
        ans += a[i];
    }
    for(int i = 1; i<=N; i++){
        scanf("%d", &b[i]);
        if(a[i] < b[i]){
            pq1.push({b[i]-a[i], i});
        }
        else{
            pq2.push({a[i]-b[i], i});
        }
    }
    if(pq2.size()%2 == 0){
        while(!pq2.empty()){
            ans -= pq2.top().first;
            pq2.pop();
        }
    }
    else{
        pq1.push({0,0});
        while(pq1.size() > 1){
            pq1.pop();
        }
        while(pq2.size() > 1){
            ans -= pq2.top().first;
            pq2.pop();
        }
        if(pq2.top().first < pq1.top().first){
            ans -= pq1.top().first;
        }
    }
    cout << ans << endl;
}
