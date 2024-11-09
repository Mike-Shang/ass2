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
    // Allocate memory for the map
    struct map *new_map = malloc(sizeof(struct map));
    if (new_map == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // Copy the map name
    strncpy(new_map->name, name, MAX_STR_LEN);
    new_map->name[MAX_STR_LEN - 1] = '\0'; // Ensure null-termination
    // Set the win requirement
    new_map->win_requirement = win_requirement;
    // Initialize other fields
    new_map->entrance = NULL; // No dungeons yet
    new_map->player = NULL;   // Player will be set later
    return new_map;
}

struct player *create_player(char *name, char *class_type)
{
    // Allocate memory for the player
    struct player *new_player = malloc(sizeof(struct player));
    if (new_player == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // Copy the player name and class type
    strncpy(new_player->name, name, MAX_STR_LEN);
    new_player->name[MAX_STR_LEN - 1] = '\0'; // Ensure null-termination
    strncpy(new_player->class_type, class_type, MAX_STR_LEN);
    new_player->class_type[MAX_STR_LEN - 1] = '\0'; // Ensure null-termination
    // Initialize stats based on class type
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
        // Default stats for unknown class
        new_player->health_points = 20;
        new_player->shield_power = 0;
        new_player->damage = 5;
        new_player->magic_modifier = 1.0;
    }
    // Initialize other fields
    new_player->inventory = NULL; // Empty inventory
    new_player->points = 0;
    new_player->class_power_used = 0; // Class power not used yet , new adding in stage 2.5
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
    // Allocate memory for the dungeon
    struct dungeon *new_dungeon = malloc(sizeof(struct dungeon));
    if (new_dungeon == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // Copy the dungeon name
    strncpy(new_dungeon->name, name, MAX_STR_LEN);
    new_dungeon->name[MAX_STR_LEN - 1] = '\0'; // Ensure null-termination
    // Set dungeon fields
    new_dungeon->monster = monster;
    new_dungeon->num_monsters = num_monsters;
    new_dungeon->contains_player = contains_player;
    // Initialize other fields
    new_dungeon->boss = NULL;          // Boss will be added later
    new_dungeon->items = NULL;         // No items yet
    new_dungeon->next = NULL;          // Next dungeon is NULL
    new_dungeon->monster_attacked = 0; // Initialize to 0 (not attacked)
    return new_dungeon;
}

int append_dungeon(struct map *map,
                   char *name,
                   enum monster_type monster,
                   int num_monsters)
{
    // Check for invalid name (already exists)
    struct dungeon *current = map->entrance;
    while (current != NULL)
    {
        if (strncmp(current->name, name, MAX_STR_LEN) == 0)
        {
            // Name already exists
            return INVALID_NAME;
        }
        current = current->next;
    }

    // Check for invalid monster type
    if (monster != SLIME && monster != GOBLIN &&
        monster != SKELETON && monster != WOLF)
    {
        return INVALID_MONSTER;
    }

    // Check for invalid number of monsters
    if (num_monsters < 1 || num_monsters > 10)
    {
        return INVALID_AMOUNT;
    }

    // Determine if the dungeon should contain the player
    int contains_player;
    if (map->entrance == NULL)
    {
        contains_player = 1;
    }
    else
    {
        contains_player = 0;
    }

    // Create the new dungeon
    struct dungeon *new_dungeon = create_dungeon(name, monster, num_monsters, contains_player);
    if (new_dungeon == NULL)
    {
        printf("Failed to create dungeon.\n");
        exit(1);
    }

    // Append the new dungeon to the map's dungeon list
    if (map->entrance == NULL)
    {
        // First dungeon, set as entrance
        map->entrance = new_dungeon;
        // Place the player in the map
        // Ensure map->player is not NULL
        if (map->player != NULL)
        {
            // Player is already created
            // Do nothing special here
        }
    }
    else
    {
        // Traverse to the end of the list and append
        current = map->entrance;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_dungeon;
    }

    // Return VALID to indicate success
    return VALID;
}

void print_map(struct map *map)
{
    if (map->entrance == NULL)
    {
        // Map is empty
        print_empty_map();
        return;
    }
    // Print the map's name
    print_map_name(map->name);
    // Get the player's name
    char *player_name = get_player_name(map->player);
    // Traverse the list of dungeons
    struct dungeon *current = map->entrance;
    int position = 1;
    while (current != NULL)
    {
        // Print the dungeon's basic details
        print_basic_dungeon(current, player_name, position);
        // Move to the next dungeon
        current = current->next;
        position++;
        // If there is a next dungeon, print the connection
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
    // Allocate memory for the boss
    struct boss *new_boss = malloc(sizeof(struct boss));
    if (new_boss == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // Set boss fields
    new_boss->health_points = health_points;
    new_boss->damage = damage;
    new_boss->points = points;
    new_boss->required_item = required_item;
    return new_boss;
}

int final_boss(struct map *map, enum item_type required_item)
{
    // Check for invalid required item
    if (required_item != PHYSICAL_WEAPON && required_item != MAGICAL_TOME &&
        required_item != ARMOR && required_item != HEALTH_POTION &&
        required_item != TREASURE)
    {
        return INVALID_ITEM;
    }

    // Create the boss with the given stats
    struct boss *new_boss = create_boss(35, 10, 20, required_item);

    // Find the last dungeon in the map
    struct dungeon *current = map->entrance;
    while (current->next != NULL)
    {
        current = current->next;
    }

    // Add the boss to the last dungeon
    current->boss = new_boss;

    // Return VALID to indicate success
    return VALID;
}

// change in stage 3.3
void player_stats(struct map *map)
{
    // Get the player's name
    // char *player_name = get_player_name(map->player);

    // Determine the dungeon name where the player is
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

    // Print the player's stats
    print_player(map->player, dungeon_name);

    // Print the player's items
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

int insert_dungeon(struct map *map, char *name, enum monster_type monster,
                   int num_monsters, int position)
{
    // 1. Check for invalid position
    if (position < 1)
    {
        return INVALID_POSITION;
    }

    // 2. Check for invalid name (already exists)
    struct dungeon *current = map->entrance;
    while (current != NULL)
    {
        if (strncmp(current->name, name, MAX_STR_LEN) == 0)
        {
            // Name already exists
            return INVALID_NAME;
        }
        current = current->next;
    }

    // 3. Check for invalid monster type
    if (monster != SLIME && monster != GOBLIN &&
        monster != SKELETON && monster != WOLF)
    {
        return INVALID_MONSTER;
    }

    // 4. Check for invalid number of monsters
    if (num_monsters < 1 || num_monsters > 10)
    {
        return INVALID_AMOUNT;
    }

    // Create the new dungeon
    int contains_player = 0; // By default, the new dungeon doesn't contain the player
    struct dungeon *new_dungeon = create_dungeon(name, monster, num_monsters, contains_player);
    if (new_dungeon == NULL)
    {
        printf("Failed to create dungeon.\n");
        exit(1);
    }

    // Insert the new dungeon at the specified position
    if (position == 1)
    {
        // New dungeon becomes the new entrance
        new_dungeon->next = map->entrance;
        map->entrance = new_dungeon;

        // Update player position
        // Remove player from previous dungeon
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
        // Place player in the new entrance dungeon
        new_dungeon->contains_player = 1;
    }
    else
    {
        // Insert at position or at the tail if position is beyond the length
        current = map->entrance;
        int index = 1;
        struct dungeon *prev = NULL;

        while (current != NULL && index < position)
        {
            prev = current;
            current = current->next;
            index++;
        }

        // Insert new dungeon between prev and current
        prev->next = new_dungeon;
        new_dungeon->next = current;
    }

    return VALID;
}

void print_dungeon(struct map *map)
{
    // Find the dungeon where the player is currently in
    struct dungeon *current = map->entrance;
    while (current != NULL)
    {
        if (current->contains_player)
        {
            // Found the dungeon containing the player
            break;
        }
        current = current->next;
    }

    if (current == NULL)
    {
        // Player is not in any dungeon
        printf("Player is not in any dungeon.\n");
        return;
    }

    // Get the player's name
    char *player_name = get_player_name(map->player);

    // Print dungeon details
    print_detail_dungeon(player_name, current);

    // Print items in the dungeon
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
    // Find the current dungeon where the player is
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
        // Player not found in any dungeon
        return INVALID;
    }

    if (command == NEXT_DUNGEON)
    {
        // Move to the next dungeon
        next = current->next;
        if (next == NULL)
        {
            // No next dungeon to move into
            return INVALID;
        }
        current->contains_player = 0;
        next->contains_player = 1;
    }
    else if (command == PREVIOUS_DUNGEON)
    {
        // Move to the previous dungeon
        if (previous == NULL)
        {
            // No previous dungeon to move into
            return INVALID;
        }
        current->contains_player = 0;
        previous->contains_player = 1;
    }
    else
    {
        // Invalid command
        return INVALID;
    }

    return VALID;
}

int fight(struct map *map, char command)
{
    // Find the current dungeon where the player is
    struct dungeon *current = map->entrance;
    while (current != NULL)
    {
        if (current->contains_player)
        {
            break;
        }
        current = current->next;
    }

    if (current == NULL)
    {
        // Player not found in any dungeon
        return INVALID;
    }

    if (current->num_monsters <= 0)
    {
        // No monsters to fight
        return INVALID;
    }

    // Calculate player's attack power
    double player_attack;
    if (command == PHYSICAL_ATTACK)
    {
        player_attack = map->player->damage;
    }
    else if (command == MAGICAL_ATTACK)
    {
        player_attack = map->player->damage * map->player->magic_modifier;
    }
    else
    {
        // Invalid command
        return INVALID;
    }

    // Get monster stats based on monster type
    int monster_health = current->monster;
    int monster_points = current->monster;

    int monsters_defeated = 0;
    double remaining_attack = player_attack;

    // Attack monsters one by one
    for (int i = 0; i < current->num_monsters; i++)
    {
        if (remaining_attack >= monster_health)
        {
            // Monster is defeated
            remaining_attack -= monster_health;
            monsters_defeated++;
        }
        else
        {
            // Not enough attack power to defeat more monsters
            break;
        }
    }

    // Update number of monsters in the dungeon
    current->num_monsters -= monsters_defeated;

    // Calculate points earned
    int points_earned = monsters_defeated * monster_points;
    map->player->points += points_earned;

    // Mark that monsters in this dungeon have been attacked
    if (monsters_defeated > 0)
    {
        current->monster_attacked = 1; // Add this field to dungeon struct if needed
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

    // Find the dungeon where the player is
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

    // Reset current to start
    current = map->entrance;

    // Process monster attacks
    while (current != NULL)
    {
        if (current->num_monsters > 0)
        {
            int monster_damage = current->monster;
            int total_damage = 0;

            // Check if monsters should attack
            if (current == player_dungeon && current->monster_attacked)
            {
                // Monsters in the player's dungeon attack
                total_damage = monster_damage * current->num_monsters;
            }
            else if (current == player_dungeon && current->monster == WOLF)
            {
                // Wolves attack every turn if player is in the same dungeon
                total_damage = monster_damage * current->num_monsters;
            }
            // Apply shield
            total_damage -= player->shield_power;
            if (total_damage < 0)
            {
                total_damage = 0;
            }

            // Reduce player's health
            if (total_damage > 0)
            {
                player->health_points -= total_damage;
                // Do not print in this function; printing is handled in main.c
            }
        }
        current = current->next;
    }

    // Check if player has been defeated
    if (player->health_points <= 0)
    {
        return PLAYER_DEFEATED;
    }

    // Remove empty dungeons (excluding the dungeon the player is in)
    current = map->entrance;
    previous = NULL;

    while (current != NULL)
    {
        // Check if the dungeon is empty and not the player's current dungeon
        if (current != player_dungeon &&
            current->num_monsters == 0 &&
            current->boss == NULL &&
            current->items == NULL)
        {
            // Remove the dungeon from the map
            struct dungeon *to_delete = current;

            if (previous == NULL)
            {
                // Removing the entrance dungeon
                map->entrance = current->next;
                current = map->entrance;
            }
            else
            {
                previous->next = current->next;
                current = previous->next;
            }

            // Free the dungeon's memory
            free_dungeon(to_delete);
        }
        else
        {
            // Move to the next dungeon
            previous = current;
            current = current->next;
        }
    }

    // Check if player meets win conditions
    int points_required = map->win_requirement;

    if (player->points >= points_required)
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
                    // Boss is still alive
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

    // Continue game
    return CONTINUE_GAME;
}

int class_power(struct map *map)
{
    struct player *player = map->player;

    // Check if the class power has already been used
    if (player->class_power_used == 1)
    {
        return INVALID;
    }

    // Mark the class power as used
    player->class_power_used = 1;

    // Apply effects based on class type
    if (strcmp(player->class_type, "Fighter") == 0)
    {
        // Increase damage by 1.5 times
        player->damage = (int)(player->damage * 1.5);
    }
    else if (strcmp(player->class_type, "Wizard") == 0)
    {
        // Find the current dungeon
        struct dungeon *current = map->entrance;
        while (current != NULL)
        {
            if (current->contains_player)
            {
                break;
            }
            current = current->next;
        }

        if (current == NULL)
        {
            // Player is not in any dungeon
            return INVALID;
        }

        // Calculate points earned from defeating all monsters
        int num_monsters = current->num_monsters;
        if (num_monsters > 0)
        {
            int monster_points = current->monster;
            int total_points = num_monsters * monster_points;

            // Add points to player
            player->points += total_points;

            // Remove all monsters
            current->num_monsters = 0;

            // Note: Boss is not affected
        }
    }
    else
    {
        // Unknown class type
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
    // Allocate memory for the item
    struct item *new_item = malloc(sizeof(struct item));
    if (new_item == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Initialize fields
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
    // 1. Check for invalid dungeon number
    if (dungeon_number < 1)
    {
        return INVALID_DUNGEON;
    }

    // Find the dungeon at position dungeon_number
    struct dungeon *current = map->entrance;
    int position = 1;
    while (current != NULL && position < dungeon_number)
    {
        current = current->next;
        position++;
    }

    if (current == NULL)
    {
        // Dungeon not found
        return INVALID_DUNGEON;
    }

    // 2. Check for invalid item type
    if (type < PHYSICAL_WEAPON || type > TREASURE)
    {
        return INVALID_ITEM;
    }

    // 3. Check for invalid point value
    if (points < 1 || points > 10)
    {
        return INVALID_POINTS;
    }

    // Create the new item
    struct item *new_item = create_item(type, points);

    // Insert the item into the dungeon's item list in the correct position
    // Items should be added in the order of the enum, with same types grouped together

    struct item *prev = NULL;
    struct item *item_current = current->items;

    // Move forward while item's type is less than the new item's type
    while (item_current != NULL && item_current->type < type)
    {
        prev = item_current;
        item_current = item_current->next;
    }

    // Now, move forward while item's type equals the new item's type
    while (item_current != NULL && item_current->type == type)
    {
        prev = item_current;
        item_current = item_current->next;
    }

    // Insert the new item between prev and item_current

    if (prev == NULL)
    {
        // Insert at the beginning
        new_item->next = current->items;
        current->items = new_item;
    }
    else
    {
        // Insert between prev and item_current
        prev->next = new_item;
        new_item->next = item_current;
    }

    return VALID;
}

int collect_item(struct map *map, int item_number)
{
    // Find the current dungeon where the player is
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
        // Player is not in any dungeon
        return INVALID_ITEM; // or INVALID
    }

    if (item_number < 1)
    {
        // Invalid item number
        return INVALID_ITEM;
    }

    // Traverse the items in the dungeon to find the item_number
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
        // Item number does not correspond to an item in the dungeon
        return INVALID_ITEM;
    }

    // Remove the item from the dungeon's item list
    if (prev_item == NULL)
    {
        // The item is the first in the list
        current_dungeon->items = curr_item->next;
    }
    else
    {
        prev_item->next = curr_item->next;
    }

    // Add the item to the head of the player's inventory
    curr_item->next = map->player->inventory;
    map->player->inventory = curr_item;

    return VALID;
}

int use_item(struct map *map, int item_number)
{
    struct player *player = map->player;

    if (item_number < 1)
    {
        // Invalid item number
        return INVALID_ITEM; // or INVALID
    }

    // Traverse the player's inventory to find the item_number
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
        // Item number does not correspond to an item in the inventory
        return INVALID_ITEM;
    }

    // Apply the item's effect on the player's stats
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
        // No effect on player's stats
        break;
    default:
        // Should not reach here
        break;
    }

    // Add the item's point value to the player's collected points
    player->points += curr_item->points;

    // Remove the item from the player's inventory
    if (prev_item == NULL)
    {
        // Item is at the head of the inventory
        player->inventory = curr_item->next;
    }
    else
    {
        prev_item->next = curr_item->next;
    }

    // Free the item's memory
    free(curr_item);

    return VALID;
}

void free_map(struct map *map)
{
    // Free all dungeons
    struct dungeon *current_dungeon = map->entrance;
    while (current_dungeon != NULL)
    {
        struct dungeon *next_dungeon = current_dungeon->next;
        free_dungeon(current_dungeon);
        current_dungeon = next_dungeon;
    }

    // Free the player
    free_player(map->player);

    // Free the map itself
    free(map);
}

// Your functions here (include function comments):

void free_dungeon(struct dungeon *dungeon)
{
    // Free the dungeon's name
    // If name was dynamically allocated, but if it's a fixed-size array, skip this step.

    // Free items in the dungeon
    struct item *current_item = dungeon->items;
    while (current_item != NULL)
    {
        struct item *next_item = current_item->next;
        free(current_item);
        current_item = next_item;
    }

    // Free the boss (if any)
    if (dungeon->boss != NULL)
    {
        free(dungeon->boss);
    }

    // Free the dungeon itself
    free(dungeon);
}

void free_player(struct player *player)
{
    // Free items in the player's inventory
    struct item *current_item = player->inventory;
    while (current_item != NULL)
    {
        struct item *next_item = current_item->next;
        free(current_item);
        current_item = next_item;
    }

    // Free the player itself
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