#include  <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace  std;

struct  Item {
    string itemID;
    string itemName;
    int quantity;
    string registrationDate;
};

//Splitting a string using a delimiter
vector<string> split(const string &line, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

//Function to add items
void addItem(vector<Item> &items, const string &itemID, const string &itemName, const int quantity, const string &registrationDate) {
    items.push_back({itemID, itemName, quantity, registrationDate
 });
}

//Listing items in alphabetical order
void listItems(const vector<Item> &items) {
    vector<Item> sortedItems = items;
    sort(sortedItems.begin(), sortedItems.end(), [](const Item &a, const Item &b) {
        return a.itemName < b.itemName;
    });

    for (const auto &item : sortedItems) {
        cout <<"Item ID: " << item.itemID << "\t" << "Item Name: " << item.itemName << "\t" <<"Quantity: " << item.quantity << "\t" <<"Registration Date: " << item.registrationDate << endl;
    }
}

//loading items from a CSV file
vector<Item> loadItemFromCSV(const string &filename) {
    vector<Item> items;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<string> data = split(line, ',');
        if (data.size() == 5) {
            addItem(items, data[0], data[1], stoi(data[2]), data[3]);
        }
    }
    file.close();
    return items;
}

//function to process the commands

void processCommands(vector<Item> &items) {
    string command;
    while (true) {
        cout<<"Enter command (addition, listItems, exit: "<<endl;
        cin>>command;
        if (command == "addition") {
            string itemID, itemName, registrationDate;
            int quantity;
            cout<< "Enter item ID: "<<endl;
            cin>>itemID;
            cout<<"Enter Item Name: "<<endl;
            cin>>itemName;
            cout<<"Enter Quantity: "<<endl;
            cin>>quantity;
            cout<<"Enter registrationDate: "<<endl;
            cin>>registrationDate;

            addItem(items, itemID, itemName, quantity, registrationDate);
            cout<< "Item added successfully!" << endl;
        }else if (command == "listItems") {
            listItems(items);
            if (items.empty()) {
                cout<<"No items found!"<<endl;
            }
        }else if (command == "exit") {
            break;
        }else {
            cout << "Invalid command. Try again!" <<endl;
        }
    }
}

int main() {
    vector<Item> items = loadItemFromCSV(("items.csv"));
    processCommands(items);
    return 0;
}