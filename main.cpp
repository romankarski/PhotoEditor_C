#include <iostream>
#include "World.hpp"
#include <ctime>
#include "mygetch.hpp"

using namespace std;

void print_brake(int size){
    for(int i = 0; i < size*2; i++){
            cout<<"_";
        }
    cout<<"_____\n";
}

int main(){
    srand(unsigned(time(0))); // seed for random generator

    

    char input = ' ';

    system("clear");
    cout<<"_____________________________________________________________________\n";
    cout<<"LEGEND : \n";
    cout<<" \n\t// Flora\nGRASS = ',',\nSOWTHISTLE = '.',\nGUARANA = 'g',\nDEADLY_NIGHTSHADE = '?',\nHERACLEUM_SOSNOWSKYI = '!',\n\t// Fauna\nWOLF = 'W',\nSHEEP = 'S',\nFOX = 'F',\nTURTLE = 'T',\nANTELOPE = 'A',\nCYBERSHEEP = 'C',\nHUMAN = 'H'\n";
    cout<<"_____________________________________________________________________\n";
    cout<<" How Big The World You Like To Be : \n";
    cout<<" press letters : a is 10, b is 11,..., z is 35 \n";
    input = mygetch();
    cout<<"_____________________________________________________________________\n";
    int size = int(input)-87;
    cout<<"size :" << size << endl;
    World virtual_world(size, false);
    input = ' ';

    while(input != 'e'){
        system("clear");
        cout<<"Roman Karski, 174040\n";
        cout<<"Press 'e' to end program\n";
        cout<<"Press 'p' to add organism\n";
        cout<<"Any key for next turn\n";
        cout<<"Also arrows control a human movement\n";

        print_brake(size);
        virtual_world.drawWorld();
        print_brake(size);
        
        //--
        std::cout<<"IN MAIN :";
        input = mygetch();

        if(input == 'p'){
            print_brake(size);

            int x = -1;
            while(x < 0 or x > size){
                cout<<"\n x :";
                cin>>x;
            }

            int y = -1;
            while(y < 0 or y > size){
                cout<<"\n y :";
                cin>>y;
            }

            int choice = -1;
            cout<<" \n\t// Flora\nGRASS = 1,\nSOWTHISTLE = 2,\nGUARANA = 3,\nDEADLY_NIGHTSHADE = 4,\nHERACLEUM_SOSNOWSKYI = 5,\n\t// Fauna\nWOLF = 6,\nSHEEP = 7,\nFOX = 8,\nTURTLE = 9,\nANTELOPE = 10\n";
            while(choice < 0 or choice > 10){
                cout<<"\n Your choice :";
                cin>>choice; 
            }
            virtual_world.addOrganism(x, y, (choice-1));
            print_brake(size); 
        }
        else{
            virtual_world.setInput(input);
            //--
            virtual_world.makeTurn();
        }
    }
}