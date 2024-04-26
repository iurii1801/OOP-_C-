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
        cout << "Ââåäèòå èìÿ: ";
        cin.ignore();
        getline(cin, name);
        cout << "Ââåäèòå äàòó ïðèåìà íà ðàáîòó: ";
        getline(cin, hireDate);
        cout << "Ââåäèòå äîëæíîñòü: ";
        getline(cin, position);
        cout << "Ââåäèòå çàðïëàòó: ";
        cin >> salary;
        cin.ignore();
    }

    void displayData() const {
        cout << "Èìÿ: " << name << ", Äàòà ïðèåìà íà ðàáîòó: " << hireDate
            << ", Äîëæíîñòü: " << position << ", Çàðïëàòà: " << salary << endl;
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
            outputFile << "Èìÿ: " << worker.getName();
            outputFile << " Äàòà ïðèåìà íà ðàáîòó: " << worker.getHireDate();
            outputFile << " Äîëæíîñòü: " << worker.getPosition();
            outputFile << " Çàðïëàòà: " << worker.getSalary() << " ëååâ."; 
            outputFile << endl; 
        }
        outputFile.close(); 
        cout << "Äàííûå óñïåøíî çàïèñàíû â ôàéë: " << filename << endl;
    }
    else {
        cout << "Îøèáêà îòêðûòèÿ ôàéëà äëÿ çàïèñè." << endl;
    }
}

void readFirstNWorkersFromFile(const string& filename, int n) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Îøèáêà îòêðûòèÿ ôàéëà äëÿ ÷òåíèÿ." << endl;
        return;
    }

    string name, hireDate, position;
    double salary;
    int count = 0;
    while (count < n && inputFile >> name >> hireDate >> position >> salary) {
        cout << "Èìÿ: " << name << ", Äàòà ïðèåìà íà ðàáîòó: " << hireDate
            << ", Äîëæíîñòü: " << position << ", Çàðïëàòà: " << salary << " ëååâ." << endl;
        count++;
        
        inputFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (count == 0) {
        cout << "Ôàéë ïóñò èëè ñîäåðæèò ìåíåå " << n << " çàïèñåé." << endl;
    }

    inputFile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Worker> workers;
    int choice;

    do {
        cout << "\nÌåíþ:" << endl;
        cout << "1) Ââåñòè ýëåìåíòû ìàññèâà ñ êëàâèàòóðû" << endl;
        cout << "2) Âûâåñòè íà ýêðàí ýëåìåíòû ìàññèâà" << endl;
        cout << "3) Ñîðòèðîâàòü â àëôàâèòíîì ïîðÿäêå ïî ïîëþ Èìÿ" << endl;
        cout << "4) Âûâåñòè íà ýêðàí ýëåìåíòû ñ çàðïëàòîé ìåíüøå ÷åì X" << endl;
        cout << "5) Äîáàâèòü íà ïîçèöèþ K íîâûé ýëåìåíò" << endl;
        cout << "6) Óäàëèòü ïåðâûé ýëåìåíò ïî äîëæíîñòè" << endl;
        cout << "7) Çàïèñàòü ýëåìåíòû ìàññèâà â ôàéë" << endl;
        cout << "8) Âûâåñòè íà ýêðàí ïåðâûå N ýëåìåíòîâ èç ôàéëà" << endl;
        cout << "0) Âûõîä" << endl;
        cout << "Âûáåðèòå äåéñòâèå: ";
        cin >> choice;

        switch (choice) {
           
        case 1: {
            int count;
            cout << "Ñêîëüêî ðàáîòíèêîâ äîáàâèòü? ";
            cin >> count;
            for (int i = 0; i < count; ++i) {
                cout << "Ðàáîòíèê " << i + 1 << ":" << endl;
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
            cout << "Ââåäèòå çíà÷åíèå X: ";
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
            cout << "Ââåäèòå ïîçèöèþ äëÿ íîâîãî ðàáîòíèêà: ";
            cin >> index;
            if (index >= 0 && index <= workers.size()) {
                Worker newWorker;
                newWorker.inputData();
                workers.insert(workers.begin() + index, newWorker);
            }
            else {
                cout << "Íåêîððåêòíàÿ ïîçèöèÿ." << endl;
            }
            break;
        }
              
        case 6: {
            string pos;
            cout << "Ââåäèòå äîëæíîñòü äëÿ óäàëåíèÿ: ";
            cin >> pos;
            auto it = find_if(workers.begin(), workers.end(), [&pos](const Worker& w) {
                return w.getPosition() == pos;
                });
            if (it != workers.end()) {
                workers.erase(it);
            }
            else {
                cout << "Ðàáîòíèê ñ òàêîé äîëæíîñòüþ íå íàéäåí." << endl;
            }
            break;
        }    
              
        case 7: {
            string filename;
            cout << "Ââåäèòå èìÿ ôàéëà: ";
            cin >> filename;
            writeToFile(workers, filename);
            break;
        }

        case 8: {
            string filename;
            int n;
            cout << "Ââåäèòå èìÿ ôàéëà äëÿ ÷òåíèÿ: ";
            cin >> filename;
            cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ N äëÿ îòîáðàæåíèÿ: ";
            cin >> n;
            readFirstNWorkersFromFile(filename, n);
            break;
        }
        case 0:
            cout << "Âûõîä èç ïðîãðàììû." << endl;
            break;
        default:
            cout << "Íåâåðíûé âûáîð, ïîïðîáóéòå åùå ðàç." << endl;
        }
        cin.ignore();
    } while (choice != 0);

    return 0;
}
