## 位运算优先级的坑

位运算的优先级并不高，低于==。

[运算符优先级表](https://learn.microsoft.com/zh-cn/cpp/cpp/cpp-built-in-operators-precedence-and-associativity?view=msvc-170#c-operator-precedence-and-associativity-table)

以下优先级从高到低：
```
乘除取余

加减

移位

< <= > >=

== !=

位运算

&& ||

```
由于位运算优先级相对较低，因此在C++里位运算会有这样的坑：
```C++
if ((j & k) == 0)
```
如果写成了
```C++
if (j & k == 0)
```
这里==会优先于&先算，然后再与j相&，不是想要的逻辑。

在`AcWing292. 炮兵阵地`和`LeetCode1276. 不浪费原料的汉堡制作方案`中都有遇到这样的坑，很隐蔽。

Java里运算符优先级也是这样，k == 0会先算，但是会因为int & boolean报错。

总之，有用到位运算和移位运算符时，最好打括号把那部分括起来。

## 三目运算符的坑
三目运算符`?`的优先级相对较低，如果三目运算符表达式还和别的进行运算，可能导致别的部分先算了，然后才算`?`。

```cpp
// `LeetCode1124. 表现良好的最长时间段`中遇到。按nums[i]是否 > 8 处理为 1 或 -1，然后求前缀和：

vector<int> nums = {6, 9, 9, 9};
int n = nums.size();
vector<int> pre(n + 1);
for (int i = 0; i < n; i++) pre[i + 1] = pre[i - 1 + 1] + (nums[i] > 8 ? 1 : -1); // 正确写法
// for (int i = 0; i < n; i++) pre[i + 1] = pre[i - 1 + 1] + nums[i] > 8 ? 1 : -1; // 错误写法，会是pre[i - 1 + 1] + nums[i]先计算，然后和8比较
```

所以，如果三目运算符表达式和别的进行运算，**三目运算符表达式整体要用括号括起来**。

## 关于%的优先级

%的优先级与乘除**相同**，左结合；高于加减。

左结合是指：当一组运算符具有相同优先级时，运算会从左往右进行。

所以，(a + b) % MOD需要打括号，a * b % MOD不用。正确且简洁的写法例如：(a + b) * (c + d) % MOD或者(a * b + c * d) % MOD，拿不准的话就尽量都打括号。

比如 5 % 2 * 3，会先算 %，再算 *，即等价于`(5 % 2) * 3`。而非 5 % (2 * 3)。

LeetCode2281中遇到计算ans时要算不止两个因子相乘的情况。a * b % MOD * c，优先级都相同，由于左结合性，会先算 a * b，然后 % MOD，然后 * c，也即`a * b % MOD * c`等价于`(a * b % MOD) * c`。而非 (a * b) % (MOD * c)。

LeetCode2281中还遇到这样一种情况：每次`ans = (ans + part1 - part2) % MOD`。题目问题性质保证 ans 每次都会增加，也就是说无限位长的情况下一定每次 part1 >= part2，但是由于计算 part1 和 part2 时二者也取模了，所以现在二者大小关系可能反转。相减就可能出负数，然后C++负数的取模和期望的不同，然后WA。

**每次取模问题遇到相减**，则要考虑差是否可能出现负数。最稳妥的方式是**只要出现差，`% MOD`之前要先`+ MOD`变成正的**，例如`(a % MOD - b % MOD + MOD) % MOD`。

## size_t无符号问题
c++ stl的容器返回size都是size_t类型，在64位机器上size_t是unsigned long long。当其与有符号数比较时，由于会转成无符号数的比较，可能会出现问题。**特别当size()减去一个负数时**。

例如：`if (vec.size() - 1 < 0) {}`，当vec是空vector，本意是条件判断结果为true，但是由于size()返回的是无符号数，会转成无符号数的比较，0ULL - 1会大于0，条件判断结果会为false。

当unsigned去减一个正数时就有这个坑，上面得改成`if (vec.size() < 1) {}`；**最通用的解决办法是转成int**，`if ((int)vec.size() - 1 < 0) {}`

在`LeetCode3159. 查询数组中元素的出现位置`中遇到这个坑。

[LeetCode475. 供暖器](https://leetcode.cn/problems/heaters/) -> findRadius_implementation2()，又出现了这个问题，那题的代码类似`while (index < nums.size() && nums[index] <= x)`，但是那题代码写的方式不对，index可能变为负数，这时负数与ULL比较，结果 < 为false，虽然index为负数下标越界了，但是不会执行到nums[index]，不会真的越界，只是执行逻辑完全错了。

也就是说，除了unsigned去减一个正数时有这个坑，另一边的int如果可能为负数也会有这个坑，需要保证**两边都必定非负**才是安全的。

## multiset
std::multiset的erase(key)会删除所有这个元素，得erase(iterator)才是只删除一个。

```cpp
vector<int> nums{5,5,5};
multiset<int> st(nums.begin(), nums.end());
st.erase(st.find(5)); // 删除一个5
st.erase(5); // 会删除所有5
```

在`LeetCode2762. 不间断子数组`中遇到这个问题，并且当有大量重复元素时，std::multiset的查找效率不如用std::map + value计数，std::multiset的相同元素有各自独立的树节点，而不是std::map<Key, int>这种频率计数的方式。因为比如Key是个struct，并且key之间的大小比较只用到了其中一部分字段，那么仅仅计数就是不行的，必须各自有独立的节点。

## std::partial_sum内部计算使用的类型
以下代码，用std::partial_sum计算完前缀和后，pre[2]会是INT_MIN，溢出了。
```cpp
vector<int> nums = {INT_MAX, 1, INT_MAX};
vector<long long> pre(nums.size() + 1);
partial_sum(nums.begin(), nums.end(), pre.begin() + 1);
cout << pre[2] << endl; // 输出INT_MIN
```
nums[i]是在int范围内的，pre[i]的类型为long long，但是partial_sum内部计算累加时，并不是用的pre[i]的类型，而是用的nums[i]的类型。也就是说，partial_sum内部计算累加时用的是int，所以虽然pre定义为了long long，但用partial_sum计算前缀和会溢出。

```cpp
partial_sum(_InputIterator __first, _InputIterator __last, _OutputIterator __result) {
    typedef typename iterator_traits<_InputIterator>::value_type _ValueType;
      ...
```

**用std::partial_sum计算前缀和，若需要开long long，不仅结果容器要是long long，计算的对象容器也得是long long。**

在[LeetCode3261. 统计满足 K 约束的子字符串数量 II](https://leetcode.cn/problems/count-substrings-that-satisfy-k-constraint-ii/)中遇到这个问题。

## int溢出但sanitizer不能发现
开了sanitizer的情况下，int计算时的发生溢出能被发现，但是超出INT_MAX的long long转化为int截断时，sanitizer不会报错。

例如：
```cpp
int x = INT_MAX;
int y = x + 1; // sanitizer会报错

long long p = INT_MAX + 1;
int q = p; // sanitizer无报错

vector<int> memo(2);
memo[0] = INT_MAX + 1; // sanitizer无报错
```

例如，[LeetCode1537. 最大得分](https://leetcode.cn/problems/get-the-maximum-score/)，做的时候memo没有开long long，san又不会对这种报错，wa了知道是溢出的问题但是san又没报错，问题很隐蔽。