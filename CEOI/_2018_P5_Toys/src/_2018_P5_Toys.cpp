#include <bits/stdc++.h>

using namespace std;

int N;
set<int> st;
set<int> ans;
vector<int> v;

void rec(int n, int idx, int tot){
    if(n == 1){
        ans.insert(tot);
        return;
    }
    for(; idx<v.size(); idx++){
        if(v[idx] > n){
            break;
        }
        if(n%v[idx] == 0){
            rec(n/v[idx], idx, tot+v[idx]-1);
        }
    }
}

int main(){
    cout.tie(0);
    cin >> N;
    st.insert(N);
    for(int i = 2; i<=sqrt(N); i++){
        if(N%i == 0){
            st.insert(i);
            st.insert(N/i);
        }
    }
    for(int n : st){
        v.push_back(n);
    }
    rec(N, 0, 0);
    cout << ans.size() << "\n";
    for(int n : ans){
        cout << n << " ";
    }
}
