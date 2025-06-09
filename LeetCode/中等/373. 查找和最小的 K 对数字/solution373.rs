/*
url: https://leetcode.cn/problems/find-k-pairs-with-smallest-sums/
参考: https://leetcode.cn/problems/find-k-pairs-with-smallest-sums/solutions/1209848/gong-shui-san-xie-duo-lu-gui-bing-yun-yo-pgw5/
相关: LeetCode668. 乘法表中第k小的数, LeetCode719. 找出第 K 小的数对距离, LeetCode1439. 有序矩阵中的第 k 个最小数组和, LeetCode786. 第 K 个最小的质数分数
标签: 【题单】二分算法, 多路归并
*/

use std::{cmp::Reverse, collections::BinaryHeap};

struct Solution373;

impl Solution373 {
    pub fn k_smallest_pairs(nums1: Vec<i32>, nums2: Vec<i32>, k: i32) -> Vec<Vec<i32>> {
        // 先找最小的k个数对，最后一个和值是多少。找第一个数对对数 >= k 的和值x
        let check = |x| {
            let mut i = 0;
            let mut j = nums2.len() as i32 - 1;
            /* 这里必须把cnt显式定义为i64，否则cnt会是i32，然后release模式下溢出是不会panic的，
            然后放LeetCode上运行，有个大用例会超出内存限制，因为cnt溢出了，二分计算的结果不对。
            见<https://leetcode.cn/problems/find-k-pairs-with-smallest-sums/submissions/635007176/>
            */
            let mut cnt: i64 = 0;
            while i < nums1.len() { // 双指针
                while j >= 0 && nums1[i] + nums2[j as usize] > x {
                    j -= 1;
                }
                cnt += (j + 1) as i64; // nums1[i]可与nums2[0, j]组合，相加之和 <= x
                i += 1;
            }
            cnt >= k as i64
        };

        let mut left = nums1.first().unwrap() + nums2.first().unwrap();
        let mut right = nums1.last().unwrap() + nums2.last().unwrap();
        while left <= right {
            let mid = (left + right) / 2;
            if !check(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }
        let x = left; // left为和的边界值
        // println!("x: {}", x);

        // 把答案找出来，找边界值x的过程时间复杂度为O(nlogU)，不会超时。而1 <= k <= 10^4，所以以下双重循环也不会超时
        let mut ans = Vec::new();

        /* 这题答案要的是（虽然题面上没说），优先选距离小的数对，距离相等，优先选字典序小的数对。如果把 <= x 的数对全找出来然后排序取前k
        个，如果nums1和nums2的元素各自都相等，则全找出来的过程会超时(O(n^2))。

        参考宫水三叶题解，先找所有 < x 的，然后按字典序找够剩下的 == x 的（用到二分）。这样时间复杂度就不会达到O(n^2)
        */
        for i in 0..nums1.len() {
            for j in 0..nums2.len() {
                if nums1[i] + nums2[j] >= x {
                    break;
                }
                ans.push(vec![nums1[i], nums2[j]]); // 和 < x 的
            }
        }
        // 补 == x 的，直到ans够k个
        for i in 0..nums1.len() {
            let index1 = Self::lower_bound(&nums2, x - nums1[i] + 1);
            let index2 = Self::lower_bound(&nums2, x - nums1[i]);
            for _ in 0..(index1 - index2) {
                if ans.len() == k as usize { return ans; }
                ans.push(vec![nums1[i], x - nums1[i]]);
            }
        }

        ans
    }

    fn lower_bound(nums: &Vec<i32>, x: i32) -> i32 {
        let mut left = 0;
        let mut right = nums.len() as i32 - 1;
        while left <= right {
            let mid = (left + right) / 2;
            if nums[mid as usize] < x {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        left
    }

    // 参考宫水三叶题解，用多路归并。所有数对构成 m * n 行，用多路归并的方式选出前k个
    pub fn k_smallest_pairs_implementation2(nums1: Vec<i32>, nums2: Vec<i32>, k: i32) -> Vec<Vec<i32>> {
        let mut pq = BinaryHeap::new();
        let mut k = k;
        for i in 0..nums1.len() {
            pq.push(Reverse((nums1[i] + nums2[0], i, 0)));
        }
        let mut ans = Vec::new();
        while k > 0 {
            let (w, i, j) = pq.pop().unwrap().0;
            ans.push(vec![nums1[i], nums2[j]]);
            k -= 1;
            if j + 1 < nums2.len() {
                pq.push(Reverse((nums1[i] + nums2[j + 1], i, j + 1)));
            }
        }
        ans
    }
}

fn main() {
    println!("{:?}", Solution373::k_smallest_pairs([1,7,11].to_vec(), [2,4,6].into(), 3));
    println!("{:?}", Solution373::k_smallest_pairs([-10,-4,0,0,6].to_vec(), [3,5,6,7,8,100].into(), 10));
    println!("{:?}", Solution373::k_smallest_pairs([0,0,0,0,0].to_vec(), [-3,22,35,56,76].into(), 22));
    println!("{:?}", Solution373::k_smallest_pairs([0,0,0,0,0,2,2,2,2].to_vec(), [-3,22,35,56,76].into(), 22));

    println!("{:?}", Solution373::k_smallest_pairs_implementation2([1,7,11].to_vec(), [2,4,6].into(), 3));
    println!("{:?}", Solution373::k_smallest_pairs_implementation2([-10,-4,0,0,6].to_vec(), [3,5,6,7,8,100].into(), 10));
    println!("{:?}", Solution373::k_smallest_pairs_implementation2([0,0,0,0,0].to_vec(), [-3,22,35,56,76].into(), 22));
    println!("{:?}", Solution373::k_smallest_pairs_implementation2([0,0,0,0,0,2,2,2,2].to_vec(), [-3,22,35,56,76].into(), 22));
}