#include <towns.h>
#include <bits/stdc++.h>

using namespace std;

int dist[2][200];
int par[200], sz[200];
bool midset[200], chk[200];
int graph[200][200];

/*
int getDistance(int i, int j){
    //cout << "? " << i << " " << j << endl;
    //int k;
    //cin >> k;
    //return k;
    return graph[i][j];
}
*/

int hubDistance(int N, int sub){
    int d1 = 0, d2 = 0;
    for(int i = 1; i<N; i++){
        dist[0][i] = getDistance(0, i);
        if(dist[0][i] > dist[0][d1]){
            d1 = i;
        }
    }
    for(int i = 0; i<N; i++){
        dist[1][i] = getDistance(d1, i);
        if(dist[1][i] > dist[1][d2]){
            d2 = i;
        }
    }
    int dia = dist[1][d2];
    //cout << "diameter endpoints: " << d1 << " " << d2 << endl;
    int ans = dia;
    for(int i = 0; i<N; i++){
        int k = (dist[0][d1] + dist[1][i] - dist[0][i])/2;
        //cout << "which set?: " << i << " " << k << endl;
        if(abs(ans-dia/2) > abs(k-dia/2)){
            ans = k;
        }
        else if(dia%2 == 0 && abs(ans-dia/2) == abs(k-dia/2) && k < ans){
            ans = k;
        }
        midset[i] = 0;
        chk[i] = 0;
    }
    int d = ans;
    ans = max(ans, dia-ans);
    //cout << "ans: " << ans << "\n";
    int lft = 0, rht = 0;
    for(int i = 0; i<N; i++){
        int k = (dist[0][d1] + dist[1][i] - dist[0][i])/2;
        //cout << "which set again?: " << i << " " << k << endl;
        //cout << dist[0][d1] << " " << dist[1][i] << " " << dist[0][i] << endl;
        if(dia-k > k && dia-k > ans){
            //cout << "lft: " << i << endl;
            midset[i] = 1;
            lft++;
        }
        else if(k > dia-k && k > ans){
            //cout << "rht: " << i << endl;
            midset[i] = 1;
            rht++;
        }
        else if(dia-k == d){
            chk[i] = 1;
        }
        //cout << dia-k << " " << k << "\n";
    }
    if(max(lft, rht) > N/2){
        return -ans;
    }
    /*
    vector<int> v, w;
    for(int i =0 ; i<N; i++){
        if(midset[i]){
            par[i] = -1;
            sz[i] = 0;
            continue;
        }
        par[i] = i;
        v.push_back(i);
        sz[i] = 1;
    }
    int g = -1;
    while(v.size()){
        //cout << "next iteration: " << k << endl;
        random_shuffle(v.begin(), v.end());
        while(v.size() >= 2){
            int n = v.back();
            v.pop_back();
            int m = v.back();
            v.pop_back();
            //cout << dist[1][n] + dist[1][m] - getDistance(n, m) << " " << 2*d << endl;
            if(dist[1][n] + dist[1][m] - getDistance(n, m) > 2*d){
                par[n] = -1;
                sz[m] += sz[n];
                w.push_back(m);
            }
        }
        if(v.size() == 1 && w.empty()){
            g = v[0];
            break;
        }
        swap(v, w);
        w.clear();
    }
    //cout << g << endl;
    if(g != -1){
        int cnt = 0;
        for(int i = 0; i<N; i++){
            if(par[i] == i && !midset[i]){
                if(dist[1][i] + dist[1][g] - getDistance(i, g) > 2*d){
                    cnt += sz[i];
                    //cout << "sz: " << i << " " << sz[i] << endl;
                }
            }
        }
        //cout << cnt << endl;
        if(cnt > N/2){
            ans = -ans;
        }
    }
    */
    /*
    int g = -1, cnt = 0;
    for(int i = 0; i<N; i++){
        if(midset[i]){
            continue;
        }
        if(cnt == 0){
            g = i;
            cnt = 1;
        }
        else if(dist[1][i] + dist[1][g] - getDistance(i, g) > 2*d){
            cnt++;
        }
        else{
            cnt--;
            if(cnt == 0){
                g = -1;
            }
        }
        //cout << i << " " << cnt << endl;
    }
    //cout << "g: " << g << endl;
    if(g != -1){
        cnt = 0;
        for(int i = 0; i<N; i++){
            if(!midset[i] && dist[1][i] + dist[1][g] - getDistance(i, g) > 2*d){
                cnt++;
            }
        }
        //cout << cnt << endl;
        if(cnt > N/2){
            ans = -ans;
        }
    }
    */

    //Attempt for 3/2 * N
    /*
    vector<int> v, w;
    for(int i = 0; i<N; i++){
        if(midset[i]){
            v.push_back(-1);
            if(w.size()){
                v.push_back(w.back());
                w.pop_back();
            }
        }
        else if(v.empty() || dist[1][i] + dist[1][v.back()] - getDistance(i, v.back()) == 2*d){
            //cout << i << endl;
            v.push_back(i);
            if(w.size()){
                v.push_back(w.back());
                w.pop_back();
            }
        }
        else{
            //cout << " " << i << endl;
            w.push_back(i);
        }
    }
    */
    /*
    for(int i =0 ; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
    for(int i = 0; i<w.size(); i++){
        cout << w[i] << " ";
    }
    cout << endl;
    */
    /*
    int g = v.back();
    v.pop_back();
    //cout << "g: " << g << endl;
    while(v.size()){
        //cout << v.back() << endl;
        if(g != -1 && v.back() != -1 && dist[1][v.back()] + dist[1][g] - getDistance(v.back(), g) > 2*d){
            //cout << "hi" << endl;
            //cout << v.back() << endl;
            if(v.size() == 1){
                w.push_back(v.back());
            }
            v.pop_back();
            if(v.size()) {
                v.pop_back();
            }
        }
        else if(w.empty()){
            return ans;
        }
        else{
            v.pop_back();
            w.pop_back();
        }
    }
    if(w.size()){
        //cout << w.size() << endl;
        return -ans;
    }
    else{
        return ans;
    }
    */
    vector<int> v, w;
    //cout << "d: " << d << "\n";
    for(int i = 0; i<N; i++){
        if(midset[i]){
            v.push_back(-1);
            if(w.size()){
                v.push_back(w.back());
                w.pop_back();
            }
            continue;
        }
        /*
        if(v.back() != -1){
            cout << dist[1][v.back()] + dist[1][i] - getDistance(i, v.back()) << "\n";
        }
        */
        if(v.empty() || v.back() == -1){
            v.push_back(i);
            if(w.size()){
                v.push_back(w.back());
                w.pop_back();
            }
        }
        else if((!chk[i] || !chk[v.back()]) && dist[1][v.back()] + dist[1][i] - getDistance(i, v.back()) == 2*d){
            v.push_back(i);
            if(w.size()){
                v.push_back(w.back());
                w.pop_back();
            }
        }
        else if(chk[i] && chk[v.back()] && dist[1][i]-getDistance(i, v.back())+dist[1][v.back()] == 2*(dia-d)){
            v.push_back(i);
            if(w.size()){
                v.push_back(w.back());
                w.pop_back();
            }
        }
        else{
            w.push_back(i);
        }
    }
    /*
    for(int n : v){
        cout << n << " ";
    }
    cout << "\n";
    for(int n : w){
        cout << n << " ";
    }
    cout << "\n";
    */
    int m = v.back();
    //cout << "m: " << m << " " << w.size() << " " << v.size() << "\n";
    while(v.size() && w.size()){
        if(m != -1 && v.back() != -1){
            if(chk[m] && chk[v.back()] && dist[1][m]-getDistance(m, v.back())+dist[1][v.back()] > 2*(dia-d)){
                v.pop_back();
                if(v.size()){
                    v.pop_back();
                }
                else{
                    w.push_back(-1);
                }
            }
            else if((!chk[m] || !chk[v.back()]) && dist[1][v.back()] + dist[1][m] - getDistance(m, v.back()) > 2*d){
                v.pop_back();
                if(v.size()){
                    v.pop_back();
                }
                else{
                    w.push_back(-1);
                }
            }
            else{
                v.pop_back();
                w.pop_back();
            }
        }
        else{
            v.pop_back();
            w.pop_back();
        }
    }
    if(w.size()){
        return -ans;
    }
    else{
        return ans;
    }
}

/*
int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    int tempN, sub, T;
    cin >> sub >> T;
    while(T--){
        cin >> tempN;
        for(int i =0 ; i<tempN; i++){
            for(int j = 0; j<tempN; j++){
                cin >> graph[i][j];
            }
        }
        cout << hubDistance(tempN, sub) << "\n";
    }
}
*/
