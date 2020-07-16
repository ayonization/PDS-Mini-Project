#include<bits/stdc++.h>
using namespace std;

const int MaxRooms=581;
bool RoomOccupied[MaxRooms];

struct Guest
{
    string name;
     int startDate;
    int endDate;
     string address;
     int age;
    int RoomNo;
};

queue<Guest> Guests;

void swap(Guest* a, Guest* b)  
{  
    Guest t = *a;  
    *a = *b;  
    *b = t;  
}  
  
int partition (Guest arr[], int low, int high)  
{  
    int pivot = arr[high].RoomNo;  
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++)  
    {  
          
        if (arr[j].RoomNo < pivot)  
        {  
            i++;  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
  

void quickSort(Guest arr[], int low, int high)  
{  
    if (low < high)  
    {  
        int pi = partition(arr, low, high);  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  



void filter(int date)
{
    while(!Guests.empty())
    {
        if(Guests.front().endDate<date) Guests.pop();
        else break;
    }
}


void checkIn()
{   
    Guest newGuest;
    string name;
     int startDate;
    int endDate;
     string address;
     int age;
    int RoomNo;

    
    cout<<"Please enter the following data with regards to the guest details"<<endl;
    cout<<"Enter Guest name"<<endl;
    cin>>name;
     cout<<"Enter todays date"<<endl;
     cin>>startDate;
    cout<<"Enter guest release date"<<endl;
    cin>>endDate;
     cout<<"Enter Guest Address"<<endl;
     cin>>address;
     cout<<"Enter guest age"<<endl;
     cin>>age;
    cout<<"Please choose a room from the following list of unoccupied rooms"<<endl;
    EmptyRooms();
    cin>>RoomNo;

    newGuest.name=name;
    newGuest.startDate=startDate;
    newGuest.endDate=endDate;
    newGuest.address=address;
    newGuest.age=age;
    newGuest.RoomNo=RoomNo;
    
    RoomOccupied[RoomNo]=true;
    
    Guests.push(newGuest);
    cout<<"The guest"<<name<<"was succesfully checked in"<<endl;

}

void sortGuests()
{   
    int n=Guests.size();
    Guest GuestsArray[n];
    for (int i = 0; i < n; i++)
    {
        GuestsArray[i]=Guests.front();
        Guests.pop();
    }
    
    quickSort(GuestsArray,0,n-1);
    
    cout<<"The sorted list of room nos with the persons occupying them is "<<endl;

    for (int i = 0; i < n; i++)
    {
        cout<<GuestsArray[i].RoomNo<<" "<<GuestsArray[i].name<<endl;
    }
    

    

    
}


void Display()
{   
    int today;
    cout<<"Enter todays date --> ";
    cin>>today;
    filter(today);
    cout<<"1. Check in a New Guest"<<endl;
    cout<<"2. Sort The Guests according to Room number"<<endl;
    cout<<"3. Search for a guest"<<endl;
    cout<<"4. Display vacant and Occupied rooms"<<endl;
    cout<<"5. Exit the portal"<<endl;
    cout<<"Enter your choice here --> ";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        checkIn();
    }
    else if(choice==2)
    {
        sortGuests();
    }
    else if(choice==3)
    {

    }
    else if(choice==4)
    {
        
    
    }
    else if(choice==5)
    {

    }
    else
    {
        cout<<"INVALID INPUT"<<endl;
    }
    
    Display();
    
}



int main()
{
    
    cout<<"WELCOME TO THE NIT SILCHAR QUARRENTINE FACILITY PORTAL"<<endl;
    cout<<"ENTER THE OPTION CORRESPONDING TO THE ACTION YOU WANT TO PERFORM"<<endl;

        for (int i = 0; i < MaxRooms; i++)
    {
        RoomOccupied[i]=false;
    }


    Display();
}