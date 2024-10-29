// Assignment 2 24T3 COMP1511: CS Dungeon
// cs_dungeon.c
//
// Fangyuan SHANG z5614452
// 10 30 2024 DMY
//
// Version 1.0.0: Assignment released.
//
// <DESCRIPTION OF YOUR PROGRAM HERE>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cs_dungeon.h"

// Add any extra #includes your code needs here.

////////////////////////////////////////////////////////////////////////////////
//                                 Constants                                  //
////////////////////////////////////////////////////////////////////////////////

// Add your own #defines here:

// Your enums go here:

////////////////////////////////////////////////////////////////////////////////
//                            Struct Definitions                              //
////////////////////////////////////////////////////////////////////////////////

// Provided structs:

// Stores information about a dungeon
struct dungeon
{
    // name of the dungeon
    char name[MAX_STR_LEN];

    // what type of monster it contains (enum described in cs_dungeon.h)
    enum monster_type monster;

    // the amount of monsters it contains
    int num_monsters;

    // a pointer to the boss monster (if it contains one) or NULL
    struct boss *boss;

    // a pointer to the first item it contains or NULL
    struct item *items;

    // an int indicating if the player is inside the dungeon
    //      1: The player is inside the dungeon
    //      0: The player is not inside the dungeon
    int contains_player;

    // a pointer to the next dungeon in the map or NULL
    struct dungeon *next;
};

// Stores information about an item
struct item
{
    // what type of item (enum described in cs_dungeon.h)
    enum item_type type;

    // how many points the item is worth
    int points;

    // a pointer to the next item in the list or NULL
    struct item *next;
};

// Stores information about the player who is exploring the dungeon map
struct player
{
    // name of the player
    char name[MAX_STR_LEN];

    // what type of class they are playing (Figher or Wizard)
    char class_type[MAX_STR_LEN];

    // how many health points they have
    int health_points;

    // how much shield power they have
    int shield_power;

    // how much damage they have
    int damage;

    // what their magic modifier is when they make magical attacks
    double magic_modifier;

    // a pointer to the first item in their inventory or NULL
    struct item *inventory;

    // the number of points they have collected over the course of the game
    int points;
};

// Stores information about the boss-level monster initially placed in the last
// dungeon in the map
struct boss
{
    // how many health points they have
    int health_points;

    // how much damage they have
    int damage;

    // how many points they are worth when defeated
    int points;

    // the item type the player is required to have to fight them
    enum item_type required_item;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////////////
//                           Additional Prototypes                            //
////////////////////////////////////////////////////////////////////////////////

// Add prototypes for any extra functions you create here.

// Stage 1
struct dungeon *create_dungeon(char *name, enum monster_type monster,
                               int num_monsters, int contains_player);

struct boss *create_boss(int health_points, int damage, int points,
                         enum item_type required_item);

// Stage 2

// Stage 3

// Stage 4

// You need to implement the following functions.
// You can find descriptions of what each function
// should do in dungeon.h

////////////////////////////////////////////////////////////////////////////////
//                             Stage 1 Functions                              //
////////////////////////////////////////////////////////////////////////////////

struct map *create_map(char *name, int win_requirement)
{
    struct map *new_map = malloc(sizeof(struct map));
    if (new_map == NULL)
    {
        printf("Failed to allocate memory for map.\n");
        exit(1);
    }

    // 复制地图名称
    strncpy(new_map->name, name, sizeof(new_map->name) - 1);
    new_map->name[sizeof(new_map->name) - 1] = '\0';

    // 设置胜利条件
    new_map->win_requirement = win_requirement;

    // 根据你的结构体定义，初始化其他字段
    // 如果没有其他字段，可以省略

    return new_map;
}

struct player *create_player(char *name, char *class_type)
{
    struct player *new_player = malloc(sizeof(struct player));
    if (new_player == NULL)
    {
        printf("Failed to allocate memory for map name.\n");
        exit(1);
    }

    // 复制玩家名称
    strncpy(new_player->name, name, sizeof(new_player->name) - 1);
    new_player->name[sizeof(new_player->name) - 1] = '\0';

    // 复制职业类型
    strncpy(new_player->class_type, class_type, sizeof(new_player->class_type) - 1);
    new_player->class_type[sizeof(new_player->class_type) - 1] = '\0';

    // 根据职业类型设置属性
    if (strcmp(class_type, "Fighter") == 0)
    {
        new_player->health_points = 30;
        new_player->shield_power = 2;
        new_player->damage = 8;
        new_player->magic_modifier = 0.9;
    }
    else if (strcmp(class_type, "Wizard") == 0)
    {
        new_player->health_points = 15;
        new_player->shield_power = 0;
        new_player->damage = 7;
        new_player->magic_modifier = 1.5;
    }
    else
    {
        printf("Unknown class type.\n");
        exit(1);
    }

    // 初始化其他字段
    // 根据你的结构体定义

    return new_player;
}

// Creates a new dungeon
//
// Parameters:
//      monster         - type of monster occupying the dungeon
//      num_monsters    - number of monsters occupying the dungeon
//      contains_player - 1 if the player is contained in this dungeon,
//                        0 otherwise
// Returns:
//      pointer to newly created struct dungeon
//
struct dungeon *create_dungeon(char *name,
                               enum monster_type monster,
                               int num_monsters,
                               int contains_player)
{
    struct dungeon *new_dungeon = malloc(sizeof(struct dungeon));
    if (new_dungeon == NULL)
    {
        printf("Failed to allocate memory for dungeon.\n");
        exit(1);
    }

    // 复制地下城名称
    strncpy(new_dungeon->name, name, sizeof(new_dungeon->name) - 1);
    new_dungeon->name[sizeof(new_dungeon->name) - 1] = '\0';

    // 设置其他属性
    new_dungeon->monster = monster;
    new_dungeon->num_monsters = num_monsters;
    new_dungeon->contains_player = contains_player;
    new_dungeon->boss = NULL; // 初始时没有 Boss

    // 初始化其他字段
    // 根据你的结构体定义

    return new_dungeon;
}

int append_dungeon(struct map *map,
                   char *name,
                   enum monster_type monster,
                   int num_monsters)
{
    // TODO: implement this function
    printf("Append Dungeon not yet implemented.\n");
    exit(1);
}

void print_map(struct map *map)
{
    // TODO: implement this function
    printf("Print Map not yet implemented.\n");
    exit(1);
}

// Creates a new boss
//
// Parameters:
//      health_points   - starting health points of the final boss monster
//      damage          - damage dealt by final boss monster in one turn
//      points          - when the boss is defeated, the player will gain
//                        this many points
//      required_item   - the player needs this type of item in their inventory
//                        in order to fight the boss each turn
// Returns:
//      pointer to newly created struct boss
//
struct boss *create_boss(int health_points, int damage, int points,
                         enum item_type required_item)
{
    // TODO: implement this function
    printf("Create Boss not yet implemented.\n");
    exit(1);
}

int final_boss(struct map *map, enum item_type required_item)
{
    // TODO: implement this function
    printf("Final Boss not yet implemented.\n");
    exit(1);
}

void player_stats(struct map *map)
{
    // TODO: implement this function
    printf("Player Stats not yet implemented.\n");
    exit(1);
}

// Your functions go here (include function comments):

////////////////////////////////////////////////////////////////////////////////
//                             Stage 2 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Provided function stubs:

int insert_dungeon(struct map *map, char *name, enum monster_type monster,
                   int num_monsters, int position)
{
    // TODO: implement this function
    printf("Insert Dungeon not yet implemented.\n");
    exit(1);
}

void print_dungeon(struct map *map)
{
    // TODO: implement this function
    printf("Print Dungeon not yet implemented.\n");
    exit(1);
}

int move_player(struct map *map, char command)
{
    // TODO: implement this function
    printf("Move Player not yet implemented.\n");
    exit(1);
}

int fight(struct map *map, char command)
{
    // TODO: implement this function
    printf("Fight not yet implemented.\n");
    exit(1);
}

int end_turn(struct map *map)
{
    // TODO: implement this function
    return CONTINUE_GAME;
}

int class_power(struct map *map)
{
    // TODO: implement this function
    printf("Class Power not yet implemented.\n");
    exit(1);
}

// Your functions go here (include function comments):

////////////////////////////////////////////////////////////////////////////////
//                             Stage 3 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Provided function stubs:

struct item *create_item(enum item_type type, int points)
{
    // TODO: implement this function
    printf("Create Item not yet implemented.\n");
    exit(1);
}

int add_item(struct map *map,
             int dungeon_number,
             enum item_type type,
             int points)
{
    // TODO: implement this function
    printf("Add Item not yet implemented.\n");
    exit(1);
}

int collect_item(struct map *map, int item_number)
{
    // TODO: implement this function
    printf("Collect Item not yet implemented.\n");
    exit(1);
}

int use_item(struct map *map, int item_number)
{
    // TODO: implement this function
    printf("Use Item not yet implemented.\n");
    exit(1);
}

void free_map(struct map *map)
{
    // TODO: implement this function
}

// Your functions here (include function comments):

////////////////////////////////////////////////////////////////////////////////
//                             Stage 4 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Provided function stubs:

int teleport(struct map *map)
{
    // TODO: implement this function
    printf("Teleport not yet implemented.\n");
    exit(1);
}

int boss_fight(struct map *map)
{
    // TODO: implement this function
    printf("Boss Fight not yet implemented.\n");
    exit(1);
}

// Your functions here (include function comments):

////////////////////////////////////////////////////////////////////////////////
//                              Helper Functions                              //
////////////////////////////////////////////////////////////////////////////////

// The following are helper functions that you can use to print any output
// that main.c cannot handle for you.
// The specification will tell you which functions you should use for each
// stage.

char *get_player_name(struct player *player)
{
    return player->name;
}

void print_map_name(char *name)
{
    printf("Map of %s!\n", name);
}

void print_basic_dungeon(struct dungeon *dungeon, char *player_name,
                         int position)
{
    printf("|^|^|^|^|^|   |^|^|^|^|^|\n\n");

    printf("%d. %s\n", position, dungeon->name);

    if (dungeon->boss == NULL)
    {
        printf("Boss: None\n");
    }
    else
    {
        printf("Boss: Present\n");
    }

    printf("Monster: %s\n", monster_string(dungeon->monster));

    if (dungeon->contains_player)
    {
        printf("%s is here\n", player_name);
    }
    else
    {
        printf("Empty\n");
    }

    printf("\n|^|^|^|^|^|   |^|^|^|^|^|\n");
}

void print_connection(void)
{
    printf("          |   |\n          |   |\n          |   |\n");
}

void print_player(struct player *player, char *dungeon_name)
{
    printf("=======Player Stats=======\n");
    if (dungeon_name == NULL)
    {
        printf("%s has not entered the map yet!\n", player->name);
    }
    else
    {
        printf("%s is currently in %s\n", player->name, dungeon_name);
    }

    printf("%s\n", class_string(player));

    printf("Health Points: %d\n", player->health_points);
    printf("Shield Power: %d\n", player->shield_power);
    printf("Damage: %d\n", player->damage);
    printf("Magic Modifier: %.1lf\n", player->magic_modifier);
    printf("Points Collected: %d\n", player->points);
    printf("%s has the following items in their inventory:\n", player->name);
}

void print_item(struct item *item, int position)
{
    printf("%d. ", position);
    printf("%s", item_string(item->type));
    printf(", worth %d point(s).\n", item->points);
}

void print_no_items()
{
    printf("No Items\n");
}

void print_detail_dungeon(char *player_name, struct dungeon *dungeon)
{
    printf("======Dungeon Details======\n");
    printf("%s is currently in %s\n", player_name, dungeon->name);

    if (dungeon->monster == WOLF)
    {
        printf("There are %d wolves\n", dungeon->num_monsters);
    }
    else
    {
        printf("There are %d %ss\n", dungeon->num_monsters,
               monster_string(dungeon->monster));
    }

    if (dungeon->boss == NULL)
    {
        printf("No boss in this dungeon\n");
    }
    else
    {
        printf("The boss is in this dungeon\n");
        printf("\tHealth Points: %d\n", dungeon->boss->health_points);
        printf("\tDamage: %d\n", dungeon->boss->damage);
        printf("\tPoints: %d\n", dungeon->boss->points);
        printf("\tRequired Item: %s\n",
               item_string(dungeon->boss->required_item));
    }

    printf("The dungeon %s has the following items:\n", dungeon->name);
}

char *class_string(struct player *player)
{
    if (strncmp(player->class_type, "Fighter", 8) == 0)
    {
        return "Fighter";
    }
    else if (strncmp(player->class_type, "Wizard", 7) == 0)
    {
        return "Wizard";
    }
    else
    {
        return "Unknown Class";
    }
}

char *item_string(enum item_type item)
{
    if (item == PHYSICAL_WEAPON)
    {
        return "Physical Weapon";
    }
    else if (item == MAGICAL_TOME)
    {
        return "Magical Tome";
    }
    else if (item == ARMOR)
    {
        return "Armor";
    }
    else if (item == HEALTH_POTION)
    {
        return "Health Potion";
    }
    else if (item == TREASURE)
    {
        return "Treasure";
    }
    else
    {
        return "Unknown Item";
    }
}

char *monster_string(enum monster_type monster)
{
    if (monster == SLIME)
    {
        return "Slime";
    }
    else if (monster == GOBLIN)
    {
        return "Goblin";
    }
    else if (monster == SKELETON)
    {
        return "Skeleton";
    }
    else if (monster == WOLF)
    {
        return "Wolf";
    }
    else
    {
        return "Unknown Monster";
    }
}

void print_boss_defeat()
{
    printf("The boss has been defeated!\n");
}

void print_empty_map()
{
    printf("There are no dungeons currently in the dungeon.\n");
}