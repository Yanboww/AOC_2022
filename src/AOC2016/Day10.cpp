#include <iostream>
#include <fstream>
#include <vector> 
#include <sstream>
#include <algorithm>
#include <cctype>

class Bot{
    public:
        std::vector<int> chips;
        void insert(int val){
            chips.push_back(val);
            std::sort(chips.begin(),chips.end());
        }
};

bool stringDigit(std::string& val){
    for(char& c : val){
        if(!std::isdigit(c))return false;
    }
    return true;
}

int part1(std::vector<Bot>& bots, std::vector<std::vector<int>>& queries, std::vector<int>& bin, int part){
    while(!queries.empty()){
        for(int i = 0; i < queries.size(); i++){
            std::vector<int> option = queries[i];
            std::vector<int>& chips = bots[option[1]].chips;
            if(chips.size() >= 2){
                int hi = chips.back();
                chips.pop_back();
                int lo = chips.front();
                chips.erase(chips.begin());
                if(option[2] == 0) bots[option[3]].insert(lo);
                else bin[option[3]]+=lo;
                if(option[4] == 0) bots[option[5]].insert(hi);
                else bin[option[5]]+=hi;
                queries.erase(queries.begin()+i);
                i--;
                if(hi == 61 && lo == 17 && part == 1){
                    return option[1];
                }
            }
        }
    }
    return bin[0] * bin[1] * bin[2];
}

int main(){
    std::ifstream file("inputs/input.txt");
    std::vector<Bot> bots(300);
    std::vector<std::vector<int>> queries;
    std::vector<int> currentQuery(6);
    std::vector<int> bin(300,0);
    std::string line;
    while(std::getline(file,line)){
        std::stringstream ss (line);
        std::string token;
        if(line.find("gives") != std::string::npos){
            int index = 0;
            while(std::getline(ss,token,' ')){
                if(stringDigit(token)){
                    currentQuery[index++] = std::stoi(token);
                    if(index == 5) break;
                } else if(token == "bot") currentQuery[index++] = 0;
                else if(token == "output") currentQuery[index++] = 1;
            }
            queries.push_back(currentQuery);
        } else{
            int val = -1;
            while(std::getline(ss,token,' ')){
                if(stringDigit(token)){
                    if(val == -1) val = std::stoi(token);
                    else{
                        bots[std::stoi(token)].insert(val);
                        break;
                    }
                }
            }
        }
    }
    std::cout << part1(bots,queries,bin,1) << "\n";
    std::cout << part1(bots,queries,bin,2) << "\n";
    return 0;
}