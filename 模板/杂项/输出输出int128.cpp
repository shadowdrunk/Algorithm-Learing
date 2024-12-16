#ifdef ShadowDrunk

__int128 read() {
    char c = getchar();
    __int128 x = 0;
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= !(c ^ 45);
    for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    if (f) x = -x;
    return x;
}

void write(__int128 x, char c = '\0') {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
    if (c != '\0') putchar(c);
}
        
#endif