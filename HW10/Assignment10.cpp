#include <iostream>
#include <string>
using namespace std;
#include "Member.h"
#include <vector>

int main()
{
	vector< Member > mem(2);
	int user, bills = 500;

	mem[0].set("12345", "54321", 1000.0, 1200.0);
	mem[1].set("98765", "56789", 200.0, 200.0);

	cout << "Welcome!\n";
	while (true)
	{
		string account, pin;

		cout << "\nPlease enter your account number: ";
		cin >> account;

		cout << "\nEnter your pin: ";
		cin >> pin;

		bool check = false;

		for (unsigned int i = 0; i < mem.size(); ++i)
			if (mem[i].check(account, pin))
			{
				check = true;
				user = i;
				break;
			}

		if (check)
		{
			while (true)
			{
				int choice;

				cout << "\nMain menu:\n";
				cout << "1 - View my balance\n";
				cout << "2 - Withdraw cash\n";
				cout << "3 - Deposit funds\n";
				cout << "4 - Exit\n\nEnter a choice: ";

				cin >> choice;

				if (choice == 4)
				{
					cout << "\nExiting the system...\n\nThank you! Goodbye!\n";
					break;
				}

				switch (choice)
				{
				case 1:

					mem[user].ViewMyBalance();
					break;

				case 2:

					mem[user].WithdrawCash(bills);
					break;

				case 3:

					mem[user].DepositFunds();
					break;
				}
			}
		}
		else
			cout << "\naccount Number or pin is wrong!\n";
	}
}