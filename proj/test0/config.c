#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <string.h>

//添加学生信息，返回指向插入的学生的指针
pUSR_INFOR add_usr_infor(pUSR_INFOR* ppUsr_Infor_h, pUSR_INFOR* ppUsr_Infor_t)
{
	system("cls");
	printf("please enter student information to add. please subject to the stable style.\n");
	printf("The stable style is usr_id usr_name cousre_id cousre_score\n");

	pUSR_INFOR pnew = (pUSR_INFOR)calloc(1, sizeof(USR_INFOR));
	scanf("%d%s%d%lf", &pnew->usr_id, pnew->usr_name, &pnew->usr_course_id, &pnew->usr_course_score);
	
	if (*ppUsr_Infor_h == NULL)					//当链表为空时
	{
		*ppUsr_Infor_t = *ppUsr_Infor_h = pnew;
	}
	else
	{
		(*ppUsr_Infor_t)->pNext_Usr_Infor = pnew;
		*ppUsr_Infor_t = pnew;
	}
	return pnew;
}

//根据学生id修改学生的信息，返回指向修改后的学生的信息的指针
pUSR_INFOR update_usr_infor(pUSR_INFOR pUsr_Infor_h, int search_id)
{
	pUSR_INFOR pupdate = NULL;
	pUSR_INFOR ptr = pUsr_Infor_h;

	printf("please enter student information to update. please subject to the stable style.\n");
	printf("The stable style is usr_id usr_name cousre_id cousre_score\n");

	if (pUsr_Infor_h == NULL)
	{
		printf("student information is empty\n");
		return NULL;
	}
	
	while (ptr)
	{
		if (ptr->usr_id == search_id)
		{
			pupdate = ptr;
			break;
		}
		ptr = ptr->pNext_Usr_Infor;
	}

	if (ptr != NULL)
	{
		memset(&(pupdate->usr_id), 0, sizeof(pupdate->usr_id));
		memset((pupdate->usr_name), 0, USR_NAME_LEN);
		memset(&(pupdate->usr_course_id), 0, sizeof(pupdate->usr_course_id));
		memset(&(pupdate->usr_course_score), 0, sizeof(pupdate->usr_course_score));
		scanf("%d%s%d%lf", &pupdate->usr_id, pupdate->usr_name, &pupdate->usr_course_id, &pupdate->usr_course_score);
	}
	else
	{
		printf("usr_id is not true\n");
	}
	return pupdate;
}

//根据学生id删除学生的信息， 是返回所删除的学生的下一个学生的指针
pUSR_INFOR delete_usr_infor(pUSR_INFOR* ppUsr_Infor_h, pUSR_INFOR* ppUsr_Infor_t, int search_id)
{
	pUSR_INFOR ptr = *ppUsr_Infor_h;			//ptr为工作指针
	pUSR_INFOR pre = *ppUsr_Infor_h;			//pre为指向工作指针之前的结点

	if (*ppUsr_Infor_h == NULL)
	{
		printf("student information is empty\n");
		return NULL;
	}

	if ((*ppUsr_Infor_h)->usr_id == search_id)
	{
		*ppUsr_Infor_h = ptr->pNext_Usr_Infor;
		if (*ppUsr_Infor_h == NULL)
		{
			(*ppUsr_Infor_t) = NULL;
		}
		free(ptr);
	}
	else
	{
		while (ptr)
		{
			if (ptr->usr_id == search_id)
			{
				pre->pNext_Usr_Infor = ptr->pNext_Usr_Infor;
				if (ptr == *ppUsr_Infor_t)
				{
					*ppUsr_Infor_t = pre;
				}
				free(ptr);
				printf("delete succes.\n");
				return pre->pNext_Usr_Infor;
			}
			else
			{
				pre = ptr;
				ptr = ptr->pNext_Usr_Infor;
			}
		}
	}
	return NULL;
}

//当前用户选择查询功能时根据权限显示具有不同功能的查询功能的菜单
SYSTEM_MENU_TYPE_TWO show_search_menu(USR_ROLE role, pUSR_INFOR pUsr_Infor_h)
{
label1:
	system("cls");
	SYSTEM_MENU_TYPE_TWO usr_select_menu;
	if (role == ADMIN)
	{
		printf("0. search all infometion\n");
		printf("1. search by name\n");
		printf("2. search by usr_id\n");
		printf("3. return previous level\n");
		printf("enter a number to select a function: ");	//还需要优化
		scanf("%d", &usr_select_menu);
	}
	else
	{
		printf("1. search by name\n");
		printf("2. search by usr_id\n");
		printf("3. return previous level\n");
		printf("enter a number to select a function: ");	//还需要优化
		scanf("%d", &usr_select_menu);
	}
	system("cls");
	//根据用户选择不同的功能显示内容
	char usr_name[USR_NAME_LEN] = { 0 };
	int usr_id = -1;
	switch (usr_select_menu)
	{
	case SER_ALL:
		print_stu_info(pUsr_Infor_h);
		break;
	case SER_BY_NAME:
		printf("please enter a name：");
		scanf("%s", usr_name);
		search_usr_infor_by_name(pUsr_Infor_h, usr_name);

		break;
	case SER_BY_ID:
		printf("please enter a usr_id：");
		scanf("%d", &usr_id);
		search_usr_infor_by_id(pUsr_Infor_h, usr_id);
		break;
	case 3:
		return usr_select_menu;
		
	}
	printf("please enter 0 to return  ");
	int i = 1;
	scanf("%d", &i);
	if (i == 0)
	{
		goto label1;
	}

	return usr_select_menu;
}


//根据用户的权限显示系统菜单，返回当前用户所选择的菜单
SYSTEM_MENU_TYPE show_system_menu(USR_ROLE role)
{
	system("cls");
	printf("***************************************************");
	printf("**************************************************\n");
	printf("*******************************");
	printf(" Student Information Management System ");
	printf("*******************************\n");
	printf("***************************************************");
	printf("**************************************************\n");

	SYSTEM_MENU_TYPE usr_select_meunu;

	//显示管理员可用的菜单
	if (role == ADMIN)
	{
		printf("\t\t\t\t1. search  student  information\n");
		printf("\t\t\t\t2. add     student  information\n");
		printf("\t\t\t\t3. delete  student  information\n");
		printf("\t\t\t\t4. update  student  information\n");
		printf("\t\t\t\t5. search  usr      account\n");
		printf("\t\t\t\t6. add     usr      account\n");
		printf("\t\t\t\t7. delete  usr      account\n");
		printf("\t\t\t\t8. update  usr      account\n");
		printf("\t\t\t\t9. exit\n");
		printf("enter a number to select a function: ");	//还需要优化
		scanf("%d", &usr_select_meunu);
	}
	else							//用户为普通用户
	{
		printf("\t\t\t\t1. search  student  information\n");
		printf("\t\t\t\t9. exit\n");
		printf("enter a number to select a function: ");  //还需要优化

		//scanf("%d", &usr_select_meunu);
		while (scanf("%d", &usr_select_meunu))
		{
			if (usr_select_meunu > 1 && usr_select_meunu < 9)
			{
				printf("enter key is fail, please enter again.\n");
				printf("enter a number to select a function: ");  //还需要优化
			}
			else
			{
				break;
			}
		}
		
	}
	return usr_select_meunu;
}


//鏈表的查找，查找輸入的用戶名是否存在以及密碼是否正確
USR_ROLE comfirm_usr(pUSR_ACCOUNT pUsr_Acount_h, char* usr_name, char* usr_pwd)
{
	while (pUsr_Acount_h)
	{
		if (strcmp(pUsr_Acount_h->usr_name, usr_name) == 0 && strcmp(pUsr_Acount_h->usr_pwd, usr_pwd) == 0)
		{
			
			return pUsr_Acount_h->usr_role;
		}
		pUsr_Acount_h = pUsr_Acount_h->pNext_Usr_Account;
	}
	printf("\nThe pwd is fail\n");
	printf("please enter again.\n");
	
}


//系统初始化函数。初始化内存中的学生信息链表和账号链表
void system_init(const char* config_file_name, pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t, pUSR_INFOR* pUsr_Infor_h, pUSR_INFOR* pUsr_Infor_t)
{
	FILE* input_file1 = NULL, *input_file2 = NULL, *input_file = NULL;
	char tmp[50] = { 0 };

	input_file = fopen(config_file_name, "r+");
	
	//打开用户账户文件
	fgets(tmp, 50, input_file);
	int i;
	for (i = 0; tmp[i]; ++i)
	{
		;
	}
	if (tmp[i - 1] == '\n')
	{
		tmp[i - 1] = '\0';
	}
	input_file1 = fopen(tmp, "r+");

	//打开学生信息文件
	fgets(tmp, 50, input_file);
	for (i = 0; tmp[i]; ++i)
	{
		;
	}
	if (tmp[i - 1] == '\n')
	{
		tmp[i - 1] = '\0';
	}
	input_file2 = fopen(tmp, "r+");

	//如果文件打开失败
	if (input_file1 == NULL || input_file2 == NULL)
	{
		perror("file1 | file2");
		exit(-1);
	}
	/*char buf[50] = { 0 };
	fgets(buf, 50, input_file2);*/

	//static cnt = 0;					//统计链表个数

	//建立用戶賬戶信息链表
	pUSR_ACCOUNT tmp_acc = (pUSR_ACCOUNT)calloc(1, sizeof(USR_ACCOUNT));
	
	while (memset(tmp_acc, 0, sizeof(USR_ACCOUNT)), fscanf(input_file1, "%s%s%d", tmp_acc->usr_name, tmp_acc->usr_pwd, &tmp_acc->usr_role) != EOF)
	{
		pUSR_ACCOUNT paccount_new = (pUSR_ACCOUNT)calloc(1, sizeof(USR_ACCOUNT));
		if (paccount_new == NULL)
		{
			printf("内存分配失败\n");
			return;
		}
		//paccount_new->usr_name = tmp_acc->usr_name;

		for (int i = 0; tmp_acc->usr_name[i]; ++i)
		{
			paccount_new->usr_name[i] = tmp_acc->usr_name[i];
		}
		for (int i = 0; tmp_acc->usr_name[i]; ++i)
		{
			paccount_new->usr_pwd[i] = tmp_acc->usr_pwd[i];
		}
		paccount_new->usr_role = tmp_acc->usr_role;

		if (*pUsr_Acount_h == NULL)
		{
			*pUsr_Acount_h = *pUsr_Acount_t = paccount_new;
		}
		else
		{
			(*pUsr_Acount_t)->pNext_Usr_Account = paccount_new;
			(*pUsr_Acount_t) = paccount_new;
		}
		//memset(paccount_new, 0, sizeof(USR_ACCOUNT));
	}
	free(tmp_acc);

	//建立學生信息链表
	pUSR_INFOR tmp_info = (pUSR_INFOR)calloc(1, sizeof(USR_INFOR));
	while (memset(tmp_info, 0, sizeof(USR_INFOR)), fscanf(input_file2, "%d%s%d%lf", &tmp_info->usr_id, tmp_info->usr_name, &tmp_info->usr_course_id, &tmp_info->usr_course_score) != EOF)
	{
		//建立學生信息链表
		pUSR_INFOR pinfor_new = (pUSR_INFOR)calloc(1, sizeof(USR_INFOR));
		if (pinfor_new == NULL)
		{
			printf("内存分配失败\n");
			return;
		}

		for (int i = 0; tmp_info->usr_name[i]; ++i)
		{
			pinfor_new->usr_name[i] = tmp_info->usr_name[i];
		}
		pinfor_new->usr_course_id = tmp_info->usr_course_id;
		pinfor_new->usr_course_score = tmp_info->usr_course_score;
		pinfor_new->usr_id = tmp_info->usr_id;



		if (*pUsr_Infor_h == NULL)
		{
			*pUsr_Infor_h = *pUsr_Infor_t = pinfor_new;
		}
		else
		{
			(*pUsr_Infor_t)->pNext_Usr_Infor = pinfor_new;
			(*pUsr_Infor_t) = pinfor_new;
		}
	}
	free(tmp_info);
	fclose(input_file1);
	fclose(input_file2);
	fclose(input_file);
	//return cnt;				//返回链表的个数
}

//显示用户信息
void print_stu_info(pUSR_INFOR pUsr_Infor_h)
{
	printf("student_id\tusr_name\tusr_course_id\tusr_course_score\n");
	while (pUsr_Infor_h)
	{
		
		printf("%d \t\t%s\t\t%d\t\t%.2lf\n", pUsr_Infor_h->usr_id, pUsr_Infor_h->usr_name, pUsr_Infor_h->usr_course_id, pUsr_Infor_h->usr_course_score);
		pUsr_Infor_h = pUsr_Infor_h->pNext_Usr_Infor;
	}
}


//根据当前用户所输的学号查询相应的学生信息
int search_usr_infor_by_id(pUSR_INFOR pUsr_Infor_h, int search_id)
{
	printf("student_id\tusr_name\tusr_course_id\tusr_course_score\n");
	while (pUsr_Infor_h)
	{
		if (pUsr_Infor_h->usr_id == search_id)
		{
			printf("%d \t\t%s\t\t%d\t\t%.2lf\n", pUsr_Infor_h->usr_id, pUsr_Infor_h->usr_name, pUsr_Infor_h->usr_course_id, pUsr_Infor_h->usr_course_score);
			return;
		}
		pUsr_Infor_h = pUsr_Infor_h->pNext_Usr_Infor;
	}
	printf("Do not the id %d", search_id);
}

//根据当前用户所输的姓名查询相应的学生信息
int search_usr_infor_by_name(pUSR_INFOR pUsr_Infor_h, char* search_name)
{
	printf("student_id\tusr_name\tusr_course_id\tusr_course_score\n");
	while (pUsr_Infor_h)
	{
		if (strcmp(pUsr_Infor_h->usr_name, search_name) == 0)
		{
			printf("%d \t\t%s\t\t%d\t\t%.2lf\n", pUsr_Infor_h->usr_id, pUsr_Infor_h->usr_name, pUsr_Infor_h->usr_course_id, pUsr_Infor_h->usr_course_score);
			return;
		}
		pUsr_Infor_h = pUsr_Infor_h->pNext_Usr_Infor;
	}
	printf("Do not the id %s\n", search_name);
}


/*********************以下是对管理系统中账户信息的操作******************************/

//根据当前账号输入的账号名查询相应的账号信息
void search_usr_account(pUSR_ACCOUNT pUsr_Acount_h, char* search_name, USR_ROLE role)
{
	if (role == ADMIN)
	{
		while (pUsr_Acount_h)
		{
			if (strcmp(pUsr_Acount_h->usr_name, search_name) == 0 && pUsr_Acount_h->usr_role != ADMIN)
			{
				printf("usr_name\tusr_pwd\tusr_role\n");
				printf("%s  %s  %d\n", pUsr_Acount_h->usr_name, pUsr_Acount_h->usr_pwd, pUsr_Acount_h->usr_role);
				break;
			}
			pUsr_Acount_h = pUsr_Acount_h->pNext_Usr_Account;
		}
		if (pUsr_Acount_h == NULL)
			printf("The search usr is not exist or the usr is ADMIN\n");
	}
	else
	{
		printf("Your right is fail.\n");
	}
}

//增加账号信息，返回指向当前账号的指针
pUSR_ACCOUNT add_usr_account(pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t)
{
	system("cls");
	printf("please enter account information to add. please subject to the stable style.\n");
	printf("The stable style is usr_name usr_pwd usr_role\n");

	pUSR_ACCOUNT pnew = (pUSR_ACCOUNT)calloc(1, sizeof(USR_ACCOUNT));
	scanf("%s%s%d", pnew->usr_name, pnew->usr_pwd, &pnew->usr_role);

	if (*pUsr_Acount_h == NULL)					//当链表为空时
	{
		*pUsr_Acount_h = *pUsr_Acount_t = pnew;
	}
	else
	{
		(*pUsr_Acount_t)->pNext_Usr_Account = pnew;
		*pUsr_Acount_t = pnew;
	}
	return pnew;
}

//修改账号信息返回指向当前修改账号的信息
pUSR_ACCOUNT update_usr_account(pUSR_ACCOUNT pUsr_Acount_h, char* search_name)
{
	pUSR_ACCOUNT pupdate = NULL;
	pUSR_ACCOUNT ptr = pUsr_Acount_h;

	printf("please enter student information to update. please subject to the stable style.\n");
	printf("The stable style is usr_name usr_pwd usr_role\n");

	if (pUsr_Acount_h == NULL)
	{
		printf("student information is empty\n");
		return NULL;
	}

	while (ptr)
	{
		if (strcmp(ptr->usr_name, search_name) == 0)
		{
			pupdate = ptr;
			break;
		}
		ptr = ptr->pNext_Usr_Account;
	}

	if (ptr != NULL)
	{
		memset(pupdate->usr_name, 0, USR_NAME_LEN);
		memset(pupdate->usr_pwd, 0, USR_PWD_LEN);
		memset(&(pupdate->usr_role), 0, sizeof(pupdate->usr_role));
		scanf("%s%s%d", pupdate->usr_name, pupdate->usr_pwd, &pupdate->usr_role);
	}
	else
	{
		printf("usr_name is not true\n");
	}
	return pupdate;


}

//删除账号信息，返回指向下一个账号的指针
pUSR_ACCOUNT delete_usr_account(pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t, char* search_name)
{
	pUSR_ACCOUNT ptr = *pUsr_Acount_h;			//ptr为工作指针
	pUSR_ACCOUNT pre = *pUsr_Acount_h;			//pre为指向工作指针之前的结点

	if (*pUsr_Acount_h == NULL)
	{
		printf("student information is empty\n");
		return NULL;
	}

	if (strcmp((*pUsr_Acount_h), search_name) == 0)
	{
		*pUsr_Acount_h = ptr->pNext_Usr_Account;
		if (*pUsr_Acount_h == NULL)
		{
			(*pUsr_Acount_t) = NULL;
		}
		free(ptr);
	}
	else
	{
		while (ptr)
		{
			if (strcmp(ptr->usr_name, search_name) == 0)
			{
				pre->pNext_Usr_Account = ptr->pNext_Usr_Account;
				if (ptr == *pUsr_Acount_t)
				{
					*pUsr_Acount_t = pre;
				}
				free(ptr);
				printf("delete succes.\n");
				if (pre->pNext_Usr_Account != NULL)
					return pre->pNext_Usr_Account;
				else
				{
					return NULL;
				}
			}
			else
			{
				pre = ptr;
				ptr = ptr->pNext_Usr_Account;
			}
		}
		printf("delete usr is not exist.\n");
	}
	return NULL;
}


//显示用户的账号信息
void print_account(pUSR_ACCOUNT pUsr_Acount_h)
{
	printf("usr_name\tusr_pwd\t\tusr_role\n");
	while (pUsr_Acount_h)
	{

		printf("%s\t\t%s\t\t%d\n", pUsr_Acount_h->usr_name, pUsr_Acount_h->usr_pwd, pUsr_Acount_h->usr_role);
		pUsr_Acount_h = pUsr_Acount_h->pNext_Usr_Account;
	}
}



//将学生信息和账号信息保存到文件里去
void save_data_to_file(char* config_file_name, pUSR_ACCOUNT pUsr_Acount_h, pUSR_INFOR pUsr_Infor_h)
{
	FILE* input_file1 = NULL, * input_file2 = NULL, * input_file = NULL;
	char tmp[50] = { 0 };

	input_file = fopen(config_file_name, "r+");

	//打开用户账户文件
	fgets(tmp, 50, input_file);
	int i;
	for (i = 0; tmp[i]; ++i)
	{
		;
	}
	if (tmp[i - 1] == '\n')
	{
		tmp[i - 1] = '\0';
	}
	input_file1 = fopen(tmp, "r+");

	//打开学生信息文件
	fgets(tmp, 50, input_file);
	for (i = 0; tmp[i]; ++i)
	{
		;
	}
	if (tmp[i - 1] == '\n')
	{
		tmp[i - 1] = '\0';
	}
	input_file2 = fopen(tmp, "r+");

	//如果文件打开失败
	if (input_file1 == NULL || input_file2 == NULL)
	{
		perror("file1 | file2");
		exit(-1);
	}

	while (pUsr_Acount_h)
	{
		fprintf(input_file1, "%s %s %d", pUsr_Acount_h->usr_name, pUsr_Acount_h->usr_pwd, pUsr_Acount_h->usr_role);
		if (pUsr_Acount_h->pNext_Usr_Account)
			fputc('\n', input_file1);
		pUsr_Acount_h = pUsr_Acount_h->pNext_Usr_Account;
	}

	while (pUsr_Infor_h)
	{
		fprintf(input_file2, "%d %s %d %.2lf", pUsr_Infor_h->usr_id, pUsr_Infor_h->usr_name, pUsr_Infor_h->usr_course_id, pUsr_Infor_h->usr_course_score);
		if (pUsr_Infor_h->pNext_Usr_Infor)
			fputc('\n', input_file2);
		pUsr_Infor_h = pUsr_Infor_h->pNext_Usr_Infor;
	}
	
	fclose(input_file1);
	fclose(input_file2);
	fclose(input_file);
}