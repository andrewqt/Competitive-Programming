#include "meetings.h"
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <utility>
#include <vector>

namespace {

const int MAX_N = 2000;
const int MAX_CALLS = 100000;

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}

int N, num_calls;
std::vector<int> graph[MAX_N];
std::set<std::pair<int, int>> edges, edges_reported;

int weight[MAX_N];

bool Visit(int p, int e, int rt = -1) {
  if (p == e) {
    ++weight[p];
    return true;
  }
  for (int q : graph[p]) {
    if (q != rt) {
      if (Visit(q, e, p)) {
        ++weight[p];
        return true;
      }
    }
  }
  return false;
}

}  // namespace

int Query(int u, int v, int w) {
  if (!(0 <= u && u <= N - 1 && 0 <= v && v <= N - 1 && 0 <= w && w <= N - 1 &&
        u != v && u != w && v != w)) {
    WrongAnswer(1);
  }
  if (++num_calls > MAX_CALLS) {
    WrongAnswer(2);
  }
  std::fill(weight, weight + N, 0);
  Visit(u, v);
  Visit(u, w);
  Visit(v, w);
  for (int x = 0; x < N; ++x) {
    if (weight[x] == 3) {
      return x;
    }
  }
  printf("Error: the input may be invalid\n");
  exit(0);
}

void Bridge(int u, int v) {
  if (!(0 <= u && u < v && v <= N - 1)) {
    WrongAnswer(3);
  }
  if (!(edges.count(std::make_pair(u, v)) >= 1)) {
    WrongAnswer(4);
  }
  if (!(edges_reported.count(std::make_pair(u, v)) == 0)) {
    WrongAnswer(5);
  }
  edges_reported.insert(std::make_pair(u, v));
}

#include "meetings.h"
#include <bits/stdc++.h>

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void rec(vector<int> v){
	if(v.size() == 1){
		return;
	}
	else if(v.size() == 2){
		Bridge(min(v[0], v[1]), max(v[0], v[1]));
		return;
	}
    shuffle(v.begin(), v.end(), rng);
	//random_shuffle(v.begin(), v.end());
	int c = v[0];
	if(v.size() > 100){
		int c1 = Query(v[0], v[1], v[2]);
		int c2 = Query(v[3], v[4], v[5]);
		int c3 = Query(v[6], v[7], v[8]);
		if(c1 != c2 && c3 != c1 && c2 != c3){
			c = Query(c1, c2, c3);	
		}
		else if(c1 == c2){
			c = c1;
		}
		else if(c1 == c3){
			c = c1;
		}
		else{
			c = c2;
		}
	}
	else if(v.size() > 5){
		c = Query(v[0], v[1], v[2]);
	}
	vector<vector<int>> st;
	for(int i = 0; i<v.size(); i++){
		int n = v[i];
		if(n == c){
			continue;
		}
		bool b = 0;
		for(int j = 0; j<st.size(); j++){
			if(Query(n, st[j][0], c) != c){
				b = 1;
				st[j].push_back(n);
				break;
			}
		}
		if(!b){
			st.push_back({n});
		}
	}
	for(auto k : st){
		int lca = k[0];
		for(int j = 1; j<k.size(); j++){
			if(lca != k[j]){
				lca = Query(lca, k[j], c);
			}
		}
		//cout << min(lca, c) << " " << max(lca, c) << "\n"; 
		Bridge(min(lca, c), max(lca, c));
		rec(k);
	}
}

void Solve(int N) {
	vector<int> v;
	for(int i = 0; i<N; i++){
		v.push_back(i);
	}
	rec(v);
}


int main() {
  if (scanf("%d", &N) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    if (scanf("%d%d", &u, &v) != 2) {
      fprintf(stderr, "Error while reading input\n");
      exit(1);
    }
    graph[u].push_back(v);
    graph[v].push_back(u);
    edges.insert(std::make_pair(u, v));
  }

  num_calls = 0;
  Solve(N);
  if (edges_reported.size() != static_cast<size_t>(N - 1)) {
    WrongAnswer(6);
  }
  printf("Accepted: %d\n", num_calls);
  return 0;
}
