#include <bits/stdc++.h>

using namespace std;

struct query{
    int typ, l, r, v;
};

int N, Q;
int BIT[200005];
int arr[200005], ans[200005];
query querylist[800005];
int nxt = 0;
vector<query*> qut;

void upd(int p, int v){
    for(int i = p; i<=N; i+=i&-i){
        BIT[i] += v;
    }
}

int sm(int l, int r){
    int sum = 0;
    for(int i = r; i>0; i-=i&-i){
        sum += BIT[i];
    }
    for(int i = l-1; i>0; i-=i&-i){
        sum -= BIT[i];
    }
    return sum;
}

void rec(vector<query*> *qu, int l, int r){
//    cout << l << " " << r << " " << qu.size() << endl;
    if(qu->empty() || l > r){
        return;
    }
    int mid = (l+r)/2;
    vector<query*> lft, rht;
    for(query* q: *qu){
        if(q->typ <= 0){
//            cout << "upd: " << q.typ << " " << q.l << " " << q.v << endl;
            if(q->v <= mid){
                if(!q->typ){
                    upd(q->l, 1);
                }
                else{
//                    cout << "HERE" << endl;
                    upd(q->r, -1);
                }
//                cout << " " << sm(1, N, 1) << endl;
            }
            if(q->v < mid){
                lft.push_back(q);
            }
            if(q->v > mid){
                rht.push_back(q);
            }
        }
        else{
            int s = sm(q->l, q->r);
//            cout << "qu : " << l << " " << r << " " << q.typ << " " << s << endl;
            if(s >= q->v){
                lft.push_back(q);
                ans[q->typ] = mid;
            }
            else{
                q->v -= s;
                rht.push_back(q);
            }
        }
    }
    assert(!sm(1, N));
    rec(&lft, l, mid-1);
    rec(&rht, mid+1, r);
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i<=N; i++){
        scanf("%d", &arr[i]);
        querylist[++nxt] = {0, i, i, arr[i]};
        qut.push_back(&querylist[nxt]);
    }
    scanf("%d", &Q);
    for(int i = 1; i<=Q; i++){
        int cmd;
        scanf("%d", &cmd);
        if(cmd == 1){
            int p, v;
            scanf("%d %d", &p, &v);
            querylist[++nxt] = {-1, p, p, arr[p]};
            qut.push_back(&querylist[nxt]);
            arr[p] = v;
            querylist[++nxt] = {0, p, p, arr[p]};
            qut.push_back(&querylist[nxt]);
        }
        else{
            int l, r, k;
            scanf("%d %d %d", &l, &r, &k);
            querylist[++nxt] = {i, l, r, k};
            qut.push_back(&querylist[nxt]);
        }
    }
    for(int i = 1; i<=N; i++){
        querylist[++nxt] = {-1, i, i, arr[i]};
        qut.push_back(&querylist[nxt]);
    }
    rec(&qut, 1, 1000000000);
    for(int i = 1; i<=Q; i++){
        if(ans[i]){
            printf("%d\n", ans[i]);
        }
    }
}
