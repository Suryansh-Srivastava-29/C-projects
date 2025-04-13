/*
    HEADER FILES INCLUDED 
*/
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>

using namespace std;

/*
    CLASS CREATED 
*/
class account 
{
    int acno;
    char name[50];
    int deposit;
    char type;
public:
    void create_account(); // Function to get data from User .
    void show_account() const ; // Function to show Data on screen .
    void modify(); // Function to add new Data .
    void dep(int); // Function to accept amount and add to balance 
    void draw(int);// Function to accept amount and subtract from balance .
    void report() const; // Function to show data in Tabular form .
    int retacno() const; // Function to return Account number . 
    int retdeposit() const; // Function to return Balance amount .
    char rettype() const; // Function to return type of account .
};
/*
    DEFINING FUNCTIONS CREATED IN CLASS 
*/
void account::create_account() 
{
    cout<<"\nEnter the Account Number : ";
    cin>>acno;
    cout<<"\nEnter the Name of Account Holder : ";
    cin.ignore();
    cin.getline(name,30);
    cout<<"\nEnter the Type of Account : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nEnter the Initial amount (For Savings:500+) (For balance:1000=) : ";
    cin>>deposit;
    cout<<"\n\n\nAccount Created ";
}

void account::show_account()
{
    cout<<"\nAccount Number : "<<acno;
    cout<<"\nAccount Holder Name : "<<name;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance Amount : "<<deposit;
}

void account::modify()
{
    cout<<"\nAccount Number : "<<acno;
    cout<<"\nModify Account Holder's name : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify Type of Account : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance Amount : ";
    cin>>deposit;
}

void account::dep(int x)
{
    deposit=deposit+x;
}

void draw(int y)
{
    deposit=deposit-x;
}

void account::report() const
{
    cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int account::retacno()
{
    return acno;
}

int account::retdeposit() const
{
    return deposit;
}

char account::rettpe() const
{
    return type;
}
/*
    CLASS FUNCTIONS END 
*/

/*
**********************************
NEW FUNCTION DEFINATION 
**********************************8
*/

void write_account();//Function to write record in Binary File .
void display_sp(int);//Function to display account details given by User .
void modify_account(int);//function to modify record of File .
void delete_account(int);//Function to delete records of a File .
void display_all();//Function to display all acoounts details .
void deposit_withdraw(int,int);//Function to deposit/withdraw amount for given account .
void intro();//Introduction Screen .


int main()
{
    char ch;
    int num;
    intro();
    do
    {
        system("cls");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. NEW ACCOUNT";
        cout<<"\n\n\t02. DEPOSIT AMOUNT";
        cout<<"\n\n\t03. WITHDRAW AMOUNT";
        cout<<"\n\n\t04. BALANCE ENQUIRY";
        cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout<<"\n\n\t06. CLOASE AN ACCOUNT";
        cout<<"\n\n\t07. MODIFY AN ACCOUNT";
        cout<<"\n\n\t08. EXIT";
        cout<<"\n\n\tSelect your Option (1-8)";
        cin>>ch;
        system("cls");
        switch(ch)
        {
            case '1':
                write_account();
                break;
            case '2':
                cout<<"\n\n\tEnter the Account Number :";
                cin>>num;
                deposit_withdraw(num,1);
                break;
            case '3':
                cout<<"\n\n\tEnter the Account Number :";
                cin>>num;  
                deposit_withdraw(num,2);
                break;
            case '4':
                cout<<"\n\n\tEnter the Account Number :";
                cin>>num;  
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                cout<<"\n\n\tEnter the Account Number :";
                cin>>num; 
                delete_account(num);
                break;
            case '7':
                cout<<"\n\n\tEnter the Account Number :";
                cin>>num; 
                modify_account(num);
                break;
            case '8':
                cout<<"Thanks for Using Bank Management System  ";
                break;
            default:
                cout<<"\a";  
        }
        cin.ignore();
        cin.get();
    }while(ch!='8');
    return 0;
}

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary| ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*>(&ac),sizeof(account));
    outFile.close();
}

void display_sp(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be opened !! Press any key ";
        return ;
    }
    cout<<"\nBalance Details\n";
    while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
    {
        cout<<"\n\nAccount number does not exist ";
    }
}


void modify_account(int n)
{
    bool found=false;
    account ac;
    fstream File ;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not Open";
        return ;
    }
    while(!File.eof()&&found==false)
    {
        File.read(reinterpret_cast<char*>(&ac),sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            cout<<"\n\nEnter the New Details of acoount "<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char*>(&ac),sizeof(account));
            cout<<"\n\n\tRecord Updated ";
            found=true;
        }
    }
    File.close();
    if(found==false)
    {
        cout<<"\n\nrecord Not Found";
    }
}

void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not open !! Press any key ";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0::beg);
    while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.retacno()!=n)
        {
            outFile.write(reinterpret_cast<char*>(&ac),sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\tRecord Deleted .. ";
}

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not open !! Press any key";
        return;
    }
    cout<<"\n\n\tAccount Holder List\n\n";
    cout<<"======================\n\n";
    cout<<"A/C No.       Name      Type      Balance \n";
    cout<<"======================\n\n";
    while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

void deposit_withdraw(int n,int option)
{
    int amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not open !! Press any key";
        return;
    }
    while(!File.eof()&&found==false)
    {
        File.read(reinterpret_cast<char*>(&ac),sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"To Deposit Amount "<<endl;
                cin>>amt;
                ac.dep(amt);
            }
            if(option==2)
            {
                cout<<"To withdraw amount ";
                cout<<"Enter the Amount to be withdrawn";
                cin>>amt;
                int bal=ac.retdeposit()-amt;
                if((bal<500 && ac.rettype=='S')||(bal<1000 && ac.rettype=='C'))
                cout<<"Insufficient Balance "<<endl;
                else
                ac.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char*>(&ac),sizeof(account));
            cout<<"\n\n\tRecord Updated";
            found=true;
        }
    }
    File.close();
    if(found==false)
    cout<<"\n\nRecord Not Found ";
}

void intro()
{
    cout<<"\n\n\n\tBANK ";
    cout<<"\n\n\tMANAGEMENT";
    cout<<"\n\n\tSYSTEN";
    cin.get();
}















/*
    The C++ <cctype> header file declares a set of functions to classify (and transform) individual characters.
    For example, isupper() checks whether a character is uppercase or not . 


*/
