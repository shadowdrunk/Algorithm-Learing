#ifdef ShadowDrunk
//欧拉函数的值是1 <= x <= n中与n互质的x的个数
//注意到在线性筛中，每一个合数都是被最小的质因子筛掉
//时间复杂度为O（n)

    //数据及初始化
    ll n = 100000;
    std::vector<ll> prime;
    std::vector<bool> not_prime(n + 1, false);
    std::vector<ll> phi(n + 1, 0);

    //核心算法
    std::function<void(ll)> euler_pri_phi = [&](ll x) -> void{
        phi[1] = 1;
        for(ll i = 2; i <= n; i++){
            if(!not_prime[i]){
                prime.push_back(i);
                phi[i] = i - 1;
            }
            for(auto pri_j : prime){
                if(i * pri_j > n)
                    break;
                not_prime[i * pri_j] = true;
                if(i % pri_j == 0){
                    //i 包含了 i * pri_j 的所有最小质因数
                    phi[pri_j * i] = phi[i] * pri_j;
                    break;
                }
                //欧拉函数的性质
                phi[i * pri_j] = phi[i] * phi[pri_j];
            }
        }
    };
    euler_pri_phi(n);

#endif