#include <rapidxml/rapidxml_utils.hpp>
#include "config.h"
#include <memory>
#include <string>
#include <utility>
#include <exception>

using namespace rapidxml;
using namespace std;

Config load_config(const string& file_name) 
{
        
   /*
 rapidxml HOWTOES:
   https://gist.github.com/JSchaenzle/2726944
   http://stackoverflow.com/questions/2808022/how-to-parse-the-xml-file-in-rapidxml
   http://www.gamedev.net/topic/666611-reading-xml-files-with-rapidxml/
 */

   Config config;

   rapidxml::file<> xmlFile(file_name.c_str());  

   xml_document<> doc;

   doc.parse<0>(xmlFile.data());

   xml_node<> *root_node = doc.first_node();

   auto database_node = root_node->first_node("database");

   // Assign the database parameter members of config. 
   std::pair<const char *, std::string&> db_params[] = { {"host", config.db.host}, {"dbname", config.db.dbname}, {"user", config.db.user}, {"password", config.db.password}};   

   for(auto& x : db_params) {

       x.second = move(database_node->first_node(x.first)->value()); 
   }

/* Old code:
   config.db.host = move(database_node->first_node("host")->value()); 

   config.db.dbname = move(database_node->first_node("dbname")->value());

   config.db.user = move(database_node->first_node("user")->value());

   config.db.password = move(database_node->first_node("password")->value());
*/
   
   auto files_node = root_node->first_node("files");
   
   for ( auto curfile_node = files_node->first_node("file"); curfile_node != nullptr; curfile_node = curfile_node->next_sibling() ) {

        // get indecies
        auto index = curfile_node->first_node("indecies")->first_node("index");

        // Get associated indecies
        vector<int> indecies; 
        
        auto total = 0;
        
        while (index != nullptr) {
    
             auto integer = stoi(index->value());  

             indecies.emplace_back(integer);   

             ++total;

             index = index->next_sibling();
        }     
        
        indecies.resize(total); 
        
        indecies.shrink_to_fit();
                
        // Construct in-place on file list 
        config.file_list.emplace_back(curfile_node->first_attribute("filename")->value(),  curfile_node->first_attribute("table")->value(),  move(indecies));
    }

   return config;
}
