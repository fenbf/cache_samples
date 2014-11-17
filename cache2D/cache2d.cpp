#include <iostream>
#include "TimeQuery.h"

void test(const int ITERS, const int ARRAY_ROWS, const int ARRAY_COLS, bool RowOrder)
{
	CpuTimeQuery cpuTime;

	const int ARRAY_TOTAL_ELEMENTS = ARRAY_ROWS * ARRAY_COLS;
	const int ARRAY_TOTAL_SIZE = ARRAY_TOTAL_ELEMENTS * sizeof(int);

	int *array = new int[ARRAY_TOTAL_ELEMENTS];
	memset(array, 0, ARRAY_TOTAL_SIZE);

	if (RowOrder)
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

int main(int argc, char *argv[])
{
	const int ARRAY_MIN_SIZE = argc > 1 ? atoi(argv[1]) : 100;
	const int ARRAY_MAX_SIZE = argc > 1 ? atoi(argv[1]) : 1000;
	const int ARRAY_STEP = argc > 2 ? atoi(argv[2]) : 100;
	const int ITERS = 1000;

	std::cout << "\t";
	for (int cols = ARRAY_MIN_SIZE; cols <= ARRAY_MAX_SIZE; cols += ARRAY_STEP)
		std::cout << cols << "\t";
	std::cout << std::endl;

	for (int rows = ARRAY_MIN_SIZE; rows <= ARRAY_MAX_SIZE; rows += ARRAY_STEP)
	{
		std::cout << rows << "\t";
		for (int cols = ARRAY_MIN_SIZE; cols <= ARRAY_MAX_SIZE; cols += ARRAY_STEP)
		{
			test(ITERS, rows, cols, false);
		}
		std::cout << std::endl;
	}	
}
