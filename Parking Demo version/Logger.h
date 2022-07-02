#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "Proof.h"
#include "Zone.h"

#define Logger_UDP_PORT "12580"
#define udp_Logger_endl {0x0d, 0x0a}

class Logger
{
public:
    MYSQL *mysql;
    Dashou dashou;
    struct sockaddr_in              log_udp_Sender;
    struct sockaddr_in              log_udp_Receiver;
    int status_Log = 0;
    int UDP_Logger_socket = -1;
    
    int port_number = atoi(Logger_UDP_PORT); 
    
    std::string Print_time(time_t now);
        
    std::string Proof_Print_time(time_t now);
    
    int initilize_UDP_Logger(MYSQL *_mysql, const char* ipAddress);
        
    int create_UDP_Logger_Server();
    
    std::string HEARTBEAT_messege_Builder(Site_type site, int accounts_sum);

    std::string ACK_webhost_messege_Builder(DashouParser *parser);

    std::string ACK_sites_messege_Builder(Site_type site,DashouParser *parser);

    std::string site_connecting_messege_Builder(Site_type site);

    std::string site_disconnecting_messege_Builder(Site_type site);
    
    std::string zone_info_messege_Builder(std::vector<Zone> Zones, int zone_log_index);

    std::string INITIAL_messege_Builder(Site_type site, DashouParser *parser);

    std::string CONTROL_TYPE_Header_messege_Builder(DashouParser parser);

    std::string CONTROL_TYPE_messege_Builder(int CONTROL_TYPE, int serial, std::vector<Camera_type> All_Cameras,int site_id, std::vector<Site_type> sites);
    
    std::string SystemParam_messege_Builder(int SystemParam_type, int setting_serial, int serial, int recv_type, Site_type site, Camera_type Camera_new_config);

    std::string proof_messege_Builder(accountInfo current_accountInfo, account_state current_account_state, Site_type site, DashouParser *parser, int plate_match, int control_type);

    int messege_Sender(std::string buffer);
    
private:
};


