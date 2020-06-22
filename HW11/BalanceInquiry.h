// BalanceInquiry.h
// BalanceInquiry class definition. Represents a balance inquiry.
#ifndef BALANCE_INQUIRY_H
#define BALANCE_INQUIRY_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class BalanceInquiry
{
public:
   BalanceInquiry( int userAccountNumber, vector< Account > &atmAccounts ); // constructor
   void execute(); // perform the balance inquiry transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts ); 
}; // end class BalanceInquiry

BalanceInquiry::BalanceInquiry(int userAccountNumber, vector< Account >& atmAccounts)
    :accountNumber(userAccountNumber),
    accounts(atmAccounts)
{
}

void BalanceInquiry::execute()
{
    auto user = getAccount(accountNumber, accounts);
    
    cout << "\nBalance Information:\n"
        << " - Available balance: $" << setprecision(2) << fixed << user->getAvailableBalance() << endl
        << " - Total balance:     $" << user->getTotalBalance() << endl;

    cout.unsetf(ios::fixed);
}

Account* BalanceInquiry::getAccount(int accountNumber, vector< Account >& accounts)
{
    for (size_t i = 0; i < accounts.size(); ++i)
        if (accountNumber == accounts[i].getAccountNumber())
            return &accounts[i];

    return NULL;
}

#endif // BALANCE_INQUIRY_H