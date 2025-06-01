/*
url: https://leetcode.cn/problems/sell-diminishing-valued-colored-balls/
标签: 【题单】二分算法, 差分
*/

use std::collections::BinaryHeap;

struct Solution1648;

impl Solution1648 {
    // 超时，数据范围有1e9，[1000000000] 1000000000 这个样例过不去
    pub fn max_profit_tle(inventory: Vec<i32>, orders: i32) -> i32 {
        const MOD: i64 = 1e9 as i64 + 7;
        let mut pq = BinaryHeap::new();
        for &x in inventory.iter() {
            pq.push(x as i64);
        }
        let mut orders = orders;
        let mut ans = 0i64;
        while orders > 0 {
            let mut x = pq.pop().unwrap();
            ans += x;
            x -= 1;
            pq.push(x);
            orders -= 1;
        }
        (ans % MOD) as i32
    }

    // 用二分来找分割线。时间复杂度 O(nlogU + n)，U为max(inventory)，n为inventory元素个数
    pub fn max_profit(inventory: Vec<i32>, orders: i32) -> i32 {
        let mut inventory = inventory;
        // inventory.sort(); // 这里不用排序
        // 找一条线，使这条线及以上的球的数量 >= orders
        let check = |k| {
            let mut sum = 0i64;
            for &x in inventory.iter() {
                sum += std::cmp::max(0, (x - k) as i64);
            }
            return sum >= orders as i64;
        };

        let mut left = 0;
        let mut right = *inventory.iter().max().unwrap();
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        // left是第一个值，以这条线为分割(包含这条线)，能选出orders个球
        let mut ans = 0i64;
        const MOD: i64 = 1e9 as i64 + 7;
        let mut orders = orders; // 还要选几个球
        for &x in inventory.iter() {
            if x > left { // [left + 1, x]的全选
                ans = (ans + (left + 1 + x) as i64 * (x - left) as i64 / 2) % MOD;
                orders -= x - left;
            }
        }
        ans = (ans + left as i64 * orders as i64) % MOD; // 在线上补球

        ans as i32
    }

    /* 上面用二分来算边界线，效率没有问题，只是没那么直接。可以用差分的方式来直接找分割线的位置。
    思路为，把球按数量排序后，从高到底来看，在到达下一个边界之前，会新出现一个矩形区域 w * h，计算这个区域新可用的球的数量
    加上已存量的球的数量是否够orders。若够则可以计算该有的高度，然后得到边界线位置。若不够则继续往下扫描。

    时间复杂度 O(nlogn + n + n)
    */
    pub fn max_profit_implementation2(inventory: Vec<i32>, orders: i32) -> i32 {
        let mut inventory: Vec<i64> = inventory.iter().map(|x| *x as i64).collect();
        let orders = orders as i64; // 直接全转成i64，免得后面运算时写一堆as i64
        
        inventory.sort();
        let mut sum = 0i64;
        let mut edge = 0;
        for i in (0..inventory.len()).rev() {
            let h = inventory[i] - if i as i32 - 1 < 0 { 0 } else { inventory[i - 1] };
            let w = (inventory.len() - i) as i64;
            if sum + w * h >= orders {
                let d = (orders - sum + (w - 1)) / w;
                edge = inventory[i] - d + 1; // 题目保证inventory总的球的数量够orders，最后一定会走到这种情况
                break;
            }
            else {
                sum += w * h;
            }
        }
        let mut ans = 0i64;
        const MOD: i64 = 1e9 as i64 + 7;
        let mut orders = orders; // 还要选几个球
        for &x in inventory.iter() {
            if x > edge {
                ans = (ans + (edge + 1 + x) as i64 * (x - edge) as i64 / 2) % MOD;
                orders -= x - edge;
            }
        }
        ans = (ans + edge as i64 * orders as i64 % MOD) % MOD; // 在边界线那行补球

        ans as i32
    }
}

pub fn main() {
    println!("{}", Solution1648::max_profit(vec![2,5], 4));
    println!("{}", Solution1648::max_profit(vec![1000000000], 1000000000));

    println!("{}", Solution1648::max_profit_implementation2(vec![2,5], 4));
    println!("{}", Solution1648::max_profit_implementation2(vec![1000000000], 1000000000));
}