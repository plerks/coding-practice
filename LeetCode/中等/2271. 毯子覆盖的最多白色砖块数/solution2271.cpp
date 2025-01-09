/*
url: https://leetcode.cn/problems/maximum-white-tiles-covered-by-a-carpet/
参考: https://leetcode.cn/problems/maximum-white-tiles-covered-by-a-carpet/solutions/1496434/by-endlesscheng-kdy9/
相关: LeetCode3413. 收集连续 K 个袋子可以获得的最多硬币数量
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2271 {
public:
    /* 区间端点在1e9的规模，但是区间数量在5 * 1e4的规模，所以需要从区间的端点来考虑。
    毯子的最佳摆放位置一定可以有一边在区间端点上(如果毯子两边都不在区间端点则可移动使在区间端点成立)，
    对于这题，各个点权值一样，可以只考虑毯子右边界在某个区间右端点上，不需要考虑毯子左边界在某个左端点的情况，
    因为这种情况下，若毯子右边界在某大块瓷砖中间，则向右移动毯子到右边界对准右端点，覆盖数不变，若毯子右边界在某块空白处，
    向左移动毯子到右边界对准右端点，覆盖数不变，因此左边界对齐可以转化为右边界对齐。
    因此，可以移动使毯子右边界在某个右端点，于是，只需考虑右端点对齐的情况即可。
    */
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        // tiles互不重叠
        sort(tiles.begin(), tiles.end());
        /* 考虑毯子(窗口)不动，瓷砖动，某块瓷砖刚刚右边界与毯子右边界对齐时，此时这块瓷砖达到最大覆盖(若瓷砖比地毯窄则是
        瓷砖完全被地毯覆盖)，加上进入流量tr - tl + 1而非覆盖面积min(carpetLen, tr - tl + 1)。
        然后有一些之前的覆盖的瓷砖从左边出去了，要计算出去的量并减去
        */
        // 整个过程是右边界在入流量，左边界在出流量，于是内容物就是进 - 出。右边进，左边出，计算答案，这三步流程
        int left = 0;
        int cover = 0;
        int ans = 0;
        for (auto &tile : tiles) {
            int tl = tile[0], tr = tile[1]; // tl, tr为这一大块瓷砖的左右端点的块号，瓷砖块号范围为[tl, tr]。(注意不是点的坐标，而是块号)
            // tr与毯子右边界对齐，此时毯子块号范围为[tr - carpetLen + 1, tr]，一共carpetLen块
            cover += tr - tl + 1; // 注意这里不能写成 min(carpetLen, tr - tl + 1)，通过右边界进入的流量确实有tr - tl + 1之多
            // 注意这里是<，因为这些数字是块号，不是点的坐标，且由于右边一定还有与毯子有重合的区间，left不会越界
            while (tiles[left][1] < tr - carpetLen + 1) {
                cover -= tiles[left][1] - tiles[left][0] + 1; // 完全移出，减去当初进入的量
                left++;
            }
            // 现在的left对应的瓷砖与毯子相交，计算出去的量，块号范围为[tiles[left][0], tr - carpetLen + 1）。也可能这个区间还完全在毯子内没出，需要与0取max
            int uncover = max(tr - carpetLen + 1 - tiles[left][0], 0);
            ans = max(ans, cover - uncover);
        }
        return ans;
    }

    /* 为什么不能考虑成，窗口不动，瓷砖往左移动，然后让左边界与左端点对齐？
    因为这时候既不是入流量的分界点，也不是出流量的分解点。
    让左边界对齐的话应该让瓷砖整体从左往右移动，这样左边界对齐时才是入流量的分界点。
    */
};

int main(int argc, char const *argv[]) {
    Solution2271 solu;
    cout << solu.maximumWhiteTiles(*new vector<vector<int>>{{1,5},{10,11},{12,18},{20,25},{30,32}}, 10) << endl;
    cout << solu.maximumWhiteTiles(*new vector<vector<int>>{{3,4},{1,2}}, 1) << endl;
    return 0;
}
