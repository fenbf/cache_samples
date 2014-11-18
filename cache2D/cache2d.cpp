#include <iostream>
#include "TimeQuery.h"

void test(const int ITERS, const int ARRAY_ROWS, const int ARRAY_COLS, bool rowOrder)
{
	CpuTimeQuery cpuTime;

	const int ARRAY_TOTAL_ELEMENTS = ARRAY_ROWS * ARRAY_COLS;
	const int ARRAY_TOTAL_SIZE = ARRAY_TOTAL_ELEMENTS * sizeof(int);

	int *array = new int[ARRAY_TOTAL_ELEMENTS];
	memset(array, 0, ARRAY_TOTAL_SIZE);

	if (rowOrder)
	{
		cpuTime.begin();
		for (int iter = 0; iter < ITERS; ++iter)
		{
			for (int i = 0; i < ARRAY_ROWS; ++i)
			{
				for (int j = 0; j < ARRAY_COLS; ++j)
					array[i*ARRAY_COLS + j] = 10;
			}
		}
		cpuTime.end();
		std::cout << cpuTime.timeInMilisec() << "\t";
	}	
	else
	{
		cpuTime.begin();
		for (int iter = 0; iter < ITERS; ++iter)
		{
			for (int j = 0; j < ARRAY_COLS; ++j)
			{
				for (int i = 0; i < ARRAY_ROWS; ++i)
					array[i*ARRAY_COLS + j] = 10;
			}
		}
		cpuTime.end();
		std::cout << cpuTime.timeInMilisec() << "\t";
	}

	delete[] array;
	array = nullptr;
}

void runTest(const int ARRAY_MIN_SIZE, const int ARRAY_MAX_SIZE, const int ARRAY_STEP, const int ITERS, bool rowOrder)
{
	std::cout << (rowOrder ? "row order" : "column order") << std::endl;

	std::cout << "\t";
	for (int cols = ARRAY_MIN_SIZE; cols <= ARRAY_MAX_SIZE; cols += ARRAY_STEP)
		std::cout << cols << "\t";
	std::cout << std::endl;

	for (int rows = ARRAY_MIN_SIZE; rows <= ARRAY_MAX_SIZE; rows += ARRAY_STEP)
	{
		std::cout << rows << "\t";
		for (int cols = ARRAY_MIN_SIZE; cols <= ARRAY_MAX_SIZE; cols += ARRAY_STEP)
		{
			test(ITERS, rows, cols, rowOrder);
		}
		std::cout << std::endl;
	}
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::cout << "using default params!" << std::endl;
		std::cout << "min_size, max_size, step" << std::endl << std::endl;
	}

	const int ARRAY_MIN_SIZE = argc > 1 ? atoi(argv[1]) : 100;
	const int ARRAY_MAX_SIZE = argc > 1 ? atoi(argv[2]) : 1000;
	const int ARRAY_STEP = argc > 2 ? atoi(argv[3]) : 100;
	const int ITERS = 1000;

	std::cout << "min size: " << ARRAY_MIN_SIZE << ", max size: " << ARRAY_MAX_SIZE << ", step: " << std::endl;
	std::cout << "max array size: " << ARRAY_MAX_SIZE*ARRAY_MAX_SIZE*sizeof(int) << " bytes" << std::endl;

	runTest(ARRAY_MIN_SIZE, ARRAY_MAX_SIZE, ARRAY_STEP, ITERS, true);
	runTest(ARRAY_MIN_SIZE, ARRAY_MAX_SIZE, ARRAY_STEP, ITERS, false);

	return 0;
}


