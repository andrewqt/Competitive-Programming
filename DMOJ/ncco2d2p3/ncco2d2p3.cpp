#include <bits/stdc++.h>

using namespace std;

string s;
int arr[155][155][155];
int N, M, K;
int dp[155][155][155][3];

int ans = 0;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> K;
    for(int b = 1; b<=M; b++){
        for(int a = 1; a<=N; a++){
            cin >> s;
            for(int k = 0; k<K; k++){
                arr[a][b][k]] = (s[k] == 'N');
            }
        }
    }

}
