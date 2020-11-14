#include <bits/stdc++.h>

using namespace std;

int p[250001], arr[250001];
int g[] = {2,3,4,12,6,7,1};
int r[] = {0, 0, 0, 0, 0};
long long MOD = 1000000009;

long long fpow(long long b, long long e){
    if(!e){
        return 1;
    }
    long long res = fpow(b, e/2);
    res = (res*res)%MOD;
    if(e%2){
        res = (res*b)%MOD;
    }
    return res;
}

int valid(int N, int inputSeq[]){
    int idx = 0;
    set<int> s;
    for(int i = 1; i<N; i++){
        if(inputSeq[i] < inputSeq[idx]){
            idx = i;
        }
    }
    int lst = inputSeq[idx];
    if(lst > N){
        lst = 0;
    }
    s.insert(lst);
    for(int i = idx+1, x = (lst)%N+1; i!=idx; i = (i+1)%N, x = (x)%N+1){
        if((inputSeq[i] <= N && inputSeq[i] != x) || s.count(inputSeq[i])){
            return 0;
        }
        s.insert(inputSeq[i]);
    }
    return 1;
}
int replacement(int N, int gondolaSeq[], int replacementSeq[]){
    fill(p, p+250001, -1);
    int idx = 0;
    for(int i = 0; i<N; i++){
        if(gondolaSeq[i] < gondolaSeq[idx]){
            idx = i;
        }
        p[gondolaSeq[i]] = i;
    }
    int lst = gondolaSeq[idx];
    if(lst > N){
        lst = 1;
    }
    int ans = 0;
    for(int i = (idx+1)%N, x = (lst)%N+1; ; i = (i+1)%N, x = (x)%N+1){
        arr[i] = x;
        if(i == idx){
            break;
        }
    }
//    cout << idx << endl;
    for(int i = (idx+1)%N; ; i = (i+1)%N){
//        cout << arr[i] << " " << gondolaSeq[i] << endl;
        while(arr[i] < gondolaSeq[i]){
            if(p[ans + N + 1] != -1){
                replacementSeq[ans] = arr[p[ans + N + 1]];
                ans++;
                arr[p[ans + N]] = ans + N;
            }
            else{
                replacementSeq[ans++] = arr[i];
                arr[i] = ans + N;
            }
        }
        if(i == idx){
            break;
        }
    }
    return ans;
}
int countReplacement(int N, int inputSeq[]){
    long long ans = valid(N, inputSeq);
    int mini = inputSeq[0];
    for(int i = 0; i<N; i++){
        mini = min(mini, inputSeq[i]);
    }
    long long cnt = 0;
    vector<long long> v;
    v.push_back(N);
    for(int i = 0; i<N; i++){
        if(inputSeq[i] > N){
            cnt++;
            v.push_back(inputSeq[i]*1LL);
        }
    }
    sort(v.begin(), v.end());
    for(int i = 1; i<=cnt; i++){
//        cout << fpow(cnt-i+1, v[i]-v[i-1]-1) << endl;
        ans = (ans*fpow(cnt-i+1, v[i]-v[i-1]-1))%MOD;
    }
    if(mini > N){
        ans = (ans*N)%MOD;
    }
    return ans;
}

int main(){
    /*
    cout << replacement(7, g, r) << endl;
    for(int i = 0; i<2; i++){
        cout << r[i] << endl;
    }
    */
    cout << countReplacement(7, g) << endl;
    cout << valid(7, g) << endl;
}
