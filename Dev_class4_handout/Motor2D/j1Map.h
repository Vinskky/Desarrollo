#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
struct Image
{
	char* source;
	unsigned int width;
	unsigned int height;

	//Image();

};

struct TerrainTypes
{
	char* name;
	unsigned int tile;
	//TerrainType()

};

struct Tile
{
	unsigned int id;
	unsigned int terrain[4];
	//TerrainType
};

struct TileSet
{
	unsigned short firstGid;
	char* name;
	unsigned int titleWith;
	unsigned int titleHeight;
	unsigned short spacing;
	unsigned short margin;

	Image imageToLoad;
	p2List<TerrainTypes> terraintypes;
	p2List<Tile> tiles;
	


	TileSet();

};

// TODO 1: Create a struct needed to hold the information to Map node
struct MapVersion
{
	enum orientation
	{
		DEFAULT_ORIENTATION,
		ORTHOGONAL,
		ISOMETRIC,
		STAGGERED,
		HEXAGONAL
	}orientation_map;
	enum renderOrder
	{
		DEFAULT_RENDERORDER,
		RIGHT_DOWN,
		RIGHT_UP,
		LEFT_DOWN,
		LEFT_UP
	}renderOrder_map;
	unsigned int width;
	unsigned int height;
	unsigned int titleWidth;
	unsigned int titleHeight;
	unsigned short nextObjectId;

	MapVersion();

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
	bool loadNFill(pugi::xml_document &map_file);
	bool loadTileSet(pugi::xml_document &map_file);

public:

	// TODO 1: Add your struct for map info as public for now
	MapVersion myMap;
	TileSet myTileSet;
private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__