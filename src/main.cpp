#include "run/run.hpp"

int main(int argv, char* argc[]) {
	std::cout << "Welcome to Maromitaz's cool banking management system!" << std::endl << std::endl;

	bank_manager manager;
	get_input(&manager);

	return 0;
}
