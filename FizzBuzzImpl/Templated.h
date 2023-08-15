#pragma once

#include <array>
#include <string>
#include <string_view>

namespace Templated {

	enum class algorithm {
		procedural,
		functional,
		fold,
	};


	struct unused_t {};


	using int2sv = std::string_view (*)(int);
	constexpr auto fizz = [](int i) -> std::string_view {
		return i % 3 == 0 ? "Fizz" : "";
	};
	constexpr auto buzz = [](int i) -> std::string_view {
		return i % 5 == 0 ? "Buzz" : "";
	};
	constinit std::array<int2sv, 2> functions{ fizz, buzz };


	template <algorithm Algo>
	struct fizzbuzz {
		template <typename Callable, Callable... callables>
		auto apply(int i) const noexcept -> std::string;
	};


	template <>
	template <typename Callable, Callable... callables>
	auto fizzbuzz<algorithm::procedural>::apply(int i) const noexcept -> std::string {
		auto should_fizz = i % 3 == 0;
		auto should_buzz = i % 5 == 0;
		if (should_fizz && should_buzz)
			return "FizzBuzz";
		else if (should_fizz)
			return "Fizz";
		else if (should_buzz)
			return "Buzz";
		else
			return "";
	}


	template <>
	template <typename Callable, Callable...>
	auto fizzbuzz<algorithm::functional>::apply(int i) const noexcept -> std::string {
		std::string out;
		for (auto f : functions)
			out += f(i);
		return out;
	}

	template <>
	template <typename Callable, Callable... callables>
	auto fizzbuzz<algorithm::fold>::apply(int i) const noexcept -> std::string {
		std::string out;
		for (auto c : { callables... })
			out += c(i);
		return out;
	}

}
