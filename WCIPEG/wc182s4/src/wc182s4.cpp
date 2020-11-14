#include <bits/stdc++.h>

using namespace std;

int N, T;
int arr[5000];
int t[5000];
vector<int> vec;

int main(){
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
    }
    int ans = 0;
    for(int i = 1; i<=N; i++){
        for(int j = i+2; j<=N; j+=2){
            for(int k = i; k<=j; k++){
                t[k] = arr[k];
            }
            int m = (i+j)/2;
            int l = i, r = j;
            while(l != m && r != m){
                if(t[l] == t[r]){
                    l++;
                    r--;
                }
                else if(t[l] > t[r]){
                    t[l] -= t[r];
                    r--;
                }
                else{
                    t[r] -= t[l];
                    l++;
                }
                if(r - m > m - l){
                    vec.push_back(1);
                }
                else if(r - m < m - l){
                    vec.push_back(2);
                }
            }
            ans += unique(vec.begin(), vec.end()) - vec.begin();
            vec.clear();
        }
    }
    cout << ans << endl;
}
