#ifdef ShadowDrunk
//时间复杂度O(m) m为字符串长度
//实质上类似查字典的过程，我们可以快速的从多个字符串中查询某个字符串是否存在
//也可以通过记录其它变量完成更多操作

const int N = 8e6 + 10; //总节点数n * m * 26    //开的是满的静态数组

struct trie_node{
    bool repeat;    //是否重复
    int son[26];    //子节点
    int num;    //前缀的出现次数
    bool isend;     //是否是单词的结尾
}trie[N];

int cnt = 1;    //当前分配的空间位置，0节点留给根节点

void Insert(std::string s){
    int now = 0;
    for(int i = 0; i < s.size(); i++){
        int ch = s[i] - 'a';
        if(trie[now].son[ch] == 0)
            trie[now].son[ch] = cnt++;  //分配位置，并更新空间指针
        now = trie[now].son[ch];
        trie[now].num += 1;     //出现次数加一
        if(i == s.size() - 1)   //单词结尾标记
            trie[now].isend = true;  
    }
}

int Find(std::string s){
    int now = 0;
    for(int i = 0; i < s.size(); i++){
        int ch = s[i] - 'a';
        if(trie[now].son[ch] == 0)  //找不到对应字符串
            return 3;
        now = trie[now].son[ch];
    }
    if(trie[now].isend == false)    //不是单词结尾
        return 3;
    if(trie[now].repeat == false){  //第一次点名
        trie[now].repeat = true;
        return 1;
    }
    return 2;   //重复点名
    //return trie[now].num;     //返回以s为前缀的单词数量
}
    
    //例题构建字典树与查询
    void solve(){
        int n;
        std::cin >> n;
        std::vector<std::string> cur(n);
        for(auto& s : cur)
            std::cin >> s;
        for(auto& s : cur)
            Insert(s);
        int q;
        std::cin >> q;
        while(q--){
            std::string s;
            std::cin >> s;
            int res = Find(s);
            if(res == 1)
                std::cout << "OK" << endl;
            else if(res == 2)
                std::cout << "REPEAT" << endl;
            else if(res == 3)
                std::cout << "WRONG" << endl;
        }
    }
    
#endif