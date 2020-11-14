#include <bits/stdc++.h>

using namespace std;

int N;
long long A, B;
long long lft[1000005], rht[1000005];
vector<pair<long long, long long>> v;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> A >> B;
    double Ap = (double) A, Bp = (double) B;
    for(int i =1 ; i<=N; i++){
        cin >> lft[i] >> rht[i];
    }
    long long ans = 0;
    if(Ap*Bp/__gcd(A, B+1) >= 1e18){
        for(int i = 1; i<=N; i++){
            ans += rht[i] - lft[i] + 1;
        }
    }
    else{
        long long P = A/__gcd(A, B+1)*B;
        for(int i = 1; i<=N; i++){
            if(rht[i] - lft[i] + 1 >= P){
                ans = P;
                cout << ans << endl;
                return 0;
            }
            lft[i] %= P, rht[i] %= P;
            if(rht[i] >= lft[i]){
                v.push_back({lft[i], 1});
                v.push_back({rht[i]+1, -1});
            }
            else{
                v.push_back({0, 1});
                v.push_back({rht[i]+1, -1});
                v.push_back({lft[i], 1});
                v.push_back({P, -1});
            }
        }
        sort(v.begin(), v.end());
        int cnt = 0;
        long long lst = 0;
        for(auto p : v){
            if(cnt){
                ans += p.first - lst;
            }
            cnt += p.second;
            lst = p.first;
        }
    }
    cout << ans << endl;
}
