# Cpp Types Library

**Unit Testing** is implemented to ensure accurate behavior in all available contexts.

<h3>Currently added types:</h3>

- [String](https://github.com/gabkhanfig/CppTypesLibrary/tree/master/CppTypesLibrary/src/types/string)
- [Dynamic Array](https://github.com/gabkhanfig/CppTypesLibrary/tree/master/CppTypesLibrary/src/types/array)
- [Bitset](https://github.com/gabkhanfig/CppTypesLibrary/tree/master/CppTypesLibrary/src/types/bitset)

<h2>String</h2>

A **constexpr** valid replacement to std::string that supports [**Small String Optimization**](https://blogs.msmvps.com/gdicanio/2016/11/17/the-small-string-optimization/) of a greater size. Many (if not all) SSO std::string implementations that are constexpr qualified have an small maximum size of 16 characters. This implementation allows for SSO strings of size 24 (including null terminator). This string, excluding any heap allocations for long strings, has a size of 32 bytes, which is identical to many std::string implementations such as MSVC++ std::string. This string also supports constexpr functionality at the same time, meaning it can be fully utilized is effectively any context. This string is also [**Unit Tested**](https://github.com/gabkhanfig/CppTypesLibrary/blob/master/CppTypesLibrary/src/types/string/string_unit_tests.cpp).

<h2>Dynamic Array</h2>

A **constexpr** valid replacement to std::vector that has a smaller footprint, being 16 bytes instead of 24/32. Due to constexpr functionality, this dynamic array can be initialized, and have any operations done on it at compile time. This dynamic array is also [**Unit Tested**](https://github.com/gabkhanfig/CppTypesLibrary/blob/master/CppTypesLibrary/src/types/array/dynamic_array_tests.cpp).

<h2>Bitset</h2>

A **constexpr** valid replacement to std::bitset that has a smaller memory footprint for small bitsets. Rather than a default smallest size of 4 bytes, this bitset has a smallest default of 1 byte, and then scaling up to 2, 4, and 8 as necessary depending on template parameters. This bitset is also [**Unit Tested**](https://github.com/gabkhanfig/CppTypesLibrary/blob/master/CppTypesLibrary/src/types/bitset/bitset_tests.cpp).
