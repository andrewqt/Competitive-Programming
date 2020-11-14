#include <bits/stdc++.h>

using namespace std;

int N, K, M = 100000;
int kval[100005], arr[1000005];
int lftf[100005], rhtf[100005];

inline long long rec(int l, int r){
    if(l > r){
        return 0;
    }
    long long ret = 0;
    vector<int> lft, rht;
    int mid = l+r>>1;
    int gcd = 0;
    rhtf[gcd]++;
    rht.push_back(0);
    for(int i = mid+1; i<=r; i++){
        gcd = __gcd(gcd, arr[i]);
        if(rht.back() != gcd){
            rht.push_back(gcd);
        }
        rhtf[gcd]++;
    }
    gcd = 0;
    lft.push_back(arr[mid]);
    for(int i= mid; i>=l; i--){
        gcd = __gcd(gcd, arr[i]);
        if(lft.back() != gcd){
            lft.push_back(gcd);
        }
        lftf[gcd]++;
    }
    for(int l : lft){
        for(int r : rht){
            if(kval[__gcd(l, r)] == K){
                ret += 1LL*lftf[l]*rhtf[r];
            }
        }
    }
    for(int n : lft){
        lftf[n] = 0;
    }
    for(int n : rht){
        rhtf[n] = 0;
    }
    return rec(l, mid-1) + rec(mid+1, r) + ret;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for(int i = 2; i<=M; i++){
        if(!kval[i]){
            long long s = i;
            do{
                for(long long j = s; j<=M; j += s){
                    kval[j]++;
                }
                s *= i;
            } while(s <= M);
        }
    }
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
    }
    cout << rec(1, N) << endl;
}
