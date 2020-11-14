#include <bits/stdc++.h>

using namespace std;

struct point{
    long long x, y;
    bool operator < (point p) const{
        if(y == p.y){
            return x > p.x;
        }
        return y < p.y;
    }
    bool operator == (point p) const{
        return p.x == x && p.y == y;
    }
};

long double dp[100005];
int cnt[100005];
point arr[100005];

long long sqr(long long x){
    return x*x;
}

double f(int j, int i){
    long long ci = sqr(arr[i].y) - 2*arr[i].y + dp[i-1] - sqr(max(0LL, arr[i-1].x - arr[i].y + 1));
    long long cj = sqr(arr[j].y) - 2*arr[j].y + dp[j-1] - sqr(max(0LL, arr[j-1].x - arr[j].y + 1));
    //cout << "val: " << (1.0*ci-cj)/(2*(arr[i].y-arr[j].y)) << endl;
    //cout << arr[i].y << " " << arr[j].y << endl;
    //cout << i << " " << j << endl;
    return (1.0*ci-cj)/(2*(arr[i].y-arr[j].y));
}

pair<int, long double> solve(long double C, int N){
    deque<int> dq;
    for(int n = 1; n<=N; n++){
        while(dq.size() >= 2 && f(dq[dq.size()-2], dq.back()) >= f(dq.back(), n)){
            dq.pop_back();
        }
        dq.push_back(n);
        while(dq.size() >= 2 && arr[n].x >= f(dq[0], dq[1])){
            dq.pop_front();
        }
        int i = dq.front();
        long double v = dp[i-1] + sqr(arr[n].x-arr[i].y+1) + C;
        if(arr[i].y <= arr[i-1].x){
            v -= sqr(arr[i-1].x-arr[i].y+1);
        }
        dp[n] = v;
        cnt[n] = cnt[i-1] + 1;
    }
    return {cnt[N], dp[N]};
}

long long take_photos(int N, int M, int K, int r[], int c[]){
    arr[0] = {0, 0};
    for(int i = 1; i<=N; i++){
        r[i-1]++, c[i-1]++;
        arr[i] = {r[i-1], c[i-1]};
        if(r[i-1] < c[i-1]){
            swap(arr[i].x, arr[i].y);
        }
    }
    sort(arr+1, arr+1+N);
    int cnt = 0;
    for(int n = 1; n<=N; n++){
        if(arr[n].x <= arr[n-1].x){
            //cout << " " << arr[n].x << " " << arr[n].y << endl;
            cnt++;
            arr[n].x = arr[n-1].x;
            arr[n].y = arr[n-1].y;
        }
    }
    unique(arr+1, arr+1+N);
    N-=cnt;
    K = min(K, N);
    long double lb = 0, ub = 2LL*M*M, ans = 1LL*M*M;
    while(lb <= ub){
        long double mid = (lb+ub)/2.0;
        pair<int, long double> p = solve(mid, N);
        //cout << mid << " " << p.second << endl;
        if(p.first == K){
            ans = p.second - (long double) (mid*p.first);
            break;
        }
        else if(p.first < K){
            //ans = min(ans, p.second - mid*p.first);
            ub = mid - 0.0000001;
        }
        else{
            lb = mid + 0.0000001;
        }
    }
    return (long long) (ans+0.5);
}

//int x[5] = {0, 2, 7, 4, 2}, y[5] = {5, 6, 4, 5, 6};
int x[5] = {0, 4, 4, 4, 4}, y[5] = {3, 4, 6, 5, 6};

int main(){
    //cout << take_photos(5, 8, 5, x, y) << endl;
    cout << take_photos(5, 7, 2, x, y) << endl;
}
