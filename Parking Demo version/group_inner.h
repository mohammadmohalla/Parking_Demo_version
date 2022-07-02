#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>


class group_inner
{
public:
    
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[10];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[10];
    my_bool       is_null[10];
    
    MYSQL_TIME    crt;
    
    long id = 0;
    long gid = 0;
    short inner_charge = 255;
    char name[50] = "";
    char sites_list[100] = "";
    short outer_charge = 255;
    short flag = 0;
    short _operator = 0;
    
    int _sites_list[100];
    
    time_t createtime;
    
    group_inner(MYSQL *_mysql);

    ~group_inner();\

    int print_group_inner();

    int Insert_update_group_inner();
    
    int Select_group_inner_by_ID(int idx);
    
    int Delete_group_inner();
    
};