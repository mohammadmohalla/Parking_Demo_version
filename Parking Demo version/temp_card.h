#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class temp_card
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[54];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[54];
    my_bool       is_null[54];
    
    MYSQL_TIME    cht;
    MYSQL_TIME    crt;
    
    
    long id = 0;
    short operate_type = 0;
    unsigned int ticket_type = 255;
    char ticket[20] = "";
    char plate[12]  = "";
    unsigned int account_state = 0;
    unsigned int parking_type  = 0;
    int present_type = 0;
    int insite = 0;
    int charge_site = 0;
    int inner_insite = 0;
    int inner_outsite = 0;
    int coupon_total_time = 0;
    int coupon_total_sum = 0;
    int limit_sum = 0;
    int paid_sum = 0;
    char online_order[255] = "";
    unsigned short hour_ticket_type = 0;
    char hour_ticket_num[20] = "";
    int charge_type = 0;
    int access_group = 0;
    int prepaid_balance = 0;
    int prepaid_account_id = 0;
    int monthly_type = 0;
    int lots_group = 0;
    int ticket_lpbind = 0;
    int inner_group = 0;
    int time_group = 0;
    char lot_name[50] = "";
    int prepaid_charge_rule = 0;
    int monthly_charge_rule = 0;
    char photo_id[255] = "";
    char owner_name[20] = "";
    char phone[16] = "";
    char email[65] = "";
    char addr[100] = "";
    char description[64] = "";
    char add_info1[255]  = "";
    char add_info2[255]  = "";
    short has_downloaded = 0;
    
    
    
    time_t in_time = 0;
    time_t pay_time = 0;
    time_t inner_intime = 0;
    time_t inner_outtime = 0;
    time_t limit_time = 0;
    time_t start_time = 0;
    time_t end_time = 0;
    
    temp_card(MYSQL *mysql);

    ~temp_card();
    
    int print_Temp_Account();
    
    int Insert_Temp_Account();
    
    int Insert_Update_Temp_Account();
    
    int Select_Temp_Account_id(int index);
    
    int Select_Temp_Account_by_plate(std::string plate, int match_plate);
    
    int Delete_Temp_Account();
    
    int Delete_All_Temp_Accounts();
        

            
};