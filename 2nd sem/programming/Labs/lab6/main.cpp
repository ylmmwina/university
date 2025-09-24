#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// структура, яка представляє книжку
struct Book {
    string title;   // назва книжки
    string author;  // автор книжки
    int year;       // рік видання

    // вивіду інформації про книжку
    void print() const {
        cout << "Title: " << title << ", Author: " << author << ", Year: " << year << endl;
    }
};

// вузол префіксного дерева (Trie)
struct TrieNode {
    TrieNode* children[256]; // масив вказівників на наступні символи (для ASCII)
    vector<int> bookIndices; // індекси книжок, які містять цей префікс

    TrieNode() {
        // ініціалізуємо всі вказівники як null
        for (int i = 0; i < 256; ++i) children[i] = nullptr;
    }
};

// клас, що реалізує всю логіку системи
class BookSystem {
private:
    vector<Book> books;    // колекція книжок
    TrieNode* root = new TrieNode(); // корінь Trie

    // метод для вставки назви книжки в Trie
    void insertIntoTrie(const string& word, int index) {
        TrieNode* node = root;
        for (char c : word) {
            unsigned char uc = (unsigned char)c; // ASCII символ
            if (!node->children[uc])
                node->children[uc] = new TrieNode(); // створити новий вузол, якщо не існує
            node = node->children[uc]; // перехід до наступного вузла
            node->bookIndices.push_back(index); // додаємо індекс книжки
        }
    }

    // метод для пошуку книжок за префіксом у Trie
    void searchTrie(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            unsigned char uc = (unsigned char)c;
            if (!node->children[uc]) {
                cout << "No matches found for prefix \"" << prefix << "\"\n";
                return;
            }
            node = node->children[uc];
        }

        cout << "Matching books:\n";
        for (int idx : node->bookIndices) {
            books[idx].print();
        }
    }

public:
    // додавання нової книжки користувачем
    void addBook() {
        Book b;
        cout << "Enter title: ";
        getline(cin, b.title);
        cout << "Enter author: ";
        getline(cin, b.author);
        cout << "Enter year: ";
        cin >> b.year;
        cin.ignore(); // очищаємо буфер після введення числа

        books.push_back(b); // додаємо книжку в список
        insertIntoTrie(b.title, books.size() - 1); // додаємо назву у Trie

        cout << "Book added!\n";
    }

    // збереження книжок у текстовий файл
    void saveToFile(const string& filename) {
        ofstream out(filename);
        for (const auto& b : books) {
            out << b.title << ";" << b.author << ";" << b.year << "\n";
        }
        cout << "Saved to: " << filename << endl;

    }

    // завантаження книжок з файлу
    void loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) {
            cout << "File not found.\n";
            return;
        }
        books.clear();         // очищаємо попередні книжки
        delete root;           // видаляємо старе дерево
        root = new TrieNode(); // створюємо нове дерево

        string line;
        while (getline(in, line)) {
            size_t p1 = line.find(';');
            size_t p2 = line.rfind(';');
            if (p1 == string::npos || p2 == string::npos) continue;

            Book b;
            b.title = line.substr(0, p1);
            b.author = line.substr(p1 + 1, p2 - p1 - 1);
            b.year = stoi(line.substr(p2 + 1));

            books.push_back(b);
            insertIntoTrie(b.title, books.size() - 1); // вставляємо назву у Trie
        }
        cout << "Collection loaded from file.\n";
    }

    // запуск пошуку по назві
    void searchByPrefix() {
        cout << "Enter prefix: ";
        string prefix;
        getline(cin, prefix);
        searchTrie(prefix);
    }

    // показ усіх книжок
    void listAll() {
        for (const auto& b : books) {
            b.print();
        }
    }
};

int main() {
    BookSystem system;
    string filename = "books.txt"; // ім’я файлу, де зберігається колекція

    while (true) {
        // меню для користувача
        cout << "\n1. Add book\n2. Show all books\n3. Search by prefix\n4. Save to file\n5. Load from file\n6. Exit\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore(); // очищення буфера

        switch (choice) {
            case 1:
                system.addBook();
                break;
            case 2:
                system.listAll();
                break;
            case 3:
                system.searchByPrefix();
                break;
            case 4:
                system.saveToFile(filename);
                break;
            case 5:
                system.loadFromFile(filename);
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
