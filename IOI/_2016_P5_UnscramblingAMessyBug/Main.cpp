#include <bits/stdc++.h>

using namespace std;

char s[128];
int ans[128];
int N;

void add_element(string s){

}

void compile_set(){

}

bool check_element(string s){

}

void gen(int l, int r){
    if(l == r){
        return;
    }
    int mid = (l+r)/2;
    for(int i =0; i<l; i++){
        s[i] = '1';
    }
    for(int i = l; i<=r; i++){
        s[i] = '0';
    }
    for(int i = r+1; i<N; i++){
        s[i] = '1';
    }
    for(int i = l; i<=mid; i++){
        s[i] = '1';
        add_element(s);
        s[i] = '0';
    }
    gen(l, mid);
    gen(mid+1, r);
}

void sol(int l, int r, set<int> pos, int idx){
    if(l == r){
        ans[idx] = l;
        return;
    }
    set<int> lft, rht;
    int lidx = 0, ridx = 0;
    for(int i = 0; i<N; i++){
        if(!pos.count(i)){
            s[i] = '1';
        }
        else{
            s[i] = '0';
        }
    }
    for(auto n : pos){
        s[n] = '1';
        if(check_element(s)){
            lft.insert(n);
            lidx = n;
        }
        else{
            rht.insert(n);
            ridx = n;
        }
        s[n] = '0';
    }
    int mid = (l+r)/2;
    sol(l, mid, lft, lidx);
    sol(mid+1, r, rht, ridx);
}

int* restore_permutation(int n, int w, int r){
    N = n;
    for(int i =0; i<N; i++){
        s[i] = '0';
    }
    gen(0, N-1);
    compile_set();
    set<int> init;
    for(int i = 0; i<N; i++){
        init.insert(i);
    }
    sol(0, N-1, init, 0);
    return ans;
}

int main(){
    N = 8;
    gen(0, N-1);
}
