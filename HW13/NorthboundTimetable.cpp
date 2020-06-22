// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h"

extern string departureTimes[ 37 ];

// NorthboundTimetable default constructor
// loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable()
{
   loadNorthboundTimetable();
}

void NorthboundTimetable::loadNorthboundTimetable()
{
    Train in;
    ifstream inFile("Northbound timetable.dat", ios::binary);

    if (!inFile)
    {
        cout << "File could not be open!( Northbound timetable.dat )";
        exit(1);
    }

    while (inFile.read((char*)&in, sizeof(Train)))
        northboundTimetable.push_back(in);

    inFile.close();
}

// returns departureTimes[ station ]
string NorthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool NorthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    for (auto& i : northboundTimetable)
        if (i.getDepartureTimes(13 - originStation) != "-" && i.getDepartureTimes(13 - destinationStation) != "-")
            if (i.getDepartureTimes(13 - originStation) >= departureTimes[departureTime])
                return true;

    return false;
}

void NorthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    int num = 0;

    cout << "\nTrain No.  Departure  Arrival\n";

    for (auto& i : northboundTimetable)
        if (i.getDepartureTimes(13 - originStation) != "-" && i.getDepartureTimes(13 - destinationStation) != "-")
            if (i.getDepartureTimes(13 - originStation) >= departureTimes[departureTime] && num < 10)
            {
                cout << setw(9) << i.getTrainNumber()
                    << setw(11) << i.getDepartureTimes(13 - originStation)
                    << setw(9) << i.getDepartureTimes(13 - destinationStation)
                    << endl;
                ++num;
            }
}

vector< Train >::iterator NorthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = northboundTimetable.begin();
   for( ; it != northboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return northboundTimetable.end();
}