/*
url: https://leetcode.cn/problems/exam-room/description/?envType=daily-question&envId=2024-12-23
参考: https://leetcode.cn/problems/exam-room/solutions/2037447/by-lcbin-tstp/
      https://leetcode.cn/problems/exam-room/solutions/2036518/kao-chang-jiu-zuo-by-leetcode-solution-074y/
标签: 懒惰删除
*/
#include <bits/stdc++.h>

using namespace std;

// 我的解法，通过，539ms，seat要顺序找一遍，复杂度太高
/* class ExamRoom {
public:
    int n;
    set<int> positions;

    ExamRoom(int n) : n(n) {
    }
    
    int seat() {
        if (positions.size() == 0) {
            positions.insert(0);
            return 0;
        }
        int pos = -1;
        int dis = -1;
        auto it = positions.begin();
        if (*positions.begin() - 0 > dis) {
            pos = 0;
            dis = *it - 0;
        }
        while (std::next(it) != positions.end()) {
            int cur = *it;
            int next = *std::next(it);
            if ((next - cur) / 2 > dis) {
                dis = (next - cur) / 2;
                pos = (next + cur) / 2;
            }
            it++;
        }
        if (n - 1 - *std::prev(positions.end()) > dis) {
            pos = n - 1;
            dis = n - 1 - *std::prev(positions.end());
        }
        positions.insert(pos);
        return pos;
    }
    
    void leave(int p) {
        positions.erase(p);
    }
}; */


/*
参考<https://leetcode.cn/problems/exam-room/solutions/2037447/by-lcbin-tstp/>
既然seat时要找最长区间，直接用set组织区间以更快地查找最长区间，并通过left和right维护左右端点以分裂和合并区间。用时28ms
*/
class ExamRoom1 {
public:
    int n;
    // 这里set作为成员变量，自定义比较器时又需要用到成员变量n，得在初始化列表里写lambda，然后这里要用std::function声明类型
    set<pair<int, int>, std::function<bool(const pair<int, int>& x, const pair<int, int>& y)>> set; // 区间
    unordered_map<int, int> left; // left[x]表示x左侧最靠近的坐人座位
    unordered_map<int, int> right;

    ExamRoom1(int n) : n(n), set(
        [&](const pair<int, int>& x, const pair<int, int>& y) {
            auto dist = [&](const pair<int, int>& p) {
                int l = p.first;
                int r = p.second;
                if (l == -1 || r == this->n) return r - l - 1; // 注意这里要写this->n而不是n，否则捕获局部变量去了，在其它函数中用set会导致问题
                else return (r - l) / 2;
            };

            int d1 = dist(x);
            int d2 = dist(y);
            return d1 == d2 ? x.first < y.first : d1 > d2;
        })
    {
        // 不在初始化列表中初始化set，这样也行
        /* auto comp = [&](const pair<int, int>& x, const pair<int, int>& y) {
            auto dist = [&](const pair<int, int>& p) {
                int l = p.first;
                int r = p.second;
                if (l == -1 || r == this->n) return r - l - 1; // 注意这里要写this->n而不是n，否则捕获局部变量去了，在其它函数中用set会导致问题
                else return (r - l) / 2;
            };

            int d1 = dist(x);
            int d2 = dist(y);
            return d1 == d2 ? x.first < y.first : d1 > d2;
        };
        std::set<pair<int, int>, std::function<bool(const pair<int, int>& x, const pair<int, int>& y)>> set2(comp);
        set = set2; */

        add({-1, n});
        this->n = n;
    }
    
    int seat() {
        auto pair = *set.begin();
        int pos = -1;
        // 选首位的两种情况
        if (pair.first == -1) {
            pos = 0;
        }
        else if (pair.second == n) {
            pos = n - 1;
        }
        else pos = (pair.first + pair.second) / 2;

        // 先del再add，左中右三个端点的left，right信息会是正确的
        del(pair);
        add({pair.first, pos});
        add({pos, pair.second});
        return pos;
    }
    
    void leave(int p) {
        int l = left[p];
        int r = right[p];
        del({l, p});
        del({p, r});
        add({l, r});
    }

    void del(pair<int, int> p) {
        set.erase(p);
        left.erase(p.second);
        right.erase(p.first);
    }

    void add(pair<int, int> p) {
        set.insert(p);
        left[p.second] = p.first;
        right[p.first] = p.second;
    }
};

struct Comp {
    bool operator()(const pair<int, int>& x, const pair<int, int>& y) const {
        int d1 = (x.second - x.first) / 2;
        int d2 = (y.second - y.first) / 2;
        return d1 == d2 ? x.first > y.first : d1 < d2;
    }
};

/* 官方题解的解法，与ExamRoom相似，只把端点组织成set而非像ExamRoom1一样把区间组织成set，为了在seat()时更快，用priority_queue
记录区间大小，用端点判断区间的合法性并懒惰删除。用时20ms
*/
class ExamRoom2 {
public:
    int n;
    set<int> seats;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;

    ExamRoom2(int n) : n(n) {
        
    }
    
    int seat() {
        if (seats.empty()) {
            seats.insert(0);
            return 0;
        }
        // 两端
        int len1 = *seats.begin();
        int len2 = n - 1 - *seats.rbegin();
        while (true) {
            if (seats.size() < 2) break;
            auto p = pq.top();
            int l = p.first;
            int r = p.second;
            if (seats.count(l) && seats.count(r) && *std::next(seats.find(l)) == r) {
                int len = (r - l) / 2;
                int pos = (l + r) / 2;
                if (len > len1 && len >= len2) {
                    pq.top();
                    seats.insert(pos);
                    pq.push({l, pos});
                    pq.push({pos, r});
                    return pos;
                }
                break;
            }
            pq.pop();
        }
        if (len1 >= len2) {
            pq.push({0, *seats.begin()});
            seats.insert(0);
            return 0;
        }
        else {
            pq.push({*seats.rbegin(), n - 1});
            seats.insert(n - 1);
            return n - 1;
        }
    }
    
    void leave(int p) {
        if (p != *seats.begin() && p != *seats.rbegin()) {
            auto it = seats.find(p);
            int l = *std::prev(it);
            int r = *std::next(it);
            pq.push({l, r});
        }
        seats.erase(p);
    }
};

int main(int argc, char const *argv[]) {
    ExamRoom1 er1(10);
    cout << er1.seat() << endl;
    cout << er1.seat() << endl;
    cout << er1.seat() << endl;
    cout << er1.seat() << endl;
    er1.leave(4);
    cout << er1.seat() << endl;

    ExamRoom2 er2(10);
    cout << er2.seat() << endl;
    cout << er2.seat() << endl;
    cout << er2.seat() << endl;
    cout << er2.seat() << endl;
    er2.leave(4);
    cout << er2.seat() << endl;
    return 0;
}
