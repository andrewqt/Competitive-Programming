#include <bits/stdc++.h>

using namespace std;

char ans[2003], keys[3], test[8005];
string sol;
int N, idx = 0;

int press(string n){
    int maxi = 0;
//    cout << n << endl;
    for(int i = 0, len = 0; i<n.size(); i++){
        cout << len << " " << i << " " << n[i] << " " << maxi << endl;
        if(sol[len] == n[i]){
//            cout << "OPT1" << endl;
            len++;
            maxi = max(maxi, len);
            if(N == len){
                break;
            }
//            cout << "OPT1" << endl;
        }
        else{
//            cout << "OPT2" << endl;
            if(len != 0){
                i--;
            }
            len = 0;
//            cout << "OPT2" << endl;
        }
    }
//    cout << maxi << endl;
    return maxi;
}

void fillup(int n){
    for(int i = 0; i<n; i++){
        test[idx++] = ans[i];
    }
}

string guess_sequence(int n){
    N = n;
    if(press("AB")){
        if(press("A")){
            ans[0] = 'A';
            keys[0] = 'B';
            keys[1] = 'X';
            keys[2] = 'Y';
        }
        else{
            ans[0] = 'B';
            keys[0] = 'A';
            keys[1] = 'X';
            keys[2] = 'Y';
        }
    }
    else{
        if(press("X")){
            ans[0] = 'X';
            keys[0] = 'A';
            keys[1] = 'B';
            keys[2] = 'Y';
        }
        else{
            ans[0] = 'Y';
            keys[0] = 'A';
            keys[1] = 'B';
            keys[2] = 'X';
        }
    }
    for(int i = 1; i<N; i++){
        fill(test, test+4*N, ans[0]);
        idx = 0;
        if(i == N-1){
            fillup(i);
            test[idx] = keys[0];
//            cout << test << endl;
            if(press(test) == N){
                ans[i] = keys[0];
            }
            else{
                test[idx] = keys[1];
//                cout << test << endl;
                if(press(test) == N){
                    ans[i] = keys[1];
                }
                else{
                    ans[i] = keys[2];
                }
            }
        }
        else{
            fillup(i);
            test[idx++] = keys[0];
            for(int j = 0; j<3; j++){
                fillup(i);
                test[idx++] = keys[1];
                test[idx++] = keys[j];
            }
//            cout << test << endl;
            int v = press(test);
            if(v == i){
                ans[i] = keys[2];
            }
            else if(v == i+1){
                ans[i] = keys[0];
            }
            else{
                ans[i] = keys[1];
            }
        }
    }
    return ans;
}

int main(){
    N = 4;
    sol[0] = 'Y';
    sol[1] = 'X';
    sol[2] = 'X';
    sol[3] = 'X';
    cout << guess_sequence(N) << endl;
}
