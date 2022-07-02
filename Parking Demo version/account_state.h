#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class account_state
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[40];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[40];
    my_bool       is_null[40];
  
    
    MYSQL_TIME    cht;
    MYSQL_TIME    crt;
    int aid = 0;
    int gid = 0;
    short ticket_type = 255;
    char ticket[20] = "";
    char plate[12] = "";
    time_t create_time = 0;
    int parking_type = 0;
    int present_type = 0;
    time_t intime = 0;
    int inserial = 0;
    time_t outtime = 0;
    int outserial = 0;
    time_t pay_time = 0;
    int pay_serial = 0;
    unsigned int paid_sum = 0;
    int charge_type = 0;
    time_t inner_intime = 0;
    int inner_inserial = 0;
    time_t inner_outtime = 0;
    int inner_outserial = 0;
    unsigned int limit_sum = 0;
    char online_order[255] = "";
    int insite = 0;
    int charge_site = 255;
    int inner_insite = 255;
    int inner_outsite = 255;
    int prepaid_balance = 0;
    int l2_id = 0;
    int prepaid_account_id = 65535;
    char hour_ticket_num[20] = "";
    short hour_ticket_type = 0;
    int coupon_total_sum = 0;
    int coupon_total_time = 0;
    int total_sum = 0;
    
    account_state(MYSQL *mysql);

    ~account_state();
    
    int print_account_state();
    
    int Insert_account_state();
    
    int Insert_update_account_state();
    
    int Select_account_state_by_ID(int index);
    
    int Select_account_state_by_ticket(std::string ticket);
    
    int Select_account_state_by_plate(std::string plate, int match_plate);
    
    int Delete_all_account_state();
    
    int Delete_account_state();
};