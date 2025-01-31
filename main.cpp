#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

struct Item {
    string itemID;
    string itemName;
    int quantity;
    string registrationDate;
};

string toLowercase(const string &str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Splitting a string using a delimiter
vector<string> split(const string &line, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to add items and save them to the CSV file
void addItem(const string &fileName, const string &itemID, const string &itemName, const int quantity, const string &registrationDate) {
    ofstream file(fileName, ios::app);
    if (file.is_open()) {
        file << itemID << "," << itemName << "," << quantity << "," << registrationDate << "\n";
        file.close();
        cout << "Item added successfully to CSV!" << endl;
    } else {
        cout << "File could not be opened!" << endl;
    }
}

// Listing items in alphabetical order by item name
void listItems(const vector<Item> &items) {
    if (items.empty()) {
        cout << "No items found!" << endl;
        return;
    }

    vector<Item> sortedItems = items;
    sort(sortedItems.begin(), sortedItems.end(), [](const Item &a, const Item &b) {
        return a.itemName < b.itemName;
    });

    for (const auto &item : sortedItems) {
        cout << "Item ID: " << item.itemID << "\t"
             << "Item Name: " << item.itemName << "\t"
             << "Quantity: " << item.quantity << "\t"
             << "Registration Date: " << item.registrationDate << endl;
    }
}

// Loading items from a CSV file
vector<Item> loadItemFromCSV(const string &fileName) {
    vector<Item> items;
    ifstream file(fileName);
    string line;

    while (getline(file, line)) {
        vector<string> data = split(line, ',');
        if (data.size() == 4) { // Expecting 4 fields: itemID, itemName, quantity, registrationDate
            items.push_back({data[0], data[1], stoi(data[2]), data[3]});
        }
    }
    file.close();
    return items;
}

void displayHelp() {
    cout << "Command syntaxes:\n";
    cout << "    itemadd <item_id> <item_name> <quantity> <registration_date>\n";
    cout << "    itemslist\n";
    cout << "    help\n";
    cout << "    exit\n";
}

// Function to process commands
void processCommands(const string &fileName, vector<Item> &items) {
    string command;
    while (true) {
        cout << "\nEnter command (itemadd, itemslist, help, exit): ";
        cin >> command;
        command = toLowercase(command);

        if (command == "itemadd") {
            string itemID, itemName, registrationDate;
            int quantity;

            cout << "Enter Item ID: ";
            cin >> itemID;
            cout << "Enter Item Name: ";
            cin >> itemName;
            cout << "Enter Quantity: ";
            cin >> quantity;
            cout << "Enter Registration Date: ";
            cin >> registrationDate;

            itemName = toLowercase(itemName);
            registrationDate = toLowercase(registrationDate);

            // Add the item to the CSV file and vector
            addItem(fileName, itemID, itemName, quantity, registrationDate);
            items.push_back({itemID, itemName, quantity, registrationDate});
        } else if (command == "itemslist") {
            listItems(items);
        } else if (command == "help") {
            displayHelp();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command. Try again!" << endl;
        }
    }
}

// Main function
int main() {
    const string fileName = "items.csv";
    vector<Item> items = loadItemFromCSV(fileName);
    processCommands(fileName, items);
    return 0;
}