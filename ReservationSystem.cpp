#include<bits/stdc++.h>
#include "ReservationSystem.h"
#include "Flight.h"
using namespace std;

/*
Name: Solehjon Ruziboev
ID:   21500283
*/

ReservationSystem::ReservationSystem(){
    noFlights = 0;
    flights = NULL;

    pcodes = new char *[MAX_NUMBER_OF_FLIGHTS+1];
    for (int i = 1; i <= MAX_NUMBER_OF_FLIGHTS; i++)
        pcodes[i] = NULL;

    codeSize = new int [MAX_NUMBER_OF_FLIGHTS+1];
    for (int i = MAX_NUMBER_OF_FLIGHTS; i >= 1; i--){
        codes.push(i);
        codeSize[i] = 0;
    }
}

ReservationSystem::~ReservationSystem(){
    delete []codeSize;
    codeSize = NULL;

    if (flights){
        delete []flights;
        flights = NULL;
    }
    for (int i = 1; i <= MAX_NUMBER_OF_FLIGHTS; i++){
        if (pcodes[i]){
            delete []pcodes[i];
            pcodes[i] = NULL;
        }
    }
    delete []pcodes;
    pcodes = NULL;
}

int ReservationSystem::getId(const int flightNo){
    for (int i = 0; i < noFlights; i++){
        if (flights[i].getId() == flightNo){
            return i;
        }
    }
    return -1;
}

void ReservationSystem::addFlight( const int flightNo, const int rowNo, const int seatNo ){
    if (getId(flightNo) != -1){
        //printf ("Flight %d already exists\n\n", flightNo);
        cout<<"Flight "<<flightNo<<" already exists"<<endl;
        return;
    }

    Flight *temp = flights;
    flights = new Flight[noFlights + 1];
    for (int i = 0; i < noFlights; i++){
        flights[i] = temp[i];
    }
    //Flight tempFlight(flightNo, rowNo, seatNo);
    flights[noFlights++] = Flight (flightNo, rowNo, seatNo);//Flight(tempFlight);

    if (temp)
        delete []temp;

    //printf ("Flight %d has been added\n\n", flightNo);
    cout<<"Flight "<<flightNo<<" has been added"<<endl<<endl;
}

void ReservationSystem::cancelFlight( const int flightNo ){
    int ind = getId(flightNo), noCodes, *curCodes;
    if (ind == -1){
        //printf ("Flight %d does not exist\n\n", flightNo);
        cout<<"Flight "<<flightNo<<" does not exist"<<endl<<endl;
        return;
    }

    curCodes = flights[ind].getResCodes(noCodes);
    for (int i = noCodes - 1; i >= 0; i--){
        codes.push(curCodes[i]);
        codeSize[curCodes[i]] = 0;

        delete pcodes[curCodes[i]];
        pcodes[curCodes[i]] = NULL;
    }

    if (curCodes)
        delete []curCodes;

    Flight *temp = flights;
    if (noFlights > 1)
        flights = new Flight [noFlights - 1];
    else
        flights = NULL;

    int c = 0;
    for (int i = 0; i < noFlights; i++){
        if (i != ind)
            flights[c++] = temp[i];
    }

    noFlights--;

    if (temp)
        delete []temp;

    //printf ("Flight %d and all of its reservations are cancelled\n\n", flightNo);
    cout<<"Flight "<<flightNo<<" and all of its reservations are cancelled"<<endl<<endl;
}

void ReservationSystem::showAllFlights(){
    if (noFlights == 0){
        //printf ("No flights exist\n\n");
        cout<<"No flights exist"<<endl<<endl;
        return;
    }

    //printf ("Flights currently operated:\n");
    cout<<"Flights currently operated:"<<endl;
    for (int i = 0; i < noFlights; i++){
        //printf ("Flight %d (%d available seats)\n", flights[i].getId(), flights[i].getFreeSeats());
        cout<<"Flight "<<flights[i].getId()<<" ("<<flights[i].getFreeSeats()<<" available seats)"<<endl;
    }
    //printf("\n");
    cout<<endl;
}

void ReservationSystem::showFlight(const int flightNo){
    int ind = getId(flightNo);
    if (ind == -1){
        //printf ("Flight %d does not exist\n\n", flightNo);
        cout<<"Flight "<<flightNo<<" does not exist"<<endl<<endl;
        return;
    }

    //printf ("Flight %d has %d available seats\n", flightNo, flights[ind].getFreeSeats());
    cout <<"Flight "<<flightNo<<" has "<<flights[ind].getFreeSeats()<<" available seats"<<endl;
    flights[ind].display();
}

int ReservationSystem::makeReservation(const int flightNo, const int numPassengers, const int *seatRow, const char *seatCol){
    int takenSeats = 0, ind = getId(flightNo), code = codes.top();
    bool done = true;


    if (ind == -1){
        //printf ("Flight %d does not exist\n\n", flightNo);
        cout<<"Flight "<<flightNo<<" does not exist"<<endl<<endl;
        return -1;
    }

    for (int i = 0; i < numPassengers; i++)
        if (!flights[ind].isFree(seatRow[i], seatCol[i])){
            //printf ("%d%c ", seatRow[i], seatCol[i]);
            cout<<seatRow[i]<<seatCol[i]<<" ";
            takenSeats++;
            done = false;
        }

    if (takenSeats == 1)
        cout<<"is not available" << endl<<endl;
        //printf ("is not available\n\n");
    else if (takenSeats > 1)
        cout<<"are not available"<<endl<<endl;
        //printf ("are not available\n\n");

    if (!done){
        return -1;
    }

    for (int i = 0; i < numPassengers; i++)
        flights[ind].reserve(seatRow[i], seatCol[i]);

    codeSize[code] = 2*numPassengers;
    addCode(code, seatRow, seatCol);
    flights[ind].addReservation(code);

    codes.pop();
    return code;
}

void ReservationSystem::cancelReservation( const int resCode ){
    if (codeSize[resCode] == 0){
        //printf ("No reservations are found under Code %d\n\n", resCode);
        cout<<"No reservations are found under Code "<<resCode<<endl<<endl;
        return;
    }

    int flightNo, ind;
    for (int i = 0; i < noFlights; i++){
        if (flights[i].isCodePresent(resCode)){
            flightNo = flights[i].getId();
            ind = i;
            break;
        }
    }

    flights[ind].cancelReservation(resCode);

    string sop = (codeSize[resCode] > 1) ? "seats" : "seat";
    cout<< "Reservation for the " << sop << " ";
    for (int i = 0; i < codeSize[resCode]; i+=2){
        //printf ("%d%c ", pcodes[resCode][i], pcodes[resCode][i+1]);
        cout<<int(pcodes[resCode][i])<<pcodes[resCode][i+1]<<" ";
        flights[ind].freeSeat(int(pcodes[resCode][i]), pcodes[resCode][i+1]);
    }
    //printf ("is cancelled in Flight %d\n\n", flightNo);
    cout<<"is cancelled in Flight "<<flightNo<<endl<<endl;
}
void ReservationSystem::showReservation( const int resCode ){
    if (codeSize[resCode] == 0){
        //printf ("No reservations under Code %d\n\n", resCode);
        cout<<"No reservations under Code "<<resCode<<endl<<endl;
        return;
    }

    int flightNo;
    for (int i = 0; i < noFlights; i++){
        if (flights[i].isCodePresent(resCode)){
            flightNo = flights[i].getId();
            break;
        }
    }

    //printf ("Reservation under Code %d in Flight %d: ", resCode, flightNo);
    cout<<"Reservation under Code "<<resCode<<" in Flight "<<flightNo<<": ";
    for (int i = 0; i < codeSize[resCode]; i+=2){
        //printf ("%d%c ", pcodes[resCode][i], pcodes[resCode][i+1]);
        cout<<int(pcodes[resCode][i])<<pcodes[resCode][i+1]<<" ";
    }
    //printf ("\n\n");
    cout<<endl<<endl;
}

void ReservationSystem::addCode(const int curCode, const int *seatRow, const char *seatCol){
    pcodes[curCode] = new char [codeSize[curCode]];
    for (int i = 0; i < codeSize[curCode]; i++){
        pcodes[curCode][i] = !(i%2) ? seatRow[i/2] : seatCol[i/2];
    }
}
