#include <bits/stdc++.h>

using namespace std;

int N;
bool tkn[200005];
int BIT[200005];
queue<int> pos[100005], neg[100005];

void upd(int n, int v){
    for(int i = n; i<=N; i+=i&-i){
        BIT[i] += v;
    }
}

int query(int n){
    int s = 0;
    for(int i = n; i; i-=i&-i){
        s += BIT[i];
    }
    return s;
}

long long count_swaps(vector<int> S){
    N = S.size();
    for(int i = 1; i<=N; i++){
        if(S[i-1] > 0){
            pos[S[i-1]].push(i);
        }
        else{
            neg[-S[i-1]].push(i);
        }
        upd(i, 1);
    }
    long long ans = 0;
    for(int i = 1; i<=N; i++){
        if(tkn[i]){
            continue;
        }
        int v = S[i-1];
        if(v > 0){
            ans++;
        }
        int idx1 = pos[abs(v)].front(), idx2 = neg[abs(v)].front();
        pos[abs(v)].pop(), neg[abs(v)].pop();
        if(idx2 < idx1){
            swap(idx2, idx1);

        }
        upd(idx1, -1), upd(idx2, -1);
        tkn[idx1] = tkn[idx2] = 1;
        ans += query(idx2);
    }
    return ans;
}

int main(){
    return 0;
}
