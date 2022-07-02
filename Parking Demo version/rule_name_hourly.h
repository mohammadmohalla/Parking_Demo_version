#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <mysql/mysql.h>

class rule_name_hourly_type
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[14];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[14];
    my_bool       is_null[14];
    
    MYSQL_TIME    crt;
    int aid = 0;
    int gid = 0;
    int rule_serial = 255;
    char fixed_time[20] = "";
    short limit_enable = 0;
    int limit_sum = 0;
    char name[50] = "";
    int within_duration = 0;
    char remark[255] = "";
    short tolerance = 0;
    short flag = 0;
    short _operator = 0;
    time_t create_time = 0;

    rule_name_hourly_type(MYSQL *mysql);

    ~rule_name_hourly_type();
    
    int print_rule_name_hourly_type();
            
    int Update_rule_name_hourly_type();
        
    int Select_rule_name_hourly_type_by_rule_serial(int serial);
        
    int Delete_rule_name_hourly_type();
    
};
