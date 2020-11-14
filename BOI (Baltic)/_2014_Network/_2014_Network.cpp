#include <bits/stdc++.h>
#include "network.h"

using namespace std;

vector<int> dist[1005];

void findRoute(int N, int A, int B){
    int D = ping(A, B)+1;
    for(int n = 1; n<=N; n++){
        if(n != A && n != B){
            int k = ping(n, B);
            dist[k+1].push_back(n);
        }
    }
    int crnt = A;
    for(int d = D-1; d; d--){
        int lst = crnt;
        for(int n : dist[d]){
            if(ping(crnt, n) == 0){
                crnt = n;
                travelTo(n);
                break;
            }
        }
        assert(crnt != lst);
    }
    travelTo(B);
}
