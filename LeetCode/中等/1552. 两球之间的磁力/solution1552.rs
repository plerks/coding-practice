/*
url: https://leetcode.cn/problems/magnetic-force-between-two-balls/
标签: 【题单】二分算法
*/

struct Solution1552;

// 此题与`LeetCode2517. 礼盒的最大甜蜜度`完全相同
impl Solution1552 {
    pub fn max_distance(mut position: Vec<i32>, m: i32) -> i32 {
        position.sort_unstable();

        // ... x1 ... x2 ... x3 ... 如果这样合法，那么把x1换成第一个数也合法，所以第一个数一定被选，后同
        let check = |d| {
            let mut last = *position.first().unwrap();
            let mut cnt = 1;
            for i in 1..position.len() {
                let x = position[i];
                if x - last >= d {
                    cnt += 1;
                    last = x;
                }
            }
            cnt >= m
        };

        let mut left = 0;
        let mut right = position.last().unwrap() - position.first().unwrap();
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        right
    }
}

pub fn main() {
    println!("{}", Solution1552::max_distance(vec![1,2,3,4,7], 3));
}