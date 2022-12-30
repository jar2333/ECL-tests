#ifndef FUNCTION_TRAITS_HPP
#define FUNCTION_TRAITS_HPP

#include <tuple>

// Credit: Barry (@brevzin on GitHub)
// https://stackoverflow.com/a/62644127

template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())>
{};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
    using result_type = ReturnType;
    using arg_tuple = std::tuple<Args...>;
    static constexpr auto arity = sizeof...(Args);
};

template <class F, std::size_t ... Is, class T>
auto lambda_to_func_ptr_impl(F f, std::index_sequence<Is...>, T) {
    return static_cast<typename T::result_type(*)(std::tuple_element_t<Is, typename T::arg_tuple>...)>(f);
}

template <class F>
auto lambda_to_func_ptr(F f) {
    using traits = function_traits<F>;
    return lambda_to_func_ptr_impl(f, std::make_index_sequence<traits::arity>{}, traits{});
}

#endif //FUNCTION_TRAITS_HPP