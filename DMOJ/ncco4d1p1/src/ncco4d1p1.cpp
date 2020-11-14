#include <bits/stdc++.h>

using namespace std;

int main(){
    priority_queue<int> pq;
    int N;
    cin >> N;
    long long ans = 0;
    for(int i = 1; i<=N; i++){
        int n;
        cin >> n;
        pq.push(-n);
    }
    while(pq.size() > 1){
        int f = pq.top();
        pq.pop();
        int s = pq.top();
        pq.pop();
        ans -= f+s;
        pq.push(f+s);
    }
    cout << ans << endl;
}
