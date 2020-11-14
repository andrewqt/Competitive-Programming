#include <bits/stdc++.h>

using namespace std;

int T;
vector<int> angles;

int main(){
    cin >> T;
    for(int i = 3; i<=180; i++){
        if(180%i == 0){
            angles.push_back(i);
        }
    }
    while(T--){
        int a;
        cin >> a;
        int ans = 180;
        for(int ang : angles){
            if(a%(180/ang) == 0 && a/(180/ang) <= ang-2){
                ans = ang;
                break;
            }
        }
        cout << ans << endl;
    }
}
