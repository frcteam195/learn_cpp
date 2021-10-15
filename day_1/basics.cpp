// we are including the standard library here
#include <iostream>
#include <string>
#include <vector>

// this is a comment

/*
  This is a
  multiline comment
*/


int main()
{
    // BASICS
    //----------------------------------------------------------------------------------------------------

    // you can print things like this:
    std::cout << "hello world\n";
    std::cout << "numbers: " << 1 << " " << 2 << " " << 3 << "\n";

    // integers are whole numbers, they can be negetive or positive
    // eg: -1000, -1, 0, 4, 6 ....
    int var_integer = 0;

    // booleans can only be true or false
    bool var_boolean = false;

    // floats are fractional numbers
    // they can be negetive or positive
    // eg -123.05, 0.0, 1.0, 555.123
    float var_float = 1.0;

    // doubles are floats with higher precision
    double var_double = 1.0;

    // characters are a single "letter"
    // they can also be a number from [0,255]
    // single letters need to have single
    char letter = 'A';

    // you can make a string like this:
    std::string name = "john";

    // you can assign a string later like this
    name = "someone else"; // name is now "someone else"

    // you can copy the contents of 1 variable from the other using "="
    std::string var1 = "name1";
    std::string var2 = "name2";
    var1 = var2;
    // now...
    //  var1 = name2
    //  var2 = name2


    // LISTS
    // ----------------------------------------------------------------------------------------------------
    // you can make lists like this:

    // list_of_ints is a list of 5 integers
    // the contents of lis_of_ints could be anything
    int list_of_ints[5];

    // you can set the elements in lists like this
    int defined_list[5] = {1, 2, 3, 4, 5};

    // you can also set the nth elementof the lists like this

    defined_list[0] = 10; // the first element is now 10
    defined_list[2] = 15; // the third element is now 15
    defined_list[4] = 30; // the last element is now 30

    // size of lists make as displayed above cannot change
    // you can't have more than 5 elements in "list_of_ints" or "defined_list"

    // a vector is a list with dynamic size
    // you can make a vector like this:
    std::vector<int> vector_of_ints;
    // you can add items to the vecor like this:
    vector_of_ints.push_back( 1 );
    // vector of ints now has [1]
    vector_of_ints.push_back( 2 );
    // vector of ints now has [1, 2]

    // you can access the contets of the list like this
    int second_element = vector_of_ints[1];
    //second_element is "2"


    // BRANCHING
    // ----------------------------------------------------------------------------------------------------
    // you can branch using the "if" statement
    // you can compare 2 things by using these operators
    //  A == B   check if A and B are equal
    //  A != B   check if A is NOT equal to B
    //  A < B    check if A is smaller than B
    //  A <= B   check if A is smaller than or equal to B
    //  A > B    check if A is greater than B
    //  A >= B   check if A is greater than or equal to B
    // here is a simple if statement

    if( false )
    {
        std::cout << "Does not happen\n";
    }
    else if( 3 == 4 )
    {
        std::cout << "Does not happen\n";
    }
    else
    {
        std::cout << "This always happens\n";
    }

    // you can combine different comparisons using "&&" and "||" operators
    // "&&" can be translated to "AND", if both values are true it evaluates to true
    // "||" can be translated to "OR", if one of the values is true, the statement evaluates as true

    int five = 5;
    int six = 6;
    std::string name_test = "john";

    if( five == 5 && name_test == "john" )
    {
        std::cout << "This HAPPENS!\n";
    }

    if( five < 6 || name_test == "john" )
    {
        std::cout << "This HAPPENS!\n";
    }

}
