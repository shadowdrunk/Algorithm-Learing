#ifdef ShadowDrunk

template<class T>
class LazySegmentTree{

    std::vector<T> tree;
    std::vector<T> tag;
    std::vector<T> arr;
    T n;

    T ls(T p){
        return p << 1;
    }
    T rs(T p){
        return p << 1 | 1;
    }

    void push_up(T p){
        tree[p] = tree[ls(p)] + tree[rs(p)];
    }

    void build(T p, T pl, T pr){
        if(pl == pr){
            tree[p] = arr[pl]; 
            return;
        }
        T mid = (pl + pr) >> 1; 
        build(ls(p), pl, mid);  
        build(rs(p), mid + 1, pr);  
        push_up(p); 
    }   

    void addtag(T p, T pl, T pr, T d){
        tag[p] += d;
        tree[p] += d * (pr - pl + 1);
    }

    void push_down(T p, T pl, T pr){
        if(tag[p]){
            T mid = (pr + pl) >> 1;
            addtag(ls(p), pl, mid, tag[p]);
            addtag(rs(p), mid + 1, pr, tag[p]);
            tag[p] = 0;
        }
    }

    void update(T L, T R, T p, T pl, T pr, T d){
        if(L <= pl && pr <= R){
            addtag(p, pl, pr, d);
            return;
        }
        push_down(p, pl, pr);
        T mid = (pl + pr) >> 1;
        if(L <= mid)
            update(L, R, ls(p), pl, mid, d);
        if(R > mid)
            update(L, R, rs(p), mid + 1, pr, d);
        push_up(p);
    }

    T query(T L, T R, T p, T pl, T pr){
        if(L <= pl && pr <= R)
            return tree[p];
        push_down(p, pl, pr);
        T mid = (pl + pr) >> 1;
        T res = 0;
        if(L <= mid)
            res += query(L, R, ls(p), pl, mid);
        if(R > mid)
            res += query(L, R, rs(p), mid + 1, pr);
        return res;
    }

public:
    explicit LazySegmentTree(std::vector<T>& cur){
        n = cur.size();
        n -= 1; //cur是1开头的序列
        tree = std::vector<T>(n << 2);
        tag = std::vector<T>(n << 2);
        arr = std::vector<T>(n + 1);
        for(T i = 1; i <= n; i++)
            arr[i] = cur[i];
        build(1, 1, n);
    }

    T query(T L, T R){
        return query(L, R, 1, 1, n);
    }
    
    void update(T L, T R, T d){
        update(L, R, 1, 1, n, d);
    }
};

#endif