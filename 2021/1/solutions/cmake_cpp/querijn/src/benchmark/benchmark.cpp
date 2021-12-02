#include "common.hpp"
#include <cstdio>

int part_one(const char* file = nullptr);
int part_two(const char* file = nullptr);

#ifdef BENCHMARK
#include "duration.hpp"
#include "debugbreak.h"

#define COUNT 1000
#define BM_ASS(Assertion, a,b,c) do { if (!(Assertion)) { printf(a,b,c); debug_break(); return -1; } } while(0)

int BENCHMARK()
{
	int v1 = part_one();
	int v2 = part_two();
	BM_ASS(v1 >= 0 && v2 >= 0, "Invalid initial input: %d / %d\n", v1, v2);

	f64 total2 = 0;
	f64 total1 = 0;
	for (int i = 0; i < COUNT; i++)
	{
		Spek::Duration start1 = Spek::GetTimeSinceStart();
		int result = part_one();
		BM_ASS(result == v1, "Result of ONE needs to be %d, is %d instead.\n", v1, result);
		Spek::Duration end1 = Spek::GetTimeSinceStart();

		Spek::Duration start2 = Spek::GetTimeSinceStart();
		result = part_two();
		BM_ASS(result == v2, "Result of TWO needs to be %d, is %d instead.\n", v2, result);
		Spek::Duration end2 = Spek::GetTimeSinceStart();

		total1 += (end1 - start1).ToSecF64();
		total2 += (end2 - start2).ToSecF64();
	}

	printf("Total 1: %3.2f ms, result = %d\n", (total1 / (f64)COUNT) * 1000.0, v1);
	printf("Total 2: %3.2f ms, result = %d\n", (total2 / (f64)COUNT) * 1000.0, v2);
}

#else

// These might become main, they should call the original function
int ONE(int argc, char* argv[]) { return part_one(argv[1]); }
int TWO(int argc, char* argv[]) { return part_two(argv[1]); }

int RUNNER(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Missing input!");
		return -1;
	}

	printf("%d\n%d\n", part_one(argv[1]), part_two(argv[1]));

	return 0;
}

#endif