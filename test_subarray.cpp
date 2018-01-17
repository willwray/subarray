#include <subarray.hpp>
#include <cassert>

int main()
{
    using namespace ltl;

    constexpr char a[]{'0','1','2','3'};
    constexpr auto e = std::size(a);

    static_assert( e == 4);

    static_assert( sget<0>(a) == '0');
    static_assert( sget<-e>(a) == '0');
    static_assert( sget<-1>(a) == '3');
    static_assert( sget<e-1>(a) == '3');

    {
    // Equivalent ways to copy entire C-array to std::array with subarray<>()
    // No template params defaults to begin and end.
    constexpr auto A = subarray(a);

    static_assert( std::size(A) == e);

    static_assert( sget<0>(A) == '0');
    static_assert( sget<-e>(A) == '0');
    static_assert( sget<-1>(A) == '3');
    static_assert( sget<e-1>(A) == '3');

    // One template param specifies begin offset as 0|-N, end defaults to end.
    constexpr auto B = subarray<0>(a);
    constexpr auto C = subarray<-e>(a);
    // Two template param specify begin offset and explicit end as N|Nmax.
    constexpr auto D = subarray<0,e>(a);
    constexpr auto E = subarray<0,LONG_MAX>(a);
    constexpr auto F = subarray<-e,e>(a);
    constexpr auto G = subarray<-e,LONG_MAX>(a);

    assert(A == B);
    assert(A == C);
    assert(A == D);
    assert(A == E);
    assert(A == F);
    assert(A == G);
    }
    {
    // Equivalent ways to copy array suffix.
    // One template param specifies begin offset
    // Two template param specify begin and end N|Nmax.
    constexpr auto A = subarray<1>(a);
    constexpr auto B = subarray<1-e>(a);
    constexpr auto C = subarray<1,e>(a);
    constexpr auto D = subarray<1,LONG_MAX>(a);
    constexpr auto E = subarray<1-e,e>(a);
    constexpr auto F = subarray<1-e,LONG_MAX>(a);

    static_assert( std::size(A)+1 == e);
    static_assert( sget<0>(A) == '1');
    static_assert( sget<-1>(A) == '3');

    assert(A == B);
    assert(A == C);
    assert(A == D);
    assert(A == E);
    assert(A == F);
    }
    {
    // Equivalent ways to copy array prefix, i.e. slicing off a suffix.
    // Requires two parameters explicit begin offset 0|-N and end.
    constexpr auto A = subarray<0,-1>(a);
    constexpr auto B = subarray<0,e-1>(a);
    constexpr auto C = subarray<-e,-1>(a);
    constexpr auto D = subarray<-e,e-1>(a);

    static_assert( std::size(A)+1 == e);
    static_assert( sget<0>(A) == '0');
    static_assert( sget<-1>(A) == '2');

    assert(A == B);
    assert(A == C);
    assert(A == D);
    }
    {
    // Array slice requires two parameters: begin and end.
    constexpr auto A = subarray<1,-1>(a);
    constexpr auto B = subarray<1,e-1>(a);
    constexpr auto C = subarray<1-e,-1>(a);
    constexpr auto D = subarray<1-e,e-1>(a);

    static_assert( std::size(A)+2 == e);
    static_assert( sget<0>(A) == '1');
    static_assert( sget<-1>(A) == '2');

    assert(A == B);
    assert(A == C);
    assert(A == D);
    }

}
