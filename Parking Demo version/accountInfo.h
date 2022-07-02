#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class accountInfo
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[36];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[36];
    my_bool       is_null[36];
    MYSQL_TIME    cht;
    MYSQL_TIME    crt;

    int id = 0;
    int gid = 0;
    char tickets[20] = "";
    short ticket_type = 255;
    char plate[12] = "";
    short access_group = 0;
    short inner_group = 0;
    short time_group = 0;
    int lots_group = 0;
    int account_state = 0;
    short parking_type = 0;
    char addr[100] ="";
    char description[100] = "";
    char email[64] = "";
    char phone[16] = "";
    char owner_name[20] = "";
    char hour_ticket_num[20] = "";
    short hour_ticket_type = 0;
    int lot_id = 0;
    char online_member[20] = "";
    short prepaid_charge_rule = 0;
    short monthly_charge_rule = 0;
    short ticket_lpbind = 0;
    short monthly_type = 0;
    short _operator = 0;
    char photo_id[20] = "";
    char add_info1[20] = "";
    char add_info2[20] = "";
    time_t start_time = 0;
    time_t end_time = 0;
    time_t limit_time = 0;
    time_t create_time = 0;
    
    accountInfo(MYSQL *mysql);

    ~accountInfo();
    
    int print_accountInfo();
        
    int Select_account_by_ID(int index);

    int Select_account_by_ticket(std::string ticket);
    
    int Select_account_by_plate(std::string plate, int match_plate);
    
    int Insert_accountInfo();
    
    int Insert_update_accountInfo();
    
    int Delete_accountInfo();
    
    int Delete_all_accountInfo();
};