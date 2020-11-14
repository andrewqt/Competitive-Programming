
// Problem : F. Dish Shopping
// Contest : Codeforces - Codeforces Round #548 (Div. 2)
// URL : https://codeforces.com/contest/1139/problem/F
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct smallnode{
	int l, r, s;
	smallnode *lft, *rht;
};

struct bignode{
	int l, r;
	smallnode *rt;
	bignode *lft, *rht;
};

int N, M;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	
}