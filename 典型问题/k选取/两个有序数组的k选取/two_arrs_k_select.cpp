/*
描述: 给定两个有序的数组，找出二者合并后的第k大元素（k从1开始）
相关: LeetCode4. 寻找两个正序数组的中位数
标签: k选取
*/

#include <bits/stdc++.h>

using namespace std;

// 具体解释见`LeetCode4. 寻找两个正序数组的中位数`解法一
// 时间复杂度O(logk)，k最大取m + n，此时时间复杂度会达到O(log(m + n))
int two_arrs_k_select(vector<int>& nums1, vector<int>& nums2, int k) { // nums1和nums2分别有序，找二者中第k大的数(k从1开始)
    int m = nums1.size(), n = nums2.size();

    int index1 = 0; // 左边的部分被删掉，nums1[index1..]是剩下的
    int index2 = 0; // 左边的部分被删掉，nums2[index2..]是剩下的

    while (true) {
        // 只剩一个数组了
        if (index1 == m) return nums2[index2 + k - 1];
        if (index2 == n) return nums1[index1 + k - 1];

        // k == 1，选两个数组最小值即可
        if (k == 1) return min(nums1[index1], nums2[index2]);

        int newIndex1 = min(index1 + k / 2 - 1, m - 1);
        int newIndex2 = min(index2 + k / 2 - 1, n - 1);
        if (nums1[newIndex1] <= nums2[newIndex2]) {
            k -= newIndex1 - index1 + 1; // [index1, newIndex1]被删掉
            index1 = newIndex1 + 1;
        }
        else {
            k -= newIndex2 - index2 + 1; // [index2, newIndex2]被删掉
            index2 = newIndex2 + 1;
        }
    }

    return -1;
}

// 具体解释见`LeetCode4. 寻找两个正序数组的中位数`解法二
/* 找 nums1 ∪ nums2 的第 k 大，即要把 nums1 和 nums2 的 m + n 个元素进行划分，从 nums1 中选 i 个最小的，从 nums2 中选 j 个最小的，
且让 i + j 为 k。即（以下用A,B记nums1和nums2）：
    A[0] A[1] ... A[i - 1] | A[i] A[i + 1] ...
    B[0] ... B[j - 1] | B[j] B[j + 1] ...
左侧合起来有 k 个元素，且要满足 左半 <= 右半（左半最大值 <= 右半最小值），答案为 max(A[i - 1], B[j - 1])

如何让 左半 <= 右半 ？
这个条件即 A[i - 1] <= B[j] && B[j - 1] <= A[i]，
二分查找 A[i - 1] <= B[j] 的最后一个i位置 等价于 A[i - 1] <= B[j] && A[i] > B[j - 1] 推出 A[i - 1] <= B[j] && B[j - 1] <= A[i]，
所以，只需二分查找 A[i - 1] <= B[j] 的最后一个i位置

此外要注意 0 <= i <= m，A左侧最多会选m个。nums1[m]更像是有个真的正无穷，不是虚拟的正无穷，A左侧选m个的时候是真的会用下标m去读nums1。
此外还需满足 0 <= (j = k - i) <= n，
解得 max(0, k - n) <= i <= min(m, k)

计算最后一个'是'位置的 max(A[i - 1], B[j - 1])
*/
// 时间复杂度O(log(min(m, n)))，即使k取m + n，时间复杂度也只取决于min(m, n)
int two_arrs_k_select_implementation2(vector<int>& nums1, vector<int>& nums2, int k) { // nums1和nums2分别有序，找二者中第k大的数(k从1开始)
    int m = nums1.size(), n = nums2.size();

    int left = max(0, k - n), right = min(m, k);
    int ans = -1;
    while (left <= right) {
        int i = left + (right - left) / 2;
        int j = k - i;

        // 处理下标越界
        int A1 = (i - 1 == -1) ? INT_MIN : nums1[i - 1];
        // int A2 = (i == m) ? INT_MAX : nums1[i]; // A2不需要
        int B1 = (j - 1 == -1) ? INT_MIN : nums2[j - 1];
        int B2 = (j == n) ? INT_MAX : nums2[j];

        if (A1 <= B2) {
            ans = max(A1, B1);
            left = i + 1;
        }
        else right = i - 1;
    }
    return ans;
}

/* 扩展：如果换成多个有序数组(数组个数c > 3)的k选取，又该怎么做？
首先，多路归并，或者把数组合并后用nth_element，可以达到线性时间复杂度

以上解法一似乎还能用，每次选前端大约 k / c 的长度出来比较，找最小值花费O(c)时间，然后每次 k -= k / c，k' = (c - 1) / c * k。
总时间应该是O(c * log_{c / (c - 1)}{k})

解法二应该是用不了了，例如c == 3，则三段长度 p + q + r == k，确定p之后，q和r有多种组合可能，还不如直接用线性时间复杂度的做法。
（有点像 LeetCode15. 三数之和 和 LeetCode18. 四数之和）
*/

int main(int argc, char const *argv[]) {
    cout << two_arrs_k_select(*new vector<int>{1, 3}, *new vector<int>{2}, 2) << endl;
    cout << two_arrs_k_select(*new vector<int>{1, 3}, *new vector<int>{2, 4}, 3) << endl;
    cout << two_arrs_k_select(*new vector<int>{2, 4, 8}, *new vector<int>{3, 6, 7}, 5) << endl;

    cout << two_arrs_k_select_implementation2(*new vector<int>{1, 3}, *new vector<int>{2}, 2) << endl;
    cout << two_arrs_k_select_implementation2(*new vector<int>{1, 3}, *new vector<int>{2, 4}, 3) << endl;
    cout << two_arrs_k_select_implementation2(*new vector<int>{2, 4, 8}, *new vector<int>{3, 6, 7}, 5) << endl;
    return 0;
}