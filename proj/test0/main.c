/*
 *问题说明：本项目为学生信息管理系统
 */
#include <stdio.h>
#include "config.h"
#include "land.h"
#include <stdlib.h>

int main(void)
{
	pUSR_ACCOUNT pUsr_Acount_h = NULL, pUsr_Acount_t = NULL;
	pUSR_INFOR pUsr_Infor_h = NULL, pUsr_Infor_t = NULL;

	system_init("configure.txt", &pUsr_Acount_h, &pUsr_Acount_t, &pUsr_Infor_h, &pUsr_Infor_t);

	char usr_name[USR_NAME_LEN] = { 0 };
	char usr_pwd[USR_PWD_LEN] = { 0 };

	//用戶登陸
	usr_land(usr_name, usr_pwd);
	//確認用戶
	USR_ROLE usr_role = comfirm_usr(pUsr_Acount_h, usr_name, usr_pwd);
	//USR_ROLE usr_role = ADMIN;     /////////////////////////////////////////////////

	//根据用户的权限显示系统菜单
	SYSTEM_MENU_TYPE usr_select_menu1;
	SYSTEM_MENU_TYPE_TWO usr_select_menu_search = 3;
	int usr_id = -1;
	char usr_acc_name[USR_NAME_LEN] = { 0 };
	int tmp = 0;
	while (1)
	{
		usr_select_menu1 = show_system_menu(usr_role);
		if (usr_select_menu1 == EXIT)						//直接退出
		{
			break;
		}

		//主功能菜单选择
		switch (usr_select_menu1)
		{
		case SER_STU_INFO:
			//当前用户选择查询功能时根据权限显示具有不同功能的查询功能的菜单
			usr_select_menu_search = show_search_menu(usr_role, pUsr_Infor_h);
			break;
		case ADD_STU_INFO:
			add_usr_infor(&pUsr_Infor_h, &pUsr_Infor_t);
			print_stu_info(pUsr_Infor_h);
			printf("enter number 0 to return ");
			scanf("%d", &tmp);
			break;
		case DEL_STU_INFO:
			system("cls");
			printf("please enter the usr_id to delete: ");				
			scanf("%d", &usr_id);
			delete_usr_infor(&pUsr_Infor_h, &pUsr_Infor_t, usr_id);
			print_stu_info(pUsr_Infor_h);
			printf("enter number 0 to return ");
			scanf("%d", &tmp);
			break;
		case UP_STU_INFO:
			system("cls");
			printf("please enter the usr_id to update: ");				//有问题
			scanf("%d", &usr_id);
			update_usr_infor(pUsr_Infor_h, usr_id);
			print_stu_info(pUsr_Infor_h);
			printf("enter number 0 to return ");
			scanf("%d", &tmp);
			break;
		case SER_USR_ACC:
			system("cls");
			printf("please enter the usr_name to search: ");				//有问题
			scanf("%s", usr_acc_name);
			search_usr_account(pUsr_Acount_h, usr_acc_name, usr_role);
			printf("enter number 0 to return ");
			scanf("%d", &tmp);
			break;
		case ADD_USR_ACC:
			add_usr_account(&pUsr_Acount_h, &pUsr_Acount_t);
			print_account(pUsr_Acount_h);
			printf("enter number 0 to return ");
			scanf("%d", &tmp);
			break;
		case DEL_USR_ACC:
			system("cls");
			printf("please enter the usr_name to delete: ");
			scanf("%s", usr_acc_name);
			delete_usr_account(&pUsr_Acount_h, &pUsr_Acount_t, usr_acc_name);
			print_account(pUsr_Acount_h);
			printf("enter number 0 to return ");
			scanf("%d", &tmp);
			break;
		case UP_USR_ACC:
			system("cls");
			printf("please enter the usr_name to update: ");				//有问题
			scanf("%s", &usr_acc_name);
			update_usr_account(pUsr_Acount_h, usr_acc_name);
			print_account(pUsr_Acount_h);
			printf("enter number 0 to return ");
			scanf("%d", &tmp);
			break;
		}
		if (!(usr_select_menu_search == RETURN))			//便于二级查询菜单的返回
			break;
	}

	//将改变的信息重新写入到文件当中
	save_data_to_file("configure.txt", pUsr_Acount_h, pUsr_Infor_h);
	
	return 0;
}
















/*

SYSTEM_MENU_TYPE show_system_menu(USR_ROLE role);

显示系统菜单，返回当前用户所选择的菜单
SYSTEM_MENU_TYPE show_search_menu(USR_ROLE role);
当前用户选择查询功能时根据权限显示具有不同功能的查询功能的菜单
void search_usr_infor_by_id(pUSR_INFOR pUsr_Infor_List, SEARCH_ID search_id);
根据当前用户所输的学号查询相应的学生信息。
void search_usr_infor_by_name(pUSR_INFOR pUsr_Infor_List, char* search_name);
根据当前用户所输的姓名查询相应的学生信息。

pUSR_INFOR add_usr_infor(pUSR_INFOR *ppUsr_Infor_List, USR_INFOR_NUM * usr_infor_num);
添加学生信息，返回指向插入的学生的指针
pUSR_INFOR update_usr_infor(pUSR_INFOR pUsr_Infor_List,SEARCH_ID search_id);
修改学生的信息，返回指向修改后的学生的信息的指针
pUSR_INFOR delete_usr_infor(pUSR_INFOR *ppUsr_Infor_List, USR_INFOR_NUM * usr_infor_num, SEARCH_ID search_id);
删除学生的信息， 是返回所删除的学生的下一个学生的指针
void search_usr_account(pUSR_ACCOUNT pUsr_Account_List, char* search_name);
根据当前账号输入的账号名查询相应的账号信息。
pUSR_ACCOUNT add_usr_account(pUSR_ACCOUNT* ppUsr_Account_List, USR_ACCOUNT_NUM* usr_account_num );
增加账号信息，返回指向当前账号的指针
pUSR_ACCOUNT update_usr_account(pUSR_ACCOUNT pUsr_Account_List,char* search_name );
修改账号信息返回指向当前修改账号的信息
pUSR_ACCOUNT delete_usr_account(pUSR_ACCOUNT *ppUsr_Account_List,USR_ACCOUNT_NUM* usr_account_num,char* search_name );
删除账号信息，返回指向下一个账号的指针
void save_data_to_file(char * config_file_name ,pUSR_ACCOUNT pUsr_Account_List,pUSR_INFOR pUsr_Infor_List );
将学生信息和账号信息保存到文件里去。
*/