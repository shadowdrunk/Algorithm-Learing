#ifdef ShadowDrunk
//欧拉函数的值是1 <= x <= n中与n互质的x的个数
//注意1的欧拉函数值为1
//本模板是根据分解定理来求欧拉函数的，实现上需要对数字进行一个素数拆分
//时间复杂度为O（n ^ 0.5)

    //核心算法
    std::function<ll(ll)> euler_phi = [&](ll x) -> ll{
        ll ans = x;
        for(ll i = 2; i * i <= x; i++){
            if(x % i == 0){
                ans = ans / i * (i - 1);    //分解定理
                while(x % i == 0){  //素数拆分
                    x = x / i;
                }
            }
        }
        if(x > 1)
            ans = ans / x * (x - 1);
        return ans;
    };

#endif