# Debug Template (C++ / Sublime Text)

A powerful C++ debugging header for competitive programming, featuring type introspection, pretty-printing, and colored structured output.

Designed for fast local debugging with zero impact on submissions.

---

## Features

* 🧠 **Automatic type detection** (int, vector, map, tuple, etc.)
* 🖨️ **Pretty-print for STL containers** (including nested structures)
* 🎯 **Variadic debug macro**: `dbg(...)`
* 🎨 **Colored output**:

  * Yellow → line number
  * Green → variable name + value
  * Blue → type info
  * Cyan → range/matrix debug
* 📍 **Line number tracking**
* 📦 Supports:

  * `vector`, `deque`, `array`
  * `set`, `map`, `unordered_map`
  * `queue`, `stack`, `priority_queue`
  * `pair`, `tuple`
* 🔍 Extra tools:

  * `dbg_range(...)`
  * `dbg_matrix(...)`

---

## Usage

Include the header:

```cpp
#include "debug.h"
```

Enable debug locally:

```cpp
#define LOCAL
```

Example:

```cpp
int x = 10;
vector<vector<int>> a = {{1,2}, {3,4}};
map<int, vector<int>> mp = {{1, {2,3}}, {4, {5}}};

dbg(x, a, mp);
```

---

## Example Output

*(colors shown in supported terminals)*

```
[Line 12] [ x = 10 ] < int > | [ a = {
  {1, 2},
  {3, 4}
} ] < vector<vector<int>> > | [ mp = {
  1 -> {2, 3}
  4 -> {5}
} ] < map<int,vector<int>> >
```

---

### Range Debug

```cpp
vector<int> v = {1,2,3,4,5};
dbg_range(v, 1, 3);
```

Output:

```
[Line 20] range[1...3] = { 2, 3, 4 }
```

---

### Matrix Debug

```cpp
vector<vector<int>> mat = {
    {1,2,3},
    {4,5,6}
};
dbg_matrix(mat);
```

Output:

```
[Line 27] matrix =
[0]    1   2   3
[1]    4   5   6
```

---

## How It Works

* Template specialization for type names
* Container detection via `begin()` / `end()`
* Recursive pretty-printing for nested structures
* Output goes to `stderr`
* Automatically disabled when `ONLINE_JUDGE` is defined

---

## Compilation

Local (debug enabled):

```bash
g++ -std=c++17 -O2 -DLOCAL main.cpp -o main
```

Submission:

* Remove `-DLOCAL` or comment out `#define LOCAL`

---

## Notes

* No overhead on online judge
* Safe to leave in contest code
* Optimized for readability under pressure

---

## Terminal Support (Important)

This template uses **ANSI color codes**, so you need a terminal that supports them.

If your current terminal does not show colors properly, consider using:

* Windows: Windows Terminal (recommended)
* Cross-platform: https://github.com/microsoft/terminal

Or install a better terminal like:

👉 https://learn.microsoft.com/en-us/windows/terminal/install

---

## Author

Minh Duc
