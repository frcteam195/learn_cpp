#include <iostream>

// namespaces allow us to have many functions with the same "signature" (name and inputs)
// but still sperating them in code

// you declare a namespace like this:
namespace add_one_namespace
{
    int add_to_input( float input ){
	return input+1;
    }
}

// you can make as many namespaces as you want
namespace add_five_namespace
{
    int add_to_input( float input ){
	return input+5;
    }
}


int main()
{
    // you use namespaces like this
    int answer_1 = add_one_namespace::add_to_input( 5 ); // this is 6
    int answer_2 = add_five_namespace::add_to_input( 5 ); // this is 10
    std::cout << answer_1 << " " << answer_2 << "\n";

    return 0;
}
