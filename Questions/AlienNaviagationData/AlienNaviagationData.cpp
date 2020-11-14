#include <bits/stdc++.h>

using namespace std;

int N, K;
set<pair<int, pair<int, int>>> st;
set<int> p;
mt19937 g1(chrono::steady_clock::now().time_since_epoch().count());

int randint(int a, int b){
    return uniform_int_distribution<int>(a, b)(g1);
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    st.insert({0, {0, 0}});
    for(int t = 20; t<=20; t++){
        string s = to_string(t) + ".in";
        freopen(s.c_str(), "w", stdout);
        N = randint(300, 300);
        K = randint(300, 300);
        cout << N << " " << K << endl;
        for(int i = 0; i<N; i++){
            int a, b, c, d;
            do{
                a = randint(-100000, 100000);
                b = randint(-100000, 100000);
                c = randint(-100000, 100000);
                /*
                int k = randint(0, 3);
                if(k == 0){
                    a = 0;
                }
                else if(k == 1){
                    b = 0;
                }
                else if(k == 2){
                    c = 0;
                }
                */
            }
            while(st.count({a, {b, c}}));
            st.insert({a, {b, c}});
            d = randint(1, K);
            cout << a << " " << b << " " << c << " " << d << endl;
        }
        st.clear();
    }
}
