#include <bits/stdc++.h>

using namespace std;

int A, B, C, X, Y, Z;

int main(){
    for(int i = 25; i<=25; i++){
        //string s = to_string(i);
        //freopen((s+"minecraftmarathonin.txt").c_str(), "r", stdin);
        //freopen(("minecraftmarathonout"+s +".txt").c_str(), "w", stdout);
        cin >> A >> B >> C >> X >> Y >> Z;
//        cout << A << " " << B << " " << C << " " << X << " " << Y << " " << Z << endl;
        A = abs(A-X), B = abs(B-Y), C = abs(C-Z);
        cout << max(A, max(B, C)) << endl;
        cout << (int) (sqrt(A*A+B*B+C*C)) << endl;
        cout << A+B+C << endl;
    }
}
