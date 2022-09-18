//C++ program to implement thread

#include <conio.h>
#include <string>
#include <iostream>
#include <thread>
#include <windows.h>



void player1(){
    bool isOn=true;

    while(isOn){
        // if(kbhit()){
                switch(getch()){
                    //To make the movement, we first erase the actual piece from where we are, and then make another one on the direction we get
                    case 'q': //e
                        std::cout<<"q \n"<<std::endl;
                        break;

                    case 'i':
                        std::cout<<"USER ENDED THREAD "; std::cout<< std::this_thread::get_id() <<std::endl;
                        isOn=false;
                        break;

                    default:
                        break;
                }
            // }
    }
}




void player2(){
    bool isOn=true;

    
    // https://stackoverflow.com/questions/41600981/how-do-i-check-if-a-key-is-pressed-on-c
    while(isOn){


        
        if(GetKeyState('W') & 0x8000){
            std::cout<<"space"<<std::endl;
        }
        if(GetKeyState('P') & 0x8000){
            std::cout<<"USER ENDED THREAD "; std::cout<< std::this_thread::get_id() <<std::endl;
            isOn=false;
        }
        

    }
}



int main()
{
// A new thread is created and executed
    std::thread th1(player1);

    std::thread th2(player2);

    bool isOn=true;

    while(isOn){


        // if(kbhit()){
            switch(getch()){
                case 'm':
                    std::cout<<"MAIN THREAD ENDED"<<std::endl;
                    isOn=false;
                    
                    break;

                default:
                    break;
            }
        // }
    }

}