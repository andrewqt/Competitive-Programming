#include <bits/stdc++.h>

using namespace std;

//priorityqueue

struct Node{
    int l, r;
    priority_queue<int, vector<int>, greater<int>> f;
    priority_queue<int> fcan;
    int can, p;
};

int N, M;
bool ans[100005];
bool exist1[100005], exist2[100005];
pair<int, int> arr[100005];
int xo[100005], xx[100005], yo[100005], yx[100005];
vector<int> cmp;
Node seg[1000005];

int getidx(int n){
    return lower_bound(cmp.begin(), cmp.end(), n) - cmp.begin() + 1;
}

inline void build(int l, int r, int idx){
    seg[idx].can = N+1;
    seg[idx].l = l, seg[idx].r = r;
    if(l == r){
        return;
    }
    int mid = l+r>>1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
}

inline void pu(int idx){
    seg[idx].p = 0;
    seg[idx].can = N+1;
    if(seg[idx].l != seg[idx].r){
        seg[idx].p = max(seg[2*idx].p, seg[2*idx+1].p);
        seg[idx].can = min(seg[2*idx].can, seg[2*idx+1].can);
    }
    seg[idx].p = max(seg[idx].f.size() ? seg[idx].f.top() : 0, seg[idx].p);
    seg[idx].can = min(seg[idx].fcan.size() ? seg[idx].fcan.top() : N+1, seg[idx].can);
}

inline void remc(int l, int r, int v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        while(seg[idx].fcan.size() && !exist1[seg[idx].fcan.top()]){
            seg[idx].fcan.pop();
        }
        pu(idx);
        return;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        remc(l, r, v, 2*idx);
    }
    else if(l > mid){
        remc(l, r, v, 2*idx+1);
    }
    else{
        remc(l, mid, v, 2*idx);
        remc(mid+1, r, v, 2*idx+1);
    }
    pu(idx);
}

inline void add(int l, int r, int v, int idx){
    //cout << l << " " << r << " " << v << endl;
    if(seg[idx].f.size() && seg[idx].f.top() > v){
        exist1[v] = 0;
        ans[v] = 1;
    }
    while(seg[idx].fcan.size() && seg[idx].fcan.top() < v){
        int n = seg[idx].fcan.top();
        exist1[n] = 0;
        remc(yo[n], yx[n], n, 1);
        ans[n] = 1;
    }
    if(seg[idx].l == l && seg[idx].r == r){
        if(exist1[v]){
            seg[idx].f.push(v);
        }
        seg[idx].fcan.push(v);
        //cout << *seg[idx].can.begin() << endl;
        while(seg[idx].can < v){
            ans[seg[idx].can] = 1;
            exist1[seg[idx].can] = 0;
            remc(yo[seg[idx].can], yx[seg[idx].can], seg[idx].can, 1);
        }
        if(seg[idx].p > v){
            ans[v] = 1;
            exist1[v] = 0;
        }
        pu(idx);
        return;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        add(l, r, v, 2*idx);
    }
    else if(l > mid){
        add(l, r, v, 2*idx+1);
    }
    else{
        add(l, mid, v, 2*idx);
        add(mid+1, r, v, 2*idx+1);
    }
    pu(idx);
}

void rem(int l, int r, int v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        while(seg[idx].f.size() && !exist2[seg[idx].f.top()]){
            seg[idx].f.pop();
        }
        while(seg[idx].fcan.size() && !exist1[seg[idx].fcan.top()]){
            seg[idx].fcan.pop();
        }
        pu(idx);
        return;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        rem(l, r, v, 2*idx);
    }
    else if(l > mid){
        rem(l, r, v, 2*idx+1);
    }
    else{
        rem(l, mid, v, 2*idx);
        rem(mid+1, r, v, 2*idx+1);
    }
    pu(idx);
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> xo[i] >> yo[i] >> xx[i] >> yx[i];
        xx[i] += xo[i];
        yx[i] += yo[i];
        yx[i]--;
        cmp.push_back(yo[i]);
        cmp.push_back(yx[i]);
    }
    sort(cmp.begin(), cmp.end());
    cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
    M = cmp.size();
    build(1, M, 1);
    for(int i = 1; i<=N; i++){
        yo[i] = getidx(yo[i]), yx[i] = getidx(yx[i]);
        arr[i].first = xo[i];
        arr[i+N].first = xx[i];
        arr[i].second = i;
        arr[i+N].second = -i;
    }
    sort(arr+1, arr+1+2*N);
    for(int n = 1; n<=2*N; n++){
        //cout << arr[n].second << endl;
        if(arr[n].second > 0){
            exist1[arr[n].second] = exist2[arr[n].second] = 1;
            add(yo[arr[n].second], yx[arr[n].second], arr[n].second, 1);
            if(!exist1[arr[n].second]){
                remc(yo[arr[n].second], yx[arr[n].second], arr[n].second, 1);
            }
        }
        else{
            exist1[-arr[n].second] = exist2[-arr[n].second] = 0;
            rem(yo[-arr[n].second], yx[-arr[n].second], -arr[n].second, 1);
        }
    }
    for(int i = 1; i<=N; i++){
        if(ans[i]){
            cout << "NE\n";
        }
        else{
            cout << "DA\n";
        }
    }
}

/*
4
1 1 20 20
1 1 1 1
1 2 1 1
1 2 2 2

3
1 1 2 2
1 4 2 2
3 2 5 5
*/
