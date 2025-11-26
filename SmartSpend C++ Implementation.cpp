/*
 * SmartSpend - Student Financial Management System
 * CIT234 Final Project
 * Developers: Garyson Walker, Destiny Abraham
 */

#include <iostream>
#include <string>
using namespace std;

//  LINKED LIST 

struct Node {
    string description;
    double amount;
    string type; // "income" or "expense"
    Node* next;
};

class TransactionList {
private:
    Node* head;

public:
    TransactionList() { head = NULL; }
    
    // Add transaction to front of list
    // Time Complexity: O(1) - Constant time insertion
    void add(string desc, double amt, string type) {
        Node* newNode = new Node();
        newNode->description = desc;
        newNode->amount = amt;
        newNode->type = type;
        newNode->next = head;
        head = newNode;
    }
    
    // Calculate total expenses by traversing linked list
    // Time Complexity: O(n) - Must visit each node
    double getTotalExpenses() {
        double total = 0;
        Node* curr = head;
        while (curr != NULL) {
            if (curr->type == "expense")
                total += curr->amount;
            curr = curr->next;
        }
        return total;
    }
    
    // Calculate total income by traversing linked list
    // Time Complexity: O(n) - Must visit each node
    double getTotalIncome() {
        double total = 0;
        Node* curr = head;
        while (curr != NULL) {
            if (curr->type == "income")
                total += curr->amount;
            curr = curr->next;
        }
        return total;
    }
    
    // Count number of expense transactions
    // Time Complexity: O(n) - Linear search through list
    int countExpenses() {
        int count = 0;
        Node* curr = head;
        while (curr != NULL) {
            if (curr->type == "expense")
                count++;
            curr = curr->next;
        }
        return count;
    }
    
    // Display recent transactions (up to 10)
    // Time Complexity: O(n) - Worst case visits all nodes
    void display() {
        Node* curr = head;
        if (curr == NULL) {
            cout << "No transactions yet.\n";
            return;
        }
        int i = 0;
        while (curr != NULL && i < 10) {
            cout << (curr->type == "expense" ? "-" : "+") 
                 << "$" << curr->amount << " - " 
                 << curr->description << "\n";
            curr = curr->next;
            i++;
        }
    }
};

// ============= QUEUE =============

struct SavingsNode {
    double amount;
    SavingsNode* next;
};

class SavingsQueue {
private:
    SavingsNode* front;
    SavingsNode* rear;

public:
    SavingsQueue() { front = rear = NULL; }
    
    // Add savings to end of queue (FIFO principle)
    // Time Complexity: O(1) - Direct insertion at rear
    void enqueue(double amt) {
        SavingsNode* newNode = new SavingsNode();
        newNode->amount = amt;
        newNode->next = NULL;
        
        if (rear == NULL) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    
    // Calculate total savings in queue
    // Time Complexity: O(n) - Must traverse entire queue
    double getTotal() {
        double total = 0;
        SavingsNode* curr = front;
        while (curr != NULL) {
            total += curr->amount;
            curr = curr->next;
        }
        return total;
    }
};

// ============= MAIN PROGRAM =============

int main() {
    TransactionList transactions;
    SavingsQueue savings;
    double dailyAllowance;
    
    cout << "\n=== WELCOME TO SMARTSPEND ===\n\n";
    
    cout << "Enter daily allowance: $";
    cin >> dailyAllowance;
    
    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Expense\n";
        cout << "2. Add Income\n";
        cout << "3. Add to Savings\n";
        cout << "4. View Summary\n";
        cout << "5. View Projected Savings\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            string desc;
            double amt;
            cout << "Description: ";
            getline(cin, desc);
            cout << "Amount: $";
            cin >> amt;
            transactions.add(desc, amt, "expense");
            cout << "Expense added!\n";
        }
        else if (choice == 2) {
            string desc;
            double amt;
            cout << "Description: ";
            getline(cin, desc);
            cout << "Amount: $";
            cin >> amt;
            transactions.add(desc, amt, "income");
            cout << "Income added!\n";
        }
        else if (choice == 3) {
            double amt;
            cout << "Amount: $";
            cin >> amt;
            savings.enqueue(amt);
            cout << "Saved $" << amt << "!\n";
        }
        else if (choice == 4) {
            cout << "\n=== DAILY SUMMARY ===\n";
            double income = transactions.getTotalIncome();
            double expenses = transactions.getTotalExpenses();
            cout << "Income:   $" << income << "\n";
            cout << "Expenses: $" << expenses << "\n";
            cout << "Balance:  $" << (income - expenses) << "\n\n";
            transactions.display();
        }
        else if (choice == 5) {
            // ===== CORE SAVINGS PROJECTION ALGORITHM =====
            // Algorithm Steps:
            // 1. Calculate average daily spending from transactions
            // 2. Subtract from daily allowance to get surplus
            // 3. Multiply surplus by remaining days
            // 4. Display projected savings
            
            cout << "\n=== PROJECTED SAVINGS ===\n";
            int daysLeft = 30;
            int expenseCount = transactions.countExpenses();
            double projected = 0;
            
            if (expenseCount > 0) {
                double avgSpending = transactions.getTotalExpenses() / expenseCount;
                projected = (dailyAllowance - avgSpending) * daysLeft;
            } else {
                projected = dailyAllowance * daysLeft;
            }
            
            if (projected < 0) projected = 0;
            
            cout << "Daily Allowance: $" << dailyAllowance << "\n";
            cout << "Days Remaining:  " << daysLeft << "\n";
            cout << "Projected:       $" << projected << "\n";
            cout << "Current Savings: $" << savings.getTotal() << "\n";
            cout << "Potential Total: $" << (savings.getTotal() + projected) << "\n";
        }
        else if (choice == 6) {
            cout << "\nThank you for using SmartSpend!\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    
    return 0;
}