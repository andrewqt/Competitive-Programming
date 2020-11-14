#include <bits/stdc++.h>

using namespace std;

int N;
int tbl[10][10][1005][1005];

void init(vector<vector<int>> arr){
    N = arr.size();
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            tbl[0][0][i][j] = arr[i][j];
        }
    }
    for(int a = 0; a<10; a++){
        for(int b = 0; b<10; b++){
            if(!a && !b){
                continue;
            }
            for(int i = 0; i<=N-(1<<a); i++){
                for(int j = 0; j<=N-(1<<b); j++){
                    if(!a){
                        tbl[a][b][i][j] = min(tbl[a][b-1][i][j], tbl[a][b-1][i][j+(1<<(b-1))]);
                    }
                    else{
                        tbl[a][b][i][j] = min(tbl[a-1][b][i][j], tbl[a-1][b][i+(1<<(a-1))][j]);
                    }
                }
            }
        }
    }
}

int query(int x1, int x2, int y1, int y2){
    int dx = x2-x1+1, dy = y2-y1+1;
    int a = 31 - __builtin_clz(dx);
    int b = 31 - __builtin_clz(dy);
    int ret = tbl[a][b][x1][y1];
    x2 -= (1<<a), x2++;
    y2 -= (1<<b), y2++;
    ret = min(ret, tbl[a][b][x1][y2]);
    ret = min(ret, tbl[a][b][x2][y1]);
    ret = min(ret, tbl[a][b][x2][y2]);
    return ret;
}

int main(){

}
