#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
struct TileSet
{
	unsigned short firstGid;
	char* name;
	unsigned int titleWith;
	unsigned int titleHeight;
	unsigned short spacing;
	unsigned short margin;

};

// TODO 1: Create a struct needed to hold the information to Map node
struct MapVersion
{
	enum orientation
	{
		ORTHOGONAL = 1,
		ISOMETRIC,
		STAGGERED,
		HEXAGONAL
	};
	enum renderOrder
	{
		RIGHT_DOWN =1,
		RIGHT_UP,
		LEFT_DOWN,
		LEFT_UP
	};
	unsigned int width;
	unsigned int height;
	unsigned int titleWidth;
	unsigned int titleHeight;
	unsigned short nextObjectId;

};
// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:
	bool loadNFill(pugi::xml_parse_result result);

public:

	// TODO 1: Add your struct for map info as public for now
	MapVersion myMap;
private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__