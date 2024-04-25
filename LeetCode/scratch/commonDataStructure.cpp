#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    // <----- vector ------>
    vector<int> v{1,3,7,5,9}; // 用std::initializer_list初始化vector
    /* 也可以写`vector<int> v = {1,3,7,5,9};`，这种写法感觉要清晰点，特别是和括号初始化一起看。
    vector<int> b{3}，b只有一个元素，b为{3}
    vector<int> d(3)，d有三个元素，d为{0, 0, 0}
    vector<int> p{1, 2}，p为{1, 2}
    vector<int> q(1, 2)，q为{2}
    */
    int n = 5;
    /* 这里graph内部已经有了n个创建好了的vector，和Java里List<List<Integer>> list = new ArrayList<>(5)不一样，Java里这样只是指定
    了initialCapacity，list里还一个对象没有。
    */
    vector<vector<int>> graph(n); // 这和vector<vector<int>> graph(n, vector<int>())效果相同，后者指定创建n个什么样的vector，这里是空vector
    vector<vector<int>> d2Arr(n, vector<int>(n)); // n*n的二维数组，元素会初始化为0
    vector<vector<vector<int>>> d3Arr(n, vector<vector<int>>(n, vector<int>(n))); // n*n*n的三维数组，元素会初始化为0
    d3Arr[1][2][2] = 2;
    v.push_back(1);
    /* 关于push_back()和emplace_back()，如果这里vector放的是一个对象，push_back()必须构建个临时对象作为参数，而
    emplace_back()可以直接传构造对象所需的参数列表，不必须创建个临时对象传进去(虽然也可以以临时对象为参数)。 */
    v.emplace_back(8);
    sort(v.begin(), v.end());
    v[2] = 10;
    v.clear();
    v.insert(v.begin(), 1);
    v.emplace(v.begin(), 2);
    v.erase(v.begin());
    v = {1,3,7,5,9};
    // 或者sort(v.rbegin(), v.rend());
    // sort(v.rbegin(), v.rend());
    sort(v.begin(), v.end(), [](int x, int y) {
        return y - x;
    });
    v.emplace(v.end(), 10);
    // v.end() - 1才是最后一个元素，*(end())是undefined behavior
    cout << *(v.end() - 1) << endl;
    /* for (int val : v) {
        cout << val << " " << endl;
    }
    for (int &val : v) { // val是引用，可以通过val改vector里的值
        cout << val << " " << endl;
    } */

    // <------ stack ------>
    stack<int> st;
    st.push(1);
    st.emplace(2); // 也可用st.emplace()来入栈
    st.pop(); // C++里stack.pop()并没返回类型，和Java不一样，应该是因为若stack里装的是比较大的对象时，若要返回则要调用拷贝构造函数，开销较大
    cout << st.top() << endl;
    cout << (st.empty() ? "true" : "false") << endl;
    cout << st.size() << endl;

    // <------ queue ------>
    queue<int> q;
    q.push(1);
    q.emplace(2);
    q.pop();
    cout << q.front() << endl; // 应该是线性的数据结构就有front()和back()方法

    // <------ deque ------>
    deque<int> dq;
    // 头插头出当栈用(也可尾插尾出)
    dq.push_front(1);
    cout << dq.front() << endl;
    dq.pop_front();
    dq.clear();
    // 当队列用
    dq.push_back(1);
    dq.push_back(2);
    cout << dq.front() << endl;
    cout << dq.back() << endl;
    dq.pop_front();

    // C++ lambda表达式的结果是个匿名函数对象
    // C++ 11 lambda表达式的参数的类型不能声明为auto，C++ 14可以，所以如果是C++ 14可以直接写[](auto &x, auto &y)
    auto comparator = [](int &x, int &y) { // C++ 11的写法
        /* 若x应该排在前面，则返回true，否则返回false。但是，由于C++里的优先队列是大根堆，所以实际
        是排在后面的元素接近队首。
        见<https://en.cppreference.com/w/cpp/container/priority_queue>:
        "Note that the Compare parameter is defined such that it returns true if its first argument 
        comes before its second argument in a weak ordering. But because the priority queue outputs 
        largest elements first, the elements that "come before" are actually output last. That is, 
        the front of the queue contains the "last" element according to the weak ordering imposed by Compare."
        */
        // 所以，思考过程应该是: x和y，x比y远离队首吗/y比x接近队首吗 ？返回true : 返回false。
        // C++的priority_queue是大根堆，Java的PriorityQueue是小根堆，所以思考方式和Java是反着的
        return x > y;
    };
    /* 参考<https://blog.csdn.net/qq_42080098/article/details/123833742>，这里comparator是个实例化的lambda对象，这种定义排序逻辑
    的方式要把comparator传进构造函数，然后priority_queue内部用这个lambda对象进行比较。因为lambda这种特殊的class没有默认构造函数，所以
    必须pq(comparator)给进去。 */
    priority_queue<int, vector<int>, decltype(comparator)> pq(comparator);
    /* 比较通用的自定义排序写法是用lambda，不过也有:
    priority_queue<int, vector<int>, less<>> q1; // 堆顶为最大
    priority_queue<int, vector<int>, greater<>> q2; // 堆顶为最小
    */
    pq.push(1);
    pq.push(9);
    pq.push(5);
    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    pq.pop();

    // <------ unordered_map ------> 类似Java的HashMap
    unordered_map<string, int> map1{{"one", 1}, {"two", 2}};
    cout << map1.count("one") << endl;
    map1["one"] = -1;
    map1.erase("one"); // 也有erase(iterator pos)方法
    map1["three"] = 3;
    cout << map1["one"] << endl; // 用operator[]如果entry不存在会直接插入默认值，直接map1["one"]有副作用，应该把operator[]当put()用，不该用于读取
    map1.erase("one");
    map1.insert({"three", -3}); // unordered_map.insert()，如果key已经存在，会直接忽略，不会覆盖。感觉只需要用类似Java HashMap的put()的operator[]
    map1.insert(make_pair("three", -4));
    /* unordered_map内部用std::pair存词条(相当于Java里的Map.entry)，由于C++泛型不一定是对象，可能是基础类型，
    所以这里find()返回的是iterator，通过判断是否是end()判断是否找到，无法像Java一样通过判断是否为null，所以C++容器
    的访问不得不用迭代器来实现，否则若放的是基础类型(例如int)，返回个0不知道是没找到还是就是找到的值为0。
    */
    auto it = map1.find("three"); // unordered_map的find()相当于Java HashMap的get()，只是判断是否有对应key的逻辑变成了it != map1.end()
    if (it != map1.end()) { // 判断是否containsKey()
        cout << it->second << endl;
    }
    if (map1.count("three")) { // count()相当于Java里的containsKey()，不过这里相当于两次查找了，上面的写法要好一点
        cout << map1.find("three")->second << endl;
    }
    // 迭代器循环unordered_map
    // unordered_map的迭代器的类型是std::unordered_map<Key, T>::iterator，Key,T换成实际的模板类型
    for (auto it = map1.begin(); it != map1.end(); it++) {
        cout << it->first << "--" << it->second << endl;
    }
    // range-based-for循环unordered_map
    /* C++的范围循环(range-based-for)，在遍历容器的时候，auto自动推导的类型是容器的value_type类型，而不是迭代器，
    而见<https://en.cppreference.com/w/cpp/container/unordered_map>，unordered_map中的value_type是std::pair<const Key, T>，
    所以以下必须是pair<"const" string, int> &entry，否则报错。最好是用auto，否则不得不了解容器内部细节。 */
    for (pair<const string, int> &entry : map1) {
        cout << entry.first << "--" << entry.second << endl;
    }

    // <------ unordered_set ------> 类似Java的HashSet
    unordered_set<string> set1;
    set1.insert("asdf");
    set1.insert("asdf");
    set1.insert("qwer");
    // C++ 17，unordered_set有bool contains()方法
    cout << (set1.find("asdf") == set1.end() ? "false" : "true") << endl;
    for (auto &s : set1) {
        cout << s << endl;
    }

    // <------ map ------> 底层是红黑树，相当于Java的TreeMap
    map<string, int> map2;
    map2["a"] = 1;
    map2["b"] = 2;
    map2["c"] = 3;
    if (map2.count("a")) {
        /* 这里如果写`auto &p = map2.find("a");`会报错不能把p bind到右边，因为find()返回的是右值。
        参考<https://zhuanlan.zhihu.com/p/335994370>:
        引用是变量的别名，由于右值没有地址，没法被修改，所以左值引用无法指向右值。
        但是，const左值引用是可以指向右值的，这里可以写成
        `const auto &p = map2.find("a");`
        const左值引用不会修改指向值，因此可以引用右值(**const左值引用可以绑定到右值**)。
        参考<https://www.zhihu.com/question/310966840/answer/595546279>:
        const T&绑定到右值，这时会创建一个临时变量T，然后让引用绑定到T。

        右值引用可以绑定到右值，因此这里也可以写成`auto &&p = map2.find("a");`

        这二者的本质应该是在于，函数返回右值时，调用函数的栈帧中会有个struct去接收那个右值，只是如果不给这个右值名字则其
        是匿名的，上面两种情况都是把这个匿名接收的内存部分用起来了。如果不是const左值引用绑定到右值，而是左值引用绑定到右值，
        这时意味着后面代码可以尝试修改这个struct，这会有误导性，虽然引用绑定到了当前栈帧中的内存，但是看起来像是在修改右值，
        应该是因为这个所以C++禁止左值引用绑定到右值。

        这里是左值引用接收函数返回的右值的情况，还有这种情况:
        `const int &var = 10;`，参考<https://zhuanlan.zhihu.com/p/97128024>，这样实际上是:
        `const int temp = 10; const int &var = temp;`

        参考<https://zhuanlan.zhihu.com/p/99524127>，合法的绑定为:
        ```
        左值引用 = 左值
        右值引用 = 右值
        常左值引用 = 右值
        ```
        最方便的还是直接: `auto p = map2.find("a");`

        注意: **函数的返回值可能是左值也可能是右值**。当函数返回基本类型或者直接返回对象时，返回值是右值。当函数返回引用时，
        返回值是左值，但是，需要函数内部自行保证内存的有效性，例如，返回静态变量或者返回new出的东西。
        像
        ```
        int& getValue() {
            int x = 42;
            return x;
        }
        ```
        这样不合理的代码编译器会有警告。
        */
        auto p = map2.find("a");
        if (p != map2.end()) {
            cout << p->first << " " << p->second << endl;
        }
        /* 逻辑应该是:
        foreach循环遍历容器，使用auto &p，这时p是容器元素类型(若容器元素类型为基础类型则直接int val : v就可以，不用引用)。
        接收迭代器，用auto p。
        */
    }
    cout << map2.lower_bound("a")->first << endl; // 返回第一个>=x的迭代器
    cout << map2.upper_bound("a")->first << endl; // 返回第一个>x的迭代器
    // 如果要找最后一个<=x，则是map2.upper_bound("a") - 1
    cout << map2.begin()->first << endl; // 第一个元素的key
    cout << map2.rbegin()->first << endl; // 最后一个元素的key

    // std::map自定义排序器，按从大到小排
    // C++ 11 lambda表达式的参数的类型不能声明为auto，C++ 14可以，所以如果是C++ 14可以直接写[](auto &x, auto &y)
    /* 这里参数按引用传递的话必须声明为const，因为map需要避免key被改，如果写成[](int &x, int &y)，stl_tree.h中
    会有一个static_assert会报错：static_assert(__is_invocable<_Compare&, const _Key&, const _Key&>{}, "comparison object must be invocable with two arguments of key type")
    */
    // 对C++ 11，这里可以写成[](const int &x, const int &y)或者[](int x, int y)
    auto comparator2 = [](const int &x, const int &y) { // C++ 11的写法
        return x > y;
    };
    map<int, int, decltype(comparator2)> map3(comparator2);
    map3[1] = 1;
    map3[2] = 2;
    cout << map3.begin()->first << endl; // 第一个元素的key
    cout << map3.rbegin()->first << endl; // 最后一个元素的key

    // <------ set ------> 底层是红黑树，相当于Java的TreeSet
    set<string> set2;
    set2.insert("aa");
    set2.insert("bb");
    set2.insert("cc");
    set2.erase("bb");
    for (auto &s : set2) {
        cout << s << endl;
    }

    // <------ list ------> 双向链表
    list<int> myList;
    myList.push_front(1);
    myList.push_back(3);
    myList.push_back(4);
    myList.pop_back();
    // list的迭代器没有+运算符，不能myList.begin() + 2之类的，对链表这是合理的。所以要myList.begin() + 2必须对it循环++到指定位置。
    myList.insert(++myList.begin(), 2);

    // <------ pair ------>
    pair<int, int> p1(1, 2);
    pair<int, int> p2 = make_pair(1, 3); // make_pair不用写泛型类型，会自动推导。这里这行创建了两个pair。
    cout << p2.first << ',' << p2.second << endl;

    // <------ tuple ------>
    tuple<int, int, int> t(2, 4, 6);
    cout << get<0>(t) << ',' << get<1>(t) << ',' << get<2>(t) << endl;

    // C++还有multiset这种容器，允许元素重复，但这可以用map实现，用value来计数即可

    /* C中max()和min()可能是用宏来实现的，因此例如`max(3, rand() % 6)`会被展开为`(((3) > (rand() % 6)) ? (3) : (rand() % 6))`，
    宏展开导致函数调用了两次，这可能导致最终的值是个错误的小于3的值。而C++的std::max()和std::min()是函数，没有这个问题。
    */

    /* vector<bool>的坑，vector<bool>不是标准vector的实现方式，单独实现了std::vector<bool>，内部用bit存，用operator[]时，
    返回的会是一个代理引用对象std::vector<bool>::reference，以下`auto visit1 = visited1[0]; visit1 = false;`会导致修改visited1中的内容。

    避坑的话直接用vector<int>即可。

    参考:
    <https://www.zhihu.com/question/23367698/answer/148258487>
    <https://www.zhihu.com/question/23367698/answer/2744093298>
    <https://en.cppreference.com/w/cpp/container/vector_bool>
    <https://en.cppreference.com/w/cpp/container/vector>
    */
    vector<bool> visited1 = {true, false, true};
    // vector<bool>的operator[]返回类型是vector<bool>中的一个内部类，这里visit1类型为std::vector<bool>::reference。
    auto visit1 = visited1[0]; // 直接写bool visit1 = visited1[0]然后visit1 = false是ok的，会隐式转换代理对象为bool，不会影响visited1[0]
    visit1 = false; // 这行过后visited1[0]也会变为false

    vector<int> visited2 = {1, 0, 1};
    auto visit2 = visited2[0]; // visited2[0]返回T&，auto推断时会去除引用，因此visit2类型为int
    visit2 = false; // 这行过后不会导致visited2[0]变
    // 上面一样的代码，对vector<bool>和vector<int>有不同的结果，因此vector<bool>并不是一个通常意义上的vector容器，有坑。
}