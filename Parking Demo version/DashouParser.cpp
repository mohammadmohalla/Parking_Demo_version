#include "DashouParser.h"

time_t mktime_slow(struct tm *tm)
{
    static struct tm cache = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    static time_t time_cache = 0;
    static time_t (*mktime_real)(struct tm *tm) = NULL;
    time_t result;
    time_t hmsarg;

    /* Load real mktime once into a static */
    if (!mktime_real)
    {
        void *handle;

        /* To forgive this cast, please see man dlopen(3). */
        dlerror();
        handle = dlsym(RTLD_NEXT, "mktime");
        *(void **) (&mktime_real) = handle;

        if (!mktime_real)
        {
            fprintf(stderr, "loading mktime: %s\n", dlerror());
            exit(EXIT_FAILURE);
        }
    }

    /* the epoch time portion of the request */
    hmsarg = 3600 * tm->tm_hour
            +  60 * tm->tm_min
            +       tm->tm_sec;

    if ( cache.tm_mday    == tm->tm_mday
         && cache.tm_mon  == tm->tm_mon
         && cache.tm_year == tm->tm_year )
    {
        /* cached - just add h,m,s from request to midnight */
        result = time_cache + hmsarg;

        /* Obscure, but documented, return value: only this value in arg struct.         
         * 
         * BUG: dst switchover was computed by mktime_real() for time 00:00:00
         * of arg day. So this return value WILL be wrong for switchover days
         * after the switchover occurs.  There is no clean way to detect this
         * situation in stock glibc.  This bug will be reflected in unit test
         * until fixed.  See also github issues #1 and #2.
         */
        tm->tm_isdst  = cache.tm_isdst;
    }
    else
    {
        /* not cached - recompute midnight on requested day */
        cache.tm_mday = tm->tm_mday;
        cache.tm_mon  = tm->tm_mon;
        cache.tm_year = tm->tm_year;
        time_cache    = mktime_real(&cache);
        tm->tm_isdst  = cache.tm_isdst;

        result = (-1 == time_cache) ? -1 : time_cache + hmsarg;
    }

    return result;
}

DashouParser::DashouParser() : dashou()
{

}

DashouParser::~DashouParser()
{

}

void DashouParser::parse(unsigned char* data)
{
    header = Encoding_ASCII_GetString(data, 0, 2);
    length = 256 * data[3] + data[2];
    serial = 256 * data[5] + data[4];
    control = data[6];
    function = control & 31;
    direction = control & CONTROL_DIRECTION_UPLOAD;
    ticket = "";
    site_type = 0;
    site_address = 0;
    site_status = "";
    ticket_type = 0;
    entry_exit_type = 0;
    plate = "";
    ticketSerial = 0;
    version = "";
    switch (function)
    {
        case CONTROL_ENTRY_REQUEST_RESPONSE:
        {
            if (direction == CONTROL_DIRECTION_UPLOAD)
            {
                datetime = char_to_time_t(data[7], data[8], data[9], data[10], data[11], data[12]);
                entry_exit_type = data[13];
                ticket_type = data[14];
                ticket = Encoding_ASCII_GetString(data, 15, 19);
                plate = Encoding_ASCII_GetString(data, 34, 12);
                site_address = data[54];
                site_status = Encoding_ASCII_GetString(data, 55, 3);
                site_status_Tail = data[58];
            }
        }
        break;
        case CONTROL_EXIT_REQUEST_RESPONSE:
        {
            if (direction == CONTROL_DIRECTION_UPLOAD)
            {
                datetime = char_to_time_t(data[7], data[8], data[9], data[10], data[11], data[12]);
                Out_type = data[13];
                ticket_type = data[14];
                ticket = Encoding_ASCII_GetString(data, 15, 19);
                plate = Encoding_ASCII_GetString(data, 34, 12);
                site_address = data[90];
                site_status = Encoding_ASCII_GetString(data, 91, 3);
                site_status_Tail = data[94];
            }
        } 
        break;
        case CONTROL_TABLET_REQUEST_RESPONSE:
        {
            if (direction == CONTROL_DIRECTION_UPLOAD)
            {
                tablet_Request_type = data[7];
                switch(tablet_Request_type)
                {
                    case tablet_scans_ticket:
                    {
                        datetime = char_to_time_t(data[8], data[9], data[10], data[11], data[12], data[13]);
                        entry_exit_type = data[14];
                        ticket_type = data[15];
                        ticket = Encoding_ASCII_GetString(data, 16, 19);
                        plate = Encoding_ASCII_GetString(data, 35, 12);
                        request_address = data[47];
                        site_address = data[100];
                        site_status = Encoding_ASCII_GetString(data, 101, 3);
                        site_status_Tail = data[104];
                    }
                    break;
                    case tablet_input_license_plate_number:
                    {
                        datetime = char_to_time_t(data[8], data[9], data[10], data[11], data[12], data[13]);
                        entry_exit_type = data[14];
                        ticket_type = data[15];
                        ticket = Encoding_ASCII_GetString(data, 16, 19);
                        plate = Encoding_ASCII_GetString(data, 35, 12);
                        request_address = data[47];
                        site_address = data[100];
                        site_status = Encoding_ASCII_GetString(data, 101, 3);
                        site_status_Tail = data[104];
                    }
                    break;
                    case tablet_reads_card:
                    {
                        
                    }
                    break;
                    case tablet_reads_QR_code:
                    {
                    }
                    break;
                    case central_pay_system_tablet_payment_confirm:
                    {
                        datetime = char_to_time_t(data[8], data[9], data[10], data[11], data[12], data[13]);
                        entry_exit_type = data[14];
                        ticket_type = data[15];
                        ticket = Encoding_ASCII_GetString(data, 16, 19);
                        plate = Encoding_ASCII_GetString(data, 35, 12);
                        request_address = data[47];
                        Manual_Fee_Collection_Type = data[48];
                        chargeable_Fee = (dashou.get_TABLET_cost(data[49], data[50], data[51], data[52]));
                        cash_Received = (dashou.get_TABLET_PAID(data[53], data[54], data[55], data[56]));
                        site_address = data[100];
                        site_status = Encoding_ASCII_GetString(data, 101, 3);
                        site_status_Tail = data[104];
                    }
                    break;
                    case exit_pay_system_tablet_payment_confirm:
                    {
                        
                    }
                    break;
                    case tablet_switching_charge_type:
                    {
                        
                    }
                    break;
                    case table_confirms_prepaid_card_fee_deduction:
                    {
                        
                    }
                    break;
                    case parking_coupon_applied_on_tablet:
                    {
                        
                    }
                    break;
                    case special_let_pass:
                    {
                        
                    }
                    break;
                    case manual_open_gate:
                    {
                        
                    }
                    break;
                    case monthly_user_let_pass_as_hourly_user:
                    {
                        
                    }
                    break;
                    case close_gate:
                    {
                        
                    }
                    break;
                    case entry_preset_license_plate_number:
                    {
                        
                    }
                    break;
                    case exit_preset_license_plate_number:
                    {
                        
                    }
                    break;
                    default:
                    {

                    }
                    break;
                }
            }
        } 
        break;
        case CONTROL_INIT_REQUEST_RESPONSE:
        {
            char_to_time_t(data[7], data[8], data[9], data[10], data[11], data[12]);
            site_address = data[13];
            site_type = data[14];
            if (length > 32)
            {
                version = Encoding_ASCII_GetString(data, 15, 32);
            }
        }
        break;
        case CONTROL_HEARTBEAT:
        {
            datetime = char_to_time_t(data[7], data[8], data[9], data[10], data[11], data[12]);
            ticket = "";
            plate = "";
            site_address = data[45];
            site_status = Encoding_ASCII_GetString(data, 46, 3);
            site_type = data[49];
            site_status_Tail = data[49];
        }
        break;
        case CONTROL_PAYMENT_BOARD_STATUS:
        {
        }
        break;
        case CONTROL_ACK_FRAME:
        {
            Setting_type = data[7];
        }
        break;
        case CONTROL_Sys_PARAM_FRAME:
        {
            datetime = char_to_time_t(data[7], data[8], data[9], data[10], data[11], data[12]);
            parameterType = data[13];
            switch (parameterType)
            {
                case CONTROL_TYPE_SITE_SETTING:
                {
                    site_address			= data[15];
                    oneCard_oneCar			= data[16];
                    same_EntryExit_group		= data[17];
                    same_EntryExit_site                 = data[18] + data[19];
                    same_EntryExit_filter		= data[20];
                    entryPresetLicensePlateNumber	= data[21];
                    exitFreeLetPass			= data[22];
                    hourlyParkingFullAccessDeny         = data[23];
                    monthlyParkingFullAccessDeny	= data[24];
                    id_PresetType_id                    = data[25];
                    id_PresetSite_in_Site_Group         = data[26];
                    credentialMode			= data[27];
                    setting_siteType                    = dashou.to_String_X2(data[28]);
                    reserved                            = dashou.to_String_X2(data[29]) + dashou.to_String_X2(data[30]) + dashou.to_String_X2(data[31]);
                }
                break;
                case CONTROL_TYPE_BALANCE_NOTIFICATION:
                {
                    balanceNotificationThreshold = data[15];
                }
                break;
                case CONTROL_TYPE_EXPIRE_FORECAST:
                {
                    expireForecastThreshold = data[15];
                }
                break;
                case CONTROL_TYPE_CAMERA_SITE:
                {
                    int count = data[15];
                    for (int i = 0; i < count; i++)
                    {
                        CameraSite temp_camera_site;
                        temp_camera_site.camera_id = data[16 + 2 * i];
                        temp_camera_site.site_address = data[17 + 2 * i];
                        cameraSiteList.push_back(temp_camera_site);
                    }
                }
                break;
                case CONTROL_TYPE_NETWORK_PARAM:
                {
                }
                break;
                case CONTROL_TYPE_SITE_NAME:
                {
                    int site_count = data[15];
                    for (int i = 0; i < site_count; i++)
                    {
                        int address = data[16 + 34 * i];
                        int type = data[17 + 34 * i];
                        if (type != 0)
                        {
                            site_name = Encoding_ASCII_GetString(data, 18 + 34 * i, 32);	//site_name = Encoding_ASCII_GetString(data, 18 + 34 * i, 32);
                            break;
                        }
                    }
                }
                break;
                case CONTROL_TYPE_LED_DISPLAY:
                {
                }
                break;
                case CONTROL_TYPE_TICKET_HEADER:
                {
                }
                break;
                case CONTROL_TYPE_RECEIPT_FORMAT:
                {
                }
                break;
                case CONTROL_TYPE_CHARGE_RATE:
                {
                    site_address = data[15];
                    int rate_count = data[16];
                    for (int i = 0; i < rate_count; i++)
                    {
                        ChargingStandard temp_ChargingStandard;
                        temp_ChargingStandard.id = data[17 + 65 * i];
                        temp_ChargingStandard.name = Encoding_ASCII_GetString(data, 18 + 65 * i, 32);
                        chargingStandardList.push_back(temp_ChargingStandard);
                    }
                }
                break;
            }
        }
        break;
        default:
        {

        }
        break;
    }
};

void DashouParser::parse2(unsigned char* data)
{
    header = Encoding_ASCII_GetString(data, 0, 2);
    length = 256 * data[3] + data[2];
    serial = 256 * data[5] + data[4];
    control = data[10];
    function = control & 31;
    ticket = "";
    site_type = 0;
    site_address = 0;
    ticket_type = 0;
    plate = "";
    entry_exit_type = 0;
    Setting_type = 0;
    ticketSerial = 0;
    version = "";
    switch (function)
    {
        case 1:// Entry request
        {
            enterTime = char_to_time_t(data[11], data[12], data[13], data[14], data[15], data[16]);//new DateTime(data[11] + 2000, data[12], data[13], data[14], data[15], data[16]);
            ticket_type = data[14];
            ticketSerial = 256 * data[18] + data[17];
            ticket = Encoding_ASCII_GetString(data, 21, 16);
            plate = Encoding_ASCII_GetString(data, 40, 12);
        } break;
        case 2:// Exit request
        {
            exitTime = char_to_time_t(data[11], data[12], data[13], data[14], data[15], data[16]);//new DateTime(data[11] + 2000, data[12], data[13], data[14], data[15], data[16]);
            ticket_type = data[21];
            ticket = Encoding_ASCII_GetString(data, 22, 16);
            plate = Encoding_ASCII_GetString(data, 41, 12);
        } break;
        case 4:// Initialization Request
        {
            site_address = data[21];
            site_type = data[22];
            if (site_type != SITE_TYPE_TABLET_APP)
                version = Encoding_ASCII_GetString(data, 23, 32);
        } break;
        case 5:// Adjust time
        {
            datetime = char_to_time_t(data[11], data[12], data[13], data[14], data[15], data[16]);
        } 
        break;
        case 7:// Heartbeat Frame
        {
            ticket = "";
            plate = "";
            site_address = data[45];
            site_status = "";
        } 
        break;
        case 10:// Space Counting ~ Refresh Zones
        {
            datetime = char_to_time_t(data[11], data[12], data[13], data[14], data[15], data[16]);
            setting_Type = data[17] + 255 * data[18];
            zone_serial = data[19];
            site_address = data[20];
        } 
        break;
        case 29:// Settings
        {
            datetime = char_to_time_t(data[11], data[12], data[13], data[14], data[15], data[16]);
            Setting_type = 256 * data[18] + data[17];
        } 
        break;
        case 23:// ACK Frame
        {
            Setting_type = data[11];
        } 
        break;
        default:
        { } 
        break;
    }
}

time_t DashouParser::char_to_time_t(unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4, unsigned char data5, unsigned char data6)
{
    tm time_and_date;
    time_and_date.tm_year = data1 + 100;
    time_and_date.tm_mon = data2 - 1;
    time_and_date.tm_mday = data3;
    time_and_date.tm_hour = data4;
    time_and_date.tm_min = data5;
    time_and_date.tm_sec = data6;
    time_t datetime = mktime_slow(&time_and_date);
    if(std::difftime(datetime, Reference_date) < 0) return Reference_date;
    return datetime;
}

std::string DashouParser::Encoding_ASCII_GetString(unsigned char *data, int index, int count)
{
    std::string stream = "";
    for (int i = index; i < index + count; i++)
    {
        stream += data[i];
    }
    return stream;
}

