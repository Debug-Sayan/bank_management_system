#include <iostream>
#include <vector>
#include <string>
#include <iomanip>  // For output formatting
using namespace std;

// Class to represent a product
class Product {
private:
    int id;
    string name;
    double price;
    int stock;

public:
    // Constructor to initialize a product
    Product(int p_id, string p_name, double p_price, int p_stock) 
        : id(p_id), name(p_name), price(p_price), stock(p_stock) {}

    // Function to display product details
    void displayProduct() const {
        cout << setw(5) << id << setw(20) << name << setw(10) << fixed << setprecision(2) << price << setw(10) << stock << endl;
    }

    // Function to check if the product is in stock
    bool isInStock(int quantity) const {
        return stock >= quantity;
    }

    // Function to reduce stock when purchased
    void reduceStock(int quantity) {
        stock -= quantity;
    }

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
};

// Class to manage the shopping cart
class Cart {
private:
    vector<pair<Product, int>> cartItems;  // Pair of product and quantity

public:
    // Function to add a product to the cart
    void addProduct(const Product& product, int quantity) {
        cartItems.push_back(make_pair(product, quantity));
    }

    // Function to display cart items
    void displayCart() const {
        cout << "\n\nCart Summary:\n";
        cout << setw(5) << "ID" << setw(20) << "Product Name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(15) << "Total" << endl;
        double totalCost = 0.0;
        for (const auto& item : cartItems) {
            double itemTotal = item.first.getPrice() * item.second;
            totalCost += itemTotal;
            cout << setw(5) << item.first.getId() << setw(20) << item.first.getName() << setw(10) << fixed << setprecision(2) << item.first.getPrice() 
                 << setw(10) << item.second << setw(15) << fixed << setprecision(2) << itemTotal << endl;
        }
        cout << "\nTotal Cost: " << totalCost << "\n";
    }

    // Function to checkout and clear the cart
    void checkout() {
        if (cartItems.empty()) {
            cout << "Cart is empty!\n";
        } else {
            cout << "Checking out...\n";
            displayCart();
            cartItems.clear();
            cout << "Thank you for your purchase!\n\n";
        }
    }

    // Check if the cart is empty
    bool isEmpty() const {
        return cartItems.empty();
    }
};

// Class to manage the E-commerce platform
class ECommercePlatform {
private:
    vector<Product> products;  // List of products in the system
    Cart userCart;             // Cart for the current user
    int nextProductId;         // Unique ID for new products

public:
    // Constructor to initialize the platform
    ECommercePlatform() : nextProductId(1) {}

    // Function to add new products (Admin access only)
    void addProduct(string name, double price, int stock) {
        Product newProduct(nextProductId++, name, price, stock);
        products.push_back(newProduct);
        cout << "Product Added Successfully!\n\n";
    }

    // Function to display available products
    void displayProducts() const {
        cout << setw(5) << "ID" << setw(20) << "Product Name" << setw(10) << "Price" << setw(10) << "Stock" << endl;
        for (const auto& product : products) {
            product.displayProduct();
        }
    }

    // Function for customer to add product to the cart
    void addToCart(int productId, int quantity) {
        bool found = false;
        for (auto& product : products) {
            if (product.getId() == productId) {
                if (product.isInStock(quantity)) {
                    userCart.addProduct(product, quantity);
                    product.reduceStock(quantity);
                    cout << "Added " << quantity << " of " << product.getName() << " to the cart.\n\n";
                } else {
                    cout << "Insufficient stock for product: " << product.getName() << "\n";
                }
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Product not found!\n\n";
        }
    }

    // Function to manage checkout
    void checkout() {
        if (userCart.isEmpty()) {
            cout << "Your cart is empty!\n";
        } else {
            userCart.checkout();
        }
    }
};

// Main function to handle the application flow
int main() {
    ECommercePlatform platform;
    int choice;
    int productId, quantity;

    // Pre-populated products (could be added via admin panel)
    platform.addProduct("Laptop", 50000.00, 10);
    platform.addProduct("Smartphone", 20000.00, 25);
    platform.addProduct("Headphones", 1500.00, 50);

    do {
        cout << "\n\n*** Welcome to the E-Commerce Platform ***\n";
        cout << "1. View Products\n";
        cout << "2. Add Product to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Checkout\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            // View available products
            platform.displayProducts();
            break;
        case 2:
            // Add product to cart
            cout << "Enter Product ID: ";
            cin >> productId;
            cout << "Enter Quantity: ";
            cin >> quantity;
            platform.addToCart(productId, quantity);
            break;
        case 3:
            // View cart
            platform.checkout();  // Display cart summary
            break;
        case 4:
            // Checkout
            platform.checkout();
            break;
        case 5:
            // Exit
            cout << "Exiting the platform. Thank you!\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
