#include <bits/stdc++.h>

using namespace std;

struct linesegment{
    int x1, y1, x2, y2, idx;
    bool operator < (linesegment l){
        return x1 < l.x1;
    }
};

set<pair<int, int>> st;
int N;
linesegment arr[100005];
linesegment org[100005];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

long long cross(linesegment l1, linesegment l2){
    return
}

bool intersect(linesegment l1, linesegment l2){

}

int solve(int idx){
    int ret = 0;
    for(int i = 1; i<=N; i++){
        if(i != idx){
            ret += intersect(arr[idx], arr[i]);
        }
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    if(fopen("cowjump.in", "r")){
        freopen("cowjump.in", "r", stdin);
        freopen("cowjump.out", "w", stdout);
    }
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> arr[i].x1 >> arr[i].y1 >> arr[i].x2 >> arr[i].y2;
        if(arr[i].x1 > arr[i].x2){
            swap(arr[i].x1, arr[i].x2);
            swap(arr[i].y1, arr[i].y2);
        }
        arr[i].idx = i;
        org[i] = arr[i];
        pq.push({arr[i].x1, i});
    }
    pair<int, int> tst;
    while(pq.size()){
        auto p = pq.top();
        pq.pop();
        int idx = abs(p.second);
        pair<int, int> q = {arr[idx].x1, idx};
        if(p.second > 0){
            st.insert(q);
            auto it = st.lower_bound(q);
            if(it != st.begin() && intersect(arr[(--it)->second], arr[(++it)->second])){
                tst = {(--it)->second, (++it)->second};
            }
            if(it != --st.end() && intersect(arr[(++it)->second], arr[(--it)->second])){
                tst = {(++it)->second, (--it)->second};
            }
        }
        else{
            st.erase(q);
            auto it = st.lower_bound(q);
            if(it != st.end() && it != st.begin() && intersect(arr[(--it)->second], arr[(++it)->second])){
                tst = {(--it)->second, (++it)->second};
            }
        }
    }
    if(tst.first > tst.second){
        swap(tst.first, tst.second);
    }
    if(solve(tst.first) >= 2){
        cout << tst.first << "\n";
    }
    else if(solve(tst.second) >= 2){
        cout << tst.second << "\n";
    }
    else{
        cout << tst.first << "\n";
    }
}
