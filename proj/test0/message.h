#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#define USR_NAME_LEN 20
#define USR_PWD_LEN 10

typedef enum USR_ROLE
{
	ADMIN;
	COM;
}USR_ROLE;

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













#endif
