#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    Node* next;

    Node(string word) {
        data = word;
        next = nullptr;
    }
};

class TextEditor {
private:
    Node* head;

public:
    TextEditor() {
        head = nullptr;
    }

    void addWord(string word) {
        Node* newNode = new Node(word);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    void undo() {
        if (head == nullptr) {                              //Liste boş
            cout << "Nothing to undo.\n";
            return;
        }

        if (head->next == nullptr) {                        // Listede tek eleman var
            delete head;
            head = nullptr;
            cout << "Last word removed.\n";
            return;
        }

        Node* temp = head;

        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        delete temp->next;
        temp->next = nullptr;
        cout << "Last word removed.\n";
    }

    void display() {
        Node* temp = head;

        if (temp == nullptr) {
            cout << "NULL\n";
            return;
        }

        while (temp != nullptr) {
            cout << "[" << temp->data << "] -> ";
            temp = temp->next;
        }

        cout << "NULL\n";
    }

    ~TextEditor() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TextEditor editor;
    string input;

    cout << "Simple Text Editor using Single Linked List\n";
    cout << "Type words to add them.\n";
    cout << "Type UNDO to remove the last word.\n";
    cout << "Type EXIT to quit.\n\n";

    while (true) {
        cout << "Enter a word: ";
        cin >> input;

        if (input == "EXIT") {
            cout << "Exiting program...\n";
            break;
        }
        else if (input == "UNDO") {
            editor.undo();
        }
        else {
            editor.addWord(input);
        }

        cout << "Current List: ";
        editor.display();
        cout << endl;
    }

    return 0;
}
