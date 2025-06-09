/*
url: https://leetcode.cn/problems/range-sum-of-sorted-subarray-sums/
参考: https://leetcode.cn/problems/range-sum-of-sorted-subarray-sums/solutions/326456/onlogs-jie-fa-er-fen-shuang-zhi-zhen-by-newhar/
相关: LeetCode378. 有序矩阵中第 K 小的元素, LeetCode668. 乘法表中第k小的数
标签: 【题单】二分算法, 二分 + 双指针, 前缀和的前缀和, [mark], [special]
*/

struct Solution1508;

impl Solution1508 {
    /* 这题直接写暴力可以通过，nums.length只有1e3的级别，把所有非空子数组和用前缀和算出来需要O(n^2)，
    排序需要O(n^2logn)，然后直接遍历求[left, right]的区间和。总时间复杂度O(n^2logn)。
    但是参考题解，有以下这种很巧妙的办法：
    首先，用LeetCode378 二分 + 双指针，可以把新数组中在left和right下标处的值求出来。新数组指nums的所有非空子数组和排序之后得到的数组。
    要求新数组[left, right]之和，转化成求[0, right]之和 - [0, left - 1]之和。记新数组前k项之和为f(k)，答案为f(right + 1) - f(left)，
    但是题目给的left'，right'下标是从1开始的，right' = right + 1，所以答案为f(right') - f(left' - 1)，这里right'是题目参数给的值。
    
    如何求f(k)？
    假设新数组k处的值为x，如果知道新数组 < x 的值的 和sum 与 个数cnt，则 == x 就有 k - cnt 个，于是 f(k) = sum + (k - cnt) * x。
    
    如何求 sum ？
    二分 + 双指针时，其实就知道了 < x 的子数组位置，例如，以 i 为左边界，直到右边界为j，[i, j)的和都 < x，则
    sum += Σ(k=i, j - 1)(psum[k] - psum[i - 1]) = ppsum[j - 1] - ppsum[i - 1] - (j - i)psum[i - 1]
    这也就意味着要求nums的 前缀和psum 的前缀和ppsum，前缀和的前缀和！
    */
    pub fn range_sum(nums: Vec<i32>, n: i32, left: i32, right: i32) -> i32 {
        let nums: Vec<i64> = nums.iter().map(|&x| x as i64).collect();
        let n = n as i64; let left = left as i64; let right = right as i64;

        let mut psum = vec![0; n as usize + 1]; // 前缀和
        for i in 0..n as usize {
            psum[i + 1] = psum[i] + nums[i];
        }
        let mut ppsum = vec![0; n as usize + 1]; // 前缀和的前缀和
        for i in 0..n as usize {
            ppsum[i + 1] = ppsum[i] + psum[i + 1];
        }

        // 求新数组中 < x 的个数，并顺带把 sum 也求出来。
        let get_sum_cnt = |x| {
            let mut j: i64 = 0;
            let mut sum: i64 = 0;
            let mut cnt: i64 = 0;
            for i in 0..n { // 双指针
                // 子数组[i, j]的和为psum[j] - psum[i - 1]，偏移 + 1
                while j < n && psum[j as usize + 1] - psum[i as usize] < x {
                    j += 1;
                }
                // j可取[i, j)
                cnt += j - i;
                sum += ppsum[j as usize] - ppsum[i as usize] - (j - i) * psum[i as usize];
            }

            (sum, cnt)
        };

        // 求新数组第 k 个数的值。即 cnt >= x 的第一个 x，cnt为新数组中 <= x 的数的个数
        // 但是，这里想要求的是 < x 的部分的sum与cnt，所以要换个思路
        // 新数组第k个数x位置示意为：{ a a } { x [x] x } { b b }
        // 则，x：
        // 既是： 1. < x 的数的个数最后一次 < k
        // 也是：2. <= x 的数的个数第一次 >= k
        // 两个性质都成立，这里得用性质1
        let get_kth = |k| {
            let mut left = 0;
            let mut right = psum[n as usize];
            while left <= right {
                let mid = (left + right) / 2;
                let (sum, cnt) = get_sum_cnt(mid);
                if cnt < k { left = mid + 1; }
                else { right = mid - 1; }
            }
            right
        };

        let f = |k| {
            let x = get_kth(k);
            let (sum, cnt) = get_sum_cnt(x);
            return sum + (k - cnt) * x;
        };

        ((f(right) - f(left - 1)) % (1e9 as i64 + 7)) as i32
    }
}

fn main() {
    println!("{}", Solution1508::range_sum([1,2,3,4].to_vec(), 4, 1, 5));
    println!("{}", Solution1508::range_sum([1,2,3,4].to_vec(), 4, 3, 4));
    println!("{}", Solution1508::range_sum([1,2,3,4].to_vec(), 4, 1, 10));
}