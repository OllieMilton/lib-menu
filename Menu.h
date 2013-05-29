#ifndef MENU_H
#define MENU_H

#include "mbed.h"

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
    void setRowNo(int);
    int getRowNo();
protected:
    char* name;
    void (*selection)(MenuItem*);
    Serial *pc;
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