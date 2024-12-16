#ifdef ShadowDrunk
//扫描线求矩形周长，如果只考虑扫描方向的线，每次加上与上次的变化大小即可
//所以一种解法是可以通过做两次扫描线来得到答案
//这里使用的是在扫描横线的同时维护有几段有效线段的一次扫描解法
//于维护矩形面积并一样，我们线段树中实际上维护的是点与点之间的线段
//模板题的数据范围不大我们直接线段树维护下标即可
//注意对于有效线段数的计算和合并，其余大致与维护矩形面积并相同
//注意这里排序方式y相同时需要优先处理入边

    //核心数据
    ll n;
    std::vector<ll> num;    //存储对应区间中有多少条有效的边
    std::vector<ll> length; //扫描线算法中线段树实际上是维护对应区间中有效总长度
    std::vector<ll> tag;    //标记对应线段是否有效  //注意不同于懒标记，这个是区间的信息
    std::vector<bool> lbd;  //左端点是否被覆盖
    std::vector<bool> rbd;  //右端点是否被覆盖
    ll minn_bd; //最左边的x位置 //这里线段树维护的不是1到n
    ll maxn_bd; //最右边的x位置
    struct ScanLine{
        ll y;
        ll left_x, right_x;
        int inout;  //入边为1，出边为-1
        ScanLine(){}
        ScanLine(ll y_, ll xl, ll xr, int io) : 
            y(y_), left_x(xl), right_x(xr), inout(io){}
    };
    std::vector<ScanLine> Line;
    bool cmp(ScanLine& a, ScanLine& b){
        if(a.y != b.y)
            return a.y < b.y;
        return a.inout > b.inout;   //注意y轴相同时需要优先处理入边（否则矩形重叠时会出错）
    }

    //线段树维护部分    //注意我们只需要区间修改和总区间查询
    ll ls(ll p){
        return p << 1;
    }
    ll rs(ll p){
        return p << 1 | 1;
    }
    void push_up(ll p, int pl, int pr){
        //注意扫描线的维护方式
        //维护周长并数据比较小，我们直接维护下标即可
        if(tag[p]){
            lbd[p] = rbd[p] = true;
            length[p] = pr - pl + 1;    //注意这里要用这样的计算方式，否则线段树维护时单独的点会计算成0
            num[p] = 1; //一条有效的边
        }
        else if(pl == pr){
            //叶子节点
            lbd[p] = rbd[p] = false;
            length[p] = num[p] = 0;
        }
        else{
            length[p] = length[ls(p)] + length[rs(p)];
            lbd[p] = lbd[ls(p)];
            rbd[p] = rbd[rs(p)];
            num[p] = num[ls(p)] + num[rs(p)];
            if(lbd[rs(p)] && rbd[ls(p)])    //合并边
                num[p] -= 1;
        }
    }
    void update(ll L, ll R, int io, ll p, ll pl, ll pr){
        if(L <= pl && pr <= R){
            tag[p] += io;   //根据出入边修改标记
            push_up(p, pl, pr);
            return;
        }
        
        ll mid = (pl + pr) >> 1;
        if(L <= mid)
            update(L, R, io, ls(p), pl, mid);
        if(R > mid)
            update(L, R, io, rs(p), mid + 1, pr);
        push_up(p, pl, pr);
    }
    void update(ll L, ll R, int io){
        //因为周长一个点是没有意义的，所以我们不需要维护一个点
        //为了方便计算和维护，我们的边的right_x都会做减一处理
        //主要是取消了单独的点的影响
        update(L, R, io, 1, minn_bd, maxn_bd - 1);    //注意这里是minn_bd, maxn_bd - 1
    }
    
    //输入与初始化
    std::cin >> n;
    Line = std::vector<ScanLine>(n * 2 + 1);
    maxn_bd = INT_MIN;
    minn_bd = INT_MAX;
    for(int i = 1; i <= n; i++){
        ll x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        Line[i * 2] = ScanLine(y2, x1, x2, -1);
        Line[i * 2 - 1] = ScanLine(y1, x1, x2, 1);
        maxn_bd = std::max(maxn_bd, x2);
        minn_bd = std::min(minn_bd, x1);
    }
    std::sort(Line.begin() + 1, Line.end(), cmp);
    ll last = 0;
    ll ans = 0;
    int sz = maxn_bd - minn_bd;
    length = std::vector<ll>(sz << 2);
    tag = std::vector<ll>(sz << 2);
    num = std::vector<ll>(sz << 2);
    lbd = std::vector<bool>(sz << 2);
    rbd = std::vector<bool>(sz << 2);

    //维护与计算答案
    for(int i = 1; i < Line.size(); i++){
        //注意这里update的维护方式可以理解为直接维护长度（或者说也是点与点之间的线段）
        if(Line[i].left_x < Line[i].right_x)    //按理来说不应该存在这样的矩形
            update(Line[i].left_x, Line[i].right_x - 1, Line[i].inout); //注意为了维护距离直接使用right_x - 1
        
        if(i != Line.size() - 1)
            ans += num[1] * 2 * (Line[i + 1].y - Line[i].y);    //计算竖线的影响
        ans += std::abs(length[1] - last);
        last = length[1];
    }
    std::cout << ans << endl;

#endif