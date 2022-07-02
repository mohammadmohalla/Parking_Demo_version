#include "Dashou.h"



class DashouParser
{

public:
    int id_warper = -1;
    struct ChargingStandard
    {
            int id;
            std::string name;
    };

    struct CameraSite
    {
            int site_address;
            int camera_id;
            std::string cameraIP;
    };

    Dashou dashou;

    std::string header = "";
    int length;
    int control;
    int function;
    int Setting_type;
    int tablet_Request_type;
    int direction;
    int serial;
    time_t datetime, enterTime, payapptime, exitTime;
    int site_type;
    int exit_address;
    int site_address;
    std::string site_status;
    int site_status_Tail;
    int ticket_type;
    int entry_exit_type;
    int Manual_Fee_Collection_Type;
    int chargeable_Fee;
    std::string ticket;
    std::string plate;
    std::string version;
    unsigned int cash_Received;
    int ticketSerial;

    int zone_serial;
    int totalFreeSpaces;
    
    // Settings
    int parameterType;
    int setting_Type;
    int sites_modified_count;
    bool season_to_hourly_swich;
    int oneCard_oneCar = 0;
    int same_EntryExit_group = 0;
    int same_EntryExit_site = 0;
    int same_EntryExit_filter = 0;
    int entryPresetLicensePlateNumber = 0;
    int exitFreeLetPass = 0;
    int hourlyParkingFullAccessDeny = 0;
    int monthlyParkingFullAccessDeny = 0;
    int id_PresetType_id = 0;
    int id_PresetSite_in_Site_Group = 0;
    int credentialMode = 0;
    std::string setting_siteType = "";
    std::string reserved = "";

    int balanceNotificationThreshold = 100;
    int expireForecastThreshold = 30;

    int Out_type = 0;

    std::string site_name = "";
    std::vector <CameraSite> cameraSiteList;
    std::vector <ChargingStandard> chargingStandardList;

    int request_address = 0;

    DashouParser();

    ~DashouParser();

    void parse(unsigned char* data);

    void parse2(unsigned char* data);

    time_t char_to_time_t(unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4, unsigned char data5, unsigned char data6);

    std::string Encoding_ASCII_GetString(unsigned char *data, int index, int count);
};
