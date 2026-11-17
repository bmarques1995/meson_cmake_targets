#include "Math.hh"
#include <iostream>

int main(int argc, char** argv)
{
	double result;
	MesonExport::Math::Multiply(5.0, 3.0, &result);

	std::cout << "Result: " << result << "\n";
	return 0;
}