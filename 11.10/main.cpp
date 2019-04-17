#include <iostream>
using namespace std;
//base class
class Account
{
private:
	double balance;
public:
	Account(double ba);
	~Account();
	int credit(double cash);
	int debit(double cash);
	double getBalance();
	int setBalance(double);
};
//the sub class
class SavingAccount : public Account
{
private:
	double interestrate;
public:
	SavingAccount(double ba, double ite);
	~SavingAccount();
	double calculate_Interest();
};
// the sub class of CheckingAccount
class CheckingAccount : public Account
{
private:
	double fee;
public:
	CheckingAccount(double ba,double fe);
	~CheckingAccount();
	int credit(double cash);
	int debit(double cash);
};

 //Account_ex.cpp
//对基类 派生类的 声明

/*
	Author By : Yumaosheng
	Number :	21140211080
	Date : 20141109
*/
#include <iostream>
using namespace std;

//the Implementation  of construction method
Account::Account(double ba)
{
	balance = ba;
}
//the Implementation  of deconstruction method
Account::~Account()
{
	balance = 0.0;
}
// the Implementation of credit method
// add some money to the Account
int Account::credit(double cash)
{
	// add the money to balance
	balance += cash;
	return 0;
}
// the Implementation of credit method
// get some money from the Account
int Account::debit(double cash)
{
	//if get the more money than the balance
	if ((balance - cash) < 0.0)
	{
		cout<<"debit amount exceeded account balance"<<endl;
		return 1;
	}else
	{
		balance -= cash;
	}
	return 0;
}
// the Implementation of getBalance method
// return the balance
double Account::getBalance()
{
	return balance;
}
// the Implementation of setBalance() method
int Account::setBalance(double cash)
{
	balance = cash;

	return 0;
}
// the Implementation of SavingAccount
// the Implementation of construction method of SavingAccount
//调用基类的构造函数
SavingAccount::SavingAccount(double ba, double inte) :Account(ba)
{
	// balance = ba;
	interestrate = inte;
}
// the Implementation of deconstruction method of SavingAccount
SavingAccount::~SavingAccount()
{
	// balance = 0.0;
	interestrate = 0.0;
}

double SavingAccount::calculate_Interest()
{
	//directly using the base's method getBalance()
	return (getBalance()*interestrate)/100.0;
}

// the Implementation of CheckingAccount
// the Implementation of construction method of CheckingAccount
// 调用基类的构造函数
CheckingAccount::CheckingAccount(double ba , double fe) : Account(ba)
{
	// balance = ba;
	// cout<<getBalance()<<endl; //test the construction
	fee = fe;
}
CheckingAccount::~CheckingAccount()
{
//	this->balance = 0.0;
	fee = 0.0;
}
// the  Implementation of CheckingAccount's credit
int CheckingAccount::credit(double cash)
{
	if (!Account::credit(cash))
	{
		if (getBalance() > fee)
		{
			// balance -= fee;
			Account::debit(fee);
		}else
		{
			// balance -= cash;
			Account::debit(cash);
			cout<<"Transaction fee exceeded account balance while crediting"<<endl;
		}
	}
	return 0;
}
// the Implementation of CheckingAccount's debit
int CheckingAccount::debit(double cash)
{
	if (! Account::debit(cash))
	{
		if (Account::getBalance() > fee)
		{
			// balance -= fee;
			Account::debit(fee);
		}else
		{
			// balance +=cash;
			Account::credit(cash);
			cout<<"Transaction fee exceeded account balance while debiting"<<endl;
		}
	}
	return 0;
}



/*
	Author By : Yumaosheng
	Number :	21140211080
	Date: 20141109
*/
#include <iostream>

int main(int argc, char const *argv[])
{
	//generate a SavingAccount object
	SavingAccount saving( 100, 3 );
	// double money = saving.calculate_Interest();
	// cout<<money<<endl;
	CheckingAccount checking1( 100, 5 );
	CheckingAccount checking2( 50, 5 );
	// test the SavingAccount
	cout<<"SavingAccount:"<<endl;
	// debit 200 yuan
	saving.debit(200);
	// debit 40 yuan
	saving.debit(40);
	// credit 50 yuan
	saving.credit(50);
	// debit 49 yuan
	saving.debit(49);
	// debit 43 yuan
	saving.debit(43);
	// credit 1 yuan
	saving.credit(1);

	saving.setBalance(saving.calculate_Interest()+saving.getBalance());

	cout<<saving.getBalance()<<endl;

	// test the CheckingAccount
	cout <<"Checking Account1:"<< endl;
	// debit 200
	checking1.debit(200);
	// debit 40
	checking1.debit(40);
	// credit 50
	checking1.credit(50);
	// debit 49
	checking1.debit(49);
	// debit 43
	checking1.debit(43);
	// credit 1
	checking1.credit(1);

	cout<<checking1.getBalance()<<endl;

	// test the checking2
	cout <<"Checking Account2:"<< endl;
	// debit 200
	checking2.debit(200);
	// debit 40
	checking2.debit(40);
	// credit 50
	checking2.credit(50);
	// debit 49
	checking2.debit(49);
	// debit 43
	checking2.debit(43);
	// credit 1
	checking2.credit(1);

	cout<<checking2.getBalance()<<endl;

	return 0;
}
