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

