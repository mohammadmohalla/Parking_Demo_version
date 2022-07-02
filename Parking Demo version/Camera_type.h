#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <mysql/mysql.h>

class Camera_type
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

    int gid = 0;
    char ip[22] = "";
    short _operator = 0;
    int cam_address = 0;
    char site_Addresses[16] = "";
    char Camera_name[50] = "";
    char user_name[20] = "";
    char password[20] = "";
    time_t create_time = 0;
    
    int sites_binded[100];

    Camera_type(MYSQL *mysql);

    ~Camera_type();
    
    int print_camera();
      
    int Insert_Update_Camera_type();
    
    int Clear_Camera_type_sites(int _address);
        
    int Insert_Update_Camera_type_binded_site();
    
    int Select_Camera_type_by_address(int address);
        
    int Delete_Camera_type();
    
};