#include <bits/stdc++.h>

using namespace std;

long long N, M, L, H;
long long MOD;
int seive[200005];
long long ans = 0;

long long mult(long long a, long long b){
    return a*b%MOD;
}

long long add(long long a, long long b){
    return (a+b)%MOD;
}

long long sub(long long a, long long b){
    return ((a-b)%MOD+MOD)%MOD;
}

long long calc(long long x, long long lim){
    if(lim <= 0){
        return 0;
    }
    long long cnt = lim/x;
    long long lst = lim/x*x;
    cout << " " << cnt << " " << lst << endl;
    long long ret = mult(M-lst+1, cnt);
    ret = add(ret, x*(cnt-1)*(x)/2);
    return mult(2LL*(N-x+1), ret);
}

int main(){
    cin >> N >> M >> L >> H >> MOD;
    if(L <= 1){
        ans = add(mult(N+1, M), mult(N, M+1));
    }
    long long l = M, r = M;
    seive[1] = 2;
    for(long long i = 1; i<=N; i++){
        if(!seive[i]){
            for(long long j = i; j<=N; j+=i){
                if(seive[j] != -1){
                    seive[j]++;
                }
            }
            for(long long j = 1LL*i*i; j<=N; j+=i){
                seive[j] = -1;
            }
        }
        if(seive[i] == -1){
            continue;
        }
        seive[i] &= 1;
        seive[i] = -(2*seive[i] - 1);
        while(l && (l-1)*(l-1)+1LL*i*i >= L*L){
            l--;
        }
        while(r && (r-1)*(r-1)+1LL*i*i >= H*H){
            r--;
        }
        cout << l << " " << r << endl;
        ans = add(ans, seive[i]*sub(calc(i, r), calc(i, l-1)));
        cout << ans << " " << i << endl;
        if(ans < 0){
            ans += MOD;
        }
    }
    cout << ans << endl;
}
