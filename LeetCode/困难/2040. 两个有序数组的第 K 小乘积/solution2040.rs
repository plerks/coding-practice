/*
url: https://leetcode.cn/problems/kth-smallest-product-of-two-sorted-arrays/
标签: 【题单】二分算法
*/

struct Solution2040;

impl Solution2040 {
    /* 这题 1 <= nums1.length, nums2.length <= 5 * 10^4，1 <= k <= nums1.length * nums2.length，k很大
    不能像LeetCode786. 第 K 个最小的质数分数那样用多路归并了，得二分
    */
    pub fn kth_smallest_product(nums1: Vec<i32>, nums2: Vec<i32>, k: i64) -> i64 {
        let nums1: Vec<i64> = nums1.iter().map(|&x| x as i64).collect();
        let nums2: Vec<i64> = nums2.iter().map(|&x| x as i64).collect();
        let m = nums1.len() as i64;
        let n = nums2.len() as i64;

        /* 找第一个x，使得乘积 <= x 的组合个数 第一次 >= k。
        但是这题nums有负数，不能双指针，得分 nums1[i] 的正负，于是check里再套一次二分
        */
        let check = |x| {
            let mut cnt = 0;
            for &a in nums1.iter() {
                if a > 0 {
                    // 找nums2中最后一个 a * b <= x 的位置，区间对 a * b <= x 从是到否
                    let mut l = 0; let mut r = n - 1;
                    while l <= r {
                        let mid = (l + r) / 2;
                        if a * nums2[mid as usize] <= x { l = mid + 1; } else { r = mid - 1; }
                    }
                    let p = r;
                    // [0, p]符合与a乘积 <= x
                    cnt += p + 1;
                }
                else {
                    // a <= 0，找nums2中第一个 a * b <= x 的位置，区间对 a * b <= x 从否到是
                    let mut l = 0; let mut r = n - 1;
                    while l <= r {
                        let mid = (l + r) / 2;
                        // dbg!(a * nums2[mid as usize]);
                        if !(a * nums2[mid as usize] <= x) { l = mid + 1; } else { r = mid - 1; }
                    }
                    let p = l;
                    // [p, n)符合与a乘积 <= x
                    cnt += n - p;
                }
            }
            cnt < k as i64
        };

        let a = nums1[0]; let b = nums1[m as usize - 1]; let c = nums2[0]; let d = nums2[n as usize - 1];
        let v = vec![a * c, a * d, b * c, b * d];

        let mut left = *v.iter().min().unwrap();
        let mut right = *v.iter().max().unwrap();
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }

        left
    }
}

fn main() {
    // println!("{}", Solution2040::kth_smallest_product([2,5].to_vec(), [3,4].to_vec(), 2));
    // println!("{}", Solution2040::kth_smallest_product([-4,-2,0,3].to_vec(), [2,4].to_vec(), 6));
    // println!("{}", Solution2040::kth_smallest_product([-2,-1,0,1,2].to_vec(), [-3,-1,2,4,5].to_vec(), 3));
    println!("{}", Solution2040::kth_smallest_product([-8,-8,3,7].to_vec(), [-1].to_vec(), 3));
}