#include <iostream>
#include <string>
#include <vector>


int main()
{

    // LOOPS
    //----------------------------------------------------------------------------------------------------

    // two of the most common ways to performing loops are:
    //  FOR loops
    //  While loops

    // For Loops
    // Should look like this
    //  for( start; loop_condition; loop_iteration ){ ... body here ... }

    std::cout << "\n"  << "simple FOR loop\n";

    for( int i = 0; i < 5; i++ )
    {
        std::cout << i << "\n";
    }

    // the loop_condition and loop_iteration don't need to be single statements
    std::cout << "\n"  << "more complicated FOR loop\n";

    int r = 1;
    int c = 1;
    // split multiple lines for legibility
    for( int i = 0;
         r < 10 || c < 10;
         i++, r=r*2, c+=2 )
    {
        std::cout << "i:" << i << " r:" << r << " c:" << c << "\n";
    }


    // WHILE LOOP
    // While loops need to be structed like this:
    //  while( condition ){ ...body... }
    //  the body will happen as long as the "condition" is true

    std::cout << "\n" << "simple while loop\n";
    int test = 0;
    while( test < 5 )
    {
        std::cout << test << "\n";
        test += 1;
    }

}
