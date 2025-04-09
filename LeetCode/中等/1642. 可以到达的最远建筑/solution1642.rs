/*
url: https://leetcode.cn/problems/furthest-building-you-can-reach/
标签: 【题单】二分算法
*/
use std::cmp::Reverse;

use std::collections::*;

struct Solution;

impl Solution {
    // 二分答案，时间复杂度O(logn * nlogn)
    pub fn furthest_building(heights: Vec<i32>, bricks: i32, ladders: i32) -> i32 {
        let n = heights.len() as i32;

        let check = |m: i32| {
            let mut bricks = bricks;
            let mut ladders = ladders;
            let mut v = vec![];
            for i in 0..m as usize {
                v.push(heights[i + 1] - heights[i]);
            }
            v.sort_by(|x, y| {
                y.cmp(x)
            });
            for &h in &v {
                if h <= 0 {
                    continue;
                }
                if ladders == 0 && bricks < h {
                    return false;
                }
                if ladders > 0 {
                    ladders -= 1;
                }
                else {
                    bricks -= h;
                }
            }
            return true;
        };

        // 二分，把问题转化为固定建筑数量能否走到，check可以贪心。从而避开原问题的策略选择
        let (mut left, mut right) = (0, n - 1);
        while left <= right {
            let mid = left + (right - left) / 2;
            if check(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }
        right
    }

    /* 参考<https://leetcode.cn/problems/furthest-building-you-can-reach/solutions/468787/ke-yi-dao-da-de-zui-yuan-jian-zhu-by-zerotrac2/>，
    这题也可以不用二分固定上界，直接找策略。
    至少能走ladders步，然后，把遇到的h按从小到大排，当size > ladders后，优先把砖块拿出来填。直到砖块用尽，这时队列里剩下的大的h能用梯子满足。
    时间复杂度O(n)
    */
    pub fn furthest_building_implementation2(heights: Vec<i32>, bricks: i32, ladders: i32) -> i32 {
        let n = heights.len() as i32;
        let mut pq = BinaryHeap::new();
        // Rust的堆默认是大根堆，往里面放Reverse实现反转
        let mut bricks = bricks;
        for i in 1..n {
            let h = heights[i as usize] - heights[(i - 1) as usize];
            if h > 0 {
                pq.push(Reverse(h));
                if pq.len() > ladders as usize {
                    // 用brick
                    bricks -= pq.pop().unwrap().0; // use std::cmp::Reverse是一个元组结构体：pub struct Reverse<T>(pub T);
                    if bricks < 0 {
                        return i - 1; // 走不到i上
                    }
                }
            }
        }
        return n - 1;
    }
}

fn main() {
    println!("{}", Solution::furthest_building(vec![4,12,2,7,3,18,20,3,19], 10, 2));
    println!("{}", Solution::furthest_building_implementation2(vec![4,12,2,7,3,18,20,3,19], 10, 2));
}