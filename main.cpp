#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

void updateUser(string name , string resut);

struct Player
{
    int games;
    int wins;
    int lastTime;
    int totalTime;
};

int main(){
    // int ch;
    // ch = getch();
    // cout << ch;
    // S=115;
    //W=119;
    //a=97;
    //d=100;
    int number;
    cout<<"1. create a new map"<<endl<<"2. playground"<<endl<<"3. Solve a maze"<<endl<<"4. Users"<<endl<<"5. History"<<endl<<"6. leaderboard"<<endl<<"7. Exit"<<endl;
    system("cls");
    
    cin>>number;
    
    switch(number){
        case 1:
            break;
        
        case 2:
            break;
        
        case 3:
            break;
        
        case 4:
            break;
        
        case 5:    
            break;
        
        case 6:
            break;
        
        case 7:
            return 0;

        default:
            break;
    }
}

void updateUser(string name , string result , int gameTime){
    ifstream file("Users/" + name + ".txt");
    Player user;
    if(file.is_open()){
        file>>user.games;
        file>>user.wins;
        file>>user.lastTime;
        file>>user.totalTime;
        file.close();
        user.games++;
        if(result == "Win"){
            user.wins++;
            user.lastTime = gameTime;
        }

        user.totalTime += gameTime;
        
        ofstream file("Users/" + name + ".txt");
        if(file.is_open()){
            file<<user.games<<endl<<user.wins<<endl<<user.lastTime<<endl<<user.totalTime;
            file.close();
        }
    }
    else{
        ofstream file;
        if(file.is_open()){
            file<<1<<endl;
            if(result == "Win"){
                file<<1<<endl;
                file<<gameTime<<endl;
            }
            else{
                file<<0<<endl;
                file<<0<<endl;
            }
            file<<gameTime;
            file.close();
        }
    }
}