#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <limits>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ============================================================
// AMOUR BAGS & ACCESSORIES - INVENTORY MANAGEMENT SYSTEM
// Burgundy and gold boutique console theme
// ============================================================

#define RESET      "\033[0m"
#define BOLD       "\033[1m"
#define GOLD       "\033[38;5;220m"
#define CHOCOLATE  "\033[38;5;88m"
#define CARAMEL    "\033[38;5;95m"
#define CREAM      "\033[38;5;230m"
#define SAGE       "\033[38;5;108m"
#define ROSE       "\033[38;5;174m"
#define MUTED      "\033[38;5;245m"
#define RED        "\033[38;5;160m"

struct Product {
    int id;
    string name;
    string brand;
    double price;
    int stock;
};

const int MAX_PRODUCTS = 50;
Product products[MAX_PRODUCTS] = {
    {101, "Backpack", "Herschel", 1500.00, 15},
    {102, "School Bag", "Jansport", 1200.00, 20},
    {103, "Mini Handbag", "Guess", 2500.00, 10},
    {104, "Shoulder Bag", "Charles & Keith", 2800.00, 8},
    {105, "Tote Bag", "Longchamp", 2200.00, 12},
    {106, "Bag Charm", "Kawaii", 250.00, 25},
    {107, "Bag Organizer", "Daiso", 180.00, 30},
    {108, "Bag Strap", "Fashion", 350.00, 18},
    {109, "Coin Purse", "Guess", 450.00, 14},
    {110, "Bag Rain Cover", "TravelMate", 200.00, 20}
};

int productCount = 10;
double totalSales = 0.0;
int totalTransactions = 0;
int totalItemsSold = 0;

string lowerCase(string value) {
    transform(value.begin(), value.end(), value.begin(),
        [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return value;
}

void line() {
    cout << GOLD << "------------------------------------------------------------" << RESET << '\n';
}

void header(const string& title) {
    cout << "\n" << GOLD << BOLD;
    cout << "============================================================\n";
    cout << "                    " << title << "\n";
    cout << "============================================================\n";
    cout << RESET;
}

int getInteger(const string& message) {
    string input;
    while (true) {
        cout << CREAM << message << RESET;
        getline(cin, input);
        stringstream ss(input);
        int value;
        char extra;
        if (ss >> value && !(ss >> extra)) return value;
        cout << RED << "[NOTICE] Please enter a valid whole number.\n" << RESET;
    }
}

double getPrice(const string& message = "Price: ") {
    string input;
    while (true) {
        cout << CREAM << message << RESET;
        getline(cin, input);
        input.erase(remove(input.begin(), input.end(), ','), input.end());
        stringstream ss(input);
        double value;
        char extra;
        if (ss >> value && !(ss >> extra) && value >= 0 && value <= 1000000000.0)
            return value;
        cout << RED << "[NOTICE] Please enter a valid non-negative price.\n" << RESET;
    }
}

int getNonNegativeInteger(const string& message) {
    while (true) {
        int value = getInteger(message);
        if (value >= 0) return value;
        cout << RED << "[NOTICE] Value cannot be negative.\n" << RESET;
    }
}

int findProduct(int id) {
    for (int i = 0; i < productCount; ++i)
        if (products[i].id == id) return i;
    return -1;
}

void displayProductRow(const Product& p) {
    cout << left << setw(8) << p.id
         << setw(21) << p.name
         << setw(22) << p.brand
         << "P" << right << setw(10) << fixed << setprecision(2) << p.price
         << setw(9) << p.stock << '\n';
}

void displayProducts() {
    header("AMOUR PRODUCT COLLECTION");
    if (productCount == 0) {
        cout << ROSE << "No products are currently available.\n" << RESET;
        return;
    }
    cout << CHOCOLATE << left << setw(8) << "ID"
         << setw(21) << "PRODUCT"
         << setw(22) << "BRAND"
         << right << setw(11) << "PRICE"
         << setw(9) << "STOCK" << RESET << '\n';
    line();
    for (int i = 0; i < productCount; ++i) displayProductRow(products[i]);
    line();
}

void searchProduct() {
    header("SMART PRODUCT SEARCH");
    cout << "Search by Product ID, product name, or brand.\n";
    cout << CREAM << "Enter keyword: " << RESET;
    string key;
    getline(cin, key);
    key = lowerCase(key);

    bool found = false;
    for (int i = 0; i < productCount; ++i) {
        string idText = to_string(products[i].id);
        if (lowerCase(products[i].name).find(key) != string::npos ||
            lowerCase(products[i].brand).find(key) != string::npos ||
            idText.find(key) != string::npos) {
            if (!found) {
                cout << left << setw(8) << "ID" << setw(21) << "PRODUCT"
                     << setw(22) << "BRAND" << right << setw(11) << "PRICE"
                     << setw(9) << "STOCK" << '\n';
                line();
            }
            displayProductRow(products[i]);
            found = true;
        }
    }
    if (!found) cout << ROSE << "No matching product found.\n" << RESET;
}

void addProduct() {
    header("ADD NEW PRODUCT");
    if (productCount >= MAX_PRODUCTS) {
        cout << RED << "Inventory capacity reached.\n" << RESET;
        return;
    }

    int id = getInteger("Product ID: ");
    if (id <= 0 || findProduct(id) != -1) {
        cout << RED << "Invalid or existing Product ID.\n" << RESET;
        return;
    }

    string name, brand;
    cout << CREAM << "Product name: " << RESET;
    getline(cin, name);
    cout << CREAM << "Brand: " << RESET;
    getline(cin, brand);
    if (name.empty() || brand.empty()) {
        cout << RED << "Product name and brand cannot be empty.\n" << RESET;
        return;
    }

    double price = getPrice();
    int stock = getNonNegativeInteger("Initial stock: ");
    products[productCount++] = {id, name, brand, price, stock};
    cout << SAGE << "Product added successfully!\n" << RESET;
}

void updateProduct() {
    header("UPDATE PRODUCT DETAILS");
    int id = getInteger("Enter Product ID: ");
    int index = findProduct(id);
    if (index == -1) {
        cout << RED << "Product not found.\n" << RESET;
        return;
    }

    cout << "\n[1] Update Name\n[2] Update Brand\n[3] Update Price\n"
         << "[4] Update Stock\n[5] Update All Details\n[0] Cancel\n";
    int choice = getInteger("Choose an option: ");
    string value;

    switch (choice) {
        case 1:
            cout << "New product name: ";
            getline(cin, value);
            if (!value.empty()) products[index].name = value;
            else cout << RED << "Name cannot be empty.\n" << RESET;
            break;
        case 2:
            cout << "New brand: ";
            getline(cin, value);
            if (!value.empty()) products[index].brand = value;
            else cout << RED << "Brand cannot be empty.\n" << RESET;
            break;
        case 3:
            products[index].price = getPrice("New price: ");
            break;
        case 4:
            products[index].stock = getNonNegativeInteger("New stock: ");
            break;
        case 5:
            cout << "New product name: ";
            getline(cin, value);
            if (value.empty()) { cout << RED << "Name cannot be empty.\n" << RESET; return; }
            products[index].name = value;
            cout << "New brand: ";
            getline(cin, value);
            if (value.empty()) { cout << RED << "Brand cannot be empty.\n" << RESET; return; }
            products[index].brand = value;
            products[index].price = getPrice("New price: ");
            products[index].stock = getNonNegativeInteger("New stock: ");
            break;
        case 0:
            cout << "Update cancelled.\n";
            return;
        default:
            cout << RED << "Invalid option.\n" << RESET;
            return;
    }
    cout << SAGE << "Product details updated.\n" << RESET;
}

void removeProduct() {
    header("REMOVE PRODUCT");
    int id = getInteger("Enter Product ID to remove: ");
    int index = findProduct(id);
    if (index == -1) {
        cout << RED << "Product not found.\n" << RESET;
        return;
    }

    cout << "Selected: " << products[index].name << " (" << products[index].brand << ")\n";
    int confirm = getInteger("Confirm removal? [1] Yes  [2] No: ");
    if (confirm != 1) {
        cout << "Removal cancelled.\n";
        return;
    }

    for (int i = index; i < productCount - 1; ++i)
        products[i] = products[i + 1];
    --productCount;
    cout << SAGE << "Product removed successfully.\n" << RESET;
}

double chooseDiscount() {
    cout << "\n  CHECKOUT DISCOUNTS\n"
         << "  [1] No Discount\n"
         << "  [2] 5% Discount\n"
         << "  [3] 10% Discount\n"
         << "  [4] 15% Discount\n";

    while (true) {
        cout << GOLD << "  Select Discount: " << RESET;
        string input;
        getline(cin, input);
        input.erase(remove_if(input.begin(), input.end(),
            [](unsigned char c) { return isspace(c); }), input.end());

        bool hasPercent = !input.empty() && input.back() == '%';
        if (hasPercent) input.pop_back();

        try {
            size_t pos = 0;
            int value = stoi(input, &pos);
            if (pos != input.length()) throw invalid_argument("invalid");

            if (hasPercent) {
                if (value == 0 || value == 5 || value == 10 || value == 15)
                    return value / 100.0;
            } else {
                switch (value) {
                    case 0: case 1: return 0.00;
                    case 2: case 5: return 0.05;
                    case 3: case 10: return 0.10;
                    case 4: case 15: return 0.15;
                }
            }
        } catch (...) {
            // Keep asking until a supported discount is entered.
        }
        cout << RED << "[NOTICE] Enter 1-4 or 0%, 5%, 10%, 15%.\n" << RESET;
    }
}

void checkout() {
    header("SALES & CHECKOUT");
    int id = getInteger("Enter Product ID: ");
    int index = findProduct(id);
    if (index == -1) {
        cout << RED << "Product not found.\n" << RESET;
        return;
    }

    cout << "\nProduct: " << products[index].name
         << "\nBrand: " << products[index].brand
         << "\nPrice: P" << fixed << setprecision(2) << products[index].price
         << "\nAvailable Stock: " << products[index].stock << '\n';

    int quantity = getInteger("Quantity to sell: ");
    if (quantity <= 0 || quantity > products[index].stock) {
        cout << RED << "Invalid quantity or insufficient stock.\n" << RESET;
        return;
    }

    double subtotal = products[index].price * quantity;
    double discountRate = chooseDiscount();
    double discountAmount = subtotal * discountRate;
    double total = subtotal - discountAmount;

    products[index].stock -= quantity;
    totalSales += total;
    ++totalTransactions;
    totalItemsSold += quantity;

    header("AMOUR SALES RECEIPT");
    cout << left << setw(23) << "Product:" << products[index].name << '\n'
         << left << setw(23) << "Brand:" << products[index].brand << '\n'
         << left << setw(23) << "Quantity:" << quantity << '\n'
         << left << setw(23) << "Unit Price:" << "P" << fixed << setprecision(2) << products[index].price << '\n'
         << left << setw(23) << "Subtotal:" << "P" << subtotal << '\n'
         << left << setw(23) << "Discount Rate:" << (discountRate * 100) << "%\n"
         << left << setw(23) << "Discount Amount:" << "P" << discountAmount << '\n';
    line();
    cout << BOLD << GOLD << left << setw(23) << "TOTAL AMOUNT:" << "P" << total << RESET << '\n';
    cout << "Remaining Stock: " << products[index].stock << '\n';
    cout << SAGE << "\nCheckout completed successfully!\n" << RESET;
}

void restockInventory() {
    header("RESTOCK INVENTORY");
    int id = getInteger("Enter Product ID: ");
    int index = findProduct(id);
    if (index == -1) {
        cout << RED << "Product not found.\n" << RESET;
        return;
    }

    cout << "Product: " << products[index].name
         << "\nCurrent stock: " << products[index].stock << '\n';
    int amount = getInteger("Additional stock: ");
    if (amount <= 0 || products[index].stock > numeric_limits<int>::max() - amount) {
        cout << RED << "Enter a valid positive quantity.\n" << RESET;
        return;
    }
    products[index].stock += amount;
    cout << SAGE << "Restock successful. New stock: " << products[index].stock << RESET << '\n';
}

void sortProductsByPrice() {
    header("SORT PRODUCTS BY PRICE");
    for (int i = 0; i < productCount - 1; ++i) {
        for (int j = 0; j < productCount - i - 1; ++j) {
            if (products[j].price > products[j + 1].price)
                swap(products[j], products[j + 1]);
        }
    }
    cout << SAGE << "Products sorted from lowest to highest price using Bubble Sort.\n" << RESET;
    displayProducts();
}

void lowStockNotifications() {
    header("LOW STOCK NOTIFICATIONS");
    bool found = false;
    for (int i = 0; i < productCount; ++i) {
        if (products[i].stock <= 5) {
            cout << ROSE << "ID: " << products[i].id
                 << " | " << products[i].name
                 << " | " << products[i].brand
                 << " | Remaining stock: " << products[i].stock << RESET << '\n';
            found = true;
        }
    }
    if (!found) cout << SAGE << "All products have stock above the low-stock limit (5).\n" << RESET;
}

void inventoryOverview() {
    header("INVENTORY OVERVIEW");
    int totalStock = 0;
    double totalValue = 0.0;
    for (int i = 0; i < productCount; ++i) {
        totalStock += products[i].stock;
        totalValue += products[i].price * products[i].stock;
    }
    cout << left << setw(28) << "Product types:" << productCount << '\n'
         << left << setw(28) << "Total units in stock:" << totalStock << '\n'
         << left << setw(28) << "Total inventory value:" << "P" << fixed << setprecision(2) << totalValue << '\n';
}

void salesPerformanceReport() {
    header("SALES PERFORMANCE REPORT");
    cout << left << setw(28) << "Completed transactions:" << totalTransactions << '\n'
         << left << setw(28) << "Items sold:" << totalItemsSold << '\n'
         << left << setw(28) << "Total sales:" << "P" << fixed << setprecision(2) << totalSales << '\n';
    if (totalTransactions > 0)
        cout << left << setw(28) << "Average sale:" << "P" << totalSales / totalTransactions << '\n';
    else
        cout << MUTED << "No completed sales yet.\n" << RESET;
}

void boutiqueDashboard() {
    header("AMOUR BOUTIQUE DASHBOARD");
    int totalStock = 0, lowStockCount = 0;
    double inventoryValue = 0.0;
    for (int i = 0; i < productCount; ++i) {
        totalStock += products[i].stock;
        inventoryValue += products[i].price * products[i].stock;
        if (products[i].stock <= 5) ++lowStockCount;
    }

    cout << GOLD << BOLD << "                 BOUTIQUE AT A GLANCE\n" << RESET;
    line();
    cout << left << setw(30) << "Listed products:" << productCount << '\n'
         << left << setw(30) << "Available units:" << totalStock << '\n'
         << left << setw(30) << "Low-stock products:" << lowStockCount << '\n'
         << left << setw(30) << "Inventory value:" << "P" << fixed << setprecision(2) << inventoryValue << '\n'
         << left << setw(30) << "Sales transactions:" << totalTransactions << '\n'
         << left << setw(30) << "Items sold:" << totalItemsSold << '\n'
         << left << setw(30) << "Total sales:" << "P" << totalSales << '\n';
    line();
}

void showMenu() {
    cout << "\n";
    cout << GOLD << BOLD
         << "============================================================\n"
         << "                    AMOUR BAGS & ACCESSORIES\n"
         << "============================================================\n"
         << "             MODERN MINIMALIST BOUTIQUE COLLECTION\n"
         << "------------------------------------------------------------\n"
         << RESET;
    cout << CHOCOLATE << BOLD
         << "\n  [01] Display Product Collection"
         << "\n  [02] Smart Product Search"
         << "\n  [03] Add New Product"
         << "\n  [04] Update Product Details"
         << "\n  [05] Remove Product"
         << "\n  [06] Sales & Checkout"
         << "\n  [07] Restock Inventory"
         << "\n  [08] Sort Products by Price"
         << "\n  [09] Low Stock Notifications"
         << "\n  [10] Inventory Overview"
         << "\n  [11] Sales Performance Report"
         << "\n  [12] Boutique Dashboard"
         << "\n  [00] Exit System"
         << RESET << '\n';
    line();
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(output, &mode))
        SetConsoleMode(output, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

    int choice;
    do {
        showMenu();
        choice = getInteger("  Enter your choice: ");
        switch (choice) {
            case 1: displayProducts(); break;
            case 2: searchProduct(); break;
            case 3: addProduct(); break;
            case 4: updateProduct(); break;
            case 5: removeProduct(); break;
            case 6: checkout(); break;
            case 7: restockInventory(); break;
            case 8: sortProductsByPrice(); break;
            case 9: lowStockNotifications(); break;
            case 10: inventoryOverview(); break;
            case 11: salesPerformanceReport(); break;
            case 12: boutiqueDashboard(); break;
            case 0:
                cout << GOLD << BOLD
                     << "\nThank you for visiting AMOUR Bags & Accessories!\n"
                     << "Have a lovely day!\n" << RESET;
                break;
            default:
                cout << RED << "[NOTICE] Choose a valid option from 0 to 12.\n" << RESET;
        }

        if (choice != 0) {
            cout << "\n";
            cout << MUTED << "Press Enter to return to the main menu..." << RESET;
            string pause;
            getline(cin, pause);
        }
    } while (choice != 0);

    return 0;
}
