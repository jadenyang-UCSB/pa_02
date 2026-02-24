// Winter'24
// Instructor: Diba Mirza
// Student name: Jaden Yang
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies

    double movieRating;

    vector<string> title;
    vector<movie> question;

    set<movie> movieList;

    letterName* dummyHead = new letterName(' ');
    string line, movieName;

    unordered_map<string, movie> movieScores;
    unordered_map<string, double> movieDictionary;

    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            movieList.insert(movie(movieName,movieRating));
            movieDictionary[movieName] = movieRating;
            title.push_back(movieName);
            // insert elements into your data structure
    }

    movieFile.close();

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
            for(auto iterate = movieList.begin(); iterate != movieList.end(); iterate++){
                cout << iterate->getmovieName() <<", " << iterate->getmovieRating() << "\n";
            }
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;

    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    letterName* curr = nullptr;
    for(auto words: title){
        curr = dummyHead;
        // cout << words  << "\n";
        for (int i = 0; i < words.size(); i++){
            int index = place(words[i]);
            if(curr->next[index] == nullptr){
                if(i != words.size() - 1){
                    curr->next[index] = new letterName(words[i]);
                }
                else{
                    curr->next[index] = new letterName(words[i], true);
                }
                curr = curr->next[index];
            }
            else{
                if(i == words.size() - 1){
                    curr = curr->next[index];
                    curr->isEnd = true;
                }
                else{
                    curr = curr->next[index];
                }
            }
        }        
    }

    for(int pre = 0; pre < prefixes.size(); pre++){
        question = {};
        string currString = prefixes[pre];

        curr = dummyHead;

        int j = 0;
        int index = place(currString[j]);

        while(j < currString.size() && curr->next[index]){
            curr = curr->next[index];
            j++;
            index = place(currString[j]);
        }

        if(curr->next[index]){
            treePrint(curr, movieDictionary, question,"", prefixes[pre]);
        }

        if(question.size() != 0){
            sort(question.begin(), question.end(),[](const movie& a, const movie& b){
                if(a.getmovieRating() != b.getmovieRating()){
                    return a.getmovieRating() > b.getmovieRating();
                }
                else{
                    return a.getmovieName() < b.getmovieName();
                }
            });

            movieScores[prefixes[pre]] = *question.begin();

            for(auto i: question){
                cout << i.getmovieName() << ", " << i.getmovieRating() << "\n";
            }
            cout << "\n";
        }
        else{
            cout << "No movies found with prefix "<< prefixes[pre] << "\n";
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    // cout << "No movies found with prefix "<<"<replace with prefix>" << endl;

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for(auto prefix: prefixes){
        if(movieScores[prefix].getmovieRating() != -1.0){
            cout << "Best movie with prefix " << prefix << " is: " << movieScores[prefix].getmovieName() << " with rating " << std::fixed << std::setprecision(1) << movieScores[prefix].getmovieRating() << "\n";
        }
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

/*

3A)
If I were to traverse the subtree I would have to do it in O(k*l) time because I'm looping through every prefix then looping through the titles of the movies. Next, 
I would have to include m*n*l because the characters and overall letters comes from the length of the movie name

3B) 

For the worst space complexity it would be O(n*l). When because every node stores letters from multiple movie titles. The number of nodes holds letters from movies.
Therefore, the space complexity would be O(n*l)

3C)
Did you design your algorithm for a low time complexity, a low space complexity, or both? What were your target complexities?
The algorithm I designed is ONLY designed for low time complexity. Each node represents a singular letter that has an array
of 84 spaces, therefore the space complexity is pretty bad. I wasn't able to achieve a low space complexity with a low time complexity as well.
Personally, I found that it was harder for low space complexity seeing that there are thousands of titles.
 
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}


        // for(int j = 0; j < prefixCHAR.size(); j++){
        //     int index = place(prefixCHAR[j]);
        //     if(curr->next[index]){
        //         currString += curr->data;
        //         curr = curr->next[index];
        //     }
        //     else{
        //         cout << "No prefix" << "\n";
        //         break;
        //     }
        // }
        