
// Problem : C. Boboniu and String
// Contest : Codeforces - Codeforces Round #664 (Div. 1)
// URL : https://codeforces.com/contest/1394/problem/C
// Memory Limit : 256 MB
// Time Limit : 3000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

#define test(x, y) if(func(x, y)) return make_pair(x, y);

int N;
string arr[300005];
pair<int, int> val[300005];

pair<int, int> solve(int r){
	int mxx = 1000000, mnx = 0, mxy = 1000000, mny = 0, mxd = 1000000, mnd = -1000000;	
	for(int i = 1; i<=N; i++){
		mxx = min(mxx, val[i].first + r);
		mnx = max(mnx, val[i].first - r);
		mxy = min(mxy, val[i].second + r);
		mny = max(mny, val[i].second - r);
		mxd = min(mxd, val[i].second - val[i].first + r);
		mnd = max(mnd, val[i].second - val[i].first - r);		
	}
	auto func = [&] (int x, int y){
		bool ret = x+y>0;
		ret &= (x >= mnx && x <= mxx);
		ret &= (y >= mny && y <= mxy);
		ret &= (x + mxd >= y);
		ret &= (x + mnd <= y);
		return ret;
	};
	test(mnx, mny);
	test(mnx, mxy);
	test(mxx, mny);
	test(mxx, mxy);
	test(mnx, mnx+mnd);
	test(mnx, mnx+mxd);
	test(mxx, mxx+mnd);
	test(mxx, mxx+mxd);
	test(mny-mnd, mny);
	test(mny-mxd, mny);
	test(mxy-mnd, mxy);
	test(mxy-mxd, mxy);
	return {-1, -1};
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		for(char c : arr[i]){
			val[i].first += (c == 'N');
			val[i].second += (c == 'B');
		}
	}
	int l = 0, r = 1000000, ans = 0;
	pair<int, int> p = {0, 0};
	while(l <= r){
		int mid = l+r>>1;
		auto q = solve(mid);
		if(q.first == -1){
			l = mid + 1;
		}
		else{
			ans = mid;
			p = q;
			r = mid - 1;
		}
	}
	solve(12);
	cout << ans << "\n";
	for(int i = 1; i<=p.first; i++){
		cout << 'N';
	}
	for(int j = 1; j<=p.second; j++){
		cout << 'B';
	}
}