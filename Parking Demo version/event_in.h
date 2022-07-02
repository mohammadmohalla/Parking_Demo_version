#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class event_in
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[28];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[28];
    my_bool       is_null[28];
    
    MYSQL_TIME    cht;
    MYSQL_TIME    crt;
    int socket = -1;

    long aid = 0;
    int gid = 0;
    short _operator = 0;
    int inSerial = 0;
    short inType = 0;
    char ticket[20] = "";
    short ticketType = 0;
    char plate[12] = "";
    int totalLots = 0;
    int monthlyLots = 0;
    int hourlyLots = 0;
    int freeTotalLots = 0;
    int freeMonthlyLots = 0;
    int freeHourlyLots = 0;
    short site = 0;
    char orderNum[20] = "";
    char photoID[64] = "";
    short isNotUp = 0;
    int lotsGroupId = 65535;
    int lotsGroupUsed = 0;
    int lotID = 0;
    short monthlyType = 255;
    
    
    
    time_t inTime = 0;
    time_t receTime = 0;
    time_t realIntime = 0;
    
    event_in(MYSQL *mysql);

    ~event_in();
           
    int print_event_in();
    
    int Insert_entry_event();
    
    int Select_entry_event_by_id(int index);
    
    int Delete_Entry_event();
    
    int Delete_All_Entry_Events();
            
};