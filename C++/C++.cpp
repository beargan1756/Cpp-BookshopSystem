#include<iostream>
#include<iomanip>
#include<string>
#define NOMINMAX //to avoid naming conflicts between the Windows.h macros and the standard library functions.
#include <limits> //for input stream manipulation
#include <Windows.h> //for system-specific functions, such as system("cls")
#include <cstdlib>
#include<ctime>
#include<map> //for using associative containers, such as std::map,
#include <list> //for using sequence containers
#include <sstream>//for date validation check in sales report

using namespace std;

struct Suggestion {
	string suggestionText;
	string email;
	bool replied = false;
};

list<Suggestion> suggestions; // Global list to store all suggestions

struct Date {
	int day;
	int month;
	int year;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.year != rhs.year) {
		return lhs.year < rhs.year;
	}
	else if (lhs.month != rhs.month) {
		return lhs.month < rhs.month;
	}
	else {
		return lhs.day < rhs.day;
	}
}

map<string, double> dailyEarnings;

const string line1 = "===============================================================================";
const string line2 = "------------------------------------------------------------------";

struct Invoice {
	int id;
};

const int MAX_INVOICE = 100;// maximum number of invoices allowed

struct Receipt {
	int id;
};

Receipt receipts[100]; // assume 100 receipts maximum

//////////////////////////////////////////////struct of books
struct Book {
	string title;
	string genre;
	string category;
	double price = 0.00;
	int quantity = 0;
};

////////////buy book array
const int fictionHorrorSize = 3;
Book fictionHorror[fictionHorrorSize] = {
	{"Where Is My Hair                ", "Fiction", "Horror", 60.00,123},
	{"Error Everywhere                ", "Fiction", "Horror", 40.00,234},
	{"The Free Rider                  ", "Fiction", "Horror", 55.00,89}
};

const int fictionRomanceSize = 3;
Book fictionRomance[fictionRomanceSize] = {
	{"Graduate with 3.5               ", "Fiction", "Romance", 45.50,332},
	{"The Desire of Go Back Home      ", "Fiction", "Romance", 60.00,112},
	{"Gwenchana                       ", "Fiction", "Romance", 58.00,99}
};

const int fictionActionSize = 3;
Book fictionAction[fictionActionSize] = {
	{"One Night Miracle:The IT Student", "Fiction", "Action", 80.00,67},
	{"Deadline of Assignments         ", "Fiction", "Action", 70.00,58},
	{"The Panas Shop                  ", "Fiction", "Action", 60.00,23}
};

const int nonFictionHistorySize = 3;
Book nonFictionHistory[nonFictionHistorySize] = {
	{"The Guns of August              ", "Non-fiction", "History", 85.40,65},
	{"Democracy: A Life               ", "Non-fiction", "History", 90.05,303},
	{"The Diary of a Young Girl       ", "Non-fiction", "History", 76.00,23}
};

const int nonFictionScienceSize = 3;
Book nonFictionScience[nonFictionScienceSize] = {
	{"Cosmos                          ", "Non-fiction", "Science", 65.00,124},
	{"The Origin Of Species           ", "Non-fiction", "Science", 55.00,228},
	{"The Elegant Universe            ", "Non-fiction", "Science", 69.00,332}
};

const int nonFictionHealthSize = 3;
Book nonFictionHealth[nonFictionHealthSize] = {
	{"How To Grow Hair                ", "Non-fiction", "Health And Wellness", 99.00,144},
	{"The Body Keep Score             ", "Non-fiction", "Health And Wellness", 86.60,155},
	{"Eat to Live                     ", "Non-fiction", "Health And Wellness", 72.00,166}
};


//////////////////////preorder book array
const int preorderFictionHorrorSize = 3;
Book preorderFictionHorror[preorderFictionHorrorSize] = {
	{"Hidden Picture                ", "Fiction", "Horror", 84.00,53},
	{"Road Of Bone                  ", "Fiction", "Horror", 88.00,72},
	{"The House Across The Lake     ", "Fiction", "Horror", 87.00,90}
};

const int preorderFictionRomanceSize = 3;
Book preorderFictionRomance[preorderFictionRomanceSize] = {
	{"Just For The Summer           ", "Fiction", "Romance", 64.50,277},
	{"Happy Place                   ", "Fiction", "Romance", 60.00,190},
	{"Cross The Line                ", "Fiction", "Romance", 58.00,201}
};

const int preorderFictionActionSize = 3;
Book preorderFictionAction[preorderFictionActionSize] = {
	{"A Death In Cornwall           ", "Fiction", "Action", 80.00,333},
	{"The Collector                 ", "Fiction", "Action", 70.00,226},
	{"The Clean kill                ", "Fiction", "Action", 60.00,125}
};

const int preorderNonFictionHistorySize = 3;
Book preorderNonFictionHistory[preorderNonFictionHistorySize] = {
	{"The Earth Transformed         ", "Non-fiction", "History", 65.00,321},
	{"Emperor Of Rome               ", "Non-fiction", "History", 55.00,34},
	{"On Freedom                    ", "Non-fiction", "History", 69.00,107}
};

const int preorderNonFictionScienceSize = 3;
Book preorderNonFictionScience[preorderNonFictionScienceSize] = {
	{"An Immense World              ", "Non-fiction", "Science", 65.00,167},
	{"The Heat Will Kill You First  ", "Non-fiction", "Science", 55.00,321},
	{"Plastic                       ", "Non-fiction", "Science", 69.00,221}
};

const int preorderNonFictionHealthSize = 3;
Book preorderNonFictionHealth[preorderNonFictionHealthSize] = {
	{"Why We Sleep                  ","Non-fiction", "Health And Wellness", 99.00,134},
	{"Food And Nutrition            ", "Non-fiction", "Health And Wellness", 82.60,112},
	{"Play and wellbeing            ", "Non-fiction", "Health And Wellness", 74.00,245}
};

struct Member {
	string memberID;
	string name;
};

const int MAX_MEMBERS = 100; // Define a fixed size for the array
Member members[MAX_MEMBERS] = { {"MBR24034", "Johnson"} };
int numMembers = 1; // Set the number of members to 1

/////////////////////////////struct of cart
struct Cart {
	string title;
	string genre;
	string category;
	double price = 0.00;
	int quantity = 0;
};

const int cartSize = 100;// define a constant integer variable to store the maximum size of the cart
Cart cart[cartSize];// declare an array of Cart objects with a size of cartSize
int cartIndex = 0;

time_t convertStringToTime(const string& date) {
	tm time = {};
	istringstream ss(date);
	ss >> get_time(&time, "%d-%m-%Y");
	return mktime(&time);
}

//function prototypes
//fiction or non-fiction
void showMenu();
//welcome page
void welcomePage();
//cust
void custchoice();
//staff
void staffchoice();
void staffmainmenu();
void updateBookQuantity(Book books[], int size, Cart cart[cartSize], int cartIndex);
void checkRemainingStock(Book books[], int size);
void Buy_checkremainstock();
void Pre_checkremainstock();
void Buy_updatestocks();
void Pre_updatestocks();
void generateReport();
void initSuggestions();
void displaySuggestions();
void markAsRepliedAndDelete();
void displaySuggestionsnoreturn();
//invoice
void invoice();
//buy book
void buybook();
void BuydisplayFiction();
void BuydisplayFictionBooks(string Category);
void BuydisplayNonFiction();
void BuydisplayNonFictionBooks(string Category2);
//preorder
void preorderbook();
void PredisplayFiction();
void PredisplayFictionBooks(string category);
void displayPreNonFictionBooks(string category2);
//custservice
void custservice();
void makesuggestion();
void requestrefund();
void custsuggestion();
//membership
void memberchoice();
void applyMembership();
void MembershipInformation();
bool verifymember(string memberID, const Member members[], int size);
bool processMemberID(string memberID, const Member members[], int size);
string generateMemberID();
//cart
void addToCart(Book book, int quantity);
void displayCart();
void clearCart();
//payment
void ProcessPayment(double& realtotal, double& servicecharge, double& totalAmount, double& memberdiscount);
void displayReceipt(string paymentMethod, double& realtotal, double& servicecharge, double& totalAmount, double& memberdiscount);
//time
string getCurrentDate();
void CurrentTime();
void CurrentDate();
//email
void custemail(string& email);
void mememail();

const char loading_bar = 219;

int main() {

	const double servicecharge = 0.06;

	//start
	initSuggestions();
	welcomePage();

	return 0;
}

void clearCart() {
	// Clear the cart by resetting each element in the array
	for (int i = 0; i < cartSize; i++) {
		// Reset each Cart object in the array to its default values
		cart[i] = Cart(); // Assuming Cart has a default constructor
	}
	cartIndex = 0;
}

void mememail() {   // function to input and validate an email address
	string email;
	bool isValidEmail = false;
	while (!isValidEmail) {
		getline(cin, email);
		bool hasAtSymbol = false;
		bool hasDotCom = false;
		for (char c : email) {
			if (c == '@') {
				hasAtSymbol = true;
			}
		}
		for (int i = email.length() - 1; i >= 0; i--) {
			char c = email[i];
			if (c == '.' && email.length() >= 4 && email[email.length() - 1] == 'm' && email[email.length() - 2] == 'o' && email[email.length() - 3] == 'c') {
				hasDotCom = true;
				break;
			}
		}
		isValidEmail = hasAtSymbol && hasDotCom;
		if (!isValidEmail) {
			cout << "Invalid input. Please enter a valid email address (e.g. example@example.com): ";
		}
	}
}

void custemail(string& email) {     // function to input and validate an email address
	bool isValidEmail = false;
	while (!isValidEmail) {
		getline(cin, email);
		bool hasAtSymbol = false;
		bool hasDotCom = false;
		for (char c : email) {
			if (c == '@') {
				hasAtSymbol = true;
			}
		}
		for (int i = email.length() - 1; i >= 0; i--) {
			char c = email[i];
			if (c == '.' && email.length() >= 4 && email[email.length() - 1] == 'm' && email[email.length() - 2] == 'o' && email[email.length() - 3] == 'c') {
				hasDotCom = true;
				break;
			}
		}
		isValidEmail = hasAtSymbol && hasDotCom;
		if (!isValidEmail) {
			cout << "Invalid input. Please enter a valid email address (e.g. example@example.com): ";
		}
	}
}

// Function to get the current date and time in a specific format
void CurrentDate() {
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);


	cout << localTime.tm_mday << "-"
		<< localTime.tm_mon + 1 << "-"
		<< localTime.tm_year + 1900 << "" << endl;
}

void CurrentTime() {
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);

	cout
		<< localTime.tm_hour << ":"
		<< localTime.tm_min << ":"
		<< localTime.tm_sec << std::endl;
}

string getCurrentDate() {
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
	int day = localTime.tm_mday;
	int month = localTime.tm_mon + 1;
	int year = localTime.tm_year + 1900;

	string dayStr = (day < 10) ? "0" + to_string(day) : to_string(day);
	string monthStr = (month < 10) ? "0" + to_string(month) : to_string(month);

	string currentDate = dayStr + "-" + monthStr + "-" + to_string(year);
	return currentDate;
}
//main menu
void welcomePage() {
	string choice;

	cout << line1 << endl;
	cout << "\t\t\t\tWelcome to\n";
	cout << " ____ ___ _   _ _  _ __   __  ____   ___   ___  _  _____   _   _  ___  ___" << endl;
	cout << "|  _ |_ _| | | | |/ /| | / / | __ ) | _ | | _ || |/ /___| | | | || _ ||  _ | " << endl;
	cout << "| | ) | ||  || | ' /  | v /  |  _ || | | | | | | ' /|___ || |_| | | | | | ) | " << endl;
	cout << "|  __/| || ||  | .|-|  | |   | |_) | |_| | |_| | . | ___) |  _  | |_| |  __/" << endl;
	cout << "|_|  |___|_| |_|_| |_| |_|   |____/ |___| |___||_||_|____/|_| |_||___||_|" << endl;
	cout << line1 << endl;

	cout << "Hello! Welcome to Pinky Bookshop." << endl << endl;

	cout << "Press 1 if you are customer.\nPress 2 if you are staff.\nPress 3 to quit the program." << endl;	//read user identity

	while (true) {
		cout << "You selected ";
		cin >> choice;

		cout << "\n";

		if (choice == "1") {
			custchoice();
			break;
		}
		else if (choice == "2") {
			staffchoice();
			break;
		}
		else if (choice == "3") {
			cout << "Exiting the program...." << endl;
			cout << "Thank you for shopping with us!" << endl;
			exit(0);//terminate the program
			break;
		}
		else {
			cout << "Invalid identity. Please reenter!\n";
		}
		//staff or customer
	}
}

void addToCart(Book book, int quantity) {
	system("cls");
	cart[cartIndex].title = book.title;
	cart[cartIndex].genre = book.genre;
	cart[cartIndex].category = book.category;
	cart[cartIndex].price = book.price;
	cart[cartIndex].quantity = quantity;
	cartIndex++;
	cout << book.title << endl;
	cout << "x " << quantity << " has been added to cart!" << endl;
}

void displayCart() {
	system("cls");

	cout << "Cart:" << endl;
	for (int i = 0; i < cartIndex; i++) {
		cout << i + 1 << ". " << cart[i].title << "- " << cart[i].genre << " - RM " << cart[i].price << endl;
		cout << " x " << cart[i].quantity << endl;
	}
}

void custchoice() {
	string name;
	string option;
	cout << "Dear customer,please enter your name:"; //get user's name
	cin.ignore();
	getline(cin, name);

	cout << "Hello " << name << " , please select one option from below:" << endl << endl;    //greeting

	cout << "1.Buy Book" << endl << "2.Preorder Book" << endl << "3.Customer service" << endl << "4.Membership" << "\n5.Exit" << endl << endl;
	cout << "Option ---> ";
	cin >> option;

	while (option < "1" || option>"5") {
		system("cls");
		cout << "Invalid option, please choose again" << endl;
		cout << "------------------------------------------" << endl;
		cout << "1.Buy Book" << endl << "2.Preorder Book" << endl << "3.Customer service" << endl << "4.Membership" << "\n5.Exit" << endl << endl << endl;
		cout << "Option ---> ";
		cin >> option;

	} // loop until a valid option (1-5) is entered
	cout << endl;
	if (option == "1") {
		buybook();
	}
	else if (option == "2") {
		preorderbook();
	}

	else if (option == "3") {
		custservice();
	}

	else if (option == "4") {
		memberchoice();
	}
	else if (option == "5") {
		welcomePage();
	}
}

//menu fiction or non-fiction
void showMenu() {
	system("cls");
	cout << "-----------------------------MENU-------------------------------------" << endl << endl << endl;
	cout << "-------------------------\t\t-------------------------" << endl;
	cout << "| 1.Fiction book\t|\t\t|2.Non-fiction book\t|" << endl;
	cout << "|_______________________|\t\t|_______________________|" << endl;
	cout << "Please choose 1 or 2:";
}

void invoice() {
	bool isMember = false;
	string memberID, Member_response, confirm;

	static int nextInvoiceId = 001; // Initialize the next available invoice ID
	Invoice invoice;
	invoice.id = nextInvoiceId++;

	while (true) {
		cout << "Are you a member  (Y or N):";
		cin >> Member_response;
		if (Member_response == "Y" || Member_response == "y") {
			cout << "Enter your member ID: ";
			cin >> memberID;
			if (processMemberID(memberID, members, MAX_MEMBERS)) {
				isMember = true; // set isMember to true if the member ID is valid
				break; // exit the loop
			}
			else {
				system("cls");
				cout << "Invalid member ID. Please try again." << endl;
				isMember = false; // reset isMember to false
				continue; // loop back to ask again
			}
		}
		else if (Member_response == "N" || Member_response == "n") {
			isMember = false; // reset isMember to false
			memberID = ""; // clear the memberID input
			break; // exit the loop
		}
		else {
			system("cls");
			cout << "Wrong decision,please choose again" << endl;
		}
	}

	double totalAmount = 0.0;//totalAmount=all subtotal+
	double subtotal = 0.0;//subtotal=quantity * price per book
	double realtotal = 0.0;//realtotal=totalAmount+servicecharge-memberdiscount
	double memberdiscount = 0.0;


	cout << "======================================================================================\n";
	cout << "\n";
	cout << "                             ========================                                 \n";
	cout << "                             *****PINKY BOOKSHOP*****                                 \n";
	cout << "                             ========================                                 \n";
	cout << "                 123,Jalan Genting Kelang, Setapak, 53300 Kuala Lumpur                \n";
	cout << "                                                                                      \n";
	cout << "  Tel: 03-31104164                                                 Date:"; CurrentDate();
	cout << "  Email: pinky123@gmail.com                                        Time:"; CurrentTime();
	cout << "\n";
	cout << "--------------------------------------------------------------------------------------\n";
	cout << "  Invoice No:" << setw(3) << setfill('0') << invoice.id << "\n";
	cout << "\n";
	cout << "  Title                                   Price(RM)        Quantity      Subtotal(RM) \n";
	for (int i = 0; i < cartIndex; i++) {
		subtotal = cart[i].price * cart[i].quantity;
		totalAmount += subtotal;

		cout << "  " << i + 1 << ". " << left << cart[i].title
			<< right << setw(13) << setfill(' ') << cart[i].price << right << setw(13)
			<< setfill(' ') << right << cart[i].quantity
			<< right << setw(19) << setfill(' ') << subtotal << "\n";
	}
	double servicecharge = totalAmount * 0.06;
	cout << "======================================================================================\n";
	cout << "\n";
	cout << "  Total Amount " << setw(13) << setfill(' ') << ":RM" << right << setw(7) << setfill(' ') << totalAmount << "\n";
	cout << "  Service Charge(6%)" << setw(8) << setfill(' ') << ":RM" << right << setw(7) << setfill(' ') << servicecharge << "\n";
	if (isMember) {
		memberdiscount = totalAmount * 0.2;
		realtotal = totalAmount + servicecharge - memberdiscount;
	}
	else {
		memberdiscount = totalAmount * 0;
		realtotal = totalAmount + servicecharge;

	}
	cout << "  Member Discount(20%)" << setw(6) << setfill(' ') << ":RM" << right << setw(7) << setfill(' ') << memberdiscount << right << setw(55) << setfill(' ') << "\n";
	realtotal = totalAmount + servicecharge - memberdiscount;
	cout << "  Total Payable" << setw(13) << setfill(' ') << ":RM" << right << setw(7) << setfill(' ') << realtotal << "\n";
	cout << "\n";
	cout << "======================================================================================\n";
	cout << "\n";

	updateBookQuantity(fictionHorror, fictionHorrorSize, cart, cartIndex);
	updateBookQuantity(fictionRomance, fictionRomanceSize, cart, cartIndex);
	updateBookQuantity(fictionAction, fictionActionSize, cart, cartIndex);
	updateBookQuantity(nonFictionHistory, nonFictionHistorySize, cart, cartIndex);
	updateBookQuantity(nonFictionScience, nonFictionScienceSize, cart, cartIndex);
	updateBookQuantity(nonFictionHealth, nonFictionHealthSize, cart, cartIndex);
	updateBookQuantity(preorderFictionHorror, preorderFictionHorrorSize, cart, cartIndex);
	updateBookQuantity(preorderFictionRomance, preorderFictionRomanceSize, cart, cartIndex);
	updateBookQuantity(preorderFictionAction, preorderFictionActionSize, cart, cartIndex);
	updateBookQuantity(preorderNonFictionHistory, preorderNonFictionHistorySize, cart, cartIndex);
	updateBookQuantity(preorderNonFictionScience, preorderNonFictionScienceSize, cart, cartIndex);
	updateBookQuantity(preorderNonFictionHealth, preorderNonFictionHealthSize, cart, cartIndex);

	do {
		cout << "Do you confirm payment?(Y/N)" << endl;
		cin >> confirm;
	} while (confirm != "N" && confirm != "n" && confirm != "Y" && confirm != "y");

	if (confirm == "Y" || confirm == "y") {
		ProcessPayment(realtotal, servicecharge, totalAmount, memberdiscount);
		cout << "Press Enter to exit...\n";
		cin.ignore(); // ignore the newline character
		cin.get(); // wait for user to press Enter

		cout << "Exiting...." << endl;
		for (int i = 0; i <= 70; i++)
		{
			Sleep(10);
			cout << loading_bar;
		}
		cout << "\n";
		system("cls");
		welcomePage();
	}
	else if (confirm == "N" || confirm == "n") {
		system("cls");
		clearCart();
		cout << "Exiting...." << endl;
		welcomePage();
	}
}


void BuydisplayFiction() {
	cout << "***********************Fiction Book*********************" << endl << endl << endl;
	cout << "*****************************************" << endl;
	cout << "* Category A:Horror\t\t\t*" << endl;
	cout << "* 1.Where Is My Hair\t\t\t*" << endl;
	cout << "* 2.Error Everywhere\t\t\t*" << endl;
	cout << "* 3.The Free Rider\t\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;

	cout << "*****************************************" << endl;
	cout << "* Category B:Romance\t\t\t*" << endl;
	cout << "* 1.Graduate with 3.5\t\t\t*" << endl;
	cout << "* 2.The Desire of Go Back Home\t\t*" << endl;
	cout << "* 3.Gwenchana\t\t\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;

	cout << "*****************************************" << endl;
	cout << "* Category C:Action\t\t\t*" << endl;
	cout << "* 1.One Night Miracle:The IT Student\t*" << endl;
	cout << "* 2.Deadline of Assignments\t\t*" << endl;
	cout << "* 3.The Panas Shop\t\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;
}

void BuydisplayFictionBooks(string Category) {
	if (Category == "A" || Category == "a") {
		cout << "*********************************************************" << endl;
		cout << "* Category A:Horror" << setw(26) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(3) << setfill(' ') << "* " << endl;
		for (int i = 0; i < fictionHorrorSize; i++) {
			cout << "* " << i + 1 << ". " << fictionHorror[i].title << setw(8) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << fictionHorror[i].price << setw(5) << setfill(' ') << "*" << endl;
		}
		cout << "*********************************************************" << endl << endl << endl;
	}

	else if (Category == "B" || Category == "b") {
		cout << "*********************************************************" << endl;
		cout << "* Category B:Romance" << setw(25) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(3) << setfill(' ') << "* " << endl;
		for (int i = 0; i < fictionRomanceSize; i++) {
			cout << "* " << i + 1 << ". " << fictionRomance[i].title << setw(8) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << fictionRomance[i].price << setw(5) << setfill(' ') << "*" << endl;
		}
		cout << "*********************************************************" << endl << endl << endl;
	}
	else if (Category == "C" || Category == "c") {
		cout << "*********************************************************" << endl;
		cout << "* Category C:Action" << setw(26) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(3) << setfill(' ') << "* " << endl;
		for (int i = 0; i < fictionActionSize; i++) {
			cout << "* " << i + 1 << ". " << fictionAction[i].title << setw(8) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << fictionAction[i].price << setw(5) << setfill(' ') << "*" << endl;
		}
		cout << "*********************************************************" << endl << endl << endl;
	}
}

void BuydisplayNonFiction() {
	cout << "***********************Non-Fiction Book*********************" << endl << endl << endl;
	cout << "*****************************************" << endl;
	cout << "* Category A:History\t\t\t*" << endl;
	cout << "* 1.The Guns of August\t\t\t*" << endl;
	cout << "* 2.Democracy: A Life\t\t\t*" << endl;
	cout << "* 3.The Diary of a Young Girl\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;

	cout << "*****************************************" << endl;
	cout << "* Category B:Science\t\t\t*" << endl;
	cout << "* 1.Cosmos\t\t\t\t*" << endl;
	cout << "* 2.The Origin of Species\t\t*" << endl;
	cout << "* 3.The Elegant Universe\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;

	cout << "*****************************************" << endl;
	cout << "* Category C:Health And Wellness\t*" << endl;
	cout << "* 1.How To Grow Hair\t\t\t*" << endl;
	cout << "* 2.The Body Keep Score\t\t\t*" << endl;
	cout << "* 3.Eat to Live\t\t\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;
}


void BuydisplayNonFictionBooks(string Category2) {
	if (Category2 == "A" || Category2 == "a") {
		cout << "********************************************************" << endl;
		cout << "* Category A:History" << setw(25) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(2) << setfill(' ') << "* " << endl;
		for (int i = 0; i < nonFictionHistorySize; i++) {
			cout << "* " << i + 1 << ". " << nonFictionHistory[i].title << setw(8) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << nonFictionHistory[i].price << setw(4) << setfill(' ') << "*" << endl;
		}
		cout << "********************************************************" << endl << endl << endl;
	}
	else if (Category2 == "B" || Category2 == "b") {
		cout << "********************************************************" << endl;
		cout << "* Category B:Science" << setw(25) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(2) << setfill(' ') << "* " << endl;
		for (int i = 0; i < nonFictionScienceSize; i++) {
			cout << "* " << i + 1 << ". " << nonFictionScience[i].title << setw(8) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << nonFictionScience[i].price << setw(4) << setfill(' ') << "*" << endl;
		}
		cout << "********************************************************" << endl << endl << endl;
	}
	else if (Category2 == "C" || Category2 == "c") {
		cout << "********************************************************" << endl;
		cout << "* Category C:Health And Wellness" << setw(13) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(2) << setfill(' ') << "* " << endl;
		for (int i = 0; i < nonFictionHealthSize; i++) {
			cout << "* " << i + 1 << ". " << nonFictionHealth[i].title << setw(8) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << nonFictionHealth[i].price << setw(4) << setfill(' ') << "*" << endl;
		}
		cout << "********************************************************" << endl << endl << endl;
	}
}

void buybook() {
	string response, response_2;
	string Category2, Category;
	int bookChoice;

	do {
		showMenu();
		string fiction;
		cin >> fiction;	//either customer want fiction book or non-fic book

		while (fiction != "1" && fiction != "2") {
			system("cls");
			cout << "Invalid option.Please choose again!" << endl;
			showMenu();
			cin >> fiction;
		}

		system("cls");

		if (fiction == "1") {
			system("cls");
			BuydisplayFiction();


			cout << endl << "Select ONE category you want(A,B or C):";
			cin >> Category;

			while (Category != "A" && Category != "a" && Category != "B" && Category != "b" && Category != "C" && Category != "c") {
				cout << "Wrong category, please choose again " << endl;
				BuydisplayFiction();
				cout << endl << "Select ONE category you want(A,B or C):";
				cin >> Category;
			}
			cout << line2 << endl;


			system("cls");
			BuydisplayFictionBooks(Category);
			cout << "Please Choose a book that you would like to buy :";
			cin >> bookChoice;

			while (bookChoice < 1 || bookChoice > 3) {

				cout << " Wrong choice, please choose again " << endl;
				cout << "------------------------------------------" << endl;
				cout << "Please Choose a book that you would like to buy :";
				cin >> bookChoice;

			}

			Book book;
			if (Category == "A" || Category == "a") {
				book = fictionHorror[bookChoice - 1];
			}
			else if (Category == "B" || Category == "b") {
				book = fictionRomance[bookChoice - 1];
			}
			else if (Category == "C" || Category == "c") {
				book = fictionAction[bookChoice - 1];
			}


			cout << "Enter quantity: ";
			int quantity;
			while (!(cin >> quantity)) {
				cout << "Invalid input. Please enter a number: ";
				cin.clear(); // Clear the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
			}
			addToCart(book, quantity);
		}

		else if (fiction == "2") {	//non fiction book option

			system("cls");

			BuydisplayNonFiction();

			cout << "Select ONE category you want(A,B or C):";
			cin >> Category2;

			while (Category2 != "A" && Category2 != "a" && Category2 != "B" && Category2 != "b" && Category2 != "C" && Category2 != "c") {
				cout << "Wrong category, please choose again " << endl;
				BuydisplayNonFiction();
				cout << endl << "Select ONE category you want(A,B or C):";
				cin >> Category2;
			}
			cout << line2 << endl;

			system("cls");

			BuydisplayNonFictionBooks(Category2);
			cout << "Please Choose a book that you would like to buy :";
			cin >> bookChoice;

			while (bookChoice < 1 || bookChoice > 3) {

				cout << " Wrong choice, please choose again " << endl;
				cout << "------------------------------------------" << endl;
				cout << "Please Choose a book that you would like to buy :";
				cin >> bookChoice;

			}

			Book book;
			if (Category2 == "A" || Category2 == "a") {
				book = nonFictionHistory[bookChoice - 1];
			}
			else if (Category2 == "B" || Category2 == "b") {
				book = nonFictionScience[bookChoice - 1];
			}
			else if (Category2 == "C" || Category2 == "c") {
				book = nonFictionHealth[bookChoice - 1];
			}
			cout << "Enter quantity: ";

			int quantity;
			while (!(cin >> quantity)) {
				cout << "Invalid input. Please enter a number: ";
				cin.clear(); // Clear the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
			}

			addToCart(book, quantity);
		}



		cout << endl << line2 << endl;
		cout << "Would you like to add more books? (Y/N)" << endl;
		cin >> response;

		while (response != "Y" && response != "y" && response != "N" && response != "n") {
			system("cls");
			cout << " Please enter single character(Y/N)" << endl;
			cout << "Wrong option, please choose again" << endl;
			cout << "----------------------------------------------" << endl;
			cout << "Would you like to add more books? (Y/N)" << endl;
			cin >> response;
		}

		if (response == "N" || response == "n") {
			break;
		}

	} while (response == "Y" || response == "y");
	int response_final;
	displayCart();
	cout << "----------------------------------------------" << endl;
	cout << "1. Proceed to invoice" << endl;
	cout << "2. Delete book from cart" << endl;
	cout << "3. Exit to main menu" << endl << endl;
	cout << "Please choose an option: ";
	cin >> response_final;

	while (response_final < 1 || response_final > 3) {
		system("cls");

		cout << "Invalid option, please choose again" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "1. Proceed to invoice" << endl;
		cout << "2. Delete book from cart" << endl;
		cout << "3. Exit to main menu" << endl << endl;
		cout << "Please choose an option: " << endl;
		cin >> response_final;
	}

	if (response_final == 1) {
		system("cls");
		invoice();
	}
	else if (response_final == 2) {
		system("cls");
		int bookNumber;
		bool validInput = false;

		displayCart();
		do {
			do {
				cout << "Enter the book number to delete: " << endl;
				cout << "--------------------------------------------------" << endl;
				cin >> bookNumber;

				if (bookNumber < 1 || bookNumber > cartIndex) {
					displayCart();
					cout << "Invalid book number. Please try again." << endl;
				}
				else {
					validInput = true;
				}
			} while (!validInput);

			for (int i = bookNumber - 1; i < cartIndex - 1; i++) {
				cart[i] = cart[i + 1];
			}


			cartIndex--;
			cout << "Book has been deleted from cart!" << endl << endl;

			if (cartIndex == 0) {
				while (true) {
					cout << "Your cart is empty. Would you like to add some books? (Y/N)" << endl;
					string emptycart_response;
					cin >> emptycart_response;
					if (emptycart_response == "Y" || emptycart_response == "y") {
						buybook();
					}
					else if (emptycart_response == "N" || emptycart_response == "n") {
						cout << "Exiting..." << endl;
						welcomePage();
					}
					else {
						system("cls");
						cout << " Please enter single character(Y/N)" << endl;
						cout << "Wrong decision, please choose again" << endl;
					}
				}
			}
			displayCart();
			cout << " Would you like to delete another book? (Y/N)" << endl;
			cout << "--------------------------------------------------------" << endl;
			cin >> response_2;

			while (response_2 != "Y" && response_2 != "y" && response_2 != "N" && response_2 != "n") {
				cout << " Please enter single character(Y/N)" << endl;
				cout << "Invalid decision, please try again" << endl;
				cin >> response_2;
			}

			if (response_2 == "N" || response_2 == "n") {
				cout << "\n";
				invoice();
			}
		} while (response_2 == "Y" || response_2 == "y");

	}
	else if (response_final == 3) {
		clearCart();
		system("cls");
		cout << "Exiting...." << endl;
		welcomePage();

	}


}

//Display preorder display fiction books
void PredisplayFiction() {
	cout << "***********************Fiction Book*********************" << endl << endl << endl;
	cout << "*****************************************" << endl;
	cout << "* Category A:Horror\t\t\t*" << endl;
	cout << "* 1.Hidden Picture\t\t\t*" << endl;
	cout << "* 2.Road Of Bones\t\t\t*" << endl;
	cout << "* 3.The House Across The Lake\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;

	cout << "*****************************************" << endl;
	cout << "* Category B:Romance\t\t\t*" << endl;
	cout << "* 1.Just For The Summer\t\t\t*" << endl;
	cout << "* 2.Happy Place\t\t\t\t*" << endl;
	cout << "* 3.Cross The Line\t\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;

	cout << "*****************************************" << endl;
	cout << "* Category C:Action\t\t\t*" << endl;
	cout << "* 1.A Death In Cornwall\t\t\t*" << endl;
	cout << "* 2.The Collector\t\t\t*" << endl;
	cout << "* 3.The Clean Kill\t\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;
}

void PredisplayFictionBooks(string category) {
	if (category == "A" || category == "a") {
		cout << "**********************************************************" << endl;
		cout << "* Category A:Horror" << setw(25) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(5) << setfill(' ') << "* " << endl;
		for (int i = 0; i < preorderFictionHorrorSize; i++) {
			cout << "* " << i + 1 << ". " << preorderFictionHorror[i].title << setw(9) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << preorderFictionHorror[i].price << setw(7) << setfill(' ') << "*" << endl;
		}
		cout << "**********************************************************" << endl << endl << endl;
	}

	else if (category == "B" || category == "b") {
		cout << "**********************************************************" << endl;
		cout << "* Category B:Romance" << setw(24) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(5) << setfill(' ') << "* " << endl;
		for (int i = 0; i < preorderFictionRomanceSize; i++) {
			cout << "* " << i + 1 << ". " << preorderFictionRomance[i].title << setw(9) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << preorderFictionRomance[i].price << setw(7) << setfill(' ') << "*" << endl;
		}
		cout << "**********************************************************" << endl << endl << endl;
	}
	else if (category == "C" || category == "c") {
		cout << "********************************************************" << endl;
		cout << "* Category C:Action" << setw(23) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(5) << setfill(' ') << "* " << endl;
		for (int i = 0; i < preorderFictionActionSize; i++) {
			cout << "* " << i + 1 << ". " << preorderFictionAction[i].title << setw(7) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << preorderFictionAction[i].price << setw(7) << setfill(' ') << "*" << endl;
		}
		cout << "********************************************************" << endl << endl << endl;
	}
}

//Display preorder display non fiction books
void PredisplayNonFiction() {
	cout << "***********************Non-Fiction Book*********************" << endl << endl << endl;
	cout << "*****************************************" << endl;
	cout << "* Category A:History\t\t\t*" << endl;
	cout << "* 1.The Earth Transformed\t\t*" << endl;
	cout << "* 2.Emperor Of Rome\t\t\t*" << endl;
	cout << "* 3.On Freedom\t\t\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;

	cout << "*****************************************" << endl;
	cout << "* Category B:Science\t\t\t*" << endl;
	cout << "* 1.An Immense World\t\t\t*" << endl;
	cout << "* 2.The Heat Will Kill You First\t*" << endl;
	cout << "* 3.Plastic\t\t\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;

	cout << "*****************************************" << endl;
	cout << "* Category C:Health And Wellness\t*" << endl;
	cout << "* 1.Why We Sleep\t\t\t*" << endl;
	cout << "* 2.Food And Nutrition\t\t\t*" << endl;
	cout << "* 3.Play And Wellbeing\t\t\t*" << endl;
	cout << "*****************************************" << endl << endl << endl;

}

void displayPreNonFictionBooks(string category2) {
	if (category2 == "A" || category2 == "a") {
		cout << "**********************************************************" << endl;
		cout << "* Category A:History" << setw(24) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(5) << setfill(' ') << "* " << endl;
		for (int i = 0; i < preorderNonFictionHistorySize; i++) {
			cout << "* " << i + 1 << ". " << preorderNonFictionHistory[i].title << setw(9) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << preorderNonFictionHistory[i].price << setw(7) << setfill(' ') << "*" << endl;
		}
		cout << "**********************************************************" << endl << endl << endl;
	}
	else if (category2 == "B" || category2 == "b") {
		cout << "**********************************************************" << endl;
		cout << "* Category B:Science" << setw(24) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(5) << setfill(' ') << "* " << endl;
		for (int i = 0; i < preorderFictionRomanceSize; i++) {
			cout << "* " << i + 1 << ". " << preorderNonFictionScience[i].title << setw(9) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << preorderNonFictionScience[i].price << setw(7) << setfill(' ') << "*" << endl;
		}
		cout << "**********************************************************" << endl << endl << endl;
	}
	else if (category2 == "C" || category2 == "c") {
		cout << "**********************************************************" << endl;
		cout << "* Category C:Health" << setw(25) << setfill(' ') << "|" << setw(10) << setfill(' ') << "Price(RM) " << setw(5) << setfill(' ') << "* " << endl;
		for (int i = 0; i < preorderNonFictionHealthSize; i++) {
			cout << "* " << i + 1 << ". " << preorderNonFictionHealth[i].title << setw(9) << setfill(' ') << "|" << "RM" << fixed << setprecision(2) << preorderNonFictionHealth[i].price << setw(7) << setfill(' ') << "*" << endl;
		}
		cout << "**********************************************************" << endl << endl << endl;
	}
}

void preorderbook() {
	string response, response_2;
	int bookChoice;
	do {
		showMenu();
		string fiction;
		cin >> fiction;	//either customer want fiction book or non-fic book

		while (fiction != "1" && fiction != "2") {
			system("cls");
			cout << "Invalid option.Please choose again!" << endl;
			showMenu();
			cin >> fiction;
		}

		system("cls");

		if (fiction == "1") {
			system("cls");
			PredisplayFiction();

			cout << endl << "Select ONE category you want(A,B or C):";
			string category;
			cin >> category;

			while (category != "A" && category != "a" && category != "B" && category != "b" && category != "C" && category != "c") {
				cout << "Wrong category, please choose again " << endl;
				PredisplayFiction();
				cout << endl << "Select ONE category you want(A,B or C):";
				cin >> category;
			}

			cout << line2 << endl;

			system("cls");

			PredisplayFictionBooks(category);
			cout << "Please Choose a book that you would like to buy :";
			cin >> bookChoice;

			while (bookChoice < 1 || bookChoice > 3) {
				cout << " Wrong choice, please choose again " << endl;
				cout << "------------------------------------------" << endl;
				PredisplayFictionBooks(category);
				cout << "Please Choose a book that you would like to buy :";
				cin >> bookChoice;

			}

			Book book;
			if (category == "A" || category == "a") {
				book = preorderFictionHorror[bookChoice - 1];
			}
			else if (category == "B" || category == "b") {
				book = preorderFictionRomance[bookChoice - 1];
			}
			else if (category == "C" || category == "c") {
				book = preorderFictionAction[bookChoice - 1];
			}
			cout << "Enter quantity: ";
			int quantity;
			while (!(cin >> quantity)) {
				cout << "Invalid input. Please enter a number: ";
				cin.clear(); // Clear the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
			}
			addToCart(book, quantity);
		}

		else if (fiction == "2") {//non fiction book option

			system("cls");

			PredisplayNonFiction();

			cout << "Select ONE category you want(A,B or C):";
			string category2;
			cin >> category2;

			while (category2 != "A" && category2 != "a" && category2 != "B" && category2 != "b" && category2 != "C" && category2 != "c") {
				cout << "Wrong category, please choose again " << endl;
				PredisplayNonFiction();
				cout << endl << "Select ONE category you want(A,B or C):";
				cin >> category2;
			}

			cout << line2 << endl;

			system("cls");

			displayPreNonFictionBooks(category2);
			cout << "Please Choose a book that you would like to buy :";
			cin >> bookChoice;

			while (bookChoice < 1 || bookChoice > 3) {
				cout << " Wrong choice, please choose again " << endl;
				cout << "------------------------------------------" << endl;
				displayPreNonFictionBooks(category2);
				cout << "Please Choose a book that you would like to buy :";
				cin >> bookChoice;

			}
			Book book;
			if (category2 == "A" || category2 == "a") {
				book = preorderNonFictionHistory[bookChoice - 1];
			}
			else if (category2 == "B" || category2 == "b") {
				book = preorderNonFictionScience[bookChoice - 1];
			}
			else if (category2 == "C" || category2 == "c") {
				book = preorderNonFictionHealth[bookChoice - 1];
			}
			cout << "Enter quantity: ";
			int quantity;
			while (!(cin >> quantity)) {
				cout << "Invalid input. Please enter a number: ";
				cin.clear(); // Clear the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
			}
			addToCart(book, quantity);
		}

		cout << endl << line2 << endl;

		cout << "Would you like to add more books? (Y/N)" << endl;
		cin >> response;

		while (response != "Y" && response != "y" && response != "N" && response != "n") {
			system("cls");
			cout << " Please enter single character(Y/N)" << endl;
			cout << "Wrong option, please choose again" << endl;
			cout << "----------------------------------------------" << endl;
			cout << "Would you like to add more books? (Y/N)" << endl;
			cin >> response;
		}
		if (response == "N" || response == "n") {
			break;
		}
	} while (response == "Y" || response == "y");

	int response_final;
	displayCart();
	cout << "----------------------------------------------" << endl;
	cout << "1. Proceed to invoice" << endl;
	cout << "2. Delete book from cart" << endl;
	cout << "3. Exit to main menu" << endl << endl;
	cout << "Please choose an option: ";
	cin >> response_final;

	while (response_final < 1 || response_final > 3) {
		system("cls");
		cout << "Invalid option, please choose again" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "1. Proceed to invoice" << endl;
		cout << "2. Delete book from cart" << endl;
		cout << "3. Exit to main menu" << endl << endl;
		cout << "Please choose an option: " << endl;
		cin >> response_final;
	}

	if (response_final == 1) {
		system("cls");
		invoice();
	}
	else if (response_final == 2) {
		int bookNumber;
		bool validInput = false;// flag to track whether the input is valid or not
		displayCart();
		do {
			do {
				cout << "Enter the book number to delete: " << endl;
				cout << "--------------------------------------------------" << endl;
				cin >> bookNumber;

				if (bookNumber < 1 || bookNumber > cartIndex) {
					cout << "Invalid book number. Please try again." << endl;
				}
				else {
					validInput = true;
				}
			} while (!validInput);

			for (int i = bookNumber - 1; i < cartIndex - 1; i++) {
				cart[i] = cart[i + 1];
			}


			cartIndex--;
			cout << "Book has been deleted from cart!" << endl << endl;

			if (cartIndex == 0) {
				while (true) {
					cout << "Your cart is empty. Would you like to add some books? (Y/N)" << endl;
					string emptycart_response;
					cin >> emptycart_response;
					if (emptycart_response == "Y" || emptycart_response == "y") {
						preorderbook();
					}
					else if (emptycart_response == "N" || emptycart_response == "n") {
						cout << "Exiting..." << endl;
						welcomePage();

					}
					else {
						system("cls");
						cout << " Please enter single character(Y/N)" << endl;
						cout << "Wrong decision, please choose again" << endl;
					}
				}
			}
			displayCart();

			cout << " Would you like to delete another book? (Y/N)" << endl;
			cout << "---------------------------------------------------" << endl;
			cin >> response_2;

			while (response_2 != "Y" && response_2 != "y" && response_2 != "N" && response_2 != "n") {
				cout << " Please enter single character(Y/N)" << endl;
				cout << "Invalid decision, please try again" << endl;
				cin >> response_2;
			}

			if (response_2 == "N" || response_2 == "n") {
				cout << "\n";
				invoice();
			}
		} while (response_2 == "Y" || response_2 == "y");
	}
	else if (response_final == 3) {
		clearCart();
		system("cls");
		cout << "Exiting...." << endl;
		for (int i = 0; i <= 70; i++)
		{
			Sleep(10);
			cout << loading_bar;
		}
		welcomePage();

	}

}

void ProcessPayment(double& realtotal, double& servicecharge, double& totalAmount, double& memberdiscount) {
	char paymentMethod;
	string CardNum, Cvv, name, Address1, Address2;
	bool paymentMade = false; // add a flag to indicate payment made

	system("cls");
	while (true) {
		cout << "Choose a payment method:" << endl;
		cout << "1. Cash" << endl;
		cout << "2. Card" << endl;
		cout << "3. E-wallet" << endl;

		cout << "Enter your choice: ";
		cin >> paymentMethod;
		system("cls");

		switch (paymentMethod) {
		case '1':
			cout << "\nPayment received! Thank you!\n";

			displayReceipt("Cash", realtotal, servicecharge, totalAmount, memberdiscount);
			paymentMade = true; // set flag to true
			break;
		case '2':

			cout << "Card number :";
			cin >> CardNum;
			cin.ignore(100000000000, '\n'); // Ignore remaining characters after reading CardNum

			cout << "\n";

			cout << "Cvv :";
			cin >> Cvv;
			cin.ignore(10000, '\n'); // Ignore remaining characters after reading CardNum

			cout << "\n";

			cout << "Name :";
			cin >> name;
			getline(cin, name);

			cout << "\n";

			cout << "Address line 1 :";
			cin >> Address1;
			getline(cin, Address1);

			cout << "\n";

			cout << "Address line 2 :";
			cin >> Address2;
			getline(cin, Address2);

			cout << "Processing payment...." << endl;
			for (int i = 0; i <= 70; i++)
			{
				Sleep(10);
				cout << loading_bar;
			}

			cout << "\nPayment received! Thank you!\n";

			displayReceipt("Card", realtotal, servicecharge, totalAmount, memberdiscount);
			paymentMade = true; // set flag to true
			break;

		case '3':
			cout << "Please scan the qr code" << endl;
			cout << "Processing payment...." << endl;
			for (int i = 0; i <= 70; i++)
			{
				Sleep(10);
				cout << loading_bar;
			}
			cout << "\nPayment received! Thank you!\n";
			displayReceipt("E-wallet", realtotal, servicecharge, totalAmount, memberdiscount);
			paymentMade = true; // set flag to true
			break;

		default:
			system("cls");
			cout << "Invalid choice. Please choose again" << endl;
			continue;
		}
		if (paymentMade) {
			break; // break out of the loop if payment made
		}
	}
}

void displayReceipt(string paymentMethod, double& realtotal, double& servicecharge, double& totalAmount, double& memberdiscount) {

	static int nextReceiptId = 1000; // Initialize the next available invoice ID
	Receipt receipt;
	receipt.id = nextReceiptId++;

	double subtotal = 0.0;//subtotal = quantity * price per book

	cout << "======================================================================================\n";
	cout << "\n";
	cout << "                             ========================                                 \n";
	cout << "                             *****PINKY BOOKSHOP*****                                 \n";
	cout << "                             ========================                                 \n";
	cout << "                 123,Jalan Genting Kelang, Setapak, 53300 Kuala Lumpur                \n";
	cout << "                                                                                      \n";
	cout << "  Tel: 03-31104164                                                 Date:"; CurrentDate();
	cout << "  Email: pinky123@gmail.com                                        Time:"; CurrentTime();
	cout << "\n";
	cout << "--------------------------------------------------------------------------------------\n";
	cout << "  Receipt No:" << setw(3) << setfill('0') << receipt.id << setw(68) << setfill(' ') << "\n";
	cout << "\n";
	cout << "  Title                                   Price(RM)       Quantity      Subtotal(RM)   \n";
	for (int i = 0; i < cartIndex; i++) {
		subtotal = cart[i].price * cart[i].quantity;

		cout << "  " << i + 1 << ". " << left << cart[i].title
			<< right << setw(13) << setfill(' ') << cart[i].price << right << setw(13)
			<< setfill(' ') << right << cart[i].quantity
			<< right << setw(19) << setfill(' ') << subtotal << "\n";
	}
	cout << "--------------------------------------------------------------------------------------\n";
	cout << "\n";
	cout << "  Total Amount" << setw(9) << setfill(' ') << ":RM" << totalAmount << endl;
	cout << "  Service Charge" << setw(7) << setfill(' ') << ":RM" << servicecharge << endl;
	cout << "  Member Discount" << setw(6) << setfill(' ') << ":RM" << memberdiscount << endl;
	cout << "\n";
	cout << "  Total Payable" << setw(8) << setfill(' ') << ":RM" << realtotal << "\n";
	cout << "  Payment Method " << setw(4) << setfill(' ') << ":" << paymentMethod << "\n";
	cout << "\n";
	cout << "--------------------------------------------------------------------------------------\n";
	cout << "                     Thank You for visiting Pinky Bookshop!                         \n";
	cout << "======================================================================================\n";


	string currentDate = getCurrentDate();
	dailyEarnings[currentDate] += realtotal;
	clearCart();

	cout << "\n";

}


void custservice() {
	system("cls");

	int cust_servicechoice;
	cout << "1.Make suggestions\n";
	cout << "2.Request refunds\n";
	cout << "3.Exit\n";
	cout << "What would you like to do? (Select 1,2 or 3)" << endl;
	cin >> cust_servicechoice;

	while (cust_servicechoice < 1 || cust_servicechoice > 3) {
		system("cls");
		cout << "Invalid option, please choose again" << endl;
		cout << "------------------------------------------" << endl;
		cout << "1.Make suggestions\n";
		cout << "2.Request refunds\n";
		cout << "3.Exit\n";
		cout << "What would you like to do? (Select 1,2 or 3)" << endl;
		cin >> cust_servicechoice;
	}

	if (cust_servicechoice == 1) {
		system("cls");
		makesuggestion();
	}
	else if (cust_servicechoice == 2) {
		system("cls");
		requestrefund();
	}
	else if (cust_servicechoice == 3) {
		system("cls");
		welcomePage();
	}

}

void makesuggestion() {
	string cs_suggestion;
	Suggestion suggestion;
	string decision1;
	do {
		cout << "What suggestion would you like to make?" << endl;
		cin.ignore();// ignore the newline character left in the input buffer
		getline(cin, cs_suggestion);// get the suggestion from the user
		suggestion.suggestionText = cs_suggestion; // set the suggestion text

		suggestion.replied = false;// set the replied flag to false

		cout << "\n";

		cout << "Please enter you email address so we may get back to you(e.g. example@example.com)" << endl;
		custemail(suggestion.email);

		suggestions.push_back(suggestion);  // Add the suggestion to the global list

		cout << "\n";

		cout << "We will go through your suggestion and get back to you by email, thank you" << endl;

		cout << "\n";

		cout << "Would you like to make another suggestion? (Yes/No)" << endl;
		cin >> decision1;

		while (decision1 != "Yes" && decision1 != "yes" && decision1 != "No" && decision1 != "no") {
			system("cls");
			cout << "Wrong decision, please choose again" << endl;
			cout << "------------------------------------------" << endl;
			cout << "Would you like to make another suggestion? (Yes/No)" << endl;
			cin >> decision1;
			cout << "\n";
		}

		if (decision1 == "No" || decision1 == "no") {
			system("cls");
			custservice();
		}
	} while (decision1 == "Yes" || decision1 == "yes");
}

void requestrefund() {
	Suggestion suggestion;
	string decision2;

	cout << "Please enter the receipt number that you want to get a refund back from" << endl;
	string receipt_no;
	while (!(cin >> receipt_no) || receipt_no.find_first_not_of("0123456789") != string::npos) {
		system("cls");
		cout << "Invalid receipt number. Please enter a valid receipt number (only digits): " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Add this line

	cout << "\n";

	cout << "What is your reason for wanting this refund?" << endl;
	string reason;
	getline(cin, reason); // reason

	cout << "\n";

	cout << "We will review your refund request and get back to you by email" << endl;
	cout << "Please enter your email(e.g. example@example.com): ";
	custemail(suggestion.email);

	suggestion.replied = false; // set the replied flag to false

	suggestions.push_back(suggestion);// add the refund request to the global list

	cout << "\n";

	cout << "We will get back to you through email in 2-3 working days" << endl;

	cout << "\n";

	cout << "Would you like to make another refund request? (Yes/No)" << endl;
	cin >> decision2;

	while (decision2 != "Yes" && decision2 != "yes" && decision2 != "No" && decision2 != "no") {
		system("cls");
		cout << "Wrong decision, please choose again" << endl;
		cout << "------------------------------------------" << endl;
		cout << "Would you like to make another refund? (Yes/No)" << endl;
		cin >> decision2;
	}

	if (decision2 == "Yes" || decision2 == "yes") {
		requestrefund();
	}


	else if (decision2 == "No" || decision2 == "no")
	{
		system("cls");
		custservice();
	}

}

// membership void
void memberchoice() {
	int member_choice;
	system("cls");
	cout << "\nMembership System Menu:\n";
	cout << "1. Apply for Membership\n";
	cout << "2. Membership Information\n";
	cout << "3. Exit\n";

	cout << "Enter your choice: ";
	cin >> member_choice;
	cout << "\n";
	cin.ignore();  // to ignore the newline character left by cin
	if (member_choice == 1) {
		applyMembership();
	}
	else if (member_choice == 2) {
		MembershipInformation();
	}
	else if (member_choice == 3) {
		system("cls");
		welcomePage();
	}
	else {
		system("cls");
		cout << "Wrong choice, please choose again" << endl;
		memberchoice();
	}
}

string generateMemberID() {
	srand(time(0)); // Seed the random number generator
	int randomID = rand() % 1000000; // Generate a random 8-digit number
	return "MBR" + to_string(randomID);

	for (int i = 0; i < MAX_MEMBERS; i++) {
		members[i].memberID = generateMemberID();
	}

}

bool isValidName(const string& name) {
	int i = 0;
	while (i < name.length()) {
		char c = name[i];
		if (!isalpha(c) && !isspace(c)) {
			return false;// return false if the character is not a letter or space
		}
		i++;
	}
	return true;// return true if the entire string consists of letters and spaces
}

void applyMembership() {
	string name;
	int age;
	string confirmPayment;
	const double memberpayment = 100;//price for membership
	string memberID;
	while (true) {
		cout << "Enter your name: ";
		getline(cin, name);

		if (isValidName(name)) {
			break; // Exit the loop if name is valid
		}
		else {
			cout << "Invalid name. Please enter a name containing only letters and spaces." << endl;
		}
	}
	do {
		cout << "Enter your age: ";
		cin >> age;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (age < 18 || age >80) {
			cout << "Age is out of range,Please reenter." << endl;
		}
		else {
		}
	} while (age < 18 || age >80);

	cout << "Enter your email(e.g. example@example.com): ";
	mememail();
	cout << "Total payment:" << memberpayment;
	cout << "\n";
	cout << "Do you confirm the payment of RM100? (Yes/No): ";
	cin >> confirmPayment;

	while (confirmPayment != "Yes" && confirmPayment != "yes" && confirmPayment != "No" && confirmPayment != "no") {
		system("cls");
		cout << "Invalid choice,Please choose again" << endl;
		cout << "--------------------------------------------" << endl;
		cout << "Total payment:" << memberpayment;
		cout << "\n";
		cout << "Do you confirm the payment of RM100? (Yes/No): ";
		cin >> confirmPayment;

	}

	if (confirmPayment == "Yes" || confirmPayment == "yes") {
		double realtotal = memberpayment;
		double servicecharge = 0.0;
		double memberdiscount = 0.0;
		double totalAmount = 0.0;//totalAmount=all subtotal+
		memberID = generateMemberID();
		Member newMember;
		newMember.memberID = memberID;
		newMember.name = name;
		members[numMembers] = newMember; // Add the new member to the array
		numMembers++; // Increment the number of members
		ProcessPayment(realtotal, servicecharge, memberdiscount, totalAmount);

		cout << "\n";
		cout << "Membership application successful for " << name << "!Thank You!" << endl;
		cout << "Your member ID is: " << memberID << endl;
		cout << "\n";

		cout << "Press Enter to exit...";
		cin.ignore(); // ignore the newline character
		cin.get(); // wait for user to press Enter

		cout << "Exiting...." << endl;
		for (int i = 0; i <= 70; i++)
		{
			Sleep(10);
			cout << loading_bar;
		}
		cout << "\n";
		system("cls");
		welcomePage();
	}
	else if (confirmPayment == "No" || confirmPayment == "no") {
		cout << "Payment not confirmed. Membership application canceled." << endl;
		cout << "\n";
		memberchoice();
	}
}

bool verifymember(string memberID, const Member members[], int size) { //to verify member

	for (int i = 0; i < size; i++) {
		if (members[i].memberID == memberID) {
			return true;
		}
	}
	return false;
}

bool processMemberID(string memberID, const Member members[], int size) {
	if (verifymember(memberID, members, MAX_MEMBERS)) {
		cout << " Welcome " << memberID << " You are entitled to 20% discount" << endl;// print welcome message and discount information
		return true;// return true to indicate successful verification
	}
	else {
		cout << " Wrong member ID please re-type\n";// print error message for invalid member ID
		return false;// return false to indicate failed verification
	}
}

void MembershipInformation() {
	cout << "\nPrice for Membership\n";
	cout << "RM100 only for lifetime!\n\n";
	cout << "Benefit of Membership:\n\n";
	cout << setw(97) << setfill('^') << "^" << endl;
	cout << "^Get Discount\t\t\t\t\t\t\t\t\t\t\t^\n";
	cout << "^You can get 20% discount if you are our member.\t\t\t\t\t\t^\n";
	cout << setw(97) << setfill('^') << "^" << endl;
	cout << "^Birthday Reward\t\t\t\t\t\t\t\t\t\t^\n";
	cout << "^You can redeem a free gift and this is valid throughtout your birthday month.\t\t\t^\n";
	cout << setw(97) << setfill('^') << "^" << endl;
	cout << "^Exclusive Promotion\t\t\t\t\t\t\t\t\t\t^\n";
	cout << "^You can get a limited-edition book and this book is not available to the public.\t\t^\n";
	cout << setw(97) << setfill('^') << "^" << endl;
	cout << "^Exclusive Event\t\t\t\t\t\t\t\t\t\t^\n";
	cout << "^You can join our membership event.This event will give you exclusive offers and giveaways.\t^\n";
	cout << setw(97) << setfill('^') << "^" << endl;

	cout << "Press Enter to continue...\n";
	cin.ignore(); // ignore the newline character
	cin.get(); // wait for user to press Enter

	memberchoice();
}

void staffchoice() {
	int staffid;
	string staffidName[5] = { "Christina", "Ash Lenglui", "Jane Smith", "Edwin Johnson", "Thomas Choo choo" };// array of staff names

	cout << "Hello ! Please key in your staff id : ";

	while (true) {
		cin >> staffid;
		if (cin.fail() || staffid < 1001 || staffid > 1005) {
			cin.clear();  // clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
			system("cls");
			cout << "\nStaff id not recognized, please try again: ";
		}
		else {
			break;  // exit the loop if the input is valid
		}
	}

	cout << "\n";

	cout << "Processing id...." << endl;
	for (int i = 0; i <= 70; i++)
	{
		Sleep(10);
		cout << loading_bar;
	}

	cout << "\n";

	cout << "Hello " << staffidName[staffid - 1001] << endl;
	cout << "\n";
	staffmainmenu();

}

void staffmainmenu() {
	int staffoption;
	string choosen, choosen2;
	while (true) {
		cout << "1.Check remaining stock\n";
		cout << "2.Update stock\n";
		cout << "3.Sales Report\n";
		cout << "4.Suggestions\n";
		cout << "5.Exit\n";
		cout << "Option ---> ";
		cin >> staffoption;


		switch (staffoption) {
		case 1:
			system("cls");
			do {
				cout << "1.Buy Book" << endl;
				cout << "2.Pre Order" << endl;
				cout << "3.Exit" << endl;
				cout << "Please choose an option:";
				cin >> choosen;

				if (choosen == "1") {
					cout << "\n";
					Buy_checkremainstock();
				}
				else if (choosen == "2") {
					cout << "\n";
					Pre_checkremainstock();
				}
				else if (choosen == "3") {
					cout << "\n";
					staffmainmenu();
				}
				else {
					system("cls");
					cout << "Invalid Choice,Please choose again" << endl;
				}
			} while (choosen != "1" && choosen != "2" && choosen != "3");
			break;


		case 2:
			system("cls");
			do {
				cout << "1.Buy Book" << endl;
				cout << "2.Pre Order" << endl;
				cout << "3.Exit" << endl;
				cout << "Please choose an option:";
				cin >> choosen2;
				if (choosen2 == "1") {
					cout << "\n";
					Buy_updatestocks();
				}
				else if (choosen2 == "2") {
					cout << "\n";
					Pre_updatestocks();
				}
				else if (choosen2 == "3") {
					cout << "\n";
					staffmainmenu();
				}
				else {
					system("cls");
					cout << "Invalid Choice,Please choose again" << endl;
				}
			} while (choosen != "1" && choosen != "2" && choosen != "3");

			break;

		case 3:
			system("cls");

			generateReport();
			break;

		case 4:
			system("cls");

			custsuggestion();
			break;

		case 5:
			system("cls");

			welcomePage();
			break;
		default:
			cout << "\n";
			cout << "Wrong option, please choose again" << endl;
			continue;
		}
		break;
	}

}


void custsuggestion() {

	int suggestionchoice;

	cout << "1.Check suggestions from customers\n";
	cout << "2.Mark suggestion as read\n";
	cout << "3.Exit\n";
	cout << "Please choose an option: " << endl;
	cin >> suggestionchoice;

	switch (suggestionchoice) {

	case 1: {
		system("cls");
		displaySuggestions();
		break;
	}
	case 2: {
		system("cls");
		markAsRepliedAndDelete();
		break;
	}
	case 3: {
		cout << "\n";
		staffmainmenu();
		break;
	}
	default:
		cout << "\n";
		custsuggestion();
	}
}

// attempt to parse the date string into day, month, and year
bool validateDate(const string& date) {
	istringstream iss(date);
	int day, month, year;
	char sep1, sep2;

	if (!(iss >> day >> sep1 >> month >> sep2 >> year)) {
		return false;
	}

	if (sep1 != '-' || sep2 != '-') {
		return false;
	}

	if (day < 1 || day > 31 || month < 1 || month > 12) {
		return false;
	}

	return true;
}

// Function to update stock
void generateReport() {
	map<string, double> dailyEarnings;
	dailyEarnings["04-02-2022"] = 5600.00;
	dailyEarnings["02-03-2022"] = 1500.00;
	dailyEarnings["08-07-2022"] = 2300.00;
	dailyEarnings["06-09-2022"] = 1500.00;
	dailyEarnings["10-10-2022"] = 2000.00;
	dailyEarnings["15-12-2022"] = 3000.00;
	dailyEarnings["17-02-2023"] = 9999.00;
	dailyEarnings["13-05-2023"] = 3000.00;
	dailyEarnings["23-07-2023"] = 4690.00;
	dailyEarnings["15-12-2023"] = 3000.00;
	dailyEarnings["03-01-2024"] = 6700.00;
	dailyEarnings["25-03-2024"] = 7600.00;
	dailyEarnings["21-04-2024"] = 4309.00;
	dailyEarnings["08-08-2024"] = 2309.00;

	string startDate, endDate;

	while (true) {
		cout << "Please enter a start date (DD-MM-YYYY): ";
		cin >> startDate;
		if (validateDate(startDate)) {
			break;
		}
		else {
			system("cls");
			cout << "Invalid date format. Please enter a date in DD-MM-YYYY format" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.sync(); // Add this line to clear the input buffer
		}
	}

	while (true) {
		cout << "Please enter an end date (DD-MM-YYYY): ";
		cin >> endDate;
		if (validateDate(endDate)) {
			time_t startTime = convertStringToTime(startDate);
			time_t endTime = convertStringToTime(endDate);

			if (startTime < endTime) {
				break;
			}
			else {
				system("cls");
				cout << "Invalid date range. The start date must be smaller than the end date." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.sync(); // Add this line to clear the input buffer

				// Re-enter start date if end date is invalid
				cout << "Please re-enter a start date (DD-MM-YYYY): ";
				cin >> startDate;
				if (!validateDate(startDate)) {
					system("cls");
					cout << "Invalid date format. Please enter a date in DD-MM-YYYY format" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin.sync(); // Add this line to clear the input buffer
				}
			}
		}
		else {
			system("cls");
			cout << "Invalid date format. Please enter a date in DD-MM-YYYY format" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.sync(); // Add this line to clear the input buffer
		}
	}

	// Create a list to store the dates and earnings
	list<pair<string, double>> earningsList;

	// Iterate over the dailyEarnings map and add the dates and earnings to the list
	for (const auto& earnings : dailyEarnings) {
		time_t date = convertStringToTime(earnings.first);
		if (date >= convertStringToTime(startDate) && date <= convertStringToTime(endDate)) {
			earningsList.push_back(earnings);
		}
	}

	// Sort the list in ascending order based on the dates
	earningsList.sort([](const pair<string, double>& a, const pair<string, double>& b) {
		return convertStringToTime(a.first) < convertStringToTime(b.first);
		});

	// Print the earnings in ascending order
	double totalEarnings = 0.00;
	for (const auto& earnings : earningsList) {
		cout << "\n";
		cout << "Earnings for " << earnings.first << ": RM " << earnings.second << endl;
		cout << "------------------------" << endl;
		totalEarnings += earnings.second;
	}

	cout << "\n";
	cout << "------------------------" << endl;
	cout << "Total earnings from " << startDate << " to " << endDate << ": RM " << totalEarnings << endl;
	cout << "------------------------" << endl;

	cout << "Press Enter to continue...\n";
	cin.ignore(); // ignore the newline character
	cin.get(); // wait for user to press Enter

	staffmainmenu();
}

void checkRemainingStock(Book books[], int size) {
	// loop through each book in the array
	for (int i = 0; i < size; i++) {
		// print the title and quantity of the current book
		cout << books[i].title << " - " << books[i].quantity << endl;
	}
}

void updateBookQuantity(Book books[], int size, Cart cart[cartSize], int cartIndex) {
	// loop through each item in the cart
	for (int i = 0; i < cartIndex; i++) {
		// loop through each book in the array
		for (int j = 0; j < size; j++) {
			if (cart[i].title == books[j].title) {
				books[j].quantity -= cart[i].quantity;
				break;
			}
		}
	}
}

void initSuggestions() {
	Suggestion suggestion1 = { "Ceo wants more girl books", "CeobusinessGirl@gmail.com", false };// create a new suggestion object
	Suggestion suggestion2 = { "Please add the new Always talking nonsense book", "QinnZi@gmail.com", false };// create another new suggestion object
	Suggestion suggestion3 = { "Change the member names to cherry gang", "cherrygang@yahoo.com", false };// create a third suggestion object

	// add each suggestion to the suggestions vector
	suggestions.push_back(suggestion1);
	suggestions.push_back(suggestion2);
	suggestions.push_back(suggestion3);
}

void displaySuggestionsnoreturn() {
	int index = 0;

	for (const auto& suggestion : suggestions) {
		if (!suggestion.suggestionText.empty()) { // Check if the suggestion is not empty
			cout << "Suggestion " << index + 1 << ":" << endl;
			cout << "Suggestion: " << suggestion.suggestionText << endl;
			cout << "Email: " << suggestion.email << endl;
			cout << "Replied: " << (suggestion.replied ? "Yes" : "No") << endl;
			cout << "---------------------------------------------------------------------------" << endl;
			index++;
		}
	}
}

void displaySuggestions() {
	int index = 0;

	for (const auto& suggestion : suggestions) {
		if (!suggestion.suggestionText.empty()) { // Check if the suggestion is not empty
			cout << "Suggestion " << index + 1 << ":" << endl;
			cout << "Suggestion: " << suggestion.suggestionText << endl;
			cout << "Email: " << suggestion.email << endl;
			cout << "Replied: " << (suggestion.replied ? "Yes" : "No") << endl;
			cout << "---------------------------------------------------------------------------" << endl;
			index++;
		}
	}cout << "Press Enter to continue...\n";
	cin.ignore(); // ignore the newline character
	cin.get(); // wait for user to press Enter

	staffmainmenu();
}

void markAsRepliedAndDelete() {
	displaySuggestionsnoreturn();
	cout << "\n";
	int suggestionIndex;
	cout << "Enter the index of the suggestion to mark as replied and delete: ";
	cin >> suggestionIndex;

	if (suggestionIndex < 1 || suggestionIndex > suggestions.size()) {
		system("cls");
		cout << "Invalid index. Please try again." << endl;
		markAsRepliedAndDelete();
	}
	else {
		list<Suggestion>::iterator it = suggestions.begin();
		advance(it, suggestionIndex - 1); // Subtract 1 because indices start at 1
		it->replied = true;
		suggestions.erase(it);
		cout << "Suggestion marked as replied and deleted." << endl;
	}
	cout << "Press Enter to continue...\n";
	cin.ignore(); // ignore the newline character
	cin.get(); // wait for user to press Enter

	staffmainmenu();
}


void Buy_checkremainstock() {
	system("cls");
	cout << "Remaining Stock..." << endl;

	cout << line2 << endl;
	checkRemainingStock(fictionHorror, fictionHorrorSize);
	cout << "\n";
	checkRemainingStock(fictionRomance, fictionRomanceSize);
	cout << "\n";
	checkRemainingStock(fictionAction, fictionActionSize);
	cout << "\n";
	checkRemainingStock(nonFictionHistory, nonFictionHistorySize);
	cout << "\n";
	checkRemainingStock(nonFictionScience, nonFictionScienceSize);
	cout << "\n";
	checkRemainingStock(nonFictionHealth, nonFictionHealthSize);
	cout << line2 << endl;

	cout << "Press Enter to continue...\n";
	cin.ignore(); // ignore the newline character
	cin.get(); // wait for user to press Enter

	staffmainmenu();
}
void Pre_checkremainstock() {
	system("cls");

	cout << "Remaining Stock..." << endl;
	cout << line2 << endl;
	checkRemainingStock(preorderFictionHorror, preorderFictionHorrorSize);
	cout << "\n";
	checkRemainingStock(preorderFictionRomance, preorderFictionRomanceSize);
	cout << "\n";
	checkRemainingStock(preorderFictionAction, preorderFictionActionSize);
	cout << "\n";
	checkRemainingStock(preorderNonFictionHistory, preorderNonFictionHistorySize);
	cout << "\n";
	checkRemainingStock(preorderNonFictionScience, preorderNonFictionScienceSize);
	cout << "\n";
	checkRemainingStock(preorderNonFictionHealth, preorderNonFictionHealthSize);
	cout << line2 << endl;

	cout << "Press Enter to continue...\n";
	cin.ignore(); // ignore the newline character
	cin.get(); // wait for user to press Enter

	staffmainmenu();
}
// Function to update stock
void Buy_updatestocks() {
	int category, bookIndex, stockUpdatebuy;
	Book* books;
	int size;
	system("cls");
	while (true) {
		cout << "Select the category to update stock:" << endl;
		cout << "1. Fiction Horror" << endl;
		cout << "2. Fiction Romance" << endl;
		cout << "3. Fiction Action" << endl;
		cout << "4. Non-Fiction History" << endl;
		cout << "5. Non-Fiction Science" << endl;
		cout << "6. Non-Fiction Health" << endl;
		cout << "7. Exit" << endl;

		while (!(cin >> category)) {
			cout << "Invalid input. Please enter a number." << endl;
			cin.clear(); // clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
		}

		switch (category) {
		case 1:
			books = fictionHorror;
			size = fictionHorrorSize;
			break;
		case 2:
			books = fictionRomance;
			size = fictionRomanceSize;
			break;
		case 3:
			books = fictionAction;
			size = fictionActionSize;
			break;
		case 4:
			books = nonFictionHistory;
			size = nonFictionHistorySize;
			break;
		case 5:
			books = nonFictionScience;
			size = nonFictionScienceSize;
			break;
		case 6:
			books = nonFictionHealth;
			size = nonFictionHealthSize;
			break;
		case 7:
			staffmainmenu();
			return; // exit the function
		default:
			system("cls");
			cout << "Invalid category selection." << endl;
			continue;
		}

		// code that uses the 'books' pointer
		system("cls");
		cout << "Select the book to update stock (1-" << size << "):" << endl;
		for (int i = 0; i < size; i++) {
			cout << (i + 1) << ". " << books[i].title << endl;
		}

		while (true) {
			cin >> bookIndex;
			if (bookIndex < 1 || bookIndex > size) {
				cout << "Invalid book selection. Please enter a number between 1 and " << size << "." << endl;
				continue;
			}
			break; // valid input, exit loop
		}

		cout << "Enter the updated stock for " << books[bookIndex - 1].title << endl;

		while (!(cin >> stockUpdatebuy)) {
			cout << "Invalid input. Please enter a number." << endl;
			cin.clear(); // clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
		}

		books[bookIndex - 1].quantity += stockUpdatebuy;

		cout << "Stock updated successfully!" << endl;
		break; // exit the loop
	}
}

void Pre_updatestocks() {
	int precategory, prebookIndex, prestockUpdate;
	Book* books;
	int size;
	system("cls");
	while (true) {
		cout << "Select the category to update stock:" << endl;
		cout << "1. Preorder Fiction Horror" << endl;
		cout << "2. Preorder Fiction Romance" << endl;
		cout << "3. Preorder Fiction Action" << endl;
		cout << "4. Preorder Non-Fiction History" << endl;
		cout << "5. Preorder Non-Fiction Science" << endl;
		cout << "6. Preorder Non-Fiction Health" << endl;
		cout << "7. Exit" << endl;

		while (!(cin >> precategory)) {
			cout << "Invalid input. Please enter a number." << endl;
			cin.clear(); // clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
		}

		switch (precategory) {
		case 1:
			books = preorderFictionHorror;
			size = preorderFictionHorrorSize;
			break;
		case 2:
			books = preorderFictionRomance;
			size = preorderFictionRomanceSize;
			break;
		case 3:
			books = preorderFictionAction;
			size = preorderFictionActionSize;
			break;
		case 4:
			books = preorderNonFictionHistory;
			size = preorderNonFictionHistorySize;
			break;
		case 5:
			books = preorderNonFictionScience;
			size = preorderNonFictionScienceSize;
			break;
		case 6:
			books = preorderNonFictionHealth;
			size = preorderNonFictionHealthSize;
			break;
		case 7:
			staffmainmenu();
			return; // exit the function
		default:
			system("cls");
			cout << "Invalid category selection." << endl;
			continue;
		}

		// code that uses the 'books' pointer
		cout << "Select the book to update stock (1-" << size << "):" << endl;
		for (int i = 0; i < size; i++) {
			cout << (i + 1) << ". " << books[i].title << endl;
		}

		while (true) {
			cin >> prebookIndex;
			if (prebookIndex < 1 || prebookIndex > size) {
				cout << "Invalid book selection. Please enter a number between 1 and " << size << "." << endl;
				continue;
			}
			break; // valid input, exit loop
		}

		cout << "Enter the updated stock for " << books[prebookIndex - 1].title << endl;

		while (!(cin >> prestockUpdate)) {
			cout << "Invalid input. Please enter a number." << endl;
			cin.clear(); // clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
		}

		books[prebookIndex - 1].quantity += prestockUpdate;

		cout << "Stock updated successfully!" << endl;
		break; // exit the loop
	}
}




