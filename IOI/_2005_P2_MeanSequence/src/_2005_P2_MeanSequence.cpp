#include <bits/stdc++.h>

using namespace std;

int N;
int lft, rht;
int cl, cr;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    lft = -1000000000, rht = 1000000000;
    cl = lft, cr = rht;
    for(int i = 1; i<=N; i++){
        int n;
        cin >> n;
        if(cr > n){
            rht -= cr-n;
            cr = n;
        }
        if(cl > n){
            lft += cl-n;
            cl = n;
        }
        cl = 2*n - cl;
        cr = 2*n - cr;
    }
    cout << max(0, rht-lft+1) << endl;
}
