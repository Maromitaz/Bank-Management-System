#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

class Bank
{
private:
	std::string holderName;
	unsigned long long cardNumber;
	unsigned long long money;
public:
	void init();
	void showCardNumber();
	void createAccount();
	void showDetails();
	void deposit(int amount);
	void withdraw(int amount);
	std::string getName();
	unsigned long long getCardNumber();
};

void f_accFound(int i, std::vector<Bank>& v_bankAccounts);
