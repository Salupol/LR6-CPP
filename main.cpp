#include <iostream>
#include <fstream>

using namespace std;
struct NODE {
    string name;
    string phone_number;
    string tarrif;
    NODE *next;
    NODE *prev;
};

NODE *createNode(string name, string phone_number, string tarrif) {
    NODE *newNode = new NODE;
    newNode->name = name;
    newNode->phone_number = phone_number;
    newNode->tarrif = tarrif;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

NODE *addNode(NODE *head, string name, string phone_number, string tarrif) {
    NODE *newnode = createNode(name, phone_number, tarrif);
    if (head == nullptr) {
        head = newnode;
    } else {
        NODE *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->prev = temp;
    }
    return head;
}

void printList(NODE *head) {
    while (head != nullptr) {
        cout << head->name << " " << head->phone_number << " " << head->tarrif << endl;
        head = head->next;
    }
}

int count_tariff(NODE *head, string tarrif) {
    int count = 0;
    NODE *temp = head;
    while (temp != nullptr) {
        if (temp->tarrif == tarrif) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

void delete_subscriber_by_number(NODE *&head, string phone_number) {
    NODE *temp = head;
    NODE *prev = nullptr;
    while (temp != nullptr) {
        if (temp->phone_number == phone_number) {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            }
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }
            if (temp == head) {
                head = temp->next;
            }
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void change_tariff(NODE *head, string name, string new_tarrif) {
    NODE *temp = head;
    while (temp != nullptr) {
        if (temp->name == name) {
            temp->tarrif = new_tarrif;
            return;
        }
        temp = temp->next;
    }
}

void deleteList(NODE *head) {
    NODE *temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void ImportFromFile(NODE *&head) {
    ifstream file("data.txt");
    if (!file) {
        cout << "file not found" << endl;
        return;
    }
    string name;
    string phone_number;
    string tarrif;
    while (file >> name >> phone_number >> tarrif) {
        head = addNode(head, name, phone_number, tarrif);
    }
}

void ExportToFile(NODE *head) {
    ofstream file("data.txt");
    NODE *temp = head;
    while (temp != nullptr) {
        file << temp->name << " " << temp->phone_number << " " << temp->tarrif << endl;
        temp = temp->next;
    }
}

int main() {
    NODE *head = nullptr;
    ImportFromFile(head);
    while (1) {
        srand(time(0));
        int answer;
        cout << "\nhello, it`s vodafone database, choose your action" << endl;
        cout << "1. add new subscriber" << endl;
        cout << "2. delete subscriber by number" << endl;
        cout << "3. change tariff" << endl;
        cout << "4. count subscribers with tariff" << endl;
        cout << "5. print all subscribers" << endl;
        cout << "6. save and exit" << endl;
        cin >> answer;
        if (!cin) {
            cout << "wrong input" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        switch (answer) {
            case 1: {
                string name;
                string phone_number;
                string tarrif;
                string answer;
                cout << "enter name" << endl;
                cin >> name;
                cout << "generate phone number or enter your own (gen for generate, anything else to manual"
                     << endl;
                cin >> answer;
                if (answer == "gen") {
                    phone_number = to_string(rand() % 10000000 + 1000000);
                    cout << "generated number is " << phone_number << endl;
                } else {
                    cout << "enter phone number" << endl;
                    cin >> phone_number;
                }
                cout << "enter tariff" << endl;
                cin >> tarrif;
                head = addNode(head, name, phone_number, tarrif);
                break;
            }
            case 2: {
                string number;
                cout << "enter number" << endl;
                cin >> number;
                delete_subscriber_by_number(head, number);
                break;
            }
            case 3: {
                string new_tarrif;
                string name;
                cout << "enter name of subscriber" << endl;
                cin >> name;
                cout << "enter new tariff" << endl;
                cin >> new_tarrif;
                change_tariff(head, name, new_tarrif);
                break;
            }
            case 4: {
                string tarrif;
                cout << "enter tariff name to count" << endl;
                cin >> tarrif;
                cout << "count of subscribers with tarrif " << tarrif << ": " << count_tariff(head, tarrif) << endl;
                break;
            }
            case 5: {
                printList(head);
                break;
            }
            case 6: {
                ExportToFile(head);
                deleteList(head);
                return 0;
            }
            default: {
                cout << "wrong input" << endl;
                break;
            }
        }
    }
}