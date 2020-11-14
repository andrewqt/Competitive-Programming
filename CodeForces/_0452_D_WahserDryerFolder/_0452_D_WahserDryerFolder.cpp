#include <bits/stdc++.h>

using namespace std;

int N, sz[3], tim[3];
int nxt[3][1005];
int getmin(int t){
    int mini = 1;
    for(int i = 1; i<=sz[t]; i++){
        if(nxt[t][i] < nxt[t][mini]){
            mini = i;
        }
    }
}

int main(){
    cin >> N >> A >> B >> C >> X >> Y >> Z;

}
