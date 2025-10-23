// COMSC-210 | Lab 24 | Mika Aquino
// IDE used: Visual Studio 2022


// INSTRUCTIONS: Convert your Lab 23 to a std::set.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
#include <iterator>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

// Functions to manage the goats in the trip
string select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    set<Goat> trip;            // Create an empty set of goats
    int choice = main_menu();   // Output a menu of choices and prompt the user for a choice

    // Execute the user's choice, and continue prompting the user for a choice until they want to quit
    while (choice != 4) { // Choice 4: quit
        // Choice 1: add a goat
        if (choice == 1) {
            add_goat(trip, names, colors);
        }
        // Choice 2: delete a goat
        else if (choice == 2) {
            delete_goat(trip);
        }
        // Choice 3: list the goats
        else if (choice == 3) {
            display_trip(trip);
        }
        cout << "\n";

        // Display the main menu again and prompt the user for a choice
        choice = main_menu();
    }

    return 0;
}

// Function to display the menu with a list of choices. It asks the user for their choice (an int).
// Args:    none
// Returns: the user's choice
int main_menu() {
    int choice;
    
    // Print the menu
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    
    // Ask the user for a choice and validate it
    do {
        cin >> choice;
        if (choice < 1 || choice > 4) {
            cout << "Invalid number. Please enter 1, 2, 3, or 4.\n";
            cout << "Choice --> ";
        }
    } while (choice < 1 || choice > 4);

    return choice;

}

// Function to allow the user to input an integer to select a goat to be deleted. It ensures that the user entered a valid integer for an existing goat.
// Args:    a list of goats
// Returns: the user's selection (an int)
string select_goat(set<Goat> trip) {
    string choice;

    display_trip(trip);

    cout << "Select a goat's name to delete.\n";
    cout << "Choice --> ";

    /*
    // Validate the user's choice
    do {
        cin >> choice;
        if (choice < 1 || choice > trip.size()) {
            cout << "Invalid number. Please enter one of the numbers from the list.\n";
            cout << "Choice --> ";
        }
    } while (choice < 1 || choice > trip.size());*/

    return choice;
}

// Function to add a random goat to the list. It selects a random name, color, and age, and uses them to create a goat that is added to the list.
// Args:    a list of goats, an array of names, an array of colors
// Returns: void
void add_goat(set<Goat>& trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];     // Randomly select a name from the array.
    string color = colors[rand() % SZ_COLORS];  // Randomly select a color from the array.
    int age = rand() % (MAX_AGE + 1);           // Randomly select an age between 0 and MAX_AGE (inclusive).

    Goat newGoat(name, age, color);             // Create a new goat using the name, age, and color.
    trip.insert(newGoat);                    // Add the new goat to the trip using set's insert() function.
    cout << "Successfully added a goat.\n";
}

// Function to delete a selected goat from the list.
// Args:    a list of goats
// Returns: void
void delete_goat(set<Goat>& trip) {
    // Return if the list is empty.
    if (trip.empty()) {
        cout << "No goats are currently in the trip.\n";
        cout << "No goats have been deleted.\n";
        return;
    }

    string name = select_goat(trip);    // Ask the user what goat to delete.

    auto it = trip.begin();             // Create an iterator at the beginning of the list.

    while (it->get_name() != name) {
        advance(it, 1);
    }

    if (it != trip.end()) {
        trip.erase(it);                 // Delete the goat using the list's erase() function with the iterator.
    }
    else {
        cout << "No goat has been found with the name " << name << ".\n";
        cout << "No goats have been deleted.\n";
    }
}

// Function to display the list of goats.
// Args:    a list of goats
// Returns: void
void display_trip(list<Goat> trip) {
    // Return if the list is empty.
    if (trip.empty()) {
        cout << "No goats are currently in the trip.\n";
        return;
    }
    
    int index = 1;
    // Traverse the list using a range-based for loop, outputting each goat's information.
    for (Goat goat : trip) {
        cout << "\t[" << index << "] " << goat.get_name() << " (" << goat.get_age() << ", " << goat.get_color() << ")\n";
        ++index;
    }
}