#include "test_app.hpp"

//std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
#if PRODUCTION_BUILD == 0
	std::cout << "Dev build...\n";
#endif
	TestApp app{};

	try
	{
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}