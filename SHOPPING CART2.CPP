
#include <iostream>
#include <vector>
#include <algorithm>

class Product {
private:
    std::string name;
    double price;
    int quantity;

public:
    Product(const std::string& name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
};

class ShoppingCart {
private:
    std::vector<Product> items;

public:
    void addProduct(const Product& product) {
        items.push_back(product);
        std::cout << product.getName() << " added to the cart.\n";
    }

    void removeProduct(const std::string& productName) {
        auto it = std::find_if(items.begin(), items.end(), [&](const Product& product) {
            return product.getName() == productName;
        });

        if (it != items.end()) {
            items.erase(it);
            std::cout << productName << " removed from the cart.\n";
        } else {
            std::cout << "Product not found in the cart.\n";
        }
    }

    void displayItems() const {
        std::cout << "Items in the cart:\n";
        for (const auto& product : items) {
            std::cout << "- " << product.getName() << ", Quantity: " << product.getQuantity() << "\n";
        }
    }

    double calculateTotalCost() const {
        double totalCost = 0.0;
        for (const auto& product : items) {
            totalCost += product.getPrice() * product.getQuantity();
        }
        return totalCost;
    }

    double calculateTotalCostWithDiscount(double discountPercent) const {
        double totalCost = calculateTotalCost();
        double discountAmount = (discountPercent / 100.0) * totalCost;
        return totalCost - discountAmount;
    }

    double calculateTax(double taxPercent) const {
        double totalCost = calculateTotalCostWithDiscount(0.0);
        return (taxPercent / 100.0) * totalCost;
    }

    double calculateTotalCostWithTax(double taxPercent) const {
        double totalCost = calculateTotalCostWithDiscount(0.0);
        double taxAmount = calculateTax(taxPercent);
        return totalCost + taxAmount;
    }
};

int main() {
    ShoppingCart cart;

    // Adding products
    Product p1("Product 1", 10.0, 5);
    Product p2("Product 2", 20.0, 3);
    Product p3("Product 3", 15.0, 7);

    cart.addProduct(p1);
    cart.addProduct(p2);
    cart.addProduct(p3);

    // Displaying items
    cart.displayItems();

    // Removing a product
    cart.removeProduct("Product 2");

    // Updating product quantity
    Product p4("Product 4", 12.0, 2);
    cart.addProduct(p4);
    cart.displayItems();

    // Calculating total cost
    double totalCost = cart.calculateTotalCost();
    std::cout << "Total cost of items in the cart: " << totalCost << "\n";

    // Calculating total cost with discount
    double totalCostWithDiscount = cart.calculateTotalCostWithDiscount(10.0);
    std::cout << "Total cost with 10% discount: " << totalCostWithDiscount << "\n";

    // Calculating tax and total cost with tax
    double taxPercent = 7.5;
    double totalCostWithTax = cart.calculateTotalCostWithTax(taxPercent);
    double taxAmount = cart.calculateTax(taxPercent);
    std::cout << "Tax Amount (" << taxPercent << "%): " << taxAmount << "\n";
    std::cout << "Total cost with tax: " << totalCostWithTax << "\n";

    return 0;
}
