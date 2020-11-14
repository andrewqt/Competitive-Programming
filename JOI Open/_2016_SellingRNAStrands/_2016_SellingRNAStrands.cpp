#include <bits/stdc++.h>

using namespace std;

int N, Q;
string s;
int trief[4][2000005];
int trier[4][2000005];
int cntf = 0, cntr = 0;
int lftf[2000005], rhtf[2000005];
int lftr[2000005], rhtr[2000005];
int totf[2000005], totr[2000005];
int pf[200005], pr[200005];
int t = 0;
int qf[200005], qr[200005];
int who[200005];
int bit[4000005];
vector<int> qu[2000005], add[2000005];
int ans[200005];

int getc(char c){
	if(c == 'A'){
		return 0;
	}
	else if(c == 'U'){
		return 1;
	}
	else if(c == 'G'){
		return 2;
	}
	else{
		return 3;
	}
}

void dfs1(int n){
	lftf[n] = ++t;
	for(int k = 3; k>=0; k--){
		if(trief[k][n]){
			dfs1(trief[k][n]);
		}
	}
	rhtf[n] = ++t;
}

void dfs2(int n){
	lftr[n] = ++t;
	for(int k = 3; k>=0; k--){
		if(trier[k][n]){
			dfs2(trier[k][n]);
		}
	}
	rhtr[n] = ++t;
}

void upd(int n){
	while(n <= 2*cntr+2){
		bit[n]++;
		n += n&-n;
	}
}

int query(int n){
	int ret = 0;
	while(n){
		ret += bit[n];
		n -= n&-n;
	}
	return ret;
}

void dfs3(int n){
	for(int q : qu[n]){
		//cout << "f " << rhtr[qr[q]] << " " << lftr[qr[q]] << "\n";
		ans[q] -= query(rhtr[qr[q]]) - query(lftr[qr[q]]-1);
	}
	for(int k = 3; k>=0; k--){
		if(trief[k][n]){
			dfs3(trief[k][n]);
		}
	}
	for(int a : add[n]){
		//cout << lftr[who[a]] << "\n";
		upd(rhtr[who[a]]);
	}
	for(int q : qu[n]){
		//cout << rhtr[qr[q]] << " " << lftr[qr[q]] << "\n";
		//cout << query(rhtr[qr[q]]) << " " << query(lftr[qr[q]]) << "\n";
		ans[q] += query(rhtr[qr[q]]) - query(lftr[qr[q]]-1);
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	for(int i = 1; i<=N; i++){
		cin >> s;
		int n = 0;
		for(char c : s){
			int k = getc(c);
			if(!trief[k][n]){
				trief[k][n] = ++cntf;
			}
			n = trief[k][n];
		}
		add[n].emplace_back(i);
		totf[n]++;
		n = 0;
		reverse(s.begin(), s.end());
		for(char c : s){
			int k = getc(c);
			if(!trier[k][n]){
				trier[k][n] = ++cntr;
			}
			n = trier[k][n];
		}
		totr[n]++;
		who[i] = n;
	}
	//cout << cntf << " " << cntr << "\n";
	/*
	for(int k : add[1]){
		cout << k << " ";
	}
	cout << "\n";
	*/
	dfs1(0);
	t = 0;
	dfs2(0);
	for(int i = 1; i<=Q; i++){
		cin >> s;
		int n = 0;
		bool b = 1;
		for(char c : s){
			int k = getc(c);
			if(trief[k][n]){
				n = trief[k][n];
			}
			else{
				b = 0;
				break;
			}
		}
		qf[i] = n;
		n = 0;
		cin >> s;
		if(!b){
			continue;
		}
		reverse(s.begin(), s.end());
		for(char c : s){
			int k = getc(c);
			if(trier[k][n]){
				n = trier[k][n];
			}
			else{
				b = 0;
				break;
			}
		}
		qr[i] = n;
		if(b){
			qu[qf[i]].emplace_back(i);	
		}
	}
	dfs3(0);
	for(int q = 1; q<=Q; q++){
		cout << ans[q] << "\n";
	}
}