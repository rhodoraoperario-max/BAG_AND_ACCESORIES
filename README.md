# AMOUR Bags & Accessories – Inventory Management System

## Project Overview

AMOUR is a console-based inventory management system developed in C++. It is designed for a boutique that sells bags and bag accessories. The system helps organize product information, monitor available stock, process sample sales, and view basic inventory and sales reports.

The program uses a burgundy and gold console theme to match the AMOUR boutique concept.

## Product Information

Each product record contains:
- Product ID
- Product name
- Brand
- Price
- Available stock

The program starts with sample products from brands such as Herschel, Jansport, Guess, Charles & Keith, Longchamp, Kawaii, Daiso, Fashion, and TravelMate. These are sample catalog entries for the project.

## Main Features

1. **Display Product Collection** – Shows all products, brands, prices, and stock.
2. **Smart Product Search** – Searches using a product ID, product name, or brand.
3. **Add New Product** – Adds a product with a unique ID and its details.
4. **Update Product Details** – Changes a product's name, brand, price, or stock.
5. **Remove Product** – Deletes a selected product from the inventory.
6. **Sales & Checkout** – Processes a sample sale, applies an optional discount, calculates the total, and updates stock.
7. **Restock Inventory** – Adds new stock to an existing product.
8. **Sort Products by Price** – Uses Bubble Sort to arrange products from lowest to highest price.
9. **Low Stock Notifications** – Displays products with five or fewer units remaining.
10. **Inventory Overview** – Shows the number of product types, total units, and estimated inventory value.
11. **Sales Performance Report** – Displays completed transactions, items sold, total sales, and average sale.
12. **Boutique Dashboard** – Presents a quick summary of inventory and sales information.

## Checkout Discounts

The checkout accepts either the menu option or the percentage value:

| Menu Option | Discount |
|---|---:|
| 1 | 0% |
| 2 | 5% |
| 3 | 10% |
| 4 | 15% |

You may also enter `0%`, `5%`, `10%`, or `15%` directly.

## Requirements

- Windows, Linux, or macOS
- A C++ compiler that supports C++11 or later
- Visual Studio Code, Code::Blocks, or another C++ IDE
- GCC / G++ compiler (recommended)

## How to Compile and Run

### Windows PowerShell / VS Code Terminal

Open the project folder in the terminal and run:

```powershell
g++ -std=c++11 main.cpp -o amour.exe
.\amour.exe
```

### Linux / macOS

```bash
g++ -std=c++11 main.cpp -o amour
./amour
```

## Scope and Delimitation

### Scope
- Manages sample bag and accessory product records.
- Supports adding, viewing, searching, updating, and removing products.
- Processes sample checkout transactions and discount calculations.
- Updates product stock after sales and restocking.
- Provides sorting, low-stock alerts, inventory summaries, and sales reports.

### Delimitations
- This is a console-based academic project.
- Product records and sales totals are stored in memory while the program is running.
- Changes are reset when the program is closed; there is no database or file-based storage.
- The checkout is a demonstration only. It does not process real payments, online orders, delivery, or customer accounts.
- The listed brands, products, prices, and stock quantities are sample data and do not indicate official brand partnerships.

## Project Structure

```text
AMOUR-Bags-and-Accessories/
├── main.cpp
└── README.md
```

## Developer

**Rhodora S. Operario**

BS Computer Engineering  
Eastern Samar State University – Main Campus

---

*AMOUR Bags & Accessories is an academic project created to demonstrate basic C++ programming, product inventory operations, searching, sorting, input validation, and simple sales reporting.*
