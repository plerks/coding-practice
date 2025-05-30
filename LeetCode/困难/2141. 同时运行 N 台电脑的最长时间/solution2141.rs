/*
url: https://leetcode.cn/problems/furthest-building-you-can-reach/
参考: https://leetcode.cn/problems/maximum-running-time-of-n-computers/solutions/1214440/liang-chong-jie-fa-er-fen-da-an-pai-xu-t-grd8/
标签: 【题单】二分算法, [mark]
*/

use std::collections::*;

struct Solution;

// 这题似乎能启发那个摊煎饼的问题，具体见./make_pancakes.rs

impl Solution {
    // 解法一，超时，17 / 52 个通过的测试用例，check时多了一重循环
    pub fn max_run_time_tle(n: i32, batteries: Vec<i32>) -> i64 {
        let mut pq = BinaryHeap::new();

        let mut check = |mid| -> bool {
            pq.clear();
            for battery in batteries.iter() {
                pq.push(*battery);
            }
            for i in 0..mid { // 轮次
                // 检查这一轮是否能给所有电池充电
                if pq.len() < n as usize { // 有剩余电量的电池不够n个
                    return false;
                }
                let mut vec = vec![];
                for j in 0..n {
                    vec.push(pq.pop().unwrap());
                }
                for v in vec {
                    if v - 1 > 0 {
                        pq.push(v - 1);
                    }
                }
            }
            true
        };

        let mut left = 0;
        let mut right = batteries.iter().sum::<i32>() / n;
        while left <= right {
            let mut mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        right as i64
    }

    // 换一个思路，每个机器要运行t时，那么就要用电池的量去填充这n个机器的t时间长度，不过一个电池不能出现在多列，比如不能：
    // 电脑1    电脑2    ...
    //   x       y
    //   x       x
    //   x
    // 那么，如果一个电池电量 > 行数t，多出来的部分是用不上的。把矩阵按列拉直，每个电池能填充 min(电量, t) 的长度
    // 然后判断 cnt 是否 >= n * t 即可知道check结果。这个判断的充要性为：
    // 去除 > t 的部分后，必须要 cnt >= n * t 才可能填满表格；而一旦 cnt >= n * t，按上面的过程可以生成一种方案。因此充要
    pub fn max_run_time(n: i32, batteries: Vec<i32>) -> i64 {
        let check = |t: i64| -> bool {
            let mut cnt = 0i64;
            for &x in batteries.iter() {
                let x = std::cmp::min(x as i64, t);
                cnt += x as i64;
            }
            return cnt >= (n as i64) * t;
        };

        let mut left = 0;
        let mut right = batteries.iter().map(|&x| x as i64).sum::<i64>() / n as i64;
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        right as i64
    }

    // 参考灵茶题解，不使用二分的解法
    // 供电时间的上界是 bound = ⌊sum / n⌋，把batteries从大到小排序，从最大的遍历，
    // 若当前电池电量 > bound，则多出去的部分也用不了，问题变为 n - 1 个电脑的子问题；
    // 若当前电池电量 <= bound，则 sum >= n * ⌊sum / n⌋ = n * bound，于是按上一种解法的排布方案，排满bound行是可行的（上界能取到），每个电池都不会出现跨列；
    // 这解法很巧妙
    pub fn max_run_time_implementation2(n: i32, batteries: Vec<i32>) -> i64 {
        let mut sum = batteries.iter().map(|&x| x as i64).sum::<i64>();
        let mut batteries = batteries;
        batteries.sort_by(|x, y| y.cmp(x));
        let mut n = n as i64;
        for &b in batteries.iter() {
            let b = b as i64;
            if b > sum / n {
                sum -= b;
                n -= 1;
                continue;
            }
            return sum / n;
        }
        -1
    }
}

pub fn main() {
    // println!("{}", Solution::max_run_time_tle(2, vec![3,3,3]));
    // println!("{}", Solution::max_run_time_tle(3, vec![10,10,3,5]));

    println!("{}", Solution::max_run_time(2, vec![3,3,3]));
    println!("{}", Solution::max_run_time(3, vec![10,10,3,5]));

    println!("{}", Solution::max_run_time_implementation2(2, vec![3,3,3]));
    println!("{}", Solution::max_run_time_implementation2(3, vec![10,10,3,5]));
}