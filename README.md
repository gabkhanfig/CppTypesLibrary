# Cpp Types Library

**Unit Testing** is implemented to ensure accurate behavior in all available contexts.

<h3>Currently added types:</h3>

- [String](https://github.com/gabkhanfig/CppTypesLibrary/tree/master/CppTypesLibrary/src/types/string)

<h2>String</h2>

A **constexpr** valid replacement to std::string that supports [**Small String Optimization**](https://blogs.msmvps.com/gdicanio/2016/11/17/the-small-string-optimization/) of a greater size. Many (if not all) SSO std::string implementations that are constexpr qualified have an small maximum size of 16 characters. This implementation allows for SSO strings of size 24 (including null terminator). This string, excluding any heap allocations for long strings, has a size of 32 bytes, which is identical to many std::string implementations such as MSVC++ std::string. This string also supports constexpr functionality at the same time, meaning it can be fully utilized is effectively any context. This string is also [**Unit Tested**](https://github.com/gabkhanfig/CppTypesLibrary/blob/master/CppTypesLibrary/src/types/string/string_unit_tests.cpp).