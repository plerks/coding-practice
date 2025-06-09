/*
url: https://leetcode.cn/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/
参考: https://leetcode.cn/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/solutions/2286593/san-chong-suan-fa-bao-li-er-fen-da-an-du-k1vd/
相关: LeetCode373. 查找和最小的 K 对数字, LeetCode786. 第 K 个最小的质数分数
标签: 【题单】二分算法, 多路归并
*/

use std::{cmp::Reverse, collections::BinaryHeap};

struct Solution1439;

impl Solution1439 {
    /* 参考灵茶题解，
    1 <= m, n <= 40，1 <= k <= min(200, n ^ m)，规模都很小，
    每行都要取一个数出来，第一行从小到大取，用多路归并的方式与第二行的数组合，这样就得到了前面行的k个最小组合。
    这样，每次存量数字与当前行组合求最小的k个和，到最后一行就是每行取一个数字，并得到了k个最小和
    时间复杂度O(mklog(min(n, k)))
    */
    pub fn kth_smallest(mat: Vec<Vec<i32>>, k: i32) -> i32 {
        let mut last_row = vec![0];
        for row in mat.iter() {
            last_row = Self::k_smallest_pairs(&last_row, &row, k);
            // 或者用：last_row = Self::k_smallest_pairs_implementation2(&last_row, &row, k);
        }
        
        *last_row.last().unwrap()
    }

    // LeetCode373. 查找和最小的 K 对数字
    // 一开始，优先队列中放入了min(n, k)个元素，后续出一个拉进一个，总时间复杂度klog(min(n, k))
    fn k_smallest_pairs(nums1: &Vec<i32>, nums2: &Vec<i32>, k: i32) -> Vec<i32> {
        let mut pq = BinaryHeap::new();
        let mut k = k;
        for i in 0..nums1.len() {
            pq.push(Reverse((nums1[i] + nums2[0], i, 0)));
        }
        let mut ans = Vec::new();
        while k > 0 && !pq.is_empty() {
            let (w, i, j) = pq.pop().unwrap().0;
            ans.push(nums1[i] + nums2[j]);
            k -= 1;
            if j + 1 < nums2.len() {
                pq.push(Reverse((nums1[i] + nums2[j + 1], i, j + 1)));
            }
        }
        ans
    }

    /* 灵茶题解中原本的写法，不先把([0..nums1.len()), 0)预先都放入队列中作为多路归并的启动点，而是(i, 0)这种点出队时拉入(i + 1, 0)。
    效果是一样的，不会发生(1, 2)和(2, 1)都在队列中，然后二者都产生(3, 3)，导致重复计数的问题。
    */
    fn k_smallest_pairs_implementation2(nums1: &Vec<i32>, nums2: &Vec<i32>, k: i32) -> Vec<i32> {
        let mut pq: BinaryHeap<Reverse<(i32, usize, usize)>> = BinaryHeap::new();
        let mut k = k;
        let mut ans = Vec::new();
        pq.push(Reverse((nums1[0] + nums2[0], 0, 0))); // 只推入(0, 0)作为种子
        while k > 0 && !pq.is_empty() {
            let (w, i, j) = pq.pop().unwrap().0;
            ans.push(nums1[i] + nums2[j]);
            k -= 1;
            if j == 0 && i + 1 < nums1.len() { // (i, 0)这种点把(i + 1, 0)拉进来，注意要j == 0
                pq.push(Reverse((nums1[i + 1] + nums2[j], i + 1, j)));
            }
            if j + 1 < nums2.len() {
                pq.push(Reverse((nums1[i] + nums2[j + 1], i, j + 1)));
            }
        }
        ans
    }
}

fn main() {
    println!("{}", Solution1439::kth_smallest([[1,3,11],[2,4,6]].map(|row| row.to_vec()).to_vec(), 5));
    println!("{}", Solution1439::kth_smallest([[1,3,11],[2,4,6]].map(|row| row.to_vec()).to_vec(), 9));
    println!("{}", Solution1439::kth_smallest([[1,10,10],[1,4,5],[2,3,6]].map(|row| row.to_vec()).to_vec(), 7));
}