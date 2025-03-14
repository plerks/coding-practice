## 位运算优先级的坑

位运算的优先级并不高，低于==。

以下优先级从高到低：
```
乘除取余加减

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

## 关于%的优先级
%的优先级低于乘除，高于加减，所以，(a + b) % MOD需要打括号，
a * b % MOD不用。正确且简洁的写法例如：(a + b) * (c + d) % MOD或者(a * b + c * d) % MOD，拿不准的话就尽量都打括号。

## size_t无符号问题
c++ stl的容器返回size都是size_t类型，在64位机器上size_t是unsigned long long。当其与有符号数比较时，由于会转成无符号数的比较，可能会出现问题。**特别当size()减去一个负数时**。

例如：`if (vec.size() - 1 < 0) {}`，当vec是空vector，本意是条件判断结果为true，但是由于size()返回的是无符号数，会转成无符号数的比较，0ULL - 1会大于0，条件判断结果会为false。

当unsigned去减一个正数时就有这个坑，上面得改成`if (vec.size() < 1) {}`；**最通用的解决办法是转成int**，`if ((int)vec.size() - 1 < 0) {}`

在`LeetCode3159. 查询数组中元素的出现位置`中遇到这个坑。

## multiset
std::multiset的erase(key)会删除所有这个元素，得erase(iterator)才是只删除一个。

```cpp
vector<int> nums{5,5,5};
multiset<int> st(nums.begin(), nums.end());
st.erase(st.find(5)); // 删除一个5
st.erase(5); // 会删除所有5
```

在`LeetCode2762. 不间断子数组`中遇到这个问题，并且当有大量重复元素时，std::multiset的查找效率不如用std::map + value计数，std::multiset的相同元素有各自独立的树节点，而不是std::map<Key, int>这种频率计数的方式。因为比如Key是个struct，并且key之间的大小比较只用到了其中一部分字段，那么仅仅计数就是不行的，必须各自有独立的节点。