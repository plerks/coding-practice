## lower_bound在需要自定义比较器时的写法

std::lower_bound的作用是二分查找第一个>=的位置，std::upper_bound的作用是二分查找第一个>的位置，使用的是operator<进行比较。但当使用其自定义比较器的重载版本时，功能又有所不同，不再固定为查找第一个>=和>的位置，而是通用的二分查找模板。

以
```cpp
template< class ForwardIt, class T, class Compare >
ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );
```
为例，lower_bound的comp定义是`comp(*iter, value)`（注意elem在前，常量value在后），其实现为：
```cpp
template<typename _ForwardIterator, typename _Tp, typename _Compare>
_ForwardIterator lower_bound_(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__val, _Compare __comp) {
    typedef typename iterator_traits<_ForwardIterator>::difference_type _DistanceType;

    _DistanceType __len = std::distance(__first, __last);

    while (__len > 0) {
        _DistanceType __half = __len >> 1;
        _ForwardIterator __middle = __first;
        std::advance(__middle, __half);
        if (__gnu_cxx::__ops::__iter_comp_val(__comp)(__middle, __val)) {
            __first = __middle;
            ++__first;
            __len = __len - __half - 1;
        }
        else
            __len = __half;
    }
    return __first;
}
```
完全就是二分的写法，因此，**lower_bound带自定义比较器的版本完全就是一个二分查找的模板**，不仅仅限于查找第一个>=的位置，通过定义comp可以实现任何二分逻辑。

（这里有个细节，标准库的写法相当于是左闭右开的二分写法，可以避开指针为-1的情况，因为begin() - 1是ub。闭区间、开区间、左开右闭区间的写法都会出现-1。）

先读[再来看写check条件与取反问题](./有序范围内的二分查找.md#再来看写check条件与取反问题)。

对给定的一个区间，无论是搜索最后一个...的位置，还是搜索第一个...的位置，都可以通过`自定义比较器lower_bound`来完成。comp类似于手写二分时的check函数，确定搜索问题之后，写comp时不需要辨别是searchLast还是searchFirst类问题，只需要知道逻辑命题是什么，先把逻辑命题写成comp的返回值，然后判断：对于逻辑命题，区间从否到是？，若区间从否开始的话则需要把comp的返回值再取反。

（手写二分本来一般是在`if (!check())`位置把check结果反向，但是这里由于不能改`std::lower_bound`的代码，所以要在check返回时取反，同样达到了把check结果反向的效果）

一对searchLast与searchFirst问题，其搜索过程是完全相同的，以闭区间写法为例，最终都应该让指针找到 right | left 的位置，searchLast的答案为right，searchFirst的答案为left。**`自定义比较器lower_bound`返回的相当于闭区间写法最终的left**，也即**lower_bound()返回的是searchFirst的结果**，**如果想要searchLast的结果，则要将返回值 - 1**。

确定搜索问题后，只需要看：

**逻辑命题；区间从否开始？；搜索问题的答案该是 ret 还是 ret - 1 ？**

**如果是searchFirst，答案是 ret；如果是searchLast，答案是 ret - 1**。

不需要去考虑两种搜索逻辑命题相反的问题，不需要把当前问题转成另一个问题来思考。就用搜索内容的逻辑命题，只是要判断取反，然后最终取值时知道是哪个值。searchLast从是到否判断出来不需取反，和searchFirst从否到是判断出来需要取反，真值是一样的，两种二分查找过程完全相同，只是最后答案位置有1的差别。

[再来看写check条件与取反问题](./有序范围内的二分查找.md#再来看写check条件与取反问题)：搜索最后一个满足某条件的位置，区间一定是从满足到不满足，那么，对于“满足条件”这件事，区间一定从是到否，**只要check()写成“满足条件”，searchLast问题区间一定从是到否，不需要取反**。**对应的searchFirst问题区间一定从否到是**。

所以，只要check()确实写成了“满足条件”，那么一定是searchLast不取反，searchFirst要取反。

**换一个角度来说，comp里的判断条件其实就是searchLast对应的判断条件。然后lower_bound()返回后看取 ret 还是 ret - 1**。也可以用这种思考方式来写comp，但是比较绕，因为可能我本来问题明明是searchFirst。

### 总结
**二分查找的过程并不知道是searchLast还是searchFirst，只是针对某个让区间从是到否变化的“命题”，移动双指针到边界位置，搜索的是边界位置。searchLast还是searchFirst是最终取答案时体现出来的。**

总之，先想好自己要搜索的是什么(比如第一个...的位置)，直接取出命题，然后取反/不取反命题，**让区间对命题是从[是...否]变化的就是对的**，最后计算结果看取哪个指针位置（searchLast/searchFirst）。

## 使用std::lower_bound()时的迭代器转下标

```cpp
vector<int> nums = {1, 3, 6, 7, 10, 15, 16, 21};
int index1 = lower_bound(nums.begin(), nums.end(), 7, [](int x, int val) {
    return x <= val;
}) - nums.begin(); // 第一个>7的位置，index1为4
int index2 = lower_bound(nums.begin(), nums.end(), 7, [](int x, int val) {
    return x <= val;
}) - nums.begin() - 1; // 最后一个<=7的位置，index2为3
```
注意，这是**标准的写法**，需要把返回的迭代器转下标。index1包含了searchFirst查找不到时应该为n的情况，index2包含了searchLast查找不到时应该为-1的情况，且不会触发begin()-1是ub的问题。

如果需要访问lower_bound()的结果元素，如果写\*lower_bound()或\*(lower_bound() - 1)，前者可能lower_bound()返回结果为end()不能解引用；后者可能lower_bound() - 1是begin() - 1，是ub，且begin() - 1也不能解引用。所以，要么采用上面标准的写法转换成下标后再判断`!= n/-1`后再访问；像std::map这样不能O(1)访问任意位置的，`先判断lower_bound() != end()`，然后`*lower_bound()` / `先判断lower_bound() != begin()`，然后`it--`，再`*it`。

在[LeetCode948. 令牌放置](https://leetcode.cn/problems/bag-of-tokens/)中遇到了，使用向右偏移了一步的前缀和数组(`vector<long long> pre(n + 1)`)并在前缀和数组中二分查找时，二分查找的结果位置要再多减一个1，因为这样的前缀和数组的头是pre.begin() + 1，例如`int last = upper_bound(pre.begin(), pre.end(), power + pre[l]) - pre.begin() - 1 - 1;`。

## 例子

`自定义比较器lower_bound`查找第一个>7的位置（对应searchLast的判断条件为**elem <= 7**，区间对于**elem <= 7**从是到否变化，无需对命题 <= 7 取反），答案为ret：
```cpp
vector<int> nums = {1, 3, 6, 7, 10, 15, 16, 21};
cout << *lower_bound(nums.begin(), nums.end(), 7) << endl; // 输出7
cout << *lower_bound(nums.begin(), nums.end(), 7, [](int x, int val) {
    return x <= val;
}) << endl; // 输出10
```

nums从小到大，查找第一个nums.back() - nums[x] < val的位置，对于命题 < val，区间从否到是，comp里需要对命题 < val 取反，答案为ret：
```cpp
vector<int> nums = {1, 3, 6, 7, 10, 15, 16, 21};
cout << *lower_bound(nums.begin(), nums.end(), 5, [&](int x, int val) {
    return nums.back() - x >= val;
}) << endl; // 输出21
```

points已好排序，查找第一个横坐标>=2的位置 => 查找最后一个横坐标<2的位置，区间对 < 2 呈从是到否，答案为ret：
```cpp
vector<pair<int, int>> points = {{1, 3}, {2, 4}, {2, 5}, {3, 4}};
int index = lower_bound(points.begin(), points.end(), 2, [](auto &elem, const int &val) {
    return elem.first < 2;
}) - points.begin(); // index为1
```

## upper_bound自定义比较器的写法

通过定义comp，`自定义比较器lower_bound`已经是个通用的二分模版了。`自定义比较器upper_bound`也是个通用二分模板，但是完全不需要使用，因为`自定义比较器upper_bound`的comp是`comp(value, elem)`，变成了value在前，elem在后，很容易弄混，且comp中的判断逻辑相较于`自定义比较器lower_bound`要反一次，所以**总是不要使用`自定义比较器upper_bound`**。

但是还是理一下upper_bound的逻辑。

```cpp
template< class ForwardIt, class T, class Compare >
ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );
```
的实现相当于：
```cpp
while (left <= right) {
    int mid = (left + right) / 2;
    // comp(val, arr[mid]相当于val < arr[mid]
    if (comp(val, arr[mid])) right = mid - 1;
    else left = mid + 1;
}
```
转换一下：
```cpp
while (left <= right) {
    int mid = (left + right) / 2;
    /* !comp相当于val >= arr[mid]，即arr[mid] <= val，
    这样，upper_bound仅仅通过operator<就完成了功能，不需要
    操作数去定义operator<=

    arr[mid] <= val <=> !(arr[mid] > val) <=> !(val < arr[mid]) 这样就转成operator<了
    */
    if (!comp(val, arr[mid])) left = mid + 1;
    else right = mid - 1;
}
```
于是，要用`自定义比较器upper_bound`的话，comp的定义得是先弄出searchLast的判断逻辑，然后取反(因为upper_bound里取了次反)，然后如果对于searchLast的判断逻辑，区间为[否 ... 是]的话，得再反一次。不如直接用`自定义比较器lower_bound`。

upper_bound的例子：

```cpp
vector<int> nums = {1, 3, 6, 7, 10, 15, 16, 21};
cout << *upper_bound(nums.begin(), nums.end(), 7) << endl; // 输出10
// 查找第一个>=7的元素 => 最后一个<7的元素
cout << *upper_bound(nums.begin(), nums.end(), 7, [](auto val, auto elem) {
    return elem >= val;
}) << endl; // 输出7

vector<pair<int, int>> points = {{1, 3}, {2, 4}, {2, 5}, {3, 4}};
// 查找第一个横坐标>=2的位置 => 查找最后一个横坐标<2的位置
int index = upper_bound(points.begin(), points.end(), 2, [](auto &val, auto &elem) {
    return !(elem.first < 2);
}) - points.begin(); // index为1
```

## operator<
上面upper_bound的例子可以看到，只需operator<即可得到operator<=，具体来说：

$$
x < y \iff x < y \\
x \le y \iff !(y < x) \\
x > y \iff y < x \\
x \ge y \iff !(x < y) \\
x == y \iff !(x < y) \&\& !(y < x) \\
x != y \iff x < y || y < x
$$

也就是说，按理只需要定义operator<，即可实现所有比较操作符，但这仅限于具备全序关系的集合，例如数，std::pair，std::tuple等。不是只定义一个operator<就万能，例如std::unordered_map，元素之间可能无法定义<关系，需要的是==关系。