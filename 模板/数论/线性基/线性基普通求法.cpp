#ifdef ShadowDrunk
//时间复杂度O(n * m)
//m是答案可能的最大的值的二进制位数
//线性基实际上是把n个数异或的结果转换为了m个位数不同的数的异或的结果
//可以把证n个数自由组合的异或结果和这m个数自由组合异或的结果的集合完全相同
//实际上是基于上述线性基特性的一个位运算构造，如果出现了同样位数的数，就将那个数转换为 p[i] ^ x
//不难证明{p[i], x} 与 {p[i], p[i] ^ x}，自由组合异或的结果的集合是相同的
//到最后如果0位也没有找到空就不用管了，按上述定理递推可以发现，只是有了可以异或得到0的组合

    //核心数据
    int M = 62; //数据范围的最大位数
    std::vector<ll> p;    //线性基
    bool zero;  //有异或和为0的组合

    //核心算法
    void Insert(ll x){
        for(int i = M; i>= 0; i--){
            if(x & (1LL << i)){
                //确定当数的位数
                if(p[i] == 0){
                    p[i] = x;
                    return;
                }
                else
                    x ^= p[i];
            }
            zero = true;    //到达0位置还没return说明有异或和为0的组合
        }
    }

    //初始化及输入输出
    int n;
    std::cin >> n;
    zero = false;
    p = std::vector<ll>(M + 1, 0);
    for(int i = 1; i <= n; i++){
        ll x;
        std::cin >> x;
        Insert(x);
    }

    //计算最大异或和
    ll ans = 0;
    for(int i = M; i >= 0; i--)
        ans = std::max(ans, ans ^ p[i]);    //顺着贪心，如果能使答案变大就进行异或

    //计算最小异或和
    ll ans;
    if(zero){
        ans = zero;
    }
    else{
        for(int i = 0; i <= M; i++)
            if(p[i] != 0){
                ans = p[i];
                break;
            }
    }

#endif