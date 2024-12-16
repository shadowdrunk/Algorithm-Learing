#ifdef ShadowDrunk
//分块的思想实际上也是一种根号分治,和线段树懒标记的思想很像
//每个块的大小是n ^ 0.5
//对于查询和修改,如果位于同一个块内直接暴力
//对于跨越多个块,我们暴力查询或修改左右两边的块,中间完全覆盖的块我们可以用懒得思想来查询或修改
//列题是区间修改和查询区间第k大,列题时间复杂度多了个lgn ^ 0.5
//正常分块的时间复杂度是O(m * n ^ 0.5)
//与莫队不同的是分块是在线的，与询问次数有关

    //输入与初始化
    nt n, m;
    std::cin >> n >> m;
    std::vector<int> cur(n + 1);
    for(int i = 1; i <= n; i++)
        std::cin >> cur[i];
    int block = std::sqrt(n);   //每一块的大小
    int t = (n + block - 1) / block;    //块的数量

    std::vector<int> st(t + 1);     //块的起始和结尾
    std::vector<int> ed(t + 1);

    for(int i = 1; i <= t; i++){
        st[i] = (i - 1) * block + 1;    
        ed[i] = std::min(n, i * block);     //防止最后一块溢出
    }

    std::vector<int> pos(n + 1);    //每个元素位于的块的序号
    for(int i = 1; i <= n; i++)
        pos[i] = (i - 1) / block + 1;
    
    std::vector<int> add(t + 1, 0);     //整个块的修改标记

    //题目每块的特殊需求
    std::vector<std::vector<int>> b;    //辅助块，块内是有序的
    b.push_back({});    //对其块数
    for(int i = 1; i <= t; i++){
        std::vector<int> now;
        for(int j = st[i]; j <= ed[i]; j++)
            now.push_back(cur[j]);
        std::sort(now.begin(), now.end());
        b.push_back(now);
    }

    //查询与修改
    std::function<void(int, int, int)> change = [&](int L, int R, int d) -> void{
        int p = pos[L];
        int q = pos[R];
        if(p == q){
            //单个块内直接暴力
            std::vector<int> now;
            for(int i = L; i <= R; i++)
                cur[i] += d;
            for(int i = st[p]; i <= ed[p]; i++)
                now.push_back(cur[i]);
            std::sort(now.begin(), now.end());
            b[p] = now;
        }
        else{
            for(int i = p + 1; i <= q - 1; i++)     //处理整块
                add[i] += d;

            std::vector<int> now;   //前面的碎块处理
            for(int i = L; i <= ed[p]; i++)
                cur[i] += d;
            for(int i = st[p]; i <= ed[p]; i++)
                now.push_back(cur[i]);
            std::sort(now.begin(), now.end());
            b[p] = now;
            
            now.clear();    //后面的碎块处理
            for(int i = st[q]; i <= R; i++)
                cur[i] += d;
            for(int i = st[q]; i <= ed[q]; i++)
                now.push_back(cur[i]);
            std::sort(now.begin(), now.end());
            b[q] = now;
        }
    };

    std::function<int(int, int, int)> ask = [&](int L, int R, int w) -> int{
        int p = pos[L];
        int q = pos[R];
        int ans = 0;
        if(p == q){
            //单个块内直接暴力
            for(int i = L; i <= R; i++)
                ans += (cur[i] >= w - add[p]);
        }
        else{
            for(int i = p + 1; i <= q - 1; i++){    //处理整块
                auto it = std::lower_bound(b[i].begin(), b[i].end(), w - add[i]);
                ans += b[i].end() - it;
            }

            for(int i = L; i <= ed[p]; i++)
                ans += (cur[i] >= w - add[p]);
            for(int i = st[q]; i <= R; i++)
                ans += (cur[i] >= w - add[q]);
        }
        return ans;
    };

    //交互或取答案
    while(m--){
        char op;
        std::cin >> op;
        if(op == 'M'){
            int l, r, d;
            std::cin >> l >> r >> d;
            change(l, r, d);
        }
        else{
            int l, r, w;
            std::cin >> l >> r >> w;
            int ans = ask(l, r, w);
            std::cout << ans << endl;
        }
    }
    
#endif