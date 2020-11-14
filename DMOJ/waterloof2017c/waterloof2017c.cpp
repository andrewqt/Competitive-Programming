#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> v;
deque<pair<int, int>> dq;

int main(){
    cin >> N >> K;
    for(int i = 1; i<=N; i++){
        int n;
        cin >> n;
        v.push_back(n);
    }
    sort(v.begin(), v.end());
    int ans = 0;
    for(int i = 0; i<N; i++){
        if(i + K - 1 < v.size()){
            while(dq.size() && dq.back().second >= v[i+K-1]-v[i]){
                dq.pop_back();
            }
            dq.push_back({i, v[i+K-1]-v[i]});
        }
        while(dq.size() && dq.front().first + K - 1 < i){
            dq.pop_front();
        }
        ans = max(ans, dq.front().second);
    }
    cout << ans << endl;
}
