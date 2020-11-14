
// Problem : USACO 2020 January Silver P2 - Loan Repayment
// Contest : DMOJ
// URL : https://dmoj.ca/problem/usaco20jans2
// Memory Limit : 512.000000 MB 
// Time Limit : 2000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;
long long N, M, K;

bool chk(long long X){
	long long C = N;
	long long cnt = 0;
	long long D = N/X;
	while(D > M){
		long long P = (D)*X;
		long long nxt = P;
		long long coe = (C-P)/D+1;
		cnt += coe;
		C -= coe*D;
		D = C/X;
	}
	cnt += (C+M-1)/M;
	return cnt <= K;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K >> M;
	long long l = 1, r = N, ans = 0;
	while(l <= r){
		long long mid = l+r>>1;
		if(chk(mid)){
			ans = mid;
			l = mid + 1;
		}	
		else{
			r = mid - 1;
		}
	}
	cout << ans << "\n";
}