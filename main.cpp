#include<dos.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<process.h>
using namespace std;

//Class for handling data of each entry. 
class car_resale
{
    private:
        char model[50]; //Model Name
        float price; //Car Price
        int use; //Years in use
        float dist; //Distance used for
        long idno; //VIN number for tracking
    public:
        void get(); 
        void show();
        long retno();
};

//Function to get data from the user.
void car_resale::get()
{
    cout<<"Enter car model: "; gets(model);
    cout<<"Enter VIN number: "; cin>>idno;
    cout<<"How much do you want to sell your vehicle for?"; cin>>price;
    cout<<"How many years has the vehicle been in use?"; cin>>use;
    cout<<"Approximate usage of vehicle? (in kilometers)"; cin>>dist;
}

//Function to show the data of a specific entry or all entries.
void car_resale::show()
{
    cout<<"\n\nCar model: "; puts(model);
    cout<<"VIN number: "<<idno;
    cout<<"\nPrice: "<<price;
    cout<<"\nUsage: "<<use;
    cout<<"\nDriven for(in kilometers): "<<dist;
}

//Function to return the VIN number for tracking.
long car_resale::retno()
{
    return idno;
}

//Driver Program
int main()
{
    system("clear"); 
    //Welcome screen
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"*******************************************************************************";
    cout<<endl;
    cout<<"                       WELCOME TO FPCS CAR SALES                       ";
    cout<<endl<<"*******************************************************************************";
    _sleep(3000);
    system("clear");
    //Data entry
    ofstream f1; car_resale a; int n, ch; char ch1;
    f1.open("car.dat", ios::out|ios::binary);
    cout<<"\nHow many records do you wish to store? "; cin>>n;
    for(int i=0; i<n; i++)
    {
        a.get();
        f1.write((char*)&a,sizeof(a));
    }
    f1.close();
    //Menu-driven program
    do
    {
        system("clear");
        cout<<"\nOption 1: Append";
        cout<<"\nOption 2: Modify";
        cout<<"\nOption 3: Search";
        cout<<"\nOption 4: Delete";
        cout<<"\nOption 5: Display";
        cout<<"\nOption 6: Exit";
        cout<<"\nEnter your choice: "; cin>>ch;
        switch(ch)
        {
            case 1: //Takes a single entry from the user and appends into the file.
            {
                f1.open("car.dat",ios::app|ios::binary);
                a.get();
                f1.write((char*)&a,sizeof(a));
                f1.close();
                break;
            }
            case 2: //Searches for a specific entry and rewrites it. 
            {
                ofstream f2;
                f2.open("car.dat", ios::out|ios::ate|ios::binary);
                int n1;
                cout<<"\nEnter the record which has to be modified: "; cin>>n1;
                int x=(n1-1)*sizeof(a);
                f2.seekp(x,ios::beg);
                a.get();
                f2.write((char*)&a,sizeof(a));
                f2.close();
                break;
            }
            case 3: //Searches for a specific entry and shows its details.
            {
                ifstream f3; int flag=0;
                f3.open("car.dat",ios::in|ios::binary);
                f3.seekg(0,ios::beg);
                long id;
                cout<<"\nEnter VIN number: "; cin>>id;
                while(f3.read((char*)&a,sizeof(a)))
                {
                    if(a.retno()==id)
                    {
                        a.show();
                        flag=1;
                    }
                }
                if(flag==0)
                    cout<<"\nID number not found. SORRY!";
                f3.close();
                break;
            }
            case 4: //Copies all data to a new file except the selected record. Deletes the old file.
            {
                ofstream f41; ifstream f42; long c;
                f42.open("car.dat",ios::in|ios::binary);
                f41.open("newcar.dat",ios::out|ios::app|ios::binary);
                f42.seekg(0,ios::beg);
                cout<<"\nEnter vin number: "; cin>>c;
                while(f42.read((char*)&a,sizeof(a)))
                {
                    if(c!=a.retno())
                    f41.write((char*)&a,sizeof(a));
                }
                remove("car.dat"); rename("newcar.dat","car.dat");
                f41.close(); f42.close();
                break;
            }
            case 5: //displays all data in the file. 
            {
                ifstream f5;
                f5.open("car.dat",ios::in|ios::binary);
                f5.seekg(0,ios::beg);
                while(f5.read((char*)&a,sizeof(a)))
                    a.show();
                f5.close();
                break;
            }
            case 6: //Exits the program. Shows a Thank You slide. 
            {
                system("clear");
                cout<<"_*_*_*_*_*_*_*_*_**_*_*_*_*_*_*_*_*_*_*_*_*_*_*_**_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*";
                cout<<"                               ************************************";
                cout<<"\n                          *      Thank you for using FPCS!!            *           ";
                cout<<"                               ************************************";
                cout<<"_*_*_*_*_*_*_*_*_**_*_*_*_*_*_*_*_*_*_*_*_*_*_*_**_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*";
                _sleep(3000);
                exit(0);
            }
        }
        cout<<"\nDo you wish to continue? "; cin>>ch1; 
    }
    while(ch1=='Y'||ch1=='y');
    return 0;
}