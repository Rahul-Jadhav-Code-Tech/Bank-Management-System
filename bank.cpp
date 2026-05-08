#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class BankAccount {
public:
    int accountNumber;
    string name;
    float balance;

    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount() {
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance         : " << balance << endl;
    }
};

vector<BankAccount> accounts;

// Save data to file
void saveToFile() {
    ofstream file("bank.txt");

    for (auto a : accounts) {
        file << a.accountNumber << endl;
        file << a.name << endl;
        file << a.balance << endl;
    }

    file.close();
}

// Load data from file
void loadFromFile() {
    ifstream file("bank.txt");

    BankAccount a;

    while (file >> a.accountNumber) {
        file.ignore();

        getline(file, a.name);

        file >> a.balance;

        accounts.push_back(a);
    }

    file.close();
}

// Search account
int searchAccount(int accNo) {

    for (int i = 0; i < accounts.size(); i++) {

        if (accounts[i].accountNumber == accNo) {
            return i;
        }
    }

    return -1;
}

// Create account
void createNewAccount() {

    BankAccount a;

    a.createAccount();

    accounts.push_back(a);

    saveToFile();

    cout << "\nAccount Created Successfully!\n";
}

// Display all accounts
void displayAllAccounts() {

    if (accounts.empty()) {
        cout << "\nNo Accounts Found!\n";
        return;
    }

    for (auto a : accounts) {

        a.displayAccount();

        cout << "\n------------------------";
    }
}

// Deposit money
void depositMoney() {

    int accNo;
    float amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    int index = searchAccount(accNo);

    if (index == -1) {
        cout << "\nAccount Not Found!\n";
        return;
    }

    cout << "Enter Deposit Amount: ";
    cin >> amount;

    accounts[index].balance += amount;

    saveToFile();

    cout << "\nAmount Deposited Successfully!\n";
}

// Withdraw money
void withdrawMoney() {

    int accNo;
    float amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    int index = searchAccount(accNo);

    if (index == -1) {
        cout << "\nAccount Not Found!\n";
        return;
    }

    cout << "Enter Withdrawal Amount: ";
    cin >> amount;

    if (amount > accounts[index].balance) {

        cout << "\nInsufficient Balance!\n";

        return;
    }

    accounts[index].balance -= amount;

    saveToFile();

    cout << "\nAmount Withdrawn Successfully!\n";
}

// Check balance
void checkBalance() {

    int accNo;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    int index = searchAccount(accNo);

    if (index == -1) {

        cout << "\nAccount Not Found!\n";

        return;
    }

    cout << "\nCurrent Balance: " << accounts[index].balance << endl;
}

int main() {

    loadFromFile();

    int choice;

    do {

        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";

        cout << "\n1. Create Account";
        cout << "\n2. Display Accounts";
        cout << "\n3. Deposit Money";
        cout << "\n4. Withdraw Money";
        cout << "\n5. Check Balance";
        cout << "\n6. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            createNewAccount();
            break;

        case 2:
            displayAllAccounts();
            break;

        case 3:
            depositMoney();
            break;

        case 4:
            withdrawMoney();
            break;

        case 5:
            checkBalance();
            break;

        case 6:
            cout << "\nExiting Program...\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}