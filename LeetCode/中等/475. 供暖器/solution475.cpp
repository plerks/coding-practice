/*
url: https://leetcode.cn/problems/heaters/
标签: 【题单】二分算法, [mark], 滑窗的一个坑
*/
#include <bits/stdc++.h>

using namespace std;

class Solution475 {
public:
    // 我的解法，二分答案
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());

        auto check = [&](int x) {
            int l = -1, r = -1; // [l, r]为上一个覆盖的houses下标区间
            for (int i = 0; i < heaters.size(); i++) {
                int p = heaters[i];
                int lo = p - x, hi = p + x;
                // 第一个>=lo
                int index1 = lower_bound(houses.begin(), houses.end(), lo) - houses.begin();
                // 最后一个<=hi
                int index2 = upper_bound(houses.begin(), houses.end(), hi) - houses.begin() - 1;
                if (index1 > r + 1) return false;
                l = index1;
                r = index2;
            }
            return r == houses.size() - 1;
        };

        int left = 0, right = max(abs(houses.back() - heaters.front()), abs(houses.front() - heaters.back()));
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }

    // 错误写法，具体见findRadius_implementation2()，28 / 30 个通过的测试用例，是个长用例才wa出来
    int findRadius_wa(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());

        auto check = [&](int x) {
            int l = -1, r = -1; // [l, r]为上一个覆盖的houses下标区间
            int index1 = 0, index2 = 0;
            for (int i = 0; i < heaters.size(); i++) {
                int p = heaters[i];
                int lo = p - x, hi = p + x;
                while (index1 < houses.size() && houses[index1] < lo) index1++;
                if (index2 < 0) cout << "negative index2" << endl;
                while (index2 < houses.size() && houses[index2] <= hi) index2++; // 改成`while (index2 == -1 || index2 < houses.size() && houses[index2] <= hi) index2++;`能过
                index2--;
                // [index1, index2]能被覆盖
                if (index1 > r + 1) return false;
                l = index1;
                r = index2;
            }
            return r == houses.size() - 1;
        };

        int left = 0, right = max(abs(houses.back() - heaters.front()), abs(houses.front() - heaters.back()));
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }

    // 把二分优化成双指针
    int findRadius_implementation2(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());

        auto check = [&](int x) {
            int r = -1; // r为上一个覆盖的houses下标右端点
            int index1 = 0, index2 = 0;
            for (int i = 0; i < heaters.size(); i++) {
                int p = heaters[i];
                int lo = p - x, hi = p + x;
                while (index1 < houses.size() && houses[index1] < lo) index1++;
                while (index2 < houses.size() && houses[index2] <= hi) index2++;
                /* 注意这里不要写index2--去获得最后一个<=hi的位置，得用个新变量index3，是个坑！如果写index2--，
                假设前两个heater在负无穷和负无穷+1的位置，x较小，一个house都覆盖不了，那么第一次循环后index2会变成-1，
                下一次循环houses[index2]直接就越界了。

                虽然应该是越界，但是，还有个奇葩的坑，就算index2变成了负数，由于size()返回的是size_t，index2 < houses.size()会
                转成无符号数的比较，会判断 < 为false，不会执行后面的houses[index2]，虽然错误本质是下标越界，但是实际不会真的发生。
                sanitizer不会有报错，只是执行逻辑完全错了。

                除了用新变量，还有种写法是改成while (index2 == -1 || index2 < houses.size() && houses[index2] <= hi) index2++;，
                见findRadius_wa()，不过最好别用这种方法，开新变量最稳妥。
                */
                int index3 = index2 - 1;
                // [index1, index3]能被覆盖
                if (index1 > r + 1) return false;
                r = index3;
            }
            return r == houses.size() - 1;
        };

        int left = 0, right = max(abs(houses.back() - heaters.front()), abs(houses.front() - heaters.back()));
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }

    // 官方题解解法，也是二分，不过不是二分答案，而是求每个house最近的heater距离，求最近heater需要二分查找。这个二分思路简单多了。
    int findRadius_implementation3(vector<int>& houses, vector<int>& heaters) {
        sort(heaters.begin(), heaters.end());
        int ans = 0;
        for (int h : houses) {
            // heater里最后一个 <= h
            int index1 = upper_bound(heaters.begin(), heaters.end(), h) - heaters.begin() - 1;
            int res = INT_MAX;
            if (index1 != -1) res = min(res, h - heaters[index1]);
            // 第一个 >= h
            int index2 = upper_bound(heaters.begin(), heaters.end(), h) - heaters.begin();
            if (index2 != heaters.size()) res = min(res, heaters[index2] - h);
            ans = max(ans, res);
        }
        return ans;
    }

    // 官方题解解法二，用双指针优化
    int findRadius_implementation4(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int ans = 0;
        /* 关于这里为什么两个初值都是0，理一下：
        这里虽然是要求最后一个<=h的heaters下标，和第一个>=h的heaters下标，
        但是前者实际上是通过searchFirst求l，l实际是第一个>h的heaters下标，然后l - 1才是最后一个<=h的heaters下标。
        也就是说，l和r实际都是searchFirst的结果，二者单调增加，值域范围为[0, n]，初值设为0，不会漏过任何一个可能的位置。
        不存在：searchLast的特殊位置为-1，初值为0会不会漏掉取值-1的问题。l, r都是searchFirst的结果！
        */
        int l = 0, r = 0; // 求最后一个<=h的heaters下标，和第一个>=h的heaters下标
        for (int h : houses) {
            while (l < heaters.size() && heaters[l] <= h) l++;
            while (r < heaters.size() && heaters[r] < h) r++;
            int res = INT_MAX;
            if (l - 1 != -1) res = min(res, h - heaters[l - 1]);
            if (r != heaters.size()) res = min(res, heaters[r] - h);
            ans = max(ans, res);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution475 solu;
    // cout << solu.findRadius(*new vector<int>{1,2,3,4}, *new vector<int>{1,4}) << endl;
    cout << solu.findRadius(*new vector<int>{1,5}, *new vector<int>{2}) << endl;

    // cout << solu.findRadius_wa(*new vector<int>{100, 101}, *new vector<int>{1,4}) << endl;
    
    cout << solu.findRadius_implementation2(*new vector<int>{1,5}, *new vector<int>{2}) << endl;

    cout << solu.findRadius_implementation3(*new vector<int>{1,5}, *new vector<int>{2}) << endl;

    cout << solu.findRadius_implementation4(*new vector<int>{1,5}, *new vector<int>{2}) << endl;
    return 0;
}