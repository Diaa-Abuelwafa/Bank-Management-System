#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

class Helper
{
	public:

		static int choice_1_or_2(string msg)
		{
			int choice = 0;

			cout << msg;
			while (true)
			{
				cout << "Choose Number 1 or 2 : ";

				cin >> choice;

				if (choice == 1 || choice == 2)
				{
					break;
				}
				else
				{
					cout << "Wrong Choice , Try Again\n";
				}
			}
			
			return choice;
		}

		static vector<string>split(string s, char d)
		{
			vector<string>Tokens;
			stringstream ss(s);

			string Temp = "";
			while (getline(ss, Temp, d))
			{
				Tokens.push_back(Temp);
			}

			return Tokens;
		}

		static bool is_int(int n)
		{
			if (n >= numeric_limits<int>::min() && n <= numeric_limits<int>::max())
			{
				return true;
			}
			
			return false;
		}

		static int read_int(string msg)
		{
			int n;
			while (true)
			{
				cout << msg;
				cin >> n;

				if (Helper::is_int(n))
				{
					return n;
				}
				else
				{
					cout << "Sorry : Please Enter The Numeric Value\n";
				}
			}
		}

		static int get_current_year()
		{	
			time_t now = time(0);
			struct tm local_time;
			localtime_s(&local_time, &now);
			return local_time.tm_year + 1900;
		}

		static int get_current_month()
		{
			time_t now = time(0);
			struct tm local_time;
			localtime_s(&local_time, &now);
			return local_time.tm_mon + 1;
		}

		static pair<int, int> read_date(string s)
		{
			int month = s[0] - '0';

			int year = 0;
			int indx = 0;
			for (int i = s.size() - 1; i >= 1; --i)
			{
				year += (s[i] - '0') * pow(10, indx++);
			}

			return make_pair(month, year);
		}

		static long string_to_long(string s)
		{
			long temp = stol(s);

			return temp;
		}

		static double string_to_double(string s)
		{
			double temp = stod(s);

			return temp;
		}

		static bool contain_keyword(string s, string k)
		{
			int size = k.size();
			int indx = 0;

			int count = s.size() / k.size();

			while ((indx + size) <= s.size())
			{
				string temp = s.substr(indx++, size);

				if (temp == k)
				{
					return true;
					break;
				}

				--count;
			}

			return false;
		}
};

struct date
{
	public:
		int month;
		int year;

		date()
		{

		}

		date(int m, int y) : month(m), year(y)
		{
			// Initializer List Constructor
		}
};

class User
{
	private:
		string username;
		string password;

	public:

		User signup()
		{
			User U;

			string _username = "";
			cout << "Enter New Username : ";
			cin >> _username;

			U.username = _username;

			string _password;
			cout << "Enter Strong Password : ";
			cin >> _password;

			U.password = _password;

			add_user_to_file(U);

			return U;
		}

		void add_user_to_file(User U)
		{
			ofstream fout("users.txt", ios::app);

			if (fout.is_open())
			{
				fout << U.username << ",";
				fout << U.password << "\n";
			}

			fout.close();
		}

		vector<User> read_users_from_file()
		{
			vector<User>users;

			ifstream fin("users.txt");

			vector<string>users_data;
			string Temp = "";
			while (getline(fin, Temp))
			{
				users_data.push_back(Temp);
			}

			for (int i = 0; i < users_data.size(); ++i)
			{
				User U;

				vector<string>Temps = Helper::split(users_data[i], ',');

				U.username = Temps[0];
				U.password = Temps[1];

				users.push_back(U);
			}

			fin.close();

			return users;
		}

		pair<User, bool> login()
		{
			bool Flag = false;

			while (true)
			{
				string _username;
				cout << "Enter Your Username : ";
				cin >> _username;

				string _password;
				cout << "Enter Your Password : ";
				cin >> _password;

				User U;

				vector<User>users = read_users_from_file();

				for (int i = 0; i < users.size(); ++i)
				{
					if (users[i].username == _username && users[i].password == _password)
					{
						U.username = _username;
						U.password = _password;
						Flag = true;
						break;
					}
				}

				if (Flag)
				{
					return make_pair(U, true);
				}
				else
				{
					cout << "Wrong Username Or Password , Try Again\n";
					cout << "Press Any Button To Continue , To Cancel Press y\n";
					char ch;
					cin >> ch;

					if (ch == 'y')
					{
						return make_pair(U, false);
						break;
					}
				}
			}		
		}
};

class Account
{
	 public:

		long account_number;
		string name;
		long mobile;
		string email;
		double balance;
		date date_opened;
		string path_file;
		long account_number_temp = 91241;

		Account()
		{

		}

		Account(int a, int b) : date_opened(a, b) {}

		vector<Account> read_accounts_from_file()
		{
			vector<Account>accounts;

			ifstream fin("accounts.txt");

			vector<string>Temps;
			string Temp;
			while (getline(fin, Temp))
			{
				Temps.push_back(Temp);
			}

			for (int i = 0; i < Temps.size(); ++i)
			{
				vector<string>strs = Helper::split(Temps[i], ',');

				pair<int, int>P = Helper::read_date(strs[5]);
				Account A(P.first, P.second);

				A.account_number = Helper::string_to_long(strs[0]);
				A.name = strs[1];
				A.mobile = Helper::string_to_long(strs[2]);
				A.email = strs[3];
				A.balance = Helper::string_to_double(strs[4]);
				A.path_file = strs[6];
				accounts.push_back(A);
			}

			fin.close();

			return accounts;
		}

		bool add_account()
		{
			Account A(Helper::get_current_month(), Helper::get_current_year());

			int nums = get_nums_accounts();
			A.account_number = account_number_temp + nums;

			string _name;
			cout << "Enter Your Name Without Space : ";
			cin >> _name;
			A.name = _name;

			string _mobile;
			cout << "Enter Your Mobile Number : ";
			cin >> _mobile;
			A.mobile = Helper::string_to_long(_mobile);

			string _email;
			cout << "Enter Your Email Address : ";
			cin >> _email;
			A.email = _email;

			string _balance;
			cout << "Enter Initial Balance : ";
			cin >> _balance;
			A.balance = Helper::string_to_double(_balance);

			A.path_file = to_string(A.account_number) + ".txt";
			ofstream fout(A.path_file, ios::trunc);
			fout.close();

			add_account_to_file(A);

			return true;
		}

		void add_account_to_file(Account A)
		{
			ofstream fout("accounts.txt", ios::app);

			fout << A.account_number << ",";
			fout << A.name << ",";
			fout << A.mobile << ",";
			fout << A.email << ",";
			fout << A.balance << ",";
			fout << A.date_opened.month;
			fout << A.date_opened.year << ",";
			fout << A.path_file << "\n";

			fout.close();
		}

		int get_nums_accounts()
		{
			vector<Account>accounts = read_accounts_from_file();

			return accounts.size();
		}

		pair<bool, int> check_account_number(long l)
		{
			vector<Account> accounts = read_accounts_from_file();

			for (int i = 0; i < accounts.size(); ++i)
			{
				if (accounts[i].account_number == l)
				{
					return make_pair(true, i);
				}
			}

			return make_pair(false, -1);
		}

		bool delete_account()
		{
			long _account_number;
			
			while (true)
			{
				cout << "Enter The Account Number : ";
				cin >> _account_number;

				pair<bool, int> result = check_account_number(_account_number);

				if (result.first)
				{
					bool Flag = delete_account_from_file(result.second);
					if (Flag)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					cout << "Error : No Account With This Account Number Try Again\n";
				}
			}
		}

		bool delete_account_from_file(int i)
		{
			vector<Account>accounts = read_accounts_from_file();

			if (accounts[i].balance > 0)
			{
				cout << "Not Allow To Delete This Account Because It Have A Balance\n";
				return false;
			}

			accounts.erase(accounts.begin() + i);

			// Clear The File
			ofstream fout("accounts.txt", ios::trunc);
			fout.close();

			for (int i = 0; i > accounts.size(); ++i)
			{
				add_account_to_file(accounts[i]);
			}

			return true;
		}

		void modify_item(string s, int n, int indx, double budget)
		{
			vector<Account> accounts = read_accounts_from_file();

			if (n == 1)
			{
				accounts[indx].name = s;
			}
			else if (n == 2)
			{
				accounts[indx].mobile = Helper::string_to_long(s);
			}
			else if (n == 3)
			{
				accounts[indx].email = s;
			}
			else if (n == 4)
			{
				accounts[indx].balance -= budget;
			}
			else if (n == 5)
			{
				accounts[indx].balance += budget;
			}

			ofstream fout("accounts.txt", ios::trunc);
			fout.close();

			for (int i = 0; i < accounts.size(); ++i)
			{
				add_account_to_file(accounts[i]);
			}
		}

		bool modify_account()
		{
			long _account_number;
			pair<bool, int> result;
			
			while (true)
			{
				cout << "Enter The Account Number : ";
				cin >> _account_number;

				result = check_account_number(_account_number);

				if (result.first)
				{
					break;
				}
				else
				{
					cout << "Error : No Account With This Account Number Try Again\n";
				}
			}

			cout << "Enter The Item Which You Need To Modify It\n";
			cout << "1 - Name\n";
			cout << "2 - Mobile\n";
			cout << "3 - Email Address\n";

			int choice;
			while (true)
			{
				cout << "Choose Number Between 1 To 3 : ";
				cin >> choice;

				if (choice == 1 || choice == 2 || choice == 3)
				{
					break;
				}
				else
				{
					cout << "Please Enter The Value Between 1 To 3 Try Again\n";
				}
			}

			if (choice == 1)
			{
				string _name;
				cout << "Enterr new Name : ";
				cin >> _name;

				modify_item(_name, 1, result.second, 0);
			}
			else if (choice == 2)
			{
				string _mobile;
				cout << "Enterr new Mobile Number : ";
				cin >> _mobile;

				modify_item(_mobile, 2, result.second, 0);
			}
			else if (choice == 3)
			{
				string _email;
				cout << "Enterr new Email Address : ";
				cin >> _email;

				modify_item(_email, 3, result.second, 0);
			}

			return true;
		}

		void print_account(Account A)
		{
			cout << "--------------\n";
			cout << "Account Number : " << A.account_number << "\n";
			cout << "Name : " << A.name << "\n";
			cout << "E-mail : " << A.email << "\n";
			cout << "Balance : " << A.balance << "\n";
			cout << "Mobile : " << A.mobile << "\n";
			cout << "Date Opened : Month " << date_opened.month << " Yesr : " << date_opened.year << "\n";
		}

		void poor_search()
		{
			long _account_number;
			pair<bool, int>result;

			while (true)
			{
				cout << "Enter The Account Number : ";
				cin >> _account_number;
				result = check_account_number(_account_number);
				
				if (result.first)
				{
					break;
				}
				else
				{
					cout << "Error : No Account With This Account Number Try Again\n";
				}
			}

			vector<Account> accounts = read_accounts_from_file();
			int indx = result.second;

			print_account(accounts[indx]);
		}

		void advanced_search()
		{
			string _keyword;
			cout << "Enter Keyword : ";
			cin >> _keyword;

			vector<Account>accounts = read_accounts_from_file();

			for (int i = 0; i < accounts.size(); ++i)
			{
				if (Helper::contain_keyword(accounts[i].name, _keyword))
				{
					print_account(accounts[i]);
				}
			}
		}

		bool withdraw()
		{
			long _account_number;
			pair<bool, int> result;

			while (true)
			{
				cout << "Enter The Account Number : ";
				cin >> _account_number;

				result = check_account_number(_account_number);

				if (result.first)
				{
					break;
				}
				else
				{
					cout << "Error : No Account With This Account Number Try Again\n";
				}
			}
			
			double _balance;
			while (true)
			{
				cout << "Note that there is a maximum withdrawal limit for each transaction which is 10,000$ per transaction\n";
				cout << "What Is The Amount Needs To Be Withdrawn From This Account : ";
				cin >> _balance;

				if (_balance <= 10000)
				{
					bool Flag = cheack_balance(result.second, _balance);

					if (Flag)
					{
						modify_item("", 4, result.second, _balance);

						Account A = get_account(result.second);

						fetch_withdraw_transaction(_balance, A);

						break;
					}
					else
					{
						cout << "Sorry You Don't Have This Amount In Your Account Try Another Value\n";
					}
				}
				else
				{
					cout << "Must Withdraw Less Than 10.000$ Try Again\n";
				}
			}

			return true;
		}

		bool cheack_balance(int indx, double budget)
		{
			vector<Account>accounts = read_accounts_from_file();

			if (budget <= accounts[indx].balance)
			{
				return true;
			}

			return false;
		}

		Account get_account(int indx)
		{
			vector<Account>accounts = read_accounts_from_file();

			return accounts[indx];
		}

		void fetch_withdraw_transaction(double withdraw, Account A)
		{
			string path = A.path_file;

			ofstream fout(path, ios::app);

			fout << A.name << " : " << "Made A Withdraw Of " << withdraw << "$\n";

			fout.close();
		}

		void fetch_deposite_transaction(double withdraw, Account A)
		{
			string path = A.path_file;

			ofstream fout(path.c_str(), ios::app);

			fout << A.name << " : " << "Made A Deposite Of " << withdraw << "$\n";

			fout.close();
		}

		void fetch_transfer_transaction(Account A1, Account A2, double amount)
		{
			string path1 = A1.path_file;
			string path2 = A2.path_file;

			ofstream fout1(path1.c_str(), ios::app);

			fout1 << A1.name << " : " << "Made A Transfer Of " << amount << "$" << " To " << A2.account_number << "\n";

			fout1.close();

			ofstream fout2(path2.c_str(), ios::app);

			fout2 << A2.name << " : " << A2.account_number << " Send You " << amount <<"$" << " From " << A1.account_number << "\n";

			fout2.close();
		}

		bool deposite()
		{
			long _account_number;
			pair<bool, int> result;

			while (true)
			{
				cout << "Enter The Account Number : ";
				cin >> _account_number;

				result = check_account_number(_account_number);

				if (result.first)
				{
					break;
				}
				else
				{
					cout << "Error : No Account With This Account Number Try Again\n";
				}
			}

			double _balance;
			while (true)
			{
				cout << "Note that there is a maximum Deposite limit for each transaction which is 10,000$ per transaction\n";
				cout << "What Is The Amount Needs To Be Deposite To This Account : ";
				cin >> _balance;

				if (_balance <= 10000)
				{
					modify_item("", 5, result.second, _balance);

					Account A = get_account(result.second);

					fetch_deposite_transaction(_balance, A);

					break;
				}
				else
				{
					cout << "Must Deposite Less Than 10.000$ Try Again\n";
				}
			}

			return true;
		}

		bool transfer()
		{
			long _account_number_1;
			pair<bool, int>result1;
			while (true)
			{
				cout << "Enter Account Number That Need To Transfer From It :";
				cin >> _account_number_1;

				result1 = check_account_number(_account_number_1);

				if (result1.first)
				{
					break;
				}
				else
				{
					cout << "Sorry : No Account With This Account Number Try Again\n";
				}
			}

			long _account_number_2;
			pair<bool, int>result2;
			while (true)
			{
				cout << "Enter Account Number That Need To Transfer To It :";
				cin >> _account_number_2;

				result2 = check_account_number(_account_number_2);

				if (result2.first)
				{
					break;
				}
				else
				{
					cout << "Sorry : No Account With This Account Number Try Again\n";
				}
			}

			double _amount;
			while (true)
			{
				cout << "Note that there is a maximum Transfer limit for each transaction which is 10,000$ per transaction\n";
				cout << "What Is The Amount Needs To Transfer It : ";
				cin >> _amount;

				if (_amount <= 10000)
				{
					bool Flag = cheack_balance(result1.second, _amount);

					if (Flag)
					{
						modify_item("", 4, result1.second, _amount);
						modify_item("", 5, result2.second, _amount);

						Account A1 = get_account(result1.second);
						Account A2 = get_account(result2.second);

						fetch_transfer_transaction(A1, A2, _amount);

						break;
					}
					else
					{
						cout << "Sorry The Account Number : " << _account_number_2 << " Dont Have This Amount Try Again\n";
					}
				}
				else
				{
					cout << "Must Withdraw Less Than 10.000$ Try Again\n";
				}
			}

			return true;
		}

		void report()
		{
			long _account_number;
			pair<bool, int> result;

			while (true)
			{
				cout << "Enter The Account Number : ";
				cin >> _account_number;

				result = check_account_number(_account_number);

				if (result.first)
				{
					break;
				}
				else
				{
					cout << "Error : No Account With This Account Number Try Again\n";
				}
			}

			Account A = get_account(result.second);

			ifstream fin(A.path_file);

			vector<string>Temp;
			string temp = "";
			while (getline(fin, temp))
			{
				Temp.push_back(temp);
			}

			int counter = 0;
			int size = Temp.size();

			while (counter < 5 && counter < size)
			{
				cout << "-----------------------\n";
				cout << Temp[counter] << "\n";
				cout << "-----------------------\n";

				++counter;
			}

			fin.close();
		}

		void print()
		{
			cout << "What Is The Arrangement Method That You Want To Display The Data In ?\n";
			cout << "1 - Name\n";
			cout << "2 - Balance\n";

			int choice;
			while (true)
			{
				cout << "Choose Number From 1 To 2\n";
				cin >> choice;
				
				if (choice == 1 || choice == 2)
				{
					break;
				}
				else
				{
					cout << "Please Enter The Numeric Value Between 1 To 2 Try Again\n";
				}
			}

			vector<Account>accounts = read_accounts_from_file();

			if (choice == 1)
			{
				sort(accounts.begin(), accounts.end(), Account::compare_by_name);
			}
			else if (choice == 2)
			{
				sort(accounts.begin(), accounts.end(), Account::compare_by_balance);
			}

			for (int i = 0; i < accounts.size(); ++i)
			{
				print_account(accounts[i]);
			}
		}

		static bool compare_by_name(const Account& A1, const Account& A2)
		{
			return A1.name <= A2.name;
		}

		static bool compare_by_balance(const Account& A1, const Account& A2)
		{
			return A1.balance <= A2.balance;
		}
};

class bank_sys
{
	public:
		void launch()
		{
			string msg1 = "Menu\n1 - Login\n2 - Sign Up\n";
			int choice1 = Helper::choice_1_or_2(msg1);

			// Make Object From Class User
			User U;

			bool Flag = true;
			pair<User, bool> P;

			switch (choice1)
			{
			case 1:
				P = U.login();
				U = P.first;

				if (P.second == false)
				{
					Flag = false;
					cout << "GoodBye :)\n";
				}
				break;

			case 2:
				U = U.signup();
				break;
			}

			if (Flag)
			{
				while (true)
				{
					cout << "---------------------------\n";
					cout << "Menu Options :\n";
					cout << "1 - Add Account\n"; // Done
					cout << "2 - Delete Account\n"; // Done
					cout << "3 - Modify Account\n"; // Done
					cout << "4 - Search For Account\n"; // Done
					cout << "5 - Advanced Search For Account\n"; // Done
					cout << "6 - Withdraw Operation\n"; // Done
					cout << "7 - Deposite Operation\n"; // Done
					cout << "8 - Transfer Operation\n"; // Done
					cout << "9 - Report Operation\n"; // Done
					cout << "10 - Print Operation\n"; // Done
					cout << "11 - Quit\n";
					cout << "----------------------------\n";

					int choice2;
					while (true)
					{
						string msg2 = "Enter Your Choice From 1 To 11 : ";
						choice2 = Helper::read_int(msg2);

						if (choice2 >= 1 && choice2 <= 11)
						{
							break;
						}
						else
						{
							cout << "Please Enter Choice From 1 To 11\n";
						}
					}

					// For Use Methods
					Account Temp(Helper::get_current_month(), Helper::get_current_year());

					bool Flag1, Flag2, Flag3, Flag4, Flag5, Flag6, Flag7 = true;
					switch (choice2)
					{
					case 1:

						Flag1 = Temp.add_account();

						if (Flag1)
						{
							cout << "Successfully Added This Account\n";
						}

						break;

					case 2:

						Flag2 = Temp.delete_account();

						if (Flag2)
						{
							cout << "Successfully Deleted This Account\n";
						}
						else
						{
							cout << "This Account Not Deleted\n";
						}

						break;

					case 3:

						Flag3 = Temp.modify_account();

						if (Flag3)
						{
							cout << "Successfully Modified This Account\n";
						}

						break;

					case 4:

						Temp.poor_search();

						break;

					case 5:

						Temp.advanced_search();

						break;

					case 6:

						Flag4 = Temp.withdraw();

						if (Flag4)
						{
							cout << "Successfully Withdraw Operation\n";
						}

						break;

					case 7:

						Flag5 = Temp.deposite();

						if (Flag5)
						{
							cout << "Successfully Deposite Operation\n";
						}

						break;

					case 8:

						Flag6 = Temp.transfer();

						if (Flag6)
						{
							cout << "Successfully Transfer Operation\n";
						}

						break;

					case 9:

						Temp.report();

						break;

					case 10:

						Temp.print();

						break;

					case 11:

						Flag7 = false;

						break;
					}

					if (Flag7)
					{
						string msg3 = "Are You Need To Make Another Operation\n1 - Yes\n2 - No\n";
						int choice3 = Helper::choice_1_or_2(msg3);
						cout << "----------------------------\n";

						if (choice3 == 2)
						{
							cout << "GoodBye :)\n";
							break;
						}
					}
					else
					{
						cout << "GoodBye!\n";
						break;
					}
				}
			}
		}
};

int main()
{
	cout << "================= Bank Management System ==================\n";
	
	bank_sys system;
	system.launch();
}