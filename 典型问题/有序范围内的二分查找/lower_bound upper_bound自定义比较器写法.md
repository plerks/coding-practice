## lower_bound在需要自定义比较器时的写法

std::lower_bound的作用是二分查找第一个>=的位置，std::upper_bound的作用是二分查找第一个>的位置，使用的是operator<进行比较。但当使用其自定义比较器的重载版本时，功能又有所不同。

以
```cpp
template< class ForwardIt, class T, class Compare >
ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );
```
为例，lower_bound的comp定义是`comp(*iter, value)`（注意elem在前，常量value在后），其实现相当于（以闭区间写法为例）：
```cpp
while (left <= right) {
    int mid = (left + right) / 2;
    if (comp(arr[mid], val)) left = mid + 1;
    else right = mid - 1;
}
return left;
```
完全就是二分的写法，因此，**lower_bound带自定义比较器的版本完全就是一个二分查找的模板**，不仅仅限于查找第一个>=的位置，通过定义comp可以实现任何二分逻辑。

关于这里comp的写法，comp就是手写二分时的check函数，`comp(elem, val)`回答的是`elem是否<val`的询问。这里的写法步骤是：无论现在的需求是searchLast还是searchFirst，都先**统一把判断条件转为searchLast的**，两种需求**都要用searchLast的判断条件来写**，那个**判断条件就是lambda的函数体**，只是**如果区间对于对应searchLast的判断条件是`从否到是`变化的话**，需要在返回时将真值**取反**。注意判断区间是否为`从否到是`都要用searchLast的判断条件来看，这很重要！

（手写二分本来是要在`if (!check())`位置把check结果反向，但是不能改`std::lower_bound`的代码，所以要在check返回时取反，同样达到了把check结果反向的效果）

有个奇妙的点，searchLast如果是单纯的数值大小比较检查，首先，现在既然需要写二分，那肯定不是平凡情况。那么无论是搜索最后一个`<val, <=val, >val, >=val`（区间小->大，小->大，大->小，大->小），区间变化都一定为[是 ... 否]。`自定义比较器lower_bound`是和指定的val比较，这样说来，需要用`自定义比较器lower_bound`的情景，转成searchLast的判断条件后，区间一定会是[是 ... 否]？根本不会出现真的需要取反的情景？

`自定义比较器lower_bound`里对于给定的comp执行了标准的二分查找过程，searchLast和searchFirst的二分查找过程代码是相同的，只是`自定义比较器lower_bound`返回的结果是searchFirst的结果，需要的话-1获得下标。可以将`自定义比较器lower_bound`视为searchLast，判断条件也要是searchLast的，只是其返回结果要-1才是searchLast的结果，所以searchLast时是lower_bound() - 1，searchFirst时是lower_bound() - 1 + 1 == lower_bound()。（注意不能真的写lower_bound() - 1，begin() - 1是ub）

```cpp
vector<int> nums = {1, 3, 6, 7, 10, 15, 16, 21};
int index1 = lower_bound(nums.begin(), nums.end(), 7, [](int x, int val) {
    return x <= val;
}) - nums.begin(); // 第一个>7的位置，index1为4
int index2 = lower_bound(nums.begin(), nums.end(), 7, [](int x, int val) {
    return x <= val;
}) - nums.begin() - 1; // 最后一个<=7的位置，index2为3
```
注意，这是**标准的写法**，index1包含了searchFirst查找不到时应该为n的情况，index2包含了searchLast查找不到时应该为-1的情况，且不会触发begin()-1是ub的问题。

**总结**：统一换为searchLast的判断条件，用这个条件判断区间是否为`从否到是`，最后结果原为searchFirst则无-1，原为searchLast则有-1。

例子：

`自定义比较器lower_bound`查找第一个>7的位置（对应searchLast的判断条件为**elem <= 7**，区间对于**elem <= 7**从是到否变化，无需取反）：
```cpp
vector<int> nums = {1, 3, 6, 7, 10, 15, 16, 21};
cout << *lower_bound(nums.begin(), nums.end(), 7) << endl; // 输出7
cout << *lower_bound(nums.begin(), nums.end(), 7, [](int x, int val) {
    return x <= val;
}) << endl; // 输出10
```

nums从小到大，查找第一个nums.back() - nums[x] < val的位置，区间从是到否（注意区间趋势是用>=来看）：
```cpp
vector<int> nums = {1, 3, 6, 7, 10, 15, 16, 21};
cout << *lower_bound(nums.begin(), nums.end(), 5, [&](int x, int val) {
    return nums.back() - x >= val;
}) << endl; // 输出21
```

points已好排序，查找第一个横坐标>=2的位置 => 查找最后一个横坐标<2的位置，区间呈从是到否：
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