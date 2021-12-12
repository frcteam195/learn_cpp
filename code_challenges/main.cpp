#include <iostream>
#include <fstream>

int main(){

    std::ifstream file = std::ifstream("input.txt");

    std::string command;
    int num;
    int depth = 0;
    int horizontal = 0;

    while( file >> command >> num ){

        if( command == "forward" )
        {
            horizontal += num;
        }
        else if( command == "down" )
        {
            depth += num;
        }
        else if( command == "up" )
        {
            depth -= num;
        }

    }

    std::cout << horizontal << " " << depth
              << " " << depth*horizontal << "\n";

    return 0;
}
