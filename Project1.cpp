#include <iostream>
#include <fstream>  // For file handling
#include <iomanip>  // For formatting output
using namespace std;

// BankAccount class to represent a customer's bank account
class BankAccount {
private:
    int accountNumber;     // Unique account number for each customer
    char name[50];         // Customer's name
    double balance;        // Current balance of the account

public:
    // Function to create a new account
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Account Holder Name: ";
        cin.ignore();  // To clear the input buffer
        cin.getline(name, 50);
        cout << "Enter Initial Deposit: ";
        cin >> balance;
        cout << "Account Created Successfully!\n\n";
    }

    // Function to display account details
    void showAccount() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << name << endl;
        cout << "Balance: " << fixed << setprecision(2) << balance << endl;
    }

    // Function to modify account details (e.g., name)
    void modifyAccount() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Modify Account Holder Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Modify Balance: ";
        cin >> balance;
        cout << "Account Modified Successfully!\n\n";
    }

    // Function to deposit money into the account
    void deposit(double amount) {
        balance += amount;
        cout << "Amount Deposited Successfully!\n\n";
    }

    // Function to withdraw money from the account
    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!\n\n";
        } else {
            balance >= amount;
            cout << "Amount Withdrawn Successfully!\n\n";
        }
    }

    // Function to return account number (used for searching)
    int getAccountNumber() const {
        return accountNumber;
    }

    // Function to return current balance
    double getBalance() const {
        return balance;
    }
};

// Function prototypes
void writeAccount();
void displayAccount(int);
void modifyAccount(int);
void deleteAccount(int);
void depositWithdraw(int, int);

// Main menu for the Bank Management System
int main() {
    int choice;
    int accountNum;

    do {
        cout << "\n\n\t*** Bank Management System ***\n";
        cout << "\n\t1. Create New Account";
        cout << "\n\t2. Deposit Amount";
        cout << "\n\t3. Withdraw Amount";
        cout << "\n\t4. Balance Enquiry";
        cout << "\n\t5. Modify Account";
        cout << "\n\t6. Delete Account";
        cout << "\n\t7. Exit";
        cout << "\n\n\tSelect Your Option (1-7): ";
        cin >> choice;

        switch (choice) {
        case 1:
            writeAccount();
            break;
        case 2:
            cout << "Enter Account Number: ";
            cin >> accountNum;
            depositWithdraw(accountNum, 1);
            break;
        case 3:
            cout << "Enter Account Number: ";
            cin >> accountNum;
            depositWithdraw(accountNum, 2);
            break;
        case 4:
            cout << "Enter Account Number: ";
            cin >> accountNum;
            displayAccount(accountNum);
            break;
        case 5:
            cout << "Enter Account Number: ";
            cin >> accountNum;
            modifyAccount(accountNum);
            break;
        case 6:
            cout << "Enter Account Number: ";
            cin >> accountNum;
            deleteAccount(accountNum);
            break;
        case 7:
            cout << "Exiting the System. Goodbye!\n";
            break;
        default:
            cout << "Invalid Option! Please Try Again.\n";
        }
    } while (choice != 7);

    return 0;
}

// Function to write a new account to the file
void writeAccount() {
    BankAccount acc;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    acc.createAccount();
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
    outFile.close();
}

// Function to display account details
void displayAccount(int accountNum) {
    BankAccount acc;
    bool found = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);

    if (!inFile) {
        cout << "File could not be opened! Press any key...\n";
        return;
    }

    // Searching for the account by account number
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccountNumber() == accountNum) {
            acc.showAccount();
            found = true;
            break;
        }
    }

    inFile.close();
    if (!found)
        cout << "Account not found!\n";
}

// Function to modify account details
void modifyAccount(int accountNum) {
    BankAccount acc;
    fstream file;
    bool found = false;
    file.open("account.dat", ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "File could not be opened! Press any key...\n";
        return;
    }

    // Searching for the account by account number
    while (!file.eof() && found == false) {
        file.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount));

        if (acc.getAccountNumber() == accountNum) {
            acc.showAccount();
            cout << "Enter New Details for the Account:\n";
            acc.modifyAccount();
            int pos = (-1) * static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
            cout << "Account Updated Successfully!\n\n";
            found = true;
        }
    }

    file.close();
    if (!found)
        cout << "Account not found!\n";
}

// Function to delete an account
void deleteAccount(int accountNum) {
    BankAccount acc;
    ifstream inFile;
    ofstream outFile;

    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened! Press any key...\n";
        return;
    }

    outFile.open("temp.dat", ios::binary);

    // Copy all accounts except the one to be deleted
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccountNumber() != accountNum) {
            outFile.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
        }
    }

    inFile.close();
    outFile.close();

    // Remove old file and rename temp file
    remove("account.dat");
    rename("temp.dat", "account.dat");

    cout << "Account Deleted Successfully!\n";
}

// Function to handle deposit or withdrawal
void depositWithdraw(int accountNum, int option) {
    BankAccount acc;
    fstream file;
    double amount;
    bool found = false;

    file.open("account.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "File could not be opened! Press any key...\n";
        return;
    }

    // Searching for the account by account number
    while (!file.eof() && found == false) {
        file.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount));

        if (acc.getAccountNumber() == accountNum) {
            acc.showAccount();
            if (option == 1) {
                cout << "Enter Amount to Deposit: ";
                cin >> amount;
                acc.deposit(amount);
            } else if (option == 2) {
                cout << "Enter Amount to Withdraw: ";
                cin >> amount;
                acc.withdraw(amount);
            }

            int pos = (-1) * static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
            cout << "Transaction Completed Successfully!\n\n";
            found = true;
        }
    }

    file.close();
    if (!found)
        cout << "Account not found!\n";
}
