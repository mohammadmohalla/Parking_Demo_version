#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <mysql/mysql.h>

class sys_user
{
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[30];
    MYSQL_BIND    bind[30];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[30];
    my_bool       is_null[30];
    
    MYSQL_TIME    dob_t;
    MYSQL_TIME    last_login_t;
    MYSQL_TIME    block_t;
    MYSQL_TIME    lock_t;
    
public:
    
    int id = 0;
    char full_name[255] = "";
    char username[255] = "";
    char password_hash[255] = "";
    time_t dob_time;
    char mobile[255] = "";
    char phone[255] = "";
    char email[255] = "";
    char photo[255] = "";
    char login_from_ip[255] = "";
    time_t last_login_time;
    int is_blocked = 0;
    time_t    block_time;
    int is_locked = 0;
    time_t    lock_time;
    int password_try_counter = 0;
    int first_login_success = 0;
    char authorities[255] = "";
    
    sys_user(MYSQL *_mysql);

    ~sys_user();
    
    int Print_sys_user();
    
    int select_sys_user(int _id);
    
    int insert_update_sys_user();
    
    int delete_sys_user();
};