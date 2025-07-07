# off the dome, no references trying to work out logic
# will we get close? only time will tell

# object definitions (keep schema consistent overall, teach during activities)

#############
### Notes ###
#############

# started at 9:30PM
# ended at 1:30AM

# variables -> types -> classes (a new type of object)
# print statements -> format print statements -> f strings
# string methods (.join(), upper/lower/split/strip) (day 1 project task to create the "welcome" screen?)

# while True game loop w/ exit condition on day 2 (not proj task, guided task)
# separate file for each day (so they can learn to reference)
# can write the "enter" function on day 2 (as the project task?) would have to implement once without object attributes tho...
# day 3 to create basic control flow in input() ("move north/east/west/south", "use item"(function?))
# difference between instance & class (instance attributes & class attributes)

# NOTE: this is basically advanced mad libs. im having a hard time keeping the functionality simple lol
# NOTE: this implementation is NOT completely bug free. the biggest issues arise from type errors, attribute errors, and key errors from doing incorrect combinations of stuff. let them have a "QA tester" time period.

#############

# class definitions. these are the "nouns" in the sentence / things players interact with
# classes should literally just be objects to store attributes. had a suggestion to have one method to let player location. very simple attribute changing method

class Room:
    def __init__(self, name, description):
        self.name = name
        self.description = description # shorthand description
        self.exits = {} # schema -> direction(str): room(Room)
        self.items = []


class Player:
    def __init__(self, name, location):
        self.name = name
        self.location = location
        self.items = []

    def set_location(self, location):
        self.location = location # idk how intuitive this is bc 'self.location' and 'location' are technically different but don't seem like it

class Item:
    def __init__(self, name, description, is_movable=True): #potential consumable attribute? NOTE: probably too complicated.
        self.name = name
        self.description = description # shorthand description
        self.removable = is_movable
        self.valid_targets = {} # item(Item): interaction description(str)
        # valid targets are other items that this item can be used on.
        # interaction description should be a present singular verb (unlock, hit, etc.)
        # for use in the use() function. NOTE: probably too complicated, but i don't know how to do object interactions otherwise.

#############

# core function definitions. these are the "verbs" in the sentence / actions players can take (NOTE: is this too complicated?)

def enter(room, player):

        directions = (i+" ("+j.name+")" for i,j in room.exits.items()) # uh... i don't know how else to do this lol

        print("\n")
        print(f"You enter the {room.name}. Before you is {room.description}.\n")
        print("Exits: ")
        print(", ".join(directions))
        print("\n")
        
        if room.items != []:
            print(f"In the {room.name}, you can see the following: ")
            print(", ".join([i.name for i in room.items]))
            print("\n")

        else:
            print(f"You do not see any items in this {room.name}.")
            print("\n")

        player.set_location(room) # using object methods

def use(actor, target):
    # if the actor has the target in their valid_targets dict (as a key), print the interaction.

    # potential remix prompt: what if we just wanted to use an item that doesn't need a target?

    # NOTE: may need to rewrite this to be less generalized and more hard-coded to check for SPECIFIC object interactions & not general ones.
    # if you see lower down, we check for specific object interactions anyways, so this function seems a little niche.
    # i think we should probably just hard code object interactions...

    print(f"You attempt to use the {actor.name} on the {target}...\n")

    if target in actor.valid_targets.keys():
        print("Success!")
        print(f"You use the {actor.name} to {actor.valid_targets[target]} the {target}.")
        print("\n")
    else:
        print("Hm. Nothing happens...")
        print("\n")

def examine(item):
    print(f"Examining the {item.name} closer, you see {item.description}\n.")
    print(f"You could try to take it or use it on something. Or not.")
    print("\n")

def take(item, player):
    if item.removable:
        player.items.append(item)
        print(f"You picked up the {item.name}.")
        print("\n")
    else:
        print(f"You can't remove the {item.name}.")
        print("\n")

#############

# instances to set up the game :3 this is where the creative stuff goes

# items
sword = Item("sword","an old rusty sword", True)
door = Item("door","a rickety door with a silver padlock", False)
chest = Item("chest","a large chest that looks newer than the rest of the room", False)
mimic = Item("mimic","a large monster shaped like a wooden chest that is blocking the door", False)
key = Item("key","a shiny silver key", True)


# item interaction logic ("logic")
sword.valid_targets[door] = "break"
sword.valid_targets[mimic] = "slice"
key.valid_targets[door] = "unlock"

# rooms
cave = Room("cave", "the beginning of a cave with the entrance blocked off by rubble")

left_tunnel = Room("left tunnel", "a small carved out tunnel with a skeleton holding an old sword at the dead end")
right_tunnel = Room("right tunnel", "a long, dark tunnel with a wide cavern opening ahead")
cavern = Room("cavern", "an open underground cavern with a small cottage in the middle and a large metal door at the back")
cottage = Room("cottage", "an old, ratty single room cottage with a large chest in one corner")

cave.exits = {
    "left": left_tunnel,
    "right": right_tunnel
}
left_tunnel.exits = {
    "right": cave
}
left_tunnel.items.append(sword)

right_tunnel.exits = {
    "left": cave,
    "up": cavern
}

cavern.exits = {
    "down": right_tunnel,
    "up": cottage
}

cottage.exits = {
    "down": cavern
}
cottage.items.append(door)
cottage.items.append(chest)

#############

rooms = []
items = []

player = Player("Guy", cave)

def main():
    print("###############################################\n")
    print(f"Hey there, {player.name}!\n")
    print("While you were walking in the woods, you slipped and fell into a hole in the ground.\n")
    print("Thankfully it wasn't a spike trap or anything, but you find yourself in a cave. The entrance is blocked of by rubble, and the only way out is forward through one of two tunnels.")
    enter(cave, player)

    while True:

        # couple things to note:
        ### 1: this while True block doesn't account for noun/verb combinations that don't work (like trying to use() a room). those will throw type errors, so we need the try/except block to catch them

        action = input("\nWhat do you do now?\n")
        action_processed = action.lower().split()

        current_room = player.location

        noun = None

        # if block for noun (items)

        try:
            if "sword" in action_processed:
                noun = sword
            
            elif "door" in action_processed:
                noun = door

            elif "chest" in action_processed:
                noun = chest

            elif "mimic" in action_processed:
                noun = mimic

            elif "key" in action_processed:
                noun = key

            # potential for special cases here? like specific combinations of nouns/verbs?
            # as stated above, i'm pretty sure we shouldn't be doing a general "use" function, and should instead have the use function the following blocks to check for specific interactions.

            if "examine" in action_processed and "chest" in action_processed:
                print("\nUh oh. As you try to back away from the chest, you see eyes and teeth pop out! It's a mimic!")
                cottage.items.remove(chest)
                cottage.items.append(mimic)
                continue
            

            # nested if block for movement
            # honestly we could probably do a case/switch statement here
            # this is a really stupid implementation but it was 1AM at this point i think

            if "move" in action_processed:
                
                try:
                    if "up" in action_processed:
                        next_room = current_room.exits["up"]
                        enter(next_room, player)

                    elif "down" in action_processed:
                        next_room = current_room.exits["down"]
                        enter(next_room, player)

                    elif "left" in action_processed:
                        next_room = current_room.exits["left"]
                        enter(next_room, player)
                    
                    elif "right" in action_processed:
                        next_room = current_room.exits["right"]
                        enter(next_room, player)

                    else:
                        print("You can't move there! Try up/down/left/right !\n")
                except KeyError:
                    print("That's not a direction with an exit in this room. Try somewhere else!\n")
                
                

            # if block for use

            elif "use" in action_processed: # see? this should just be the use function i think...
                target = input(f"What would you like to use the {noun.name} on?\n")
                if target == "mimic" and noun == sword:
                    print("You slice the mimic in half with your s,word! Now dead, its maw opens, revealing a shiny silver key in its mouth.")
                    cottage.items.append(key)
                elif target == "door" and noun == key:
                    print("You use the silver key on the large metal door. It opens... to reveal a staircase back out of the cave! You're free!\n")
                    print("Thanks for playing. Try again?\n\n")
                    break
                else:
                    use(noun, target)
            
            # if block for rest of verbs
            # these ones are super easy, i think these are good functions & make sense to implement GENERALLY. as opposed to use()

            elif "examine" in action_processed:
                examine(noun)
            elif "take" in action_processed:
                take(noun, player)
            elif "exit" in action_processed:
                print("\nExiting the game. Thanks for playing!\n")
                break
            else:
                print("I'm not sure what you're trying to do!\n")
                print("Try using one of the following verbs on something in the room:")
                print("move, use, examine, take, exit\n")

        except (TypeError, AttributeError): #this should catch MOST intentional errors, but not unintentional ones
            print("\nHmm. I can't understand what you're trying to do!")
            print("Maybe try to do that action on something else in the room?")

main() # make sure to actually call main() or nothing happens...