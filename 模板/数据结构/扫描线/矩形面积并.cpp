#ifdef ShadowDrunk
//扫描线求矩形面积的并实际上是将矩形重新拆分
//我们从下往上扫描，将进入矩形的边定义为入边，出去矩形的边定义为出边
//我们只用维护某个区间的空（点和点之间形成的线段）的包含入边数即可
//只要某个区间的tag[p]（包含区间数） > 0，那么就计算某个区间的贡献
//我们从第一条边扫到最上面，计算当前存在的重新按y坐标切割的新矩形的面积即可
//注意我们需要对题目的数据进行离散化，因为数字可能很大

    //核心数据
    ll n;
    std::vector<ll> length; //扫描线算法中线段树实际上是维护对应区间中有效总长度
    std::vector<ll> tag;    //标记对应线段是否有效  //注意不同于懒标记，这个是区间的信息
    std::vector<ll> xx;     //存放离散化之后x轴的坐标
    int num;    //记录离散化后下标个数
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
        return a.y < b.y;
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
        //实际上是在维护点之间的空(线段)
        if(tag[p])
            length[p] = xx[pr + 1] - xx[pl];    //第pr到pl个线段
        else if(pl == pr)
            length[p] = 0;  //叶子节点特殊处理
        else
            length[p] = length[ls(p)] + length[rs(p)];
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
        update(L, R, io, 1, 1, num);    //注意这里不是n
    }

    //输入与初始化
    std::cin >> n;
    length = std::vector<ll>(n << 3, 0);    //注意一个矩形两个x坐标
    tag = std::vector<ll>(n << 3, 0);
    xx = std::vector<ll>(n * 2 + 1);
    Line = std::vector<ScanLine>(n * 2 + 1);
    for(int i = 1; i <= n; i++){
        ll x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        Line[i * 2] = ScanLine(y2, x1, x2, -1);
        xx[i * 2] = x2;
        Line[i * 2 - 1] = ScanLine(y1, x1, x2, 1);
        xx[i * 2 - 1] = x1;
    }
    std::sort(xx.begin() + 1, xx.end());
    std::sort(Line.begin() + 1, Line.end(), cmp);   //从下到上扫描
    xx.erase(std::unique(xx.begin() + 1, xx.end()), xx.end());
    num = xx.size() - 1;    //离散化后数的个数

    //计算部分
    //注意线段树维护的含义，所需要对update的特殊调用方式
    ll ans = 0;
    for(int i = 1; i < Line.size(); i++){
        //扫描所有的边
        ans += length[1] * (Line[i].y - Line[i - 1].y);

        int L, R;
        L = std::lower_bound(xx.begin() + 1, xx.end(), Line[i].left_x) - xx.begin();
        R = std::lower_bound(xx.begin() + 1, xx.end(), Line[i].right_x) - xx.begin();
        //L和R是离散化后的下标
        //L点和R点之间的线段实际上是第L到第R - 1段空
        update(L, R - 1, Line[i].inout);
    }
    std::cout << ans << endl;

#endif