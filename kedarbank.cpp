#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <string.h>
#include <sstream>
#include <stack>




using namespace std;

//class declerations
class bank
{
public:
    float totalsaving;
     float totalchecking;
     int accnotrace;
     int exectrace;

};


class user {

public:
    stack<string> transactionhistory;
    int accountnumber;
    int pin;
    char name[20];
    int acctype;//0=saving; 1=checking; 2= both
    float sbalance;
    float cbalance;
    bool premium;
    int numberoftransactions;
    int lastinterest;
    void transactionsplusplus();
    void showuser();
    float withdraw ();
    void deposit();
    void createaccount();
    void addusertrace(string);
    void getinterest();
    void writeuserfile(string);


};
user u;
bank b;
//function decleration for main
void writeuser(user);
void deleteuser(int);
void finduser(int);
void modifyuser(int);
void writebank(bank);
bank restorebank();
void goswitch(int,int);
void addexectrace(int,string);
void modifyuserproper(user);

fstream fp;
int maxaccountnumber;
int executiontrace=1;

//main
int main(void)
{

    b = restorebank();
    addexectrace(0,"restoring bank state");
    maxaccountnumber=b.accnotrace;
    //cout<<"The bank accnotrace is:"<<b.accnotrace<<endl;
    executiontrace=b.exectrace;
    int accno=-999,option,pin;
    //user u;
    freshstart:
    cout << "\t\t\t\t\tWelcome to Kedar's Bank ABM" << endl;
	cout << "======================================================================================" << endl;
	while(true)
    {
        cout << "If you are new to our bank and want to open an account , please contact the bank manager at your nearest branch. \n\n\nIf you are an existing customer, Please enter your accno to Login into the ABM (enter -888 to exit)" << endl;
        cout<<"accno: ";
        cin>>accno;

        if((accno==-888)||((accno>0)&&(accno<100))||(accno>maxaccountnumber)||accno<-2)
        {
            cout<<"\nNo Such User. Quitting Program now. Thanks."<<endl;
            return 0;
        }

        if((accno>=100)&&(accno <= maxaccountnumber))
         {
                finduser(accno);

                cout<<"Enter your four digit PIN"<<endl;
                cin>>pin;
                if(pin==(u.pin))
                {
                    addexectrace(accno,"has logged in");
                mainoptions:

                cout << "------------------------------------------------------" << endl;
                cout << "           Please enter your choice of operation.  " << endl;
                cout << "                1. Check balance                  " << endl;
                cout << "                2. Withdrawal                     " << endl;
                cout << "                3. Deposit                        " << endl;
                cout << "                4. Transfer Funds(within account) " << endl;
                cout << "                5. Transfer to different person   " << endl;
                cout << "                6. Print transaction history      " << endl;
                cout << "                7. Get Interest                         " << endl;
                cout << "                8. Logout                         " << endl;
                cout << "------------------------------------------------------" << endl;
            }
             else
            {
                cout<<"You have entered the Wrong PIN. You will be logged out."<<endl;
                addexectrace(accno,"Entered wrong pin");
                goto wrongpin;
             }

         }
          else if (accno == -1)
            {
                mainoptions1:
                addexectrace(accno,"has logged in");
                cout << "------------------------------------------------------" << endl;
                cout<<" Welcome, You have been identified as the manager of the branch."<<endl;
                cout << "           Please enter your choice of operation.  " << endl;
                cout << "               1. Open Bank Account                 " << endl;
                cout << "               2. Modify an Account                " << endl;
                cout << "               3. Close account     " << endl;
                cout << "               4. Print details of specific customer  " << endl;
                cout << "               5. Print details of all the customers of the bank        " << endl;
                cout << "               6. Some bank stats                           " << endl;
                cout << "               7. Print a user's activity             " << endl;
                cout << "               8. Logout                         " << endl;
                cout << "------------------------------------------------------" << endl;
            }
        else if (accno == -2)
            { addexectrace(accno,"has logged in");
            mainoptions2:
                cout << "------------------------------------------------------" << endl;
                cout<<" Welcome, You have been identified as IT Engineer of the branch."<<endl;
                cout << "           Please enter your choice of operation.  " << endl;
                cout << "               1. Switch Execution Trace On/Off           " << endl;
                cout << "               2. Logout                            " << endl;
                cout << "------------------------------------------------------" << endl;
            }

        cout<<"Option: "<<endl;
        cin>>option;
        goswitch(accno,option);
        if ((option == 2 && accno == -2) || (accno == -1 && option == 8) || (accno > 0 && option == 8))
        {
            accno = -999;
            goto freshstart;
        }
        else if(accno ==-2)
         goto mainoptions2;
        else if(accno==-1)
            goto mainoptions1;
        else if (accno>0)
            goto mainoptions;

    }
    wrongpin:
    cout<<"\n\n\n\n\t\t Thankyou for using Kedar's Bank ABM. Hope to see you back soon. "<<endl;
    getch();
    return 0;
}
void goswitch(int accno, int option)
{
	int opt = 0;
	int temp = 0;
	//user u;
	if (accno > 0)
    {
		if (option >= 1 && option <= 8)
		{
			opt = option; // no adjustments needed
			//finduser(accno);
		}
        else
        {
            cout<<"Invalid Option"<<endl;
            return;
        }
	}
	else if (accno == -1)
    {
		if (option >= 1 && option <= 8)
        {
			opt = option + 8; // adjust for the previous type of user
		}
		else{cout<<"Invalid Option"<<endl; return;}
	}
	else if (accno == -2)
	{
		if (option == 1 || option == 2)
		{
            opt = option + 16; // adjust for the previous two types of users
		}
		else {cout << "Invalid option"<<endl; return;}
	}

	switch (opt) {
    case 1:
        //cout<<"Acc no in switch is "<<accno<<endl;
        finduser(accno);
        addexectrace(accno," checked balance");
        u.showuser();
        u.addusertrace("Checked Balance");
        u.writeuserfile("Checked Balance");
        break;
    case 2:
       finduser(accno);
       addexectrace(accno," withdrew amount");
       u.addusertrace("Withdrew amount");
       u.writeuserfile("Checked Balance");
        u.withdraw();

        modifyuserproper(u);
        break;
    case 3:
        finduser(accno);
        u.deposit();
        addexectrace(accno," deposited amount");
       u.addusertrace("deposited amount");u.writeuserfile("Deposited amount");
        modifyuserproper(u);
        break;
    case 4:
        {
        if(u.acctype!=2)
            cout<<"U need 2 accounts. Contact manager"<<endl;
        else
        {
            cout<<"Enter 1 for Savings to Checking or 0 for Checking to Savings"<<endl;
            cin>>temp;
            cout<<"Enter the amount you want to transfer. "<<endl;
            float amount1;
            cin>>amount1;
            if(temp)
            {
                u.cbalance=u.cbalance+amount1;
                u.sbalance=u.sbalance-amount1;
            }
            else
            {
                u.cbalance=u.cbalance-amount1;
                u.sbalance=u.sbalance+amount1;
            }
            addexectrace(accno," transferred within account");
       u.addusertrace("Transferred withing account");
       u.writeuserfile("Transferred withing account");
        modifyuserproper(u);
        }
        break;}
    case 5:
        {   int temp1;
            //user temp;
            float amount1;
            finduser(accno);
            amount1 = u.withdraw();
            cout<<amount1<<" was taken from your account"<<endl;
            modifyuserproper(u);
            cout<<"Enter the receivers account number"<<endl;
            cin>>temp1;
            finduser(temp1);
            addexectrace(accno," transferred to other accounts");
            u.addusertrace("Transferred to other accounts");
            u.writeuserfile("Transferred to other accounts");
            cout<<"Transferring "<<amount1<<" to "<<u.name;
            u.sbalance+=amount1;
            modifyuserproper(u);
            cout<<"Transfer Complete"<<endl;
            finduser(accno);
            break;
        }
    case 6:
        {
            addexectrace(accno," asked for statement");
            u.addusertrace("Asked for Statement");
            //u.writeuserfile("Asked for Statement");
            cout<<"Last transactions are"<<endl;//TODO
            /*stringstream ss;
            ss << u.accountnumber;
            string checkacc = ss.str();
            ifstream in("usertrace.txt");
            string str;
            int linecntr=0;
            while(in)
            {
            in.gets();
            //if(in) cout << str << endl;
            //linecntr+=1;
            if(strcmp(str,checkacc)==0)
*/        //  string str;
           //while(u.transactionhistory.empty()==false)
            //{
           //     str = u.transactionhistory.
           // }
            //}

        stringstream ss;
        ss << u.accountnumber;
        string name = ss.str();
        name = name + ".txt";
        ifstream inFile(name.c_str());

        string line;
while (getline(inFile, line))
    cout<<line<<endl;
inFile.close();
            break;

        }
    case 7:
        {
            finduser(accno);
            u.getinterest();
            modifyuserproper(u);
            addexectrace(accno," interest was given");
            u.addusertrace("Interest was given by bank");
            u.writeuserfile("Interest was given by bank");

            break;
        }
    case 9:
        {
            user newuser;
            newuser.createaccount();
            writeuser(newuser);
            addexectrace(accno," Created new account");
            //addusertrace(accno,"Created new account");
            cout<<"New User Updated in records"<<endl;
            break;
        }
    case 10:
        {
            int temp1;
            cout<<"Enter the account number to be modified"<<endl;
            cin>>temp1;
            modifyuser(temp1);
            addexectrace(accno," Modified account");
            break;
        }
    case 11:
        {
            int temp1;
            user temp;
            addexectrace(accno," deleted account");
            cout<<"Enter the account number to be deleted"<<endl;
            cin>>temp1;
            finduser(temp1);
            if(temp.sbalance==0&&temp.cbalance==0)
                deleteuser(temp1);
            else
                cout<<"As balances are not zero. Cannot delete."<<endl;
            break;
        }
    case 12:
        {
            int temp1;
            user temp;
            addexectrace(accno," checked on a specific user");
            cout<<"Enter the account number"<<endl;
            cin>>temp1;
            finduser(temp1);
            u.showuser();
            break;
        }
    case 13:
        {
            int i;
            user temp;
            addexectrace(accno," asked for info of all users");
            //for(i=100;i<=maxaccountnumber;i++)
            //{addexectrace(accno," asked for info of all users");
             //   finduser(i);
              //  u.showuser();
            //}
            fp.open("user.dat",ios::in);

 while(fp.read((char*)&u,sizeof(user)))
 {
  u.showuser();
 }
 fp.close();
        break;
        }
    case 14:
        {
            b= restorebank();
            cout<<"Total Number of Customers = "<<b.accnotrace-100<<endl;
            cout<<"Total amount in Savings = "<<b.totalsaving<<endl;
            cout<<"Total Amount in Checking = "<<b.totalchecking<<endl;
            addexectrace(accno," asked for bank info");
            break;
        }
    case 15:
        {
            addexectrace(accno," asked for user operations");
            cout<<"Here are the last 20 operations done by users on this abm"<<endl;
            ifstream in("usertrace.txt");
            char str[255];
            int linecntr=0;
            while((in)&&(linecntr<20))
            {
            in.getline(str, 255);
            if(in) cout << str << endl;
            linecntr+=1;

            }

            in.close();

            break;
        }
    case 17:
        {
            char c;
            if(executiontrace)
                cout<<"Execution trace is ON. Wanna turn off? (y/n)"<<endl;
            else
                cout<<"Execution trace is OFF. Wanna turn on? (y/n)"<<endl;
            cin>>c;
            if(c=='y')
            {

            addexectrace(accno," toggled execution trace flag");
                executiontrace=!executiontrace;}
            break;
        }
    case 8:
    case 16:
    case 18:
        {
            addexectrace(accno," Logged Off");
            cout<<"You will be logged Off."<<endl;
            cout<<"\n\n\n\n\t\t Thankyou for using Kedar's Bank ABM. Hope to see you back soon. "<<endl;
            break;
        }


	default:
		cout << "Invalid user ID or option...exiting";
		break;
	} // end switch statement

	return;
}
////////////////////////////////////////////////////////////////////////

void writeuser(user u)
{
    addexectrace(-2," called writeuser()");
	/*ofstream outFile;
	outFile.open("user.dat",ios::binary|ios::app);
	outFile.write(reinterpret_cast<char *> (&u), sizeof(user));
	outFile.close();*/
	fp.open("user.dat",ios::out|ios::app);
 fp.write((char*)&u,sizeof(user));
 fp.close();
}
void finduser(int accno)
{
	//user u;
	addexectrace(accno," finduser() called");
	bool flag=false;
	fp.open("user.dat",ios::in);
 while(fp.read((char*)&u,sizeof(user)))
 {
  if(u.accountnumber==accno)
  {

   flag=true;
   fp.close();
  // return (u);
  }
}

if (flag==false)
    {cout<<"\n!!Account number does not exist!!"<<endl;}

}

void modifyuser(int accno)
{
    addexectrace(accno," modifyuser() caled");
	bool found=false;
	user u;
	char yesorno;
	fp.open("user.dat",ios::in|ios::out);
	while(fp.read((char*)&u,sizeof(user)) && found==false)
 {
  if(u.accountnumber==accno)
  {
			u.showuser();
			if(u.acctype==0)
            {
                cout<<"Do you want to add checking account (press y for Yes or n for No) ?"<<endl;
                cin>>yesorno;
                if(yesorno=='y')
                {
                    cout<<"Enter the deposit amount (should be greater than = 1000)"<<endl;
                    cin>>u.cbalance;
                    b.totalchecking+=u.cbalance;
                    u.acctype=2;
                    goto skip;
                }


            }
            else if(u.acctype==1)
            {
                cout<<"Do you want to add savings account (press y for Yes or n for No) ?"<<endl;
                cin>>yesorno;
                if(yesorno=='y')
                {
                    cout<<"Enter the deposit amount (should be greater than = 500)"<<endl;
                    cin>>u.sbalance;
                    b.totalsaving+=u.sbalance;
                    u.acctype=2;
                    goto skip;
                }


            }
            else if(u.acctype ==2)
                {cout<<"User already has both accounts. To delete go back to Main Menu and select proper option."<<endl;}
			skip:
			int pos=-1*sizeof(u);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&u,sizeof(user));
			cout<<"\n\n\t Record Updated";
			found=true;
			fp.close();
			writebank(b);


		  }
	}


	if(found==false)
        cout<<"No record found. Some problem"<<endl;
}
void modifyuserproper(user usr)
{
    addexectrace(usr.accountnumber," modifyuserproper() called");
	bool found=false;
	//user u;
	fp.open("user.dat",ios::in|ios::out);
	while(fp.read((char*)&u,sizeof(user)) && found==false)
	{

		if(u.accountnumber==usr.accountnumber)
		{
			int pos=-1*sizeof(u);
   fp.seekp(pos,ios::cur);
   fp.write((char*)&usr,sizeof(user));
   cout<<"\n\n\t Record Updated";
   found=true;
   fp.close();

		  }
	}


	if(found==false)
        cout<<"No record found. Some problem"<<endl;


}

void deleteuser(int accno)
{
	//user u;
	fp.open("user.dat",ios::in|ios::out);
 fstream fp2;
 fp2.open("Temp.dat",ios::out);
 fp.seekg(0,ios::beg);
 while(fp.read((char*)&u,sizeof(user)))
 {
  if(u.accountnumber!=accno)
  {
   fp2.write((char*)&u,sizeof(user));
  }
 }
 fp2.close();
 fp.close();
 remove("user.dat");
 rename("Temp.dat","user.dat");
 cout<<"\n\n\tRecord Deleted ..";
}

void writebank(bank b)
{
	ofstream outFile;
	outFile.open("bank.dat",ios::binary|ios::trunc);
	outFile.write(reinterpret_cast<char *> (&b), sizeof(bank));
	outFile.close();
}

bank restorebank()
{
    addexectrace(0," restorebank() called");
	bank b;
	bool flag=false;
	ifstream inFile;
	inFile.open("bank.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
	}
    inFile.read(reinterpret_cast<char *> (&b), sizeof(bank));
	inFile.close();
    return b;
}



void addexectrace(int accno,string toput)
{
    if(executiontrace==1)
    {
    time_t now = time(0);
    string date = ctime(&now);
    fstream outFile;
	outFile.open("executiontrace.txt",ios::out|ios::app);
	outFile<<date<<accno<<" "<<toput<<endl;
	outFile.close();
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////user functions.
void user::addusertrace(string toput)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = ctime(&now);
    fstream outFile;
	outFile.open("usertrace.txt",ios::out|ios::app);
	outFile<<accountnumber<<" "<<1900 + ltm->tm_year<<"/"<<1 + ltm->tm_mon<<"/"<<ltm->tm_mday<<" "<<toput<<endl;
	outFile.close();
}
void user::writeuserfile(string toput)
{
        stringstream ss;
        ss << accountnumber;
        string name = ss.str();
        name = name + ".txt";
        ofstream outFile(name.c_str(),ios::app);
        outFile<<toput<<endl;
        outFile.close();

}
void user::showuser()
{
    addexectrace(u.accountnumber," showuser() called");
    cout<<"Account Number: "<<accountnumber<<endl;
    cout<<"Name :"<<name<<endl;
    cout<<"Number of transactions: "<<numberoftransactions<<endl;
    if (premium)
        cout<<"You are a premium customer"<<endl;
    cout<<"Last interest: "<<lastinterest<<endl;
    if(acctype==0)
    {
        cout<<"Savings balance is :"<<sbalance<<endl;
        cout<<"Do not have a checking account. "<<endl;
    }
    else if(acctype==1)
    {
        cout<<"Checking balance is :"<<cbalance<<endl;
        cout<<"Do not have a savings account. "<<endl;
    }
    else
    {
        cout<<"Savings balance is :"<<sbalance<<endl;
        cout<<"Checking balance is :"<<cbalance<<endl;
    }
}

void user::getinterest()
{
    if(acctype==0||acctype==2){
    addexectrace(accountnumber," called getinterest()");
    float r = 1.0;
    if (premium)
        r=1.5;
    time_t now1 = time(0);
    tm *ltm1 = localtime(&now1);
    if(abs(lastinterest-(ltm1
                         ->tm_mon+1))>1)
        sbalance=sbalance+((sbalance*abs(lastinterest-(ltm1->tm_mon+1))*r)/100);

    lastinterest=ltm1->tm_mon+1;
    }
}
float user::withdraw()
{
    addexectrace(accountnumber," called withdraw()");
    bank b = restorebank();
    showuser();
    float amount;
    char yon='k';
    switch(acctype)
    {
    case 0:{
        cout<<"Enter the amount you wish to withdraw"<<endl;
        cin>>amount;
        if((sbalance-amount)<500)
            cout<<"Your balance will become/is less than 500. You should maintain more than 500 balance."<<endl;
        if((sbalance-amount)<0)
            cout<<"Cannot withdraw this amount. Insufficient balance."<<endl;
        else
        {
        sbalance=sbalance-amount;
        b.totalsaving=b.totalsaving-amount;
        transactionsplusplus();
        }
        break;}
    case 1:
{

        cout<<"Enter the amount you wish to withdraw"<<endl;
        cin>>amount;
        if(((cbalance-amount)<1000)&&cbalance>=1000)
            {
            cout<<"Your balance will become less than 1000. You should maintain more than 1000 balance.\n You will be charged a fee of 2$ for going below 1000. press y to go ahead and n to stop"<<endl;

            cin>>yon;
            if (yon=='n')
            {
                goto katle;
            }

            }
        if((cbalance-amount)<0)
        {
            cout<<"Cannot withdraw this amount. Insufficient balance."<<endl;
        }
        else
        {
        cbalance=cbalance-amount;
        b.totalchecking=b.totalchecking-amount;
        if (yon=='y')
            {cbalance=cbalance-2;}
        transactionsplusplus();
        }
        break;}
    case 2:
        cout<<"Enter s for Saving and c for Checking"<<endl;
        cin>>yon;
        switch(yon)
        {
           case 's':
                cout<<"Enter the amount you wish to withdraw"<<endl;
                cin>>amount;
                if((sbalance-amount)<500)
                    cout<<"Your balance will become/is less than 500. You should maintain more than 500 balance."<<endl;
                if((sbalance-amount)<0)
                    cout<<"Cannot withdraw this amount. Insufficient balance."<<endl;
                else
                {
                sbalance=sbalance-amount;
                b.totalsaving=b.totalsaving-amount;
                transactionsplusplus();
                }
                break;
            case 'c':
                cout<<"Enter the amount you wish to withdraw"<<endl;
                cin>>amount;
                if(((cbalance-amount)<1000)&&cbalance>1000)
                    {
                    cout<<"Your balance will become less than 1000. You should maintain more than 1000 balance.\n You will be charged a fee of 2$ for going below 1000. press y to go ahead and n to stop"<<endl;

                    cin>>yon;
                    if (yon=='n')
                    {
                        goto katle;
                    }

                    }
                if((sbalance-amount)<0)
                {
                    cout<<"Cannot withdraw this amount. Insufficient balance."<<endl;
                }
                else
                {
                cbalance=cbalance-amount;
                b.totalchecking=b.totalchecking-amount;
                if (yon=='y')
                    cbalance=cbalance-2;
                transactionsplusplus();
                }
                break;
        }

        katle:
            writebank(b);

    }
return amount;
}
void user::deposit()
{
    addexectrace(accountnumber," called deposit()");
    bank b = restorebank();
    char c;
    float amount;
    cout<<"Enter the amount"<<endl;
    cin>>amount;
    if(acctype==0)
    {
        if(!(sbalance>=500))
            cout<<"Your balance is less than 500. Please keep above 500"<<endl;
        sbalance+=amount;
        b.totalsaving+=sbalance;
    }
    if(acctype==1)
    {
        if(!(cbalance>=1000))
            cout<<"Your balance is less than 1000. Please keep above 1000"<<endl;
        cbalance+=amount;
        b.totalchecking+=cbalance;
    }
    if(acctype==2){
    cout<<"Enter s for savings and c for checking"<<endl;
    cin>>c;
    if(c=='s')
    {
        if(!(sbalance>=500))
            cout<<"Your balance is less than 500. Please keep above 500"<<endl;
        sbalance+=amount;
        b.totalsaving+=sbalance;
    }
    else
    {
        if(!(cbalance>=1000))
            cout<<"Your balance is less than 1000. Please keep above 1000"<<endl;
        cbalance+=amount;
        b.totalchecking+=cbalance;
    }}
    transactionsplusplus();
    writebank(b);
}
void user::createaccount()
{
    addexectrace(-1," called createaccount()");
    bank b = restorebank();
    char c;
    float amount;
    accountnumber=maxaccountnumber;
    maxaccountnumber+=1;
    b.accnotrace=maxaccountnumber;
    cout<<"Account Number is: "<<accountnumber<<endl;
    cout<<"Enter name";
    //cin.ignore();
    scanf("%s",&name);
    time_t now2 = time(0);
    tm *ltm2 = localtime(&now2);
    lastinterest=ltm2->tm_mon;
    cout<<"Press s for creating Savings account and c for creating checking account.";
    cin>>c;
    if(c=='s')
    {
        acctype=0;
        cout<<"Enter amount to deposit. Must me >500"<<endl;
        cin>>sbalance;
        b.totalsaving+=sbalance;
        cbalance=0;
    }
    else
    {
        acctype=1;
        cout<<"Enter amount to deposit. Must me >1000"<<endl;
        cin>>cbalance;
        b.totalchecking+=cbalance;
        sbalance=0;
    }
    numberoftransactions=0;
    cout<<"Ask user to enter numeric pin"<<endl;
    cin>>pin;
    cout<<"Wanna be a premium member? One time charge of 100$ 1 Yes 0 for No. \n .1$ per 5 transactions Else it is .1$ per 4 transactions as banking fee. "<<endl;
    cin>>premium;
    writebank(b);
    cout<<"Account Created Successfully. Account Number is "<<accountnumber<<endl;
}
void user::transactionsplusplus()
{
    addexectrace(accountnumber," called transactionsplusplus()");
if(premium)
{
 numberoftransactions=(numberoftransactions+1)%4;
 if (numberoftransactions==0)
        {
            if (acctype==0)
                sbalance=sbalance-1;
            else
                cbalance=cbalance-1;
        }
}
else
{
 numberoftransactions=(numberoftransactions+1)%2;
 if (numberoftransactions==0)
        {
            if (acctype==0)
                sbalance=sbalance-1;
            else
                cbalance=cbalance-1;
        }
}

}


