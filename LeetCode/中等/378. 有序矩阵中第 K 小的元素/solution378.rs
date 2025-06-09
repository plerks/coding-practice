/*
url: https://leetcode.cn/problems/kth-smallest-element-in-a-sorted-matrix/
相关: LeetCode1508. 子数组和排序后的区间和, LeetCode668. 乘法表中第k小的数
标签: 【题单】二分算法
*/

struct Solution378;

impl Solution378 {
    // 二分答案，check过程中也用到了二分，时间复杂度O(logU * nlogn)，U为 max(matrix) - min(matrix)
    pub fn kth_smallest(matrix: Vec<Vec<i32>>, k: i32) -> i32 {
        let n = matrix.len(); // matrix为n * n的矩阵

        // <= x 的数的个数是否 < k，找第一个'否'
        let check = |x| {
            let mut cnt = 0;
            for i in 0..n {
                // 查找
                let bound = Self::upper_bound(&matrix[i], x);
                cnt += bound;
            }
            cnt < k
        };

        let mut left = matrix[0][0];
        let mut right = matrix[n - 1][n - 1];
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        left
    }

    // 找第一个 > x 的数的下标
    fn upper_bound(vec: &Vec<i32>, x: i32) -> i32 {
        let mut left: i32 = 0;
        let mut right: i32 = vec.len() as i32 - 1;
        while left <= right {
            let mid = (left + right) / 2;
            if vec[mid as usize] <= x { left = mid + 1; }
            else { right = mid - 1; }
        }
        left
    }

    /* 参考官方题解，check可以做到O(n)，matrix行列都是单增的，这就有个关键性质，如果在第一行找到了
    x所应在的分界线，后面的行这个分界位置一定是单调往左移动的，因此可以优化。
    时间复杂度O(logU * n)
    */
    pub fn kth_smallest_implementation2(matrix: Vec<Vec<i32>>, k: i32) -> i32 {
        let n = matrix.len(); // matrix为n * n的矩阵

        // <= x 的数的个数是否 < k，找第一个'否'
        let check = |x| {
            let mut cnt = 0;
            let mut i: i32 = 0;
            let mut j: i32 = n as i32 - 1;
            while i < n as i32 {
                while j >= 0 && matrix[i as usize][j as usize] > x {
                    j -= 1;
                }
                cnt += j + 1;
                i += 1;
            }
            cnt < k
        };

        let mut left = matrix[0][0];
        let mut right = matrix[n - 1][n - 1];
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        left
    }

    /* check时还有一种写法，
    第k个数x位置示意为：{ a a } { x [x] x } { b b }
    那么，
    x 既是 <= x 的数的个数第一次 >= k
    也是 < x 的数的个数最后一次 < k

    LeetCode1508中用： < x 的数的个数最后一次 < k 这个性质要合适一点
    */
    pub fn kth_smallest_implementation3(matrix: Vec<Vec<i32>>, k: i32) -> i32 {
        let n = matrix.len(); // matrix为n * n的矩阵

        // < x 的数的个数是否 < k，找最后一个'是'
        let check = |x| {
            let mut cnt = 0;
            let mut i: i32 = 0;
            let mut j: i32 = n as i32 - 1;
            while i < n as i32 {
                while j >= 0 && matrix[i as usize][j as usize] >= x {
                    j -= 1;
                }
                cnt += j + 1;
                i += 1;
            }
            cnt < k
        };

        let mut left = matrix[0][0];
        let mut right = matrix[n - 1][n - 1];
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

    // 待做: 力扣提到这题有O(n)的解法，是篇论文，见[Selection in X+Y and matrices with sorted rows and columns](http://www.cse.yorku.ca/~andy/pubs/X+Y.pdf)
}

pub fn main() {
    println!("{}", Solution378::kth_smallest([[1,5,9],[10,11,13],[12,13,15]].map(|row| row.to_vec()).to_vec(), 8));
    println!("{}", Solution378::kth_smallest([[-5]].map(|row| row.to_vec()).to_vec(), 1));

    println!("{}", Solution378::kth_smallest_implementation2([[1,5,9],[10,11,13],[12,13,15]].map(|row| row.to_vec()).to_vec(), 8));
    println!("{}", Solution378::kth_smallest_implementation2([[-5]].map(|row| row.to_vec()).to_vec(), 1));

    println!("{}", Solution378::kth_smallest_implementation3([[1,5,9],[10,11,13],[12,13,15]].map(|row| row.to_vec()).to_vec(), 8));
    println!("{}", Solution378::kth_smallest_implementation3([[-5]].map(|row| row.to_vec()).to_vec(), 1));
}