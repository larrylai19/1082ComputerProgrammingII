// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h"

// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::loadReservations()
{
    Reservation in;
    ifstream inFile("Reservation details.dat", ios::binary);
    if (!inFile)
    {
        inFile.close();
        ofstream CreateFile("Reservation details.dat", ios::binary);
        CreateFile.close();
        ifstream inFile("Reservation details.dat", ios::binary);
    }

    while (inFile.read((char*)&in, sizeof(Reservation)))
        reservations.push_back(in);
}

void ReservationDatabase::storeReservations()
{
    ofstream outFile("Reservation details.dat", ios::binary);

    for (const auto& i : reservations)
        outFile.write((char*)&i, sizeof(Reservation));

    outFile.close();
}

bool ReservationDatabase::exist( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return true; // return true if match found

   return false; // if no matching reservation was found, return false
}

void ReservationDatabase::displayReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   reservations.erase( it );
   cout << "Reservation Cancelled.\n\n";
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::reduceSeats( string idNumber, string reservationNumber )
{
    auto Res = searchReservation(idNumber, reservationNumber);
    int Radult, Rcon;

    while (true)
    {
        cout << "\nHow many adult tickets to cancel? ";
        cin >> Radult;
        cout << "How many concession tickets to cancel? ";
        cin >> Rcon;

        if (Radult <= Res->getAdultTickets() && Rcon <= Res->getConcessionTickets() && (Radult + Rcon) < (Res->getAdultTickets() + Res->getConcessionTickets()))
            break;
        cout << "\nThe tickets shouldn't smaller than 1.\nPlease input again.\n";
    }

    Res->setAdultTickets(Res->getAdultTickets() - Radult);
    Res->setConcessionTickets(Res->getConcessionTickets() - Rcon);

    Res->displayReservationDetails();

    cout << "\nYou have successfully reduced the number of tickets!\n\n";
}

vector< Reservation >::iterator ReservationDatabase::searchReservation( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return it; // return iterator to thecurrent reservation if match found

   return reservations.end();
}