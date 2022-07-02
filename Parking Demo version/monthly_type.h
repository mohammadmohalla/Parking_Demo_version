#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class monthly_type
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[2];
    MYSQL_BIND    bind[19];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[19];
    my_bool       is_null[19];
    
    MYSQL_TIME    crt;
    

    unsigned long aid;
    int id = -1;
    unsigned long gid = 0;
    short type = 0xff;
    int access_group_id = 0xffff;
    unsigned short time_group_id = 0xff;
    unsigned short inner_group_id = 0xff;
    unsigned short monthly_charge_rule = 0xff;
    unsigned short prepaid_charge_rule = 0xff;
    unsigned short vip_flag = 0xff;
    unsigned long reserved = 0;
    char name[64] = "";
    char description[255] = "";
    short flag = 0;
    int _operator = 0;
    time_t createtime = 0;
    unsigned short lotgroup_countingtype = 0;
    unsigned short expires = 0xff;
    
    monthly_type(MYSQL *mysql);

    ~monthly_type();
    
    int print_monthly_type();
            
    int Insert_Update_monthly_type();
    
    int Select_monthly_type_by_id(int id, int garage_id);
            
    int Delete_monthly_type();
};