#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
struct letterName{
    char data;
    bool isEnd;
    letterName* next[125]= {nullptr};
    
    letterName(char letter) : isEnd(false), data(letter){};
    letterName(char letter, bool ending) :  data(letter), isEnd(ending){};
};

class movie{
    public:
        string getmovieName() const;
        double getmovieRating() const;
        friend bool operator<(movie a, movie b);
        movie(string name, double rate) : movieName(name),movieRating(rate){};
        movie(): movieName("none"),movieRating(-1.0){};
    private:
        string movieName;
        double movieRating;
};

bool operator<(movie a, movie b);
bool operator>(movie a, movie b);
bool operator==(movie a, movie b);

int place(char letter);
void treePrint(letterName* root, const unordered_map<string, double>& movie_rate, vector<movie>& query, string b, string prefix);