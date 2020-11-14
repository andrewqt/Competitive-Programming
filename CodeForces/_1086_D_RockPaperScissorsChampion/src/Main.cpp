#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r, maxi, mini, cnt;
};

Node seg[800005][3];
int arr[200005];

void pul(int idx){
    for(int i = 0; i<3; i++){
        seg[idx][i].maxi = seg[idx][i].mini = (arr[seg[idx][i].l]+i)%3;
        if(seg[idx][i].maxi == 1){
            seg[idx][i].cnt = 1;
        }
        else{
            seg[idx][i].cnt = 0;
        }
    }
}

void pun(int idx){
    for(int i = 0; i<3; i++){
        seg[idx][i].maxi = max(seg[2*idx][i].maxi, seg[2*idx+1][i].maxi);
        seg[idx][i].mini = min(seg[2*idx][i].mini, seg[2*idx+1][i].mini);
        seg[idx][i].cnt = seg[2*idx+1][i].cnt + seg[2*idx][i].cnt;
    }
}

void build(int l, int r, int idx){
    seg[idx][0].l = seg[idx][1].l = seg[idx][2].l = l;
    seg[idx][0].r = seg[idx][1].r = seg[idx][2].r = r;
    if(l == r){
        pul(idx);
        return;
    }
    int mid = (l + r)/2;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
    pun(idx);
}

void upd(int p, int idx){
    if(seg[idx][0].l == seg[idx][0].r){
        pul(idx);
        return;
    }
    if(p <= (seg[idx][0].l + seg[idx][0].r)/2){
        upd(p, 2*idx);
    }
    else{
        upd(p, 2*idx+1);
    }
    pun(idx);
}

int upbnd(int idx, int tre){
    if(seg[idx][tre].l == seg[idx][tre].r){
        return seg[idx][tre].l;
    }
    if(seg[2*idx+1][tre].maxi == 2){
        return upbnd(2*idx+1, tre);
    }
    else{
        return upbnd(2*idx, tre);
    }
}

int lwbnd(int idx, int tre){
    if(seg[idx][tre].l == seg[idx][tre].r){
        return seg[idx][tre].l;
    }
    if(seg[2*idx][tre].maxi == 2){
        return upbnd(2*idx, tre);
    }
    else{
        return upbnd(2*idx+1, tre);
    }
}

int qumin(int l, int r, int idx, int tre){
    if(seg[idx][tre].l == l && seg[idx][tre].r == r){
        return seg[idx][tre].mini;
    }
    int mid = (seg[idx][tre].l + seg[idx][tre].r)/2;
    if(r <= mid){
        return qumin(l, r, 2*idx, tre);
    }
    else if(l > mid){
        return qumin(l, r, 2*idx+1, tre);
    }
    else{
        return min(qumin(l, mid, 2*idx, tre), qumin(mid+1, r, 2*idx+1, tre));
    }
}

int getcount(int l, int r, int idx, int tre){
    if(seg[idx][tre].l == l && seg[idx][tre].r == r){
        return seg[idx][tre].cnt;
    }
    int mid = (seg[idx][tre].l + seg[idx][tre].r)/2;
    if(r <= mid){
        return getcount(l, r, 2*idx, tre);
    }
    else if(l > mid){
        return getcount(l, r, 2*idx+1, tre);
    }
    else{
        return getcount(l, mid, 2*idx, tre) + getcount(mid+1, r, 2*idx+1, tre);
    }
}

int N, Q;
string s, t;
//R --> 1, P --> 2, S --> 0

void ans(){
    int cnt = 0;
    for(int i = 0; i<3; i++){
        if(seg[1][i].maxi <= 1){
            if(seg[1][i].mini == 1){
                cnt += seg[1][i].cnt;
            }
            continue;
        }
        int lb = lwbnd(1, i);
        int ub = upbnd(1, i);
        if(lb != 1 && qumin(1, lb-1, 1, i)){
            lb = 1;
        }
        if(ub != N && qumin(ub+1, N, 1, i)){
            ub = N;
        }
        cnt += getcount(lb, ub, 1, i);
        cout << lb << " " << ub << endl;
    }
    cout << cnt << endl;
}

int main(){
    cin >> N >> Q;
    getline(cin, s);
    getline(cin, s);
    for(int i = 1; i<=N; i++){
        char c = s[i-1];
        cout << c << endl;
        if(c == 'R'){
            arr[i] = 1;
        }
        else if(c == 'P'){
            arr[i] = 0;
        }
        else{
            arr[i] = 2;
        }
    }
    build(1, N, 1);
    ans();
    while(Q--){
        int n;
        cin >> n >> t;
        char c = t[0];
        if(c == 'R'){
            arr[n] = 1;
        }
        else if(c == 'P'){
            arr[n] = 0;
        }
        else{
            arr[n] = 2;
        }
        upd(n, 1);
        int cnt = 0;
        ans();
    }
}
