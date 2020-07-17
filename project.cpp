#include<bits/stdc++.h>
using namespace std;

const int MaxRooms=581;
bool RoomOccupied[MaxRooms];
int guestCount=0;

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
  
int partition (Guest arr[], int low, int high,int property)  
{  
     int pivotInt = arr[high].RoomNo; 
     string pivotStr=arr[high].name; 
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++)  
    {  
        if(property==0)
        {
            if (arr[j].RoomNo < pivotInt)  
            {  
                i++;  
                swap(&arr[i], &arr[j]);  
            }  
        }  
        else if(property==1)
        {
            if(property==0)
        {
            if (arr[j].name < pivotStr)  
            {  
                i++;  
                swap(&arr[i], &arr[j]);  
            }  
        } 
        }
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
  

void quickSort(Guest arr[], int low, int high,int property)  
{  
    if (low < high)  
    {  
        int pi = partition(arr, low, high,property);  
        quickSort(arr, low, pi - 1,property);  
        quickSort(arr, pi + 1, high,property);  
    }  
}  

int binarySearch(Guest arr[], string x,int n) 
    { 
        int l = 0 ; 
        int r = n - 1; 
        while (l <= r)  
        { 
            int m = l + (r - l) / 2; 
  
        int res; 
        if (x == (arr[m].name)) 
            res = 0; 

            if (res == 0) 
                return m;

            if (x > (arr[m].name)) 
                l = m + 1; 

            else
                r = m - 1; 
        } 
  
        return -1; 
    }


void filter(int date)
{
    while(!Guests.empty())
    {
        if(Guests.front().endDate<date) 
        {
            RoomOccupied[Guests.front().RoomNo]=false;
            Guests.pop();
        }
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

        int count=0;
        for(int i=81;i<581 && count<10; i++)
        {
            if(!RoomOccupied[i])
            {
                cout<<i<<" ";
                count+=1;
            }
        }
        cout<<endl;
       cin>>RoomNo;

    newGuest.name=name;
    newGuest.startDate=startDate;
    newGuest.endDate=endDate;
    newGuest.address=address;
    newGuest.age=age;
    newGuest.RoomNo=RoomNo;
    
    RoomOccupied[RoomNo]=true;
    
    Guests.push(newGuest);
    cout<<"The guest "<<name<<" was succesfully checked in"<<endl;

    guestCount+=1;
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
    
    quickSort(GuestsArray,0,n-1,0);
    
    cout<<"The sorted list of room nos with the persons occupying them is "<<endl;
     
    for (int i = 0; i < n; i++)
    {
        cout<<GuestsArray[i].RoomNo<<" "<<GuestsArray[i].name<<endl;
    }
    
    for (int i = 0; i < n; i++)
    {
        Guests.push(GuestsArray[i]);
    }
    
}

void searchGuest()
{
    int n=Guests.size();
    Guest GuestsArray[n];
    for (int i = 0; i < n; i++)
    {
        GuestsArray[i]=Guests.front();
        Guests.pop();
    }

    quickSort(GuestsArray,0,n-1,1);
    string name;
    cout<<"Enter the name of the person you want to search "<<endl;
    cin>>name;
    int result=binarySearch(GuestsArray,name,n);
    if(result==-1)
    {
        cout<<"No such person exists in the system "<<endl;
    }
    else
    {
        cout<<"Name : "<<name<<" ";
        cout<<"Room no : "<<GuestsArray[result].RoomNo<<endl;
    }
    
    for (int i = 0; i < n; i++)
    {
        Guests.push(GuestsArray[i]);
    }
    

}

void displayRooms()
{
    cout<<"Currently "<<guestCount<<" rooms are occupied and "<<500-guestCount<<" rooms are availabele "<<endl;
    cout<<"The occupied rooms are "<<endl;
    for (int i = 81; i < 581; i++)
    {
        if(RoomOccupied[i]) cout<<i<<" ";
    }

    cout<<"The unoccupied rooms are "<<endl;

    for (int i = 81; i < 581; i++)
    {
        if(!RoomOccupied[i]) cout<<i<<" ";

        if(i%20==0) cout<<endl;
    }
    
    
}
void Display()
{   
    bool end=false;
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
        if(guestCount<500) checkIn();
        else cout<<"There are no more empty rooms"<<endl;
    }
    else if(choice==2)
    {
        sortGuests();
    }
    else if(choice==3)
    {
         searchGuest();
    }
    else if(choice==4)
    {
        displayRooms();
    }
    else if(choice==5)
    {
        cout<<"Are you sure you want to exit? (y/n)"<<endl;
        char confirmation;
        cin>>confirmation;
        if(confirmation=='y')
        {
            cout<<"Thank you for using the portal "<<endl;
            end=true;

        }
    }
    else
    {
        cout<<"INVALID INPUT"<<endl;
    }
    
   if(!end) Display();
    
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
