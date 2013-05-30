#ifndef MENU_H
#define MENU_H

#include <mbed.h>

class Menu;

/** MenuNode represents an entry in a menu. Each menu node is instantiated with
 * two callbacks, one for selecting the node and one for entering the node.
 * Methods are provided for determining whether the node is selected and
 * retrieving the row number set by the containing menu.
 */
class MenuNode {

private:
    typedef void (*EnterMenuNode)(MenuNode*);
    void (*entered)(MenuNode*);
    bool selected;
    int row;
    friend class Menu;
public:

    /** Defines a pointer to a functions that is called when the node is selected.
     */
    typedef void (*SelectionChange)(MenuNode*);
    
    /** Constructs a new MenuNode object. The constructor takes two function pointers as
     * arguments both of which must take a single argument of a MenuNode pointer.
     * 
     * @code
     *
     *  void enterNode(MenuNode *node) {
     *
     *  }
     *
     *  void selectNode(MenuNode *node) {
     *
     *  }
     *
     *  main() {
     *     MenuNode *node = new MenuNode(&enterNode, &selectNode, "name");
     *  }
     *
     * @endcode
     *
     * @param EnterMenuNode A pointer to a callback fuction called when the node is entered.
     * @param SelectionChange A pointer to a callback fuction called when the node is selected.
     * @param name The name of the MenuNode.
     */
    MenuNode(EnterMenuNode, SelectionChange, char*);
    
    /** Gets the name of the node.
     * @return A char array containing the node name.
     */
    char* getName();
    
    /** Enters this instance of MenuNode and ultimatley calls the entered callback function.
     */
    virtual void enter();
    
    /** Determines wheter tgis instance is selected.
     * @return true if selected.
     */
    bool isSelected();
    
    /** Selects this instance of MenuNode in its containing Menu and called the selected call back function.
     */
    void select();
    
    
protected:
    char* name;
    void (*selection)(MenuNode*);
    MenuNode();
};

/** Menu represents a container for a set of MenuNodes. Menu is itself
 * a menu node meaning that Menu objects can be used as sun menus. 
 */
class Menu : public MenuNode {

private:
    typedef void (*EnterMenu)(Menu*);
    MenuNode **nodes;
    void (*entered)(Menu*);
    int selectedNode;
    int nodeCount;
public:

    /** Constructs a new menu objects.
     *
     * @code
     *  void enterMenu(Menu *menu) {
     *
     *  }
     *
     *  void selectNode(MenuNode *node) {
     *
     *  }
     *
     *  Menu root(&enterMenu, &selectNode, "root", 5);
     *  
     * @endcode
     *
     * @param EnterMenu A pointer to a functions to be called when the Menu is entered.
     * @param SelectionChange A pointer to a function to be called when the Menu is selected.
     * @param char* A char array containing the name of the Menu.
     * @param int The number of node that this Menu will contain. 
     */
    Menu(EnterMenu, SelectionChange, char*, int);
    
    /** Adds the given node to the Menu. MenuNodes are ordered by the order in which they are added.
     * Note that a Menu is also a MenuNode meaning that a menu can bee added as a MenuNode to create a sub Menu.
     *
     * @code
     * Menu root(&enterMenu, &selectNode, "root", 5);
     *
     * void main() {
     *  Menu *sub1 = new Menu(&enterMenu, &selectNode, "Settings", 5);
     *  MenuNode *ipnode = new MenuNode(&enterNode, &setip, "IP Address");
     *  MenuNode *netmasknode = new MenuNode(&enterNode, &setmask, "Net mask");
     *  sub1->addMenuNode(*ipnode);
     *  sub1->addMenuNode(*netmasknode);
     *  root.addMenuNode(*sub1);
     *  root.enter();
     * }
     *
     * @para MenuNode A reference to the MenuNode to add.
     */
    void addMenuNode(MenuNode&);
    
    /** Gets a pointer to the selected MenuNode.
     * @return A pointer to the selected MenuNode.
     */
    MenuNode & getSelectedNode();
    
    /** Gets the number of MenuNodes contained by this Menu.
     * @return The MenuNode count.
     */
    int size();
    
    /** Enters this implementation of Menu. */
    virtual void enter();
    
    /** Moves the selection up to the previous MenuNode if there is one and de-selects the current. */
    void up();
    
    /** Moves the selection down to the next node if there is one and de-selects the current. */
    void down();
};

#endif