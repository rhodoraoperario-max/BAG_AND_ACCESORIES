#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ==========================================
// AMOUR BURGUNDY LUXURY COLOR THEME
// ==========================================

#define RESET       "\033[0m"
#define BOLD        "\033[1m"

#define CHOCOLATE   "\033[38;5;255m"
#define MOCHA       "\033[38;5;88m"
#define CARAMEL     "\033[38;5;95m"
#define GOLD        "\033[38;5;220m"
#define CREAM       "\033[38;5;230m"
#define SAGE        "\033[38;5;108m"
#define ROSE        "\033[38;5;174m"
#define WHITE       "\033[38;5;255m"
#define MUTED       "\033[38;5;245m"

// ==========================================
// PRODUCT STRUCTURE
// ==========================================

struct Product {
    int id;
    string name, brand;
    double price;
    int stock;
};

// ==========================================
// INITIAL PRODUCTS
// ==========================================

Product products[50] = {

    // BAGS
    {101, "Backpack", "Herschel", 1500, 15},
    {102, "School Bag", "Jansport", 1200, 20},
    {103, "Mini Handbag", "Guess", 2500, 10},
    {104, "Shoulder Bag", "Charles & Keith", 2800, 8},
    {105, "Tote Bag", "Longchamp", 2200, 12},

    // BAG ACCESSORIES
    {106, "Bag Charm", "Kawaii", 250, 25},
    {107, "Bag Organizer", "Daiso", 180, 30},
    {108, "Bag Strap", "Fashion", 350, 18},
    {109, "Coin Purse", "Guess", 450, 14},
    {110, "Bag Rain Cover", "TravelMate", 200, 20}
};

int productCount = 10;

// ==========================================
// SALES TRACKER
// ==========================================

double totalSales = 0;
int totalTransactions = 0;

// ==========================================
// DESIGN HELPER FUNCTIONS
// ==========================================

void line() {
    cout << CARAMEL
         << "------------------------------------------------------------"
         << RESET << endl;
}

void header(string title) {

    cout << "\n";

    cout << GOLD << BOLD;

    cout << "============================================================\n";

    cout << "                    " << title << "\n";

    cout << "============================================================\n";

    cout << RESET;
}

void success(string message) {

    cout << SAGE << BOLD
         << "\n  [SUCCESS] " << message
         << RESET << endl;
}

void error(string message) {

    cout << ROSE << BOLD
         << "\n  [NOTICE] " << message
         << RESET << endl;
}

// ==========================================
// INPUT VALIDATION
// ==========================================

int getInteger(string message) {

    string input;

    while (true) {

        cout << GOLD << message << RESET;

        getline(cin, input);

        try {

            size_t pos;

            int number = stoi(input, &pos);

            if (pos == input.length()) {
                return number;
            }

        } catch (...) {
        }

        error("Please enter a valid number.");
    }
}

// ==========================================
// PRICE INPUT
// ==========================================

double getPrice() {

    string input;

    while (true) {

        cout << GOLD << "  Price: P" << RESET;

        getline(cin, input);

        string clean = "";

        for (char c : input) {

            if (c != ',') {
                clean += c;
            }
        }

        try {

            size_t pos;

            double price = stod(clean, &pos);

            if (pos == clean.length() &&
                price >= 0 &&
                price <= 1000000000.0) {

                return price;
            }

        } catch (...) {
        }

        error("Invalid price. Please try again.");
    }
}

// ==========================================
// STOCK INPUT
// ==========================================

int getStock() {

    while (true) {

        int stock = getInteger("  Stock: ");

        if (stock >= 0) {
            return stock;
        }

        error("Stock cannot be negative.");
    }
}

// ==========================================
// FIND PRODUCT
// ==========================================

int findProduct(int id) {

    for (int i = 0; i < productCount; i++) {

        if (products[i].id == id) {
            return i;
        }
    }

    return -1;
}

// ==========================================
// CASE-INSENSITIVE SEARCH
// ==========================================

string toLowerCase(string text) {

    transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        }
    );

    return text;
}

// ==========================================
// 1. DISPLAY PRODUCTS
// ==========================================

void display() {

    header("PRODUCT COLLECTION");

    if (productCount == 0) {

        error("No products available.");

        return;
    }

    cout << GOLD << BOLD
         << left
         << setw(8) << "ID"
         << setw(20) << "PRODUCT"
         << setw(20) << "BRAND"
         << setw(12) << "PRICE"
         << "STOCK\n"
         << RESET;

    line();

    for (int i = 0; i < productCount; i++) {

        cout << CHOCOLATE
             << left
             << setw(8) << products[i].id
             << setw(20) << products[i].name
             << setw(20) << products[i].brand
             << RESET;

        cout << GOLD << "P"
             << fixed << setprecision(2)
             << setw(11) << products[i].price
             << RESET;

        if (products[i].stock <= 5) {
            cout << ROSE;
        }
        else {
            cout << SAGE;
        }

        cout << products[i].stock << RESET << endl;
    }

    line();
}

// ==========================================
// 2. SMART PRODUCT SEARCH
// ==========================================

void search() {

    header("SMART PRODUCT SEARCH");

    string keyword;

    cout << GOLD
         << "  Enter Product ID, Name, or Brand: "
         << RESET;

    getline(cin, keyword);

    if (keyword.empty()) {

        error("Search field cannot be empty.");

        return;
    }

    string searchText = toLowerCase(keyword);

    bool found = false;

    for (int i = 0; i < productCount; i++) {

        string name = toLowerCase(products[i].name);

        string brand = toLowerCase(products[i].brand);

        if (to_string(products[i].id) == keyword ||
            name.find(searchText) != string::npos ||
            brand.find(searchText) != string::npos) {

            cout << SAGE << BOLD
                 << "\n  PRODUCT FOUND\n"
                 << RESET;

            cout << CHOCOLATE
                 << "  ID: " << products[i].id
                 << "\n  Name: " << products[i].name
                 << "\n  Brand: " << products[i].brand
                 << RESET;

            cout << GOLD
                 << "\n  Price: P"
                 << fixed << setprecision(2)
                 << products[i].price
                 << RESET;

            cout << SAGE
                 << "\n  Stock: " << products[i].stock
                 << RESET << endl;

            found = true;
        }
    }

    if (!found) {
        error("No matching product found.");
    }
}

// ==========================================
// 3. ADD PRODUCT
// ==========================================

void addProduct() {

    header("ADD NEW PRODUCT");

    if (productCount >= 50) {

        error("Inventory is full.");

        return;
    }

    int id = getInteger("  Enter Product ID: ");

    if (id <= 0) {

        error("Product ID must be positive.");

        return;
    }

    if (findProduct(id) != -1) {

        error("Product ID already exists.");

        return;
    }

    string name, brand;

    cout << GOLD << "  Product Name: " << RESET;

    getline(cin, name);

    if (name.empty()) {

        error("Product name cannot be empty.");

        return;
    }

    cout << GOLD << "  Brand: " << RESET;

    getline(cin, brand);

    if (brand.empty()) {

        error("Brand cannot be empty.");

        return;
    }

    double price = getPrice();

    int stock = getStock();

    products[productCount] = {
        id, name, brand, price, stock
    };

    productCount++;

    success("Product added successfully!");
}

// ==========================================
// 4. UPDATE PRODUCT
// ==========================================

void updateProduct() {

    header("UPDATE PRODUCT");

    int id = getInteger("  Enter Product ID: ");

    int index = findProduct(id);

    if (index == -1) {

        error("Product not found.");

        return;
    }

    cout << CHOCOLATE
         << "\n  [1] Update Product Name"
         << "\n  [2] Update Brand"
         << "\n  [3] Update Price"
         << "\n  [4] Update Stock"
         << "\n  [5] Update All"
         << "\n  [0] Cancel"
         << RESET << endl;

    int choice = getInteger("  Select option: ");

    switch (choice) {

        case 1: {

            cout << GOLD << "  New Name: " << RESET;

            string name;
            getline(cin, name);

            if (name.empty()) {
                error("Name cannot be empty.");
                return;
            }

            products[index].name = name;
            break;
        }

        case 2: {

            cout << GOLD << "  New Brand: " << RESET;

            string brand;
            getline(cin, brand);

            if (brand.empty()) {
                error("Brand cannot be empty.");
                return;
            }

            products[index].brand = brand;
            break;
        }

        case 3:

            products[index].price = getPrice();
            break;

        case 4:

            products[index].stock = getStock();
            break;

        case 5: {

            string name, brand;

            cout << GOLD << "  New Name: " << RESET;
            getline(cin, name);

            if (name.empty()) {
                error("Name cannot be empty.");
                return;
            }

            cout << GOLD << "  New Brand: " << RESET;
            getline(cin, brand);

            if (brand.empty()) {
                error("Brand cannot be empty.");
                return;
            }

            products[index].name = name;
            products[index].brand = brand;
            products[index].price = getPrice();
            products[index].stock = getStock();

            break;
        }

        case 0:

            cout << MOCHA
                 << "  Update cancelled.\n"
                 << RESET;

            return;

        default:

            error("Invalid choice.");

            return;
    }

    success("Product updated successfully!");
}

// ==========================================
// 5. DELETE PRODUCT
// ==========================================

void deleteProduct() {

    header("REMOVE PRODUCT");

    int id = getInteger("  Enter Product ID: ");

    int index = findProduct(id);

    if (index == -1) {

        error("Product not found.");

        return;
    }

    cout << CHOCOLATE
         << "\n  Product: "
         << products[index].name
         << RESET << endl;

    int confirm = getInteger("  Delete? [1] Yes [2] No: ");

    if (confirm != 1) {

        cout << MOCHA
             << "  Deletion cancelled.\n"
             << RESET;

        return;
    }

    for (int i = index; i < productCount - 1; i++) {

        products[i] = products[i + 1];
    }

    productCount--;

    success("Product deleted successfully!");
}

// ==========================================
// 6. SELL PRODUCT WITH DISCOUNT
// ==========================================

void sellProduct() {

    header("BOUTIQUE CHECKOUT");

    int id = getInteger("  Enter Product ID: ");

    int index = findProduct(id);

    if (index == -1) {

        error("Product not found.");

        return;
    }

    cout << CHOCOLATE
         << "\n  Product: " << products[index].name
         << "\n  Brand: " << products[index].brand
         << "\n  Available Stock: " << products[index].stock
         << RESET << endl;

    int quantity = getInteger("  Quantity to sell: ");

    if (quantity <= 0) {

        error("Invalid quantity.");

        return;
    }

    if (quantity > products[index].stock) {

        error("Not enough stock available.");

        return;
    }

    double subtotal = products[index].price * quantity;

    cout << GOLD << BOLD
         << "\n  CHECKOUT DISCOUNTS\n"
         << RESET;

    cout << CHOCOLATE
         << "  [1] No Discount"
         << "\n  [2] 5% Discount"
         << "\n  [3] 10% Discount"
         << "\n  [4] 15% Discount"
         << RESET << endl;

    double discountRate = 0;
    string input;
    bool validDiscount = false;

    while (!validDiscount) {

        cout << GOLD << "  Select Discount: " << RESET;

        getline(cin, input);

        // Remove spaces
        input.erase(
            remove_if(input.begin(), input.end(),
                [](unsigned char c) {
                    return isspace(c);
                }),
            input.end()
        );

        bool hasPercent = false;

        if (!input.empty() && input.back() == '%') {

            hasPercent = true;
            input.pop_back();
        }

        try {

            size_t pos;

            int value = stoi(input, &pos);

            if (pos != input.length()) {
                throw invalid_argument("Invalid input");
            }

            if (hasPercent) {

                if (value == 0 || value == 5 ||
                    value == 10 || value == 15) {

                    discountRate = value / 100.0;
                    validDiscount = true;
                }

            } else {

                switch (value) {

                    case 0:
                    case 1:
                        discountRate = 0.00;
                        validDiscount = true;
                        break;

                    case 2:
                    case 5:
                        discountRate = 0.05;
                        validDiscount = true;
                        break;

                    case 3:
                    case 10:
                        discountRate = 0.10;
                        validDiscount = true;
                        break;

                    case 4:
                    case 15:
                        discountRate = 0.15;
                        validDiscount = true;
                        break;
                }
            }

        } catch (...) {

            validDiscount = false;
        }

        if (!validDiscount) {

            error("Invalid discount! Enter 1-4 or 0%, 5%, 10%, 15%.");
        }
    }

    // Calculate discount
    double discount = subtotal * discountRate;

    double total = subtotal - discount;

    // Update inventory
    products[index].stock -= quantity;

    totalSales += total;

    totalTransactions++;

    // SALES RECEIPT

    cout << MOCHA << BOLD << "\n";

    cout << "================================================\n";
    cout << "                 SALES RECEIPT\n";
    cout << "================================================\n" << RESET;

    cout << CHOCOLATE
         << "  Product: " << products[index].name
         << "\n  Brand: " << products[index].brand
         << "\n  Quantity: " << quantity
         << "\n  Unit Price: P" << fixed << setprecision(2)
         << products[index].price
         << "\n  Subtotal: P" << subtotal
         << RESET;

    cout << ROSE
         << "\n  Discount Rate: "
         << fixed << setprecision(0)
         << discountRate * 100 << "%"
         << "\n  Discount Amount: P"
         << fixed << setprecision(2)
         << discount
         << RESET;

    cout << GOLD << BOLD
         << "\n  TOTAL AMOUNT: P" << total
         << RESET;

    cout << SAGE
         << "\n  Remaining Stock: " << products[index].stock
         << RESET << endl;

    cout << MOCHA
         << "================================================\n"
         << RESET;

    success("Thank you! Transaction completed.");
}

// ==========================================
// 7. RESTOCK PRODUCT
// ==========================================

void restockProduct() {

    header("RESTOCK INVENTORY");

    int id = getInteger("  Enter Product ID: ");

    int index = findProduct(id);

    if (index == -1) {

        error("Product not found.");

        return;
    }

    cout << CHOCOLATE
         << "\n  Product: " << products[index].name
         << "\n  Current Stock: " << products[index].stock
         << RESET << endl;

    int quantity = getInteger("  Additional Stock: ");

    if (quantity <= 0) {

        error("Invalid quantity.");

        return;
    }

    products[index].stock += quantity;

    cout << SAGE
         << "\n  New Stock: " << products[index].stock
         << RESET << endl;

    success("Inventory restocked successfully!");
}

// ==========================================
// 8. SORT PRODUCTS BY PRICE
// BUBBLE SORT
// ==========================================

void sortProducts() {

    header("PRICE ARRANGEMENT");

    if (productCount == 0) {

        error("No products available.");

        return;
    }

    for (int i = 0; i < productCount - 1; i++) {

        for (int j = 0; j < productCount - i - 1; j++) {

            if (products[j].price > products[j + 1].price) {

                Product temp = products[j];

                products[j] = products[j + 1];

                products[j + 1] = temp;
            }
        }
    }

    success("Products arranged from lowest to highest price.");

    display();
}

// ==========================================
// 9. LOW STOCK ALERT
// ==========================================

void lowStock() {

    header("LOW STOCK NOTIFICATIONS");

    bool found = false;

    for (int i = 0; i < productCount; i++) {

        if (products[i].stock <= 5) {

            cout << ROSE << BOLD
                 << "\n  LOW STOCK ALERT"
                 << "\n  Product ID: " << products[i].id
                 << "\n  Product: " << products[i].name
                 << "\n  Brand: " << products[i].brand
                 << "\n  Remaining Stock: " << products[i].stock
                 << RESET << endl;

            found = true;
        }
    }

    if (!found) {

        cout << SAGE
             << "\n  All products have sufficient stock!\n"
             << RESET;
    }
}

// ==========================================
// 10. INVENTORY SUMMARY
// ==========================================

void inventorySummary() {

    header("INVENTORY OVERVIEW");

    int totalStock = 0;

    double totalValue = 0;

    for (int i = 0; i < productCount; i++) {

        totalStock += products[i].stock;

        totalValue += products[i].price * products[i].stock;
    }

    cout << CHOCOLATE
         << "\n  Total Product Types: " << productCount
         << "\n  Total Items in Stock: " << totalStock
         << RESET;

    cout << GOLD
         << "\n  Total Inventory Value: P"
         << fixed << setprecision(2)
         << totalValue
         << RESET << endl;

    line();
}

// ==========================================
// 11. SALES PERFORMANCE REPORT
// ==========================================

void salesReport() {

    header("SALES PERFORMANCE REPORT");

    cout << CHOCOLATE
         << "\n  Total Transactions: "
         << totalTransactions
         << RESET;

    cout << GOLD
         << "\n  Total Sales Revenue: P"
         << fixed << setprecision(2)
         << totalSales
         << RESET << endl;

    line();

    if (totalTransactions == 0) {

        cout << MUTED
             << "\n  No sales transactions recorded yet."
             << RESET << endl;

    } else {

        double averageSale = totalSales / totalTransactions;

        cout << SAGE
             << "\n  Average Sale per Transaction: P"
             << fixed << setprecision(2)
             << averageSale
             << RESET << endl;
    }

    line();
}

// ==========================================
// 12. BOUTIQUE DASHBOARD
// ==========================================

void dashboard() {

    header("AMOUR BOUTIQUE DASHBOARD");

    int totalStock = 0;

    int lowStockCount = 0;

    double inventoryValue = 0;

    for (int i = 0; i < productCount; i++) {

        totalStock += products[i].stock;

        inventoryValue += products[i].price * products[i].stock;

        if (products[i].stock <= 5) {
            lowStockCount++;
        }
    }

    cout << GOLD << BOLD
         << "\n             AMOUR BAGS & ACCESSORIES"
         << RESET << endl;

    line();

    cout << CHOCOLATE
         << "\n  PRODUCT CATEGORIES"
         << "\n  ------------------"
         << "\n  Total Product Types: " << productCount
         << "\n  Total Items in Stock: " << totalStock
         << RESET << endl;

    cout << GOLD
         << "\n  INVENTORY VALUE"
         << "\n  ---------------"
         << "\n  Total Value: P"
         << fixed << setprecision(2)
         << inventoryValue
         << RESET << endl;

    cout << ROSE
         << "\n  STOCK ALERTS"
         << "\n  ------------"
         << "\n  Products with Low Stock: " << lowStockCount
         << RESET << endl;

    cout << SAGE
         << "\n  SALES PERFORMANCE"
         << "\n  ------------------"
         << "\n  Total Transactions: " << totalTransactions
         << "\n  Total Revenue: P"
         << fixed << setprecision(2)
         << totalSales
         << RESET << endl;

    line();

    cout << CARAMEL
         << "\n  Thank you for choosing AMOUR!"
         << RESET << endl;
}

// ==========================================
// MAIN MENU - YELLOW/GOLD HEADING
// ==========================================

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
         << RESET << endl;

    line();
}

// ==========================================
// MAIN FUNCTION
// ==========================================

int main() {

#ifdef _WIN32

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD mode = 0;

    if (console != INVALID_HANDLE_VALUE &&
        GetConsoleMode(console, &mode)) {

        SetConsoleMode(
            console,
            mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING
        );
    }

#endif

    cout << "\033[0m\033[2J\033[H";

    int choice;

    do {

        showMenu();

        choice = getInteger("  Enter your choice: ");

        switch (choice) {

            case 1:
                display();
                break;

            case 2:
                search();
                break;

            case 3:
                addProduct();
                break;

            case 4:
                updateProduct();
                break;

            case 5:
                deleteProduct();
                break;

            case 6:
                sellProduct();
                break;

            case 7:
                restockProduct();
                break;

            case 8:
                sortProducts();
                break;

            case 9:
                lowStock();
                break;

            case 10:
                inventorySummary();
                break;

            case 11:
                salesReport();
                break;

            case 12:
                dashboard();
                break;

            case 0:

                cout << GOLD << BOLD
                     << "\n  Thank you for visiting AMOUR BAGS & ACCESSORIES!"
                     << "\n  Have a wonderful day!"
                     << RESET << endl;

                break;

            default:

                error("Invalid menu choice. Please try again.");
        }

        if (choice != 0) {

            cout << MUTED
                 << "\n  Press ENTER to return to the main menu...";

            cin.get();

            cout << RESET;
        }

    } while (choice != 0);

    cout << RESET << endl;

    return 0;
}
