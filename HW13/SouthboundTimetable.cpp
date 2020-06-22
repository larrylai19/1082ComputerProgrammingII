// FlightSchedule.cpp
// Member-function definitions for class SouthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SouthboundTimetable.h"

extern string departureTimes[ 37 ];

// SouthboundTimetable default constructor
// loads southbound timetable from the file "Southbound timetable.dat"
SouthboundTimetable::SouthboundTimetable()
{
   loadSouthboundTimetable();
}

void SouthboundTimetable::loadSouthboundTimetable()
{
    Train in;
    ifstream inFile("Southbound timetable.dat", ios::binary);

    if (!inFile)
    {
        cout << "File could not be open!( Southbound timetable.dat )";
        exit(1);
    }

    while (inFile.read((char*)&in, sizeof(Train)))
        southboundTimetable.push_back(in);

    inFile.close();
}

// returns departureTimes[ station ]
string SouthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool SouthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    for (auto& i : southboundTimetable)
        if (i.getDepartureTimes(originStation) != "-" && i.getDepartureTimes(destinationStation) != "-")
            if (i.getDepartureTimes(originStation) >= departureTimes[departureTime])
                return true;      

    return false;
}

void SouthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    int num = 0;

    cout << "\nTrain No.  Departure  Arrival\n";

    for (auto& i : southboundTimetable)
        if (i.getDepartureTimes(originStation) != "-" && i.getDepartureTimes(destinationStation) != "-")
            if (i.getDepartureTimes(originStation) >= departureTimes[departureTime] && num < 10)
            {
                cout << setw(9) << i.getTrainNumber()
                    << setw(11) << i.getDepartureTimes(originStation)
                    << setw(9) << i.getDepartureTimes(destinationStation)
                    << endl;
                ++num;
            }
}

vector< Train >::iterator SouthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = southboundTimetable.begin();
   for( ; it != southboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return southboundTimetable.end();
}