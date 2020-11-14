#include <bits/stdc++.h>

using namespace std;

int N;
double t1, t2, k;

double calc(int s1, int s2){
    return t1*k*s1/100.0+t2*s2;
}

vector<pair<double, int>> ans;

int main(){
    cin >> N >> t1 >> t2 >> k;
    for(int i = 1; i<=N; i++){
        int a, b;
        cin >> a >> b;
        ans.push_back({-max(calc(a, b), calc(b, a)), i});
    }
    sort(ans.begin(), ans.end());
    for(int i = 0; i<N; i++){
        printf("%d %.2f\n", ans[i].second, -ans[i].first);
    }
}
