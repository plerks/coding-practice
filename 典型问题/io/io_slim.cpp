#include <vector>

// 快读快写、格式化输出等工具函数。只使用 c 的 stdio (getchar / printf / putchar)，不使用任何 c++ 的 iostream (cin / cout)
// ┌──────────────────────────── io template & debug tool begin ────────────────────────────┐
#include <string>
#include <type_traits>
namespace am::io {
    template <typename T, typename = std::enable_if<std::is_integral_v<T>>>
    void rd(T& x) { // 读入整数
        T k = 0, f = 1;
        char c = getchar();
        while ((c < '0' || c > '9') && c != EOF) f = (c == '-') ? 0 : f, c = getchar();
        while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
        x = f ? k : -k;
    }
    void rd(std::string& s) { // 读入单词
        s.clear(); int c = getchar();
        while (c == ' ' || c == '\n') c = getchar();
        while (c != ' ' && c != '\n' && c != EOF) { s.push_back(c); c = getchar(); }
    }
    void rdline(std::string& s) { // 读入一行，注意：与通常的读行函数不同，rdline 的实现跳过了前导空白字符
        s.clear(); int c = getchar();
        while (c == ' ' || c == '\n') c = getchar();
        while (c != '\n' && c != EOF) {
            s.push_back(c);
            c = getchar();
        }
    }
    namespace inner { // 为 print(fmt, ...) 提供辅助函数，外部不应使用这些函数，但是由于 c++ 的限制没法直接定义为 private
        void print(char c) { // 打印 char
            putchar(c);
        }
        void print(const char s[]) { // 打印字符串字面量
            for (const char* c = s; *c != '\0'; ++c) putchar(*c);
        }
        template <typename T, typename = std::enable_if<std::is_integral_v<T>>>
        void print(T x) { // 打印整数
            if (x < 0) putchar('-'), x = -x;
            if (x > 9) print(x / 10);
            putchar((x % 10) ^ 48);
        }
        void print(const std::string& s) { // 打印 std::string
            const char *p = s.c_str();
            while (*p) print(*p), ++p;
        }
        __attribute__((unused))
        void print_fmt_impl(std::string::const_iterator begin, std::string::const_iterator end) {
            for (; begin != end; ++begin) print(*begin);
        }
        template <typename T, typename... Args> // 递归展开参数
        void print_fmt_impl(std::string::const_iterator begin, std::string::const_iterator end, T&& first, Args&&... rest) {
            while (begin != end) {
                if (*begin == '{' && std::next(begin) != end && *(begin + 1) == '}') {
                    print(first); begin += 2; // 跳过 {}
                    print_fmt_impl(begin, end, std::forward<Args>(rest)...); // 递归处理剩余参数
                    return;
                } else { print(*begin); ++begin; }
            }
        }
    }
    template <typename... Args>
    void print(const std::string& fmt, Args&&... args) { // 用格式化字符串打印 (类似 c 的 printf)，占位符为 {}
        inner::print_fmt_impl(fmt.begin(), fmt.end(), std::forward<Args>(args)...);
    }
    template <typename Iterator>
    std::string format(Iterator begin, Iterator end, const std::string& separator = ", ", const std::string& bracket = "[]") {
        std::string s;
        if (0 < bracket.size()) s.push_back(bracket[0]);
        for (; begin != end; begin++) { s.append(std::to_string(*begin)); if (std::next(begin) != end) s.append(separator); }
        if (1 < bracket.size()) s.push_back(bracket[1]);
        return s;
    }
} using namespace am::io;

namespace am::debug {
    // namespace debug 下的函数作用需要在本地自行定义好 DEBUG 宏，若无 DEBUG 宏则不会起任何作用，若通过 IDE 定义 DEBUG 宏，提交至 oj 时无需任何代码更改
    // 1. 本地 DEBUG 时的输入重定向。若有 DEBUG 宏且有 INPUT_FILE (默认为 case.txt) 这个文件，则将其作为输入
    // 2. 本地 DEBUG 时的调试打印函数。若有 DEBUG 宏则用 BrightYellow 颜色打印 INFO
    #ifdef DEBUG
        auto debug_init = []() -> int {
            // 终端一般是阻塞式的读，stdin重定向为文件后一般是非阻塞式的（会读到EOF）
            #define INPUT_FILE "case.txt" // 用例文件
            FILE* f = fopen(INPUT_FILE, "r");
            if (f) { // 若有 INPUT_FILE 则重定向输入
                freopen(INPUT_FILE, "r", stdin); fclose(f);
            }
            return 0;
        }();
    #endif
    #ifdef DEBUG
        // 这里 do {...} while (0) 的技巧：是为了让这个宏函数是一个语句，不能直接用 {...} ，其对 if (cond) debug(x); else foo(); 不行
        #define debug(x) \
            do { \
                print("\u{1B}[93m"); \
                print("[L{} {}] ", __LINE__, #x); \
                print("{}", x); \
                putchar('\n'); \
                print("\u{1B}[0m"); \
            } while (0)
        #define debugf(fmt, ...) \
            do { \
                print("\u{1B}[93m"); \
                print("[L{}] ", __LINE__); \
                print(fmt, ##__VA_ARGS__); \
                putchar('\n'); \
                print("\u{1B}[0m"); \
            } while (0)
    #else
    #define debug(x)   ((void)0)
    #define debugf(...) ((void)0)
    #endif
} using namespace am::debug;
// └──────────────────────────── io template & debug tool end   ────────────────────────────┘

int main(int argc, char const *argv[]) {
    print("a = {}, b = {}, c = {}\n", 1, 3, "dsa");

    /* 占位符后面没给对应参数，按理说应该是ub了，但是由于奇妙的巧合，这里会直接调用 am::io::inner::print_fmt_impl(it, end)，
    然后会直接打印字符串。于是，print(fmt, ...) 神奇地具有了 printf(fmt, ...) 和 print(string) 的双重功能
    */
    print("aa{}\n");
    
    int a = 3;
    debug(a);
    const std::vector<int> vec = {1, 7, 5, 3, 2};
    print("{}\n", am::io::format(vec.begin(), vec.end()));

    print("a = {}, b = {}, c = {}\n", 1, 3, "dsa");

    std::string s;
    rd(s);
    debug(s);
    debugf("s: {}", s);
    print("{}\n", s);
    return 0;
}