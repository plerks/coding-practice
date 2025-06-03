/*
url: https://leetcode.cn/problems/minimize-the-maximum-difference-of-pairs/
标签: 【题单】二分算法, 二分 + 贪心
*/

struct Solution2616;

impl Solution2616 {
    pub fn minimize_max(nums: Vec<i32>, p: i32) -> i32 {
        let mut nums = nums;
        nums.sort();

        let check = |k| {
            let mut cnt = 0;
            let mut i = 1;
            while i < nums.len() {
                if nums[i] - nums[i - 1] <= k {
                    cnt += 1;
                    i += 2;
                }
                else { i += 1; }
            }
            return cnt >= p;
        };

        let mut left = 0;
        let mut right = nums.last().unwrap() - nums.first().unwrap();
        while left <= right {
            let mid = (left + right) / 2;
            if !check(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }
        left
    }
}

pub fn main() {
    println!("{}", Solution2616::minimize_max(vec![10,1,2,7,1,3], 2));
}