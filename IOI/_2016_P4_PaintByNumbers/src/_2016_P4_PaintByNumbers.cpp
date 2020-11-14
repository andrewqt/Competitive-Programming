#include <bits/stdc++.h>
//#include "paint.h"

using namespace std;

long long pre[2][200005];
bool dp[2][2][105][200005];
int dif[2][200005];

string solve_puzzle(string s, vector<int> c){
    int N = s.size(), K = c.size();
    for(int i = 1; i<=N; i++){
        if(s[i-1] == '_'){
            pre[0][i] = 1;
        }
        else if(s[i-1] == 'X'){
            pre[1][i] = 1;
        }
        pre[0][i] += pre[0][i-1];
        pre[1][i] += pre[1][i-1];
    }
    dp[t][0][0][0] = dp[t][1][0][0] = 1;
    for(int k = 0; k<=K; k++){
        for(int i= 0; i<=N; i++){
            for(int b = 0; b<2; b++){
                if(dp[0][b][k][i]){
                    if(s[i] != 'X'){
                        dp[0][0][k][i+1] = 1;
                    }
                    if(k != K && c[k] + i <= N && pre[0][c[k]+i]-pre[0][i] == 0){
                        dp[0][1][k+1][i+c[k]] = 1;
                    }
                }
            }
        }
    }
    reverse(s.begin(), s.end());
    reverse(c.begin(), c.end());
    string ret;
    for(int i = 1; i<=N; i++){
        dif[0][i] += dif[0][i-1];
        dif[1][i] += dif[1][i-1];
    }
    for(int i = 1; i<=N; i++){
        if(dif[0][i] && dif[1][i]){
            ret.push_back('?');
        }
        else if(dif[0][i]){
            ret.push_back('_');
        }
        else{
            ret.push_back('X');
        }
    }
    return ret;
}

int main(){
    //cout << solve_puzzle("..........", {3, 4}) << endl;
    cout << solve_puzzle("........", {3, 4}) << endl;
}

