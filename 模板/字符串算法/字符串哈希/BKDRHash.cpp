#ifdef ShadowDrunk
//实际上是字符串的进制哈希
//经常使用的哈希进制是31，131，1313，13131，131313等
//有小概率可能出现哈希冲突
//实现时直接使用ull自动上溢出，避免低效率的取模运算
//被卡可以尝试模数哈希或是双值哈希
//模数哈希即为一个base，和一个mod，不使用自然溢出，通过取模运算判断哈希
//双值哈希则为一个base，两个mod，计算时算两个mod意义下的hash，只要有一个不同就不同
//常用mod 1e9 + 7, 998244353, 212370440130137957

    //核心算法，获取字符串哈希值
    ull BKDRHash(std::string& s){
        ull P = 131;
        ull H = 0;
        int n = s.size();
        for(int i = 0; i < s.size(); i++)
            H = H * P + s[i] - 'a' + 1; //注意这里暗含了ull的上溢出，实际等同于取模
        return H;
    }

    //获取子串哈希预处理
    for(int i = 1; i <= n; i++)
        P[i] = P[i - 1] * PP;
    for(int i = 1; i <= n; i++)
        H[i] = H[i - 1] * PP + s[i];

    //获取子串的哈希
    ull get_hash(ull L, ull R){
        return H[R] - H[L - 1] * P[R - L + 1];
    }
    
#endif