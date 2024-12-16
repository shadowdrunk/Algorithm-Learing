#ifdef ShadowDrunk
//时间复杂度O(n * lgn) + n * (m) ， 这里的m需要看题目的具体内容
//点分治是一种用于求解树上路径信息的一种分治方法
//把树上的每条路径都按照是否经过某个节点来进行分治
//根据树的重心的性质，我们删除了树的重心，剩余的子树的节点个数一定 <= n / 2
//所以我们最多进行lgn次分治，每次分治计算所有的路径信息加起来都是O（n）的
//本模板题是查询m次是否存在长度为k的路径，我们在点分治时把当前树所有点到root的距离计算出来
//通过尺取法(双指针)配合记录节点的属于那颗子树来进行快速验证
//我们总共会验证n次，每次验证时间复杂度为O(n * m)

    //核心数据
    int n;
    int m;
    struct edge{
        int to;
        int val;
    };
    std::vector<std::vector<edge>> vec;
    std::vector<bool> vis;  //记录某个点是否被作为根节点计算过
    int root;
    std::vector<int> can_vis;   //记录以rt为根能到达的节点
    std::vector<int> tree;  //记录rt能到达的节点分别属于那一颗子树
    std::vector<int> dis;   //记录能到达的节点到rt的距离
    std::vector<int> sz;    //记录以rt为根时某个节点为根的子树大小（删除了已经作为重心的点后）
    std::vector<int> max_sz;    //记录某个节点的最大的子树大小（删除了已经作为重心的点后）
    std::vector<int> ask;   //记录题目询问
    std::vector<bool> ans;  //记录询问答案

    //尺取法排序比较函数
    bool cmp(int a, int b){ //can_vis中的排序方式
        return dis[a] < dis[b];
    }

    //核心算法
    //获取重心
    void get_root(int node, int fa, int total){
        sz[node] = 1;
        max_sz[node] = 0;   //注意这里要清0，消去上一次求重心的影响
        for(auto ed : vec[node]){
            int v = ed.to;
            if(v == fa || vis[v])
                continue;
            get_root(v, node, total);
            sz[node] += sz[v];
            max_sz[node] = std::max(max_sz[node], sz[v]);
        }
        max_sz[node] = std::max(max_sz[node], total - sz[node]);
        if(!root || max_sz[node] < max_sz[root])
            root = node;
    }

    //计算当前树中所有点到root的距离和可到点和归属子树
    void get_dis(int node, int fa, int len, int from){
        dis[node] = len;
        tree[node] = from;
        can_vis.push_back(node);
        for(auto ed : vec[node]){
            int v = ed.to;
            if(v == fa || vis[v])
                continue;
            get_dis(v, node, len + ed.val, from);
        }
    }

    //计算询问的答案
    void calc(int node){
        dis[node] = 0;
        tree[node] = node;
        can_vis.clear();    //注意清空
        can_vis.push_back(node);    //注意要加上当前根节点
        for(auto ed : vec[node]){
            int v = ed.to;
            if(vis[v])
                continue;
            get_dis(v, node, ed.val, v);
        }
        std::sort(can_vis.begin(), can_vis.end(), cmp);
        for(int i = 1; i <= m; i++){
            if(ans[i])
                continue;
            int l = 0;
            int r = can_vis.size() - 1;
            while(l < r){
                if(dis[can_vis[l]] + dis[can_vis[r]] > ask[i])
                    r -= 1;
                else if(dis[can_vis[l]] + dis[can_vis[r]] < ask[i])
                    l += 1;
                else if(tree[can_vis[l]] == tree[can_vis[r]]){
                    //实际上此时哪边等于移动哪个
                    //都不想等或者都相等随便移动
                    if(dis[can_vis[r]] == dis[can_vis[r - 1]])
                        r -= 1;
                    else
                        l += 1;
                }
                else{
                    ans[i] = true;
                    break;
                }
            }
        }
    }

    //点分治算法
    void dfz(int node){
        vis[node] = true;
        calc(node);
        for(auto ed : vec[node]){
            int v = ed.to;
            if(vis[v])
                continue;
            root = 0;   //get_dis里的编写，所以要置0
            get_root(v, node, sz[v]);
            dfz(root);  //继续处理子树的重心
        }
    }

    //输入与初始化
    std::cin >> n;
    std::cin >> m;
    vec = std::vector<std::vector<edge>>(n + 1);
    vis = std::vector<bool>(n + 1, false);
    dis = std::vector<int>(n + 1, 0);
    sz = std::vector<int>(n + 1, 0);
    max_sz = std::vector<int>(n + 1, 0);
    tree = std::vector<int>(n + 1, 0);
    ask = std::vector<int>(m + 1, 0);
    ans = std::vector<bool>(m + 1, false);

    for(int i = 1; i <= n - 1; i++){
        int x, y, w;
        std::cin >> x >> y >> w;
        vec[x].push_back({y, w});
        vec[y].push_back({x, w});
    }
    for(int i = 1; i <= m; i++){
        std::cin >> ask[i];
        if(ask[i] == 0) //特判等于0的路径
            ans[i] = true;
    }

    //调用点分治
    get_root(1, -1, n);
    dfz(root);

    //输出询问答案
    for(int i = 1; i <= m; i++)
        if(ans[i])
            std::cout << "AYE" << endl;
        else
            std::cout << "NAY" << endl;


#endif