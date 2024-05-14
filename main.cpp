#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Priority {
    Low,
    Medium,
    High
};

class Task {
public:
    virtual void display() = 0;
    virtual bool isCompleted() = 0;
    virtual void markAsCompleted() = 0;
};

class TaskItem : public Task {
private:
    string title;
    string description;
    bool completed;
    Priority priority;

public:
    friend bool comparePriority(TaskItem& task1, TaskItem& task2) {
        return task1.priority < task2.priority;
    }

    TaskItem(string title, string description, Priority priority)
        : title(title), description(description), completed(false), priority(priority) {}

    virtual void display() override {
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Priority: ";
        switch (priority) {
        case Priority::Low:
            cout << "Low";
            break;
        case Priority::Medium:
            cout << "Medium";
            break;
        case Priority::High:
            cout << "High";
            break;
        }
        cout << endl;
        cout << "Status: " << (completed ? "Completed" : "Not Completed") << endl;
    }

    virtual bool isCompleted() override {
        return completed;
    }

    virtual void markAsCompleted() override {
        completed = true;
    }

    bool operator==(TaskItem& other) {
        return (title == other.title && description == other.description && completed == other.completed && priority == other.priority);
    }
};

class Note {
private:
    string content;

public:
    Note(string content) : content(content) {}

    void display() {
        cout << "Note: " << content << endl;
    }
};

class TaskList {
private:
    vector<TaskItem> items;
    vector<Note> notes;

public:
    void addTask(TaskItem task) {
        items.push_back(task);
    }

    void addNote(Note note) {
        notes.push_back(note);
    }

    void displayAll() {
        cout << "All Tasks:" << endl;
        for (TaskItem& item : items) {
            item.display();
            cout << endl;
        }
        cout << "All Notes:" << endl;
        for (Note& note : notes) {
            note.display();
            cout << endl;
        }
    }

    TaskItem& getTask(int index) {
        if (index >= 0 && index < items.size()) {
            return items[index];
        }
        else {
            cout << "Invalid index for task." << endl;
            exit(1);
        }
    }

    Note getNote(int index) {
        if (index >= 0 && index < notes.size()) {
            return notes[index];
        }
        else {
            cout << "Invalid index for note." << endl;
            exit(1);
        }
    }

    static void displayTotalTasks(TaskList& taskList) {
        cout << "Total Tasks: " << taskList.items.size() << endl;
    }
};

Priority getPriorityFromUser() {
    int priority;
    cout << "Enter priority (0 for Low, 1 for Medium, 2 for High): ";
    cin >> priority;
    return static_cast<Priority>(priority);
}

void addTask(TaskList& taskList) {
    string title, description;
    cout << "Enter task title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter task description: ";
    getline(cin, description);
    Priority priority = getPriorityFromUser();
    TaskItem task(title, description, priority);
    taskList.addTask(task);
}

void addNote(TaskList& taskList) {
    string content;
    cout << "Enter note content: ";
    cin.ignore();
    getline(cin, content);
    Note note(content);
    taskList.addNote(note);
}

void markTaskAsCompleted(TaskList& taskList) {
    int index;
    cout << "Enter the index of the task to mark as completed: ";
    cin >> index;
    taskList.getTask(index).markAsCompleted();
}

void compareTasks(TaskList& taskList) {
    int index1, index2;
    cout << "Enter the index of the first task to compare: ";
    cin >> index1;
    cout << "Enter the index of the second task to compare: ";
    cin >> index2;
    TaskItem& task1 = taskList.getTask(index1);
    TaskItem& task2 = taskList.getTask(index2);
    if (comparePriority(task1, task2)) {
        cout << "Task at index " << index2 << " has higher priority than task at index " << index1 << "." << endl;
    }
    else {
        cout << "Task at index " << index1 << " has higher priority than task at index " << index2 << "." << endl;
    }
}

int main() {
    TaskList taskList;
    int choice;
    do {
        cout << "\nTask Management System\n";
        cout << "1. Add Task\n";
        cout << "2. Add Note\n";
        cout << "3. Display All Tasks and Notes\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Compare Task Priority\n";
        cout << "6. Display Total Tasks\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addTask(taskList);
            break;
        case 2:
            addNote(taskList);
            break;
        case 3:
            taskList.displayAll();
            break;
        case 4:
            markTaskAsCompleted(taskList);
            break;
        case 5:
            compareTasks(taskList);
            break;
        case 6:
            TaskList::displayTotalTasks(taskList);
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
