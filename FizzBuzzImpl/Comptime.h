#pragma once

#include <bitset>
#include <array>
#include <string>
#include <string_view>

namespace Comptime {

	constexpr auto should_fizz = [](int i) {return i % 3 == 0; };
	constexpr auto should_buzz = [](int i) {return i % 5 == 0; };

	struct feedback {
		char letters[5];
	};
	constexpr feedback fizz{ "Fizz" };
	constexpr feedback buzz{ "Buzz" };

	struct result {
		std::bitset<2> data{};

		constexpr explicit result() {}
		constexpr explicit result(int _i) :
			data(static_cast<unsigned long long>((should_buzz(_i) << 1) + should_fizz(_i)))
		{}

		constexpr auto fizz() const noexcept -> bool { return data[0]; }
		constexpr auto buzz() const noexcept -> bool { return data[1]; }

		constexpr auto to_string() const noexcept -> std::string {
			if (fizz() && buzz()) return "FizzBuzz";
			else if (fizz()) return "Fizz";
			else if (buzz()) return "Buzz";
			else return "";
		}


		template<feedback ... Feedbacks>
		auto to_string() const noexcept -> std::string {
			std::string out;
			size_t ptr{ 0 };
			for (auto f : { Feedbacks... })
				if (data[ptr++]) out += f.letters;
			return out;
		}

	};

	template<int start, unsigned int count>
	constexpr auto make_results() noexcept {
		std::array<result, count> results;

		for (int i{ start }; i < count; ++i)
			results[i] = result(i);

		return results;
	}

	template<int i, bool ExpectedFizz, bool ExpectedBuzz>
	consteval auto test() noexcept {
		constexpr result r(i);
		static_assert(r.fizz() == ExpectedFizz && r.buzz() == ExpectedBuzz);
	}

	template<int i, bool UnexpectedFizz, bool UnexpectedBuzz>
	consteval auto test_fail() noexcept {
		constexpr result r(i);
		static_assert(!(r.fizz() == UnexpectedFizz && r.buzz() == UnexpectedBuzz));
	}
}