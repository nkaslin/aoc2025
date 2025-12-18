#include "template.h"
#define int long long
auto parse2 = [](const string& s) {
    long long x, y;
    const char* p = s.c_str();
    x = strtol(p, (char**)&p, 10); ++p;
    y = strtol(p, nullptr, 10);
    return tuple{x, y};
};

struct Point {
    int x {};
    int y {};
};

bool operator==(const Point& p1, const Point& p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v) {
    int n = v.size();
    for (int i=0; i<n-1; i++) {
        os << v[i] << " ";
    }
    os << v.back();
    return os;
}

// bool ccw(Point& A, Point& B, Point& C) {
//     return (C.y-A.y) * (B.x-A.x) > (B.y-A.y) * (C.x-A.x);
// }

// bool intersect(Point& A, Point& B, Point& C, Point& D) {
//     return (ccw(A, C, D) != ccw(B, C, D)) && (ccw(A, B, C) != ccw(A, B, D));
// }

int orientation(const Point& p, const Point& q, const Point& r) {
    long long val = (q.y - p.y) * (r.x - q.x)
                  - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;        // collinear
    return (val > 0) ? 1 : 2;      // clockwise or counterclockwise
}

bool onSegment(const Point& p, const Point& q, const Point& r) {
    return q.x >= std::min(p.x, r.x) && q.x <= std::max(p.x, r.x) &&
           q.y >= std::min(p.y, r.y) && q.y <= std::max(p.y, r.y);
}

bool intersect(
    const Point& A, 
    const Point& B,
    const Point& C, 
    const Point& D
) {

    int o1 = orientation(A, B, C);
    int o2 = orientation(A, B, D);
    int o3 = orientation(C, D, A);
    int o4 = orientation(C, D, B);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special collinear cases
    if (o1 == 0 && onSegment(A, C, B)) return true;
    if (o2 == 0 && onSegment(A, D, B)) return true;
    if (o3 == 0 && onSegment(C, A, D)) return true;
    if (o4 == 0 && onSegment(C, B, D)) return true;

    return false;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");
    

    string line;
    vector<Point> points;
    while (getline(fin, line)) {
        auto [x, y] = parse2(line);
        Point p = Point(x, y);
        points.push_back(p);
    }

    // cout << points << endl;

    int n = points.size();
    int res = 0;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            Point c1 = Point(points[i].x, points[i].y);
            Point c2 = Point(points[i].x, points[j].y);
            Point c3 = Point(points[j].x, points[i].y);
            Point c4 = Point(points[j].x, points[j].y);

            bool inside = true;
            for (int k=0; k<n; k++) {
                Point p1 = points[k], p2 = points[(k+1)%n];
                if (c1 != p1 && c2 != p1 && c1 != p2 && c2 != p2) {
                    if (intersect(c1, c2, p1, p2)) {
                        inside = false;
                        break;
                    }
                }
                if (c1 != p1 && c3 != p1 && c1 != p2 && c3 != p2) {
                    if (intersect(c1, c3, p1, p2)) {
                        inside = false;
                        break;
                    }
                }
                if (c4 != p1 && c2 != p1 && c4 != p2 && c2 != p2) {
                    if (intersect(c4, c2, p1, p2)) {
                        inside = false;
                        break;
                    }
                }
                if (c4 != p1 && c2 != p1 && c4 != p2 && c2 != p2) {
                    if (intersect(c4, c2, p1, p2)) {
                        inside = false;
                        break;
                    }
                } 
            }
            if (inside) {
                int area = (abs(c1.x-c3.x) + 1) * (abs(c1.y-c2.y) + 1);
                res = max(res, area);
                // cout << area << " " << c1 << " " << c4 << endl; 
            }
        }
    }

    // Point A = Point(1,1), B = Point(1,3), C = Point(0, 2), D = Point(1,2);
    // cout << intersect(A, B, C, D) << endl;

    // int x = 3;
    // float y = (float) x;
    // cout << y << endl;

    fout << res << '\n';
    return 0;
}
