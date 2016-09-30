#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1FileSystem.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

MapVersion::MapVersion(): orientation_map(DEFAULT_ORIENTATION), renderOrder_map(DEFAULT_RENDERORDER), width(0), height(0), titleWidth(0), titleHeight(0), nextObjectId(0)
{}

TileSet::TileSet(): firstGid(0), name("\0"), titleWith(0), titleHeight(0), spacing(0), margin(0)
{}

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map

	// Remove all tilesets


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	char* buf;
	int size = App->fs->Load(tmp.GetString(), &buf);
	pugi::xml_parse_result result = map_file.load_buffer(buf, size);

	RELEASE(buf);

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		
		loadNFill(map_file);
		loadTileSet(map_file);
		
		//atoi("numeroIdTileSet")
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	

	// TODO 5: LOG all the data loaded
	// iterate all tilesets and LOG everything

	map_loaded = ret;

	return ret;
}

bool j1Map::loadNFill(pugi::xml_document &map_file)
{
	pugi::xml_node mapNode = map_file.child("map");

	myMap.height = mapNode.attribute("height").as_int();
	if (myMap.height == 0)
	{
		LOG("Error loading height to map_file");
			return false;
	}

	myMap.width = mapNode.attribute("width").as_int();
	if (myMap.width == 0)
	{
		LOG("Error loading width to map_file");
			return false;
	}

	myMap.nextObjectId = mapNode.attribute("nextobjectid").as_int();
	if (myMap.nextObjectId == 0)
	{
		LOG("Error loading nextObjectId to map_file");
		return false;
	}

	myMap.titleHeight = mapNode.attribute("tileheight").as_int();
	if (myMap.titleHeight == 0)
	{
		LOG("Error loading titleHeight to map_file");
		return false;
	}
	
	myMap.titleWidth = mapNode.attribute("tilewidth").as_int();
	if (myMap.titleWidth == 0)
	{
		LOG("Error loading titleWidth to map_file");
		return false;
	}

	//orientation loading
	if (mapNode.attribute("orientation").value() == "orthogonal")
		myMap.orientation_map = myMap.ORTHOGONAL;
	if (mapNode.attribute("orientation").value() == "isometric")
		myMap.orientation_map = myMap.ISOMETRIC;
	if (mapNode.attribute("orientation").value() == "staggered")
		myMap.orientation_map = myMap.ORTHOGONAL;
	if (mapNode.attribute("orientation").value() == "hexagonal")
		myMap.orientation_map = myMap.HEXAGONAL;
	if (myMap.orientation_map == myMap.DEFAULT_ORIENTATION)
	{
		LOG("Error trying to loading orientation");
		return false;
	}
		

	//render loading
	if (mapNode.attribute("renderorder").value() == "right-down")
		myMap.renderOrder_map = myMap.RIGHT_DOWN;
	if (mapNode.attribute("renderorder").value() == "right-up")
		myMap.renderOrder_map = myMap.RIGHT_UP;
	if (mapNode.attribute("renderorder").value() == "left-down")
		myMap.renderOrder_map = myMap.LEFT_DOWN;
	if (mapNode.attribute("renderorder").value() == "left-up")
		myMap.renderOrder_map = myMap.LEFT_UP;
	if (myMap.renderOrder_map = myMap.DEFAULT_RENDERORDER)
	{
		LOG("Error trying to loading renderorder probably you introduce a wrong direction");
		return false;
	}

	return true;

}

bool j1Map::loadTileSet(pugi::xml_document &tile_file)
{
	pugi::xml_node tileNode = map_file.child("tileset");

	myTileSet.firstGid = tileNode.attribute("firstgid").as_int();
	if (myTileSet.firstGid == 0)
	{
		LOG("Error loading firstgId to tileSet");
		return false;
	}

	myTileSet.name = (char* )tileNode.attribute("name").value();
	if (myTileSet.name == "\0")
	{
		LOG("Error loading name to tileSet");
		return false;
	}

	myTileSet.titleWith = tileNode.attribute("tilewidth").as_int();
	if (myTileSet.titleWith == 0)
	{
		LOG("Error loading titleWith to tileSet");
		return false;
	}

	myTileSet.titleHeight = tileNode.attribute("tileheight").as_int();
	if (myTileSet.titleHeight == 0)
	{
		LOG("Error loading titleHeight to tileSet");
		return false;
	}

	myTileSet.spacing = tileNode.attribute("spacing").as_int();
	if (myTileSet.spacing == 0)
	{
		LOG("Error loading spacing to tileSet");
		return false;
	}

	myTileSet.margin = tileNode.attribute("margin").as_int();
	if (myTileSet.margin == 0)
	{
		LOG("Error loading margin to tileSet");
		return false;
	}

	//Loading image
	myTileSet.imageToLoad.source = tileNode.child("image").attribute("source").value();
	if (myTileSet.imageToLoad.source == "\0")
	{
		LOG("Error loading image name to tileSet");
		return false;
	}

	myTileSet.imageToLoad.height = tileNode.child("image").attribute("height").as_int();
	if (myTileSet.imageToLoad.height == 0)
	{
		LOG("Error loading image height to tileSet");
		return false;
	}

	myTileSet.imageToLoad.width = tileNode.child("image").attribute("width").as_int();
	if (myTileSet.imageToLoad.width == 0)
	{
		LOG("Error loading image width to tileSet");
		return false;
	}

	p2List_item<TerrainTypes>* pointer = myTileSet.terraintypes.start;

	while (pointer != nullptr)
	{
		pointer->data.tile = tileNode.child("terrain").attribute("tile").as_int();
		pointer->data.name = tileNode.child("terrain").attribute("name").value();
		pointer->next;
	}

	p2List_item<Tile>* iterator = myTileSet.tiles.start;
	pugi::xml_node* point = &tileNode.child("tile");
	while (iterator != nullptr)
	{
		iterator->data.id = point->attribute("id").as_int();
		
		std::string probando = point->attribute("terrain").value();
		char * name1 = probando.c_str;

		for (int i = 0; i < 4; i++)
		{
			iterator->data.terrain[i] = name1[i];
		}
		myTileSet.tiles.add(iterator->data);
		point = &point->next_sibling();
		if (point->next_sibling().name() != "tile")
			iterator = nullptr;
	}
	return true;
}

