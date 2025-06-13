/*
url: https://leetcode.cn/problems/median-of-two-sorted-arrays/
参考: https://leetcode.cn/problems/median-of-two-sorted-arrays/solutions/258842/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/
相关: 典型问题/k选取/两个有序数组的k选取/
标签: 【题单】二分算法, k选取, [mark]
*/

#include <bits/stdc++.h>

using namespace std;

class Solution4 {
public:
    /* 对给定的两个有序数组进行k选取，时间复杂度O(log(m + n))。（以下的 “第k大” 都是指从1开始编号的）
    这题的技巧来自于这样一件事，如果能确定一些数一定在nums1和nums2合并之后 < k 的位置(k从1开始)，也就是说这些数太靠左，
    则其一定是不会成为第k个数的，可以把这些数删掉，要搜索的位置k也减小相应数量。

    具体来说，对nums1和nums2，考虑nums1[⌊k/2⌋ - 1]和nums2[⌊k/2⌋ - 1]这两个点，其前面都有⌊k/2⌋ - 1个元素，
    ⌊k/2⌋ - 1 + ⌊k/2⌋ - 1 = k - 2 或 k - 3 <= k - 2。

    1. 假设现在 nums1[⌊k/2⌋ - 1] < nums2[⌊k/2⌋ - 1]，把nums1[0, ⌊k/2⌋ - 1)叫做A段，nums2[0, ⌊k/2⌋ - 1)叫做B段，
    可以知道，就算A，B段的元素全部 <= nums1[⌊k/2⌋ - 1]，nums1[⌊k/2⌋ - 1]也不过是第 k - 2 + 1 大的元素，一定在第 k 大
    的元素的左侧，必不可能为第 k 大，nums1[0, ⌊k/2⌋ - 1]可以全部剪掉，且 k -= ⌊k/2⌋。这样，把搜索的 k 减半了。
    也就是说，小侧的尖端可以排除。
    简单来说，nums1[⌊k/2⌋ - 1]左侧最多可以放成 A B nums1[⌊k/2⌋ - 1]，但是即便这样也不够，才 k - 1 个元素，所以nums1前段必可剪掉。
    注意，这时不能把B段剪掉，看着B段挺靠前，但是实际可能含有第k大，因为A的右侧可能还有小的值，B段的值的实际排序位置不一定很靠左，例如：
        A: 1 1 1 [2] 3 3 4  B: 5 5 5 [6] ...
    只能剪小侧尖端，A段和分界点nums1[⌊k/2⌋ - 1]都被剪掉。不能剪另一侧，也不能两侧都剪。

    2. nums1[⌊k/2⌋ - 1] > nums2[⌊k/2⌋ - 1]。对称的情况，剪B段

    3. nums1[⌊k/2⌋ - 1] == nums2[⌊k/2⌋ - 1]。合并入上面的一种情况即可

    为什么选nums1[⌊k/2⌋ - 1]和nums2[⌊k/2⌋ - 1]这两个点？
    因为其前面各有⌊k/2⌋ - 1个数，合起来 <= k - 2 个数，我们要剪小侧尖端剪枝，一次要尽量多的剪，⌊k/2⌋ - 1是个上限。一次剪掉的节点数
    是⌊k/2⌋。

    边界情况：

    有一个数组剪空了，直接返回剩余数组第 k 个位置的元素。不特判会访问下标越界

    k == 1，此时不特判的话剪掉的节点数⌊k/2⌋ == 0，可能会死循环

    ⌊k/2⌋ - 1超过某个数组右边界，注意不可能两个都超过，都超过说明剩余元素个数 < ⌊k/2⌋ + ⌊k/2⌋ <= k，说明一开始的 k 就有问题，
    这时只需把当前轮要找的前端分界点选成最后一个元素即可。选 ⌊k/2⌋ - 1 只是为了一轮尽量多地剪，找出来的前端枝变短了，但是“剪小侧尖端”仍然
    是正确的，只是没剪掉那么多。

    时间复杂度：
    每轮 k 都变成原来的一半，时间复杂度为O(logk)，k最大取m + n，此时时间复杂度会达到O(log(m + n))

    如果⌊k/2⌋ - 1越界，这时剪不了那么多元素，会不会影响时间复杂度？
    不会，不妨设A段越界。若判断出来剪B段，则此轮k还是减半；若判断出来剪A段，那么A段直接就剪空了，下轮就直接是边界情况退出了。
    */
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

    /* 官方题解解法一，这题的中位数定义为，若 m + n 为奇数则中位数为中间那个，若为偶数则中位数为中间两个数的平均值。
    不过这解法，中位数的定义改一下，只需改一下对应参数值就行了。
    这里主要功能在于 two_arrs_k_select() 功能强大，实现了对给定的两个有序数组进行k选取，且时间复杂度为O(log(m + n))。
    two_arrs_k_select() 的代码可以对两个有序数组进行任意位置的选取
    */
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if ((m + n) % 2 == 1) {
            return two_arrs_k_select(nums1, nums2, (m + n) / 2 + 1); // 第i大，i从1开始编号
        }
        else {
            return (two_arrs_k_select(nums1, nums2, (m + n) / 2) + two_arrs_k_select(nums1, nums2, (m + n) / 2 + 1)) / 2.0;
        }
    }

    /* 官方题解解法二，中位数的本质是（注意这题中位数的定义是若 m + n 为奇数则中位数为中间那个，若为偶数则中位数为中间两个数的平均值），
    要把 nums1 和 nums2 的 m + n 个元素进行划分，从 nums1 中选 i 个最小的，从 nums2 中选 j 个最小的，
    且让 i + j 为总元素个数的一半，这样就把 nums1 ∪ nums2 进行了对半划分，即（以下用A,B记nums1和nums2）：
    A[0] A[1] ... A[i - 1] | A[i] A[i + 1] ...
    B[0] ... B[j - 1] | B[j] B[j + 1] ...
    两条竖线将总元素对半分，且 左半 <= 右半（左半最大值 <= 右半最小值）
    这样，找中位数就只需看分界线位置。

    如何划分？
        如果 m + n 是偶数，则让 i + j = m + n - (i + j)，对半分
        如果 m + n 是奇数，则让 i + j = m + n - (i + j) + 1，左半比右半多一个
    
    两种情况可以合并：让 i + j == ⌊(m + n + 1) / 2⌋ （m + n为奇数时是式子本身，为偶数时与(m + n) / 2相等）

    知道了两条分界线对半分要满足的关系，如何找到那条分界线使得 左半 <= 右半 成立？
    左半 <= 右半 等价于 A[i - 1] <= B[j] && B[j - 1] <= A[i]
    神奇的来了，i + j 为定值，i往右1步，j就往左一步。A[i - 1] <= B[j] && B[j - 1] <= A[i] 几乎是 “使得 A[i - 1] <= B[j]的最后一个`i`”的定义！
    最后一个 A[i - 1] <= B[j]的`i`，则 A[i - 1] <= B[j] && A[i] > B[j - 1] 能推出 A[i - 1] <= B[j] && B[j - 1] <= A[i]
    实际上这最后一个`i`满足的条件还要强一点。

    于是，只需二分搜索 最后一个 A[i - 1] <= B[j]的`i`。
    如果 m + n 是奇数，则中位数为 ( max(A[i - 1], B[j - 1]) + min(A[i], B[j]) ) / 2
    如果 m + n 是偶数，则中位数为 max(A[i - 1], B[j - 1])

    还有一个细节，i + j == ⌊(m + n + 1) / 2⌋，则 j 最小为 ⌊(m + n + 1) / 2⌋ - m，若 m > n + 1，则 j 可能为负数，不合法（j是选的B的个数，0 <= j <= n）
    这是因为 m > n 时若把A中所有元素都划分到左侧，则B就算划0个到左侧，左侧总元素个数也超过一半了。

    官方题解的解决办法是保证m <= n，即当 m > n 时交换 nums1 和 nums2，然后在 i ∈ [0, m] 二分找i
    还有一个解决办法是：0 <= i <= m，0 <= (j = ⌊(m + n + 1) / 2⌋ - i) <= n，解得 max(0, ⌊(m + n + 1) / 2⌋ - n) <= i <= min(m, ⌊(m + n + 1) / 2⌋)，设置二分范围即可
    
    时间复杂度 O(min(m, n))，即使k取m + n，时间复杂度也只取决于min(m, n)
    */
    double findMedianSortedArrays_implementation2(vector<int>& nums1, vector<int>& nums2) {
        // 这里看似可以写成 if (nums1.size() > nums2.size() + 1)，但是有个极端用例 {2} {}，会nums2下标越界
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays_implementation2(nums2, nums1);
        }

        // 现在m <= n
        int m = nums1.size(), n = nums2.size();

        // 找最后一个A[i - 1] <= B[j]的`i`
        // 注意这里很特殊，是闭区间二分写法，但是right要为 m 而非 m - 1，因为 最后一个A[i - 1] <= B[j]的`i` 可能要取m，A左侧最多会选m个元素。
        // 如果最开始是[0, m - 1]，则searchLast的范围为[-1, m - 1]，取不到 m。nums1[m]不是有个虚拟的正无穷，而更像是真的要当作插了个正无穷，
        // nums1[i - 1]位置也真的要当作插了个负无穷，是真会用下标去读-1和m位置的值的！
        int left = 0, right = m;
        int A1 = 0, A2 = 0, B1 = 0, B2 = 0; // 这里可以随便初始化，后面一定有一次赋值
        while (left <= right) {
            int mid = (left + right) / 2;
            int t = (m + n + 1) / 2 - mid;
            
            // 处理越界问题
            A1 = (mid - 1 == -1) ? INT_MIN : nums1[mid - 1];
            // A2 = (mid == m) ? INT_MAX : nums1[mid];
            // B1 = (t - 1 == -1) ? INT_MIN : nums2[t - 1];
            B2 = (t == n) ? INT_MAX : nums2[t];

            if (A1 <= B2) left = mid + 1;
            else right = mid - 1;
        }
        // right为最后一个A[i - 1] <= B[j]的`i`
        // A1,A2,B1,B2现在的值可能是区间内回答为'否'的点计算出来的，所以要重新算
        int i = right;
        int j = (m + n + 1) / 2 - i;
        A1 = (i - 1 == -1) ? INT_MIN : nums1[i - 1];
        A2 = (i == m) ? INT_MAX : nums1[i];
        B1 = (j - 1 == -1) ? INT_MIN : nums2[j - 1];
        B2 = (j == n) ? INT_MAX : nums2[j];

        return ((m + n) % 2 == 1) ? max(A1, B1) : (max(A1, B1) + min(A2, B2)) / 2.0;
    }

    // findMedianSortedArrays_implementation2()里不用交换nums1和nums2以保证m <= n。通过计算二分范围也可
    double findMedianSortedArrays_implementation3(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();

        int left = max(0, (m + n + 1) / 2 - n), right = min(m, (m + n + 1) / 2);
        int A1 = 0, A2 = 0, B1 = 0, B2 = 0;
        while (left <= right) {
            int mid = (left + right) / 2;
            int t = (m + n + 1) / 2 - mid;
            
            // 处理越界问题
            A1 = (mid - 1 == -1) ? INT_MIN : nums1[mid - 1];
            // A2 = (mid == m) ? INT_MAX : nums1[mid];
            // B1 = (t - 1 == -1) ? INT_MIN : nums2[t - 1];
            B2 = (t == n) ? INT_MAX : nums2[t];

            if (A1 <= B2) left = mid + 1;
            else right = mid - 1;
        }
        // right为最后一个A[i - 1] <= B[j]的`i`
        // A1,A2,B1,B2现在的值可能是区间内回答为'否'的点计算出来的，所以要重新算
        int i = right;
        int j = (m + n + 1) / 2 - i;
        A1 = (i - 1 == -1) ? INT_MIN : nums1[i - 1];
        A2 = (i == m) ? INT_MAX : nums1[i];
        B1 = (j - 1 == -1) ? INT_MIN : nums2[j - 1];
        B2 = (j == n) ? INT_MAX : nums2[j];

        return ((m + n) % 2 == 1) ? max(A1, B1) : (max(A1, B1) + min(A2, B2)) / 2.0;
    }

    // 和findMedianSortedArrays_implementation2()本质上一样，但是有个小细节
    double findMedianSortedArrays_implementation4(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays_implementation4(nums2, nums1);
        }

        int m = nums1.size(), n = nums2.size();

        // 找最后一个A[i - 1] <= B[j]的`i`
        int left = 0, right = m;
        int median1 = 0; // max(A1, B1)
        int median2 = 0; // min(A2, B2)
        while (left <= right) {
            int i = (left + right) / 2;
            int j = (m + n + 1) / 2 - i;
            
            // 处理越界问题
            int A1 = (i - 1 == -1) ? INT_MIN : nums1[i - 1];
            int A2 = (i == m) ? INT_MAX : nums1[i];
            int B1 = (j - 1 == -1) ? INT_MIN : nums2[j - 1];
            int B2 = (j == n) ? INT_MAX : nums2[j];

            if (A1 <= B2) {
                /* 有意思的是这里，官方题解这种写法在循环过程中计算了median1和median2，不用出循环后单独再计算一次，
                但是为什么只在这个if分支计算了，另外一个分支没有？
                因为我们要的是searchLast，也就是去找最后一个A[i - 1] <= B[j]的`i`的位置，最后用这个回答为'是'的位置求A1,A2,B1,B2，进一步求median1和median2。
                一方面，每次区间回答'是'而进这个分支，马上就计算了，median1,2结果是最后一次回答为'是'的位置的最新计算结果；另一方面，另外那个回答'否'的分支不需要计算，不会去用。
                */
                median1 = max(A1, B1);
                median2 = min(A2, B2);
                left = i + 1;
            }
            else right = i - 1;
        }

        return ((m + n) % 2 == 1) ? median1 : (median1 + median2) / 2.0;
    }

    // 官方题解解法二的思路不仅可以用来求中位数，也可以实现一般化的k选取
    double findMedianSortedArrays_implementation5(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if ((m + n) % 2 == 1) {
            return two_arrs_k_select_implementation2(nums1, nums2, (m + n) / 2 + 1); // 第i大，i从1开始编号
        }
        else {
            return (two_arrs_k_select_implementation2(nums1, nums2, (m + n) / 2) + two_arrs_k_select(nums1, nums2, (m + n) / 2 + 1)) / 2.0;
        }
    }

    // 见"典型问题/k选取/两个有序数组的k选取/two_arrs_k_select.cpp two_arrs_k_select_implementation2()"
    // 时间复杂度O(log(min(m, n)))
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
};

int main(int argc, char const *argv[]) {
    Solution4 solu;
    cout << solu.findMedianSortedArrays(*new vector<int>{1,3}, *new vector<int>{2}) << endl;
    cout << solu.findMedianSortedArrays(*new vector<int>{1,2}, *new vector<int>{3,4}) << endl;

    cout << "=========" << endl;

    cout << solu.findMedianSortedArrays_implementation2(*new vector<int>{1,3}, *new vector<int>{2}) << endl;
    cout << solu.findMedianSortedArrays_implementation2(*new vector<int>{1,2}, *new vector<int>{3,4}) << endl;
    cout << solu.findMedianSortedArrays_implementation2(*new vector<int>{2,2,4,4}, *new vector<int>{2,2,2,4,4}) << endl;
    cout << solu.findMedianSortedArrays_implementation2(*new vector<int>{2}, *new vector<int>{}) << endl;

    cout << "=========" << endl;

    cout << solu.findMedianSortedArrays_implementation3(*new vector<int>{1,3}, *new vector<int>{2}) << endl;
    cout << solu.findMedianSortedArrays_implementation3(*new vector<int>{1,2}, *new vector<int>{3,4}) << endl;

    cout << "=========" << endl;

    cout << solu.findMedianSortedArrays_implementation4(*new vector<int>{1,3}, *new vector<int>{2}) << endl;
    cout << solu.findMedianSortedArrays_implementation4(*new vector<int>{1,2}, *new vector<int>{3,4}) << endl;
    cout << solu.findMedianSortedArrays_implementation4(*new vector<int>{}, *new vector<int>{1}) << endl;

    cout << "=========" << endl;

    cout << solu.findMedianSortedArrays_implementation5(*new vector<int>{1,3}, *new vector<int>{2}) << endl;
    cout << solu.findMedianSortedArrays_implementation5(*new vector<int>{1,2}, *new vector<int>{3,4}) << endl;
    cout << solu.findMedianSortedArrays_implementation5(*new vector<int>{}, *new vector<int>{1}) << endl;
    return 0;
}