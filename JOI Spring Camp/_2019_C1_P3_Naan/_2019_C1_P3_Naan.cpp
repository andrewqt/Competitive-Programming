#include <bits/stdc++.h>

using namespace std;

int N, L;
long long arr[2005][2005];
long long pre[2005][2005];
long long tar[2005];
bool done[2005];
vector<int> perm;
vector<long long> val;

long long calc(long long l, long long r, int idx){
	long long lblk = l/1000000000+1;
	long long rblk = r/1000000000;
	long long ret = pre[idx][rblk] - pre[idx][lblk];
	ret += arr[idx][rblk+1] * (r%1000000000);
	ret += arr[idx][lblk] * (1000000000 - l%1000000000);
	return ret;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> L;
	for(int i = 1; i<=N; i++){
		for(int l = 1; l<=L; l++){
			cin >> arr[i][l];
			tar[i] += arr[i][l] * 1000000000;
			pre[i][l] = pre[i][l-1] + arr[i][l] * 1000000000;
		}
		tar[i] /= N;
	}
	long long lst = 0;
	for(int t = 1; t<N; t++){
		long long bst = L*1000000000LL, idx = 0;
		for(int i = 1; i<=N; i++){
			if(!done[i]){
				long long l = lst+1, r = bst;
				if(calc(lst, bst, i) < tar[i]){
					continue;
				}
				while(l <= r){
					long long mid = l+r>>1;
					if(calc(lst, mid, i) >= tar[i]){
						bst = mid;
						r = mid - 1;
						idx = i;
					}
					else{
						l = mid + 1;
					}
				}
			}
		}
		perm.push_back(idx);
		val.push_back(bst);
		lst = bst;
		done[idx] = 1;
	}
	for(int i = 1; i<=N; i++){
		if(!done[i]){
			perm.push_back(i);
		}
	}
	for(int i = 1; i<N; i++){
		cout << val[i-1] << " " << 1000000000 << "\n";
	}
	for(int i = 1; i<=N; i++){
		cout << perm[i-1] << " ";
	}
}