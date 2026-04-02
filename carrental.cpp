#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <stdexcept> // For exception handling
#include "car.h"
#include "customer.h"
using namespace std;

Cars car;
Lease_info lease;

void login();
// First output
void Menu()
{
    int num = 1;
    for (int i = 0; i < 9; ++i)
    {
        cout << "\t\t\t";
        cout << "Enter " << num << "\t- To Select  " << car.company[i] << endl;
        num++;
    }
}

// Second output
void Details(int Choice)
{
    system("CLS");
    cout << "\n\n\n\t\t\t-----------------------------\n";
    cout << "\t\t\tYou Have Selected - " << car.company[Choice - 1] << endl;
    cout << "\t\t\t-----------------------------\n\n\n";
    cout << "\t\t\tModel : " << car.model[Choice - 1] << endl;
    cout << "\t\t\tColor : " << car.color[Choice - 1] << endl;
    cout << "\t\t\tMaximum Speed : " << car.max_speed[Choice - 1] << endl;
    cout << "\t\t\tPrice : " << car.price[Choice - 1] << endl;
}

// Check lease credit
void checklease(int k, string name, string id, int payment)
{
    try
    {
        if (lease.payment_acc[k] < car.price[k])
        {
            // Throw exception if payment is insufficient
            throw runtime_error("Payment is less than the car price!");
        }

        cout << "\n\n\n\t\t\tProcess has been done successfully!! " << endl;
        ofstream invoice(id + "_" + name + ".txt");

        if (!invoice)
        {
            // Throw exception if the file can't be opened
            throw runtime_error("Error generating invoice file.");
        }

        invoice << "Customer Name : " << name << endl;
        invoice << "Customer National ID : " << id << endl;
        invoice << "Car Name : " << car.company[k] << endl;
        invoice << "Car Model : " << car.model[k] << endl;
        invoice << "Car Color : " << car.color[k] << endl;
        invoice << "Car  Price : " << payment << endl;
        invoice.close();
    }
    catch (const exception &e)
    {
        cout << "\n\n\n\t\t\tException occurred: " << e.what() << endl;
    }
}

// User Input
void user_input(int theChoice)
{
    system("CLS");
    int j = theChoice - 1;
    cout << "\t\t\t----------------------------------------\n";
    cout << "\t\t\tPlease Provide Your Personal Details  : \n";
    cout << "\t\t\t----------------------------------------\n\n";
    cout << "\n\tNOTE: PROVIDE FIRST NAME ONLY, DO NOT ENTER SPACE WHILE PROVIDING NAME,\n\tPAYMENT WON'T PROCEED IF THE GIVEN AMOUNT IS LESS THAN THE RATE OF CAR\n\n\n\n";

    try
    {
        cout << "\t\t\tEnter Your Name : ";
        cin >> lease.Name[100];

        cout << "\t\t\tEnter Your National ID : ";
        cin >> lease.Natio_ID[j];

        cout << "\t\t\tPayment Amount: ";
        cin >> lease.payment_acc[j];

        // Check if the payment entered is a valid positive integer
        if (lease.payment_acc[j] < 0)
        {
            throw invalid_argument("Invalid payment amount! Must be a positive number.");
        }

        // Call checklease function
        checklease(j, lease.Name[100], lease.Natio_ID[j], lease.payment_acc[j]);
    }
    catch (const exception &e)
    {
        cout << "\n\n\n\t\t\tException occurred: " << e.what() << endl;
    }
}

int main()
{
    try
    {
        login();

        string decide = "yes";
        cout << "\t\t\t----------------------------------------------\n";
        cout << "\t\t\t\tOOC SIMPLE CAR RENTAL SYSTEM \n";
        cout << "\t\t\tWelcome to Our Company ,Choose from the menu : " << endl;
        cout << "\t\t\t----------------------------------------------\n";

        while (decide != "exit")
        {
            Menu();

            cout << "\n\n\n\t\t\tYour Choice: ";
            int theChoice;
            cin >> theChoice;

            // Handle invalid car choice input (out of range)
            if (theChoice < 1 || theChoice > 9)
            {
                throw out_of_range("Invalid car selection! Please choose a number between 1 and 9.");
            }

            Details(theChoice);

            cout << "\n\n\n\t\t\tAre You Sure, you want to rent this Car? (yes /no /exit ) : ";
            cin >> decide;

            if (decide == "yes")
            {
                user_input(theChoice);
                cout << "\n\n\t\t\tDo you want to continue ?(yes/no) ";
                cin >> decide;
                if (decide == "no")
                    break;

                system("CLS");
            }
            else if (decide == "no")
            {
                system("CLS");
                continue;
            }
            else if (decide == "exit")
            {
                system("CLS");
                break;
            }
        }
    }
    catch (const exception &e)
    {
        cout << "\n\n\n\t\t\tException occurred: " << e.what() << endl;
    }

    getch();
    return 0;
}

// Login function
void login()
{
    string pass = "";
    char ch;
    cout << "\n\n\n\n\n\n\n\t\t\t\t\t  Sunshine Car Rental System Login";
    cout << "\n\n\n\n\n\n\n\t\t\t\t\t\tEnter Password: ";
    ch = _getch();
    while (ch != 13)
    { // character 13 is enter
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    if (pass == "pass")
    {
        cout << "\n\n\n\n\t\t\t\t\t  Access Granted! Welcome To Our System \n\n";
        system("PAUSE");
        system("CLS");
    }
    else
    {
        cout << "\n\n\n\n\t\t\t\t\tAccess Aborted...Please Try Again!!\n";
        system("PAUSE");
        system("CLS");
        login();
    }
}
