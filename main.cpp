#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <exception>
#include <stdexcept>

using json = nlohmann::json;

class OPERATOR {
public:
    virtual double operator()(const double &, const double &) {
        return 0;
    }
};

class ADD: public OPERATOR {
public:
    double operator()(const double &x, const double &y) {
        return x+y;
    }
};

class SUB: public OPERATOR {
public:
    double operator()(const double &x, const double &y) {
        return x-y;
    }
};

class MUL: public OPERATOR {
public:
    double operator()(const double &x, const double &y) {
        return x*y;
    }
};

class DIV: public OPERATOR {
public:
    double operator()(const double &x, const double &y) {
        if (y == 0) throw std::domain_error("Division by zero.");
        return x/y;
    }
};

std::map<std::string,std::shared_ptr<OPERATOR>> create_table(void) {
// This function creates a table with the correspondance between the keyword and the function object
// It was designed in this way to facilitate the addition of new tasks.

    std::map<std::string, std::shared_ptr<OPERATOR>> m{};
   
    m["ADD"]= std::make_shared<ADD>(ADD());
    m["SUB"]= std::make_shared<SUB>(SUB());
    m["MUL"]= std::make_shared<MUL>(MUL());
    m["DIV"]= std::make_shared<DIV>(DIV());

    return m;
}

void process_file (std::string & str) {
// This function opens the files and parses the json file
// The corresponding task are dispatched by calling the corresponding object function
    
    std::ifstream input_file;
    json j;

    input_file.open (str);
    if (input_file.fail()) {
        std::cerr << "Error opening the file \"" << str << "\"." << std::endl;
        throw ("I/O Error.");
    }
    
    try{
        input_file >> j;
    } catch (json::parse_error &e) {
        std::cerr <<"Error parsing json file at byte " << e.byte << std::endl;
        throw e;
    }
    
    // Loads the table with the correspondance between the keyword and the object function
    auto m = create_table();
    
    auto vec = j["tasks"];
    if (vec.size()==0) {
        std::cerr <<"No tasks found under \"tasks\" keyword." << std::endl;        
    }

    for (const auto &x: vec) {

        double num1;
        double num2;
        std::string type;

        auto it = x.find("num1");
        if (it == x.end()) {
            std::cerr << "Operand \"num1\" not found." << std::endl;
            throw std::invalid_argument("Operand \"num1\" not found.");
        } else 
            num1 = x["num1"];;

        it = x.find("num2");
        if (it == x.end()) {
            std::cerr << "Operand \"num2\" not found." << std::endl;
            throw std::invalid_argument("Operand \"num2\" not found.");
            
        } else 
           num2 = x["num2"];

        it = x.find("type");
        if (it == x.end()) {
            std::cerr << "Task type \"type\" not found." << std::endl;
            throw std::invalid_argument("Task type \"type\" not found.");            
        } else 
            type = x["type"];

        try {
            // Calls the function object corresponding to the keyword
            std::cout << (*m.at(type))(num1, num2) << " " << std::endl;

        } catch (std::out_of_range &e) {
            std::cerr << "Operation " << type << " not defined in the set of tasks." << std::endl;
            throw std::invalid_argument("Invalid task name.");            
        } catch (std::domain_error &e) {
            std::cerr << "Error found while processing " << type << ". " << e.what() << std::endl;
            throw e;           
        } catch (std::exception &e) {
            std::cerr << "Error while processing the task file." << e.what() << std::endl;
            throw e;
        }
    }
}

int main(int argc, char **argv) {

    if (argc!=2) {
        std::cerr << "Error in the number of arguments." << std::endl;
        std::cerr << "Usage: ./task-scheduler \"filename\"" << std::endl;
        return 1;
    }
    std::string str = argv[1];
    try {    
        process_file(str);
    } catch (std::exception &e) {
        std::cerr << "Program stopped due to an error." << std::endl;
    }
    return 0;
}