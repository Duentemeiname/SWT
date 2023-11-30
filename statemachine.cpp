#include <iostream>
#include <sstream>
#include "statemachine.h"

StateMachine::StateMachine(std::string value)
{
    this->state = "ledig";
    // Durchlaufe Zeichenkette
    std::istringstream inputStream(value);

    // Speicher 
    std::string line;

    int y = 0;
    // Durchlaufe jede Zeile
    while (std::getline(inputStream, line)) 
    {
        int i = 0;
        for (char c : line)
        {
            if (c == ',') 
            {
                i++;
                if (i > 2)
                {
                    throw std::runtime_error("Es wurden zu viele Argumente übergeben: " + line);
                }
            }
        }
        if (i < 2)
        {
            throw std::runtime_error("Es wurden zu wenige Argumente übergeben: " + line);
        }

        // Durchlaufe String 
        std::istringstream lineStream(line);

        // Zwischenspeicher 
        std::string array[3]; 

        for (int i = 0; i < 3; i++) 
        {
            if (!(std::getline(lineStream, array[i], ',')))
            {
                if (i == 0 && line.empty())
                {
                    break;
                }
                else
                {
                    throw std::runtime_error("Fehler beim Lesen des Strings " + line);
                }
            }
        }

        cases[y].push_back(array[0]);
        cases[y].push_back(array[1]);
        cases[y].push_back(array[2]);

        y= y+1;
    }
    std::cout<<"Klasse erfolgreich gebaut"<<std::endl;
}
std::string StateMachine::prozess(std::string value)
{
    for (auto it = cases.begin(); it != cases.end(); it++)
    {
        std::vector<std::string>& values = it->second;

        if(value == values[1] && state == values[0])
        {
            this->state = values[2];
            std::cout << "Wechsel erfolgreich" << std::endl;
            return values[2];
        }
    }
    throw std::runtime_error("Dieser Wechsel ist nicht möglich!");
}

std::string StateMachine::getState()
{
    return this->state;
}

int main()
{
    try
    {
        std::cout<<"Test 1 - Build Class"<<std::endl;
        StateMachine test(" ,,ledig\nledig,Hochzeit,verheiratet\nverheiratet,Scheidung,geschieden\ngeschieden,Hochzeit,verheiratet\nverheiratet,PartnerGestorben,verwitwet\nverwitwet,Hochzeit,verheiratet\nledig,Tod, \ngeschieden,Tod, \nverwitwet,Tod, \nverheiratet,Tod, ");
        std::cout<<test.getState()<<std::endl;

        std::cout<<"Test 2 - Ledig -> Heiraten"<<std::endl;
        test.prozess("Hochzeit");
        std::cout<<test.getState()<<std::endl;

        // std::cout<<"Test 9 - Heiraten -> Tod"<<std::endl;
        // test.prozess("Tod");
        // std::cout<<test.getState()<<std::endl;

        // std::cout<<"Test 10 - Heiraten -> ledig"<<std::endl;
        // test.prozess("Ledig");
        // std::cout<<test.getState()<<std::endl;

        std::cout<<"Test 3 - Heiraten -> Scheidung"<<std::endl;
        test.prozess("Scheidung");
        std::cout<<test.getState()<<std::endl;

        // std::cout<<"Test 11 - Scheidung -> verwitwet"<<std::endl;
        // test.prozess("PartnerGestorben");
        // std::cout<<test.getState()<<std::endl;

        std::cout<<"Test 4 - Scheidung -> Heiraten"<<std::endl;
        test.prozess("Hochzeit");
        std::cout<<test.getState()<<std::endl;

        std::cout<<"Test 5 - Heiraten -> PartnerGestorben"<<std::endl;
        test.prozess("PartnerGestorben");
        std::cout<<test.getState()<<std::endl;

        // std::cout<<"Test 12 - verwitwet -> geschieden"<<std::endl;
        // test.prozess("Scheidung");
        // std::cout<<test.getState()<<std::endl;

        std::cout<<"Test 6 - PartnerGestorben -> Heiraten"<<std::endl;
        test.prozess("Hochzeit");
        std::cout<<test.getState()<<std::endl;

        std::cout<<"Test 7 -  Heiraten -> Scheidung"<<std::endl;
        test.prozess("Scheidung");
        std::cout<<test.getState()<<std::endl;

        // std::cout<<"Test 13 - Scheidung -> PartnerGestorben"<<std::endl;
        // test.prozess("PartnerGestorben");
        // std::cout<<test.getState()<<std::endl;

        std::cout<<"Test 8 - Scheidung -> Tod"<<std::endl;
        test.prozess("Tod");
        std::cout<<test.getState()<<std::endl;

        // std::cout<<"Test 14 - Tod -> Heiraten"<<std::endl;
        // test.prozess("Hochzeit");
        // std::cout<<test.getState()<<std::endl;

    }
    catch (const std::exception& e)
    {
        std::cerr << "Fehler: " << e.what() << std::endl;
    }

    return 0;
}