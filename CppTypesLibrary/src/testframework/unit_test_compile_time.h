#pragma once

#ifndef RUN_UNIT_TESTS_AT_COMPILE_TIME
#define RUN_UNIT_TESTS_AT_COMPILE_TIME true
#endif

#define _pragmsg(s) _Pragma(#s)
#define PRAGMA_MESSAGE(msg) _pragmsg(message(#msg))

#ifndef TEST_TYPES
#error TEST_TYPES macro for compile-type unit tests not defined before including unit_test_compile_time.h
#endif


#if RUN_UNIT_TESTS_AT_COMPILE_TIME == true

/* Compile time test assertion. Uses constexpr functions to ensure functionality while compiling.
In the header that defines this macro, by setting RUN_UNIT_TESTS_AT_COMPILE_TIME to false, unit tests will not run.
@param test: Constexpr function returning some checkable condition (usually bool) to static assert.  
@param message: Message to display upon test failing.*/
#define TEST_ASSERT(test, message) \
PRAGMA_MESSAGE([Run Unit Test]: test); \
static_assert(test, "[" TEST_TYPES " Unit Test]: " #test "... " message)

#else

/* Will not execute. Define RUN_UNIT_TESTS_AT_COMPILE_TIME to true to make tests run. */
#define TEST_ASSERT(test, message)

#endif

