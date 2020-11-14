#include <bits/stdc++.h>

using namespace std;

int N;
struct Node{
    long long l,r, pre,suf,maxi;
};
Node seg[4000001];
long long v[1000005];

Node pushup(Node lft, Node rht){
    Node n;
    n.l = lft.l;
    n.r = rht.r;
    if(lft.pre == lft.r - lft.l + 1){
        n.pre = lft.pre + rht.pre;
    }
    else{
        n.pre = lft.pre;
    }
    if(rht.suf == rht.r - rht.l + 1){
        n.suf = rht.suf + lft.suf;
    }
    else{
        n.suf = rht.suf;
    }
    n.maxi = max(lft.maxi, rht.maxi);
    n.maxi = max(n.maxi, max(n.suf, n.pre));
    n.maxi = max(n.maxi, lft.suf + rht.pre);
    return n;
}

Node copy(Node n){
    Node x;
    x.l = n.l;
    x.r = n.r;
    x.pre = n.pre;
    x.suf = n.suf;
    x.maxi = n.maxi;
    return x;
}

void build(int l, int r, int idx){
    seg[idx].l = l;
    seg[idx].r = r;
    if(l == r){
        seg[idx].pre = seg[idx].suf = seg[idx].maxi = v[l];
        return;
    }
    int mid = (l+r)/2;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
    seg[idx] = pushup(seg[2*idx], seg[2*idx+1]);
//    cout << seg[idx].l << " " << seg[idx].r << " " << seg[idx].maxi << endl;
}

Node query(int l, int r, int idx){
    if(seg[idx].l ==l && seg[idx].r == r){
        return copy(seg[idx]);
    }
    int mid = (seg[idx].l + seg[idx].r)/2;
    if(r <= mid){
        return query(l, r, 2*idx);
    }
    else if(l > mid){
        return query(l, r, 2*idx+1);
    }
    else{
        return pushup(query(l, mid, 2*idx), query(mid+1, r, 2*idx+1));
    }
}

vector<long long> minimum_costs(vector<int> H, vector<int> L, vector<int> R){
    N = H.size();
    vector<long long> ans;
    for(int i =1; i<=N; i++){
        v[i] = H[i-1]%2;
    }
    build(1, N, 1);
    for(int i =0; i<L.size(); i++){
        Node n = query(L[i]+1, R[i]+1, 1);
        ans.push_back(2*(n.r-n.l+1) - n.maxi);
    }
    return ans;
}

int main(){
    cout << "HERE" << endl;
    vector<int> a, b, c;
    a.push_back(2);
    a.push_back(4);
    a.push_back(3);
    a.push_back(5);
    b.push_back(0);
    b.push_back(1);
    c.push_back(2);
    c.push_back(3);
    vector<long long> d = minimum_costs(a,b,c);
    for(auto n : d){
        cout << n << endl;
    }
}
