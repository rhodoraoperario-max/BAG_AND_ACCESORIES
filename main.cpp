#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

// ==========================================
// BAG & ACCESSORIES SHOP
// INVENTORY MANAGEMENT SYSTEM
// ==========================================

struct Product {
    int id;
    string name, brand;
    double price;
    int stock;
};

Product products[50] = {
    // 5 BAGS
    {101, "Backpack", "Herschel", 1500, 15},
    {102, "School Bag", "Jansport", 1200, 20},
    {103, "Mini Handbag", "Guess", 2500, 10},
    {104, "Shoulder Bag", "Charles & Keith", 2800, 8},
    {105, "Tote Bag", "Longchamp", 2200, 12},

    // 5 BAG ACCESSORIES
    {106, "Bag Charm", "Kawaii", 250, 25},
    {107, "Bag Organizer", "Daiso", 180, 30},
    {108, "Bag Strap", "Fashion", 350, 18},
    {109, "Coin Purse", "Guess", 450, 14},
    {110, "Bag Rain Cover", "TravelMate", 200, 20}
};

int productCount = 10;

// ==========================================
// INPUT VALIDATION
// ==========================================

int getInteger(string message) {
    string input;

    while (true) {
        cout << message;
        getline(cin, input);

        try {
            size_t pos;
            int number = stoi(input, &pos);

            if (pos == input.length())
                return number;

        } catch (...) {}

        cout << "Invalid number! Try again.\n";
    }
}

// PRICE INPUT
double getPrice() {
    string input;

    while (true) {
        cout << "Price: ";
        getline(cin, input);

        string clean = "";

        for (char c : input) {
            if (c != ',')
                clean += c;
        }

        try {
            size_t pos;
            double price = stod(clean, &pos);

            if (pos == clean.length() &&
                price >= 0 && price <= 1000000000.0)
                return price;

        } catch (...) {}

        cout << "Invalid price! Try again.\n";
    }
}

// STOCK INPUT
int getStock() {
    while (true) {
        int stock = getInteger("Stock: ");

        if (stock >= 0)
            return stock;

        cout << "Stock cannot be negative!\n";
    }
}

// ==========================================
// SEARCH PRODUCT INDEX
// ==========================================

int findProduct(int id) {

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id)
            return i;
    }

    return -1;
}

// ==========================================
// 1. DISPLAY PRODUCTS
// ==========================================

void display() {

    cout << "\n============================================\n";
    cout << "              PRODUCT LIST\n";
    cout << "============================================\n";

    if (productCount == 0) {
        cout << "No products available!\n";
        return;
    }

    cout << left
         << setw(8) << "ID"
         << setw(20) << "PRODUCT"
         << setw(20) << "BRAND"
         << setw(12) << "PRICE"
         << "STOCK\n";

    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < productCount; i++) {

        cout << left
             << setw(8) << products[i].id
             << setw(20) << products[i].name
             << setw(20) << products[i].brand
             << "P" << fixed << setprecision(2)
             << setw(11) << products[i].price
             << products[i].stock << endl;
    }

    cout << "============================================\n";
}

// ==========================================
// 2. SEARCH PRODUCT
// ==========================================

void search() {

    int id = getInteger("\nEnter Product ID: ");

    int index = findProduct(id);

    if (index == -1) {
        cout << "\nProduct not found!\n";
        return;
    }

    cout << "\n========== PRODUCT FOUND ==========\n";

    cout << "ID: " << products[index].id
         << "\nName: " << products[index].name
         << "\nBrand: " << products[index].brand
         << "\nPrice: P" << fixed << setprecision(2)
         << products[index].price
         << "\nStock: " << products[index].stock << endl;
}

// ==========================================
// 3. ADD PRODUCT
// ==========================================

void addProduct() {

    if (productCount >= 50) {
        cout << "Inventory is full!\n";
        return;
    }

    int id = getInteger("\nEnter Product ID: ");

    if (findProduct(id) != -1) {
        cout << "Product ID already exists!\n";
        return;
    }

    products[productCount].id = id;

    cout << "Product Name: ";
    getline(cin, products[productCount].name);

    if (products[productCount].name.empty()) {
        cout << "Product name cannot be empty!\n";
        return;
    }

    cout << "Brand: ";
    getline(cin, products[productCount].brand);

    if (products[productCount].brand.empty()) {
        cout << "Brand cannot be empty!\n";
        return;
    }

    products[productCount].price = getPrice();
    products[productCount].stock = getStock();

    productCount++;

    cout << "\nProduct added successfully!\n";
}

// ==========================================
// 4. UPDATE PRODUCT
// ==========================================

void updateProduct() {

    int id = getInteger("\nEnter Product ID to update: ");

    int index = findProduct(id);

    if (index == -1) {
        cout << "Product not found!\n";
        return;
    }

    cout << "\n[1] Update Product Name\n";
    cout << "[2] Update Brand\n";
    cout << "[3] Update Price\n";
    cout << "[4] Update Stock\n";
    cout << "[5] Update All\n";
    cout << "[0] Cancel\n";

    int choice = getInteger("Choose: ");

    switch (choice) {

        case 1:
            cout << "New Name: ";
            getline(cin, products[index].name);
            break;

        case 2:
            cout << "New Brand: ";
            getline(cin, products[index].brand);
            break;

        case 3:
            products[index].price = getPrice();
            break;

        case 4:
            products[index].stock = getStock();
            break;

        case 5:
            cout << "New Name: ";
            getline(cin, products[index].name);

            cout << "New Brand: ";
            getline(cin, products[index].brand);

            products[index].price = getPrice();
            products[index].stock = getStock();
            break;

        case 0:
            cout << "Update cancelled!\n";
            return;

        default:
            cout << "Invalid choice!\n";
            return;
    }

    cout << "\nProduct updated successfully!\n";
}

// ==========================================
// 5. DELETE PRODUCT
// ==========================================

void deleteProduct() {

    int id = getInteger("\nEnter Product ID to delete: ");

    int index = findProduct(id);

    if (index == -1) {
        cout << "Product not found!\n";
        return;
    }

    cout << "\nProduct: " << products[index].name << endl;

    int confirm = getInteger(
        "Delete this product? [1] Yes [2] No: ");

    if (confirm != 1) {
        cout << "Delete cancelled!\n";
        return;
    }

    for (int i = index; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }

    productCount--;

    cout << "Product deleted successfully!\n";
}

// ==========================================
// 6. SELL PRODUCT
// ==========================================

void sellProduct() {

    int id = getInteger("\nEnter Product ID to sell: ");

    int index = findProduct(id);

    if (index == -1) {
        cout << "Product not found!\n";
        return;
    }

    cout << "Product: " << products[index].name << endl;
    cout << "Available Stock: " << products[index].stock << endl;

    int quantity = getInteger("Quantity to sell: ");

    if (quantity <= 0) {
        cout << "Invalid quantity!\n";
        return;
    }

    if (quantity > products[index].stock) {
        cout << "Not enough stock available!\n";
        return;
    }

    double total = products[index].price * quantity;

    products[index].stock -= quantity;

    cout << "\n========== SALES RECEIPT ==========\n";
    cout << "Product: " << products[index].name << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Price: P" << products[index].price << endl;
    cout << "Total Amount: P" << total << endl;
    cout << "Remaining Stock: "
         << products[index].stock << endl;
    cout << "===================================\n";

    cout << "Product sold successfully!\n";
}

// ==========================================
// 7. RESTOCK PRODUCT
// ==========================================

void restockProduct() {

    int id = getInteger("\nEnter Product ID to restock: ");

    int index = findProduct(id);

    if (index == -1) {
        cout << "Product not found!\n";
        return;
    }

    cout << "Product: " << products[index].name << endl;
    cout << "Current Stock: " << products[index].stock << endl;

    int quantity = getInteger("Enter additional stock: ");

    if (quantity <= 0) {
        cout << "Invalid quantity!\n";
        return;
    }

    products[index].stock += quantity;

    cout << "\nStock updated successfully!\n";
    cout << "New Stock: " << products[index].stock << endl;
}

// ==========================================
// 8. SORT PRODUCTS BY PRICE
// ==========================================

void sortProducts() {

    if (productCount == 0) {
        cout << "No products to sort!\n";
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

    cout << "\nProducts sorted by lowest price!\n";

    display();
}

// ==========================================
// 9. LOW STOCK PRODUCTS
// ==========================================

void lowStock() {

    cout << "\n========== LOW STOCK PRODUCTS ==========\n";

    bool found = false;

    for (int i = 0; i < productCount; i++) {

        if (products[i].stock <= 5) {

            cout << "\nID: " << products[i].id
                 << "\nName: " << products[i].name
                 << "\nBrand: " << products[i].brand
                 << "\nRemaining Stock: "
                 << products[i].stock << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "No low stock products!\n";
    }
}

// ==========================================
// 10. INVENTORY SUMMARY
// ==========================================

void inventorySummary() {

    int totalStock = 0;
    double totalValue = 0;

    for (int i = 0; i < productCount; i++) {

        totalStock += products[i].stock;

        totalValue += products[i].price * products[i].stock;
    }

    cout << "\n===================================\n";
    cout << "        INVENTORY SUMMARY\n";
    cout << "===================================\n";

    cout << "Total Product Types: " << productCount << endl;

    cout << "Total Items in Stock: " << totalStock << endl;

    cout << "Total Inventory Value: P"
         << fixed << setprecision(2)
         << totalValue << endl;

    cout << "===================================\n";
}

// ==========================================
// MAIN PROGRAM
// ==========================================

int main() {

    int choice;

    do {

        cout << "\n========================================\n";
        cout << "          BAG & ACCESSORIES SHOP\n";
        cout << "        INVENTORY MANAGEMENT SYSTEM\n";
        cout << "========================================\n";

        cout << "[1] Display Products\n";
        cout << "[2] Search Product\n";
        cout << "[3] Add Product\n";
        cout << "[4] Update Product\n";
        cout << "[5] Delete Product\n";
        cout << "[6] Sell Product\n";
        cout << "[7] Restock Product\n";
        cout << "[8] Sort Products by Price\n";
        cout << "[9] Display Low Stock Products\n";
        cout << "[10] Inventory Summary\n";
        cout << "[0] Exit\n";

        cout << "========================================\n";

        choice = getInteger("Choose an option: ");

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

            case 0:
                cout << "\nThank you for using Bag & Accessories Shop!\n";
                cout << "Have a great day!\n";
                break;

            default:
                cout << "\nInvalid choice! Select from 0-10.\n";
        }

    } while (choice != 0);

    return 0;
}