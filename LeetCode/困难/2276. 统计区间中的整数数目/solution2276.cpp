/*
url: https://leetcode.cn/problems/count-integers-in-intervals/description/
LeetCode参考: https://leetcode.cn/problems/count-integers-in-intervals/solutions/2566065/tong-ji-qu-jian-zhong-de-zheng-shu-shu-m-jkey/
              https://leetcode.cn/problems/count-integers-in-intervals/solutions/1495396/by-endlesscheng-clk2/
相关: LeetCode57. 插入区间, LeetCode56. 合并区间
标签: 区间, 区间合并, 有序集合, 平衡二叉搜索树, 红黑树, 线段树
*/

#include <bits/stdc++.h>

using namespace std;

// 69 / 73 个通过的测试用例，超出内存限制
class CountIntervals_exceed_memory_limit {
public:
    vector<pair<int, int>> intervals;

    CountIntervals_exceed_memory_limit() {

    }
    
    // `LeetCode57. 插入区间`，插入区间的合并
    void add(int left, int right) {
        vector<pair<int, int>> old = intervals;
        intervals.clear();
        int i = 0;
        while (i < old.size() && old[i].second < left) {
            intervals.push_back(old[i]);
            i++;
        }
        while (i < old.size() && !(old[i].first > right)) {
            left = min(left, old[i].first);
            right = max(right, old[i].second);
            i++;
        }
        intervals.push_back(make_pair(left, right));
        while (i < old.size()) {
            intervals.push_back(old[i]);
            i++;
        }
    }
    
    int count() {
        int ans = 0;
        for (auto &p : intervals) {
            ans += p.second - p.first + 1;
        }
        return ans;
    }
};

// 官方题解解法，和`LeetCode57. 插入区间`思路是相同的，但是用有序集合更快地找出要合并的区间
class CountIntervals {
public:
    map<int, int> myMap;

    // C++成员变量和成员函数不能重名，Java可以，这里有count()函数了，只能叫cnt。
    int cnt = 0; // C++ 11 in-class initialization

    CountIntervals() {

    }
    
    void add(int left, int right) {
        /* 已有的区间分三类，右端点小于left，左端点大于right，这两类与[left, right]无相交，要进行合并的是剩下的那种区间 */
        /* 这里map存的key是左端点，因此每次在map中查找最后一个左端点小于等于right的，看看能否合并。注意，这里不能每次查找
        第一个右端点大于等于left的，因为map的key是左端点。C++的有序集合提供的是low_bound()和upper_bound()，分别寻找第一个
        大于等于和第一个大于，用upper_bound() - 1得到last <= */
        auto interval = myMap.upper_bound(right); // 这时interval是第一个左端点>right的，或者end()
        if (interval != myMap.begin()) { // 有前一个元素，则用upper_bound()减1
            interval--;
        }
        else {
            interval = myMap.end(); // 否则没有last <=，last <=为空
        }
        // 这样一个if else下来interval才相当于Java TreeMap的floorEntry()的效果，floorEntry()返回null相当于让iterator为map.end()
        while (interval != myMap.end() && interval->second >= left) {
            left = min(left, interval->first);
            right = max(right, interval->second);
            cnt -= interval->second - interval->first + 1;
            myMap.erase(interval);
            interval = myMap.upper_bound(right);
            if (interval != myMap.begin()) {
                interval--;
            }
            else {
                interval = myMap.end();
            }
        }
        cnt += right - left + 1;
        myMap[left] = right; // 插入[left, right]区间
    }
    
    int count() {
        return cnt;
    }
};

// 待做: 这题灵茶山艾府题解还提供了用线段树的解法

int main(int argc, char const *argv[]) {
    CountIntervals_exceed_memory_limit solu;
    solu.add(2, 3);
    solu.add(7, 10);
    cout << solu.count() << endl;
    solu.add(5, 8);
    cout << solu.count() << endl;

    CountIntervals solu2;
    solu2.add(2, 3);
    solu2.add(7, 10);
    cout << solu2.count() << endl;
    solu2.add(5, 8);
    cout << solu2.count() << endl;

    CountIntervals solu3;
    solu3.add(33, 49);
    solu3.add(43, 47);
    solu3.add(37, 37);
    solu3.add(26, 38);
    solu3.add(11, 11);
    cout << solu3.count() << endl;
    return 0;
}