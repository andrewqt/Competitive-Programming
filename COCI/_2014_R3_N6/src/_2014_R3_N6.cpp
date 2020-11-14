#include <bits/stdc++.h>

using namespace std;

int N, M, B = 500;
vector<int> pre[100005], arr[100005];
vector<int> hvy;
bool ishvy[100005];

int main(){
    cin >> N >> M >> B;
    for(int i = 1; i<=N; i++){
        int K;
        cin >> K;
        arr[i].push_back(0);
        int n;
        cin >> n;
        arr[i].push_back(n);
        for(int j = 2; j<=K; j++){
            cin >> n;
            arr[n].push_back(n);
            pre[i].push_back(abs(n - arr[i].back()));
        }
        if(K > 200){
            hvy.push_back(i);
            ishvy[i] = 1;
        }
    }
}
