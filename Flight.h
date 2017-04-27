#pragma once

/*
Name: Solehjon Ruziboev
ID:   21500283
*/

class Flight{
    public:
        Flight ();
        Flight (int a_id, int a_rows, int a_columns);

        //copy constructor
        Flight (const Flight &x);

        //overloaded assignment operator
        void operator= (const Flight &right);

        ~Flight();

        bool isFree(int a_row, char char_column);

        bool reserve(int a_row, char char_column);

        void freeSeat(int a_row, char char_column);

        void addReservation(int code);
        void cancelReservation(int code);

        bool isCodePresent (int code);

        void display();

        int getId() const;
        int getRows() const;
        int getColumns() const;
        int getFreeSeats() const;
        int *getResCodes(int &sz) const;

        void setId(int a_id);
        void setRows(int a_rows);
        void setColumns(int a_columns);
        void setFreeSeats(int a_freeSeats);

    private:
        int id, rows, columns, freeSeats, resNo;
        int *resCodes;
        char **data;
};

