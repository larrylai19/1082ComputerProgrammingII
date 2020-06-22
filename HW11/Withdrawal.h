// Withdrawal.h
// Withdrawal class definition. Represents a withdrawal transaction.
#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Withdrawal
{
public:
   Withdrawal( int userAccountNumber, vector< Account > &atmAccounts, int &atmRemainingBills );
   void execute(); // perform the withdrawal transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   int amount; // amount to withdraw
   int &remainingBills; // number of $20 bills remaining 

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts );

   // display a menu of withdrawal amounts and the option to cancel;
   // return the chosen amount or 0 if the user chooses to cancel
   int displayMenuOfAmounts() const;
}; // end class Withdrawal

Withdrawal::Withdrawal(int userAccountNumber, vector< Account >& atmAccounts, int& atmRemainingBills)
    :accountNumber(userAccountNumber),
    accounts(atmAccounts),
    amount(),
    remainingBills(atmRemainingBills)
{
}

void Withdrawal::execute()
{
    cout << "\nWithdrawal options:\n"
        << "1 - $20\n"
        << "2 - $40\n"
        << "3 - $60\n"
        << "4 - $100\n"
        << "5 - $200\n"
        << "6 - Cancel transaction\n";

    amount = displayMenuOfAmounts();

    auto user = getAccount(accountNumber, accounts);

    while ((amount > user->getAvailableBalance()) || ((amount / 20) > remainingBills))
    {
        if (amount > user->getAvailableBalance())
        {
            cout << "\nThere are not enough money in your account to withdrawal.\nPlease enter again.\n";
            amount = displayMenuOfAmounts();
        }
        else
        {
            cout << "\nThere are not enough money to withdrawal.\nPlease enter again.\n";
            amount = displayMenuOfAmounts();
        }
    }

    if (amount == 0)
        return;

    user->debit(amount);

    cout << "\nPlease take your cash from the cash dispenser.\n";
}

Account* Withdrawal::getAccount(int accountNumber, vector< Account >& accounts)
{
    for (size_t i = 0; i < accounts.size(); ++i)
        if (accountNumber == accounts[i].getAccountNumber())
            return &accounts[i];

    return NULL;
}

int Withdrawal::displayMenuOfAmounts() const
{
    cout << "\nChoose a withdrawal option (1-6): ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        return 20;
        break;

    case 2:
        return 40;
        break;  

    case 3:
        return 60;
        break;

    case 4:
        return 100;
        break;

    case 5:
        return 200;
        break;

    case 6:
        return 0;
        break;

    default:
        cout << "\nChoose a withdrawal option (1-6): ";
        cin >> choice;
        break;

    }
}

#endif // WITHDRAWAL_H