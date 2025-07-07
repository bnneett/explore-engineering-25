
class Room:
    def __init__(self, name:str, description:str):
        self.name = name
        self.description = description
        self.exits = [] # no dict. idiot
        self.items = []
    

class Player:
    def __init__(self, name:str, location):
        self.name = name
        self.location = location
        self.items = []


class Item:
    def __init__(self, name:str, description:str, is_movable=True): #potential consumable attribute? NOTE: probably too complicated.
        self.name = name
        self.description = description # shorthand description
        self.removable = is_movable

#############

# testing stuff (also to explore how class attributes work & why we need a self.name attribute)
# talk about private scope vs public scope

house = Room("house", "a small wooden house")
bathroom = Room("bathroom", "a clean bathroom")
fork = Item("fork", "a shiny silver fork")

house.add_exit("right", bathroom)
house.add_item(fork)

print(house)
print(house.name) # what's different about this vs printing just house?
print(house.description)



