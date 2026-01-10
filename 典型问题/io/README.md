# 自定义的 io 板子和 debug 工具配置。

用 [io_slim.cpp](./io_slim.cpp) 里的感觉更合适一些，io.cpp 整太长了。

## [io.cpp](./io.cpp)

### 输入输出

快读快写、格式化输出等工具函数。

只使用 c 的 stdio (getchar / printf / putchar)，不使用任何 c++ 的 iostream (cin / cout)，因此也不需要 `cin.tie(0)->sync_with_stdio(false);`。

输入函数:

* `rd(T& x)`，T 为整数类型（int / long long）

* `rd(std::string& s)`

* `rdline(std::string& s)`

    与通常的读行函数不同，**rdline 的实现跳过了前导空白字符**

输出函数:

* `wr(T x)`，T 为 整数 / 浮点 类型

* `wr(char c)`

* `print(T& t) / println(T& t)`，实现了对常见类型的各种 print 函数

* `print(string& fmt, ...) / println(string& fmt, ...)`，类似 c 的 `printf()`，不过占位符用 `{}`

### debug 工具

本地 debug 工具配置，包括 输入重定向 和 debug打印函数。

namespace am::debug 下的函数作用需要在本地自行定义好 **DEBUG 宏**，若无 DEBUG 宏则不会起任何作用。

预期使用方式为: 本地 IDE 定义好 DEBUG 宏，使用 `debug()` 函数打印调试，且提交至 oj 时无需任何代码更改。

通过在本地定义 DEBUG 宏，在本地开启了:

1. 输入重定向

    若定义了 DEBUG 宏，则会尝试 fopen INPUT_FILE (默认为 "case.txt")，若确实有这个文件，则 am::debug 会将 stdin 重定向为 INPUT_FILE。

    否则，stdin 仍为终端。

2. debug 宏函数

    * `debug(x)`，用 BrightYellow 颜色打印 debug 变量

    * `debugf(fmt, ...)`，用 BrightYellow 颜色格式化打印

    注意 `debug()` 和 `debugf()` 都会**自动换行**

am::debug 的内容提交至 OJ 时，只要 OJ 没有定义 DEBUG 宏，就会**自动失效**，**无需**特意删除 debug 相关的内容，且在 OJ 上也不会有任何多余行为（例如尝试打开/重定向文件）。

## [io_slim.cpp](./io_slim.cpp)

### 输入输出

io.cpp 太长了，io_slim.cpp 把内容精简了下并压行。

输入函数:

* `rd(T& x)`，T 为 int / long long / std::string

* `rdline(std::string& s)`

    与通常的读行函数不同，**rdline 的实现跳过了前导空白字符**

输出函数:

* 统一只用 `print(string& fmt, ...)`

    "{}" 能直接接受 整数、char、字符串。
    
    但是这里的实现导致了个很神奇的点，例如`print("aa{}\n");`，这样的调用，占位符后面没给够对应参数，按理说应该是ub了，但是由于奇妙的巧合，`print("aa{}\n");`会直接调用 am::io::inner::print_fmt_impl(it, end)，然后会直接打印字符串。于是，print(fmt, ...) 神奇地具有了 `printf(fmt, ...)` 和 `print(string)` 的双重功能。
    
    占位符 > 打印参数，后面占位符直接打印为 "{}"，占位符 < 打印参数，后面参数不打印。不会发生 segmentation fault。

格式化函数:

* `string format(begin, end, separator, bracket)`

    用来 format 一些结构，然后打印，例如 `am::io::format(vec.begin(), vec.end())` 会直接得到 "[1, 7, 5, 3, 2]"，separator 和 bracket 可以指定 分隔符 和 要不要括号，要哪种括号 。

    想要打印 vector 的话，就可以 `print("{}\n", am::io::format(vec.begin(), vec.end()));` 。

### debug 工具

和 io.cpp 里的没变化，只是压行了。

## [io_slim_final.cpp](./io_slim_final.cpp) （推荐）

再压缩，现在行数就比较小了。

### 输入输出

输入函数:

* `rd(T& x)`，T 为 int / long long / std::string

* `rdline(std::string& s)`

    与通常的读行函数不同，**rdline 的实现跳过了前导空白字符**

输出函数:

* `wr(T x)`，T 为 int / long long / char

* `wr(const std::string& s)`

剩余功能用 getchar / putchar / printf 完成即可，若要 printf std::string 则: printf("%s", s.c_str());

格式化函数:

* `string format(iterable, separator, bracket)`

### debug 工具

同样进行了简化，只实现为最简洁实用的三个功能：

1. 自动检测 case.txt 并输入重定向。

2. 设置输出有颜色以便在终端粘贴输入运行的话也好区分输入输出。作为 ans 的输出为绿色(这里绿色不代表正确性，以后觉得有误导性的话可以改成紫色95)，debug() 块里的输出为黄色。

3. `debug(code)` 块。若无 DEBUG 宏，则被 debug() 包裹的 code 不生效，否则生效，用于本地调试。

## [io_minimized.cpp](./io_minimized.cpp)

极简化的，对大部分情况也够用了

## 关于函数名冲突问题

printf 是 C 有的函数，然后才发现 C++23 有 std::print 和 std::println，格式和我整的一模一样，甚至占位符也都是"{}"。（我是看 Rust 这样所以我也用 "{}" 作占位符，感觉 chatgpt 学习了 C++23 的实现，但是没和我说这个事）

用 `-std=c++23` 会导致 `print` 有歧义。

所以后面可以改改，把 io_slim.cpp 里的那个 `print` 改成 `prtf`。

# 关于 windows 下换行符的问题

`rd() / rdline() / wr()` 等函数用的是 `getchar() / putchar()`，判断 `getchar() == '\n'` 和 `wr('\n')` 的逻辑对于 windows 下换行符为 `\r\n` 会不会有问题？

不会，`getchar` 和 `putchar` 操作的是 stdin / stdout，而 stdin / stdout / stderr 默认以**文本模式**打开，CRT（C runtime）会自动做换行转换。所以在文本模式下， `putchar('\n')` 实际在 windows 下会输出 `\r\n`，对于行末的 `\r\n`，`getchar()` 只会一次读到 `\n`，`\r` 会被 CRT 吃掉。

如果 stdin / stdout 是**二进制模式**，例如 `freopen("case.txt", "rb", stdin)`，`getchar` 确实会读到 `\r`，`putchar('\n')` 也只会原样输出 `\n`。

此外，`read() / write()` 总是二进制模式，二者是系统调用（不过严格来说 windows 下 msvc 的 read / write 是 CRT 对 Win32 API ReadFile / WriteFile的封装），不会转换字符。

试了下，如果文件里 "\r\n" 没连着的话，文本模式也能读出 '\r'

```cpp
FILE *fp = fopen("case.txt", "wb");
if (fp) {
    fputc('1', fp);
    fputc('\r', fp);
    fclose(fp);
}

freopen("case.txt", "r", stdin);
int c;
c = getchar(); // '1'
c = getchar(); // 会读到'\r'
c = getchar(); // EOF
```