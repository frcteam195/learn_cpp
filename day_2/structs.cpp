#include <iostream>
#include <vector>

// structs are a collection of other datatypes
// you can define a struct like this:
struct Student{
    int age;
    float height_meters;
    std::string name;
};

struct Classroom
{
    int classroom_number;
    std::vector<Student> students;
};

int main()
{

    // you can use a struct like this
    Student john; // just like making any other variable

    // you can set values like this
    john.name = "john";
    john.age = 19;
    john.height_meters = 1.75;

    // you can access the values liek this:
    int johns_age = john.age;

    std::cout << "Student name: " << john.name << "\n";
    std::cout << "  age: " << johns_age << "\n";
    std::cout << "  height: " << john.height_meters << "\n\n";


    // you can't print structs directly unless you do some more work (explained later)
    // std::cout << john << "\n";     //<---- this will fail


    // structs can contain other structs
    Classroom classroom_zero;
    classroom_zero.classroom_number = 0;
    classroom_zero.students.push_back( john ); // add john to this classroom

    std::cout << "first student in classroom 0: " << classroom_zero.students[0].name << "\n";


    return 0;
}
