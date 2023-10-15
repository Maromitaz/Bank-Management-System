#pragma once
#include <vector>

#include "./../bank_creator/bank_creator.hpp"

class bank_manager
{
private:
	std::vector<bank_creator> visa;
	std::vector<bank_creator> mastercard;
public:
	void add_account(
		std::string card_number,
		std::string ssn,
		std::string name,
		std::string pin,
		std::string exp_date,
		std::string ccv,
		std::string issuing_network,
		uint64 money
	);
	void create_account(std::string name, std::string ssn, std::string issuer);
	void check_balance(std::string card, std::string pin);
	void deposit_money(std::string card, std::string pin, uint64 amount);
	void withdraw_money(std::string card, std::string pin, uint64 amount);
	std::vector<bank_creator> get_master_cards();
	std::vector<bank_creator> get_visa_cards();
};

