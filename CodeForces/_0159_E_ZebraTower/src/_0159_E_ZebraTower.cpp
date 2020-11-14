#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> cmp;
vector<int> lst[100005];
int clr[100005], v[100005];
long long maxi[100005];

int main(){
    cin >> N;
    for(int i= 1; i<=N; i++){
        cin >> clr[i] >> v[i];
        cmp.push_back(clr[i]);
    }
    sort(cmp.begin(), cmp.end());
    cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
    int M = (int) cmp.size();
    for(int i =0; i<M; i++){
        lst[i].push_back(0);
    }
    for(int i = 1; i<=N; i++){
        lst[lower_bound(cmp.begin(), cmp.end(), clr[i])-cmp.begin()].push_back(v[i]);
    }
    long long ans = 0;
    fill(maxi+1, maxi+1+N, LLONG_MIN);
    for(int i = 0; i<M; i++){
        sort(lst[i].begin()+1, lst[i].end());
        for(int j = 1; j<lst[i].size(); j++){
            lst[i][j] += lst[i][j-1];
            ans = max(ans, max(lst[i][j] + maxi[j+1], lst[i][j] + maxi[j]));
            ans = max(ans, lst[i][j] + maxi[j-1]);
        }
        for(int j= 1;j <lst[i].size(); j++){
            maxi[j] = max(maxi[j], lst[i][j]);
        }
    }
    cout << ans << endl;
}
