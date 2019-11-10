

#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<cstring>
#include<cstdlib>
#include<time.h>
#include<fstream>
#include<string>
#include<iomanip>  
#include<dir.h>                         

using namespace std;

time_t now,later;
	                                         			
void sleep(int delay)                   
{now=time(NULL);                         
later=now+delay;                            
while(now<=later)                    
now=time(NULL);
}

void vline(char ch)         // border creator
{
  for (int i=80;i>0;i--)
  cout<<ch;
}										// THIS PROGRAM CREATES ITS OWN DIRECTORY FOR ITS TARGET FILES

int status = mkdir("C:\\Database");    // creating target destination


//-------------------------------------------------------------------------------------------------------------------------
                                              // USER INTERFACE                                  
fstream custFile;
fstream tempFile;
fstream fout;
fstream fin;
                                

const int NAME_LEN = 45;
const int ADDR_LEN = 45;
const int CITY_LEN = 20;
const int STATE_LEN = 15;
const int ZIP_LEN = 11;
const int PHONE_LEN = 14;
const int ARRAY_SIZE = 11;

// Structure used to represent customer data 
struct Customer
{
char name [NAME_LEN];                                   // BALANCE WILL GOVERN THE COST
char address [ADDR_LEN];
char city [CITY_LEN];
char state [STATE_LEN];
char zip [ZIP_LEN];
char phone [PHONE_LEN];
double balance;// ON COMPANY CARD,WHICH WILL BE TAKEN. IF NOT ENOUGH FOR ANY ACTION,PROGRAM WILL PROMPT TO ADD MORE. 
double cost;
};

//Prototypes 
void setInfo(long);
void display(long);
long search();
void deleteRec();
void modifyRec();
void showAll();

bool rnew = 0;
bool bnew = 0;
bool fnew = 0;
bool hnew = 0;

bool mod = 0;
bool bmod = 0;
bool fmod = 0;
bool hmod = 0;

// Function definitions

// setInfo *
// Get info for customer record and write to file. *

void setInfo(long fp)
{
Customer c;
Customer x;
int valid;
c.cost=0;
do
{set:
valid = 1;
cout << "\nPlease enter the following information:\n";
cout << "\nCustomer Name: ";
cin.getline(c.name, 45);

custFile.open("C:\\Database\\cust.dat", ios::in | ios::binary);
while (true)
{
custFile.read(reinterpret_cast<char*>(&x), sizeof(Customer)); //Read one record 
if (custFile.fail())
break;
if (strcmpi(c.name,x.name) == 0) // If search value matches customers name..
{cout<<"\n\n\t\t You cannot use that customer name. It already exists.";
sleep(2);
system("cls");
goto set;
}
}
custFile.clear();
custFile.close();

cout << "\nCustomer Address: ";
cin.getline(c.address, 45);
cout << "\nCity: ";
cin.getline(c.city, 20);
cout << "\nState: ";
cin.getline(c.state, 10);
cout << "\nZip: ";
cin.getline(c.zip, 11);
cout << "\nTelephone: ";
cin.getline(c.phone, 14);
cout << "\nAccount Balance: ";
cin >> c.balance;
cin.get();

if (strlen(c.name) ==0 || strlen(c.address) ==0 || strlen(c.city) ==0 || strlen(c.state) ==0 || strlen(c.zip) ==0 )
{
cout << "You must enter infroamtion for each field. \n";
valid = 0;
}
if (c.balance < 0)
{
cout << "Please enter 0 or greater for account balance. \n";
valid = 0;
}
c.balance-=100.0;
c.cost+=100.0;               // REGISTRATION FEES
} while (!valid);

if (rnew)
{
custFile.open("C:\\Database\\cust.dat", ios::out | ios::app | ios ::binary );
}
else if (mod)
{
custFile.open("C:\\Database\\cust.dat", ios::out | ios::app | ios ::binary );
custFile.seekp(fp, ios::beg);
}
if (custFile.fail())
{
cout << "\nError opening file.\n";
return;
}
custFile.write(reinterpret_cast<char*>(&c), sizeof(c));
if (custFile.fail())
{
cout << "\nError writing record to file. \n";
custFile.clear();
custFile.close();
return;
}
custFile.clear();
custFile.close();
system("cls");
cout<<"\n\n\n\n\n\t\t\tAccount successfully recorded.\n";
sleep(1);
system("cls");
return;

}


// Display *
// display record at a given file position. *

void display(long fp)
{
Customer c;
custFile.open("C:\\Database\\cust.dat", ios::in | ios::binary);
if (custFile.fail())
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
if (custFile.peek() == EOF)
{
cout << "\nFile is empty.\n";
custFile.clear();
custFile.close();
return;
}
custFile.seekg(fp, ios::beg);
custFile.read(reinterpret_cast<char*>(&c), sizeof(Customer));

cout.precision(2);
cout.setf(ios::fixed | ios::showpoint);
cout << "Customer Name: " << c.name << endl;
cout << "Customer Address: " << c.address << endl;
cout << "City: " << c.city << endl;
cout << "State: " << c.state << endl;
cout << "Zip: " << c.zip << endl;
cout << "Telephone: " << c.phone << endl;
cout << "Account Balance: " << c.balance << endl;
custFile.clear();
custFile.close();
cout << "\nPress Enter to continue. ";
cin.get();
system("cls");
}


// search
// Returns file pointer position
// of a customer record

long search()
{
char name[45];
Customer c;
long fp=-1;
cout << "\nEnter Valid Customer's Name: ";
cin.ignore();
cin.getline(name, 45);
if (name[0] == '\0') //if nothing is entered do nothing
{
return -1;
}
custFile.open("C:\\Database\\cust.dat", ios::in | ios::binary);
while (true)
{
custFile.read(reinterpret_cast<char*>(&c), sizeof(Customer)); //Read one record 
if (custFile.fail())
break;
if (strcmpi(c.name,name) == 0) // If search value matches customers name..
{
fp = custFile.tellg();
custFile.clear();
custFile.close();
break;
}
}
return (fp - sizeof(c));
//cout << "Record not Found\n";
custFile.clear();
custFile.close();
//return -1;
}

// ShowAll *
// Show records in file *

void showAll()
{
cin.ignore();
Customer c;
int count = 0;
custFile.open("C:\\Database\\cust.dat", ios::in | ios::binary);
if (custFile.fail())
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
cout << "\n***Begin Customer Record***\n\n";

while (custFile.peek()!=EOF)
{
custFile.read(reinterpret_cast<char*>(&c), sizeof(Customer));
cout << setprecision(2);
cout << fixed << showpoint;
cout << "\nRECORD NUMBER " << ++count << ":" << endl;
cout << "\nCustomer name: " << c.name << endl;
cout << "Customer Address: " << c.address << endl;
cout << "City: " << c.city << endl;
cout << "State: " << c.state << endl;
cout << "Zip: " << c.zip << endl;
cout << "Telephone: " << c.phone << endl;
cout << "Account Balance: " << c.balance << endl;
cout << endl<<endl;

}
if (count == 0)
{
cout << "\n		File is empty.\n" << endl;
}
cout << "\n***End of Customer Record Listing***\n\n";
cout<<"     There are "<<count<<" records.\n\n";
sleep(1);
cout << "\nPress Enter to Back To Main. ";
cin.get();
system("cls");
custFile.clear();
custFile.close();
}

void modifyRec()
{   Customer n,x;
    long rpos=0;
    long wpos=0;
    char cname[31];
    int no=0;
    int valid=0;
    double bal=0;
	cout<<" Welcome To Database Updater\n";
	fstream fin;
	fin.open("C:\\Database\\cust.dat", ios::out | ios::in | ios::binary);
	if(!fin)
	{cout<<" Unable to Open Link";
	}
	else
	{     
		  cout<<" Enter Account Name-";
		   cin>>cname;
		  
		
		  
		while(fin)
		{ 
		  fin.read((char*)&n,sizeof(Customer));
		  if (fin)
		  {
		  
		   if(strcmp(n.name,cname)==0)
		   {cout<<" Match Found \n";
		    display(fin.tellg());
		    cout<<endl;
		    do
              {set:
               valid = 1;
		    cout << "\nPlease enter the following information:\n";
cout << "\nCustomer Name: ";
cin.getline(n.name, 45);

custFile.open("C:\\Database\\cust.dat", ios::in | ios::binary);
while (true)
{
custFile.read(reinterpret_cast<char*>(&x), sizeof(Customer)); //Read one record 
if (custFile.fail())
break;
if (strcmpi(n.name,x.name) == 0) // If search value matches customers name..
{cout<<"\n\n\t\t You cannot use that customer name. It already exists.";
sleep(2);
system("cls");
goto set;
}
}
custFile.clear();
custFile.close();

cout << "\nCustomer Address: ";
cin.getline(n.address, 45);
cout << "\nCity: ";
cin.getline(n.city, 20);
cout << "\nState: ";
cin.getline(n.state, 10);
cout << "\nZip: ";
cin.getline(n.zip, 11);
cout << "\nTelephone: ";
cin.getline(n.phone, 14);
cout << "\nAccount Balance: ";
cin >> n.balance;
cin.get();

if (strlen(n.name) ==0 || strlen(n.address) ==0 || strlen(n.city) ==0 || strlen(n.state) ==0 || strlen(n.zip) ==0 )
{
cout << "You must enter infroamtion for each field. \n";
valid = 0;
}
if (n.balance < 0)
{
cout << "Please enter 0 or greater for account balance. \n";
valid = 0;
}
              
} while (!valid);

		    cout<<" Update Complete\n";
		    rpos=fin.tellg();
		    wpos=rpos-sizeof(n);
		    fin.seekp(wpos,ios::beg);
		    fin.write((char*)&n,sizeof(n));
		  break;
      		}
		   }
		}
		
	}
	fin.close();
	
}

// deleteREc *
// This function marks a record for deletion by placing *

void deleteRec()                         // PROBLEM WITH DELETION:
{													// IT DELETES EVERYTHING  
Customer x;
    char n[21];
    int flag=0;
	
	fout.open("C:\\Database\\temp.dat", ios::out | ios::binary);
	fin.open("C:\\Database\\cust.dat", ios::in | ios::out | ios::binary);
	if(!fin)
	{cout<<" Unable to Open Link";
	}
	else
	{     
		  cout<<" Enter Accout Name To be Deleted\n";
		  fflush(stdin);
		  gets(n);
		  while(fin)
	    { 
		  fin.read((char*)&x,sizeof(Customer));
		  if (fin)
		  {
		  
		   if(strcmpi(x.name,n)==0)
		   { flag=1;
		    cout<<endl;
		    
		   }
    		else
    		{fout.write((char*)&x,sizeof(Customer));
			}
	      } 
	    }
	  
	}
	fout.close();
	fin.close();
	remove("C:\\Database\\cust.dat");
	rename("C:\\Database\\temp.dat","C:\\Database\\cust.dat");
	if(flag==0)
	{cout<<"\n Match not found";
	}
  if(flag==1)
  {
cout << "\nDeletion Successful. \n";
}
}
//-----------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------
                                           //BUS RESERVE

class Bus
{
  int busn;
  char driver[20], arrival[10], depart[10], from[20], to[20], seat[8][4][10];

public:
  void install(long bfp);
  void erase();
  void modify();
  void allotment(Customer c);
  void cancel(Customer c);
  inline void empty();
  void show();
  void avail();
  void position();
}b;


void Bus::install(long bfp)
{ 
  cout<<"Enter bus no: ";
  cin>>b.busn;
  cout<<"\nEnter Driver's name: ";
  fflush(stdin);
  gets(b.driver);                              //we can write to files but cant read it
  cout<<"\nArrival time: ";
  cin>>b.arrival;
  cout<<"\nDeparture: ";
  cin>>b.depart;
  cout<<"\nFrom: \t\t\t";
  fflush(stdin);
  gets(b.from);
  cout<<"\nTo: \t\t\t";
  fflush(stdin);
  gets(b.to);
  b.empty();
  
  
  if (bnew)
{
fout.open("C:\\Database\\busdetails.dat", ios::out | ios::app | ios ::binary );
}
else if (bmod)
{
fout.open("C:\\Database\\busdetails.dat", ios::out | ios::app | ios ::binary );
fout.seekp(bfp, ios::beg);
}
if (fout.fail())
{
cout << "\nError opening file.\n";
return;
}
fout.write(reinterpret_cast<char*>(&b), sizeof(Bus));
if (fout.fail())
{
cout << "\nError writing record to file. \n";
fout.clear();
fout.close();
return;
}
fout.clear();
fout.close();
  system("cls");
  cout<<"\n\n\n\n\n\t\t\tThe bus is being registered...";
  sleep(1);
  system("cls");
}

void Bus::erase()
{ 
  Bus x;
    int no=0;
    int flag=0;
	fstream fin;
	ofstream fout;
	fout.open("C:\\Database\\temp.dat", ios::out | ios::binary);
	fin.open("C:\\Database\\busdetails.dat", ios::in | ios::binary);
	if(!fin)
	{cout<<" Unable to Open Link";
	}
	else
	{     
		  cout<<" Enter bus Number To be Deleted\n";
		  cin>>no;
		  while(fin)
	    { 
		  fin.read((char*)&x,sizeof(Bus));
		  if (fin)
		  {
		  
		   if(x.busn==no)
		   {cout<<" Match Found \n";
		    flag=1;
		    cout<<endl;
		    cout<<" Bus Status-Dormant\n";
		   }
    		else
    		{fout.write((char*)&x,sizeof(Bus));
			}
	      } 
	    }
	  
	}
	fout.close();
	fin.close();
	remove("C:\\Database\\busdetails.dat");
	rename("C:\\Database\\temp.dat","C:\\Database\\busdetails.dat");
	if(flag==1)
	{
  cout<<"\n\n\n\n\n\t\t\tThe bus is being deleted...";
  sleep(1);
  system("cls");
	 }
  else if(flag==0)
  {cout<<"No such bus";
  
  }

fin.clear();
fin.close();
}


void Bus::modify()
{   Bus b2;
   int bn;
    long rpos=0;
    long wpos=0;
    int no=0;
    int valid=0;
    double bal=0;
	cout<<" Welcome To Database Updater\n";
	fstream fin;
	fin.open("C:\\Database\\busdetails.dat", ios::out | ios::in | ios::binary);
	if(!fin)
	{cout<<" Unable to Open Link";
	}
	else
	{     
		  cout<<"Enter bus no.: ";
  cin>>bn;
		  
		
		  
		while(fin)
		{ 
		  fin.read((char*)&b2,sizeof(Bus));
		  if (fin)
		  {
		  
		   if(b2.busn==bn)
		   {cout<<" Match Found \n";
		    cout<<endl;
		    
		    cout << "\nPlease enter the following information:\n";
cout<<"Enter bus no: ";
  cin>>b2.busn;
  cout<<"\nEnter Driver's name: ";
  fflush(stdin);
  gets(b2.driver);                              //we can write to files but cant read it
  cout<<"\nArrival time: ";
  cin>>b2.arrival;
  cout<<"\nDeparture: ";
  cin>>b2.depart;
  cout<<"\nFrom: \t\t\t";
  fflush(stdin);
  gets(b2.from);
  cout<<"\nTo: \t\t\t";
  fflush(stdin);
  gets(b2.to);
  b2.empty();


		    cout<<" Update Complete\n";
		    rpos=fin.tellg();
		    wpos=rpos-sizeof(b2);
		    fin.seekp(wpos,ios::beg);
		    fin.write((char*)&b2,sizeof(b2));
		  break;
      		}
		   
		 else
  {cout<<"No such bus";
  break;
  }
		
	}
	fin.close();
	
}
  system("cls");
  cout<<"\n\n\n\n\n\t\t\tThe bus is being updated...";
  sleep(1);
  system("cls");
}

}

void Bus::allotment(Customer c)             
{ 

  
  int seatn;
  int n=0;
  int number;
  top:
  cout<<"Bus no: ";
  cin>>number;
  fin.open("C:\\Database\\busdetails.dat", ios::in | ios::binary);
  fout.open("C:\\Database\\busdetails.dat", ios::out | ios::binary);
if (!fin)
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
fin.seekg(ios::beg);
while (fin)
{
fin.read(reinterpret_cast<char*>(&b), sizeof(Bus));
  
    if(b.busn==number)
    {n=1;
	break;
	}
  }

  while(n==1)
  {
    cout<<"\nSeat Number: ";
    cin>>seatn;
    if(seatn>32)

    {
      cout<<"\nThere are only 32 seats available in this bus.";
    }

    else

    {
    if (strcmp(b.seat[seatn/4][(seatn%4)-1], "*")==0)
      {
        cout<<"Enter passenger's name: ";
        cin>>b.seat[seatn/4][(seatn%4)-1];                     
        cout<<"\n Seat reserved";
        sleep(1);
        c.balance-=40.0;
        c.cost+=40.0;
        fout.write((char*)&b,sizeof(Bus));
        break;
      }

    else
	 cout<<"The seat no. is already reserved.\n";
	 
      }
      }
    if(n==0)
    {
      cout<<"Enter correct bus no.\n";
      goto top;
    }
    
    fout.close();
    fin.close();
  }
  void Bus::cancel(Customer c)             //ADDED cancel option....
{ 
  int seatn;
  int n=0;
  int number;
  char tempname[10];
  top:
  cout<<"Bus no: ";
  cin>>number;
  fin.open("C:\\Database\\busdetails.dat", ios::in | ios::binary);
  fout.open("C:\\Database\\busdetails.dat", ios::out | ios::binary);
if (!fin)
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
fin.seekg(ios::beg);
while (fin)
{
fin.read(reinterpret_cast<char*>(&b), sizeof(Bus));
  
    if(b.busn==number)
    {n=1;
	break;
	}
  }

  while(n==1)
  {
    cout<<"\nSeat Number: ";
    cin>>seatn;
    if(seatn>32)

    {
      cout<<"\nThere are only 32 seats available in this bus.";
    }
    else
if (strcmp(b.seat[seatn/4][(seatn%4)-1], "*")==0)
{
	 cout<<"The seat no. is already empty.\n";
	 break;
}
    else

    {cout<<"Enter passenger's name: ";
    fflush(stdin);
    gets(tempname);
    if (strcmp(b.seat[seatn/4][(seatn%4)-1],tempname)==0)
      {
        
        strcpy(b.seat[seatn/4][(seatn%4)-1],"*");                     
        cout<<"\n Seat cancelled";
        sleep(1);
        fout.write((char*)&b,sizeof(Bus));
        break;
      }
    else 
    {cout<<"Incorrect Name!";
	}
    
	 
      }
      }
    if(n==0)
    {
      cout<<"Enter correct bus no.\n";
      goto top;
    }
    
    fout.close();
    fin.close();
  }

void Bus::empty()
{ 
  for(int i=0; i<8;i++)
  {
    for(int j=0;j<4;j++)
    {
      strcpy(seat[i][j], "*");
    }
  }
}

void Bus::show()
{ 
  
  int n=0;
  int number;
  cout<<"Enter bus no: ";
  cin>>number;
  fin.open("C:\\Database\\busdetails.dat", ios::in | ios::binary);
if (!fin)
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
fin.seekg(ios::beg);
while (fin)
{
fin.read(reinterpret_cast<char*>(&b), sizeof(Bus));
  
    if(b.busn==number)
    {n=1;
	break;
	}
  }

while(n==1)
{
  vline('*');
    cout<<"Bus no: \t"<<b.busn<<"\nDriver: \t"<<b.driver
    <<"\nArrival time: \t"<<b.arrival<<"\nDeparture Time: "
    <<b.depart<<"\nFrom: \t\t";
    fflush(stdin);
	puts(b.from);
	cout<<"To: \t\t";
	fflush(stdin);
    puts(b.to);
	cout<<"\n";
    vline('*');
    vline('_');
    
  b.position();
  int a=1;
  for (int i=0; i<8; i++)
  {
    for(int j=0;j<4;j++)
    {
      a++;
      if(strcmp(b.seat[i][j],"*")!=0)
      cout<<"\nThe seat no "<<(a-1)<<" is reserved for "<<b.seat[i][j]<<".";
    }
  }
  break;
  }
  if(n==0)
    {
	cout<<"Enter correct bus no: ";
	}
    fin.close();
}

void Bus::position()
{ 
  int s=0,x=0;
  for (int i =0; i<8;i++)
  {
    cout<<"\n";
    for (int j = 0;j<4; j++)
    {
      s++;
      if(strcmp(b.seat[i][j], "*")==0)
        {
          cout.width(5);
          cout.fill(' ');                              //showing the seating plan
          cout<<s<<".";
          cout.width(10);                     //empty seats
          cout.fill(' ');
          cout<<b.seat[i][j];
          x++;
        }
        else
        {
        cout.width(5);
        cout.fill(' ');
        cout<<s<<".";                      //occupied seats
        cout.width(10);
        cout.fill(' ');
        cout<<b.seat[i][j];
        }
      }
    }
  cout<<"\n\nThere are "<<x<<" seats empty in Bus No: "<<b.busn;
  }
  
void Bus::avail()
{  
 cin.ignore();

int count = 0;
fin.open("C:\\Database\\busdetails.dat", ios::in | ios::binary);
if (fin.fail())
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
fin.seekg(ios::beg);

while (fin.peek()!=EOF)
{
fin.read(reinterpret_cast<char*>(&b), sizeof(Bus));
cout << setprecision(2);
cout << fixed << showpoint;
vline('*');
cout << "\nRECORD NUMBER " << ++count << ":" << endl;
  
  cout<<"Bus no: \t"<<b.busn<<endl;
  cout<<"\nDriver: \t"<<b.driver<<endl;
  cout<<"\nArrival time: \t"<<b.arrival<<endl;
  cout<<"\nDeparture Time: "<<b.depart<<endl;
  cout<<"\nFrom: \t\t";
    fflush(stdin);
    puts(b.from);
	cout<<"To: \t\t";
	fflush(stdin);
    puts(b.to);
    vline('*');
    vline('_');

}
if (count == 0)
{
cout<<"\n\n\n\n\n\t\t\tThere are no available buses";
	sleep(1);
	system("cls");
}
if (count!=0)
{
cout<<"\n  There are "<<count<<" buses.\n\n";
}
sleep(1);
cout << "\nPress Enter to Back To Main. ";
cin.get();
system("cls");
fin.clear();
fin.close();
}

void badmin();

void Busreserve(Customer c)
{ 
int w,flag=1;
busmenu:
while(flag==1)
{
   // system("cls");
  cout<<"\n\n\n\n\n";
  cout<<"\t\t\t1.Admin Cell\n\t\t\t"
  <<"2.Reservation\n\t\t\t"
  <<"3.Cancellation\n\t\t\t"
  <<"4.Show\n\t\t\t"
  <<"5.Buses Available. \n\t\t\t"
  <<"6.Exit";
  cout<<"\n\n\t\t\tEnter your choice: ";
  cin>>w;
  system("cls");
  switch(w)

  {
    case 1:  badmin();
      break;
    case 2:  b.allotment(c);
      break;
    case 3:  b.cancel(c);
      break;
    case 4:  b.show();
      break;
    case 5:  b.avail();
      break;
    case 6:  system("cls");
    flag=0;                            
    break;
    default: system("cls");
	cout<<"\nInvalid option";
	sleep(1);
	continue;
	break;
  }
goto busmenu;
}
}

void badmin()
{	
	Customer c;
    fflush(stdin);
    char pass[6],code[20];   //   admin only ;)
    int flag,ch=0;
	strcpy(pass,"boss");             //oh.....and by the way the password to everything is boss
	strcpy(code," ");                                    
	system("cls");
do
{  int t=1;
	 cout<<"Enter Access Code: ";
	gets(code);
	if(strcmp(code,pass)==0)
	{ flag=1;
	while(t==1)
	{
	system("cls");
  cout<<"\n\n\n\n\n";
  cout<<"\t\t\t1.Install\n\t\t\t"
  <<"2.Erase\n\t\t\t"
  <<"3.Modify"<<"\n\t\t\t4.Back"<<"\n\n\t\t\tEnter your choice: ";
  cin>>ch;
  switch(ch)

  {
    case 1:  
    bnew = 1;
	b.install(0);
	bnew = 0;
      break;
    case 2:  b.erase();
      break;
    case 3:  b.modify();
      break;
    case 4:  system("cls");
    t=0;
	break;
    default: system("cls");
	cout<<"\n\n\n\n\n\t\t\tInvalid check";
	sleep(1);
	continue;
  }
	}
	
}
else
{cout<<"Access Denied";
}
}while(flag==0);
}
//----------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------
                                 // FLIGHT BOOKING

class Flight
{
  int flightn;
  char airline[20], arrival[10], depart[10], from[20], to[20], seat[25][4][10];

public:
  void install(long ffp);
  void erase();
  void modify();
  void allotment(Customer c);
  void empty();
  void show();                                        // added option for meals...but for now it doesnt do anything
  void avail();
  void position();
}f;

void Flight::install(long ffp)
{ 
  cout<<"Enter flight no: ";
  cin>>f.flightn;
  cout<<"\nEnter Airline name: ";
  fflush(stdin);
  gets(f.airline);                              //we can write to files but cant read it
  cout<<"\nArrival time: ";
  cin>>f.arrival;
  cout<<"\nDeparture: ";
  cin>>f.depart;
  cout<<"\nFrom: \t\t\t";
  fflush(stdin);
  gets(f.from);
  cout<<"\nTo: \t\t\t";
  fflush(stdin);
  gets(f.to);
  f.empty();
  
  
  if (fnew)
{
fout.open("C:\\Database\\flightdetails.dat", ios::out | ios::app | ios ::binary );
}
else if (fmod)
{
fout.open("C:\\Database\\flightdetails.dat", ios::out | ios::app | ios ::binary );
fout.seekp(ffp, ios::beg);
}
if (fout.fail())
{
cout << "\nError opening file.\n";
return;
}
fout.write(reinterpret_cast<char*>(&f), sizeof(Flight));
if (fout.fail())
{
cout << "\nError writing record to file. \n";
fout.clear();
fout.close();
return;
}
fout.clear();
fout.close();
  system("cls");
  cout<<"\n\n\n\n\n\t\t\tThe flight is being registered...";
  sleep(1);
  system("cls");
}

void Flight::erase()
{ 
  Flight x;
    int no=0;
    int flag=0;
	fstream fin;
	ofstream fout;
	fout.open("C:\\Database\\temp.dat", ios::out | ios::binary);
	fin.open("C:\\Database\\flightdetails.dat", ios::in | ios::binary);
	if(!fin)
	{cout<<" Unable to Open Link";
	}
	else
	{     
		  cout<<" Enter flight Number To be Deleted\n";
		  cin>>no;
		  while(fin)
	    { 
		  fin.read((char*)&x,sizeof(Flight));
		  if (fin)
		  {
		  
		   if(x.flightn==no)
		   {cout<<" Match Found \n";
		    flag=1;
		    cout<<endl;
		    cout<<" Flight Status-Dormant\n";
		   }
    		else
    		{fout.write((char*)&x,sizeof(Flight));
			}
	      } 
	    }
	  
	}
	fout.close();
	fin.close();
	remove("C:\\Database\\flightdetails.dat");
	rename("C:\\Database\\temp.dat","C:\\Database\\flightdetails.dat");
	if(flag==1)
	{
  cout<<"\n\n\n\n\n\t\t\tThe flight is being deleted...";
  sleep(1);
  system("cls");
	 }
  else if(flag==0)
  {cout<<"No such flight";
  
  }

fin.clear();
fin.close();
}


void Flight::modify()
{   Flight f2;
   int bn;
    long rpos=0;
    long wpos=0;
    int no=0;
    int valid=0;
    double bal=0;
	cout<<" Welcome To Database Updater\n";
	fstream fin;
	fin.open("C:\\Database\\flightdetails.dat", ios::out | ios::in | ios::binary);
	if(!fin)
	{cout<<" Unable to Open Link";
	}
	else
	{     
		  cout<<"Enter flight no.: ";
  cin>>bn;
		  
		
		  
		while(fin)
		{ 
		  fin.read((char*)&f2,sizeof(Flight));
		  if (fin)
		  {
		  
		   if(f2.flightn==bn)
		   {cout<<" Match Found \n";
		    cout<<endl;
		    
		    cout << "\nPlease enter the following information:\n";
cout<<"Enter flight no: ";
  cin>>f2.flightn;
  cout<<"\nEnter Airline name: ";
  fflush(stdin);
  gets(f2.airline);                              //we can write to files but cant read it
  cout<<"\nArrival time: ";
  cin>>f2.arrival;
  cout<<"\nDeparture: ";
  cin>>f2.depart;
  cout<<"\nFrom: \t\t\t";
  fflush(stdin);
  gets(f2.from);
  cout<<"\nTo: \t\t\t";
  fflush(stdin);
  gets(f2.to);
  f2.empty();


		    cout<<" Update Complete\n";
		    rpos=fin.tellg();
		    wpos=rpos-sizeof(f2);
		    fin.seekp(wpos,ios::beg);
		    fin.write((char*)&f2,sizeof(f2));
		  break;
      		}
		   
		 else
  {cout<<"No such flight";
  break;
  }
		
	}
	fin.close();
	
}
  system("cls");
  cout<<"\n\n\n\n\n\t\t\tThe flight is being updated...";
  sleep(1);
  system("cls");
}

}

void Flight::allotment(Customer c)             // PROBLEM - DOESNT ALLOT
{ 

  
  int seatn;
  int n=0;
  int number;
  top:
  cout<<"Flight no: ";
  cin>>number;
  fin.open("C:\\Database\\flightdetails.dat", ios::in | ios::binary);
  fout.open("C:\\Database\\flightdetails.dat", ios::out | ios::binary);
if (fin.fail())
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
fin.seekg(ios::beg);
while (fin)
{
fin.read(reinterpret_cast<char*>(&f), sizeof(Flight));
  
    if(f.flightn==number)
    {n=1;
	break;
	}
  }

  while(n==1)
  {
    cout<<"\nSeat Number: ";
    cin>>seatn;
    if(seatn>100)

    {
      cout<<"\nThere are only 100 seats available in this flight.";
    }

    else

    {
    if (strcmp(f.seat[seatn/4][(seatn%4)-1], "*")==0)
      {
        cout<<"Enter passenger's name: ";
        cin>>f.seat[seatn/4][(seatn%4)-1];                     // PROBLEM IN ALLOTING
        cout<<"\n Seat reserved";
        sleep(1);
        c.balance-=40.0;
        c.cost+=40.0;
        fout.write((char*)&f,sizeof(Flight));
        break;
      }

    else
	 cout<<"The seat no. is already reserved.\n";
	 
      }
      }
    if(n==0)
    {
      cout<<"Enter correct flight no.\n";
      goto top;
    }
    
    fout.close();
    fin.close();
  }

void Flight::empty()
{ 
  for(int i=0; i<25;i++)
  {
    for(int j=0;j<4;j++)
    {
      strcpy(seat[i][j], "*");
    }
  }
}

void Flight::show()
{ 
  
  int n=0;
  int number;
  cout<<"Enter flight no: ";
  cin>>number;
  fin.open("C:\\Database\\flightdetails.dat", ios::in | ios::binary);
if (fin.fail())
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
fin.seekg(ios::beg);
while (fin.peek()!=EOF)
{
fin.read(reinterpret_cast<char*>(&f), sizeof(Flight));
  
    if(f.flightn==number)
    {n=1;
	break;
	}
  }

while(n==1)
{
  vline('*');
    cout<<"Flight no: \t"<<f.flightn<<"\nDriver: \t"<<f.airline
    <<"\nArrival time: \t"<<f.arrival<<"\nDeparture Time: "
    <<f.depart<<"\nFrom: \t\t";
    fflush(stdin);
	puts(f.from);
	cout<<"To: \t\t";
	fflush(stdin);
    puts(f.to);
	cout<<"\n";
    vline('*');
    vline('_');
    
  f.position();
  int a=1;
  for (int i=0; i<25; i++)
  {
    for(int j=0;j<4;j++)
    {
      a++;
      if(strcmp(f.seat[i][j],"*")!=0)
      cout<<"\nThe seat no "<<(a-1)<<" is reserved for "<<f.seat[i][j]<<".";
    }
  }
  break;
  }
  if(n==0)
    cout<<"Enter correct flight no: ";
    fin.clear();
    fin.close();
}

void Flight::position()
{ 
  int s=0,x=0;
  for (int i =0; i<25;i++)
  {
    cout<<"\n";
    for (int j = 0;j<4; j++)
    {
      s++;
      if(strcmp(f.seat[i][j], "*")==0)
        {
          cout.width(5);
          cout.fill(' ');                              //showing the seating plan
          cout<<s<<".";
          cout.width(10);                     //empty seats
          cout.fill(' ');
          cout<<f.seat[i][j];
          x++;
        }
        else
        {
        cout.width(5);
        cout.fill(' ');
        cout<<s<<".";                      //occupied seats
        cout.width(10);
        cout.fill(' ');
        cout<<f.seat[i][j];
        }
      }
    }
  cout<<"\n\nThere are "<<x<<" seats empty in Flight No: "<<f.flightn;
  }
  
void Flight::avail()
{  
 cin.ignore();

int count = 0;
fin.open("C:\\Database\\flightdetails.dat", ios::in | ios::binary);
if (fin.fail())
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
fin.seekg(ios::beg);

while (fin.peek()!=EOF)
{
fin.read(reinterpret_cast<char*>(&f), sizeof(Flight));
cout << setprecision(2);
cout << fixed << showpoint;
vline('*');
cout << "\nRECORD NUMBER " << ++count << ":" << endl;
  
  cout<<"Flight no: \t"<<f.flightn<<endl;
  cout<<"\nAirline: \t"<<f.airline<<endl;
  cout<<"\nArrival time: \t"<<f.arrival<<endl;
  cout<<"\nDeparture Time: "<<f.depart<<endl;
  cout<<"\nFrom: \t\t";
    fflush(stdin);
    puts(f.from);
	cout<<"To: \t\t";
	fflush(stdin);
    puts(f.to);
    vline('*');
    vline('_');

}
if (count == 0)
{
cout<<"\n\n\n\n\n\t\t\tThere are no available flights";
	sleep(1);
	system("cls");
}
if (count!=0)
{
cout<<"\n  There are "<<count<<" flights.\n\n";
}
sleep(1);
cout << "\nPress Enter to Back To Main. ";
cin.get();
system("cls");
fin.clear();
fin.close();
}

void fadmin();

void Flightbooking(Customer c)
{ 
int w,flag=1;
flightmenu:
while(flag==1)
{
   // system("cls");
  cout<<"\n\n\n\n\n";
  cout<<"\t\t\t1.Admin Cell\n\t\t\t"
  <<"2.Reservation\n\t\t\t"
  <<"3.Show\n\t\t\t"
  <<"4.Flights Available. \n\t\t\t"
  <<"5.Exit";
  cout<<"\n\n\t\t\tEnter your choice: ";
  cin>>w;
  system("cls");
  switch(w)

  {
    case 1:  fadmin();
      break;
    case 2:  f.allotment(c);
      break;
    case 3:  f.show();
      break;
    case 4:  f.avail();
      break;
    case 5:  system("cls");
    flag=0;                            
    break;
    default: system("cls");
	cout<<"\nInvalid option";
	sleep(1);
	continue;
	break;
  }
goto flightmenu;
}
}

void fadmin()
{	
	Customer c;
    fflush(stdin);
    char pass[6],code[20];   //   admin only ;)
    int flag,ch=0;
	strcpy(pass,"boss");             //oh.....and by the way the password to everything is boss
	strcpy(code," ");                                    
	system("cls");
do
{  int t=1;
	 cout<<"Enter Access Code: ";
	gets(code);
	if(strcmp(code,pass)==0)
	{ flag=1;
	while(t==1)
	{
	system("cls");
  cout<<"\n\n\n\n\n";
  cout<<"\t\t\t1.Install\n\t\t\t"
  <<"2.Erase\n\t\t\t"
  <<"3.Modify"<<"\n\t\t\t4.Back"<<"\n\n\t\t\tEnter your choice: ";
  cin>>ch;
  switch(ch)

  {
    case 1:  
    fnew = 1;
	f.install(0);
	fnew = 0;
      break;
    case 2:  f.erase();
      break;
    case 3:  f.modify();
      break;
    case 4:  system("cls");
    t=0;
	break;
    default: system("cls");
	cout<<"\n\n\n\n\n\t\t\tInvalid check";
	sleep(1);
	continue;
  }
	}
	
}
else
{cout<<"Access Denied";
}
}while(flag==0);
}
//----------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------
                                         // HOTEL RESERVATION

class Hotel
{
  char hoteln[20], place[20], star[10], pool[5], restaurant[5], park[5], room[10][4][10];

public:
  void install(long hfp);                                       //file reading is still in Problem
  void erase();
  void modify();                                        //writing works...but not reading
  void allotment(Customer c);
  void empty();
  void show();
  void avail();
  void position();                                  //look at the new parameters...!
}h;


void Hotel::install(long hfp)
{ 
  cout<<"Enter Hotel name: ";
  fflush(stdin);
  gets(h.hoteln);
  cout<<"\nEnter Place: ";
  fflush(stdin);
  gets(h.place);
  cout<<"\nStar Rating: ";
  cin>>h.star;
  cout<<"\nPool: ";
  cin>>h.pool;
  cout<<"\nRestaurant: \t\t\t";
  fflush(stdin);
  gets(h.restaurant);
  cout<<"\nPark: \t\t\t";
  fflush(stdin);
  gets(h.park);
  h.empty();
  
  
  if (hnew)
{
fout.open("C:\\Database\\hoteldetails.dat", ios::out | ios::app | ios ::binary );
}
else if (hmod)
{
fout.open("C:\\Database\\hoteldetails.dat", ios::out | ios::app | ios ::binary );
fout.seekp(hfp, ios::beg);
}
if (fout.fail())
{
cout << "\nError opening file.\n";
return;
}
fout.write(reinterpret_cast<char*>(&h), sizeof(Hotel));
if (fout.fail())
{
cout << "\nError writing record to file. \n";
fout.clear();
fout.close();
return;
}
fout.clear();
fout.close();
  system("cls");
  cout<<"\n\n\n\n\n\t\t\tThe hotel is being registered...";
  sleep(1);
  system("cls");
}

void Hotel::erase()
{ 
  Hotel x;
    char no[20];
    int flag=0;
	fstream fin;
	ofstream fout;
	fout.open("C:\\Database\\temp.dat", ios::out | ios::binary);
	fin.open("C:\\Database\\hoteldetails.dat", ios::in | ios::binary);
	if(!fin)
	{cout<<" Unable to Open Link";
	}
	else
	{     
		  cout<<" Enter Hotel name To be Deleted\n";
		  fflush(stdin);
  			gets(no);
		  while(fin)
	    { 
		  fin.read((char*)&x,sizeof(Hotel));
		  if (fin)
		  {
		  
		   if(strcmpi(x.hoteln,no)==0)
		   {cout<<" Match Found \n";
		    flag=1;
		    cout<<endl;
		    cout<<" Hotel Status-Dormant\n";
		   }
    		else
    		{fout.write((char*)&x,sizeof(Hotel));
			}
	      } 
	    }
	  
	}
	fout.close();
	fin.close();
	remove("C:\\Database\\hoteldetails.dat");
	rename("C:\\Database\\temp.dat","C:\\Database\\hoteldetails.dat");
	if(flag==1)
	{
  cout<<"\n\n\n\n\n\t\t\tThe hotel is being deleted...";
  sleep(1);
  system("cls");
	 }
  else if(flag==0)
  {cout<<"No such hotel";
  
  }

fin.clear();
fin.close();
}


void Hotel::modify()
{   Hotel h2;
   char bn[20];
    long rpos=0;
    long wpos=0;
    int no=0;
    int valid=0;
    double bal=0;
	fstream fin;
	fin.open("C:\\Database\\hoteldetails.dat", ios::out | ios::in | ios::binary);
	if(!fin)
	{cout<<" Unable to Open Link";
	}
	else
	{     
		  cout<<"Enter hotel name: ";
  fflush(stdin);
  gets(bn);
		  
		while(fin)
		{ 
		  fin.read((char*)&h2,sizeof(Hotel));
		  if (fin)
		  {
		  
		   if(strcmpi(h2.hoteln,bn)==0)
		   {cout<<" Match Found \n";
		    cout<<endl;
		    
		    cout << "\nPlease enter the following information:\n";
cout<<"Enter Hotel name: ";
  fflush(stdin);
  gets(h2.hoteln);
  cout<<"\nEnter Place: ";
  fflush(stdin);
  gets(h2.place);
  cout<<"\nStar Rating: ";
  cin>>h2.star;
  cout<<"\nPool: ";
  cin>>h2.pool;
  cout<<"\nRestaurant: \t\t\t";
  fflush(stdin);
  gets(h2.restaurant);
  cout<<"\nPark: \t\t\t";
  fflush(stdin);
  gets(h2.park);
  h2.empty();


		    cout<<" Update Complete\n";
		    rpos=fin.tellg();
		    wpos=rpos-sizeof(h2);
		    fin.seekp(wpos,ios::beg);
		    fin.write((char*)&h2,sizeof(h2));
		  break;
      		}
		   
		 else
  {cout<<"No such hotel";
  break;
  }
		
	}
	fin.close();
	
}
  system("cls");
  cout<<"\n\n\n\n\n\t\t\tThe hotel is being updated...";
  sleep(1);
  system("cls");
}

}

void Hotel::allotment(Customer c)             // PROBLEM - DOESNT ALLOT
{ 

  
  int roomno;
  int n=0;
  char hname[20];
  top:
  cout<<"Hotel name: ";
  fflush(stdin);
  gets(hname);
  fin.open("C:\\Database\\hoteldetails.dat", ios::in | ios::binary);
  fout.open("C:\\Database\\hoteldetails.dat", ios::out | ios::binary);
if (fin.fail())
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
fin.seekg(ios::beg);
while (fin)
{
fin.read(reinterpret_cast<char*>(&h), sizeof(Hotel));
  
    if(strcmpi(h.hoteln,hname)==0)
    {n=1;
	break;
	}
  }

  while(n==1)
  {
    cout<<"\nRoom Number: ";
    cin>>roomno;
    if(roomno>40)

    {
      cout<<"\nThere are only 40 rooms available in this hotel.";
    }

    else

    {
    if (strcmp(h.room[roomno/4][(roomno%4)-1], "*")==0)
      {
        cout<<"Enter guest's name: ";
        cin>>h.room[roomno/4][(roomno%4)-1];                     // PROBLEM IN ALLOTING
        cout<<"\n Room reserved";
        sleep(1);
        c.balance-=40.0;
        c.cost+=40.0;
        fout.write((char*)&h,sizeof(Hotel));
        break;
      }

    else
	 cout<<"The room no. is already reserved.\n";
	 
      }
      }
    if(n==0)
    {
      cout<<"Enter correct hotel name\n";
      goto top;
    }
    
    fout.close();
    fin.close();
  }

void Hotel::empty()
{ 
  for(int i=0; i<10;i++)
  {
    for(int j=0;j<4;j++)
    {
      strcpy(room[i][j], "*");
    }
  }
}

void Hotel::show()
{ 
  
  int n=0;
  char hname[20];
  cout<<"Enter hotel name: ";
  fflush(stdin);
  gets(hname);
  fin.open("C:\\Database\\hoteldetails.dat", ios::in | ios::binary);
if (fin.fail())
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
fin.seekg(ios::beg);
while (fin.peek()!=EOF)
{
fin.read(reinterpret_cast<char*>(&h), sizeof(Hotel));
  
    if(strcmpi(h.hoteln,hname)==0)
    {n=1;
	break;
	}
  }

while(n==1)
{
  vline('*');
    cout<<"Hotel name: \t"<<fflush(stdin);
	puts(h.hoteln);cout<<"\nPlace: \t";fflush(stdin);
	puts(h.place);
    cout<<"\nStar Rating: ";
  cout<<h.star;
  cout<<"\nPool: ";
  cout<<h.pool;
  cout<<"\nRestaurant: \t\t\t";
  fflush(stdin);
  puts(h.restaurant);
  cout<<"\nPark: \t\t\t";
  fflush(stdin);
  puts(h.park);

	cout<<"\n";
    vline('*');
    vline('_');
    
  h.position();
  int a=1;
  for (int i=0; i<10; i++)
  {
    for(int j=0;j<4;j++)
    {
      a++;
      if(strcmp(h.room[i][j],"*")!=0)
      cout<<"\nThe room "<<(a-1)<<" is reserved for "<<h.room[i][j]<<".";
    }
  }
  break;
  }
  if(n==0)
    cout<<"Enter correct hotel name: ";
    fin.clear();
    fin.close();
}

void Hotel::position()
{ 
  int s=0,x=0;
  for (int i =0; i<10;i++)
  {
    cout<<"\n";
    for (int j = 0;j<4; j++)
    {
      s++;
      if(strcmp(h.room[i][j], "*")==0)
        {
          cout.width(5);
          cout.fill(' ');                              //showing the seating plan
          cout<<s<<".";
          cout.width(10);                     //empty seats
          cout.fill(' ');
          cout<<h.room[i][j];
          x++;
        }
        else
        {
        cout.width(5);
        cout.fill(' ');
        cout<<s<<".";                      //occupied seats
        cout.width(10);
        cout.fill(' ');
        cout<<h.room[i][j];
        }
      }
    }
  cout<<"\n\nThere are "<<x<<" rooms empty in Hotel No: ";
  fflush(stdin);
	puts(h.hoteln);
  }
  
void Hotel::avail()
{  
 cin.ignore();

int count = 0;
fin.open("C:\\Database\\hoteldetails.dat", ios::in | ios::binary);
if (fin.fail())
{
cout << "\nError opening file. \n\n*(File may be empty)\n";
return;
}
fin.seekg(ios::beg);

while (fin.peek()!=EOF)
{
fin.read(reinterpret_cast<char*>(&h), sizeof(Hotel));
cout << setprecision(2);
cout << fixed << showpoint;
vline('*');
cout << "\nRECORD NUMBER " << ++count << ":" << endl;
  
  cout<<"Hotel name: \t";fflush(stdin);
	puts(h.hoteln);cout<<"\nPlace: \t";fflush(stdin);
	puts(h.place);
    cout<<"\nStar Rating: ";
  cout<<h.star;
  cout<<"\nPool: ";
  cout<<h.pool;
  cout<<"\nRestaurant: \t\t\t";
  fflush(stdin);
  puts(h.restaurant);
  cout<<"\nPark: \t\t\t";
  fflush(stdin);
  puts(h.park);
    vline('*');
    vline('_');

}
if (count == 0)
{
cout<<"\n\n\n\n\n\t\t\tThere are no available hotels";
	sleep(1);
	system("cls");
}
if (count!=0)
{
cout<<"\n  There are "<<count<<" hotels.\n\n";
}
sleep(1);
cout << "\nPress Enter to Back To Main. ";
cin.get();
system("cls");
fin.clear();
fin.close();
}

void hadmin();

void Hotelreservation(Customer c)
{ 
int w,flag=1;
hotelmenu:
while(flag==1)
{
   // system("cls");
  cout<<"\n\n\n\n\n";
  cout<<"\t\t\t1.Admin Cell\n\t\t\t"
  <<"2.Reservation\n\t\t\t"
  <<"3.Show\n\t\t\t"
  <<"4.Hotels Available. \n\t\t\t"
  <<"5.Exit";
  cout<<"\n\n\t\t\tEnter your choice: ";
  cin>>w;
  system("cls");
  switch(w)

  {
    case 1:  hadmin();
      break;
    case 2:  h.allotment(c);
      break;
    case 3:  h.show();
      break;
    case 4:  h.avail();
      break;
    case 5:  system("cls");
    flag=0;                            
    break;
    default: system("cls");
	cout<<"\nInvalid option";
	sleep(1);
	continue;
	break;
  }
goto hotelmenu;
}
}

void hadmin()
{	
	Customer c;
    fflush(stdin);
    char pass[6],code[20];   //   admin only ;)
    int flag,ch=0;
	strcpy(pass,"boss");             //oh.....and by the way the password to everything is boss
	strcpy(code," ");                                    
	system("cls");
do
{  int t=1;
	 cout<<"Enter Access Code: ";
	gets(code);
	if(strcmp(code,pass)==0)
	{ flag=1;
	while(t==1)
	{
	system("cls");
  cout<<"\n\n\n\n\n";
  cout<<"\t\t\t1.Install\n\t\t\t"
  <<"2.Erase\n\t\t\t"
  <<"3.Modify"<<"\n\t\t\t4.Back"<<"\n\n\t\t\tEnter your choice: ";
  cin>>ch;
  switch(ch)

  {
    case 1:  
    hnew = 1;
	h.install(0);
	hnew = 0;
      break;
    case 2:  h.erase();
      break;
    case 3:  h.modify();
      break;
    case 4:  system("cls");
    t=0;
	break;
    default: system("cls");
	cout<<"\n\n\n\n\n\t\t\tInvalid check";
	sleep(1);
	continue;
  }
	}
	
}
else
{cout<<"Access Denied";
}
}while(flag==0);
}
//----------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------
struct Date
{int year;
int month;
int day;
};
time_t t = time(0);   // get time now
    struct tm * now1 = localtime( & t );
    
struct Menu
{char tempname[45];
char from[20],to[20];
  int nights,rooms,adults,child;
    Date d;
    
};

void destmenu(Customer c)
{
int vdate;
Menu dest;
cout<<"\n Press Enter to view offered destinations, and proceed to trip planner.";
cin.get();
system("cls");
cout<<"\n\t\t\t Our Destinations... \n";
cout<<"\n\n1. Norway: \"A once-in-a-lifetime destination and the essence of its appeal is \n\n            remarkably simple.\"";
cout<<"\n\n2. Barcelona: \"Barcelona is an enchanting seaside city with boundless culture, \n\n            fabled architecture, and a world-class drinking and dining scene.\"";
cout<<"\n\n3. Rio de Janeiro: \"Golden beaches and lush mountains, samba-fueled nightlife \n\n            and spectacular football matches.\"";
cout<<"\n\n4. Tokyo: \"Yoking past and future, Tokyo dazzles with its traditional culture \n\n            and passion for everything new.\"";
cout<<"\n\n5. Sydney: \"Day or night, this city sure is good-lookin\'.Scratch the surface \n\n            and it only gets better.\"";
//sleep(5);
cout<<"\n\n Press Enter to continue...";
cin.get();
system("cls");

//********************************************************************************************
  strcpy(dest.tempname,c.name);
  cout<<"\n Enter Origin/From: ";
  fflush(stdin);
  gets(dest.from);
  cout<<"\n Enter Destination: ";
  fflush(stdin);
  tol:
  gets(dest.to);
  if((strcmpi(dest.to,"norway")!=0)&&(strcmpi(dest.to,"barcelona")!=0)&&(strcmpi(dest.to,"rio de janeiro")!=0)&&(strcmpi(dest.to,"tokyo")!=0)&&(strcmpi(dest.to,"sydney")!=0))
  {cout<<"\n Sorry, that destination does not include in our list.\n\n  But don\'t worry, we\'ll update soon !";
  cout<<"\n\n Press enter to retry.";
  cin.get();
  system("cls");
  goto tol; 
  }
  else
  {cout<<"You\'ve decided to travel to "<<dest.to<<".\n  Press Enter.";
  cin.get();
  }
  do
  {vdate=1;
  system("cls");
  cout<<"\n Date of Departure: ";
  cout<<" DD: ";
  cin>>dest.d.day;
  cout<<" MM: ";
  cin>>dest.d.month;
  cout<<" YYYY: ";
  cin>>dest.d.year;
  if((dest.d.year<(now1->tm_year + 1900))||(dest.d.year>2020))
  {cout<<"\n Enter valid year!";
  sleep(1);
  vdate=0;
  }
  if((dest.d.month<(now1->tm_mon + 1))&&(dest.d.year==(now1->tm_year + 1900))||(dest.d.month>12)||(dest.d.month<1))
  {cout<<"\n Enter valid month!";
  sleep(1);
  vdate=0;
  }
  if((dest.d.day<=(now1->tm_mday)&&((dest.d.month==(now1->tm_mon + 1))&&(dest.d.year==(now1->tm_year + 1900))))||((dest.d.day<1)||(dest.d.day>31)))                                        
  {cout<<"\n Enter date not less than tomorrow!";
  sleep(1);
  vdate=0;
  }
  if(((dest.d.month==4)||(dest.d.month==6)||(dest.d.month==9)||(dest.d.month==11))&&dest.d.day>30)
  {cout<<"Enter valid date!";
  sleep(1);
  vdate=0;
  }
  if(((dest.d.year)%4!=0)&&(dest.d.month==2)&&(dest.d.day>28))
  {cout<<"Enter valid date!";
  sleep(1);
  vdate=0;
  }
  if((dest.d.month==2)&&(dest.d.day>29))
  {cout<<"Enter valid date!";
  sleep(1);
  vdate=0;
  }
}while(!vdate);
night:
cout<<"\n Nights: ";
cin>>dest.nights;
if(dest.nights<1)
{cout<<"Enter atleast 1 night!";
sleep(1);
goto night;
}
room:
cout<<"\n Rooms: ";
cin>>dest.rooms;
if(dest.rooms<1)
{cout<<"Enter atleast 1 room!";
sleep(1);
goto room;
}
adult:
cout<<"Adults: ";
cin>>dest.adults;
if(dest.adults<1)
{cout<<"There should be atleast 1 adult!";
sleep(1);
goto adult;
}
cout<<"Children: ";
cin>>dest.child;
cout<<"\n\n Press Enter to continue to planner.";
fout.open("C:\\Database\\dest.dat", ios::out | ios::app | ios ::binary );
fout.write(reinterpret_cast<char*>(&dest), sizeof(Menu));
fout.clear();
fout.close();
}

int main()
{
Customer c;
long fpos=0;
int choice = 6;
int ch=1;
char YorN;
 

do
{ first:
cout << "\n ------------------ M A I N M E N U ----------------- \n\n";
cout << "1. Enter a new Customer Account\n";
cout << "2. Display a Customer Account\n";
cout << "3. Delete a Customer Account \n";
cout << "4. Change a Customer Account \n";
cout << "5. Show all records\n";
cout << "6. Proceed to Trip Planning\n";
cout << "7. Exit the program\n\n";

// Determine user's choice
do
{
cout << "Enter your choice (1-7): ";     
cin >> choice;
} while (choice < 1 || choice > 7);
system("cls");
//Process user's choice
switch (choice)
{
case 1:
cin.get();
cout << "\nYou selected Enter a new Customer Account.\n\n";
rnew = 1;
setInfo(0);
rnew = 0;
break;
case 2:
cout << "\nYou selected Display a Customer Account.\n\n";
fpos = search();
if (fpos != -1)
{
display(fpos);
}
else
cout << "\nRecord not Found.";
break;
case 3:
cout << "\nYou selected Delete a Customer Account.\n\n";

deleteRec();
break;

case 4:
cout << "\nYou selected Change a Customer Account.\n\n";
modifyRec();
break;


case 5:
cout << "\nYou selected Show all Customer Accounts.\n\n";
showAll();
break;

case 6:
	
	fpos = search();                   
if (fpos > -1)
{


custFile.open("C:\\Database\\cust.dat", ios::in | ios::binary);
custFile.seekg(fpos, ios::beg);
custFile.read(reinterpret_cast<char*>(&c), sizeof(Customer));

cout << "\n Welcome "<<c.name<<",\n";


trip:
cout << "\n ------------------ TRIP PLANNER ----------------- \n\n";
cout << "1. Decide Destination\n";
cout << "2. Reserve Bus Tickets\n";
cout << "3. Book Flight Tickets\n";
cout << "4. Arrange Hotel Accomodation\n";
cout << "5. See your bill amount\n";
cout << "6. Back to Main Menu\n";

do
{
cout << "Enter your choice (1-6): ";     
cin >> ch;
} while (ch < 1 || ch > 6);
system("cls");
switch(ch)
{case 1:
	destmenu(c);
	goto trip;
	break;
 case 2:
	cout<<"\n\n\n\n\n\t\t\t BUS RESERVATION ";
	sleep(1);
	Busreserve(c);
	system("cls");
	cout<<"\n\n\n\n\n\t\t\tBUS RESERVATION COMPLETE";
	sleep(1);
	system("cls");
	goto trip;
	break;
 case 3:
 	cout<<"\n\n\n\n\n\t\t\t FLIGHT BOOKING ";
	sleep(1);
	Flightbooking(c);
	system("cls");
	cout<<"\n\n\n\n\n\t\t\tFLIGHT BOOKING COMPLETE";
	sleep(1);
	system("cls");
	goto trip;
	break;
 case 4:
 	cout<<"\n\n\n\n\n\t\t\t HOTEL RESERVATION ";
	sleep(1);
	Hotelreservation(c);
	system("cls");
	cout<<"\n\n\n\n\n\t\t\tHOTEL RESERVATION COMPLETE";
	sleep(1);
	system("cls");
	goto trip;
	break;
 case 5:
 	cout<<"\n\n\n\tYour Total bill amount is "<<c.cost<<endl;
 	goto trip;
 	break;
 case 6:
 	custFile.seekg(ios::beg);
 	custFile.clear();
 	custFile.close();
 	goto first;
 	break;
 default:
 	break;
}
}
else
{cout << "\nRecord not Found.";
custFile.open("C:\\Database\\cust.dat", ios::in | ios::binary);
custFile.seekg(ios::beg);
custFile.clear();
custFile.close();
goto first;}
goto first;
case 7:
	system("cls");
	cout<<"\n\n\n\n\n\n\n\n\t\t\t\tThank  You  !!!\n\n\n";
	sleep(1);
	system("cls");
exit(0);
break;
default: //Anything not between 1-6
system("cls");
break;
} // End switch
} while (choice != 7);
return 0;
}// End of Main


