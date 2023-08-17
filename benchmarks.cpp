#include "benchmark/benchmark.h"
#include "FizzBuzzImpl/Templated.h"
#include "FizzBuzzImpl/Comptime.h"

using namespace std;

template <Templated::algorithm Algo, Templated::int2sv... Functions>
static void templated_test(benchmark::State& state) {
	using namespace Templated;
	const fizzbuzz<Algo> fb{};
	for (auto _ : state) {
		for (int i = 0; i <= 1024; ++i) {
			const auto out = fb.apply<int2sv, Functions...>(i);
			benchmark::DoNotOptimize(out);
		}
	}
}
BENCHMARK(templated_test<Templated::algorithm::procedural>);
BENCHMARK(templated_test<Templated::algorithm::procedural, Templated::fizz, Templated::buzz>);
BENCHMARK(templated_test<Templated::algorithm::functional>);
BENCHMARK(templated_test<Templated::algorithm::functional, Templated::fizz, Templated::buzz>);
BENCHMARK(templated_test<Templated::algorithm::fold, Templated::fizz, Templated::buzz>);


static void comptime_static_tostring__test(benchmark::State& state) {
	using namespace Comptime;
	for (auto _ : state) {
		constexpr auto results = result::make_range<0, 1024>();
		for (int i = 0; i < results.size(); ++i) {
			auto sv = results[i].to_string();
			benchmark::DoNotOptimize(sv);
		}
	}
}
BENCHMARK(comptime_static_tostring__test);


BENCHMARK_MAIN();
