#pragma once

#include <windows.h>

class CpuTimeQuery
{
protected:
	double m_time;
	LARGE_INTEGER startTime, endTime, freqTime;

public:
	void begin()
	{
		QueryPerformanceFrequency(&freqTime);
		QueryPerformanceCounter(&startTime);
	}

	void end()
	{
		QueryPerformanceCounter(&endTime);
		m_time = (double)(endTime.QuadPart - startTime.QuadPart) * 1000.0 / (double)freqTime.QuadPart;
	}

	double timeInMilisec() const { return m_time; }
	double timeInSeconds() const { return m_time*0.001; }
};

