// Read an INI file into easy-to-access name/value pairs.

// inih and INIReader are released under the New BSD license (see LICENSE.txt).
// Go to the project home page for more info:
//
// http://code.google.com/p/inih/

#ifndef INIREADER_H
#define INIREADER_H

#include <map>
#include <string>
#include <sstream>
#include <vector>


// Read an INI file into easy-to-access name/value pairs. (Note that I've gone
// for simplicity here rather than speed, but it should be pretty decent.)
namespace INIParser {

  class INIReader {

  public:
    
    // Construct INIReader and parse given filename. See ini.hh for more info
    // about the parsing.
    INIReader( const std::string& filename, bool optlower=true );
    
    // Return the result of ini_parse(), i.e., 0 on success, line number of
    // first error on parse error, or -1 on file open error.
    int parseError() const;
    
    // Get a string value from INI file, returning default_value if not found.
    std::string get( const std::string& section, const std::string& name,
		     const std::string& default_value ) const;
    
    // Get all names in a section:
    std::vector<std::string> getNames( const std::string& section ) const;
    
    // Get value converted to specific type supporting 
    // stringstream >> conversion:
    template <typename T>
    T getType( const std::string& section, const std::string& name, 
	       T defaultValue ) const {
      std::string valueStr= get( section, name, "" );
      T result= stringToType( valueStr, defaultValue );
      return result;
    }
    
    // Transform key=value strings:
    std::string optionxform( const char* ) const;

    // Debugging aids:
    void dump() const;
    void dumpSection( const std::string& section ) const;
    
  private:

    int _error;
    bool _optlower;
    std::map<std::string,std::map<std::string,std::string> > _sectionMap;
    // Handler for parser ini.cc:
    static int valueHandler( void* user, const char* section, const char* name,
			     const char* value );
    
  };
  
  // Helper functions:
  
  // Get value string tokenised a la isspace:
  std::vector<std::string> getTokens( const std::string& valueStr );
  
  // Convert string to types supporting stringstream >>:
  template <typename T> 
  T stringToType( const std::string& text, T defaultValue ) {
    std::stringstream sstr( text );
    T result;
    if( !(sstr >> result) ) result= defaultValue;
    return result;
  }
  // Get a boolean value, returning default_value if not found or if not
  // a valid true/false value. Valid true values are "true", "yes", 
  // "on", "1", and valid false values are "false", "no", "off", "0" (not 
  // case sensitive).
  template <>
  bool stringToType<bool>( const std::string& text, bool defaultValue );
  
}

#endif  // INIREADER_H
