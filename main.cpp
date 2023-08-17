#include "FizzBuzzImpl/Comptime.h"
#include "FizzBuzzImpl/Templated.h"
#include <print>

inline constinit Templated::unused_t tester = std::invoke([]() {
	using Comptime::test;
	using Comptime::test_fail;

	test<1, false, false>();
	test<3, true, false>();
	test<5, false, true>();
	test<15, true, true>();
	test_fail<2, true, false>();

	return Templated::unused_t{};
});


struct scope_printer {
	explicit scope_printer(std::string_view view) {
		std::println("{}", view);
	}
	~scope_printer() {
		std::println("");
	}
};


int main() {
	{
		scope_printer p{ "Templated tryout" };
		using Templated::algorithm;
		Templated::fizzbuzz<algorithm::functional> fb;
		for (int i{ 0 }; i < 16; ++i) {
			auto out = fb.apply<Templated::unused_t>(i);
			std::println("{}", out.empty() ? std::to_string(i) : out);
		}
	}

	{
		scope_printer p{ "Comptime tryout" };
		using namespace Comptime;
		constexpr auto results = result::make_range<0, 16>();
		for (int i{ 0 }; i < 16; ++i) {
			auto out = results[i].to_string();
			std::println("{}", out.empty() ? std::to_string(i) : out);
		}
	}
}
