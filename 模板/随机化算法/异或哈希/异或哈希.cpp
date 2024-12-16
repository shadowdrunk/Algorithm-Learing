#ifdef ShadowDrunk
//异或哈希，实际上是把一个小范围内的数字通过哈希算法映射到一个很大的值域范围内
//这样使得异或的结果集非常大，从而使得异或哈希之间的冲突概率非常小（注意仍然有可能冲突）
//我们可以粗略的看成从集合中随意的挑选几个数其异或的结果都是不同的
//经常用来处理是否存在组合问题，是否存在出现k次问题，x ^ 2问题
//通常原来的初始值域范围在1e6内是可以接受的

    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    //抄自哥哥的版本随机数生成器
    
    int V = 1e6;    //初始值域范围
    std::vector <ll> val(V + 1, 0); //映射值

    void init(){
        for(int i = 1; i <= V; i++)
            val[i] = rng();
            //val[i] = rng() / k    //计算k次问题时，k进制需要防止溢出
    }

    //k进制的异或
    //二进制的异或实际上是进行mod2，不进位的加法
    //会带来一个lg复杂度
    ll xork(ll a, ll b, ll k) {
        vector<ll> vec;
        while (a || b) {
            vec.push_back((a + b) % k);
            a /= k;
            b /= k;
        }
        ll res = 0;
        ll p = 1;
        for (auto x: vec) {
            res += p * x;
            p *= k;
        }
        return res;
    }
#endif