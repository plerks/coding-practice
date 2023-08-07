/*
url: https://leetcode.cn/problems/stone-game-ix/
LeetCode参考: https://leetcode.cn/problems/stone-game-ix/solutions/1459077/by-gong-zi-mian-p0k7/
              https://leetcode.cn/problems/stone-game-ix/solutions/2373721/2029-shi-zi-you-xi-ix-by-stormsunshine-9n0w/
*/

public class Solution2029 {
    public boolean stoneGameIX(int[] stones) {
        int[] nums = new int[3];
        for (int i : stones) {
            nums[i % 3]++;
        }
        return findAns(1, nums.clone()) || findAns(2, nums.clone());
    }

    private boolean findAns(int first, int[] nums) {
        /*
        选余数为0会反转2人身份，但是不会导致直接出局；
        Alice第一次取1，则Bob必须取1，然后接着Alice必须取2，然后Bob 1, Alice 2, Bob 1...。即Alice第一次1，后面全2，Bob一直1；
        Alice第一次取2，则Bob必须2，然后Alice 1，Bob 2, Alice 1, Bob 2。即Alice第一次2，后面全1，Bob一直2；
        1和2的个数就成为关键
        */
        if (nums[first] <= 0) return false;
        boolean ans = true;
        nums[first]--;
        int AliceChoice = 3 - first;
        int BobChoice = first;
        // 2人能选完石子而不触发出局（1和2选完之后选0就不会触发出局）。除去第一次的Alice，现在是Bob Alice Bob Alice ...地选
        if (nums[AliceChoice] == nums[BobChoice] || nums[BobChoice] == nums[AliceChoice] + 1) {
            return false;
        }
        ans = nums[AliceChoice] > nums[BobChoice];
        // 选余数为0会反转2人身份
        if (nums[0] % 2 != 0) {
            ans = !ans;
        }
        return ans;
    }

    public boolean stoneGameIX_implementation2(int[] stones) {
        int[] nums = new int[3];
        for (int i : stones) {
            nums[i % 3]++;
        }
        return MyStoneGameIX_implementation2(0, nums.clone(), 0) || MyStoneGameIX_implementation2(1, nums.clone(), 0) || MyStoneGameIX_implementation2(2, nums.clone(), 0);
    }

    // 这个朴素的用递归的写法没搞定，LeetCode上74 / 106 个通过的测试用例
    private boolean MyStoneGameIX_implementation2(int choice, int[] nums, int currentSum) {
        if (nums[choice] <= 0) return false;
        nums[choice]--;
        if ((currentSum + choice) % 3 == 0) {
            return false;
        }
        currentSum = (currentSum + choice) % 3;
        // 石子选完
        if (nums[0] == 0 && nums[1] == 0 && nums[2] == 0) return false;
        boolean case1 = true, case2 = true, case3 = true;
        // Bob 3种选择
        if (nums[0] > 0) {
            nums[0]--;
            currentSum = (currentSum + 0) % 3;
            if (currentSum == 0) {
                case1 = true;
            }
            else {
                case1 = MyStoneGameIX_implementation2(0, nums, currentSum) || MyStoneGameIX_implementation2(1, nums, currentSum) || MyStoneGameIX_implementation2(2, nums, currentSum);
            }
            currentSum = (currentSum - 0) % 3;
            nums[0]++;
        }
        if (nums[1] > 0) {
            nums[1]--;
            currentSum = (currentSum + 1) % 3;
            if (currentSum == 0) {
                case2 = true;
            }
            else {
                case2 = MyStoneGameIX_implementation2(0, nums, currentSum) || MyStoneGameIX_implementation2(1, nums, currentSum) || MyStoneGameIX_implementation2(2, nums, currentSum);
            }
            currentSum = (currentSum - 1) % 3;
            nums[1]++;
        }
        if (nums[2] > 0) {
            nums[2]--;
            currentSum = (currentSum + 2) % 3;
            if (currentSum == 0) {
                case3 = true;
            }
            else {
                case3 = MyStoneGameIX_implementation2(0, nums, currentSum) || MyStoneGameIX_implementation2(1, nums, currentSum) || MyStoneGameIX_implementation2(2, nums, currentSum);
            }
            currentSum = (currentSum - 2) % 3;
            nums[2]++;
        }
        // Bob会做最佳选择，因此三种情况都Alice赢Alice才会赢
        return case1 && case2 && case3;
    }

    public static void main(String[] args) {
        Solution2029 solu = new Solution2029();
        System.out.println(solu.stoneGameIX(new int[]{5,11,12,1,4,5,3}));
        System.out.println(solu.stoneGameIX_implementation2(new int[]{5,11,12,1,4,5,3}));
    }
}