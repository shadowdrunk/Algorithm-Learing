#ifdef ShadowDrunk
//只是普通的路径压缩并查集
//并查集可以用来快速判断集合归属和合并集合
//并查集还可以用来判断图中有多少个连通块

    //记录与初始化
    std::vector<int> fa(n + 1);
    std::iota(fa.begin(), fa.end(), 0);

    //核心算法，路径压缩的查找
    std::function<int(int)> find = [&](int i) -> int{
        if(fa[i] != i)
            fa[i] = find(fa[i]);
        return fa[i];
    };

    //x合并到y的写法
    fa[find(x)] = find(y);

#endif