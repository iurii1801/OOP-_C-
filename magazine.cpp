#include <iostream>
#include <string>

using namespace std;

class Product {
protected:
    string productName;
    double price;
    int quantity;

public:
    Product(string productName, double price, int quantity)
        : productName(productName), price(price), quantity(quantity) {}

    double calculateTotalCost(int quantity) {
        return price * quantity;
    }

    void displayProductDetails() {
        cout << "Product Name: " << productName << endl;
        cout << "Price: " << price << endl;
        cout << "Quantity: " << quantity << endl;
    }
};

class Electronics : public Product {
private:
    string brand;
    int warrantyPeriod;
    string manufacturer;

public:
    Electronics(string productName, double price, int quantity, string brand, int warrantyPeriod, string manufacturer)
        :Product(productName, price, quantity), brand(brand), warrantyPeriod(warrantyPeriod), manufacturer(manufacturer) {}

    void extendWarranty(int months) {
        warrantyPeriod += months;
    }

    void updateManufacturer(string newManufacturer) {
        manufacturer = newManufacturer;
    }

    void displayProductDetails() {
        Product::displayProductDetails();
        cout << "Brand: " << brand << endl;
        cout << "Warranty Period: " << warrantyPeriod << " months" << endl;
        cout << "Manufacturer: " << manufacturer << endl;
    }
};

class Clothing : public Product {
private:
    string size;

public:
    Clothing(string productName, double price, int quantity, string size)
        : Product(productName, price, quantity), size(size) {}

    void changeSize(string newSize) {
        size = newSize;
    }

    bool isSizeAvailable(string newSize) {
        return size == newSize && quantity > 0;
    }

    void displayProductDetails() {
        Product::displayProductDetails();
        cout << "Size: " << size << endl;
    }
};

int main() {
    Electronics electronicsProduct("Laptop", 27000, 5, "Asus tuf gaming", 24, "Asus Corporations");
    Clothing clothingProduct("Jeans", 1750, 5, "L");

    electronicsProduct.displayProductDetails();
    cout << "Total cost for 5 laptops: " << electronicsProduct.calculateTotalCost(5) << endl;

    cout << endl;

    clothingProduct.displayProductDetails();
    cout << "Total cost for 4: " << clothingProduct.calculateTotalCost(3) << endl;

    electronicsProduct.extendWarranty(6);
    electronicsProduct.updateManufacturer("Manufacturer corp.");

    cout << "\nUpdated Electronics Product Details:\n";
    electronicsProduct.displayProductDetails();

   
    clothingProduct.changeSize("L");
    cout << "\nChanged Clothing Size: " << clothingProduct.calculateTotalCost(1) << endl;
    cout << "Is Size 'L' Available? " << (clothingProduct.isSizeAvailable("L") ? "Yes" : "No") << endl;

    return 0;
}
