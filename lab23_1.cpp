#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream file(filename);
    string line;
    while(getline(file, line)){
        size_t pos = line.find(':');
        string name = line.substr(0, pos);
        string scoreStr = line.substr(pos + 1);
        
        int score1, score2, score3;
        sscanf(scoreStr.c_str(), "%d %d %d", &score1, &score2, &score3);
        int totalScore = score1 + score2 + score3;
        
        names.push_back(name);
        scores.push_back(totalScore);
        grades.push_back(score2grade(totalScore));
    }
    file.close();
}

void getCommand(string& command, string& key){
    cout << "Please input your command:\n";
    getline(cin, command);
    
    command = toUpperStr(command);
    
    size_t spacePos = command.find(' ');
    
    if(spacePos == string::npos) {
        key = "";
    } else {

        key = toUpperStr(command.substr(spacePos + 1));
        command = toUpperStr(command.substr(0, spacePos));
    }
}


void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    bool found = false;
    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    bool found = false;
    for(size_t i = 0; i < names.size(); i++){

        if(toUpperStr(string(1, grades[i])) == key){
            if (!found) {
                cout << "---------------------------------\n";
                found = true;
            }
            cout << names[i] << " (" << scores[i] << ")\n";
        }
    }
    if(found){
        cout << "---------------------------------\n";
    } else {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}