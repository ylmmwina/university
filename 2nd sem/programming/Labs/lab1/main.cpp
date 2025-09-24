#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

struct Product {
    string name;
    double price;
    int quantity;
};

struct Node {
    Product data;
    Node* next;
    Node* prev;
};

struct CircularDoublyLinkedList {
    Node* head;

    CircularDoublyLinkedList() : head(nullptr) {}

    void addProduct(const Product& product);
    void deleteProduct(int index);
    Node* searchProduct(const string& name) const;
    Node* searchProductByIndex(int index) const;
    void displayProducts() const;
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
    int getSize() const;
};

int CircularDoublyLinkedList::getSize() const {
    if (!head) return 0;
    int size = 0;
    Node* current = head;
    do {
        size++;
        current = current->next;
    } while (current != head);
    return size;
}

void CircularDoublyLinkedList::addProduct(const Product& product) {
    Node* newNode = new Node{product, nullptr, nullptr};
    if (!head) {
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        Node* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
}

void CircularDoublyLinkedList::deleteProduct(int index) {
    if (!head) return;
    int size = getSize();
    if (index < 0 || index >= size) return;

    Node* current;
    if (index < size / 2) {
        current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        current = head->prev;
        for (int i = size - 1; i > index; --i) {
            current = current->prev;
        }
    }

    if (current->next == current) {
        head = nullptr;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        if (current == head) head = current->next;
    }
    delete current;
}

Node* CircularDoublyLinkedList::searchProduct(const string& name) const {
    if (!head) return nullptr;
    Node* current = head;
    do {
        if (current->data.name == name) return current;
        current = current->next;
    } while (current != head);
    return nullptr;
}

Node* CircularDoublyLinkedList::searchProductByIndex(int index) const {
    if (!head) return nullptr;
    int size = getSize();
    if (index < 0 || index >= size) return nullptr;

    Node* current;
    if (index < size / 2) {
        current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        current = head->prev;
        for (int i = size - 1; i > index; --i) {
            current = current->prev;
        }
    }
    return current;
}

void CircularDoublyLinkedList::displayProducts() const {
    if (!head) return;
    Node* current = head;
    int index = 0;
    do {
        cout << "Index: " << index << " | Product: " << current->data.name << ", Price: " << current->data.price << ", Quantity: " << current->data.quantity << "\n";
        current = current->next;
        ++index;
    } while (current != head);
}

void CircularDoublyLinkedList::saveToFile(const string& filename) const {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for writing: " << filename << "\n";
        return;
    }

    if (!head) {
        cerr << "No products to save.\n";
        return;
    }

    Node* current = head;
    do {
        size_t nameLength = current->data.name.size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(current->data.name.c_str(), nameLength);
        file.write(reinterpret_cast<const char*>(&current->data.price), sizeof(current->data.price));
        file.write(reinterpret_cast<const char*>(&current->data.quantity), sizeof(current->data.quantity));

        current = current->next;
    } while (current != head);

    cout << "Products saved successfully to " << filename << "\n";
    file.close();
}

void CircularDoublyLinkedList::loadFromFile(const string& filename) {
    if (!fs::exists(filename)) {
        cerr << "Error: File does not exist: " << filename << "\n";
        return;
    }

    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file: " << filename << "\n";
        return;
    }

    // Очищуємо список перед завантаженням
    if (head) {
        Node* current = head;
        Node* next;
        do {
            next = current->next;
            delete current;
            current = next;
        } while (current != head);
        head = nullptr;
    }

    cout << "Loading file: " << filename << "\n";

    int count = 0;
    while (!file.eof()) {
        size_t nameLength;
        if (!file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) break;

        string name(nameLength, '\0');
        file.read(&name[0], nameLength);

        double price;
        int quantity;
        file.read(reinterpret_cast<char*>(&price), sizeof(price));
        file.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));

        if (!file) break;  // Перевірка, чи все прочиталося

        addProduct({name, price, quantity});
        ++count;
    }

    if (count == 0) {
        cerr << "No products loaded. File might be empty or corrupted.\n";
    } else {
        cout << "File loaded successfully: " << filename << " with " << count << " products.\n";
    }

    file.close();
}


void compareProductPrices(const map<string, CircularDoublyLinkedList>& stores) {
    string productName;
    cout << "Enter product name to compare: ";
    cin >> productName;

    for (const auto& store : stores) {
        Node* found = store.second.searchProduct(productName);
        if (found) {
            cout << "Store: " << store.first << " | Price: " << found->data.price << " | Quantity: " << found->data.quantity << "\n";
        }
    }
}

void menu(map<string, CircularDoublyLinkedList>& stores) {
    int choice;
    string storeName;
    CircularDoublyLinkedList* currentStore = nullptr;

    do {
        cout << "\nMenu:\n";
        cout << "1. Select/Create Store\n";
        cout << "2. Add Product\n";
        cout << "3. Delete Product\n";
        cout << "4. Search Product by Name\n";
        cout << "5. Search Product by Index\n";
        cout << "6. Display Products\n";
        cout << "7. Save Store to File\n";
        cout << "8. Load Store from File\n";
        cout << "9. Compare Product Prices\n";
        cout << "10. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter store name: ";
                cin >> storeName;
                currentStore = &stores[storeName];
                break;
            case 2:
                if (!currentStore) {
                    cout << "Select a store first!\n";
                    break;
                }
            {
                Product newProduct;
                cout << "Enter product name: "; cin >> newProduct.name;
                cout << "Enter price: "; cin >> newProduct.price;
                cout << "Enter quantity: "; cin >> newProduct.quantity;
                currentStore->addProduct(newProduct);
            }
            break;
            case 3:
                if (!currentStore) {
                    cout << "Select a store first!\n";
                    break;
                }
                {
                int index;
                cout << "Enter index to delete: "; cin >> index;
                stores[storeName].deleteProduct(index);
                break;
            }
            case 4:
                if (!currentStore) {
                    cout << "Select a store first!\n";
                    break;
                }
                {
                string name;
                cout << "Enter product name: "; cin >> name;
                Node* found = stores[storeName].searchProduct(name);
                if (found) {
                    cout << "Found: " << found->data.name << ", Price: " << found->data.price << ", Quantity: " << found->data.quantity << "\n";
                } else {
                    cout << "Product not found\n";
                }
                break;
            }
            case 5:
                if (!currentStore) {
                    cout << "Select a store first!\n";
                    break;
                }
                {
                int index;
                cout << "Enter product index: "; cin >> index;
                Node* found = stores[storeName].searchProductByIndex(index);
                if (found) {
                    cout << "Found: " << found->data.name << ", Price: " << found->data.price << ", Quantity: " << found->data.quantity << "\n";
                } else {
                    cout << "Product not found\n";
                }
                break;
            }
            case 6:
                if (!currentStore) {
                    cout << "Select a store first!\n";
                    break;
                }
                currentStore->displayProducts();
                break;
            case 7:
                if (!currentStore) {
                    cout << "Select a store first!\n";
                    break;
                }
                currentStore->saveToFile(storeName + ".bin");
                break;
            case 8:
                if (!currentStore) {
                    cout << "Select a store first!\n";
                    break;
                }
            cout << "Enter filename to load: ";
            cin >> storeName;
            currentStore->loadFromFile(storeName + ".bin");
            break;

            case 9:
                compareProductPrices(stores);
                break;
            case 10:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 10);
}

int main() {
    map<string, CircularDoublyLinkedList> stores;
    menu(stores);
    return 0;
}