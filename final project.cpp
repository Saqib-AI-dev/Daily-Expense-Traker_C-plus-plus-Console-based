#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Expense {
    int date;       // Day of month (1–31)
    string day;     // Name of day (Mon, Tue, etc.)
    int month;      // Month number
    float amount;   // Money spent
    string category;// Category name
};

Expense expenses[1000];
int expenseCount = 0;

void loadFromFile() {
    ifstream file("expenses.txt");
    if (!file) return;

    while (file >> expenses[expenseCount].date
                >> expenses[expenseCount].day
                >> expenses[expenseCount].month
                >> expenses[expenseCount].amount) {
        file.ignore();
        getline(file, expenses[expenseCount].category);
        expenseCount++;
    }
    file.close();
}

void saveToFile() {
    ofstream file("expenses.txt");
    for (int i = 0; i < expenseCount; i++) {
        file << expenses[i].date << " "
             << expenses[i].day << " "
             << expenses[i].month << " "
             << expenses[i].amount << " "
             << expenses[i].category << endl;
    }
    file.close();
}

void addExpense() {
    cout << "\nEnter Date (1–31): ";
    cin >> expenses[expenseCount].date;

    cout << "Enter Day (Mon–Sun): ";
    cin >> expenses[expenseCount].day;

    cout << "Enter Month (1–12): ";
    cin >> expenses[expenseCount].month;

    cout << "Enter Amount: ";
    cin >> expenses[expenseCount].amount;

    cout << "Enter Category: ";
    cin.ignore();
    getline(cin, expenses[expenseCount].category);

    expenseCount++;
    cout << "\n? Expense Added Successfully!\n";
}

void showCategories() {
    cout << "\n--- All Categories You Entered ---\n";
    if (expenseCount == 0) {
        cout << "No records found.\n";
        return;
    }
    for (int i = 0; i < expenseCount; i++) {
        cout << i+1 << ". " << expenses[i].category << endl;
    }
}

void categorySummary() {
    if (expenseCount == 0) {
        cout << "\nNo expenses found.\n";
        return;
    }

    cout << "\n--- Categories Available ---\n";
    for (int i = 0; i < expenseCount; i++)
        cout << i+1 << ". " << expenses[i].category << endl;

    string cat;
    cout << "\nEnter category to summarize: ";
    cin.ignore();
    getline(cin, cat);

    float total = 0;
    int count = 0;

    for (int i = 0; i < expenseCount; i++) {
        if (expenses[i].category == cat) {
            total += expenses[i].amount;
            count++;
        }
    }

    if (count == 0)
        cout << "\nNo records found for this category.\n";
    else
        cout << "\nTotal spent in " << cat << ": " << total << endl;
}

// -----------------------------
// NEW: Monthly Total
// -----------------------------
void monthlyTotal() {
    if (expenseCount == 0) {
        cout << "\nNo expenses found.\n";
        return;
    }

    int month;
    cout << "\nEnter month (1–12) to see total expenses: ";
    cin >> month;

    float total = 0;
    for (int i = 0; i < expenseCount; i++) {
        if (expenses[i].month == month)
            total += expenses[i].amount;
    }

    cout << "Total expenses in month " << month << ": " << total << endl;
}

// -----------------------------
// NEW: Highest Expense Day
// -----------------------------
void highestExpenseDay() {
    if (expenseCount == 0) {
        cout << "\nNo expenses found.\n";
        return;
    }

    float maxAmount = expenses[0].amount;
    string day = expenses[0].day;
    int date = expenses[0].date;
    int month = expenses[0].month;

    for (int i = 1; i < expenseCount; i++) {
        if (expenses[i].amount > maxAmount) {
            maxAmount = expenses[i].amount;
            day = expenses[i].day;
            date = expenses[i].date;
            month = expenses[i].month;
        }
    }

    cout << "\nHighest expense was " << maxAmount 
         << " on " << day << ", " << date << "/" << month << endl;
}

int main() {
    loadFromFile();

    int choice;

    while (true) {
        cout << "\n====== Expense Tracker ======\n";
        cout << "1. Add Expense\n";
        cout << "2. Show Categories\n";
        cout << "3. Category Summary\n";
        cout << "4. Monthly Total\n";
        cout << "5. Highest Expense Day\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            addExpense();
        else if (choice == 2)
            showCategories();
        else if (choice == 3)
            categorySummary();
        else if (choice == 4)
            monthlyTotal();
        else if (choice == 5)
            highestExpenseDay();
        else if (choice == 6) {
            saveToFile();
            cout << "Saving and exiting...\n";
            break;
        }
        else
            cout << "Invalid choice!\n";
    }

    return 0;
}