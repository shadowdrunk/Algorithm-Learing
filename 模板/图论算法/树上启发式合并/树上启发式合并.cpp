#ifdef ShadowDrunk
//时间复杂度O(nlgn)
//是一种离线算法，实际上把所有的答案都提前预处理出来了
//实际上和树链刨分按重儿子划分的思想很像，问题中要回答以node节点为根的子树的答案
//每个节点的答案由其所有儿子和当前节点的影响构成
//我们对于每个节点先计算其轻儿子的答案（不保留对父亲节点的影响）
//在计算其重儿子的答案，保留对父亲节点影响
//然后我们加上当前节点影响，获取当前节点答案。最后根据是否保留影响，处理是否删除
//实际上每个节点到根节点最多只有lgn条轻边，而重儿子在计算答案对父亲影响时只会被遍历到一次，所以总复杂度O(nlgn)

    //核心数据
    std::vector<std::vector<int>> vec;
    int totcolor;
    std::vector<int> count;
    std::vector<int> sz;    //记录以当前节点为根的子树的大小
    std::vector<int> son;   //记录重儿子
    std::vector<int> L;     //当前节点的dfs序
    std::vector<int> R;     //当前节点为根的子树中最大的dfs序
    std::vector<int> Node;  //dfs序为i的节点
    int dfn;
    std::vector<int> cur;   //题目给出每个节点的颜色
    std::vector<int> ans;   //每个节点为根子树的答案

    //处理答案和影响部分
    void add(int node){
        if(count[cur[node]] == 0)
            totcolor += 1;
        count[cur[node]] += 1;
    }
    void del(int node){
        count[cur[node]] -= 1;
        if(count[cur[node]] == 0)
            totcolor -= 1;
    }
    int getans(){
        return totcolor;
    }

    ///树上启发式合并核心算法
    //第一遍dfs，处理数据
    void dfs1(int node, int fa){
        dfn += 1;
        L[node] = dfn;
        sz[node] = 1;
        Node[dfn] = node;
        for(auto v : vec[node]){
            if(v != fa){
                dfs1(v, node);
                sz[node] += sz[v];
                if(!son[node] || sz[son[node]] < sz[v])
                    son[node] = v;
            }
        }
        R[node] = dfn;
    }
    //第二遍dfs，树上启发式合并，计算答案
    void dfs2(int node, int fa, bool keep){
        //keep表示是否保留当前节点对于父亲节点的影响
        //计算轻儿子答案，不保留影响
        for(auto v : vec[node]){
            if(v != fa && v != son[node])
                dfs2(v, node, false);
        }
        //计算重儿子答案，保留影响
        if(son[node])
            dfs2(son[node], node, true);
        //加入轻儿子和当前节点影响，计算当前节点答案
        for(auto v : vec[node]){
            if(v != fa && v != son[node]){
                for(int i = L[v]; i <= R[v]; i++)
                    add(Node[i]);    
            }
        }
        add(node);
        ans[node] = getans();
        if(!keep){
            //不保留则删去影响
            for(int i = L[node]; i <= R[node]; i++)
                del(Node[i]);
        }
    }

    //输入和初始化
    int n;
    std::cin >> n;
    totcolor = 0;
    dfn = 0;
    vec = std::vector<std::vector<int>>(n + 1);
    count = std::vector<int>(n + 1, 0);
    sz = std::vector<int>(n + 1, 0);
    son = std::vector<int>(n + 1, 0);
    L = std::vector<int>(n + 1, 0);
    R = std::vector<int>(n + 1, 0);
    Node = std::vector<int>(n + 1, 0);
    cur = std::vector<int>(n + 1, 0);
    ans = std::vector<int>(n + 1, 0);

    //调用方式
    dfs1(1, -1);
    dfs2(1, -1, 1);

#endif