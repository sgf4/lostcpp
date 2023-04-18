#pragma once
#include "Integers.hpp"
#include <tuple>

template<auto v>
struct IntegralConstant {
    static constexpr decltype(v) value = v;
};

struct FalseType : IntegralConstant<false> {};
struct TrueType : IntegralConstant<true> {};

template<typename T>
struct TypeIdentity {
    using type = T;
};

// Remove reference
template<typename T>
struct RemoveReferenceImpl {
    using type = T;
};

template<typename T>
struct RemoveReferenceImpl<T&> {
    using type = T;
};

template<typename T>
struct RemoveReferenceImpl<T&&> {
    using type = T;
};

template<typename T>
using RemoveReference = typename RemoveReferenceImpl<T>::type;

// Is same
template<typename T1, typename T2>
struct IsSameImpl : FalseType {};

template<typename T1>
struct IsSameImpl<T1, T1> : TrueType {};

template<typename T1, typename T2>
concept IsSame = IsSameImpl<T1, T2>::value;

// Is in
template<typename T1, typename... Ts>
struct IsInImpl : FalseType {};

template<typename T1, typename T2, typename... Ts>
struct IsInImpl<T1, T2, Ts...> : IsInImpl<T1, Ts...> {};

template<typename T1, typename... Ts>
struct IsInImpl<T1, T1, Ts...> : TrueType {};

template<typename T, typename... Ts>
concept IsIn = IsInImpl<T, Ts...>::value;

// Is tuple
template<typename T>
struct IsTupleImpl : FalseType {};

template<typename... Ts>
struct IsTupleImpl<std::tuple<Ts...>> : TrueType {};

template<typename T>
struct IsTupleImpl<const T> : IsTupleImpl<T> {};

template<typename T>
concept IsTuple = IsTupleImpl<T>::value;

// TupleElement
template<u32 I, typename T>
struct TupleElementImpl {};

template<u32 I, typename T, typename... Ts>
requires (I == 0)
struct TupleElementImpl<I, std::tuple<T, Ts...>> : TypeIdentity<T> {};

template<u32 I, typename T, typename... Ts>
struct TupleElementImpl<I, std::tuple<T, Ts...>> : TupleElementImpl<I-1, std::tuple<Ts...>> {};

template<u32 I, typename T>
using TupleElement = typename TupleElementImpl<I, T>::type;

// TupleSize
template<typename T>
struct TupleSizeImpl {};

template<typename... Ts>
struct TupleSizeImpl<std::tuple<Ts...>> : IntegralConstant<sizeof...(Ts)> {};

template<typename T>
constexpr u32 TupleSize = TupleSizeImpl<T>::value;

// TuepleElement no error
template<u32 I, typename T>
struct TupleElementNoerrorImpl : TypeIdentity<void> {};

template<u32 I, typename T, typename... Ts>
requires (I == 0)
struct TupleElementNoerrorImpl<I, std::tuple<T, Ts...>> : TypeIdentity<T> {};

template<u32 I, typename T, typename... Ts>
struct TupleElementNoerrorImpl<I, std::tuple<T, Ts...>> : TupleElementNoerrorImpl<I-1, std::tuple<Ts...>> {};

template<u32 I, typename T>
using TupleElementNoerror = typename TupleElementNoerrorImpl<I, T>::type;


// TupleReverse
template<typename T1, typename T2>
struct TupleReverseImpl : TypeIdentity<T2> {};

template<typename T, typename... Ts1, typename... Ts2>
struct TupleReverseImpl<std::tuple<T, Ts1...>, std::tuple<Ts2...>> : TupleReverseImpl<std::tuple<Ts1...>, std::tuple<T, Ts2...>> {};

template<typename T>
using TupleReverse = typename TupleReverseImpl<T, std::tuple<>>::type;

// Tuple forward
template<typename T, template<typename...> typename Tmpl>
struct TupleForwardImpl {};

template<typename... Ts, template<typename...> typename Tmpl>
struct TupleForwardImpl<std::tuple<Ts...>, Tmpl> : TypeIdentity<Tmpl<Ts...>> {};

template<typename T, template<typename...> typename Tmpl>
using TupleForward = typename TupleForwardImpl<T, Tmpl>::type;

// Tuple forward function
template<typename T>
constexpr decltype(auto) TupleForwardFn(auto fn) {
    return [&] <typename... Ts> (TypeIdentity<std::tuple<Ts...>>) constexpr {
        fn.template operator()<Ts...>();
    }(TypeIdentity<T>{});
}

template<typename T, typename Tupl, u32 I=0>
struct TupleGetIndexImpl {};

template<typename T, typename... Ts, u32 I>
struct TupleGetIndexImpl<T, std::tuple<T, Ts...>, I> : IntegralConstant<I> {};

template<typename T, typename T1, typename... Ts, u32 I>
struct TupleGetIndexImpl<T, std::tuple<T1, Ts...>, I> : TupleGetIndexImpl<T, std::tuple<Ts...>, I+1> {};

template<typename T, typename Tupl>
constexpr u32 TupleGetIndex = TupleGetIndexImpl<T, Tupl>::value;

// TupleOffset
template<typename T, typename Tupl>
constexpr u64 tupleOffset() {
    Tupl* tuple {};
    return (u64) &tuple->template get<T>();
}

template<u32 n, typename Tupl>
constexpr u64 tupleOffset() {
    Tupl* tuple {};
    return (u64) &tuple->template get<n>();
}

// Tuple offset
/*
template<typename T, typename Tupl>
constexpr u32 tupleOffset() {
    Tupl* tuple {};
    return (u32) &std::get<T>(*tuple);
}
template<std::size_t n, typename Tupl>
constexpr std::size_t tupleOffset() {
    Tupl* tuple {};
    return (std::size_t) &std::get<n>(*tuple);
}
*/

// Unpack tuples from tuple 
template<typename T, typename Result = std::tuple<>>
struct UnpackTuplesImpl : TypeIdentity<Result> {};

template<typename T, typename... Ts1, typename... Ts2>
struct UnpackTuplesImpl<std::tuple<std::tuple<Ts1...>, Ts2...>, T> : UnpackTuplesImpl<std::tuple<Ts1..., Ts2...>, T> {};

template<IsTuple T, typename... Ts1, typename... Ts2>
struct UnpackTuplesImpl<std::tuple<T, Ts1...>, std::tuple<Ts2...>> : UnpackTuplesImpl<std::tuple<Ts1...>, std::tuple<Ts2..., T>> {};

template<typename T>
using UnpackTuples = typename UnpackTuplesImpl<T>::type;

// Is From Template
template<typename T, template<typename...> typename Tmpl>
struct IsFromTemplateImpl : FalseType {};

template<typename... Ts, template<typename...> typename Tmpl>
struct IsFromTemplateImpl<Tmpl<Ts...>, Tmpl> : TrueType {};

template<typename T, template<typename...> typename Tmpl>
concept IsFromTemplate = IsFromTemplateImpl<T, Tmpl>::value;

// Type switcher
template<typename T1, typename T2>
struct Case {
    using type_case = T1;
    using type_eq = T2;
};

// Conditional
template<bool cond, typename T1, typename T2>
struct ConditionalImpl : TypeIdentity<T2> {};

template<bool cond, typename T1, typename T2>
requires (cond)
struct ConditionalImpl<cond, T1, T2> : TypeIdentity<T1> {};

template<bool cond, typename T1, typename T2>
using Conditional = typename ConditionalImpl<cond, T1, T2>::type;

// Type switcher
template<typename T, typename... Cs>
struct TypeSwitchImpl {};

template<typename T, typename C, typename... Cs>
struct TypeSwitchImpl<T, C, Cs...> : 
    Conditional<IsSame<T, typename C::type_case>, 
        TypeIdentity<typename C::type_eq>, 
        TypeSwitchImpl<T, Cs...>
    > {};

template<typename T, IsFromTemplate<Case>... Cs>
using TypeSwitch = typename TypeSwitchImpl<T, Cs...>::type;

// Overload
template<typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// validexpr
#define VALIDEXPR(...) overloaded { \
        [] <typename = void> requires requires() { \
            __VA_ARGS__; \
        } () consteval { \
            return true; \
        }, \
        [] <typename = void> () consteval { \
            return false; \
        } \
    }() 
