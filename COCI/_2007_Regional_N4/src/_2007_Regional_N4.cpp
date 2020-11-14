#include <bits/stdc++.h>

using namespace std;

string s;
int dp[2005][5005];

int main(){
    cin >> s;
    int idx = s.rfind('=');
    int ans = 0;
    for(int i = idx+1; i<s.size(); i++){
        ans = ans*10 + (s[i]-'0');
    }
}
