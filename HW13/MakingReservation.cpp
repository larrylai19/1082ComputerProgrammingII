// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

extern int inputAnInteger( int begin, int end );

extern string departureTimes[ 37 ];

extern string Station[13];

// MakingReservation constructor
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      SouthboundTimetable &theSouthboundTimetable,
                                      NorthboundTimetable &theNorthboundTimetable )
   : reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
}

void MakingReservation::execute()
{
   if( chooseTrain() ) // displays timetables for 10 coming trains, then let user choose a train
   {
      inputReservationDetails();

      inputContactPersonInfo();

      reservationDatabase.addReservation( reservation );

      cout << "\nReservation Completed!\n\n";
   }
   else
      cout << "\nSorry! No train is available!\n\n";
}

bool MakingReservation::chooseTrain()
{
    int temp, departuretime;
    string stemp;

    cout << "Origin Station";
    for (int i = 1; i < 13; ++i)
        cout << endl << i << ". " << Station[i];
    do cout << "\n? ";
    while ((temp = inputAnInteger(1, 12)) == -1);
    reservation.setOriginStation(temp);

    cout << "\nDestination Station";
    for (int i = 1; i < 13; ++i)
        cout << endl << i << ". " << Station[i];
    while (true)
    {
        do cout << "\n? ";
        while ((temp = inputAnInteger(1, 12)) == -1);
        if (temp != reservation.getOriginStation())
            break;
    }
    reservation.setDestinationStation(temp);


    cout << "\nDeparture Time";
    for (int i = 1; i < 37; ++i)
        cout << endl << setw(2) << i << ". " << departureTimes[i];
    do cout << "\n? ";
    while ((departuretime = inputAnInteger(1, 36)) == -1);
    
    if (reservation.getOriginStation() < reservation.getDestinationStation())
    {
        if (!southboundTimetable.trainsAvailable(departuretime, reservation.getOriginStation(), reservation.getDestinationStation()))
            return false;
        southboundTimetable.displayComingTrains(departuretime, reservation.getOriginStation(), reservation.getDestinationStation());
    }
    else
    {
        if (!northboundTimetable.trainsAvailable(departuretime, reservation.getOriginStation(), reservation.getDestinationStation()))
            return false;
        northboundTimetable.displayComingTrains(departuretime, reservation.getOriginStation(), reservation.getDestinationStation());
    }

    cout << "\nEnter Train Number: ";
    cin >> stemp;
    reservation.setTrainNumber(stemp);

    return true;
}

void MakingReservation::inputReservationDetails()
{
   cout << "\nCar Class\n" << "1. Standard Car\n" << "2. Business Car";

   int carClass;
   do cout << "\n? ";
   while( ( carClass = inputAnInteger( 1, 2 ) ) == -1 );
   reservation.setCarClass( carClass );

	cout << "\nDeparture Date: ";

   char date[12];
   cin >> date;
   reservation.setDate( date );
   cin.ignore();

	cout << "\nHow many adult tickets? ";

   int adultTickets;
   cin >> adultTickets;
   reservation.setAdultTickets( adultTickets );

	cout << "\nHow many concession tickets? ";

   int concessionTickets;
   cin >> concessionTickets;
   reservation.setConcessionTickets( concessionTickets );

   cout << "\nTrip Details\n";
   reservation.displayReservationDetails();
}

void MakingReservation::inputContactPersonInfo()
{
   cout << "\nEnter Contact Person Information\n\n";

   cout << "ID Number: ";
   string idNumber;
   cin >> idNumber;
   reservation.setIdNumber( idNumber );

   cout << "\nPhone: ";
   string phone;
   cin >> phone;
   cin.ignore();
   reservation.setPhone( phone );

   srand( static_cast< unsigned int >( time( 0 ) ) );
   char reservationNumber[ 12 ];
   for( int i = 0; i < 8; i++ )
      reservationNumber[ i ] = rand() % 10 + '0';
   reservationNumber[ 8 ] = '\0';
   reservation.setReservationNumber( reservationNumber );
   
	cout << "\nReservation Number: " << reservationNumber << endl;
}