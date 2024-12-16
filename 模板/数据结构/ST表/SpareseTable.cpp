#ifdef ShadowDrunk
//ST表基于倍增原理，可以用来处理覆盖性问题，如RMQ，GCD
//初始化时间复杂度nlg(n)
//查询复杂度O（1）
//该模板是一个类，使用时要先初始化一个对象
template <typename T>
class SpareseTable{
private:

    using func_type = std::function<T(const T &, const T &)>;
    //ST[i][j]代表从i到i + (1 << j) - 1的区间   （共（i << j）个元素
    std::vector<std::vector<T>> ST;
    //静态比较函数
    static T default_func(const T &t1, const T &t2){ return std::max(t1, t2); }
    func_type Shadow;

public:

    SpareseTable(const std::vector<T> &cur, func_type _func = default_func){
        Shadow = _func;
        int len = cur.size();
        int l1 = std::ceil(std::__lg(len)) + 1;
        //长度对应的二进制的第一个位置加一
        ST.assign(len, std::vector<T>(l1, 0));
        //注意该ST表序号从0开始
        for(int i = 0; i < len; i++){
            ST[i][0] = cur[i];
        }

        for(int j = 1; j < l1; j++){
            int pj = (1 << (j - 1));
            for(int i = 0; i + pj < len; i++){
                ST[i][j] = Shadow(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
                //从前两个区间中递推出当前区间的结果
            }
        }
    }

    T query(int l, int r){
        int lt = r - l + 1;
        int q = std::floor(std::__lg(lt));
        //中间元素的lg，确保一定能覆盖半个区间及以上
        return Shadow(ST[l][q], ST[r - (1 << q) + 1][q]);
    }

};

#endif