#include <iostream>
#include <fstream>
#include <cstring>
#include <list>

using namespace std;

#define MAX_BOOKS 20

struct Date {
    int month;
    int year;
};

struct Book {
    char Name[50];
    char Avtor[50];
    Date Data;
    float Cost;
};

list<Book> books;


void loadBooksFromFile() {
    ifstream file("SHOP.dat", ios::binary);
    if (!file) {
        cout << "Error loading from file.\n";
        return;
    }

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        books.push_back(book);
    }

    file.close();
}


void showBooks() {
    if (books.empty()) {
        cout << "No books found.\n";
        return;
    }

    for (const auto& book : books) {
        cout << "Name: " << book.Name << ", Author: " << book.Avtor
            << ", Date: " << book.Data.month << "/" << book.Data.year
            << ", Cost: " << book.Cost << "\n";
    }
}


void deleteBooksByYear(int year) {
    books.remove_if([year](const Book& book) {
        return book.Data.year == year;
        });
    cout << "Books from year " << year << " have been deleted.\n";
}


void addNewBooks(int N) {
    for (int i = 0; i < N; ++i) {
        Book newBook;
        cout << "Enter book name: ";
        cin.ignore();
        cin.getline(newBook.Name, 50);
        cout << "Enter author: ";
        cin.getline(newBook.Avtor, 50);
        cout << "Enter month and year of publication (MM YYYY): ";
        cin >> newBook.Data.month >> newBook.Data.year;
        cout << "Enter cost: ";
        cin >> newBook.Cost;
        books.push_back(newBook);
    }
    cout << "Added " << N << " new books.\n";
}


void saveBooksToFile() {
    ofstream file("SHOP_NEW.DAT", ios::binary);
    if (!file) {
        cout << "Error saving to file.\n";
        return;
    }

    for (const auto& book : books) {
        file.write(reinterpret_cast<const char*>(&book), sizeof(Book));
    }

    file.close();
    cout << "Books saved.\n";
}


void readLastTenBooks() {
    ifstream file("SHOP_NEW.DAT", ios::binary);
    if (!file) {
        cout << "Error loading from file.\n";
        return;
    }

    list<Book> lastTenBooks;
    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        lastTenBooks.push_back(book);
    }

    file.close();

    lastTenBooks.sort([](const Book& a, const Book& b) {
        return strcmp(a.Avtor, b.Avtor) < 0;
        });

    ofstream sortedFile("BOOK.DAT", ios::binary);
    if (!sortedFile) {
        cout << "Error saving to file.\n";
        return;
    }

    for (const auto& b : lastTenBooks) {
        sortedFile.write(reinterpret_cast<const char*>(&b), sizeof(Book));
    }

    sortedFile.close();
    cout << "Books sorted by author and saved to BOOK.DAT.\n";
}

int main() {
    int choice;
    do {
        cout << "\n1. Load books from SHOP.dat\n";
        cout << "2. Show all books\n";
        cout << "3. Delete books by year\n";
        cout << "4. Add N new books\n";
        cout << "5. Save updated books to SHOP_NEW.DAT\n";
        cout << "6. Read and sort last 10 books from SHOP_NEW.DAT\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadBooksFromFile();
            break;
        case 2:
            showBooks();
            break;
        case 3:
            int year;
            cout << "Enter year to delete books: ";
            cin >> year;
            deleteBooksByYear(year);
            break;
        case 4:
            int N;
            cout << "Enter number of new books to add: ";
            cin >> N;
            addNewBooks(N);
            break;
        case 5:
            saveBooksToFile();
            break;
        case 6:
            readLastTenBooks();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 7);

    return 0;
}
