//トポロジカルソート

//( deg : 入次数 ),( n : 頂点数 )
vector<int> Topological_Sort(vector<vector<int>> &graph, vector<int> &deg, int n) {
    // トポロジカルソートを記録する配列
    vector<int> sorted;

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    while (que.empty() == false) {
        int v = q.front();
        q.pop();
        for(auto c : graph[v]){
            deg[c]--;
            if(deg[c] == 0)q.push(c);
        }
        sorted.push_back(v);
    }

    // トポロジカルソートを返す
    return sorted;
}

//main関数にて渡した関数と返ってきた関数のサイズが同じであればトポロジカルソートが正しくできていたことになる。
//もし、サイズが異なれば正しくトポロジカルソートされておらず,グラフ内に閉路が存在することになる。