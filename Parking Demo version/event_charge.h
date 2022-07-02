#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class event_charge
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[41];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[41];
    my_bool       is_null[41];
    
    MYSQL_TIME    cht;
    MYSQL_TIME    crt;
    int socket = -1;

    long aid = 0;
    int gid = 0;
    int charge_serial = 0;
    int actually_pay = 0;
    unsigned short charge_type = 255;
    unsigned short payment_type = 255;
    int in_serial = 0;
    short isnotup = 0;
    char ticket[20] = "";
    unsigned short ticket_type = 0;
    char plate[20] = "";
    char online_member_id[22] = "";
    char order_num[255] = "";
    char other_order_num[255] = "";
    unsigned int park_duration = 0;
    char photo_id[64] = "";
    int should_pay = 0;
    unsigned short site = 255;
    int group_prepaid_serial = 65535;
    unsigned int balance = 0;
    int coupon_type = 0;
    short _operator = 0;
    short reserve_state = 0;
    short warn = 0;
    unsigned short pcode = 0;
    short invoiced = 0;
    int tpid = 65535;
    unsigned int coupon_out_id = 0;
    int lotid = 0;
    char phone[12] = "";
    char owner_name[20] = "";
    
    
    
    
    time_t charge_time = 0;
    time_t start_time = 0;
    time_t end_time = 0;
    time_t in_time = 0;
    time_t rece_time = 0;
    
    event_charge(MYSQL *mysql);

    ~event_charge();
            
    int print_charge_event();
        
    int Select_charge_event_by_id(int index);
    
    int Select_charge_event_by_ticket(std::string ticket);

    int Select_charge_event_by_plate(std::string curr_plate, int match_plate);
    
    int Insert_update_charge_event();
    
    int Delete_charge_event();
    
    int Delete_All_charge_Events();

            
};