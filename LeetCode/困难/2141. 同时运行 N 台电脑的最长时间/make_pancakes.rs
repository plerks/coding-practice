/*
描述: 从solution2141的解法想到这个摊煎饼的问题：
    用一只平底锅煎饼，每次最多放两张饼，煎一张饼正反两面各需一分钟，则3张饼至少需要几分钟？把饼的数量一般化为n，该怎么做？

    这里平底锅的2个位置相当于solution2141有2台电脑，每张饼有两面相当于电池电量为2，但是问题变成了要把电池电量在最短时间内消耗完，要多少分钟？
    和solution2141非常相似的是，这里也有约束：同一行最多只能出现一次某张饼。
    用max_run_time()二分的思路，竖着摆，最后看能否把饼消耗完（而非solution2141的情景能否填满矩阵）；
    然后观察出直接的公式
标签: [mark]
*/

// 解法一，二分答案
fn min_time_to_make_pancakes(n: i32) -> i32 {
    let check = |t| -> bool {
        // 2 * t 个空格，竖着摆，看能否把电池消耗完，每个电池的量为2，不能出现在同一行，和 LeetCode2141. 同时运行 N 台电脑的最长时间 非常相似
        let mut edge = n * 2; // 面数
        let mut empty = t << 1; // 空位数
        while edge > 0 && empty > 0 {
            edge -= 2; // 保证了 t >= 2，这里按列拉直以后一定能放上2个面，不用与2取min都能保证不会摆到同一行
            empty -= 2;
        }
        return edge == 0;
    };

    let mut left = 2; // 保证了 check 时的 t >= 2
    let mut right = n << 1;
    while left <= right {
        let mid = (left + right) / 2;
        if !check(mid) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

/*
似乎总能恰好利用到所有空位。

n为偶数时平凡的方案就是最优的：
1_正 2_正
1_反 2_反
3_正 4_正
3_反 4_反

n为奇数时，原本是会这样：
1_正 2_正
1_反 2_反
3_正 4_正
3_反 4_反
5_正
5_反

但是利用最后的3张煎饼，仍然能达到100%的空位利用率：
1_正 2_正
1_反 2_反
3_正 4_反
3_反 5_正
4_正 5_反

于是有结论：答案为 if n == 1 { 2 } else { n }
*/
fn min_time_to_make_pancakes_implementation2(n: i32) -> i32 {
    return if n == 1 { 2 } else { n };
}

fn main() {
    println!("{}", min_time_to_make_pancakes(1));
    println!("{}", min_time_to_make_pancakes(2));
    println!("{}", min_time_to_make_pancakes(3));
    println!("{}", min_time_to_make_pancakes(4));
    println!("{}", min_time_to_make_pancakes(5));
    println!("{}", min_time_to_make_pancakes(6));

    for i in 1..10000 {
        if min_time_to_make_pancakes(i) != min_time_to_make_pancakes_implementation2(i) {
            println!("two implementation not equal for i: {}", i); // 没有发生打印这一行
        }
    }

    for i in 1..10000 {
        assert_eq!(
            min_time_to_make_pancakes(i),
            min_time_to_make_pancakes_implementation2(i),
            "not equal for i: {}",
            i
        );
    }
}