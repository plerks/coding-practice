/*
url: https://leetcode.cn/problems/k-th-smallest-prime-fraction/
相关: LeetCode373. 查找和最小的 K 对数字, LeetCode1439. 有序矩阵中的第 k 个最小数组和
参考: https://leetcode.cn/problems/k-th-smallest-prime-fraction/solutions/1127751/gong-shui-san-xie-yi-ti-shuang-jie-you-x-8ymk/
标签: 【题单】二分算法, 多路归并, 二分 + 双指针, 浮点数二分
*/

use std::collections::BinaryHeap;

struct Solution786;

struct Quotient {
    dividend: i32,
    divisor: i32
}

impl Eq for Quotient {}

impl PartialEq for Quotient {
    fn eq(&self, other: &Self) -> bool {
        self.dividend * other.divisor == self.divisor * other.dividend
    }
}

impl PartialOrd for Quotient {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        return Some(self.cmp(other));
    }
}

impl Ord for Quotient {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        match (self.dividend * other.divisor).cmp(&(self.divisor * other.dividend)) {
            std::cmp::Ordering::Less => std::cmp::Ordering::Greater,
            std::cmp::Ordering::Equal => std::cmp::Ordering::Equal,
            std::cmp::Ordering::Greater => std::cmp::Ordering::Less,
        }
    }
}

// kth_smallest_prime_fraction_implementation2()不能直接记值了，要记位置
struct Fraction<'a> {
    i: i32,
    j: i32,
    arr: &'a [i32]
}

impl<'a> Eq for Fraction<'a> {}

impl<'a> PartialEq for Fraction<'a> {
    fn eq(&self, other: &Self) -> bool {
        self.arr[self.i as usize] * self.arr[other.j as usize] == self.arr[self.j as usize] * self.arr[other.i as usize]
    }
}

impl<'a> PartialOrd for Fraction<'a> {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        return Some(self.cmp(other));
    }
}

impl<'a> Ord for Fraction<'a> {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        match (self.arr[self.i as usize] * self.arr[other.j as usize]).cmp(&(self.arr[self.j as usize] * self.arr[other.i as usize])) {
            std::cmp::Ordering::Less => std::cmp::Ordering::Greater,
            std::cmp::Ordering::Equal => std::cmp::Ordering::Equal,
            std::cmp::Ordering::Greater => std::cmp::Ordering::Less,
        }
    }
}

impl Solution786 {
    // 题目范围小，直接暴力就能过，2 <= arr.length <= 1000，时间复杂度O(n^2)
    pub fn kth_smallest_prime_fraction(arr: Vec<i32>, k: i32) -> Vec<i32> {
        let mut pq = BinaryHeap::new();
        for &i in arr.iter() {
            for &j in arr.iter() {
                pq.push(Quotient { dividend: i, divisor: j });
            }
        }
        let mut ans = Quotient { dividend: -1, divisor: -1 };
        for _ in 0..k {
            ans = pq.pop().unwrap();
        }

        vec![ans.dividend, ans.divisor]
    }

    // 多路归并，时间复杂度O(klogk)
    pub fn kth_smallest_prime_fraction_implementation2(arr: Vec<i32>, k: i32) -> Vec<i32> {
        let mut pq = BinaryHeap::new();
        let n = arr.len();
        for i in 0..n {
            pq.push(Fraction { i: i as i32, j: n as i32 - 1, arr: &arr }); // 种子
        }
        let mut k = k;
        while k > 1 {
            let frac = pq.pop().unwrap();
            k -= 1;
            if frac.j - 1 > frac.i {
                pq.push(Fraction { i: frac.i as i32, j: frac.j - 1, arr: &arr });
            }
        }
        let frac = pq.pop().unwrap(); // 这是第k个
        
        vec![arr[frac.i as usize], arr[frac.j as usize]]
    }

    // 二分，如何高效检查？双指针，i变大，j也要变大，才能找到分数 <= x 的位置
    // 参考宫水三叶题解，这里二分的话由于是分数，涉及浮点数二分，如何获取答案？check时记录最接近 x 的arr组合
    // 能通过，不过二分最好不涉及浮点数
    pub fn kth_smallest_prime_fraction_implementation3(arr: Vec<i32>, k: i32) -> Vec<i32> {
        let episilon = 1e-8;
        let mut ans0 = -1;
        let mut ans1 = -1;

        // 找第一个个数 >= k 的分数值，个数指<= 分数值的组合个数。注意这样二分的条件，算出的答案一定是arr中有对应的组合得到的
        let mut check = |x| {
            let mut j = 1;
            let mut cnt = 0;
            for i in 0..arr.len() {
                let a = arr[i];
                j = std::cmp::max(j, i + 1);
                while j < arr.len() && a as f64 / arr[j] as f64 > x {
                    j += 1;
                }
                // arr[i] / arr[j]是第一个 <= x 的
                if j < arr.len() {
                    let b = arr[j];
                    if f64::abs(a as f64 / b as f64 - x) < episilon {
                        ans0 = a;
                        ans1 = b;
                    }
                }
                // [j, n)
                cnt += arr.len() - j;
            }
            cnt < k as usize
        };

        let mut left = 0f64;
        let mut right = 1.0;
        while right - left > episilon {
            let mid = (left + right) / 2.0;
            if check(mid) {
                left = mid;
            }
            else {
                right = mid;
            }
        }
        // println!("left: {}", left);

        vec![ans0, ans1]
    }
}

fn main() {
    println!("{:?}", Solution786::kth_smallest_prime_fraction(vec![1,2,3,5], 3));
    println!("{:?}", Solution786::kth_smallest_prime_fraction_implementation2(vec![1,2,3,5], 3));
    println!("{:?}", Solution786::kth_smallest_prime_fraction_implementation3(vec![1,2,3,5], 3));
}