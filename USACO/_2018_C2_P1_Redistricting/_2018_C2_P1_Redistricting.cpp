#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r, mini;
};

int N, K;
int dp[300005];
string s;
Node seg[2405000];
vector<int> mono[600005];
int pre[300005];
int lft[600005], rht[600005];

void build(int l, int r, int idx){
    seg[idx].l = l;
    seg[idx].r = r;
    if(l == r){
        seg[idx].mini = INT_MAX-1;
        return;
    }
    int mid = (l+r)/2;
    build(l, mid, 2*idx);
    build(mid+1,r, 2*idx+1);
    seg[idx].mini = min(seg[2*idx].mini, seg[2*idx+1].mini);
}

void upd(int p, int v, int idx){
    if(seg[idx].l == seg[idx].r){
        seg[idx].mini = v;
        return;
    }
    int mid = (seg[idx].l + seg[idx].r)/2;
    if(p <= mid){
        upd(p, v, 2*idx);
    }
    else{
        upd(p, v, 2*idx+1);
    }
    seg[idx].mini = min(seg[2*idx].mini, seg[2*idx+1].mini);
}

int query(int l, int r, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        return seg[idx].mini;
    }
    int mid = (seg[idx].l + seg[idx].r)/2;
    if(r <= mid){
        return query(l, r, 2*idx);
    }
    else if(l > mid){
        return query(l, r, 2*idx+1);
    }
    else{
        return min(query(l, mid, 2*idx), query(mid+1, r, 2*idx+1));
    }
}

int main(){
	freopen("redistricting.in", "r", stdin);
	freopen("redistricting.out", "w", stdout);
    cin >> N >> K;
    cin >> s;
    for(int i =1; i<=N; i++){
        pre[i] = (s[i-1] == 'H' ? 1 : -1) + pre[i-1];
    }
    build(0, 600002, 1);
    upd(300000, 0, 1);
    mono[300000].push_back(0);
    fill(rht, rht+600005, -1);
    rht[300000] = 0;
    for(int l = -K+1, r = 1; r<=N; r++, l++){
        int i = pre[r] + 300000;
        dp[r] = min(query(0, i-1, 1), query(i, 600001, 1) + 1);
        while(rht[i]-lft[i] >= 0 && dp[mono[i][rht[i]]] >= dp[r]){
            rht[i]--;
        }
        if(mono[i].size() <= rht[i]+1){
            mono[i].push_back(r);
            rht[i]++;
        }
        else{
            mono[i][++rht[i]] = r;
        }
        upd(i, dp[mono[i][lft[i]]], 1);
        if(l >= 0){
            i = pre[l] + 300000;
            while(rht[i]-lft[i] >= 0 && mono[i][lft[i]] <= l){
                lft[i]++;
            }
            if(rht[i]-lft[i] < 0){
                upd(i, INT_MAX-1, 1);
            }
            else{
                upd(i, dp[mono[i][lft[i]]], 1);
            }
        }
    }
    cout << dp[N] << endl;
}
