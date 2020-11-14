#include <bits/stdc++.h>

using namespace std;

struct Query{
    long long p, ty, by;
    int v;
    bool operator < (Query q) const{
        if(p == q.p){
            return v < q.v;
        }
        return p > q.p;
    }
};

int N, Q;
priority_queue<Query> pq;
int BIT[800000];
vector<long long> yval;
int ans[200005];

int sum(int p){
    int s = 0;
    for(int i = p; i>0; i-=i&-i){
        s += BIT[i];
    }
    return s;
}

void upd(int p, int v){
    for(int i=p; i<=600005; i+=i&-i){
        BIT[i]+=v;
    }
}

long long refl(long long n){
    long long x = 0;
    for(long long i = 0; i<61; i++){
        if((1LL<<i)&n){
            x |= (1LL<<(60-i));
        }
    }
    return x;
}

long long hbit(long long n){
    for(long long i = 60; i>=0; i--){
        if((1LL<<i)&n){
            return i;
        }
    }
    return 0;
}

long long bset(long long n, long long idx){
    for(long long i = idx; i<61; i++){
        n |= (1LL<<i);
    }
    return n;
}

int bs(long long v){
    int l = 0, r = yval.size()-1;
    while(l <= r){
        int m = (l+r)>>1;
        if(yval[m] == v){
            return m+1;
        }
        else if(yval[m] > v){
            r = m-1;
        }
        else{
            l = m+1;
        }
    }
    return 0;
}

int main(){
    cin >> N >> Q;
    for(int i= 1; i<=N; i++){
        long long x, y;
        int v;
        cin >> x >> y >> v;
        long long hx = hbit(x), hy = hbit(y);
        long long ux = bset(x, hx), uy = bset(y, hy);
        x = x^(1LL<<hx)|(1LL<<60);
        y = y^(1LL<<hy)|(1LL<<60);
        x = refl(x);
        y = refl(y);
        ux = refl(ux);
        uy = refl(uy);
//        cout << x << " " << y << " " << ux << " " << uy << " " << hx << " " << hy << endl;
        yval.push_back(uy);
        yval.push_back(y);
        pq.push({x, uy, y, v});
        pq.push({ux, uy, y, -v});
    }
    for(int i= 1; i<=Q; i++){
        long long x, y;
        cin >> x >> y;
        x = refl(x);
        y = refl(y);
        yval.push_back(y);
        pq.push({x, y, i, 0});
    }
    sort(yval.begin(), yval.end());
    while(pq.size()){
        long long crnt = pq.top().p;
//        cout << crnt << endl;
        while(pq.size() && pq.top().p == crnt){
            if(pq.top().v){
//                cout << pq.top().ty << " " << pq.top().by << endl;
                int ub = bs(pq.top().ty), lb = bs(pq.top().by);
//                cout << ub << " " << lb << endl;
                upd(ub+1, -pq.top().v);
                upd(lb, pq.top().v);
            }
            else{
//                cout << "here" << endl;
                int y = bs(pq.top().ty);
                long long idx = pq.top().by;
//                cout << " " << y << " " << idx << endl;
                ans[idx] = sum(y);
            }
            pq.pop();
        }
    }
    for(int i= 1; i<=Q; i++){
        printf("%d\n", ans[i]);
    }
}
