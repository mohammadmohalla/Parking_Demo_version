#include "Logger.h"

std::string add_version(std::string ver, int type)
{
    std::string result = "";
    if(type == SITE_TYPE_ENTRY_BOARD)
        return ver;
    else if(type == SITE_TYPE_EXIT_BOARD)
    {
        for(int i = 0; i < 28; i++)
        {
            result += ver[i];
        }
        return result;
    }
    else if(type == SITE_TYPE_TABLET_APP)
    {
        return result;
    }
    return result;
}

std::string correct_ticket(char *ver)
{
    std::string result = "f";
    if(ver[0] == 0)
    {
        return "";
    }
    else
    {
        for(int j = 0; j < 16 ; j++)
        {
            if(ver[j] == 0)
                break;
            result += ver[j];
        }
    }   
    return ver;
}

std::string correct_plate(char *ver, int plate_match)
{
    std::string result = "";
    if(ver[0] == 0)
    {
        return "";
    }
    else
    {
        for(int j = 0; j < plate_match ; j++)
        {
            if(ver[j] == 0)
                break;
            result += ver[j];
        }
    }   
    return result;
}

std::string Logger::Print_time(time_t now)
{
    if(now == 0) return "000000000000";
    tm *my_time = localtime(&now);
    std::string date = "";
    date += dashou.to_String_00(my_time->tm_year - 100);
    date += "-";
    date += dashou.to_String_00(my_time->tm_mon + 1);
    date += "-";
    date += dashou.to_String_00(my_time->tm_mday);
    date += " ";
    date += dashou.to_String_00(my_time->tm_hour);
    date += ":";
    date += dashou.to_String_00(my_time->tm_min);
    date += ":";
    date += dashou.to_String_00(my_time->tm_sec);
    return date;

}

std::string Logger::Proof_Print_time(time_t now)
{
    if(now == 0) return "000000000000";
    tm *my_time = localtime(&now);
    std::string date = "";
    date += dashou.to_String_00(my_time->tm_year + 1900);
    date += "-";
    date += dashou.to_String_00(my_time->tm_mon + 1);
    date += "-";
    date += dashou.to_String_00(my_time->tm_mday);
    date += " ";
    date += dashou.to_String_00(my_time->tm_hour);
    date += ":";
    date += dashou.to_String_00(my_time->tm_min);
    date += ":";
    date += dashou.to_String_00(my_time->tm_sec);
    return date;

}

int Logger::initilize_UDP_Logger(MYSQL *_mysql, const char* ipAddress)
{
    try
    {
        mysql = _mysql;
        log_udp_Receiver.sin_family = AF_INET;
        log_udp_Receiver.sin_port = htons(port_number);
        log_udp_Receiver.sin_addr.s_addr = inet_addr("255.255.255.255");

        log_udp_Sender.sin_family = AF_INET;
        log_udp_Sender.sin_port = htons(0);
        log_udp_Sender.sin_addr.s_addr = inet_addr(ipAddress);   
        return 0;
    }
    catch(...)
    {
        fprintf(stderr, "Unknown error during initilize UDP Logger..!\n");
        return -108;
    }
}

int  Logger::create_UDP_Logger_Server()
{
    try
    {
        UDP_Logger_socket = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }
    catch(...)
    {
        fprintf(stderr, "Error in setting Broadcast UDP Log Socket\n");
        close(UDP_Logger_socket);
        return -109;
    }
    if (UDP_Logger_socket < 0)
    {
            fprintf(stderr, "Error in setting Broadcast UDP Log Socket\n");
            close(UDP_Logger_socket);
            return -109;
    }    
    try
    {
        if (bind(UDP_Logger_socket, (sockaddr*)&log_udp_Sender, sizeof(log_udp_Sender)) < 0)
        {
            fprintf(stderr, "Error in BINDING PORT (%d) for UDP Log.\n", port_number);
            close(UDP_Logger_socket);
            return -110;
        }
    }
    catch(...)
    {
        fprintf(stderr, "Error in BINDING PORT (%d) for UDP Log.\n", port_number);
        close(UDP_Logger_socket);
        return -110;
    }
    int Broadcast = 1;
    int setsockoption = 0;
    try
    {
        setsockoption = setsockopt(UDP_Logger_socket, SOL_SOCKET, SO_BROADCAST, &Broadcast, sizeof(int));
    }
    catch(...)
    {
        fprintf(stderr, "Error in setsockopt UDP Log Socket..!\n");
        return -111;
    }
    if(setsockoption == 0)
    {
        return 0;
    }
    else
    {
        fprintf(stderr, "Error in setsockopt UDP Log Socket..!\n");
        return -111;
    }
    return 0;
}

std::string Logger::HEARTBEAT_messege_Builder(Site_type site, int accounts_sum)
{
    std::string report = "";
    report += "OL Site " + std::to_string(site.address) + ","; 
    report += "sitetype " + std::to_string(site.type) + site.site_Status + ",";
    report += "RPayLotsOccupied 0,Garage 1,";
    report += "city 3075,";
    report += "AccountSum " + std::to_string(accounts_sum);
    report += udp_Logger_endl;
    report += "LostHeart.GarageSerial=1";
    report += udp_Logger_endl;
    return report;
}

std::string Logger::ACK_webhost_messege_Builder(DashouParser *parser)
{
    std::string report = "";
    report += "receive offline confirm frame of type '" + std::to_string(parser->Setting_type) + "',frame ";
    report += std::to_string(parser->serial) + ".";
    report += udp_Logger_endl;
    return report;
    //receive offline confirm frame of type '4',frame 2636.
}

std::string Logger::ACK_sites_messege_Builder(Site_type site,DashouParser *parser)
{
    std::string report = "";
    report += "receive site " + std::to_string(site.address) + " confirm frame of type '" + std::to_string(parser->Setting_type);
    report += "'.frame " + std::to_string(parser->serial);
    report += udp_Logger_endl;
    return report;
    //receive site 3 confirm frame of type '29'.frame 1619
}

std::string Logger::site_connecting_messege_Builder(Site_type site)
{
    std::string report = "";
    report += udp_Logger_endl;
    report += "=========== (Server detection IP: " + dashou.to_String_00(site.address) + " is online) =====";
    report += Print_time(time(0)) + "=========";
    report += udp_Logger_endl;
    return report;
}

std::string Logger::site_disconnecting_messege_Builder(Site_type site)
{
    std::string report = "";
    report += udp_Logger_endl;
    report += "=========== (Server detection IP: " + dashou.to_String_00(site.address) + " offline) =====";
    report += Print_time(time(0)) + "=========";
    report += udp_Logger_endl;
    return report;
}

std::string Logger::zone_info_messege_Builder(std::vector<Zone> Zones, int zone_log_index)
{
    std::string report = "";
    report += "Zone " + std::to_string(zone_log_index) + ", ";//Partition 3, 
    report += "set total parking space: " + std::to_string(Zones[zone_log_index].totalSpaces) + ", ";
    //set total parking space: 32767, 
    report += "monthly rental total parking space: " + std::to_string(Zones[zone_log_index].totalSpacesSeason) + ", ";
    //monthly rental total parking space: 32767, 
    report += "hourly total parking space: " + std::to_string(Zones[zone_log_index].totalSpacesHourly) + ", ";
    //hourly total parking space: 32767, 
    report += "remaining total parking space: " + std::to_string(Zones[zone_log_index].vacantSpaces) + ", ";
    //remaining total parking space: 0000, 
    report += "remaining monthly rental parking space: " + std::to_string(Zones[zone_log_index].vacantSpacesSeason) + ", ";
    //remaining monthly rental parking space: 32767, 
    report += "remaining hourly rental parking space: " + std::to_string(Zones[zone_log_index].vacantSpacesHourly) + ", ";
    //remaining hourly rental parking space: 32767,
    report += udp_Logger_endl;
    return report;
}

std::string Logger::INITIAL_messege_Builder(Site_type site, DashouParser *parser)
{
    std::string report = "";
    if(site.type == SITE_TYPE_TABLET_APP)
    {
        report += "site " + std::to_string(site.id) + " had init event,version ?";
    }
    else
    {
        report += "site " + std::to_string(site.id) + " had init event,version " + add_version(site.version, site.type);
    }
    report += ",frame index:" + std::to_string(parser->serial) + ",origin siteType:" + std::to_string(site.type);
    report += udp_Logger_endl;
    report += "siteType:" + std::to_string(site.type);
    report += udp_Logger_endl;
    report += "offline send fifo";
    report += udp_Logger_endl;
    return report;
}

std::string Logger::CONTROL_TYPE_Header_messege_Builder(DashouParser parser)
{
    std::string report = "";
    report += "Offline receive SystemParam frame of type '" + std::to_string(parser.function) + "',frindex ";
    report += ",frame index:" + std::to_string(parser.serial);
    report += udp_Logger_endl;
    report += "offline send fifo";
    report += udp_Logger_endl;
    return report;
    //Offline receive SystemParam frame of type '3',frindex 9
    //offline send fifo
}

std::string Logger::CONTROL_TYPE_messege_Builder(int CONTROL_TYPE, int serial, std::vector<Camera_type> All_Cameras,int site_id, std::vector<Site_type> sites)
{
    std::string report = "";
    switch(CONTROL_TYPE)
    {
        case CONTROL_TYPE_SITE_SETTING:
        {
            report += "Site " + std::to_string(sites[site_id].address) + ", initial setting ";
            report += std::to_string(CONTROL_TYPE_SITE_SETTING);
            report += ", frame number " + std::to_string(serial);
            report += udp_Logger_endl;
            report += "set to site " + std::to_string(sites[site_id].address) + ",OnlyOneCar ";
            report += std::to_string(sites[site_id].oneCard_oneCar) + ",ZeroAutoPass " 
                   +  std::to_string(sites[site_id].exitFreeLetPass);
            report += udp_Logger_endl;
            //Site 4, initial setting 1, frame number 1621
            //set to site 4 ,OnlyOneCar 0,ZeroAutoPass 0
        }
        break;
        case CONTROL_TYPE_BALANCE_NOTIFICATION:
        {
            report += "Site " + std::to_string(sites[site_id].address) + ", initial setting ";
            report += std::to_string(CONTROL_TYPE_BALANCE_NOTIFICATION);
            report += ", frame number " + std::to_string(serial);
            report += udp_Logger_endl;
            //Site 3, initial setting 14, frame number 1622
        }
        break;
        case CONTROL_TYPE_EXPIRE_FORECAST:
        {
            report += "Site " + std::to_string(sites[site_id].address) + ", initial setting ";
            report += std::to_string(CONTROL_TYPE_EXPIRE_FORECAST);
            report += ", frame number " + std::to_string(serial);
            report += udp_Logger_endl;
            //Site 3, initial setting 15, frame number 1623
        }
        break;
        case CONTROL_TYPE_CAMERA_SITE:
        {
            report += "Site " + std::to_string(sites[site_id].address) + ", initial setting ";
            report += std::to_string(CONTROL_TYPE_CAMERA_SITE);
            report += ", frame number " + std::to_string(serial);
            report += udp_Logger_endl;
            for(int i = 0; i < All_Cameras.size(); i++)
            {
                report += "camera ip " + std::to_string(All_Cameras[i].cam_address);
                char *str = All_Cameras[i].site_Addresses;
                char * pch;
                pch = strtok (str,",");
                while (pch != NULL)
                {
                    report += ",site " + std::to_string(atoi(pch));
                    pch = strtok (NULL,",");
                }
                report += udp_Logger_endl;
            }
            //Site 3, initial setting 20, frame number 1624
            //camera ip 146,site 3
            //camera ip 168,site 4
        }
        break;
        case CONTROL_TYPE_NETWORK_PARAM:
        {
            report += "Site " + std::to_string(sites[site_id].address) + ", initial setting ";
            report += std::to_string(CONTROL_TYPE_NETWORK_PARAM);
            report += ", frame number " + std::to_string(serial);
            report += udp_Logger_endl;
            //Site 3, initial setting 26, frame number 1625
        }
        break;
        case CONTROL_TYPE_SITE_NAME:
        {
            report += "Site " + std::to_string(sites[site_id].address) + ", initial setting ";
            report += std::to_string(CONTROL_TYPE_SITE_NAME);
            report += ", frame number " + std::to_string(serial);
            report += udp_Logger_endl;
            for(int i = 1; i < sites.size(); i++)
            {
                if(sites[i].id != -1)
                {
                    report += "Site " + std::to_string(sites[i].address) + ", type 0x" 
                       + dashou.to_String_X2(sites[i].type) 
                       + ", name " + sites[i].db_name;
                    report += udp_Logger_endl;
                }
            }
            //Site 3, initial setting 27, frame number 1626
            //Site 3, type 0x04, name Exit
            //Site 4, type 0x03, name Entrance
            //Site 16, type 0x06, name APP
        }
        break;
        case CONTROL_TYPE_LED_DISPLAY:
        {
            report += "Site " + std::to_string(sites[site_id].address) + ", initial setting ";
            report += std::to_string(CONTROL_TYPE_LED_DISPLAY);
            report += ", frame number " + std::to_string(serial);
            report += udp_Logger_endl;
            //Site 3, initial setting 28, frame number 1627
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
            
        }
        break;
        default :
        {
            
        }
        break;
    }
    return report;
}

std::string Logger::SystemParam_messege_Builder(int SystemParam_type, int setting_serial, int serial, int recv_type, Site_type site, Camera_type Camera_new_config)
{
    std::string report = "";
    report += "Offline receive SystemParam frame of type ";
    report += "'" + std::to_string(SystemParam_type) + "',";
    report += "frindex " + std::to_string(setting_serial);
    report += udp_Logger_endl;
    switch (SystemParam_type)
    {
        case 3:// one proof on car
        {
            // info already written           
        }
        break;
        case 10:// confirm plate
        {
            // info not written           
        }
        break;
        case 11:// auto open Free
        {
            //Site 3 set AutoPass 1,NotMatch-AutoPass 0
            report += "site " + std::to_string(site.address);
            report += "set AutoPass " + std::to_string(site.exitFreeLetPass % 2);
            report += ",NotMatch-AutoPass " + std::to_string(site.exitFreeLetPass / 128);
            report += udp_Logger_endl;
        }
        break;
        case 13: // Full no entry
        {
            //site 4 set HourlyFullClose 0,MonthlyFullClose 0
            report += "site " + std::to_string(site.address);
            report += "set HourlyFullClose " + std::to_string(site.hourlyParkingFullAccessDeny);
            report += ",MonthlyFullClose " + std::to_string(site.monthlyParkingFullAccessDeny);
            report += udp_Logger_endl;
        }
        break;
        case 14: // balance Notification Threshold
        {
            // info not written    
        }
        break;
        case 15: // expire Forecast Threshold
        {
            // info not written    
        }
        break;
        case 17:
        {
            report += "site " + std::to_string(site.address);
            report += "set PresetChargeTypeID " + std::to_string(site.id_PresetType_id);
            report += udp_Logger_endl;
        }
        break;
        case 20: // Camera Site
        {
            char *str = Camera_new_config.site_Addresses;
            char *pch;
            pch = strtok (str,",");
            while (pch != NULL)
            {
                report += "Camera IP " + std::to_string(Camera_new_config.cam_address);
                report += " binding site " + std::to_string(atoi(pch)) + "!";
                report += udp_Logger_endl;
                pch = strtok (NULL,",");
            }
            //Offline receive SystemParam frame of type '20',frindex 7
            //Camera IP 146 binding site 16!
            //Camera IP 146 binding site 3!
        }
        break;
        case 50: //
        {
            //No.0:SiteAddr = 4,set TicketInOutMod: 1,MonthlyToHourlyEnable 0
            report += "No.0:SiteAddr =  " + std::to_string(site.address);
            report += ",set TicketInOutMod: " + std::to_string(site.credentialMode);
            report += ",MonthlyToHourlyEnable " + std::to_string(site.season_to_hourly_swich);
            report += udp_Logger_endl;
        }
        break;
        default:
        {
            
        }
        break;
    }
    report += "offline send fifo";
    report += udp_Logger_endl;
    return report;
    //Offline receive SystemParam frame of type '21',frindex 12
    //offline send fifo
    //receive offline confirm frame of type '4',frame 32436.

}

std::string Logger::proof_messege_Builder(accountInfo current_accountInfo, account_state current_account_state, Site_type site, DashouParser *parser, int plate_match, int control_type)
{
    std::string report = "";
    switch (control_type)
    {
        case CONTROL_ENTRY_REQUEST_RESPONSE:
        {
            report += "receive In-Request,site " + std::to_string(site.address) + ",type " + std::to_string(current_account_state.present_type);
            report += ",frame " + std::to_string(parser->serial) + ",LP:" + correct_plate(current_accountInfo.plate, plate_match);
            report += ",Ticket " + correct_ticket(current_accountInfo.tickets);
            report += ",OperatorCode 1,sitetype 0x8" + std::to_string(site.type) + "ffffff";
            report += udp_Logger_endl;
            switch(current_accountInfo.parking_type)
            {
                case hourly_parker:
                {
                    report += "Can not find the Account!";
                    report += udp_Logger_endl;
                    report += "Hourly Car In!,request type " + std::to_string(parser->entry_exit_type);
                    report += ",Response Type " + std::to_string(current_account_state.present_type);
                    report += ",TicketNumber:" + correct_ticket(current_account_state.ticket) + ",LPNumber:" + correct_plate(current_account_state.plate, plate_match); 
                    report += udp_Logger_endl;
                }
                break;
                case hourly_based_monthly_parker:
                {
                    report += "LPNumberMatchLevel:1";
                    report += udp_Logger_endl;
                    report += "LPNumber " + correct_plate(current_account_state.plate, plate_match) + " Match in Fo_AccountDatasLib[" + std::to_string(current_account_state.aid) + "],";
                    report += " CarlibLP " + correct_plate(current_account_state.plate, plate_match) + ",Account type " + std::to_string(current_account_state.parking_type);
                    report += ",parking type " + std::to_string(current_account_state.present_type) + ",MatchChars " + std::to_string(plate_match);
                    report += udp_Logger_endl;
                    report += "Enable MonthlyTypes!,MonthlyTypeSerial " + std::to_string(current_accountInfo.monthly_type) + ",";
                    report += "VIP Flag " + std::to_string(current_accountInfo.account_state);
                    report += ",AccessGroup " + std::to_string(current_accountInfo.access_group);
                    report += ",TimeGroup " + std::to_string(current_accountInfo.time_group);
                    report += ",InnerGarageGroup " + std::to_string(current_accountInfo.inner_group);
                    report += ",PrepaidChargeTypeID " + std::to_string(current_accountInfo.prepaid_charge_rule); 
                    report += udp_Logger_endl;
                    report += "Monthly Car In! ,PrepaidBalance " + std::to_string(current_account_state.prepaid_balance);
                    report += ",TicketNumber:" + correct_ticket(current_account_state.ticket) + ",LPNumber:" + correct_plate(current_account_state.plate, plate_match); 
                    report += udp_Logger_endl;
                }
                break;
                default:
                {
                    report += "proof account type unknown (200)*(.)  (300)*(!)";   
                    report += udp_Logger_endl;
                }
                break;
            }
            report += "In type " + std::to_string(parser->entry_exit_type);
            report += ",LotsGroup " + std::to_string(current_accountInfo.lots_group);
            report += ",occupied " + std::to_string(0);//proof.Parking_Space_Current_Occupied_Space_Number
            report += ",In time: " + Proof_Print_time(parser->datetime);
            report += ",LP " + correct_plate(current_account_state.plate, plate_match);
            report += ",Ticket " + correct_ticket(current_account_state.ticket);
            report += ",SiteAddr " + std::to_string(site.address);
            report += udp_Logger_endl;
        }
        break;
        case CONTROL_EXIT_REQUEST_RESPONSE:
        {
            report += "receive Out-Request,site " + std::to_string(site.address) + ",type " + std::to_string(parser->entry_exit_type);
            report += ",frame " + std::to_string(parser->serial) + ",LP:" + correct_plate(current_account_state.plate, plate_match);
            report += ",Ticket " + correct_ticket(current_account_state.ticket);
            report += ",CreditUsed " + std::to_string(0);//proof.Credit_Value_Total
            report += ",OperatorCode 1,sitetype 0x8" + std::to_string(site.type) + "ffffff";
            report += udp_Logger_endl;
            switch(current_account_state.parking_type)
            {
                case hourly_parker:
                {
                    if(current_account_state.present_type == plate_hourly)
                    {
                        report += "LPNumber " + correct_plate(current_account_state.plate, plate_match) + " Match in Fo_AccountDatasLib[" + std::to_string(current_account_state.aid) + "],";
                        report += " CarlibLP " + correct_plate(current_account_state.plate, plate_match) + ",Account type " + std::to_string(current_account_state.parking_type);
                        report += ",parking type " + std::to_string(current_account_state.present_type) + ",MatchChars " + std::to_string(plate_match);
                        report += udp_Logger_endl;
                    }
                    report += "Car want Out!,TicketNumber:" + correct_ticket(current_account_state.ticket) + ",LPNumber:" + correct_plate(current_account_state.plate, plate_match);
                    report += ",type " + std::to_string(parser->entry_exit_type);
                    report += ",PrepaidBalance " + std::to_string(current_account_state.prepaid_balance);
                    report += ",parking time " + std::to_string(std::difftime(current_account_state.pay_time, current_account_state.intime));
                    report += udp_Logger_endl;
                    report += ">>>>Final ChargeSum = " + std::to_string(0);
                    report += ",AlreadyPaid " + std::to_string(current_account_state.paid_sum);
                    report += ",CouponSum: " + std::to_string(0);
                    report += ",TimeCouponDuration! " + std::to_string(0);
                    report += ",ShouldPaySum " + std::to_string(current_account_state.limit_sum);
                    Site_type entry_site(mysql);
                    entry_site.Select_Site_type_by_id(current_account_state.insite);
                    report += ",chargeType " + std::to_string(entry_site.id_PresetType_id);
                    report += ",ParkTime " + std::to_string(std::difftime(current_account_state.pay_time, current_account_state.intime));
                    report += ",loop " + std::to_string(5);
                    report += udp_Logger_endl;
                    report += ",TicketNumber:" + correct_ticket(current_account_state.ticket) + ",LPNumber:" + correct_plate(current_account_state.plate, plate_match); 
                    report += udp_Logger_endl;
                    report += "Charge event shouldpay " + std::to_string(current_account_state.limit_sum);
                    report += ",Actualpay " + std::to_string(current_account_state.paid_sum);
                    report += ",parktime " + std::to_string(std::difftime(current_account_state.pay_time, current_account_state.intime));
                    report += ",charge type " + std::to_string(current_account_state.charge_type);
                    report += ",SiteAddr " + std::to_string(site.address);
                    report += udp_Logger_endl;
                }
                break;
                case hourly_based_monthly_parker:
                {
                    report += "LPNumber " + correct_plate(current_account_state.plate, plate_match) + " Match in Fo_AccountDatasLib[" + std::to_string(current_account_state.aid) + "],";
                    report += " CarlibLP " + correct_plate(current_account_state.plate, plate_match) + ",Account type " + std::to_string(current_account_state.parking_type);
                    report += ",parking type " + std::to_string(current_account_state.present_type) + ",MatchChars " + std::to_string(plate_match);
                    report += udp_Logger_endl;
                    report += "Car want Out!,TicketNumber:" + correct_ticket(current_account_state.ticket) + ",LPNumber:" + correct_plate(current_account_state.plate, plate_match);
                    report += ",type " + std::to_string(current_account_state.present_type);
                    report += ",PrepaidBalance " + std::to_string(current_account_state.prepaid_balance);
                    report += ",parking time " + std::to_string(std::difftime(current_account_state.pay_time, current_account_state.intime));
                    report += udp_Logger_endl;
                }
                break;
                default:
                {
                    report += "proof account type unknown (200)*(.)  (300)*(!)";   
                    report += udp_Logger_endl;
                }
                break;
            }
            report += "Out time: " + Proof_Print_time(current_account_state.outtime);
            report += "Match InTime: " + Proof_Print_time(current_account_state.intime) + ")";
            report += ",out type " + Proof_Print_time(current_account_state.present_type);
            report += ",SiteAddr " + std::to_string(site.address);
            report += ",parktime " + std::to_string(std::difftime(current_account_state.pay_time, current_account_state.intime));
            report += ",Alreadypay " + std::to_string(current_account_state.paid_sum);
            report += ",LotsGroup " + std::to_string(current_accountInfo.lots_group);//proof.Parking_Space_Group_Number
            report += ",Occupied " + std::to_string(0);//proof.Parking_Space_Current_Occupied_Space_Number
            report += udp_Logger_endl;
            report += "out rps type " + std::to_string(current_account_state.present_type);
            report += ",should pay " + std::to_string(current_account_state.limit_sum);
            report += ",already pay " + std::to_string(current_account_state.paid_sum);
            report += ",TP " + correct_ticket(current_account_state.ticket);
            report += ",LP " + correct_plate(current_account_state.plate, plate_match);
            report += ",site " + std::to_string(site.address);
            report += ",CreditUsed " + std::to_string(0);//proof.Credit_Value_Total
            report += udp_Logger_endl;
        }
        break;
        case CONTROL_TABLET_REQUEST_RESPONSE:
        {
            report += "receive APP-Request,site " + std::to_string(site.address) + ",type " + std::to_string(parser->tablet_Request_type);
            report += ",frame " + std::to_string(parser->serial) + ",LP:" + correct_plate(current_account_state.plate, plate_match);
            report += ",Ticket " + correct_ticket(current_account_state.ticket);
            report += "CouponNum: " + std::to_string(0);//proof.Coupon_Value
            report += udp_Logger_endl;
            switch (parser->tablet_Request_type)
            {
                case tablet_scans_ticket:
                {
                    report += "APP receive  request ";
                    report += ",tablet request type " + parser->tablet_Request_type;
                    report += ",access request type " + current_account_state.present_type;
                    report += ",Ticket " + correct_ticket(current_account_state.ticket);
                    report += ",LP " + correct_plate(current_account_state.plate, plate_match);
                    report += ",request address " + std::to_string(site.address);
                    Site_type entry_site(mysql);
                    entry_site.Select_Site_type_by_id(current_account_state.insite);
                    report += ",chargeType " + std::to_string(entry_site.id_PresetType_id);
                    report += ",receivable " + std::to_string(current_account_state.limit_sum);
                    report += ",actual receipt 0";                                  //must include a value
                    report += ",credit deduction 0";                                //must include a value
                    report += ",coupon Num 0";                                      //must include a value
                    report += ",total face value of parking coupons 0";             //must include a value
                    report += ",the total face value of the parking ticket is 0";   //must include a value
                    report += ",the job number is 1";                               //must include a value
                    report += ",the electronic payment: ";                          //must include a value
                    report += ",amount 0";                                          //must include a value
                    report += ",type 0";                                            //must include a value
                    report += ",voucher ";                                          //must include a value
                    report += ",balance " + std::to_string(current_account_state.prepaid_balance);
                    report += ",tablet address " + std::to_string(site.address);
                    report += ",tablet status " + std::to_string(site.type) + site.site_Status;
                    report += udp_Logger_endl;
                    report += "APP input car number!";
                    report += ",TicketNumber:" + correct_ticket(current_account_state.ticket);
                    report += ",LPNumber:" + correct_plate(current_account_state.plate, plate_match);
                    report += ",type " + current_account_state.parking_type;
                    report += udp_Logger_endl;
                    report += ">>>>Final ChargeSum = " + std::to_string(current_account_state.paid_sum);
                    report += ",AlreadyPaid " + std::to_string(current_account_state.paid_sum);
                    report += ",CouponSum: " + std::to_string(0);//proof.Coupon_Value
                    report += ",TimeCouponDuration! " + std::to_string(0);//proof.Coupon_Value
                    report += ",ShouldPaySum " + std::to_string(current_account_state.limit_sum);
                    report += ",chargeType " + std::to_string(entry_site.id_PresetType_id);
                    report += ",ParkTime " + std::to_string(std::difftime(current_account_state.pay_time, current_account_state.intime));
                    report += ",loop 10";                                           //must include a value
                    report += udp_Logger_endl;
                    report += "Exit offer event!";
                    report += udp_Logger_endl;
                }
                break;
                case tablet_input_license_plate_number:
                {
                    report += "APP receive  request ";
                    report += ",tablet request type " + parser->tablet_Request_type;
                    report += ",access request type " + current_account_state.present_type;
                    report += ",Ticket " + correct_ticket(current_account_state.ticket);
                    report += ",LP " + correct_plate(current_account_state.plate, plate_match);
                    report += ",request address " + std::to_string(site.address);
                    Site_type entry_site(mysql);
                    entry_site.Select_Site_type_by_id(current_account_state.insite);
                    report += ",chargeType " + std::to_string(entry_site.id_PresetType_id);
                    report += ",receivable " + std::to_string(current_account_state.limit_sum);
                    report += ",actual receipt 0";                                  //must include a value
                    report += ",credit deduction 0";                                //must include a value
                    report += ",coupon Num 0";                                      //must include a value
                    report += ",total face value of parking coupons 0";             //must include a value
                    report += ",the total face value of the parking ticket is 0";   //must include a value
                    report += ",the job number is 1";                               //must include a value
                    report += ",the electronic payment: ";                          //must include a value
                    report += ",amount 0";                                          //must include a value
                    report += ",type 0";                                            //must include a value
                    report += ",voucher ";                                          //must include a value
                    report += ",balance " + std::to_string(current_account_state.prepaid_balance);
                    report += ",tablet address " + std::to_string(site.address);
                    report += ",tablet status " + std::to_string(site.type) + site.site_Status;
                    report += udp_Logger_endl;                        
                    report += "LPNumber " + correct_plate(current_account_state.plate, plate_match);
                    report += "Match in Fo_AccountDatasLib[" + std::to_string(current_account_state.aid) + "], ";
                    report += "CarlibLP " + correct_plate(current_account_state.plate, plate_match);
                    report += ",Account type " + std::to_string(current_account_state.parking_type);
                    report += ",parking type " + std::to_string(current_account_state.present_type);
                    report += ",MatchChars " + std::to_string(plate_match);                               
                    report += udp_Logger_endl;
                    report += "APP input car number!";
                    report += ",TicketNumber:" + correct_ticket(current_account_state.ticket);
                    report += ",LPNumber:" + correct_plate(current_account_state.plate, plate_match);
                    report += ",type " + current_account_state.parking_type;
                    report += udp_Logger_endl;
                    report += ">>>>Final ChargeSum = " + std::to_string(current_account_state.paid_sum);
                    report += ",AlreadyPaid " + std::to_string(current_account_state.paid_sum);
                    report += ",CouponSum: " + std::to_string(0);//proof.Coupon_Value
                    report += ",TimeCouponDuration! " + std::to_string(0);//proof.Coupon_Value
                    report += ",ShouldPaySum " + std::to_string(current_account_state.limit_sum);
                    report += ",chargeType " + std::to_string(entry_site.id_PresetType_id);
                    report += ",ParkTime " + std::to_string(std::difftime(current_account_state.pay_time, current_account_state.intime));
                    report += ",loop 10";                                           //must include a value
                    report += udp_Logger_endl;
                    report += "Exit offer event!";
                    report += udp_Logger_endl;
                }
                break;
                case central_pay_system_tablet_payment_confirm:
                {
                    report += "APP receive  request ";
                    report += ",tablet request type " + parser->tablet_Request_type;
                    report += ",access request type " + current_account_state.present_type;
                    report += ",Ticket " + correct_ticket(current_account_state.ticket);
                    report += ",LP " + correct_plate(current_account_state.plate, plate_match);
                    report += ",request address " + std::to_string(site.address);
                    Site_type entry_site(mysql);
                    entry_site.Select_Site_type_by_id(current_account_state.insite);
                    report += ",chargeType " + std::to_string(entry_site.id_PresetType_id);
                    report += ",receivable " + std::to_string(current_account_state.limit_sum);
                    report += ",actual receipt 0";                                  //must include a value
                    report += ",credit deduction 0";                                //must include a value
                    report += ",coupon Num 0";                                      //must include a value
                    report += ",total face value of parking coupons 0";             //must include a value
                    report += ",the total face value of the parking ticket is 0";   //must include a value
                    report += ",the job number is 1";                               //must include a value
                    report += ",the electronic payment: ";                          //must include a value
                    report += ",amount 0";                                          //must include a value
                    report += ",type 0";                                            //must include a value
                    report += ",voucher ";                                          //must include a value
                    report += ",balance " + std::to_string(current_account_state.prepaid_balance);
                    report += ",tablet address " + std::to_string(site.address);
                    report += ",tablet status " + std::to_string(site.type) + site.site_Status;
                    report += udp_Logger_endl;                        
                    report += "LPNumber " + correct_plate(current_account_state.plate, plate_match);
                    report += "Match in Fo_AccountDatasLib[" + std::to_string(current_account_state.aid) + "], ";
                    report += "CarlibLP " + correct_plate(current_account_state.plate, plate_match);
                    report += ",Account type " + std::to_string(current_account_state.parking_type);
                    report += ",parking type " + std::to_string(current_account_state.present_type);
                    report += ",MatchChars " + std::to_string(plate_match);                               
                    report += udp_Logger_endl;
                    report += "APP Central Confirm the charge :" + std::to_string(current_account_state.paid_sum) + "!";
                    report += ",TicketNumber:" + correct_ticket(current_account_state.ticket);
                    report += ",LPNumber:" + correct_plate(current_account_state.plate, plate_match);
                    report += ",rsptype " + std::to_string(current_account_state.ticket_type);
                    report += udp_Logger_endl;
                }
                break;
                default:
                {
                    report += "tablet Request type unknown (200)*(.)  (300)*(!)";   
                    report += udp_Logger_endl;
                }
                break;
            }            
        }
        break;
        default:
        {
            report += "proof control unknown (200)*(.)  (300)*(!)";   
            report += udp_Logger_endl;
        }
        break;
    }
    return report;
}

int Logger::messege_Sender(std::string buffer)
{
    //std::cout << buffer << std::endl;
    int result = sendto(UDP_Logger_socket, buffer.c_str(), strlen(buffer.c_str()), 0, (sockaddr*)&log_udp_Receiver, sizeof(log_udp_Receiver));
    return result;
}