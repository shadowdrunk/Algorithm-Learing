#ifdef ShadowDrunk
//时间复杂度O（n + m）
//实际上是将两个矛盾的关系转换为了图的关系来求解
//例题中的输入 a, va, b, vb意味着 a为va或者b为vb ,这可以理解为notva与notvb矛盾
//可以转换为notva 则一定 vb，notvb 则一定 va
//我们把对应点的true 和 false 当作两个不同的点来进行建图(注意true为n + 1开始后的点)
//我们对这个有向图进行tarjan求sccno，不难发现同一个sccno里的点一个选了全部必选
//我们可以发现图中拓扑排序(将sccno缩点之后)，序号越高则依赖性越高(越多点选择之后必须选该点，则该点依赖性越高)
//所以我们在构造解时可以从依赖性越高的点开始倒着选
//tarjan求sccno中sccno的序号实际上就是拓扑逆序的序号,所以我们直接按sccno的序号来判定即可
//sccno的序号越高意味着拓扑排序的序号越低，所以当sccno[i] > sccno[i + n]时我们选择true

    //核心数据
    int n;
    int sz; //sz = n * 2
    std::vector<int> low;
    std::vector<int> num;
    int dfn = 0;
    int cnt = 0;
    std::vector<int> sccno;
    std::stack<int> stk;
    std::vector<std::vector<int>> vec;

    //核心算法
    //tarjan部分
    void dfs(int node){
        stk.push(node);
        dfn += 1;
        low[node] = num[node] = dfn;
        for(auto v : vec[node]){
            if(!num[v]){
                dfs(v);
                low[node] = std::min(low[node], low[v]);
            }
            else if(!sccno[v])
                low[node] = std::min(low[node], num[v]);
        }
        if(low[node] == num[node]){
            cnt += 1;
            while(true){
                int now = stk.top();
                sccno[now] = cnt;
                stk.pop();
                if(now == node)
                    break;
            }
        }
    }
    void Tarjan(){
        cnt = 0;
        dfn = 0;
        //注意这里要用sz
        for(int i = 1; i <= sz; i++)
            if(!num[i])
                dfs(i);
    }

    //two_SAT判断是否存在解
    bool two_SAT(){
        Tarjan();
        for(int i = 1; i <= n; i++)
            if(sccno[i] == sccno[i + n])    //同一个强连通分量里的必须都选
                return false;
        return true;
    }

    //数据输入与初始化
    std::cin >> n;
    sz = n * 2;
    low = std::vector<int>(sz + 1);
    num = std::vector<int>(sz + 1);
    sccno = std::vector<int>(sz + 1, 0);
    vec = std::vector<std::vector<int>>(sz + 1);
    int m;
    std::cin >> m;
    for(int i = 1; i <= m; i++){
        int a, b, va, vb;
        std::cin >> a >> va >> b >> vb;
        int notva = va ^ 1;
        int notvb = vb ^ 1;
        vec[a + notva * n].push_back(b + vb * n);
        vec[b + notvb * n].push_back(a + va * n);
    }

    //构造一组解
    if(two_SAT()){
        std::cout << "POSSIBLE" << endl;
        for(int i = 1; i <= n; i++)
            std::cout << (sccno[i] > sccno[i + n]) << sendl[i == n];
        //tarjan 得到的 sccno是拓扑排序的逆序，按照我们建图的方式我们因该选择拓扑排序，序号大的元素
        //sccno的序号越小意味着拓扑序越大
        //注意从1 + n开始才是true
    }
    else
        std::cout << "IMPOSSIBLE" << endl;



#endif