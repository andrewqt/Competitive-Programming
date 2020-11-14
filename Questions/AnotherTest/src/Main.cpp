#include <bits/stdc++.h>

using namespace std;

int N;
vector<pair<long long, int>> vec;
long long arr[1000005];

int main(){
    cin >> N;
    long long tot = 0;
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
        tot += arr[i];
    }
    tot /= N;
    for(int i =1; i<=N; i++){
        arr[i] -= tot;
        vec.push_back({arr[i], i});
    }
    sort(vec.begin(), vec.end());
    int p = vec[N/2];
    int t = N;
    long long crnt = 0, inhand = 0;
    for(int i = p; t--; i = (i)%N+1){
        crnt += abs(inhand);
        inhand += arr[i];
    }
    cout << crnt << endl;
}
