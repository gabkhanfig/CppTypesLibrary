# Cpp Types Library

**Unit Testing** is implemented to ensure accurate behavior in all available contexts.

<h3>Currently added types:</h3>

- [String](https://github.com/gabkhanfig/CppTypesLibrary/tree/master/CppTypesLibrary/src/types/string)
- [Dynamic Array](https://github.com/gabkhanfig/CppTypesLibrary/tree/master/CppTypesLibrary/src/types/array)
- [Bitset](https://github.com/gabkhanfig/CppTypesLibrary/tree/master/CppTypesLibrary/src/types/bitset)

<h2>String</h2>

A **constexpr** valid replacement to std::string that supports [**Small String Optimization**](https://blogs.msmvps.com/gdicanio/2016/11/17/the-small-string-optimization/) along with [**Const Data Segment**](https://en.wikipedia.org/wiki/Data_segment) strings. The primary use is video games in which the systems typically have larger amounts of ram, and thus having a larger buffer is valid. This implementation allows any buffer size that is a multiple of 32 (includes null terminator). Any runtime const char* strings loaded into the const data segment of the application will not bother performing unnecessary copies. Also makes for fast string equality checking on those strings. String has the correct alignment for future SIMD optimization.

<h2>Dynamic Array</h2>

A **constexpr** valid replacement to std::vector that has a smaller footprint, being 16 bytes instead of 24/32. Due to constexpr functionality, this dynamic array can be initialized, and have any operations done on it at compile time. This dynamic array is also [**Unit Tested**](https://github.com/gabkhanfig/CppTypesLibrary/blob/master/CppTypesLibrary/src/types/array/dynamic_array_tests.cpp).

<h2>Bitset</h2>

A **constexpr** valid replacement to std::bitset that has a smaller memory footprint for small bitsets. Rather than a default smallest size of 4 bytes, this bitset has a smallest default of 1 byte, and then scaling up to 2, 4, and 8 as necessary depending on template parameters. This bitset is also [**Unit Tested**](https://github.com/gabkhanfig/CppTypesLibrary/blob/master/CppTypesLibrary/src/types/bitset/bitset_tests.cpp).
