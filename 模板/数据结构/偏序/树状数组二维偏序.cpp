#ifdef ShadowDrunk
//二维偏序问题形象来说就是统计一个二维坐标系矩形中点的个数
//只要是符合偏序定义的二维偏序问题就可以通过这样的思路来进行求解
//实际上是通过合理的排序使得题目的二维偏序问题变成一维偏序问题
//实际上可以通过二维前缀和的思想转换成基于四个点的或基于两条边的偏序问题
//这里使用的是类似于扫描线思想的两条边的拆分方式
//按x从左往右进行扫描，我们动态加入点（将所有点按x排序）
//对于一个矩形其中点的个数就是其右边的边到x最小位置y范围内包含点的数减去左边的边左移一个单位包含的个数
//实际只用一个单点修改区间查询的数据结构即可维护

    //树状数组
    ll n;
    std::vector<ll> tree;
    ll lowbit(ll x){
        return (-x) & x;
    }
    void update(ll x, ll d){
        while(x <= n){
            tree[x] += d;
            x += lowbit(x);
        }
    }
    ll sum(ll x){
        ll ans = 0;
        while(x > 0){
            ans += tree[x];
            x -= lowbit(x);
        }
        return ans;
    }

    //边数据
    std::vector<ll> yy; //存放y坐标离散化后的结果
    struct edge{
        ll x;
        ll high_y, low_y;
        int inout;  //出边为1,加入答案中,入边为-1,减去答案中
        int ind;
        edge(){}
        edge(ll x_, ll ly, ll hy, int id, int io) : 
            x(x_), low_y(ly), high_y(hy), ind(id), inout(io){}
    };
    bool cmp(edge& a, edge& b){
        return a.x < b.x;
    }

    //输入与初始化
    int np;
    std::cin >> np;
    int m;
    std::cin >> m;
    std::vector<std::pair<ll, ll>> point(np + 1);
    yy = std::vector<ll>(1, 0); //保证1序
    for(int i = 1; i <= np; i++){
        std::cin >> point[i].ff >> point[i].ss;
        yy.push_back(point[i].ss);
    }
    std::sort(point.begin(), point.end()); //point按左端点排序

    std::vector<ll> ans(m + 1, 0);
    std::vector<edge> ask(m * 2 + 1);   //将矩形像扫描线一样按边拆分
    for(int i = 1; i <= m; i++){
        ll x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        yy.push_back(y1);
        yy.push_back(y2);
        ask[i * 2] = edge(x2, y1, y2, i, 1);
        ask[i * 2 - 1] = edge(x1 - 1, y1, y2, i, -1);   //注意根据前缀和的计算方式，这里是x1 - 1
    }
    std::sort(yy.begin() + 1, yy.end());
    yy.erase(std::unique(yy.begin() + 1, yy.end()), yy.end());
    n = yy.size();
    tree = std::vector<ll>(n + 1, 0);  //开y坐标离散化后的大小即可

    std::sort(ask.begin() + 1, ask.end(), cmp);

    //扫描与计算答案
    int now_p = 1;
    for(int i = 1; i < ask.size(); i++){
        //向扫描线一样扫过去
        ll x = ask[i].x;
        while(now_p <= np && point[now_p].ff <= x){
            ll pos = std::lower_bound(yy.begin() + 1, yy.end(), point[now_p].ss) - yy.begin();
            update(pos, 1);
            now_p += 1;
        }
        ll h_y = std::lower_bound(yy.begin() + 1, yy.end(), ask[i].high_y) - yy.begin();
        ll l_y = std::lower_bound(yy.begin() + 1, yy.end(), ask[i].low_y) - yy.begin();
        ll val = sum(h_y) - sum(l_y - 1);
        ans[ask[i].ind] += (ask[i].inout == 1 ? val : -val);
    }

#endif