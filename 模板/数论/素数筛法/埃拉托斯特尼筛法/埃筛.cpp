#ifdef ShadowDrunk
//时间复杂度为O（nlgn)

    //数据及初始化
    ll n = 100000;
    std::vector<bool> is_prime(n + 1, true);

    //核心算法
    std::function<void(ll)> Eratosthenes = [&](ll x) -> void{
        is_prime[0] = is_prime[1] = false;
        for (ll i = 2; i * i <= x; ++i) {
            if (is_prime[i])
            for (int j = i * i; j <= n; j += i) is_prime[j] = false;
        }
    };
    Eratosthenes(n);

#endif