#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r, maxi, lzy, re;
};

Node seg[400005];
int N, Q, R;
int id[100005], hvy[100005], dep[100005], top[100005], par[100005], sz[100005], tim = 0;
vector<int> graph[100005];
int qu[20];

inline void build(int l, int r, int idx){
    seg[idx].l = l;
    seg[idx].r = r;
    seg[idx].re = 1;
    if(l == r){
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
}

inline void pd(int idx){
    seg[2*idx].maxi += seg[idx].lzy;
    seg[2*idx+1].maxi += seg[idx].lzy;
    seg[2*idx].lzy += seg[idx].lzy;
    seg[2*idx+1].lzy += seg[idx].lzy;
    seg[idx].lzy = 0;
}

inline void res(int idx){
    seg[2*idx].maxi = 0;
    seg[2*idx+1].maxi = 0;
    seg[2*idx].re = seg[2*idx].lzy = 0;
    seg[2*idx+1].re = seg[2*idx+1].lzy = 0;
    seg[idx].re = 1;
}

inline void upd(int l, int r, int v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        seg[idx].maxi += v;
        seg[idx].lzy += v;
        return;
    }
    if(!seg[idx].re){
        res(idx);
    }
    if(seg[idx].lzy){
        pd(idx);
    }
    int mid = (seg[idx].l + seg[idx].r)>> 1;
    if(r <= mid){
        upd(l, r, v, 2*idx);
    }
    else if(l > mid){
        upd(l, r, v, 2*idx+1);
    }
    else{
        upd(l, mid, v, 2*idx);
        upd(mid+1, r, v, 2*idx+1);
    }
    seg[idx].maxi = max(seg[2*idx].maxi, seg[2*idx+1].maxi);
}

inline void dfs(int n){
    sz[n]++;
    for(int e : graph[n]){
        if(e != par[n]){
            par[e] = n;
            dep[e] = dep[n] + 1;
            dfs(e);
            sz[n] += sz[e];
            hvy[n] = sz[e] > sz[hvy[n]] ? e : hvy[n];
        }
    }
}

inline void hld(int n, int a){
    top[n] = a;
    id[n] = ++tim;
    if(hvy[n]){
        hld(hvy[n], a);
    }
    for(int e : graph[n]){
        if(e != par[n] && e != hvy[n]){
            hld(e, e);
        }
    }
}

inline void pthupd(int u, int v, int x){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]){
            swap(u, v);
        }
        upd(id[top[u]], id[u], x, 1);
        u = par[top[u]];
    }
    if(dep[u] < dep[v]){
        swap(u, v);
    }
    upd(id[v], id[u], x, 1);
}

int main(){
    scanf("%d %d", &N, &Q);
    for(int i= 1; i<N; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(1);
    build(1, N, 1);
    hld(1, 1);
    while(Q--){
        int v, k;
        scanf("%d %d", &v, &k);
        for(int i =0; i<k; i++){
            scanf("%d", &qu[i]);
        }
        for(int i = 1; i<k; i++){
            if(i-1){
                upd(id[qu[i-1]], id[qu[i-1]], -1, 1);
            }
            pthupd(qu[i-1], qu[i], 1);
        }
        if(v == 0){
            if(seg[1].maxi > 1){
                printf("%d\n", 0);
            }
            else{
                printf("%d\n", 1);
            }
        }
        else if(v == 1){
            bool chk = 0;
            if(seg[1].maxi <= 2){
                for(int j = 1; j<k; j++){
                    pthupd(qu[j-1], qu[j], -1);
                    if(seg[1].maxi <= 1){
                        upd(id[qu[j-1]], id[qu[j-1]], 1, 1);
                        upd(id[qu[j]], id[qu[j]], 1, 1);
                        if(seg[1].maxi <= 1){
                            chk = 1;
                            break;
                        }
                        upd(id[qu[j-1]], id[qu[j-1]], -1, 1);
                        upd(id[qu[j]], id[qu[j]], -1, 1);
                    }
                    pthupd(qu[j-1], qu[j], 1);
                }
            }
            if(!chk){
                printf("%d\n", 0);
            }
            else{
                printf("%d\n", 1);
            }
        }
        else{
            bool chk = 0;
            if(seg[1].maxi <= 3){
                for(int i = 1; i<k && !chk; i++){
                    pthupd(qu[i-1], qu[i], -1);
                    upd(id[qu[i-1]], id[qu[i-1]], 1, 1);
                    upd(id[qu[i]], id[qu[i]], 1, 1);
                    if(seg[1].maxi <= 1){
                        chk = 1;
                        break;
                    }
                    for(int j = k-1; j>i; j--){
                        pthupd(qu[j-1], qu[j], -1);
                        if(seg[1].maxi <= 1){
                            upd(id[qu[j-1]], id[qu[j-1]], 1, 1);
                            upd(id[qu[j]], id[qu[j]], 1, 1);
                            if(seg[1].maxi <= 1){
                                chk = 1;
                                break;
                            }
                            upd(id[qu[j-1]], id[qu[j-1]], -1, 1);
                            upd(id[qu[j]], id[qu[j]], -1, 1);
                        }
                        pthupd(qu[j-1], qu[j], 1);
                    }
                    pthupd(qu[i-1], qu[i], 1);
                    upd(id[qu[i-1]], id[qu[i-1]], -1, 1);
                    upd(id[qu[i]], id[qu[i]], -1, 1);
                }
            }
            if(!chk){
                printf("%d\n", 0);
            }
            else{
                printf("%d\n", 1);
            }
        }
        seg[1].maxi = seg[1].lzy = seg[1].re = 0;
    }
}
