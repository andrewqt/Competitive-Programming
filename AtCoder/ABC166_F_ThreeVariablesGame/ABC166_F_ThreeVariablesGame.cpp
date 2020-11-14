
// Problem : F - Three Variables Game
// Contest : AtCoder - AtCoder Beginner Contest 166
// URL : https://atcoder.jp/contests/abc166/tasks/abc166_f
// Memory Limit : 1024 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

string ss[100005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int a[3];
	int N;
	cin >> N >> a[0] >> a[1] >> a[2];
	vector<char> ans;
	for(int i = 1; i<=N; i++){
		cin >> ss[i];
	}
	ss[N+1] = "AB";
	for(int i = 1; i<=N; i++){
		string s = ss[i];
		if(a[s[0]-'A'] == 0 && a[s[1]-'A'] == 0){
			cout << "No\n";
			return 0;
		}
		else if(a[s[0]-'A'] == a[s[1]-'A']){
			if(ss[i+1][0] == s[1] || ss[i+1][1] == s[1]){
				a[s[1]-'A']++, a[s[0]-'A']--;
				ans.push_back(s[1]);
			}
			else{
				a[s[1]-'A']--, a[s[0]-'A']++;
				ans.push_back(s[0]);
			}
		}
		else if(a[s[0]-'A'] > a[s[1]-'A']){
			ans.push_back(s[1]);
			a[s[0]-'A']--, a[s[1]-'A']++;
		}
		else{
			ans.push_back(s[0]);
			a[s[0]-'A']++, a[s[1]-'A']--;
		}
	}
	cout << "Yes\n";
	for(auto c : ans){
		cout << c << "\n";
	}
}