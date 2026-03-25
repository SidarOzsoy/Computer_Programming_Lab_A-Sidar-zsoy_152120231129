#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    int ratings[3];
    Song* next;
    Song* prev;

    Song(string t, string a, int r1, int r2, int r3) {
        title = t;
        artist = a;
        ratings[0] = r1;
        ratings[1] = r2;
        ratings[2] = r3;
        next = nullptr;
        prev = nullptr;
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    void addSong(string title, string artist, int r1, int r2, int r3) {
        Song* newSong = new Song(title, artist, r1, r2, r3);

        if (head == nullptr) {
            head = tail = current = newSong;
            return;
        }

        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    void nextSong() {
        if (current == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        if (current->next == nullptr) {
            cout << "You are already at the last song.\n";
            return;
        }

        current = current->next;
        cout << "Moved to next song: " << current->title << "\n";
    }

    void prevSong() {
        if (current == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        if (current->prev == nullptr) {
            cout << "You are already at the first song.\n";
            return;
        }

        current = current->prev;
        cout << "Moved to previous song: " << current->title << "\n";
    }

    void removeCurrent() {
        if (current == nullptr) {
            cout << "Playlist is empty. Nothing to remove.\n";
            return;
        }

        Song* temp = current;

        if (head == tail) {
            head = tail = current = nullptr;
        }
        else if (current == head) {
            head = head->next;
            head->prev = nullptr;
            current = head;
        }
        else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
            current = tail;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;
        }

        cout << "Removed song: " << temp->title << "\n";
        delete temp;
    }

    void displayPlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        Song* temp = head;
        cout << "\n--- Playlist ---\n";

        while (temp != nullptr) {
            if (temp == current) {
                cout << "-> ";
            } else {
                cout << "   ";
            }

            cout << "Title: " << temp->title
                 << ", Artist: " << temp->artist
                 << ", Ratings: ";

            for (int i = 0; i < 3; i++) {
                cout << temp->ratings[i];
                if (i < 2) {
                    cout << ", ";
                }
            }

            cout << "\n";
            temp = temp->next;
        }

        cout << "----------------\n";
    }

    ~Playlist() {
        Song* temp = head;
        while (temp != nullptr) {
            Song* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

int main() {
    Playlist playlist;
    string command;

    while (true) {
        cout << "\nEnter command (ADD, NEXT, PREV, REMOVE, DISPLAY, EXIT): ";
        cin >> command;

        if (command == "ADD") {
            string title, artist;
            int r1, r2, r3;

            cin.ignore();
            cout << "Enter song title: ";
            getline(cin, title);

            cout << "Enter artist name: ";
            getline(cin, artist);

            cout << "Enter 3 critic ratings: ";
            cin >> r1 >> r2 >> r3;

            playlist.addSong(title, artist, r1, r2, r3);
            cout << "Song added successfully.\n";
        }
        else if (command == "NEXT") {
            playlist.nextSong();
        }
        else if (command == "PREV") {
            playlist.prevSong();
        }
        else if (command == "REMOVE") {
            playlist.removeCurrent();
        }
        else if (command == "DISPLAY") {
            playlist.displayPlaylist();
        }
        else if (command == "EXIT") {
            cout << "Exiting program.\n";
            break;
        }
        else {
            cout << "Invalid command.\n";
        }
    }

    return 0;
}
