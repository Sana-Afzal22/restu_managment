

#include <iostream>
#include <unordered_map>
#include <string>
#include <iomanip>
using namespace std;

// Menu Class
class Menu {
public:
    unordered_map<string, double> items; // Item name and price

    void addItem(string name, double price) {
        items[name] = price;
    }

    void displayMenu() {
        cout << "\nMenu:\n";
        for (auto &item : items) {
            cout << left << setw(15) << item.first << " $" << item.second << "\n";
        }
    }
};

// Inventory Class
class Inventory {
public:
    unordered_map<string, int> stock; // Item name and quantity

    void addStock(string item, int quantity) {
        stock[item] += quantity;
    }

    void updateStock(string item, int quantity) {
        if (stock[item] >= quantity) {
            stock[item] -= quantity;
        } else {
            cout << "Not enough stock for " << item << "!\n";
        }
    }

    void displayStock() {
        cout << "\nInventory:\n";
        for (auto &item : stock) {
            cout << left << setw(15) << item.first << " " << item.second << " units\n";
        }
    }
};

// Order Class
class Order {
public:
    unordered_map<string, int> orderItems; // Item name and quantity

    void addItem(string item, int quantity) {
        orderItems[item] += quantity;
    }

    double calculateTotal(Menu &menu) {
        double total = 0;
        for (auto &item : orderItems) {
            total += menu.items[item.first] * item.second;
        }
        return total;
    }

    void displayOrder() {
        cout << "\nOrder Details:\n";
        for (auto &item : orderItems) {
            cout << left << setw(15) << item.first << " " << item.second << " units\n";
        }
    }
};

// Reservation Class
class Reservation {
public:
    unordered_map<int, string> tableStatus; // Table number and customer name

    void reserveTable(int tableNumber, string customerName) {
        if (tableStatus[tableNumber].empty()) {
            tableStatus[tableNumber] = customerName;
            cout << "Table " << tableNumber << " reserved for " << customerName << ".\n";
        } else {
            cout << "Table " << tableNumber << " is already reserved by " << tableStatus[tableNumber] << ".\n";
        }
    }

    void displayReservations() {
        cout << "\nTable Reservations:\n";
        for (auto &table : tableStatus) {
            if (!table.second.empty()) {
                cout << "Table " << table.first << ": Reserved by " << table.second << "\n";
            } else {
                cout << "Table " << table.first << ": Available\n";
            }
        }
    }
};

// Main Function
int main() {
    Menu menu;
    Inventory inventory;
    Reservation reservation;
    Order order;

    // Sample Data
    menu.addItem("Pizza", 8.99);
    menu.addItem("Burger", 5.49);
    menu.addItem("Coke", 1.99);

    inventory.addStock("Pizza", 10);
    inventory.addStock("Burger", 15);
    inventory.addStock("Coke", 20);

    reservation.tableStatus[1] = ""; // Table 1 is available
    reservation.tableStatus[2] = ""; // Table 2 is available

    int choice;

    do {
        cout << "\n--- Restaurant Management System ---\n";
        cout << "1. Display Menu\n";
        cout << "2. Place an Order\n";
        cout << "3. View Inventory\n";
        cout << "4. Update Inventory\n";
        cout << "5. Reserve a Table\n";
        cout << "6. View Reservations\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            menu.displayMenu();
            break;

        case 2: {
            string item;
            int quantity;
            cout << "Enter item name: ";
            cin >> item;
            cout << "Enter quantity: ";
            cin >> quantity;

            if (inventory.stock[item] >= quantity) {
                order.addItem(item, quantity);
                inventory.updateStock(item, quantity);
                cout << "Item added to order.\n";
            } else {
                cout << "Not enough stock for " << item << ".\n";
            }
            cout << "Current Order Total: $" << order.calculateTotal(menu) << "\n";
            break;
        }

        case 3:
            inventory.displayStock();
            break;

        case 4: {
            string item;
            int quantity;
            cout << "Enter item name: ";
            cin >> item;
            cout << "Enter quantity to add: ";
            cin >> quantity;
            inventory.addStock(item, quantity);
            cout << "Inventory updated.\n";
            break;
        }

        case 5: {
            int tableNumber;
            string customerName;
            cout << "Enter table number: ";
            cin >> tableNumber;
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, customerName);
            reservation.reserveTable(tableNumber, customerName);
            break;
        }

        case 6:
            reservation.displayReservations();
            break;

        case 7:
            cout << "Exiting system. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
    }