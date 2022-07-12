#include <iostream>

#include "shared/foo.hh"

int main() {
	std::cout << "Hello " << example::foo() << "\n";
	return 0;
}
