#include <bits/stdc++.h>

using namespace std;

long long dp[100005];
long long pos[100005], srt[100005];
int perm[3];

int main(){
    int N;
    cin >> N;
    for(int i= 1; i<=N; i++){
        cin >> pos[i] >> srt[i];
    }
    sort(pos+1, pos+1+N);
    sort(srt+1, srt+1+N);
    dp[1] = pos[1] == srt[1] ? LLONG_MAX/2 : abs(pos[1]-srt[1]);
    dp[2] = LLONG_MAX/2;
    if(N >= 2){
        if(pos[2] != srt[2]){
            dp[2] = dp[1] + abs(pos[2]-srt[2]);
        }
        if(pos[2] != srt[1] && pos[1] != srt[2]){
            dp[2] = min(abs(pos[1]-srt[2]) + abs(pos[2]-srt[1]), dp[2]);
        }
    }
    perm[0] = 0;
    perm[1] = 1;
    perm[2] = 2;
    for(int i = 3; i<=N; i++){
        perm[0] = 0;
        perm[1] = 1;
        perm[2] = 2;
        dp[i] = LLONG_MAX/2;
        do{
            bool b = true;
            for(int j = 0; j<3; j++){
                if(srt[i-j] == pos[i-perm[j]]){
                    b = false;
                }
            }
            if(b){
                long long tot = 0;
                for(int j = 0; j<3; j++){
                    tot += abs(srt[i-j] - pos[i-perm[j]]);
                }
                dp[i] = min(tot + dp[i-3], dp[i]);
            }
        }
        while(next_permutation(perm, perm+3));
        perm[0] = 0;
        perm[1] = 1;
        do{
            bool b = true;
            for(int j = 0; j<2; j++){
                if(srt[i-j] == pos[i-perm[j]]){
                    b = false;
                }
            }
            if(b){
                long long tot = 0;
                for(int j = 0; j<2; j++){
                    tot += abs(srt[i-j] - pos[i-perm[j]]);
                }
                dp[i] = min(tot + dp[i-2], dp[i]);
            }
        }
        while(next_permutation(perm, perm+2));
        perm[0] = 0;
        do{
            bool b = true;
            for(int j = 0; j<1; j++){
                if(srt[i-j] == pos[i-perm[j]]){
                    b = false;
                }
            }
            if(b){
                long long tot = 0;
                for(int j = 0; j<1; j++){
                    tot += abs(srt[i-j] - pos[i-perm[j]]);
                }
                dp[i] = min(tot + dp[i-1], dp[i]);
            }
        }
        while(next_permutation(perm, perm+1));
        assert(dp[i] != LLONG_MAX/2);
    }
    cout << dp[N] << endl;
}
