#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class event_out
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[37];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[37];
    my_bool       is_null[37];
    
    MYSQL_TIME    cht;
    MYSQL_TIME    crt;
    int socket = -1;

    long aid = 0;
    int gid = 0;
    short _operator = 0;
    int out_serial = 0;
    short out_type = 0;
    char ticket[20] = "";
    short ticket_type = 0;
    char plate[12] = "";
    unsigned int total_paid = 0;
    int in_serial = 0;
    int total_lots = 0;
    int monthly_lots = 0;
    int hourly_lots = 0;
    int free_total_lots = 0;
    int free_monthly_lots = 0;
    int free_hourly_lots = 0;
    short site = 0;
    char order_num[20] = "";
    char photo_id[64] = "";
    short isnotup = 0;
    int lots_group_id = 65535;
    int lots_group_occupied = 0;
    unsigned int park_duration = 0;
    int total_should = 0;
    int coupon_total_sum = 0;
    int coupon_total_time = 0;
    int coupon_real_sum = 0;
    int coupon_real_time = 0;
    int charge_type = 0;
    int lotID = 0;
    short monthlyType = 255;
    
    
    
    time_t out_time = 0;
    time_t in_time = 0;
    time_t rece_time = 0;
    
    event_out(MYSQL *mysql);

    ~event_out();
    
    int print_event_out();
    
    int Select_exit_event_by_id(int index);
        
    int Insert_exit_event();
        
    int Delete_Exit_event();
    
    int Delete_All_Exit_Events();
            
};