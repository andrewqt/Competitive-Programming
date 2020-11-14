#include <bits/stdc++.h>

using namespace std;

int N;
string s;
int pre[80];
int dp[80][80];

int main(){
    cin >> N >> s;
    s = s + "X";
    N++;
    for(int i = 1; i<=N; i++){
        if(s[i-1] != 'V' && s[i-1] != 'K'){
            s[i-1] = 'X';
            pre[i]++;
        }
        pre[i] += pre[i-1];
    }
    for(int i = 1; i<=N; i++){
        for(int j = 0; j<=i; j++){
            dp[i][j] = INT_MAX;
        }
    }

}
