#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <clocale>
#include <fstream>

using namespace std;

class Worker {
private:
    string name;
    string hireDate;
    string position;
    double salary;

public:
    Worker() : name(""), hireDate(""), position(""), salary(0.0) {}

    Worker(string name, string hireDate, string position, double salary)
        : name(name), hireDate(hireDate), position(position), salary(salary) {}

    ~Worker() {}

    void inputData() {
        cout << "Введите имя: ";
        cin.ignore();
        getline(cin, name);
        cout << "Введите дату приема на работу: ";
        getline(cin, hireDate);
        cout << "Введите должность: ";
        getline(cin, position);
        cout << "Введите зарплату: ";
        cin >> salary;
        cin.ignore();
    }

    void displayData() const {
        cout << "Имя: " << name << ", Дата приема на работу: " << hireDate
            << ", Должность: " << position << ", Зарплата: " << salary << endl;
    }

   
    string getName() const { return name; }
    string getHireDate() const { return hireDate; } 
    string getPosition() const { return position; }
    double getSalary() const { return salary; }

    static bool compareByName(const Worker& a, const Worker& b) {
        return a.name < b.name;
    }
};

void writeToFile(const vector<Worker>& workers, const string& filename) {
    ofstream outputFile(filename); 
    if (outputFile.is_open()) {
        for (const Worker& worker : workers) {
            outputFile << "Имя: " << worker.getName();
            outputFile << " Дата приема на работу: " << worker.getHireDate();
            outputFile << " Должность: " << worker.getPosition();
            outputFile << " Зарплата: " << worker.getSalary() << " леев."; 
            outputFile << endl; 
        }
        outputFile.close(); 
        cout << "Данные успешно записаны в файл: " << filename << endl;
    }
    else {
        cout << "Ошибка открытия файла для записи." << endl;
    }
}

void readFirstNWorkersFromFile(const string& filename, int n) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла для чтения." << endl;
        return;
    }

    string name, hireDate, position;
    double salary;
    int count = 0;
    while (count < n && inputFile >> name >> hireDate >> position >> salary) {
        cout << "Имя: " << name << ", Дата приема на работу: " << hireDate
            << ", Должность: " << position << ", Зарплата: " << salary << " леев." << endl;
        count++;
        
        inputFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (count == 0) {
        cout << "Файл пуст или содержит менее " << n << " записей." << endl;
    }

    inputFile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Worker> workers;
    int choice;

    do {
        cout << "\nМеню:" << endl;
        cout << "1) Ввести элементы массива с клавиатуры" << endl;
        cout << "2) Вывести на экран элементы массива" << endl;
        cout << "3) Сортировать в алфавитном порядке по полю Имя" << endl;
        cout << "4) Вывести на экран элементы с зарплатой меньше чем X" << endl;
        cout << "5) Добавить на позицию K новый элемент" << endl;
        cout << "6) Удалить первый элемент по должности" << endl;
        cout << "7) Записать элементы массива в файл" << endl;
        cout << "8) Вывести на экран первые N элементов из файла" << endl;
        cout << "0) Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
           
        case 1: {
            int count;
            cout << "Сколько работников добавить? ";
            cin >> count;
            for (int i = 0; i < count; ++i) {
                cout << "Работник " << i + 1 << ":" << endl;
                Worker newWorker;
                newWorker.inputData();
                workers.push_back(newWorker);
            }
            break;
        }
              
        case 2:
            for (const auto& worker : workers) {
                worker.displayData();
            }
            break;
            
        case 3:
            sort(workers.begin(), workers.end(), Worker::compareByName);
            break;
           
        case 4: {
            double threshold;
            cout << "Введите значение X: ";
            cin >> threshold;
            for (const auto& worker : workers) {
                if (worker.getSalary() < threshold) {
                    worker.displayData();
                }
            }
            break;
        }
              
        case 5: {
            int index;
            cout << "Введите позицию для нового работника: ";
            cin >> index;
            if (index >= 0 && index <= workers.size()) {
                Worker newWorker;
                newWorker.inputData();
                workers.insert(workers.begin() + index, newWorker);
            }
            else {
                cout << "Некорректная позиция." << endl;
            }
            break;
        }
              
        case 6: {
            string pos;
            cout << "Введите должность для удаления: ";
            cin >> pos;
            auto it = find_if(workers.begin(), workers.end(), [&pos](const Worker& w) {
                return w.getPosition() == pos;
                });
            if (it != workers.end()) {
                workers.erase(it);
            }
            else {
                cout << "Работник с такой должностью не найден." << endl;
            }
            break;
        }    
              
        case 7: {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            writeToFile(workers, filename);
            break;
        }

        case 8: {
            string filename;
            int n;
            cout << "Введите имя файла для чтения: ";
            cin >> filename;
            cout << "Введите количество элементов N для отображения: ";
            cin >> n;
            readFirstNWorkersFromFile(filename, n);
            break;
        }
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор, попробуйте еще раз." << endl;
        }
        cin.ignore();
    } while (choice != 0);

    return 0;
}
