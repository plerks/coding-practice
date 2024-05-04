// https://leetcode.cn/problems/day-of-the-week/description/

#include <bits/stdc++.h>

using namespace std;

class Solution1185 {
public:
    string dayOfTheWeek(int day, int month, int year) {
        // 直接用Zeller公式
        if (month == 1 || month == 2) {
            year--;
            month = month + 12;
        }
        int c = year / 100;
        int y = year % 100;
        int d = day;
        int m = month;
        int w = (y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1) % 7;
        w = (w % 7 + 7) % 7;
        return vector<string>{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}[w];
    }
};

int main(int argc, char const *argv[]) {
    Solution1185 solu;
    cout << solu.dayOfTheWeek(31, 8, 2019) << endl;
    return 0;
}
