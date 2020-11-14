#include <bits/stdc++.h>

using namespace std;

int N, Q;
int cnt[200005];
int offset = 100000;
string s;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q >> s;
    fill(cnt, cnt+2*offset, -1);
    while(Q--){
        int l, r, t, p;
        cin >> t;
        if(t == 1){
            cin >> l >> r;
            cnt[offset] = l-1;
            int crnt = offset;
            int ans = 0;
            int rngl = offset, rngr = offset;
            for(int i = l; i<=r; i++){
                if(s[i-1] == '('){
                    crnt++;
                }
                else{
                    cnt[crnt] = -1;
                    crnt--;
                }
                rngl = min(rngl, crnt);
                rngr = max(rngr, crnt);
                if(!(cnt[crnt]+1)){
                    cnt[crnt] = i;
                }
                ans = max(ans, i - cnt[crnt]);
            }
            for(int i = rngl; i<=rngr; i++){
                cnt[i] = -1;
            }
            cout << ans << "\n";
        }
        else{
            cin >> p;
            if(s[p-1] == '('){
                s[p-1] = ')';
            }
            else{
                s[p-1] = '(';
            }
        }
    }
}
