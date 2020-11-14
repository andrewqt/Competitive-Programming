#include <bits/stdc++.h>

using namespace std;

int A, B, C, X, Y, Z;

int main(){
    cin >> A >> B >> C >> X >> Y >> Z;
    A = abs(A-X), B = abs(B-Y), C = abs(C-Z);
    cout << max(A, max(B, C)) << endl;
    cout << (int) (sqrt(A*A+B*B+C*C)) << endl;
    cout << A+B+C << endl;
}
