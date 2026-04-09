#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ORDERS = 20; 
const float PRICE_PIZZA = 10.00;
const float PRICE_BURGER = 5.00;
const float PRICE_PASTA = 7.50;
const float PRICE_SALAD = 4.00;
const float EXCHANGE_RATE = 300.00;  

int orderCount = 0;
int orderIDs[20];
string dishNames[20];
int quantities[20];
float prices[20];
float totalSales = 0.0;

void header();
void createOrder();
void viewOrders();
void updateOrder();
void deleteOrder();
void viewTotalSales();
void saveOrdersToFile();
void loadOrdersFromFile();

int main() {
    loadOrdersFromFile();

    int choice;
    while (true) {
        system("cls");
        header();
        
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
            cout << "\nExiting the system... Thank you!" << endl;
            saveOrdersToFile();
            break;
        }

        if (choice == 1) createOrder();
        else if (choice == 2) viewOrders();
        else if (choice == 3) updateOrder();
        else if (choice == 4) deleteOrder();
        else if (choice == 5) viewTotalSales();
        else {
            cout << "\nInvalid choice! Please try again." << endl;
            getch();
        }
    }
    return 0;
}

void header() {
    system("color 1F");
    
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
    cout << "\n                     RESTAURANT MANAGEMENT SYSTEM                         " << endl;
    cout << "  ===================================================================== " << endl;
}

void createOrder() {
    if (orderCount >= 20) {
        cout << "\nMaximum orders limit reached!" << endl;
        getch();
        return;
    }

    system("cls");
    header();

    int orderType, quantity;
    float price = 0;

    cout << "\nEnter the dish you want to order:" << endl;
    cout << "1. Pizza  - " << PRICE_PIZZA * EXCHANGE_RATE << " PKR" << endl;
    cout << "2. Burger - " << PRICE_BURGER * EXCHANGE_RATE << " PKR" << endl;
    cout << "3. Pasta  - " << PRICE_PASTA * EXCHANGE_RATE << " PKR" << endl;
    cout << "4. Salad  - " << PRICE_SALAD * EXCHANGE_RATE << " PKR" << endl;
    cout << "Enter your choice: ";
    cin >> orderType;

    if (orderType == 1) {
        dishNames[orderCount] = "Pizza";
        price = PRICE_PIZZA;
    } 
    else if (orderType == 2) {
        dishNames[orderCount] = "Burger";
        price = PRICE_BURGER;
    } 
    else if (orderType == 3) {
        dishNames[orderCount] = "Pasta";
        price = PRICE_PASTA;
    } 
    else if (orderType == 4) {
        dishNames[orderCount] = "Salad";
        price = PRICE_SALAD;
    } 
    else {
        cout << "\nInvalid choice!" << endl;
        getch();
        return;
    }

    cout << "Enter quantity: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "\nQuantity must be greater than 0!" << endl;
        getch();
        return;
    }

    orderIDs[orderCount] = orderCount + 1;
    quantities[orderCount] = quantity;
    prices[orderCount] = price;
    totalSales += price * quantity;
    orderCount++;

    cout << "\nOrder added successfully! Order ID: " << orderIDs[orderCount-1] << endl;
    saveOrdersToFile();
    getch();
}

void viewOrders() {
    system("cls");
    header();

    if (orderCount == 0) {
        cout << "\nNo orders placed yet." << endl;
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
    header();

    if (orderCount == 0) {
        cout << "\nNo orders to update." << endl;
        getch();
        return;
    }

    int orderID, newQuantity;
    cout << "\nEnter the Order ID to update: ";
    cin >> orderID;

    bool found = false;
    for (int i = 0; i < orderCount; i++) {
        if (orderIDs[i] == orderID) {
            cout << "Current quantity: " << quantities[i] << endl;
            cout << "Enter new quantity: ";
            cin >> newQuantity;

            if (newQuantity <= 0) {
                cout << "\nQuantity must be greater than 0!" << endl;
                getch();
                return;
            }

            totalSales -= prices[i] * quantities[i];
            quantities[i] = newQuantity;
            totalSales += prices[i] * quantities[i];
            cout << "\nOrder updated successfully!" << endl;
            found = true;
            saveOrdersToFile();
            break;
        }
    }
    if (!found) {
        cout << "\nOrder ID not found!" << endl;
    }
    getch();
}

void deleteOrder() {
    system("cls");
    header();

    if (orderCount == 0) {
        cout << "\nNo orders to delete." << endl;
        getch();
        return;
    }

    int orderID;
    cout << "\nEnter the Order ID to delete: ";
    cin >> orderID;

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
            cout << "\nOrder deleted successfully!" << endl;
            found = true;
            saveOrdersToFile();
            break;
        }
    }
    if (!found) {
        cout << "\nOrder ID not found!" << endl;
    }
    getch();
}

void viewTotalSales() {
    system("cls");
    header();
    cout << "\nTotal Sales: " << totalSales * EXCHANGE_RATE << " PKR" << endl;
    getch();
}

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
    }
}

void loadOrdersFromFile() {
    ifstream inFile("orders.txt", ios::in);
    orderCount = 0;
    totalSales = 0.0;

    if (inFile.is_open()) {
        while (orderCount < 20 && inFile >> orderIDs[orderCount]) {
            inFile.ignore();
            getline(inFile, dishNames[orderCount]);
            inFile >> quantities[orderCount];
            inFile >> prices[orderCount];
            totalSales += prices[orderCount] * quantities[orderCount];
            orderCount++;
        }
        inFile.close();
    }
}

