#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <string.h>

//���ѧ����Ϣ������ָ������ѧ����ָ��
pUSR_INFOR add_usr_infor(pUSR_INFOR* ppUsr_Infor_h, pUSR_INFOR* ppUsr_Infor_t)
{
	system("cls");
	printf("please enter student information to add. please subject to the stable style.\n");
	printf("The stable style is usr_id usr_name cousre_id cousre_score\n");

	pUSR_INFOR pnew = (pUSR_INFOR)calloc(1, sizeof(USR_INFOR));
	scanf("%d%s%d%lf", &pnew->usr_id, pnew->usr_name, &pnew->usr_course_id, &pnew->usr_course_score);
	
	if (*ppUsr_Infor_h == NULL)					//������Ϊ��ʱ
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

//����ѧ��id�޸�ѧ������Ϣ������ָ���޸ĺ��ѧ������Ϣ��ָ��
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

//����ѧ��idɾ��ѧ������Ϣ�� �Ƿ�����ɾ����ѧ������һ��ѧ����ָ��
pUSR_INFOR delete_usr_infor(pUSR_INFOR* ppUsr_Infor_h, pUSR_INFOR* ppUsr_Infor_t, int search_id)
{
	pUSR_INFOR ptr = *ppUsr_Infor_h;			//ptrΪ����ָ��
	pUSR_INFOR pre = *ppUsr_Infor_h;			//preΪָ����ָ��֮ǰ�Ľ��

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

//��ǰ�û�ѡ���ѯ����ʱ����Ȩ����ʾ���в�ͬ���ܵĲ�ѯ���ܵĲ˵�
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
		printf("enter a number to select a function: ");	//����Ҫ�Ż�
		scanf("%d", &usr_select_menu);
	}
	else
	{
		printf("1. search by name\n");
		printf("2. search by usr_id\n");
		printf("3. return previous level\n");
		printf("enter a number to select a function: ");	//����Ҫ�Ż�
		scanf("%d", &usr_select_menu);
	}
	system("cls");
	//�����û�ѡ��ͬ�Ĺ�����ʾ����
	char usr_name[USR_NAME_LEN] = { 0 };
	int usr_id = -1;
	switch (usr_select_menu)
	{
	case SER_ALL:
		print_stu_info(pUsr_Infor_h);
		break;
	case SER_BY_NAME:
		printf("please enter a name��");
		scanf("%s", usr_name);
		search_usr_infor_by_name(pUsr_Infor_h, usr_name);

		break;
	case SER_BY_ID:
		printf("please enter a usr_id��");
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


//�����û���Ȩ����ʾϵͳ�˵������ص�ǰ�û���ѡ��Ĳ˵�
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

	//��ʾ����Ա���õĲ˵�
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
		printf("enter a number to select a function: ");	//����Ҫ�Ż�
		scanf("%d", &usr_select_meunu);
	}
	else							//�û�Ϊ��ͨ�û�
	{
		printf("\t\t\t\t1. search  student  information\n");
		printf("\t\t\t\t9. exit\n");
		printf("enter a number to select a function: ");  //����Ҫ�Ż�

		//scanf("%d", &usr_select_meunu);
		while (scanf("%d", &usr_select_meunu))
		{
			if (usr_select_meunu > 1 && usr_select_meunu < 9)
			{
				printf("enter key is fail, please enter again.\n");
				printf("enter a number to select a function: ");  //����Ҫ�Ż�
			}
			else
			{
				break;
			}
		}
		
	}
	return usr_select_meunu;
}


//朱�Ĳ��ң�����ݔ����Ñ����Ƿ�����Լ��ܴa�Ƿ����_
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


//ϵͳ��ʼ����������ʼ���ڴ��е�ѧ����Ϣ������˺�����
void system_init(const char* config_file_name, pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t, pUSR_INFOR* pUsr_Infor_h, pUSR_INFOR* pUsr_Infor_t)
{
	FILE* input_file1 = NULL, *input_file2 = NULL, *input_file = NULL;
	char tmp[50] = { 0 };

	input_file = fopen(config_file_name, "r+");
	
	//���û��˻��ļ�
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

	//��ѧ����Ϣ�ļ�
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

	//����ļ���ʧ��
	if (input_file1 == NULL || input_file2 == NULL)
	{
		perror("file1 | file2");
		exit(-1);
	}
	/*char buf[50] = { 0 };
	fgets(buf, 50, input_file2);*/

	//static cnt = 0;					//ͳ���������

	//�����Ñ��~����Ϣ����
	pUSR_ACCOUNT tmp_acc = (pUSR_ACCOUNT)calloc(1, sizeof(USR_ACCOUNT));
	
	while (memset(tmp_acc, 0, sizeof(USR_ACCOUNT)), fscanf(input_file1, "%s%s%d", tmp_acc->usr_name, tmp_acc->usr_pwd, &tmp_acc->usr_role) != EOF)
	{
		pUSR_ACCOUNT paccount_new = (pUSR_ACCOUNT)calloc(1, sizeof(USR_ACCOUNT));
		if (paccount_new == NULL)
		{
			printf("�ڴ����ʧ��\n");
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

	//�����W����Ϣ����
	pUSR_INFOR tmp_info = (pUSR_INFOR)calloc(1, sizeof(USR_INFOR));
	while (memset(tmp_info, 0, sizeof(USR_INFOR)), fscanf(input_file2, "%d%s%d%lf", &tmp_info->usr_id, tmp_info->usr_name, &tmp_info->usr_course_id, &tmp_info->usr_course_score) != EOF)
	{
		//�����W����Ϣ����
		pUSR_INFOR pinfor_new = (pUSR_INFOR)calloc(1, sizeof(USR_INFOR));
		if (pinfor_new == NULL)
		{
			printf("�ڴ����ʧ��\n");
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
	//return cnt;				//��������ĸ���
}

//��ʾ�û���Ϣ
void print_stu_info(pUSR_INFOR pUsr_Infor_h)
{
	printf("student_id\tusr_name\tusr_course_id\tusr_course_score\n");
	while (pUsr_Infor_h)
	{
		
		printf("%d \t\t%s\t\t%d\t\t%.2lf\n", pUsr_Infor_h->usr_id, pUsr_Infor_h->usr_name, pUsr_Infor_h->usr_course_id, pUsr_Infor_h->usr_course_score);
		pUsr_Infor_h = pUsr_Infor_h->pNext_Usr_Infor;
	}
}


//���ݵ�ǰ�û������ѧ�Ų�ѯ��Ӧ��ѧ����Ϣ
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

//���ݵ�ǰ�û������������ѯ��Ӧ��ѧ����Ϣ
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


/*********************�����ǶԹ���ϵͳ���˻���Ϣ�Ĳ���******************************/

//���ݵ�ǰ�˺�������˺�����ѯ��Ӧ���˺���Ϣ
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

//�����˺���Ϣ������ָ��ǰ�˺ŵ�ָ��
pUSR_ACCOUNT add_usr_account(pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t)
{
	system("cls");
	printf("please enter account information to add. please subject to the stable style.\n");
	printf("The stable style is usr_name usr_pwd usr_role\n");

	pUSR_ACCOUNT pnew = (pUSR_ACCOUNT)calloc(1, sizeof(USR_ACCOUNT));
	scanf("%s%s%d", pnew->usr_name, pnew->usr_pwd, &pnew->usr_role);

	if (*pUsr_Acount_h == NULL)					//������Ϊ��ʱ
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

//�޸��˺���Ϣ����ָ��ǰ�޸��˺ŵ���Ϣ
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

//ɾ���˺���Ϣ������ָ����һ���˺ŵ�ָ��
pUSR_ACCOUNT delete_usr_account(pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t, char* search_name)
{
	pUSR_ACCOUNT ptr = *pUsr_Acount_h;			//ptrΪ����ָ��
	pUSR_ACCOUNT pre = *pUsr_Acount_h;			//preΪָ����ָ��֮ǰ�Ľ��

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


//��ʾ�û����˺���Ϣ
void print_account(pUSR_ACCOUNT pUsr_Acount_h)
{
	printf("usr_name\tusr_pwd\t\tusr_role\n");
	while (pUsr_Acount_h)
	{

		printf("%s\t\t%s\t\t%d\n", pUsr_Acount_h->usr_name, pUsr_Acount_h->usr_pwd, pUsr_Acount_h->usr_role);
		pUsr_Acount_h = pUsr_Acount_h->pNext_Usr_Account;
	}
}



//��ѧ����Ϣ���˺���Ϣ���浽�ļ���ȥ
void save_data_to_file(char* config_file_name, pUSR_ACCOUNT pUsr_Acount_h, pUSR_INFOR pUsr_Infor_h)
{
	FILE* input_file1 = NULL, * input_file2 = NULL, * input_file = NULL;
	char tmp[50] = { 0 };

	input_file = fopen(config_file_name, "r+");

	//���û��˻��ļ�
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

	//��ѧ����Ϣ�ļ�
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

	//����ļ���ʧ��
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