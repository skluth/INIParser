
// Example that shows simple usage of the INIReader class

#include "INIReader.hh"
#include <iostream>
#include <complex>


int main() {

  using namespace INIParser;

  INIReader reader( "test.ini" );
  if( reader.parseError() < 0 ) {
    std::cout << "Can't load 'test.ini'\n";
    return 1;
  }

  std::cout << "Config loaded from 'test.ini': version="
	    << reader.getType( "protocol", "version", -1 ) << ", name="
	    << reader.get( "user", "name", "UNKNOWN" ) << ", email="
	    << reader.get( "user", "email", "UNKNOWN" ) << ", active="
	    << reader.getType( "user", "active", true ) << ", number="
	    << reader.getType( "protocol", "number", 0.0 ) << "\n";
  
  reader.dump();

  double d= stringToType( "1.23", 0.0 );
  long il= stringToType( "456", 0 );
  int ii= stringToType( "789", 0 );
  std::complex<double> c= stringToType( "(1.0,1.0)", 
					std::complex<double>() );
  std::cout << d << " " << il << " " << ii << " " << c << std::endl;
  
  INIReader avgparser( "/home/skluth/mtopaverage/test.txt" );
  if( reader.parseError() < 0 ) {
    std::cout << "Can't load 'test.txt'\n";
    return 1;
  }
  std::vector<std::string> names= avgparser.getNames( "Data" );
  for( size_t i= 0; i < names.size(); i++ ) {
    std::string name= names[i];
    std::string values= avgparser.get( "Data", name, "" );
    std::cout << name << ": " << values << std::endl;
    std::vector<std::string> tokens= getTokens( values );
    std::string opt= tokens[tokens.size()-1];
    tokens.pop_back();
    for( size_t itok= 0; itok < tokens.size(); itok++ ) {
      std::cout << tokens[itok] << " ";
    }
    std::cout << std::endl;
  }

  return 0;

}
