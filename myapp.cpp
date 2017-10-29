/*
    Developed by - SATWIK
   Date - 26 August 2016
*/

#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>

class CarShop
    {
           int code;
           char name[80], company[50], status[40];
           float rating, units;
       public:
          float Getratings() { return rating; }
          CarShop(){ strcpy(status, "AVA");}
          int Getcode() { return code; }
          char* Getname() { return name; }
          char* Getcompany() { return company; }
          char* GetStatus() { return status;}
          float Getunits() { return units; }
          void Enter();
          void ChangeStatus() { units = 0; rating = 0; code = 0; strcpy(status, "DEL");}
          void Display()
       {
          cout<<"\n\t*********************"<<endl;
          cout<<"\tCode = "<<code<<endl;
          cout<<"\tModel = "; puts(name);
          cout<<"\tCompany = "; puts(company);
          cout<<"\tNumber of units = "<<units<<endl;
          cout<<"\tRating = "<<rating<<endl;
          cout<<"\n\t*********************"<<endl;
          
       }
    };
           

void CarShop::Enter()
       {
        cout<<"\nEnter car code = ";
        cin>>code;
        cout<<"\nEnter car model = ";
        gets(name);
        cout<<"\nEnter company name = ";
        gets(company);
        cout<<"\nEnter number of units = ";
        cin>>units;
        cout<<"\nEnter car rating = ";
        cin>>rating;
        while((rating>5) || (rating<0))
         {
             cout<<"Rating must be between 0 to 5."<<endl;
             cin>>rating;

         }
       }


class User
       {
           char pass[10];
           public:
             User() { strcpy(pass,"DPSRKP123"); }
             void UserConfirm();
             char* Getpass(){ return pass;}
        };
        
        
void User::UserConfirm()
       {
           char password[30];
           cout<<"\nEnter password = ";
           gets(password);
           do
            {
                if(strcmp(Getpass(),password) == 0)
                cout<<"Welcome back ."<<endl;
                else
               {
                cout<<"Incorrect Password - try again."<<endl;
                gets(password);
               }
            } while(strcmp(Getpass(),password)!=0);
       }


void SortCode()
       {
       fstream fil;
       CarShop L, L1;
       fil.open("RECORD.dat", ios::binary|ios::out|ios::in);
       fil.seekg(0, ios::end);
       int NOR = (fil.tellg()/sizeof(L));
       for(int i = 0; i<NOR - 1; i++)
        {
           for(int j = 0; j<NOR-i-1; j++)
        {
           fil.seekg(j*sizeof(L));
           fil.read((char*)&L, sizeof(L));
           fil.read((char*)&L1, sizeof(L1));
           if(L.Getcode() > L1.Getcode())
            {
               fil.seekp(j*sizeof(L));
               fil.write((char*)&L1, sizeof(L1));
               fil.write((char*)&L, sizeof(L));
            }
        }
        }
        fil.close();
       }


void Search();
void SearchName();
void SearchCode();
void SearchUnits();
void SearchCompany();
void SearchRatings();
void Add();
void Delete();
void NoOfCars();
void SortCode();
void Edit();



void Menu()
       {
           int A;
           char ch;
           do
           {
             clrscr();
             cout<<"\n\t\t\t****************************";
             cout<<"\n\t\t\t*    CAR RENTAL PROJECT    *";
             cout<<"\n\t\t\t****************************";
             cout<<"\n\n\t\t\t*************";
             cout<<"\n\t\t\t* MAIN MENU *";
             cout<<"\n\t\t\t*************";
             cout<<"\n1.  Search "<<endl;
             cout<<"2.  Add a car "<<endl;
             cout<<"3.  Delete a car "<<endl;
             cout<<"4.  Check for number of cars in the shop "<<endl;
             cout<<"5.  Sort cars according to code "<<endl;
             cout<<"6.  Edit a Car "<<endl;
             cin>>A;
             switch(A)
             {
            case 1: Search();
                  break;
            case 2: Add();
                  break;
            case 3: Delete();
                  break;
            case 4: NoOfCars();
                  break;
            case 5: SortCode();
                  break;
            case 6: Edit();
                  break;
            default:
                {
                    cout<<"\n\n\t\t\tWrong choice.....!!!";
                    cout<<"\n\t\t\tPress any key to continue....!!";
                    getch();
                }
             }
             clrscr();
             cout<<"\n\t\t\t****************************";
             cout<<"\n\t\t\t*    CAR RENTAL PROJECT    *";
             cout<<"\n\t\t\t****************************";
             cout<<"\n\n\t\t\t*************";
             cout<<"\n\t\t\t* MAIN MENU *";
             cout<<"\n\t\t\t*************";
             cout<<"\nWould you like to choose another option?"<<endl;
             cin>>ch;
           } while(ch == 'y');
       }
       

void Edit()
   {
           clrscr();
        cout<<"\n\n\t\t\t**************";
        cout<<"\n\t\t\t* EDIT A CAR *";
        cout<<"\n\t\t\t**************";
        CarShop L;
        int found=0;
        fstream fil;
        fil.open("RECORD.dat", ios::binary|ios::in|ios::out);
        int Code;
        cout<<"\nEnter code of car to be edited from database = ";
        cin>>Code;
        while(!found && fil.read((char*)&L, sizeof(L)))
        {
            if(L.Getcode() == Code && strcmp("DEL",L.GetStatus()))
                {
                    found++;
                }
                if (found)
                {
                    L.Display();
                    L.Enter();
                    int N = fil.tellg() - sizeof(L);
                    fil.seekp(N);
                    fil.write((char*)&L, sizeof(CarShop));
                    cout<<"Car "<<Code<<"... has been edited."<<endl;
                }
                }
       if (!found)
       cout<<"Record not found..."<<endl;
       fil.close();
       getch();
   }


void Search()
   {
           int A;
           char ch = 'y';
           while (ch == 'y')
           {
             clrscr();
             cout<<"\n\t\t\t****************************";
             cout<<"\n\t\t\t*    CAR RENTAL PROJECT    *";
             cout<<"\n\t\t\t****************************";
             cout<<"\n\n\t\t\t***************";
             cout<<"\n\t\t\t* SEARCH MENU *";
             cout<<"\n\t\t\t***************";
             cout<<"\nEnter one of the following to be searched - "<<endl;
             cout<<"1.  Name "<<endl;
             cout<<"2.  Company "<<endl;
             cout<<"3.  Units "<<endl;
             cout<<"4.  Code "<<endl;
             cout<<"5.  Ratings "<<endl;
             cin>>A;
             switch(A)
             {
                case 1: SearchName();
                      break;
                case 2: SearchCompany();
                      break;
                case 3: SearchUnits();
                      break;
                case 4: SearchCode();
                      break;
                case 5: SearchRatings();
                      break;
                default:
                {
                    cout<<"\n\n\t\t\tWrong choice.....!!!";
                    cout<<"\n\t\t\tPress any key to continue....!!";
                    getch();
                }      
             }
             cout<<"Would you like to choose another option?"<<endl;
             cin>>ch;
           }    
   }


void SearchName()
    {
       CarShop L;
       clrscr();
       int count = 0;
       cout<<"\n\n\t\t\t***************";
        cout<<"\n\t\t\t* SEARCH NAME *";
        cout<<"\n\t\t\t***************";
       fstream fil;
       fil.open("RECORD.dat", ios::binary|ios::in);
       char Name[60];
       cout<<"\nEnter name of the car to be searched - ";
       gets(Name);
       L.Getname();
       while(fil.read((char*)&L, sizeof(L)))
       {
          if(strcmpi(Name, L.Getname()) == 0 && strcmp("DEL",L.GetStatus()))
         {
            L.Display();
            count++;
         }
          else
            cout<<"";
       }
       if (count == 0)
       cout<<"\n\t\tName Records Not Found!"<<endl;
       fil.close();
    }
       
       
void SearchCode()
       {
       CarShop L;
       fstream fil;
       int count = 0;
       clrscr();
       cout<<"\n\n\t\t\t***************";
        cout<<"\n\t\t\t* SEARCH CODE *";
        cout<<"\n\t\t\t***************";
       fil.open("RECORD.dat", ios::binary|ios::in);
       int Code;
       cout<<"\nEnter car code to be searched -";
       cin>>Code;
       L.Getcode();
        while(fil.read((char*)&L, sizeof(L)))
          {
            if(L.Getcode() == Code && strcmp("DEL",L.GetStatus()))
                {
                    L.Display();
                    count++;
                }
            else
                cout<<"";
          }
        if (count == 0)
        cout<<"\nCode Not Found!!";
       fil.close();
       }


void SearchRatings()
       {
       CarShop L;
       clrscr();
       int count = 0;
       cout<<"\n\n\t\t\t******************";
        cout<<"\n\t\t\t* SEARCH RATINGS *";
        cout<<"\n\t\t\t******************";
       fstream fil;
       fil.open("RECORD.dat", ios::binary|ios::in);
       float choice;
       cout<<"\nEnter ratings to be searched - ";
       cout<<"\n\t\t0+";
       cout<<"\n\t\t1+";
       cout<<"\n\t\t2+";
       cout<<"\n\t\t3+";
       cout<<"\n\t\t4+"<<endl;;
       cin>>choice;
       while(fil.read((char*)&L, sizeof(L)))
       {
           if(L.Getratings() >= choice && strcmp("DEL",L.GetStatus()))
            {
                L.Display();
                count++;
            }
            else
                cout<<"";
       }
       if (count == 0)
       cout<<"\n\t\tNo cars in that rating found!"<<endl;
       fil.close();
       }


void SearchUnits()
       {
       CarShop L;
       clrscr();
       int count = 0;
       cout<<"\n\n\t\t\t****************";
        cout<<"\n\t\t\t* SEARCH UNITS *";
        cout<<"\n\t\t\t****************";
       fstream fil;
       char name[30];
       fil.open("RECORD.dat", ios::binary|ios::in);
       cout<<"\nEnter name of car - ";
       gets(name);
       while(fil.read((char*)&L, sizeof(L)))
            {
                if(strcmp(name, L.Getname()) == 0 && strcmp("DEL",L.GetStatus()))
                {
                    if(L.Getunits() >= 0)
                        {        
                            L.Display();
                            count++;
                        }
                else
                cout<<"";
               }
       }
       if (count == 0)
       cout<<"\n\t\tUnits Not Found!"<<endl;
       fil.close();
       }


void SearchCompany()
    {
        CarShop L;
        clrscr();
        cout<<"\n\n\t\t\t******************";
        cout<<"\n\t\t\t* SEARCH COMPANY *";
        cout<<"\n\t\t\t******************";
        int count = 0;
        fstream fil;
        fil.open("RECORD.dat", ios::binary|ios::in);
        char Company[50];
        cout<<"\nEnter company name = ";
        gets(Company);
        L.Getcompany();
        while(fil.read((char*)&L, sizeof(L)))
        {
            if(strcmpi(Company, L.Getcompany()) == 0 && strcmp("DEL",L.GetStatus()))
                {
                    L.Display();
                    count++;
                }
            else
                cout<<"";
        }
       if (count == 0)
       cout<<"\n\t\tCompany Records Not Found!"<<endl;
       fil.close();
    }


void Add()
   {
       CarShop L;
       char C;
       do
       {
            clrscr();
            cout<<"\n\n\t\t\t*************";
            cout<<"\n\t\t\t* ADD A CAR *";
            cout<<"\n\t\t\t*************";
            fstream fil;
            fil.open("RECORD.dat", ios::binary|ios::app);
            L.Enter();
            fil.write((char*)&L, sizeof(L));
            cout<<"\n\t\tMore (Y/N) ?"; cin>>C;
            fil.close();
        }
        while (C == 'Y'|| C == 'y');
   }


void Delete()
       {
           clrscr();
           cout<<"\n\n\t\t\t****************";
            cout<<"\n\t\t\t* REMOVE A CAR *";
            cout<<"\n\t\t\t****************";
           CarShop L;
           int found=0;
           fstream fil;
           fil.open("RECORD.dat", ios::binary|ios::in|ios::out);
           int Code;
           cout<<"\nEnter code of car to be deleted from database = ";
           cin>>Code;
           while(!found && fil.read((char*)&L, sizeof(L)))
           {
                if(L.Getcode() == Code && strcmp("DEL",L.GetStatus()))
                {
                    found++;
                }
                if (found)
                {
                L.Display();
                L.ChangeStatus();
                int N = fil.tellg() - sizeof(L);
                fil.seekp(N);
                fil.write((char*)&L, sizeof(CarShop));
                cout<<"Car "<<Code<<"... has been deleted."<<endl;
                }
            }
       if (!found)
       cout<<"Record Not found"<<endl;
       fil.close();
       getch();
       }


void NoOfCars()
       {
           CarShop L;
           clrscr();
           cout<<"\n\n\t\t\t******************";
            cout<<"\n\t\t\t* Number of Cars *";
            cout<<"\n\t\t\t******************";
           float Count = 0;
           fstream fil;
           fil.open("RECORD.dat", ios::binary|ios::in);
           while(fil.read((char*)&L, sizeof(L)))
           {
                   Count = Count + L.Getunits();
           }
           cout<<"\nNo of cars in the shop are = "<<Count<<endl;
           fil.close();
           getch();
       }
     
void main()
    {
        User U;
        clrscr();
        cout<<" _____________________________";
        cout<<"____________________________________________ "<<endl;
        cout<<"  Welcome to Delhi Public School, R.K. Puram's CarShop Management";
        cout<< "System."<<endl<<" _______________________________";
        cout<<"__________________________________________ "<<endl;
        U.UserConfirm();
        Menu();
        getch();
    }