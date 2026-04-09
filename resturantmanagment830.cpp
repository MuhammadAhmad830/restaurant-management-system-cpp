#include <iostream>
#include <windows.h>  
#include <conio.h>  
#include <fstream>  
using namespace std;

const int MAX_ORDERS = 10; 
const float PRICE_PIZZA = 10.00;
const float PRICE_BURGER = 5.00;
const float PRICE_PASTA = 7.50;
const float PRICE_SALAD = 4.00;
const float EXCHANGE_RATE = 300.00;  

// Global variables
int orderCount = 0;
int orderIDs[MAX_ORDERS];
string dishNames[MAX_ORDERS];
int quantities[MAX_ORDERS];
float prices[MAX_ORDERS];
float totalSales = 0.0;

// Function prototypes
void clearScreen();
void createOrder();
void viewOrders();
void updateOrder();
void deleteOrder();
void header();
void viewTotalSales();
void saveOrdersToFile();
void loadOrdersFromFile();

int main() {
   
    int choice;

   
    loadOrdersFromFile();

    while (true) {
        
       system("cls");
        
        header();
        
        // Menu Display
        cout << "\n===== Restaurant Management System =====" << endl;
        cout << "1. Create Order" << endl;
        cout << "2. View Orders" << endl;
        cout << "3. Update Order" << endl;
        cout << "4. Delete Order" << endl;
        cout << "5. View Total Sales" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        
        if (choice == 6) {
            cout << "Exiting the system..." << endl;
            saveOrdersToFile(); 
            break;
        }

       
        if (choice == 1) {
            createOrder();
        } else if (choice == 2) {
            viewOrders();
        } else if (choice == 3) {
            updateOrder();
        } else if (choice == 4) {
            deleteOrder();
        } else if (choice == 5) {
            viewTotalSales();
        } else {
            cout << "Invalid choice. Please try again." << endl;
            getch(); 
        }
    }

    return 0;
}



void createOrder() {
    if (orderCount < MAX_ORDERS) {
        int orderType, quantity;
        float price;

       system("cls");
        cout << "Enter the dish you want to order:" << endl;
        cout << "1. Pizza - " << PRICE_PIZZA * EXCHANGE_RATE << " PKR" << endl;
        cout << "2. Burger - " << PRICE_BURGER * EXCHANGE_RATE << " PKR" << endl;
        cout << "3. Pasta - " << PRICE_PASTA * EXCHANGE_RATE << " PKR" << endl;
        cout << "4. Salad - " << PRICE_SALAD * EXCHANGE_RATE << " PKR" << endl;
        cout << "Enter your choice: ";
        cin >> orderType;
        cout << "Enter quantity: ";
        cin >> quantity;

     
        if (orderType == 1) {
            dishNames[orderCount] = "Pizza";
            price = PRICE_PIZZA;
        } else if (orderType == 2) {
            dishNames[orderCount] = "Burger";
            price = PRICE_BURGER;
        } else if (orderType == 3) {
            dishNames[orderCount] = "Pasta";
            price = PRICE_PASTA;
        } else if (orderType == 4) {
            dishNames[orderCount] = "Salad";
            price = PRICE_SALAD;
        } else {
            cout << "Invalid choice!" << endl;
            getch(); 
            return;
        }

        // Save the order
        orderIDs[orderCount] = orderCount + 1;  
        quantities[orderCount] = quantity;
        prices[orderCount] = price;
        totalSales += price * quantity;
        orderCount++;

        cout << "Order added successfully!" << endl;

       
        saveOrdersToFile();
    } else {
        cout << "Maximum orders reached. Cannot add more orders." << endl;
    }
    getch(); 
}

// Function to view all orders
void viewOrders() {
   system("cls");
    if (orderCount == 0) {
        cout << "No orders placed yet." << endl;
    } else {
        cout << "\n===== Orders List =====" << endl;
        for (int i = 0; i < orderCount; i++) {
            cout << "Order ID: " << orderIDs[i] 
                 << ", Dish: " << dishNames[i] 
                 << ", Quantity: " << quantities[i]
                 << ", Price: " << prices[i] * quantities[i] * EXCHANGE_RATE << " PKR" << endl;
        }
    }
    getch();
}


void updateOrder() {
   system("cls");
    if (orderCount == 0) {
        cout << "No orders to update." << endl;
    } else {
        int orderID, newQuantity;
        cout << "Enter the Order ID to update: ";
        cin >> orderID;

        // Find order by ID
        bool found = false;
        for (int i = 0; i < orderCount; i++) {
            if (orderIDs[i] == orderID) {
                cout << "Current quantity: " << quantities[i] << endl;
                cout << "Enter new quantity: ";
                cin >> newQuantity;
                totalSales -= prices[i] * quantities[i]; 
                quantities[i] = newQuantity;
                totalSales += prices[i] * quantities[i];  
                cout << "Order updated successfully!" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Order ID not found!" << endl;
        }

       
        saveOrdersToFile();
    }
    getch(); 
}


void deleteOrder() {
  system("cls");
    if (orderCount == 0) {
        cout << "No orders to delete." << endl;
    } else {
        int orderID;
        cout << "Enter the Order ID to delete: ";
        cin >> orderID; // 2

       
        bool found = false;  
        for (int i = 0; i < orderCount; i++) {
            if (orderIDs[i] == orderID) {
                totalSales -= prices[i] * quantities[i];  

                
                for (int j = i; j < orderCount - 1; j++) {
                    orderIDs[j] = orderIDs[j + 1];
                    dishNames[j] = dishNames[j + 1];
                    quantities[j] = quantities[j + 1];
                    prices[j] = prices[j + 1];
                }

                orderCount--;  
                cout << "Order deleted successfully!" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Order ID not found!" << endl;
        }

        
        saveOrdersToFile();
    }
    getch(); 
}


void viewTotalSales() {
    system("cls");
    cout << "\nTotal Sales: " << totalSales * EXCHANGE_RATE << " PKR" << endl;
    getch();
}

// Function to save orders to a file
void saveOrdersToFile() {
    ofstream outFile("orders.txt", ios::out);
    if (outFile.is_open()) {
        for (int i = 0; i < orderCount; i++) {
            outFile << orderIDs[i] << "\n"
                   << dishNames[i] << "\n"
                    << quantities[i] << "\n"
                    << prices[i] << "\n";
        }
        outFile.close();
        cout << "Orders saved to file successfully!" << endl;
    } else {
        cout << "Error opening file for saving orders!" << endl;
    }
}

// Function to load orders from a file
void loadOrdersFromFile() {
    ifstream inFile("orders.txt", ios::in);
    if (inFile.is_open()) {
        while (inFile >> orderIDs[orderCount]) {
            inFile.ignore(); 
            getline(inFile, dishNames[orderCount]);
            inFile >> quantities[orderCount];
            inFile >> prices[orderCount];
            totalSales += prices[orderCount] * quantities[orderCount];
            orderCount++;
        }
        inFile.close();
        cout << "Orders loaded from file successfully!" << endl;
    } else {
        cout << "No previous orders found, starting fresh." << endl;
    }
}
void header(){
     system("color 1F");
    // system("color 02");
     
    cout << " _____ _____ _____ _____ _____ _____ _____ _____ _____                      " << endl;
    cout << "| __  |   __|   __|_   _|  |  | __  |  _  |   | |_   _|                    " << endl;
    cout << "|    -|   __|__   | | | |  |  |    -|     | | | | | |                      " << endl;
    cout << "|__|__|_____|_____| |_| |_____|__|__|__|__|_|___| |_|                      " << endl;
    cout << "                                                                         " << endl;
    cout << "               _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ " << endl;
    cout << "              |     |  _  |   | |  _  |   __|   __|     |   __|   | |_   _|" << endl;
    cout << "              | | | |     | | | |     |  |  |   __| | | |   __| | | | | |  " << endl;
    cout << "              |_|_|_|__|__|_|___|__|__|_____|_____|_|_|_|_____|_|___| |_|  " << endl;
    cout << "                                                                         " << endl;
    cout << "                                       _____ __ __ _____ _____ _____ _____ " << endl;
    cout << "                                      |   __|  |  |   __|_   _|   __|     |" << endl;
    cout << "                                      |__   |_   _|__   | | | |   __| | | |" << endl;
    cout << "                                      |_____| |_| |_____| |_| |_____|_|_|_|" << endl;

   
}

