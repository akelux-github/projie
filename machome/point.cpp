#include <map>
#include <vector>
using namespace std;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};
    
struct Line {  // A x + B*y = C (A>0, gcd(A,B)=1)  or A=0, B=1, y = C  
  int A;
  int B;
  int C;
  Line (int a, int b, int c) : A(a), B(b), C(c) { }
  bool operator<(const Line& l2) const {
      return A<l2.A || (A==l2.A && B<l2.B) || (A==l2.A && B==l2.B && C<l2.C);
  }
}; 
        
class Solution {

    static int gcd(int a, int b) { // a>0, b>0
        if (a>b) {
            a %= b;
        }
        while (a>0) {
            b %= a;
            if (b==0) {
                return a;
            } else {
                a %= b;
            }
        }
        return b;
    }
    
    static Line computeLine(const Point& p1, const Point& p2) {
        // (x-p1.x)*(p1.y-p2.y) = (y-p1.y)*(p1.x-p2.x)
        int A=p1.y-p2.y;
        if (A == 0) {
            return Line(0, 1, p1.y);
        } else {
            int B= p1.x-p2.x;
            int d = 1;
            if (A>0) {
                d = (B>0)?gcd(A,B):gcd(A,-B);
            } else {
                d = (B>0)?-gcd(-A,B):-gcd(-A,-B);
            }
            A /= d;
            B /= d;
            // A/d*x -B/d*y = p1.x*A/d-p1.y/B/d
            return Line(A, -B, A*p1.x-B*p1.y);
        }
    }
    
    static bool onLine(const Point& p, const Line& l) {
        return l.A*p.x+l.B*p.y == l.C;
    }
    
public:
    int maxPoints(vector<Point> &points) {
        size_t n = points.size();
        std::map<Line, int> line_count;
        for (size_t i = 0; i<n-1; ++i) {
            for (size_t j = i+1; j<n; ++j) {
                line_count.insert(pair<Line, int>(computeLine(points[i], points[j]), 0));
            }
        }
        
        for (size_t i = 0; i<n; ++i) {
            for (std::map<Line, int>::iterator it = line_count.begin(); it!=line_count.end();++it) {
                if (onLine(points[i], it->first)) {
                    ++(it->second);
                }
            }
        }
        
        int max_count = 0;
        for (std::map<Line, int>::iterator it = line_count.begin(); it!=line_count.end();++it) {
                if (it->second>max_count) {
                    max_count = it->second;
                }
        }
        return max_count;
    }
};
