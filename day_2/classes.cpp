#include <iostream>
#include <vector>


// Explaining classes here...
class Furniture{

// Anything in here is public and can be access by things outside of this class
public:

    // Constructor, called whenever we make a new Furniture instance
    Furniture(){
	std::cout << "Created a Furniture\n";

	// we need to set our instance variables here, leaving them undefined can lead to issuies
	material = "undefined";
	cost_to_produce = 0;
	is_sold = false;
	sold_for = 0;
    }

    // Destructor, called whenever a Furniture instance is destroyed
    ~Furniture(){
	std::cout << "Destroyed a Furniture\n";
    }

    void set_material( std::string mat_in ){
	material = mat_in;
    }

    float get_profit(){
	return calculate_profit();
    }

    void set_cost( float amount ){
	cost_to_produce = amount;
    }

    void sell( float amount ){
	is_sold = true;
	sold_for = amount;
    }

    // these are public instance variables
    std::string material;
    float cost_to_produce;
    bool is_sold;
    float profit;
    float sold_for;

// Anything in here can only be access from within this class
private:

    float calculate_profit(){
	return sold_for - cost_to_produce;
    }
};



// ----------------------------------------------------------------------------------------------------



// Classes can derive features from another class (more than once if desired)
// you can make a class derive from another like this

class Chair : public Furniture{
public:
    Chair(){
	std::cout << "Created a chair\n";
	is_chair_stool = false;
    }

    // Chair has the funcitons in it's parent class "Furniture"

    // Chair can also have extra functions and variable
    void set_is_stool( bool _is_stool ){
	is_chair_stool = _is_stool;
    }

    bool is_stool(){
	return is_chair_stool;
    }

private:
    bool is_chair_stool;
};



int main(){

    Furniture wood_furniture;
    wood_furniture.set_material( "wood" );
    wood_furniture.set_cost(200);
    wood_furniture.sell(500);
    std::cout << "wood furniture made: " << wood_furniture.get_profit() << "\n";


    std::cout << "---- \n";
    Chair chair_furniture;
    chair_furniture.set_material( "wood" );
    chair_furniture.set_cost(100);
    chair_furniture.sell(350);
    chair_furniture.set_is_stool(false);
    std::cout << "chair furniture made: " << chair_furniture.get_profit() << "\n";
    std::cout << "  is chair a stool? : " << chair_furniture.is_stool() << "\n";

    std::cout << "---- \n";

    return 0;
}
