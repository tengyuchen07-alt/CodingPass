#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <vector>
using std::vector;

#include<string>
using namespace std;

struct Date
{
    int year;
    int month;
    int day;
    int hour;
};

struct MemberRecord
{
    char idNumber[12];   // account number
    char password[24];   // password
    char name[8];        // name
};

struct ReservationRecord
{
    char idNumber[12]; // account number
    int branchCode;      // branch code
    Date date;           // reservation date
    int numCustomers;    // number of customers
};

char branchNames[19][24] = { "", "Taipei Dunhua South", "Taipei Zhongxiao",
                                     "Taipei Songjiang",    "Taipei Nanjing",
                                     "Taipei Linsen",       "Taipei Zhonghua New",
                                     "Banqiao Guanqian",    "Yonghe Lehua",
                                     "Taoyuan Zhonghua",    "Taoyuan Nankan",
                                     "Zhongli Zhongyang",   "Hsinchu Beida",
                                     "Taichung Ziyou",      "Chiayi Ren'ai",
                                     "Tainan Ximen",        "Kaohsiung Zhonghua New",
                                     "Kaohsiung Jianxing",  "Pingtung Kending" };

// read all memberDetails from the file Members.dat
void loadMemberDetails(vector< MemberRecord >& memberDetails);

// read all reservations that are not out of date, from the file Reservations.dat
void loadReservations(vector< ReservationRecord >& reservations);

// compute the current date
Date compCurrentDate();

// return true if and only if date1 <= date2
bool lessEqual(const Date& date1, const Date& date2);

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

// login and display the submenu
void login(const vector< MemberRecord >& memberDetails,
    vector< ReservationRecord >& reservations);

// there exists a member with specified idNumber and password
bool valid(char idNumber[], char password[],
    const vector< MemberRecord >& memberDetails);

// add a new reservation for the member with specified IDnumber
void reservation(char idNumber[], vector< ReservationRecord >& reservations);

// compute 7 dates which is starting from the current date
void compAvailableDates(Date availableDates[]);

// display all fields of reservation
void output(ReservationRecord reservation);

// display all reservations for the member with specified IDnumber,
// then let the member to choose one of them to delete
void queryDelete(char idNumber[], vector< ReservationRecord >& reservations);

// add a new member
void registration(vector< MemberRecord >& memberDetails);

// return true if idNumber is a legal ID number
//bool legalID( char idNumber[] );

// return true if idNumber belongs to memberDetails
bool existingID(char idNumber[], const vector< MemberRecord >& memberDetails);

// write all memberDetails into the file Members.dat
void saveMemberDetails(const vector< MemberRecord >& memberDetails);

// write all reservations that are not out of date, into the file Reservations.dat
void saveReservations(const vector< ReservationRecord >& reservations);

int main()
{
    vector< MemberRecord > memberDetails; // member details for all members
    vector< ReservationRecord > reservations; // all reservations

    loadMemberDetails(memberDetails);
    loadReservations(reservations);

    cout << "Welcome to the Cashbox Party World!\n\n";

    int choice;
    while (true)
    {
        cout << "1 - Login\n";
        cout << "2 - Registration\n";
        cout << "3 - End\n";

        do cout << "\nEnter your choice (1~3): ";
        while ((choice = inputAnInteger(1, 3)) == -1);
        cout << endl;

        switch (choice)
        {
        case 1:
            login(memberDetails, reservations);
            break;

        case 2:
            registration(memberDetails);
            break;

        case 3:
            saveMemberDetails(memberDetails);
            saveReservations(reservations);
            cout << "Thank you! Goodbye!\n\n";
            system("pause");
            return 0;

        default:
            cout << "\nIncorrect choice!\n";
            break;
        }
    }

    system("pause");
}

void loadMemberDetails(vector< MemberRecord >& memberDetails)
{
    ifstream in("Members.dat", ios::in | ios::binary);
    in.clear();
    in.seekg(0, ios::beg);
    MemberRecord m;
    while (in.read((char*)&m, sizeof(MemberRecord))) {
        memberDetails.push_back(m);
    }
    in.close();
}

void loadReservations(vector< ReservationRecord >& reservations)
{
    ifstream in("Reservations.dat", ios::in | ios::binary);
    in.clear();
    in.seekg(0, ios::beg);
    ReservationRecord r;
    while (in.read((char*)&r, sizeof(ReservationRecord))) {
        reservations.push_back(r);
    }
    in.close();
}

Date compCurrentDate()
{
    Date currentDate;
    tm structuredTime;
    time_t rawTime = time(0);
    localtime_s(&structuredTime, &rawTime);

    currentDate.year = structuredTime.tm_year + 1900;
    currentDate.month = structuredTime.tm_mon + 1;
    currentDate.day = structuredTime.tm_mday;
    currentDate.hour = structuredTime.tm_hour;

    return currentDate;
}

bool lessEqual(const Date& date1, const Date& date2)
{
    if (date1.year > date2.year)return false;
    if (date1.year < date2.year)return true;
    if (date1.month > date2.month)return false;
    if (date1.month < date2.month)return true;
    if (date1.day > date2.day)return false;
    if (date1.day < date2.day)return true;
    return true;
}

int inputAnInteger(int begin, int end)
{
    char string[80];
    cin.getline(string, 80, '\n');
    /*cin >> string;*/
    if (strlen(string) == 0)
        exit(0);

    for (unsigned int i = 0; i < strlen(string); i++)
        if (string[i] < '0' || string[i] > '9')
            return -1;

    int number = atoi(string);
    if (number >= begin && number <= end)
        return number;
    else
        return -1;
}

void login(const vector< MemberRecord >& memberDetails,
    vector< ReservationRecord >& reservations)
{
    char idNumber[12] = "";
    char password[24] = "";

    do {
        cout << "Please enter your ID number: ";
        cin >> idNumber;
        cout << "Enter your password: ";
        cin >> password;
    } while (!valid(idNumber, password, memberDetails));

    cin.ignore();

    int choice;

    while (true)
    {
        cout << "\n1 - Make Reservation\n";
        cout << "2 - Reservation Enquiry/Canceling\n";
        cout << "3 - End\n";

        do {
            cout << "\nEnter your choice (1~3): ";
        } while ((choice = inputAnInteger(1, 3)) == -1);
        cout << endl;

        switch (choice)
        {
        case 1:
            reservation(idNumber, reservations);
            break;

        case 2:
            queryDelete(idNumber, reservations);
            break;

        case 3:
            return;

        default:
            cout << "\nIncorrect choice!\n";
            break;
        }
    }
}

bool valid(char idNumber[], char password[], const vector< MemberRecord >& memberDetails)
{
    int i = 0;
    for (const auto& i : memberDetails) {
        if (!strcmp(idNumber, i.idNumber) && !strcmp(password, i.password)) {
            return true;
        }
    }
    cout << endl;
    cout << "Invalid account number or password. Please try again." << endl << endl;
    return false;
}

void reservation(char idNumber[], vector< ReservationRecord >& reservations)
{
    ReservationRecord newReservation;
    Date currentDate = compCurrentDate();

    for (int i = 1; i <= 18; i++) {
        cout << setw(2) << i << ". " << branchNames[i] << endl;
    }

    int choice;
    do {
        cout << endl;

        cout << "Enter your choice (0 to end): ";
        cin >> choice;
        if (choice == 0) {
            cin.ignore();
            return;
        }
    } while (choice > 18 || choice < 1);
    newReservation.branchCode = choice;
    cout << endl;
    cout << "The current hour is " << currentDate.year << '\/' << currentDate.month << '\/' << currentDate.day << '\:' << currentDate.hour << endl;

    Date choicedate[7];
    cout << "\nAvailable days:\n\n";
    compAvailableDates(choicedate);
    cout << endl;
    do {
        cout << "Enter your choice (0 to end):";
        cin >> choice;
        cout << endl;
        if (choice == 0) {
            cin.ignore();
            return;
        }
    } while (choice > 7 || choice < 1);

    newReservation.date = choicedate[choice - 1];
    if (choice != 1)newReservation.date.hour = 0;

    int early;
    if (lessEqual(newReservation.date, currentDate) && newReservation.date.hour + 1 != 24) {
        early = currentDate.hour + 1;
    }
    else { early = 0; }

    do {
        cout << "Enter hour(" << early << "~23): ";
        cin >> choice;
        cout << endl;

    } while (choice > 23 || choice < early);
    newReservation.date.hour = choice;

    do {
        cout << "Enter the number of customers (1~30, 0 to end): ";
        cin >> choice;
        cout << endl;
        if (choice == 0) {
            cin.ignore();
            return;
        }

    } while (choice > 30 || choice < 1);
    newReservation.numCustomers = choice;

    cout << endl << setw(26) << "Branch"
        << setw(14) << "Date" << setw(8) << "Hour"
        << setw(19) << "No of Customers" << endl;

    output(newReservation);

    cout << "\nReservation Completed!\n";

    reservations.push_back(newReservation);
    saveReservations(reservations);
    cin.ignore();
}

void compAvailableDates(Date availableDates[])
{
    Date currentDate = compCurrentDate();
    int month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    availableDates[0] = currentDate;
    if (availableDates[0].hour + 1 >= 24) {
        availableDates[0].hour = 0;
        availableDates[0].day++;
        if (!(availableDates[0].year % 400) || !(availableDates[0].year % 4) && (availableDates[0].year % 100)) {
            month[2] = 29;
        }
        else {
            month[2] = 28;
        }
        if (availableDates[0].day > month[availableDates[0].month]) {
            availableDates[0].day = 1;
            availableDates[0].month++;
            if (availableDates[0].month > 12) {
                availableDates[0].year++;
                availableDates[0].month = 1;
            }
        }
    }
    cout << "1. " << availableDates[0].year << '/' << availableDates[0].month << '/' << availableDates[0].day << endl;
    for (int i = 1; i < 7; i++) {
        availableDates[i] = availableDates[i - 1];
        availableDates[i].day++;
        if (!(availableDates[i].year % 400) || !(availableDates[i].year % 4) && (availableDates[i].year % 100)) {
            month[2] = 29;
        }
        else {
            month[2] = 28;
        }
        if (availableDates[i].day > month[availableDates[0].month]) {
            availableDates[i].day = 1;
            availableDates[i].month++;
            if (availableDates[i].month > 12) {
                availableDates[i].year++;
                availableDates[i].month = 1;
            }
        }
        cout << i + 1 << ". " << availableDates[i].year << '/' << availableDates[i].month << '/' << availableDates[i].day << endl;
    }
}

void output(ReservationRecord reservation)
{
    cout << setw(26) << branchNames[reservation.branchCode]
        << setw(8) << reservation.date.year << '-'
        << setw(2) << setfill('0') << reservation.date.month << '-'
        << setw(2) << setfill('0') << reservation.date.day
        << setw(8) << setfill(' ') << reservation.date.hour
        << setw(19) << reservation.numCustomers << endl;
}

void queryDelete(char idNumber[], vector< ReservationRecord >& reservations)
{
    Date currentDate = compCurrentDate();
    if (reservations.empty()) {
        cout << "No reservations!" << endl;
        return;
    }

    vector<ReservationRecord>temp_r;
    for (int i = 0; i < reservations.size(); i++) {
        if (lessEqual(currentDate, reservations[i].date)) {
            temp_r.push_back(reservations[i]);
        }
    }
    reservations = temp_r;
    cout << setw(33) << "Branch"
        << setw(14) << "Date" << setw(8) << "Hour"
        << setw(19) << "No of Customers" << endl;
    for (int i = 0; i < reservations.size(); i++) {
        cout << i + 1 << ".     ";
        output(reservations[i]);
    }
    int choice;
    do {
        cout << endl;
        cout << "Choose a reservation to cancel (0: keep all reservations): ";
        cin >> choice;
        if (choice == 0) {
            cin.ignore();
            return;
        }
    } while (choice<1 || choice>reservations.size());

    vector <ReservationRecord>temp;
    for (int i = 0; i < reservations.size(); i++) {
        if (i != choice - 1) {
            temp.push_back(reservations[i]);
        }
    }
    reservations = temp;
    saveReservations(reservations);
    cin.ignore();
}

void registration(vector< MemberRecord >& memberDetails)
{
    MemberRecord newMember;

    cout << "Input your ID Number: ";
    cin >> newMember.idNumber;
    cin.ignore();

    if (existingID(newMember.idNumber, memberDetails))
    {
        cout << "\nYou are already a member!\n\n";
        return;
    }

    cout << "Input your Name: ";
    cin >> newMember.name;

    cout << "Choose a password: ";
    cin >> newMember.password;

    cin.ignore();

    memberDetails.push_back(newMember);

    cout << "\nRegistration Completed!\n\n";
}

bool existingID(char idNumber[], const vector< MemberRecord >& memberDetails)
{
    for (const auto& i : memberDetails) {
        if (!strcmp(idNumber, i.idNumber))return true;
    }
    return false;
}

void saveMemberDetails(const vector< MemberRecord >& memberDetails)
{
    ofstream out("Members.dat", ios::out | ios::binary);
    out.clear();
    out.seekp(0, ios::end);
    for (int i = 0; i < memberDetails.size(); i++) {
        out.write((char*)&memberDetails[i], sizeof(MemberRecord));
    }
	out.close();
}

void saveReservations(const vector< ReservationRecord >& reservations)
{
    ofstream out("Reservations.dat", ios::out | ios::binary);
    out.clear();
    out.seekp(0, ios::end);
    for (int i = 0; i < reservations.size(); i++) {
        out.write((char*)&reservations[i], sizeof(ReservationRecord));
    }
    out.close();
}