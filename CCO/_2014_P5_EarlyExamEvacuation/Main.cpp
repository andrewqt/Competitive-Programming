#include <bits/stdc++.h>

using namespace std;

long long N, M;
long long A, B;
int arr[600005];
int BIT[100005];
bool seat[100005][6];

void upd(int n, int v){
    for(int i = n; i<=100000; i+=i&-i){
        BIT[i]+=v;
    }
}

int sum(int n){
    int s = 0;
    for(int i = n; i>0; i-=i&-i){
        s += BIT[i];
    }
    return s;
}

int main(){
    cin >> N >> M >> A >> B;
    for(int i = 1; i<=N; i++){
        upd(i, 2);
    }
    long long crnt = 0, ans = 0;
    for(int i = 1; i<=M; i++){
        string s, t;
        cin >> s;
        int c = s[s.size()-1] - 'A';
        int n = stoi(s.substr(0, s.size()-1));
        long long f = 0, b = 0;
        if(c == 0 && !seat[n][1]){
            f++;
            b++;
        }
        if(c == 5 && !seat[n][4]){
            f++;
            b++;
        }
        if(c == 2 || c == 3){
            upd(n, -1);
        }
        f += sum(n);
        b += sum(N) - sum(n-1);
        crnt += f*A;
        arr[i] = (b-f);
        seat[n][c] = 1;
//        cout << " " << arr[i] << endl;
    }
    ans = crnt + B*((M)*(M-1)/2);
    sort(arr+1, arr+M+1);
    for(long long i = 1; i<=M; i++){
        crnt += A*(arr[i]);
        ans = min(ans, crnt+B*((M-i)*(M-i-1)/2) + B*((i)*(i-1)/2));
//        cout << crnt+B*((M-i)*(M-i-1)/2) + B*((i)*(i-1)/2) << endl;
    }
    cout << ans << endl;
}
