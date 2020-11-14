#include <bits/stdc++.h>

using namespace std;

int N, M;
long long c, C;

vector<pair<int, int>> vec;

int main(){
    cin >> N >> M;
    cin >> c >> C;
    int max1 = 0, max2 = 0;
    for(int i = 1; i<=N; i++){
        int n;
        cin >> n;
        max1 = max(max1, n);
        vec.push_back({n, 0});
    }
    for(int i = 1; i<=M; i++){
        int n;
        cin >> n;
        max2 = max(max2, n);
        vec.push_back({n, 1});
    }
    if(max1 != max2){
        cout << "Impossible" << endl;
        return 0;
    }
    vec.push_back({-1, -1});
    sort(vec.begin(), vec.end());
    long long minians = 0, maxians = 0;
    long long rows = 0, cols = 0;
    long long crntbest = 0;
    int cnt = 0;
    for(int i = 1; i<=N+M; i++){
        if(vec[i].second){
            if(crntbest != vec[i].first || cnt == 0){
                minians += vec[i].first;
            }
            else if(crntbest == vec[i].first){
                cnt--;
            }
            maxians += (N-rows)*vec[i].first;
            cols++;
        }
        else{
            if(crntbest != vec[i].first){
                cnt = 0;
            }
            crntbest = vec[i].first;
            minians += crntbest;
            maxians += (M-cols)*vec[i].first;
            rows++;
            cnt++;
        }
    }
    cout << "Minimum: " << c*minians << ", maximum: " << C*maxians << endl;
}
