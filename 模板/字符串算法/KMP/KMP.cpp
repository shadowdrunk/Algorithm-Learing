#ifdef ShadowDrunk
//时间复杂度O(n)
//关键在于理解对于前缀函数的匹配
//原字符串为s，要找的匹配的子串为模式串p
//本模板字符串均是0序字符串
//模式串长度为n，原串长度为m

    //数据及初始化
    std::string p;
    std::cin >> p;
    std::string s;
    std::cin >> s;
    std::vector<int> Next;
    int count = 0;  //匹配次数
    int last = -1;  //上一次匹配位置

    //计算前缀函数 以i为结尾的字符串是否存在相等的真前缀和真后缀
    //nxt是模式串的前缀函数
    std::function<void(std::string&)> get_Next = [&](std::string& pattern) -> void{
        //对模式串进行处理得到前缀函数
        int len = pattern.size();
        Next = std::vector<int>(len + 1, 0);    
        Next[0] = 0; Next[1] = 0; //长度为1时没有前缀和后缀
        //Next[i] 表示模式串长度为i的子字符串中真前缀与真后缀的最长交集长度
        //真前缀后缀，不包括字符串本身
        for(int i = 1; i < len; i++){   
            //i的增加看作后缀的扩展
            int j = Next[i];    //i后移动，j匹配下一个字符
            while(j && pattern[i] != pattern[j])    //发现不匹配j移动到长度为Next[j]的前缀的Next处再次匹配
                j = Next[j];    //这里和kmp实际匹配类似
            if(pattern[i] == pattern[j])
                Next[i + 1] = j + 1;
            else
                Next[i + 1] = 0;
        }
    };


    //kmp查询匹配
    std::function<void()> kmp = [&]() -> void{
        int j = 0;
        get_Next(p);
        int slen = s.size();
        int plen = p.size();
        for(int i = 0; i < slen; i++){
            while(j && s[i] != p[j])
                j = Next[j];
            if(s[i] == p[j])
                j += 1;
            if(j == plen){
                //匹配成功
                if(i - last >= plen){
                    //匹配不能重叠才用加这个判断
                    count += 1;
                    last = i;
                }
            }
        }
    };

    
#endif