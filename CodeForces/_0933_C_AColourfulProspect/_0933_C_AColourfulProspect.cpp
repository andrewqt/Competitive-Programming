
// Problem : C. A Colourful Prospect
// Contest : Codeforces - Codeforces Round #462 (Div. 1)
// URL : https://codeforces.com/contest/933/problem/C
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct Point{
	long double x, y;
	Point(){
		
	}
	Point(long double _x, long double _y){
		x = _x;
		y = _y;
	}
	bool operator == (const Point & p) const{
		return x == p.x && y == p.y;
	}
	bool operator < (const Point & p) const {
		if(p.x == x){
			return p.y < y;
		}
		return p.x < x;
	}
};

struct Circle{
	Point c;
	int r;
	Circle(){
		
	}
	Circle(int _x, int _y, int _r){
		c = Point((long double) _x, (long double) _y);
		r = _r;
	}
	bool operator == (const Circle & cc) const{
		return cc.c == c && cc.r == r;
	}
	bool operator < (const Circle & cc) const{
		if(c == cc.c){
			return cc.r < r;
		}
		return c < cc.c;
	}
};

int N;
Circle c[3];
set<Point> mp;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 0; i<N; i++){
		int x, y, r;
		cin >> x >> y >> r;
		c[i] = Circle(x, y, r);
	}
	int f = 1;
	for(int i = 0; i<N; i++){
		bool inter = 0;
		for(int j = 0; j<N; j++){
			if(i == j){
				continue;
			}
			long double v = -2*(c[i].c.x*c[j].c.x+c[i].c.y*c[j].c.y) + c[j].r*c[j].r-c[i].r*c[i].r;
			v -= 
		}
	}
}