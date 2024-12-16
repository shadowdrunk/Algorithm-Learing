#ifdef ShadowDrunk
//对于区间询问的问题，[l, r]如果能够通过O（1）的时间转移到l和r相邻的区间
//那么就可以使用莫队算法来解决
//莫队算法的原理就是将区间的查询离线进行分块,按莫队的方式排序,再暴力维护区间。
//因为分块排序的缘故，时间复杂度最终是O（n * n ^ 0.5）

    //核心数据
    int n;
    struct node{
        int L, R;
        int ind;
    };
    std::vector<int> pos;
    std::vector<int> cnt;
    std::vector<int> cur;
    std::vector<node> ask;
    int ANS = 0;

    //核心算法
    bool cmp(node a, node b){
        if(pos[a.L] != pos[b.L])    //先按左端点分块排序
            return pos[a.L] < pos[b.L];
        //右端点根据奇偶块升降排序，右端点不按分块排序
        if(pos[a.L] & 1)
            return a.R > b.R;
        return a.R < b.R;
    }
    void add(int x){
        cnt[cur[x]] += 1;
        if(cnt[cur[x]] == 1)
            ANS += 1;
    }
    void del(int x){
        cnt[cur[x]] -= 1;
        if(cnt[cur[x]] == 0)
            ANS -= 1;
    }

    //输入输出流程
    std::cin >> n;
    pos = std::vector<int>(n + 1, 0);
    cur = std::vector<int>(n + 1);
    cnt = std::vector<int>(1e6 + 1, 0);
    ANS = 0;
    //处理输入
    for(int i = 1; i <= n; i++)
        std::cin >> cur[i];
    //分块
    int block = std::sqrt(n);   //每一块元素的个数
    for(int i = 1; i <= n; i++)
        pos[i] = (i - 1) / block + 1;
    //处理询问
    int m;
    std::cin >> m;
    ask = std::vector<node>(m + 1);
    for(int i = 1; i <= m; i++){
        int l, r;
        std::cin >> l >> r;
        ask[i].L = l;
        ask[i].R = r;
        ask[i].ind = i;
    }
    std::sort(ask.begin() + 1, ask.end(), cmp);     //对查询按莫队的排序方式排序
    //暴力维护区间
    int L = 1;
    int R = 0;
    std::vector<int> ans(m + 1, 0); 
    for(int i = 1; i <= m; i++){
        while(L > ask[i].L)
            add(--L);
        while(R < ask[i].R)
            add(++R);
        while(L < ask[i].L)
            del(L++);
        while(R > ask[i].R)
            del(R--);
        ans[ask[i].ind] = ANS;
    }
    for(int i = 1; i <= m; i++)
        std::cout << ans[i] << endl;
    
#endif