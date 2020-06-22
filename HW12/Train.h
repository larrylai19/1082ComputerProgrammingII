#ifndef TRAIN_H
#define TRAIN_H

extern int adultTicketPrice[13][13];
extern char departureTimes[37][8];
extern char Station[13][10];
extern char CarClass[3][9];

struct Reservation
{
    char reservationNumber[12]; // used to identify a reservation  訂位代號
    char trainNumber[8]; // used to identify a train  車次號碼
    char idNumber[12]; // the id number of the contact person  取票人的身分證字號
    char phone[12]; // the (local or mobile) phone number of the contact person  取票人的聯絡電話
    char date[12]; // outbound date  搭乘日期
    int originStation; // the origin station code  起程站代碼
    int destinationStation; // the destination station code  到達站代碼
    int carClass; // the car class code; 1:standard car, 2:business car  車廂種類; 1:標準車廂, 2:商務車廂
    int adultTickets; // the number of adult tickets  全票張數
    int concessionTickets; // the number of concession tickets  優待票張數
};

struct Train
{
    char trainNumber[8]; // used to identify a train  車次號碼
    char departureTimes[13][8]; // the departure time of a train for each station  火車在各站的離站時間
};                                       // departureTimes[0] is not used   departureTimes[0]未使用

struct TrainDetails
{
    char trainNumber[8];
    char departureTime[8];
    char arrivalTime[8];
    int adultPrice;
    int concessionPrice;
};

class Book
{
public:
    Book();
    ~Book();
    void LoadAllReservation(); // 讀取所有訂單
    void SaveAllReservation(); // 儲存所有訂單
    void LoadNorthBound(); // 讀取列車資訊( 北上 )
    void LoadSouthBound(); // 讀取列車資訊( 南下 )
    void ShowTripDetails(Reservation& newRes, TrainDetails& tripDetail);
    TrainDetails ChooseTrainNorth(Reservation& newRes, char* DepartureTime);
    TrainDetails ChooseTrainSouth(Reservation& newRes, char* DepartureTime);
    TrainDetails GetDetails(Reservation* inquire);
    Reservation* BookExist(Reservation& inquire);
    int EnterChoice(int min, int max, int except = 0);

    void Booking();
    void BookingHistory();

private:
    vector< Reservation > reservation;
    vector< Train > Northbound;
    vector< Train > Southbound;
    vector< TrainDetails > TrainToChoose;
};

Book::Book()
{
    LoadAllReservation();
    LoadNorthBound();
    LoadSouthBound();
}

Book::~Book()
{
    SaveAllReservation();
}

void Book::LoadAllReservation()
{
    ifstream inFile("Reservation details.dat", ios::binary);

    if (!inFile)
    {
        inFile.close();

        ofstream CreateFile("Reservation details.dat", ios::binary);
        CreateFile.close();

        ifstream inFile("Reservation details.dat", ios::binary);
    }

    Reservation in;

    while (inFile.read((char*)(&in), sizeof(Reservation)))
        reservation.push_back(in);

    inFile.close();
}

void Book::SaveAllReservation()
{
    ofstream outFile("Reservation details.dat", ios::binary);

    for (const auto& i : reservation)
        outFile.write((char*)(&i), sizeof(Reservation));

    outFile.close();
}

void Book::LoadNorthBound()
{
    ifstream inFile("Northbound timetable.dat", ios::binary);

    if (!inFile)
    {
        cout << "File could not be open!( Northbound timetable.dat )\n";
        exit(1);
    }

    Train in;

    while (inFile.read((char*)(&in), sizeof(Train)))
        Northbound.push_back(in);

    inFile.close();
}

void Book::LoadSouthBound()
{
    ifstream inFile("Southbound timetable.dat", ios::binary);

    if (!inFile)
    {
        cout << "File could not be open!( Southbound timetable.dat )\n";
        exit(1);
    }

    Train in;

    while (inFile.read((char*)(&in), sizeof(Train)))
        Southbound.push_back(in);

    inFile.close();
}

void Book::ShowTripDetails(Reservation& newRes, TrainDetails& tripDetail)
{
    cout << setw(10) << newRes.date
        << setw(11) << newRes.trainNumber
        << setw(9) << Station[newRes.originStation]
        << setw(10) << Station[newRes.destinationStation]
        << setw(11) << tripDetail.departureTime
        << setw(9) << tripDetail.arrivalTime
        << setw(5) << tripDetail.adultPrice << "*" << setw(2) << newRes.adultTickets
        << setw(9) << tripDetail.concessionPrice << "*" << setw(2) << newRes.concessionTickets
        << setw(6) << newRes.adultTickets * tripDetail.adultPrice + newRes.concessionTickets * tripDetail.concessionPrice
        << setw(10) << CarClass[newRes.carClass];
}

TrainDetails Book::ChooseTrainNorth(Reservation& newRes, char* DepartureTime)
{
    TrainToChoose.clear();

    TrainDetails in;
    size_t temp = 0;

    for (size_t i = 1; i < Northbound.size(); ++i)
        if ((strcmp(Northbound[i].departureTimes[13 - newRes.originStation], "-") != 0) && (strcmp(Northbound[i].departureTimes[13 - newRes.destinationStation], "-") != 0))
            if ((strcmp(Northbound[i].departureTimes[13 - newRes.originStation], DepartureTime)) != -1)
            {
                temp = i;
                break;
            }

    if (!temp)
        for (size_t i = 1; i < Northbound.size(); ++i)
            if ((strcmp(Northbound[i].departureTimes[13 - newRes.originStation], "-") != 0) && (strcmp(Northbound[i].departureTimes[13 - newRes.destinationStation], "-") != 0))
            {
                temp = i;
                break;
            }

    while (TrainToChoose.size() < 10)
    {
        if ((strcmp(Northbound[temp].departureTimes[13 - newRes.originStation], "-") != 0) && (strcmp(Northbound[temp].departureTimes[13 - newRes.destinationStation], "-") != 0))
        {
            strcpy_s(in.departureTime, 8, Northbound[temp].departureTimes[13 - newRes.originStation]);
            strcpy_s(in.arrivalTime, 8, Northbound[temp].departureTimes[13 - newRes.destinationStation]);
            strcpy_s(in.trainNumber, 8, Northbound[temp].trainNumber);
            TrainToChoose.push_back(in);
        }
        ++temp;
        if (temp >= Northbound.size())
            temp = 1;
    }

    for (const auto& i : TrainToChoose)
        cout << setw(9) << i.trainNumber
        << setw(11) << i.departureTime
        << setw(9) << i.arrivalTime
        << endl;

    while (true)
    {
        cout << "\nEnter Train Number: ";
        cin >> newRes.trainNumber;

        for (auto& i : TrainToChoose)
            if (!strcmp(newRes.trainNumber, i.trainNumber))
            {
                if (newRes.carClass == 1)
                {
                    //i.adultPrice = adultTicketPrice[13 - newRes.destinationStation][13 - newRes.originStation];
                    i.adultPrice = adultTicketPrice[newRes.originStation][newRes.destinationStation];
                    i.concessionPrice = i.adultPrice / 2;
                }
                else
                {
                    //i.adultPrice = adultTicketPrice[13 - newRes.originStation][13 - newRes.destinationStation];
                    i.adultPrice = adultTicketPrice[newRes.destinationStation][newRes.originStation];
                    i.concessionPrice = i.adultPrice / 2;
                }
                return i;
            }

        cout << "\nPlease input the train number in the list\n";
    }
}

TrainDetails Book::ChooseTrainSouth(Reservation& newRes, char* DepartureTime)
{
    TrainToChoose.clear();

    TrainDetails in;
    size_t temp = 0;

    for (size_t i = 1; i < Southbound.size(); ++i)
        if ((strcmp(Southbound[i].departureTimes[newRes.originStation], "-") != 0) && (strcmp(Southbound[i].departureTimes[newRes.destinationStation], "-") != 0))
            if ((strcmp(Southbound[i].departureTimes[newRes.originStation], DepartureTime)) != -1)
            {
                temp = i;
                break;
            }

    if (!temp)
        for (size_t i = 1; i < Southbound.size(); ++i)
            if ((strcmp(Southbound[i].departureTimes[newRes.originStation], "-") != 0) && (strcmp(Southbound[i].departureTimes[newRes.destinationStation], "-") != 0))
            {
                temp = i;
                break;
            }

    while (TrainToChoose.size() < 10)
    {
        if ((strcmp(Southbound[temp].departureTimes[newRes.originStation], "-") != 0) && (strcmp(Southbound[temp].departureTimes[newRes.destinationStation], "-") != 0))
        {
            strcpy_s(in.departureTime, 8, Southbound[temp].departureTimes[newRes.originStation]);
            strcpy_s(in.arrivalTime, 8, Southbound[temp].departureTimes[newRes.destinationStation]);
            strcpy_s(in.trainNumber, 8, Southbound[temp].trainNumber);
            TrainToChoose.push_back(in);
        }
        ++temp;
        if (temp >= Southbound.size())
            temp = 1;
    }

    for (const auto& i : TrainToChoose)
        cout << setw(9) << i.trainNumber
        << setw(11) << i.departureTime
        << setw(9) << i.arrivalTime
        << endl;

    while (true)
    {
        cout << "\nEnter Train Number: ";
        cin >> newRes.trainNumber;

        for (auto& i : TrainToChoose)
            if (!strcmp(newRes.trainNumber, i.trainNumber))
            {
                if (newRes.carClass == 1)
                {
                    i.adultPrice = adultTicketPrice[newRes.destinationStation][newRes.originStation];
                    i.concessionPrice = i.adultPrice / 2;
                }
                else
                {
                    i.adultPrice = adultTicketPrice[newRes.originStation][newRes.destinationStation];
                    i.concessionPrice = i.adultPrice / 2;
                }
                return i;
            }

        cout << "\nPlease input the train number in the list\n";
    }
}

TrainDetails Book::GetDetails(Reservation* inquire)
{
    TrainDetails data;

    if (inquire->originStation < inquire->destinationStation)
    {
        for (const auto& i : Southbound)
            if (!strcmp(inquire->trainNumber, i.trainNumber))
            {
                strcpy_s(data.departureTime, 8, i.departureTimes[inquire->originStation]);
                strcpy_s(data.arrivalTime, 8, i.departureTimes[inquire->destinationStation]);
                strcpy_s(data.trainNumber, 8, i.trainNumber);
                if (inquire->carClass == 1)
                {
                    data.adultPrice = adultTicketPrice[inquire->destinationStation][inquire->originStation];
                    data.concessionPrice = data.adultPrice / 2;
                }
                else
                {
                    data.adultPrice = adultTicketPrice[inquire->originStation][inquire->destinationStation];
                    data.concessionPrice = data.adultPrice / 2;
                }
            }
    }
    else
    {
        for (const auto& i : Northbound)
            if (!strcmp(inquire->trainNumber, i.trainNumber))
            {
                strcpy_s(data.departureTime, 8, i.departureTimes[13 - inquire->originStation]);
                strcpy_s(data.arrivalTime, 8, i.departureTimes[13 - inquire->destinationStation]);
                strcpy_s(data.trainNumber, 8, i.trainNumber);
                if (inquire->carClass == 1)
                {
                    //data.adultPrice = adultTicketPrice[13 - inquire->destinationStation][13 - inquire->originStation];
                    data.adultPrice = adultTicketPrice[inquire->originStation][inquire->destinationStation];
                    data.concessionPrice = data.adultPrice / 2;
                }
                else
                {
                    //data.adultPrice = adultTicketPrice[13 - inquire->originStation][13 - inquire->destinationStation];
                    data.adultPrice = adultTicketPrice[inquire->destinationStation][inquire->originStation];
                    data.concessionPrice = data.adultPrice / 2;
                }
            }
    }

    return data;
}

Reservation* Book::BookExist(Reservation& inquire)
{
    for (auto& i : reservation)
        if ((!strcmp(i.idNumber, inquire.idNumber)) && (!strcmp(i.reservationNumber, inquire.reservationNumber)))
            return &i;

    return nullptr;      
}

int Book::EnterChoice(int min, int max, int except)
{
    char input[80];
    int choice;
    bool check = true;

    while (check)
    {
        check = false;

        cin.getline(input, 80, '\n');

        if(!strlen(input))
            cin.getline(input, 80, '\n');

        for (size_t i = 0; i < strlen(input); ++i)
            if (input[i] < '0' || input[i] > '9')
            {
                check = true;
                break;
            }

        if (check)
        {
            cout << "\nWrong input, Please enter a number\n? ";
            continue;
        }

        choice = atoi(input);

        if (choice >= min && choice <= max && choice != except)
            break;

        check = true;

        if (except != 0)
            cout << "\nWrong input, Please enter a number in range( " << min << " ~ " << max << " )"
                << "\nAnd don't input except choice " << except << "\n? ";
        else
            cout << "\nWrong input, Please enter a number in range( " << min << " ~ " << max << " )\n? ";
    }

    return choice;
}

void Book::Booking()
{
    Reservation newRes;
    TrainDetails tripDetail;
    char DepartureTime[8];
    int temp;

    cout << "\nOrigin Station\n";
    for (int i = 1; i < 13; ++i)
        cout << i << ". " << Station[i] << endl;
    cout << "? ";
    newRes.originStation = EnterChoice(1, 12);

    cout << "\nDestination Station\n";
    for (int i = 1; i < 13; ++i)
        cout << i << ". " << Station[i] << endl;
    cout << "? ";
    newRes.destinationStation = EnterChoice(1, 12, newRes.originStation);

    cout << "\nCar Class\n1. Standard Car\n2. Business Car\n? ";
    newRes.carClass = EnterChoice(1, 2);

    cout << "\nDeparture Date: ";
    cin >> newRes.date;

    cout << "\nDeparture Time\n";
    for (int i = 1; i < 37; ++i)
        cout << setw(2) << i << ". " << departureTimes[i] << endl;
    cout << "? ";
    temp = EnterChoice(1, 36);
    strcpy_s(DepartureTime, 8, departureTimes[temp]);

    cout << "\nHow many adult tickets? ";
    cin >> newRes.adultTickets;

    cout << "\nHow many concession tickets? ";
    cin >> newRes.concessionTickets;

    cout << "\nTrain No.  Departure  Arrival\n";
    if (newRes.originStation < newRes.destinationStation)
        tripDetail = ChooseTrainSouth(newRes, DepartureTime);
    else
        tripDetail = ChooseTrainNorth(newRes, DepartureTime);

    cout << "\nTrip Details\n"
        "      Date  Train No.     From        To  Departure  Arrival   Adult  Concession  Fare     Class\n";

    ShowTripDetails(newRes, tripDetail);

    cout << "\n\nEnter Contact Person Information\n";
    cout << "\nID Number: ";
    cin >> newRes.idNumber;
    cout << "\nPhone: ";
    cin >> newRes.phone;

    srand((unsigned)time(0));
    for (int i = 0; i < 8; ++i)
        newRes.reservationNumber[i] = (rand() % 10 + '0');
    newRes.reservationNumber[8] = '\0';

    cout << "\nEnter Reservation Number: " << newRes.reservationNumber;
    cout << "\n\nReservation Completed!\n\n";

    reservation.push_back(newRes);
}

void Book::BookingHistory()
{
    Reservation inquire;
    Reservation* Res;
    int choice;

    while (true)
    {
        cout << "\nEnter ID Number: ";
        cin >> inquire.idNumber;
        cout << "\nEnter Reservation Number: ";
        cin >> inquire.reservationNumber;
        if ((Res = BookExist(inquire)) != nullptr)
            break;
        cout << "\nThere is no data. Please input again.\n";
    }

    TrainDetails Details = GetDetails(Res);

    cout << "\nReservation Details\n\n";
    cout << "      Date  Train No.     From        To  Departure  Arrival   Adult  Concession  Fare     Class\n";
    
    ShowTripDetails(*Res, Details);

    cout << "\n\nEnter Your Choice"
        << "\n1. Cancellation"
        << "\n2. Reduce"
        << "\n3. End\n? ";

    switch (choice = EnterChoice(1, 3))
    {
    case 1:
        for (size_t i = 0; i < reservation.size(); ++i)
            if (!strcmp(Res->reservationNumber, reservation[i].reservationNumber))
            {
                reservation.erase(reservation.begin() + i);
                break;
            }

        cout << "\nReservation Cancelled.\n\n";
        break;
        
    case 2:
        int adult, concession;

        while (true)
        {
            cout << "\nHow many adult tickets to cancel? ";
            cin >> adult;
            cout << "How many concession tickets to cancel? ";
            cin >> concession;
            if ((Res->adultTickets - adult >= 0) &&
                (Res->concessionTickets - concession >= 0) &&
                ((Res->adultTickets - adult) + (Res->concessionTickets - concession)) > 0)
                break;
            cout << "\nThe tickets shouldn't smaller than 1. Please input again\n";
        }

        Res->adultTickets -= adult;
        Res->concessionTickets -= concession;

        cout << "\nReservation Details\n\n";
        cout << "      Date  Train No.     From        To  Departure  Arrival   Adult  Concession  Fare     Class\n";
        
        ShowTripDetails(*Res, Details);

        cout << "\n\nYou have successfully reduced the number of tickets!\n\n";
        break;
        
    case 3:
        return;
        break;

    }
}

#endif