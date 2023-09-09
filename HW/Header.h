#pragma once

//structure to store employees data
struct Employee {
    char name[50];
    char lastName[50];
    char phoneNumber[20];
    double salary;
};

void PrintMenu();
void GetEmployee(Employee* employee, int i);
void SearchBySalary(Employee* employee);
void SearchByLastName(Employee* employee);
void AddEmployee(const char* filename, Employee* employee, int size);
void UpdateEmployee(const char* filename, Employee* employee);
void ShowEmployeesData(const char* filename, Employee* employee);
void SortByLastName(Employee* employee, const char* filename);
bool isCheckedPhone(char* checkPhone);
void askInform(Employee* employee, int size);
void DeleteEmployee(Employee* employee);


