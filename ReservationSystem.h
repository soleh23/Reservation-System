#include<bits/stdc++.h>
#include "Flight.h"
#pragma once

using namespace std;

/*
Name: Solehjon Ruziboev
ID:   21500283
*/

class ReservationSystem {
    public:
        ReservationSystem();
        ~ReservationSystem();

        void addFlight( const int flightNo, const int rowNo, const int seatNo );
        void cancelFlight( const int flightNo );

        void showAllFlights();
        void showFlight( const int flightNo );

        int makeReservation( const int flightNo, const int numPassengers,
                             const int *seatRow, const char *seatCol );

        void cancelReservation( const int resCode );
        void showReservation( const int resCode );

        // additional data members and functions
        int getId(const int flightNo);

    private:
        const static int MAX_NUMBER_OF_FLIGHTS = 1e6;
        int noFlights, *codeSize;
        Flight *flights;
        char **pcodes;
        stack<int>codes;

        void addCode(const int curCode, const int *seatRow, const char *seatCol);
};

