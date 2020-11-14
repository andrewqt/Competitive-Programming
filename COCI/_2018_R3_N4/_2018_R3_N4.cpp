#include <bits/stdc++.h>

using namespace std;

priority_queue<long long> pq;
priority_queue<pair<long long, long long>> qu;
vector<long long> vec;
long long x[105], y[105], r[105];
bool here[105];
long long N, M;

int main(){
    cin >> N >> M;
    int Q;
    cin >> Q;
    for(int i =Q; i>=1; i--){
        cin >> x[i] >> y[i] >> r[i];
    }
    Q++;
    x[Q] = y[Q] = 1;
    r[Q] = 500000000;
    long long ans = 0;
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=Q; j++){
            if((x[j]-i)*(x[j]-i) > r[j]*r[j]){
                continue;
            }
            long long t = sqrt(r[j]*r[j]-(x[j]-i)*(x[j]-i));
            vec.push_back(max(y[j]-t, 1LL));
            vec.push_back(min(t+y[j]+1, M+1));
            qu.push({-(max(y[j]-t, 1LL)), j});
            qu.push({-(min(t+y[j]+1, M+1)), -j});
//            cout << i << " " << j << " " << t << " " << max(y[j]-t, 1LL) << " " << min(t+y[j]+1, M+1) << endl;
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        for(int j = 0; j<vec.end()-vec.begin(); j++){
//            cout << vec[j] << endl;
            if(!pq.empty()){
//                cout << " " << -pq.top() << " " << vec[j] << endl;
                ans += (vec[j] - vec[j-1])*-pq.top();
//                cout << ans << endl;
            }
            while(!qu.empty() && -qu.top().first <= vec[j]){
                here[abs(qu.top().second)] = qu.top().second > 0;
                if(here[abs(qu.top().second)]){
                    pq.push(-qu.top().second);
                }
                qu.pop();
            }
            while(!pq.empty() && !here[-pq.top()]){
                pq.pop();
            }
        }
//        cout << ans - i*M << endl;
        vec.clear();
    }
    cout << ans - N*M << endl;
}
