#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


class Shellcosplay{                                     //parameters of the shell
        private:
        
        string wearhere;
        vector<string> cmdhistory;
        vector<pid_t> idhstry;
        public:
Shellcosplay(string Location){                          //delete for location
        wearhere = Location;
        cmdhistory.clear();
        idhstry.clear();
};
string getShellcosplayLocation(){
        return wearhere;
}


void appendShellcosplayLocation(string toAppend){       //append location
        wearhere.append(toAppend);
}
void setShellcosplayLocation(string Location){          //location
        wearhere = Location;
} 

void hisotryoutput (){                                  //prints out history and gets data
        int size = cmdhistory.size();
        if(size == 0)
        return;
        int i = 0;
        for(; i < size ; i++){
                cout  <<i<<"  " << cmdhistory.at(size-1-i) << "\n" ;
        }
}
string repetehistory (int i){                           //gets datalocations and returns the string of the location
        int size = cmdhistory.size();
        string string1;
        if(size == 0)
        return  0;
        
        cout << "You are replaying "<<i<<"\n";
          string1= cmdhistory.at(i);
        return string1; 
        
}
void savecmd (string toRecord){                         //save history data
        cmdhistory.push_back(toRecord);
}
void savepid (pid_t toRecord){                          //save pid data
        idhstry.push_back(toRecord);                    
        }
void undohist(){                                        //deletes hsitory -c
        cmdhistory.clear();
}
void undohistpid(){                                     //delets pid for terminate
        idhstry.clear();
}
int sizeofpid(){                                        //size of data
        return idhstry.size();
}
pid_t idat(int i){                                      //pid data
        return idhstry.at(i);
        }
};
int strtoint(string shellinputstring){                                              //strings to int fucntion before reaslzing i could just use stoi
        int size = shellinputstring.size() - 1;
        double exp = 0;
        int val = 0;
        for (; size >= 0; size--){       
                val += ( (int)shellinputstring[size] - 48 ) * pow(10, exp);
                exp++;
        }
        return val;
}

char ** strtoarray(string shellinputstring){                                        //string to chars for input line inputtts
        stringstream ss(shellinputstring);
        vector<string> placeholder;
        placeholder.clear();
        while(ss >> shellinputstring){
                placeholder.push_back(shellinputstring);
        }
        int size = placeholder.size();
        int size2 = 0; 
        char **programargs = new char*[size + 1];
        programargs[0] = new char[placeholder.at(0).size()];
        strcpy(programargs[0], placeholder.at(0).c_str());
        int i = 1;
        int j = 0;
        for(; i < size; i++){
                j++;
                programargs[i] = new char[placeholder.at(i).size()];
                strcpy(programargs[i], placeholder.at(i).c_str() );
        }
        programargs[j + 1] = (char *) 0;
        return programargs;
}

Shellcosplay parseString(Shellcosplay Shellcosplay, string shellinputstring){
        int i;
        start:
        stringstream ss(shellinputstring);
        string input;
        string inputtt = "";
        string inputtt1;
        string parameters;
        bool relative = false;                                          //Save input text to history
        Shellcosplay.savecmd(shellinputstring);                         //go thgour history 
        ss >> input;
       
        if(input.compare("repeat") == 0){            
                ss >> inputtt;
                int j = stoi(inputtt);
                ss >> input;
                        for(int c=0; c<j;c++){
                                start1:
                                if(input.compare("replay") == 0){
                                        ss >> inputtt;
                                        int i = stoi(inputtt);
                                        input=Shellcosplay.repetehistory(i);
                                        Shellcosplay.savecmd(shellinputstring);
                                        cout  << shellinputstring ;
                                        goto start1;
                                }
                                if(input.compare("history") == 0){                                      // hisotry
                                        ss >> inputtt1;
                                        if(inputtt1.compare("-c") == 0)
                                                Shellcosplay.undohist();
                                        else if(inputtt1 == "")
                                                Shellcosplay.hisotryoutput();
                                        else
                                                cout << "invalid input\n";
                                                //return Shellcosplay;
                                }

                                else if(input.compare("start") == 0){
                                                ss >> inputtt;
                                                string dothingswithstrings = "";
                                                int mychildren;
                                                if(inputtt[0] == '/'){                         
                                                        dothingswithstrings = inputtt;
                                                }
                                                else{                                           
                                                        dothingswithstrings = Shellcosplay.getShellcosplayLocation() + '/' + inputtt;
                                                }
                                                const char * dothingswithchars = dothingswithstrings.c_str();
                                                        if(access(dothingswithchars, X_OK) != 0){
                                                                cout << "File non existent\n";
                                                        }
                                                pid_t PID = fork();
                                                if(PID == 0){                                                          //If execute with given path and parameters giveven                                     
                                                        while(ss >> parameters){
                                                                inputtt.append(" ");
                                                                inputtt.append(parameters);
                                                        }
                                                char **programargs = strtoarray(inputtt);
                                                execv(dothingswithchars, programargs);
                                                }                               //If its an error, return
                                                else if(PID < 0){
                                                        cout << "could not fork \n";
                                                }                                                                       //wait for chidl to process
                                                else
                                                        waitpid(PID, &mychildren, WUNTRACED);
                                                } 
                                                else if(input.compare("background") == 0){
                                                                ss >> inputtt;
                                                                string dothingswithstrings = "";
                                                                int mychildren;
                                                        if(inputtt[0] == '/'){                         
                                                                dothingswithstrings = inputtt;
                                                        }
                                                        else{                                           
                                                                dothingswithstrings = Shellcosplay.getShellcosplayLocation() + '/' + inputtt;
                                                        }
                                                        const char * dothingswithchars = dothingswithstrings.c_str();
                                                        if(access(dothingswithchars, X_OK) != 0){
                                                                cout << "file nonexistent\n";
                                                        }
                                                        pid_t PID = fork();                     
                                                                                        //With any parameters given by user passed as one array of programargs, with arg[0] being the path
                                                        if(PID == 0){
                                                                while(ss >> parameters){
                                                                        inputtt.append(" ");
                                                                        inputtt.append(parameters);
                                                                }

                                                                char **programargs = strtoarray(inputtt);
                                                                execv(dothingswithchars, programargs);
                                                        }

                                                        else if(PID < 0){                                        //If its an error, return
                                                                cout << "could not fork \n";
                                                                //return Shellcosplay;
                                                        }
                                                        else{ //If its a parent process, wait for the child process to finish 
                                                                cout<<"PID is " << PID ;
                                                                Shellcosplay.savepid(PID);
                                                                waitpid(PID, &mychildren, WNOHANG);
                                                        }
                                                }
                                                else if(input.compare("terminate") == 0){
                                                        ss >> inputtt;
                                                        pid_t arg = (pid_t)strtoint(inputtt);
                                                        int killSuccess = kill( (arg), SIGKILL);
                                                        if(killSuccess == -1){
                                                                cout << "coult not terminate\n";
                                                        }
                                                }
                                                else if (input.compare("terminateall") == 0){
                                                        int size = Shellcosplay.sizeofpid();
                                                        int p = 0;
                                                        pid_t currentPID;
                                                        cout << "terminating " << size << " processes: ";
                                                        for (; p < size; p++){
                                                                currentPID = Shellcosplay.idat(p);
                                                                kill(currentPID, SIGKILL);
                                                                cout << currentPID << " ";
                                                        }
                                                Shellcosplay.undohistpid();
                                                }
                                                else{
                                                        cout << "invalid input, try again";
                                                }
                        }
        }






        if(input.compare("replay") == 0){
                ss >> inputtt;
                int i = stoi(inputtt);
                shellinputstring=Shellcosplay.repetehistory(i);
                Shellcosplay.savecmd(shellinputstring);
                cout  << shellinputstring ;
                goto start;
                //return Shellcosplay;
        }
        //Print input History
        if(input.compare("history") == 0){
                ss >> inputtt;
                if(inputtt.compare("-c") == 0)
                Shellcosplay.undohist();
                else if(inputtt == "")
                Shellcosplay.hisotryoutput();
                else
                        cout << "Invalid input\n";
                return Shellcosplay;
        }
        else if(input.compare("start") == 0){
                ss >> inputtt;
                string dothingswithstrings = "";
                int mychildren;
                        if(inputtt[0] == '/'){                                        
                                dothingswithstrings = inputtt;
                        }
                else{                                                                                           
                        dothingswithstrings = Shellcosplay.getShellcosplayLocation() + '/' + inputtt;
                }
                const char * dothingswithchars = dothingswithstrings.c_str();
                if(access(dothingswithchars, X_OK) != 0){
                        cout << "file nonexistent\n";
                return Shellcosplay;
                }
                pid_t PID = fork();
        
                if(PID == 0){
                        while(ss >> parameters){
                                inputtt.append(" ");
                                inputtt.append(parameters);
                        }
                        char **programargs = strtoarray(inputtt);
                        execv(dothingswithchars, programargs);
                        }//If its an error, return
                        else if(PID < 0){
                                cout << "Could not fork \n";
                                return Shellcosplay;
                        }
                else
                        waitpid(PID, &mychildren, WUNTRACED);

                        return Shellcosplay;
        } 
        else if(input.compare("background") == 0){
                ss >> inputtt;
                string dothingswithstrings = "";
                int mychildren;
                if(inputtt[0] == '/'){                                         
                        dothingswithstrings = inputtt;
                }
                else{                                                           
                        dothingswithstrings = Shellcosplay.getShellcosplayLocation() + '/' + inputtt;
                }
                const char * dothingswithchars = dothingswithstrings.c_str();
                if(access(dothingswithchars, X_OK) != 0){
                        cout << "file nonexistent\n";
                        return Shellcosplay;
                }
                pid_t PID = fork();
                if(PID == 0){
                        while(ss >> parameters){
                                inputtt.append(" ");
                                inputtt.append(parameters);
                        }
                        char **programargs = strtoarray(inputtt);
                        execv(dothingswithchars, programargs);
                }
                else if(PID < 0){
                        cout << "could not fork \n";
                        return Shellcosplay;
                }
                else{
                        cout<<"PID is " << PID;
                        Shellcosplay.savepid(PID);
                        waitpid(PID, &mychildren, WNOHANG);
                }
                return Shellcosplay;
        }
        else if(input.compare("terminate") == 0){
                ss >> inputtt;
                pid_t arg = (pid_t)strtoint(inputtt);
                int terminateachived = kill( (arg), SIGKILL);
                if(terminateachived == -1){
                        cout << "failed to terminate\n";
                        return Shellcosplay;
                }
                return Shellcosplay;
        }
        else if (input.compare("terminateall") == 0){
                int size = Shellcosplay.sizeofpid(); 
                int p = 0;
                pid_t currentPID;
                cout << "terminating " << size << " processes: ";
                        for (; p < size; p++){
                        currentPID = Shellcosplay.idat(p);
                        kill(currentPID, SIGKILL);
                        cout << currentPID << " ";
                }
                Shellcosplay.undohistpid();
                return Shellcosplay;
        }
        else{
                cout << " \n invalid input, try again \n";
                return Shellcosplay;
        }
}

int main(){
        std::string shellinputstring;
        char wearhere[500];
        string workingLocation = getcwd(wearhere, sizeof(wearhere));
        Shellcosplay Shellcosplay(workingLocation);
        cout << "Enter input:\n# ";
        getline(cin, shellinputstring);
        while(shellinputstring.compare("byebye") != 0){
                Shellcosplay = parseString(Shellcosplay, shellinputstring);
                cout << "\n# ";
                getline(cin, shellinputstring);
        }
}
 
