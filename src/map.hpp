#pragma once

#include "entity.hpp"
#include <string>
#include <vector>


//! Represents in-game map, parsed from .map file in /maps
class Map {
	std::vector<Entity> entities;

	public:
	Map();					// Empty map
	Map(std::string map); // constructor, where map is the filename of the map in /maps

	private:
	void addEntity(Entity entity);
	
};