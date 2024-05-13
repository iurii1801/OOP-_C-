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
    ;

    TaskItem(string title, string description, Priority priority) : title(title), description(description), completed(0), priority(priority) {}

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
    bool operator==(TaskItem whatever) {
        return (title == whatever.title && description == whatever.description && completed == whatever.completed && priority == whatever.priority);
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

    void DisplayAll() {
        cout << "All Tasks:" << endl;
        for (Task& item : items) {
            item.display();
            cout << endl;
        }
        cout << "All Notes:" << endl;
        for (Note& note : notes) {
            note.display();
            cout << endl;
        }
    }

    TaskItem getTask(int index) {
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
    static void DisplayTotalTasks(TaskList taskList) {
        cout << "Total Tasks: " << taskList.items.size() << endl;
    }
};




int main() {
    TaskItem task("Meeting", "To walk with friends", Priority::Low);
    TaskItem task1("To do individual work", "Python project", Priority::Medium);
    TaskItem task2("Lab 3 OOP", "To do all steps of lab", Priority::High);

    task2.markAsCompleted();

    Note note("To prepare to exams");
    Note note1("To finish all labs");
    Note note2("To buy products");

    TaskList taskList;
    taskList.addTask(task);
    taskList.addTask(task1);
    taskList.addTask(task2);
    taskList.addNote(note);
    taskList.addNote(note1);
    taskList.addNote(note2);

    taskList.DisplayAll();

    cout << "Task at index 1:" << endl;
    TaskItem taskAtIndex1 = taskList.getTask(1);
    taskAtIndex1.display();

    cout << "Note at index 0:" << endl;
    Note noteAtIndex0 = taskList.getNote(0);
    noteAtIndex0.display();

    TaskList::DisplayTotalTasks(taskList);

    if (comparePriority(task1, task2)) {
        cout << "Task 2 has higher priority than Task 1." << endl;
    }
    else {
        cout << "Task 1 has higher priority than Task 2." << endl;
    }


    if (task1 == task2) {
        cout << "Tasks are equal." << endl;
    }
    else {
        cout << "Tasks are not equal." << endl;
    }

    return 0;
}

