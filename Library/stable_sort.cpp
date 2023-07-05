//安定ソート　：　同一の値が存在した時,元の順序を保持することを保証する。
//ABC308 - C

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


