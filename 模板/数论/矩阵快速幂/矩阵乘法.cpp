#ifdef ShadowDrunk
//矩阵乘法快速幂只能用于自乘
//时间复杂度为O(N ^ 3 * lg n)
//常用于将一些线性关系的dp转移进行优化到lg级别
//实现用的数组，别忘了memset

    const int N = 3;
    const ll mod = 19260817;

    struct matrix{
        ll m[N][N]; //注意此处实现用的数组，写时别忘了memset
    };
    void show(matrix a){
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                std::cout << a.m[i][j] << sendl[j == N - 1];
    }

    matrix operator * (const matrix& a, const matrix& b){
        matrix c;
        std::memset(c.m, 0, sizeof(c.m));
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                for(int k = 0; k < N; k++)
                    c.m[i][j] = (c.m[i][j] + a.m[i][k] * b.m[k][j] % mod) % mod;
        return c;
    }

    matrix pow_matrix(matrix a, int n){
        matrix ans;
        std::memset(ans.m, 0, sizeof(ans.m));
        for(int i = 0; i < N; i++)
            ans.m[i][i] = 1;
        while(n){
            if(n % 2 == 1)
                ans = ans * a;
            a = a * a;
            n /= 2;
        }
        return ans;
    }

#endif