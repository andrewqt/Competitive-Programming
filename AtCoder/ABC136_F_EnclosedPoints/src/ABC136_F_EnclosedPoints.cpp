#include <bits/stdc++.h>

using namespace std;

int N;
pair<int, int> arr[200005];
vector<int> cmp;
long long pow2[200005];
long long MOD = 998244353;
int BIT[2][200005];

void upd(int t, int p, int v){
    for(int i = p; i<=N; i+=i&-i){
        BIT[t][i] += v;
    }
}

int query(int t, int p){
    int s = 0;
    for(int i = p; i>0; i-=i&-i){
        s += BIT[t][i];
    }
    return s;
}

int getidx(int p){
    return lower_bound(cmp.begin(), cmp.end(), p) - cmp.begin() + 1;
}

long long add(long long a, long long b){
    return (a+b)%MOD;
}

long long sub(long long a, long long b){
    a = add(a, -b);
    if(a < 0){
        a += MOD;
    }
    return a;
}

long long mult(long long a, long long b){
    return a*b%MOD;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    pow2[0] = 1;
    for(int i = 1; i<=N; i++){
        cin >> arr[i].first >> arr[i].second;
        cmp.push_back(arr[i].second);
        pow2[i] = mult(pow2[i-1], 2);
    }
    sort(cmp.begin(), cmp.end());
    sort(arr+1, arr+1+N);
    for(int i = 1; i<=N; i++){
        arr[i].second = getidx(arr[i].second);
        upd(1, arr[i].second, 1);
    }
    long long ans = 0;
    for(int i = 1; i<=N; i++){
        upd(1, arr[i].second, -1);
        ans = add(ans, pow2[N]-1);
        int sumlfttop = query(0, arr[i].second), sumrhttop = query(1, arr[i].second);
        int sumlftbot = i - sumlfttop - 1, sumrhtbot = N - i - sumrhttop;
        //cout << "1: " << ans << endl;
        ans = sub(ans, pow2[sumlfttop+sumrhttop]);
        ans = sub(ans, pow2[sumlfttop+sumlftbot]);
        ans = sub(ans, pow2[sumrhttop+sumrhtbot]);
        ans = sub(ans, pow2[sumlftbot+sumrhtbot]);
        //cout << "2: " << ans << endl;
        ans = add(ans, pow2[sumlfttop]);
        ans = add(ans, pow2[sumrhttop]);
        ans = add(ans, pow2[sumlftbot]);
        ans = add(ans, pow2[sumrhtbot]);
        //cout << "3: " << ans << endl;
        upd(0, arr[i].second, 1);
    }
    cout << ans << endl;
}
