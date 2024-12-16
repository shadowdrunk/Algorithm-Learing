#ifdef ShadowDrunk
//建树时间复杂度O(n * maxn) 查询时间复杂度O（maxn）
//字典树的衍生用法实际上是把数字变成二进制当字符串处理
//可以方便我们贪心的匹配每个位
//常用于寻找最大异或结果的两个元素或最小异或结果的两个元素
//也可以通过记录其它变量完成更多操作

const int N = 3e6 + 10;

struct trie_node{
    int son[2];    //子节点
}trie[N];

int maxn = 30;   //最大位
int cnt = 1;    //当前分配的空间位置，0节点留给根节点

void Insert(int val){
    int now = 0;
    for(int i = maxn; i >= 0; i--){
        int ind = (val >> i) & 1;   //从高到低同一长度的处理每个数字
        if(trie[now].son[ind] == 0)
            trie[now].son[ind] = cnt++;  //分配位置，并更新空间指针
        now = trie[now].son[ind];   
    }
}

int Find(int val){  //找到异或结果最大的两个元素
    int now = 0;
    int res = 0;
    for(int i = maxn; i >= 0; i--){
        int ind = (val >> i) & 1;  
        if(trie[now].son[!ind] != 0){   //尽可能找不同的位置
            now = trie[now].son[!ind];
            res |= ((!ind) << i);
        }
        else if(trie[now].son[ind] != 0){
            now = trie[now].son[ind];
            res |= (ind << i);
        }
    }
    return val ^ res;   //返回的就是当前位置匹配的最大的异或的结果
}
    
#endif