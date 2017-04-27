#include<bits/stdc++.h>
#include "Flight.h"
using namespace std;

/*
Name: Solehjon Ruziboev
ID:   21500283
*/

Flight::Flight(){
    data = NULL;
    resCodes = NULL;

    id = 0;
    rows = 0;
    columns = 0;
    freeSeats = 0;
    resNo = 0;
}

Flight::Flight (int a_id, int a_rows, int a_columns){
    data = new char *[a_rows];
    for (int i = 0; i < a_rows; i++){
        data[i] = new char [a_columns];
        for (int j = 0; j < a_columns; j++){
            data[i][j] = 'o';
        }
    }

    resCodes = NULL;

    id = a_id;
    rows = a_rows;
    columns = a_columns;
    freeSeats = rows*columns;
    resNo = 0;
}

//never used
//copy constructor
Flight::Flight (const Flight &x){
    printf ("copy constructor called.\n");
    rows = x.rows;
    columns = x.columns;
    id = x.id;
    freeSeats = x.freeSeats;
    resCodes = x.getResCodes(resNo);

    if (rows > 0 && columns > 0){
        data = new char *[rows];
        for (int i = 0; i < rows; i++){
            data[i] = new char [columns];
            for (int j = 0; j < columns; j++){
                data[i][j] = x.data[i][j];
            }
        }
    }
    else {
        data = NULL;
    }

}

void Flight::operator=(const Flight &right){
    //printf ("overload assign operator called.\n");
    id = right.id;
    freeSeats = right.freeSeats;

    if (&right != this){
        if (right.resNo != resNo){
            if (resNo > 0)
                delete []resCodes;

            resNo = right.resNo;
            if (resNo > 0)
                resCodes = new int [resNo];
            else
                resCodes = NULL;
        }
        for (int i = 0; i < resNo; i++)
            resCodes[i] = right.resCodes[i];

        if (rows != right.rows || columns != right.columns){
            //printf ("im in if statement\n");
            for (int i = 0; i < rows; i++){
                if (data[i]){
                    delete[] data[i];
                    data[i] = NULL;
                }
            }
            if (data){
                delete[] data;
                data = NULL;
            }

            rows = right.rows;
            columns = right.columns;


            data = (rows > 0) ? (new char *[rows]) : NULL;

            for (int i = 0; i < rows; i++)
                data[i] = (columns > 0) ? (new char[columns]) : NULL;
        }

        /*data = new char *[rows];
        for (int i = 0; i < rows; i++)
            data[i] = new char [columns];*/
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                data[i][j] = right.data[i][j];
    }

}

Flight::~Flight(){
    for (int i = 0; i < rows; i++){
        if (data[i]){
            delete[] data[i];
            data[i] = NULL;
        }
    }
    if (data){
        delete[] data;
        data = NULL;
    }
    if (resCodes){
        delete[] resCodes;
        resCodes = NULL;
    }
}

bool Flight::isFree(int a_row, char char_column){
    int row = a_row - 1, column = char_column - 'A';
    return (data[row][column] == 'o');
}

bool Flight::reserve(int a_row, char char_column){
    int row = a_row - 1, column = char_column - 'A';
    if (data[row][column] == 'o'){
        data[row][column] = 'x';
        freeSeats--;
        return true;
    }
    else {
        //printf ("%d%c ", row, char_column);
        return false;
    }
}

void Flight::freeSeat(int a_row, char char_column){
    int row = a_row - 1, column = char_column - 'A';
    data[row][column] = 'o';
    freeSeats++;
}

void Flight::addReservation(int code){
    int *temp = resCodes;
    resCodes = new int [resNo + 1];
    for (int i = 0; i < resNo; i++){
        resCodes[i] = temp[i];
    }
    resCodes[resNo++] = code;

    if (temp)
        delete []temp;
}

void Flight::cancelReservation(int code){
    int *temp = resCodes;

    if (resNo - 1 > 0)
        resCodes = new int [resNo - 1];
    else
        resCodes = NULL;

    int c = 0;
    for (int i = 0; i < resNo; i++){
        if (temp[i] != code)
            resCodes[c++] = temp[i];
    }
    resNo--;

    if (temp)
        delete []temp;
}

bool Flight::isCodePresent (int code){
    for (int i = 0; i < resNo; i++){
        if (resCodes[i] == code)
            return true;
    }
    return false;
}

void Flight::display(){
    printf ("  ");
    for (int i = 0; i < columns; i++)
        printf ("%c ", 'A' + i);

    printf ("\n");

    for (int i = 0; i < rows; i++){
        printf ("%d ", i + 1);
        for (int j = 0; j < columns; j++){
            printf ("%c ", data[i][j]);
        }
        printf ("\n");
    }
    printf("\n");
}

int Flight::getId() const{
    return id;
}
int Flight::getRows() const{
    return rows;
}
int Flight::getColumns() const{
    return columns;
}
int Flight::getFreeSeats() const{
    return freeSeats;
}
int* Flight::getResCodes(int &sz) const{
    sz = resNo;
    int *temp = sz ? (new int [sz]) : NULL;
    for (int i = 0; i < sz; i++)
        temp[i] = resCodes[i];

    return temp;
}

void Flight::setId(int a_id){
    id = a_id;
}
void Flight::setRows(int a_rows){
    rows = a_rows;
}
void Flight::setColumns(int a_columns){
    columns = a_columns;
}
void Flight::setFreeSeats(int a_freeSeats){
    freeSeats = a_freeSeats;
}
