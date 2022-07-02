#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class rule_step_monthly
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[3];
    MYSQL_BIND    bind[10];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[10];
    my_bool       is_null[10];
    
    MYSQL_TIME    crt;
    

    unsigned long gid = 0;
    unsigned long rule_serial = -1;
    unsigned long step_serial = -1;
    unsigned long max_units = 0;
    unsigned long duration = 0;
    unsigned long unit_sum = 0;
    short flag = 0;
    int _operator = 0;
    time_t createtime = 0;
    
    
    
    rule_step_monthly(MYSQL *mysql);

    ~rule_step_monthly();
            
    int print_rule_step_monthly();
    
    int Insert_Update_rule_step_monthly();
    
    int Select_rule_step_monthly_by_serial(int garage_id, int _rule_serial, int _step_serial);
    
    int Delete_all_rule_step_monthly(int garage_id, int _rule_serial);
            
    int Delete_rule_step_monthly();
};