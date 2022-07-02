#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <mysql/mysql.h>

class monthly_to_hourly_type
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[8];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[8];
    my_bool       is_null[8];
    
    MYSQL_TIME    crt;
    
    int id = 0;
    int gid = 0;
    char name[50] = "";
    char hour_charge_type[50] = "";
    short flag = 0;
    short _operator = 0;
    time_t create_time = 0;

    monthly_to_hourly_type(MYSQL *mysql);

    ~monthly_to_hourly_type();
    
    int print_monthly_to_hourly_type();
            
    int Update_monthly_to_hourly_type();
        
    int Select_monthly_to_hourly_type_by_id(int index);
        
    int Delete_monthly_to_hourly_type();
    
};