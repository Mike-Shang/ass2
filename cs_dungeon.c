// Assignment 2 24T3 COMP1511: CS Dungeon
// cs_dungeon.c
//
// Fangyuan SHANG z5614452
// 10 30 2024 DMY
//
// Version 1.0.0: Assignment released.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cs_dungeon.h"

// Add any extra #includes your code needs here.

////////////////////////////////////////////////////////////////////////////////
//                                 Constants                                  //
////////////////////////////////////////////////////////////////////////////////

// Add your own #defines here:

#define IS_ACTIVE 1
#define IS_TURE 0
#define IS_CONDITION 1

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

    // New add
    int monster_attacked;
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

    // new adding by myself
    int class_power_used; // 0 if not used, 1 if used
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

// my function declaration

void free_dungeon(struct dungeon *dungeon);
void free_player(struct player *player);

////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//                             Stage 1 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Provided Function stubs:

struct map *create_map(char *name, int win_requirement)
{
    struct map *new_map = malloc(sizeof(struct map));
    if (new_map == NULL)
    {

        printf("Memory allocation failed.\n");

        exit(1);
    }

    strncpy(new_map->name, name, MAX_STR_LEN);

    new_map->name[MAX_STR_LEN - 1] = '\0';

    new_map->win_requirement = win_requirement;

    new_map->entrance = NULL;

    new_map->player = NULL;
    return new_map;
}

struct player *create_player(char *name, char *class_type)
{

    struct player *new_player = malloc(sizeof(struct player));

    if (new_player == NULL)
    {

        printf("Memory allocation failed.\n");

        exit(1);
    }

    strncpy(new_player->name, name, MAX_STR_LEN);

    new_player->name[MAX_STR_LEN - 1] = '\0';

    strncpy(new_player->class_type, class_type, MAX_STR_LEN);

    new_player->class_type[MAX_STR_LEN - 1] = '\0';

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

        new_player->health_points = 20;
        new_player->shield_power = 0;
        new_player->damage = 5;
        new_player->magic_modifier = 1.0;
    }

    new_player->inventory = NULL;
    new_player->points = 0;
    new_player->class_power_used = 0;
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
struct dungeon *create_dungeon(char *name, enum monster_type monster,
                               int num_monsters, int contains_player)
{

    struct dungeon *new_dungeon = malloc(sizeof(struct dungeon));
    if (new_dungeon == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strncpy(new_dungeon->name, name, MAX_STR_LEN);
    new_dungeon->name[MAX_STR_LEN - 1] = '\0';

    new_dungeon->monster = monster;
    new_dungeon->num_monsters = num_monsters;
    new_dungeon->contains_player = contains_player;

    new_dungeon->boss = NULL;
    new_dungeon->items = NULL;
    new_dungeon->next = NULL;
    new_dungeon->monster_attacked = 0;

    return new_dungeon;
}

int append_dungeon(struct map *map,
                   char *name,
                   enum monster_type monster,
                   int num_monsters)
{

    struct dungeon *current = map->entrance;
    while (current != NULL)
    {
        if (strncmp(current->name, name, MAX_STR_LEN) == 0)
        {

            return INVALID_NAME;
        }
        current = current->next;
    }

    if (monster != SLIME && monster != GOBLIN &&
        monster != SKELETON && monster != WOLF)
    {
        return INVALID_MONSTER;
    }

    if (num_monsters < 1 || num_monsters > 10)
    {
        return INVALID_AMOUNT;
    }

    int contains_player;
    if (map->entrance == NULL && IS_ACTIVE == IS_CONDITION)
    {
        contains_player = 1;
    }
    else
    {
        contains_player = 0;
    }

    struct dungeon *new_dungeon = create_dungeon(name, monster,
                                                 num_monsters,
                                                 contains_player);
    if (new_dungeon == NULL)
    {
        printf("Failed to create dungeon.\n");
        exit(1);
    }

    if (map->entrance == NULL)
    {

        map->entrance = new_dungeon;

        if (map->player != NULL)
        {
        }
    }
    else
    {

        current = map->entrance;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_dungeon;
    }

    return VALID;
}

void print_map(struct map *map)
{
    if (map->entrance == NULL && IS_ACTIVE == IS_CONDITION)
    {

        print_empty_map();
        return;
    }

    print_map_name(map->name);

    char *player_name = get_player_name(map->player);

    struct dungeon *current = map->entrance;
    int position = 1;
    while (current != NULL)
    {
        print_basic_dungeon(current, player_name, position);

        current = current->next;
        position++;

        if (current != NULL)
        {
            print_connection();
        }
    }
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

    struct boss *new_boss = malloc(sizeof(struct boss));
    if (new_boss == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    new_boss->health_points = health_points;
    new_boss->damage = damage;
    new_boss->points = points;
    new_boss->required_item = required_item;
    return new_boss;
}

int final_boss(struct map *map, enum item_type required_item)
{

    if (required_item != PHYSICAL_WEAPON && required_item != MAGICAL_TOME &&
        required_item != ARMOR && required_item != HEALTH_POTION &&
        required_item != TREASURE)
    {
        return INVALID_ITEM;
    }

    struct boss *new_boss = create_boss(35, 10, 20, required_item);

    struct dungeon *current = map->entrance;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->boss = new_boss;

    return VALID;
}

// change in stage 3.3
void player_stats(struct map *map)
{

    char *dungeon_name = NULL;
    struct dungeon *current = map->entrance;
    while (current != NULL)
    {
        if (current->contains_player)
        {
            dungeon_name = current->name;
            break;
        }
        current = current->next;
    }

    print_player(map->player, dungeon_name);

    if (map->player->inventory == NULL)
    {
        print_no_items();
    }
    else
    {
        struct item *current_item = map->player->inventory;
        int item_number = 1;
        while (current_item != NULL)
        {
            print_item(current_item, item_number);
            current_item = current_item->next;
            item_number++;
        }
    }
}

// Your functions go here (include function comments):

////////////////////////////////////////////////////////////////////////////////
//                             Stage 2 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Provided function stubs:

int insert_dungeon(struct map *map, char *name,
                   enum monster_type monster,
                   int num_monsters, int position)
{

    if (position < 1)
    {
        return INVALID_POSITION;
    }

    struct dungeon *current = map->entrance;
    while (current != NULL)
    {
        if (strncmp(current->name, name, MAX_STR_LEN) == 0)
        {

            return INVALID_NAME;
        }
        current = current->next;
    }

    if (monster != SLIME && monster != GOBLIN &&
        monster != SKELETON && monster != WOLF)
    {
        return INVALID_MONSTER;
    }

    if (num_monsters < 1 || num_monsters > 10)
    {
        return INVALID_AMOUNT;
    }

    int contains_player = 0;
    struct dungeon *new_dungeon = create_dungeon(name, monster,
                                                 num_monsters, contains_player);
    if (new_dungeon == NULL)
    {
        printf("Failed to create dungeon.\n");
        exit(1);
    }

    if (position == 1)
    {

        new_dungeon->next = map->entrance;
        map->entrance = new_dungeon;

        current = new_dungeon->next;
        while (current != NULL)
        {
            if (current->contains_player)
            {
                current->contains_player = 0;
                break;
            }
            current = current->next;
        }

        new_dungeon->contains_player = 1;
    }
    else
    {

        current = map->entrance;
        int index = 1;
        struct dungeon *prev = NULL;

        while (current != NULL && index < position)
        {
            prev = current;
            current = current->next;
            index++;
        }

        prev->next = new_dungeon;
        new_dungeon->next = current;
    }

    return VALID;
}

void print_dungeon(struct map *map)
{

    struct dungeon *current = map->entrance;
    while (current != NULL)
    {
        if (current->contains_player)
        {
            break;
        }
        current = current->next;
    }

    if (current == NULL && IS_ACTIVE == IS_CONDITION)
    {
        printf("Player is not in any dungeon.\n");
        return;
    }

    char *player_name = get_player_name(map->player);

    print_detail_dungeon(player_name, current);

    if (current->items == NULL)
    {
        print_no_items();
    }
    else
    {
        struct item *item_current = current->items;
        int item_number = 1;
        while (item_current != NULL)
        {
            print_item(item_current, item_number);
            item_current = item_current->next;
            item_number++;
        }
    }
}

int move_player(struct map *map, char command)
{
    struct dungeon *current = map->entrance;
    struct dungeon *previous = NULL;
    struct dungeon *next = NULL;

    while (current != NULL)
    {
        if (current->contains_player)
        {
            break;
        }
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        return INVALID;
    }

    if (command == NEXT_DUNGEON && IS_ACTIVE == IS_CONDITION)
    {
        next = current->next;
        if (next == NULL)
        {
            return INVALID;
        }
        current->contains_player = 0;
        next->contains_player = 1;
    }
    else if (command == PREVIOUS_DUNGEON)
    {
        if (previous == NULL)
        {
            return INVALID;
        }
        current->contains_player = 0;
        previous->contains_player = 1;
    }
    else
    {
        return INVALID;
    }

    return VALID;
}

int fight(struct map *map, char command)
{
    struct dungeon *current = map->entrance;
    while (current != NULL)
    {
        if (current->contains_player && IS_ACTIVE == IS_CONDITION)
        {
            break;
        }
        current = current->next;
    }

    if (current == NULL)
    {
        return INVALID;
    }

    if (current->num_monsters <= 0)
    {
        return INVALID;
    }

    double player_attack;
    if (command == PHYSICAL_ATTACK)
    {
        player_attack = map->player->damage;
    }
    else if (command == MAGICAL_ATTACK)
    {
        player_attack = map->player->damage *
                        map->player->magic_modifier;
    }
    else
    {
        return INVALID;
    }

    int monster_health = current->monster;
    int monster_points = current->monster;

    int monsters_defeated = 0;
    double remaining_attack = player_attack;

    for (int i = 0; i < current->num_monsters; i++)
    {
        if (remaining_attack >= monster_health)
        {
            remaining_attack -= monster_health;
            monsters_defeated++;
        }
        else
        {
            break;
        }
    }

    current->num_monsters -= monsters_defeated;

    int points_earned = monsters_defeated * monster_points;
    map->player->points += points_earned;

    if (monsters_defeated > 0 && IS_ACTIVE == IS_CONDITION)
    {
        current->monster_attacked = 1;
    }

    return VALID;
}

// change in stage 3.1
// change in stage 3.5

int end_turn(struct map *map)
{
    struct dungeon *current = map->entrance;
    struct dungeon *previous = NULL;
    struct player *player = map->player;

    struct dungeon *player_dungeon = NULL;
    while (current != NULL)
    {
        if (current->contains_player)
        {
            player_dungeon = current;
            break;
        }
        current = current->next;
    }

    current = map->entrance;

    while (current != NULL)
    {
        if (current->num_monsters > 0)
        {
            int monster_damage = current->monster;
            int total_damage = 0;

            if (current == player_dungeon && current->monster_attacked)
            {
                total_damage = monster_damage * current->num_monsters;
            }
            else if (current == player_dungeon && current->monster == WOLF)
            {
                total_damage = monster_damage * current->num_monsters;
            }
            total_damage -= player->shield_power;
            if (total_damage < 0)
            {
                total_damage = 0;
            }

            if (total_damage > 0)
            {
                player->health_points -= total_damage;
            }
        }
        current = current->next;
    }

    if (player->health_points <= 0)
    {
        return PLAYER_DEFEATED;
    }

    current = map->entrance;
    previous = NULL;

    while (current != NULL)
    {

        if (current != player_dungeon &&
            current->num_monsters == 0 &&
            current->boss == NULL &&
            current->items == NULL)
        {
            struct dungeon *to_delete = current;

            if (previous == NULL)
            {
                map->entrance = current->next;
                current = map->entrance;
            }
            else
            {
                previous->next = current->next;
                current = previous->next;
            }

            free_dungeon(to_delete);
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    int points_required = map->win_requirement;

    if (player->points >= points_required && IS_ACTIVE == IS_CONDITION)
    {
        int all_monsters_defeated = 1;
        int boss_defeated = 0;

        current = map->entrance;
        while (current != NULL)
        {
            if (current->num_monsters > 0)
            {
                all_monsters_defeated = 0;
            }
            if (current->boss != NULL)
            {
                if (current->boss->health_points <= 0)
                {
                    boss_defeated = 1;
                }
                else
                {
                    boss_defeated = 0;
                }
            }
            current = current->next;
        }

        if (boss_defeated)
        {
            return WON_BOSS;
        }
        else if (all_monsters_defeated)
        {
            return WON_MONSTERS;
        }
    }

    return CONTINUE_GAME;
}

int class_power(struct map *map)
{
    struct player *player = map->player;

    if (player->class_power_used == 1)
    {
        return INVALID;
    }

    player->class_power_used = 1;

    if (strcmp(player->class_type, "Fighter") == 0)
    {
        player->damage = (int)(player->damage * 1.5);
    }
    else if (strcmp(player->class_type, "Wizard") == 0)
    {
        struct dungeon *current = map->entrance;
        while (current != NULL)
        {
            if (current->contains_player && IS_ACTIVE == IS_CONDITION)
            {
                break;
            }
            current = current->next;
        }

        if (current == NULL)
        {
            return INVALID;
        }

        int num_monsters = current->num_monsters;
        if (num_monsters > 0)
        {
            int monster_points = current->monster;
            int total_points = num_monsters * monster_points;

            player->points += total_points;

            current->num_monsters = 0;
        }
    }
    else
    {
        return INVALID;
    }

    return VALID;
}

// Your functions go here (include function comments):

////////////////////////////////////////////////////////////////////////////////
//                             Stage 3 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Provided function stubs:

// change the end_turn !!!!!!!

struct item *create_item(enum item_type type, int points)
{
    struct item *new_item = malloc(sizeof(struct item));
    if (new_item == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    new_item->type = type;
    new_item->points = points;
    new_item->next = NULL;

    return new_item;
}

int add_item(struct map *map,
             int dungeon_number,
             enum item_type type,
             int points)
{
    if (dungeon_number < 1 && IS_ACTIVE == IS_CONDITION)
    {
        return INVALID_DUNGEON;
    }

    struct dungeon *current = map->entrance;
    int position = 1;
    while (current != NULL && position < dungeon_number)
    {
        current = current->next;
        position++;
    }

    if (current == NULL)
    {
        return INVALID_DUNGEON;
    }

    if (type < PHYSICAL_WEAPON || type > TREASURE)
    {
        return INVALID_ITEM;
    }

    if (points < 1 || points > 10)
    {
        return INVALID_POINTS;
    }

    struct item *new_item = create_item(type, points);

    struct item *prev = NULL;
    struct item *item_current = current->items;

    while (item_current != NULL && item_current->type < type)
    {
        prev = item_current;
        item_current = item_current->next;
    }

    while (item_current != NULL && item_current->type == type)
    {
        prev = item_current;
        item_current = item_current->next;
    }

    if (prev == NULL)
    {
        new_item->next = current->items;
        current->items = new_item;
    }
    else
    {
        prev->next = new_item;
        new_item->next = item_current;
    }

    return VALID;
}

int collect_item(struct map *map, int item_number)
{
    struct dungeon *current_dungeon = map->entrance;
    while (current_dungeon != NULL)
    {
        if (current_dungeon->contains_player)
        {
            break;
        }
        current_dungeon = current_dungeon->next;
    }

    if (current_dungeon == NULL)
    {

        return INVALID_ITEM;
    }

    if (item_number < 1)
    {
        return INVALID_ITEM;
    }

    struct item *prev_item = NULL;
    struct item *curr_item = current_dungeon->items;
    int current_item_number = 1;

    while (curr_item != NULL && current_item_number < item_number)
    {
        prev_item = curr_item;
        curr_item = curr_item->next;
        current_item_number++;
    }

    if (curr_item == NULL || current_item_number != item_number)
    {
        return INVALID_ITEM;
    }

    if (prev_item == NULL && IS_ACTIVE == IS_CONDITION)
    {
        current_dungeon->items = curr_item->next;
    }
    else
    {
        prev_item->next = curr_item->next;
    }

    curr_item->next = map->player->inventory;
    map->player->inventory = curr_item;

    return VALID;
}

int use_item(struct map *map, int item_number)
{
    struct player *player = map->player;

    if (item_number < 1)
    {

        return INVALID_ITEM;
    }

    struct item *prev_item = NULL;
    struct item *curr_item = player->inventory;
    int current_item_number = 1;

    while (curr_item != NULL && current_item_number < item_number)
    {
        prev_item = curr_item;
        curr_item = curr_item->next;
        current_item_number++;
    }

    if (curr_item == NULL || current_item_number != item_number)
    {
        return INVALID_ITEM;
    }

    switch (curr_item->type)
    {
    case PHYSICAL_WEAPON:
        player->damage += curr_item->points;
        break;
    case MAGICAL_TOME:
        player->magic_modifier += (curr_item->points) / 10.0;
        break;
    case ARMOR:
        player->shield_power += curr_item->points / 2;
        break;
    case HEALTH_POTION:
        player->health_points += curr_item->points + 5;
        if (player->health_points > MAX_HEALTH)
        {
            player->health_points = MAX_HEALTH;
        }
        break;
    case TREASURE:
        break;
    default:
        break;
    }

    player->points += curr_item->points;

    if (prev_item == NULL && IS_ACTIVE == IS_CONDITION)
    {
        player->inventory = curr_item->next;
    }
    else
    {
        prev_item->next = curr_item->next;
    }

    free(curr_item);

    return VALID;
}

void free_map(struct map *map)
{
    struct dungeon *current_dungeon = map->entrance;
    while (current_dungeon != NULL)
    {
        struct dungeon *next_dungeon = current_dungeon->next;
        free_dungeon(current_dungeon);
        current_dungeon = next_dungeon;
    }

    free_player(map->player);

    free(map);
}

// Your functions here (include function comments):

void free_dungeon(struct dungeon *dungeon)
{

    struct item *current_item = dungeon->items;
    while (current_item != NULL)
    {
        struct item *next_item = current_item->next;
        free(current_item);
        current_item = next_item;
    }

    if (dungeon->boss != NULL && IS_ACTIVE == IS_CONDITION)
    {
        free(dungeon->boss);
    }

    free(dungeon);
}

void free_player(struct player *player)
{
    struct item *current_item = player->inventory;
    while (current_item != NULL)
    {
        struct item *next_item = current_item->next;
        free(current_item);
        current_item = next_item;
    }

    free(player);
}

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