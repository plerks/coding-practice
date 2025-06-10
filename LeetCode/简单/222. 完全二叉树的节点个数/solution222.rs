/*
url: https://leetcode.cn/problems/count-complete-tree-nodes/
参考: https://leetcode.cn/problems/count-complete-tree-nodes/solutions/495655/wan-quan-er-cha-shu-de-jie-dian-ge-shu-by-leetco-2/
标签: 【题单】二分算法, 完全二叉树, 完全二叉树节点数, [special]
*/

use std::rc::Rc;
use std::cell::RefCell;

#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
  pub val: i32,
  pub left: Option<Rc<RefCell<TreeNode>>>,
  pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
  #[inline]
  pub fn new(val: i32) -> Self {
    TreeNode {
      val,
      left: None,
      right: None
    }
  }
}

struct Solution222;

impl Solution222 {
    /* 参考官方题解，奇妙的解法，利用完全二叉树的性质，可以在o(n)时间内求出完全二叉树的节点个数，都不需要遍历一遍树。
    首先，一直往左下走，可以知道完全二叉树的高度（logn时间）
    由于是完全二叉树，倒数第二层往上是满的，节点数为2^h - 1。
    现在问题是要确定最下面一层有多少个节点，把根节点编号为1，则最后一层节点编号范围为[2^h, 2^(h+1) - 1]。注意节点编号同样是 <= 左上部 的节点数量。
    用二分去检查，由于完全二叉树最下面一层从左往右排的，所以只需检查最后那个点有没有就行。
    假设检查编号为k的节点是否存在，完全二叉树有个性质，根节点从1开始编号的情况下，编号的二进制能代表路径，
    k的二进制中，最高位一定为1，剩下的位从左到右为路径，0代表左，1代表右。例如，编号为6(0b110)，则根到这个节点的路径为根 -> 右(1) -> 左(0)

    时间复杂度O(h * h) = O(logn * logn)
    */
    pub fn count_nodes(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        if root.is_none() { return 0; }
        let root = root.unwrap();
        let mut h = 0;
        let mut node = root.clone();
        while let Some(lchild) = node.clone().borrow().left.clone() { // node是个指针，复制开销不大，复制目的是为了避免双重借用
            h += 1;
            node = lchild;
        }
        
        // 节点个数范围 [2^h - 1, 2^(h+1) - 1]
        let mut left = (1 << h) - 1;
        let mut right = (1 << (h + 1)) - 1;
        while left <= right {
            let mid = (left + right) / 2;
            if Self::check(&root, mid) { left = mid + 1; }
            else { right = mid - 1; }
        }

        right
    }

    // 完全二叉树是否有k个节点，也即编号为k处是否有节点
    fn check(root: &Rc<RefCell<TreeNode>>, k: i32) -> bool {
        if k == 0 { return true; }
        let mut cur = root.clone();
        let bitlen = 32 - k.leading_zeros();
        for i in (0..bitlen - 1).rev() {
            let path_bit = (k >> i) & 1;
            if path_bit == 0 {
                let op = cur.borrow().left.clone();
                match op {
                    Some(next) => cur = next,
                    None => return false
                }
            }
            else {
                let op = cur.borrow().right.clone();
                match op {
                    Some(next) => cur = next,
                    None => return false
                }
            }
        }

        true
    }
}

fn main() {
    let node1 = Rc::new(RefCell::new(TreeNode { val: 1, left: None, right: None }));
    let node2 = Rc::new(RefCell::new(TreeNode { val: 2, left: None, right: None }));
    let node3 = Rc::new(RefCell::new(TreeNode { val: 3, left: None, right: None }));
    let node4 = Rc::new(RefCell::new(TreeNode { val: 4, left: None, right: None }));
    let node5 = Rc::new(RefCell::new(TreeNode { val: 5, left: None, right: None }));

    node1.borrow_mut().left = Some(node2.clone()); // 把Rc clone一下，clone得到的是指针，内容物是同一份
    node1.borrow_mut().right = Some(node3.clone());
    node2.borrow_mut().left = Some(node4.clone());
    node2.borrow_mut().right = Some(node5.clone());

    println!("{}", Solution222::count_nodes(Some(node1)));

    println!("=========");

    let node1 = Rc::new(RefCell::new(TreeNode { val: 1, left: None, right: None }));
    println!("{}", Solution222::count_nodes(Some(node1)));
}