#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Car structure to hold car details
struct Car {
    string plateNumber;
    string model;

    Car(string plate, string mdl) : plateNumber(plate), model(mdl) {}
};

// ParkingLot class for the automatic parking system
class ParkingLot {
private:
    vector<bool> parkingSlots;    // Tracks whether a parking slot is occupied (true means occupied)
    int totalSlots;               // Total number of parking slots

public:
    // Constructor to initialize parking lot with given total slots
    ParkingLot(int total) : totalSlots(total) {
        parkingSlots.resize(total, false);  // Initially all slots are empty (false)
    }

    // Function to check if a slot is available and reserve it
    bool reserveSlot(int slotNumber, const Car& car) {
        if (slotNumber < 1 || slotNumber > totalSlots) {
            cout << "Invalid slot number!" << endl;
            return false;
        }

        if (parkingSlots[slotNumber - 1]) {  // If the slot is already occupied
            cout << "Sorry, Slot " << slotNumber << " is already reserved!" << endl;
            return false;
        }

        // Reserve the slot
        parkingSlots[slotNumber - 1] = true;
        cout << "Car " << car.plateNumber << " has successfully reserved slot " << slotNumber << endl;
        return true;
    }

    // Function to show parking lot status
    void showStatus() {
        cout << "\nParking Lot Status: \n";
        for (int i = 0; i < totalSlots; ++i) {
            if (parkingSlots[i]) {
                cout << "Slot " << i + 1 << " is reserved.\n";
            } else {
                cout << "Slot " << i + 1 << " is available.\n";
            }
        }
    }

    // Function to check if the user is trying to reserve more than one slot
    bool isSlotAlreadyReserved(int slotNumber) {
        if (parkingSlots[slotNumber - 1]) {
            return true;
        }
        return false;
    }
};

int main() {
    // Create a parking lot with 50 slots
    ParkingLot lot(50);

    string plate, model;
    int slotNumber;

    // Store reserved cars' plate numbers to prevent multiple reservations by one person
    vector<string> reservedCars;

    while (true) {
        cout << "\nEnter car details to reserve a parking slot (or type 'exit' to quit):\n";
        
        // Get plate number
        cout << "Enter plate number: ";
        cin >> plate;

        if (plate == "exit") {
            break;
        }

        // Check if this plate has already reserved a slot
        bool alreadyReserved = false;
        for (size_t i = 0; i < reservedCars.size(); ++i) {
            if (reservedCars[i] == plate) {
                alreadyReserved = true;
                break;
            }
        }

        if (alreadyReserved) {
            cout << "You cannot reserve more than one slot. You already have a reserved slot!" << endl;
            continue;
        }

        // Get model of the car
        cout << "Enter car model: ";
        cin >> model;

        // Create a car object
        Car car(plate, model);

        // Get the slot number the user wants to reserve
        cout << "Enter the slot number you want to reserve (1 to 50): ";
        cin >> slotNumber;

        // Check if the slot is available and reserve it
        if (lot.reserveSlot(slotNumber, car)) {
            // Add the plate number to the list of reserved cars
            reservedCars.push_back(plate);
        }

        // Show current parking lot status
        lot.showStatus();
    }

    return 0;
}

