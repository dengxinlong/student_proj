/*
 *����˵��������ĿΪѧ����Ϣ����ϵͳ
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

	//�Ñ����
	usr_land(usr_name, usr_pwd);
	//�_�J�Ñ�
	USR_ROLE usr_role = comfirm_usr(pUsr_Acount_h, usr_name, usr_pwd);
	//USR_ROLE usr_role = ADMIN;     /////////////////////////////////////////////////

	//�����û���Ȩ����ʾϵͳ�˵�
	SYSTEM_MENU_TYPE usr_select_menu1;
	SYSTEM_MENU_TYPE_TWO usr_select_menu_search = 3;
	int usr_id = -1;
	char usr_acc_name[USR_NAME_LEN] = { 0 };
	int tmp = 0;
	while (1)
	{
		usr_select_menu1 = show_system_menu(usr_role);
		if (usr_select_menu1 == EXIT)						//ֱ���˳�
		{
			break;
		}

		//�����ܲ˵�ѡ��
		switch (usr_select_menu1)
		{
		case SER_STU_INFO:
			//��ǰ�û�ѡ���ѯ����ʱ����Ȩ����ʾ���в�ͬ���ܵĲ�ѯ���ܵĲ˵�
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
			printf("please enter the usr_id to update: ");				//������
			scanf("%d", &usr_id);
			update_usr_infor(pUsr_Infor_h, usr_id);
			print_stu_info(pUsr_Infor_h);
			printf("enter number 0 to return ");
			scanf("%d", &tmp);
			break;
		case SER_USR_ACC:
			system("cls");
			printf("please enter the usr_name to search: ");				//������
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
			printf("please enter the usr_name to update: ");				//������
			scanf("%s", &usr_acc_name);
			update_usr_account(pUsr_Acount_h, usr_acc_name);
			print_account(pUsr_Acount_h);
			printf("enter number 0 to return ");
			scanf("%d", &tmp);
			break;
		}
		if (!(usr_select_menu_search == RETURN))			//���ڶ�����ѯ�˵��ķ���
			break;
	}

	//���ı����Ϣ����д�뵽�ļ�����
	save_data_to_file("configure.txt", pUsr_Acount_h, pUsr_Infor_h);
	
	return 0;
}
















/*

SYSTEM_MENU_TYPE show_system_menu(USR_ROLE role);

��ʾϵͳ�˵������ص�ǰ�û���ѡ��Ĳ˵�
SYSTEM_MENU_TYPE show_search_menu(USR_ROLE role);
��ǰ�û�ѡ���ѯ����ʱ����Ȩ����ʾ���в�ͬ���ܵĲ�ѯ���ܵĲ˵�
void search_usr_infor_by_id(pUSR_INFOR pUsr_Infor_List, SEARCH_ID search_id);
���ݵ�ǰ�û������ѧ�Ų�ѯ��Ӧ��ѧ����Ϣ��
void search_usr_infor_by_name(pUSR_INFOR pUsr_Infor_List, char* search_name);
���ݵ�ǰ�û������������ѯ��Ӧ��ѧ����Ϣ��

pUSR_INFOR add_usr_infor(pUSR_INFOR *ppUsr_Infor_List, USR_INFOR_NUM * usr_infor_num);
���ѧ����Ϣ������ָ������ѧ����ָ��
pUSR_INFOR update_usr_infor(pUSR_INFOR pUsr_Infor_List,SEARCH_ID search_id);
�޸�ѧ������Ϣ������ָ���޸ĺ��ѧ������Ϣ��ָ��
pUSR_INFOR delete_usr_infor(pUSR_INFOR *ppUsr_Infor_List, USR_INFOR_NUM * usr_infor_num, SEARCH_ID search_id);
ɾ��ѧ������Ϣ�� �Ƿ�����ɾ����ѧ������һ��ѧ����ָ��
void search_usr_account(pUSR_ACCOUNT pUsr_Account_List, char* search_name);
���ݵ�ǰ�˺�������˺�����ѯ��Ӧ���˺���Ϣ��
pUSR_ACCOUNT add_usr_account(pUSR_ACCOUNT* ppUsr_Account_List, USR_ACCOUNT_NUM* usr_account_num );
�����˺���Ϣ������ָ��ǰ�˺ŵ�ָ��
pUSR_ACCOUNT update_usr_account(pUSR_ACCOUNT pUsr_Account_List,char* search_name );
�޸��˺���Ϣ����ָ��ǰ�޸��˺ŵ���Ϣ
pUSR_ACCOUNT delete_usr_account(pUSR_ACCOUNT *ppUsr_Account_List,USR_ACCOUNT_NUM* usr_account_num,char* search_name );
ɾ���˺���Ϣ������ָ����һ���˺ŵ�ָ��
void save_data_to_file(char * config_file_name ,pUSR_ACCOUNT pUsr_Account_List,pUSR_INFOR pUsr_Infor_List );
��ѧ����Ϣ���˺���Ϣ���浽�ļ���ȥ��
*/