#include <bits/stdc++.h>

using namespace std;

long long x[1000005], y[1000005];
int N;

long long f(int x0, int y0){
    long long sum = 0;
    for(int i =1; i<=N; i++){
        sum += max(abs(x[i]-x0), abs(y[i]-y0));
//        cout << abs(x[i]) << " " << abs(y[i]) << endl;
    }
    return sum;
}

long long binx(int x){
    long long l = (1<<30)-1, r = -(1<<30)-1;
    long long best = 8000000000;
    while(l <= r){
        long long mid = (l+r)/2;
        long long crnt = f(x, mid), rht = f(x, mid+1);
        best = min(best, min(crnt, rht));
        if(mid <= crnt){
            r = mid-1;
        }
        else{
            l = mid+1;
        }
    }
    return best;
}

long long biny(int y){
    long long l = (1<<30)-1, r = -(1<<30)+1;
    long long best = 8000000000;
    while(l <= r){
        long long mid = (l+r)/2;
        long long crnt = f(mid, y), rht = f(mid+1, y);
        best = min(best, min(crnt, rht));
        if(mid <= crnt){
            r = mid-1;
        }
        else{
            l = mid+1;
        }
    }
    return best;
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i<=N; i++){
        scanf("%lld %lld", &x[i], &y[i]);
    }
//    cout << f(0, 0) << endl;
    long long tx = (1<<30)-1, ty = (1<<30)-1, bx = -((1<<30)-1), by = -((1<<30)-1);
    long long best = 8000000000000000000;
    int cnt = 35;
    while(cnt--){
        long long midx = (tx+bx)/2, midy = (ty+by)/2;
        long long crnt = f(midx, midy);
        long long toprht = f(midx+1, midy+1);
        long long toplft = f(midx-1, midy+1);
        long long botrht = f(midx+1, midy-1);
        long long botlft = f(midx-1, midy-1);
        long long low = min(min(toprht, toplft), min(botrht, botlft));
        best = min(best, low);
        best = min(best, min(binx(midx), biny(midy)));
        for(long long i = -10; i<=10; i++){
            for(long long j = -10; j<=10; j++){
                best = min(best, f(midx+i, midy+j));
            }
        }
//        cout << best << " " << midx << " " << midy << endl;
//        cout << best << " " << crnt << " " << top << " " << rht << endl;
        if(low == botlft){
            tx = midx-1;
            ty = midy-1;
        }
        else if(low == toplft){
            bx = midx+1;
            ty = midy-1;
        }
        else if(low == botrht){
            tx = midx-1;
            by = midy+1;
        }
        else{
            bx = midx+1;
            by = midy+1;
        }
    }
    for(long long i = -10; i<=10; i++){
        for(long long j = -10; j<=10; j++){
            best = min(best, f(tx+i, ty+j));
        }
    }
    printf("%lld\n", best);
}
