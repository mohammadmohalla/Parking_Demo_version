#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class rule_name_monthly
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[2];
    MYSQL_BIND    bind[8];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[8];
    my_bool       is_null[8];
    
    MYSQL_TIME    crt;
    

    unsigned long gid;
    unsigned long rule_serial = -1;
    char name[50] = "";
    char remark[200] = "";
    short flag = 0;
    int _operator = 0;
    time_t createtime = 0;
    
    rule_name_monthly(MYSQL *mysql);

    ~rule_name_monthly();
            
    int print_rule_name_monthly();
    
    int Insert_Update_rule_name_monthly();
    
    int Select_rule_name_monthly_by_serial(int serial, int garage_id);
            
    int Delete_rule_name_monthly();
};