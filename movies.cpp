#include "movies.h"
#include <vector>
#include <unordered_map>

using namespace std;

string movie::getmovieName() const{
    return movieName;
}

double movie::getmovieRating() const{
    return movieRating;
}

bool operator<(movie a, movie b){
    return (a.getmovieName() < b.getmovieName());
}

bool operator>(movie a, movie b){
    return (a.getmovieName() > b.getmovieName());
}

bool operator==(movie a, movie b){
    if(a.getmovieName() == b.getmovieName() && a.getmovieRating() == b.getmovieRating()){
        return true;
    }
    return false;
}

int place(char letter){
    if(letter >= 'A' && letter <= 'Z'){
        return letter - 'A';
    }
    else if(letter >= 'a' && letter <= 'z'){
        return (letter - 'a') + 26;
    }
    else if(letter >= '0' && letter <= '9'){
        return (letter - '0') + 52;
    }
    else if(letter >= '[' && letter <= '`'){
        return(letter - '[') + 62;
    }
    else if(letter >= '!' && letter <= '/'){
        return(letter - '!') + 76;
    }
    else if(letter >= ':' && letter <= '@'){
        return(letter - ':') + 83;
    }
    else if(letter >= '{' && letter <= '~'){
        return (letter - '{') + 90;
    }
    else if (letter == ' '){
        return 95;
    }
    else{
        // cout << "This is not in our dictionary " << letter << "Sorry" << "\n";
        return -1;
    }
}

void treePrint(letterName* root, const unordered_map<string, double>& movie_rate, vector<movie>& query, string b, string prefix){
    if(!root){
        return;
    }

    if(root->isEnd == true){
        b += root->data;
        b.erase(0,1);
        // for(auto[name, value]: movie_rate){
        //     cout << name << "\n";
        //     cout << prefix + b << "\n";
        //     cout << "\n";
        // }
        auto it = movie_rate.find(prefix + b);
        if(it != movie_rate.end()){
            query.push_back(movie(it->first,it->second));
        }
        // else{
        //     cout << "I didn't find it";
        // }
        return;
    }
    
    for(int k = 0; k < 125; k++){
        if(root->next[k] != nullptr){
            treePrint(root->next[k], movie_rate, query, b + root->data, prefix);
            b.erase(b.size(),b.size());
        }
    }
    return;
}
