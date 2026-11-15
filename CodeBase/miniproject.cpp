/*
 * Made with ♡ by Saket kumar hehe
 * Turning coffee ☕ into code.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

template <typename T>
T largestOfThree(T a, T b, T c) {
    T largest = a;
    if (b > largest) largest = b;
    if (c > largest) largest = c;
    return largest;
}

template <typename T>
class Student {
private:
    string name;
    T score;

public:
    Student() : name(""), score(T()) {}
    Student(const string& n, T s) : name(n), score(s) {}

    string getName() const { return name; }
    T getScore() const { return score; }

    void display() const {
        cout << left << setw(25) << name << right << setw(10) << score << endl;
    }
};

template <typename T>
class ResultBook {
private:
    vector<Student<T>> records;

    static string toLower(string s) {
        transform(s.begin(), s.end(), s.begin(),
                  [](unsigned char c) { return tolower(c); });
        return s;
    }

public:
    void add(const string& name, T score) {
        records.push_back(Student<T>(name, score));
    }

    bool empty() const { return records.empty(); }
    size_t size() const { return records.size(); }

    void displayAll() const {
        if (records.empty()) {
            cout << "  No records available.\n";
            return;
        }
        cout << left << setw(25) << "  Name" << right << setw(10) << "Score" << endl;
        cout << "  " << string(33, '-') << endl;
        for (const auto& s : records) {
            cout << "  ";
            s.display();
        }
    }

    double average() const {
        if (records.empty()) return 0.0;
        double sum = 0;
        for (const auto& s : records) sum += s.getScore();
        return sum / records.size();
    }

    void showTopper() const {
        if (records.empty()) return;
        size_t best = 0;
        for (size_t i = 1; i < records.size(); i++)
            if (largestOfThree(records[best].getScore(), records[i].getScore(),
                               records[best].getScore()) == records[i].getScore())
                best = i;
        cout << "  Topper : " << records[best].getName()
             << " (" << records[best].getScore() << ")\n";
    }

    void search(const string& key) const {
        string k = toLower(key);
        bool found = false;
        for (const auto& s : records) {
            if (toLower(s.getName()).find(k) != string::npos) {
                if (!found) {
                    cout << "  Matching record(s):\n";
                    found = true;
                }
                cout << "  ";
                s.display();
            }
        }
        if (!found) cout << "  No student found with name \"" << key << "\".\n";
    }

    bool saveToFile(const string& filename) const {
        ofstream out(filename);
        if (!out) return false;
        for (const auto& s : records)
            out << s.getName() << ';' << s.getScore() << '\n';
        return true;
    }

    int loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) return -1;
        records.clear();
        string line;
        int count = 0;
        while (getline(in, line)) {
            size_t pos = line.rfind(';');
            if (pos == string::npos) continue;
            string name = line.substr(0, pos);
            istringstream iss(line.substr(pos + 1));
            T score;
            if (iss >> score) {
                add(name, score);
                count++;
            }
        }
        return count;
    }
};

string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

string readName(const string& prompt) {
    while (true) {
        string s = readLine(prompt);
        size_t first = s.find_first_not_of(" \t");
        size_t last = s.find_last_not_of(" \t");
        if (first != string::npos) return s.substr(first, last - first + 1);
        cout << "  [Invalid Input] Name cannot be empty.\n";
    }
}

template <typename T>
T readNumber(const string& prompt, T lo, T hi) {
    while (true) {
        string line = readLine(prompt);
        istringstream iss(line);
        T value;
        if (iss >> value && (iss >> ws).eof()) {
            if (value >= lo && value <= hi) return value;
            cout << "  [Invalid Input] Value must be between " << lo << " and " << hi << ".\n";
        } else {
            cout << "  [Invalid Input] Please enter a valid number.\n";
        }
    }
}


template <typename T>
void addStudent(ResultBook<T>& book) {
    string name = readName("  Enter student name : ");
    T score = readNumber<T>("  Enter score (0-100): ", T(0), T(100));
    book.add(name, score);
    cout << "  Record added successfully.\n";
}

template <typename T>
void largestOfThreeMenu() {
    cout << "  Enter three scores to compare:\n";
    T a = readNumber<T>("   Score 1: ", T(0), T(100));
    T b = readNumber<T>("   Score 2: ", T(0), T(100));
    T c = readNumber<T>("   Score 3: ", T(0), T(100));
    cout << "  Largest score = " << largestOfThree(a, b, c) << endl;
}

template <typename T>
void averageMenu(const ResultBook<T>& book) {
    if (book.empty()) {
        cout << "  No records available to calculate average.\n";
        return;
    }
    cout << fixed << setprecision(2);
    cout << "  Total students : " << book.size() << endl;
    cout << "  Average score  : " << book.average() << endl;
    book.showTopper();
    cout.unsetf(ios::fixed);
}

template <typename T>
void searchMenu(const ResultBook<T>& book) {
    if (book.empty()) {
        cout << "  No records available to search.\n";
        return;
    }
    book.search(readName("  Enter name to search: "));
}

template <typename T>
void saveMenu(const ResultBook<T>& book, const string& file) {
    if (book.saveToFile(file))
        cout << "  Saved " << book.size() << " record(s) to \"" << file << "\".\n";
    else
        cout << "  [Error] Could not write to \"" << file << "\".\n";
}

template <typename T>
void loadMenu(ResultBook<T>& book, const string& file) {
    int n = book.loadFromFile(file);
    if (n < 0) cout << "  [Error] File \"" << file << "\" not found. Save records first.\n";
    else       cout << "  Loaded " << n << " record(s) from \"" << file << "\".\n";
}

void printMenu() {
    cout << "     RESULT PROCESSING SYSTEM\n";
    cout << "  1. Add student record\n";
    cout << "  2. Display student records\n";
    cout << "  3. Find largest of three scores\n";
    cout << "  4. Calculate average\n";
    cout << "  5. Search student by name\n";
    cout << "  6. Save records to file\n";
    cout << "  7. Load records from file\n";
    cout << "  8. Exit\n";
}

int chooseType() {
    cout << "  Select score type:\n";
    cout << "   1. Integer marks   \n";
    cout << "   2. Floating scores \n";
    return readNumber<int>("  Your choice: ", 1, 2);
}

int main() {
    ResultBook<int> intBook;
    ResultBook<double> dblBook;
    const string intFile = "results_int.txt";
    const string dblFile = "results_float.txt";

    while (true) {
        printMenu();
        int choice = readNumber<int>("  Enter your choice (1-8): ", 1, 8);
        cout << endl;

        if (choice == 8) {
            cout << "  Thank you for using the Result Processing System. Goodbye!\n";
            break;
        }

        if (choice == 2) {
            cout << "  --- Integer Records ---\n";
            intBook.displayAll();
            cout << "\n  --- Floating-point Records ---\n";
            dblBook.displayAll();
            continue;
        }

        int type = chooseType();
        cout << endl;
        switch (choice) {
            case 1: type == 1 ? addStudent(intBook) : addStudent(dblBook); break;
            case 3: type == 1 ? largestOfThreeMenu<int>() : largestOfThreeMenu<double>(); break;
            case 4: type == 1 ? averageMenu(intBook) : averageMenu(dblBook); break;
            case 5: type == 1 ? searchMenu(intBook) : searchMenu(dblBook); break;
            case 6: type == 1 ? saveMenu(intBook, intFile) : saveMenu(dblBook, dblFile); break;
            case 7: type == 1 ? loadMenu(intBook, intFile) : loadMenu(dblBook, dblFile); break;
        }
    }
    return 0;
}
