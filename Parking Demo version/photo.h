#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class photo
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[30];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[30];
    my_bool       is_null[30];
    MYSQL_TIME    receive_t;
    MYSQL_TIME    event_t;

    int id = 0;
    int gid = 0;
    char country[50] = "";
    char camera_address[50] = "";
    char photo_name[50] = "";
    time_t receive_time = 0;
    char object_type[50] = "";
    char original_bounding_box[50] = "";
    int speed = 0;
    char driving_direction[50] = "";
    char master_of_car[50] = "";
    char plate_number[12] = "";
    char ticket[20] = "";
    char garage_event_type[20] = "";
    int garage_event_serial = 0;
    char plate_color[50] = "";
    char plate_type[50] = "";
    int event_lane = 0;
    char event_type[50] = "";
    time_t event_time = 0;
    char vehicle_color[50] = "";
    char vehicle_size[50] = "";
    char vehicle_type[50] = "";
    char photo_path[255] = "";
    
    photo(MYSQL *mysql);

    ~photo();
    
    int print_photo();
        
    int Select_photo_by_ID(int index);
    
    int Insert_photo();
    
    int Delete_photo();
    
    int Delete_all_photo();
};