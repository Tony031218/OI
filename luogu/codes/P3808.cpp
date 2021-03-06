/*************************************************************
 *  > File Name        : P3808.cpp
 *  > Author           : Tony
 *  > Created Time     : 2019/05/26 17:52:00
 *  > Algorithm        : [字符串]AC
**************************************************************/

#include <bits/stdc++.h>
using namespace std;

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();}
    while (isdigit(ch))  {x = x * 10 + ch - 48; ch = getchar();}
    return x * f;
}

const int maxn = 1e6 + 10;
char p[maxn];
int n;

struct AC_Automata {
    int ch[maxn][26], val[maxn], fail[maxn], last[maxn], cnt[maxn], nodecnt;
    void init() {
        memset( ch , 0, sizeof( ch ));
        memset(val , 0, sizeof(val ));
        memset(cnt , 0, sizeof(cnt ));
        memset(fail, 0, sizeof(fail));
        memset(last, 0, sizeof(last));
        nodecnt = 0;
    }
    int idx(char c) { return c - 'a'; }
    void insert(char *s) {
        int u = 0, n = strlen(s);
        for (int i = 0; i < n; ++i) {
            int c = idx(s[i]);
            if (!ch[u][c]) ch[u][c] = ++nodecnt;
            u = ch[u][c];
        }
        val[u]++;
    }
    void getFail() {
        queue<int> q; q.push(0);
        while (!q.empty()) {
            int u = q.front(), k = fail[u]; q.pop();
            for (int c = 0; c < 26; ++c) {
                int v = ch[u][c];
                if (!v) { ch[u][c] = ch[k][c]; continue; }
                q.push(v);
                fail[v] = u ? ch[k][c] : 0;
                last[v] = val[fail[v]] ? fail[v] : last[fail[v]];
            }
        }
    }
    int count(char *s) {
        int u = 0, n = strlen(s), res = 0;
        for (int i = 0; i < n; ++i) {
            int c = idx(s[i]);
            u = ch[u][c];
            if (val[u]) res += val[u], val[u] = 0;
            int v = u;
            while (last[v]) {
                v = last[v];
                if (val[v]) res += val[v], val[v] = 0;
            }
        }
        return res;
    }
    // void query(char * T) {
    //     int u = 0, n = strlen(T), res = 0;
    //     for (int i = 0; i < n; ++i) {
    //         int c = idx(T[i]);
    //         u = ch[u][c];
    //         if (val[u]) cnt[val[u]]++;
    //         int v = last[u];
    //         while (v) {
    //             if (val[v]) cnt[val[v]]++;
    //             v = last[v];
    //         }
    //     }
    //     for (int i = 1; i <= m; ++i) res = max(res, cnt[i]);
    //     printf("%d\n", res);
    //     for (int i = 1; i <= m; ++i) if (cnt[i] == res) printf("%s\n", s[i]);
    //     return;
    // }
}AC;

int main() {
    n = read();
    AC.init();
    for (int i = 1; i <= n; ++i) {
        scanf("%s", p);
        AC.insert(p);
    }
    AC.getFail();
    scanf("%s", p);
    printf("%d\n", AC.count(p));
    return 0;
}