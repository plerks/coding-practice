# [LogTrick](/LeetCode/题单/位运算.md#logtrick)

相关题目:

* [LeetCode2411. 按位或最大的最小子数组长度](https://leetcode.cn/problems/smallest-subarrays-with-maximum-bitwise-or/)

* [LeetCode3171. 找到按位或最接近 K 的子数组](https://leetcode.cn/problems/find-subarray-with-bitwise-or-closest-to-k/)

* [LeetCode898. 子数组按位或操作](https://leetcode.cn/problems/bitwise-ors-of-subarrays/)

* [LeetCode2447. 最大公因数等于 K 的子数组数目](https://leetcode.cn/problems/number-of-subarrays-with-gcd-equal-to-k/) (GCD LogTrick)

* [LeetCode2654. 使数组所有元素变成 1 的最少操作次数](https://leetcode.cn/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/) (GCD LogTrick)

LogTrick，以 OR 运算为例，枚举 nums 的所有左端点 i ，如何求出所有右端点对应的子数组 nums[i, j] 的 OR 结果？

有 O(n^2) 个子数组，但是由于 OR 的性质，子数组 OR 的结果却没有这么多个。

已知 [i + 1, i + 1], [i + 1, i + 2], .. , [i + 1, n - 1] 的 OR 结果，当下一轮枚举以 nums[i] 为头时，只要 nums[i] | [i + 1, i + x] 的值与上一轮的 [i + 1, i + x] 一样，那么右侧我们都不用计算了。因为一定会有 $(nums[i] | ... | nums[i + x]) | ... | nums[i + y] == (nums[i + 1] | ... | nums[i + x]) | ... | nums[i + y]$。虽然一轮 i 的计算最多花费 O(n) 时间，但是所有 i 的计算，由于 nums 每个数最多增添 32 次 1，总时间为 O(nlogU)。

(nums[i] 中的 1 已经被 [i + 1, i + x] 中的 1 完全覆盖了，所以右侧不需要算了，i 既未引入新的 1 ， OR 的结果一定是原来的值)

也就是说，**LogTrick依赖运算的性质，用 O(nlogU) 的时间就：枚举左/右，计算右/左，得到了一遍所有子数组 (O(n^2)个) 的 OR 结果。** （要把所有 OR 结果存起来得 O(n^2)，但是因为 OR 运算的性质，不会有那么多值需要算）

具体见 LeetCode2411 的注释。