#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

int id = 7;
int id_employee = 42;
int fineRate = 500;
double discount = 56;

int countLinesInFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return -1; // Return -1 to indicate an error
    }

    int lineCount = 0;
    string line;
    while (getline(file, line))
    {
        lineCount++;
    }

    file.close();
    return lineCount;
}
class Car
{
private:
    string model;
    int condition;
    int rentPrice;
    bool isAvailable;
    int returnDays;
    string rentedTo;

public:
    // Public constructor to initialize Car object
    Car(const string &model, int cond, int price, bool available, const string &rentedTo, int days)
        : model(model),  condition(cond), rentPrice(price), isAvailable(available), rentedTo(rentedTo), returnDays(days) {}
    void changecondition(int cond)
    {
        condition = cond;
        rentedTo = "None";
        isAvailable = 1;
    }

    int getrentPrice()
    {
        return rentPrice;
    }

    void displayDetailsIfAvailable() const
    {
        // cout<<isAvailable;
        if (isAvailable == 1)
        {
            cout << "Model: " << model << "\n";
            cout << "Condition in number of stars: " << condition << "\n";
            cout << "Rent Price: $" << rentPrice << "\n";
            cout << "Is Available: Yes\n";
            cout << "-------------------------\n";
        }
    }
    static void displayDetails()
    {
        ifstream file("carDatabase.txt");
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string model, rentedTo;
            int price, available, days, condition;

            getline(ss, model, ',');

            char comma;
            ss >> condition >> comma >> price >> comma >> available >> comma;
            getline(ss, rentedTo, ',');
            ss >> days;
            // cout<<days<<" ";
            cout << "modelid : " << model << endl;
            cout << "condition in stars: " << condition << endl;
            cout << "price: $" << price << endl;
            cout << "available(1 for yes and 0 for no)" << available << endl;
            cout << "rented to : " << rentedTo << endl;
            cout << "--------------\n";
        }

        file.close();
        return;
    }

    bool checkAvailability() const
    {
        return isAvailable;
    }
    string getrentedTo() const
    {
        return rentedTo;
    }
    int getreturnday() const
    {
        return returnDays;
    }
    int getCondition()
    {
        return condition;
    }
    string getModel()
    {
        return model;
    }
};
class user
{
protected:
    string username;
    string password;
    string ID;

public:
    user() {}
    user(const std::string &uname, const std::string &pwd, const std::string &id)
        : username(uname), password(pwd), ID(id) {}
};

class Manager : public user
{
public:
    Manager(const std::string &uname, const std::string &pwd, const std::string &id)
        : user(uname, pwd, id) {}

    Manager() {}

    void registerNewCustomer() const;
    void registerNewEmployee() const;
    void DeleteCar(const string &filename, const string &carname);
    void delCust(const string &filename, const string &username);
    void deleteEmployee(const string &filename, const string &username);
};
void Manager::DeleteCar(const string &filename, const string &carname)
{
    ifstream inFile(filename);
    ofstream tempFile("file.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, rentedTo;
        int price, available, days, condition;

        getline(ss, model, ',');
        char comma;
        ss >> condition >> comma >> price >> comma >> available >> comma;
        getline(ss, rentedTo, ',');
        ss >> days;

        if (model == carname)
        {
            // Update the line with new information
            if (available == 0)
            {
                cout << "Car is rented so not possible to delete!";
            }
            else
                updated = true;
            continue;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("file.txt", filename.c_str());
    }
    else
    {
        remove("file.txt"); // Delete the temporary file if no update was made
    }
}

class Customer : private user
{
private:
    int fineDue;
    int customerRecord;

public:
    Customer(const string &uname, const string &pwd, const string &id,
             int fine, int record)
        : user(uname, pwd, id), fineDue(fine), customerRecord(record) {}

    Customer() {}
    string getUsername() const
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    string getID()
    {
        return ID;
    }
    int getFineDue()
    {
        return fineDue;
    }
    int getCustomerRecord()
    {
        return customerRecord;
    }
    bool authenticate(const string &enteredPassword) const
    {
        return (password == enteredPassword);
    }
    static vector<Customer> readCustomerData()
    {
        vector<Customer> customers;
        ifstream file("customerDatabase.txt");
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            Customer customer;
            getline(ss, customer.username, ',');
            getline(ss, customer.password, ',');
            getline(ss, customer.ID, ',');
            char comma;
            ss >> customer.customerRecord >> comma >> customer.fineDue;

            customers.push_back(customer);
        }

        file.close();
        return customers;
    }

    static void writeCustomerData(const vector<Customer> &customers)
    {
        ofstream file("customerDatabase.txt");
        for (size_t i = 0; i < customers.size(); ++i)
        {
            const auto &customer = customers[i];
            file << customer.username << ","
                 << customer.password << ","
                 << customer.ID << ","
                 << customer.customerRecord << ","
                 << customer.fineDue;

            // Do not write a newline character if it's the last entry
            if (i != customers.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }
};
class Employee : private user
{
private:
    int fineDue;
    int employeeRecord;

public:
    Employee(const string &uname, const string &pwd, const string &id,
             int fine, int record)
        : user(uname, pwd, id), fineDue(fine), employeeRecord(record) {}

    Employee() {}
    string getUsername() const
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    string getID()
    {
        return ID;
    }
    int getFineDue()
    {
        return fineDue;
    }
    int getemployeeRecord()
    {
        return employeeRecord;
    }
    bool authenticate(const string &enteredPassword) const
    {
        return (password == enteredPassword);
    }
    static vector<Employee> reademployeeData()
    {
        vector<Employee> employees;
        ifstream file("employeeDatabase.txt");
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            Employee employee;
            getline(ss, employee.username, ',');
            getline(ss, employee.password, ',');
            getline(ss, employee.ID, ',');
            char comma;
            ss >> employee.employeeRecord >> comma >> employee.fineDue;

            employees.push_back(employee);
        }

        file.close();
        return employees;
    }

    static void writeemployeeData(const vector<Employee> &employees)
    {
        ofstream file("employeeDatabase.txt");
        for (size_t i = 0; i < employees.size(); ++i)
        {
            const auto &employee = employees[i];
            file << employee.username << ","
                 << employee.password << ","
                 << employee.ID << ","
                 << employee.employeeRecord << ","
                 << employee.fineDue;

            // Do not write a newline character if it's the last entry
            if (i != employees.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }
};
void Manager::registerNewCustomer() const
{
    vector<Customer> customers = Customer::readCustomerData();
    cout << "Enter username: ";
    string username;
    cin >> username;

    auto it = find_if(customers.begin(), customers.end(),
                      [username](const Customer &c)
                      { return c.getUsername() == username; });

    if (it != customers.end())
    {
        cout << "This username already exists. Please try again.\n";
    }
    else
    {
        string password;
        cout << "Enter the password you want to set: ";
        cin >> password;

        string confirmPwd;
        cout << "Confirm the password that you have written above: ";
        cin >> confirmPwd;

        if (password == confirmPwd)
        {
            Customer newCustomer(username, password, to_string(id), 0, 5);
            customers.push_back(newCustomer);
            Customer::writeCustomerData(customers);
            cout << "Your registration is successful! Please log in again to continue.\n";
        }
        else
        {
            cout << "Password and Confirm Password that you have entered do not match. Your registration failed.\n";
        }
    }
}
void Manager::registerNewEmployee() const
{
    vector<Employee> Employees = Employee::reademployeeData();
    cout << "Enter username: ";
    string username;
    cin >> username;

    auto it = find_if(Employees.begin(), Employees.end(),
                      [username](const Employee &c)
                      { return c.getUsername() == username; });

    if (it != Employees.end())
    {
        cout << "This username already exists. Try Again.\n";
    }
    else
    {
        string password;
        cout << "Enter the password you want to set: ";
        cin >> password;

        string confirmPwd;
        cout << "Confirm the password that you have written above:";
        cin >> confirmPwd;

        if (password == confirmPwd)
        {
            Employee newEmployee(username, password, to_string(id_employee), 0, 5);
            Employees.push_back(newEmployee);
            Employee::writeemployeeData(Employees);
            cout << "Your registration is successful! Please log in again to continue.\n";
        }
        else
        {
            cout << "Password and Confirm Password that you have entered do not match. Your registration failed.\n";
        }
    }
}

static vector<Car> readCarData()
{
    vector<Car> cars;
    ifstream file("carDatabase.txt");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string model, rentedTo;
        int price, available, days, condition;

        getline(ss, model, ',');

        char comma;
        ss >> condition >> comma >> price >> comma >> available >> comma;
        getline(ss, rentedTo, ',');
        ss >> days;
        // cout<<days<<" ";
        Car car(model, condition, price, available, rentedTo, days);

        cars.push_back(car);
    }

    file.close();
    return cars;
}
int hasUserRentedCar(const string &filename, const string &username)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return false; // Error condition or default value
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, rentedTo;
        int price, available, days, condition;

        getline(ss, model, ',');

        char comma;
        ss >> condition >> comma >> price >> comma >> available >> comma;
        getline(ss, rentedTo, ',');
        ss >> days;

        if (rentedTo == username)
        {
            inFile.close();
            return 1;
        }
    }

    inFile.close();
    return 0;
}
void updateCarInfo(const string &filename, const string &carname, int newCondition, bool newAvailability, int returndays, const string &newrentedTo)
{
    ifstream inFile(filename);
    ofstream tempFile("file.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, rentedTo;
        int price, available, days, condition;

        getline(ss, model, ',');

        char comma;
        ss >> condition >> comma >> price >> comma >> available >> comma;
        getline(ss, rentedTo, ',');
        ss >> days;

        if (model == carname)
        {
            // Update the line with new information
            tempFile << model << "," << newCondition << "," << price << ","
                     << newAvailability << "," << newrentedTo << "," << returndays;
            updated = true;
        }
        else
        {
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (updated)
    {
        remove(filename.c_str());
        rename("file.txt", filename.c_str());
    }
    else
    {
        remove("file.txt"); // Delete the temporary file if no update was made
    }
}

void updateCustomerInfo(const string &filename, const string &username, int newCustomerRecord, int days)
{
    ifstream inFile(filename);
    ofstream tempFile("file.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int customerRecord, fineDue;
        char comma;

        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> customerRecord >> comma >> fineDue;

        if (uname == username)
        {
            tempFile << uname << "," << password << "," << id << "," << customerRecord + newCustomerRecord << "," << fineDue + fineRate * days;
            updated = true;
        }
        else
        {
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (updated)
    {
        remove(filename.c_str());
        rename("file.txt", filename.c_str());
    }
    else
    {
        remove("file.txt"); 
    }
}

void clearfinedue(const string &filename, const string &username, int amount)
{
    ifstream inFile(filename);
    ofstream tempFile("file.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int customerRecord, fineDue;
        char comma;

        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> customerRecord >> comma >> fineDue;

        if (uname == username)
        {
            tempFile << uname << "," << password << "," << id << "," << customerRecord << "," << fineDue - amount << endl;
            updated = true;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (updated)
    {
        remove(filename.c_str());
        rename("file.txt", filename.c_str());
    }
    else
    {
        remove("file.txt"); 
    }
}
void Manager ::delCust(const string &filename, const string &username)
{
    ifstream inFile(filename);
    ofstream tempFile("file.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int customerRecord, fineDue;
        char comma;

        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> customerRecord >> comma >> fineDue;

        if (uname == username)
        {
            updated = true;
            continue;
        }
        else
        {
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (updated)
    {
        remove(filename.c_str());
        rename("file.txt", filename.c_str());
    }
    else
    {
        remove("file.txt"); 
    }
}

void updateEmployeeInfo(const string &filename, const string &username, int newEmployeeRecord, int days)
{
    ifstream inFile(filename);
    ofstream tempFile("file.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int EmployeeRecord, fineDue;
        char comma;

        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> EmployeeRecord >> comma >> fineDue;

        if (uname == username)
        {
            tempFile << uname << "," << password << "," << id << "," << EmployeeRecord + newEmployeeRecord << "," << (int)((double)fineDue + (double)fineRate * days * (1 - discount));
            updated = true;
        }
        else
        {
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (updated)
    {
        remove(filename.c_str());
        rename("file.txt", filename.c_str());
    }
    else
    {
        remove("file.txt"); 
    }
}

void Manager ::deleteEmployee(const string &filename, const string &username)
{
    ifstream inFile(filename);
    ofstream tempFile("file.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int EmployeeRecord, fineDue;
        char comma;

        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> EmployeeRecord >> comma >> fineDue;

        if (uname == username)
        {
            updated = true;
            continue;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (updated)
    {
        remove(filename.c_str());
        rename("file.txt", filename.c_str());
    }
    else
    {
        remove("file.txt"); 
    }
}

int getCarCondition(const string &filename, const string &model_entering)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return -1; 
    }

    string line;
    int condition = -1; 

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, rentedTo;
        int conditionFromFile, price, available, days;

        getline(ss, model, ',');

        char comma;
        ss >> conditionFromFile >> comma >> price >> comma >> available >> comma;

        getline(ss, rentedTo, ',');
        ss >> days;

        if (model_entering == model)
        {
            condition = conditionFromFile; 
            break;                        
        }
    }

    inFile.close();
    return condition; 
}
int getCarAvailability(const string &filename, const string &model_entering)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return -1; 
    }

    string line;
    int availability = 1; 
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, rentedTo;
        int conditionFromFile, price, available, days;

        getline(ss, model, ',');
        char comma;
        ss >> conditionFromFile >> comma >> price >> comma >> available >> comma;

        getline(ss, rentedTo, ',');
        ss >> days;

        if (model_entering == model)
        {
            availability = available; 
            break;                    
        }
    }

    inFile.close();
    return availability; 
}
string getCarOwner(const string &filename, const string &model_entering)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return "\n"; 
    }

    string line;
    string owner; 
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, rentedTo;
        int conditionFromFile, price, available, days;

        getline(ss, model, ',');
        
        char comma;
        ss >> conditionFromFile >> comma >> price >> comma >> available >> comma;

        getline(ss, rentedTo, ',');
        ss >> days;

        if (model_entering == model)
        {
            owner = rentedTo; 
            break;          
        }
    }

    inFile.close();
    return owner; 
}
int getCardays(const string &filename, const string &model_entering)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return -1; 
    }

    string line;
    int returndays = 0; 
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, rentedTo;
        int conditionFromFile, price, available, days;

        getline(ss, model, ',');
        char comma;
        ss >> conditionFromFile >> comma >> price >> comma >> available >> comma;

        getline(ss, rentedTo, ',');
        ss >> days;

        if (model == model_entering)
        {
            returndays = days; 
            break;             
        }
    }

    inFile.close();
    return returndays; 
}
void addCarToFile(const string &filename, const string &model,  int condition, int rentPrice, bool isAvailable, const string &rentedTo, int days)
{
    ofstream file(filename, ios::app); 
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    file << model << "," <<  condition << "," << rentPrice << "," << isAvailable << "," << rentedTo << "," << days;

    file.close();
}
int main()
{
    vector<Car> cars = readCarData();
    vector<Customer> customers = Customer::readCustomerData();
    vector<Employee> employees = Employee::reademployeeData();
    id = customers.size() + 1;
    id_employee = employees.size() + 1;
    while (1)
    {
        cout << "Enter 1 if you are a manager, 2 if you are a employee, and 3 if you are a customer and 4 to end your query. ";
        int input_1;
        cin >> input_1;
        if (input_1 == 4)
            return 0;
        string username;
        if (input_1 == 3)
        {
            cout << "Enter Yes if you are already registered, else enter No ";
            string input_2;
            cin >> input_2;

            if (input_2 == "Yes")
            {
                cout << "Enter your username registered: ";

                cin >> username;

                vector<Customer> customers = Customer::readCustomerData();

                auto it = find_if(customers.begin(), customers.end(),
                                  [username](const Customer &c)
                                  { return c.getUsername() == username; });

                if (it != customers.end())
                {
                    cout << "Enter your password registered: ";
                    string password;
                    cin >> password;
                    cars = readCarData();

                    if (it->authenticate(password))
                    {
                        cout << "Your login is successful! Welcome, " << it->getUsername() << " to our Car Rental System.!\n";
                        cout << "Available Cars:\n";
                        for (auto &car : cars)
                        {
                            if (car.checkAvailability())
                                car.displayDetailsIfAvailable();
                        }
                        cout << "Enter the number of cars you want to return ";
                        int car_ret_no;
                        cin >> car_ret_no;
                        
                        for (int a = 0; a < car_ret_no; a++)
                        {
                            cout << "Enter Carname you want to return " << endl;
                            string carname;
                            cin >> carname;
                            int prev_condition = getCarCondition("carDatabase.txt", carname);
                            string user;
                            user = getCarOwner("carDatabase.txt", carname);
                            if (username != user)
                            {
                                cout << "You cannot return this car. You have not rented this car. \n";
                                continue;
                            }

                            cout << "Condition of returning the car(rating) " << endl;
                            int condition;

                            cin >> condition;
                            int change = condition - prev_condition;
                            cout << "Enter the duration in number of days after which you are returning the car that you have rented. " << endl;
                            int days;
                            cin >> days;
                            int rdays = getCardays("carDatabase.txt", carname);
                            int change_days = max(0, days - rdays);
                            // change required

                            updateCustomerInfo("customerDatabase.txt", username, change, change_days);
                            updateCarInfo("carDatabase.txt", carname, condition, 1, 0, "None");
                        }

                        /*Asking to rent Car*/
                        vector<Customer> customers = Customer::readCustomerData();
                        int customercheck;
                        for (auto &customer : customers)
                        {
                            if (username == customer.getUsername())
                            {
                                customercheck = customer.getCustomerRecord();
                            }
                        }
                        cars = readCarData();
                        cout << "You can rent "
                             << " " << customercheck << "  no of cars" << endl;
                        cout << "Number of Cars that you want to rent ";
                        int carRent;
                        cin >> carRent;
                        for (int a = 0; a < carRent; a++)
                        {
                            cout << "Enter CarName that you want to rent: ";
                            string carname;
                            cin >> carname;
                            if (!(getCarAvailability("carDatabase.txt", carname)))
                            {
                                cout << "This car is not available for you to rent" << endl;
                                continue;
                            }
                            int days;
                            cout << "Enter the number of days for which you want to rent this car ";
                            cin >> days;
                            int price = 0;
                            int condition = getCarCondition("carDatabase.txt", carname);
                            cout << "condition(rating) : " << condition << endl;
                            updateCarInfo("carDatabase.txt", carname, condition, 0, days, username);
                            for (auto &car : cars)
                            {
                                if (carname == car.getModel())
                                {

                                    price += days * car.getrentPrice();
                                }
                            }
                            cout << "Payable Price is " << price << endl;
                        }
                        cout << "Enter the amount by which you want to clear your fine : " << endl;
                        int amount;
                        cin >> amount;
                        clearfinedue("customerDatabase.txt", username, amount);
                    }

                    else
                    {
                        cout << "You have entered incorrect password. Please try again.\n";
                    }
                }
                else
                {
                    cout << "This username is not found/not registered. Please register.\n";
                }
            }
            else
            {
                Manager manager;
                manager.registerNewCustomer();
            }
        }
        else if (input_1 == 1)
        {
            Manager manager;
            cout << "Enter 1 to view the car database details : ";
            int input_4;
            cin >> input_4;
            if (input_4 == 1)
                Car::displayDetails();

            string input_1;
            cout << "Enter 'yes' if you want to register a new customer, else enter 'no'." << endl;

            cin >> input_1;
            if (input_1 == "yes")
                manager.registerNewCustomer();

            cout << "Enter 'yes' if you want to update the details of an existing customer, else enter 'no'." << endl;

            cin >> input_1;
            if (input_1 == "yes")
            {
                cout << "Enter the username whose details you want to update. " << endl;
                string username;
                cin >> username;
                cout << "Please provide integer value of change in the customer database. " << endl;
                int crecord;
                cin >> crecord;
                cout << "Enter the the number of days for which the customer is to be fined. " << endl;
                int days;
                cin >> days;
                updateCustomerInfo("customerDatabase.txt", username, crecord, days);
            }

            cout << "Enter yes if you want to delete a customer or no otherwise. " << endl;
            cin >> input_1;
            if (input_1 == "yes")
            {
                cout << "Please provide the username of the customer you want to delete. ";
                string username;
                cin >> username;
                if (hasUserRentedCar("carDatabase.txt", username))
                {
                    cout << "This user can't be delete as he had rented car in our Car Rental System and not returned." << endl;
                }
                else
                    manager.delCust("customerDatabase.txt", username);
            }

            cout << "Enter yes if you want to register new employee or no otherwise. " << endl;
            cin >> input_1;
            if (input_1 == "yes")
                manager.registerNewEmployee();
            cout << "Enter yes if you want to update the fields of an existing employee or no otherwise. " << endl;
            cin >> input_1;
            if (input_1 == "yes")
            {
                cout << "Enter the username of the employee whose details you want to update." << endl;
                string username;
                cin >> username;
                cout << "Please enter the integer value of change in employee record. " << endl;
                int crecord;
                cin >> crecord;
                cout << "Enter the the number of days for which the employee is to be fined. " << endl;
                int days;
                cin >> days;
                updateEmployeeInfo("employeeDatabase.txt", username, crecord, days);
            }
            cout << "Enter yes if you want to delete an employee or no otherwise. " << endl;
            cin >> input_1;
            if (input_1 == "yes")
            {
                cout << "Please provide the username of the employee you want to delete.";
                string username;
                cin >> username;
                if (hasUserRentedCar("carDatabase.txt", username))
                {
                    cout << "This user can't be delete as he had rented car in our Car Rental System and not returned." << endl;
                }
                else
                    manager.deleteEmployee("employeeDatabase.txt", username);
            }
            cout << "Enter yes if you want to add a car or no otherwise. ";
            cin >> input_1;
            if (input_1 == "yes")
            {
                cout << "Enter carname : ";
                string model;
                int rentPrice, condition;
                cin >> model;
                cout << "Enter car condition in stars : ";
                cin >> condition;
                cout << "Enter rent price : ";
                cin >> rentPrice;
                addCarToFile("carDatabase.txt", model, condition, rentPrice, 1, "None", 0);
            }
            cout << "Enter yes if you want to update any car property or no othrwise. ";
            cin >> input_1;
            if (input_1 == "yes")
            {
                cout << "Enter carname : ";
                string carname;
                cin >> carname;
                cout << "Enter new condition : ";
                int condition;
                cin >> condition;
                cout << "Enter newAvailability[0/1] : ";
                int available;
                cin >> available;
                cout << "Number of days for which car is rented : ";
                int days;
                cin >> days;
                cout << "Enter new renter: ";
                string newrentedTo;
                cin >> newrentedTo;
                updateCarInfo("carDatabase.txt", carname, condition, available, days, newrentedTo);
            }
            cout << "Enter yes if you want to delete any car or no otherwise. ";
            cin >> input_1;
            if (input_1 == "yes")
            {
                string carname;
                cout << "Enter carname : ";
                cin >> carname;
                manager.DeleteCar("carDatabase.txt", carname);
                cout << endl;
            }
        }
        else if (input_1 == 2)
        {
            cout << "Enter yes if you are already registered or no otherwise. ";
            string input_2;
            cin >> input_2;

            if (input_2 == "yes")
            {
                cout << "Enter username: ";

                cin >> username;

                vector<Employee> Employees = Employee::reademployeeData();

                auto it = find_if(Employees.begin(), Employees.end(),
                                  [username](const Employee &c)
                                  { return c.getUsername() == username; });

                if (it != Employees.end())
                {
                    cout << "Enter password: ";
                    string password;
                    cin >> password;
                    cars = readCarData();
                    if (it->authenticate(password))
                    {
                        cout << "Your login is successful! Welcome, " << it->getUsername() << "to our Car Rental System.!\n";
                        cout << "Available Cars:\n";
                        for (auto &car : cars)
                        {
                            if (car.checkAvailability())
                                car.displayDetailsIfAvailable();
                        }
                        cout << "Enter the number of cars you want to return ";
                        int car_ret_no;
                        cin >> car_ret_no;
                        for (int a = 0; a < car_ret_no; a++)
                        {
                            cout << " Enter Carname " << endl;
                            string carname;
                            cin >> carname;
                            int prev_condition = getCarCondition("Car.txt", carname);
                            string user;
                            user = getCarOwner("carDatabase.txt", carname);
                            if (username != user)
                            {
                                cout << "You cannot return this car as you have not rented this car. \n";
                                continue;
                            }

                            cout << "Condition of returning the car(rating). " << endl;
                            int condition;

                            cin >> condition;
                            int change = condition - prev_condition;
                            cout << "Enter the duration in number of days after which you are returning the car " << endl;
                            int days;
                            cin >> days;
                            int rdays = getCardays("carDatabase.txt", carname);
                            int change_days = max(0, days - rdays);
                            // change required

                            updateEmployeeInfo("Employee.txt", username, change, change_days);
                            updateCarInfo("carDatabase.txt", carname, condition, 1, 0, "None");
                        }

                        /*Asking to rent Car*/
                        vector<Employee> Employees = Employee::reademployeeData();
                        int Employeecheck;
                        for (auto &Employee : Employees)
                        {
                            if (username == Employee.getUsername())
                            {
                                Employeecheck = Employee.getemployeeRecord();
                            }
                        }
                        cars = readCarData();
                        cout << "Employee can rent "
                             << " " << Employeecheck << "  no of cars" << endl;
                        cout << "Enter the number cars you want to rent. ";
                        int carRent;
                        cin >> carRent;
                        for (int a = 0; a < carRent; a++)
                        {
                            cout << "Enter CarName ";
                            string carname;
                            cin >> carname;
                            if (!(getCarAvailability("carDatabase.txt", carname)))
                            {
                                cout << "This car is not available for rent." << endl;
                                continue;
                            }
                            int days;
                            cout << "Enter the number of days for which you want to rent the car ";
                            cin >> days;
                            int price = 0;
                            int condition = getCarCondition("Car.txt", carname);
                            cout << "condition : " << condition << endl;
                            updateCarInfo("carDatabase.txt", carname, condition, 0, days, username);
                            for (auto &car : cars)
                            {
                                if (carname == car.getModel())
                                {

                                    price += (int)((double)(1 - discount) * days * car.getrentPrice());
                                }
                            }
                            cout << "Payable Price is " << price << endl;
                        }
                        cout << "Enter amount by which you want to clear your fine : " << endl;
                        int amount;
                        cin >> amount;
                        clearfinedue("Employee.txt", username, amount);
                    }

                    else
                    {
                        cout << "You have entered incorrect password. Please try again.\n";
                    }
                }
                else
                {
                    cout << "Username not found. Please register.\n";
                }
            }
            else
            {
                Manager manager;
                manager.registerNewEmployee();
            }
        }
    }
    return 0;
}
