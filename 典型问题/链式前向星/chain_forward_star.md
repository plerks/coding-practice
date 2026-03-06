# 链式前向星

## 介绍

图的一种存储方式

本质是用数组模拟邻接表，不是写成 `vector<vector<int>> g / vector<int> g[N];` 的形式，而是把边都统一都放在 `edge` 数组中，然后 `head[i]` 存储了 `i` 号节点的第一条边在 `edge` 中的下标，而 `Edge` 结构体中又存储了兄弟边的编号，从而将 `edge` 数组中的兄弟边关系连接起来。

访问 u 的所有出边的流程是：

head[u]  edge[head[u]].next  edge[edge[head[u]].next].next  ...  -1

可以看出也达到了邻接表的功能，相比邻接表，这种存储方式会多个所有边的线性存储结构可用。

## 参考

* https://blog.csdn.net/sugarbliss/article/details/86495945

* https://oi-wiki.org/graph/save/