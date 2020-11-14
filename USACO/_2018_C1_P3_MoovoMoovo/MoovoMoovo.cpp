#include <bits/stdc++.h>

using namespace std;

int N, K;
int grid[200][12];
int par[2000];
int sz[2000];

int get(int n){
    return par[n] = par[n] == n ? n : get(par[n]);
}

int main(){
    cin >> N >> K;
    for(int i = 1; i<=N; i++){
        long long n;
        cin >> n;
        for(int j = 10; j>0; j--){
            grid[i][j] = (int) (n%10);
            n/=10;
        }
    }
    int T = 1005;
    while(T--){
        for(int i = 0; i<10*N; i++){
            par[i] = i;
            sz[i] = 1;
        }
        for(int i = 1; i<=N; i++){
            for(int j = 1; j<=10; j++){
                if(grid[i][j]){
                    if(grid[i-1][j] == grid[i][j]){
                        int p = get((i-2)*10+j-1);
                        par[p] = (i-1)*10+j-1;
                        sz[(i-1)*10+j-1] += sz[p];
                    }
                    if(grid[i][j-1] == grid[i][j] && get((i-1)*10+j-2) != (i-1)*10+j-1){
                        int p = get((i-1)*10+j-2);
                        par[p] = (i-1)*10+j-1;
                        sz[(i-1)*10+j-1] += sz[p];
                    }
                }
            }
        }
        for(int i = 1; i<=N; i++){
            for(int j = 1; j<=10; j++){
                if(grid[i][j]){
                    if(sz[get((i-1)*10+j-1)] >= K){
                        grid[i][j] = 0;
                    }
                }
            }
        }
        for(int j =1; j<=10; j++){
            for(int k = 1; k<=N; k++){
                for(int i = 1; i<N; i++){
                    if(!grid[i+1][j]){
                        grid[i+1][j] = grid[i][j];
                        grid[i][j] = 0;
                    }
                }
            }
        }
    }
    for(int i = 1; i<=N; i++){
        for(int j =1; j<=10; j++){
            cout <<grid[i][j];
        }
        cout << endl;
    }
}
