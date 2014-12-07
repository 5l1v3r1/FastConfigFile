
#include <iostream>
#include "ConfigFile.h"

using namespace std;

int main()
{
    //Exemple of use

    try{
        ConfigFile cf("test.txt", true);
        std::string nom;
        cout << "nom=" << cf.get("name", nom) << endl;
        cf.parse();
        cout << "nom=" << cf.get("name", nom) << endl;
        cout << cf;
		cf.set("name", "Dumbo");
		cf.save();
    }

    catch(ConfigFile::Exception& error){

        std::cerr << "Error: " << error.what() << std::endl;
    }

    catch(...){
        return 1;
    }

    return 0;
}

