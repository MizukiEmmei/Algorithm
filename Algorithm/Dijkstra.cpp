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
#define long long ll
const ll INF = 1e18;

//dijkstra法
void dijkstra(vector< vector<ll> > &graph, int s, vector<ll> &distance, vector<int> &prev) {
    int N = graph.size();
    distance.resize(N, INF);
    prev.resize(N, -1); 
    priority_queue<pair<ll,int>, vector< pair<ll,int> >, greater< pair<ll,int> > > pq; 
    dis[s] = 0;
    pq.emplace(dis[s], s);
    while (!pq.empty()) {
        pair<ll,int> p = pq.top();
        pq.pop();
        int v = p.second;
        if (dis[v] < p.first) {
            continue;
        }
        for (auto &e : graph[v]) {
            if (dis[e.to] > distance[v] + e.cost) {
                dis[e.to] = distance[v] + e.cost;
                prev[e.to] = v; 
                pq.emplace(distance[e.to], e.to);
            }
        }
    }
}

//経路の復元
vector<int> get_path(constvector<int> &prev, int t) {
    vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}
