//Dijkstra法を用いた解法
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <chrono>
#include <forward_list>
#include <initializer_list>
#include <random>
#include <ratio>
#include <regex>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
using namespace std;
typedef long long ll;
#define rep(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = 1; i <= n; i++)

using Edge = pair<int, pair<int,int> >;

struct UnionFind {
    vector<int> par,siz; //par[x] : xの親頂点を表す、自身が根の場合は-1 //  siz[x] : xの属する根付き木の頂点数を表す

    UnionFind(int n) : par(n, -1) , siz(n,1) {}

    int root(int x){
        if(par[x] == -1)return x;
        else return par[x] = root(par[x]);//経路圧縮
    }

    bool issame(int x, int y){
        return root(x) == root(y);
    }

    bool unite(int x, int y){
        x = root(x);
        y = root(y);

        if(x == y)return false;

        if(siz[x] < siz[y])swap(x,y);

        par[y] = x;
        siz[x] += siz[y];
        
        return true;
    }

    int size(int x){
        return siz[root(x)];
    }
};

using Graph = vector< vector<Edge> >;
Graph G(100);


int distance(int x1, int y1, int x2, int y2){
    return (int)(sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}

void dijkstra(int start,vector<long long> &dist, vector<int> &prev){
        dist.resize(100, 10000000000000000);
        prev.resize(100, -1);
        priority_queue< pair<ll,int>, vector< pair<ll,int> >, greater< pair<ll,int> > > pq;
        pq.emplace(dist[start] = 0,start);
        while(!pq.empty()){
            pair<ll,int> p = pq.top();
            pq.pop();
            int v = p.second;
            if(dist[v] < p.first)continue;
            for(auto &e : G[v]){
                if(dist[e.to] > dist[v] + e.weight){
                    dist[e.to] = dist[v] + e.weight;
                    prev[e.to] = v;
                    pq.emplace(dist[e.to], e.to);
                }
            }
        }
    };

vector<int> get_path(const vector<int> &prev, int t) {
    vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end()); // 逆順なのでひっくり返す
    return path;
}




int main(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> x(n),y(n);
    rep(i,n) cin >> x[i] >> y[i];
    vector<int> u(m),v(m),w(m);
    vector<ll> dist(100,10000000000000000);
    vector<int> prev(100,-1);


    rep(i,m){
        cin >> u[i] >> v[i] >> w[i];
        u[i]--;v[i]--;
        G[i].push_back(Edge(w[i],make_pair(u[i],v[i])));
    }
    vector<int> a(k),b(k);
    rep(i,k) cin >> a[i] >> b[i];
    vector< vector<int> > count(n,vector<int>()); //放送局、一番小さい住民の数
    vector<int> mx(n,0); //放送局、距離の最大値

    rep(i,k){
        int mn = 1000000;
        int num;
        rep(j,n){
            int d = distance(a[i],b[i],x[j],y[j]);
            if(mn > d){
                mn = d;
                num = j;
            }
        }
        count[num].push_back(i);
        mx[num] = max(mx[num],mn);
    }


    vector<int> P(n,0);
    vector<int> B(m,0);

    rep(i,n){
        if(count[i].size() >= 11)continue;
        else{
            rep(j,count[i].size()){
                int z = count[i][j]; //countが10以下の群に含まれる住民の番号 a[z],b[z]
                int mn = 1000000;
                int num;    
                rep(k,n){
                    if(count[k].size() < 11)continue;
                    else{
                        int d = distance(a[z],b[z],x[k],y[k]);
                        if(mn > d){
                            mn = d;
                            num = k;
                        }
                    }
                }
                mx[num] = max(mx[num],mn);
            }
        }
    }



    vector<int> lis;

    rep(i,n){
        if(count[i].size() < 11)continue;
        else{
            lis.push_back(i);
            P[i] = mx[i]+1;
        }
    }


    set< pair<int,int> >  st;
    dijkstra(0,dist,prev);
    //rep(i,n)cout << prev[i] << " ";
    //cout << endl << "====================" << endl;

    for(int i = 0; i < lis.size(); i++){
        vector<int> path = get_path(prev,lis[i]);
        rep(j,path.size()-1)st.insert(make_pair(path[j],path[j+1]));
        //if(i == 1)rep(j,path.size())cout << path[j] << " ";
    }

    rep(i,m){
        if(st.count(make_pair(u[i],v[i])) || st.count(make_pair(v[i],u[i])))B[i] = 1;
        else B[i] = 0;
    }


    auto cost = [&](){  
        ll sum = 0;
        rep(i,n)sum += P[i]*P[i];
        rep(i,m){
            if(B[i] == 1)sum += w[i];
        }
        return sum;
    };

    rep(i,n) cout << P[i] << " ";
    cout << endl;
    rep(i,m) cout << B[i] << " ";
    cout << endl;
    //cout << cost() << endl;

}
