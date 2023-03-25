#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct Student
{
	string name;
	string group;
	float age{};
};

enum Menu { NewStudents = 1, SearchName, AverageAge, Exit };

Student CreateStudent()
{
	string name;
	string group;
	float age{};

	cout << "Введите имя студента: " << endl;
	getline(cin, name);

	group = "BV211";
	cout << "Группа студента: " << group << endl;

	cout << "Введите возраст студента: " << endl;
	cin >> age;
	cin.ignore();

	return Student{ name, group, age };
}

void FillStudents(Student* students, int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		students[i] = CreateStudent();
	}
}

void PrintStudent(const Student& students)
{
	cout << "----------------------" << endl;
	cout << "Имя студента: " << students.name << endl;
	cout << "Группа: " << students.group << endl;
	cout << "Возраст: " << students.age << endl;
	cout << "----------------------" << endl;
}

void PrintStudents(Student* students, int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		cout << "№" << i + 1 << ':' << endl;
		PrintStudent(students[i]);
		cout << endl;
	}
}

bool IsExist(const char* originalString, const char* findStr)
{
	auto length = strlen(findStr);
	auto found = _strnicmp(originalString, findStr, length);

	return  found == 0;
}

void FindStudent(Student* students, int SIZE)
{
	string found_name;
	cout << "Введите часть имени для поиска:" << endl;
	getline(cin, found_name);

	for (int i = 0; i < SIZE; i++)
	{
		Student& student = students[i];

		if (!IsExist(student.name.data(), found_name.data()))
			continue;

		PrintStudent(student);
		cout << endl;
	}
}

void AverageAgeOfStudents(Student* students, int SIZE)
{
	float sum{};
	float avg{};

	for (int i = 0; i < SIZE; i++)
	{
		sum = sum + students[i].age;
	}

	avg = sum / SIZE;
	cout << "Средний возраст студентов в группе: " << avg << endl;
}

int MainMenu(Student* students, int SIZE)
{
	int point{};

	cout << "Ну, и чего дальше делаем?" << endl;
	cout << "Нажмите 1, чтобы создать новый список студентов" << endl;
	cout << "Нажмите 2, чтобы найти студента по имени" << endl;
	cout << "Нажмите 3, чтобы вычислить средний возраст студентов в группе BV211" << endl;
	cout << "Нажмите 4, чтобы покинуть программу" << endl;

	cin >> point;
	cin.ignore();

	switch (point)
	{
	case NewStudents:
		FillStudents(students, SIZE);

		system("cls");

		cout << "Список студентов: " << endl;
		PrintStudents(students, SIZE);

		MainMenu(students, SIZE);

		break;

	case SearchName:
		FindStudent(students, SIZE);
		break;

	case AverageAge:
		AverageAgeOfStudents(students, SIZE);
		break;

	case Exit:
		return 0;
		break;

	default:
		break;
	}

	return point;
}

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);

	int SIZE{};
	cout << "Введите количество студентов в группе: " << endl;
	cin >> SIZE;
	cin.ignore();

	auto students = new Student[SIZE];

	FillStudents(students, SIZE);

	system("cls");

	cout << "Список студентов: " << endl;
	PrintStudents(students, SIZE);

	MainMenu(students, SIZE);

	return 0;
}