#include <bits/stdc++.h>

using namespace std;

int main(){
    long long N;
    int K, Q;
    cin >> N >> K >> Q;
    assert(K != 1);
    if(K == 1){
        while(Q--){
                long long a, b;
            cin >> a >> b;
            printf("%d\n", abs(a-b));
        }
    }
    else{
        while(Q--){
            long long a, b;
            cin >> a >> b;
            a--;
            b--;
            int cnt = 0;
            while(a != b){
                if(a < b){
                    swap(a, b);
                }
                cnt++;
                a = (a-1)/K;
            }
            printf("%d\n", cnt);
        }
    }
}
