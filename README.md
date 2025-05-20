# C++ Monadic Types: Maybe and Either

![GitHub License](https://img.shields.io/github/license/kurijlj/Cpp-Monadic-Types-Maybe-and-Either)
[![GitHub Super-Linter](https://github.com/kurijlj/Cpp-Monadic-Types-Maybe-and-Either/actions/workflows/code-syntax-style-check.yml/badge.svg)](https://github.com/marketplace/actions/super-linter)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/kurijlj/Cpp-Monadic-Types-Maybe-and-Either/cmake-multi-platform.yml?branch=main&event=push&style=flat&logo=cmake&label=CMake%20build&labelColor=%23064F8C)
![Static Badge](https://img.shields.io/badge/-v17-%23ffffff?style=flat&logo=cplusplus&labelColor=%2300599C)
![Static Badge](https://img.shields.io/badge/-3.14-%23ffffff?style=flat&logo=cmake&labelColor=%23064F8C)

## 🚀 Project Overview

This project provides robust and modern C++ implementations of the **Maybe** and
**Either** monads, leveraging `std::optional` and `std::variant` respectively.
These monadic types are powerful tools for writing more expressive, safer, and
less error-prone code by explicitly handling the presence or absence of values
(`Maybe`) and the success or failure of operations (`Either`) without relying on
traditional error codes, null pointers, or exceptions for control flow.

The implementations include:

* **`Maybe<T>`**: A type that represents an optional value,
akin to `std::optional<T>`.
* **`Either<T, Err>`**: A type that represents a value that is either a success
(`T`) or an error (`Err`).
* **Monadic `mbind` operation**: For applying functions to the contained value
(if present/successful) and chaining operations.
* **Convenient Pipe Operator (`|`)**: An overloaded operator for a fluent,
functional style of chaining monadic computations.

## ✨ Features

* **Type Safety**: Built on modern C++ standard library features
(`std::optional`, `std::variant`) for compile-time safety.
* **Expressive Code**: Enables a functional programming style for clearer error
and presence handling.
* **Resource Efficiency**: Designed with move semantics to ensure proper
movement of large objects (demonstrated in the demo).
* **Unit Tested**: Comprehensive unit tests using the **GoogleTest** framework
ensure reliability and correctness.
* **Cross-Platform Build**: Utilizes **CMake** for a robust and
portable build system.

## 🧩 Third-party Library Integration

* **[clipp](https://github.com/muellan/clipp):** The framework assumes clipp as
  a header-only library. Steps on how to link to the library are described in
  the top-level CMakeLists.txt file.
* **[GoogleTest](https://github.com/google/googletest):** The project integrates
  GoogleTest using the FetchContent module. The test target is added
  to the project in the CMakeLists.txt file.

## ⚙️ Usage Instructions

To integrate Maybe and Either into your own C++ projects, simply copy the header
files:

* `Maybe.h`
* `Either.h`

... into your project's source tree or an include directory. Since these are
header-only libraries, no separate compilation or linking is required beyond
ensuring your compiler can find the header files.

## 🛠️ Build Instructions

This project uses CMake for its build system. Follow these steps to build the
project on your system:

### Prerequisites

* A C++17 compatible compiler (e.g., GCC 7+, Clang 5+, MSVC 2017+)
* CMake (version 3.14 or higher recommended)
* GoogleTest (will be fetched automatically by CMake if not found)

### Steps

**1. Clone the repository:**

```bash
git clone https://github.com/kurijlj/Cpp-Monadic-Types-Maybe-and-Either-CLI-Framework
cd your-repo
```

**2. Create a build directory:**

It's good practice to build outside of the source tree.

```bash
mkdir build
cd build
```

**3. Configure CMake:**

  ```bash
  cmake ..
  ```

*(Optional: If you want to specify a generator, e.g., for Ninja:* `cmake -G Ninja ..`
*or you want to build the tests:*`-DBUILD_TESTS:BOOL=ON`*)*

**4. Build the project:**

```bash
cmake --build .
```

This will compile the `Maybe` and `Either` libraries, their unit tests, and
the demo application.

## 🧪 Running Tests

After building, you can run the unit tests to verify the implementation:

```bash
cd build
ctest --verbose
# or, for a specific test executable (e.g., if you have separate test executables for Maybe and Either)
# ./bin/test_maybe.exe
# ./bin/test_either.exe
# ./bin/maybe_either_demo.exe
```

### 💡 Demo Application

A demo application is included to showcase the usage of Maybe and Either,
particularly demonstrating how ExpensiveToCopy objects are handled efficiently
through move semantics.

To run the demo:

```bash
cd build
./bin/maybe_either_demo.exe
```

## 🤝 Contributing

Contributions are welcome! Please feel free to open issues, submit pull
requests, or suggest improvements.

## 📄 License

This repository is licensed under the [GNU General Public License
v3.0](LICENSE), ensuring that the code remains open-source and accessible to the
community.

## 📧 Contact

Ljubomir Kurij - <ljubomir_kurij@protonmail.com>

Project Link: <https://github.com/kurijlj/Cpp-Monadic-Types-Maybe-and-Either>
