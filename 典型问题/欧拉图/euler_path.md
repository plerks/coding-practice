# Hierholzer 算法计算欧拉路径

## 介绍

LeetCode332的[官方题解](https://leetcode.cn/problems/reconstruct-itinerary/solutions/389885/zhong-xin-an-pai-xing-cheng-by-leetcode-solution/)中有相关概念的总结：

* 通过图中所有边恰好一次且行遍所有顶点的通路称为欧拉通路；

* 通过图中所有边恰好一次且行遍所有顶点的回路称为欧拉回路；

* 具有欧拉回路的无向图称为欧拉图；

* 具有欧拉通路但不具有欧拉回路的无向图称为半欧拉图。

对于欧拉图/半欧拉图的判别

* 对于无向图 G，G 是欧拉图当且仅当 G 是连通的且没有奇度顶点。

* 对于无向图 G，G 是半欧拉图当且仅当 G 是连通的且 G 中恰有 0 个或 2 个奇度顶点。

* 对于有向图 G，G 是欧拉图当且仅当 G 的所有顶点属于同一个强连通分量且每个顶点的入度和出度相同。

* 对于有向图 G，G 是半欧拉图当且仅当（以下4个条件是and的关系）
    + 如果将 G 中的所有有向边退化为无向边时，那么 G 的所有
顶点属于同一个强连通分量；
    
    + 最多只有一个顶点的出度与入度差为 1；
    
    + 最多只有一个顶点的入度与出度差为 1；
    
    + 所有其他顶点的入度和出度相同。

## 参考

* https://leetcode.cn/problems/reconstruct-itinerary/solutions/389885/zhong-xin-an-pai-xing-cheng-by-leetcode-solution/

* https://oi-wiki.org/graph/euler/

## 相关

* LuoguP2731 [USACO3.3] 骑马修栅栏 Riding the Fences