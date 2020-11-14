#include <bits/stdc++.h>

using namespace std;

struct node{
    int p;
    int len;
    char c;
};

node arr[1000005];
int crnt = 0, idx = 0;
int tbl[20][1000005];

void Init(){
    arr[0] = {-1, 0, ' '};
}

void add(int n){
    for(int d = 1; d<20; d++){
        tbl[d][n] = tbl[d-1][tbl[d-1][n]];
    }
}

void TypeLetter(char c){
    arr[++idx] = {crnt, arr[crnt].len+1, c};
    tbl[0][idx] = crnt;
    add(idx);
    crnt = idx;
}

void UndoCommands(int u){
    int k = crnt;
    while(u--){
        crnt = arr[crnt].p;
    }
    arr[++idx].c = arr[crnt].c;
    arr[idx].len = arr[crnt].len;
    arr[idx].p = k;
    add(idx);
    crnt = idx;
}

char GetLetter(int p){
    int t = crnt;
    p++;
    for(int d = 19; d>=0; d--){
        if(arr[tbl[d][t]].len >= p){
            t = tbl[d][t];
        }
    }
    return arr[t].c;
}

/*
int main(){
    Init();
    TypeLetter('a');
    TypeLetter('b');
    cout << GetLetter(1) << endl;
    TypeLetter('d');
    UndoCommands(2);
    UndoCommands(1);
    cout << GetLetter(2) << endl;
    TypeLetter('e');
    UndoCommands(1);
    UndoCommands(5);
    TypeLetter('c');
    cout << GetLetter(2) << endl;
    UndoCommands(2);
    cout << GetLetter(2) << endl;
}
*/
