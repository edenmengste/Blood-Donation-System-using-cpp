//Here is the code for our program    

#include <iostream>
#include <string>

using namespace std;

// Constants for the maximum number of donors and blood inventory types
const int MAX_DONORS = 100; // Maximum number of donors that can be registered
const int MAX_BLOOD_INVENTORY = 8; // Number of different blood types
const int INITIAL_BLOOD_AMOUNT = 50; // Initial amount of each blood type in the inventory
const int MAX_BLOOD_CAPACITY = 100; // Maximum capacity for each blood type in the inventory

// Function to check if a given blood type is valid
bool isValidBloodType(const string& bloodType) {
    // Array of valid blood types
    const string validBloodTypes[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    // Check if the input blood type matches any of the valid types
    for (const string& type : validBloodTypes) {
        if (bloodType == type) {
            return true; // Return true if a match is found
        }
    }
    return false; // Return false if no match is found
}

int main() {
    // Structure to hold donor information
    struct Donor {
        string name; // Donor's name
        int age; // Donor's age
        string bloodType; // Donor's blood type
    };

    // Structure to hold blood inventory information
    struct BloodInventory {
        string bloodType; // Type of blood
        int quantity; // Quantity of blood in units
    };

    // Array to hold registered donors
    Donor donors[MAX_DONORS];
    // Initialize the blood inventory with initial amounts
    BloodInventory inventory[MAX_BLOOD_INVENTORY] = {
        {"A+", INITIAL_BLOOD_AMOUNT},
        {"A-", INITIAL_BLOOD_AMOUNT},
        {"B+", INITIAL_BLOOD_AMOUNT},
        {"B-", INITIAL_BLOOD_AMOUNT},
        {"AB+", INITIAL_BLOOD_AMOUNT},
        {"AB-", INITIAL_BLOOD_AMOUNT},
        {"O+", INITIAL_BLOOD_AMOUNT},
        {"O-", INITIAL_BLOOD_AMOUNT}
    };

    int donorCount = 0; // Counter for the number of registered donors
    int choice; // Variable to store user menu choice

    // Main loop for the blood donation system
    do {
        // Display the main menu
        cout << "\nWelcome to our Blood Donation system" << endl;
        cout << "1. Register Donor" << endl;
        cout << "2. Request Blood" << endl;
        cout << "3. Admin Access" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice; // Get user choice

        switch (choice) {
            case 1: { // Register Donor
                // Check if the donor list is full
                if (donorCount >= MAX_DONORS) {
                    cout << "Donor list is full!" << endl;
                    break; // Exit the case if full
                }

                // Prompt for donor name
                start:
                cout << "Enter donor name: ";
                cin >> donors[donorCount].name;

                // Input validation for name (should not contain numbers)
                for (char c : donors[donorCount].name) {
                    if (isdigit(c)) {
                        cout << "Invalid input! Name should not contain numbers." << endl;
                        goto start; // Exit the program or handle as needed
                    }
                }
// Input validation for age
                cout << "Enter donor age: ";
                while (true) {
                    cin >> donors[donorCount].age; // Get donor age
                    // Check for valid age input
                    if (cin.fail() || donors[donorCount].age < 0) {
                        cout << "Invalid input! Please enter a valid age (positive number): ";
                        cin.clear(); // Clear the error flag
                        cin.ignore(10000, '\n'); // Discard invalid input
                    } else {
                        break; // Valid input
                    }
                }

                // Input validation for blood type
                cout << "Enter blood type (e.g., A+, B-, O+): ";
                while (true) {
                    cin >> donors[donorCount].bloodType; // Get blood type
                    // Check if the blood type is valid
                    if (!isValidBloodType(donors[donorCount].bloodType)) {
                        cout << "Invalid input! Please enter a valid blood type (A+, A-, B+, B-, AB+, AB-, O+, O-/Use capital letters/): ";
                    } else {
                        break; // Valid input
                    }
                }

 donorCount++; // Increment the donor count
                cout << "Donor registered successfully!" << endl; // Confirmation message
                break; // Exit the case
            }
            case 2: { // Request Blood
                string bloodType; // Variable to store requested blood type
                cout << "Enter blood type needed (e.g., A+, B-, O+): ";
                cin >> bloodType; // Get blood type needed

                // Validate the requested blood type
                if (!isValidBloodType(bloodType)) {
                    cout << "Invalid input! Please enter a valid blood type (A+, A-, B+, B-, AB+, AB-, O+, O- /Use Capital letters/): " << endl;
                    break; // Exit the case if invalid
                }

                bool found = false; // Flag to check if blood type is found
                // Search for the requested blood type in the inventory
                for (int i = 0; i < MAX_BLOOD_INVENTORY; i++) {
                    if (inventory[i].bloodType == bloodType) {
                        // Check if the requested blood type is available
                        if (inventory[i].quantity > 0) {
                            cout << "Blood type " << bloodType << " is available. " << endl;
                            cout << "Blood requested successfully!" << endl;
                            inventory[i].quantity--; // Decrease the quantity by 1
                        } else {
                            cout << "Sorry, blood type " << bloodType << " is out of stock." << endl; // Out of stock message
                        }
                        found = true; // Set found flag to true
                        break; // Exit the loop
                    }
                }
                // If blood type is not found in inventory
                if (!found) {
                    cout << "Blood type " << bloodType << " not found in inventory." << endl;
                }
                break; // Exit the case
            }
            case 3: { // Admin Access
                string adminPassword = "admin123"; // Simple password for admin access
                string inputPassword; // Variable to store input password
                cout << "Enter admin password: ";
                cin >> inputPassword; // Get admin password

                // Check if the entered password is correct
                if (inputPassword == adminPassword) {
                    int adminChoice; // Variable to store admin menu choice
                    do {
                        // Display the admin menu
                        cout << "\nAdmin Menu" << endl;
                        cout << "1. Add Blood to Inventory" << endl;
                        cout << "2. View Blood Inventory" << endl;
                        cout << "3. View Donors" << endl; // Option to view registered donors
                        cout << "4. Exit Admin Menu" << endl;
                        cout << "Enter your choice: ";
                        cin >> adminChoice; // Get admin choice

                        switch (adminChoice) {
                            case 1: { // Add Blood to Inventory
                                string bloodType; // Variable to store blood type to add
                                int amount; // Variable to store amount to add
                                cout << "Enter blood type to add (e.g., A+, B-, O+): ";
                                cin >> bloodType; // Get blood type to add

                                // Input validation for blood type
                                while (!isValidBloodType(bloodType)) {
                                    cout << "Invalid input! Please enter a valid blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
                                    cin >> bloodType; // Get valid blood type
                                }

                                // Input validation for quantity to add
                                cout << "Enter quantity to add: ";
                                while (true) {
                                    cin >> amount; // Get quantity to add
                                    // Check for valid quantity input
                                    if (cin.fail() || amount < 0) {
                                        cout << "Invalid input! Please enter a valid quantity (positive number): ";
                                        cin.clear(); // Clear the error flag
                                        cin.ignore(10000, '\n'); // Discard invalid input
                                    } else {
                                        break; // Valid input
                                    }
                                }

                                // Search for the blood type in the inventory
                                for (int i = 0; i < MAX_BLOOD_INVENTORY; i++) {
                                    if (inventory[i].bloodType == bloodType) {
                                        // Check if adding the amount exceeds the maximum capacity
                                        if (inventory[i].quantity + amount <= MAX_BLOOD_CAPACITY) {
                                            inventory[i].quantity += amount; // Add the amount to the inventory
                                            cout << "Added " << amount << " units of " << bloodType << " to inventory." << endl;
                                        } else {
                                            cout << "Cannot add blood. Maximum capacity for " << bloodType << " reached!" << endl; // Capacity reached message
                                        }
                                        break; }
                                }
                                break; // Exit the case
                            }
                            case 2: { // View Blood Inventory
                                // Display current blood inventory
                                cout << "Current Blood Inventory:" << endl;
                                for (int i = 0; i < MAX_BLOOD_INVENTORY; i++) {
                                    cout << "Blood Type: " << inventory[i].bloodType
                                         << ", Quantity: " << inventory[i].quantity << endl; // Show blood type and quantity
                                }
                                break; // Exit the case
                            }
                            case 3: { // View Donors
                                // Check if there are registered donors
                                if (donorCount == 0) {
                                    cout << "No donors registered." << endl; // No donors message
                                    break; // Exit the case
                                }

// Display list of registered donors
                                cout << "List of registered donors:" << endl;
                                for (int i = 0; i < donorCount; i++) {
                                    cout << "Donor " << (i + 1) << ": " << donors[i].name
                                         << ", Age: " << donors[i].age
                                         << ", Blood Type: " << donors[i].bloodType << endl; // Show donor details
                                }
                                break; // Exit the case
                            }
                            case 4:
                                cout << "Exiting Admin Menu." << endl; // Exit message
                                break; // Exit the case
                            default:
                                cout << "Invalid choice! Please try again." << endl; // Invalid choice message
                        }
                    } while (adminChoice != 4); // Loop until admin chooses to exit
                } else {
                    cout << "Incorrect password! Access denied." << endl; // Access denied message
                }
                break; // Exit the case
            }
            case 4: // Exit
                cout << "Exiting the system. Thank you!" << endl; // Exit message
                break; // Exit the case
            default:
                cout << "Invalid choice! Please try again." << endl; // Invalid choice message
        }
    } while (choice != 4); // Loop until user chooses to exit
    return 0;
    }
