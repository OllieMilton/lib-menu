#ifndef MENU_H
#define MENU_H

#include <string.h>

/** 
 * MenuItem represents an entry in a menu. Each menu item is instantiated with
 * two callbacks, one for selecting the item and one for entering the item.
 * Methods are provided for determining whether the item is selected and
 * retrieving the row number set by the containing menu.
 */
class MenuItem {

private:
    typedef void (*EnterMenuItem)(MenuItem*);
    void (*entered)(MenuItem*);
    bool selected;
    int row;
public:
    typedef void (*SelectionChange)(MenuItem*);
    
    /**
     * Constructs a new MenuItem object. The constructor takes two function pointers as
     * arguments both of which must take a single argument of a MenuItem pointer.
     *
     * Example:
     * @code
     *  MenuItem *item = new MenuItem(&enterItem, &select, name);
     * @end code
     *
     * @param EnterMenuItem - A pointer to a callback fuction called when the item is entered.
     * @param SelectionChange - A pointer to a callback fuction called when the item is selected.
     * @param name - The name of the MenuItem.
     */
    MenuItem(EnterMenuItem, SelectionChange, char*);
    
    /**
     * Gets the name of the item.
     * @return A char array containing the item name.
     */
    char* getName();
    
    /**
     * Enters this instance of MenuItem and ultimatley calls the entered callback function.
     */
    virtual void enter();
    
    /**
     * Determines wheter tgis instance is selected.
     * @return true if selected.
     */
    bool isSelected();
    
    /**
     * Selects this instance of MenuItem in its containing Menu and called the selected call back function.
     */
    void select();
    
    /**
     * De-selectes this instance - this is called internally by Menu DO NOT CALL THIS.
     */
    void deSelect();
protected:
    char* name;
    void (*selection)(MenuItem*);
    MenuItem();
};

/**
 * Menu represents a container for a set of MenuItems. Menu is itself
 * a menu item meaning that Menu objects can be used as sun menus. 
 */
class Menu : public MenuItem {

private:
    typedef void (*EnterMenu)(Menu*);
    MenuItem **items;
    void (*entered)(Menu*);
    int selectedItem;
    int itemCount;
public:
    Menu(EnterMenu, SelectionChange, char*, int);
    Menu(char*, int);
    void addMenuItem(MenuItem&);
    MenuItem & selectedRow();
    int size();
    virtual void enter();
    void up();
    void down();
};

#endif