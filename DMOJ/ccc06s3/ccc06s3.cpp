#include <bits/stdc++.h>

using namespace std;

pair<int, int> pt1, pt2;

int ccw(pair<int, int> p, pair<int, int> q, pair<int, int> r){
	long long v = (p.first-r.first)*(q.second-r.second) - (p.second-r.second)*(q.first-r.first);
	if(v < 0){
		return -1;
	}
	else if(v > 0){
		return 1;
	}
	return 0;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> pt1.first >> pt1.second >> pt2.first >> pt2.second;
	int N;
	cin >> N;
	int cnt = 0;
	while(N--){
		int k;
		cin >> k;
		bool intersect = 0;
		vector<pair<int, int>> v;
		for(int i = 0; i<k; i++){
			pair<int, int> p;
			cin >> p.first >> p.second;
			v.push_back(p);
		}
		v.push_back(*v.begin());
		for(int i = 0; i<k; i++){
			if(ccw(pt1, v[i], pt2) != ccw(pt1, v[i+1], pt2) && ccw(v[i], pt1, v[i+1]) != ccw(v[i], pt2, v[i+1])){
				intersect = 1;
			}
		}
		cnt += intersect;A
	}
	cout << cnt << endl;
}