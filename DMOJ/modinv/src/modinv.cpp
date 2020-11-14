#include <bits/stdc++.h>

using namespace std;

unsigned long long extgcd(unsigned long long a, unsigned long long b,
                          long long *x0, long long *y0){
    if(a == 0){
        *x0 = 0;
        *y0 = 1;
        return b;
    }
    long long x1, y1;
    unsigned long long ret = extgcd(b%a, a, &x1, &y1);
    //cout << " " << x1 << " " << y1 << " " << a << " " << b << endl;
    *x0 = (y1 - b/a*x1);
    *y0 = x1;
    //cout << *x0 << " " << *y0 << endl;
    return ret;
}

int main(){
    unsigned long long N, M;
    long long X, Y;
    cin >> N >> M;
    extgcd(N, M, &X, &Y);
    while(X < 0){
        X += M;
    }
    cout << X << endl;
}
