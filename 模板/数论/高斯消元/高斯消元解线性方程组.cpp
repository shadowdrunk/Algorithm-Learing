#ifdef ShadowDrunk
//使用高斯约旦法进行消元
//时间复杂度为O(n ^ 3)
//注意运算时处理好浮点数的精度问题
//最后的答案如果有解则是一个标准的主对角线外系数全为0的矩阵

    //核心数据
    std::vector<std::vector<double>> a;
    double eps = 1e-7; //精度处理
    int n; //n元与n个方程组

    //核心算法
    int guess(){
        for(int i = 1; i <= n; i++){
            //枚举列
            int max = i;
            //选择最大系数
            for(int j = 1; j <= n; j++){
                //系数唯一对应并且在i之前则跳过
                if(std::abs(a[j][j]) > eps && j < i)
                    continue;
                if(std::fabs(a[j][i]) > std::fabs(a[max][i]))
                    max = j;
            }

            //置换为阶梯矩阵
            for(int j = 1; j <= n + 1; j++)
                std::swap(a[i][j], a[max][j]);

            if(std::fabs(a[i][i]) < eps){
                continue;
            }
            //将这一行主元的系数变为1
            for(int j = n + 1; j >= 1; j--){
                a[i][j] = a[i][j] / a[i][i];
            }
            //将这一列其它的系数置0
            for(int j = 1; j <= n; j++){
                if(j != i){
                    double tmp = a[j][i] / a[i][i];
                    for(int k = 1; k <= n + 1; k++)
                        a[j][k] -= a[i][k] * tmp;
                }
            }
        }
        int key = 1;

        for(int i = 1; i <= n; i++){
            if(std::fabs(a[i][i]) < eps){
                if(std::fabs(a[i][n + 1]) > eps)    //无解优先级更高
                    key = -1;
                else if(key != -1)
                    key = 0;
            }
        }
        return key;
    }

    //输入与输出
    std::cin >> n;
    a = std::vector<std::vector<double>>(n + 1, std::vector<double>(n + 2));
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n + 1; j++)
            std::cin >> a[i][j];

    int key = guess();
    if(key != 1){
        //0是有无穷解，-1是无解
        if(key == 0)
            std::cout << "Infinite group solutions" << endl;
        else
            std::cout << "No solution" << endl;
        return;
    }
    std::cout.precision(2);
    for(int i = 1; i <= n; i++)
        std::cout << std::fixed << a[i][n + 1] << endl;

#endif