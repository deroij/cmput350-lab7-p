#ifndef PACK_H
#define PACK_H

namespace pack_detail {

// Q1
template <typename... Args>
constexpr int packSize = sizeof...(Args);


// Q2
template <int QueryIndex, typename... Args>
struct _packIndexToType;

// Base case
template <typename First, typename... Rest>
struct _packIndexToType<0, First, Rest...> {
    using type = First;
};

// Recursive case
template <int QueryIndex, typename First, typename... Rest> requires (QueryIndex > 0)
struct _packIndexToType<QueryIndex, First, Rest...> : _packIndexToType<QueryIndex - 1, Rest...> {};


// Q3
template <int Accumulated, typename QueryType, typename... Args>
constexpr int _packTypeToIndex;

// Base case
template <int Accumulated, typename QueryType>
constexpr int _packTypeToIndex<Accumulated, QueryType> = -1;

// Recursive case
template <int Accumulated, typename QueryType, typename First, typename... Rest>
constexpr int _packTypeToIndex<Accumulated, QueryType, First, Rest...> = std::is_same_v<QueryType, First> ? Accumulated : _packTypeToIndex<Accumulated + 1, QueryType, Rest...>;




}

template <typename... Args>
struct Pack {
    static constexpr int size = pack_detail::packSize<Ts...>;

    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Ts...>;

    template <typename QueryType>
    static constexpr int index = pack_detail::_packTypeToIndex<0, QueryType, Ts...>;
};

#endif  // PACK_H
