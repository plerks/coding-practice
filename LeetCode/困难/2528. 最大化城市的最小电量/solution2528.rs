/*
url: https://leetcode.cn/problems/maximize-the-minimum-powered-city/
参考: https://leetcode.cn/problems/maximize-the-minimum-powered-city/solutions/2050272/er-fen-da-an-qian-zhui-he-chai-fen-shu-z-jnyv/
标签: 【题单】二分算法, 前缀和, 差分, 贪心
*/

struct Solution2528;

impl Solution2528 {
    /*
    思路：二分答案，如果一个station的电量不够，则需要消耗k给其增长电量，把新电站贪心地建在station + r处是最优的，
    但是要处理这个新建的电站对其它点的影响，我想的是用线段树，用线段树的思路应该是可以的，但是看题解不需要用线段树。
    参考灵茶题解：

    1. 如何计算一开始时各个station的电量？
    一个station的电量是 [i - r, i + r] 间的所有电站的数量，于是用前缀和来求

    2. 新建一个电站，这个电站会对多个station有影响，如何处理？
    差分，这样就能在新增电站后，继续往右走时仍然能计算出当前遍历到的station的电量

    这题之前应该做过一道类似的，但是想不起来是哪道了
    */
    pub fn max_power(stations: Vec<i32>, r: i32, k: i32) -> i64 {
        let n = stations.len();
        let stations: Vec<i64> = stations.iter().map(|x| *x as i64).collect();
        let r = r as i64;
        let k = k as i64;

        let mut pre = vec![0; n + 1]; // 前缀和
        for i in 0..n {
            pre[i + 1] = pre[i] + stations[i];
        }
        let mut power = vec![0; n]; // 当前各个station的电量
        for i in 0..n {
            power[i] = pre[std::cmp::min(n, i + r as usize + 1)] - pre[std::cmp::max(0, i as i64 - r) as usize];
        }

        let check = |c| {
            let mut diff = vec![0; n]; // 差分数组
            let mut k = k; // 剩余新建电站机会
            let mut delta = 0; // 当前累积的差分量(或者说差分数组的前缀和)

            for i in 0..stations.len() {
                delta += diff[i];
                let x = power[i];
                let request = std::cmp::max(0, c - x - delta);
                if request > 0 {
                    if request > k { return false; }
                    k -= request;
                    delta += request; // 增量
                    if i + 2 * r as usize + 1 < n {
                        diff[i + 2 * r as usize + 1] -= request; // 减量，电站建在 i + 2 * r 的位置，到 i + 2 * r + 1 当前的累积量会 - request
                    }
                }
            }
            
            true
        };

        let mut left = *power.iter().min().unwrap();
        let mut right = left + k;
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
    println!("{}", Solution2528::max_power(vec![1,2,4,5,0], 1, 2));
    println!("{}", Solution2528::max_power(vec![4,4,4,4], 0, 3));
    println!("{}", Solution2528::max_power(vec![4,2], 1, 1));
}