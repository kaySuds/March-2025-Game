Level text files contain data for tile grids to use for each level and should be interpreted using the following.

1. The first line of the file is the name of the level and the starting x and y position for the player:

e.g
LEVEL_NAME      START_POS_X      START_POS_Y      NUM_COLUMNS_PER_ROW
Basement        0                0                5

2. Each group of lines afterword represent tiles from left-to-right and top-to-bottom:

e.g
TILE_TYPE       TOP_EDGE        RIGHT_EDGE       BOTTOM_EDGE       LEFT_EDGE       OBJECT_ID(OBJ Only)   
OBJ             O               W                D                 O               Object-1  

Tile types map to the following types in the code:
FLR -> FLOOR
HLE -> HOLE
LDR -> LADDER
OBJ -> FLOOR_WITH_OBJECT - In this case the associated object ID will follow the LEFT_EDGE data.

Edge types are:
O -> OPEN
W -> WALL
D -> DOOR

3. Each level is separted by a line containing only a dash - character and this should be used as a delimter between levels.