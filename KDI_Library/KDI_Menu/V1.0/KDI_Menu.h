/*****************************************************************************
 * @file    		KDI_Menu.h
 * @author  		Polzuchy_haos
 * @brief   		Header file of KDI_Menu module.
 * @version			1.0
 *
 * ***************************************************************************
 * This software used for create menu for microcontrollers. Basically, this is the output of one section of the menu,
 * to which 7 segment indicators can be related. In case of an increase in the simultaneous number of parameter indications,
 * rewrite the handler function and / or use the library KDI_Menu_item.
 *
 * 									##### How to use this driver #####
 * 1) Declare a structure KDI_Menu and fill it with zeros.
 * 2) Use functions KDI_Menu_Init for initialization.
 * 3) Use functions KDI_Menu_Add_Next and KDI_Menu_Add_Child create menu.
 * 4) Use functions KDI_Menu_Start for start menu.
 * 5) To move through the menu use functions  KDI_Menu_Drive and call a KDI_Menu_Handler.
 *
 *
 */

#ifndef KDI_MENU_H_
#define KDI_MENU_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief	Includes lib KDI_Menu_item.h
 * 			The work of this program is built on the elements of the library
 *
 */
#include "KDI_Menu_item.h"


/*
 * @brief	Menu command enumeration
 */

typedef enum{

	MENU_COMMAND_NO				=	0,
	MENU_COMMAND_FORWARD		=	1,
	MENU_COMMAND_BACKWARD		=	2,
	MENU_COMMAND_UP				=	3,
	MENU_COMMAND_DOWN			=	4,

}KDI_Menu_Command;

/*
 * @brief	End menu enumeration
 */
typedef enum{

	MENU_NO_END		=	0,
	MENU_END		=	1,

}KDI_Menu_end;

/*
 * @brief	General structure for work library
 */

typedef struct Menu{

	KDI_Menu_item* Head;			/*!< Pointer on head menu, used for return to the top of the menu */

	KDI_Menu_item* pointer;			/*!< Main menu pointer, which points to the current menu item */

	KDI_Menu_Level level;			/*!< Current menu level */

	KDI_Menu_Level level_max;		/*!< Max menu level */

	KDI_Menu_Command Command;		/*!< Command for handler */

	void(*print_string)(char* );	/*!< Pointer on function print string or char*/

	void(*print_int)(int );			/*!< Pointer on function print int, short, long, uint8_t, uint16_t, uint32_t and uint64_t*/

	void(*print_float)(float );		/*!< Pointer of function print float and double */


}KDI_Menu;

/*Initialization function */
void KDI_Menu_Init(KDI_Menu* menu, void* data, KDI_Type_data type);

/*Handler function */
void KDI_Menu_Handler(KDI_Menu* menu);

/*Functions for creating menus*/
void KDI_Menu_Add_Next(KDI_Menu* menu, void* data, KDI_Type_data type, KDI_Menu_Command command);
void KDI_Menu_Add_Child(KDI_Menu* menu, void* data, KDI_Type_data type, KDI_Menu_end end, KDI_Menu_Command command);
void KDI_Menu_Start(KDI_Menu* menu);

/*Functions for moves menus*/
void KDI_Menu_Drive(KDI_Menu* menu, KDI_Menu_Command command);
void KDI_Menu_Command_Forward(KDI_Menu* menu);
void KDI_Menu_Command_Backward(KDI_Menu* menu);
void KDI_Menu_Command_Up(KDI_Menu* menu);
void KDI_Menu_Command_Down(KDI_Menu* menu);

/*Functions to pass pointer to data output */
void KDI_Menu_Set_print_char(KDI_Menu* menu, void(*point)(char*));
void KDI_Menu_Set_print_int(KDI_Menu* menu, void(*point)(int));
void KDI_Menu_Set_print_float(KDI_Menu* menu, void(*point)(float));

/*Function get pointer on MenuItem*/
KDI_Menu_item* KDI_Menu_Get_Pointer_Current_Item(KDI_Menu* menu);
KDI_Menu_item* KDI_Menu_Get_Pointer_Next_Item(KDI_Menu* menu);
KDI_Menu_item* KDI_Menu_Get_Pointer_Last_Item(KDI_Menu* menu);
KDI_Menu_item* KDI_Menu_Get_Pointer_Child_Item(KDI_Menu* menu);
KDI_Menu_item* KDI_Menu_Get_Pointer_Parent_Item(KDI_Menu* menu);

#ifdef __cplusplus
}
#endif

#endif /* KDI_MENU_H_ */
