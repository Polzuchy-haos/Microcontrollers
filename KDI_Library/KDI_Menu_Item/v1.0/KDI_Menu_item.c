/*****************************************************************************
 * @file    		KDI_Menu_item.h
 * @author  		Polzuchy_haos
 * @brief   		Source file of KDI_Menu_item module.
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
 *												#### Example Used Library ####
 *
 *
 * 1) Let's decide on the menu, as an example, let's analyze a cyclic string of parameters.
 *
 * 	 	->	A1 -> A2 -> A3 ->
 *			|	   |	 |
 *		   data  data   data
 *
 * 2)Build 3 menu item:
 *
 * 		KDI_Menu_item* A1 = KDI_GetMenu_item();
 * 		KDI_Menu_item* A2 = KDI_GetMenu_item();
 * 		KDI_Menu_item* A3 = KDI_GetMenu_item();
 *
 * 3)Let's fill each structure with data.
 *
 * 		KDI_MenuItem_SetData(A1, (void*)"A1");
 * 		KDI_MenuItem_SetTypeData(A1, TYPE_DATA_CHAR);
 * 		KDI_MenuItem_SetLevel(A1, MENU_LEVEL_1);
 *
 * 		do the same with A2 and A3.
 *
 * 4)Establish a connection between structures:
 *
 *		KDI_MenuItem_SetLinkOnNextMenuItem(A1, A2);
 *		KDI_MenuItem_SetLinkOnLastMenuItem(A1, A3);
 *
 *		do the same with A2 and A3.
 *
 * 5)Create children for each structure and fill it with data:
 *
 *		KDI_MenuItem_SetLinkOnChildMenuItem(A1, KDI_GetMenu_item());
 *
 *		KDI_MenuItem_SetData(KDI_MenuItem_GetLinkOnChildMenuItem(A1), (void*)data);
 * 		KDI_MenuItem_SetTypeData(KDI_MenuItem_GetLinkOnChildMenuItem(A1), TYPE_DATA_INT);
 * 		KDI_MenuItem_SetLevel(KDI_MenuItem_GetLinkOnChildMenuItem(A1), MENU_LEVEL_DATA);
 *
 *		do the same with A2 and A3.
 *
 * 6)We write a handler for our needs.
 *
 */


#include "KDI_Menu_item.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 		Includes for used malloc
 */
#include <stdlib.h>

/**
 * @brief		Get new menu item
 * @param 		Nope
 *
 * @return		Pointer KDI_Menu_item*
 */

KDI_Menu_item* KDI_GetMenu_item(){

	/* Allocation of dynamic memory for structure*/
	KDI_Menu_item* item = malloc(sizeof(KDI_Menu_item));

	/* Initialize the entire structure with zeros*/
	item->child_item = 0;

	item->data = 0;

	item->last_item = 0;

	item->next_item = 0;

	item->parent_item = 0;

	item->type = 0;

	item->level_menu = 0;

	/* Return pointer on new menu item*/
	return item;

}

/**
 * @brief		Save pointer on data
 * @param 		Pointer on menu item type KDI_Menu_item*
 * @param		Pointer on data type void*
 *
 * @return		Nope
 */

void KDI_MenuItem_SetData(KDI_Menu_item* item, void* data){

	/* Save pointer on data inside menu item*/
	item->data = data;

}

/**
 * @brief		Get pointer on data
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		Pointer on data type void*
 */

void* KDI_MenuItem_GetData(KDI_Menu_item* item){

	/* Return pointer on data saved inside menu item*/
	return item->data;

}

/**
 * @brief		Save type on data
 * @param 		Pointer on menu item type KDI_Menu_item*
 * @param		enum KDI_Type_data
 *
 * @return		Nope
 */

void KDI_MenuItem_SetTypeData(KDI_Menu_item* item, KDI_Type_data type){

	/* Save type on data inside menu item*/
	item->type = type;

}

/**
 * @brief		Get type on data
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		Type on data KDI_Type_data
 */

KDI_Type_data KDI_MenuItem_GetTypeData(KDI_Menu_item* item){

	/* Return pointer on data saved inside menu item*/
	return item->type;

}

/**
 * @brief		Save level menu item
 * @param 		Pointer on menu item type KDI_Menu_item*
 * @param		enum KDI_Menu_Level
 *
 * @return		Nope
 */
void KDI_MenuItem_SetLevel(KDI_Menu_item* item, KDI_Menu_Level level){

	/* Set menu level*/
	item->level_menu = level;

}

/**
 * @brief		Get menu level
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		KDI_Menu_Level
 */

KDI_Menu_Level KDI_MenuItem_GetLevel(KDI_Menu_item* item){

	/* Return menu level saved inside menu item*/
	return item->level_menu;

}

/**
 * @brief		Set pointer on next menu level
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		Nope
 */

void KDI_MenuItem_SetLinkOnNextMenuItem(KDI_Menu_item* item1, KDI_Menu_item* item2){

	/* Save pointer on next menu item*/
	item1->next_item = item2;
}

/**
 * @brief		Set pointer on last menu level
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		Nope
 */
void KDI_MenuItem_SetLinkOnLastMenuItem(KDI_Menu_item* item1, KDI_Menu_item* item2){

	/* Save pointer on last menu item*/
	item1->last_item = item2;
}

/**
 * @brief		Set pointer on parent menu level
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		Nope
 */
void KDI_MenuItem_SetLinkOnParentMenuItem(KDI_Menu_item* item1, KDI_Menu_item* item2){

	/* Save pointer on parent menu item*/
	item1->parent_item = item2;
}

/**
 * @brief		Set pointer on child menu level
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		Nope
 */
void KDI_MenuItem_SetLinkOnChildMenuItem(KDI_Menu_item* item1, KDI_Menu_item* item2){

	/* Save pointer on child menu item*/
	item1->child_item = item2;
}

/**
 * @brief		Get pointer on next menu level
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		KDI_Menu_item* menu item
 */
KDI_Menu_item* KDI_MenuItem_GetLinkOnNextMenuItem(KDI_Menu_item* item1){

	/* Return pointer on next menu item*/
	return item1->next_item;
}

/**
 * @brief		Get pointer on last menu level
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		KDI_Menu_item* menu item
 */
KDI_Menu_item* KDI_MenuItem_GetLinkOnLastMenuItem(KDI_Menu_item* item1){

	/* Return pointer on last menu item*/
	return item1->last_item;
}

/**
 * @brief		Get pointer on parent menu level
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		KDI_Menu_item* menu item
 */
KDI_Menu_item* KDI_MenuItem_GetLinkOnParentMenuItem(KDI_Menu_item* item1){

	/* Return pointer on parant menu item*/
	return item1->parent_item;
}

/**
 * @brief		Get pointer on child menu level
 * @param 		Pointer on menu item type KDI_Menu_item*
 *
 * @return		KDI_Menu_item* menu item
 */
KDI_Menu_item* KDI_MenuItem_GetLinkOnChildMenuItem(KDI_Menu_item* item1){

	/* Return pointer on child menu item*/
	return item1->child_item;
}

#ifdef __cplusplus
}
#endif
