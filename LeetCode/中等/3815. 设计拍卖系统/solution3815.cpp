/*
url: https://leetcode.cn/problems/design-auction-system/
标签: LeetCode第485场周赛
*/
#include <bits/stdc++.h>

using namespace std;

// 双向map / 懒删除堆的题，典型套路，之前也遇到过

// 方法一，双向map
// 要查询一个物品的最高出价，因此要对某种物品维护一个 (price, set<user>) 的 map，set<user> 是为了同出价时返回最大 userId，可以换成优先队列
// 为了修改一个user的出价，要维护一个 (user, price) 的 map
// user 修改 price 时，如何同步到 (price, set<user>) 的那个 map ? 根据 (user, price) 查到旧 price，然后去 set<user> 里删，然后将 user 插入到新 price 为 key 的 set 中
class AuctionSystem {
    unordered_map<int, map<int, set<int>>> item_mp1; // (item, (price, set<user>))
    unordered_map<int, unordered_map<int, int>> item_mp2; // (item, (user, price))
public:
    AuctionSystem() {
        
    }
    
    void addBid(int userId, int itemId, int bidAmount) {
        auto& mp1 = item_mp1[itemId];
        auto& mp2 = item_mp2[itemId];
        // 删除旧的出价记录（如果有）
        if (mp2.count(userId)) {
            int old_price = mp2[userId];
            mp1[old_price].erase(userId);
            if (mp1[old_price].empty()) mp1.erase(old_price); // 这个出价没人了必须删，不然查最高出价时会认为最高价没人出，返回 -1，实际次高价有人出，那个才是最高价
        }
        // 插入新记录
        mp2[userId] = bidAmount;
        mp1[bidAmount].insert(userId);
    }
    
    void updateBid(int userId, int itemId, int newAmount) {
        addBid(userId, itemId, newAmount);
    }
    
    void removeBid(int userId, int itemId) {
        auto& mp1 = item_mp1[itemId];
        auto& mp2 = item_mp2[itemId];
        int old_price = mp2[userId];
        mp1[old_price].erase(userId);
        if (mp1[old_price].empty()) mp1.erase(old_price);
        mp2.erase(userId);
    }
    
    int getHighestBidder(int itemId) {
        auto& mp1 = item_mp1[itemId];
        if (mp1.empty()) return -1;
        auto it = mp1.rbegin()->second.rbegin();
        if (it == mp1.rbegin()->second.rend()) return -1;
        return *it;
    }
};

// 方法二，懒删除堆
// 将方法一中的对某一 item 的 (price, set<user>) 的 map 换成 priority_queue<(price, userId)>，然后在查询时懒删除堆中的元素
class AuctionSystem_impl2 {
    unordered_map<int, priority_queue<pair<int, int>>> item_mp1; // (item, priority_queue<(price, userId)>)，pq 记录了对这个 item 的所有出价情况
    unordered_map<int, unordered_map<int, int>> item_mp2; // (item, (user, price))
public:
    AuctionSystem_impl2() {
        
    }
    
    void addBid(int userId, int itemId, int bidAmount) {
        item_mp1[itemId].push({bidAmount, userId});
        item_mp2[itemId][userId] = bidAmount;
    }
    
    void updateBid(int userId, int itemId, int newAmount) {
        addBid(userId, itemId, newAmount);
    }
    
    void removeBid(int userId, int itemId) {
        item_mp2[itemId].erase(userId);
        // item 的 pq 不用更新，懒删除 pq 中元素
    }
    
    int getHighestBidder(int itemId) {
        auto it = item_mp1.find(itemId);
        if (it == item_mp1.end()) return -1;
        auto& pq = it->second;

        while (!pq.empty()) {
            auto& [price, user] = pq.top();
            if (!item_mp2[itemId].count(user) || item_mp2[itemId][user] != price) {
                pq.pop();
            }
            else return user;
        }
        return -1;
    }
};
// item_mp2 的 userId 和 itemId 总是套在一起的，可以压缩成一个 long long ，这样可以少套一层 map，见灵茶题解

int main(int argc, char const *argv[]) {
    return 0;
}