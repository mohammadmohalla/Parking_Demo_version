#include <iostream>
#include <time.h>
#include <string.h>
#include <sstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>


class Zone
{
public:
    
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[21];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[21];
    my_bool       is_null[21];
    
    MYSQL_TIME    crt;
    
    int aid;
    int gid;
    
    short serial;
    std::string Serial = "";
    char name[50] = "";
    short asofficial;
    
    short cover_pgm_id = -1;
    short align_pgm_id = -1;
    
    int vacantSpacesHourly = -1;// free_hourly_lots
    //std::string VacantSpacesHourly;
    
    int vacantSpacesSeason = -1;//free_monthly_lots
    //std::string VacantSpacesSeason;
    
    int vacantSpaces;//free_total_lots
    //std::string VacantSpaces;
    
    int totalSpaces;//total_lots
    //std::string TotalSpaces;
    
    int totalSpacesHourly;//hourly_lots
    //std::string TotalSpacesHourly;
    
    int totalSpacesSeason;//monthly_lots
    //std::string TotalSpacesSeason;
    
    char insites_list[255] = "";
    char outsites_list[50] = "";
    
    int parking_Guidance_Total_Space;//pgm_total_lots
    //std::string Parking_Guidance_Total_Space;

    int parking_Guidance_Available_Space;//pgm_free_total_lots
    //std::string Parking_Guidance_Available_Space;
    
    short flag = 0;
    
    short _operator;
    
    time_t createtime = 0;

    int entry_address[100] = {0};
    int exit_address[100] = {0};
    ///std::string entry_name = "";        
    //std::string exit_name = "";
    //bool status = false;

    Zone(MYSQL *_mysql);

    ~Zone();
    
    int print_Zone();
    
    int select_Zone(int _serial);
    
    int insert_update_Zone();
    
    int delete_Zone();
    
    std::string get_Serial();

    std::string get_TotalSpaces();

    std::string get_TotalSpacesSeason();

    std::string get_TotalSpacesHourly();

    std::string get_VacantSpaces();

    std::string get_VacantSpacesSeason();

    std::string get_VacantSpacesHourly();

    void entryHourly();

    void exitHourly();

    void entrySeason();

    void exitSeason();

    std::string to_String_X2(int v);

    std::string to_String_X4(int v);
};


