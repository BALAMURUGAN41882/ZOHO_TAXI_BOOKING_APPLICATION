#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstdlib>
#include<string>
using namespace std;

class Taxi
{

public:

    static int tNo;
    int taxiNo;
    char curLocation;
    int totalFair;
    int endTime;
    vector <string> raidDetails;

    Taxi()
    {
        taxiNo = tNo++;
        curLocation = 'A';
        endTime = 0;
        totalFair = 0;
    }

    void updateStatus(char curLocation, int fair, int endTime, string s)
    {
        this->curLocation = curLocation;
        totalFair += fair;
        this->endTime = endTime;
        raidDetails.push_back(s);
    }

    void getDetails()
    {
        cout<<endl;
        cout<<"Taxi Number              : "<<taxiNo<<endl;
        cout<<"    Total Fair Collected : "<<totalFair<<endl;
        cout<<"    Raid Details         : "<<endl;
        for(string s : raidDetails)
            cout<<"        "<<s<<endl;
    }

    void curStatus()
    {
        cout<<"Taxi Number          : "<<taxiNo<<endl;
        cout<<"Total Fair Collected : "<<totalFair<<endl;
        cout<<"Current Location     : "<<curLocation<<endl;
        cout<<"End Time             : "<<endTime<<endl;
        cout<<"Raid Details         : "<<endl;
        for(string s : raidDetails)
            cout<<"        "<<s<<endl;
    }
};

class Customer
{
public:
    int cID;
    int mappedTaxi;
    int raidFair;
    char startPoint;
    char endPoint;
    int startTime;
    int endTime;
    static int crefid;//default is 0
    string s;

    void getRaidDetails(Taxi freeTaxi[], int  n)
    {
        int hr,min;
        char temp;
        cID = crefid++;
        mappedTaxi = 0;
        cout<<"Enter starting location and end location : ";
        cin>>startPoint>>endPoint;
        cout<<"Enter Starting Time (hh:mm) : ";
        cin>>hr>>temp>>min;
        startTime = hr * 60 + min;
        int minDistance = 10000;// INTMAX

        int curFair = 0;//current amount
        //----------------------------------------------------------------------------------------------
        int raidDistance = abs(endPoint - startPoint);
        for(int i = 0; i < n; i++)
        {
            int distance = abs(freeTaxi[i].curLocation - startPoint);
            if(distance < minDistance && freeTaxi[i].endTime <= startTime)
            {
                mappedTaxi = freeTaxi[i].taxiNo;//freetaxi is object of Taxi class we can access instance and methods in taxi calss through object
                minDistance = abs(freeTaxi[i].curLocation - startPoint);
                curFair = freeTaxi[i].totalFair;
            }
            else if(distance == minDistance && freeTaxi[i].totalFair < curFair )
            {
                mappedTaxi = freeTaxi[i].taxiNo;
                minDistance = abs(freeTaxi[i].curLocation - startPoint);
                curFair = freeTaxi[i].totalFair;
            }
        }
        //------------------------------------------------------------------------------------------------
        if(mappedTaxi == 0)
        {
            cout<<"No taxi available..."<<endl;
            crefid--;
            return;
        }
        endTime = startTime + raidDistance * 15;
        raidFair = raidDistance * 15;

        for(int i = 0; i < n; i++)
        {
            if(freeTaxi[i].taxiNo == mappedTaxi)
            {
                s = "Customer "+to_string(cID)+" have raid from "+startPoint+" to "+endPoint+" between "+to_string(startTime/60) +":"+to_string(startTime%60)+" and "+to_string(endTime/60) +":"+to_string(endTime%60)+" with cost of "+to_string(raidFair);
                freeTaxi[i].updateStatus(endPoint, raidFair, endTime, s);
                cout<<endl<<"----  Taxi Booked Sucessfully ----"<<endl;
            }
        }
    }
};

int Taxi::tNo = 1;
int Customer::crefid = 1;

int main()
{
    int taxiCount;
    cout<<"Enter Taxi Count : ";
    cin>>taxiCount;
    Taxi t[taxiCount];//object array for taxi it contains n number of objects
    unordered_map<int, string> cDetails;
    int ch = 1;
    while(1)
    {
        cout<<"\nBooking Templates: \n1. Book Taxi\n2. Get Taxi Details\n3. Track My Taxi\n4. Search for Customer\n5. Exit\n\nEnter Choice : ";
        cin>>ch;
        if(ch == 1)
        {
            Customer c; //object for customer
            c.getRaidDetails(t,taxiCount);//we pass two parameters for getraiddetails (object array, n)
            cDetails[c.cID] = c.s;
        }
        else if(ch == 2)
        {
            for(Taxi tax : t)
                tax.getDetails();
        }
        else if(ch == 3)
        {
            int tn;
            cout<<"Enter Taxi Number : ";
            cin>>tn;
            for(Taxi tax : t)
                if(tax.taxiNo == tn)
                    tax.curStatus();
        }
        else if(ch == 4)
        {
            int cn;
            cout<<"Enter Customer Number : ";
            cin>>cn;
            if(cDetails.find(cn) != cDetails.end())
                cout<<cDetails[cn]<<endl;
            else
                cout<<"Not Found..."<<endl;
        }
        else
            break;
    }
    return 0;
}
