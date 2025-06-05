/*
url: https://leetcode.cn/problems/maximum-tastiness-of-candy-basket/
标签: 【题单】二分算法
*/

struct Solution2517;

impl Solution2517 {
    pub fn maximum_tastiness(price: Vec<i32>, k: i32) -> i32 {
        let mut price = price;
        price.sort_unstable();

        // ... x1 ... x2 ... x3 ... 如果这样合法，那么把x1换成第一个数也合法，所以第一个数一定被选，后同
        let check = |d| {
            let mut last = *price.first().unwrap();
            let mut cnt = 1;
            for i in 1..price.len() {
                let x = price[i];
                if x - last >= d {
                    cnt += 1;
                    last = x;
                }
            }
            cnt >= k
        };

        let mut left = 0;
        let mut right = price.last().unwrap() - price.first().unwrap();
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
    println!("{}", Solution2517::maximum_tastiness(vec![13,5,1,8,21,2], 3));
}