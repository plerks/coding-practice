/*
url: https://leetcode.cn/problems/minimize-maximum-of-array/
标签: 【题单】二分算法
*/

struct Solution2439;

impl Solution2439 {
    pub fn minimize_array_value(nums: Vec<i32>) -> i32 {
        let check = |k: i64| {
            let mut d = 0i64;
            for i in (1..nums.len()).rev() {
                let cur = nums[i] as i64 + d;
                d = std::cmp::max(0, (cur - k) as i64); // 会导致的nums[i - 1]的增量
            }
            d + nums[0] as i64 <= k as i64
        };
        
        let mut left = 0;
        let mut right = *nums.iter().max().unwrap();
        while left <= right {
            let mid = (left + right) / 2;
            if !check(mid as i64) { left = mid + 1; }
            else { right = mid - 1; }
        }
        left as i32
    }
}

pub fn main() {
    println!("{}", Solution2439::minimize_array_value(vec![3,7,1,6]));
    println!("{}", Solution2439::minimize_array_value(vec![10,1]));
    println!("{}", Solution2439::minimize_array_value(vec![2,7,9,19,5,19]));
}