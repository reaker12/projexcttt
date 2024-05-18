#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>
#include <algorithm> // Add this header for std::find
#include <sstream>   // Add this header for std::istringstream

using namespace std;

class PatientRecordManager {
public:
    struct PatientRecord {
        string name;
        string address;
        int age;
        char sex;
        string diseaseDescription;
        int specialistRoomNumber;
    };

private:
    vector<PatientRecord> records;

public:
    void addNewPatientRecord(string name, string address, int age, char sex, string diseaseDescription, int specialistRoomNumber, string serviceType) {
        PatientRecord record = { name, address, age, sex, diseaseDescription, specialistRoomNumber };
        records.push_back(record);
        cout << "New patient record added for " << name << " with service type: " << serviceType << endl;
    }

    const vector<PatientRecord>& getRecords() const {
        return records;
    }

    void searchOrEditPatientRecord(int recordNumber) {
        if (recordNumber >= 1 && recordNumber <= records.size()) {
            PatientRecord& record = records[recordNumber - 1];
            cout << "Record found. You can edit now." << endl;
            cout << "Current Name: " << record.name << ". Enter new name (or press Enter to keep current): ";
            string newName;
            cin.ignore();
            getline(cin, newName);
            if (!newName.empty()) record.name = newName;
            // Similar input handling for other fields can be added here
        }
        else {
            cout << "Record not found." << endl;
        }
    }

    void searchOrEditPatientRecord(string fullName) {
        for (auto& record : records) {
            if (record.name == fullName) {
                cout << "Record found. You can edit now." << endl;
                cout << "Current Name: " << record.name << ". Enter new name (or press Enter to keep current): ";
                string newName;
                cin.ignore();
                getline(cin, newName);
                if (!newName.empty()) record.name = newName;
                // Similar input handling for other fields can be added here
                return;
            }
        }
        cout << "Record not found." << endl;
    }

    void listPatientRecords(string option) {
        // This function needs more context-specific implementation details
        for (const auto& record : records) {
            cout << "Name: " << record.name << ", Address: " << record.address << ", Age: " << record.age
                << ", Sex: " << record.sex << ", Disease: " << record.diseaseDescription
                << ", Room: " << record.specialistRoomNumber << endl;
        }
    }

    void deletePatientRecord(int recordNumber) {
        if (recordNumber >= 1 && recordNumber <= records.size()) {
            records.erase(records.begin() + (recordNumber - 1));
            cout << "Record deleted." << endl;
        }
        else {
            cout << "Record not found." << endl;
        }
    }
};

class FinancialRecordManager {
private:
    struct FinancialRecord {
        double totalCharge;
        double totalDeposited;
        double totalMoneyToReturn;
    };

    unordered_map<int, FinancialRecord> records;

public:
    void displayFinancialRecords(int recordNumber) {
        auto it = records.find(recordNumber);
        if (it != records.end()) {
            cout << "Financial Records for Record Number: " << recordNumber << endl;
            cout << "Total Charge: " << it->second.totalCharge << endl;
            cout << "Total Deposited: " << it->second.totalDeposited << endl;
            cout << "Total Money to Return: " << it->second.totalMoneyToReturn << endl;
        }
        else {
            cout << "Financial Records not found for Record Number: " << recordNumber << endl;
        }
    }
};

class TreatmentManager {
private:
    unordered_map<int, string> treatments;

public:
    void addTreatment(int recordNumber, string treatmentDescription) {
        treatments[recordNumber] = treatmentDescription;
    }

    void displayTreatment(int recordNumber) {
        auto it = treatments.find(recordNumber);
        if (it != treatments.end()) {
            cout << "Treatment for Record Number: " << recordNumber << ": " << it->second << endl;
        }
        else {
            cout << "Treatment not found for Record Number: " << recordNumber << endl;
        }
    }

    void editTreatment(int recordNumber, string newTreatmentDescription) {
        if (treatments.find(recordNumber) != treatments.end()) {
            treatments[recordNumber] = newTreatmentDescription;
            cout << "Treatment updated." << endl;
        }
        else {
            cout << "Treatment not found for Record Number: " << recordNumber << endl;
        }
    }

    void deleteTreatment(int recordNumber) {
        if (treatments.erase(recordNumber)) {
            cout << "Treatment deleted." << endl;
        }
        else {
            cout << "Treatment not found for Record Number: " << recordNumber << endl;
        }
    }
};

class MedicineManager {
private:
    unordered_map<int, vector<string>> medicineLists;

public:
    void addMedicine(int recordNumber, string medicine) {
        medicineLists[recordNumber].push_back(medicine);
    }

    void displayMedicine(int recordNumber) {
        auto it = medicineLists.find(recordNumber);
        if (it != medicineLists.end()) {
            cout << "Medicines for Record Number: " << recordNumber << ": ";
            for (const auto& medicine : it->second) {
                cout << medicine << ", ";
            }
            cout << endl;
        }
        else {
            cout << "Medicines not found for Record Number: " << recordNumber << endl;
        }
    }

    void deleteMedicine(int recordNumber, string medicine) {
        auto it = medicineLists.find(recordNumber);
        if (it != medicineLists.end()) {
            auto& medicines = it->second;
            auto pos = std::find(medicines.begin(), medicines.end(), medicine);

            if (pos != medicines.end()) {
                medicines.erase(pos);
                cout << "Medicine deleted." << endl;
            }
            else {
                cout << "Medicine not found." << endl;
            }
        }
        else {
            cout << "Medicines not found for Record Number: " << recordNumber << endl;
        }
    }
};

class FileHandler {
public:
    void saveToFile(const vector<PatientRecordManager::PatientRecord>& patientRecords) {
        ofstream outFile("patient_records.txt");
        if (outFile.is_open()) {
            for (const auto& record : patientRecords) {
                outFile << record.name << "," << record.address << "," << record.age << "," << record.sex << ","
                    << record.diseaseDescription << "," << record.specialistRoomNumber << endl;
            }
            outFile.close();
            cout << "Patient records saved to file." << endl;
        }
        else {
            cout << "Unable to open file for saving patient records." << endl;
        }
    }

    void readFromFile(vector<PatientRecordManager::PatientRecord>& patientRecords) {
        ifstream inFile("patient_records.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                std::istringstream ss(line);

                string name, address, diseaseDescription;
                int age, specialistRoomNumber;
                char sex;
                getline(ss, name, ',');
                getline(ss, address, ',');
                ss >> age;
                ss.ignore();
                ss >> sex;
                ss.ignore();
                getline(ss, diseaseDescription, ',');
                ss >> specialistRoomNumber;
                patientRecords.push_back({ name, address, age, sex, diseaseDescription, specialistRoomNumber });
            }
            inFile.close();
            cout << "Patient records loaded from file." << endl;
        }
        else {
            cout << "Unable to open file for reading patient records." << endl;
        }
    }

    void updateFile(const vector<PatientRecordManager::PatientRecord>& patientRecords) {
        saveToFile(patientRecords);
    }
};

class Menu {
public:
    void displayMainMenu() {
        cout << "Hospital Management System" << endl;
        cout << "1. Add New Patient Record" << endl;
        cout << "2. Search/Edit Patient Record" << endl;
        cout << "3. List Patient Records" << endl;
        cout << "4. Delete Patient Record" << endl;
        cout << "5. Display Financial Records" << endl;
        cout << "6. Add Treatment" << endl;
        cout << "7. Display Treatment" << endl;
        cout << "8. Edit Treatment" << endl;
        cout << "9. Delete Treatment" << endl;
        cout << "10. Add Medicine" << endl;
        cout << "11. Display Medicine" << endl;
        cout << "12. Delete Medicine" << endl;
        cout << "13. Save to File" << endl;
        cout << "14. Read from File" << endl;
        cout << "15. Update File" << endl;
        cout << "16. Exit" << endl;
        cout << "Enter your choice: ";
    }

    int getUserChoice() {
        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 16) {
            cout << "Invalid option! Please enter a number between 1 and 16." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter your choice: ";
        }
        return choice;
    }

    string getServiceTypeChoice() {
        string serviceType;
        cout << "Enter service type (O.P.D. or Emergency): ";
        cin >> serviceType;
        return serviceType;
    }

    int getRecordNumberInput() {
        int recordNumber;
        cout << "Enter record number: ";
        cin >> recordNumber;
        return recordNumber;
    }

    string getFullNameInput() {
        string fullName;
        cout << "Enter full name: ";
        cin.ignore();
        getline(cin, fullName);
        return fullName;
    }

    string getListOptionChoice() {
        string option;
        cout << "Enter list option (alphabetical, emergency, opd, date): ";
        cin >> option;
        return option;
    }
};

int main() {
    PatientRecordManager patientRecordManager;
    FinancialRecordManager financialRecordManager;
    TreatmentManager treatmentManager;
    MedicineManager medicineManager;
    FileHandler fileHandler;
    Menu menu;

    int choice;
    do {
        menu.displayMainMenu();
        choice = menu.getUserChoice();

        switch (choice) {
        case 1: {
            string name, address, diseaseDescription, serviceType;
            int age, specialistRoomNumber;
            char sex;
            cout << "Enter patient details:" << endl;
            cout << "Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Address: ";
            getline(cin, address);
            cout << "Age: ";
            while (true) {
                cin >> age;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input for age. Please enter a number." << endl;
                }
                else {
                    break;
                }
            }
            cout << "Sex (M/F): ";
            while (true) {
                cin >> sex;
                if (sex == 'M' || sex == 'F') {
                    break;
                }
                else {
                    cout << "Invalid input! Please enter M or F: " << endl;
                }
            }
            cout << "Disease Description: ";
            cin.ignore();
            getline(cin, diseaseDescription);
            cout << "Specialist Room Number: ";
            cin >> specialistRoomNumber;
            serviceType = menu.getServiceTypeChoice();
            patientRecordManager.addNewPatientRecord(name, address, age, sex, diseaseDescription, specialistRoomNumber, serviceType);
            break;
        }
        case 2: {
            int recordNumber;
            cout << "Enter record number: ";
            cin >> recordNumber;
            patientRecordManager.searchOrEditPatientRecord(recordNumber);
            break;
        }
        case 3: {
            string option = menu.getListOptionChoice();
            patientRecordManager.listPatientRecords(option);
            break;
        }
        case 4: {
            int recordNumber;
            cout << "Enter record number to delete: ";
            cin >> recordNumber;
            patientRecordManager.deletePatientRecord(recordNumber);
            break;
        }
        case 5: {
            int recordNumber;
            cout << "Enter record number to display financial records: ";
            cin >> recordNumber;
            financialRecordManager.displayFinancialRecords(recordNumber);
            break;
        }
        case 6: {
            int recordNumber;
            string treatment;
            cout << "Enter record number for treatment: ";
            cin >> recordNumber;
            cout << "Enter treatment description: ";
            cin.ignore();
            getline(cin, treatment);
            treatmentManager.addTreatment(recordNumber, treatment);
            break;
        }
        case 7: {
            int recordNumber;
            cout << "Enter record number to display treatment: ";
            cin >> recordNumber;
            treatmentManager.displayTreatment(recordNumber);
            break;
        }
        case 8: {
            int recordNumber;
            string newTreatment;
            cout << "Enter record number to edit treatment: ";
            cin >> recordNumber;
            cout << "Enter new treatment description: ";
            cin.ignore();
            getline(cin, newTreatment);
            treatmentManager.editTreatment(recordNumber, newTreatment);
            break;
        }
        case 9: {
            int recordNumber;
            cout << "Enter record number to delete treatment: ";
            cin >> recordNumber;
            treatmentManager.deleteTreatment(recordNumber);
            break;
        }
        case 10: {
            int recordNumber;
            string medicine;
            cout << "Enter record number for medicine: ";
            cin >> recordNumber;
            cout << "Enter medicine: ";
            cin.ignore();
            getline(cin, medicine);
            medicineManager.addMedicine(recordNumber, medicine);
            break;
        }
        case 11: {
            int recordNumber;
            cout << "Enter record number to display medicine: ";
            cin >> recordNumber;
            medicineManager.displayMedicine(recordNumber);
            break;
        }
        case 12: {
            int recordNumber;
            string medicine;
            cout << "Enter record number to delete medicine from: ";
            cin >> recordNumber;
            cout << "Enter medicine to delete: ";
            cin.ignore();
            getline(cin, medicine);
            medicineManager.deleteMedicine(recordNumber, medicine);
            break;
        }
        case 13: {
            fileHandler.saveToFile(patientRecordManager.getRecords());
            break;
        }
        case 14: {
            vector<PatientRecordManager::PatientRecord> patientRecords;
            fileHandler.readFromFile(patientRecords);
            // Assuming the program should update the patientRecordManager with the read records
            for (const auto& record : patientRecords) {
                patientRecordManager.addNewPatientRecord(record.name, record.address, record.age, record.sex, record.diseaseDescription, record.specialistRoomNumber, "");
            }
            break;
        }
        case 15: {
            fileHandler.updateFile(patientRecordManager.getRecords());
            break;
        }
        case 16:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 16);

    return 0;
}