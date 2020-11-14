#include <bits/stdc++.h>

using namespace std;

int N;
int arr[1<<18];
multiset<int> st;
bool tkn[1<<18];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i = 0; i<1<<N; i++){
        cin >> arr[i];
    }
    sort(arr, arr+(1<<N), greater<int>());
    tkn[0] = 1;
    for(int d = 0; d<N; d++){
        for(int i = 0; i<1<<N; i++){
            if(tkn[i]){
                st.insert(arr[i]);
            }
        }
        for(int i = 0; i<1<<N && st.size(); i++){
            if(!tkn[i] && *(--st.end()) > arr[i]){
                tkn[i] = 1;
                st.erase(--st.end());
            }
        }
        st.clear();
    }
    for(int i = 0; i<1<<N; i++){
        if(!tkn[i]){
            cout << "No"  << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
