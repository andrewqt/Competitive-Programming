#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> graph[100005];
unordered_map<int, int> mp [100005];
int sd[3], clr[100005], tpar[100005], dpar[100005], dep[100005];
deque<int> box[100005];
bool vis[100005];
priority_queue<pair<int,int>> pq;

int get(int n){
    return tpar[n] = tpar[n] == n ? n : get(tpar[n]);
}

void dfs(int n){
    tpar[n] = n;
    for(int e : graph[n]){
        if(e != dpar[n]){
            dpar[e] = n;
            dep[e] = dep[n] + 1;
            dfs(e);
        }
    }
}

void chk(int x, int y,int i){
    if(mp[x].count(y)){
        int n = mp[x][y];
        graph[n].push_back(i);
        graph[i].push_back(n);
    }
    else{
        mp[x][y] = i;
    }
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i<=N-2; i++){
        scanf("%d %d %d %d", &sd[0], &sd[1], &sd[2], &clr[i]);
        sort(sd, sd+3);
        chk(sd[0], sd[1], i);
        chk(sd[0], sd[2], i);
        chk(sd[1], sd[2], i);
        box[clr[i]].push_back(i);
    }
    dfs(1);
    for(int i =1; i<=N; i++){
        while(!box[i].empty()){
            int n = box[i].front();
            vis[n] = 1;
            pq.push({dep[n], n});
            box[i].pop_front();
        }
        while(!pq.empty()){
            int n = pq.top().first;
            pq.pop();
            if(!box[clr[n]].empty()){
                while(!box[clr[n]].empty()){
                    vis[box[clr[n]].front] = 1;
                    pq.push({dep[box[clr[n]].front],box[clr[n]].front});
                    box[clr[n]].pop_front();
                }
                pq.push({dep[n], n});
                continue;
            }
            if(pq.empty()){
                break;
            }

        }
    }
}
