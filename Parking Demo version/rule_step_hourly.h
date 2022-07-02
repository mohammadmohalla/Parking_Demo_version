#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <mysql/mysql.h>

class rule_step_hourly_type
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[2];
    MYSQL_BIND    bind[25];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[25];
    my_bool       is_null[25];
    
    MYSQL_TIME    sttime;
    MYSQL_TIME    entime;
    MYSQL_TIME    crt;
    int gid = 0;
    int rule_serial = 255;
    int block_serial = 256;
    char brief[255] = "";
    short type = 0;
    short cross_period = 0;
    short deduct = 0;
    int duration = 0;
    time_t starttime = 0;
    time_t endtime = 0;
    int max_sum = 0;
    short relation = 0;
    char reserve[50] = "";
    short is_integer = 0;
    int sum = 0;
    short next_serial = 0;
    short flag = 0;
    short _operator = 0;
    time_t createtime = 0;
    short start_week = 0;
    short end_week = 0;

    rule_step_hourly_type(MYSQL *mysql);

    ~rule_step_hourly_type();
    
    int print_rule_step_hourly_type();
            
    int Update_rule_step_hourly_type();
        
    int Select_rule_step_hourly_type_by_rule_block_serial(int _rule_serial, int _block_serial);
    
    int Delete_all_rule_step_hourly_type_by_rule_serial(int garage_id, int _rule_serial);
        
    int Delete_rule_step_hourly_type();
    
};

