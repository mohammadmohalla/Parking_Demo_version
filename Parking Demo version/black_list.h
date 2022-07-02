#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <mysql/mysql.h>

class black_list_type
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[9];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[9];
    my_bool       is_null[9];
    
    MYSQL_TIME    crt;
    
    int id = 0;
    int gid = 0;
    char description[200] = "";
    char ticket[20] = "";
    short ticket_type = 255;
    char plate[12] = "";
    short _operator = 0;
    time_t create_time = 0;

    black_list_type(MYSQL *mysql);

    ~black_list_type();
        
    int print_black_list();

    int Insert_Update_black_list_type();
        
    int Select_black_list_type_by_id(int index);
        
    int Delete_black_list_type();
    
};