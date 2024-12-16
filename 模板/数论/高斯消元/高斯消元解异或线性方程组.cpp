#ifdef ShadowDrunk
//时间复杂度为O(n ^ 3)
//实际上与高斯消元法思想一样，因为异或满足高斯消元运算所需要的性质
//异或线性方程组指的是系数都是0或1，常数都是0或1，结果都是0或1
//注意实际上异或也可以看作是模2的加法
//必要时候可以使用bitset优化

    //核心数据
    std::vector<std::vector<int>> a;
    int n; //n元
    int m; //m个方程组
    int ans = 0; //有唯一解至少要ans个方程

    //核心算法
    int guess(){

        for(int i = 1; i <= n; i++){
            int max = i;
            while(max <= m && !a[max][i])
                max++;
        
            if(max > m)
                return 0;
            
            ans = std::max(ans, max);

            for(int j = 1; j <= n + 1; j++)
                std::swap(a[i][j], a[max][j]);

            for(int j = 1; j <= m; j++){
                if(j != i){
                    if(a[j][i]){
                        for(int k = 1; k <= n + 1; k++)
                            a[j][k] = a[i][k] ^ a[j][k];
                    }
                        
                }
            }
        }
        
        int key = 1;
        for(int i = 1; i <= n; i++){
            if(!a[i][i]){
                if(a[i][n + 1])    //无解优先级更高
                    key = -1;
                else if(key != -1)
                    key = 0;
            }
        }
        return key;
    }

    //输入与输出
    std::cin >> n >> m;
    a = std::vector<std::vector<int>>(m + 1, std::vector<int>(n + 2));
    for(int i = 1; i <= m; i++){
        std::string s;
        std::cin >> s;
        for(int j = 1; j <= n; j++)
            a[i][j] = s[j - 1] - '0';
        int res;
        std::cin >> res;
        a[i][n + 1] = res;
    }
    


    int key = guess();
    if(key == 1){
        std::cout << ans << endl;
        for(int i = 1; i <= n; i++)
            if(a[i].back() == 0)
                std::cout << "Earth" << endl;
            else
                std::cout << "?y7M#" << endl;
        return;
    }
    else{
        std::cout << "Cannot Determine" << endl;
    }

#endif