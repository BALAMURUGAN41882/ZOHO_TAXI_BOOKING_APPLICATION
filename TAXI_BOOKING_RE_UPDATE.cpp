#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstdlib>
#include<string>
using namespace std;

struct raidDetails
{
    int custID;
    int taxiNo;
    int startTime;
    int endTime;
    char startLocation;
    char endLocation;
    int fair;
};

class Taxi
{
    private:
        int taxiNo;
        int totalFair;
        char startLocation;
        static int taxiIdGenerate ;
        static int taxino;
    public:
        vector <raidDetails> raidInfo;
    public:
        Taxi()
        {
            cout<<endl<<"Taxi: "<<taxino++<<" is there"<<endl;
            taxiNo = taxiIdGenerate++;
            totalFair = 0;
            startLocation = 'A';
        }
        void updateStatus(struct raidDetails & rd)
        {
            raidInfo.push_back(rd);
            totalFair += rd.fair;
        }
        void getDetails()
        {
            cout<<"Taxi Number              : "<<taxiNo<<endl;
            cout<<"Total Fair Collected     : "<<totalFair<<endl;
            if(!raidInfo.empty())
            {
                cout<<endl<<"Raid Details : "<<endl;
                for(int i = 0; i < raidInfo.size(); i++)
                {

                    cout<< i+1 << ". Customer-" << raidInfo[i].custID << " have raid from " << raidInfo[i].startLocation << " to " <<raidInfo[i].endLocation ;
                    cout<<" between "<< (raidInfo[i].startTime)/60 << ":" << (raidInfo[i].startTime)%60 <<" and "<< (raidInfo[i].endTime)/60 << ":" << (raidInfo[i].endTime)%60;
                    cout<<" with total fair of "<<raidInfo[i].fair << endl;
                }
            }
        }
        int getTotalFair()
        {
            return totalFair;
        }
        int getTaxiNo()
        {
            return taxiNo;
        }

        void checkCustomer(int id)
        {
            for(raidDetails r : raidInfo)//raid info is a structure name and r is raidinfo object
                if(r.custID == id)
                    cout<<"Customer-" << r.custID << " have raid from " << r.startLocation << " to " <<r.endLocation << " between "<< (r.startTime)/60 << ":" << (r.startTime)%60 <<" and "<< (r.endTime)/60 << ":" << (r.endTime)%60 <<" with total fair of "<<r.fair<<endl;
        }
};

class Customer
{
    private:
        int customerID;
        raidDetails r;// r object can't access outside the class becoz  it is private
        static int customerIdGenerate;
    public:
        Customer()
        {
            int hr, min;
            char ch;
            customerID = customerIdGenerate++;
            cout<<"Enter Your Starting and End Point : ";
            cin>>r.startLocation>>r.endLocation;
            cout<<"Enter Your Starting Time : ";
            cin>>hr>>ch>>min;
            r.startTime = (hr * 60) + min;
            r.endTime = r.startTime + abs(r.startLocation - r.endLocation) * 15;
        }

        int bookTaxi(Taxi availTaxi[], int no_of_taxi)
        {
            int curTaxiIndex = -1;
            int minDistance = INT_MAX;
            int curTaxiFair = INT_MAX;
            for(int i = 0; i < no_of_taxi; i++)
            {
                int canSet = 1;
                int curDistance = r.startLocation - 65; //distance to travel
                for(raidDetails taxiRaid : availTaxi[i].raidInfo) //RAID INFO IS A VECTOR
                {
                    cout<<"TAXI "<<i+1<<" CHECK"<<"  ";
                    if(r.endTime <= taxiRaid.startTime)
                    {
                        curDistance = 0;
                    }
                    else if(r.startTime >=taxiRaid.endTime)
                        curDistance = abs(r.startLocation - taxiRaid.endLocation);
                    else
                        canSet = 0;
                }

                if(canSet && curDistance <= minDistance && curTaxiFair > availTaxi[i].getTotalFair()) //canset is may o or 1
                {
                    curTaxiIndex = i;
                    minDistance = curDistance;
                    curTaxiFair = availTaxi[i].getTotalFair();
                }
            }
            if(curTaxiIndex != -1)
            {
                r.custID = customerID;
                r.taxiNo = availTaxi[curTaxiIndex].getTaxiNo();
                r.fair =  abs(r.startLocation - r.endLocation) * 15;
                availTaxi[curTaxiIndex].updateStatus(r);
                return 1;
            }
            return 0;
        }
};
int Taxi::taxiIdGenerate=1;
int Customer::customerIdGenerate=1;
int Taxi::taxino=1;


int main()
{
    int no_of_taxi;
    int ch;
    cout<<"------------- ZOHO TAXI BOOKING APPLICATION --------------"<<endl;
    cout<<"Enter No of Taxi : ";
    cin>>no_of_taxi;
    Taxi taxi[no_of_taxi];

    while(1)
    {
        cout<<"\nBooking Templates: \n1. Book Taxi\n2. Get Taxi Details\n3. Track Customer\n4. Exit\n\nEnter Choice : ";
        cin>>ch;
        if(ch == 1)
        {
            Customer c;
            if(c.bookTaxi(taxi , no_of_taxi))
                cout<<endl<<"Taxi Booked Success Fully..."<<endl;
            else
                cout<<"Sorry... Taxi Not Available..."<<endl;
        }
        else if(ch == 2)
        {
            for(int i = 0; i < no_of_taxi; i++)
                taxi[i].getDetails();
        }
        else if(ch == 3)
        {
            int user;
            cout<<"Enter Customer ID : ";
            cin>>user;
            for(int i = 0; i < no_of_taxi; i++)
                taxi[i].checkCustomer(user);
        }
        else
            break;
        cout<<endl;
    }

    return 0;
}
