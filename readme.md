# `subarray`
`subarray` is a standalone header-only mod

### `subarray<B,E>(T[N]) -> std::array<T,b-e>`
`subarray` is a function for materialising a C-array sub-range as a std::array,
<br>i.e. for trimming a suppiled C-array and converting it to std::array in one go.
* Copies a C-array, whole or a sub-range, to a returned std::array
* Enables direct initialisation of std::array from a C-array range
  * Eliminates the need for two-phase initialisation
  * and so allows const / constexpr initialisation without IIILE
* Uses negative indices to represent offsets from the end of the C-array
  * Saves the caller from computing the offset, possibly calling size()

For example:
```c++
    constexpr auto hello_6 = subarray("hello");
    constexpr auto hello5 = subarray<0,-1>("hello");
```
1. The first call, without any template arguments, copies the whole array
2. The second call strips the terminating null from the string literal argument

The first call is the same as [`to_array`](http://en.cppreference.com/w/cpp/experimental/to_array), proposed for Library TS2
[N3824](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3824.htm):
* `std::experimental::to_array(T[N]) -> std::array<T,N>`

`subarray` adds template parameters to specify [begin,end) index offsets:
* `subarray<B,E>(T[N]) -> std::array<T,b-e>`
<br>Positive indices in the range [0,N) are regular indices from array.begin()
<br>Negative indices in the range [-N,-1] are offsets from array.end()
<br>array.end() is itself is a special case represented by value `LONG_MAX`
<br>(the 0 value is otherwise ambiguous)

If only one template argument is given then it specifies the range begin index
<br>and the range end defaults to array.end(), that is, it returns a suffix of the array:
```c++
    constexpr auto ello_5 = subarray<1>("hello");
```
See [`test_subarray.cpp`](test_subarray.cpp) for more usage examples.

### `sget<I>(a)`
The subarray lib also defines a pair of templated indexing helpers,
<br>like `std::get<I>` but for the signed indices as used by subarray:
* `sget<I>(T[N]) -> T`
* `sget<I>(std::array<T,N>) -> T`

For example,
* `sget<0>(a)` returns the first element of `a`
* `sget<-1>(a)` returns the last element of `a`