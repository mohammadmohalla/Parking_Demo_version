#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class event_payment
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[27];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[27];
    my_bool       is_null[27];
    
    MYSQL_TIME    cht;
    MYSQL_TIME    crt;
    int socket = -1;

    long aid = 0;
    int gid = 0;
    short _operator = 0;
    int serial = 0;
    unsigned short type = 0;
    char ticket[20] = "";
    unsigned short ticket_type = 0;
    char plate[12] = "";
    int currency_sum = 0;
    int coin_sum = 0;
    int currency_balance = 0;
    int coin_balance = 0;
    short site = 255;
    
    
    
    time_t event_time = 0;
    time_t rece_time = 0;
    
    event_payment(MYSQL *mysql);

    ~event_payment();
    
    int print_event_payment();
        
    int Insert_payment_event();
    
    int Select_payment_event_by_id(int index);
    
    int Delete_Payment_event();
    
    int Delete_All_Payment_Events();

            
};