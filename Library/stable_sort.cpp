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
using namespace std;
#define rep(i, n) for(int i = 0; i < n; i++)


int main(){
    vector< pair<int,int> > c(10);
    rep(i,10)c[i].first = i;
    rep(i,10)cin >> c[i].second;

    auto f = [&](pair<int,int> i, pair<int,int> j) {
        return i.second > j.second; //二番目の値で降順ソート,値が等しい場合は元の順序を保持する
    };
  
    stable_sort(c.begin(),c.end(),f);
    rep(i,10)cout << c[i].first << " ";
}


