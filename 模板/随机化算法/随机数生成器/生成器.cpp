#ifdef ShadowDrunk
//使用时直接像用rand一样即可

    mt19937 eng(random_device{}()); //返回值是unsigned int,区间范围为[0 ,4e9],即 UINT32_MAX
    mt19937_64 eng64(random_device{}()); //返回值是unsigned long long,范围更大, UINT64_MAX

    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    //同上，这个是抄自哥哥的版本
    
#endif