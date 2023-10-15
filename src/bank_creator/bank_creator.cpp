#include <thread>
#include <chrono>
#include <iostream>

#include "bank_creator.hpp"

using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::chrono::duration_cast;

void bank_creator::init(std::string name, std::string ssn, std::string issuing_network) {
	this->ssn = ssn;
	this->name = name;
	this->card_number = generate_card(issuing_network);
	this->pin = generate_numbers(4);
	this->ccv = generate_numbers(3);

	char month[3]{ (generate_number() - 48) % 2 + 48 };
	if (month[0] == 1) {
		month[1] = (generate_number() - 48) % 3 + 48;
	}
	else {
		month[1] = generate_number();
	}
	this->exp_date += month[0];
	this->exp_date += month[1];
	this->exp_date += "/";
	this->exp_date += '2';
	this->exp_date += (generate_number() - 48) % 3 + 4 + 48;

	string_lower_case(&issuing_network);

	this->issuing_network = issuing_network;

	this->money = 0;

	std::cout << "Account created successfully." << std::endl
		<< "Card number: " << this->card_number << std::endl
		<< "PIN: " << this->pin << std::endl
		<< "Expiry date: " << this->exp_date << std::endl
		<< "CCV " << this->ccv << std::endl;
}
void bank_creator::load_card(
		std::string card_number,
		std::string ssn, 
		std::string name, 
		std::string pin, 
		std::string exp_date, 
		std::string ccv, 
		std::string issuing_network, 
		uint64 money
	) {
	this->ssn = ssn;
	this->name = name;
	this->card_number = card_number;
	this->pin = pin;
	this->ccv = ccv;
	this->exp_date = exp_date;
	this->issuing_network = issuing_network;
	this->money = money;
}

char bank_creator::generate_number() {
	int current_ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	return (char)(current_ms % 10 + 48); // adding 48 because in ascii 48 decimal is 0
	// There's a link below for additional information referring to ascii
	// https://upload.wikimedia.org/wikipedia/commons/1/1b/ASCII-Table-wide.svg
}

std::string bank_creator::generate_numbers(size_t lenght = 1) {
	std::string get_number = "";

	for (size_t i = 0; i < lenght; i++) {
		get_number += generate_number();
		int wait_time = get_number.at(i) - (get_number.at(i) / 3);
		if (wait_time % 2 != 0) {
			if(wait_time % 3 == 0)
				wait_time = (wait_time / 2 + 1) + (wait_time / (wait_time / 3));
			else
				wait_time = (wait_time / 2 + 1) + (wait_time / (wait_time % 3));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
	}
	return get_number;
}
void string_lower_case(std::string *str){
	for (char c : *str) {
		c = tolower(c);
	}
}

// Getting the sum of the numbers is essential to prove that the card is a valid one.
// If the card is divisible by 10 (number % 10) then it is a valid card.
int ret_sum(std::string ret_card) {
	int sum = 0;
	int multiplier = 1;
	for (char nr : ret_card) {
		if (multiplier % 2 == 0) {
			multiplier--;
		}
		else {
			multiplier++;
		}
		int new_number = (nr - 48) * multiplier;
		if (new_number > 9)
			new_number = (new_number % 10) + (new_number / 10);
		sum += new_number;
	}
	return sum;
}

std::string bank_creator::generate_card(std::string issuing_network) {
	// This will be of use if you wonder if what I've said in the comments is real or not.
	// https://en.wikipedia.org/wiki/Payment_card_number
	string_lower_case(&issuing_network);
	std::string ret_card = "";

	if (issuing_network == "visa") {
		// Starting with 4 as a visa card always starts with 4.
		ret_card += '4';
		// A visa card has the number lenght 13, 16 or 19.
		int visa_lenght = generate_number() % 4;
		if (visa_lenght == 1) {
			ret_card += generate_numbers(12);
		}
		else if (visa_lenght == 2) {
			ret_card += generate_numbers(15);
		}
		else {
			ret_card += generate_numbers(18);
		}
	}
	else if (issuing_network == "mastercard") {
		// Mastercard has it's card number starting from 51 to 55 or 2221-2750.
		ret_card += '5';
		int second_number = generate_number() % 5 + 1;
		ret_card += (char)second_number + 48; // ret_card can be 51, 52, 53, 54, 55
		ret_card += generate_numbers(14);
	}
	else {
		std::cerr << "Generator supports only \"visa\" and \"mastercard\" as an issuer network" << std::endl;
		exit(EXIT_FAILURE);
	}
	int multiplier;
	int sum = ret_sum(ret_card);
	int card_lenght = ret_card.length();

	if (card_lenght % 2 == 0)
		multiplier = 2;
	else
		multiplier = 1;

	for (int i = 1; i < card_lenght - 1; i++) {
		if (sum % 10 == 0)
			break;

		if (multiplier % 2 == 0) {
			multiplier--;
		}
		else {
			multiplier++;
		}

		int char_val = ret_card.at(card_lenght - i) - 48;
		short change = 10 - (sum % 10);

		if (char_val + change > 9) {
			ret_card.at(card_lenght - i) = '9';
		}
		else {
			ret_card.at(card_lenght - i) += change;
		}

		sum = ret_sum(ret_card);
	}
	return ret_card;

}

std::string bank_creator::get_ssn() {
	return this->ssn;
}

std::string bank_creator::get_name() {
	return this->name;
}

std::string bank_creator::get_card_number() {
	return this->card_number;
}

std::string bank_creator::get_pin() {
	return this->pin;
}

std::string bank_creator::get_exp_date() {
	return this->exp_date;
}

std::string bank_creator::get_ccv()
{
	return this->ccv;
}

std::string bank_creator::get_issuing_network() {
	return this->issuing_network;
}

uint64 bank_creator::get_balance() {
	return this->money;
}

void bank_creator::deposit_money(uint64 amount) {
	this->money += amount;
}

void bank_creator::withdraw_money(uint64 amount) {
	this->money -= amount;
}
