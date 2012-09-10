#include <string>

#include "map.hpp"
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

Map::Map(std::string map) {
	map = "/bin/maps/" + map;		//TODO: probably not compatible on all systems, need to figure this out
// 	boost::filesystem::path full_path( boost::filesystem::current_path().string() + map );
	boost::filesystem::path full_path(map);
	boost::filesystem::fstream file(full_path);
	std::string newLine;
	if(!file.is_open()) {
			//file could not be found
	} else {
		while(std::getline(file, newLine)) {
			std::istringstream iss(newLine);
			//newLine is the corresponding line
		}
	}
}