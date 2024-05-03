// https://leetcode.cn/problems/number-of-burgers-with-no-waste-of-ingredients/description/

#include <bits/stdc++.h>

using namespace std;

class Solution1276 {
public:
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {
        if (tomatoSlices == 0 && cheeseSlices == 0) return {0, 0};
        // 巨无霸汉堡和小皇堡所需奶酪都是1，因此若刚好用完，堡总数为cheeseSlices，枚举巨无霸汉堡数量
        int maxCount = min(tomatoSlices / 4, cheeseSlices);
        int i = 0;
        do {
            if (4 * i + 2 * (cheeseSlices - i) == tomatoSlices) return {i, cheeseSlices - i};
            i++;
        }
        while (i < maxCount);
        return {};
    }

    vector<int> numOfBurgers_implementation2(int tomatoSlices, int cheeseSlices) {
        /* 若能成功，则堡总数为cheeseSlices，设巨无霸汉堡为x个，则小皇堡为cheeseSlices - x，问题
        转化为是否存在x>=0，使得4x + 2(cheeseSlices - x) == tomatoSlices。即x=(tomatoSlices - 2 * cheeseSlices) / 2是否为非负整数，
        然后还要检查小皇堡的数量是否为正。 */
        int n = tomatoSlices - 2 * cheeseSlices;
        // 这里必须(n & 1) == 0而不能n & 1 == 0，==的优先级比&高，位运算优先级的坑
        if ((n >= 0) && ((n & 1) == 0) && (cheeseSlices - n / 2 >= 0)) return {n / 2, cheeseSlices - n / 2};
        return {};
    }
};

int main(int argc, char const *argv[]) {
    Solution1276 solu;
    auto vec = solu.numOfBurgers(16, 7);
    auto vec2 = solu.numOfBurgers(0, 0);
    auto vec3 = solu.numOfBurgers(2, 1);
    auto vec4 = solu.numOfBurgers_implementation2(16, 7);
    auto vec5 = solu.numOfBurgers_implementation2(2385088, 164763);
    return 0;
}
