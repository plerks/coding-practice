/*
url: https://leetcode.cn/problems/sqrtx/
标签: 【题单】二分算法
*/

struct Solution69;

impl Solution69 {
    pub fn my_sqrt(x: i32) -> i32 {
        // 寻找 t^2 <= x 的最后一个t
        let mut left = 0;
        let mut right = x as i64;
        while left <= right {
            let mid = (left + right) / 2;
            if mid * mid <= x as i64 { left = mid + 1; }
            else { right = mid - 1; }
        }
        right as i32
    }
}

fn main() {
    // println!("{}", Solution69::my_sqrt(4));
    // println!("{}", Solution69::my_sqrt(8));
    println!("{}", Solution69::my_sqrt(2147395599));
}