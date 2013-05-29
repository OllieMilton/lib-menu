#ifndef MENU_H
#define MENU_H

#include <string.h>
/** MenuItem represents an entry in a menu. Each menu item is instantiated with
 * two callbacks, one for selecting the item and one for entering the item.
 * Methods are provided for determining whether the item is selected 
 *
 */
class MenuItem {

private:
    typedef void (*EnterMenuItem)(MenuItem*);
    void (*entered)(MenuItem*);
    bool selected;
    int row;
public:
    typedef void (*SelectionChange)(MenuItem*);
    MenuItem();
    MenuItem(EnterMenuItem, SelectionChange, char*);
    char* getName();
    virtual void enter();
    bool isSelected();
    void select();
    void deSelect();
    int getRowNo();
    void setRowNo(int);
protected:
    char* name;
    void (*selection)(MenuItem*);
};

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
    MenuItem & getItem(int);
    MenuItem & selectedRow();
    int size();
    virtual void enter();
    void up();
    void down();
};

#endif