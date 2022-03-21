/*****************************************************************************
 * @file    		KDI_Menu.c
 * @author  		Polzuchy_haos
 * @brief   		Source file of KDI_Menu module.
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
 *
 *
 * 									#### Example Used Library ####
 *
 * 1) Decide on the arrangement of the menu:
 *
 * 		A	->	A1	->	data
 * 				A2	->	data
 * 				A3	->	data
 * 				A4	->	data
 * 				A5	->	data
 *
 * 		B	->	B1	->	data
 * 				B2	->	data
 * 				B3	->	data
 * 				B4	->	data
 * 				B5	->	data
 *
 * 		We have two groups of parameters. Each group has 5 parameters.
 * 		The beginning of our menu will start with A.
 * 		Since this is the first group of parameters, it includes A and B.
 * 		To go to subgroup A. The main pointer must be on item A and use the movement down.
 * 		Now we have access to elements A1, A2, A3, A4, A5.
 * 		To go to the data of the A3 element,
 * 		our main pointer must stand on it and again we move down,
 * 		now the data of the A3 element is available to us.
 * 		To return to subgroup A, we use the up movement.
 * 		To return to the main group, use the up movement again.
 *
 * 2) Let's create a data structure:
 *
 * 		KDI_Menu MyMenu = {0};
 *
 * 3) Initialize the structure use 	KDI_Menu_Init:
 *
 * 		KDI_Menu_Init(&MyMenu, "  A ", TYPE_DATA_CHAR);
 *
 * 		We will pass the string literal "  A " as data,
 * 		this is our first element and the entire menu will begin with it.
 *
 * 4) Add the first element of subgroup A:
 *
 * 		KDI_Menu_Add_Child(&MyMenu, "  A1", TYPE_DATA_CHAR, MENU_NO_END, MENU_COMMAND_DOWN);
 *
 * 		Since this is a parameter for us, we will pass the string literal "A1" as data,
 * 		since this is not the end of this branch for us, we pass it to the MENU_NO_END function.
 * 		Considering A is the parent of A1, this is the child,
 * 		then with the MENU_COMMAND_DOWN command we will go down the branch and our main pointer will point to A1.
 *
 * 5) Add child the item A1:
 *
 * 		KDI_Menu_Add_Child(&MyMenu, &A1, TYPE_DATA_INT, MENU_END, MENU_COMMAND_NO);
 *
 * 		Since child A1 is a final element and represents data, then we pass a pointer to this data,
 * 		assign a data type that corresponds to this data. Specify that this is the end of the branch.
 * 		We don’t move around the menu, because there is no sense.
 * 		Now the menu pointer is on element A1!
 *
 * 6) Add next item i.e A2:
 *
 * 		KDI_Menu_Add_Next(&MyMenu, "  A2", TYPE_DATA_CHAR, MENU_COMMAND_FORWARD);
 *
 * 		We pass the string literal "A2" to the function and move the menu pointer to this element.
 * 		Now our menu looks like this:
 *
 * 			A
 * 			|
 * 		   >A1 -> *A2 ->
 * 			|	   |
 * 			d	   d
 *
 *
 * 7) Create subgroup A using points 5 and 6:
 *
 * 		KDI_Menu_Add_Next(&MyMenu, "  Ax", TYPE_DATA_CHAR, MENU_COMMAND_FORWARD);
 *			KDI_Menu_Add_Child(&MyMenu, &Ax, TYPE_DATA_INT, MENU_END, MENU_COMMAND_NO);
 *
 * 8) After you have finished with subgroup A, you need to return the menu pointer from A5 to A.
 * 	  Use the function	KDI_Menu_Drive:
 *
 * 	  	KDI_Menu_Drive(&MyMenu, MENU_COMMAND_UP);
 *
 * 9) Add element B similar to points 6:
 *
 * 		KDI_Menu_Add_Next(&MyMenu, "   B", TYPE_DATA_CHAR, MENU_COMMAND_FORWARD);
 *
 * 		Since we need to construct a subgroup B, we will pass the pointer to it.
 *
 * 10) Similarly to points 4, 5 and 6 we will construct a subgroup B:
 *
 * 		KDI_Menu_Add_Next(&MyMenu, "  Bx", TYPE_DATA_CHAR, MENU_COMMAND_FORWARD);
 *			KDI_Menu_Add_Child(&MyMenu, &Bx, TYPE_DATA_INT, MENU_END, MENU_COMMAND_NO);
 * 11) Let's return our pointer to the beginning of our menu, namely to element A.
 * 	   Use function KDI_Menu_Start
 *
 * 	   	KDI_Menu_Start(&MyMenu);
 *
 * 12) Since we are using int and char data types, we will pass pointers to the int and char output functions:
 *
 *		void print_str(char *p);
 *		void print_int(int p);
 *
 *		KDI_Menu_Set_print_char(&MyMenu, print_str);
 *		KDI_Menu_Set_print_int(&MyMenu, print_int);
 *
 * 13) All our menu is ready. Now, in order to move along it, we will use a function KDI_Menu_Drive,
 * 	   and in order to display data, we will use a function KDI_Menu_Handler. Example:
 *
 * 	   		if(button == pressed){
 *
 * 	   			KDI_Menu_Drive(&MyMenu, MENU_COMMAND_FORWARD);
 * 	   			KDI_Menu_Handler(&MyMenu);
 *
 * 	   		}
 *
 *
 *
 */

#include "KDI_Menu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Includes for used malloc
 */
#include <stdlib.h>

/**
  * @brief 		Displays various data taken from MenuItem
  * @param  	Pointer on KDI_Menu
  *	@return		Nope
  *
  */

void KDI_Menu_Handler(KDI_Menu* menu){

	/*Check type data */
	switch(menu->pointer->type){

	/*For char data */
	case TYPE_DATA_CHAR:

		/*print data*/
		menu->print_string((char*)menu->pointer->data);
		break;

	/*For integer data */
	case TYPE_DATA_INT:

		/*print data*/
		menu->print_int(*(int*)menu->pointer->data);
		break;

	/*For float data */
	case TYPE_DATA_FLOAT:

		/*print data*/
		menu->print_float(*(float*)menu->pointer->data);
		break;

	/*For float data */
	case TYPE_DATA_VOID:

		/*print on display "Error 0" */
		menu->print_string("E0  ");
		break;
	}

}

/**
  * @brief 		Changes the pointer to the start
  * @param  	Pointer on KDI_Menu
  *	@return		Nope
  *
  */

void KDI_Menu_Start(KDI_Menu* menu){

	/*Pointer points to the first element  */
	menu->pointer = menu->Head;

}

/**
  * @brief 		Initialization structure
  *
  * @param  	Pointer on KDI_Menu
  * @param		Pointer on data type void*
  * @param		Type date.
  * 			This parameter can be one of the KDI_Type_data enum values:
  * 				@arg TYPE_DATA_VOID;
  *					@arg TYPE_DATA_CHAR;
  *					@arg TYPE_DATA_INT;
  *					@arg TYPE_DATA_FLOAT;
  *
  *	@return		Nope
  *
  * @note		This function initialization structure and create first
  * 			menu element, usually this is a parameter, and its
  * 			parameters is the name of the parameter, i.e. string (char*).
  */

void KDI_Menu_Init(KDI_Menu* menu, void* data, KDI_Type_data type){

	/* Create first element menu */
	menu->pointer = KDI_GetMenu_item();

	/* Start level menu*/
	menu->level = MENU_LEVEL_1;

	/* Max level menu*/
	menu->level_max = MENU_LEVEL_1;

	/* Save pointer on start menu */
	menu->Head = menu->pointer;

	/* Save pointer on next item*/
	KDI_MenuItem_SetLinkOnNextMenuItem(menu->pointer, menu->pointer);

	/* Save pointer on last item*/
	KDI_MenuItem_SetLinkOnLastMenuItem(menu->pointer, menu->pointer);

	/* Save pointer on data*/
	KDI_MenuItem_SetData(menu->pointer, data);

	/* Save type data*/
	KDI_MenuItem_SetTypeData(menu->pointer, type);

	/* Save menu level*/
	KDI_MenuItem_SetLevel(menu->pointer, MENU_LEVEL_1);

}


/**
  * @brief 		Add new menu item.
  *
  * @param  	Pointer on KDI_Menu.
  * @param		Pointer on data type void*.
  * @param		Type date.
  * 			This parameter can be one of the KDI_Type_data enum values:
  * 				@arg TYPE_DATA_VOID;
  *					@arg TYPE_DATA_CHAR;
  *					@arg TYPE_DATA_INT;
  *					@arg TYPE_DATA_FLOAT;
  *
  *	@param		Menu navigation command.
  *				This parameter can be one of the KDI_Menu_Command enum values:
  *					@arg MENU_COMMAND_NO
  *					@arg MENU_COMMAND_FORWARD
  *					@arg MENU_COMMAND_BACKWARD
  *					@arg MENU_COMMAND_UP
  *					@arg MENU_COMMAND_DOWN
  *
  *	@return		Nope
  *
  * @note		This create new menu item, usually this is a parameter, and its
  * 			parameters is the name of the parameter, i.e. string (char*).
  */


void KDI_Menu_Add_Next(KDI_Menu* menu, void* data, KDI_Type_data type, KDI_Menu_Command command){

	/* Copy pointer on head */
	KDI_Menu_item* head = KDI_MenuItem_GetLinkOnNextMenuItem(menu->pointer);

	/* Create new menu item and save pointer as next item*/
	KDI_MenuItem_SetLinkOnNextMenuItem(menu->pointer, KDI_GetMenu_item());

	/* In new item save pointer on current item*/
	KDI_MenuItem_SetLinkOnLastMenuItem(menu->pointer->next_item, menu->pointer);

	/* In new item save pointer on head*/
	KDI_MenuItem_SetLinkOnNextMenuItem(menu->pointer->next_item, head);

	/* In head save pointer on last item*/
	KDI_MenuItem_SetLinkOnLastMenuItem(head, menu->pointer->next_item);

	/* In new item save pointer on common parent*/
	KDI_MenuItem_SetLinkOnParentMenuItem(menu->pointer->next_item, menu->pointer->parent_item);

	/* In new item save pointer on date*/
	KDI_MenuItem_SetData(menu->pointer->next_item, data);

	/* In new item save type date*/
	KDI_MenuItem_SetTypeData(menu->pointer->next_item, type);

	/* In new item save menu level*/
	KDI_MenuItem_SetLevel(menu->pointer->next_item, menu->level);

	/* Command execution */
	if(command)	KDI_Menu_Drive(menu, command);

}

/**
  * @brief 		Create child item
  * 			P -> P -> P
  * 			|	 |	  |
  * 			C	 C	  C
  *
  * @param  	Pointer on KDI_Menu
  * @param		Pointer on data type void*
  * @param		Type date.
  * 			This parameter can be one of the KDI_Type_data enum values:
  * 				@arg TYPE_DATA_VOID;
  *					@arg TYPE_DATA_CHAR;
  *					@arg TYPE_DATA_INT;
  *					@arg TYPE_DATA_FLOAT;
  *
  *	@param		Defines the end of the menu, usually the data itself.
  *				This parameter can be one of the KDI_Menu_end enum values:
  *					@arg MENU_NO_END
  *					@arg MENU_END
  *
  * @param		Menu navigation command.
  *				This parameter can be one of the KDI_Menu_Command enum values:
  *					@arg MENU_COMMAND_NO
  *					@arg MENU_COMMAND_FORWARD
  *					@arg MENU_COMMAND_BACKWARD
  *					@arg MENU_COMMAND_UP
  *					@arg MENU_COMMAND_DOWN
  *
  *	@return		Nope
  *
  * @note		This create new menu item is child, this is a parameter or a date.
  * 			If its parameter used string (char*) and used MENU_NO_END.
  * 			if its date MENU_END.
  */

void KDI_Menu_Add_Child(KDI_Menu* menu, void* data, KDI_Type_data type, KDI_Menu_end end, KDI_Menu_Command command){

	/* Create new item and save pointer as child*/
	KDI_MenuItem_SetLinkOnChildMenuItem(menu->pointer, KDI_GetMenu_item()); //Создание обьекта ребенка и сохранения указателя у родителя

	/* In new item save pointer on a date*/
	KDI_MenuItem_SetData(menu->pointer->child_item, data);				//Присвоение Указателя на данные

	/* In new item save type date*/
	KDI_MenuItem_SetTypeData(menu->pointer->child_item, type);			//Присвоение типа данных

	/* In new item save pointer on next item*/
	KDI_MenuItem_SetLinkOnNextMenuItem(menu->pointer->child_item, menu->pointer->child_item);

	/* In new item save pointer on last item*/
	KDI_MenuItem_SetLinkOnLastMenuItem(menu->pointer->child_item, menu->pointer->child_item);

	/* Check end menu*/
	if(end){

		/* In new item set level as level data */
		KDI_MenuItem_SetLevel(menu->pointer->child_item, MENU_LEVEL_DATA);

	}else{

		/* In new item save increment level */
		KDI_MenuItem_SetLevel(menu->pointer->child_item, menu->level + 1);
	}

	/* In new item save pointer on parent */
	KDI_MenuItem_SetLinkOnParentMenuItem(menu->pointer->child_item, menu->pointer);	// ребенок получает указатель на родителя

	/* Determination of the maximum level menu*/
	if(KDI_MenuItem_GetLevel(menu->pointer->child_item) > menu->level_max) menu->level_max = menu->pointer->child_item->level_menu;

	/* Command execution */
	if(command)	KDI_Menu_Drive(menu, command);
}

/**
  * @brief 		Function for move menu
  *
  * @param  	Pointer on KDI_Menu
  *	@param		Menu navigation command.
  *				This parameter can be one of the KDI_Menu_Command enum values:
  *					@arg MENU_COMMAND_NO
  *					@arg MENU_COMMAND_FORWARD
  *					@arg MENU_COMMAND_BACKWARD
  *					@arg MENU_COMMAND_UP
  *					@arg MENU_COMMAND_DOWN
  *
  *	@return		Nope
  */

void KDI_Menu_Drive(KDI_Menu* menu, KDI_Menu_Command command){

	/* Check command*/
	switch(command){

	/* Command NO*/
	case MENU_COMMAND_NO:
		return;
		break;

	/* Command Forward*/
	case MENU_COMMAND_FORWARD:

		/* Function command forward*/
		KDI_Menu_Command_Forward(menu);
		return;
		break;

	/* Command Backward*/
	case MENU_COMMAND_BACKWARD:

		/* Function command Backward*/
		KDI_Menu_Command_Backward(menu);
		return;
		break;

	/* Command Up */
	case MENU_COMMAND_UP:

		/* Function command Up*/
		KDI_Menu_Command_Up(menu);
		return;
		break;

	/* Command Down*/
	case MENU_COMMAND_DOWN:

		/* Function command Down*/
		KDI_Menu_Command_Down(menu);
		return;
		break;

	/* Processing in case of invalid values */
	default:
		return;
		break;
	}
}


/**
  * @brief 		Move on next item
  * @param  	Pointer on KDI_Menu
  * @return 	Nope
  */

void KDI_Menu_Command_Forward(KDI_Menu* menu){

	/* Pointer next item save as main or current pointer */
	menu->pointer = menu->pointer->next_item;

}


/**
  * @brief 		Move on previous item
  * @param  	Pointer on KDI_Menu
  * @return 	Nope
  */

void KDI_Menu_Command_Backward(KDI_Menu* menu){

	/* Pointer last item save as main or current pointer */
	menu->pointer = menu->pointer->last_item;

}


/**
  * @brief 		Go to Child item
  * 			*P	| 	 |   P
  * 			 |	| => |   |
  * 			 C 	|    |  *C
  * @param  	Pointer on KDI_Menu
  * @return 	Nope
  */

void KDI_Menu_Command_Down(KDI_Menu* menu){

	/* Check on unlimited level*/
	if(menu->level < menu->level_max){

		/* If level date then exit*/
		if(menu->level == MENU_LEVEL_DATA) return;

		/* Increment level*/
		menu->level++;

		/* Check on unlimited level*/
		if(menu->level > menu->level_max){

			/* Save level as value level max*/
			menu->level = menu->level_max;

		}else {

			/* Pointer on child save as current pointer*/
			menu->pointer = menu->pointer->child_item;

		}
		return;
	}

	/* If the parent the child have level menu as data */
	if(menu->pointer->child_item->level_menu == MENU_LEVEL_DATA){

		/* Child pointer save as main pointer*/
		menu->pointer = menu->pointer->child_item;

		/* Menu level save as data level*/
		menu->level = MENU_LEVEL_DATA;
		return;
	}

}


/**
  * @brief 		Back to parent item
  * 			 P	| 	 |  *P
  * 			 |	| => |   |
  * 			*C 	|    |   C
  * @param  	Pointer on KDI_Menu
  * @return 	Nope
  */

void KDI_Menu_Command_Up(KDI_Menu* menu){

	/* Check on unlimited level*/
	if(menu->level > 1){

		/*decrement menu level*/
		menu->level--;

		/* Cheak level */
		if(menu->level < 0){
			menu->level = 1;
		}
		else{

			/* Parent pointer save as main pointer*/
			menu->pointer = menu->pointer->parent_item;
		}
		return;
	}

	/* If the parent the child have level menu as data */
	if(menu->level == MENU_LEVEL_DATA){

		/* Parent pointer save as main pointer*/
		menu->pointer = menu->pointer->parent_item;

		/* Menu level save as data level*/
		menu->level = menu->pointer->level_menu;
		return;
	}


}

/**
  * @brief 		Save pointer on function output char
  *
  * @param  	Pointer on KDI_Menu
  * @param		Pointer on function type "void name_fuction(char*)"
  * @return 	Nope
  */

void KDI_Menu_Set_print_char(KDI_Menu* menu, void(*point)(char*)){

	/* Save pointer on function*/
	menu->print_string = point;
}


/**
  * @brief 		Save pointer on function output int
  *
  * @param  	Pointer on KDI_Menu
  * @param		Pointer on function type "void name_fuction(int)"
  * @return 	Nope
  */

void KDI_Menu_Set_print_int(KDI_Menu* menu, void(*point)(int)){

	/* Save pointer on function*/
	menu->print_int = point;
}


/**
  * @brief 		Save pointer on function output float
  *
  * @param  	Pointer on KDI_Menu
  * @param		Pointer on function type "void name_fuction(float)"
  * @return 	Nope
  */
void KDI_Menu_Set_print_float(KDI_Menu* menu, void(*point)(float)){

	/* Save pointer on function*/
	menu->print_float = point;
}

#ifdef __cplusplus
}
#endif
