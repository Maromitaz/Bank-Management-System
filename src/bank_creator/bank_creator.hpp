#pragma once
#include <string>
#include <cstdlib>
#include <ctime>
using uint64 = long long;

void string_lower_case(std::string* str);

class bank_creator
{
private:
	std::string card_number;
	std::string ssn;
	std::string name;
	std::string pin;
	std::string exp_date;
	std::string ccv;
	std::string issuing_network;

	uint64 money;

	char generate_number();
	std::string generate_numbers(size_t lenght);
	std::string generate_card(std::string issuing_network);
public:
	void init(std::string name, std::string ssn, std::string issuing_network);
	void load_card(
		std::string card_number,
		std::string ssn,
		std::string name,
		std::string pin,
		std::string exp_date,
		std::string ccv,
		std::string issuing_network,
		uint64 money
	);
	std::string get_ssn();
	std::string get_name();
	std::string get_card_number();
	std::string get_pin();
	std::string get_exp_date();
	std::string get_ccv();
	std::string get_issuing_network();


	uint64 get_balance();
	void deposit_money(uint64 amount);
	void withdraw_money(uint64 amount);
};

