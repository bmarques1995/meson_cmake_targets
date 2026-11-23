#include "Log.hh"
#include <iostream>
#include "Math.hh"

void MesonExport::Log::Message(const char* msg)
{
	std::cout << msg << "\n";
}

void MesonExport::Log::SampleSymbol()
{
	double val;
	Math::Add(5.0, 3.0, &val);
	std::cout << val << "\n";
}
