#include <bits/stdc++.h>

using namespace std;

int N;
long long T;
long long BITcnt[1000005], BITval[1000005];
vector<pair<int, int>> graph[100005];
long long num[100005], val[100005];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> T;
    for(int i = 1; i<=N; i++){
        cin >> num[i];
    }
    for(int i = 1; i<=N; i++){
        cin >> val[i];
    }
}
