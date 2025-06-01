/*
url: https://leetcode.cn/problems/maximum-number-of-tasks-you-can-assign/
参考: https://leetcode.cn/problems/maximum-number-of-tasks-you-can-assign/solutions/3655745/er-fen-da-an-tan-xin-pi-pei-shuang-duan-avcrj/
标签: 【题单】二分算法, 二分 + 贪心
*/

use std::collections::*;

struct Solution2071;

impl Solution2071 {
    /* 参考灵茶题解，
    想的时候又忘了二分简化改变了思考方式了，想成先不吃药，用双指针让每个人去完成自己能完成的最大task，然后考虑吃药，让剩余
    的人的大端去完成剩余task的小端。但是这样不行，比如只有一颗药，这颗药给最强worker或最弱worker吃的最优方案都会存在。
    二分确定下来之后，只需选x个能完成的task就行了，当然选最强的worker和最弱的task。也就是典型的 二分 + 贪心。
    选出 x 对之后还需要考虑组合方式，例如 5 5 8 和 4 6 6，刚好对位匹配不是最优，得 [5,6] [5,6] [8, 4 + 5] 最优。
    于是，先不吃药，让每个人去完成最大能完成的任务，然后再考虑吃药的问题吗？
    不行，例如 10 10 16 和 10 11 15，pill = 1， strength = 1，这可以完成所有任务，但是匹配成 [10, 11] [10 15]，剩下的一个完成不了。

    正确匹配方式：
    从小到大遍历workers，注意现在我们要检查**所有**这x个任务能否都完成，
    1. 若当前worker能完成一个任务，则让其完成
    2. 若当前worker没有能完成的任务，则必须吃药，让其去完成其能完成的最大任务，充分利用药效
    如果当前worker有能完成的任务，却让他吃药去完成一个更大的任务，这不是最优的，因为后面会让一个更强的工人完成一个当前worker就能完成的任务，
    这颗药可能是浪费的。
    于是，从小到大遍历workers，把当前worker吃药能完成的任务放到队列中，这样后面就不用重新找吃药的情况下的边界了
    */
    pub fn max_task_assign(tasks: Vec<i32>, workers: Vec<i32>, pills: i32, strength: i32) -> i32 {
        let mut tasks = tasks;
        let mut workers = workers;
        tasks.sort();
        workers.sort();

        let check = |x| {
            let mut coverable_tasks = VecDeque::new();
            let mut pills = pills;
            let mut i = 0;
            for &w in &workers[workers.len() - x .. workers.len()] {
                while i < x && tasks[i] <= w + strength {
                    coverable_tasks.push_back(tasks[i]);
                    i += 1;
                }
                if coverable_tasks.is_empty() { // 吃药的情况下都没有能完成的任务
                    return false;
                }
                if w >= *coverable_tasks.front().unwrap() { // 不用吃药
                    coverable_tasks.pop_front();
                    continue;
                }
                // 完成不了最小的，说明必须吃药，那就去完成吃药的情况下能完成的最大的
                if pills == 0 {
                    return false;
                }
                pills -= 1;
                coverable_tasks.pop_back();
            }
            true
        };

        let mut left = 0;
        let mut right = std::cmp::min(tasks.len(), workers.len());
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        right as i32
    }
}

pub fn main() {
    println!("{}", Solution2071::max_task_assign(vec![3,2,1], vec![0,3,3], 1, 1));
    println!("{}", Solution2071::max_task_assign(vec![5,4], vec![0,0,0], 1, 5));
    println!("{}", Solution2071::max_task_assign(vec![10,15,30], vec![0,10,10,10,10], 3, 10));
    println!("{}", Solution2071::max_task_assign(vec![5,9,8,5,9], vec![1,6,4,2,6], 1, 5));  
}