# 描述

Meet in the middle 这个技巧适用于输入数据较小，但还没小到能直接使用暴力搜索的情况，特别是针对指数级的暴力算法。本质来说是 分治 + 高效的pushup 起作用了。

Meet in the middle 算法的主要思想是将整个搜索过程分成两半，分别搜索，最后将两半的结果合并。合并过程看具体问题。

假设暴力递归搜索每个分支出 2 个子递归实例，合并代价为 O(1)，则 Meet in the middle 将时间复杂度从 $ O(2^n) $ 变成 $ O(2 * 2^{n/2}) $，对于指数时间复杂度的问题，能大大减小时间复杂度。

# 相关

LeetCode3850. 统计结果等于 K 的序列数目

LuoguP2962 [USACO09NOV] Lights G

# 参考

https://oi-wiki.org/search/bidirectional/
