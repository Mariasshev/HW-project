#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include "Header.h"

using namespace std;
int index = 0;   //to show amount of employees
const int MaxSize = 100;  //max amount
errno_t code;


void delayPrint(string str, int delay)
{
    for (int i = 0; str[i] != 0; i++)
    {
        cout << str[i];
        Sleep(delay);
    }
}

void red()
{
    printf("\033[1;31m");
}
void green() {
    printf("\033[1;32m");
}
void white()
{
    printf("\033[1;37m");
}
void yellow()
{
    printf("\033[1;33m");
}
void blue()
{
    printf("\033[1;34m");
}
void turquoise()
{
    printf("\033[1;36m");
}

int main()
{
    setlocale(LC_ALL, "");
    Employee* employee = new Employee[MaxSize];
    delayPrint("Welcome to ", 35);
    blue();
    delayPrint("Employee Management System\n\n ", 35);
    white();
    int userAction;
    const char* filename = "employee.txt";
    bool repeat = false;

    do {
        PrintMenu();
        white();
        delayPrint("Enter your choice\n ", 35);
        blue();
        cout << "(your answer): ";
        white();
        cin >> userAction;
        switch (userAction) {
        case 1:
            int amount;
            cout << "Enter amount of employees you need to add: ";
            cin >> amount;
            askInform(employee, amount);    //function to get data about employee(s)
            AddEmployee(filename, employee, amount);    //function to write data to a file
            break;
        case 2:
            DeleteEmployee(employee);
            AddEmployee(filename, employee, index);
            break;
        case 3:
            UpdateEmployee(filename, employee);
            AddEmployee(filename, employee, index);
            break;
        case 4:
            ShowEmployeesData(filename, employee);
            break;
        case 5:
            SortByLastName(employee, filename);
            break;
        case 6:
            SearchBySalary(employee);
            break;
        case 7:
            SearchByLastName(employee);
            break;
        case 8:
            delayPrint("The program is exiting", 20);
            delayPrint("...", 20);
            break;
        default:
            delayPrint("Incorrect choice, try again\n ", 35);
            cout << endl;
            break;
        }
        if (userAction == 9) {
            break;
        }
        else {
            delayPrint("Continue?\n[1] - yes\t[0] - no\n", 35);
            cout << endl;
            blue();
            cout << "(your answer): ";
            white();
            cin >> repeat;
        }

    } while (repeat);

    return 0;
}

//Function to print menu
void PrintMenu() {
    turquoise();
    delayPrint("[1] - Add Employee\n ", 5);

    yellow();
    delayPrint("[2] - Delete Employee\n ", 5);

    turquoise();
    delayPrint("[3] - Update Employee Data\n ", 5);

    yellow();
    delayPrint("[4] - Display All Employees\n ", 5);

    turquoise();
    delayPrint("[5] - Sort Employees by Lastname\n ", 5);

    yellow();
    delayPrint("[6] - Search Employees by Salary\n ", 5);

    turquoise();
    delayPrint("[7] - Search Employees by Lastname\n ", 5);

    red();
    delayPrint("[8] - Exit\n ", 35);
    cout << endl;
}

//function to show eployee(s) by criterias (salary, last name)
void GetEmployee(Employee* employee, int i) {

    cout << "Name: " << employee[i].name << endl;
    cout << "Surname: " << employee[i].lastName << endl;
    cout << "Phone number: " << employee[i].phoneNumber << endl;
    cout << "Salary: " << employee[i].salary << endl << endl;
}

//function to search employee(s) in list by salary
void SearchBySalary(Employee* employee) {
    //check
    if (index == 0)
    {
        cout << "List is empty!" << endl;
    }
    else {
        int salary;
        bool check = false;
        cout << "Enter emplyee`s salary: ";
        cin >> salary;

        for (int i = 0; i < index; i++)
        {
            if (salary == employee[i].salary)
            {
                GetEmployee(employee, i);
                check = true;

            }
        }
        if (!check)
        {
            cout << "Incorrect salary" << endl;
        }
    }

}

//function to search employee(s) in list by last name
void SearchByLastName(Employee* employee) {
    //check
    if (index == 0)
    {
        cout << "List is empty!" << endl;
    }
    else {
        char lastName[20];
        bool check = false;
        cout << "Enter emplyee`s surname: ";
        cin.ignore();
        cin.getline(lastName, sizeof(lastName) + 1);
        for (int i = 0; i < index; i++)
        {
            if (strcmp(lastName, employee[i].lastName) == 0)
            {
                GetEmployee(employee, i);
                check = true;
            }
        }

        if (!check) {
            cout << "Incorrect surname" << endl;
        }
    }
}

//function to add employee(s) to list
void AddEmployee(const char* filename, Employee* employee, int size)
{
    FILE* employeeData;
    employeeData = fopen(filename, "w");
    if (employeeData == 0)
    {
        cout << "Error opening file\n";
    }
    else
    {
        for (int i = 0; i < size; i++) {
            fprintf(employeeData, "Name: %s \n", employee[i].name);
            fprintf(employeeData, "Last name: %s \n", employee[i].lastName);
            fprintf(employeeData, "Phone number: %s \n", employee[i].phoneNumber);
            fprintf(employeeData, "Salary: %lf \n\n", employee[i].salary);
        }
        cout << "Data saved! " << endl;
        fclose(employeeData);
        printf("Employee data loaded to file successfully!\n");
    }
}


//function to update(change) employee`s information
void UpdateEmployee(const char* filename, Employee* employee) {
    FILE* employeeData;
    employeeData = fopen(filename, "w");        //use mode "a" to add employees to the list (not to overwrite list)
    if (employeeData == 0)
    {
        cout << "Error opening file\n";
    }
    else
    {
        char name[20];
        bool flag = 0;
        cout << "Enter emplyee`s name: ";
        cin.ignore();
        cin.getline(name, sizeof(name) + 1);
        for (int i = 0; i < index; i++)
        {
            if (strcmp(name, employee[i].name) == 0)
            {
                flag = 1;
                int answer;
                cout << "Change:\n[1] - name\n[2] - lastname\n[3] - phone\n[4] - salary\n";
                cin >> answer;

                switch (answer)
                {
                case 1:
                    cout << "Enter new name: ";
                    cin.ignore();
                    cin.getline(employee[i].name, sizeof(employee[i].name));
                    cout << "Name changed!" << endl;
                    break;
                case 2:
                    cout << "Enter new lastname: ";
                    cin.ignore();
                    cin.getline(employee[i].lastName, sizeof(employee[i].lastName));
                    cout << "Surname changed!" << endl;
                    break;
                case 3:
                    cout << "Enter new phone number: ";
                    cin.ignore();
                    cin.getline(employee[i].phoneNumber, sizeof(employee[i].phoneNumber));
                    cout << "Phone number changed!" << endl;
                    break;
                case 4:
                    cout << "Enter new salary: ";
                    cin >> employee[i].salary;
                    cout << "Phone number changed!" << endl;
                    break;
                default:
                    cout << "Incorrect number" << endl;
                    break;
                }
            }
        }
        if (!flag)
        {
            cout << "There is not such name :(  " << endl;
        }
        fclose(employeeData);
    }
}

//function to show all employees
void ShowEmployeesData(const char* filename, Employee* employee) {
    FILE* employeeData;
    code = fopen_s(&employeeData, filename, "r");
    if (!code)
    {
        char c;
        while ((c = fgetc(employeeData)) != EOF)
            cout << c;
    }
    else {
        cout << "Something wet wrong :(" << endl;
    }
    fclose(employeeData);
}

void SortByLastName(Employee* employee, const char* filename) {
    //check
    if (index == 0)
    {
        cout << "List is empty!" << endl;
    }
    else {
        for (size_t i = 0; i < index - 1; i++)
        {
            for (int j = 0; j < index - 1 - i; j++) {
                if (strcmp(employee[j].lastName, employee[j + 1].lastName) > 0) {
                    Employee change = employee[j];
                    employee[j] = employee[j + 1];
                    employee[j + 1] = change;
                }
            }
        }
        AddEmployee(filename, employee, index);
    }

}

//function to check phone
bool isCheckedPhone(char* checkPhone) {
    int size = 0;
    while (checkPhone[size] != '\0')
    {
        if (!isdigit(checkPhone[size]))
        {
            return false;
        }
        size++;
    }

    if (size == 10)
    {
        return true;
    }
    else {
        return false;
    }

}


//function to ask employee`s data 
void askInform(Employee* employee, int size)
{
    if (index < MaxSize)
    {
        for (int i = 0; i < size; i++)
        {
            Employee newEmployee;

            //name + lastname 
            cin.ignore();
            cout << "Name: ";
            cin.getline(newEmployee.name, sizeof(newEmployee.name));
            cout << "Surname: ";
            cin.getline(newEmployee.lastName, sizeof(newEmployee.lastName));

            //phone
            char checkPhone[12];
            do {
                cout << "Phone number (for exp. 012 345 67 89): ";
                cin.getline(checkPhone, sizeof(checkPhone));
                if (!isCheckedPhone(checkPhone))
                {
                    cout << "Wrong number, try again" << endl;
                }

            } while (!isCheckedPhone(checkPhone));
            strcpy_s(newEmployee.phoneNumber, checkPhone);

            //salary
            cout << "Salary: ";
            cin >> newEmployee.salary;
            cout << endl;
            employee[index] = newEmployee;
            index++;
        }
    }
    else
    {
        cout << "List is full!" << endl;
    }
}

//function to delete employee
void DeleteEmployee(Employee* employee)
{
    char lastname[20];
    int empIndex = -1;
    cout << "Enter employee`s lastname: ";
    cin.ignore();
    cin.getline(lastname, sizeof(lastname));

    int check;
    cout << "Delete employee?\n[1] - yes\n[2] - no\n";
    cin >> check;
    switch (check)
    {
    case 1:
        for (int i = 0; i < index; i++) {
            if (strcmp(employee[i].lastName, lastname) == 0)
            {
                empIndex = i;
                break;
            }
        }
        if (empIndex != -1) {
            for (int i = empIndex; i < index - 1; i++)
            {
                employee[i] = employee[i + 1];
            }
            index--;
            cout << "Data deleted successfully" << endl;
        }
        else {
            cout << "Incorrect lastname" << endl;
        }
        break;
    case 2:
        cout << "Delete is canceled" << endl;
    default:
        cout << "Incorrect answer" << endl;
        break;
    }

}