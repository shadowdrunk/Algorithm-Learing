#ifdef ShadowDrunk
//时间复杂度O（n + m）
//常用于处理图的前后关系

    //初始数据
    std::vector<int> ru(26, 0);
    std::queue<int> que;
    std::vector<int> ans;

    //核心算法
    std::function<bool()> tosport = [&]() -> bool{
        for(int i = 1; i <= n; i++)
            if(ru[i] == 0)
                que.push(i);
        while(!que.empty()){
            int node = que.front();
            que.pop();
            ans.push_back(node);
            for(auto x : vec[node]){
                ru[x] -= 1;
                if(ru[x] == 0)
                    que.push(x);
            }
        }
        return (ans.size() == n); //是否能将n个节点完成排序
    };
    
#endif