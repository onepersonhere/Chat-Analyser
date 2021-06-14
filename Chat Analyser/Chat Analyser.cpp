#include <algorithm>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;
/***
Analysis: number of messages sent by person - done
          average length of each word - done
          average number of words
          cout in a line

***/

string getname(string line) {
    int previndex, nextindex, length;
    string name;
    size_t found = line.find_first_of("-");
    
    size_t found1 = line.find_first_of(":"); 
    found1 = line.find(":", found1 + 1);
    if (found != string::npos) {
        previndex = found + 2;
    }
    else {
        return "no name";
    }
    size_t found2 = line.find("changed the subject from");
    if ((found1 != string::npos) && (previndex == 20) && (found2 == string::npos)) {
        nextindex = found1;
        length = nextindex - previndex;
        try {
            name = line.substr(previndex, length);
        }
        catch (exception& e){
            cout << "Standard exception: " << e.what() << endl;
        }
    }
    else {
        return "no name";
    }
    
    return name;
}

double getMeanLength(string line, double *count) {
    size_t found = line.find("-"); 
    size_t found1 = line.find(":", found + 1);
    
    if ((found != string::npos) && (found1 != string::npos)) { 
        //cout << line << "\n";
        line.erase(line.begin(), line.begin() + found + 2);
        
    }
    
    stringstream ss(line);
    string sIndiv;
    char space = ' ';

    double totalLength = 0;
    if (line != "<Media omitted>") {
        while (getline(ss, sIndiv, space)) {
            totalLength += sIndiv.size();
            *count = *count + 1;
        }
        if ((totalLength != 0) && (*count != 0)) {
            double meanLength = totalLength / *count; //cout << totalLength << " " << *count << " " << meanLength << "\n";
            return meanLength;
        }
    }
    return 0;
}


int main()
{   
    map<string, int> num_of_messages;
    map<string, long double> total_average_length;
    map<string, double> total_average_num;
    string line;
    ifstream file("exported.txt");
    ofstream wfile("export.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {   
            double count = 0;
            string name = getname(line);
            //cout << name << "\n";
            long double avgLength = getMeanLength(line, &count);
            //cout << count << "\n";

            if ((name != "no name") && (name != "") && (name != "oid function [-Werror=return-type]")) {
                num_of_messages[name] += 1;
                total_average_length[name] += avgLength; //cout << name << ": " << total_average_length.at(name) << " " << avgLength << "\n";
                total_average_num[name] += count;
            }
        }
        
        for (std::map<string, long double>::iterator it = total_average_length.begin(); it != total_average_length.end(); ++it) {

            long double totalAvgLength = it->second;
            
            long double totalAvgNum = total_average_num.find(it->first)->second;

            double totalnum = num_of_messages.find(it->first)->second;

            long double avgAvgLength = totalAvgLength / totalnum;

            double avgAvgNum = totalAvgNum / totalnum;
            
            if (wfile.is_open()) {
                wfile << " " << it->first << " => average length of words: " << avgAvgLength << " average number of words: " << avgAvgNum << '\n';
                wfile << " " << it->first << " has: " << totalnum << " messages\n";
            }
        }
        //for (auto& x : total_average_length) {
        //        std::cout << x.first << ": " << x.second << '\n';
        //}
        wfile.close();
        file.close();
    }

    cout << "Programme Ran Successfully :)\n";
    return 0;
}


