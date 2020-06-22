#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <iomanip>

class Member
{
public:
	Member();

	void set(string accountnumber, string pin, double avail, double total); // 設定資料
	bool check(string accountnumber, string pin); // 檢查用戶是否存在

	void ViewMyBalance(); // 查看餘額
	void WithdrawCash(int& bill);  // 提款
	void DepositFunds();  // 存款

private:
	string accountNumber;
	string Pin;
	double availablebalance;
	double totalbalance;
};

#endif // !MEMBER_H

Member::Member()
	:accountNumber(),
	Pin(),
	availablebalance(),
	totalbalance()
{
}

void Member::set(string accountnumber, string pin, double avail, double total)
{
	accountNumber = accountnumber;
	Pin = pin;
	availablebalance = avail;
	totalbalance = total;
}

bool Member::check(string accountnumber, string pin)
{
	return ((accountNumber == accountnumber) && (Pin == pin));
}

void Member::ViewMyBalance()
{
	cout << "\nBalance Information:\n"
		<< " - Available balance: $" << setprecision(2) << fixed << availablebalance << endl
		<< " - Total balance:     $" << totalbalance << endl;

	cout.unsetf(ios::fixed);
}

void Member::WithdrawCash(int& bill)
{
	while (true)
	{
		int choice;

		cout << "\nWithdrawal options:\n"
			<< "1 - $20\n"
			<< "2 - $40\n"
			<< "3 - $60\n"
			<< "4 - $100\n"
			<< "5 - $200\n"
			<< "6 - Cancel transaction\n";
		cout << "\nChoose a withdrawal option (1-6): ";

		cin >> choice;

		switch (choice)
		{
		case 1:

			if (availablebalance >= 20 && bill >= 1)
			{
				availablebalance -= 20;
				totalbalance -= 20;
				bill -= 1;
				cout << "\nPlease take your cash from the cash dispenser.\n";
				return;
			}

			cout << "\nYou don't have too much money.\nOr I don't have enough cash.\nPlease enter again.\n";
			break;

		case 2:

			if (availablebalance >= 40 && bill >= 2)
			{
				availablebalance -= 40;
				totalbalance -= 40;
				bill -= 2;
				cout << "\nPlease take your cash from the cash dispenser.\n";
				return;
			}

			cout << "\nYou don't have too much money.\nOr I don't have enough cash.\nPlease enter again.\n";
			break;

		case 3:

			if (availablebalance >= 60 && bill >= 3)
			{
				availablebalance -= 60;
				totalbalance -= 60;
				bill -= 3;
				cout << "\nPlease take your cash from the cash dispenser.\n";
				return;
			}

			cout << "\nYou don't have too much money.\nOr I don't have enough cash.\nPlease enter again.\n";
			break;

		case 4:

			if (availablebalance >= 100 && bill >= 5)
			{
				availablebalance -= 100;
				totalbalance -= 100;
				bill -= 5;
				cout << "\nPlease take your cash from the cash dispenser.\n";
				return;
			}

			cout << "\nYou don't have too much money.\nOr I don't have enough cash.\nPlease enter again.\n";
			break;

		case 5:

			if (availablebalance >= 200 && bill >= 10)
			{
				availablebalance -= 200;
				totalbalance -= 200;
				bill -= 10;
				cout << "\nPlease take your cash from the cash dispenser.\n";
				return;
			}

			cout << "\nYou don't have too much money.\nOr I don't have enough cash.\nPlease enter again.\n";
			break;

		case 6:

			return;
			break;
		}
	}
}

void Member::DepositFunds()
{
	double cents;

	cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";
	cin >> cents;

	if (cents == 0)
		return;

	double dollars = cents / 100;

	cout << "\nPlease insert a deposit envelope containing $"
		<< setprecision(2) << fixed << dollars
		<< " in the deposit slot.\n"
		<< "\nYour envelope has been received.\n"
		<< "NOTE: The money deposited will not be available until we\n"
		<< "verify the amount of any enclosed cash, and any enclosed checks clear.\n";

	totalbalance += dollars;
	return;
}