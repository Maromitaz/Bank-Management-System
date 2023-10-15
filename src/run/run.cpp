#include "run.hpp"
#include <string>
#include <sstream>

void clear_screen(void) {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void clear_input_buffer(void) {
	while (getchar() != '\n');
}

enum options {
	EXIT,
	CREATE_ACCOUNT,
	CHECK,
	WITHDRAW,
	DEPOSIT,
	LOAD_FROM_FILE,
	SAVE_TO_FILE,
};

void create_account(bank_manager *manager) {
	std::string name = "";
	std::string ssn = "";
	std::string issuer = "";

	std::cout << "Please insert your name: ";
	std::getline(std::cin, name);
	std::cin.clear();
	std::cout << "Please insert your ssn (not the real one): ";
	std::getline(std::cin, ssn);
	std::cin.clear();
	std::cout << "Please insert your issuer of choice (mastercard, visa): ";
	std::getline(std::cin, issuer);
	std::cin.clear();
	std::cout << "Generating..." << std::endl;
	manager->create_account(name, ssn, issuer);
}

void check_balance(bank_manager *manager) {
	std::string card = "";
	std::string pin = "";

	std::cout << "Please insert your card number: ";
	std::getline(std::cin, card);
	std::cin.clear();
	std::cout << "Please insert your card pin: ";
	std::getline(std::cin, pin);
	std::cin.clear();
	manager->check_balance(card, pin);
}

void deposit(bank_manager* manager) {
	std::string card = "";
	std::string pin = "";
	uint64 amount = 0;

	std::cout << "Please insert your card number: ";
	std::getline(std::cin, card);
	std::cin.clear();
	std::cout << "Please insert your card pin: ";
	std::getline(std::cin, pin);
	std::cin.clear();
	std::cout << "Please insert your amount to depozit: ";
	std::cin >> amount;
	std::cin.clear();
	manager->deposit_money(card, pin, amount);
}

void withdraw(bank_manager *manager) {
	std::string card = "";
	std::string pin = "";
	uint64 amount = 0;

	std::cout << "Please insert your card number: ";
	std::getline(std::cin, card);
	std::cin.clear();
	std::cout << "Please insert your card pin: ";
	std::getline(std::cin, pin);
	std::cin.clear();
	std::cout << "Please insert your amount to withdraw: ";
	std::cin >> amount;
	std::cin.clear();
	manager->withdraw_money(card, pin, amount);
}

std::stringstream return_string_to_save(bank_creator bank) {
	std::stringstream card_data_already_stringed;
	card_data_already_stringed << bank.get_card_number() << ' ';
	card_data_already_stringed << bank.get_ssn() << ' ';
	card_data_already_stringed << bank.get_name() << ' ';
	card_data_already_stringed << bank.get_pin() << ' ';
	card_data_already_stringed << bank.get_exp_date() << ' ';
	card_data_already_stringed << bank.get_ccv() << ' ';
	card_data_already_stringed << bank.get_issuing_network() << ' ';
	card_data_already_stringed << bank.get_balance() << '\n';

	return card_data_already_stringed;
}

void write_to_file(std::string str, FILE* data_file) {
	fputs(&(str)[0], data_file);
}

#ifdef _WIN32
// Windows systems
#include <Windows.h>
// Literally getcwd from unistd.h
char* getcwd(char* buf, unsigned long size) {
	GetCurrentDirectoryA(size, buf);
	return buf;
}
#else
// UNIX-like systems
#include <unistd.h>
#define MAX_PATH 260
#endif

void load_from_file(bank_manager* manager) {
	char* file_open = static_cast<char*>(malloc(CHAR_MAX));
#ifdef _WIN32
	char file[] = "\\data.txt";
#else
	char file[] = "/data.txt";
#endif
	if (getcwd(file_open, MAX_PATH)) {
		strcat(file_open, file);
	}
	FILE* data_file = fopen(file_open, "r");
	if (data_file == NULL) {
		std::cout << "An error occured." << std::endl;
		std::cout << "Check if user has any right to write files." << std::endl;
		exit(1);
	}
	free(file_open);

	using str_vector = std::vector<std::string>;

	char* line = static_cast<char*>(malloc(CHAR_MAX));
	while (fgets(line, CHAR_MAX, data_file) != NULL) {
		if (line != "") {
			std::stringstream line_ss(line);
			str_vector data;
			std::string piece_of_data = "";
			while (line_ss >> piece_of_data) {
				data.push_back(piece_of_data);
			}
			std::string card_number = data[0];
			std::string ssn = data[1];
			std::string name = data[2];
			std::string pin = data[3];
			std::string exp_date = data[4];
			std::string ccv = data[5];
			std::string issuing_network = data[6];
			std::string money_str = data[7];
			uint64 money = 0;
			for (uint64 i = money_str.size(); 0 < i; i--) {
				char money_char = money_str.at(i - 1);
				money = money * 10 + (money_char - 48);
			}
			manager->add_account(
				card_number,
				ssn,
				name,
				pin,
				exp_date,
				ccv,
				issuing_network,
				money
			);
		}
		free(line);
		fclose(data_file);
	}
}

void save_to_file(bank_manager* manager) {
	char* file_open = static_cast<char*>(malloc(sizeof(char) + MAX_PATH));
#ifdef _WIN32
	char file[] = "\\data.txt";
#else
	char file[] = "/data.txt";
#endif
	if (getcwd(file_open, MAX_PATH)) {
		strcat(file_open, file);
	}
	FILE* data_file = fopen(file_open, "w");
	free(file_open);
	if (data_file == NULL) {
		printf("%s\n\n\n\n", file_open);
		std::cout << "An error occured." << std::endl;
		std::cout << "Check if user has any right to write files." << std::endl;

		exit(1);
	}
	std::string contents_buffer = { 0 };
	std::vector<bank_creator> visa_cards = manager->get_visa_cards();

	for (bank_creator bank : visa_cards) {
		write_to_file(return_string_to_save(bank).str(), data_file);
	}
	std::vector<bank_creator> master_cards = manager->get_master_cards();

	for (bank_creator bank : master_cards) {
		write_to_file(return_string_to_save(bank).str(), data_file);
	}

	fclose(data_file);
}

void get_input(bank_manager* manager) {
	std::cout << "Please select a number specified on the screen." << std::endl
		<< "1) Create an account;" << std::endl
		<< "2) Check balance;" << std::endl
		<< "3) Withdraw;" << std::endl
		<< "4) Deposit;" << std::endl
		<< "5) Load from file;" << std::endl
		<< "6) Save to file (will override the file);" << std::endl
		<< "0) To exit." << std::endl << std::endl;
	std::cout << "Input: ";

	short choice = 0;
	std::cin >> choice;
	clear_input_buffer();
	switch (choice)
	{
	case CREATE_ACCOUNT:
		clear_screen();
		create_account(manager);
		break;
	case CHECK:
		clear_screen();
		check_balance(manager);
		break;
	case DEPOSIT:
		clear_screen();
		deposit(manager);
		break;
	case WITHDRAW:
		clear_screen();
		withdraw(manager);
		break;
	case LOAD_FROM_FILE:
		clear_screen();
		load_from_file(manager);
		break;
	case SAVE_TO_FILE:
		clear_screen();
		save_to_file(manager);
		break;
	case EXIT:
		clear_screen();
		exit(EXIT_SUCCESS);
		break;
	default:
		clear_screen();
		std::cout << "Sorry, but your input must be 1-6 or 0 if you wish to exit." << std::endl;
		break;
	}
	get_input(manager);
}
