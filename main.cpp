#include <iostream>

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
    newNode->next = NULL;
    newNode->prev = nullptr;
    return newNode;
}

NODE *addNode(NODE *head, string name, string phone_number, string tarrif) {
    NODE *newnode = createNode(name, phone_number, tarrif);
    if (head == NULL) {
        head = newnode;
    } else {
        NODE *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->prev = temp;
    }
    return head;
}

void printList(NODE *head) {
    NODE *last;
    while (head != NULL) {
        cout << head->name << " " << head->phone_number << " " << head->tarrif << endl;
        last = head;
        head = head->next;
    }
}

int count_tariff(NODE *head, string tarrif) {
    int count = 0;
    NODE *temp = head;
    while (temp != NULL) {
        if (temp->tarrif == tarrif) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

void delete_subscriber_by_number(NODE *head, string phone_number) {
    NODE *temp = head;
    while (temp != NULL) {
        if (temp->phone_number == phone_number) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            delete temp;
            return;
        }
        temp = temp->next;
    }
}

void change_tariff(NODE *head, string name, string new_tarrif) {
    NODE *temp = head;
    while (temp != NULL) {
        if (temp->name == name) {
            temp->tarrif = new_tarrif;
            return;
        }
        temp = temp->next;
    }
}

void deleteList(NODE *head) {
    NODE *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {

    NODE *head = NULL;
    head = addNode(head, "Ivan", "1234567", "tariff1");
    head = addNode(head, "Petro", "1234568", "tariff2");
    head = addNode(head, "Vasyl", "1234569", "tariff1");
    head = addNode(head, "Oleg", "1234570", "tariff2");
    head = addNode(head, "Ihor", "1234571", "tariff1");
    while (1) {
        int answer;
        cout << "\nhello, its vodaphone database, choose your action" << endl;
        cout << "1. add new subscriber" << endl;
        cout << "2. delete subscriber by number" << endl;
        cout << "3. change tariff" << endl;
        cout << "4. count subscribers with tariff" << endl;
        cout << "5. print all subscribers" << endl;
        cout << "6. exit" << endl;
        cin >> answer;
        switch (answer) {
            case 1: {
                string name;
                string phone_number;
                string tarrif;
                string answer;
                cout << "enter name" << endl;
                cin >> name;
                cout << "generate phone number or enter your own (gen for generate, anything else to manual" << endl;
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
                cout << count_tariff(head, tarrif) << endl;
                break;
            }
            case 5: {
                printList(head);
                break;
            }
            case 6: {
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