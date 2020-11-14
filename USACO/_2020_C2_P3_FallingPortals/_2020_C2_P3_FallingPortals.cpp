#include <bits/stdc++.h>

using namespace std;

struct frac{
	long long n, d;
	bool operator < (frac f) const{
		return n*f.d < f.n*d;
	}
	bool operator <= (frac f) const{
		return n*f.d <= f.n*d;
	}
};

int N;
vector<pair<int, frac>> graph[2005];
frac dist[2005];
int b[2005], d[2005];
frac ans[2005];
priority_queue<pair<frac, int>, vector<pair<frac, int>>, greater<pair<frac, int>>> pq;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("falling.in", "r")){
		freopen("falling.in", "r", stdin);
		freopen("falling.out", "w", stdout);
	}
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> b[i];
	}	
	for(int i = 1; i<=N; i++){
		cin >> d[i];
	}
	for(int i = 1; i<=N; i++){
		for(int j = i+1; j<=N; j++){
			long long n = b[j]-b[i];
			long long d = j-i;
			if(n >= 0){
				long long g = __gcd(n, d);
				n /= g, d /= g;
				graph[i].push_back({j, {n, d}});
				graph[j].push_back({i, {n, d}});
				//cout << " " << n << " " << d << "\n";
			} 
		}
	}
	for(int s = 1; s<=N; s++){
		for(int n = 1; n<=N; n++){
			dist[n] = {2000000000, 1};
		}
		dist[s] = {0, 1};
		pq.push({dist[s], s});
		while(pq.size()){
			auto n = pq.top();
			//cout << s << " " << n.second << "\n";
			pq.pop();
			for(auto e : graph[n.second]){
				auto wt = n.first;
				if(wt <= e.second && e.second < dist[e.first]){
					dist[e.first] = e.second;
					pq.push({dist[e.first], e.first});
				}
			}
		}
		if(dist[d[s]].n == 2000000000){
			cout << -1 << "\n";
		}
		else{
			cout << dist[d[s]].n << "/" << dist[d[s]].d << "\n";
		}
	}
}