/**
 * birthdays.cpp
 * Project UID: 59fc568b7f83f8c109ae360f448f7f821ba0a71
 * 
 * <Dominic Wydeven>
 * <dwydeven>
 *
 * EECS 183: Project 2
 *
 * <Calculate day of week on given day and print 10 Leap Years>
 */

#include <cmath>
#include <iostream>
#include <string>

using namespace std;


/**
 * REQUIRES: nothing
 * MODIFIES: cout
 * EFFECTS:  Prints out the initial heading for the program
 */
void printHeading();


/**
 * REQUIRES: nothing
 * MODIFIES: cout
 * EFFECTS:  Prints out the final greeting for the program
 */
void printCloser();


/**
 * REQUIRES: nothing
 * MODIFIES: cout 
 * EFFECTS:  Prints the menu text. Does not read from cin.
 */
void printMenu();

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: nothing
 * MODIFIES: cout, cin
 * EFFECTS:  1. Prints the menu
 *           2. Reads the input from the user
 *           3. Checks to make sure the input is within range for the menu
 *              If not prints "Invalid menu choice"
 *           4. Continues to print the menu and read an input until 
 *              a valid one is entered
 *           5. Returns the user's choice of menu options
 * 
 *           This function must call printMenu().
 */
int getMenuChoice();

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: month, day, year represent a valid date
 * MODIFIES: nothing
 * EFFECTS:  Returns true if the date is in the limits
 *           of the Gregorian calendar otherwise returns false
 *           See the spec for definition of "limits of the Gregorian calendar"
 */
bool isGregorianDate(int m, int d, int y);

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: year is a Gregorian year
 * MODIFIES: nothing
 * EFFECTS:  returns true if the year is a leap year
 *           otherwise returns false.
 *           See the spec for definition of a leap year.
 */
bool isLeapYear(int year);

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: month, day, year may represent a date
 * MODIFIES: nothing
 * EFFECTS:  returns true if the date is valid
 *           otherwise returns false
 *           See the spec for definition of "valid"
 */
bool isValidDate(int month, int day, int year);

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: month, day, year is a valid date
 *           i.e., the date passed to this function has already passed
 *               isValidDate()
 * MODIFIES: nothing
 * EFFECTS:  returns the value f that Zeller's formula calculates
 */
int determineDay(int month, int day, int year);

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: day is a value of f output by Zeller's formula
*            (0 represents Saturday, 1 Sunday, 2 Monday, 3 Tuesday, etc)
 * MODIFIES: cout
 * EFFECTS:  prints the day of the week corresponding to day, suchas
 *           "Sunday", "Monday", ..., "Saturday"
 */
void printDayOfBirth(int day);

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: nothing
 * MODIFIES: cout, cin
 * EFFECTS:  Asks for the month / day / year of the user's birthday.
 *           If the date is valid, it will print the day
 *           of the week you were born on
 *           Otherwise, it will print "Invalid date" prompt.
 */
void determineDayOfBirth();

/**
 * Note:  write your test cases in test.cpp BEFORE you implement this function
 *
 * REQUIRES: nothing
 * MODIFIES: cin, cout
 * EFFECTS:  Asks for a Gregorian year and prints the
 *           10 leap years after (not including) the year entered.
 *           If the year is invalid, it prints nothing.
 *
 *           This function must call isLeapYear().
 */
void print10LeapYears();

/* 
 * EFFECTS: Main driver for the Birthdays program. See the
 *          "Putting it Together" section of the spec for what
 *          this function needs to accomplish.
 */
void birthdays() {
    printHeading();
    int choice = getMenuChoice();
    while (choice == 1 || choice == 2) {
        while (choice == 1) {
            determineDayOfBirth();
            choice = getMenuChoice();
        }
        while (choice == 2) {
            print10LeapYears();
            choice = getMenuChoice();
        }
    }
    if (choice == 3) {
        printCloser();
    }
    }


void printHeading() {
    cout << "*******************************" << endl
         << "      Birthday Calculator      " << endl
         << "*******************************" << endl << endl;
    return;
}


void printCloser() {
    cout << endl;
    cout << "****************************************************" << endl
         << "      Thanks for using the Birthday Calculator      " << endl
         << "****************************************************" << endl
         << endl;
    return;
}


void printMenu() {
    cout << endl;
    cout << "Menu Options" << endl
         << "------------" << endl;
    cout << "1) Determine day of birth" << endl;
    cout << "2) Print the next 10 leap years" << endl;
    cout << "3) Finished" << endl << endl;
    
    cout << "Choice --> ";
    return;
}

int getMenuChoice() {
    printMenu();
    int choice;
    cin >> choice;
    // Valid choices must be between 1-3 inclusive
    while (choice >= 4 || choice <= 0) {
        cout << "\nInvalid menu choice" << endl;
        printMenu();
        cin >> choice;
    }
    return choice;
}

bool isGregorianDate(int m, int d, int y) {
    // Ensuring that all values are positive and non-zero
    if ((m > 0) && (d > 0) && (y > 0)) {
        // Cuttoff for Gregorian Date is 9 / 13 / 1752
        if (y == 1752) {
            if (m == 9) {
                if (d > 13) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else if (m > 9) {
                return true;
            }
            else {
                return false;
            }
        }
        // Any year after 1752, all dates Gregorian 
        else if (y > 1752) {
            return true;
        }
        // And before, all are not Gregorian 
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool isLeapYear(int year) {
    // Ensures year is Gregorian
    if (year >= 1752) {
        // Elimates years not evenly divisible by 4
        if ((year % 4) != 0) {
            return false;
        }
        // Year mod 100 gives last two digits of year, if 0, then century
        else if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            }
            // Elimanates century years not evenly divisibly by 400
            else {
                return false;
            }
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

bool isValidDate(int month, int day, int year) {
    if (isGregorianDate(month, day, year)) {
        if (month == 2) {
            // Cuttoff for Feb. is 29 if leap year, and 28 if not leap year
            if ((isLeapYear(year)) && (day < 30)) {
                return true;
            }
            else if ((!isLeapYear(year)) && (day < 29)) {
                return true;
            }
            else {
                return false;
            }
        }
        // Month must be 12 or under
        else if (month >= 13) {
            return false;
        }
        // Attempt to not be egregious and go month by month
        // Odd months under 8 can have 31 days
        // Even months over 7 can have 31 days
        else if (((month <= 7) && (month % 2 == 1)) || 
            ((month >= 8) && (month % 2 == 0))) {
            if (day <= 31) {
                return true;
            }
            else {
                return false;
            }
        }
        // Even months under 8 can have 30 days (besides Feb)
        // Odd months over 7 can have 30 days
        else if (((month <= 7) && (month % 2 == 0)) ||
            ((month >= 8) && (month % 2 == 1))) {
            if (day <= 30) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

int determineDay(int month, int day, int year) {
    // Integer truncation will leave floor of century 
    int century = year / 100;
    int year2digit = year % 100;
    // Switching January to month of 13
    if (month == 1) {
        month = 13;
        year2digit--;
    }
    // Switching Feburary to month of 14
    else if (month == 2) {
        month = 14;
        year2digit--;
    }
    // If year2digit was 00, and month was 1 or 2, then year2digit drops to -1
    // Assign -1 to be 99, and drop the century by 1
    if (year2digit == -1) {
        year2digit = 99;
        century--;
    }
    int ZellersConstant = 0;
    int ZellersSum = 0;
    // Use of Zellers formula
    int floorYear = year2digit / 4;
    int floorCentury = century / 4;
    ZellersSum = day + floor(13 * (month + 1) / 5) + year2digit +
        floorYear + floorCentury + 5 * century;
    ZellersConstant = ZellersSum % 7;
    return ZellersConstant;
    // Note to grader: Recieved error when trying to combine 
    // mod 7 with the formula, operation was then performed outside
}

void printDayOfBirth(int day) {
    if (day == 0) {
        cout << "Saturday" << endl;
    }
    else if (day == 1) {
        cout << "Sunday" << endl;
    }
    else if (day == 2) {
        cout << "Monday" << endl;
    }
    else if (day == 3) {
        cout << "Tuesday" << endl;
    }
    else if (day == 4) {
        cout << "Wednesday" << endl;
    }
    else if (day == 5) {
        cout << "Thursday" << endl;
    }
    else if (day == 6) {
        cout << "Friday" << endl;
    }
    // Using this statement so autograder exits code
    // did not work with else set to Friday
    else {
        cout << "Day not valid";
    }
    
    return;
}

void determineDayOfBirth() {
    cout << "\nEnter your date of birth" << endl <<
        "format: month / day / year  -->" << endl;
    int month, day, year = 0;
    char slash = '/';
    cin >> month >> slash >> day >> slash >> year;
    if (!isValidDate(month, day, year)) {
        cout << "Invalid date" << endl;
    }
    else {
        cout << "You were born on a: ";
        printDayOfBirth(determineDay(month, day, year));
        cout << "\nHave a great birthday!!!" << endl;
    }
}

void print10LeapYears() {
    cout << "Enter year --> " << endl;
    int year, nextLeapYear = 0;
    cin >> year;
    // Year must be Gregorian
    if (year >= 1752) {
        if (isLeapYear(year)) {
            nextLeapYear = year + 4;
        }
        else if (year % 4 == 1) {
            nextLeapYear = year + 3;
        }
        else if (year % 4 == 2) {
            nextLeapYear = year + 2;
        }
        else if (year % 4 == 3) {
            nextLeapYear = year + 1;
        }
        else {
            nextLeapYear = year + 4;
        }

        for (int i = 0; i < 10; i++) {
            if (isLeapYear(nextLeapYear)) {
                cout << "Leap year is " << nextLeapYear << endl;
                nextLeapYear += 4;
            }
            // Else statement accounts for non-leap year by 
            // incrementing twice and printing inbetween
            else {
                int skipCentury = nextLeapYear + 4;
                cout << "Leap year is " << skipCentury << endl;
                nextLeapYear = skipCentury + 4;
            }
        }
        cout << endl;
    }
    // Needs to return an empty line to match sample runs
    cout << "\n";
}
// End of functions: Thank you!