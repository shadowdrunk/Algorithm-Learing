#ifdef ShadowDrunk

template <class T>
T gcd(T a, T b){
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
template <class T>
T lcm(T a, T b){
    return (a * b) / gcd(a, b);
}

#endif