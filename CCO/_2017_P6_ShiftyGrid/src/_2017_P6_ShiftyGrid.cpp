#include <bits/stdc++.h>

using namespace std;

struct query{
    int typ, idx, shift;
};

int N, M, K;
int Rpos[100000], Cpos[100000];
int grid[105][105];
int temp[105];
bool top = 0;
vector<query> ans;

void rightshift(int r, int k){
    ans.push_back({1, r, k});
    for(int i = 0; i<M; i++){
        temp[(i+k)%M] = grid[r][i];
    }
    for(int i = 0; i<M; i++){
        grid[r][i] = temp[i];
        Cpos[grid[r][i]] = i;
    }
    /*
    for(int i =0; i<N; i++){
        for(int j= 0; j<M; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */
}

void downshift(int c, int k){
    ans.push_back({2, c, k});
    for(int i = 0; i<N; i++){
        temp[(i+k)%N] = grid[i][c];
    }
    for(int i = 0; i<N; i++){
        grid[i][c] = temp[i];
        Rpos[grid[i][c]] = i;
    }
    /*
    for(int i =0; i<N; i++){
        for(int j= 0; j<M; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */
}

void cyclesolve(int p){
    int crnt = grid[N-1][p];
    rightshift(N-1, M-1-p%M);
    if(top){
        downshift(M-1, N-1);
    }
    else{
        downshift(M-1, 1);
    }
    top ^= 1;
//    cout << top << endl;
    while(crnt >= (N-1)*M){
//        cout << crnt << " " << p << " " << (crnt+M-p)%M << endl;
        rightshift(N-1, M-(crnt+M-p)%M);
        p = crnt;
        if(top){
            downshift(M-1, N-1);
            crnt = grid[N-2][M-1];
        }
        else{
            downshift(M-1, 1);
            crnt = grid[0][M-1];
        }
        top^=1;
//        cout << top << endl;
    }
    rightshift(N-1, M-(M-1-p%M)%M);
}

int main(){
    cin >> N >> M;
    K = N*M;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            cin >> grid[i][j];
            Rpos[grid[i][j]] = i;
            Cpos[grid[i][j]] = j;
        }
    }
    for(int i = 0; i<N-1; i++){
        for(int j= 0; j<M-1; j++){
            int n = i*M+j;
//            cout << " " << n << endl;
            int r = Rpos[n], c = Cpos[n];
            if(Rpos[n] == N-1){
                rightshift(r, M-1-c);
                downshift(M-1, 1);
                rightshift(r, c+1);
                downshift(M-1, N-1);
            }
            else{
                rightshift(r, M-1-c);
                downshift(M-1, N-1-r);
                rightshift(r, c+1);
            }
            rightshift(N-1, M-1);
        }
        for(int j = 0; j<M-1; j++){
            downshift(j, N-1);
        }
    }
//    cout << "here" << endl;
    for(int i = 0; i<N-1; i++){
        int n = i*M+M-1;
//        cout << " " << n << endl;
        int r = Rpos[n], c = Cpos[n];
        if(r == N-1){
            rightshift(r, M-1-c);
        }
        else{
            downshift(M-1, N-1-r);
            rightshift(N-1, 1);
            downshift(M-1, r+1);
            rightshift(N-1, M-1);
        }
        downshift(M-1, N-1);
    }
    rightshift(N-1, M-Cpos[(N-1)*M]);
//    cout << "here" << endl;
    for(int i= 0; i<M; i++){
        if(grid[N-1][i]%M != i){
//            cout << " " << grid[N-1][i] << endl;
            cyclesolve(i);
        }
    }
    if(top){
        for(int i = 0; i<N-2; i++){
            downshift(M-1, N-i);
            if(top){
                rightshift(0, M-1);
                downshift(M-1, N-1);
                rightshift(0, 1);
                downshift(M-1, 1);
                rightshift(0, M-1);
                top = 0;
            }
            else{
                rightshift(0, 1);
                downshift(M-1, N-1);
                rightshift(0, M-1);
                downshift(M-1, 1);
                rightshift(0, 1);
                top = 1;
            }
            downshift(M-1, i);
        }
    }
    cout << ans.size() << endl;
    for(auto a : ans){
        cout << a.typ << " " << (a.idx+1) << " " << a.shift << "\n";
    }
    /*
    for(int i =0; i<N; i++){
        for(int j =0; j<M; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    */
}
