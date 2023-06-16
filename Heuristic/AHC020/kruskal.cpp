//クラスカル法による最小全域木を用いた解法
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

using Edge = pair<int, pair<int,int> >;
using Graph = vector< vector<Edge> >;
UnionFind uf(100);

int distance(int x1, int y1, int x2, int y2){
    return (int)(sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}

int main(){
    auto start = chrono::system_clock::now();
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> x(n),y(n);
    rep(i,n) cin >> x[i] >> y[i];
    vector<int> u(m),v(m),w(m);
    vector<Edge> edges(m);
    rep(i,m){
        cin >> u[i] >> v[i] >> w[i];
        u[i]--;v[i]--;
        edges[i] = Edge(w[i],make_pair(u[i],v[i]));
    }
    vector<int> a(k),b(k);
    rep(i,k) cin >> a[i] >> b[i];
    vector< vector< pair<int,int> > > count(n,vector< pair<int,int> >()); //count[i].size : 近傍の住民の数 , count[i] = i番目の放送局の各住民に対するpair(距離,住民番号)
    vector<int> mx(n,0); //放送局、距離の最大値
    vector<int> P(n,0);
    vector<int> B(m,0);

    auto near_residence = [&](){
        rep(i,k){
            int mnn = 1000000;
            int num;
            rep(j,n){
                int d = distance(a[i],b[i],x[j],y[j]);
                if(mnn > d){
                    mnn = d;
                    num = j;
                }
            }
            mx[num] = max(mx[num],mnn);
            count[num].push_back(make_pair(mnn,i));
        }
        rep(i,n)if(count[i].size() != 0)P[i] = mx[i]+1;    
    };    

    rep(i,n){
        sort(count[i].begin(),count[i].end());
        reverse(count[i].begin(),count[i].end());
    }
    
    auto kruskal = [&](){
        sort(edges.begin(),edges.end());
        set < pair<int,int> > st;
        rep(i,m){
            int w = edges[i].first;
            int u = edges[i].second.first;
            int v = edges[i].second.second;
            if(count[u].size() == 0)continue;
            if(count[v].size() == 0)continue;
            if(uf.issame(u,v))continue;
            st.insert(make_pair(u,v));
            uf.unite(u,v);
        }
        rep(i,m){
            if(st.count(make_pair(u[i],v[i])))B[i] = 1;
            else if(st.count(make_pair(v[i],u[i])))B[i] = 1;
            else B[i] = 0;
        }
    };

    auto cost = [&](){  
        ll sum = 0;
        rep(i,n)sum += P[i]*P[i];
        rep(i,m){
            if(B[i] == 1)sum += w[i];
        }
        return sum;
    };

    //住民resiを２番目に近い放送局にくっつけてスコアが良くなれば、、
    auto yamanobori = [&](int rd,int resi,int dis1,int dis2){
            int mnn = 100000000;  //新しい放送局numと住民resiとの距離
            int num; //新しい放送局番号
            rep(i,n){
                if(i == rd)continue;
                int d = distance(a[resi],b[resi],x[i],y[i]);
                if(mnn > d){
                    mnn = d;
                    num = i;
                }
            }
            int score = 0;
            if(mnn > 5000)return (false,num);
            if(mx[num] < mnn){
                score += (dis1*dis1) - (dis2*dis2); //放送局rdの円が小さくなったのでスコアUP(cost減)
                score -= (mnn-mx[num])*(mnn-mx[num]); //新しい放送局numは円が大きくなったのでスコアDOWN(cost増)
                if(score > 0)return (true,num);
                else return (false,num);
            }
             return (true,num);  
    };
    //放送局の近傍住民の探索
    //近傍住民がいない放送局はPを0にしている。
    near_residence();
    //山登り法の実装
    while(true){
        auto now = chrono::system_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - start).count();
        if(elapsed >= 1800) break;
        int rd = rand() % 100; //電波を0にする放送局をランダムに決定する
        if(P[rd] == 0)continue;
        if(count[rd].size() > 50)continue;
        bool flag;int num;
        flag,num = yamanobori(rd,count[rd][0].second,count[rd][0].first,count[rd][1].first);
        if(flag){
            
        }

    }
    //クラスカル法により辺の最適化を行う
    kruskal();

    rep(i,n) cout << P[i] << " ";
    cout << endl;
    rep(i,m) cout << B[i] << " ";
    cout << endl;
    //cout << cost() << endl;

}
