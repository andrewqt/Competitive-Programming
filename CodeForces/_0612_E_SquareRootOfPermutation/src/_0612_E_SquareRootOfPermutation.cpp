#include <bits/stdc++.h>

using namespace std;

int N;
int p[1000005];
bool tkn[1000005];
int ans[1000005];
vector<vector<int>> vec[1000005];

int main(){
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
    }
    for(int i = 1; i<=N; i++){
        if(!tkn[i]){
            int c = i;
            vector<int> v;
            while(!tkn[c]){
                v.push_back(c);
                tkn[c] = 1;
                c = p[c];
            }
            if(v.size() == 1){
                continue;
            }
            else if(v.size()%2 == 1){
                for(int j = 0; j<v.size(); j++){
                    ans[j] = v[(j+1)%v.size()];
                }
            }
        }
    }
}
