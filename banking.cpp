#include<iostream>
#include<fstream>
#include<cstring>
#include<string>

using namespace std;

class account
{
    int ano;
    string name;
    int deposit;
    char type;
public:
    void createacc();
    void showacc();
    void modify();
    void dep(int);
    void withdraw(int);
    void report();
    int retano();
    int retdeposit();
    char rettype();
};

void account::createacc()
{
    cout<<"Enter account number:"<<endl;
    cin>>ano;
    cout<<"Enter name of account holder:"<<endl;
    cin>>name;
    cout<<"Enter account type (C/S):"<<endl;
    cin>>type;
    type=toupper(type);                 //Ensure type is uppercase
    cout<<"Enter initial deposit for account (Must be >500 for Current and >1000 for Savings:"<<endl;
    cin>>deposit;
    cout<<"Your account has been created"<<endl;
}

void account::showacc()
{
    cout<<"Account Details"<<endl;
    cout<<"\nAccount No.: "<<ano<<endl;
    cout<<"Account Holder Name: "<<name<<endl;
    cout<<"Type of Account: "<<type<<endl;
    cout<<"Balance: "<<deposit<<endl;
}


void account::modify()
{
    cout<<"Account Number:"<<ano<<endl;
    cout<<"Enter name of account holder:"<<endl;
    cin>>name;
    cout<<"Enter type of account (C/S):"<<endl;
    cin>>type;
    type=toupper(type);
    cout<<"Enter balance:";
    cin>>deposit;
}



void account::dep(int x)
{
    deposit+=x;
}

void account::withdraw(int x)
{
    deposit-=x;
}

void account::report()
{
    cout<<ano<<"\t\t"<<name<<" "<<type<<"\t"<<deposit<<endl;
}

int account::retano()
{
    return ano;
}

int account::retdeposit()
{
    return deposit;
}

char account::rettype()
{
    return type;
}


void intro();
void newAcc();
void dispAcc(int);
void dispAcc();
void modAcc(int);
void delAcc(int);
void dep_with(int, int);



int main()
{
    int n,ch;
    intro();
    do
    {

        cout<<"\tMenu"<<endl;
        cout<<"1. Create account"<<endl;
        cout<<"2. Deposit amount"<<endl;
        cout<<"3. Withdraw amount"<<endl;
        cout<<"4. Check balance"<<endl;
        cout<<"5. Display details of all accounts"<<endl;
        cout<<"6. Close an account"<<endl;
        cout<<"7. Update account details"<<endl;
        cout<<"8. Quit"<<endl;
        cout<<"Choose an option."<<endl;
        cin>>ch;
        switch(ch)
        {
            case 1:     newAcc();
                        break;
                
            case 2:     cout<<"Enter account number:"<<endl;
                        cin>>n;
                        dep_with(n, 1);
                        break;
                
            case 3:     cout<<"Enter account number:"<<endl;
                        cin>>n;
                        dep_with(n, 2);
                        break;
                
            case 4:     cout<<"Enter account number:"<<endl;
                        cin>>n;
                        dispAcc(n);
                        break;
                
            case 5:     dispAcc();
                        break;
                
            case 6:     cout<<"Enter account number:"<<endl;
                        cin>>n;
                        delAcc(n);
                        break;
                
            case 7:     cout<<"Enter account number:"<<endl;
                        cin>>n;
                        modAcc(n);
                        break;
                
            case 8:    cout<<"->Exiting the banking system"<<endl<<"Thank you for using the banking system"<<endl;
                        break;
            
            default:   cout<<"Invalid choice"<<endl;
        }
    }while(ch!=8);
    return 0;
}



void newAcc()
{
    account ac;
    ofstream fout;
    fout.open("account.dat",ios::binary|ios::app);
    ac.createacc();
    fout.write((char *) &ac, sizeof(account));
    fout.close();
}


void dispAcc(int n)
{
    account ac;
    int flag=0;
    ifstream fin;
    fin.open("account.dat",ios::binary);
    if(!fin)
    {
        cout<<"Unable to open file- press any key"<<endl;
        return;
    }
    while(fin.read((char *)&ac, sizeof(account)))
    {
        if(ac.retano()==n)
        {
            ac.showacc();
            flag=1;
        }
    }
    fin.close();
    if(flag==0)
        cout<<"Account number does not exist"<<endl;
}



void modAcc(int n)
{
    int check=0;
    account ac;
    fstream f;
    f.open("account.dat",ios::binary|ios::in|ios::out);
    if(!f)
    {
        cout<<"Unable to open file- press any key to continue"<<endl;
        return;
    }
    while(f.read((char *) &ac, sizeof(account)) && check==0)
    {
        if(ac.retano()==n)
        {
            ac.showacc();
            cout<<"Modifying account details."<<endl;
            ac.modify();
            int pos=(-1)*sizeof(account);
            f.seekp(pos,ios::cur);
            f.write((char *) &ac, sizeof(account));
            cout<<"Record updated successfully"<<endl;
            check=1;
        }
    }
    f.close();
    if(check==0)
        cout<<"\n\n Record Not Found ";
}



void delAcc(int n)
{
    account ac;
    ifstream fin;
    ofstream fout;
    fin.open("account.dat",ios::binary);
    if(!fin)
    {
        cout<<"Unable to open file- press any key to continue.";
        return;
    }
    fout.open("Temp.dat",ios::binary);
    fin.seekg(0,ios::beg);
    while(fin.read((char *) &ac, sizeof(account)))
    {
        if(ac.retano()!=n)
            fout.write((char *) &ac, sizeof(account));
        
    }
    fin.close();
    fout.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"The record has been deleted"<<endl;
}


void dispAcc()
{
    account ac;
    ifstream fin;
    fin.open("account.dat",ios::binary);
    if(!fin)
    {
        cout<<"Unable to open file- press a key";
        return;
    }
    cout<<"\t\t\tAccounts"<<endl;
    cout<<"===================================================="<<endl;
    cout<<"Acc.No\tName\tType\tBalance"<<endl;
    cout<<"===================================================="<<endl;
    while(fin.read((char *) &ac, sizeof(account)))
    {
        ac.report();
    }
    fin.close();
}


void dep_with(int n, int option)
{
    int amt;
    int check=0;
    account ac;
    fstream f;
    f.open("account.dat", ios::binary|ios::in|ios::out);
    if(!f)
    {
        cout<<"Unable to open file, press any key to continue."<<endl;
        return;
    }
    while(f.read((char *) &ac, sizeof(account)) && check==0)
    {
        if(ac.retano()==n)
        {
            ac.showacc();
            if(option==1)
            {
                cout<<"Enter amount to be deposited into the account"<<endl;
                cin>>amt;
                ac.dep(amt);
            }
            if(option==2)
            {
                cout<<"Enter amount to be withdrawn from the account"<<endl;
                cin>>amt;
                int bal=ac.retdeposit()-amt;
                if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                    cout<<"Balance insufficient";
                else
                    ac.withdraw(amt);
            }
            int pos=(-1)* sizeof(ac);
            f.seekp(pos,ios::cur);
            f.write((char *) &ac, sizeof(account));
            cout<<"Balance successfully updated"<<endl;
            check=1;
	       }
    }
    f.close();
    if(check==0)
        cout<<"\tRecord not found."<<endl;
}



void intro()
{
    cout<<"\t\tBanking Project"<<endl<<endl;
    cout<<"Made by: Akshara Sundararajan"<<endl;
    cout<<"         GGIS"<<endl<<endl;
}

