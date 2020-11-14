#include "secret.h"
#include <bits/stdc++.h>

using namespace std;

int cache[1000][1000];
int arr[1000];
int N;

void rec1(int l, int r){
    if(r-l <= 1){
        return;
    }
    int mid = (l+r)/2;
    for(int i = mid-1; i>=l; i--){
        cache[i][mid] = Secret(arr[i], cache[i+1][mid]);
    }
    for(int j = mid+2; j<=r; j++){
        cache[mid+1][j] = Secret(cache[mid+1][j-1], arr[j]);
    }
    rec1(l, mid);
    rec1(mid+1, r);
}

int rec2(int lq, int rq, int l, int r){
    int mid = (l+r)/2;
    if(rq <= mid){
        return rec2(lq, rq, l, mid);
    }
    else if(lq > mid){
        return rec2(lq, rq, mid+1, r);
    }
    else{
        return Secret(cache[lq][mid], cache[mid+1][rq]);
    }
}

void Init(int n, int A[]){
    N = n;
    for(int i =0; i<N; i++){
        for(int j =0; j<N; j++){
            cache[i][j] = -1;
        }
    }
    for(int i =0; i<N; i++){
        cache[i][i] = arr[i] = A[i];
    }
    rec1(0, N-1);
}

int Query(int x, int y){
    if(cache[x][y] != -1){
        return cache[x][y];
    }
    return rec2(x, y, 0, N-1);
}

int main(){
    int A[] = {1, 3, 2, 5};
    Init(4, A);
    cout << Query(0, 2) << endl;
}
