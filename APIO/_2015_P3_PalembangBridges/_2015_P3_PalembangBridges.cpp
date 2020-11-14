
// Problem : 
// 
// 
// Contest : DMOJ
// URL : https://dmoj.ca/problem/apio15p3
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct FenwickTree{
	long long bit[200005];
	int N;
	void upd(int n, int v){
		while(n <= N){
			bit[n] += v;
			n += n&-n;
		}
	}
	long long query(int n){
		long long ret = 0;
		while(n){
			ret += bit[n];
			n -= n&-n;
		}
		return ret;
	}
	int clmb(long long t){
		int ret = 0;
		long long sum = 0;
		for(int d = 17; d>=0; d--){
			if(ret+(1<<d) <= N && bit[ret+(1<<d)] + sum < t){
				sum += bit[ret+(1<<d)];
				ret += (1<<d);
			}
		}
		return ret+1;
	}
	void clr(){
		fill(bit, bit+1+N, 0);
	}
};

int T, N;
pair<int, int> arr[100005];
vector<int> cmp;
FenwickTree cnt, sum;
long long pre[100005], suf[100005];

int getidx(int n){
	return lower_bound(cmp.begin(), cmp.end(), n) - cmp.begin() + 1;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T >> N;
	long long c = 0;
	int idx = 0;
	for(int i =1 ; i<=N; i++){
		char a, b;
		int A, B;
		cin >> a >> A >> b >> B;
		if(a == b){
			c += abs(A-B);
		}
		else{
			c++;
			if(A > B){
				swap(A, B);
			}
			cmp.push_back(A);
			cmp.push_back(B);
			arr[++idx] = {A, B};
		}
	}
	N = idx;
	sort(arr+1, arr+1+N, [](pair<int, int> a, pair<int, int> b){
		return a.first+a.second < b.first+b.second;
		}
	);
	sort(cmp.begin(), cmp.end());
	cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
	sum.N = cnt.N = cmp.size();
	for(int i = 1; i<=N; i++){
		int a = getidx(arr[i].first), b = getidx(arr[i].second);
		cnt.upd(a, 1);
		cnt.upd(b, 1);
		sum.upd(a, arr[i].first);
		sum.upd(b, arr[i].second);
		int idx = cnt.clmb(i);
		long long pos = cmp[idx-1];
		pre[i] = pos*(cnt.query(idx)) - sum.query(idx);
		pre[i] += sum.query(sum.N) - sum.query(idx) - pos*(2*i-cnt.query(idx));
	}
	sum.clr();
	cnt.clr();
	for(int i = N; i; i--){
		int a = getidx(arr[i].first), b = getidx(arr[i].second);
		cnt.upd(a, 1);
		cnt.upd(b, 1);
		sum.upd(a, arr[i].first);
		sum.upd(b, arr[i].second);
		int idx = cnt.clmb(N-i+1);
		long long pos = cmp[idx-1];
		suf[i] = pos*(cnt.query(idx)) - sum.query(idx);
		suf[i] += sum.query(sum.N) - sum.query(idx) - pos*(2*(N-i+1)-cnt.query(idx)); 
	}
	long long out = pre[N];
	if(T == 2){
		for(int i = 0; i<=N; i++){
			out = min(pre[i] + suf[i+1], out);
		}
	}
	cout << out+c << "\n";
}