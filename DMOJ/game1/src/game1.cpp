#include <bits/stdc++.h>

using namespace std;

int N;
pair<int, int> arr[1001];

int main(){
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> arr[i].first;
        arr[i].second = i;
    }
    while(true){
        int x = 0;
        sort(arr+1, arr+1+N);
        for(int i =1; i<N; i++){
            x ^= arr[i].first;
        }
        cout << arr[N].second << " " << arr[N].first - x << endl;
        arr[N].first -= x;
        cout.flush();
        int p, n;
        cin >> p >> n;
        if(!p && !n){
            break;
        }
        for(int i= 1; i<=N; i++){
            if(p == arr[i].second){
                arr[i].first -= n;
            }
        }
    }
}
