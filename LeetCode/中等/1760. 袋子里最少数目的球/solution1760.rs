/*
url: https://leetcode.cn/problems/minimum-limit-of-balls-in-a-bag/
标签: 【题单】二分算法
*/

struct Solution1760;

impl Solution1760 {
    pub fn minimum_size(nums: Vec<i32>, max_operations: i32) -> i32 {
        let check = |k| {
            let mut operation_cnt = 0i64;
            for &x in nums.iter() {
                operation_cnt += ((x + k - 1) / k - 1) as i64; // 最开始1堆，分完 (x + k - 1) / k 堆，操作次数为二者相减
            }
            return operation_cnt <= max_operations as i64;
        };

        let mut left = 1;
        let mut right = *nums.iter().max().unwrap();

        while left <= right {
            let mid = (left + right) >> 1;
            if !check(mid) {
                left = mid + 1;
            }
            else { right = mid - 1; }
        }
        left
    }
}

pub fn main() {
    println!("{}", Solution1760::minimum_size(vec![2,4,8,2], 4));
    println!("{}", Solution1760::minimum_size(vec![9], 200));
    println!("{}", Solution1760::minimum_size(vec![1000000000,1000000000,1000000000], 1000000000));
}