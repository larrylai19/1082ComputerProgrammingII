// Deposit.h
// Deposit class definition. Represents a deposit transaction.
#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Deposit
{
public:
   Deposit( int userAccountNumber, vector< Account > &atmAccounts );
   void execute(); // perform the deposit transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   double amount; // amount to deposit

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts ); 
   double promptForDepositAmount() const; // prompt user to enter a deposit amount in cents 
}; // end class Deposit

Deposit::Deposit(int userAccountNumber, vector< Account >& atmAccounts)
    :accountNumber(userAccountNumber),
    accounts(atmAccounts),
    amount()
{
}

void Deposit::execute()
{
    if ((amount = promptForDepositAmount()) == 0)
        return;

    auto user = getAccount(accountNumber, accounts);

    cout << "\nPlease insert a deposit envelope containing $"
        << setprecision(2) << fixed << amount
        << " in the deposit slot.\n"
        << "\nYour envelope has been received.\n"
        << "NOTE: The money deposited will not be available until we\n"
        << "verify the amount of any enclosed cash, and any enclosed checks clear.\n";

    cout.unsetf(ios::fixed);

    user->credit(amount);
}

Account* Deposit::getAccount(int accountNumber, vector< Account >& accounts)
{
    for (size_t i = 0; i < accounts.size(); ++i)
        if (accountNumber == accounts[i].getAccountNumber())
            return &accounts[i];

    return NULL;
}

double Deposit::promptForDepositAmount() const
{
    double cents;

    cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";
    cin >> cents;

    if (cents == 0)
        return 0;

    return (cents / 100);
}

#endif // DEPOSIT_H