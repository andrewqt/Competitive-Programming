
// Problem : Problem 1. Standing Out from the Herd
// Contest : USACO - USACO 2017 December Contest, Platinum
// URL : http://www.usaco.org/index.php?page=viewproblem2&cpid=768
// Memory Limit : 256 MB
// Time Limit : 4000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
pair<pair<int, int>, pair<int, int>> srt[200005];
int pos[200005];
int lcp[200005];
long long ans[200005];
long long toend[200005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("standingout.in", "r")){
		freopen("standingout.in", "r", stdin);
		freopen("standingout.out", "w", stdout);
	}
	cin >> N;
	string s = "";
	int idx = 0;
	for(int i = 1; i<=N; i++){
		string t;
		cin >> t;
		s += t;
		for(char c : t){
			idx++;
			srt[idx].first.first = c-'a' + 1;
			srt[idx].second.first = i;
			srt[idx].second.second = idx;
		}
		idx++;
		srt[idx].first.first = 27;
		srt[idx].second.second = idx;
		s += "$";
	}
	idx++;
	srt[idx].first.first = 27;
	srt[idx].second.second = idx;
	s += "$";
	int M = idx;
	for(int d = 0; d<=17; d++){
		for(int i= 1; d && i<=M; i++){
			srt[i].first.first = pos[srt[i].second.second];
			srt[i].first.second = pos[(srt[i].second.second+(1<<(d-1))-1)%M+1];
		}
		sort(srt+1, srt+1+M);
		idx = 1;
		for(int i = 1; i<=M; i++){
			if(i-1){
				idx += srt[i].first != srt[i-1].first;
			}
			pos[srt[i].second.second] = idx;
		}
	}
	int d = 0;
	for(int i = 1; i<=M; i++){
		if(pos[i] == M){
			d = 0;
		}
		d -= !!d;
		while(s[i-1+d] == s[srt[pos[i]+1].second.second-1+d]){
			d++;
		}
		lcp[pos[i]] = d;
	}
	/*
	for(int i = 1; i<=M; i++){
		cout << srt[i].first.first << " " << s.substr(srt[i].second.second-1) << " " << lcp[i] << "\n";
	}
	*/
	for(int i = M; i; i--){
		if(s[i-1] == '$'){
			toend[i] = 0;
		}
		else{
			toend[i] = toend[i+1] + 1;
		}
	}
	for(int i = 1; i<=M; i++){
		int contr = 0;
		int lftcontr = toend[srt[i].second.second], rhtcontr = toend[srt[i].second.second];
		for(int l = i-1; l; l--){
			lftcontr= min(lftcontr, lcp[l]);
			if(srt[i].second.first != srt[l].second.first){
				contr = max(lftcontr, contr);
				break;
			}
		}
		for(int r = i; r < M; r++){
			rhtcontr = min(rhtcontr, lcp[r]);
			if(srt[i].second.first != srt[r+1].second.first){
				contr = max(contr, rhtcontr);
				break;
			}
		}
		//cout << contr << " " << toend[i] << "\n";
		//cout << toend[srt[i].second.second] - contr << " " << srt[i].second.second << "\n";
		if(srt[i-1].second.first == srt[i].second.first){
			ans[srt[i].second.first] += toend[srt[i].second.second] - max(lcp[i-1], contr);
		}
		else{
			ans[srt[i].second.first] += toend[srt[i].second.second] - contr;
		}
	}
	for(int i = 1; i<=N; i++){
		cout << ans[i] << "\n";
	}
	
}