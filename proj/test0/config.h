#ifndef __CONFIG_H__
#define __CONFIG_H__


#define USR_NAME_LEN 20
#define USR_PWD_LEN 20

//定义账户的身份类型，管理员或者普通用户
typedef enum USR_ROLE
{
	ADMIN,
	COMMON,
}USR_ROLE;

//一级菜单的类别
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

//二级查询菜单的类别
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

typedef int USR_INFOR_NUM;							//用户个数



//系统初始化函数。初始化内存中的学生信息链表和账号列表
void system_init(const char* config_file_name, pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t, pUSR_INFOR* pUsr_Infor_h, pUSR_INFOR* pUsr_Infor_t);

//根据输入的用户名和密码检查是否合法并确认当前账号的权限（管理员或普通用户）
USR_ROLE comfirm_usr(pUSR_ACCOUNT pUsr_Acount_h, char* usr_name, char* usr_pwd);

//根据用户的权限显示系统菜单，返回当前用户所选择的菜单
SYSTEM_MENU_TYPE show_system_menu(USR_ROLE role);

/*********************以下是对管理系统中学生信息的操作******************************/
//当前用户选择查询功能时根据权限显示具有不同功能的查询功能的菜单
SYSTEM_MENU_TYPE_TWO show_search_menu(USR_ROLE role, pUSR_INFOR pUsr_Infor_h);

//显示学生的全部信息
void print_stu_info(pUSR_INFOR pUsr_Infor_h);

//根据当前用户所输的学号查询相应的学生信息
int search_usr_infor_by_id(pUSR_INFOR pUsr_Infor_h, int search_id);

//根据当前用户所输的姓名查询相应的学生信息
int search_usr_infor_by_name(pUSR_INFOR pUsr_Infor_h, char* search_name);

//添加学生信息，返回指向插入的学生的指针
pUSR_INFOR add_usr_infor(pUSR_INFOR* ppUsr_Infor_h, pUSR_INFOR* ppUsr_Infor_t);

//修改学生的信息，返回指向修改后的学生的信息的指针
pUSR_INFOR update_usr_infor(pUSR_INFOR ppUsr_Infor_h, int search_id);

//删除学生的信息， 是返回所删除的学生的下一个学生的指针
pUSR_INFOR delete_usr_infor(pUSR_INFOR* ppUsr_Infor_h, pUSR_INFOR* ppUsr_Infor_t, int search_id);


/*********************以下是对管理系统中账户信息的操作******************************/
//根据当前账号输入的账号名查询相应的账号信息
void search_usr_account(pUSR_ACCOUNT pUsr_Acount_h, char* search_name, USR_ROLE role);

//增加账号信息，返回指向当前账号的指针
pUSR_ACCOUNT add_usr_account(pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t);

//修改账号信息返回指向当前修改账号的信息
pUSR_ACCOUNT update_usr_account(pUSR_ACCOUNT pUsr_Account_List, char* search_name);

//删除账号信息，返回指向下一个账号的指针
pUSR_ACCOUNT delete_usr_account(pUSR_ACCOUNT* pUsr_Acount_h, pUSR_ACCOUNT* pUsr_Acount_t, char* search_name);

//将学生信息和账号信息保存到文件里去
void save_data_to_file(char* config_file_name, pUSR_ACCOUNT pUsr_Account_List, pUSR_INFOR pUsr_Infor_List);

void print_account(pUSR_ACCOUNT pUsr_Acount_h);





#endif
