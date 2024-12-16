#ifdef ShadowDrunk
//时间复杂度为O(n * m) (n位初始数组元素个数，m为值可能的最高二进制位)
//实际是高斯消元解异或线性方程组的一种运用
//其正确我们可以根据高斯消元的原理而证明，经过变化得到的答案矩阵一定能通过变换回到初始矩阵
//矩阵最后是一个单位矩阵
//所以根据这个性质，我们可以求解第k大的异或和，把第i个线性基当从高往低的第i个二进制位来决定选不选即可
//如1111就是最大异或和，1110就是第二大异或和(1代表第i个线性基参与异或)
//注意该方法的时间复杂度是较大的。

    //核心数据
    std::vector<ll> a;  //存储n个数，Guess后按位看是类似单位矩阵
    int n; //n个数
    bool zero;  //是否有异或和为0的组合

    //核心算法
    void Guess(){
        int k = 1;   //k标记当前是第几行
        for(ll j = (1LL << 62); j; j >>= 1){
            int i = k;
            while(i <= n){
                if(a[i] & j)
                    break;
                i += 1;
            }
            if(i > n)
                continue;   //注意这里还没有改变k
            std::swap(a[i], a[k]);
            for(int z = 1; z <= n; z++)
                if(z != k && a[z] & j)
                    a[z] ^= a[k];
            k += 1;
        }
        k -= 1;
        if(k != n)
            zero = true;
        else 
            zero = false;
        n = k;
    }

    //查询算法
    ll Query(ll k){
        //查询第k小的异或和
        ll ans = 0;
        if(zero)
            k -= 1;
        if(!k)
            return 0;

        for(int i = n; i >= 1; i--){
            if(k & 1)
                ans ^= a[i];
            k >>= 1;
        }
        if(k)
            return -1;
        else
            return ans;
    }

    //输入与初始化
    std::cin >> n;
    a = std::vector<ll>(n + 1, 0);
    for(int i = 1; i <= n; i++)
        std::cin >> a[i];
    Guess();
    
    //多组查询结果
    int q;
    std::cin >> q;
    while(q--){
        int k;
        std::cin >> k;
        std::cout << Query(k) << endl;
    }

#endif