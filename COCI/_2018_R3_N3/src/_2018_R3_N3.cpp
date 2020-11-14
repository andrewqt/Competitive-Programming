#include <bits/stdc++.h>

using namespace std;

int N, K;
int arr[2000][2000];
int cnt[2000];
int t[2000];
string s;

int main(){
    cin >> N >> K;
    getline(cin, s);
    for(int i =1; i<=N; i++){
        getline(cin, s);
        for(int j = 1; j<=N; j++){
            arr[i][j] = s[j-1] == 'o';
            cnt[j] += arr[i][j];
        }
    }
    int crnt = 0;
    for(int i = 1; i<=N; i++){
        crnt += min(N-cnt[i], cnt[i]);
    }
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            t[j] = cnt[j] - (2*arr[i][j]-1);
        }
        int temp = 0;
        for(int j = 1; j<=N; j++){
            temp += min(N-t[j], t[j]);
        }
        if(crnt > temp){
            for(int j = 1; j<=N; j++){
                cnt[j] = t[j];
            }
            crnt = temp;
        }
    }
    if(crnt <= K){
        cout << "DA" << endl;
    }
    else {
        cout << "NE" << endl;
    }
}
