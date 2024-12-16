#ifdef ShadowDrunk
//本模板为Dinic算法实现
//使用当前弧优化，奇偶边优化
//使用链式向前星进行建图
//理论时间复杂度最坏O(n ^ 2 * m)
//其实现的一个基本思路是图的总流量只会因为找到其残留网络中的增广路而增大
//所以实际上最朴素的Edmonds-Karp算法就是使用bfs找最短增广路知道图中不存在这增广路
//而dinic算法在Edmonds-Karp的基础上进行优化，使用bfs分层，再dfs
//bfs分层确保dfs的过程中走的都是最短增广路的路径，而dfs可能可以一次找到多条增广路径
//一张图中我们其增广路径最多只有n * m条
//我们每次bfs + dfs最少也会找到一条

//核心数据
const int N = 250;
const int M = 11000;    //双向边需要开两倍
const ll INF = 1e9;
int n, m;   //记录实际点和边的信息
int s, t;   //记录源点和汇点
int cnt = 1;    //使用奇偶边进行优化双向边，起始位置不能是0
int head[N];
struct {
    int to;
    int nex;
    int w;
}e[M];

//链式向前星建边
void add(int u, int v, int w){
    cnt++;
    e[cnt].to = v;
    e[cnt].w = w;
    e[cnt].nex = head[u];
    head[u] = cnt;
}

int now[N];     //当前弧优化
int dep[N];     //记录分层图的深度
int bfs(){
    for(int i = 1; i <= n; i++)
        dep[i] = INF;
    dep[s] = 0;
    now[s] = head[s];   //当前弧优化，now是head的副本
    std::queue<int> que;
    que.push(s);
    while(!que.empty()){
        int u = que.front();
        que.pop();
        for(int i = head[u]; i > 0; i = e[i].nex){
            int v = e[i].to;
            if(e[i].w > 0 && dep[v] == INF){
                que.push(v);
                now[v] = head[v];   //完成对now的拷贝
                dep[v] = dep[u] + 1;
                if(v == t)
                    return 1;   //立即返回，bfs分层需要保证dfs搜索的都是边数最少的最短路径
                //实际上这里与Edmonds-Karp算法很想，但应为dfs，可能一次确定多条增广路
            }
        }
    }
    return 0;   //无法到达说明t不在残留网络中，不存在增广路
}

int dfs(int u, ll sum){
    if(u == t)
        return sum;     //sum此时就是当前路径对最大流的贡献
    ll k = 0;   //k是当前最小的剩余容量
    ll flow = 0;    //flow表示经过该点的所有流量和
    for(int i = now[u]; i > 0 && sum > 0; i = e[i].nex){
        now[u] = i; //注意这里的遍历和更改，应为dfs的性质，不用考虑当前i之前的点
        int v = e[i].to;
        if(e[i].w > 0 && (dep[v] == dep[u] + 1)){
            //使用dep限制只能访问下一层
            k = dfs(v, std::min(sum, (ll)e[i].w));
            if(k == 0)
                dep[v] = INF;   //剪枝，此时从此点到t的路劲已经增广完毕
            e[i].w -= k;    //更新残留网络
            e[i ^ 1].w += k;    //建边时的奇偶边技巧
            flow += k;
            sum -= k;   //sum表示经过该点的剩余流量
        }
    }
    return flow;
}

//调用方式
std::cin >> n >> m >> s >> t;
for(int i = 1; i <= m; i++){
    int u, v, w;
    std::cin >> u >> v >> w;
    add(u, v, w);
    add(v, u, 0);   //建立反向边，初始容量为0
}
ll ans = 0;
while(bfs()){   //一直查找知道不存在增广路
    ans += dfs(s, INF); //源点容量视作INF
}
std::cout << ans << endl;

#endif