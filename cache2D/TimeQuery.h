#pragma once

#include <chrono>

class CpuTimeQuery
{
protected:
	double m_time;

protected:
	std::chrono::time_point<std::chrono::system_clock> m_cpuTimePointStart;

public:
	void begin()
	{
		m_cpuTimePointStart = std::chrono::system_clock::now();
	}

	void end()
	{
		auto diff = std::chrono::system_clock::now() - m_cpuTimePointStart;
		auto mili = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
		m_time = static_cast<double>(mili);
	}

	double timeInMilisec() const { return m_time; }
	double timeInSeconds() const { return m_time*0.001; }
};

