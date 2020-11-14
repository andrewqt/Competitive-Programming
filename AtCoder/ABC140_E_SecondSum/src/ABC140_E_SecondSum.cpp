#include <bits/stdc++.h>

using namespace std;

int N;
int idx[100005];
set<int> st;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i =1; i<=N; i++){
        int n;
        cin >> n;
        idx[n] = i;
    }
    st.insert(0), st.insert(N+1);
    long long ans = 0;
    for(int n = N; n>0; n--){

        int p = idx[n];
        int lb = *(--st.lower_bound(p));
        int ub = *(st.upper_bound(p));
        if(lb){
            int t = *(--st.lower_bound(lb));
            ans += 1LL*n*(lb-t)*(ub-p);
        }
        if(ub != N+1){
            int t = *(st.upper_bound(ub));
            ans += 1LL*n*(p-lb)*(t-ub);
        }
        st.insert(p);
    }
    cout << ans << endl;
}
