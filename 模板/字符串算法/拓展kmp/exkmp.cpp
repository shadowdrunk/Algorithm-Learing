#ifdef ShadowDrunk
//时间复杂度O(n + m)
//拓展kmp是kmp匹配思想的一个拓展应用
//其匹配另外一个字符串的思想和求z函数思想类似
//z函数中z[i]的含义是从z[i] 到 z[n]的子串与该字符串的最长公共前缀
//我们实现上通过维护右端点最靠右的匹配区间来进行实现即可达到O(n + m)的线性复杂度
//对于区间l,r中的i其匹配的最少为 std::min(z[i - l], r - i + 1) 
//上面是根据最长公共前缀的性质得到的
//本模板使用的均是0序号字符串

    //核心数据
    std::vector<int> z;
    std::vector<int> extend;

    void z_function(std::string pattern){
        int n = pattern.size();
        int l = -1;
        int r = -1;  //l 和 r 维护右端点最靠右的匹配端
        z = std::vector<int>(n, 0);   //z[i] 表示pattern[i] 到 pattern[n - 1] 与pattern的最长公共前缀
        z[0] = n;
        for(int i = 1; i < n; i++){
            if(i <= r)
                z[i] = std::min(z[i - l], r - i + 1);   //匹配段内对应匹配长度没有超过匹配段
            while(i + z[i] < n && pattern[z[i]] == pattern[i + z[i]])
                z[i] += 1;
            if(i + z[i] - 1 > r){
                l = i;
                r = i + z[i] - 1;
            }
        }
    }

    void ex_kmp(std::string s, std::string p){
        int lens = s.size();
        int lenp = p.size();
        extend = std::vector<int>(lens, 0);
        int l = -1;
        int r = -1;  //和求z函数类似, l 和 r 维护的意义相同
        for(int i = 0; i < lens; i++){
            if(i <= r)
                extend[i] = std::min(z[i - l], r - i + 1);  //注意这里是z[i - l],因为是与p进行匹配
            while(i + extend[i] < lens && extend[i] < lenp && s[i + extend[i]] == p[extend[i]])
                extend[i] += 1;   
            if(i + extend[i] - 1 > r){
                l = i;
                r = i + extend[i] - 1;
            }
        }
    }

    
#endif