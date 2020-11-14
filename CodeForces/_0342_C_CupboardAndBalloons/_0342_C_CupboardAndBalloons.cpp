#include <bits/stdc++.h>

using namespace std;

double H, R;

int main(){
    cin >> R >> H;
    double r = R/2.0;
    double L = H;
    H -= r;
    long long ans = 2;
    cout << "test" << " " << r*sqrt(3) << endl;
    for(int i = 1; H-(r*sqrt(3)) >= 0; i++){
        if(i&1){
            H -= (r*sqrt(3));
            L -= (r*sqrt(3));
            ans++;
        }
        else if(H-(r*sqrt(3)) >= 0){
            H -=(r*sqrt(3));
            L -=(r*sqrt(3));
            ans+=2;
        }
    }
    while(L >= r*sqrt(3)){
        ans++;
        L -= r*sqrt(3);
    }
    cout << ans << endl;
}
