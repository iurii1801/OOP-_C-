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
        cout << "������� ���: ";
        cin.ignore();
        getline(cin, name);
        cout << "������� ���� ������ �� ������: ";
        getline(cin, hireDate);
        cout << "������� ���������: ";
        getline(cin, position);
        cout << "������� ��������: ";
        cin >> salary;
        cin.ignore();
    }

    void displayData() const {
        cout << "���: " << name << ", ���� ������ �� ������: " << hireDate
            << ", ���������: " << position << ", ��������: " << salary << endl;
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
            outputFile << "���: " << worker.getName();
            outputFile << " ���� ������ �� ������: " << worker.getHireDate();
            outputFile << " ���������: " << worker.getPosition();
            outputFile << " ��������: " << worker.getSalary() << " ����."; 
            outputFile << endl; 
        }
        outputFile.close(); 
        cout << "������ ������� �������� � ����: " << filename << endl;
    }
    else {
        cout << "������ �������� ����� ��� ������." << endl;
    }
}

void readFirstNWorkersFromFile(const string& filename, int n) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "������ �������� ����� ��� ������." << endl;
        return;
    }

    string name, hireDate, position;
    double salary;
    int count = 0;
    while (count < n && inputFile >> name >> hireDate >> position >> salary) {
        cout << "���: " << name << ", ���� ������ �� ������: " << hireDate
            << ", ���������: " << position << ", ��������: " << salary << " ����." << endl;
        count++;
        
        inputFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (count == 0) {
        cout << "���� ���� ��� �������� ����� " << n << " �������." << endl;
    }

    inputFile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Worker> workers;
    int choice;

    do {
        cout << "\n����:" << endl;
        cout << "1) ������ �������� ������� � ����������" << endl;
        cout << "2) ������� �� ����� �������� �������" << endl;
        cout << "3) ����������� � ���������� ������� �� ���� ���" << endl;
        cout << "4) ������� �� ����� �������� � ��������� ������ ��� X" << endl;
        cout << "5) �������� �� ������� K ����� �������" << endl;
        cout << "6) ������� ������ ������� �� ���������" << endl;
        cout << "7) �������� �������� ������� � ����" << endl;
        cout << "8) ������� �� ����� ������ N ��������� �� �����" << endl;
        cout << "0) �����" << endl;
        cout << "�������� ��������: ";
        cin >> choice;

        switch (choice) {
           
        case 1: {
            int count;
            cout << "������� ���������� ��������? ";
            cin >> count;
            for (int i = 0; i < count; ++i) {
                cout << "�������� " << i + 1 << ":" << endl;
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
            cout << "������� �������� X: ";
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
            cout << "������� ������� ��� ������ ���������: ";
            cin >> index;
            if (index >= 0 && index <= workers.size()) {
                Worker newWorker;
                newWorker.inputData();
                workers.insert(workers.begin() + index, newWorker);
            }
            else {
                cout << "������������ �������." << endl;
            }
            break;
        }
              
        case 6: {
            string pos;
            cout << "������� ��������� ��� ��������: ";
            cin >> pos;
            auto it = find_if(workers.begin(), workers.end(), [&pos](const Worker& w) {
                return w.getPosition() == pos;
                });
            if (it != workers.end()) {
                workers.erase(it);
            }
            else {
                cout << "�������� � ����� ���������� �� ������." << endl;
            }
            break;
        }    
              
        case 7: {
            string filename;
            cout << "������� ��� �����: ";
            cin >> filename;
            writeToFile(workers, filename);
            break;
        }

        case 8: {
            string filename;
            int n;
            cout << "������� ��� ����� ��� ������: ";
            cin >> filename;
            cout << "������� ���������� ��������� N ��� �����������: ";
            cin >> n;
            readFirstNWorkersFromFile(filename, n);
            break;
        }
        case 0:
            cout << "����� �� ���������." << endl;
            break;
        default:
            cout << "�������� �����, ���������� ��� ���." << endl;
        }
        cin.ignore();
    } while (choice != 0);

    return 0;
}
