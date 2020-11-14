
// Problem : F - Enclose All
// Contest : AtCoder Beginner Contest 151
// URL : https://atcoder.jp/contests/abc151/tasks/abc151_f
// Memory Limit : 1024.000000 MB 
// Time Limit : 2000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

struct point{
	long double x, y;
	bool operator == (point p){
		return (abs(p.x-x) <= 1e-7) && (abs(p.y-y) <= 1e-7);
	}
};

int N;
point arr[55];

long double dis(point a, point b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

point midpt(point a, point b){
	return {(a.x+b.x)/2, (b.y+a.y)/2};
}

long double mxdis(point c){
	long double mx = 0;
	for(int i = 1; i<=N; i++){
		mx = max(mx, dis(c, arr[i]));
	}
	return mx;
}

point slp(point a, point b){
	if(a.x < b.x){
		swap(a, b);
	}
	int g = __gcd((int)(a.y-b.y), (int)(a.x-b.x));
	return {(a.y-b.y)/g, (a.x-b.x)/g};
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i].x >> arr[i].y;
	}
	long double ans = 2000*2000;
	for(int i = 1; i<=N; i++){
		ans = min(ans, mxdis(arr[i]));
	}
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			point c = midpt(arr[i], arr[j]);
			ans = min(ans, mxdis(c));
		}
	}
	for(int i = 1; i<=N; i++){
		for(int j = i+1; j<=N; j++){
			for(int k = j+1; k<=N; k++){
				auto s1 = slp(arr[i], arr[j]), s2 = slp(arr[i], arr[k]);
				if(s1 == s2){
					continue;
				}
				auto m1 = midpt(arr[i], arr[j]), m2 = midpt(arr[i], arr[k]);
				long double t;
				if(s1.first == 0){
					
				}
				else if(s2.first == 0){
					
				}
				else if(s1.second == 0){
					
				}
				else if(s2.second == 0){
					
				}
				else{
					
				}
			}
		}
	}
	cout << setprecision(14) << sqrt(ans) << endl;
}