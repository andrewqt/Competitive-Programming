#include <bits/stdc++.h>

using namespace std;

int N;
int arr[7] = {2, 3, 5, 7, 11, 13, 17};
vector<int> v = {0, 0, 0, 0, 0, 0, 0};
int cnt = 0;
map<vector<int>, int> mp;
vector<int> graph[2005];
int num[2000];
int out[2000][2000];
int dist[2000][2000];
int who[1000005];

void rec(int idx, int lst, int tot){
    //cout<< idx << " " << lst << " " << tot << endl;
    if(idx == 7){
        cnt++;
        mp[v] = cnt;
        int prod = 1;
        for(int i = 0; i<7; i++){
            prod *= v[i]+1;
        }
        num[cnt] = prod;
        return;
    }
    for(int i = 0; i<=lst && tot <= 1000000000; i++){
        v[idx] = i;
        rec(idx+1, i, tot);
        if(1000000000/arr[idx] < tot){
            break;
        }
        tot *= arr[idx];
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    rec(0, 22, 1);
    N = cnt;
    cout << N << endl;
    for(auto a : mp){
        for(auto b : mp){
            int dif = 0;
            for(int i = 0; i<7; i++){
                dif += abs(a.first[i]-b.first[i]);
            }
            if(dif == 1){
                graph[a.second].push_back(b.second);
            }
        }
    }
    for(int i = 1; i<=N; i++){
        queue<int> qu;
        qu.push(i);
        for(int j = 1; j<=N; j++){
            dist[i][j] = INT_MAX/3;
        }
        dist[i][i] = 0;
        while(qu.size()){
            int n = qu.front();
            qu.pop();
            for(int e : graph[n]){
                if(dist[i][e] > dist[i][n] + 1){
                    dist[i][e] = dist[i][n] + 1;
                    qu.push(e);
                }
            }
        }
    }
    for(int k = 1; k<=N; k++){
        for(int i = 1; i<=N; i++){
            out[k][i] = INT_MAX/3;
        }
    }
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            out[i][num[j]] = min(out[i][num[j]], dist[i][j]);
        }
    }
    for(int n = 1; n<=1000000; n++){
        vector<int> k;
        int t = n;
        for(int p = 2; p<=sqrt(t); p++){
            if(t%p == 0){
                int cnt = 0;
                while(t%p == 0){
                    t/=p;
                    cnt++;
                }
                k.push_back(cnt);
            }
        }
        if(t > 1){
            k.push_back(1);
        }
        sort(k.begin(), k.end(), greater<int>());
        while(k.size() < 7){
            k.push_back(0);
        }
        who[n] = mp[k];
        /*
        if(n == 438012 || n == 691200){
            cout << n << endl;
            for(int j =0 ; j<7; j++){
                cout << k[j] << " ";
            }
            cout << endl;
            cout << n << " " << num[who[n]] << endl;
        }
        */
    }
    int Q;
    cin >> Q;
    while(Q--){
        int a, b;
        cin >> a >> b;
        cout << min(out[who[b]][num[who[a]]], out[who[a]][num[who[b]]]) << "\n";
    }
}
