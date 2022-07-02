#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <mysql/mysql.h>


class server_errors_log
{
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[10];
    MYSQL_BIND    bind[10];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[10];
    my_bool       is_null[10];
    
    MYSQL_TIME    err_t;
    MYSQL_TIME    created_t;
    
public:
    
    int id = 0;
    int gid = -1;
    char err_code[20] = "";
    char err_msg[65535] = "";
    char err_pos[255] = "";
    time_t err_time = -1;
    time_t created_at = 0;
    
    server_errors_log(MYSQL *_mysql);

    ~server_errors_log();
    
    int Print_server_errors_log();
    
    int select_server_errors_log(int _id);
    
    int insert_update_server_errors_log();
    
    int delete_server_errors_log();
};