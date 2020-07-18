#include <bits/stdc++.h>
#include <conio.h>
#include <string>

using namespace std;

const int FirstRoom=81;
const int LastRoom = 581;

bool RoomOccupied[LastRoom];
int guestCount = 0;
char Continue;

struct Guest
{
    string name;
    int startDate;
    int startMonth;
    int endDate;
    int endMonth;
    string address;
    int age;
    int RoomNo;
};

queue<Guest> Guests;

void swap(Guest *a, Guest *b)
{
    Guest t = *a;
    *a = *b;
    *b = t;
}

int partition(Guest arr[], int low, int high, int choice)
{
    int pivotInt = arr[high].RoomNo;
    string pivotStr = arr[high].name;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (choice == 1)
        {
            if (arr[j].RoomNo < pivotInt)
            {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        else if (choice == 0)
        {

            if (arr[j].name.compare(pivotStr) < 0)
            {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Guest arr[], int low, int high, int choice)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, choice);
        quickSort(arr, low, pi - 1, choice);
        quickSort(arr, pi + 1, high, choice);
    }
}

int binarySearch(Guest arr[], int n, int roomNo, string x, int choice)
{
    int l = 0;
    int r = n - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;

        int res;
        int compare = x.compare(arr[m].name);

        if ((compare == 0 && choice == 0) || (roomNo == arr[m].RoomNo && choice == 1))
            res = 0;

        if (res == 0)
            return m;

        if ((compare > 0 && choice == 0) || (roomNo > arr[m].RoomNo && choice == 1))
            l = m + 1;

        else
            r = m - 1;
    }

    return -1;
}

void InitializeRooms()
{
    for (int i = FirstRoom; i < LastRoom; i++)
    {
        RoomOccupied[i] = false;
    }
}

int calcDate(int day, int month)
{
    return 100 * month + day;
}

void filter(int date, int month)
{
    while (!Guests.empty())
    {
        if (calcDate(Guests.front().endDate, Guests.front().endMonth) < calcDate(date, month))
        {
            RoomOccupied[Guests.front().RoomNo] = false;
            guestCount -= 1;
            Guests.pop();
        }
        else
            break;
    }
}

void checkIn()
{
    Guest newGuest;
    string name;
    int startDate;
    int startMonth;
    int endDate;
    int endMonth;
    string address;
    int age;
    int RoomNo;

    cout << "Please enter the following data with regards to the guest details" << endl;
    cout << endl;

    cout << "Enter Guest Name -> ";
    getline(cin >> ws, name);

    cout << "Enter guest check in date (dd mm)-> ";
    cin >> startDate >> startMonth;
    if (startDate > 31 || startDate < 1 || startMonth > 12 || startMonth < 1)
    {
        do
        {
            cout << "Please enter a valid date" << endl;
            cout << "Enter date again -> ";
            cin >> startDate >> startMonth;
        } while (startDate > 31 || startDate < 1 || startMonth > 12 || startMonth < 1);
    }

    cout << "Enter guest release date (dd mm) -> ";
    cin >> endDate >> endMonth;
    if (endDate > 31 || endDate < 1 || endMonth > 12 || endMonth < 1 || (endMonth < startMonth) || (endDate < startDate && endMonth <= startMonth))
    {
        do
        {
            cout << "Please enter a valid date" << endl;
            cout << "Enter date again -> ";
            cin >> endDate >> endMonth;
        } while (endDate > 31 || endDate < 1 || endMonth > 12 || endMonth < 1 || (endMonth < startMonth) || (endDate < startDate && endMonth <= startMonth));
    }
    cout << "Enter Guest Address -> ";
    getline(cin >> ws, address);

    cout << "Enter guest age -> ";
    cin >> age;

    cout << "Please choose a room from the following list of unoccupied rooms -> ";

    int count = 0;
    for (int i = FirstRoom; i < LastRoom && count < 10; i++)
    {
        if (!RoomOccupied[i])
        {
            cout << i << " ";
            count += 1;
        }
    }
    cout << endl;
    cout << "Enter the Room Number --> ";
    cin >> RoomNo;
    if (RoomOccupied[RoomNo] || RoomNo < 81 || RoomNo > 580)
    {
        do
        {
            cout << "This Room is not available. Please enter a Room Number again ->";
            cin >> RoomNo;
        } while (RoomOccupied[RoomNo]);
    }

    newGuest.name = name;
    newGuest.startDate = startDate;
    newGuest.startMonth = startMonth;
    newGuest.endDate = endDate;
    newGuest.endMonth = endMonth;
    newGuest.address = address;
    newGuest.age = age;
    newGuest.RoomNo = RoomNo;

    RoomOccupied[RoomNo] = true;

    Guests.push(newGuest);
    cout << endl;
    cout << "The guest " << name << " was succesfully checked in" << endl;
    cout << endl;

    guestCount += 1;
    cout << "##########################################################" << endl;
    cout << endl;
}

void sortGuests()
{
    int n = Guests.size();
    Guest GuestsArray[n];
    for (int i = 0; i < n; i++)
    {
        GuestsArray[i] = Guests.front();
        Guests.pop();
    }

    int choice;
    cout << "Enter 0 if you want to sort on the basis of name" << endl;
    cout << "Enter 1 if you want to sort on the basis of Room No" << endl;
    cout << endl;
    cout << "Enter your choice here-> ";
    cin >> choice;
    quickSort(GuestsArray, 0, n - 1, choice);
    cout << endl;

    char info;
    bool showname = true, showDates = true, showAddress = true, showRoomNo = true, showAge = true;
    cout << "Would you like to see all information about the guests? (y/n) -> ";
    cin >> info;
    cout << endl;
    if (info == 'n')
    {
        cout << "Enter the information youd like to display(y/n) " << endl;

        cout << "name -> ";
        cin >> info;
        if (info == 'n')
            showname = false;

        cout << "Room No -> ";
        cin >> info;
        if (info == 'n')
            showRoomNo = false;

        cout << "Check in and Check out Dates ->";
        cin >> info;
        if (info == 'n')
            showDates = false;

        cout << "Address -> ";
        cin >> info;
        if (info == 'n')
            showAddress = false;

        cout << "Age -> ";
        cin >> info;
        if (info == 'n')
            showAge = false;
    }

    cout << "The sorted list is " << endl;
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        if (showname)
            cout << "name: " << GuestsArray[i].name << endl;
        if (showRoomNo)
            cout << "Room No: " << GuestsArray[i].RoomNo << endl;
        if (showDates)
        {
            cout << "Check in: " << GuestsArray[i].startDate << " / " << GuestsArray[i].startMonth << endl;
            cout << "Check Out:  " << GuestsArray[i].endDate << " / " << GuestsArray[i].endMonth << endl;
        }
        if (showAddress)
            cout << "Address: " << GuestsArray[i].address << endl;
        if (showAge)
            cout << "Age: " << GuestsArray[i].age << endl;
        cout << endl;
    }
    cout << "##########################################################" << endl;
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        Guests.push(GuestsArray[i]);
    }
}

void searchGuest()
{
    int n = Guests.size();
    Guest GuestsArray[n];
    for (int i = 0; i < n; i++)
    {
        GuestsArray[i] = Guests.front();
        Guests.pop();
    }

    int result;
    cout << "Enter 0 if you want to search on the basis of name " << endl;
    cout << "Enter 1 if you want to search on the basis of Room No " << endl;
    int choice;
    cout << "Enter your choice here -> ";
    cin >> choice;
    cout << endl;
    quickSort(GuestsArray, 0, n - 1, choice);
    if (choice == 0)
    {
        string name;
        cout << "Enter the name you want to search-> ";
        getline(cin >> ws, name);
        cout << endl;
        result = binarySearch(GuestsArray, n, 0, name, choice);
        if (result == -1)
        {
            cout << "No such person exists in the system " << endl;
        }
        else
        {
            cout << "Your requested details are -> " << endl;
            cout << endl;
            cout << "Name : " << GuestsArray[result].name << endl;
            cout << "Room no : " << GuestsArray[result].RoomNo << endl;
            cout << "Check in date : " << GuestsArray[result].startDate << "/" << GuestsArray[result].startMonth << endl;
            cout << "Release date : " << GuestsArray[result].endDate << "/" << GuestsArray[result].endMonth << endl;
            cout << "Address : " << GuestsArray[result].address << endl;
            cout << "Age : " << GuestsArray[result].age << endl;
        }
    }
    else if (choice == 1)
    {
        int roomNo;
        cout << "Enter the Room no you want to search -> ";
        cin >> roomNo;
        cout << endl;
        result = binarySearch(GuestsArray, n, roomNo, "", choice);
        if (result == -1)
        {
            cout << "This Room has not been alloted to anyone " << endl;
        }
        else
        {
            cout << "Your requested details are -> " << endl;
            cout << endl;
            cout << "Name : " << GuestsArray[result].name << endl;
            cout << "Room no : " << GuestsArray[result].RoomNo << endl;
            cout << "Check in date : " << GuestsArray[result].startDate << "/" << GuestsArray[result].startMonth << endl;
            cout << "Release date : " << GuestsArray[result].endDate << "/" << GuestsArray[result].endMonth << endl;
            cout << "Address : " << GuestsArray[result].address << endl;
            cout << "Age : " << GuestsArray[result].age << endl;
        }
    }
    cout << endl;
    cout << "##########################################################" << endl;
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        Guests.push(GuestsArray[i]);
    }
}

void displayRooms()
{
    cout << "Currently " << guestCount << " rooms are occupied and " << 500 - guestCount << " rooms are availabele " << endl;
    cout << endl;
    cout << "The occupied rooms are " << endl;
    for (int i = FirstRoom; i < LastRoom; i++)
    {
        if (RoomOccupied[i])
            cout << i << " ";
    }
    cout << endl;

    cout << "The unoccupied rooms are " << endl;

    for (int i = FirstRoom; i < LastRoom; i++)
    {
        if (!RoomOccupied[i])
            cout << i << " ";

        if (i % 20 == 0)
            cout << endl;
    }
    cout << endl;
    cout << "##########################################################" << endl;
    cout << endl;
}
void Display()
{
    bool end = false;
    int day;
    int month;
    int password;
    int userpass;
    password = 12345678;
    string username;
    string ramesh;
    username = ramesh;
    string vername;
    

    cout << "Enter today's date (dd mm) --> ";
    cin >> day >> month;
    if (day > 31 || day < 1 || month > 12 || month < 1)
    {
        do
        {
            cout << "Please enter a valid date" << endl;
            cout << "Enter date again -> ";
            cin >> day >> month;
        } while (day > 31 || day < 1 || month > 12 || month < 1);
    }
    cout << endl;
    filter(day, month);

    cout << "Please choose among the following options" << endl;
    cout << endl;
    cout << "1. Check in a New Guest" << endl;
    cout << "2. Sort The Guest List" << endl;
    cout << "3. Search for a guest" << endl;
    cout << "4. Display vacant and Occupied rooms" << endl;
    cout << "5. Exit the portal" << endl;
    cout << endl;
    cout << "Enter your choice here --> ";
    int choice;
    cin >> choice;
    cout << endl;
    if (choice == 1)
    {
        if (guestCount < 500)
            checkIn();
        else
            cout << "There are no more empty rooms" << endl;
    }
    else if (choice == 2)
    {
        sortGuests();
    }
    else if (choice == 3)
    {
        cout << "Enter username:";
        cin >> vername;
        cout << endl;
        cout << "Enter password:";
        cin >> userpass;
        cout << endl;
        if (vername == username && userpass == password)
        {
            searchGuest();
        }
    }
    else if (choice == 4)
    {
        displayRooms();
    }
    else if (choice == 5)
    {
        cout << "Are you sure you want to exit? (y/n)" << endl;
        char confirmation;
        cin >> confirmation;
        if (confirmation == 'y')
        {
            cout << "Thank you for using the portal " << endl;
            end = true;
        }
    }
    else
    {
        cout << "INVALID INPUT" << endl;
    }

    if (!end)
        Display();
}

int main()
{
    cout << "###########################################################" << endl;
    cout << endl;
    cout << "WELCOME TO THE NIT SILCHAR QUARANTINE FACILITY PORTAL" << endl;
    cout << endl;
    cout << "###########################################################" << endl;
    cout << endl;

    InitializeRooms();    
    Display();
}
