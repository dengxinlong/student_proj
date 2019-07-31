#ifndef __CONFIG_H__
#define __CONFIG_H__


#define USR_NAME_LEN 20
#define USR_PWD_LEN 20

//�����˻���������ͣ�����Ա������ͨ�û�
typedef enum USR_ROLE
{
	ADMIN,
	COMMON,
}USR_ROLE;

//һ���˵������
typedef enum SYSTEM_MENU_TYPE
{
	SER_STU_INFO = 1,
	ADD_STU_INFO,
	DEL_STU_INFO,
	UP_STU_INFO,
	SER_USR_ACC,
	ADD_USR_ACC,
	DEL_USR_ACC,
	UP_USR_ACC,
	EXIT,
}SYSTEM_MENU_TYPE;

//������ѯ�˵������
typedef enum SYSTEM_MENU_TYPE_TWO
{
	SER_ALL = 0,
	SER_BY_NAME,
	SER_BY_ID,
	RETURN,
}SYSTEM_MENU_TYPE_TWO;

typedef struct usr_account_tag
{
	char usr_name[USR_NAME_LEN];
	char usr_pwd[USR_PWD_LEN];
	USR_ROLE  usr_role;
	struct usr_account_tag* pNext_Usr_Account;
}USR_ACCOUNT, *pUSR_ACCOUNT;

typedef struct usr_infor_tag
{
	int usr_id;
	char usr_name[USR_NAME_LEN];
	int usr_course_id;
	double usr_course_score;
	struct usr_infor_tag* pNext_Usr_Infor;

}USR_INFOR, *pUSR_INFOR;

typedef int USR_INFOR_NUM;							//�û�����



//ϵͳ��ʼ����������ʼ���ڴ��е�ѧ����Ϣ������˺��б�
void system_init(const char* config_file_name, pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t, pUSR_INFOR* pUsr_Infor_h, pUSR_INFOR* pUsr_Infor_t);

//����������û������������Ƿ�Ϸ���ȷ�ϵ�ǰ�˺ŵ�Ȩ�ޣ�����Ա����ͨ�û���
USR_ROLE comfirm_usr(pUSR_ACCOUNT pUsr_Acount_h, char* usr_name, char* usr_pwd);

//�����û���Ȩ����ʾϵͳ�˵������ص�ǰ�û���ѡ��Ĳ˵�
SYSTEM_MENU_TYPE show_system_menu(USR_ROLE role);

/*********************�����ǶԹ���ϵͳ��ѧ����Ϣ�Ĳ���******************************/
//��ǰ�û�ѡ���ѯ����ʱ����Ȩ����ʾ���в�ͬ���ܵĲ�ѯ���ܵĲ˵�
SYSTEM_MENU_TYPE_TWO show_search_menu(USR_ROLE role, pUSR_INFOR pUsr_Infor_h);

//��ʾѧ����ȫ����Ϣ
void print_stu_info(pUSR_INFOR pUsr_Infor_h);

//���ݵ�ǰ�û������ѧ�Ų�ѯ��Ӧ��ѧ����Ϣ
int search_usr_infor_by_id(pUSR_INFOR pUsr_Infor_h, int search_id);

//���ݵ�ǰ�û������������ѯ��Ӧ��ѧ����Ϣ
int search_usr_infor_by_name(pUSR_INFOR pUsr_Infor_h, char* search_name);

//���ѧ����Ϣ������ָ������ѧ����ָ��
pUSR_INFOR add_usr_infor(pUSR_INFOR* ppUsr_Infor_h, pUSR_INFOR* ppUsr_Infor_t);

//�޸�ѧ������Ϣ������ָ���޸ĺ��ѧ������Ϣ��ָ��
pUSR_INFOR update_usr_infor(pUSR_INFOR ppUsr_Infor_h, int search_id);

//ɾ��ѧ������Ϣ�� �Ƿ�����ɾ����ѧ������һ��ѧ����ָ��
pUSR_INFOR delete_usr_infor(pUSR_INFOR* ppUsr_Infor_h, pUSR_INFOR* ppUsr_Infor_t, int search_id);


/*********************�����ǶԹ���ϵͳ���˻���Ϣ�Ĳ���******************************/
//���ݵ�ǰ�˺�������˺�����ѯ��Ӧ���˺���Ϣ
void search_usr_account(pUSR_ACCOUNT pUsr_Acount_h, char* search_name, USR_ROLE role);

//�����˺���Ϣ������ָ��ǰ�˺ŵ�ָ��
pUSR_ACCOUNT add_usr_account(pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t);

//�޸��˺���Ϣ����ָ��ǰ�޸��˺ŵ���Ϣ
pUSR_ACCOUNT update_usr_account(pUSR_ACCOUNT pUsr_Account_List, char* search_name);

//ɾ���˺���Ϣ������ָ����һ���˺ŵ�ָ��
pUSR_ACCOUNT delete_usr_account(pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t, char* search_name);

//��ѧ����Ϣ���˺���Ϣ���浽�ļ���ȥ
void save_data_to_file(char* config_file_name, pUSR_ACCOUNT pUsr_Account_List, pUSR_INFOR pUsr_Infor_List);

void print_account(pUSR_ACCOUNT pUsr_Acount_h);





#endif
