#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>

class Site_type
{
public:
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[25];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[25];
    my_bool       is_null[25];
    
    MYSQL_TIME    cht;
    MYSQL_TIME    crt;
    int socket = -1;

    short id = 0;
    int gid = 0;
    short _operator = 0;
    short type = 0;
    std::string site_Type;
    int address = 0;
    char site_Address[22] = "";
    int status = 0;
    std::string site_Status = "000000";

    char db_name[50] = "";
    int versionLength = 0;
    std::string version = "";
    std::string VersionASCIIHEX = "";
    bool Heartbeat;
    int localSerial;
    //
    // Settings
    short oneCard_oneCar = 0;
    short same_EntryExit_group = 255;
    short same_EntryExit_site = 0;
    int same_EntryExit_filter = 0;
    short entryPresetLicensePlateNumber = 0;
    short exitFreeLetPass = 0;
    short hourlyParkingFullAccessDeny = 0;
    short monthlyParkingFullAccessDeny = 0;
    short id_PresetType_id = 0; // charging Standard id
    short id_PresetSite_in_Site_Group = 255;
    short credentialMode = 1;
    short season_to_hourly_swich = 0;
    short credentialMode_app = 1;
    
    char cache_plate[12] = "";
    short cache_etype = 0;

    time_t createtime = 0;
    time_t cache_time = 0;
    std::string site_createtime = "";
    std::string site_cache_time = "";
    

    int balanceNotificationThreshold = 0;
    int expireForecastThreshold = 0;

    std::string cameraIP;
    std::string chargingStandard;
    std::string ticketFormat;
    std::string receiptFormat;
    
    Site_type(MYSQL *mysql);

    ~Site_type();
    
    int print_site();
        
    int Insert_Update_Site_type();
    
    int Select_Site_type_by_id(int id);
    
    int Select_Site_type_by_address(int address);
    
    int Delete_Site_type();
    
};