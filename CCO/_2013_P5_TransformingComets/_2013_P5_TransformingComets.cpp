#include <bits/stdc++.h>

using namespace std;

int TESTCASENUM;
int N;

long long dist(pair<long long, long long> a, pair<long long, long long> b){
    return (b.first-a.first)*(b.first-a.first) + (a.second-b.second)*(a.second-b.second);
}

long long crs(pair<long long, long long> a, pair<long long, long long> b, pair<long long, long long> c){
    return (a.first-b.first)*(c.second-b.second) - (a.second-b.second)*(c.first-b.first);
}

vector<long long> build(int N){
    vector<long long> ret;
    vector<pair<long long, long long>> pts;
    for(int i= 1; i<=N; i++){
        long long x, y;
        cin >> x >> y;
        pts.push_back({x, y});
    }
    long long fct = dist(pts[0], pts[1]);
    for(int i =0; i<N; i++){
        int idx1 = (i+1)%N, idx2 = (i+2)%N;
        long long d = dist(pts[i], pts[idx1]);
        fct = __gcd(fct, d);
        ret.push_back(d*1000000000LL);
        ret.push_back(crs(pts[i], pts[idx1], pts[idx2]));
    }
    for(int i=0; i<ret.size(); i++){
        ret[i] /= fct;
    }
    return ret;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> TESTCASENUM;
    while(TESTCASENUM--){
        cin >> N;
        vector<long long> p1 = build(N), p2 = build(N);
        swap(p1, p2);
        for(int i = 0; i<2*N; i++){
            p1.push_back(p1[i]);
        }
        for(int i =0; i<2*N; i++){
        }
        vector<int> ff;
        ff.push_back(0);
        for(int i = 1, j = 0; i<2*N;){
            if(p2[i] == p2[j]){
                ff.push_back(++j);
                i++;
            }
            else if(j == 0){
                ff.push_back(j);
                i++;
            }
            else{
                j = ff[j-1];
            }
        }
        int ans = 0;
        for(int i= 0, j = 0; i<4*N; ){
            if(p1[i] == p2[j]){
                i++;
                j++;
                if(j == 2*N){
                    ans = (i-2*N)/2+1;
                    break;
                }
            }
            else if(j == 0){
                i++;
            }
            else{
                j = ff[j-1];
            }
        }
        cout << ans << endl;
    }
}
