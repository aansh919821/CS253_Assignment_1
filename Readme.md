# Car Rental System Readme

## Introduction

This program is a basic car rental system with user authentication, customer functions, and manager privileges. Users interact through a console interface, performing tasks like renting cars and managing databases. Data is stored in external text files for persistence.

## Key Features

1. **User Authentication:**
   - Customers and employees log in with usernames and passwords.
   - New users can register with optional details.

2. **Functions:**
   - Customers view and rent cars, return them, and clear fines.
   - Employees have similar functions with added discounts.
   - Managers handle administrative tasks like registering users and managing the car database.

3. **Data Persistence:**
   - User, car, customer, and employee data is stored in external text files.

4. **Error Handling:**
   - Provides clear error messages.
   - Handles invalid inputs gracefully.

## Usage

1. **Compilation:**
   - Compile using a C++ compiler, e.g., `g++ car_rental_system.cpp -o car_rental_system`.

2. **Execution:**
   - Run the compiled executable: `./car_rental_system`.
   - Follow console prompts.

## File Structure

- `car_rental_system.cpp`: Main code implementing the car rental system.
- `car.txt`, `customerDatabase.txt`, `employeeDatabase.txt`: Store information.

## Assumptions and Limitations

1. Single-user environment.
2. Text files for data storage may not scale for large datasets.

   **Additional Assumptions:**
   - Usernames and ModelId are unique identifiers.
   - Single manager assumption.

## Future Enhancements

1. Implement a graphical user interface (GUI).
2. Support multiple locations and branches.

## Contributors

Developed by Ansh Agarwal for a CS253 course assignment.
