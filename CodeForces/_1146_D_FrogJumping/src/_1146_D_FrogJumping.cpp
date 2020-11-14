#include <bits/stdc++.h>

using namespace std;

long long N, A, B;
long long fst[100005];

int main(){
    cin >> N >> A >> B;
    long long ans = 1, crnt = 1, cnt = 1;
    long long nxt = (-B%A+A)%A, top = nxt + B, r = 0;
    fill(fst+1, fst+A, -1);
    long long n = 0;
    while(n <= N && cnt < N){
        if(top <= N){
            long long num = (top-n)/A;
            ans += num*(crnt+cnt)
        }
    }
}
