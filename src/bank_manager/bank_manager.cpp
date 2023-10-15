#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "bank_manager.hpp"

void bank_manager::add_account(
		std::string card_number,
		std::string ssn,
		std::string name,
		std::string pin,
		std::string exp_date,
		std::string ccv,
		std::string issuing_network,
		uint64 money
	) {
	bank_creator temp_bank;
	temp_bank.load_card(card_number, ssn, name, pin, exp_date, ccv, issuing_network, money);
	if (temp_bank.get_issuing_network() == "visa") {
		this->visa.insert(visa.end(), temp_bank);
	}
	if (temp_bank.get_issuing_network() == "mastercard") {
		this->mastercard.insert(mastercard.end(), temp_bank);
	}
}
void bank_manager::create_account(std::string name, std::string ssn, std::string issuer) {
	bank_creator temp_bank;
	temp_bank.init(name, ssn, issuer);
	if (temp_bank.get_issuing_network() == "visa") {
		this->visa.insert(visa.end(), temp_bank);
	}
	if (temp_bank.get_issuing_network() == "mastercard") {
		this->mastercard.insert(mastercard.end(), temp_bank);
	}
}


char no_cards[] = "There are no cards available in the system.\n Please create one!";
char no_account[] = "The card that you've introduced is not registered in the system.\n Please try again or create one!";

int access_banking_account(std::string card_number, std::vector<bank_creator> issuer) {
	int ret_val = -1;
	for (size_t i = 0; i < issuer.size(); i++) {
		std::string temp_card_number = issuer[i].get_card_number();
		if (temp_card_number == card_number) {
			ret_val = static_cast<int>(i);
		}
	}
	return ret_val;
}


void bank_manager::check_balance(std::string card, std::string pin) {
	if (this->visa.empty() && this->mastercard.empty()) {
		std::cout << no_cards << std::endl;
		return;
	}

	int ret_card_addr_index = access_banking_account(card, this->mastercard);
	short issuer = 0;

	if (ret_card_addr_index == -1) {
		ret_card_addr_index = access_banking_account(card, this->visa);
		issuer = 1;
	}

	if (ret_card_addr_index > -1) {
		bank_creator* ret_card = reinterpret_cast<bank_creator*>(malloc(sizeof(bank_creator)));
		if (issuer == 0) {
			ret_card = &(this->mastercard.at(ret_card_addr_index));
		}
		else {
			ret_card = &(this->visa.at(ret_card_addr_index));
		}

		if (ret_card->get_pin() == pin) {
			std::cout << "Your balance is: " << ret_card->get_balance() << std::endl;
		}
		else {
			std::cout << "Invalid pin." << std::endl;
		}
		return;
	}

	std::cout << no_account << std::endl;
	return;
}

void bank_manager::deposit_money(std::string card, std::string pin, uint64 amount) {
	if (this->visa.empty() && this->mastercard.empty()) {
		std::cout << no_cards << std::endl;
		return;
	}

	int ret_card_addr_index = access_banking_account(card, this->mastercard);
	short issuer = 0;

	if (ret_card_addr_index == -1) {
		ret_card_addr_index = access_banking_account(card, this->visa);
		issuer = 1;
	}

	if (ret_card_addr_index > -1) {
		bank_creator* ret_card = reinterpret_cast<bank_creator*>(malloc(sizeof(bank_creator)));
		if (issuer == 0) {
			ret_card = &(this->mastercard.at(ret_card_addr_index));
		}
		else {
			ret_card = &(this->visa.at(ret_card_addr_index));
		}

		if (ret_card->get_pin() == pin) {
			ret_card->deposit_money(amount);
			std::cout << "Successfully depozited " << amount << " from your banking account!" << std::endl << std::endl;
		}
		else {
			std::cout << "Invalid pin." << std::endl;
		}
		return;
	}

	std::cout << no_account << std::endl;
	return;
}

void bank_manager::withdraw_money(std::string card, std::string pin, uint64 amount) {
	if (this->visa.empty() && this->mastercard.empty()) {
		std::cout << no_cards << std::endl;
		return;
	}

	int ret_card_addr_index = access_banking_account(card, this->mastercard);

	if (ret_card_addr_index > -1) {
		bank_creator* ret_card = &(this->mastercard.at(ret_card_addr_index));
		if (ret_card->get_pin() == pin) {
			ret_card->withdraw_money(amount);
			std::cout << "Successfully withdrew " << amount << " from your banking account!" << std::endl << std::endl;
		}
		else {
			std::cout << "Invalid pin." << std::endl;
		}
		return;
	}

	ret_card_addr_index = access_banking_account(card, this->visa);

	if (ret_card_addr_index > -1) {
		bank_creator* ret_card = &(this->visa.at(ret_card_addr_index));
		if (ret_card->get_pin() == pin) {
			ret_card->withdraw_money(amount);
			std::cout << "Successfully withdrew " << amount << " from your banking account!" << std::endl << std::endl;
		}
		else {
			std::cout << "Invalid pin." << std::endl;
		}
		return;
	}

	std::cout << no_account << std::endl;
	return;
}

std::vector<bank_creator> bank_manager::get_master_cards() {
	return this->mastercard;
}

std::vector<bank_creator> bank_manager::get_visa_cards() {
	return this->visa;
}
