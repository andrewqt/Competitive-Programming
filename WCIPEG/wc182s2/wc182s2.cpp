#include <bits/stdc++.h>

using namespace std;

int N;
int arr[300000];

int main(){
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
    }
    int mini = 0, maxi = 0;
    if(arr[1] > 1){
        cout << -1 << endl;
        return 0;
    }
    else{
        arr[1] = 1;
    }
    for(int i = N; i>0; i--){
        if(arr[i] == 0){
            arr[i] = max(arr[i+1] - 1, 0);
        }
        else if(arr[i] == 1){
            if(arr[i+1] > 2){
                cout << -1 << endl;
                return 0;
            }
        }
        else if(arr[i+1] == 0){

        }
        else if(arr[i] == arr[i+1] - 1){
            arr[i] = max(arr[i+1] - 1, 0);
        }
        else if(arr[i+1] != 1) {
            cout << -1 << endl;
            return 0;
        }
    }
    for(int i = 1; i<=N; i++){
        if(arr[i] == 1){
            mini++;
            maxi++;
        }
        else if(arr[i] == 0){
            maxi++;
        }
    }
    cout << mini-1 << " " << maxi-1 << endl;
}
