
#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class ConfigFile{

    public:

    //config file exceptions
    class Exception : public std::exception{
        public:
        Exception(const std::string what="Config File error") throw() {exceptionString=what;}
        ~Exception() throw() {}
        const char* what() const throw() {return exceptionString.c_str();}

        protected:
        std::string exceptionString;
    };

    //constructor, open the config file with given parameters, but do not copy it into memory
    ConfigFile(std::string _filename, bool create=false, std::ios_base::openmode _mode = std::ios_base::in|std::ios_base::out,  bool _ignoreSpaces=true) :
    filename(_filename), mode(_mode), stream(filename.c_str(), mode), ignoreSpaces(_ignoreSpaces){
        if(!stream){
            if(create)
            {
                stream.close();
                stream.open(filename.c_str(), mode|std::ios_base::trunc);
            }

            else throw Exception("Could not open " + filename);
        }
    }

    //destructor
    ~ConfigFile(){

        std::cout << "Destroying config file " << filename << std::endl;

        if(stream)
            stream.close();
    }

    std::string getFilename() const {return filename;}

    std::ios_base::openmode getMode() const {return mode;}

    //if set true, parsing will ignore spaces before and after the 'equal' sign, and spaces at line start and line end
    bool getIgnoreSpaces() const {return ignoreSpaces;}
    void setIgnoreSpaces(bool _ignoreSpaces) {ignoreSpaces = _ignoreSpaces;}

    //reads the file to memory
    void parse();

    template <class T> T& get(std::string key, T& value){
        std::stringstream s(entries[key]);
        s >> value;
        return value;
    }

    template <class T> void set(std::string key, T value){
        std::stringstream s;
        s << value;
        entries[key] = s.str();
    }

    const std::map<std::string, std::string>& getMap() const{return entries;}

    void save(std::string _filename="");

    protected:

    std::string filename;
    std::ios_base::openmode mode;
    std::fstream stream;
    std::map<std::string, std::string> entries;
    bool ignoreSpaces;

    //used if ignoreSpaces = true
    void clearLine(std::string & line, size_t & equalPos);
};

//print config file info to stream
std::ostream& operator<<(std::ostream& out, const ConfigFile &cf);

#endif

