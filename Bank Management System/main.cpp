#include "core/core.h"

int main() {
	std::vector<Bank> bankAccounts;
	bool programRun = true;
	while (programRun)
	{
		std::cout << "Choose an option from the ones below (write the number)" << std::endl
			<< "1. Create an account;" << std::endl 
			<< "2. Access an account;" << std::endl
			<< "3. Exit the program."  << std::endl
			<< "Input: ";
		std::string option = "0";
		std::getline(std::cin, option);
		std::cin.clear();
		if (option == "1")
		{
			Bank tempBankAccount;
			tempBankAccount.init();
			bankAccounts.push_back(tempBankAccount);
			system("cls");
			std::cout << "Account created!" << std::endl;
			tempBankAccount.showCardNumber(); std::cout << std::endl;
		}
		else if (option == "2") {
			std::cout << "Which account should that be?" << std::endl
				<< "Card number: ";
			unsigned long long tempCardNumber;
			std::cin >> tempCardNumber;
			std::cin.ignore();
			bool b_accFound = false;
			int i_accFound = 0;
			Bank bankAccount;
			for (int i=0; i < bankAccounts.size(); i++) {
				bankAccount = bankAccounts[i];
				if (bankAccount.getCardNumber() == tempCardNumber) {
					b_accFound = true;
					i_accFound = i;
				}
			}
			if (b_accFound) {
				//Bank* caca = reinterpret_cast<Bank*>(bankAccounts);
				f_accFound(i_accFound, bankAccounts);
			}
		}
		else if (option == "3")
			programRun = false;
	} 
	return 0;
}
