#include <bits/stdc++.h>

using namespace std;

int R, C, N, SR, SC;
int minR, maxR, minC, maxC;


int main(){
    cin >> SR >> SC;
//    swap(SR, SC);
    cin >> R >> C >> N;
    maxR = 1000000000;
    maxC = 1000000000;
    for(int i = 1; i<=R; i++){
        int n;
        cin >> n;
        if(n < SR){
            minR = max(minR, n);
        }
        else{
            maxR = min(maxR, n);
        }
    }
    for(int i = 1; i<=C; i++){
        int n;
        cin >> n;
        if(n < SC){
            minC = max(minC, n);
        }
        else{
            maxC = min(maxC, n);
        }
    }
    int cnt = 0;
    for(int i =1; i<=N; i++){
        int x, y;
        cin >> x >> y;
//        swap(x, y);
        if(x > minR && x < maxR && y > minC && y < maxC){
            cout << "Y" << endl;
        }
        else{
            cout << "N" << endl;
        }
    }

}
