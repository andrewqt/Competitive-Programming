#include <bits/stdc++.h>

using namespace std;

int main(){
    for(int i = 0; i<=120/5; i++){
        for(int j = 0; j<=120/4; j++){
            if((i*5+4*j)%3 == 0 && i*5+4*j <= 120){
                cout << i << " " << j << " " << (120-i*5-4*j)/3 << endl;
            }
        }
    }
}
