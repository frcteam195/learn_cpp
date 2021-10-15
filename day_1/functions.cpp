#include <iostream>
#include <string>
#include <vector>

// You can simplify and reuse your code by defining "functions"
// Functions can have many inputs, we call these "parameters"
// Functions can have only 1 output, we call this the "return value"

// Here is an example of a function that takes in a number and returns number + 5
int add_five( int input )
{
    int out = input + 5;
    return out;
}

// Functions don't have to return anything
// Here is a function that just prints something
void print_hello_world()
{
    std::cout << "Hello World\n";
}

int main()
{

    // you use functions like this
    print_hellow_world();

    // you can store the returns in other variables
    int twenty = add_five( 15 );

}
