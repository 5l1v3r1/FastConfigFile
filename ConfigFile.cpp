
#include "ConfigFile.h"

std::ostream& operator<<(std::ostream& out, const ConfigFile &cf){
    out << "---Infos---\n\n";
    out << "Name: " << cf.getFilename() << std::endl;
    out << "Mode: " << cf.getMode() << std::endl;
    out << "Spaces: " << (cf.getIgnoreSpaces() ? "Ignored" : "Not ignored") << std::endl;
    out << "-----------\n";

    const std::map<std::string, std::string>& entries = cf.getMap();

    for(std::map<std::string, std::string>::const_iterator i=entries.begin(); i != entries.end(); ++i){
            out << (*i).first << "=" << (*i).second << std::endl;
    }

    return out;
}

void ConfigFile::parse(){

    std::string line;
    std::string key;

    while(!stream.eof()){

        std::getline(stream, line);
        size_t pos = line.find("=");

        if(pos == std::string::npos){
            continue;
        }

        if(ignoreSpaces){
            clearLine(line, pos);
        }

        entries[line.substr(0, pos)] = line.substr(pos+1);
    }
}

void ConfigFile::save(std::string _filename){

    if(_filename == ""){
        _filename = filename;
    }

    std::fstream saveStream(_filename.c_str(), std::ios_base::out|std::ios_base::trunc);

    if(!saveStream)
    {
        throw ConfigFile::Exception("Could not open " + _filename);
    }

    saveStream << *this;

    saveStream.close();
}

void ConfigFile::clearLine(std::string & line, size_t & equalPos){

        while(line[equalPos-1] == ' '){
            equalPos--;
            line.erase(equalPos, 1);
        }

        while(line[equalPos+1] == ' '){
            line.erase(equalPos+1, 1);
        }

        while(line[0] == ' '){
            equalPos--;
            line.erase(0, 1);
        }

         while(line[line.length()-1] == ' '){
            line.erase(line.length()-1, 1);
        }
}
