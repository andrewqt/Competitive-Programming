#include <bits/stdc++.h>

using namespace std;

int ans[525][525];
int pre[525][262145];
int N, Q;
const int B = 500, M = 262144, MM = 262143;
int arr[262145];
int st[262145];
int act[262145];
int typ[262145];
int lst[262145];
int C, i, m, b, k, lbk, rbk, j, T = -1;

void fastscan(int &number){
    number = 0;
    for (register int c = getchar(); (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
}

int solve(int l, int r, const int lb = 0, const int rb = 0){
    int ret = 0;
    for(j = l; j<r;){
        if(typ[arr[j]] > 1){
            if(lst[arr[j]] != C){
                act[arr[j]] = pre[rb][arr[j]] - pre[lb][arr[j]];
                lst[arr[j]] = C;
            }
            act[arr[j]]++;
            ret += (act[arr[j]]<<1)-1;
        }
        else{
            ret++;
        }
        if(st[++j] != -1){
            break;
        }
    }
    return ret;
}

int main(){
    fastscan(N);
    fastscan(Q);
    const int S = N/B;
    for(i = 0; i<N; i++){
        fastscan(arr[i]);
        st[i] = (i%B == 0 ? ++T : -1);
        pre[T][arr[i]]++;
        typ[arr[i]]++;
    }
    st[N] = -1;
    for(m = 0; m<M; m++){
        if(typ[m] < 2){
            continue;
        }
        for(b = 1; b<=S; b++){
            pre[b][m] += pre[b-1][m];
        }
    }
    for(k = 0; k<N; k+=B){
        C++;
        for(i = k+B; i<=N; i+=B){
            ans[st[k]][st[i]] = (solve(i-B, i) + ans[st[k]][st[i]-1])&MM;
        }
    }
    int lst = 0;
    while(Q--){
        int l, r;
        fastscan(l);
        fastscan(r);
        l ^= lst, r ^= lst;
        C++;
        rbk = (r/B);
        if(r-l+1 <= B){
            lst = solve(l, r+1);
            if(l < rbk*B){
                lst += solve(rbk*B, r+1);
            }
        }
        else{
            lbk = (l/B);
            lst = ans[lbk+1][rbk];
            lst += solve(l, r+1, lbk, rbk-1);
            lst += solve(rbk*B, r+1, lbk, rbk-1);
        	lst &= MM;
		}
        printf("%d\n", lst);
    }
}