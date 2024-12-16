#ifdef ShadowDrunk
//注意本模板是用于处理子树问题的，基于dfs序展开子树的树上莫队
//如果是路径问题通常需要用欧拉序展开树
//通常可能需要想想是不是真的需要树上莫队，树上启发式合并可不可以做
//本模板题是统计子树中颜色出现次数大于k次的询问（注意k每个询问不同）

    //核心数据
    const int maxn = 1e5 + 10;
    std::vector<std::vector<int>> vec;
    std::vector<int> L;     //当前节点的dfs序
    std::vector<int> R;     //当前节点为根的子树中最大的dfs序
    std::vector<int> Node;  //dfs序为i的节点
    int dfn;
    std::vector<int> cur;   //题目给出每个节点的颜色          
    std::vector<int> ans;   //每个节点为根子树的答案
    std::vector<int> count;
    int n;
    std::vector<int> better;
    struct qury{
        int L, R;
        int ind;
        int k;
    };
    std::vector<qury> ask;
    std::vector<int> pos;

    //核心算法莫队部分
    bool cmp(qury a, qury b){
        if(pos[a.L] != pos[b.L])    //先按左端点分块排序
            return pos[a.L] < pos[b.L];
        //右端点根据奇偶块升降排序，右端点不按分块排序
        if(pos[a.L] & 1)
            return a.R > b.R;
        return a.R < b.R;
    }
    void add(int node){
        count[cur[node]] += 1;
        better[count[cur[node]]] += 1;
    }
    void del(int node){
        better[count[cur[node]]] -= 1;
        count[cur[node]] -= 1;
    }
    int getans(int k){
        if(k > n)
            return 0;
        return better[k];
    }
    //核心算法预处理dfs序
    void dfs1(int node, int fa){
        dfn += 1;
        L[node] = dfn;
        Node[dfn] = node;
        for(auto v : vec[node]){
            if(v != fa){
                dfs1(v, node);
            }
        }
        R[node] = dfn;
    }

    //数据初始化
    std::cin >> n;
    dfn = 0;
    vec = std::vector<std::vector<int>>(n + 1);
    count = std::vector<int>(maxn + 1, 0);
    L = std::vector<int>(n + 1, 0);
    R = std::vector<int>(n + 1, 0);
    Node = std::vector<int>(n + 1, 0);
    cur = std::vector<int>(n + 1, 0);
    better = std::vector<int>(n + 1, 0);
    better[0] = n;
    int m;
    std::cin >> m;
    ans = std::vector<int>(m + 1, 0);
    ask = std::vector<qury>(m + 1);
    pos = std::vector<int>(n + 1, 0);
    //输入与分块
    for(int i = 1; i <= n; i++)
        std::cin >> cur[i];
    for(int i = 1; i <= n - 1; i++){
        int x, y;
        std::cin >> x >> y;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    dfs1(1, -1);
    int block = std::sqrt(n);   //每一块元素的个数
    for(int i = 1; i <= n; i++)
        pos[i] = (i - 1) / block + 1;
    for(int i = 1; i <= m; i++){
        int node, k;
        std::cin >> node >> k;

        ask[i].ind = i;
        ask[i].L = L[node];
        ask[i].R = R[node];
        ask[i].k = k;
    }

    //莫队部分与输出答案
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
        ans[ask[i].ind] = getans(ask[i].k);
    }
    for(int i = 1; i <= m; i++)
        std::cout << ans[i] << endl;

#endif