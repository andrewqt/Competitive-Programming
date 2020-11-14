#include <bits/stdc++.h>

using namespace std;

int N;
bool dp[500000];
int arr[1000];

int main(){
    scanf("%d", &N);
    dp[0] = 1;
    int maxi = 0;
    int tot = 0;
    for(int i = 1; i<=N; i++){
        scanf("%d", &arr[i]);
        tot += arr[i];
    }
    for(int i =1 ; i<=N; i++){
        for(int j = tot/2; j>=arr[i]; j--){
            dp[j] |= dp[j-arr[i]];
            if(dp[j]) {
                    maxi = max(j, maxi);
            }
        }
    }
    cout << (tot-maxi)-maxi << endl;
}
