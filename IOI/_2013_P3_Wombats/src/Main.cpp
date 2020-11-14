#include <bits/stdc++.h>

using namespace std;

const int fatnodesz = 10;
int segv[1500][200][200];
int segl[1500], segr[1500];
int N, M;
int V[5000][201], H[5000][201];
int tbl[201][201][2];
int opt[201][201];

void setup(int idx, int c){
    for(int i = 0 ; i<M; i++){
        for(int j = 0; j<M; j++){
            tbl[i][j][c] = segv[idx][i][j];
        }
    }
}

void solve(int n, int idx){
    for(int i = 0; i<M; i++){
        segv[idx][i][i] = INT_MAX;
        for(int j = 0; j<M; j++){
            if(tbl[i][j][1] + tbl[j][i][0] + V[n][j] < segv[idx][i][i]){
                segv[idx][i][i] = tbl[i][j][1] + tbl[j][i][0] + V[n][j];
                opt[i][i] = j;
            }
        }
    }
    for(int i = 1; i<M; i++){
        for(int l = 0; l+i < M; l++){
            int r = i+l;
            segv[idx][l][r] = INT_MAX;
            for(int k = opt[l][r-1]; k<=opt[l+1][r]; k++){
                if(tbl[l][k][1] + tbl[k][r][0] + V[n][k] < segv[idx][l][r]){
                    segv[idx][l][r] = tbl[l][k][1] + tbl[k][r][0] + V[n][k];
                    opt[l][r] = k;
                }
            }
        }
        for(int l = M-1; l-i>=0; l--){
            int r = l-i;
            segv[idx][l][r] = INT_MAX;
            for(int k = opt[l][r+1]; k>=opt[l-1][r]; k--){
                if(tbl[l][k][1] + tbl[k][r][0] + V[n][k] < segv[idx][l][r]){
                    segv[idx][l][r] = tbl[l][k][1] + tbl[k][r][0] + V[n][k];
                    opt[l][r] = k;
                }
            }
        }
    }
}

void pun(int idx,int mid){
    setup(idx<<1, 1);
    setup((idx<<1)|1, 0);
    solve(mid, idx);
}

void puf(int idx, int l, int r){
    for(int i = 0; i<M; i++){
        int d = 0;
        for(int j = i; j<M; j++){
            segv[idx][i][j] = segv[idx][j][i] = tbl[i][j][1] = tbl[j][i][1] = d;
            d += H[l][j];
        }
    }
    for(int n = l+1; n<=r; n++){
        for(int i = 0; i<M; i++){
            int d = 0;
            for(int j = i; j<M; j++){
                tbl[i][j][0] = tbl[j][i][0] = d;
                d += H[n][j];
            }
        }
        solve(n-1, idx);
        setup(idx, 1);
    }
}

void build(int l, int r, int idx){
    segl[idx] = l;
    segr[idx] = r;
    if(r - l + 1 <= fatnodesz){
        puf(idx, l, r);
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, idx<<1);
    build(mid+1, r, (idx<<1)+1);
    pun(idx, mid);
}

void init(int n, int m, int h[5000][200], int v[5000][200]){
    N = n;
    M = m;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            H[i][j] = h[i][j];
            V[i][j] = v[i][j];
        }
    }
    build(0, N-1, 1);
}

void updV(int P, int idx){
    int mid = (segl[idx] + segr[idx])>>1;
    if(segr[idx] - segl[idx] + 1 <= fatnodesz){
        puf(idx, segl[idx], segr[idx]);
        return;
    }
    else if(P == mid){
        pun(idx, mid);
        return;
    }
    if(P < mid){
        updV(P, idx<<1);
    }
    else{
        updV(P, (idx<<1)|1);
    }
    pun(idx, mid);
}

void updH(int P, int idx){
    if(segr[idx] - segl[idx] + 1 <= fatnodesz){
        puf(idx, segl[idx], segr[idx]);
        return;
    }
    int mid = (segl[idx] + segr[idx])>>1;
    if(P <= mid){
        updH(P, idx<<1);
    }
    else{
        updH(P, idx<<1|1);
    }
    pun(idx, mid);
}

void changeV(int P, int Q, int W){
    V[P][Q] = W;
    updV(P, 1);
}

void changeH(int P, int Q, int W){
    H[P][Q] = W;
    updH(P, 1);
}

int escape(int X1, int X2){
    return segv[1][X1][X2];
}
/*
int inH[5000][200];
int inV[5000][200];

int main(){
    int N, M;
    cin >> N >> M;
    for(int i =0; i<N; i++){
        for(int j =0; j<M-1; j++){
            cin >> inH[i][j];
        }
    }
    for(int i =0; i<N-1; i++){
        for(int j = 0; j<M; j++){
            cin >>inV[i][j];
        }
    }
    init(N, M, inH, inV);
    cout << escape(6, 13) << endl;
    cout << escape(12, 13) << endl;
    cout << escape(18, 8) << endl;
}
*/

int main(){

}


/*
const int R = 2, C = 1;
int inH[5000][200];
int inV[5000][200];

int main(){
    inV[0][0] = 1000;
    init(R, C, inH, inV);
    cout << escape(0, 0) << endl;
}
*/
