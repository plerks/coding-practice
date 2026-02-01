/*
url: https://leetcode.cn/problems/design-ride-sharing-system/
标签: LeetCode第487场周赛
*/
#include <bits/stdc++.h>

using namespace std;

/* LeetCode设计题常见的不能随便操作数据结构中间的元素，那就记录情况，然后最后懒删除，和上周的 LeetCode3815. 设计拍卖系统 一样的风格。
周赛时的写法，也可以用一个 set 装确实在等待的乘客，不用 wait_id，见灵茶题解。我这里用 mp[riderId] = -1 表示没在等待，实际直接删除就好了。
*/
class RideSharingSystem {
public:
    int wait_id = 1;
    queue<pair<int, int>> rider; // 装 (rider_id, wait_id)
    queue<int> driver;
    unordered_map<int, int> mp; // (rider_id, wait_id)

    RideSharingSystem() {
        
    }
    
    void addRider(int riderId) {
        rider.push({riderId, wait_id});
        mp[riderId] = wait_id;
        wait_id++;
    }
    
    void addDriver(int driverId) {
        driver.push(driverId);
    }
    
    vector<int> matchDriverWithRider() {
        int rider_id = -1;
        int driver_id = -1;

        while (!rider.empty() && rider.front().second != mp[rider.front().first]) {
            rider.pop();
        }
        if (!rider.empty() && !driver.empty()) {
            rider_id = rider.front().first, rider.pop();
            driver_id = driver.front(), driver.pop();
        }

        return {driver_id, rider_id};
    }
    
    void cancelRider(int riderId) {
        mp[riderId] = -1;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}