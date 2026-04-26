/*
TYPE_NAME   : int, long long, double, float, char, bool, string,
              array, vector, pair, tuple,
              set, multiset,
              map, unordered_map,
              queue, stack, priority_queue

PRINT_VALUE : primitive types,
              pair, tuple, deque , 
              vector / nested containers,
              map, queue, stack, priority_queue

EXTRA       : dbg(...), dbg_range(...),
              nested container formatting,
              line number + type display
*/
#pragma once
#include <bits/stdc++.h>
using namespace std;
// ================= COLOR =================
#ifndef ONLINE_JUDGE
#define DBG_RESET   "\033[0m"
#define DBG_RED     "\033[31m"
#define DBG_GREEN   "\033[32m"
#define DBG_YELLOW  "\033[33m"
#define DBG_BLUE    "\033[34m"
#define DBG_CYAN    "\033[36m"
#define DBG_PURPLE  "\033[35m"
#else
#define DBG_RESET   ""
#define DBG_RED     ""
#define DBG_GREEN   ""
#define DBG_YELLOW  ""
#define DBG_BLUE    ""
#define DBG_CYAN    ""
#define DBG_PURPLE  ""
#endif
// ================= TYPE NAME =================

template<typename T>
struct TypeName {
    static string get() { return "unknown"; }
};

#define REGISTER_TYPE(T) \
template<> struct TypeName<T> { \
    static string get() { return #T; } \
};
REGISTER_TYPE(bool)
REGISTER_TYPE(char)
REGISTER_TYPE(signed char)
REGISTER_TYPE(unsigned char)
REGISTER_TYPE(wchar_t)
REGISTER_TYPE(char16_t)
REGISTER_TYPE(char32_t)
REGISTER_TYPE(short)
REGISTER_TYPE(unsigned short)
REGISTER_TYPE(int)
REGISTER_TYPE(unsigned)
REGISTER_TYPE(long)
REGISTER_TYPE(unsigned long)
REGISTER_TYPE(long long)
REGISTER_TYPE(unsigned long long)
REGISTER_TYPE(float)
REGISTER_TYPE(double)
REGISTER_TYPE(long double)
REGISTER_TYPE(string_view)
REGISTER_TYPE(wstring)
REGISTER_TYPE(string)
// array 
template<typename T, size_t N>
struct TypeName<array<T,N>> {
    static string get() {
        return "array<" + TypeName<T>::get() + "," + to_string(N) + ">";
    }
};
// deque
template<typename T>
struct TypeName<deque<T>> {
    static string get() {
        return "deque<" + TypeName<T>::get() + ">";
    }
};

// bitset
template<size_t N>
struct TypeName<bitset<N>> {
    static string get() {
        return "bitset<" + to_string(N) + ">";
    }
};
// vector
template<typename T>
struct TypeName<vector<T>> {
    static string get() {
        return "vector<" + TypeName<T>::get() + ">";
    }
};
// pair
template<typename A, typename B>
struct TypeName<pair<A,B>> {
    static string get() {
        return "pair<" + TypeName<A>::get() + "," + TypeName<B>::get() + ">";
    }
};
// tuple
template<typename Tuple, size_t... I>
string tuple_type_name(index_sequence<I...>) {
    string res = "tuple<";
    ((res += TypeName<tuple_element_t<I, Tuple>>::get() +
        (I + 1 == tuple_size_v<Tuple> ? "" : ",")), ...);
    res += ">";
    return res;
}

template<typename... Args>
struct TypeName<tuple<Args...>> {
    static string get() {
        return tuple_type_name<tuple<Args...>>(
            index_sequence_for<Args...>{}
        );
    }
};
// set
template<typename T>
struct TypeName<set<T>> {
    static string get() {
        return "set<" + TypeName<T>::get() + ">";
    }
};

// multiset
template<typename T>
struct TypeName<multiset<T>> {
    static string get() {
        return "multiset<" + TypeName<T>::get() + ">";
    }
};

// map
template<typename K, typename V>
struct TypeName<map<K,V>> {
    static string get() {
        return "map<" + TypeName<K>::get() + "," + TypeName<V>::get() + ">";
    }
};

// unordered_map
template<typename K, typename V>
struct TypeName<unordered_map<K,V>> {
    static string get() {
        return "unordered_map<" + TypeName<K>::get() + "," + TypeName<V>::get() + ">";
    }
};
// multimap
template<typename K, typename V>
struct TypeName<multimap<K,V>> {
    static string get() {
        return "multimap<" + TypeName<K>::get() + "," + TypeName<V>::get() + ">";
    }
};
// unordered_multimap
template<typename K, typename V>
struct TypeName<unordered_multimap<K,V>> {
    static string get() {
        return "unordered_multimap<" + TypeName<K>::get() + "," + TypeName<V>::get() + ">";
    }
};
// unordered_map 
template<typename T>
struct TypeName<unordered_set<T>> {
    static string get() {
        return "unordered_set<" + TypeName<T>::get() + ">";
    }
};
// queue 
template<typename T, typename Container>
struct TypeName<queue<T, Container>> {
    static string get() {
        return "queue<" + TypeName<T>::get() + ">";
    }
};
// stack 
template<typename T, typename Container>
struct TypeName<stack<T, Container>> {
    static string get() {
        return "stack<" + TypeName<T>::get() + ">";
    }
};

// priority_queue
template<typename T, typename Container, typename Compare>
struct TypeName<priority_queue<T, Container, Compare>> {
    static string get() {
        return "priority_queue<" + TypeName<T>::get() + ">";
    }
};

// helper
template<typename T>
string type_name() {
    return TypeName<T>::get();
}

// ================= CONTAINER DETECT =================

template<typename T, typename = void>
struct is_container : false_type {};

template<typename T>
struct is_container<T,
    void_t<
        decltype(begin(declval<T>())),
        decltype(end(declval<T>()))
    >
> : true_type {};

template<>
struct is_container<string> : false_type {};

// ================= PRINT VALUE =================

template<typename T>
enable_if_t<!is_container<T>::value> print_value(const T &x, int depth = 0) {
    cerr << x;
}

template<typename A, typename B>
void print_value(const pair<A,B> &p, int depth = 0) {
    cerr << "{ ";
    print_value(p.first, depth + 1);
    cerr << ", ";
    print_value(p.second, depth + 1);
    cerr << " }";
}
template<typename Tuple, size_t... I>
void print_tuple(const Tuple& t, index_sequence<I...>) {
    cerr << "{ ";
    ((print_value(get<I>(t)),
      cerr << (I + 1 == sizeof...(I) ? "" : ", ")), ...);
    cerr << " }";
}

template<typename... Args>
void print_value(const tuple<Args...>& t, int depth = 0) {
    print_tuple(t, index_sequence_for<Args...>{});
}
// queue
template<typename T>
void print_value(queue<T> q, int depth = 0) {
    cerr << "{ ";
    bool first = true;
    while (!q.empty()) {
        if (!first) cerr << ", ";
        print_value(q.front(), depth + 1);
        q.pop();
        first = false;
    }
    cerr << " }";
}

// stack
template<typename T>
void print_value(stack<T> s, int depth = 0) {
    cerr << "{ ";
    bool first = true;
    while (!s.empty()) {
        if (!first) cerr << ", ";
        print_value(s.top(), depth + 1);
        s.pop();
        first = false;
    }
    cerr << " }";
}
// deque
template<typename T>
void print_value(const deque<T>& dq, int depth = 0) {
    cerr << "{ ";
    bool first = true;
    for (const auto& x : dq) {
        if (!first) cerr << ", ";
        print_value(x, depth + 1);
        first = false;
    }
    cerr << " }";
}

// bitset
template<size_t N>
void print_value(const bitset<N>& bs, int depth = 0) {
    cerr << bs;
}
// priority_queue
template<typename T>
void print_value(priority_queue<T> pq, int depth = 0) {
    cerr << "{ ";
    bool first = true;
    while (!pq.empty()) {
        if (!first) cerr << ", ";
        print_value(pq.top(), depth + 1);
        pq.pop();
        first = false;
    }
    cerr << " }";
}
template<typename K, typename V>
void print_value(const map<K,V>& mp, int depth = 0) {
    cerr << "{\n";
    for (auto &[k,v] : mp) {
        cerr << string((depth + 1) * 2, ' ');
        print_value(k, depth + 1);
        cerr << " -> ";
        print_value(v, depth + 1);
        cerr << '\n';
    }
    cerr << string(depth * 2, ' ') << "}";
}
// container đẹp hơn (nested)
template<typename T>
enable_if_t<is_container<T>::value, void>
print_value(const T &v, int depth = 0) {
    cerr << "{";
    bool first = true;

    for (const auto &x : v) {
        if (!first) cerr << ", ";

        if constexpr (is_container<decay_t<decltype(x)>>::value) {
            cerr << "\n" << string((depth + 1) * 2, ' ');
            print_value(x, depth + 1);
        } else {
            print_value(x, depth + 1);
        }

        first = false;
    }

    if constexpr (!is_same_v<T, string>) {
        if (!v.empty() && is_container<decay_t<decltype(*v.begin())>>::value) {
            cerr << "\n" << string(depth * 2, ' ');
        }
    }

    cerr << "}";
}
// ================= RANGE / MATRIX DEBUG =================

#ifndef ONLINE_JUDGE

template<typename T>
void dbg_range(const vector<T>& a, int l, int r,
               const string& name = "range") {
    cerr << DBG_CYAN
         << "[Line " << __LINE__ << "] "
         << name << "[" << l << "..." << r << "] = { ";

    for (int i = l; i <= r; i++) {
        if (i > l) cerr << ", ";
        print_value(a[i]);
    }

    cerr << " }"
         << DBG_RESET
         << '\n';
}

template<typename T>
void dbg_matrix(const vector<vector<T>>& a,
                const string& name = "matrix") {
    cerr << DBG_CYAN
         << "[Line " << __LINE__ << "] "
         << name << " =\n";

    if (a.empty()) {
        cerr << "{}" << DBG_RESET << '\n';
        return;
    }

    for (int i = 0; i < (int)a.size(); i++) {
    cerr << "[" << i << "] ";
    for (auto &x : a[i]) {
        cerr << setw(4) << x;
    }
    cerr << '\n';
}

    cerr << DBG_RESET;
}

#else

template<typename T>
void dbg_range(const vector<T>&, int, int,
               const string& = "") {}

template<typename T>
void dbg_matrix(const vector<vector<T>>&,
                const string& = "") {}

#endif
// ================= VARIADIC DEBUG =================

#ifndef ONLINE_JUDGE
//find top level 
const char* find_top_level_comma(const char* s) {
    int round = 0, angle = 0, brace = 0;

    for (; *s; s++) {
        if (*s == '(') round++;
        else if (*s == ')') round--;
        else if (*s == '<') angle++;
        else if (*s == '>') angle--;
        else if (*s == '{') brace++;
        else if (*s == '}') brace--;

        else if (*s == ',' && round == 0 && angle == 0 && brace == 0) {
            return s;
        }
    }
    return nullptr;
}
inline void debug_out() {
    cerr << '\n';
}

template<typename T, typename... Args>
void debug_out(const char* names, T&& value, Args&&... args) {
    const char* comma = find_top_level_comma(names);
    cerr << DBG_GREEN << "[ " << DBG_RESET;
    if (comma) {
        cerr.write(names, comma - names);
    } else {
        cerr << names;
    }

    cerr << " = ";
    print_value(value);
    cerr << DBG_BLUE
     << " ] < "
     << type_name<decay_t<T>>()
     << " >"
     << DBG_RESET;

    if constexpr (sizeof...(args) > 0) {
        cerr << " | ";
        debug_out(comma ? comma + 1 : names, forward<Args>(args)...);
    } else {
        cerr << '\n';
    }
}

// thêm line number
#define dbg(...) \
    cerr << DBG_YELLOW << "[Line " << __LINE__ << "] " << DBG_RESET, \
    debug_out(#__VA_ARGS__, __VA_ARGS__)

#else
#define dbg(...)
#endif
    /*
⣿⣿⣿⣿⣿⣿⡷⣯⢿⣿⣷⣻⢯⣿⡽⣻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠸⣿⣿⣆⠹⣿⣿⢾⣟⣯⣿⣿⣿⣿⣿⣿⣽⣻⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣻⣽⡿⣿⣎⠙⣿⣞⣷⡌⢻⣟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⡄⠹⣿⣿⡆⠻⣿⣟⣯⡿⣽⡿⣿⣿⣿⣿⣽⡷⣯⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣟⣷⣿⣿⣿⡀⠹⣟⣾⣟⣆⠹⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢠⡘⣿⣿⡄⠉⢿⣿⣽⡷⣿⣻⣿⣿⣿⣿⡝⣷⣯⢿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣯⢿⣾⢿⣿⡄⢄⠘⢿⣞⡿⣧⡈⢷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣧⠘⣿⣷⠈⣦⠙⢿⣽⣷⣻⣽⣿⣿⣿⣿⣌⢿⣯⢿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣟⣯⣿⢿⣿⡆⢸⡷⡈⢻⡽⣷⡷⡄⠻⣽⣿⣿⡿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣏⢰⣯⢷⠈⣿⡆⢹⢷⡌⠻⡾⢋⣱⣯⣿⣿⣿⣿⡆⢻⡿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⡎⣿⢾⡿⣿⡆⢸⣽⢻⣄⠹⣷⣟⣿⣄⠹⣟⣿⣿⣟⣿⣿⣿⣿⣿⣿⣽⣿⣿⣿⡇⢸⣯⣟⣧⠘⣷⠈⡯⠛⢀⡐⢾⣟⣷⣻⣿⣿⣿⡿⡌⢿⣻⣿⣿
⣿⣿⣿⣿⣿⣿⣧⢸⡿⣟⣿⡇⢸⣯⣟⣮⢧⡈⢿⣞⡿⣦⠘⠏⣹⣿⣽⢿⣿⣿⣿⣿⣯⣿⣿⣿⡇⢸⣿⣿⣾⡆⠹⢀⣠⣾⣟⣷⡈⢿⣞⣯⢿⣿⣿⣿⢷⠘⣯⣿⣿
⣿⣿⣿⣿⣿⣿⣿⡈⣿⢿⣽⡇⠘⠛⠛⠛⠓⠓⠈⠛⠛⠟⠇⢀⢿⣻⣿⣯⢿⣿⣿⣿⣷⢿⣿⣿⠁⣾⣿⣿⣿⣧⡄⠇⣹⣿⣾⣯⣿⡄⠻⣽⣯⢿⣻⣿⣿⡇⢹⣾⣿
⣿⣿⣿⣿⣿⣿⣿⡇⢹⣿⡽⡇⢸⣿⣿⣿⣿⣿⣞⣆⠰⣶⣶⡄⢀⢻⡿⣯⣿⡽⣿⣿⣿⢯⣟⡿⢀⣿⣿⣿⣿⣿⣧⠐⣸⣿⣿⣷⣿⣿⣆⠹⣯⣿⣻⣿⣿⣿⢀⣿⢿
⣿⣿⣿⣿⣿⣿⣿⣿⠘⣯⡿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣧⡈⢿⣳⠘⡄⠻⣿⢾⣽⣟⡿⣿⢯⣿⡇⢸⣿⣿⣿⣿⣿⣿⡀⢾⣿⣿⣿⣿⣿⣿⣆⠹⣾⣷⣻⣿⡿⡇⢸⣿
⣿⣿⣿⣿⣿⣿⣿⣿⡇⢹⣿⠇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠻⡇⢹⣆⠹⣟⣾⣽⣻⣟⣿⣽⠁⣾⣿⣿⣿⣿⣿⣿⣇⣿⣿⠿⠛⠛⠉⠙⠋⢀⠁⢘⣯⣿⣿⣧⠘⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⡈⣿⡃⢼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡙⠌⣿⣆⠘⣿⣞⡿⣞⡿⡞⢠⣿⣿⣿⣿⣿⡿⠛⠉⠁⢀⣀⣠⣤⣤⣶⣶⣶⡆⢻⣽⣞⡿⣷⠈⣿
⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠘⠁⠉⠉⠉⠉⠉⠉⠉⠉⠉⠙⠛⠛⢿⣄⢻⣿⣧⠘⢯⣟⡿⣽⠁⣾⣿⣿⣿⣿⣿⡃⢀⢀⠘⠛⠿⢿⣻⣟⣯⣽⣻⣵⡀⢿⣯⣟⣿⢀⣿
⣿⣿⣿⣟⣿⣿⣿⣿⣶⣶⡆⢀⣿⣾⣿⣾⣷⣿⣶⠿⠚⠉⢀⢀⣤⣿⣷⣿⣿⣷⡈⢿⣻⢃⣼⣿⣿⣿⣿⣻⣿⣿⣿⡶⣦⣤⣄⣀⡀⠉⠛⠛⠷⣯⣳⠈⣾⡽⣾⢀⣿
⣿⢿⣿⣿⣻⣿⣿⣿⣿⣿⡿⠐⣿⣿⣿⣿⠿⠋⠁⢀⢀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣌⣥⣾⡿⣿⣿⣷⣿⣿⢿⣷⣿⣿⣟⣾⣽⣳⢯⣟⣶⣦⣤⡾⣟⣦⠘⣿⢾⡁⢺
⣿⣻⣿⣿⡷⣿⣿⣿⣿⣿⡗⣦⠸⡿⠋⠁⢀⢀⣠⣴⢿⣿⣽⣻⢽⣾⣟⣷⣿⣟⣿⣿⣿⣳⠿⣵⣧⣼⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣽⣳⣯⣿⣿⣿⣽⢀⢷⣻⠄⠘
⣿⢷⣻⣿⣿⣷⣻⣿⣿⣿⡷⠛⣁⢀⣀⣤⣶⣿⣛⡿⣿⣮⣽⡻⣿⣮⣽⣻⢯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⢀⢸⣿⢀⡆
⠸⣟⣯⣿⣿⣷⢿⣽⣿⣿⣷⣿⣷⣆⠹⣿⣶⣯⠿⣿⣶⣟⣻⢿⣷⣽⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢀⣯⣟⢀⡇
⣇⠹⣟⣾⣻⣿⣿⢾⡽⣿⣿⣿⣿⣿⣆⢹⣶⣿⣻⣷⣯⣟⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢀⡿⡇⢸⡇
⣿⣆⠹⣷⡻⣽⣿⣯⢿⣽⣻⣿⣿⣿⣿⣆⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⢸⣿⠇⣼⡇
⡙⠾⣆⠹⣿⣦⠛⣿⢯⣷⢿⡽⣿⣿⣿⣿⣆⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠎⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⢀⣿⣾⣣⡿⡇
⣿⣷⡌⢦⠙⣿⣿⣌⠻⣽⢯⣿⣽⣻⣿⣿⣿⣧⠩⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⢰⢣⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⢀⢀⢿⣞⣷⢿⡇
⣿⣽⣆⠹⣧⠘⣿⣿⡷⣌⠙⢷⣯⡷⣟⣿⣿⣿⣷⡀⡹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣈⠃⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢀⣴⡧⢀⠸⣿⡽⣿⢀
⢻⣽⣿⡄⢻⣷⡈⢿⣿⣿⢧⢀⠙⢿⣻⡾⣽⣻⣿⣿⣄⠌⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⢁⣰⣾⣟⡿⢀⡄⢿⣟⣿⢀
⡄⢿⣿⣷⢀⠹⣟⣆⠻⣿⣿⣆⢀⣀⠉⠻⣿⡽⣯⣿⣿⣷⣈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⢀⣠⠘⣯⣷⣿⡟⢀⢆⠸⣿⡟⢸
⣷⡈⢿⣿⣇⢱⡘⢿⣷⣬⣙⠿⣧⠘⣆⢀⠈⠻⣷⣟⣾⢿⣿⣆⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⣠⡞⢡⣿⢀⣿⣿⣿⠇⡄⢸⡄⢻⡇⣼
⣿⣷⡈⢿⣿⡆⢣⡀⠙⢾⣟⣿⣿⣷⡈⠂⠘⣦⡈⠿⣯⣿⢾⣿⣆⠙⠻⠿⠿⠿⠿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⢋⣠⣾⡟⢠⣿⣿⢀⣿⣿⡟⢠⣿⢈⣧⠘⢠⣿
⣿⣿⣿⣄⠻⣿⡄⢳⡄⢆⡙⠾⣽⣿⣿⣆⡀⢹⡷⣄⠙⢿⣿⡾⣿⣆⢀⡀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⣀⣠⣴⡿⣯⠏⣠⣿⣿⡏⢸⣿⡿⢁⣿⣿⢀⣿⠆⢸⣿
⣿⣿⣿⣿⣦⡙⣿⣆⢻⡌⢿⣶⢤⣉⣙⣿⣷⡀⠙⠽⠷⠄⠹⣿⣟⣿⣆⢙⣋⣤⣤⣤⣄⣀⢀⢀⢀⢀⣾⣿⣟⡷⣯⡿⢃⣼⣿⣿⣿⠇⣼⡟⣡⣿⣿⣿⢀⡿⢠⠈⣿
⣿⣿⣿⣿⣿⣷⣮⣿⣿⣿⡌⠁⢤⣤⣤⣤⣬⣭⣴⣶⣶⣶⣆⠈⢻⣿⣿⣆⢻⣿⣿⣿⣿⣿⣿⣷⣶⣤⣌⣉⡘⠛⠻⠶⣿⣿⣿⣿⡟⣰⣫⣴⣿⣿⣿⣿⠄⣷⣿⣿⣿
*/
