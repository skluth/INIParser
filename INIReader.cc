
// Code for INIReader class and helper functions:

#include "INIReader.hh"
#include "ini.hh"
#include <algorithm>
#include <iostream>

using std::string;
using std::vector;
using std::map;
using namespace INIParser;


// Ctor, read complete ini file here using the built-in handler:
INIReader::INIReader( const string& filename ) {
  _error= ini_parse( filename.c_str(), valueHandler, this );
}

// Return error status after reading:
int INIReader::parseError() const {
  return _error;
}

// Dump parsed data:
void INIReader::dump() const {
  for( map<string,map<string,string> >::const_iterator sectionIter= 
	 _sectionMap.begin(); sectionIter != _sectionMap.end(); 
       sectionIter++ ) {
    dumpSection( sectionIter->first );
  }
  return;
}
void INIReader::dumpSection( const string& section ) const {
  std::cout << "dump section " << section << std::endl;
  vector<string> names= getNames( section );
  for( size_t i= 0; i < names.size(); i++ ) {
    string name= names[i];
    std::cout << name << " " << get( section, name, "" ) << std::endl;
  }
  return;
}

// Get value(s) as string, return default if no matching entry
// in map:
string INIReader::get( const string& section, const string& name, 
		       const string& default_value ) const {
  string result= default_value;
  map<string,map<string,string> >::const_iterator sectionIter= 
    _sectionMap.find( section );
  if( sectionIter != _sectionMap.end() ) {
    const map<string,string> nameMap= sectionIter->second;
    map<string,string>::const_iterator mapIter= nameMap.find( name );
    if( mapIter != nameMap.end() ) result= mapIter->second;
  }
  return result;
}

// Get all names in a section in a sorted vector, returns
// empty vector when no section map is found or when it is empty:
vector<string> INIReader::getNames( const string& section ) const {
  vector<string> names;
  map<string,map<string,string> >::const_iterator sectionIter=
    _sectionMap.find( section );
  if( sectionIter != _sectionMap.end() ) {
    const map<string,string> nameMap= sectionIter->second;
    for( map<string,string>::const_iterator nameIter= nameMap.begin();
	 nameIter != nameMap.end(); nameIter++ ) {
      names.push_back( nameIter->first );
    }
    std::sort( names.begin(), names.end() );
  }
  return names;
}

// Handler as expected by ini.cc, it is called for each parsed line.
// Store value with keys <section> and <name> in map of maps:
int INIReader::valueHandler( void* user, const char* section, const char* name,
			     const char* value ) {
  INIReader* reader= (INIReader*) user;
  if( reader->_sectionMap[section][name].size() > 0 ) {
    reader->_sectionMap[section][name]+= "\n";
  }
  reader->_sectionMap[section][name]+= value;
  return 1;
}

// Get value string as vector of tokens separated by isspace:
vector<string> INIParser::getTokens( const string& valueStr ) {
  string token;
  vector<string> tokens;
  for( string::const_iterator iter= valueStr.begin(); 
       iter != valueStr.end(); iter++ ) {
    const char c= *iter;
    if( isspace( c ) ) {
      if( token.length() > 0 ) {
	tokens.push_back( token );
	token.clear();
      }
    }
    else {
      token+= c;
    }
  }
  if( token.length() > 0 ) tokens.push_back( token );
  return tokens;
}

// Get bool value using specialised template function:
template <>
bool INIParser::stringToType<bool>( const string& text, 
				    bool default_value ) {
  string valstr= text;
  std::transform( valstr.begin(), valstr.end(), valstr.begin(), ::tolower );
  bool result= default_value;
  if( valstr == "true" || valstr == "yes" || 
      valstr == "on" || valstr == "1" ) result= true;
  else if( valstr == "false" || valstr == "no" || 
	   valstr == "off" || valstr == "0" ) result= false;
  return result;
}

