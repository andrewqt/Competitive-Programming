#include <bits/stdc++.h>

using namespace std;

int N;
int fre[200005];
int pre[200005];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    for(int i = 1; i<=N; i++){
        int n;
        cin >> n;
        fre[n]++;
    }
    int ans = 0, ansl = 0, ansr = 0;
    for(int r = 1, l = 1; r<=200000; r++){
        pre[r] = pre[r-1] + fre[r];
        if(fre[r] == 0){
            l = r + 1;
        }
        else if(fre[r] == 1){
            if(ans < pre[r] - pre[l-1]){
                ans = pre[r] - pre[l-1];
                ansr = r;
                ansl = l;
            }
            l = r;
        }
        else{
            if(ans < pre[r] - pre[l-1]){
                ans = pre[r] - pre[l-1];
                ansr = r;
                ansl = l;
            }
        }
    }
    vector<int> v;
    for(int i = ansl; i<=ansr; i++){
        cout << i << " " << fre[i] << endl;
        while(fre[i]){
            v.push_back(i);
            fre[i]--;
        }
    }
    sort(v.begin(), v.end());
    for(int i = 0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
    unique(v.begin(), v.end());
    for(int i = 0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
    reverse(unique(v.begin(), v.end()), v.end());
    for(int i = 0; i<v.size(); i++){
        cout << v[i] << "\n";
    }
    cout << v.size() << "\n";
    for(int n : v){
        cout << n << " ";
    }
}
