#include <bits/stdc++.h>

using namespace std;

int N, M, L;
int dgr[305];
vector<pair<int, int>> v;
vector<pair<int, int>> ans;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> L;
    int miniodd = 0, minieven = 0;
    for(int i = L; i; i--){
        cin >> dgr[i];
        if(dgr[i]%2 && !miniodd){
            miniodd = dgr[i];
        }
        if(dgr[i]%2 == 0 && !minieven){
            minieven = dgr[i];
        }
    }
    N = dgr[1]+1;
    int sum = 0;
    for(int i = 1; i<=L; i++){
        v.push_back({dgr[i], i});
        sum += dgr[i];
    }
    for(int i = L+1; i<N; i++){
        v.push_back({min(minieven, miniodd), i});
        sum += min(minieven, miniodd);
    }
    if(sum%2 == 1){
        v.push_back({miniodd, N});
    }
    else{
        v.push_back({minieven, N});
    }
    for(int n = 1; n<=N; n++){
        sort(v.begin(), v.end(), greater<pair<int, int>>());
        cout << v[0].first << endl;
        for(int i = 1; i<=v[0].first; i++){
            ans.push_back({v[i].second, v[0].second});
            v[i].first--;
            assert(v[i].first >= 0);
        }
        sort(v.begin(), v.end());
        v.pop_back();
    }
    M = ans.size();
    cout << M << "\n";
    for(auto p : ans){
        cout << p.first << " " << p.second << "\n";
    }
}
