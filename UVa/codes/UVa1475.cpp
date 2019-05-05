/*************************************************************
 *  > File Name        : UVa1475.cpp
 *  > Author           : Tony
 *  > Created Time     : 2019/05/05 12:52:48
**************************************************************/

#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;     //精度
const double PI  = acos(-1);

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
};
typedef Point Vector;
Vector operator + (Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Vector a, Vector b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, double p) { return Vector(a.x * p, a.y * p); }
Vector operator / (Vector a, double p) { return Vector(a.x / p, a.y / p); }
int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}

bool operator < (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool operator == (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
double Dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double Length(Vector a) { return sqrt(Dot(a, a)); }
double Angle(Vector a, Vector b) { return acos(Dot(a, b) / Length(a) / Length(b)); }
double Cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
double Area2(Point a, Point b, Point c) { return Cross(b - a, c - a); }
double Dist2(const Point& A, const Point& B) { return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y); }
double angle(Vector v) { return atan2(v.y, v.x); }
Vector Normal(Vector a) { double L = Length(a); return Vector(-a.y / L, a.x / L); }
struct Line {
    Point p;
    Vector v;
    double ang;
    Line() {}
    Line(Point p, Vector v): p(p), v(v) { ang = atan2(v.y, v.x); }
    bool operator < (const Line& L) const {
        return ang < L.ang;
    }
    Point point(double t) {
        return p + v * t;
    }
    Line move(double d) {
        return Line(p + Normal(v) * d, v);
    }
};
bool OnLeft(Line L, Point p) { return Cross(L.v, p - L.p) > 0; }
Point GetLineIntersection(Line a, Line b) {
    Vector u = a.p - b.p;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.p + a.v * t;
}

vector<Point> HalfplaneIntersection(vector<Line> L) {
    int n = L.size();
    sort(L.begin(), L.end());
    int first, last;
    vector<Point> p(n);
    vector<Line>  q(n);
    vector<Point> ans;
    q[first = last = 0] = L[0];
    for (int i = 1; i < n; i++) {
        while (first < last && !OnLeft(L[i], p[last - 1])) last--;
        while (first < last && !OnLeft(L[i], p[first]))   first++;
        q[++last] = L[i];
        if (fabs(Cross(q[last].v, q[last - 1].v)) < eps) {
            last--;
            if (OnLeft(q[last], L[i].p)) q[last] = L[i];
        }
        if (first < last) p[last - 1] = GetLineIntersection(q[last - 1], q[last]);
    }
    while (first < last && !OnLeft(q[first], p[last - 1])) last--;
    if (last - first <= 1) return ans;
    p[last] = GetLineIntersection(q[last], q[first]);
    for (int i = first; i <= last; i++) ans.push_back(p[i]);
    return ans;
}

const int maxn = 50010;
int n;
Point p[maxn];

bool check(int mid) {
    vector<Line> L;
    for (int i = 0; i < n; ++i) {
        L.push_back(Line(p[(i + mid + 1) % n], p[i] - p[(i + mid + 1) % n]));
    }
    return HalfplaneIntersection(L).empty();
}

int solve() {
    if (n == 3) return 1;
    int l = 1, r = n - 3, mid;
    while (l < r) {
        mid = l + (r - l) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            p[i] = Point(x, y);
        }
        printf("%d\n", solve());
    }
    return 0;
}