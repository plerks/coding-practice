/*
url: https://leetcode.cn/problems/minimized-maximum-of-products-distributed-to-any-store/
标签: 【题单】二分算法
*/

struct Solution2064;

impl Solution2064 {
    pub fn minimized_maximum(n: i32, quantities: Vec<i32>) -> i32 {
        let check = |k| {
            let mut i = 0;
            for &q in quantities.iter() {
                i += (q + k - 1) / k;
                if i > n {
                    return false;
                }
            }
            true
        };
        
        let mut left = 1;
        let mut right = *quantities.iter().max().unwrap();
        while left <= right {
            let mid = (left + right) / 2;
            if !check(mid) {
                left = mid + 1;
            }
            else { right = mid - 1; }
        }
        left
    }
}

pub fn main() {
    println!("{}", Solution2064::minimized_maximum(6, vec![11, 6]));
    println!("{}", Solution2064::minimized_maximum(1, vec![1]));
}