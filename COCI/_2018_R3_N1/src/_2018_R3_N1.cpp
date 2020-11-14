#include <bits/stdc++.h>

using namespace std;

string s;
int cnt;
string chk = "HONI";
int idx;

int main(){
    getline(cin, s);
    for(int i = 0; i<s.end()-s.begin()+1; i++){
        if(s[i] == chk[idx]){
            cnt++;
            idx = (idx + 1)%4;
        }
    }
    cout << cnt/4 << endl;
}
