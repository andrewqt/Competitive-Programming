#include <bits/stdc++.h>

using namespace std;

int N, Q;
long long BIT[300000], ans[300000];
pair<int, int> srt[300000];
pair<int, int> qu[300000];
int l[300000], r[300000];

void upd(int n, long long v){
    for(int i = n; i<300000; i+=i&-i){
        BIT[i] += v;
    }
}

long long sum(int n){
    long long sum = 0;
    for(int i = n; i>0; i-=i&-i){
        sum += BIT[i];
    }
    return sum;
}

int main(){
    scanf("%d %d", &N, &Q);
    for(int i =1; i<=N; i++){
        int n;
        scanf("%d", &n);
        upd(i, n);
        srt[i] = {n, i};
    }
    for(int i =1; i<=Q; i++){
        int k;
        scanf("%d %d %d", &l[i], &r[i], &k);
        qu[i] = {k, i};
    }
    sort(srt+1, srt+1+N);
    sort(qu+1, qu+1+Q);
    int idx = 1;
    for(int i =1; i<=Q; i++){
        int k = qu[i].first;
        while(idx <= N && srt[idx].first < k){
            upd(srt[idx].second, -srt[idx].first*2);
            idx++;
        }
        ans[qu[i].second] = sum(r[qu[i].second]) - sum(l[qu[i].second] - 1);
    }
    for(int i = 1; i<=Q; i++){
        printf("%lld\n", ans[i]);
    }
}
