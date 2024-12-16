#ifdef ShadowDrunk
//注意本模板是用于处理树上的路径问题
//通过欧拉序将一颗树展开之后通过莫队转换成区间问题进行维护
//树上莫队求路径问题通常需要快速lca的算法，本模板使用的是树链刨分求lca
//本模板题是求路径之间颜色的种类

    //核心数据
    std::vector<std::vector<int>> vec;
    std::vector<int> L;     //当前节点的dfs序
    std::vector<int> R;     //当前节点为根的子树中最大的dfs序
    std::vector<int> Node;  //dfs序为i的节点
    std::vector<int> cur;   //题目给出每个节点的颜色          
    std::vector<int> ans;   //每个节点为根子树的答案
    std::vector<int> count;
    std::vector<int> vis;
    int n;
    std::vector<int> dfn;   //我的dfn是1序的
    std::vector<int> deep;
    std::vector<int> fa;
    std::vector<int> sz;
    std::vector<int> son;
    std::vector<int> top;
    struct qury{
        int L, R;
        int ind;
    };
    std::vector<qury> ask;
    std::vector<int> pos;
    int ANS;

    //核心算法莫队部分（LCA实际应该算树链刨分部分）
    bool cmp(qury a, qury b){
        if(pos[a.L] != pos[b.L])    //先按左端点分块排序
            return pos[a.L] < pos[b.L];
        //右端点根据奇偶块升降排序，右端点不按分块排序
        if(pos[a.L] & 1)
            return a.R > b.R;
        return a.R < b.R;
    }
    void add(int node){
        vis[node] += 1;
        if(vis[node] == 1){
            count[cur[node]] += 1;
            if(count[cur[node]] == 1)
                ANS += 1;
        }
        else if(vis[node] == 2){
            count[cur[node]] -= 1;
            if(count[cur[node]] == 0)
                ANS -= 1;
        }
    }
    void del(int node){
        vis[node] -= 1;
        if(vis[node] == 1){
            count[cur[node]] += 1;
            if(count[cur[node]] == 1)
                ANS += 1;
        }
        else if(vis[node] == 0){
            count[cur[node]] -= 1;
            if(count[cur[node]] == 0)
                ANS -= 1;
        }
    }
    int LCA(int x, int y){
        while(top[x] != top[y]){
            //跳转链头深度大的点
            if(deep[top[x]] < deep[top[y]])
                std::swap(x, y);
            x = fa[top[x]];
        }
        return (deep[x] < deep[y] ? x : y);
    }
    int getans(int x, int y){
        int lca = LCA(x, y);
        int res = ANS;
        if(lca != x && lca != y){
            add(lca);
            res = ANS;
            del(lca);
        }
        return res;
    }
    //核心算法预处理与树链刨分部分
    void dfs1(int node, int father){
        deep[node] = deep[father] + 1;
        fa[node] = father;
        sz[node] = 1;

        dfn.push_back(node);
        L[node] = dfn.size() - 1;
        Node[dfn.size() - 1] = node;
        for(auto v : vec[node]){
            if(v != father){
                dfs1(v, node);
                sz[node] += sz[v];
                if(!son[node] || sz[son[node]] < sz[v])
                        son[node] = v;
            }
        }
        dfn.push_back(node);
        R[node] = dfn.size() - 1;
        Node[dfn.size() - 1] = node;
    }
    void dfs2(int node, int topx){
        top[node] = topx;
        if(!son[node])
            return;
        dfs2(son[node], topx);
        for(auto v : vec[node]){
            if(v != fa[node] && v != son[node]){
                dfs2(v, v);
            }
        }
    }

    //数据初始化
    std::cin >> n;
    dfn = std::vector<int>(1, 0);
    Node = std::vector<int>(2 * n + 1, 0);  //注意这里记录欧拉序要开成2 * n
    vec = std::vector<std::vector<int>>(n + 1);
    count = std::vector<int>(n + 1, 0);
    L = std::vector<int>(n + 1, 0);
    R = std::vector<int>(n + 1, 0);
    cur = std::vector<int>(n + 1, 0);
    deep = std::vector<int>(n + 1, 0);
    fa = std::vector<int>(n + 1);
    sz = std::vector<int>(n + 1);
    son = std::vector<int>(n + 1);
    top = std::vector<int>(n + 1);
    vis = std::vector<int>(n + 1);
    ANS = 0;
    int m;
    std::cin >> m;
    ans = std::vector<int>(m + 1, 0);
    ask = std::vector<qury>(m + 1);
    std::vector<int> num(1, 0);     //本题颜色种类需要离散化
    for(int i = 1; i <= n; i++){
        int x;
        std::cin >> x;
        cur[i] = x;
        num.push_back(x);
    }
    std::sort(num.begin() + 1, num.end());
    num.erase(std::unique(num.begin() + 1, num.end()), num.end());
    for(int i = 1; i <= n; i++){
        int ind = std::lower_bound(num.begin(), num.end(), cur[i]) - num.begin();
        cur[i] = ind;
    }

    //输入与调用
    for(int i = 1; i <= n - 1; i++){
        int x, y;
        std::cin >> x >> y;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    dfs1(1, 0);
    dfs2(1, 1);

    int len = dfn.size() - 1;
    int block = std::sqrt(len);   //每一块元素的个数
    pos = std::vector<int>(len + 1, 0);
    for(int i = 1; i <= len; i++)
        pos[i] = (i - 1) / block + 1;
    for(int i = 1; i <= m; i++){
        int x, y;
        std::cin >> x >> y;
        ask[i].ind = i;
        if(L[x] > L[y])
            std::swap(x, y);

        if(R[x] > L[y]){
            //此时y在x子树内
            ask[i].L = L[x];
            ask[i].R = L[y];
        }
        else{
            ask[i].L = R[x];
            ask[i].R = L[y];
        }
    }
    std::sort(ask.begin() + 1, ask.end(), cmp); 
    int L = 1;
    int R = 0;
    for(int i = 1; i <= m; i++){
        while(L > ask[i].L)
            add(Node[--L]);
        while(R < ask[i].R)
            add(Node[++R]);
        while(L < ask[i].L)
            del(Node[L++]);
        while(R > ask[i].R)
            del(Node[R--]);
        ans[ask[i].ind] = getans(Node[L], Node[R]);
    }

    //输出答案
    for(int i = 1; i <= m; i++)
        std::cout << ans[i] << endl;

#endif