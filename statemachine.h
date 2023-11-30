#include <iostream>
#include <map>
#include <vector>

class StateMachine 
{
private:
    std::string state;
    std::map<int, std::vector<std::string>> cases;

public:
    StateMachine(std::string stateTransTable);
    std::string prozess(std::string trigger);
    std::string getState();
};