/*
 * Menu.cpp
 *
 *  Created on: 30 Oct 2011
 *      Author: ollie
 */
#include "Menu.h"

Menu::Menu(EnterMenu enterAction, SelectionChange selectionChangeAct, char* newName, int size) : MenuNode() {
    entered = enterAction;
    name = newName;
    selection = selectionChangeAct;
    selectedNode = 0;
    nodeCount = 0;
    nodes = new MenuNode*[size];
}

Menu::~Menu() {
    for (int i=0; i < sizeof(nodes); i++) {
        delete nodes[i];
    }
    delete nodes;
}

void Menu::addMenuNode(MenuNode & node) {
    nodes[nodeCount] = &node;
    nodeCount++;
}

void Menu::enter() {
    entered(this);
    if (nodeCount > 0) {
        nodes[0]->select();
    }
}

void Menu::up() {
    if (selectedNode > 0) {
        (*(nodes[selectedNode])).selected = false;
        (*(nodes[--selectedNode])).select();
    }
}

void Menu::down() {
    if (selectedNode < nodeCount-1) {
        (*(nodes[selectedNode])).selected = false;
        (*(nodes[++selectedNode])).select();
    }
}

int Menu::size() {
    return sizeof(nodes);
}

MenuNode & Menu::getSelectedNode() {
    return *(nodes[selectedNode]);
}

MenuNode::MenuNode(EnterMenuNode enterAction, SelectionChange selectionChangeAct, char* newname) {
    name = new char[12];
    strcpy(name, newname);
    entered = enterAction;
    selection = selectionChangeAct;
    selected = false;
    row = 0;
}

MenuNode::MenuNode() {
    selected = false;
    row = 0;
}

void MenuNode::enter() {
    entered(this);
}

char* MenuNode::getName() {
    return name;
}

void MenuNode::select() {
    selected = true;
    selection(this);
}

bool MenuNode::isSelected() {
    return selected;
}
