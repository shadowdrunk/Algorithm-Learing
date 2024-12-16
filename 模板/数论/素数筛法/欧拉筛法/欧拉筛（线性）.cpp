#ifdef ShadowDrunk
//时间复杂度为O（n)

    //数据及初始化
    int N = 1e5 + 10;
    std::vector<int> prime;
    std::vector<bool> not_prime(N + 1, false);
    not_prime[1] = true;
    //核心算法
    std::function<void()> euler_pri = [&]() -> void{
        for(int i = 2; i <= N; i++){
            if(!not_prime[i])
                prime.push_back(i);
            for(auto pri_j : prime){
                if(i * pri_j > N)
                    break;
                not_prime[i * pri_j] = true;
                //i % pri_j == 0
                //换言之，i 之前被 pri_j 筛过了
                //由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定会被
                // pri_j 的倍数筛掉，就不需要在这里先筛一次
                if(i % pri_j == 0)
                    break;
            }
        }
    };
    euler_pri();

    //外置版本
    void init(){
        not_prime[1] = true;
        std::function<void()> euler_pri = [&]() -> void{
            for(int i = 2; i <= N; i++){
                if(!not_prime[i])
                    prime.push_back(i);
                for(auto pri_j : prime){
                    if(i * pri_j > N)
                        break;
                    not_prime[i * pri_j] = true;
                    //i % pri_j == 0
                    //换言之，i 之前被 pri_j 筛过了
                    //由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定会被
                    // pri_j 的倍数筛掉，就不需要在这里先筛一次
                    if(i % pri_j == 0)
                        break;
                }
            }
        };
        euler_pri();
    }

#endif