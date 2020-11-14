#include <bits/stdc++.h>

using namespace std;

int N, K, M;
long long dist1[205][205][7][4], dist2[205][205][7][4];
string scdl[205][205];
int moves[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; //turning right dir++;

int main(){
    cin>> N >> K >> M;
    for(int i = 1; i<=M; i++){
        int R, C;
        cin >> R >> C;
        cin >> scdl[R][C];
    }
    long long ans = 0;
    int cR = 1, cC = 1, D = 0, dir = 0;
    bool b = 1;
    while(K > 0){
        int delta = 0, pdir = dir;
        int lst1 = dist1[cR][cC][D][dir], lst2 = dist2[cR][cC][D][dir];
        if(scdl[cR][cC].size()){
            if(scdl[cR][cC][D] == 'R'){
                dir++;
                dir&=3;
                delta++;
                K--;
            }
            if(scdl[cR][cC][D] == 'L'){
                dir = (dir + 3)&3;
                delta++;
                K--;
            }
        }
        if(cR + moves[dir][0] == 0 || cR + moves[dir][0] == N+1 ||
           cC + moves[dir][1] == 0 || cC + moves[dir][1] == N+1){
            dir = (dir+2)&3;
            delta++;
            K--;
        }
        cR += moves[dir][0];
        cC += moves[dir][1];
        D = (D+1)%7;
        if(dist1[cR][cC][D][dir] && b){
            ans += (lst1 - dist1[cR][cC][D][dir] + 1)
                    *(K/(lst2 + delta - dist2[cR][cC][D][dir]));
            K%=(lst2 + delta - dist2[cR][cC][D][dir]);
            b = 0;
        }
        dist1[cR][cC][D][dir] = lst1+1;
        dist2[cR][cC][D][dir] = lst2+delta;
        ans++;
    }
    cout << ans-1 << endl;
}
