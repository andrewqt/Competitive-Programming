#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> v;
deque<int> lst[2];
bool tkn[2][100005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	long long ans = 0;
	for(int i = 1; i<=2*N; i++){
		int x, y;
		cin >> x >> y;
		y--;
		if(y <= 0){
			ans += -y;
			lst[0].push_back(x);
		}
		else{
			ans += y-1;
			lst[1].push_back(x);
		}
		v.push_back(x);
	}
	long long toty = ans;
	cout << ans << endl;
	sort(v.begin(), v.end());
	sort(lst[0].begin(), lst[0].end());
	sort(lst[1].begin(), lst[1].end());
	for(int i = 0; i<2*N; i+=2){
		int idx = i/2 + 1;
		ans += abs(v[i]-idx);
		ans += abs(v[i+1]-idx);
	}
	for(int n : v){
		cout << n << " ";
	}
	cout << endl;
	//cout << ans << endl;
	cout << lst[0].size() << " " << lst[1].size() << endl;
	for(int n : lst[0]){
		cout << n << " ";
	}
	cout << endl;
	for(int n : lst[1]){
		cout << n << " ";
	}
	cout << endl;
	long long tot1 = 0;
	for(int i = 0; i<N-1; i++){
		tot1 += abs(lst[0][i] - (i+1));
	}
	cout << tot1 << " ";
	long long tot2 = 0;
	for(int i = 0; i<N-1; i++){
		tot2 += abs(lst[1][i] - (i+1));
	}
	cout << tot2 << endl;
	cout << tot1 + tot2 << endl;
	cout << ans << endl;
	for(int i = N; i; i--){
		for(int k = 2*i-1; k>2*i-3; k--){
			//cout << lst[0].size() << " " << lst[1].size() << " " << v[k] << endl;
			if(!tkn[0][i] && (lst[0].size() && lst[0].back() == v[k])){
				lst[0].pop_back();
				tkn[0][i] = 1;
			}
			else if(!tkn[1][i] && (lst[1].size() && lst[1].back() == v[k])){
				lst[1].pop_back();
				tkn[1][i] = 1;
			}
			else if(!tkn[0][i]){
				lst[1].pop_back();
				tkn[0][i] = 1;
				ans++;
			}
			else{
				lst[0].pop_back();
				lst[1][i] = 1;
				ans++;
			}
		}
	}
	cout << ans << "\n";
}