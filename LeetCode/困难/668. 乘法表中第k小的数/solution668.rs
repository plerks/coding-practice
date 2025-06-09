/*
url: https://leetcode.cn/problems/kth-smallest-number-in-multiplication-table/
相关: LeetCode373. 查找和最小的 K 对数字, LeetCode1508. 子数组和排序后的区间和, LeetCode378. 有序矩阵中第 K 小的元素
标签: 【题单】二分算法, [special]
*/

struct Solution668;

impl Solution668 {
    pub fn find_kth_number(m: i32, n: i32, k: i32) -> i32 {
        // <= x 的数的个数是否 < k，找第一个'否'
        /* 如果写成<=x的数的个数是否<=k，找最后一个'是'，二分得到的结果right可能不在乘法表中。这里有点特殊，==k的情况若
        存在，正解会在right左边，若不存在，正解会在right右边，这种思路找到的不是答案。
        例如：
        值    126(正解)    127(right)    128
        cnt   401         401           405

        值    310         311(right)    312(正解)
        cnt   470         470           472

        所以要找第一个 >= k 的位置，这样在cnt不连续随着值x跳跃变化的情况下，找到的值x才是正解。
        */
        let check = |x| {
            let mut cnt = 0;
            for i in 1..(m + 1) {
                cnt += std::cmp::min(n, x / i);
            }
            cnt < k
        };

        let mut left = 0;
        let mut right = m * n;
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        left
    }

    /* 见 LeetCode1508. 子数组和排序后的区间和 与 LeetCode378. 有序矩阵中第 K 小的元素
    x位置示意为：{ a a } { x [x] x } { b b }，x有两个性质：
    既是 <= x 的数的个数第一次 >= k
    也是 < x 的数的个数最后一次 < k

    两种写法都可以
    */
    pub fn find_kth_number_implementation2(m: i32, n: i32, k: i32) -> i32 {
        // < x 的个数 < k，找最后一个'是'
        let check = |x| {
            let mut cnt = 0;
            for i in 1..(m + 1) {
                cnt += std::cmp::min(n, x / i);
            }
            cnt < k
        };

        let mut left = 0;
        let mut right = m * n;
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        left
    }
}

pub fn main() {
    // println!("{}", Solution668::find_kth_number(3,3,5));
    println!("{}", Solution668::find_kth_number(45,12,471));
    println!("{}", Solution668::find_kth_number(42,34,401));
}