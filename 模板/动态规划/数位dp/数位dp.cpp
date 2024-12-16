#ifdef ShadowDrunk
//常用于统计一个范围内符合条件得数有多少
//本模板是记忆化搜索得模板
//本模板写时的例题是统计一个范围内的数字中的windy数（相邻位相差大于等于2的正整数）

    //例题输入
    ll l, r;
    std::cin >> l >> r;

    //关键数据
    int N = 18; //看题目数据范围定，N表示位数 + 1
    std::vector<std::vector<ll>> dp(N, std::vector<ll>(N, -1));
    std::vector<int> num;   //num中存储每个数字的每个位

    //或取数位函数
    std::function<void(ll)> get_num = [&](ll x) -> void{
        num.clear();
        num.push_back(0);   //使数字位数正确
        while(x){
            num.push_back(x % 10);
            x /= 10;
        }
    };

    //核心算法
    std::function<ll(ll, ll, bool, bool)> dfs = [&](ll pos, ll last, bool lead, bool limit) -> ll{
        ll ans = 0;
        if(pos == 0)
            return (!lead); //题目要求整数
        if(last != -100 && !limit && !lead && dp[pos][last] != -1)
            return dp[pos][last];    //dp记录的状态没有数位限制和前导0
        int up = (limit ? num[pos] : 9);
        for(int i = 0; i <= up; i++){
            if(i == 0 && lead)  //判断前导0（只有一只选0才会一直lead）
                ans += dfs(pos - 1, -100, true, limit && i == up);

            else if(std::abs(i - last) < 2) //不符合要求的数位舍去
                continue;
            
            else if(std::abs(i - last) >= 2)    //符合要求的数位
                ans += dfs(pos - 1, i, false, limit && i == up);
        }
        if(!limit && !lead)
            dp[pos][last] = ans;
        return ans;
    };

    //或取答案函数，包含多次使用的初始化与长度调整
    std::function<ll(ll)> get = [&](ll x) -> ll{
        get_num(x);
        for(int i = 0; i < N; i++)
                for(int k = 0; k < 10; k++)
                    dp[i][k] = -1;
        int len = num.size() - 1;
        return dfs(len, -100, true, true);
    };

    //例题输出答案
    std::cout << get(r) - get(l - 1) << endl;

#endif