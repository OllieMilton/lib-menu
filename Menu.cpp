/*
 * Menu.cpp
 *
 *  Created on: 30 Oct 2011
 *      Author: ollie
 */
#include "Menu.h"

Menu::Menu(EnterMenu enterAction, SelectionChange selectionChangeAct, char* newName, int size) : MenuItem() {
    entered = enterAction;
    name = newName;
    selection = selectionChangeAct;
    selectedItem = 0;
    itemCount = 0;
    items = new MenuItem*[size];
}

Menu::Menu(char* newName, int size) {
    selectedItem = 0;
    itemCount = 0;
    name = newName;
    items = new MenuItem*[size];
}

void Menu::addMenuItem(MenuItem & item) {
    item.setRowNo(itemCount);
    items[itemCount] = &item;
    itemCount++;
}

void Menu::enter() {
    entered(this);
}

void Menu::up() {
    if (selectedItem > 0) {
        (*(items[selectedItem])).deSelect();
        (*(items[--selectedItem])).select();
    }
}

void Menu::down() {
    if (selectedItem < itemCount-1) {
        (*(items[selectedItem])).deSelect();
        (*(items[++selectedItem])).select();
    }
}

int Menu::size() {
    return sizeof(items);
}

MenuItem & Menu::getItem(int item) {
    return *(items[item]);
}

MenuItem & Menu::selectedRow() {
    return *(items[selectedItem]);
}

MenuItem::MenuItem(EnterMenuItem enterAction, SelectionChange selectionChangeAct, char* newname) {
    name = new char[12];
    strcpy(name, newname);
    entered = enterAction;
    selection = selectionChangeAct;
    selected = false;
    row = 0;
}

MenuItem::MenuItem() {
    selected = false;
    row = 0;
}

void MenuItem::enter() {
    entered(this);
}

char* MenuItem::getName() {
    return name;
}

void MenuItem::select() {
    selected = true;
    selection(this);
}

void MenuItem::deSelect() {
    selected = false;
}

bool MenuItem::isSelected() {
    return selected;
}

void MenuItem::setRowNo(int r) {
    row = r;
}

int MenuItem::getRowNo() {
    return row;
}