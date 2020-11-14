#include <bits/stdc++.h>

using namespace std;

int N;
double eps = 3e-8;
double x[100005], y[100005], typ[100005]; //0 U, 1 D, 2 R, 3 L

double calc(double val){
    double minix = 1000000000, maxix = -1000000000, miniy = 1000000000, maxiy = -1000000000;
    for(int i = 1; i<=N; i++){
        if(typ[i] == 0){
            minix = min(minix, x[i]);
            maxix = max(maxix, x[i]);
            miniy = min(miniy, y[i] + val);
            maxiy = max(maxiy, y[i] + val);
        }
        else if(typ[i] == 1){
            minix = min(minix, x[i]);
            maxix = max(maxix, x[i]);
            miniy = min(miniy, y[i] - val);
            maxiy = max(maxiy, y[i] - val);
        }
        else if(typ[i] == 2){
            minix = min(minix, x[i] + val);
            maxix = max(maxix, x[i] + val);
            miniy = min(miniy, y[i]);
            maxiy = max(maxiy, y[i]);
        }
        else{
            minix = min(minix, x[i] - val);
            maxix = max(maxix, x[i] - val);
            miniy = min(miniy, y[i]);
            maxiy = max(maxiy, y[i]);
        }
    }
    return (maxix-minix)*(maxiy-miniy);
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    for(int i= 1; i<=N; i++){
        cin >> x[i] >> y[i];
        char c;
        cin >> c;
        if(c == 'D'){
            typ[i] = 1;
        }
        else if(c == 'R'){
            typ[i] = 2;
        }
        else if(c == 'L'){
            typ[i] = 3;
        }
        else{
            typ[i] = 0;
        }
    }
    double l = 0, r = 200000000;
    while(r - l > eps){
        double mid1 = l + (r-l)/3, mid2 = r - (r-l)/3;
        if(calc(mid1) < calc(mid2)){
            r = mid2;
        }
        else{
            l = mid1;
        }
    }
    double ans = min(calc(l), calc(r));
    ans = min(calc((l+r)/2.0), ans);
    ans = min(calc((2*l+r)/3), ans);
    ans = min(calc((2*r+l)/3), ans);
    printf("%.3f\n", ans);
}
