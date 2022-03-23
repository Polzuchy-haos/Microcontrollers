/*****************************************************************************
 * @file    		KDI_Menu_item.h
 * @author  		Polzuchy_haos
 * @brief   		Header file of KDI_Menu_item module.
 * @version			1.0
 *
 * ***************************************************************************
 * This software used for create menu for microcontrollers. This library is suitable for creating various menus for seven-segment indicators,
 * for LED displays, and for creating terminals.To do this, you need to create elements and link them together using linking methods or
 * directly through structures. To easily create a menu, use the KDI_Menu library, there are convenient tools for creating menus.
 * The library is based entirely on KDI_Menu_item.
 *
 * 												##### How to use this driver #####
 * 1) Get menu item used KDI_GetMenu_item.
 * 2) Populate a struct using a function or directly via a struct.
 * 3) Build more structures like this and populate them
 * 4) Link structures using pointers inside.
 * 5) Create a pointer and a handler for your tasks and point to the first menu item,
 * 	  after which, after the events appear in the handler, follow the pointers inside
 *
 *
 *
 *
 *
 *
 */

#ifndef KDI_MENU_ITEM_H_
#define KDI_MENU_ITEM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief This enum used for save type pointer on a data
 */
typedef enum{

	TYPE_DATA_VOID		=	0,
	TYPE_DATA_CHAR		=	1,
	TYPE_DATA_INT		=	2,
	TYPE_DATA_FLOAT		=	3,

}KDI_Type_data;

/*
 * @brief This enum used for menu nesting tracking
 */

typedef enum{

	MENU_LEVEL_DATA		=	0,
	MENU_LEVEL_1		=	1,
	MENU_LEVEL_2		=	2,
	MENU_LEVEL_3		=	3,
	MENU_LEVEL_4		=	4,
	MENU_LEVEL_5		=	5,
	MENU_LEVEL_6		=	6,
	MENU_LEVEL_7		=	7,

}KDI_Menu_Level;

/*
 * @brief Structure is one item menu.
 * 		  The structure works on the principle of linked lists.
 */

typedef struct Menu_item{

	void* data;							/*!< Pointer on data. Pointer void* type, need data type conversion required */

	KDI_Type_data type		:4;			/*!< Enum for save type data. needed to permanently transform data in your functions*/

	KDI_Menu_Level level_menu	:4;		/*!< Enum for menu nesting tracking, 0 level is level data*/

	struct Menu_item* last_item;		/*!< Pointer on previous menu item*/

	struct Menu_item* next_item;		/*!< Pointer on next menu item*/

	struct Menu_item* parent_item;		/*!< Pointer on parent menu item*/

	struct Menu_item* child_item;		/*!< Pointer on child menu item*/


}KDI_Menu_item;

/* Function get pointer on new menu item */
KDI_Menu_item* KDI_GetMenu_item();

/* Functions set/get pointer on data */
void KDI_MenuItem_SetData(KDI_Menu_item* item, void* data);
void* KDI_MenuItem_GetData(KDI_Menu_item* item);

/* Functions set/get pointer on type data*/
void KDI_MenuItem_SetTypeData(KDI_Menu_item* item, KDI_Type_data type);
KDI_Type_data KDI_MenuItem_GetTypeData(KDI_Menu_item* item);

/* Functions set/get pointer on level menu*/
void KDI_MenuItem_SetLevel(KDI_Menu_item* item, KDI_Menu_Level level);
KDI_Menu_Level KDI_MenuItem_GetLevel(KDI_Menu_item* item);

/* Function set link between menu item*/
void KDI_MenuItem_SetLinkOnNextMenuItem(KDI_Menu_item* item1, KDI_Menu_item* item2);
void KDI_MenuItem_SetLinkOnLastMenuItem(KDI_Menu_item* item1, KDI_Menu_item* item2);
void KDI_MenuItem_SetLinkOnParentMenuItem(KDI_Menu_item* item1, KDI_Menu_item* item2);
void KDI_MenuItem_SetLinkOnChildMenuItem(KDI_Menu_item* item1, KDI_Menu_item* item2);

/* Function get link between menu item*/
KDI_Menu_item* KDI_MenuItem_GetLinkOnNextMenuItem(KDI_Menu_item* item1);
KDI_Menu_item* KDI_MenuItem_GetLinkOnLastMenuItem(KDI_Menu_item* item1);
KDI_Menu_item* KDI_MenuItem_GetLinkOnParentMenuItem(KDI_Menu_item* item1);
KDI_Menu_item* KDI_MenuItem_GetLinkOnChildMenuItem(KDI_Menu_item* item1);

#ifdef __cplusplus
}
#endif

#endif /* SRC_KDI_MENU_ITEM_H_ */
