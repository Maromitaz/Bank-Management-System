#include "core.h"
unsigned long long cardGenerator() {
	unsigned long long final_card = 5;
	srand((unsigned)time(NULL));
	for (unsigned short i = 0; i < 11; i++) {
		unsigned short tempRand = rand() % 10;
		final_card = final_card * 10 + tempRand;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return final_card;
}


void Bank::init() {
	std::cout << "Please enter your name: ";
	std::getline(std::cin, holderName);
	cardNumber = cardGenerator();
	money = 0;
}

void Bank::showCardNumber() {
	std::cout << cardNumber << std::endl;
}

void Bank::showDetails() {
	std::cout << "The account's holder name: " << holderName << std::endl;
	std::cout << "The account's balance: $" << money << std::endl;
	std::cout << "Press enter to go back...";
	std::cin.get();
	system("cls");
}

void Bank::deposit(int amount) {
	money = money + amount;
	std::cout << money << std::endl;
	system("cls");
}

void Bank::withdraw(int amount) {
	system("cls");
	if (money < amount)
		std::cout << "Unable to withdraw 'cuz you lackin' brother." << std::endl << std::endl;
	else {
		money = money - amount;
	}
}

std::string Bank::getName() {
	return holderName;
}

unsigned long long Bank::getCardNumber() {
	return cardNumber;
}

void f_accFound(int i, std::vector<Bank>& v_bankAccounts) {
	std::cout << "What would you like to do?" << std::endl
		<< "1. Check your account; " << std::endl
		<< "2. Deposit your money; " << std::endl
		<< "3. Withdraw your money;" << std::endl
		<< "4. Go back." << std::endl;
	std::string accCheckOption;
	std::getline(std::cin, accCheckOption);
	std::cin.clear();
	if (accCheckOption == "1") {
		v_bankAccounts[i].showDetails();
	}
	else if (accCheckOption == "2") {
		std::cout << "Please insert the amount that you wish to deposit: ";
		int amoundDeposit;
		std::cin >> amoundDeposit;
		std::cin.ignore();
		v_bankAccounts[i].deposit(amoundDeposit);
	}
	else if (accCheckOption == "3") {
		std::cout << "Please insert the amount that you wish to withdraw: ";
		int amoundWithdraw;
		std::cin >> amoundWithdraw;
		std::cin.ignore();
		v_bankAccounts[i].withdraw(amoundWithdraw);
	}
	else if (accCheckOption == "4") {
		system("cls");
		return;
	}
	f_accFound(i, v_bankAccounts);
}
