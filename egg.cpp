
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <thread>   
#include <chrono>   
using namespace std;



//class for bad egg
class bad_egg : public exception {
public:
    const char* what() const noexcept override {
        return "Looks like you ate a rotten egg";
    }
};


//main class defining the egg
class Egg {
protected:
    string size;
    string flavor;
public:
    Egg(string s, string f) : size(s), flavor(f) {}
    string getSize() const { return size; }
    string getFlavor() const { return flavor; }
    virtual void eat_egg() const = 0; 
    virtual ~Egg() = default;
};


//Inherit class from egg in order to eat
class BoiledEgg : public Egg {
public:
    BoiledEgg(string s, string f) : Egg(s, f) {}
    void eat_egg() const override {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "You eat a " << size << " boiled egg. It's " << flavor << "!\n";
    }
};


//Another inherit class from egg in order to eat
class ScrambledEgg : public Egg {
public:
    ScrambledEgg(string s, string f) : Egg(s, f) {}
    void eat_egg() const override {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "You eat a " << size << " scrambled egg. It's " << flavor << "!\n";
    }
};


//class for RottenEgg
class RottenEgg : public Egg {
public:
    RottenEgg(string s, string f) : Egg(s, f) {}
    void eat_egg() const override {
        this_thread::sleep_for(chrono::seconds(1));
        throw bad_egg(); 
    }
};


//class for carton in which eggs are stored
class Carton {
private:
    vector<Egg*> eggs;
public:
    void addEgg(Egg* e) {
        if (eggs.size() < 12)
            eggs.push_back(e);
    }
    void eatEgg() {
        if (eggs.empty()) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << "There are no eggs left in the carton.\n";
            return;
        }
        Egg* e = eggs.back();
        eggs.pop_back();
        try {
            e->eat_egg();
        } catch (const bad_egg& except) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << except.what() << endl;
        }
        delete e; 
    }
};


//main function where everything happens
int main() {
    Carton c;
    c.addEgg(new BoiledEgg("big", "delicious"));
    c.addEgg(new ScrambledEgg("medium", "salty"));
    c.addEgg(new RottenEgg("small", "awful"));

    for (int i = 0; i < 4; ++i)
        c.eatEgg();

    return 0;
}
