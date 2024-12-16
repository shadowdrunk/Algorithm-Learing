#ifdef ShadowDrunk
//时间复杂度O(n)
//寻找一个字符串中最长的回文子串的长度
//实际是对于回文性质的巧妙理解
//先将原字符串加工处理，全部以中心字符为1个来处理
//P[i]的含义是以i为中心的子串的最长回文半径
//实际答案为P[i] - 1。最长取max即可

    //数据及初始化
    std::string s;
    std::cin >> s;

    //改变原字符串
    std::function<std::string(std::string&)> change = [&](std::string& s) -> std::string{
        int n = s.size();
        std::string new_s;
        new_s.push_back('$');   //首尾添加不同的奇怪字符，减少边界判断
        new_s.push_back('#');
        for(int i = 0; i < n; i++){
            new_s.push_back(s[i]);
            new_s.push_back('#');
        }
        new_s.push_back('&');
        return new_s;
    };
    std::string new_s = change(s);

    int new_n = new_s.size();
    //最长的以i为中心的回文串的最长长度是P[i] - 1
    std::vector<int> P(new_n + 1, 0);   //以i为中心的回文串的最长半径
    
    //manachar核心算法
    std::function<void()> manachar = [&]() -> void{
        int R = 0, C = 0;   //最远右端与最远右端的中心
        for(int i = 1; i < new_n; i++){
            //两种情况取最小
            //前面是对称回文串被包住，后面是没被包住
            if(i < R)   
                P[i] = std::min(P[C * 2 - i], P[C] + C - i);    
            else
                P[i] = 1;
            //中心拓展暴力
            while(new_s[i + P[i]] == new_s[i - P[i]])
                P[i] += 1;
            if(P[i] + i > R){
                R = P[i] + i;
                C = i;
            }
        }
    };
    manachar();

    //答案计算
    int ans = 1;
    for(int i = 1; i <= n; i++)
        ans = std::max(ans, P[i] - 1);
    std::cout << ans << endl;

    
#endif