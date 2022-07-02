#ifndef include
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <bits/stdc++.h>
#include <curl/curl.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <resolv.h>
#include <malloc.h>
#include <errno.h>
#include "Logger.h"
#include "error_Factory.h"


#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "md5.h"
#include <string.h>
#include <fcntl.h>


#define FAIL -1
#define DEBUG
#define MAX_SITES 255
#define MAX_black_list 1000
#define MAX_rule_step_list 100
#define DEFAULT_BUFLEN 1024
#define DATABASE_NAME  "parking_without_serverboard_db"
#define DATABASE_USERNAME "adminremote"
#define DATABASE_PASSWORD "123456789"
#define conf_txt "/var/www/html/confige.txt"

#define HTTP_request_URL_HEADER "GET "
#define HTTP_request_TAIL "\r\n"
#define OPTION_HTTP_request_PREV_HOST " HTTP/1.1\r\nUser-Agent: offline_service 1.1\r\nAccept: */*\r\nHost: "
#define OPTION_HTTP_request_APRE_HOST "\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\nCookie: secure; secure\r\n" 

#define GET_Current_Time_HTTP_request "/cgi-bin/global.cgi?action=getCurrentTime"
#define INSERT_BlackList_HTTP_request "/cgi-bin/recordUpdater.cgi?action=insert&name=TrafficBlackList&PlateNumber=%s&MasterOfCar=%s&PlateColor=%s&VehicleColor=%s&BeginTime=%s&CancelTime=%s"
#define UPDATE_BlackList_HTTP_request "/cgi-bin/recordUpdater.cgi?action=update&name=TrafficBlackList&recno=%s&PlateNumber=%s&MasterOfCar=%s&PlateColor=%s&VehicleColor=%s&BeginTime=%s&CancelTime=%s"
#define REMOVE_BlackList_HTTP_request "/cgi-bin/recordUpdater.cgi?action=remove&name=TrafficBlackList&recno=%s"
#define FINDER_BlackList_HTTP_request "/cgi-bin/recordFinder.cgi?action=find&name=TrafficBlackList&condition.PlateNumber=%s"

#define INSERT_WhiteList_HTTP_request "/cgi-bin/recordUpdater.cgi?action=insert&name=TrafficRedList&AuthorityList.OpenGate=true&PlateNumber=%s&MasterOfCar=%s&PlateColor=%s&VehicleColor=%s&BeginTime=%s&CancelTime=%s"
#define UPDATE_WhiteList_HTTP_request "/cgi-bin/recordUpdater.cgi?action=update&name=TrafficRedList&recno=%s&AuthorityList.OpenGate=true&PlateNumber=%s&MasterOfCar=%s&PlateColor=%s&VehicleColor=%s&BeginTime=%s&CancelTime=%s"
#define REMOVE_WhiteList_HTTP_request "/cgi-bin/recordUpdater.cgi?action=remove&name=TrafficRedList&recno=%s"
#define FINDER_WhiteList_HTTP_request "/cgi-bin/recordFinder.cgi?action=find&name=TrafficRedList&condition.PlateNumber=%s"

#define EVENT_LISTENNING_HTTP_request "/cgi-bin/eventManager.cgi?action=attach&codes=[TrafficJunction]&heartbeat=3"
#define EVENT_GETMANSNAP_HTTP_request "/cgi-bin/snapManager.cgi?action=attachFileProc&Flags[0]=Event&Events=[TrafficJunction]&heartbeat=3"
#define BUFFER_SIZE 1514

#endif

#ifndef variable_declaration
struct camera_event_TrafficCar
{
    bool IsBlackCar = false;
    time_t CapTime = 0;
    char CarType[10] = "";
    char Event[20] = "";
    bool OpenGate = false;
    time_t BeginTime = 0;
    time_t CancelTime = 0;
    time_t CreateTime = 0;
    bool Enable = false;
    char MasterOfCar[20] = "";
    char PlateColor[50] = "";
    char PlateNumber[20] = "";
    char PlateType[50] = "";
    int RecNo = -1;
    char TelephoneNumber[50] = "";
    bool TrustCar = false;
    char VehicleColor[50] = "";
    char VehicleType[50] = "";
};
struct camera_event_variable
{
    char plate[20] = "";
    char garage_event_type[20] = "";
    int garage_event_serial = 0;
};
struct camera_event
{
    char code[20] = "";
    int FrameSequence = -1;
    char Country[10] = "";
    int ObjectID = -1;
    char ObjectType[50] = "";
    char OriginalBoundingBox[50] = "";
    int Speed = 0;
    char DrivingDirection[50] = "";
    char MasterOfCar[50] = "";
    struct camera_event_TrafficCar current_TrafficCar;
    struct camera_event_variable;
};
struct response_header
{
    std::string entire_response_header = "";
    std::string Response_line_0 = "";
    std::string WWW_Authenticate = "";
    std::string realm = "";
    std::string qop = "";
    std::string nonce = "";
    std::string cnonce = "";
    std::string opaque = "";
};
MYSQL                               *mysql;
MYSQL                               *real_connect;
pthread_t                           main_Server_Thread;
pthread_t                           UDP_Server_Thread;
int                                 server_socket = INVALID_SOCKET;
int                                 webHost_Client_socket = INVALID_SOCKET;
SSL_CTX                             *ctx;
SSL                                 *ssl;
int                                 UDP_server_socket = INVALID_SOCKET;
struct sockaddr_in                  udp_Sender;
struct sockaddr_in                  udp_Receiver;
std::vector<std::string>            cars_Registered;
std::vector<Proof>                  all_proof;
std::vector<Site_type>              sites;
Setting                             Current_Settings(NULL);
garage_info                         Current_garage(NULL);
std::vector<Camera_type>            All_Cameras;
std::vector<monthly_to_hourly_type> monthly_to_hourly_list;
std::vector<rule_name_hourly_type>  rule_name_hourly_list;
std::vector<rule_step_hourly_type>  rule_step_hourly_list;
std::vector<black_list_type>        black_list;
std::vector<accountInfo>            accountInfo_list;
std::vector<account_state>          account_state_list;
std::vector<event_in>               event_in_list;
std::vector<event_out>              event_out_list;
std::vector<event_payment>          event_payment_list;
std::vector<temp_card>              temp_card_list;
std::vector<temp_card>              recv_temp_card_list;
std::vector<group_inner>            group_inner_list;
std::vector<monthly_type>           monthly_type_list;
std::vector<monthly_type>           temp_monthly_type_list;
std::vector<rule_name_monthly>      rule_name_monthly_list;
std::vector<rule_step_monthly>      rule_step_monthly_list;
std::vector<rule_step_monthly>      temp_rule_step_monthly_list;
std::vector<std::string>            offline_mode_messages_list;
int                                 Cameras[256];
int                                 Snap_Cameras[256];
pthread_t                           my_thread[MAX_SITES];
pthread_t                           main_Camera_Thread;
pthread_t                           my_Camera_Thread[MAX_SITES];
pthread_t                           my_Camera_snaps_Thread[MAX_SITES];
camera_event_variable               camera_event_data[MAX_SITES];
bool                                entry_event_by_Junction_Camera[MAX_SITES];
bool                                exit_event_by_Junction_Camera[MAX_SITES];
bool                                Camera_status[MAX_SITES];
bool                                Camera_snap_status[MAX_SITES];
struct sockaddr_in                  server;
struct sockaddr_in                  client_WEBHOST;
const char*                         WebHost_IP;
const char*                         WebHost_PORT;
pthread_t                           config_thread;
pthread_t                           client_WEBHOST_thread;
pthread_t                           client_WEBHOST_thread_receive_STD_step;
pthread_t                           client_WEBHOST_thread_receive_STD_montly_step;
pthread_t                           client_WEBHOST_thread_receive_accounts;
pthread_t                           client_WEBHOST_thread_receive_monthly_type;
bool                                webhost_reconnect_try = true;
bool                                conf_has_changed = false;
bool site_ACK_setting = false;
int site_ACK_setting_serial = -1;
int site_ACK_setting_type = -1;
int OPTION_VALUE = 1;
std::string msg = "";
int accounts_sum = 0;
int gen_Entry_serial = 0;
int gen_Exit_serial = 0;
int gen_APPpay_serial = 0;
int proof_serial = 0;
int broadcastSerial = 0;
int localSerialDownLink = 0;
int localSerialUpLink = 0;
int localSerialSetting = 0;
int heartbeatIndex = 0;

bool web_host_locked = false;
bool web_host_client_send_confirm_data = false;
Site_type server_site(NULL);

Logger log_udp;
DashouParser parser;
DashouParser parser_host;
Dashou dashou;
std::vector<Zone> Zones;
int Zone_as_official = 1;

char My_Online_IP[25] = "";
char My_local_IP_port[25] = "";
char my_ip_prefix[20] = "";
char My_local_IP[25] = "";
char default_port[25] = "";
char udp_port[25] = "";

#endif

#ifndef function_declaration

time_t string_to_time_t(const char *date);

std::string time_t_to_http_time(time_t now)
{
    if(now == 0) return "000000000000";
    tm *my_time = localtime(&now);
    std::string date = "";
    date += std::to_string(my_time->tm_year + 1900);
    date += "-";
    date += dashou.to_String_00(my_time->tm_mon + 1);
    date += "-";
    date += dashou.to_String_00(my_time->tm_mday);
    date += "%20";
    date += dashou.to_String_00(my_time->tm_hour);
    date += ":";
    date += dashou.to_String_00(my_time->tm_min);
    date += ":";
    date += dashou.to_String_00(my_time->tm_sec);
    return date;
}

std::string camera_event_variable_to_string(camera_event_variable current_camera_event_variable)
{
    std::string s = "";
    s += std::to_string(current_camera_event_variable.garage_event_serial);
    s += "_";
    s += std::string(current_camera_event_variable.garage_event_type);
    s += "_";
    s += std::string(current_camera_event_variable.plate);
    return s;
}
// connection function

std::string md5_A1_calc(std::string user, std::string realm, std::string password)
{
    std::string A1 = user + ":" + realm + ":" + password;
    return md5(A1);
}

std::string md5_A2_calc(std::string method, std::string requested_uri)
{
    std::string A2 = method + ":" + requested_uri;
    return md5(A2);
}

std::string request_digest_calc(std::string md5_A1, std::string nonce, std::string nc, std::string cnonce, std::string qop, std::string md5_A2)
{
    std::string str = md5_A1 + ":" + nonce + ":" + nc + ":" + cnonce + ":" + qop + ":" + md5_A2;
    return md5(str);
}

std::string struct_response_to_string(response_header res, std::string user, std::string password, std::string requested_uri)
{
    std::string s = "";
    s += "Authorization: Digest username=\"";
    s += user;
    s += "\", ";
    s += "realm=\"";
    s += res.realm;
    s += "\", ";
    s += "nonce=\"";
    s += res.nonce;
    s += "\", ";
    s += "uri=\"";
    s += requested_uri;
    s += "\", ";
    s += "algorithm=\"";
    s += "MD5";
    s += "\", ";
    s += "qop=";
    s += res.qop;
    s += ", ";
    s += "nc=";
    s += "00000001";
    s += ", ";
    s += "cnonce=\"";
    s += res.cnonce;
    s += "\", ";
    s += "response=\"";
    std::string md5_A1 = md5_A1_calc(user, res.realm, password);
    std::string md5_A2 = md5_A2_calc("GET", requested_uri);
    std::string request_digest = request_digest_calc(md5_A1, res.nonce, "00000001", res.cnonce, res.qop, md5_A2);
    s += request_digest;
    s += "\", ";
    s += "opaque=\"";
    s += res.opaque;
    s += "\"";
    s += "\r\n";
    return s;
}

response_header get_response_info(std::string str)
{
    response_header res;
    res.entire_response_header = str;
    int i = 0;
    int k = 0;
    for(i = 0; i < str.length(); i++)
    {
        if(i == 0 && res.Response_line_0.compare("") == 0)
        {
            while(str[i + k] != '\n')
            {
                res.Response_line_0 += str[i + k];
                k++;
            }
        }
        if(str.substr(i, 18).compare("WWW-Authenticate: ") == 0)
        {
            k = 18;
            while(str[i + k] != ' ')
            {
                res.WWW_Authenticate += str[i + k];
                k++;
            }
            i += 17;
        }
        if(str.substr(i, 7).compare("realm=\"") == 0)
        {
            k = 7;
            while(str[i + k] != '"')
            {
                res.realm += str[i + k];
                k++;
            }
        }
        if(str.substr(i, 5).compare("qop=\"") == 0)
        {
            k = 5;
            while(str[i + k] != '"')
            {
                res.qop += str[i + k];
                k++;
            }
        }
        if(str.substr(i, 7).compare("nonce=\"") == 0)
        {
            k = 7;
            while(str[i + k] != '"')
            {
                res.nonce += str[i + k];
                k++;
            }
        }
        if(str.substr(i, 8).compare("opaque=\"") == 0)
        {
            k = 8;
            while(str[i + k] != '"')
            {
                res.opaque += str[i + k];
                k++;
            }
        }
    }
    res.cnonce = md5(std::to_string(time(0)));
    return res;
}

int create_socket()
{
    int on = 1, sock;     
    sock = socket(AF_INET, SOCK_STREAM, 0);
    struct timeval tout;
    tout.tv_sec=3;
    tout.tv_usec=500000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tout, sizeof(tout));
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &on, sizeof(int));
    if(sock == -1)
    {
            perror("setsockopt");
            exit(1);
    }
    return sock;
}

int socket_connect(int sock, const char* Camera_ADDRESS, const char* Camera_PORT)
{
    struct sockaddr_in client_CAMERA;
    bzero(&client_CAMERA, sizeof(client_CAMERA));
    client_CAMERA.sin_addr.s_addr = inet_addr(Camera_ADDRESS);
    client_CAMERA.sin_family = AF_INET;
    client_CAMERA.sin_port = htons(atoi(Camera_PORT));
    int execute = connect(sock, (struct sockaddr *)&client_CAMERA,sizeof(client_CAMERA));
    if (execute < 0)
    {
        //std::cout << "connection refused\n";
        return execute;
    }
    return 0;
}

int send_http_request(const char* Camera_ADDRESS, std::string str, char buffer[BUFFER_SIZE])
{
    int fd = create_socket();
    socket_connect(fd, Camera_ADDRESS, "80"); 
    send(fd, str.c_str(), strlen(str.c_str()), 0);
    bzero(buffer, BUFFER_SIZE);
    int byte_rec = recv(fd, buffer, BUFFER_SIZE - 1, 0);
    //fprintf(stderr, "%s", buffer);
    return byte_rec;
}

bool success_listenning(char buffer[BUFFER_SIZE])
{
    std::string response = "";
    int i = 0;
    while(buffer[i] != '\n')
    {
        response += buffer[i];
        i++;
    }
    if(response.substr(0,15).compare("HTTP/1.1 200 OK") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string get_response_CONTENT(std::string str, int byte_Rec)
{
    std::string CONTENT_length = "";
    std::string CONTENT = "";
    int length = 0;
    int i = 0;
    int k = 0;
    for(i = 0; i < str.length(); i++)
    {
        if(str.substr(i,15).compare("CONTENT-LENGTH:") == 0 || str.substr(i,15).compare("Content-Length:") == 0)
        {
            k = 15;
            while(str[i + k] != '\n')
            {
                CONTENT_length += str[i + k];
                k++;
            }
            length = std::stoi(CONTENT_length);
            for(int j = 0; i + k + j + 4 < byte_Rec; j++)
            {
                CONTENT += str[i + k + j + 3];
            }
            break;
        }
    }
    return CONTENT;
}

int get_record_Number(std::string str)
{
    std::string record_Number = "";
    int Rec_No = 0;
    int i = 0;
    int k = 0;
    for(i = 0; i < str.length(); i++)
    {
        if(str.substr(i,17).compare("records[0].RecNo=") == 0)
        {
            k = 17;
            while(str[i + k] != '\n')
            {
                record_Number += str[i + k];
                k++;
            }
            Rec_No = std::stoi(record_Number);
            break;
        }
    }
    return Rec_No;
}

int get_binary_response(char buffer[BUFFER_SIZE], char data[BUFFER_SIZE])
{
    int length = 0;
    char content_length[20] = "";
    char content_fixed[16] = "CONTENT-LENGTH:";
    char content_fixed1[16] = "Content-Length:";
    int k = 0;
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        memcpy(content_length, buffer + i, 15);
        content_length[15] = 0;
        if(strcmp(content_length, content_fixed) == 0 || strcmp(content_length, content_fixed1) == 0)
        {
            k = 15;
            while(buffer[i + k] != '\n')
            {
                k++;
            }
            for(int j = 0; i + k + j + 3 < BUFFER_SIZE; j++)
            {
                data [j] = buffer[i + k + j + 3];
                length++;
            }
            break;
        }
    }
    return length;
}

std::string get_response_Type(std::string str)
{
    std::string CONTENT_TYPE = "";
    int length = 0;
    int i = 0;
    int k = 0;
    for(i = 0; i < str.length(); i++)
    {
        if(str.substr(i,14).compare("Content-Type: ") == 0 || str.substr(i,14).compare("Content-Type: ") == 0)
        {
            k = 14;
            while(str[i + k] != '\n')
            {
                CONTENT_TYPE += str[i + k];
                k++;
            }
            break;
        }
    }
    return CONTENT_TYPE;
}

int get_response_CONTENT_LENGTH(std::string str)
{
    std::string CONTENT_length = "";
    std::string CONTENT = "";
    int length = 0;
    int i = 0;
    int k = 0;
    for(i = 0; i < str.length(); i++)
    {
        if(str.substr(i,15).compare("CONTENT-LENGTH:") == 0 || str.substr(i,15).compare("Content-Length:") == 0)
        {
            k = 15;
            while(str[i + k] != 0x0d)
            {
                CONTENT_length += str[i + k];
                k++;
            }
            try
            {
                length = std::stoi(CONTENT_length);
            }
            catch(...)
            {
                fprintf(stderr, "Error in get_response_CONTENT_LENGTH stoi ...!!\n");
            }
        }
    }
    return length;
}

// park function

std::string build_insert_black_list_uri(char plate[12])
{
    char res[1024] = "";
    int n = sprintf (res, INSERT_BlackList_HTTP_request, plate, "Unkown", "Unkown", "Unkown", "2000-01-01%2002:00:00", "2000-01-01%2002:00:00");
    return std::string(res);
}

std::string build_update_black_list_uri(char plate[12], int record_number)
{
    char res[1024] = "";
    int n = sprintf (res, UPDATE_BlackList_HTTP_request, std::to_string(record_number).c_str(), plate, "Unkown", "Unkown", "Unkown", "2000-01-01%2002:00:00", "2000-01-01%2002:00:00");
    return std::string(res);
}

std::string build_remove_black_list_uri(int record_number)
{
    char res[1024] = "";
    int n = sprintf (res, REMOVE_BlackList_HTTP_request, std::to_string(record_number).c_str());
    return std::string(res);
}

std::string build_find_black_list_uri(char plate[12])
{
    char res[1024] = "";
    int n = sprintf (res, FINDER_BlackList_HTTP_request, plate);
    return std::string(res);
}

std::string build_insert_white_list_uri(accountInfo current_accountInfo)
{
    char res[1024] = "";
    int n = sprintf (res, INSERT_WhiteList_HTTP_request, current_accountInfo.plate, current_accountInfo.owner_name, "Unkown", "Unkown", time_t_to_http_time(current_accountInfo.start_time).c_str(), time_t_to_http_time(current_accountInfo.end_time).c_str());
    return std::string(res);
}

std::string build_update_white_list_uri(accountInfo current_accountInfo, int record_number)
{
    char res[1024] = "";
    int n = sprintf (res, UPDATE_WhiteList_HTTP_request, std::to_string(record_number).c_str(), current_accountInfo.plate, current_accountInfo.owner_name, "Unkown", "Unkown", time_t_to_http_time(current_accountInfo.start_time).c_str(), time_t_to_http_time(current_accountInfo.end_time).c_str());
    return std::string(res);
}

std::string build_remove_white_list_uri(int record_number)
{
    char res[1024] = "";
    int n = sprintf (res, REMOVE_WhiteList_HTTP_request, std::to_string(record_number).c_str());
    return std::string(res);
}

std::string build_find_white_list_uri(accountInfo current_accountInfo)
{
    char res[1024] = "";
    int n = sprintf (res, FINDER_WhiteList_HTTP_request, current_accountInfo.plate);
    return std::string(res);
}

void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile)
{
    /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(ctx) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}

SSL_CTX* InitCTX(void)
{
    SSL_METHOD *method;
    SSL_CTX *ctx;
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    method = (SSL_METHOD *)TLSv1_2_client_method();  /* Create new client-method instance */
    ctx = SSL_CTX_new(method);   /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void check_image_path(std::string image_dir)
{
    struct stat sb;
    std::string path = image_dir;
    if (!(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) 
    {
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    path = image_dir + "/Junction";
    if (!(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) 
    {
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    path = image_dir + "/Junction/Entry";
    if (!(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) 
    {
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    path = image_dir + "/Junction/Exit";
    if (!(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) 
    {
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
}

int send_image(photo current_photo)
{
    CURL *curl;
    CURLcode res;

    curl_mime *form = NULL;
    curl_mimepart *field = NULL;
    struct curl_slist *headerlist = NULL;
    static const char buf[] = "Expect:";

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if(curl)
    {
        form = curl_mime_init(curl);
        
        field = curl_mime_addpart(form);
        curl_mime_name(field, "upfile");
        std::string data_picture = "";
        data_picture = std::string(current_photo.photo_path) + std::string(current_photo.photo_name);
        curl_mime_filedata(field, data_picture.c_str());

        field = curl_mime_addpart(form);
        curl_mime_name(field, "name");
        curl_mime_data(field, current_photo.photo_name, CURL_ZERO_TERMINATED);

        field = curl_mime_addpart(form);
        curl_mime_name(field, "parking_lot_id");
        curl_mime_data(field, std::to_string(current_photo.gid).c_str(), CURL_ZERO_TERMINATED);
        
        field = curl_mime_addpart(form);
        curl_mime_name(field, "cam_ip");
        curl_mime_data(field, current_photo.camera_address, CURL_ZERO_TERMINATED);

        field = curl_mime_addpart(form);
        curl_mime_name(field, "recive_time");
        curl_mime_data(field, std::to_string(current_photo.receive_time).c_str(), CURL_ZERO_TERMINATED);

        field = curl_mime_addpart(form);
        curl_mime_name(field, "plate_number");
        curl_mime_data(field, current_photo.plate_number, CURL_ZERO_TERMINATED);
        
        field = curl_mime_addpart(form);
        curl_mime_name(field, "ticket");
        curl_mime_data(field, current_photo.ticket, CURL_ZERO_TERMINATED);
        
        field = curl_mime_addpart(form);
        curl_mime_name(field, "garage_event_type");
        curl_mime_data(field, current_photo.garage_event_type, CURL_ZERO_TERMINATED);
        
        field = curl_mime_addpart(form);
        curl_mime_name(field, "garage_event_serial");
        curl_mime_data(field, std::to_string(current_photo.garage_event_serial).c_str(), CURL_ZERO_TERMINATED);

        field = curl_mime_addpart(form);
        curl_mime_name(field, "plate_color");
        curl_mime_data(field, current_photo.plate_color, CURL_ZERO_TERMINATED);

        field = curl_mime_addpart(form);
        curl_mime_name(field, "plate_type");
        curl_mime_data(field, current_photo.plate_type, CURL_ZERO_TERMINATED);

        field = curl_mime_addpart(form);
        curl_mime_name(field, "event_lane");
        curl_mime_data(field, std::to_string(current_photo.event_lane).c_str(), CURL_ZERO_TERMINATED);

        field = curl_mime_addpart(form);
        curl_mime_name(field, "event_type");
        curl_mime_data(field, current_photo.event_type, CURL_ZERO_TERMINATED);

        field = curl_mime_addpart(form);
        curl_mime_name(field, "event_time");
        curl_mime_data(field, std::to_string(current_photo.event_time).c_str(), CURL_ZERO_TERMINATED);

        field = curl_mime_addpart(form);
        curl_mime_name(field, "vehicle_color");
        curl_mime_data(field, current_photo.vehicle_color, CURL_ZERO_TERMINATED);

        field = curl_mime_addpart(form);
        curl_mime_name(field, "vehicle_size");
        curl_mime_data(field, current_photo.vehicle_size, CURL_ZERO_TERMINATED);
        
        field = curl_mime_addpart(form);
        curl_mime_name(field, "vehicle_type");
        curl_mime_data(field, current_photo.vehicle_type, CURL_ZERO_TERMINATED);
        headerlist = curl_slist_append(headerlist, buf);
        curl_easy_setopt(curl, CURLOPT_URL, Current_Settings.uploadurl);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return -105;
        }
        else
        {
            fprintf(stderr, "\n");
        }
        curl_easy_cleanup(curl);
        curl_mime_free(form);
        curl_slist_free_all(headerlist);
    }
    else
    {
        return -106;
    }
    return 0;
}

camera_event event_parse(std::string data)
{
    camera_event current_camera_event;
    std::string var_data = "";
    int length = 0;
    int i = 0;
    int k = 0;
    for(i = 0; i < data.length(); i++)
    {
        if(data.substr(i,10).compare("\"Code\" : \"") == 0)
        {
            k = 10;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.code, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,18).compare("\"FrameSequence\" : ") == 0)
        {
            k = 18;
            while(data[i + k] != ',')
            {
                var_data += data[i + k];
                k++;
            }
            try
            {
                current_camera_event.FrameSequence = std::stoi(var_data);
            }
            catch(...)
            {
                current_camera_event.FrameSequence = -1;
            }
            var_data = "";
            i += k;
        }
        if(data.substr(i,13).compare("\"Country\" : \"") == 0)
        {
            k = 13;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.Country, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,13).compare("\"ObjectID\" : ") == 0 && current_camera_event.ObjectID == 0)
        {
            k = 13;
            while(data[i + k] != ',')
            {
                var_data += data[i + k];
                k++;
            }
            try
            {
                current_camera_event.ObjectID = std::stoi(var_data);
            }
            catch(...)
            {
                current_camera_event.ObjectID = -1;
            }
            var_data = "";
            i += k;
        }
        if(data.substr(i,16).compare("\"ObjectType\" : \"") == 0 && std::string(current_camera_event.ObjectType).compare("") == 0)
        {
            k = 16;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.ObjectType, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,24).compare("\"OriginalBoundingBox\" : ") == 0 && std::string(current_camera_event.OriginalBoundingBox).compare("") == 0)
        {
            k = 24;
            while(data[i + k] != ',')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.OriginalBoundingBox, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,10).compare("\"Speed\" : ") == 0 && current_camera_event.Speed == 0)
        {
            k = 10;
            while(data[i + k] != ',')
            {
                var_data += data[i + k];
                k++;
            }
            try
            {
                current_camera_event.Speed = std::stoi(var_data);
            }
            catch(...)
            {
                current_camera_event.Speed = -1;
            }
            var_data = "";
            i += k;
        }
        if(data.substr(i,21).compare("\"DrivingDirection\" : ") == 0)
        {
            k = 21;
            while(data[i + k] != ',')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.DrivingDirection, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,15).compare("\"IsBlackCar\" : ") == 0)
        {
            k = 15;
            while(data[i + k] != '\n')
            {
                var_data += data[i + k];
                k++;
            }
            if(var_data.compare("false") == 0)
            {
                current_camera_event.current_TrafficCar.IsBlackCar = false;
            }
            if(var_data.compare("true") == 0)
            {
                current_camera_event.current_TrafficCar.IsBlackCar = true;
            }
            var_data = "";
            i += k;
        }
        if(data.substr(i,12).compare("\"CapTime\" : ") == 0)
        {
            k = 12;
            while(data[i + k] != '.' && data[i + k] != '\n')
            {
                var_data += data[i + k];
                k++;
            }
            try
            {
                current_camera_event.current_TrafficCar.CapTime = std::stol(var_data);
            }
            catch(...)
            {
                current_camera_event.current_TrafficCar.CapTime = Reference_date;
            }
            var_data = "";
            i += k;
        }
        if(data.substr(i,13).compare("\"CarType\" : \"") == 0)
        {
            k = 13;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.current_TrafficCar.CarType, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,11).compare("\"Event\" : \"") == 0)
        {
            k = 11;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.current_TrafficCar.Event, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,13).compare("\"OpenGate\" : ") == 0)
        {
            k = 13;
            while(data[i + k] != '\n')
            {
                var_data += data[i + k];
                k++;
            }
            if(var_data.compare("false") == 0)
            {
                current_camera_event.current_TrafficCar.OpenGate = false;
            }
            if(var_data.compare("true") == 0)
            {
                current_camera_event.current_TrafficCar.OpenGate = true;
            }
            var_data = "";
            i += k;
        }
        if(data.substr(i,15).compare("\"BeginTime\" : \"") == 0)
        {
            k = 15;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            current_camera_event.current_TrafficCar.BeginTime = string_to_time_t(var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,16).compare("\"CancelTime\" : \"") == 0)
        {
            k = 16;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            current_camera_event.current_TrafficCar.CancelTime = string_to_time_t(var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,15).compare("\"CreateTime\" : ") == 0)
        {
            k = 15;
            while(data[i + k] != ',')
            {
                var_data += data[i + k];
                k++;
            }
            try
            {
                current_camera_event.current_TrafficCar.CreateTime = std::stol(var_data);
            }
            catch(...)
            {
                current_camera_event.current_TrafficCar.CreateTime = Reference_date;
            }
            var_data = "";
            i += k;
        }
        if(data.substr(i,11).compare("\"Enable\" : ") == 0)
        {
            k = 11;
            while(data[i + k] != ',')
            {
                var_data += data[i + k];
                k++;
            }
            if(var_data.compare("false") == 0)
            {
                current_camera_event.current_TrafficCar.Enable = false;
            }
            if(var_data.compare("true") == 0)
            {
                current_camera_event.current_TrafficCar.Enable = true;
            }
            var_data = "";
            i += k;
        }
        if(data.substr(i,17).compare("\"MasterOfCar\" : \"") == 0)
        {
            k = 17;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.current_TrafficCar.MasterOfCar, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,16).compare("\"PlateColor\" : \"") == 0)
        {
            k = 16;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.current_TrafficCar.PlateColor, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,17).compare("\"PlateNumber\" : \"") == 0)
        {
            k = 17;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.current_TrafficCar.PlateNumber, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,15).compare("\"PlateType\" : \"") == 0)
        {
            k = 15;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.current_TrafficCar.PlateType, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,10).compare("\"RecNo\" : ") == 0)
        {
            k = 10;
            while(data[i + k] != ',')
            {
                var_data += data[i + k];
                k++;
            }
            try
            {
                current_camera_event.current_TrafficCar.RecNo = std::stoi(var_data);
            }
            catch(...)
            {
                current_camera_event.current_TrafficCar.RecNo = -1;
            }
            var_data = "";
            i += k;
        }
        if(data.substr(i,21).compare("\"TelephoneNumber\" : \"") == 0)
        {
            k = 21;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.current_TrafficCar.TelephoneNumber, var_data.c_str());
            var_data = "";
            i += k;
        }        
        if(data.substr(i,13).compare("\"TrustCar\" : ") == 0)
        {
            k = 13;
            while(data[i + k] != ',')
            {
                var_data += data[i + k];
                k++;
            }
            if(var_data.compare("false") == 0)
            {
                current_camera_event.current_TrafficCar.TrustCar = false;
            }
            if(var_data.compare("true") == 0)
            {
                current_camera_event.current_TrafficCar.TrustCar = true;
            }
            var_data = "";
            i += k;
        }
        if(data.substr(i,18).compare("\"VehicleColor\" : \"") == 0)
        {
            k = 18;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.current_TrafficCar.VehicleColor, var_data.c_str());
            var_data = "";
            i += k;
        }
        if(data.substr(i,17).compare("\"VehicleType\" : \"") == 0)
        {
            k = 17;
            while(data[i + k] != '"')
            {
                var_data += data[i + k];
                k++;
            }
            strcpy(current_camera_event.current_TrafficCar.VehicleType, var_data.c_str());
            var_data = "";
            i += k;
            break;
        }
    }
    return current_camera_event;
}

void print_camera_event(camera_event current_camera_event)
{
    std::cout << "camera_event Code = " << std::string(current_camera_event.code) << std::endl;
    std::cout << "camera_event FrameSequence = " << current_camera_event.FrameSequence << std::endl;
    std::cout << "camera_event Country = " << std::string(current_camera_event.Country) << std::endl;
    std::cout << "camera_event ObjectID = " << current_camera_event.ObjectID << std::endl;
    std::cout << "camera_event ObjectType = " << std::string(current_camera_event.ObjectType) << std::endl;
    std::cout << "camera_event OriginalBoundingBox = " << std::string(current_camera_event.OriginalBoundingBox) << std::endl;
    std::cout << "camera_event Speed = " << current_camera_event.Speed << std::endl;
    std::cout << "camera_event DrivingDirection = " << std::string(current_camera_event.DrivingDirection) << std::endl;
    std::cout << "camera_event IsBlackCar = " << current_camera_event.current_TrafficCar.IsBlackCar << std::endl;
    std::cout << "camera_event CapTime = " << dashou.Print_time(current_camera_event.current_TrafficCar.CapTime) << std::endl;
    std::cout << "camera_event CarType = " << std::string(current_camera_event.current_TrafficCar.CarType) << std::endl;
    std::cout << "camera_event Event = " << std::string(current_camera_event.current_TrafficCar.Event) << std::endl;
    std::cout << "camera_event OpenGate = " << current_camera_event.current_TrafficCar.OpenGate << std::endl;
    std::cout << "camera_event BeginTime = " << dashou.Print_time(current_camera_event.current_TrafficCar.BeginTime) << std::endl;
    std::cout << "camera_event CancelTime = " << dashou.Print_time(current_camera_event.current_TrafficCar.CancelTime) << std::endl;
    std::cout << "camera_event CreateTime = " << dashou.Print_time(current_camera_event.current_TrafficCar.CreateTime) << std::endl;
    std::cout << "camera_event Enable = " << current_camera_event.current_TrafficCar.Enable << std::endl;
    std::cout << "camera_event MasterOfCar = " << std::string(current_camera_event.current_TrafficCar.MasterOfCar) << std::endl;
    std::cout << "camera_event PlateColor = " << std::string(current_camera_event.current_TrafficCar.PlateColor) << std::endl;
    std::cout << "camera_event PlateNumber = " << std::string(current_camera_event.current_TrafficCar.PlateNumber) << std::endl;
    std::cout << "camera_event PlateType = " << std::string(current_camera_event.current_TrafficCar.PlateType) << std::endl;
    std::cout << "camera_event RecNo = " << current_camera_event.current_TrafficCar.RecNo << std::endl;
    std::cout << "camera_event TelephoneNumber = " << std::string(current_camera_event.current_TrafficCar.TelephoneNumber) << std::endl;
    std::cout << "camera_event TrustCar = " << current_camera_event.current_TrafficCar.TrustCar << std::endl;
    std::cout << "camera_event VehicleColor = " << std::string(current_camera_event.current_TrafficCar.VehicleColor) << std::endl;
    std::cout << "camera_event VehicleType = " << std::string(current_camera_event.current_TrafficCar.VehicleType) << std::endl;
}

void finish_with_error(MYSQL *mysql, int error_code);

void unkown_error(MYSQL *mysql, int error_code);

int get_server_error_log_insert_aid();

int get_photo_insert_aid();

bool initialize(char* _my_local_IP);

bool create_Server(const char* My_local_IP, int OPTION_VALUE);

bool create_Client(const char* WebHost_IP_ADDRESS, const char* WebHost_Client_PORT, const char* My_online_IP);

bool create_UDP_Server(const char* ipAddress,const char* port);

void* process_config(void * arg);

void* UDP_process_server(void *arg);

void* main_Camera_Process(void * arg);

void* Camera_Process(void * arg);

void* Camera_snap_Process(void * arg);

void* client_WEBHOST_Process(void *arg);

void initSite(Site_type site, DashouParser *parser);

std::string genACK(int function, int serial, int error);

std::string genSysParam(Site_type site, DashouParser *parser);

std::string genSysParamBalanceNotification(Site_type site, DashouParser *parser);

std::string genSysParamExpireForecast(Site_type site, DashouParser *parser);

std::string genSysParamCameraSite(Site_type site, DashouParser *parser);

std::string genSysParamNetworkParam(Site_type site, DashouParser *parser);

std::string genSysParamSiteName(Site_type site, DashouParser *parser);

std::string genSysParamLeddisplay(Site_type site, DashouParser *parser);

std::string genSysParamTicketHeader(Site_type site, DashouParser *parser);

std::string genSysParamReceiptFormat(Site_type site, DashouParser *parser);

std::string genSysParamChargeRate(Site_type site, DashouParser *parser);

std::string gen_ServiceBoard_Entry_Request_Msg(event_in current_event_in);

std::string gen_ServiceBoard_Pay_Request_Msg110(account_state current_account_state, event_charge current_event_charge);

std::string gen_ServiceBoard_Pay_Request_Msg100(event_charge current_event_charge, bool charge);

std::string gen_ServiceBoard_Exit_Request_Msg100(event_out current_event_out);

std::string gen_ServiceBoard_Exit_Request_Msg110(account_state current_account_state, event_out current_event_out);

std::string get_site_Type(int type);

std::string get_site_Address(int address);

std::string get_site_Status(int status);

std::string gen_ServiceBoard_TimeSpaces_Msg();

int searchProof(Proof &proof, int REQUEST_TYPE);

std::string gen_ServiceBoard_Entry_To_Webhost_Request_Msg();

std::string gen_ServiceBoard_Init_To_Webhost_Request_Msg();

std::string gen_ServiceBoard_ACK_Msg(int serial, int function, int error);

std::string gen_ServiceBoard_Init_Done_To_Webhost_Request_Msg();

std::string gen_ServiceBoard_Spaces_To_Webhost_Msg(int serial, int TotalSpace, int TotalSpaceSeason, int TotalSpaceHourly, int TotalVacantSpace, int VacantSpaceSeason, int VacantSpaceHourly);

std::string gen_ServiceBoard_Spaces_ACK2_Msg(int serial);

std::string gen_ServiceBoard_Init_Device_To_Webhost_Request_Msg(Site_type site);

std::string gen_ServiceBoard_Heartbeat_Site_To_Webhost_Request_Msg(Site_type site);

void Handle_webhost_received_data(unsigned char* webhost_buffer, DashouParser *parser_host);

int find_site_by_address(int site_address);

bool initServiceBoard(DashouParser *parser_host);

bool heartbeat(int zone_log_counter, int zone_log_index, DashouParser *parser_host);

void registerNewSiteToWebHost(Site_type site);

void print_sites_list(MYSQL *mysql, std::vector<Site_type> _sites_list);

void print_blacklist_list(MYSQL *mysql, std::vector<black_list_type> _black_list);

void print_rule_name_hourly_list(MYSQL *mysql, std::vector<rule_name_hourly_type> _rule_name_hourly_type_list);

void print_zone_list(MYSQL *mysql, std::vector<Zone> _zones_list);

void print_monthly_to_hourly_list(MYSQL *mysql, std::vector<monthly_to_hourly_type> _monthly_to_hourly_list);

void print_camera_list(MYSQL *mysql, std::vector<Camera_type> _Camera_type_list);

void print_accountinfo_list(MYSQL *mysql, std::vector<accountInfo> _accountinfo_list);

void print_account_state_list(MYSQL *mysql, std::vector<account_state> _account_state_list);

void print_event_in_list(MYSQL *mysql, std::vector<event_in> _event_in_list);

void print_event_out_list(MYSQL *mysql, std::vector<event_out> _event_out_list);

void print_event_payment_list(MYSQL *mysql, std::vector<event_payment> _event_payment_list);

void print_event_charge_list(MYSQL *mysql, std::vector<event_charge> _event_charge_list);

void print_temp_card_list(MYSQL *mysql, std::vector<temp_card> _temp_card_list);

void print_group_inner_list(MYSQL *mysql, std::vector<group_inner> _group_inner_list);

void print_monthly_type_list(MYSQL *mysql, std::vector<monthly_type> _monthly_type_list);

void print_rule_name_monthly_list(MYSQL *mysql, std::vector<rule_name_monthly> _monthly_type_list);

void print_rule_step_monthly_list(MYSQL *mysql, std::vector<rule_step_monthly> _rule_step_monthly_list);

std::vector<black_list_type> read_db_black_list(MYSQL *mysql);

std::vector<rule_name_hourly_type> read_db_rule_name_hourly(MYSQL *mysql);

std::vector<Zone> read_db_Zone(MYSQL *mysql);

std::vector<monthly_to_hourly_type> read_db_monthly_to_hourly(MYSQL *mysql);

std::vector<Camera_type> read_db_camera(MYSQL *mysql);

std::vector<accountInfo> read_db_accountInfo(MYSQL *mysql);

std::vector<account_state> read_db_account_state(MYSQL *mysql);

std::vector<event_in> read_db_event_in(MYSQL *mysql);

std::vector<event_out> read_db_event_out(MYSQL *mysql);

std::vector<event_payment> read_db_event_payment(MYSQL *mysql);

std::vector<event_charge> read_db_event_charge(MYSQL *mysql);

std::vector<temp_card> read_db_temp_card(MYSQL *mysql);

std::vector<group_inner> read_db_group_inner(MYSQL *mysql);

std::vector<monthly_type> read_db_monthly_type(MYSQL *mysql);

std::vector<rule_name_monthly> read_db_rule_name_monthly(MYSQL *mysql);

std::vector<rule_step_monthly> read_db_rule_step_monthly(MYSQL *mysql);

int get_account_info_insert_aid();

int get_account_state_insert_aid();

int get_event_in_insert_aid();

int get_event_out_insert_aid();

int get_event_payment_insert_aid();

int get_event_charge_insert_aid();

int get_temp_card_insert_id();

int get_aid_monthly_type_from_id(int id);

int get_monthly_type_insert_aid();

int search_for_account(std::string ticket, std::string plate);

int search_for_camera(int site_id);

void make_event_in(event_in &current_event_in, int site_id, camera_event current_camera_event);

void make_event_charge(accountInfo current_accountInfo, account_state current_account_state, event_charge &current_event_charge);

void make_event_out(accountInfo current_accountInfo, account_state current_account_state, event_out &current_event_out, int site_id);

void make_accountInfo(accountInfo &current_accountInfo, DashouParser *parser);

void make_account_state(account_state &current_account_state, int site_id, DashouParser *parser);

void temp_card_to_account(std::vector<temp_card> _temp_card_list);

bool check_blacklist_exist(std::string plate);

int get_zone_id_by_site(int site_id);

void setDateTime(int day, int month, int year,int hour, int min, int sec);

std::string genSysParam_response_garage_info_to_webhost(garage_info Current_garage, int Setting_type);

std::string genSysParam_response_proofmodel_to_webhost(int site_to_change[], int Setting_type, int site_count);

std::string genSysParam_response_onecaroneproof_to_webhost(int site_to_change[], int Setting_type, int site_count);

std::string genSysParam_response_id_PresetType_to_webhost(int site_to_change[], int Setting_type, int site_count);

std::string genSysParam_response_black_list_to_webhost(int Setting_type, int count, bool add_to_black_list, black_list_type tmp_black_account);

std::string genSysParam_response_confirm_plate_to_webhost(int site_to_change[], int Setting_type, int site_count);

std::string genSysParam_response_exitFreeLetPass_to_webhost(int site_to_change[], int Setting_type, int site_count);

std::string genSysParam_response_Full_no_entry_to_webhost(int site_to_change[], int Setting_type, int site_count);

std::string genSysParam_response_plate_match_level_to_webhost(int Setting_type, int plate_match_level);

std::string genSysParam_response_mobile_charge_standard_to_webhost(int Setting_type, int mobile_charge_standard);

std::string genSysParam_response_user_auth_to_webhost(int Setting_type, sys_user Current_sys_user);

std::string genSysParam_response_balanceNotificationThreshold_to_webhost(int Setting_type, int balanceNotificationThreshold);

std::string genSysParam_response_expireForecastThreshold_to_webhost(int Setting_type, int expireForecastThreshold);

std::string genSysParam_response_monthly_to_hourly_to_webhost(int Setting_type, int count, monthly_to_hourly_type tmp_montohour);

std::string genSysParam_response_CameraSite_to_webhost(int Setting_type, int cam_count, int camera_to_change[], int camera_bind[]);

std::string genspace_Counting_response_to_webhost(time_t time, int setting_Type, int zone_serial);

std::string genspace_Counting_confirm_to_webhost(time_t time, int setting_Type, int zone_serial);

std::string Enable_diasble_zone_confirm_to_webhost(int Setting_type, int zone_count, int zone_serial[]);

std::string Entry_Exit_zone_confirm_to_webhost(time_t time, int setting_Type, int entry_site_count, int exit_site_count, Zone zone);

std::string genSysParam_response_SiteName_to_webhost(int site_to_change[], int Setting_type, int site_count);

std::string genSysParam_response_Hourly_Charging_STD_to_webhost(int Setting_type, int rule_serial, bool non_step_rules);

std::string genSysParam_response_Hourly_Charging_STD_step_to_webhost(int Setting_type, int rule_serial, int block_serial);

std::string genSysParam_response_download_account_to_webhost(int Setting_type, temp_card current_temp_card);

std::string genSysParam_response_retainingdays_webhost(int Setting_type);

std::string genSysParam_response_group_inner_to_webhost(int Setting_type, int count, int sites_count[], int inner_group_serial[]);

std::string genSysParam_response_id_PresetSite_in_Site_Group_to_webhost(int site_to_change[], int Setting_type, int site_count);

std::string genSysParam_response_rule_name_monthly_to_webhost(int Setting_type, rule_name_monthly current_rule_name_monthly);

std::string genSysParam_response_rule_step_monthly_to_webhost(int Setting_type, rule_step_monthly current_rule_step_monthly);

std::string genSysParam_response_monthly_type_to_webhost(int Setting_type, monthly_type current_monthly_type);

int find_car_by_plate(int function, std::string plate);

std::vector <std::pair<std::string, std::vector<std::string>>> read_csv(std::string filename);

std::vector <std::pair<std::string, std::vector<std::string>>> read_site(std::string filename);

int get_int_from_string (std::string number);

int get_address_from_name (std::string number);

void print_screen_report(Proof proof);

int calculate_address_from_IP(char* IP);

#endif

#ifndef server_creat_function

bool initialize(char* _my_local_IP)
{ 
    char * pch;
    char server_address[25] = "";
    strcpy(server_address, _my_local_IP);
    pch = strtok (server_address,".");
    pch = strtok (NULL, ".");
    pch = strtok (NULL, ".");
    pch = strtok (NULL, ".");
    server_site.id = atoi(pch);
    server_site.address = atoi(pch);
    server_site.type = 1;
    strcpy(server_site.site_Address, _my_local_IP);
    server_site.status = 16777215;
    strcpy(server_site.db_name, "POS Controller");
    server_site.site_Status = "ffffff";
    int execute = 0;
    for (int i = 0; i < MAX_SITES; i++)
    {
        if(i == server_site.id)
        {
            sites.push_back(server_site);
        }
        else
        {
            Site_type site(mysql);
            execute = site.Select_Site_type_by_id(i);
            if(execute == 0)
            {
                if(site.id > 0 && site.id < 255 && site.gid > 0)
                {
                    site.address = calculate_address_from_IP(site.site_Address);
                    site.site_Status = "000000";
                    site.status = 0;
                }
                else
                {
                    site.id = -1;
                }
                sites.push_back(site);
            }
            else
            {
                finish_with_error(mysql, -1 * execute);
            }
        }
    }
    
    //print_sites_list(mysql, sites);
    
    black_list = read_db_black_list(mysql);
    //print_blacklist_list(mysql, black_list);
    
    rule_name_hourly_list = read_db_rule_name_hourly(mysql);
    //print_rule_name_hourly_list(mysql, rule_name_hourly_list);
    
    Zones = read_db_Zone(mysql);
    //print_zone_list(mysql, Zones);
    
    monthly_to_hourly_list = read_db_monthly_to_hourly(mysql);
    //print_monthly_to_hourly_list(mysql, monthly_to_hourly_list);
    
    memset(entry_event_by_Junction_Camera, 0, sizeof(entry_event_by_Junction_Camera));
    memset(exit_event_by_Junction_Camera, 0, sizeof(exit_event_by_Junction_Camera));
    memset(Camera_status, 0, sizeof(Camera_status));
    memset(Camera_snap_status, 0, sizeof(Camera_snap_status));
    All_Cameras = read_db_camera(mysql);
    //print_camera_list(mysql, All_Cameras);

    accountInfo_list = read_db_accountInfo(mysql);
    //print_accountinfo_list(mysql, accountInfo_list);
    
    account_state_list = read_db_account_state(mysql);
    //print_account_state_list(mysql, account_state_list);
    
    event_in_list = read_db_event_in(mysql);
    //print_event_in_list(mysql, event_in_list);
    
    event_out_list = read_db_event_out(mysql);
    //print_event_out_list(mysql, event_out_list);
    
    event_payment_list = read_db_event_payment(mysql);
    //print_event_payment_list(mysql, event_payment_list);
    
    temp_card_list = read_db_temp_card(mysql);
    //print_temp_card_list(mysql, temp_card_list);
    
    group_inner_list = read_db_group_inner(mysql);
    //print_group_inner_list(mysql, group_inner_list);
    
    monthly_type_list = read_db_monthly_type(mysql);
    //print_monthly_type_list(mysql, monthly_type_list);
    
    rule_name_monthly_list = read_db_rule_name_monthly(mysql);
    //print_rule_name_monthly_list(mysql, rule_name_monthly_list);
    
    rule_step_monthly_list = read_db_rule_step_monthly(mysql);
    //print_rule_step_monthly_list(mysql, rule_step_monthly_list);
    return true;
}

bool create_Server(const char* My_local_IP, int OPTION_VALUE)
{
    struct timeval tout;
    tout.tv_sec=3;
    tout.tv_usec=500000;
    std::cout << "Setting up server..." << std::endl;
    std::cout << "Creating server socket..." << std::endl;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << "Could not create socket...!\n";
    }
    // bind client ip to local network
    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = inet_addr(My_local_IP);
    localaddr.sin_port = 0;  // Any local port will do
    bind(webHost_Client_socket, (struct sockaddr *)&localaddr, sizeof(localaddr));
    //
    setsockopt(server_socket, SOL_SOCKET, SO_RCVTIMEO, &tout, sizeof(tout));
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &OPTION_VALUE, sizeof(OPTION_VALUE))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    if (server_socket == SOCKET_ERROR)
    {
            std::cout << "Create failed with error:  WSAGetLastError()" << "\n";
            close(server_socket);
            exit(EXIT_FAILURE);
    }
    return true;
}

bool create_Client(const char* WebHost_IP_ADDRESS, const char* WebHost_Client_PORT, const char* My_online_IP)
{
    bzero(&client_WEBHOST, sizeof(client_WEBHOST));
    webHost_Client_socket = socket(AF_INET , SOCK_STREAM , 0);
    // bind client ip to online network
    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = inet_addr(My_online_IP);
    localaddr.sin_port = 0;  // Any local port will do
    bind(webHost_Client_socket, (struct sockaddr *)&localaddr, sizeof(localaddr));
    //
    
    struct hostent* host;   
    host = gethostbyname(WebHost_IP_ADDRESS);
    in_addr * address = (in_addr * )host->h_addr;
    std::string ip_address = inet_ntoa(* address);
    std::cout << std::string(WebHost_IP_ADDRESS) << " (" << ip_address << ")\n";//ip_address.c_str()
    client_WEBHOST.sin_addr.s_addr = inet_addr(ip_address.c_str());
    client_WEBHOST.sin_family = AF_INET;
    client_WEBHOST.sin_port = htons(atoi(WebHost_Client_PORT));
    std::cout << "Connecting Web Host " << ip_address << ":" << std::string(WebHost_Client_PORT) << " ...\n";
    struct timeval tout;
    tout.tv_sec=0;
    tout.tv_usec=600000;
    setsockopt(webHost_Client_socket, SOL_SOCKET, SO_RCVTIMEO, &tout, sizeof(tout));
    setsockopt(webHost_Client_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &OPTION_VALUE, sizeof(OPTION_VALUE));
    if (webHost_Client_socket == INVALID_SOCKET)
    {
        return false;
    }
    if (connect(webHost_Client_socket, (struct sockaddr *)&client_WEBHOST,sizeof(client_WEBHOST)) < 0)
    {
        webHost_Client_socket = INVALID_SOCKET;
        webhost_reconnect_try = true;
        return false;
    }
    else
    {
        ssl = SSL_new(ctx);          /* create new SSL connection state */
        SSL_set_fd(ssl, webHost_Client_socket);     /* attach the socket descriptor */
        if(SSL_connect(ssl) == FAIL) /* perform the connection */
        {
            ERR_print_errors_fp(stderr);
            webHost_Client_socket = INVALID_SOCKET;
            webhost_reconnect_try = true;
            std::cout << "failed to Connect" << std::endl;
            return false;
        }
        std::cout << "Successfully Connected" << std::endl;
        if(initServiceBoard(&parser_host))
        {
            for(int i = 0; i < offline_mode_messages_list.size();i++)
            {
                usleep(70000);
                std::string bytes = offline_mode_messages_list[i];
                int iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
                if (iResult <= 0)
                {
                    std::cout << "Error sending offline mode messages list (index = " << i << ")." << std::endl;
                    return false;
                }
                else
                {
                    //std::cout << "sending offline mode messages list (index = " << i << ") OK." << std::endl;
                }
                
            }
	    web_host_locked = false;
            pthread_create(&client_WEBHOST_thread, NULL ,client_WEBHOST_Process, &parser_host);
            webhost_reconnect_try = false;
        }
        else
        {
            shutdown(webHost_Client_socket, SHUT_RDWR);
            close(webHost_Client_socket);
            SSL_CTX_free(ctx);        /* release context */
            webhost_reconnect_try = true;
            webHost_Client_socket = INVALID_SOCKET;
            return false;
        }
        return true;
    }
}

bool create_UDP_Server(const char* ipAddress, const char*  UDP_port)
{
    UDP_server_socket = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (UDP_server_socket < 0)
    {
        std::cout << "Error in setting Broadcast Socket\n";
        close(UDP_server_socket);
        return 0;
    }        
    udp_Sender.sin_family = AF_INET;
    udp_Sender.sin_port = htons(0);
    udp_Sender.sin_addr.s_addr = inet_addr(ipAddress);
    if (bind(UDP_server_socket, (sockaddr*)&udp_Sender, sizeof(udp_Sender)) < 0)
    {
        std::cout << "Error in BINDING";
        close(UDP_server_socket);
        return 0;
    }
    int Broadcast = 1;
    int status = setsockopt(UDP_server_socket, SOL_SOCKET, SO_BROADCAST, &Broadcast, sizeof(int) );
    std::cout << "Setsockopt Status = " << status << ".\n";
    pthread_create(&UDP_Server_Thread, NULL, UDP_process_server, NULL);
    return true;
}

#endif

#ifndef thread_functions

void* process_config(void * arg)
{
    bool first_time = true;
    char* Invite_Code;
    char* Online_IP;
    char* WebHost_IP;
    char* my_Online_IP_file;
    char* my_Local_IP_file;
    char* udp_port_file;
    char* QR_Code_IP;
    char* ETRE_Code_IP;
    char* Upload_IP;
    char* Upload_URL;
    char Invite_Code_db[10];
    char Online_IP_db[255];
    char WebHost_IP_db[255];
    char MY_Online_IP_file[25];
    char MY_Local_IP_file[25];
    char UDP_PORT_file[25];
    char QR_Code_IP_db[255];
    char ETRE_Code_IP_db[25];
    char Upload_IP_db[255];
    char Upload_URL_db[255];
    char line0[255] = "";
    char line1[255] = "";
    char line2[255] = "";
    char line3[255] = "";
    char line4[255] = "";
    char line5[255] = "";
    char line6[255] = "";
    char line7[255] = "";
    char line8[255] = "";
    char line9[255] = "";
    char line10[255] = "";
    std::ifstream file;
    std::string str = "";
    std::string all_text[11];
    int i = 0;
    while (true)
    {
	try
        {
            file.open (conf_txt);
            all_text[0] = "";
            all_text[1] = "";
            all_text[2] = "";
            all_text[3] = "";
            all_text[4] = "";
            all_text[5] = "";
            all_text[6] = "";
            all_text[7] = "";
            all_text[8] = "";
            all_text[9] = "";
            all_text[10] = "";
            i = 0;
            while(!file.eof())
            {
                std::getline(file,str);
                all_text[i] = str;
                i++;
            }
            file.close();
            memset(line0, 0, sizeof(line0));
            strcpy(line0, all_text[0].c_str());
            Invite_Code = strtok (line0,"=");
            Invite_Code = strtok (NULL,"=");
            strcpy(Invite_Code_db, Invite_Code);
            //printf("%s\n", Invite_Code_db);

            memset(line1, 0, sizeof(line1));
            strcpy(line1, all_text[1].c_str());
            Online_IP = strtok (line1,"=");
            Online_IP = strtok (NULL,"=");
            strcpy(Online_IP_db, Online_IP);
            //printf("%s\n", Online_IP_db);

            memset(line2, 0, sizeof(line2));
            strcpy(line2, all_text[2].c_str());
            WebHost_IP = strtok (line2,"=");
            WebHost_IP = strtok (NULL,"=");
            strcpy(WebHost_IP_db, WebHost_IP);
            //printf("%s\n", WebHost_IP_db);

            memset(line3, 0, sizeof(line3));
            strcpy(line3, all_text[3].c_str());
            my_Online_IP_file = strtok (line3,"=");
            my_Online_IP_file = strtok (NULL,"=");
            strcpy(MY_Online_IP_file, my_Online_IP_file);
            //printf("%s\n", MY_Online_IP_file);

            memset(line4, 0, sizeof(line4));
            strcpy(line4, all_text[4].c_str());
            my_Local_IP_file = strtok (line4,"=");
            my_Local_IP_file = strtok (NULL,"=");
            strcpy(MY_Local_IP_file, my_Local_IP_file);
            //printf("%s\n", MY_Local_IP_file);

            memset(line5, 0, sizeof(line5));
            strcpy(line5, all_text[5].c_str());
            udp_port_file = strtok (line5,"=");
            udp_port_file = strtok (NULL,"=");
            strcpy(udp_port, udp_port_file);
            //printf("%s\n", udp_port);

            memset(line6, 0, sizeof(line6));
            strcpy(line6, all_text[6].c_str());
            QR_Code_IP = strtok (line6,"=");
            QR_Code_IP = strtok (NULL,"=");
            strcpy(QR_Code_IP_db, QR_Code_IP);
            //printf("%s\n", QR_Code_IP);

            memset(line7, 0, sizeof(line7));
            strcpy(line7, all_text[7].c_str());
            ETRE_Code_IP = strtok (line7,"=");
            ETRE_Code_IP = strtok (NULL,"=");
            strcpy(ETRE_Code_IP_db, ETRE_Code_IP);
            //printf("%s\n", ETRE_Code_IP_db);

            memset(line8, 0, sizeof(line8));
            strcpy(line8, all_text[8].c_str());
            Upload_IP = strtok (line8,"=");
            Upload_IP = strtok (NULL,"=");
            strcpy(Upload_IP_db, Upload_IP);
            //printf("%s\n", Upload_IP_db);

            memset(line9, 0, sizeof(line9));
            strcpy(line9, all_text[9].c_str());
            Upload_URL = strtok (line9,"=");
            Upload_URL = strtok (NULL,"=");
            strcpy(Upload_URL_db, Upload_URL);
            //printf("%s\n", Upload_URL_db);
            if(first_time)
            {
                strcpy(Current_Settings.invite_code, Invite_Code_db);
                strcpy(Current_Settings.online_marjor_ip, Online_IP_db);
                strcpy(Current_Settings.online_minor_ip, WebHost_IP_db);
                strcpy(My_Online_IP, MY_Online_IP_file);
                strcpy(My_local_IP_port, MY_Local_IP_file);

                std::cout << "config:\n";
                std::cout << "my online ip = " << std::string(My_Online_IP) << ".\n";

                char ip_port_full[20];
                strcpy(ip_port_full, My_local_IP_port);
                char* dword = strtok (ip_port_full,":");
                strcpy(My_local_IP, dword);
                dword = strtok (NULL,":");
                strcpy(default_port, dword);
                std::cout << "my local ip = " << std::string(My_local_IP) << ".\n";
                std::cout << "default port = " << std::string(default_port) << ".\n";

                char site_prefix_full[20];
                char site_prefix[20];
                strcpy(site_prefix_full, My_local_IP_port);
                char* ptr = strtok (site_prefix_full,".");
                strcpy(site_prefix, ptr);
                strcat(site_prefix, ".");
                ptr = strtok (NULL,".");
                strcat(site_prefix, ptr);
                strcat(site_prefix, ".");
                ptr = strtok (NULL,".");
                strcat(site_prefix, ptr);
                strcpy(my_ip_prefix, site_prefix);
                std::cout << "site_prefix = " << std::string(my_ip_prefix) << ".\n";
                std::cout << "udp port = " << std::string(udp_port) << ".\n";

                strcpy(Current_Settings.site_prefix, my_ip_prefix);
                strcpy(Current_Settings.qrcode_url, QR_Code_IP_db);
                strcpy(Current_Settings.etrecord_ip, ETRE_Code_IP_db);
                strcpy(Current_Settings.uploadip, Upload_IP_db);
                strcpy(Current_Settings.uploadurl, Upload_URL_db);
                Current_Settings.update_Setting();

                check_image_path(std::string(Current_Settings.image_dir));
                std::cout << "readed successfully\n";
                first_time = false;
            }
            else
            {
                if(strcmp(WebHost_IP_db, Current_Settings.online_minor_ip) != 0)
                {
                    std::cout << "Current_Settings.online_minor_ip is changed\n";
                    std::cout << std::string(WebHost_IP_db) << ".\n";
                    std::cout << std::string(Current_Settings.online_minor_ip) << ".\n";
                    strcpy(Current_Settings.online_minor_ip, WebHost_IP_db);
                    Current_Settings.update_Setting();
                    conf_has_changed = true;
                }
                else if(strcmp(My_local_IP_port, MY_Local_IP_file) != 0)
                {
                    std::cout << "Offline server IP is changed\n";
                    std::cout << std::string(My_local_IP_port) << ".\n";
                    std::cout << std::string(MY_Local_IP_file) << ".\n";
                    strcpy(My_local_IP_port, MY_Local_IP_file);

                    std::cout << "\nconfig:\n";
                    char ip_port_full[20];
                    strcpy(ip_port_full, My_local_IP_port);
                    char* dword = strtok (ip_port_full,":");
                    strcpy(My_local_IP, dword);
                    dword = strtok (NULL,":");
                    strcpy(default_port, dword);
                    std::cout << "my ip = " << std::string(My_local_IP) << ".\n";
                    std::cout << "default port = " << std::string(default_port) << ".\n";

                    char site_prefix_full[20];
                    char site_prefix[20];
                    strcpy(site_prefix_full, My_local_IP_port);
                    char* ptr = strtok (site_prefix_full,".");
                    strcpy(site_prefix, ptr);
                    strcat(site_prefix, ".");
                    ptr = strtok (NULL,".");
                    strcat(site_prefix, ptr);
                    strcat(site_prefix, ".");
                    ptr = strtok (NULL,".");
                    strcat(site_prefix, ptr);
                    strcpy(my_ip_prefix, site_prefix);
                    std::cout << "site_prefix = " << std::string(my_ip_prefix) << ".\n";
                    std::cout << "udp port = " << std::string(udp_port) << ".\n";

                    conf_has_changed = true;
                }
                else
                {
                    conf_has_changed = false;
                }
            }
            sleep(1);
        }
        catch(...)
        {
            fprintf(stderr, "Unkown error in process_config...!\n");
            pthread_exit(NULL);
        }
    } 
}

void* UDP_process_server(void * arg)
{
    try
    {
        std::string buffer = "";
        int port_number = atoi(default_port); 
        udp_Receiver.sin_family = AF_INET;
        udp_Receiver.sin_port = htons(port_number);
        udp_Receiver.sin_addr.s_addr = inet_addr("255.255.255.255");
        int k = 0;
        while (1)
        {
            k++;
            buffer = gen_ServiceBoard_TimeSpaces_Msg();
            sendto(UDP_server_socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0, (struct sockaddr*)&udp_Receiver, sizeof(udp_Receiver));
            sleep(3);
        }
    }
    catch(...)
    {
        fprintf(stderr, "Unkown error in UDP_process_server...!\n");
    }
}

void* client_WEBHOST_Process(void * arg)
{
    try
    {
        int zone_log_counter = 0;
        int zone_log_index = 0;
        int recv_tries = 0;
        heartbeatIndex = 0;
        DashouParser *parser_host = (DashouParser*) arg;
        std::cout << "Client Web Host Started" << std::endl;
        unsigned char WebHost_buffer[DEFAULT_BUFLEN] = "";
        int bytesRec = 0;
        std::string bytes = "";
        while (webHost_Client_socket != INVALID_SOCKET)
        {
            recv_tries = 0;
            while(recv_tries < 5 && webHost_Client_socket != INVALID_SOCKET)
            {

                while(web_host_locked)
                {
                    recv_tries = 0;
                }
                bytesRec = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                parser_host->parse2(WebHost_buffer);
                if (bytesRec <= 0)
                {
                    if(recv_tries == 4)
                    {
                        //std::cout << "Web Host no order." << std::endl;
                    } 
                    recv_tries++;
                }
                else if (bytesRec > 16)
                {
                    bytes = gen_ServiceBoard_ACK_Msg(parser_host->serial, parser_host->function, 0);
                    int iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
                    Handle_webhost_received_data(WebHost_buffer,parser_host);
                    recv_tries = 0;
                }

            }
            usleep(600000 * (5 - recv_tries));
            if(webHost_Client_socket == INVALID_SOCKET) break;
            if(!heartbeat(zone_log_counter, zone_log_index, parser_host))
            {
                close(webHost_Client_socket);
                webHost_Client_socket = INVALID_SOCKET;
                webhost_reconnect_try = true;
                std::cout << "WebHost is Disconnected \n";
                break;                  
            }
            zone_log_counter++;
            if(zone_log_counter == 10) 
            {
                zone_log_counter = 0;  
                zone_log_index++;
            }
            if(zone_log_index == 16) 
            {
                zone_log_index = 0;
            }
        }
        std::cout << "thread exit while loop... \n" ;
        std::cout.flush();
        webHost_Client_socket = INVALID_SOCKET;
        webhost_reconnect_try = true;
        pthread_exit(NULL);
    }
    catch(...)
    {
        fprintf(stderr, "Unkown error in client_WEBHOST_Process...!\n");
        webHost_Client_socket = INVALID_SOCKET;
        webhost_reconnect_try = true;
    }
}

void* receive_STD_step(void * arg)
{
    web_host_locked = true;
    DashouParser *parser_host = (DashouParser*) arg;
    unsigned char webhost_buffer[DEFAULT_BUFLEN] = "";
    int iResult = 0;
    std::string report = "";
    std::string buffer = "";
    int bytesRec = 0;
    while (webHost_Client_socket != INVALID_SOCKET)
    {
        bytesRec = SSL_read(ssl, webhost_buffer, DEFAULT_BUFLEN);
        parser_host->parse2(webhost_buffer);
        while(!web_host_client_send_confirm_data);
        if (bytesRec <= 0)
        {
            std::cout << "break receive STD step...\n";
            break;                   
        }
        else if (bytesRec > 100)
        {
            std::string bytes = gen_ServiceBoard_ACK_Msg(parser_host->serial, parser_host->function, 0);
            int iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
            usleep(1000);
            if(parser_host->Setting_type == 33 || parser_host->Setting_type == 32801)
            {
                report = "";
                int Setting_type = parser_host->Setting_type;
                rule_step_hourly_type rule_step_hourly(mysql);
                rule_step_hourly.gid = Current_Settings.gid;
                rule_step_hourly.rule_serial = webhost_buffer[19];
                rule_step_hourly.block_serial = webhost_buffer[20];
                rule_step_hourly.type = webhost_buffer[21];
                if(webhost_buffer[22] == 0xff) webhost_buffer[22] = 0;
                if(webhost_buffer[23] == 0xff) webhost_buffer[23] = 1;
                if(webhost_buffer[24] == 0xff) webhost_buffer[24] = 1;
                rule_step_hourly.starttime = parser_host->char_to_time_t(webhost_buffer[22], webhost_buffer[23], webhost_buffer[24], webhost_buffer[25], webhost_buffer[26], webhost_buffer[27]);
                if(webhost_buffer[28] == 0xff) webhost_buffer[28] = 0;
                if(webhost_buffer[29] == 0xff) webhost_buffer[29] = 1;
                if(webhost_buffer[30] == 0xff) webhost_buffer[30] = 1;
                rule_step_hourly.endtime = parser_host->char_to_time_t(webhost_buffer[28], webhost_buffer[29], webhost_buffer[30], webhost_buffer[31], webhost_buffer[32], webhost_buffer[33]);
                rule_step_hourly.duration = dashou.get_X4_Number(webhost_buffer[34], webhost_buffer[35], webhost_buffer[36], webhost_buffer[37]);
                rule_step_hourly.relation = dashou.get_X2_Number(webhost_buffer[38], webhost_buffer[39]);
                rule_step_hourly.deduct = webhost_buffer[40];
                rule_step_hourly.cross_period = webhost_buffer[41];
                rule_step_hourly.sum = dashou.get_X4_Number(webhost_buffer[42], webhost_buffer[43], webhost_buffer[44], webhost_buffer[45]);
                rule_step_hourly.max_sum = dashou.get_X4_Number(webhost_buffer[46], webhost_buffer[47], webhost_buffer[48], webhost_buffer[49]);
                rule_step_hourly.next_serial = webhost_buffer[50];
                rule_step_hourly.start_week = webhost_buffer[51];
                rule_step_hourly.end_week = webhost_buffer[52];
                rule_step_hourly.reserve[0] = webhost_buffer[53];
                rule_step_hourly.reserve[1] = webhost_buffer[54];
                for(int i = 0; i < 64; i++)
                {
                    rule_step_hourly.brief[i] = webhost_buffer[55 + i];
                }
                rule_step_hourly._operator = webhost_buffer[119];
                rule_step_hourly.Update_rule_step_hourly_type();
                report = log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                buffer = "";
                buffer = genSysParam_response_Hourly_Charging_STD_step_to_webhost(Setting_type, rule_step_hourly.rule_serial, rule_step_hourly.block_serial);
                SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                //iResult = SSL_read(ssl, webhost_buffer, DEFAULT_BUFLEN, 0);
                //if (iResult < 0)
                //{
                //    std::cout << "Error recv Web Host Hourly Charging STD step ACK...\n";
                //}
                //parser_host->parse2(webhost_buffer);
                //report += log_udp.ACK_webhost_messege_Builder(parser_host);
                log_udp.messege_Sender(report);
            }
            else if(parser_host->Setting_type == 34)
            {
                report = "";
                int Setting_type = parser_host->Setting_type;
                int rule_serial = webhost_buffer[19];
                bool non_step_rules = false;
                if(webhost_buffer[20] == 0xff && webhost_buffer[21] == 0xff)
                {
                    non_step_rules = true;
                }
                else
                {
                    if(webhost_buffer[20] == 0xff)
                    {
                        rule_name_hourly_list[rule_serial].flag = 0;
                    }
                    else
                    {
                        rule_name_hourly_list[rule_serial].flag = 1;
                    }
                    for(int i = 0; i < 50; i++)
                    {
                        rule_name_hourly_list[rule_serial].name[i] = webhost_buffer[20 + i];
                    }
                    rule_name_hourly_list[rule_serial].limit_enable = webhost_buffer[84];
                    rule_name_hourly_list[rule_serial].limit_sum = dashou.get_X4_Number(webhost_buffer[85],webhost_buffer[86],webhost_buffer[87],webhost_buffer[88]);
                    strcpy(rule_name_hourly_list[rule_serial].fixed_time ,dashou.Print_time(dashou.char_to_time_t(0, 1, 1, webhost_buffer[92],webhost_buffer[93],webhost_buffer[94])).c_str());
                    rule_name_hourly_list[rule_serial].within_duration = dashou.get_X4_Number(webhost_buffer[95],webhost_buffer[96],webhost_buffer[97],webhost_buffer[98]);
                    rule_name_hourly_list[rule_serial].tolerance = dashou.get_X2_Number(webhost_buffer[99],webhost_buffer[100]);
                    for(int i = 0; i < 255; i++)
                    {
                        rule_name_hourly_list[rule_serial].remark[i] = webhost_buffer[101 + i];
                    }
                    rule_name_hourly_list[rule_serial]._operator = webhost_buffer[357];
                }
                report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                rule_name_hourly_list[rule_serial].Update_rule_name_hourly_type();
                buffer = "";
                buffer = genSysParam_response_Hourly_Charging_STD_to_webhost(Setting_type, rule_serial, non_step_rules);
                SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                iResult = SSL_read(ssl, webhost_buffer, DEFAULT_BUFLEN);
                if (iResult < 0)
                {
                    std::cout << "Error recv Web Host Hourly Charging STD ACK...\n";
                }
                report += log_udp.ACK_webhost_messege_Builder(parser_host);
                log_udp.messege_Sender(report);
                //break; // for sync condition 20-12-2020
            }
        }
    }
    web_host_locked = false;
}

void* receive_STD_montly_step(void * arg)
{
    DashouParser *parser_host = (DashouParser*) arg;
    unsigned char webhost_buffer[DEFAULT_BUFLEN] = "";
    int iResult = 0;
    std::string report = "";
    std::string buffer = "";
    int bytesRec = 0;
    while (webHost_Client_socket != INVALID_SOCKET)
    {
        bytesRec = SSL_read(ssl, webhost_buffer, DEFAULT_BUFLEN);
        parser_host->parse2(webhost_buffer);
        while(!web_host_client_send_confirm_data);
        if (bytesRec <= 0)
        {
            std::cout << "break receive STD step...\n";
            break;                   
        }
        else if (bytesRec > 16)
        {
            report = "";
            buffer = "";
            std::string bytes = gen_ServiceBoard_ACK_Msg(parser_host->serial, parser_host->function, 0);
            iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
            if(parser_host->Setting_type == 48 || parser_host->Setting_type == 32816)
            {
                int Setting_type = parser_host->Setting_type;
                rule_step_monthly current_rule_step_monthly(mysql);
                current_rule_step_monthly.rule_serial = webhost_buffer[19];
                current_rule_step_monthly.step_serial = webhost_buffer[20];
                current_rule_step_monthly.gid = Current_garage.gid;
                current_rule_step_monthly.flag = webhost_buffer[21];
                current_rule_step_monthly.max_units = dashou.get_X2_Number(webhost_buffer[22], webhost_buffer[23]);
                current_rule_step_monthly.duration = dashou.get_X4_Number(webhost_buffer[24], webhost_buffer[25], webhost_buffer[26], webhost_buffer[27]);
                current_rule_step_monthly.unit_sum = dashou.get_X4_Number(webhost_buffer[28], webhost_buffer[29], webhost_buffer[30], webhost_buffer[31]);
                buffer = genSysParam_response_rule_step_monthly_to_webhost(Setting_type, current_rule_step_monthly);
                SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                current_rule_step_monthly.createtime = time(0);
                temp_rule_step_monthly_list.push_back(current_rule_step_monthly);
                //current_rule_step_monthly.Insert_Update_rule_step_monthly();
                //iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN, 0);
                //if (iResult < 0)
                //{
                //    std::cout << "Error recv Web Host one proof on car ACK...\n";
                //}
                //parser_host->parse2(WebHost_buffer);
                //report += log_udp.ACK_webhost_messege_Builder(parser_host);
                //log_udp.messege_Sender(report); 
            }
            else if(parser_host->Setting_type == 49)
            {
                int Setting_type = parser_host->Setting_type;
                rule_name_monthly current_rule_name_monthly(mysql);
                current_rule_name_monthly.gid = Current_garage.gid;
                if(webhost_buffer[20] == 0xff && webhost_buffer[21] == 0xff)
                {
                    current_rule_name_monthly.Select_rule_name_monthly_by_serial(webhost_buffer[19], Current_garage.gid);
                    if(current_rule_name_monthly.Delete_rule_name_monthly())
                    {
                        //std::cout << "rule name monthly setting:\n";
                        //std::cout << "rule name monthly " + std::to_string(webhost_buffer[19]) + " Deleted successfully.\n";
                    }
                    current_rule_name_monthly.rule_serial = webhost_buffer[19];
                    for(int i = 0; i < 64; i++)
                    {
                        current_rule_name_monthly.name[i] = webhost_buffer[20 + i];
                    }
                    for(int i = 0; i < 256; i++)
                    {
                        current_rule_name_monthly.remark[i] = webhost_buffer[84 + i];
                    }
                    current_rule_name_monthly.createtime = time(0);
                }
                else
                {
                    current_rule_name_monthly.rule_serial = webhost_buffer[19];
                    for(int i = 0; i < 50; i++)
                    {
                        current_rule_name_monthly.name[i] = webhost_buffer[20 + i];
                    }
                    for(int i = 0; i < 200; i++)
                    {
                        current_rule_name_monthly.remark[i] = webhost_buffer[84 + i];
                    }
                    current_rule_name_monthly.createtime = time(0);
                    current_rule_name_monthly.Insert_Update_rule_name_monthly();
                    //std::cout << "rule name monthly setting:\n";
                    //printf("gid\trule_sr\tname\t\tremark\tflag\toper\tcreate time\n");
                    //printf("%ld\t%ld\t%s\t%s\t\t%d\t%d\t%s\n",
                    //    current_rule_name_monthly.gid,
                    //    current_rule_name_monthly.rule_serial,
                    //    current_rule_name_monthly.name,
                    //    current_rule_name_monthly.remark,
                    //    current_rule_name_monthly.flag,
                    //    current_rule_name_monthly._operator,
                    //    dashou.Print_time(current_rule_name_monthly.createtime).c_str());
                }
                buffer = genSysParam_response_rule_name_monthly_to_webhost(Setting_type, current_rule_name_monthly);
                SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                //web_host_locked = true;
                //iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN, 0);
                //web_host_locked = false;
                //if (iResult < 0)
                //{
                //    std::cout << "Error recv Web Host one proof on car ACK...\n";
                //}
                //parser_host->parse2(WebHost_buffer);
                //report += log_udp.ACK_webhost_messege_Builder(parser_host);
                //log_udp.messege_Sender(report); 
                break;
            }
        }
    }
    web_host_locked = false;
    if(temp_rule_step_monthly_list.size() > 0)
    {
        temp_rule_step_monthly_list[0].Delete_all_rule_step_monthly(Current_garage.gid, temp_rule_step_monthly_list[0].rule_serial);
    
        for(int i = 0; i < temp_rule_step_monthly_list.size(); i++)
        {
            temp_rule_step_monthly_list[i].Insert_Update_rule_step_monthly();
        }
        temp_rule_step_monthly_list.clear();
        rule_step_monthly_list.clear();
        rule_step_monthly_list = read_db_rule_step_monthly(mysql);
    }
}

void* receive_accounts(void * arg)
{
    web_host_locked = true;
    DashouParser *parser_host = (DashouParser*) arg;
    unsigned char webhost_buffer[DEFAULT_BUFLEN] = "";
    int iResult = 0;
    std::string report = "";
    std::string buffer = "";
    int bytesRec = 0;
    while (webHost_Client_socket != INVALID_SOCKET)
    {
        bytesRec = SSL_read(ssl, webhost_buffer, DEFAULT_BUFLEN);
        parser_host->parse2(webhost_buffer);
        while(!web_host_client_send_confirm_data);
        if (bytesRec <= 0)
        {
            std::cout << "break receive accounts...\n";
            break;                   
        }
        else if (bytesRec > 100)
        {
            std::string bytes = gen_ServiceBoard_ACK_Msg(parser_host->serial, parser_host->function, 0);
            int iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
            usleep(1000);
            if(parser_host->Setting_type == 25)
            {
                report = "";
                int Setting_type = parser_host->Setting_type;
                temp_card current_temp_card(mysql);
                current_temp_card.id = get_temp_card_insert_id();
                account_state current_account_state(mysql);
                current_temp_card.operate_type = webhost_buffer[19];
                current_temp_card.ticket_type = webhost_buffer[20];
                for(int i = 0; i < 19; i++)
                {
                    current_temp_card.ticket[i] = webhost_buffer[21 + i];
                }
                for(int i = 0; i < 12; i++)
                {
                    current_temp_card.plate[i] = webhost_buffer[40 + i];
                }
                current_temp_card.account_state = webhost_buffer[52];
                current_temp_card.parking_type = webhost_buffer[53];
                current_temp_card.present_type = webhost_buffer[54];
                current_temp_card.in_time = dashou.char_to_time_t(webhost_buffer[55], webhost_buffer[56], webhost_buffer[57], webhost_buffer[58], webhost_buffer[59], webhost_buffer[60]);
                current_temp_card.pay_time = dashou.char_to_time_t(webhost_buffer[61], webhost_buffer[62], webhost_buffer[63], webhost_buffer[64], webhost_buffer[65], webhost_buffer[66]);
                current_temp_card.inner_intime = dashou.char_to_time_t(webhost_buffer[67], webhost_buffer[68], webhost_buffer[69], webhost_buffer[70], webhost_buffer[71], webhost_buffer[72]);
                current_temp_card.inner_outtime = dashou.char_to_time_t(webhost_buffer[73], webhost_buffer[74], webhost_buffer[75], webhost_buffer[76], webhost_buffer[77], webhost_buffer[78]);
                current_temp_card.insite = webhost_buffer[79];
                current_temp_card.charge_site = webhost_buffer[80];
                current_temp_card.inner_insite = webhost_buffer[81];
                current_temp_card.inner_outsite = webhost_buffer[82];
                current_temp_card.coupon_total_time = dashou.get_X4_Number(webhost_buffer[83], webhost_buffer[84], webhost_buffer[85], webhost_buffer[86]);
                current_temp_card.coupon_total_sum = dashou.get_X4_Number(webhost_buffer[87], webhost_buffer[88], webhost_buffer[89], webhost_buffer[90]);
                current_temp_card.limit_sum = dashou.get_X4_Number(webhost_buffer[91], webhost_buffer[92], webhost_buffer[93], webhost_buffer[94]);
                current_temp_card.limit_time = dashou.char_to_time_t(webhost_buffer[95], webhost_buffer[96], webhost_buffer[97], webhost_buffer[98], webhost_buffer[99], webhost_buffer[100]);
                current_temp_card.paid_sum = dashou.get_X4_Number(webhost_buffer[101], webhost_buffer[102], webhost_buffer[103], webhost_buffer[104]);
                for(int i = 0; i < 12; i++)
                {
                    current_temp_card.online_order[i] = webhost_buffer[105 + i];
                }
                current_temp_card.hour_ticket_type = webhost_buffer[117];
                for(int i = 0; i < 19; i++)
                {
                    current_temp_card.hour_ticket_num[i] = webhost_buffer[118 + i];
                }
                current_temp_card.access_group = webhost_buffer[138];//dashou.get_X2_Number(webhost_buffer[137], webhost_buffer[138]);
                current_temp_card.start_time = dashou.char_to_time_t(webhost_buffer[139], webhost_buffer[140], webhost_buffer[141], webhost_buffer[142], webhost_buffer[143], webhost_buffer[144]);
                current_temp_card.end_time = dashou.char_to_time_t(webhost_buffer[145], webhost_buffer[146], webhost_buffer[147], webhost_buffer[148], webhost_buffer[149], webhost_buffer[150]);
                current_temp_card.prepaid_balance = dashou.get_X4_Number(webhost_buffer[151], webhost_buffer[152], webhost_buffer[153], webhost_buffer[154]);
                current_temp_card.prepaid_account_id = dashou.get_X2_Number(webhost_buffer[155], webhost_buffer[156]);
                current_temp_card.monthly_type = webhost_buffer[157];
                current_temp_card.lots_group = dashou.get_X2_Number(webhost_buffer[158], webhost_buffer[159]);
                current_temp_card.ticket_lpbind = webhost_buffer[160];
                current_temp_card.inner_group = webhost_buffer[161];
                current_temp_card.time_group = webhost_buffer[162];
                for(int i = 0; i < 16; i++)
                {
                    current_temp_card.lot_name[i] = webhost_buffer[163 + i];
                }
                current_temp_card.prepaid_charge_rule = webhost_buffer[179];
                current_temp_card.monthly_charge_rule = webhost_buffer[180];
                for(int i = 0; i < 16; i++)
                {
                    current_temp_card.photo_id[i] = webhost_buffer[181 + i];
                }
                for(int i = 0; i < 16; i++)
                {
                    current_temp_card.owner_name[i] = webhost_buffer[197 + i];
                }
                for(int i = 0; i < 16; i++)
                {
                    current_temp_card.phone[i] = webhost_buffer[213 + i];
                }
                for(int i = 0; i < 32; i++)
                {
                    current_temp_card.email[i] = webhost_buffer[229 + i];
                }
                for(int i = 0; i < 64; i++)
                {
                    current_temp_card.addr[i] = webhost_buffer[261 + i];
                }
                for(int i = 0; i < 64; i++)
                {
                    current_temp_card.description[i] = webhost_buffer[325 + i];
                }
                for(int i = 0; i < 64; i++)
                {
                    current_temp_card.add_info1[i] = webhost_buffer[389 + i];
                }
                for(int i = 0; i < 64; i++)
                {
                    current_temp_card.add_info2[i] = webhost_buffer[453 + i];
                }
                current_temp_card.Insert_Update_Temp_Account();
                recv_temp_card_list.push_back(current_temp_card);
                report = log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                buffer = "";
                buffer = genSysParam_response_download_account_to_webhost(Setting_type, current_temp_card);
                SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                //                iResult = SSL_read(ssl, webhost_buffer, DEFAULT_BUFLEN, 0);
//                if (iResult < 0)
//                {
//                    std::cout << "Error recv Web Host Entry Exit zone ACK...\n";
//                }
//                parser_host->parse2(webhost_buffer);
//                report += log_udp.ACK_webhost_messege_Builder(parser_host);
//                log_udp.messege_Sender(report);
            }
        }
    }
    web_host_locked = false;
    temp_card_to_account(recv_temp_card_list);
}

void* receive_monthly_type(void * arg)
{
    web_host_locked = true;
    DashouParser *parser_host = (DashouParser*) arg;
    unsigned char webhost_buffer[DEFAULT_BUFLEN] = "";
    int iResult = 0;
    std::string report = "";
    std::string buffer = "";
    int bytesRec = 0;
    while (webHost_Client_socket != INVALID_SOCKET)
    {
        bytesRec = SSL_read(ssl, webhost_buffer, DEFAULT_BUFLEN);
        parser_host->parse2(webhost_buffer);
        while(!web_host_client_send_confirm_data);
        if (bytesRec <= 0)
        {
            std::cout << "break receive monthly type...\n";
            break;                   
        }
        else if (bytesRec > 100)
        {
            std::string bytes = gen_ServiceBoard_ACK_Msg(parser_host->serial, parser_host->function, 0);
            int iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
            usleep(1000);
            if(parser_host->Setting_type == 51)
            {
                report = "";
                int Setting_type = parser_host->Setting_type;
                monthly_type current_monthly_type(mysql);
                current_monthly_type.id = webhost_buffer[19];
                current_monthly_type.aid = get_aid_monthly_type_from_id(current_monthly_type.id);
                current_monthly_type.gid = Current_garage.gid;
                current_monthly_type.type = (webhost_buffer[20] == 0xff) ? 4 : webhost_buffer[20];
                current_monthly_type.flag = !(webhost_buffer[20] == 0xff);
                current_monthly_type.access_group_id = webhost_buffer[21];
                current_monthly_type.time_group_id = webhost_buffer[22];
                current_monthly_type.inner_group_id = webhost_buffer[23];
                current_monthly_type.monthly_charge_rule = webhost_buffer[24];
                current_monthly_type.prepaid_charge_rule = webhost_buffer[25];
                current_monthly_type.vip_flag = webhost_buffer[26];
                current_monthly_type.reserved = 0xffff;
                current_monthly_type.lotgroup_countingtype = webhost_buffer[27];
                current_monthly_type.expires = webhost_buffer[28];
                current_monthly_type.createtime = time(0);
                for(int i = 0; i < 64; i++)
                {
                    current_monthly_type.name[i]= webhost_buffer[29 + i];
                }
                if(webhost_buffer[93] == 0x2d && webhost_buffer[94] == 0x2d)
                {
                    strcpy(current_monthly_type.description, "--");
                }
                else
                {
                    for(int i = 0; i < 255; i++)
                    {
                        current_monthly_type.description[i]= webhost_buffer[93 + i];
                    }
                }
                current_monthly_type._operator = webhost_buffer[349];
                temp_monthly_type_list.push_back(current_monthly_type);
                //current_monthly_type.Insert_Update_monthly_type();
                //std::cout << "monthly type setting:\n";
                //printf("aid\tid\tgid\ttype\tagid\ttgid\tigid\tmcr\tpcr\tvipf\tlotc\texp\tname\t\tdesc\tflag\toper\n");
                //printf("%ld\t%d\t%ld\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%s\t%d\t%d\t%s\n",
                //    current_monthly_type.aid,
                //    current_monthly_type.id,
                //    current_monthly_type.gid,
                //    current_monthly_type.type,
                //    current_monthly_type.access_group_id,
                //    current_monthly_type.time_group_id,
                //    current_monthly_type.inner_group_id,
                //    current_monthly_type.monthly_charge_rule,
                //    current_monthly_type.prepaid_charge_rule, 
                //    current_monthly_type.vip_flag,
                //    current_monthly_type.lotgroup_countingtype,
                //    current_monthly_type.expires,
                //    current_monthly_type.name,
                //    current_monthly_type.description,
                //    current_monthly_type.flag,
                //    current_monthly_type._operator,
                //    dashou.Print_time(current_monthly_type.createtime).c_str());
                buffer = "";
                buffer = genSysParam_response_monthly_type_to_webhost(Setting_type, current_monthly_type);
                SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                //iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                //web_host_locked = false;
                //if (iResult < 0)
                //{
                //    std::cout << "Error recv Web Host one proof on car ACK...\n";
                //}
                //parser_host->parse2(WebHost_buffer);
                //report += log_udp.ACK_webhost_messege_Builder(parser_host);
                //log_udp.messege_Sender(report); 
            }
        }
    }
    web_host_locked = false;
    for(int i = 0; i < temp_monthly_type_list.size(); i++)
    {
        temp_monthly_type_list[i].Insert_Update_monthly_type();
    }
    temp_monthly_type_list.clear();
    monthly_type_list.clear();
    monthly_type_list = read_db_monthly_type(mysql);
}

void* main_Camera_Process(void * arg)
{
    check_image_path(Current_Settings.image_dir);
    int cam_address = 0;
    std::string camera_device_address = "";
    bool m_bSubIntelligent = false;
    int *ip_pass = (int*)malloc(sizeof(*ip_pass));
    while(1)
    {
        try
        {
            All_Cameras.clear();
            All_Cameras = read_db_camera(mysql);
            for(int i = 0; i < All_Cameras.size(); i++)
            {
                if(All_Cameras[i].ip[0] != 0)
                {
                    std::string cam_ip(All_Cameras[i].ip);
                    cam_address = std::stoi(cam_ip);
                    *ip_pass = cam_address;
                    camera_device_address = std::string(Current_Settings.site_prefix) + std::string(".") + cam_ip;
                    if(Camera_status[cam_address] == 0)
                    {
                        try
                        {
                            pthread_create(&my_Camera_Thread[cam_address], NULL , Camera_Process, ip_pass);
                        }
                        catch(...)
                        {
                            std::cout << "Unkown error while create thread for Camera #" << cam_address << "..!\n";
                        }
                    }
                    sleep(1);
                    if(Camera_snap_status[cam_address] == 0)
                    {
                        try
                        {
                            pthread_create(&my_Camera_snaps_Thread[cam_address], NULL , Camera_snap_Process, ip_pass);
                        }
                        catch(...)
                        {
                            std::cout << "Unkown error while create thread for snap Camera #" << cam_address << "..!\n";
                        }
                    }
                    sleep(1);
                }
            }
        }
        catch(...)
        {
            std::cout << "Unkown error in main_Camera_Process..!\n";
        }
    }
}

void* Camera_Process(void * arg)
{
    int cam_address = *((int *) arg);
    int byte_Rec = 0;
    char buffer[BUFFER_SIZE] = "";
    std::string web_buffer = "";
    int iResult = 0;
    unsigned char client_buffer[DEFAULT_BUFLEN] = "";
    Camera_type current_Camera(mysql);
    Site_type current_site(mysql);
    current_Camera.Select_Camera_type_by_address(cam_address);
    current_site.Select_Site_type_by_id(current_Camera.sites_binded[0]);
    std::string camera_device_address = std::string(Current_Settings.site_prefix) + std::string(".") + std::to_string(cam_address);
    std::string listen_event = std::string(HTTP_request_URL_HEADER) + EVENT_LISTENNING_HTTP_request + OPTION_HTTP_request_PREV_HOST + camera_device_address + OPTION_HTTP_request_APRE_HOST + std::string(HTTP_request_TAIL);
    Cameras[cam_address] = create_socket();
    if(socket_connect(Cameras[cam_address], camera_device_address.c_str(), "80") >= 0)
    {
        send(Cameras[cam_address], listen_event.c_str(), strlen(listen_event.c_str()), 0);
        recv(Cameras[cam_address], buffer, BUFFER_SIZE - 1, 0);
        response_header response = get_response_info(std::string(buffer));
        std::string authorized_listen_event = std::string(HTTP_request_URL_HEADER) + EVENT_LISTENNING_HTTP_request + OPTION_HTTP_request_PREV_HOST + camera_device_address + OPTION_HTTP_request_APRE_HOST + struct_response_to_string(response, "admin", "admin123", EVENT_LISTENNING_HTTP_request) + std::string(HTTP_request_TAIL);
        Cameras[cam_address] = create_socket();
        socket_connect(Cameras[cam_address], camera_device_address.c_str(), "80"); 
        send(Cameras[cam_address], authorized_listen_event.c_str(), strlen(authorized_listen_event.c_str()), 0);
        recv(Cameras[cam_address], buffer, BUFFER_SIZE - 1, 0);
        if(success_listenning(buffer))
        {
            std::cout << "camera (" << camera_device_address << ") working at cam thread " << cam_address << "\n";
            std::cout << "camera (" << camera_device_address << ") working with site " << current_site.id << "\n";
            Camera_status[cam_address] = 1;
            current_site.status = 0xffffff;
            current_site.site_Status = "ffffff";
            current_site.Insert_Update_Site_type();
            int counter = 0;
            while(true)
            {
                if(Cameras[cam_address] != -1)
                {
                    bzero(buffer, BUFFER_SIZE);
                    byte_Rec = 0;
                    byte_Rec = recv(Cameras[cam_address], buffer, BUFFER_SIZE - 1, 0);
                    //fprintf(stderr, "%s", buffer);
                    if(byte_Rec > 0)
                    {
                        if(byte_Rec < 76)
                        {
                            //std::cout << "Content "  << counter++ << " from Cam #" << cam_address << " : " << get_response_CONTENT(std::string(buffer), byte_Rec) << "\n";
                        }
                        else
                        {
                            int n = byte_Rec;
                            int text_size = get_response_CONTENT_LENGTH(std::string(buffer));
                            std::string buffer_data = std::string(buffer);
                            //std::cout << "Content Length = "  << text_size << "\n";
                            while (n <= text_size) 
                            {
                                memset(buffer, 0, BUFFER_SIZE);
                                byte_Rec = recv(Cameras[cam_address], buffer, BUFFER_SIZE, 0);
                                buffer_data += std::string(buffer);
                                n += byte_Rec;
                            }
                            camera_event current_camera_event = event_parse(buffer_data);
                            print_camera_event(current_camera_event);
                            if(current_site.type == SITE_TYPE_ENTRY_BOARD  && current_camera_event.current_TrafficCar.PlateNumber[0] != 0)
                            {
                                camera_event_data[cam_address].garage_event_serial = ++gen_Entry_serial;
                                strcpy(camera_event_data[cam_address].garage_event_type, "Entry");
                                strcpy(camera_event_data[cam_address].plate, current_camera_event.current_TrafficCar.PlateNumber);
                                event_in current_event_in(mysql);
                                make_event_in(current_event_in, current_site.id, current_camera_event);
                                accountInfo current_accountInfo(mysql);
                                account_state current_account_state(mysql);
                                current_accountInfo.Select_account_by_plate(current_camera_event.current_TrafficCar.PlateNumber, Current_Settings.plate_match_level);
                                current_account_state.Select_account_state_by_plate(current_camera_event.current_TrafficCar.PlateNumber, Current_Settings.plate_match_level);
                                current_account_state.insite = current_site.id;
                                if(current_camera_event.current_TrafficCar.OpenGate == true && current_camera_event.current_TrafficCar.TrustCar == true)
                                {
                                    if(current_account_state.present_type == 0 && current_accountInfo.parking_type != 64)
                                    {
                                        current_event_in.inType = current_account_state.parking_type;
                                        current_event_in.ticketType = TICKET_TYPE_NO_TICKET;
                                        current_account_state.present_type = current_account_state.parking_type;
                                        current_account_state.intime = time(0);
                                        current_account_state.inserial = current_event_in.inSerial;
                                        int zone_id = -1;
                                        zone_id = get_zone_id_by_site(current_site.id);
                                        if(zone_id >= 0)
                                        {
                                            Zone zone(mysql);
                                            zone.select_Zone(zone_id);
                                            zone.entrySeason();
                                            zone.insert_update_Zone();
                                            current_event_in.totalLots = zone.totalSpaces;
                                            current_event_in.monthlyLots = zone.totalSpacesSeason;
                                            current_event_in.hourlyLots = zone.totalSpacesHourly;
                                            current_event_in.freeTotalLots = zone.vacantSpaces;
                                            current_event_in.freeMonthlyLots = zone.vacantSpacesSeason;
                                            current_event_in.freeHourlyLots = zone.vacantSpacesHourly;
                                        }
                                        accounts_sum++;
                                        current_accountInfo.Insert_update_accountInfo();
                                        current_account_state.Insert_update_account_state();
                                    }
                                    else
                                    {
                                        std::cout << "car is already inside..!!\n";
                                        current_event_in.inType = access_limit;
                                        current_event_in.ticketType = TICKET_TYPE_NO_TICKET;
                                        current_accountInfo.id = 0;
                                        current_account_state.aid = 0;
                                        current_accountInfo.gid = 0;
                                        current_account_state.gid = 0;
                                        current_accountInfo.~accountInfo();
                                        current_account_state.~account_state();
                                    }
                                }
                                else
                                {
                                    current_event_in.inType = access_limit;
                                    current_event_in.ticketType = TICKET_TYPE_NO_TICKET;
                                    current_accountInfo.id = 0;
                                    current_account_state.aid = 0;
                                    current_accountInfo.gid = 0;
                                    current_account_state.gid = 0;
                                    current_accountInfo.~accountInfo();
                                    current_account_state.~account_state();
                                }
                                current_event_in.Insert_entry_event();
                                if (webHost_Client_socket != INVALID_SOCKET)
                                {
                                    web_host_locked = true;
                                    web_buffer = gen_ServiceBoard_Entry_Request_Msg(current_event_in);
                                    SSL_write(ssl, (char *)dashou.StringToByteArray(web_buffer), strlen(web_buffer.c_str()) / 2);
                                    iResult = SSL_read(ssl, client_buffer, DEFAULT_BUFLEN);
                                    if (iResult < 0)
                                    {
                                        std::cout << "Error recv Web Host Proof 81 ACK...\n";
                                    }
                                    web_host_locked = false;
                                }
                                else
                                {
                                    web_buffer = gen_ServiceBoard_Entry_Request_Msg(current_event_in);
                                    offline_mode_messages_list.push_back(web_buffer);
                                    std::cout << "save event to send later.\n";
                                }
                            }
                            if(current_site.type == SITE_TYPE_EXIT_BOARD && current_camera_event.current_TrafficCar.PlateNumber[0] != 0)
                            {
                                camera_event_data[cam_address].garage_event_serial = ++gen_Exit_serial;
                                strcpy(camera_event_data[cam_address].garage_event_type, "Exit");
                                strcpy(camera_event_data[cam_address].plate, current_camera_event.current_TrafficCar.PlateNumber);
                                accountInfo current_accountInfo(mysql);
                                account_state current_account_state(mysql);
                                current_accountInfo.Select_account_by_plate(current_camera_event.current_TrafficCar.PlateNumber, Current_Settings.plate_match_level);
                                current_account_state.Select_account_state_by_plate(current_camera_event.current_TrafficCar.PlateNumber, Current_Settings.plate_match_level);
                                event_out current_event_out(mysql);
                                current_event_out.site = current_site.id;
                                current_account_state.outtime = current_camera_event.current_TrafficCar.CapTime;
                                current_account_state.outserial = gen_Exit_serial;
                                make_event_out(current_accountInfo, current_account_state, current_event_out, current_site.id);
                                current_account_state.insite = current_site.id;
                                if(current_camera_event.current_TrafficCar.OpenGate == true && current_camera_event.current_TrafficCar.TrustCar == true)
                                {
                                    if(current_account_state.present_type != 0 && current_accountInfo.parking_type != 64)
                                    {
                                        current_event_out.out_type = current_account_state.parking_type;
                                        current_event_out.ticket_type = TICKET_TYPE_NO_TICKET;
                                        current_account_state.present_type = 0;
                                        current_account_state.intime = time(0);
                                        current_account_state.outserial = current_event_out.out_serial;
                                        int zone_id = -1;
                                        zone_id = get_zone_id_by_site(current_site.id);
                                        if(zone_id >= 0)
                                        {
                                            Zone zone(mysql);
                                            zone.select_Zone(zone_id);
                                            zone.exitSeason();
                                            zone.insert_update_Zone();
                                            current_event_out.total_lots = zone.totalSpaces;
                                            current_event_out.monthly_lots = zone.totalSpacesSeason;
                                            current_event_out.hourly_lots = zone.totalSpacesHourly;
                                            current_event_out.free_total_lots = zone.vacantSpaces;
                                            current_event_out.free_monthly_lots = zone.vacantSpacesSeason;
                                            current_event_out.free_hourly_lots = zone.vacantSpacesHourly;
                                        }
                                        accounts_sum--;
                                        current_accountInfo.Insert_update_accountInfo();
                                        current_account_state.Insert_update_account_state();
                                    }
                                    else
                                    {
                                        std::cout << "car is not inside..!!\n";
                                        current_event_out.out_type = access_limit;
                                        current_event_out.ticket_type = TICKET_TYPE_NO_TICKET;
                                        current_accountInfo.id = 0;
                                        current_account_state.aid = 0;
                                        current_accountInfo.gid = 0;
                                        current_account_state.gid = 0;
                                        current_accountInfo.~accountInfo();
                                        current_account_state.~account_state();
                                    }
                                }
                                else
                                {
                                    current_event_out.out_type = access_limit;
                                    current_event_out.ticket_type = TICKET_TYPE_NO_TICKET;
                                    current_accountInfo.id = 0;
                                    current_account_state.aid = 0;
                                    current_accountInfo.gid = 0;
                                    current_account_state.gid = 0;
                                    current_accountInfo.~accountInfo();
                                    current_account_state.~account_state();
                                }
                                current_event_out.Insert_exit_event();
                                if (webHost_Client_socket != INVALID_SOCKET)
                                {
                                    web_host_locked = true;
                                    web_buffer = gen_ServiceBoard_Exit_Request_Msg110(current_account_state, current_event_out);
                                    SSL_write(ssl, (char *)dashou.StringToByteArray(web_buffer), strlen(web_buffer.c_str()) / 2);
                                    iResult = SSL_read(ssl, client_buffer, DEFAULT_BUFLEN);
                                    if (iResult < 0)
                                    {
                                        std::cout << "Error recv Web Host Proof 110 ACK...\n";
                                    }
                                    web_host_locked = false;
                                }
                                else
                                {
                                    web_buffer = gen_ServiceBoard_Exit_Request_Msg110(current_account_state, current_event_out);
                                    offline_mode_messages_list.push_back(web_buffer);
                                    std::cout << "save event to send later.\n";
                                }
                            }
                        }
                    }
                    else
                    {
                        Camera_status[cam_address] = 0;
                        break;
                    }
                }
                else
                {
                    Camera_status[cam_address] = 0;
                    break;
                }
            }
        }
        else
        {
            std::cout << "camera (" << camera_device_address << ") offline\n";
            Camera_status[cam_address] = 0;
        }
    }
    else
    {
        std::cout << "camera (" << camera_device_address << ") offline\n";
        Camera_status[cam_address] = 0;
    }
}

void* Camera_snap_Process(void * arg)
{
    int cam_address = *((int *) arg);
    int byte_rec = 0;
    char buffer[BUFFER_SIZE] = "";
    std::string buffer_data = "";
    std::string camera_device_address = std::string(Current_Settings.site_prefix) + std::string(".") + std::to_string(cam_address);
    std::string getsnap_event = std::string(HTTP_request_URL_HEADER) + EVENT_GETMANSNAP_HTTP_request + OPTION_HTTP_request_PREV_HOST + camera_device_address + OPTION_HTTP_request_APRE_HOST + std::string(HTTP_request_TAIL);
    Snap_Cameras[cam_address] = create_socket();
    if(socket_connect(Snap_Cameras[cam_address], camera_device_address.c_str(), "80") >= 0)
    {
        send(Snap_Cameras[cam_address], getsnap_event.c_str(), strlen(getsnap_event.c_str()), 0);
        recv(Snap_Cameras[cam_address], buffer, BUFFER_SIZE, 0);
        response_header response = get_response_info(std::string(buffer));
        std::string authorized_getsnap_event = std::string(HTTP_request_URL_HEADER) + EVENT_GETMANSNAP_HTTP_request + OPTION_HTTP_request_PREV_HOST + camera_device_address + OPTION_HTTP_request_APRE_HOST + struct_response_to_string(response, "admin", "admin123", EVENT_LISTENNING_HTTP_request) + std::string(HTTP_request_TAIL);
        Snap_Cameras[cam_address] = create_socket();
        socket_connect(Snap_Cameras[cam_address], camera_device_address.c_str(), "80"); 
        send(Snap_Cameras[cam_address], authorized_getsnap_event.c_str(), strlen(authorized_getsnap_event.c_str()), 0);
        recv(Snap_Cameras[cam_address], buffer, BUFFER_SIZE, 0);
        if(success_listenning(buffer))
        {
            std::cout << "snap camera (" << camera_device_address << ") working at cam thread " << cam_address << "\n";
            Camera_snap_status[cam_address] = 1;
            int counter = 0;
            while(true)
            {
                if(Snap_Cameras[cam_address] != -1)
                {
                    memset(buffer, 0, BUFFER_SIZE);
                    byte_rec = recv(Snap_Cameras[cam_address], buffer, BUFFER_SIZE, 0);
                    usleep(10000);
                    if(byte_rec > 0)
                    {
                        std::string file_type = get_response_Type(std::string(buffer));
                        if(file_type.substr(0,10).compare("text/plain") == 0)
                        {
                            int text_size = get_response_CONTENT_LENGTH(std::string(buffer));
                            if(text_size < 10)
                            {
                                buffer_data = get_response_CONTENT(std::string(buffer), byte_rec);
                                //std::cout << "Content "  << counter++ << " from snap Cam #" << cam_address << " : " << buffer_data << "\n";
                            }
                            else
                            {
                                int n = byte_rec;
                                int image_size = 0;
                                buffer_data = get_response_CONTENT(std::string(buffer), byte_rec);
                                while (n <= text_size) 
                                {
                                    memset(buffer, 0, BUFFER_SIZE);
                                    byte_rec = recv(Snap_Cameras[cam_address], buffer, BUFFER_SIZE, 0);
                                    buffer_data += std::string(buffer);
                                    n += byte_rec;
                                }
                                //std::cout << buffer_data << "\n";
                                image_size = get_response_CONTENT_LENGTH(std::string(buffer));
                                char image_start[BUFFER_SIZE] = "";
                                n = get_binary_response(buffer, image_start);
                                FILE *fp;
                                std::string filename = (std::string(Current_Settings.image_dir) + camera_event_variable_to_string(camera_event_data[cam_address]) + std::string(".jpg"));
                                std::cout << "filename = " << filename << ".\n";
                                fp = fopen(filename.c_str(), "w");
                                fwrite(image_start, n, 1, fp);
                                while (n <= image_size) 
                                {
                                    byte_rec = recv(Snap_Cameras[cam_address], buffer, BUFFER_SIZE - 1, 0);
                                    fwrite(buffer, byte_rec, 1, fp);
                                    n += byte_rec;
                                }
                                fclose(fp);
                                if(camera_event_data[cam_address].garage_event_serial > 0)
                                {
                                    photo current_photo(mysql);
                                    try
                                    {
                                        current_photo.id = get_photo_insert_aid();
                                        current_photo.gid = Current_garage.gid;
                                        strcpy(current_photo.camera_address, camera_device_address.c_str());
                                        std::string photo_name = camera_event_variable_to_string(camera_event_data[cam_address]) + std::string(".jpg");
                                        strcpy(current_photo.photo_name, photo_name.c_str());
                                        current_photo.receive_time = time(0);
                                        strcpy(current_photo.plate_number, camera_event_data[cam_address].plate);
                                        strcpy(current_photo.plate_color, "");
                                        strcpy(current_photo.plate_type, "");
                                        current_photo.event_lane = 1;
                                        strcpy(current_photo.event_type, "TrafficJunction");
                                        current_photo.event_time = time(0);
                                        strcpy(current_photo.vehicle_color, "");
                                        strcpy(current_photo.vehicle_size, "");
                                        strcpy(current_photo.vehicle_type, "");
                                        strcpy(current_photo.ticket, "");
                                        strcpy(current_photo.garage_event_type, camera_event_data[cam_address].garage_event_type);
                                        current_photo.garage_event_serial = camera_event_data[cam_address].garage_event_serial;
                                        strcpy(current_photo.photo_path, Current_Settings.image_dir);
                                        int execute = 0;
                                        execute = current_photo.Insert_photo();
                                        if(execute == 0)
                                        {
                                            fprintf(stderr, "photo : %s is inserted\n", current_photo.photo_name);
                                            send_image(current_photo);
                                        }
                                        else
                                        {
                                            finish_with_error(mysql, execute);
                                        }
                                    }
                                    catch(...)
                                    {
                                        unkown_error(mysql, -102);
                                    }
                                }
                                camera_event_data[cam_address].garage_event_serial = 0;
                                strcpy(camera_event_data[cam_address].garage_event_type, "");
                                strcpy(camera_event_data[cam_address].plate, "");
                            }
                        }
                    }
                    else
                    {
                        Camera_snap_status[cam_address] = 0;
                        break;
                    }
                }
                else
                {
                    Camera_snap_status[cam_address] = 0;
                    break;
                }
            }
        }
        else
        {
            std::cout << "camera snap (" << camera_device_address << ") offline\n";
            Camera_snap_status[cam_address] = 0;
        }
    }
    else
    {
        std::cout << "camera snap (" << camera_device_address << ") offline\n";
        Camera_snap_status[cam_address] = 0;
    }
}
#endif

#ifndef initilize_function

void  initSite(Site_type site, DashouParser *parser)
{
    std::string report = "";
    report += log_udp.site_connecting_messege_Builder(site);
    report += log_udp.INITIAL_messege_Builder(site, parser);
    unsigned char client_buffer[DEFAULT_BUFLEN] = "";
    unsigned char WebHost_buffer[DEFAULT_BUFLEN] = "";
    int iResult = 0;
    int bytesRec = 0;
    // genSysParam
    std::string buffer = genSysParam(site, parser);
    iResult = send(site.socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "Error sending genSysParam to site";
    }
    else
    {
        report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_SITE_SETTING,localSerialDownLink, All_Cameras, site.id, sites);
    }
    bytesRec = recv(site.socket, client_buffer, DEFAULT_BUFLEN, 0);
    
    if(webHost_Client_socket != INVALID_SOCKET)
    {
        registerNewSiteToWebHost(site);
        web_host_locked = true;
        iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
        if (iResult == SOCKET_ERROR)
	{
		std::cout << "Error recv Web Host Init Device ACK";
	}
        else
        {
            web_host_locked = false;
            DashouParser *parser_host = new DashouParser();
            parser_host->parse2(WebHost_buffer);
            report += log_udp.ACK_webhost_messege_Builder(parser_host);
        }
    }
    parser->parse(client_buffer);
    if (bytesRec == SOCKET_ERROR)
    {
        std::cout << "Error recv genSysParam ACK from site";
    }
    else
    {
        report += log_udp.ACK_sites_messege_Builder(site, parser);
    }
    // genSysParamBalanceNotification
    buffer = genSysParamBalanceNotification(site, parser);
    iResult = send(site.socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
    if (iResult == SOCKET_ERROR)
    {
            std::cout << "Error sending genSysParamBalanceNotification to site";
    }
    else
    {
        report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_BALANCE_NOTIFICATION,localSerialDownLink, All_Cameras, site.id, sites);
    }
    bytesRec = recv(site.socket, client_buffer, DEFAULT_BUFLEN, 0);
    parser->parse(client_buffer);
    if (bytesRec == SOCKET_ERROR)
    {
            std::cout << "Error recv genSysParamBalanceNotification from site";
    }
    else
    {
        report += log_udp.ACK_sites_messege_Builder(site, parser);
    }
    // genSysParamExpireForecast
    buffer = genSysParamExpireForecast(site, parser);
    iResult = send(site.socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
    if (iResult == SOCKET_ERROR)
    {
            std::cout << "Error sending genSysParamExpireForecast to site";
    }
    else
    {
        report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_EXPIRE_FORECAST,localSerialDownLink, All_Cameras, site.id, sites);
    }
    bytesRec = recv(site.socket, client_buffer, DEFAULT_BUFLEN, 0);
    parser->parse(client_buffer);
    if (bytesRec == SOCKET_ERROR)
    {
            std::cout << "Error recv genSysParamExpireForecast from site";
    }
    else
    {
        report += log_udp.ACK_sites_messege_Builder(site, parser);
    }
    // genSysParamCameraSite
    buffer = genSysParamCameraSite(site, parser);
    iResult = send(site.socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
    if (iResult == SOCKET_ERROR)
    {
            std::cout << "Error sending genSysParamCameraSite to site";
    }
    else
    {
        report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_CAMERA_SITE,localSerialDownLink, All_Cameras, site.id, sites);
    }
    bytesRec = recv(site.socket, client_buffer, DEFAULT_BUFLEN, 0);
    parser->parse(client_buffer);
    if (bytesRec == SOCKET_ERROR)
    {
            std::cout << "Error recv genSysParamCameraSite from site";
    }
    else
    {
        report += log_udp.ACK_sites_messege_Builder(site, parser);
    }
    //// genSysParamNetworkParam
    buffer = genSysParamNetworkParam(site, parser);
    iResult = send(site.socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
    if (iResult == SOCKET_ERROR)
    {
            std::cout << "Error sending genSysParamNetworkParam to site";
    }
    else
    {
        report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_NETWORK_PARAM,localSerialDownLink, All_Cameras, site.id, sites);
    }
    bytesRec = recv(site.socket, client_buffer, DEFAULT_BUFLEN, 0);
    parser->parse(client_buffer);
    if (bytesRec == SOCKET_ERROR)
    {
            std::cout << "Error recv genSysParamNetworkParam from site";
    }
    else
    {
        report += log_udp.ACK_sites_messege_Builder(site, parser);
    }
    // genSysParamSiteName
    buffer = genSysParamSiteName(site, parser);
    iResult = send(site.socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
    if (iResult == SOCKET_ERROR)
    {
            std::cout << "Error sending genSysParamSiteName to site";
    }
    else
    {
        report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_SITE_NAME,localSerialDownLink, All_Cameras, site.id, sites);
    }
    bytesRec = recv(site.socket, client_buffer, DEFAULT_BUFLEN, 0);
    parser->parse(client_buffer);
    if (bytesRec == SOCKET_ERROR)
    {
            std::cout << "Error recv genSysParamSiteName from site";
    }
    else
    {
        report += log_udp.ACK_sites_messege_Builder(site, parser);
    }
    if (site.type == SITE_TYPE_ENTRY_BOARD || site.type == SITE_TYPE_EXIT_BOARD)
    {
        // genSysParamLeddisplay
        buffer = genSysParamLeddisplay(site, parser);
        iResult = send(site.socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
        if (iResult == SOCKET_ERROR)
        {
            std::cout << "Error sending genSysParamLeddisplay to site";
        }
        else
        {
            report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_LED_DISPLAY,localSerialDownLink, All_Cameras, site.id, sites);
        }
        bytesRec = recv(site.socket, client_buffer, DEFAULT_BUFLEN, 0);
        parser->parse(client_buffer);
        if (bytesRec == SOCKET_ERROR)
        {
            std::cout << "Error recv genSysParamLeddisplay from site";
        }
        else
        {
            report += log_udp.ACK_sites_messege_Builder(site, parser);
        }
        // genSysParamTicketHeader
        buffer = genSysParamTicketHeader(site, parser);
        iResult = send(site.socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
        if (iResult == SOCKET_ERROR)
        {
            std::cout << "Error sending genSysParamTicketHeader to site";
        }
        bytesRec = recv(site.socket, client_buffer, DEFAULT_BUFLEN, 0);
        parser->parse(client_buffer);
        if (bytesRec == SOCKET_ERROR)
        {
            std::cout << "Error recv genSysParamTicketHeader from site";
        }
    }
    // genSysParamReceiptFormat
    buffer = genSysParamReceiptFormat(site, parser);
    iResult = send(site.socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "Error sending genSysParamReceiptFormat to site";
    }
    bytesRec = recv(site.socket, client_buffer, DEFAULT_BUFLEN, 0);
    parser->parse(client_buffer);
    if (bytesRec == SOCKET_ERROR)
    {
        std::cout << "Error recv genSysParamReceiptFormat from site";
    }
    // genSysParamChargeRate
    if (site.type == SITE_TYPE_TABLET_APP)
    {
        buffer = genSysParamChargeRate(site, parser);
        iResult = send(site.socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
        if (iResult == SOCKET_ERROR)
        {
            std::cout << "Error sending genSysParamChargeRate to site";
        }
        bytesRec = recv(site.socket, client_buffer, DEFAULT_BUFLEN, 0);
        parser->parse(client_buffer);
        if (bytesRec == SOCKET_ERROR)
        {
            std::cout << "Error recv genSysParamChargeRate from site";
        }
    }
    log_udp.messege_Sender(report);
}

std::string genACK(int function, int serial, int error)
{
	std::string s = "";
	s += HEADER;
	s += dashou.calcLength(2);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_ACK_FRAME);
	s += dashou.to_String_X2(function);
	s += dashou.to_String_X2(error);
	s += "FF0F";
	s += TAIL;
	return s;//dashou.StringToByteArray(s);
}

std::string genSysParam(Site_type site, DashouParser *parser)
{
	int length = 25;
	int serial = (++localSerialDownLink);
	std::string s = "";
	time_t datetime = time(0);
	tm *now = localtime(&datetime);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_Sys_PARAM_FRAME);
	s += dashou.calcCurrentTime(datetime);
	s += dashou.int2HexStrReverse2Byte(CONTROL_TYPE_SITE_SETTING);      //01
	s += dashou.to_String_X2(site.address);                             //02
	s += dashou.to_String_X2(site.oneCard_oneCar);                      // 1 Card 1 Car -03
	s += dashou.to_String_X2(site.same_EntryExit_group);                // Same Entry/Exit Group number-04
	s += dashou.to_String_X4(site.same_EntryExit_site);                 // Same Entry/Exit Site -05
	s += dashou.to_String_X2(site.same_EntryExit_filter);               // Same Entry/Exit Filter Seconds -06
	s += dashou.to_String_X2(site.entryPresetLicensePlateNumber);       // Entry Preset License Plate Number -07
        s += dashou.to_String_X2(site.exitFreeLetPass);                     // Exit $0 Let Pass
	s += dashou.to_String_X2(site.hourlyParkingFullAccessDeny);         // Hourly Parking Full Access Deny
	s += dashou.to_String_X2(site.monthlyParkingFullAccessDeny);        // Monthly Parking Full Access Deny
	s += dashou.to_String_X2(site.id_PresetType_id);                    // site.type.ToString("X2"); // ID Preset Type ID
	s += dashou.to_String_X2(site.id_PresetSite_in_Site_Group);         // ID Preset Site-in-Site Group
	if (site.type == SITE_TYPE_TABLET_APP)
		s += dashou.to_String_X2(site.credentialMode_app);          // Credential Mode
	else
		s += dashou.to_String_X2(site.credentialMode);              // Credential Mode

	s += dashou.to_String_X2(site.type);
	s += "000000";
	s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
	s += TAIL;

	return s;
}

std::string genSysParamBalanceNotification(Site_type site, DashouParser *parser)
{
	int length = 12;
	int serial = (++localSerialDownLink);
	std::string s = "";
	time_t now = time(0); //DateTime now = DateTime.Now;
	tm *timenow = localtime(&now);
	std::string balance_s = dashou.to_String_X8(Current_Settings.alarm_balance);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_Sys_PARAM_FRAME);	//Dashou.CONTROL_Sys_PARAM_FRAME.ToString("X2");
	s += dashou.calcCurrentTime(now);
	s += dashou.int2HexStrReverse2Byte(CONTROL_TYPE_BALANCE_NOTIFICATION);
	s += balance_s; //Balance notification info
	s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday, timenow->tm_hour);
	s += TAIL;
	return s;//dashou.StringToByteArray(s);
}

std::string genSysParamExpireForecast(Site_type site, DashouParser *parser)
{
	int length = 12;
	int serial = (++localSerialDownLink);
	std::string s = "";
	time_t now = time(0);
	tm *timenow = localtime(&now);
	std::string expire_s = dashou.to_String_X8(Current_Settings.alarm_enddata);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_Sys_PARAM_FRAME);
	s += dashou.calcCurrentTime(now);
	s += dashou.int2HexStrReverse2Byte(CONTROL_TYPE_EXPIRE_FORECAST);
	s += expire_s;
	s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday, timenow->tm_hour);
	s += TAIL;
	return s;
}

std::string genSysParamCameraSite(Site_type site, DashouParser *parser)
{
	int length = 521;
	int serial = (++localSerialDownLink);
	std::string s = "";
	time_t now = time(0);
	tm *timenow = localtime(&now);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_Sys_PARAM_FRAME);
	s += dashou.calcCurrentTime(now);
	s += dashou.int2HexStrReverse2Byte(CONTROL_TYPE_CAMERA_SITE);
	s += dashou.to_String_X2(All_Cameras.size());
        int counter = 0;
        for(int i = 0; i < All_Cameras.size(); i++)
        {
            for(int j = 0; All_Cameras[i].sites_binded[j] != 0; j++)
            {
                s += dashou.to_String_X2(All_Cameras[i].cam_address);
                s += dashou.to_String_X2(All_Cameras[i].sites_binded[j]);
                counter++;
            }
        }
        s += dashou.to_String_X2(All_Cameras.size());
        s += "cd";
        counter++;
        while(counter < 256)
        {
            s += "0000";
            counter++;
        }
	s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday, timenow->tm_hour);
	s += TAIL;
	return s;
}

std::string genSysParamNetworkParam(Site_type site, DashouParser *parser)
{
	int length = 158;
	int serial = (++localSerialDownLink);
	std::string s = "";
	time_t now = time(0);
	tm *timenow = localtime(&now);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_Sys_PARAM_FRAME);
	s += dashou.calcCurrentTime(now);
	s += dashou.int2HexStrReverse2Byte(CONTROL_TYPE_NETWORK_PARAM);
	s += Online_master_port;
	s += Online_master_ip;
	s += Online_slave_port;
	s += Online_slave_ip;
	s += "00000000000000000000000000000000000000";
	s += "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += E_Transaction_port;
	s += E_Transaction_ip;
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday, timenow->tm_hour);
	s += TAIL;
	return s;
}

std::string genSysParamSiteName(Site_type site, DashouParser *parser)
{
	int length = 961;
	int serial = (++localSerialDownLink);
	std::string s = "";
	time_t now = time(0);
	tm *timenow = localtime(&now);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_Sys_PARAM_FRAME);
	s += dashou.calcCurrentTime(now);
	s += dashou.int2HexStrReverse2Byte(CONTROL_TYPE_SITE_NAME);
        int sites_writed = 0;
        for(int i = 0; i < MAX_SITES; i++)
        {
            if(sites[i].id > 0 && sites[i].gid > 0)
            {
                s += dashou.to_String_X2(sites[i].address);
                s += dashou.to_String_X2(sites[i].type);
                for(int j = 0; j < 32; j++)
                {
                    s += dashou.to_String_X2(sites[i].db_name[j]);
                }
                sites_writed++;
            }
        }
        for(int i = sites_writed; i < 28; i++)
        {
            s += "00000000000000000000000000000000000000000000000000000000000000000000"; 
        }
//	if (site.type == SITE_TYPE_ENTRY_BOARD)
//		s += "05030045786974000000000000000000000000000000000000000000000000000000000403456e7472616e636500000000000000000000000000000000000000000000000010004150500000000000000000000000000000000000000000000000000000000000c700d5beb5e331393900000000000000000000000000000000000000000000000000de006d6f62696c650000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000db01cd00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
//	else if (site.type == SITE_TYPE_EXIT_BOARD)
//		s += "07030445786974000000000000000000000000000000000000000000000000000000000400456e7472616e636500000000000000000000000000000000000000000000000010004150500000000000000000000000000000000000000000000000000000000000c700d5beb5e331393900000000000000000000000000000000000000000000000000c800d5beb5e332303000000000000000000000000000000000000000000000000000d200d5beb5e332313000000000000000000000000000000000000000000000000000de006d6f62696c65000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000b901cd00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
//	else if (site.type == SITE_TYPE_TABLET_APP)
//		s += "05030045786974000000000000000000000000000000000000000000000000000000000400456e7472616e636500000000000000000000000000000000000000000000000010064150500000000000000000000000000000000000000000000000000000000000c700d5beb5e331393900000000000000000000000000000000000000000000000000de006d6f62696c650000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000c601cd00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
        s += "00";
	s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday, timenow->tm_hour);
	s += TAIL;
	return s;
}

std::string genSysParamLeddisplay(Site_type site, DashouParser *parser)
{
	int length = 520;
	int serial = (++localSerialDownLink);
	std::string s = "";
	time_t now = time(0);
	tm *timenow = localtime(&now);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_Sys_PARAM_FRAME);
	s += dashou.calcCurrentTime(now);
	s += dashou.int2HexStrReverse2Byte(CONTROL_TYPE_LED_DISPLAY);
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday, timenow->tm_hour);
	s += TAIL;
	return s;
}

std::string genSysParamTicketHeader(Site_type site, DashouParser *parser)
{
	int length = 520;
	int serial = (++localSerialDownLink);
	std::string s = "";
	time_t now = time(0);
	tm *timenow = localtime(&now);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_Sys_PARAM_FRAME);
	s += dashou.calcCurrentTime(now);
	s += dashou.int2HexStrReverse2Byte(CONTROL_TYPE_TICKET_HEADER);
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday, timenow->tm_hour);
	s += TAIL;
	return s;
}

std::string genSysParamReceiptFormat(Site_type site, DashouParser *parser)
{
	int length = 958;
	int serial = (++localSerialDownLink);
	std::string s = "";
	time_t now = time(0);
	tm *timenow = localtime(&now);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_Sys_PARAM_FRAME);
	s += dashou.calcCurrentTime(now);
	s += dashou.int2HexStrReverse2Byte(CONTROL_TYPE_RECEIPT_FORMAT);
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday, timenow->tm_hour);
	s += TAIL;
	return s;
}

std::string genSysParamChargeRate(Site_type site, DashouParser *parser)
{
	int length = 985;
	int serial = (++localSerialDownLink);
	std::string s = "";
	time_t now = time(0);
	tm *timenow = localtime(&now);	//DateTime now = DateTime.Now;
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_Sys_PARAM_FRAME); //Dashou.CONTROL_Sys_PARAM_FRAME.ToString("X2");
	s += dashou.calcCurrentTime(now);
	s += dashou.int2HexStrReverse2Byte(CONTROL_TYPE_CHARGE_RATE);
	s += "1004";
	s += "00436861726765205374616e6461726420300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";// 0Charge rate 0
	s += "01436861726765205374616e6461726420310000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";// 1Charge rate 1
	s += "03436861726765205374616e6461726420330000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";// 3Charge rate 3
	s += "04436861726765205374616e6461726420340000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";// 4Charge rate 4
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += "00000000000000000000000000000000000000000000000000000000000000000000000000007202cd7402cd000000000000000000000000000000000000000000";
	s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday, timenow->tm_hour);
	s += TAIL;
	return s;
}

#endif

#ifndef parking_process_function

std::string gen_ServiceBoard_Entry_Request_Msg(event_in current_event_in)
{
	int length = 67;
	int inner_function = 129;    // 0x81
	int serial = ++localSerialUpLink;
	std::string s = "";
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.to_String_X2(inner_function);
	s += dashou.calcCurrentTime(current_event_in.inTime);
	s += dashou.to_String_X4(current_event_in.inSerial);
	s += dashou.to_String_X2(current_event_in.inType);
        s += dashou.to_String_X2(current_event_in.ticketType);
        for(int i = 0; i < 19; i++)                                 //s += proof.get_TicketASCIIHEX();
        {
            s += dashou.to_String_X2(current_event_in.ticket[i]);
        }
        for(int i = 0; i < 12; i++)                                 //s += proof.get_PlateASCIIHEX();
        {
            s += dashou.to_String_X2(current_event_in.plate[i]);
        }
	s += dashou.to_String_X4(current_event_in.lotsGroupId);
	s += dashou.to_String_X4(0);                                //proof.Parking_Space_Current_Occupied_Space_Number
        s += dashou.to_String_X4(current_event_in.freeHourlyLots);
        s += dashou.to_String_X4(current_event_in.freeMonthlyLots);
        s += dashou.to_String_X4(current_event_in.freeTotalLots);
        s += dashou.to_String_X4(current_event_in.hourlyLots);
        s += dashou.to_String_X4(current_event_in.monthlyLots);
        s += dashou.to_String_X4(current_event_in.totalLots);
        s += "01";                                                  //Operator Code 
        s += dashou.to_String_X2(current_event_in.site);
        s += "00";                                                  //Unknown (0x00)
        s += "c010";                                                //Fixed? as in Service Board Heartbeat (0x10C0)
	s += dashou.to_String_X2(current_event_in.site);
        Site_type entry_site(mysql);
        entry_site.Select_Site_type_by_id(current_event_in.site);
	if(entry_site.status == 0xffffff)                           //s += proof.get_StatusASCIIHEX();
            s += "ffffff";            
        else 
            s += "000000";
        s += dashou.to_String_X2(current_event_in.site);
	s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
	s += TAIL;
	return s;
}

std::string gen_ServiceBoard_Pay_Request_Msg110(account_state current_account_state, event_charge current_event_charge)
{
    int length = 96;
    int inner_function = 130;    // 0x82
    int serial = ++localSerialUpLink;
    std::string s = "";
    time_t now = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(current_event_charge.charge_time);
    s += dashou.to_String_X4(current_event_charge.charge_serial);
    s += dashou.to_String_X2(current_event_charge.charge_type);
    s += dashou.to_String_X2(current_event_charge.payment_type);
    s += dashou.to_String_X2(current_event_charge.ticket_type);
    for(int i = 0; i < 19; i++)                                         //s += proof.get_TicketASCIIHEX();
    {
        s += dashou.to_String_X2(current_event_charge.ticket[i]);
    }
    for(int i = 0; i < 12; i++)                                         //s += proof.get_PlateASCIIHEX();
    {
        s += dashou.to_String_X2(current_event_charge.plate[i]);
    }
    s += dashou.to_String_X8(current_event_charge.park_duration);       //(proof.Current_Parking_Time);"00000000"
    s += dashou.to_String_X8(current_event_charge.should_pay);          //(proof.Current_Parking_Fee);"00000000"
    s += dashou.to_String_X8(0);
    s += dashou.to_String_X8(current_event_charge.should_pay);
    s += dashou.to_String_X8(0);
    s += dashou.calcCurrentTime(current_event_charge.in_time);
    s += dashou.to_String_X4(current_event_charge.in_serial);
    s += dashou.to_String_X4(current_event_charge.group_prepaid_serial);
    s += dashou.to_String_X4(0);
    int zone_id = -1;
    zone_id = get_zone_id_by_site(sites[current_account_state.insite].id);
    if(zone_id > 0 && zone_id < 16)
    {
        s += dashou.to_String_X4(Zones[zone_id].totalSpaces);
        s += dashou.to_String_X4(Zones[zone_id].totalSpacesSeason);
        s += dashou.to_String_X4(Zones[zone_id].totalSpacesHourly);
        s += dashou.to_String_X4(Zones[zone_id].vacantSpaces);
        s += dashou.to_String_X4(Zones[zone_id].vacantSpacesSeason);
        s += dashou.to_String_X4(Zones[zone_id].vacantSpacesHourly);
    }
    else
    {
        s += dashou.to_String_X4(0x7fff);
        s += dashou.to_String_X4(0x7fff);
        s += dashou.to_String_X4(0x7fff);
        s += dashou.to_String_X4(0x7fff);
        s += dashou.to_String_X4(0x7fff);
        s += dashou.to_String_X4(0x7fff);
    }
    s += "01"; // Operator Code 
    s += dashou.to_String_X2(current_event_charge.site);
    s += "00"; // Unknown (0x00)
    s += "c010"; // Fixed? as in Service Board Heartbeat (0x10C0)
    s += dashou.to_String_X2(current_event_charge.site);
    Site_type entry_site(mysql);
    entry_site.Select_Site_type_by_id(current_event_charge.site);
    if(entry_site.status == 0xffffff)                           //s += proof.get_StatusASCIIHEX();
        s += "ffffff";            
    else 
        s += "000000";
    Site_type current_charge_site(mysql);
    current_charge_site.Select_Site_type_by_address(current_event_charge.site);
    s += dashou.to_String_X2(current_charge_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TABLET_REQUEST_RESPONSE, inner_function);
    s += TAIL;
    return s;
}

std::string gen_ServiceBoard_Pay_Request_Msg100(event_charge current_event_charge, bool charge)
{
    int length = 86;
    int inner_function = 134;// 0x86
    int serial = ++localSerialUpLink;
    std::string s = "";
    time_t now = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(current_event_charge.charge_time);
    s += dashou.to_String_X4(current_event_charge.charge_serial);
    s += dashou.to_String_X2(current_event_charge.payment_type);
    s += dashou.to_String_X2(current_event_charge.charge_type);
    s += dashou.to_String_X2(current_event_charge.ticket_type);
    for(int i = 0; i < 19; i++)                                         //s += proof.get_TicketASCIIHEX();
    {
        s += dashou.to_String_X2(current_event_charge.ticket[i]);
    }
    for(int i = 0; i < 12; i++)                                         //s += proof.get_PlateASCIIHEX();
    {
        s += dashou.to_String_X2(current_event_charge.plate[i]);
    }
    s += dashou.calcCurrentTime(current_event_charge.start_time);
    s += dashou.calcCurrentTime(current_event_charge.end_time);
    s += dashou.to_String_X8(current_event_charge.actually_pay); // cost
    s += dashou.to_String_X8(current_event_charge.should_pay); // cost
    if(charge)
    {
        s += dashou.to_String_X8(current_event_charge.balance);
        s += "0000"; //to determine if charge or pay hourly
    }
    else
    {
        s += dashou.to_String_X8(current_event_charge.park_duration);
        s += "ffff"; //to determine if charge or pay hourly
    }
    s += dashou.calcCurrentTime(current_event_charge.in_time);
    s += dashou.to_String_X4(current_event_charge.in_serial);
    s += "01"; // Operator Code 
    s += dashou.to_String_X2(current_event_charge.site);
    s += "00"; // Unknown (0x00)
    s += "c010"; // Fixed? as in Service Board Heartbeat (0x10C0)
    s += dashou.to_String_X2(current_event_charge.site);
    Site_type entry_site(mysql);
    entry_site.Select_Site_type_by_id(current_event_charge.site);
    if(entry_site.status == 0xffffff)//s += proof.get_StatusASCIIHEX();
        s += "ffffff";            
    else 
        s += "000000";
    s += dashou.to_String_X2(current_event_charge.site);
    s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
    s += TAIL;
    return s;
}

std::string gen_ServiceBoard_Exit_Request_Msg100(event_out current_event_out)
{
    int length = 86;
    int inner_function = 134;// 0x86
    int serial = ++localSerialUpLink;
    std::string s = "";
    time_t now = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(current_event_out.out_time);
    s += dashou.to_String_X4(current_event_out.out_serial);
    s += dashou.to_String_X2(current_event_out.site);
    s += dashou.to_String_X2(cash);
    s += dashou.to_String_X2(current_event_out.ticket_type);
    for(int i = 0; i < 19; i++)                                         //s += proof.get_TicketASCIIHEX();
    {
        s += dashou.to_String_X2(current_event_out.ticket[i]);
    }
    for(int i = 0; i < 12; i++)                                         //s += proof.get_PlateASCIIHEX();
    {
        s += dashou.to_String_X2(current_event_out.plate[i]);
    }
    s += "000000000000000000000000"; // Unknown (Zeros)
    s += dashou.to_String_X8(current_event_out.total_paid); // cost
    s += dashou.to_String_X8(current_event_out.total_should); // cost
    s += dashou.to_String_X8(current_event_out.park_duration);
    s += "ffff"; // Unknown (0xFFFF)
    s += dashou.calcCurrentTime(current_event_out.in_time);
    s += dashou.to_String_X4(current_event_out.in_serial);
    s += "01"; // Operator Code 
    s += dashou.to_String_X2(current_event_out.site);
    s += "00"; // Unknown (0x00)
    s += "c010"; // Fixed? as in Service Board Heartbeat (0x10C0)
    s += dashou.to_String_X2(current_event_out.site);
    Site_type entry_site(mysql);
    entry_site.Select_Site_type_by_id(current_event_out.site);
    if(entry_site.status == 0xffffff)                                   //s += proof.get_StatusASCIIHEX();
        s += "ffffff";            
    else 
        s += "000000";
    s += dashou.to_String_X2(current_event_out.site);
    s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
    s += TAIL;
    return s;
}

std::string gen_ServiceBoard_Exit_Request_Msg110(account_state current_account_state, event_out current_event_out)
{
    int length = 96;
    int inner_function = 130;    // 0x82
    int serial = ++localSerialUpLink;
    std::string s = "";
    time_t now = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(current_event_out.out_time);
    s += dashou.to_String_X4(current_event_out.out_serial);
    s += dashou.to_String_X2(current_event_out.charge_type);
    s += dashou.to_String_X2(current_event_out.out_type);
    s += dashou.to_String_X2(current_event_out.ticket_type);
    for(int i = 0; i < 19; i++)                                         //s += proof.get_TicketASCIIHEX();
    {
        s += dashou.to_String_X2(current_event_out.ticket[i]);
    }
    for(int i = 0; i < 12; i++)                                         //s += proof.get_PlateASCIIHEX();
    {
        s += dashou.to_String_X2(current_event_out.plate[i]);
    }
    s += dashou.to_String_X8(current_event_out.total_should);           //(proof.Current_Parking_Time);"00000000"
    s += dashou.to_String_X8(current_event_out.park_duration);          //(proof.Current_Parking_Fee);"00000000"
    s += dashou.to_String_X8(0);
    s += dashou.to_String_X8(0);
    s += dashou.to_String_X8(current_event_out.total_paid);
    s += dashou.calcCurrentTime(current_event_out.in_time);
    s += dashou.to_String_X4(current_event_out.in_serial);
    s += dashou.to_String_X4(current_event_out.lots_group_occupied);
    s += dashou.to_String_X4(0);
    int zone_id = -1;
    Zone zone(mysql);
    zone_id = get_zone_id_by_site(sites[current_account_state.insite].id);
    zone.select_Zone(zone_id);
    if(zone_id >= 0 && zone_id < 16)
    {
        s += dashou.to_String_X4(zone.vacantSpacesHourly);
        s += dashou.to_String_X4(zone.vacantSpacesSeason);
        s += dashou.to_String_X4(zone.vacantSpaces);
        s += dashou.to_String_X4(zone.totalSpacesHourly);
        s += dashou.to_String_X4(zone.totalSpacesSeason);
        s += dashou.to_String_X4(zone.totalSpaces);
    }
    else
    {
        s += dashou.to_String_X4(0xff7f);
        s += dashou.to_String_X4(0xff7f);
        s += dashou.to_String_X4(0xff7f);
        s += dashou.to_String_X4(0xff7f);
        s += dashou.to_String_X4(0xff7f);
        s += dashou.to_String_X4(0xff7f);
    }
    s += "01"; // Operator Code 
    s += dashou.to_String_X2(current_event_out.site);
    s += "00"; // Unknown (0x00)
    s += "c010"; // Fixed? as in Service Board Heartbeat (0x10C0)
    s += dashou.to_String_X2(current_event_out.site);
    Site_type entry_site(mysql);
    entry_site.Select_Site_type_by_id(current_event_out.site);
    if(entry_site.status == 0xffffff)                           //s += proof.get_StatusASCIIHEX();
        s += "ffffff";            
    else 
        s += "000000";
    s += dashou.to_String_X2(current_event_out.site);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TABLET_REQUEST_RESPONSE, inner_function);
    s += TAIL;
    return s;
}
#endif

#ifndef udp_function

std::string gen_ServiceBoard_TimeSpaces_Msg()
{
	int length = 264;
	int serial = ++broadcastSerial;
	time_t now = time(0);
	std::string s = "";
	std::string z = "";
        Zone zone(mysql);
	for (int i = 0; i < 16; i++)
	{
            zone.select_Zone(i);
            z += zone.get_TotalSpaces() + zone.get_TotalSpacesSeason() + zone.get_TotalSpacesHourly() + zone.get_VacantSpaces() + zone.get_VacantSpacesSeason() + zone.get_VacantSpacesHourly() + "0000" + "0000";
	}
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += dashou.to_String_X2(CONTROL_BROADCAST_TIME_AND_SPACES);
	s += dashou.calcCurrentTime(now);
	s += z;
	s += "DCFE";
	s += "FF0F";
	s += TAIL;
	return s;//Dashou.StringToByteArray(s);
}

std::string gen_ServiceBoard_Spaces_To_Webhost_Msg(int serial, int TotalSpace, int TotalSpaceSeason, int TotalSpaceHourly, int TotalVacantSpace, int VacantSpaceSeason, int VacantSpaceHourly)
{
	int inner_function = 138;    // 0x8A
	int length = 330;
	std::string s = "";
	time_t now = time(0);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.to_String_X2(inner_function);
	s += dashou.calcCurrentTime(now);

	std::string TS = dashou.to_String_X4(TotalSpace);
	std::string TSS = dashou.to_String_X4(TotalSpaceSeason);
	std::string TSH = dashou.to_String_X4(TotalSpaceHourly);
	std::string TVS = dashou.to_String_X4(TotalVacantSpace);
	std::string VSS = dashou.to_String_X4(VacantSpaceSeason);
	std::string VSH = dashou.to_String_X4(VacantSpaceHourly);
	std::string z1 = TS + TSS + TSH + TVS + VSS + VSH + "FFFF" + "0000";

	s += "1500010100";
	s += z1;
	s += "0000000000000000000000000000000000000000000000000000e4000000f9ffffffe30000001c000000a0ab012000000080b80b0000278000089a7f0008000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += dashou.to_String_X2(server_site.type);

	s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
	s += TAIL;
	return s;
}

std::string gen_ServiceBoard_Spaces_ACK2_Msg(int serial)
{
	int inner_function = 138;    // 0x8A
	int length = 11;
	std::string s = "";
	time_t now = time(0);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.to_String_X2(inner_function);
	s += dashou.to_String_X2(server_site.address);
	s += "0308142e001500";//SITE_STATUS_SERVICE_BOARD
	s += "0000";
	s += dashou.to_String_X2(server_site.type);
	s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
	s += TAIL;
	return s;
}

#endif

#ifndef webhost_client_functions

std::string gen_ServiceBoard_ACK_Msg(int serial, int function, int error)
{
	int length = 2;
	int inner_function = CONTROL_ACK_FRAME + CONTROL_DIRECTION_UPLOAD;
	std::string s = "";
	time_t now = time(0);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.to_String_X2(inner_function);
	s += dashou.to_String_X2(function);
	s += dashou.to_String_X2(error);
	s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
	s += TAIL;
	return s;
}

std::string gen_ServiceBoard_Entry_To_Webhost_Request_Msg()
{
	int length = 188;
	int inner_function = 149;    // 0x81
	int serial = (++localSerialUpLink);
	std::string s = "";
	time_t now = time(0);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.to_String_X2(inner_function);
	s += dashou.calcCurrentTime(now);
	s += Online_master_port;
	s += Online_master_ip;
	s += Online_slave_port;
	s += Online_slave_ip;
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += Garage_ID;
	s += CITY_ID;
	s += Service_board_version;
	s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
	s += TAIL;
	return s;
}

std::string gen_ServiceBoard_Init_To_Webhost_Request_Msg()
{
	int length = 50;
	int inner_function = 128 + 4; // 132 = 0x80 || 0x04
	int serial = (++localSerialUpLink);
	std::string s = "";
	time_t now = time(0);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.to_String_X2(inner_function);
	s += dashou.calcCurrentTime(now);
	s += "060a8000E901";
	s += Service_board_version_short;
	s += dashou.to_String_X2(server_site.address);
	s += SITE_STATUS_SERVICE_BOARD;
	s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
	s += TAIL;
	return s;
}

std::string gen_ServiceBoard_Init_Done_To_Webhost_Request_Msg()
{
	int inner_function = 132;    // 0x84
	int length = 161;
	int serial = ++localSerialUpLink;
	std::string s = "";
	time_t now = time(0);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.to_String_X2(inner_function);
	s += dashou.calcCurrentTime(now);
	s += "070a2d0001000000";
	s += CITY_ID;
	s += "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	s += dashou.to_String_X2(server_site.address);
	s += "ffffff";
	s += dashou.to_String_X2(server_site.type);
	s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
	s += TAIL;
	return s;
}

bool initServiceBoard(DashouParser *parser_host)
{
	std::cout << "ini Web" << std::endl;
	std::string bytes = "";
	unsigned char WebHost_buffer[DEFAULT_BUFLEN] = "";
	// Send Init request 202
	bytes = "";
	bytes = gen_ServiceBoard_Entry_To_Webhost_Request_Msg();
	int iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
	if (iResult <= 0)
	{
		std::cout << "Error sending Init 202 to Web Host" << std::endl;
                return false;
	}
	else
	{
            //std::cout << "request Init 202 to Web Host" << std::endl;
	}
	// Receive Init request Ack 16
	int bytesRec = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
	if (bytesRec <= 0)
	{
            std::cout << "Error recv Web Host ACK" << std::endl;
            return false;
	}
	else
	{
		//std::cout << "recv Web Host ACK 202" << std::endl;
                parser_host->parse2(WebHost_buffer);
	}
	
        sleep(1);
	// Send Init request 64
	bytes = "";
	bytes = gen_ServiceBoard_Init_To_Webhost_Request_Msg();
	iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
	if (iResult <= 0)
	{
		std::cout << "Error sending Init 64 to Web Host" << std::endl;
                return false;
	}
	else
	{
		//std::cout << "request Init 64 to Web Host" << std::endl;
	}
	// Receive Sys Param frame 178
	bytesRec = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
	if (bytesRec <= 0)
	{
		std::cout << "Error recv Web Host Sys Param 178" << std::endl;
                return false;
	}
	else
	{
		//std::cout << "recv Web Host Sys Param 178" << std::endl;
                parser_host->parse2(WebHost_buffer);
	}

	// Send Sys param ack 16
	bytes = "";
	bytes = gen_ServiceBoard_ACK_Msg(parser_host->serial, parser_host->function, 0);
	iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
	if (iResult <= 0)
	{
		std::cout << "Error sending Sys Param ACK" << std::endl;
                return false;
	}
	else
	{
		//std::cout << "sending Sys Param ACK" << std::endl;
	}
	// Receive Sys Param frame 16
	bytesRec = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
	if (bytesRec <= 0)
	{
		std::cout << "Error recv Web Host Sys Param 16" << std::endl;
                return false;
	}
        else
	{
		//std::cout << "recv Web Host Sys Param 16" << std::endl;
                parser_host->parse2(WebHost_buffer);
	}
	

	// Receive Balance notification 20   
	bytesRec = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
	if (bytesRec <= 0)
	{
		std::cout << "Error recv Web Host Balance notification 20" << std::endl;
                return false;
	}
        else
        {
            //std::cout << "recv Web Host Balance notification 20" << std::endl;
            parser_host->parse2(WebHost_buffer);
            time_t adjust_time = parser_host->datetime;
            struct tm * webhost_time;
            webhost_time = localtime(&adjust_time);
            setDateTime(webhost_time->tm_mday, webhost_time->tm_mon + 1, webhost_time->tm_year + 1900, webhost_time->tm_hour, webhost_time->tm_min, webhost_time->tm_sec);
        }
	

	// Send Sys param Balance notification ack 16
	bytes = "";
	bytes = gen_ServiceBoard_ACK_Msg(parser_host->serial, parser_host->function, 0);
	iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
	if (iResult <= 0)
	{
		std::cout << "Error sending Sys param Balance notification ACK" << std::endl;
                return false;
	}
        else
        {
		//std::cout << "sending Sys param Balance notification ACK" << std::endl;
	}
	// Receive Expire forecast 168
	bytesRec = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
	if (bytesRec <= 0)
	{
            std::cout << "Error recv Web Host Expire forecast 168" << std::endl;
            return false;
	}
	else
        {
            //std::cout << "recv Web Host Expire forecast 168" << std::endl;
            parser_host->parse2(WebHost_buffer);
        }

	// Send Sys param Expire forecast ack 16
	bytes = "";
	bytes = gen_ServiceBoard_ACK_Msg(parser_host->serial, parser_host->function, 0);
	iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
	if (iResult <= 0)
	{
            std::cout << "Error sending Sys param Expire forecast ACK" << std::endl;
            return false;
	}
        else
        {
            //std::cout << "sending Sys param Expire forecast ACK" << std::endl;
        }

	// Send Sys param Camera site ack 175
	bytes = "";
	bytes = gen_ServiceBoard_Init_Done_To_Webhost_Request_Msg();
	iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
	if (iResult <= 0)
	{
		std::cout << "Error sending Init Done To Webhost" << std::endl;
                return false;
	}
        else
        {
            //std::cout << "sending Init Done To Webhost" << std::endl;
        }

	// Receive Camera site 16
	bytesRec = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
	if (bytesRec <= 0)
	{
		std::cout << "Error recv Web Host done ini ack 16" << std::endl;
                return false;
	}
        else
        {
            //std::cout << "recv Web Host done ini ack 16" << std::endl;
            parser_host->parse2(WebHost_buffer);
        }
        return true;
}

std::string gen_ServiceBoard_Heartbeat_Site_To_Webhost_Request_Msg(Site_type site)
{
	int inner_function = 131;    // 0x83
	int length = 27;
	int serial = ++localSerialUpLink;
	std::string s = "";
	time_t now = time(0);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.to_String_X2(inner_function);
	s += dashou.calcCurrentTime(now);
	s += "ff7fff7f0000ff7fff7fff7f0000c010";
	s += dashou.to_String_X2(site.address);
        if(site.status == 0)
        {
            s += "000000";
        }
        else
        {
            s += "ffffff";
        }
        site.type = (site.type < 128) ? site.type : site.type - 128; // augly fix for stupied bug
        std::cout << "site.type = " << site.type << " and local Serial UpLink = " << localSerialUpLink << "\n";
	s += dashou.to_String_X2(site.type);
	s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
	s += TAIL;
	return s;//Dashou.StringToByteArray(s);
}

bool heartbeat(int zone_log_counter, int zone_log_index, DashouParser *parser_host)
{
    try
    {
        std::string log_messege = "";
        std::string bytes = "";
        unsigned char WebHost_buffer[DEFAULT_BUFLEN] = "";
        int bytesRec;
        while(sites[heartbeatIndex].id <= 0)
        {
            heartbeatIndex++;
            if (heartbeatIndex == sites.size()) 
            {
                heartbeatIndex = 0;
            }
        }
        if (heartbeatIndex < sites.size() && webHost_Client_socket != INVALID_SOCKET)
        {
            //Send Heartbeat frame 41 
            bytes = "";
            bytes = gen_ServiceBoard_Heartbeat_Site_To_Webhost_Request_Msg(sites[heartbeatIndex]);
            log_messege += log_udp.HEARTBEAT_messege_Builder(sites[heartbeatIndex], accounts_sum);
            if(zone_log_counter == 9)
            {
                log_messege += log_udp.zone_info_messege_Builder(Zones, zone_log_index);
            }
            web_host_locked = true;
            int iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
            if (iResult <= 0)
            {
                std::cout << "Error sending Heartbeat to Web Host" << std::endl;
                webHost_Client_socket = INVALID_SOCKET;
                return false;
            }
            bytesRec = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
            if (bytesRec <= 0)
            {
                std::cout << "Error recv Heartbeat ack Web Host" << std::endl;
                webHost_Client_socket = INVALID_SOCKET;
                return false;
            }
            web_host_locked = false;
            parser_host->parse2(WebHost_buffer);
            log_messege += log_udp.ACK_webhost_messege_Builder(parser_host);
            heartbeatIndex++;
            log_udp.messege_Sender(log_messege);
        }	
    }
    catch(...)
    {
        
    }
    return true;
}

std::string gen_ServiceBoard_Init_Device_To_Webhost_Request_Msg(Site_type site)
{
	int inner_function = 132;    // 0x84
	int length = 50;
	int serial = ++localSerialUpLink;
	std::string s = "";
	time_t now = time(0);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.to_String_X2(inner_function);
	s += dashou.calcCurrentTime(now);
	if (site.type == SITE_TYPE_EXIT_BOARD)
	{
		s += "340b8000";
		s += dashou.to_String_X2(site.address);
		s += dashou.to_String_X2(site.type);
		s += Exit_Board_Version;
		s += "00";
	}
	else if (site.type == SITE_TYPE_ENTRY_BOARD)
	{
		s += "300b8000";
		s += dashou.to_String_X2(site.address);
		s += dashou.to_String_X2(site.type);
		s += Entry_Board_Version;
		s += "00";
	}
	else if (site.type == SITE_TYPE_TABLET_APP)
	{
		s += "210c8000";
		s += dashou.to_String_X2(site.address);
		s += dashou.to_String_X2(site.type);
		s += "8f00CD";
		s += "000000000000000000000000000000000000000000000000000000000000";
	}
	s += dashou.to_String_X2(server_site.address);
	s += "ffffff";//SITE_STATUS_SERVICE_BOARD
	s += dashou.to_String_X2(server_site.type);
	s += dashou.calcChecksum_client(length, serial, CONTROL_ENTRY_REQUEST_RESPONSE, inner_function);
	s += TAIL;
	return s;
}

void registerNewSiteToWebHost(Site_type site)
{
	std::string bytes = "";
	char WebHost_buffer[DEFAULT_BUFLEN] = "";
	int bytesRec;
	bytes = "";
	bytes = gen_ServiceBoard_Init_Device_To_Webhost_Request_Msg(site);
	int iResult = SSL_write(ssl, (char *)dashou.StringToByteArray(bytes), strlen(bytes.c_str()) / 2);
	if (iResult == SOCKET_ERROR)
	{
            std::cout << "Error sending Init 64 to Web Host";
	}
}

void Handle_webhost_received_data(unsigned char* webhost_buffer, DashouParser *parser_host)
{	
    unsigned char WebHost_buffer[DEFAULT_BUFLEN] = "";
    unsigned char client_buffer[DEFAULT_BUFLEN] = "";
    int iResult = 0;
    std::string report = "";
    std::string buffer = "";
    switch (parser_host->function)
    {
        case 10:// Space Counting ~ Refresh Zones
        {
            buffer = "";
            buffer = genspace_Counting_response_to_webhost(parser_host->datetime, parser_host->setting_Type, parser_host->zone_serial);
            SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
            SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
            buffer = "";
            buffer = genspace_Counting_confirm_to_webhost(parser_host->datetime, parser_host->setting_Type, parser_host->zone_serial);
            SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
            std::cout << "web host request Refresh Zones...\n" << std::endl;
        }
        break;
        case 23:
        {

        }
        break;
        case 27: // charge setting
        {
            report = "";
            time_t start_time = dashou.char_to_time_t(webhost_buffer[19], webhost_buffer[20], webhost_buffer[21], webhost_buffer[22], webhost_buffer[23], webhost_buffer[24]);
            time_t end_time = dashou.char_to_time_t(webhost_buffer[25], webhost_buffer[26], webhost_buffer[27], webhost_buffer[28], webhost_buffer[29], webhost_buffer[30]);
            int balance = dashou.get_X4_Number(webhost_buffer[39], webhost_buffer[40], webhost_buffer[41], webhost_buffer[42]);
            char ticket[20] = "";
            for(int i = 0; i < 19; i++)
            {
                ticket[i] = webhost_buffer[43 + i];
            }
            char plate[12] = "";
            for(int i = 0; i < 12; i++)
            {
                plate[i] = webhost_buffer[63 + i];
            }
            std::cout << "plate is " << std::string(plate) << "\n";
            event_charge current_event_charge(mysql);
            accountInfo current_accountInfo(mysql);
            account_state current_account_state(mysql);
            current_accountInfo.Select_account_by_plate(plate, Current_Settings.plate_match_level);
            current_account_state.Select_account_state_by_plate(plate, Current_Settings.plate_match_level);
            switch (parser_host->Setting_type)
            {
                case 32:
                {
                    if(current_accountInfo.id == 0)
                    {
                        std::cout << "Account not found to charge\n";
                    }
                    else
                    {
                        current_accountInfo.start_time = start_time;
                        current_accountInfo.end_time = end_time;
                        current_accountInfo.Insert_update_accountInfo();
                        current_event_charge.aid = get_event_charge_insert_aid();
                        current_event_charge.gid = Current_garage.gid;
                        current_event_charge.in_serial = current_account_state.inserial;
                        current_event_charge.site = 255;
                        current_event_charge.charge_time = time(0);
                        current_event_charge.charge_serial = ++gen_APPpay_serial;
                        current_event_charge.actually_pay = 0;
                        current_event_charge.charge_type = 0;
                        current_event_charge.payment_type = time_issue_cash;
                        current_event_charge.start_time = current_accountInfo.start_time;
                        current_event_charge.end_time = current_accountInfo.end_time;
                        strcpy(current_event_charge.plate, plate);
                        current_event_charge.rece_time = time(0);
                        current_event_charge.Insert_update_charge_event();
                    }
                }
                break;
                case 33:
                {
                    if(current_accountInfo.id == 0)
                    {
                        std::cout << "Account not found to charge\n";
                    }
                    else
                    {
                        current_event_charge.aid = get_event_charge_insert_aid();
                        current_event_charge.gid = Current_garage.gid;
                        current_event_charge.in_serial = current_account_state.inserial;
                        current_event_charge.site = 255;
                        current_event_charge.charge_time = time(0);
                        current_event_charge.charge_serial = ++gen_APPpay_serial;
                        current_event_charge.start_time = current_accountInfo.start_time;
                        current_event_charge.end_time = current_accountInfo.end_time;
                        current_event_charge.actually_pay = 0;
                        current_event_charge.charge_type = 0;
                        current_event_charge.payment_type = num_issue_cash;
                        strcpy(current_event_charge.plate, plate);
                        current_event_charge.balance = balance;
                        current_event_charge.rece_time = time(0);
                        current_event_charge.Insert_update_charge_event();
                    }
                }
                break;
                case 34:
                {
                    if(current_accountInfo.id == 0)
                    {
                        std::cout << "Account not found to charge\n";
                    }
                    else
                    {
                        current_event_charge.aid = get_event_charge_insert_aid();
                        current_event_charge.gid = Current_garage.gid;
                        current_event_charge.in_serial = current_account_state.inserial;
                        current_event_charge.site = 255;
                        current_event_charge.charge_time = time(0);
                        current_event_charge.charge_serial = ++gen_APPpay_serial;
                        current_event_charge.start_time = current_accountInfo.start_time;
                        current_event_charge.end_time = current_accountInfo.end_time;
                        current_event_charge.actually_pay = 0;
                        current_event_charge.charge_type = 0;
                        current_event_charge.payment_type = store_issue_cash;
                        strcpy(current_event_charge.plate, plate);
                        current_event_charge.balance = balance;
                        current_event_charge.rece_time = time(0);
                        current_event_charge.Insert_update_charge_event();
                    }
                }
                break;
            }
            buffer = "";
            buffer = gen_ServiceBoard_Pay_Request_Msg100(current_event_charge, 1);
            SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
            web_host_locked = true;
            iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
            if (iResult < 0)
            {
                std::cout << "Error recv Pay 100 Response ACK...\n";
            }
            web_host_locked = false;
            parser_host->parse2(WebHost_buffer);
            report += log_udp.ACK_webhost_messege_Builder(parser_host);
            log_udp.messege_Sender(report);
        }
        break;
        case 29: // Settings
        {
            switch (parser_host->Setting_type)
            {
                case 1: // info
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int new_gid = ((webhost_buffer[7] * 0x100) + webhost_buffer[6]) * 100000 + (webhost_buffer[9] * 0x100) +  webhost_buffer[8];
                    char carPark_name[65] = "";
                    for(int i = 0; i < 64; i++)
                    {
                        carPark_name[i] = webhost_buffer[i + 19];
                    }
                    char carPark_addr[105] = "";
                    for(int j = 0; j < 104; j++)
                    {
                        carPark_addr[j] = webhost_buffer[j + 83];
                    }
                    std::string carPark_Brief = "";
                    for(int i = 0; i < 10240 ; i++)
                    {
                        if(webhost_buffer[i + 187] != '#')
                        {
                            carPark_Brief.push_back(webhost_buffer[i + 187]);
                        }
                        if(webhost_buffer[i + 187] == '#' && webhost_buffer[i + 188] == '#')
                        {
                            break;
                        }
                    }
                    std::string system_Notice = "";
                    for(int i = 0; i < 10240 ; i++)
                    {
                        if(webhost_buffer[i + 187 + carPark_Brief.length() + 2] != '#')
                        {
                            system_Notice.push_back(webhost_buffer[i + 187 + carPark_Brief.length() + 2]);
                        }
                        if(webhost_buffer[i + 187 + carPark_Brief.length() + 2] == '#' && webhost_buffer[i + 188 + carPark_Brief.length() + 2] == '#')
                        {
                            break;
                        }
                    }
                    std::string Reservation = "";
                    for(int i = 0; i < 10240 ; i++)
                    {
                        if(webhost_buffer[i + 187 + carPark_Brief.length() + system_Notice.length() + 4] != '#')
                        {
                            Reservation.push_back(webhost_buffer[i + 187 + carPark_Brief.length() + system_Notice.length() + 4]);
                        }
                        if(webhost_buffer[i + 187 + carPark_Brief.length() + system_Notice.length() + 4] == '#' && webhost_buffer[i + 188 + carPark_Brief.length() + system_Notice.length() + 4] == '#')
                        {
                            break;
                        }
                    }

                    std::string Share_Parking = "";
                    for(int i = 0; i < 10240 ; i++)
                    {
                        Share_Parking.push_back(webhost_buffer[i + 187 + carPark_Brief.length() + system_Notice.length() + Reservation.length() + 6]);
                        if(webhost_buffer[i + 187 + carPark_Brief.length() + system_Notice.length() + Reservation.length() + 10] == 0xcd)
                        {
                            break;
                        }
                    }
                    std::cout << "new_gid = " << new_gid <<  ".\n" ;
                    std::cout << "carPark_name is " << std::string(carPark_name) << ".\n";
                    std::cout << "carPark_addr is " << std::string(carPark_addr) << ".\n";
                    std::cout << "carPark_Brief is " << carPark_Brief <<  ".\n" ;
                    std::cout << "system_Notice is " << system_Notice <<  ".\n" ;
                    std::cout << "Reservation   is " << Reservation <<  ".\n" ;
                    std::cout << "Share_Parking is " << Share_Parking <<  ".\n" ;
                    strcpy(Current_garage.name,carPark_name);
                    strcpy(Current_garage.addr,carPark_addr);
                    strcpy(Current_garage.description,carPark_Brief.c_str());
                    strcpy(Current_garage.notice,system_Notice.c_str());
                    strcpy(Current_garage.reservation_brief,Reservation.c_str());
                    strcpy(Current_garage.share_brief,Share_Parking.c_str());
                    Current_garage.insert_update_garage_info();
                    buffer = "";
                    buffer = genSysParam_response_garage_info_to_webhost(Current_garage, Setting_type);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host one proof on car ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);

                }
                break;
                case 3:// one proof on car
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int site_count = webhost_buffer[19];
                    int site_address = 0;
                    int site_to_change[256];
                    memset(site_to_change, 0, sizeof(site_to_change));
                    for(int i = 0; i < site_count; i++)
                    {
                        site_address = webhost_buffer[20 + 2 * i];
                        site_to_change[i] = find_site_by_address(site_address);
                        parser_host->oneCard_oneCar = webhost_buffer[21 + 2 * i];
                        if(site_to_change[i] > 0)
                        {
                            sites[site_to_change[i]].oneCard_oneCar = parser_host->oneCard_oneCar;
                            std::cout << "Client #" << sites[site_to_change[i]].id <<" : address (172.16.57." << site_address << ") : ( one proof one car = " << sites[site_to_change[i]].oneCard_oneCar << " ).\n";
                            report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[site_to_change[i]], All_Cameras[0]);
                            sites[site_to_change[i]].Insert_Update_Site_type();
                            if(sites[site_to_change[i]].status == 0xffffff)
                            {
                                buffer = "";
                                buffer = genSysParam(sites[site_to_change[i]], parser_host);
                                send(sites[site_to_change[i]].socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
                                while(!site_ACK_setting);
                                if(site_ACK_setting)
                                {
                                    site_ACK_setting = false;
                                    report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_SITE_SETTING, localSerialDownLink, All_Cameras,site_to_change[i], sites);                               
                                    parser_host->serial = site_ACK_setting_serial;
                                    parser_host->Setting_type = site_ACK_setting_type;
                                    report += log_udp.ACK_sites_messege_Builder(sites[site_to_change[i]], parser_host);
                                }
                            }
                        }
                        else
                        {
                            std::cout << "Client #" << parser_host->site_address << " : not exist\n";
                        }
                    }
                    buffer = "";
                    buffer = genSysParam_response_onecaroneproof_to_webhost(site_to_change, Setting_type, site_count);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host one proof on car ACK...\n";
                    }
                    web_host_locked = false;
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 7:// group inner
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int count = webhost_buffer[19];
                    int inner_group_serial[256];
                    memset(inner_group_serial, 0, sizeof(inner_group_serial));
                    int sites_count[256];
                    memset(sites_count, 0, sizeof(sites_count));
                    std::vector<group_inner> temp_group_inner;
                    int byte_index = 20;
                    for(int j = 0; j < count; j++)
                    {
                        inner_group_serial[j] = webhost_buffer[byte_index];
                        group_inner current_group_inner(mysql);
                        current_group_inner.createtime = time(0);
                        current_group_inner.Select_group_inner_by_ID(inner_group_serial[j]);
                        current_group_inner.id = inner_group_serial[j];
                        current_group_inner.gid = Current_garage.gid;
                        if(webhost_buffer[byte_index + 1] == 0xff)
                        {
                            current_group_inner.flag = 0;
                        }
                        else
                        {
                            for(int i = 0; i < 32; i++)
                            {
                                current_group_inner.name[i] = webhost_buffer[byte_index + 1 + i];
                            }
                            current_group_inner.flag = 1;
                        }
                        current_group_inner.inner_charge = webhost_buffer[byte_index + 33];
                        current_group_inner.outer_charge = webhost_buffer[byte_index + 34];
                        sites_count[j] = webhost_buffer[byte_index + 35];
                        memset(current_group_inner.sites_list, 0, sizeof(current_group_inner.sites_list));
                        for(int i = 0; i < sites_count[j]; i++)
                        {
                            current_group_inner._sites_list[i] = webhost_buffer[byte_index + 36 + i];
                            strcat(current_group_inner.sites_list, std::to_string(current_group_inner._sites_list[i]).c_str());
                            if(i != sites_count[j] - 1)
                            {
                                strcat(current_group_inner.sites_list, ",");
                            }
                        }
                        byte_index += 36 + sites_count[j];
                        temp_group_inner.push_back(current_group_inner);
                    }
                    int _operator = webhost_buffer[byte_index];
                    std::cout << "group inner setting:\n";
                    for(int i = 0; i < count; i++)
                    {
                        inner_group_serial[i];
                        temp_group_inner[i].Insert_update_group_inner();
                        printf("gid\tname\t\t\tinner charge\touter charge\tsites list\tflag\n");
                        printf("%ld\t%s\t%d\t\t%d\t\t%s\t\t%d\n", temp_group_inner[i].gid, temp_group_inner[i].name, temp_group_inner[i].inner_charge, temp_group_inner[i].outer_charge, temp_group_inner[i].sites_list, temp_group_inner[i].flag);
                    }
                    buffer = "";
                    buffer = genSysParam_response_group_inner_to_webhost(Setting_type, count, sites_count, inner_group_serial);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host one proof on car ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 10:// confirm plate
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int site_count = webhost_buffer[19];
                    int site_address = 0;
                    int site_to_change[256];
                    memset(site_to_change, 0, sizeof(site_to_change));
                    for(int i = 0; i < site_count; i++)
                    {
                        site_address = webhost_buffer[20 + 2 * i];
                        site_to_change[i] = find_site_by_address(site_address);
                        parser_host->entryPresetLicensePlateNumber = webhost_buffer[21 + 2 * i];
                        if(site_to_change[i] > 0)
                        {
                            sites[site_to_change[i]].entryPresetLicensePlateNumber = parser_host->entryPresetLicensePlateNumber;
                            std::cout << "Client #" << sites[site_to_change[i]].id <<" : address (172.16.57." << site_address << ") : ( confirm plate = " << sites[site_to_change[i]].entryPresetLicensePlateNumber << " ).\n";
                            report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[site_to_change[i]], All_Cameras[0]);
                            sites[site_to_change[i]].Insert_Update_Site_type();
                            if(sites[site_to_change[i]].status == 0xffffff)
                            {
                                buffer = "";
                                buffer = genSysParam(sites[site_to_change[i]], parser_host);
                                send(sites[site_to_change[i]].socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
                                while(!site_ACK_setting);
                                if(site_ACK_setting)
                                {
                                    site_ACK_setting = false;
                                    report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_SITE_SETTING, localSerialDownLink, All_Cameras,site_to_change[i], sites);                               
                                    parser_host->serial = site_ACK_setting_serial;
                                    parser_host->Setting_type = site_ACK_setting_type;
                                    report += log_udp.ACK_sites_messege_Builder(sites[site_to_change[i]], parser_host);
                                }
                            }
                        }
                        else
                        {
                            std::cout << "Client #" << parser_host->site_address << " : not exist\n";
                        }
                    }  
                    buffer = "";
                    buffer = genSysParam_response_confirm_plate_to_webhost(site_to_change, Setting_type, site_count);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host confirm plate ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 11:// auto open Free
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int site_count = webhost_buffer[19];
                    int site_address = 0;
                    int site_to_change[256];
                    memset(site_to_change, 0, sizeof(site_to_change));
                    for(int i = 0; i < site_count; i++)
                    {
                        site_address = webhost_buffer[20 + 2 * i];
                        site_to_change[i] = find_site_by_address(site_address);
                        parser_host->exitFreeLetPass = webhost_buffer[21 + 2 * i];
                        if(site_to_change > 0)
                        {
                            sites[site_to_change[i]].exitFreeLetPass = parser_host->exitFreeLetPass;
                            std::cout << "Client #" << sites[site_to_change[i]].id <<" : address (172.16.57." << site_address << ") : ( auto open Free = " << sites[site_to_change[i]].exitFreeLetPass << " ).\n";
                            report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[site_to_change[i]], All_Cameras[0]);
                            sites[site_to_change[i]].Insert_Update_Site_type();
                            if(sites[site_to_change[i]].status == 0xffffff)
                            {
                                buffer = "";
                                buffer = genSysParam(sites[site_to_change[i]], parser_host);
                                send(sites[site_to_change[i]].socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
                                while(!site_ACK_setting);
                                if(site_ACK_setting)
                                {
                                    site_ACK_setting = false;
                                    report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_SITE_SETTING, localSerialDownLink, All_Cameras,site_to_change[i], sites);                               
                                    parser_host->serial = site_ACK_setting_serial;
                                    parser_host->Setting_type = site_ACK_setting_type;
                                    report += log_udp.ACK_sites_messege_Builder(sites[site_to_change[i]], parser_host);
                                }
                            }
                        }
                        else
                        {
                            std::cout << "Client #" << parser_host->site_address << " : not exist\n";
                        }
                    }
                    buffer = "";
                    buffer = genSysParam_response_exitFreeLetPass_to_webhost(site_to_change, Setting_type, site_count);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host auto open Free ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);  
                }
                break;
                case 12: // plate match
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    Current_Settings.plate_match_level = 8 - webhost_buffer[19];
                    std::cout << "All Clients set ( plate match = " << Current_Settings.plate_match_level << " ).\n";
                    report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    Current_Settings.update_Setting();
                    buffer = "";
                    buffer = genSysParam_response_plate_match_level_to_webhost(Setting_type, Current_Settings.plate_match_level);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host plate match level ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 13:// Full no entry
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int site_count = webhost_buffer[19];
                    int site_address = 0;
                    int site_to_change[256];
                    memset(site_to_change, 0, sizeof(site_to_change));
                    for(int i = 0; i < site_count; i++)
                    {
                        site_address = webhost_buffer[20 + 3 * i];
                        parser_host->monthlyParkingFullAccessDeny = webhost_buffer[21 + 3 * i];
                        parser_host->hourlyParkingFullAccessDeny = webhost_buffer[22 + 3 * i];
                        site_to_change[i] = find_site_by_address(site_address);
                        if(site_to_change[i] > 0)
                        {
                            sites[site_to_change[i]].monthlyParkingFullAccessDeny = parser_host->monthlyParkingFullAccessDeny;
                            sites[site_to_change[i]].hourlyParkingFullAccessDeny = parser_host->hourlyParkingFullAccessDeny;
                            std::cout << "Client #" << sites[site_to_change[i]].id <<" : address (172.16.57." << site_address << ") : ( Full no entry season : = " << sites[site_to_change[i]].monthlyParkingFullAccessDeny << " ) , " << "( Full no entry hourly : = " << sites[site_to_change[i]].hourlyParkingFullAccessDeny << " ).\n";
                            report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[site_to_change[i]], All_Cameras[0]);
                            sites[site_to_change[i]].Insert_Update_Site_type();
                            if(sites[site_to_change[i]].status == 0xffffff)
                            {
                                buffer = "";
                                //buffer = genSysParam(sites[site_to_change[i]], parser_host);
                                send(sites[site_to_change[i]].socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
                                while(!site_ACK_setting);
                                if(site_ACK_setting)
                                {
                                    site_ACK_setting = false;
                                    report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_SITE_SETTING, localSerialDownLink, All_Cameras,site_to_change[i], sites);                               
                                    parser_host->serial = site_ACK_setting_serial;
                                    parser_host->Setting_type = site_ACK_setting_type;
                                    report += log_udp.ACK_sites_messege_Builder(sites[site_to_change[i]], parser_host);
                                }
                            }
                        }
                        else
                        {
                            std::cout << "Client #" << parser_host->site_address << " : not exist\n";
                        }
                    }
                    buffer = "";
                    buffer = genSysParam_response_Full_no_entry_to_webhost(site_to_change, Setting_type, site_count);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host auto open Free ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 14: // balance Notification Threshold 
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    Current_Settings.alarm_balance = dashou.get_X4_Number
                    (webhost_buffer[19],webhost_buffer[20],webhost_buffer[21],webhost_buffer[22]);
                    std::cout << "All Clients set ( balance Notification Threshold = " << Current_Settings.alarm_balance << " SYP ).\n";
                    report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    Current_Settings.update_Setting();
                    std::queue<std::string> sites_ACKs;
                    int really_sent = 0;
                    for(int i = 1; i < sites.size(); i++)
                    {
                        if(sites[i].address != -1 && sites[i].status == 0xffffff && sites[i].id != server_site.id)
                        {
                            sites[i].balanceNotificationThreshold = Current_Settings.alarm_balance;
                            buffer = "";
                            buffer = genSysParamBalanceNotification(sites[i], parser_host);
                            send(sites[i].socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
                            while(!site_ACK_setting);
                            if(site_ACK_setting)
                            {
                                site_ACK_setting = false;
                                report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_BALANCE_NOTIFICATION, localSerialDownLink, All_Cameras, i, sites);
                                parser_host->serial = site_ACK_setting_serial;
                                parser_host->Setting_type = site_ACK_setting_type;
                                sites_ACKs.push(log_udp.ACK_sites_messege_Builder(sites[i], parser_host));
                                really_sent++;
                            }
                        }
                    }
                    for(int i = 0; i < really_sent; i++)
                    {
                        report += sites_ACKs.front();
                        sites_ACKs.pop();
                    }
                    buffer = "";
                    buffer = genSysParam_response_balanceNotificationThreshold_to_webhost(Setting_type, Current_Settings.alarm_balance);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host balance Notification Threshold ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 15: // expire Forecast Threshold
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    Current_Settings.alarm_enddata = dashou.get_X4_Number
                    (webhost_buffer[19],webhost_buffer[20],webhost_buffer[21],webhost_buffer[22]);
                    std::cout << "All Clients set ( expire Forecast Threshold = " << Current_Settings.alarm_enddata << " Days ).\n";
                    report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    Current_Settings.update_Setting();
                    std::queue<std::string> sites_ACKs;
                    int really_sent = 0;
                    for(int i = 1; i < sites.size(); i++)
                    {
                        if(sites[i].address != -1 && sites[i].status == 0xffffff && sites[i].id != server_site.id)
                        {
                            sites[i].expireForecastThreshold = Current_Settings.alarm_enddata ;
                            buffer = "";
                            buffer = genSysParamExpireForecast(sites[i], parser_host);
                            send(sites[i].socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
                            while(!site_ACK_setting);
                            if(site_ACK_setting)
                            {
                                site_ACK_setting = false;
                                report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_EXPIRE_FORECAST, localSerialDownLink, All_Cameras, i, sites);
                                parser_host->serial = site_ACK_setting_serial;
                                parser_host->Setting_type = site_ACK_setting_type;
                                sites_ACKs.push(log_udp.ACK_sites_messege_Builder(sites[i], parser_host));
                                really_sent++;
                            }
                        }
                    }
                    for(int i = 0; i < really_sent; i++)
                    {
                        report += sites_ACKs.front();
                        sites_ACKs.pop();
                    }
                    buffer = "";
                    buffer = genSysParam_response_expireForecastThreshold_to_webhost(Setting_type, Current_Settings.alarm_enddata);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host expire Forecast Threshold ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 16:// season to hourly
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int count = webhost_buffer[19];
                    int monthly_to_hourly_type_index = webhost_buffer[20] - 1;
                    std::string types = std::to_string(webhost_buffer[21]);
                    if(webhost_buffer[21] == 255)
                    {
                        monthly_to_hourly_list[monthly_to_hourly_type_index].flag = 0;
                    }
                    else
                    {
                        monthly_to_hourly_list[monthly_to_hourly_type_index].flag = 1;
                    }
                    strcpy(monthly_to_hourly_list[monthly_to_hourly_type_index].hour_charge_type ,types.c_str());
                    monthly_to_hourly_list[monthly_to_hourly_type_index]._operator = webhost_buffer[22];
                    report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    monthly_to_hourly_list[monthly_to_hourly_type_index].Update_monthly_to_hourly_type();
                    std::cout << "monthly to hourly list" << std::endl;
                    std::cout << "ID\t" << "GID\t" << "name\t\t" << "h_c_t\t" << "flag\t" << "operator\t" << "createtime\t" << std::endl;
                    for (int i = 0; i < monthly_to_hourly_list.size(); i++)
                    {
                        if(monthly_to_hourly_list[i].id > 0 && monthly_to_hourly_list[i].gid > 0 )
                        {
                            if(i == 2 || i == 4)
                            {
                                printf("%d\t%d\t%s\t%s\t%d\t%d\t\t%ld", monthly_to_hourly_list[i].id, monthly_to_hourly_list[i].gid, monthly_to_hourly_list[i].name, monthly_to_hourly_list[i].hour_charge_type, monthly_to_hourly_list[i].flag, monthly_to_hourly_list[i]._operator, monthly_to_hourly_list[i].create_time);
                                std::cout << std::endl;
                            }
                            else
                            {
                                printf("%d\t%d\t%s\t\t%s\t%d\t%d\t\t%ld", monthly_to_hourly_list[i].id, monthly_to_hourly_list[i].gid, monthly_to_hourly_list[i].name, monthly_to_hourly_list[i].hour_charge_type, monthly_to_hourly_list[i].flag, monthly_to_hourly_list[i]._operator, monthly_to_hourly_list[i].create_time);
                                std::cout << std::endl;
                            }
                        }
                    }
                    buffer = "";
                    buffer = genSysParam_response_monthly_to_hourly_to_webhost(Setting_type, count, monthly_to_hourly_list[monthly_to_hourly_type_index]);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host monthly to hourly ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 17:// Apply charging Standard
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int site_count = webhost_buffer[19];
                    int site_address = 0;
                    int site_to_change[256];
                    memset(site_to_change, 0, sizeof(site_to_change));
                    for(int i = 0; i < site_count; i++)
                    {
                        site_address = webhost_buffer[20 + 2 * i];
                        parser_host->id_PresetType_id = webhost_buffer[21 + 2 * i];
                        site_to_change[i] = find_site_by_address(site_address);
                        if(site_to_change[i] > 0)
                        {
                            sites[site_to_change[i]].id_PresetType_id = parser_host->id_PresetType_id;
                            std::cout << "Client #" << sites[site_to_change[i]].id <<" : address (172.16.57." << site_address << ") : ( PresetChargeTypeID = " << sites[site_to_change[i]].id_PresetType_id << " ).\n";
                            report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[site_to_change[i]], All_Cameras[0]);
                            sites[site_to_change[i]].Insert_Update_Site_type();
                        }
                        else
                        {
                            std::cout << "Client #" << parser_host->site_address << " : not exist\n";
                        }
                    }
                    buffer = "";
                    buffer = genSysParam_response_id_PresetType_to_webhost(site_to_change, Setting_type, site_count);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host Apply charging Standard ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 18:// site in site group
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int site_count = webhost_buffer[19];
                    int site_address = 0;
                    int site_to_change[256];
                    memset(site_to_change, 0, sizeof(site_to_change));
                    for(int i = 0; i < site_count; i++)
                    {
                        site_address = webhost_buffer[20 + 2 * i];
                        parser_host->id_PresetSite_in_Site_Group = webhost_buffer[21 + 2 * i];
                        site_to_change[i] = find_site_by_address(site_address);
                        if(site_to_change[i] > 0)
                        {
                            sites[site_to_change[i]].id_PresetSite_in_Site_Group = parser_host->id_PresetSite_in_Site_Group;
                            std::cout << "Client #" << sites[site_to_change[i]].id <<" : address (172.16.57." << site_address << ") : ( id Preset Site in Site Group = " << sites[site_to_change[i]].id_PresetSite_in_Site_Group << " ).\n";
                            report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[site_to_change[i]], All_Cameras[0]);
                            sites[site_to_change[i]].Insert_Update_Site_type();
                        }
                        else
                        {
                            std::cout << "Client #" << parser_host->site_address << " : not exist\n";
                        }
                    } 
                    buffer = "";
                    buffer = genSysParam_response_id_PresetSite_in_Site_Group_to_webhost(site_to_change, Setting_type, site_count);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host Apply charging Standard ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 19:// black list
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int count = webhost_buffer[19];
                    int idx_list = -1;
                    black_list_type tmp_black_account(mysql);
                    tmp_black_account.create_time = time(0);
                    tmp_black_account.gid = Current_Settings.gid;
                    tmp_black_account.id = webhost_buffer[20] + 256 * webhost_buffer[21];
                    tmp_black_account.ticket_type = webhost_buffer[22];
                    for(int i = 0; i < 19; i++)
                    {
                        tmp_black_account.ticket[i] = webhost_buffer[23 + i];
                    }
                    for(int i = 0; i < 12; i++)
                    {
                        tmp_black_account.plate[i] = webhost_buffer[42 + i];
                    }
                    for(int i = 0; i < 32; i++)
                    {
                        tmp_black_account.description[i] = webhost_buffer[54 + i];
                    }
                    bool add_to_black_list = webhost_buffer[86];
                    tmp_black_account._operator = webhost_buffer[87];
                    std::cout << "Black List ";
                    if(add_to_black_list)
                    {
                        std::cout << "Add blacklist\n";
                        char buffer[BUFFER_SIZE];
                        int byte_rec = 0;
                        if(check_blacklist_exist(std::string(tmp_black_account.plate)))
                        {
                            std::cout << "blacklist is exist\n";
                            for(int i = 0; i < All_Cameras.size(); i++)
                            {
                                std::string camera_address = std::string(Current_Settings.site_prefix) + "." +std::string(All_Cameras[i].ip);
                                std::string find_black_list = build_find_black_list_uri(tmp_black_account.plate);
                                std::string find_car_black_list = HTTP_request_URL_HEADER + find_black_list + OPTION_HTTP_request_PREV_HOST + camera_address + OPTION_HTTP_request_APRE_HOST;
                                byte_rec = send_http_request(camera_address.c_str(), find_car_black_list + HTTP_request_TAIL, buffer);
                                response_header response = get_response_info(std::string(buffer));
                                std::string authorized_find_car_black_list = find_car_black_list + struct_response_to_string(response, "admin", "admin123", find_black_list) + HTTP_request_TAIL;
                                byte_rec = send_http_request(camera_address.c_str(), authorized_find_car_black_list, buffer);
                                int record_num = get_record_Number(get_response_CONTENT(std::string(buffer), byte_rec));
                                std::string update_black_list = build_update_black_list_uri(tmp_black_account.plate, record_num);
                                std::string update_car_black_list = HTTP_request_URL_HEADER + update_black_list + OPTION_HTTP_request_PREV_HOST + camera_address + OPTION_HTTP_request_APRE_HOST;
                                byte_rec = send_http_request(camera_address.c_str(), update_car_black_list + HTTP_request_TAIL, buffer);
                                response = get_response_info(std::string(buffer));
                                std::string authorized_update_car_black_list = update_car_black_list + struct_response_to_string(response, "admin", "admin123", update_black_list) + HTTP_request_TAIL;
                                byte_rec = send_http_request(camera_address.c_str(), authorized_update_car_black_list, buffer);
                                std::cout << get_response_CONTENT(std::string(buffer), byte_rec) << "\n";
                            }
                        }
                        else
                        {
                            std::cout << "blacklist is not exist\n";
                            for(int i = 0; i < All_Cameras.size(); i++)
                            {
                                std::string camera_address = std::string(Current_Settings.site_prefix) + "." +std::string(All_Cameras[i].ip);
                                std::string insert_black_list = build_insert_black_list_uri(tmp_black_account.plate);
                                std::string insert_car_black_list = HTTP_request_URL_HEADER + insert_black_list + OPTION_HTTP_request_PREV_HOST + camera_address + OPTION_HTTP_request_APRE_HOST;
                                byte_rec = send_http_request(camera_address.c_str(), insert_car_black_list + HTTP_request_TAIL, buffer);
                                response_header response = get_response_info(std::string(buffer));
                                std::string authorized_insert_car_black_list = insert_car_black_list + struct_response_to_string(response, "admin", "admin123", insert_black_list) + HTTP_request_TAIL;
                                byte_rec = send_http_request(camera_address.c_str(), authorized_insert_car_black_list, buffer);
                                std::cout << get_response_CONTENT(std::string(buffer), byte_rec) << "\n";
                            }
                        }
                    }
                    else
                    {
                        std::cout << "Remove blacklist\n";
                        char buffer[BUFFER_SIZE];
                        int byte_rec = 0;
                        for(int i = 0; i < All_Cameras.size(); i++)
                        {
                            std::string camera_address = std::string(Current_Settings.site_prefix) + "." +std::string(All_Cameras[i].ip);
                            std::string find_black_list = build_find_black_list_uri(tmp_black_account.plate);
                            std::string find_car_black_list = HTTP_request_URL_HEADER + find_black_list + OPTION_HTTP_request_PREV_HOST + camera_address + OPTION_HTTP_request_APRE_HOST;
                            byte_rec = send_http_request(camera_address.c_str(), find_car_black_list + HTTP_request_TAIL, buffer);
                            response_header response = get_response_info(std::string(buffer));
                            std::string authorized_find_car_black_list = find_car_black_list + struct_response_to_string(response, "admin", "admin123", find_black_list) + HTTP_request_TAIL;
                            byte_rec = send_http_request(camera_address.c_str(), authorized_find_car_black_list, buffer);
                            int record_num = get_record_Number(get_response_CONTENT(std::string(buffer), byte_rec));
                            std::string remove_black_list = build_remove_black_list_uri(record_num);
                            std::string remove_car_black_list = HTTP_request_URL_HEADER + remove_black_list + OPTION_HTTP_request_PREV_HOST + camera_address + OPTION_HTTP_request_APRE_HOST;
                            byte_rec = send_http_request(camera_address.c_str(), remove_car_black_list + HTTP_request_TAIL, buffer);
                            response = get_response_info(std::string(buffer));
                            std::string authorized_remove_car_black_list = remove_car_black_list + struct_response_to_string(response, "admin", "admin123", remove_black_list) + HTTP_request_TAIL;
                            byte_rec = send_http_request(camera_address.c_str(), authorized_remove_car_black_list, buffer);
                            std::cout << get_response_CONTENT(std::string(buffer), byte_rec) << "\n";
                        }
                    }
                    std::cout << "account id = " << tmp_black_account.id << ".\n";
                    std::cout << "ticket type = " << tmp_black_account.ticket_type << ".\n";
                    std::cout << "ticket = " << tmp_black_account.ticket << ".\n";
                    std::cout << "plate = " << tmp_black_account.plate << ".\n";
                    std::cout << "description = " << tmp_black_account.description << ".\n";
                    report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    buffer = "";
                    buffer = genSysParam_response_black_list_to_webhost(Setting_type, count, add_to_black_list, tmp_black_account);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host expire Forecast Threshold ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                    if(add_to_black_list)
                    {
                        tmp_black_account.Insert_Update_black_list_type();
                    }
                    else
                    {
                        tmp_black_account.Delete_black_list_type();
                    }
                    //black_list.clear();
                    //tmp_black_account.id = 0;
                    //tmp_black_account.gid = 0;
                    //for (int i = 0; i < MAX_black_list; i++)
                    //{
                    //  tmp_black_account.Select_black_list_type_by_id(i);
                    //    if(tmp_black_account.id > 0 && tmp_black_account.gid > 0 )
                    //    {
                    //        black_list.push_back(tmp_black_account);
                    //        tmp_black_account.id = 0;
                    //        tmp_black_account.gid = 0;
                    //    }
                    //}
                    //std::cout << "Black List" << std::endl;
                    //std::cout << "ID\t" << "GID\t" << "description\t" << "ticket\t" << "ticket_type\t" << "plate\t" << "operator\t" << "createtime\t" << std::endl;
                    //for (int i = 0; i < black_list.size(); i++)
                    //{
                    //    if(black_list[i].id > 0 && black_list[i].gid > 0 )
                    //    {
                    //        printf("%d\t%d\t%s\t%s\t%d\t%s\t%d\t%ld", black_list[i].id, black_list[i].gid, black_list[i].description, black_list[i].ticket, black_list[i].ticket_type, black_list[i].plate, black_list[i]._operator, black_list[i].create_time);
                    //        std::cout << std::endl;
                    //    }
                    //}
                }
                break;
                case 20: // Camera Site
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int cam_count = webhost_buffer[19];
                    int site_cam_address;
                    int camera_to_change[256];
                    memset(camera_to_change, 0, sizeof(camera_to_change));
                    int camera_bind[256];
                    memset(camera_bind, 0, sizeof(camera_bind));
                    std::vector<Camera_type> temp_Camera_type;
                    for(int i = 0; i < cam_count; i++)
                    {
                        camera_to_change[i] = webhost_buffer[20 + (i * 75)] + (1 - (webhost_buffer[20 + (i * 75)]>=0))*256;
                        Camera_type Camera_new_config(mysql);
                        if(i == 0)
                        {
                            Camera_new_config.Clear_Camera_type_sites(camera_to_change[i]);
                        }
                        else
                        {
                            if(camera_to_change[i] != camera_to_change[i - 1])
                            {
                                Camera_new_config.Clear_Camera_type_sites(camera_to_change[i]);
                            }
                        }
                        Camera_new_config.gid = Current_garage.gid;
                        Camera_new_config.cam_address = camera_to_change[i];
                        std::string camera_ip = std::to_string(Camera_new_config.cam_address);
                        strcpy(Camera_new_config.ip, camera_ip.c_str());
                        for(int j = 0; j < 32; j++)
                        {
                            Camera_new_config.Camera_name[j] = webhost_buffer[21 + j + (i * 75)]; 
                        }
                        for(int j = 0; j < 20; j++)
                        {
                            Camera_new_config.user_name[j] = webhost_buffer[53 + j + (i * 75)]; 
                        }
                        for(int j = 0; j < 20; j++)
                        {
                            Camera_new_config.password[j] = webhost_buffer[73 + j + (i * 75)]; 
                        }
                        site_cam_address = webhost_buffer[93 + (i * 75)] + (1-(webhost_buffer[93 + (i * 75)]>=0))*256;
                        std::string site_address = std::to_string(site_cam_address);
                        strcpy(Camera_new_config.site_Addresses, site_address.c_str());
                        camera_bind[i] = webhost_buffer[94 + (i * 75)] + (1-(webhost_buffer[94 + (i * 75)]>=0))*256;
                        Camera_new_config.create_time = time(0);
                        Camera_new_config._operator = webhost_buffer[20 + (cam_count * 75)] + (1 - (webhost_buffer[20 + (cam_count * 75)]>=0))*256;
                        printf("%d\t%s\t%s\t%s\t%s\t%s\t%d\n", Camera_new_config.gid, Camera_new_config.ip, Camera_new_config.Camera_name, Camera_new_config.user_name, Camera_new_config.password, Camera_new_config.site_Addresses, Camera_new_config._operator);
                        if(i == 0)
                        {
                            int execute = Camera_new_config.Insert_Update_Camera_type();
                        }
                        else
                        {
                            if(camera_to_change[i] != camera_to_change[i - 1])
                            {
                                Camera_new_config.Insert_Update_Camera_type();
                            }
                            else
                            {
                                Camera_new_config.Insert_Update_Camera_type_binded_site();
                            }
                        }
                        report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], Camera_new_config);
                    }
                    buffer = "";
                    web_host_locked = true;
                    buffer = genSysParam_response_CameraSite_to_webhost(Setting_type, cam_count, camera_to_change, camera_bind);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host Camera Site ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 21: // Enable diasble zone
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int zone_count = 0;
                    int zone_serial[256];
                    memset(zone_serial, 0, sizeof(zone_serial));
                    zone_count = webhost_buffer[19];
                    for(int i = 0; i < zone_count; i++)
                    {
                        zone_serial[i] = webhost_buffer[20 + (i * 52)];
                        if(webhost_buffer[21 + (i * 52)] == 0xff)
                        { 
                            strcpy(Zones[zone_serial[i]].name ,"");
                            Zones[zone_serial[i]].name[0] = 0xff;
                            Zones[zone_serial[i]].flag = 0;
                        }
                        else
                        {
                            Zones[zone_serial[i]].flag = 1;
                            strcpy(Zones[zone_serial[i]].name ,"");
                            for(int j = 0; j < 32; j++)
                            {
                                Zones[zone_serial[i]].name[j] = webhost_buffer[21 + j + (i * 52)];
                            }
                            Zones[zone_serial[i]].asofficial = webhost_buffer[53 + (i * 52)];
                            Zones[zone_serial[i]].totalSpaces = dashou.get_X2_Number(webhost_buffer[54 + (i * 52)],webhost_buffer[55 + (i * 52)]);
                            Zones[zone_serial[i]].totalSpacesSeason = dashou.get_X2_Number(webhost_buffer[56 + (i * 52)],webhost_buffer[57 + (i * 52)]);
                            Zones[zone_serial[i]].totalSpacesHourly = dashou.get_X2_Number(webhost_buffer[58 + (i * 52)],webhost_buffer[59 + (i * 52)]);
                            Zones[zone_serial[i]].vacantSpaces = dashou.get_X2_Number(webhost_buffer[60 + (i * 52)],webhost_buffer[61 + (i * 52)]);
                            Zones[zone_serial[i]].vacantSpacesSeason = dashou.get_X2_Number(webhost_buffer[62 + (i * 52)],webhost_buffer[63 + (i * 52)]);
                            Zones[zone_serial[i]].vacantSpacesHourly = dashou.get_X2_Number(webhost_buffer[64 + (i * 52)],webhost_buffer[65 + (i * 52)]);
                            Zones[zone_serial[i]].parking_Guidance_Available_Space = dashou.get_X2_Number(webhost_buffer[66 + (i * 52)],webhost_buffer[67 + (i * 52)]);
                            Zones[zone_serial[i]].parking_Guidance_Total_Space = dashou.get_X2_Number(webhost_buffer[68 + (i * 52)],webhost_buffer[69 + (i * 52)]);
                        }
                        Zones[zone_serial[i]]._operator = webhost_buffer[20 + (zone_count * 52)];
                        Zones[zone_serial[i]].createtime = time(0);
                        Zones[zone_serial[i]].insert_update_Zone();
                        std::cout << Zones[zone_serial[i]].serial <<  " " 
                                  << Zones[zone_serial[i]].name << " " 
                                  << Zones[zone_serial[i]].insites_list << " " 
                                  << Zones[zone_serial[i]].outsites_list << " " 
                                  << Zones[zone_serial[i]].totalSpacesSeason<< " " 
                                  << Zones[zone_serial[i]].vacantSpacesSeason << " " 
                                  << Zones[zone_serial[i]].totalSpacesHourly << " " 
                                  << Zones[zone_serial[i]].vacantSpacesHourly << " " 
                                  << Zones[zone_serial[i]].flag << "\n";
                    }
                    report = log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    buffer = "";
                    buffer = Enable_diasble_zone_confirm_to_webhost(Setting_type, zone_count, zone_serial);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host Enable diasble zone ACK...\n";
                    }
                    web_host_locked = false;
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 22: // Entry Exit zone
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int zone_serial = webhost_buffer[19];
                    int site_count = webhost_buffer[20];
                    int entry_site_count = -1;
                    int exit_site_count = -1;
                    std::string in = "";
                    std::string out = "";
                    for(int i = 0; i < 100; i++)
                    {
                        Zones[zone_serial].entry_address[i] = 0;
                        Zones[zone_serial].exit_address[i] = 0;
                    }
                    if(site_count == 0)
                    {
                        for(int i = 0; i < 100; i++)
                        {
                            Zones[zone_serial].entry_address[i] = 0;
                            Zones[zone_serial].exit_address[i] = 0;
                        }
                    }
                    else
                    {
                        for(int i = 0; i < site_count; i++)
                        {
                            int site_ip = webhost_buffer[21 + (2 * i)];
                            if(webhost_buffer[22 + (2 * i)] == 0)
                            {
                                entry_site_count++;
                                Zones[zone_serial].entry_address[entry_site_count] = site_ip;
                            }
                            else if(webhost_buffer[22 + (2 * i)] == 1)
                            {
                                exit_site_count++;
                                Zones[zone_serial].exit_address[exit_site_count] = site_ip;
                            }
                        }
                        if(entry_site_count > -1)
                        {
                            for(int i = 0; i < entry_site_count; i++)
                            {
                                in += std::to_string(Zones[zone_serial].entry_address[i]);
                                in += ",";
                            }
                            if (Zones[zone_serial].entry_address[entry_site_count] != 0)
                            {
                                in += std::to_string(Zones[zone_serial].entry_address[entry_site_count]);
                            }
                        }
                        if (exit_site_count > -1)
                        {
                            for(int i = 0; i < exit_site_count; i++)
                            {
                                out += std::to_string(Zones[zone_serial].exit_address[i]);
                                out += ",";
                            }
                            if(Zones[zone_serial].exit_address[exit_site_count] != 0)
                            {
                                out += std::to_string(Zones[zone_serial].exit_address[exit_site_count]);
                            }
                        }
                    }
                    strcpy(Zones[zone_serial].insites_list,in.c_str());       
                    strcpy(Zones[zone_serial].outsites_list,out.c_str());
                    Zones[zone_serial].insert_update_Zone();
                    std::cout << Zones[zone_serial].serial <<  " " 
                              << Zones[zone_serial].name << " " 
                              << Zones[zone_serial].insites_list << " " 
                              << Zones[zone_serial].outsites_list << " " 
                              << Zones[zone_serial].totalSpacesSeason<< " " 
                              << Zones[zone_serial].vacantSpacesSeason << " " 
                              << Zones[zone_serial].totalSpacesHourly << " " 
                              << Zones[zone_serial].vacantSpacesHourly << " " 
                              << Zones[zone_serial].flag << "\n";
                    report = log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    buffer = "";
                    buffer = Entry_Exit_zone_confirm_to_webhost(parser_host->datetime, Setting_type, entry_site_count, exit_site_count, Zones[zone_serial]);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host Entry Exit zone ACK...\n";
                    }
                    web_host_locked = false;
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 25: // download account
                {
                    web_host_client_send_confirm_data = false;
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    pthread_create(&client_WEBHOST_thread_receive_accounts, NULL , receive_accounts, parser_host);
                    recv_temp_card_list.clear();
                    temp_card current_temp_card(mysql);
                    current_temp_card.id = get_temp_card_insert_id();
                    current_temp_card.operate_type = webhost_buffer[19];
                    current_temp_card.ticket_type = webhost_buffer[20];
                    for(int i = 0; i < 19; i++)
                    {
                        current_temp_card.ticket[i] = webhost_buffer[21 + i];
                    }
                    for(int i = 0; i < 12; i++)
                    {
                        current_temp_card.plate[i] = webhost_buffer[40 + i];
                    }
                    current_temp_card.account_state = webhost_buffer[52];
                    current_temp_card.parking_type = webhost_buffer[53];
                    current_temp_card.present_type = webhost_buffer[54];
                    current_temp_card.in_time = dashou.char_to_time_t(webhost_buffer[55], webhost_buffer[56], webhost_buffer[57], webhost_buffer[58], webhost_buffer[59], webhost_buffer[60]);
                    current_temp_card.pay_time = dashou.char_to_time_t(webhost_buffer[61], webhost_buffer[62], webhost_buffer[63], webhost_buffer[64], webhost_buffer[65], webhost_buffer[66]);
                    current_temp_card.inner_intime = dashou.char_to_time_t(webhost_buffer[67], webhost_buffer[68], webhost_buffer[69], webhost_buffer[70], webhost_buffer[71], webhost_buffer[72]);
                    current_temp_card.inner_outtime = dashou.char_to_time_t(webhost_buffer[73], webhost_buffer[74], webhost_buffer[75], webhost_buffer[76], webhost_buffer[77], webhost_buffer[78]);
                    current_temp_card.insite = webhost_buffer[79];
                    current_temp_card.charge_site = webhost_buffer[80];
                    current_temp_card.inner_insite = webhost_buffer[81];
                    current_temp_card.inner_outsite = webhost_buffer[82];
                    current_temp_card.coupon_total_time = dashou.get_X4_Number(webhost_buffer[83], webhost_buffer[84], webhost_buffer[85], webhost_buffer[86]);
                    current_temp_card.coupon_total_sum = dashou.get_X4_Number(webhost_buffer[87], webhost_buffer[88], webhost_buffer[89], webhost_buffer[90]);
                    current_temp_card.limit_sum = dashou.get_X4_Number(webhost_buffer[91], webhost_buffer[92], webhost_buffer[93], webhost_buffer[94]);
                    current_temp_card.limit_time = dashou.char_to_time_t(webhost_buffer[95], webhost_buffer[96], webhost_buffer[97], webhost_buffer[98], webhost_buffer[99], webhost_buffer[100]);
                    current_temp_card.paid_sum = dashou.get_X4_Number(webhost_buffer[101], webhost_buffer[102], webhost_buffer[103], webhost_buffer[104]);
                    for(int i = 0; i < 12; i++)
                    {
                        current_temp_card.online_order[i] = webhost_buffer[105 + i];
                    }
                    current_temp_card.hour_ticket_type = webhost_buffer[117];
                    for(int i = 0; i < 19; i++)
                    {
                        current_temp_card.hour_ticket_num[i] = webhost_buffer[118 + i];
                    }
                    current_temp_card.access_group = webhost_buffer[138];//dashou.get_X2_Number(webhost_buffer[137], webhost_buffer[138]);
                    current_temp_card.start_time = dashou.char_to_time_t(webhost_buffer[139], webhost_buffer[140], webhost_buffer[141], webhost_buffer[142], webhost_buffer[143], webhost_buffer[144]);
                    current_temp_card.end_time = dashou.char_to_time_t(webhost_buffer[145], webhost_buffer[146], webhost_buffer[147], webhost_buffer[148], webhost_buffer[149], webhost_buffer[150]);
                    current_temp_card.prepaid_balance = dashou.get_X4_Number(webhost_buffer[151], webhost_buffer[152], webhost_buffer[153], webhost_buffer[154]);
                    current_temp_card.prepaid_account_id = dashou.get_X2_Number(webhost_buffer[155], webhost_buffer[156]);
                    current_temp_card.monthly_type = webhost_buffer[157];
                    current_temp_card.lots_group = dashou.get_X2_Number(webhost_buffer[158], webhost_buffer[159]);
                    current_temp_card.ticket_lpbind = webhost_buffer[160];
                    current_temp_card.inner_group = webhost_buffer[161];
                    current_temp_card.time_group = webhost_buffer[162];
                    for(int i = 0; i < 16; i++)
                    {
                        current_temp_card.lot_name[i] = webhost_buffer[163 + i];
                    }
                    current_temp_card.prepaid_charge_rule = webhost_buffer[179];
                    current_temp_card.monthly_charge_rule = webhost_buffer[180];
                    for(int i = 0; i < 16; i++)
                    {
                        current_temp_card.photo_id[i] = webhost_buffer[181 + i];
                    }
                    for(int i = 0; i < 16; i++)
                    {
                        current_temp_card.owner_name[i] = webhost_buffer[197 + i];
                    }
                    for(int i = 0; i < 16; i++)
                    {
                        current_temp_card.phone[i] = webhost_buffer[213 + i];
                    }
                    for(int i = 0; i < 32; i++)
                    {
                        current_temp_card.email[i] = webhost_buffer[229 + i];
                    }
                    for(int i = 0; i < 64; i++)
                    {
                        current_temp_card.addr[i] = webhost_buffer[261 + i];
                    }
                    for(int i = 0; i < 64; i++)
                    {
                        current_temp_card.description[i] = webhost_buffer[325 + i];
                    }
                    for(int i = 0; i < 64; i++)
                    {
                        current_temp_card.add_info1[i] = webhost_buffer[389 + i];
                    }
                    for(int i = 0; i < 64; i++)
                    {
                        current_temp_card.add_info2[i] = webhost_buffer[453 + i];
                    }
                    current_temp_card.Insert_Update_Temp_Account();
                    recv_temp_card_list.push_back(current_temp_card);
                    report = log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    buffer = "";
                    buffer = genSysParam_response_download_account_to_webhost(Setting_type, current_temp_card);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_client_send_confirm_data = true;
                    //web_host_locked = true;
                    //iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    //if (iResult < 0)
                    //{
                    //    std::cout << "Error recv Web Host Entry Exit zone ACK...\n";
                    //}
                    //web_host_locked = false;
                    //parser_host->parse2(WebHost_buffer);
                    //report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    //log_udp.messege_Sender(report);
                    //make_account_from_card(current_temp_card);      
                }
                break;
                case 26: // Network parameter
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int master_port = webhost_buffer[19] + webhost_buffer[20] * 256;
                    int master_ip[4]= {0,0,0,0};
                    for (int i = 0; i < 4; i++)
                    {
                        master_ip[3 - i] = webhost_buffer[21 + i];
                    }
                    int slave_port = webhost_buffer[25] + webhost_buffer[26] * 256;
                    int slave_ip[4]= {0,0,0,0};
                    for (int i = 0; i < 4; i++)
                    {
                        slave_ip[3 - i] = webhost_buffer[27 + i];
                    }
                    char qrcode_scan[255];
                    for(int i = 31; i < 159; i++) 
                    {
                        qrcode_scan[i] = webhost_buffer[i];
                    }
                    int trans_port = webhost_buffer[159] + webhost_buffer[160] * 256;
                    int trans_ip[4]= {0,0,0,0};
                    for (int i = 0; i < 4; i++)
                    {
                        trans_ip[3 - i] = webhost_buffer[161 + i];
                    }
                    int city = webhost_buffer[167] + (webhost_buffer[168] * 256);
                    int garag = webhost_buffer[165] + (webhost_buffer[166] * 256);
                    int new_gid = 0;
                    std::string master_add = "" + std::to_string(master_ip[0]) + "." + std::to_string(master_ip[1]) + "." + std::to_string(master_ip[2]) + "." + std::to_string(master_ip[3]) + ":" + std::to_string(master_port);
                    std::cout << master_add << "\n";
                    std::string slave_add = "" + std::to_string(slave_ip[0]) + "." + std::to_string(slave_ip[1]) + "." + std::to_string(slave_ip[2]) + "." + std::to_string(slave_ip[3]) + ":" + std::to_string(slave_port);
                    std::cout << slave_add << "\n";
                    std::cout << "QR address = " << qrcode_scan << "\n";
                    std::string trans_add = "" + std::to_string(trans_ip[0]) + "." + std::to_string(trans_ip[1]) + "." + std::to_string(trans_ip[2]) + "." + std::to_string(trans_ip[3]) + ":" + std::to_string(trans_port);
                    std::cout << trans_add << "\n";
                    int num = city;
                    while(num > 0)
                    {
                        num /= 10;
                        garag *= 10;
                    }
                    new_gid = garag + city;
                    std::cout << "new gid = " << new_gid << "\n";
                    Current_Settings.gid = new_gid;
                    strcpy(Current_Settings.online_marjor_ip,master_add.c_str());
                    strcpy(Current_Settings.online_minor_ip,slave_add.c_str());
                    strcpy(Current_Settings.qrcode_url,qrcode_scan);
                    strcpy(Current_Settings.etrecord_ip,trans_add.c_str());
                    Current_Settings.update_Setting();
                    // replay to webhost
                }
                break;
                case 27:// site name
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int site_count = webhost_buffer[19];
                    int site_address = 0;
                    int site_to_change[256];
                    Site_type current_site(mysql);
                    memset(site_to_change, 0, sizeof(site_to_change));
                    for(int j = 0; j < site_count; j++)
                    {
                        site_to_change[j] = webhost_buffer[20 + (33 * j)];
                        current_site.id = site_to_change[j];
                        current_site.Select_Site_type_by_id(site_to_change[j]);
                        memset(current_site.db_name, 0, sizeof(current_site.db_name));
                        for(int i = 0; i < 32; i++)
                        {
                            current_site.db_name[i] = webhost_buffer[21 + i + (33 * j)];
                        }
                        if(1)
                        {
                            current_site.id_PresetSite_in_Site_Group = parser_host->id_PresetSite_in_Site_Group;
                            printf("Client #%d : address (%s) : (name : %s).\n", site_to_change[j], current_site.site_Address, current_site.db_name);
                            report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, current_site, All_Cameras[0]);
                            current_site.Insert_Update_Site_type();
                        }
                        else
                        {
                            std::cout << "Client #" << parser_host->site_address << " : not exist\n";
                        }
                    }
                    buffer = "";
                    buffer = genSysParam_response_SiteName_to_webhost(site_to_change, Setting_type, site_count);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host Site Name ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 31: // retaining days
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    Current_Settings.events_retainingdays = dashou.get_X2_Number(webhost_buffer[19], webhost_buffer[20]);
                    Current_Settings.photos_retainingdays = dashou.get_X2_Number(webhost_buffer[21], webhost_buffer[22]);
                    // Current_Settings.unknown variable =  dashou.get_X2_Number(webhost_buffer[23], webhost_buffer[24]); unknown variable = 30  several IN/OUT Max. charge A/C
                    Current_Settings.clear_time = webhost_buffer[25];
                    std::cout << "Current_Settings events_retainingdays" << Current_Settings.events_retainingdays << "\n";
                    std::cout << "Current_Settings photos_retainingdays" << Current_Settings.photos_retainingdays << "\n";
                    std::cout << "Current_Settings clear_time" << Current_Settings.clear_time << "\n";
                    Current_Settings.update_Setting();
                    buffer = "";
                    buffer = genSysParam_response_retainingdays_webhost(Setting_type);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host one proof on car ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 33: // Hourly Charging STD step
                {
                    web_host_client_send_confirm_data = false;
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    pthread_create(&client_WEBHOST_thread_receive_STD_step, NULL , receive_STD_step, parser_host);
                    rule_step_hourly_type rule_step_hourly(mysql);
                    rule_step_hourly.gid = Current_Settings.gid;
                    rule_step_hourly.rule_serial = webhost_buffer[19];
                    rule_step_hourly.Delete_all_rule_step_hourly_type_by_rule_serial(Current_garage.gid, webhost_buffer[19]);
                    rule_step_hourly.block_serial = webhost_buffer[20];
                    rule_step_hourly.type = webhost_buffer[21];
                    if(webhost_buffer[22] == 0xff) webhost_buffer[22] = 0;
                    if(webhost_buffer[23] == 0xff) webhost_buffer[23] = 1;
                    if(webhost_buffer[24] == 0xff) webhost_buffer[24] = 1;
                    rule_step_hourly.starttime = parser_host->char_to_time_t(webhost_buffer[22], webhost_buffer[23], webhost_buffer[24], webhost_buffer[25], webhost_buffer[26], webhost_buffer[27]);
                    if(webhost_buffer[28] == 0xff) webhost_buffer[28] = 0;
                    if(webhost_buffer[29] == 0xff) webhost_buffer[29] = 1;
                    if(webhost_buffer[30] == 0xff) webhost_buffer[30] = 1;
                    rule_step_hourly.endtime = parser_host->char_to_time_t(webhost_buffer[28], webhost_buffer[29], webhost_buffer[30], webhost_buffer[31], webhost_buffer[32], webhost_buffer[33]);
                    rule_step_hourly.duration = dashou.get_X4_Number(webhost_buffer[34], webhost_buffer[35], webhost_buffer[36], webhost_buffer[37]);
                    rule_step_hourly.relation = dashou.get_X2_Number(webhost_buffer[38], webhost_buffer[39]);
                    rule_step_hourly.deduct = webhost_buffer[40];
                    rule_step_hourly.cross_period = webhost_buffer[41];
                    rule_step_hourly.sum = dashou.get_X4_Number(webhost_buffer[42], webhost_buffer[43], webhost_buffer[44], webhost_buffer[45]);
                    rule_step_hourly.max_sum = dashou.get_X4_Number(webhost_buffer[46], webhost_buffer[47], webhost_buffer[48], webhost_buffer[49]);
                    rule_step_hourly.next_serial = webhost_buffer[50];
                    rule_step_hourly.start_week = webhost_buffer[51];
                    rule_step_hourly.end_week = webhost_buffer[52];
                    rule_step_hourly.reserve[0] = webhost_buffer[53];
                    rule_step_hourly.reserve[1] = webhost_buffer[54];
                    for(int i = 0; i < 64; i++)
                    {
                        rule_step_hourly.brief[i] = webhost_buffer[55 + i];
                    }
                    rule_step_hourly._operator = webhost_buffer[119];
                    rule_step_hourly.Update_rule_step_hourly_type();
                    report = log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    buffer = "";
                    buffer = genSysParam_response_Hourly_Charging_STD_step_to_webhost(Setting_type, rule_step_hourly.rule_serial, rule_step_hourly.block_serial);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_client_send_confirm_data = true;
                    //web_host_locked = true;
                    //iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    //if (iResult < 0)
                    //{
                    //    std::cout << "Error recv Web Host Hourly Charging STD step ACK...\n";
                    //}
                    //web_host_locked = false;
                    //parser_host->parse2(WebHost_buffer);
                    //report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    //log_udp.messege_Sender(report);
                    //
                    //rule_step_hourly_list.clear();
                    //rule_step_hourly_type tmp_rule_step_hourly(mysql);
                    //for (int i = 0; i < 16; i++)
                    //{
                    //    for(int j = 0; j < MAX_rule_step_list; j++)
                    //    {
                    //        tmp_rule_step_hourly.Select_rule_step_hourly_type_by_rule_block_serial(i, j);
                    //        if(tmp_rule_step_hourly.gid > 0 && tmp_rule_step_hourly.rule_serial < 16 && tmp_rule_step_hourly.block_serial < 256)
                    //        {
                    //            rule_step_hourly_list.push_back(tmp_rule_step_hourly);
                    //            tmp_rule_step_hourly.gid = 0;
                    //            tmp_rule_step_hourly.rule_serial = 255;
                    //            tmp_rule_step_hourly.block_serial = 256;
                    //        }
                    //    }
                    //}
                }
                break;
                case 34: // Hourly Charging STD
                {
                    web_host_client_send_confirm_data = false;
                    int Setting_type = parser_host->Setting_type;
                    pthread_create(&client_WEBHOST_thread_receive_STD_step, NULL , receive_STD_step, parser_host);
                    report = "";
                    int rule_serial = webhost_buffer[19];
                    bool non_step_rules = false;
                    if(webhost_buffer[20] == 0xff && webhost_buffer[21] == 0xff)
                    {
                        non_step_rules = true;
                    }
                    else
                    {
                        if(webhost_buffer[20] == 0xff)
                        {
                            rule_name_hourly_list[rule_serial].flag = 0;
                        }
                        else
                        {
                            rule_name_hourly_list[rule_serial].flag = 1;
                        }
                        for(int i = 0; i < 50; i++)
                        {
                            rule_name_hourly_list[rule_serial].name[i] = webhost_buffer[20 + i];
                        }
                        rule_name_hourly_list[rule_serial].limit_enable = webhost_buffer[84];
                        rule_name_hourly_list[rule_serial].limit_sum = dashou.get_X4_Number(webhost_buffer[85],webhost_buffer[86],webhost_buffer[87],webhost_buffer[88]);
                        strcpy(rule_name_hourly_list[rule_serial].fixed_time ,dashou.Print_time(dashou.char_to_time_t(0, 1, 1, webhost_buffer[92],webhost_buffer[93],webhost_buffer[94])).c_str());
                        rule_name_hourly_list[rule_serial].within_duration = dashou.get_X4_Number(webhost_buffer[95],webhost_buffer[96],webhost_buffer[97],webhost_buffer[98]);
                        rule_name_hourly_list[rule_serial].tolerance = dashou.get_X2_Number(webhost_buffer[99],webhost_buffer[100]);
                        for(int i = 0; i < 255; i++)
                        {
                            rule_name_hourly_list[rule_serial].remark[i] = webhost_buffer[101 + i];
                        }
                        rule_name_hourly_list[rule_serial]._operator = webhost_buffer[357];
                    }
                    report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    rule_name_hourly_list[rule_serial].Update_rule_name_hourly_type();
                    buffer = "";
                    buffer = genSysParam_response_Hourly_Charging_STD_to_webhost(Setting_type, rule_serial, non_step_rules);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_client_send_confirm_data = true;
                    //web_host_locked = true;
                    //iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    //web_host_locked = false;
                    //if (iResult < 0)
                    //{
                    //    std::cout << "Error recv Web Host Hourly Charging STD ACK...\n";
                    //}
                    //report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    //log_udp.messege_Sender(report);
                }    
                break;
                case 48:// season Charging STD step
                {
                    web_host_locked = true;
                    web_host_client_send_confirm_data = false;
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    pthread_create(&client_WEBHOST_thread_receive_STD_montly_step, NULL , receive_STD_montly_step, parser_host);
                    rule_step_monthly current_rule_step_monthly(mysql);
                    temp_rule_step_monthly_list.clear();
                    //current_rule_step_monthly.Delete_all_rule_step_monthly(Current_garage.gid, webhost_buffer[19]);
                    current_rule_step_monthly.rule_serial = webhost_buffer[19];
                    current_rule_step_monthly.step_serial = webhost_buffer[20];
                    current_rule_step_monthly.gid = Current_garage.gid;
                    current_rule_step_monthly.flag = webhost_buffer[21];
                    current_rule_step_monthly.max_units = dashou.get_X2_Number(webhost_buffer[22], webhost_buffer[23]);
                    current_rule_step_monthly.duration = dashou.get_X4_Number(webhost_buffer[24], webhost_buffer[25], webhost_buffer[26], webhost_buffer[27]);
                    current_rule_step_monthly.unit_sum = dashou.get_X4_Number(webhost_buffer[28], webhost_buffer[29], webhost_buffer[30], webhost_buffer[31]);
                    //                        std::cout << "rule step monthly setting:\n";
                    //                        printf("rule_sr\tstep_sr\tgid\tflag\tmax_units\tduration\tunit_sum\n");
                    //                        printf("%ld\t%ld\t%ld\t%d\t%ld\t%ld\t%ld\n",
                    //                                current_rule_step_monthly.rule_serial,
                    //                                current_rule_step_monthly.step_serial,
                    //                                current_rule_step_monthly.gid,
                    //                                current_rule_step_monthly.flag,
                    //                                current_rule_step_monthly.max_units,
                    //                                current_rule_step_monthly.duration,
                    //                                current_rule_step_monthly.unit_sum);
                    buffer = "";
                    buffer = genSysParam_response_rule_step_monthly_to_webhost(Setting_type, current_rule_step_monthly);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    current_rule_step_monthly.createtime = time(0);
                    temp_rule_step_monthly_list.push_back(current_rule_step_monthly);
                    web_host_client_send_confirm_data = true;
                    //current_rule_step_monthly.Insert_Update_rule_step_monthly();
                    //web_host_locked = true;
                    //iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    //web_host_locked = false;
                    //if (iResult < 0)
                    //{
                    //    std::cout << "Error recv Web Host one proof on car ACK...\n";
                    //}
                    //parser_host->parse2(WebHost_buffer);
                    //report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    //log_udp.messege_Sender(report); 
                }
                break;
                case 49:// season Charging STD
                {
                    web_host_locked = true;
                    web_host_client_send_confirm_data = false;
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    pthread_create(&client_WEBHOST_thread_receive_STD_montly_step, NULL , receive_STD_montly_step, parser_host);
                    rule_name_monthly current_rule_name_monthly(mysql);
                    current_rule_name_monthly.gid = Current_garage.gid;
                    if(webhost_buffer[20] == 0xff && webhost_buffer[21] == 0xff)
                    {
                        current_rule_name_monthly.Select_rule_name_monthly_by_serial(webhost_buffer[19], Current_garage.gid);
                        if(current_rule_name_monthly.Delete_rule_name_monthly())
                        {
                            //std::cout << "rule name monthly setting:\n";
                            //std::cout << "rule name monthly " + std::to_string(webhost_buffer[19]) + " Deleted successfully.\n";
                        }
                        current_rule_name_monthly.rule_serial = webhost_buffer[19];
                        for(int i = 0; i < 64; i++)
                        {
                            current_rule_name_monthly.name[i] = webhost_buffer[20 + i];
                        }
                        for(int i = 0; i < 256; i++)
                        {
                            current_rule_name_monthly.remark[i] = webhost_buffer[84 + i];
                        }
                        current_rule_name_monthly.createtime = time(0);
                    }
                    else
                    {
                        current_rule_name_monthly.rule_serial = webhost_buffer[19];
                        for(int i = 0; i < 50; i++)
                        {
                            current_rule_name_monthly.name[i] = webhost_buffer[20 + i];
                        }
                        for(int i = 0; i < 200; i++)
                        {
                            current_rule_name_monthly.remark[i] = webhost_buffer[84 + i];
                        }
                        current_rule_name_monthly.createtime = time(0);
                        current_rule_name_monthly.Insert_Update_rule_name_monthly();
                        //std::cout << "rule name monthly setting:\n";
                        //printf("gid\trule_sr\tname\t\tremark\tflag\toper\tcreate time\n");
                        //printf("%ld\t%ld\t%s\t%s\t\t%d\t%d\t%s\n",
                        //    current_rule_name_monthly.gid,
                        //    current_rule_name_monthly.rule_serial,
                        //    current_rule_name_monthly.name,
                        //    current_rule_name_monthly.remark,
                        //    current_rule_name_monthly.flag,
                        //    current_rule_name_monthly._operator,
                        //    dashou.Print_time(current_rule_name_monthly.createtime).c_str());
                    }
                    buffer = "";
                    buffer = genSysParam_response_rule_name_monthly_to_webhost(Setting_type, current_rule_name_monthly);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_client_send_confirm_data = true;
                    //web_host_locked = true;
                    //iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN, 0);
                    //web_host_locked = false;
                    //if (iResult < 0)
                    //{
                    //    std::cout << "Error recv Web Host one proof on car ACK...\n";
                    //}
                    //parser_host->parse2(WebHost_buffer);
                    //report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    //log_udp.messege_Sender(report); 
                }
                break;
                case 50:// proof model
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    int site_count = webhost_buffer[19];
                    int site_address = 0;
                    int site_to_change[256];
                    memset(site_to_change, 0, sizeof(site_to_change));
                    for(int i = 0; i < site_count; i++)
                    {
                        site_address = webhost_buffer[20 + 3 * i];
                        parser_host->credentialMode = webhost_buffer[21 + 3 * i];
                        parser_host->season_to_hourly_swich = webhost_buffer[22 + 3 * i];
                        site_to_change[i] = find_site_by_address(site_address);
                        if(site_to_change[i] > 0)
                        {
                            sites[site_to_change[i]].credentialMode = parser_host->credentialMode;
                            sites[site_to_change[i]].season_to_hourly_swich= parser_host->season_to_hourly_swich;
                            std::cout << "Client #" << sites[site_to_change[i]].id <<" : address (172.16.57." << site_address << ") : ( proof model = " << sites[site_to_change[i]].credentialMode << " ).\n";
                            report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[site_to_change[i]], All_Cameras[0]);
                            sites[site_to_change[i]].Insert_Update_Site_type();
                            if(sites[site_to_change[i]].status == 0xffffff)
                            {
                                buffer = "";
                                buffer = genSysParam(sites[site_to_change[i]], parser_host);
                                send(sites[site_to_change[i]].socket, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2, 0);
                                while(!site_ACK_setting);
                                if(site_ACK_setting)
                                {
                                    site_ACK_setting = false;
                                    report += log_udp.CONTROL_TYPE_messege_Builder(CONTROL_TYPE_SITE_SETTING, localSerialDownLink, All_Cameras,site_to_change[i], sites);                               
                                    parser_host->serial = site_ACK_setting_serial;
                                    parser_host->Setting_type = site_ACK_setting_type;
                                    report += log_udp.ACK_sites_messege_Builder(sites[site_to_change[i]], parser_host);
                                }
                            }
                        }
                        else
                        {
                            std::cout << "Client #" << parser_host->site_address << " : not exist\n";
                        }
                    }
                    buffer = "";
                    buffer = genSysParam_response_proofmodel_to_webhost(site_to_change, Setting_type, site_count);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host proof model ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 51:// monthly_type
                {
                    web_host_locked = true;
                    web_host_client_send_confirm_data = false;
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    pthread_create(&client_WEBHOST_thread_receive_monthly_type, NULL , receive_monthly_type, parser_host);
                    monthly_type current_monthly_type(mysql);
                    temp_monthly_type_list.clear();
                    current_monthly_type.id = webhost_buffer[19];
                    current_monthly_type.aid = (get_aid_monthly_type_from_id(current_monthly_type.id) > 0) ? get_aid_monthly_type_from_id(current_monthly_type.id) : get_monthly_type_insert_aid();
                    current_monthly_type.gid = Current_garage.gid;
                    current_monthly_type.type = (webhost_buffer[20] == 0xff) ? 4 : webhost_buffer[20];
                    current_monthly_type.flag = !(webhost_buffer[20] == 0xff);
                    current_monthly_type.access_group_id = webhost_buffer[21];
                    current_monthly_type.time_group_id = webhost_buffer[22];
                    current_monthly_type.inner_group_id = webhost_buffer[23];
                    current_monthly_type.monthly_charge_rule = webhost_buffer[24];
                    current_monthly_type.prepaid_charge_rule = webhost_buffer[25];
                    current_monthly_type.vip_flag = webhost_buffer[26];
                    current_monthly_type.reserved = 0xffff;
                    current_monthly_type.lotgroup_countingtype = webhost_buffer[27];
                    current_monthly_type.expires = webhost_buffer[28];
                    current_monthly_type.createtime = time(0);
                    for(int i = 0; i < 64; i++)
                    {
                        current_monthly_type.name[i]= webhost_buffer[29 + i];
                    }
                    if(webhost_buffer[93] == 0x2d && webhost_buffer[94] == 0x2d)
                    {
                        strcpy(current_monthly_type.description, "--");
                    }
                    else
                    {
                        for(int i = 0; i < 255; i++)
                        {
                            current_monthly_type.description[i]= webhost_buffer[93 + i];
                        }
                    }
                    current_monthly_type._operator = webhost_buffer[349];
                    temp_monthly_type_list.push_back(current_monthly_type);
                    //current_monthly_type.Insert_Update_monthly_type();
                    //std::cout << "monthly type setting:\n";
                    //printf("aid\tid\tgid\ttype\tagid\ttgid\tigid\tmcr\tpcr\tvipf\tlotc\texp\tname\t\tdesc\tflag\toper\n");
                    //printf("%ld\t%d\t%ld\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%s\t%d\t%d\t%s\n",
                    //    current_monthly_type.aid,
                    //    current_monthly_type.id,
                    //    current_monthly_type.gid,
                    //    current_monthly_type.type,
                    //    current_monthly_type.access_group_id,
                    //    current_monthly_type.time_group_id,
                    //    current_monthly_type.inner_group_id,
                    //    current_monthly_type.monthly_charge_rule,
                    //    current_monthly_type.prepaid_charge_rule, 
                    //    current_monthly_type.vip_flag,
                    //    current_monthly_type.lotgroup_countingtype,
                    //    current_monthly_type.expires,
                    //    current_monthly_type.name,
                    //    current_monthly_type.description,
                    //    current_monthly_type.flag,
                    //    current_monthly_type._operator,
                    //    dashou.Print_time(current_monthly_type.createtime).c_str());
                    buffer = "";
                    buffer = genSysParam_response_monthly_type_to_webhost(Setting_type, current_monthly_type);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_client_send_confirm_data = true;
                    //iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    //web_host_locked = false;
                    //if (iResult < 0)
                    //{
                    //    std::cout << "Error recv Web Host one proof on car ACK...\n";
                    //}
                    //parser_host->parse2(WebHost_buffer);
                    //report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    //log_udp.messege_Sender(report); 
                }
                break;
                case 61:// mobile charge standard
                {
                    report = "";
                    int Setting_type = parser_host->Setting_type;
                    Current_Settings.mobile_charge_standard = webhost_buffer[19];
                    std::cout << "All Clients set ( mobile charge standard = " << Current_Settings.mobile_charge_standard << " ).\n";
                    report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    Current_Settings.update_Setting();
                    buffer = "";
                    buffer = genSysParam_response_mobile_charge_standard_to_webhost(Setting_type, Current_Settings.mobile_charge_standard);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host plate match level ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 63:// mobile reservation tolerance
                {
                    report = "";;
                    int Setting_type = parser_host->Setting_type;
                    Current_Settings.mobile_reservation_tolerance = dashou.get_X4_Number(webhost_buffer[19], webhost_buffer[20], webhost_buffer[21], webhost_buffer[22]);
                    std::cout << "All Clients set ( mobile reservation tolerance = " << Current_Settings.mobile_reservation_tolerance << " ).\n";
                    report += log_udp.SystemParam_messege_Builder(Setting_type, localSerialSetting, parser_host->serial, parser_host->Setting_type, sites[0], All_Cameras[0]);
                    Current_Settings.update_Setting();
                    buffer = "";
                    buffer = genSysParam_response_mobile_charge_standard_to_webhost(Setting_type, Current_Settings.mobile_charge_standard);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host plate match level ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
                case 64:// authorities
                {
                    report = "";
                    int index = 0;
                    int Setting_type = parser_host->Setting_type;
                    sys_user current_sys_user(mysql);
                    int k = 0;
                    for(int i = 19; i < 255; i++)
                    {
                        if(webhost_buffer[i] != '#')
                        {
                            current_sys_user.full_name[k] = webhost_buffer[i];
                            k++;
                        }
                        if(webhost_buffer[i] == '#' && webhost_buffer[i + 1] == '#')
                        {
                            index = i + 2;
                            break;
                        }
                    }
                    k = 0;
                    for(int i = index; i < 255; i++)
                    {
                        if(webhost_buffer[i] != '#')
                        {
                            current_sys_user.username[k] = webhost_buffer[i];
                            k++;
                        }
                        if(webhost_buffer[i] == '#' && webhost_buffer[i + 1] == '#')
                        {
                            index = i + 2;
                            break;
                        }
                    }
                    k = 0;
                    for(int i = index; i < 255; i++)
                    {
                        if(webhost_buffer[i] != '#')
                        {
                            current_sys_user.password_hash[k] = webhost_buffer[i];
                            k++;
                        }
                        if(webhost_buffer[i] == '#' && webhost_buffer[i + 1] == '#')
                        {
                            index = i + 2;
                            break;
                        }
                    }
                    current_sys_user.dob_time = dashou.char_to_time_t(webhost_buffer[index], webhost_buffer[index + 1], webhost_buffer[index + 2], webhost_buffer[index + 3],webhost_buffer[index + 4],webhost_buffer[index + 5]);
                    index += 6;
                    k = 0;
                    for(int i = index; i < 255; i++)
                    {
                        if(webhost_buffer[i] != '#')
                        {
                            current_sys_user.mobile[k] = webhost_buffer[i];
                            k++;
                        }
                        if(webhost_buffer[i] == '#' && webhost_buffer[i + 1] == '#')
                        {
                            index = i + 2;
                            break;
                        }
                    }
                    k = 0;
                    for(int i = index; i < 255; i++)
                    {
                        if(webhost_buffer[i] != '#')
                        {
                            current_sys_user.phone[k] = webhost_buffer[i];
                            k++;
                        }
                        if(webhost_buffer[i] == '#' && webhost_buffer[i + 1] == '#')
                        {
                            index = i + 2;
                            break;
                        }
                    }
                    k = 0;
                    for(int i = index; i < 255; i++)
                    {
                        if(webhost_buffer[i] != '#')
                        {
                            current_sys_user.email[k] = webhost_buffer[i];
                            k++;
                        }
                        if(webhost_buffer[i] == '#' && webhost_buffer[i + 1] == '#')
                        {
                            index = i + 2;
                            break;
                        }
                    }
                    k = 0;
                    for(int i = index; i < 255; i++)
                    {
                        if(webhost_buffer[i] != '#')
                        {
                            current_sys_user.login_from_ip[k] = webhost_buffer[i];
                            k++;
                        }
                        if(webhost_buffer[i] == '#' && webhost_buffer[i + 1] == '#')
                        {
                            index = i + 2;
                            break;
                        }
                    }
                    current_sys_user.last_login_time = dashou.char_to_time_t(webhost_buffer[index], webhost_buffer[index + 1], webhost_buffer[index + 2], webhost_buffer[index + 3],webhost_buffer[index + 4],webhost_buffer[index + 5]);
                    index += 6;
                    current_sys_user.is_blocked = webhost_buffer[index];
                    index ++;
                    current_sys_user.block_time = dashou.char_to_time_t(webhost_buffer[index], webhost_buffer[index + 1], webhost_buffer[index + 2], webhost_buffer[index + 3],webhost_buffer[index + 4],webhost_buffer[index + 5]);
                    index += 6;
                    current_sys_user.is_locked = webhost_buffer[index];
                    index ++;
                    current_sys_user.lock_time = dashou.char_to_time_t(webhost_buffer[index], webhost_buffer[index + 1], webhost_buffer[index + 2], webhost_buffer[index + 3],webhost_buffer[index + 4],webhost_buffer[index + 5]);
                    index += 6;
                    current_sys_user.password_try_counter = dashou.get_X4_Number(webhost_buffer[index], webhost_buffer[index + 1], webhost_buffer[index + 2], webhost_buffer[index + 3]);
                    index += 4;
                    current_sys_user.first_login_success = webhost_buffer[index];
                    index ++;
                    k = 0;
                    current_sys_user.authorities[k] = '[';
                    k ++;
                    for(int i = index; i < index + 22; i += 2)
                    {
                        current_sys_user.authorities[k] = webhost_buffer[i];
                        current_sys_user.authorities[k + 1] = webhost_buffer[i + 1];
                        k += 2;
                        current_sys_user.authorities[k] = ']';
                        if(k < 40)
                        {
                            current_sys_user.authorities[k + 1] = '[';
                        }
                        k += 2;
                    }
                    current_sys_user.Print_sys_user();
                    buffer = "";
                    buffer = genSysParam_response_user_auth_to_webhost(Setting_type, current_sys_user);
                    SSL_write(ssl, (char *)dashou.StringToByteArray(buffer), strlen(buffer.c_str()) / 2);
                    web_host_locked = true;
                    iResult = SSL_read(ssl, WebHost_buffer, DEFAULT_BUFLEN);
                    web_host_locked = false;
                    if (iResult < 0)
                    {
                        std::cout << "Error recv Web Host plate match level ACK...\n";
                    }
                    parser_host->parse2(WebHost_buffer);
                    report += log_udp.ACK_webhost_messege_Builder(parser_host);
                    log_udp.messege_Sender(report);
                }
                break;
            }
        }
        break;
        default:
        break;
    }
}
#endif

#ifndef get_information_functions

void finish_with_error(MYSQL *mysql, int error_code)
{
    fprintf(stderr, "%s\n", mysql_error(mysql));
    server_errors_log current_error(mysql);
    current_error.id = get_server_error_log_insert_aid();
    current_error.gid = Current_garage.gid/100000;
    std::string code = "Off" + to_String_X3_err(Current_garage.gid) + "DB" + to_String_X4_err(-1 * error_code);
    strcpy(current_error.err_code, code.c_str());
    strcpy(current_error.err_pos, Off000DB_err_position(-1 * error_code).c_str());
    strcpy(current_error.err_msg, Off000DB_err_message(error_code).c_str());
    current_error.err_time = time(0);
    current_error.created_at = time(0);
    int execute = current_error.insert_update_server_errors_log();
    if(execute == 0)
    {
        fprintf(stderr, "server error log inserted successfuly\n");
    }
    else
    {
        current_error.id = get_server_error_log_insert_aid();
        current_error.gid = Current_garage.gid/100000;
        std::string code = "Off" + to_String_X3_err(Current_garage.gid/100000) + "DB" + to_String_X4_err(execute);
        strcpy(current_error.err_pos, Off000DB_err_position(execute).c_str());
        strcpy(current_error.err_msg, Off000DB_err_message(-1 * execute).c_str());
        current_error.err_time = time(0);
        current_error.created_at = time(0);
        current_error.insert_update_server_errors_log();
    }
}

void unkown_error(MYSQL *mysql, int error_code)
{
    fprintf(stderr, "%s\n", mysql_error(mysql));
    server_errors_log current_error(mysql);
    current_error.id = get_server_error_log_insert_aid();
    current_error.gid = Current_garage.gid/100000;
    std::string code = "Off" + to_String_X3_err(Current_garage.gid/100000) + "UN" + to_String_X4_err(error_code);
    strcpy(current_error.err_pos, "main");
    strcpy(current_error.err_msg, Off000UN_err_message(-1 * error_code).c_str());
    current_error.err_time = time(0);
    current_error.created_at = time(0);
    int execute = current_error.insert_update_server_errors_log();
    if(execute == 0)
    {
        fprintf(stderr, "server error log inserted successfuly\n");
    }
    else
    {
        current_error.id = get_server_error_log_insert_aid();
        current_error.gid = Current_garage.gid/100000;
        std::string code = "Off" + to_String_X3_err(Current_garage.gid/100000) + "DB" + to_String_X4_err(execute);
        strcpy(current_error.err_pos, Off000DB_err_position(execute).c_str());
        strcpy(current_error.err_msg, Off000DB_err_message(-1 * execute).c_str());
        current_error.err_time = time(0);
        current_error.created_at = time(0);
    }
}

time_t string_to_time_t(const char *date)
{
    struct tm datetime;
    int yy, month, dd, hh, mm, ss;
    sscanf(date, "%d-%d-%d %d:%d:%d", &yy, &month, &dd, &hh, &mm, &ss);
    datetime.tm_year = yy - 1900;
    datetime.tm_mon = month - 1;
    datetime.tm_mday = dd;
    datetime.tm_hour = hh;
    datetime.tm_min = mm;
    datetime.tm_sec = ss;
    datetime.tm_isdst = -1;

    return mktime(&datetime);
}

void print_sites_list(MYSQL *mysql, std::vector<Site_type> _sites_list)
{
    Site_type current_Site(mysql);
    for(int i = 0; i < _sites_list.size(); i++)
    {
        current_Site = _sites_list[i];
        if(current_Site.id > 0)
        {
            current_Site.print_site();
        }
    }
}

void print_blacklist_list(MYSQL *mysql, std::vector<black_list_type> _black_list)
{
    black_list_type current_black_list(mysql);
    for(int i = 0; i < _black_list.size(); i++)
    {
        current_black_list = _black_list[i];
        current_black_list.print_black_list();
    }
}

void print_rule_name_hourly_list(MYSQL *mysql, std::vector<rule_name_hourly_type> _rule_name_hourly_type_list)
{
    rule_name_hourly_type current_rule_name_hourly(mysql);
    for(int i = 0; i < _rule_name_hourly_type_list.size(); i++)
    {
        current_rule_name_hourly = _rule_name_hourly_type_list[i];
        current_rule_name_hourly.print_rule_name_hourly_type();
    }
}

void print_zone_list(MYSQL *mysql, std::vector<Zone> _zones_list)
{
    Zone current_Zone(mysql);
    for(int i = 0; i < _zones_list.size(); i++)
    {
        current_Zone = _zones_list[i];
        current_Zone.print_Zone();
    }
}

void print_monthly_to_hourly_list(MYSQL *mysql, std::vector<monthly_to_hourly_type> _monthly_to_hourly_list)
{
    monthly_to_hourly_type current_monthly_to_hourly(mysql);
    for(int i = 0; i < _monthly_to_hourly_list.size(); i++)
    {
        current_monthly_to_hourly = _monthly_to_hourly_list[i];
        current_monthly_to_hourly.print_monthly_to_hourly_type();
    }
}

void print_camera_list(MYSQL *mysql, std::vector<Camera_type> _Camera_type_list)
{
    Camera_type current_Camera_type(mysql);
    for(int i = 0; i < _Camera_type_list.size(); i++)
    {
        current_Camera_type = _Camera_type_list[i];
        current_Camera_type.print_camera();
    }
}

void print_accountinfo_list(MYSQL *mysql, std::vector<accountInfo> _accountinfo_list)
{
    accountInfo current_account(mysql);
    for(int i = 0; i < _accountinfo_list.size(); i++)
    {
        current_account = _accountinfo_list[i];
        current_account.print_accountInfo();
    }
}

void print_account_state_list(MYSQL *mysql, std::vector<account_state> _account_state_list)
{
    account_state current_account(mysql);
    for(int i = 0; i < _account_state_list.size(); i++)
    {
        current_account = _account_state_list[i];
        current_account.print_account_state();
    }
}

void print_event_in_list(MYSQL *mysql, std::vector<event_in> _event_in_list)
{
    event_in current_event_in(mysql);
    for(int i = 0; i < _event_in_list.size(); i++)
    {
        current_event_in = _event_in_list[i];
        current_event_in.print_event_in();
    }
}

void print_event_out_list(MYSQL *mysql, std::vector<event_out> _event_out_list)
{
    event_out current_event_out(mysql);
    for(int i = 0; i < _event_out_list.size(); i++)
    {
        current_event_out = _event_out_list[i];
        current_event_out.print_event_out();
    }
}

void print_event_payment_list(MYSQL *mysql, std::vector<event_payment> _event_payment_list)
{
    event_payment current_event_payment(mysql);
    for(int i = 0; i < _event_payment_list.size(); i++)
    {
        current_event_payment = _event_payment_list[i];
        current_event_payment.print_event_payment();
    }
}

void print_event_charge_list(MYSQL *mysql, std::vector<event_charge> _event_charge_list)
{
    event_charge current_event_charge(mysql);
    for(int i = 0; i < _event_charge_list.size(); i++)
    {
        current_event_charge = _event_charge_list[i];
        
    }
}

void print_temp_card_list(MYSQL *mysql, std::vector<temp_card> _temp_card_list)
{
    temp_card current_temp_card(mysql);
    for(int i = 0; i < _temp_card_list.size(); i++)
    {
        current_temp_card = _temp_card_list[i];
        current_temp_card.print_Temp_Account();
    }
}

void print_group_inner_list(MYSQL *mysql, std::vector<group_inner> _group_inner_list)
{
    group_inner current_group_inner(mysql);
    for(int i = 0; i < _group_inner_list.size(); i++)
    {
        current_group_inner = _group_inner_list[i];
        current_group_inner.print_group_inner();
    }
}

void print_monthly_type_list(MYSQL *mysql, std::vector<monthly_type> _monthly_type_list)
{
    monthly_type current_monthly_type(mysql);
    for(int i = 0; i < _monthly_type_list.size(); i++)
    {
        current_monthly_type = _monthly_type_list[i];
        current_monthly_type.print_monthly_type();
    }
}

void print_rule_name_monthly_list(MYSQL *mysql, std::vector<rule_name_monthly> _rule_name_monthly_list)
{
    rule_name_monthly current_rule_name_monthly(mysql);
    for(int i = 0; i < _rule_name_monthly_list.size(); i++)
    {
        current_rule_name_monthly = _rule_name_monthly_list[i];
        current_rule_name_monthly.print_rule_name_monthly();
    }
}

void print_rule_step_monthly_list(MYSQL *mysql, std::vector<rule_step_monthly> _rule_step_monthly_list)
{
    rule_step_monthly current_rule_step_monthly(mysql);
    for(int i = 0; i < _rule_step_monthly_list.size(); i++)
    {
        current_rule_step_monthly = _rule_step_monthly_list[i];
        current_rule_step_monthly.print_rule_step_monthly();
    }
}

std::vector<black_list_type> read_db_black_list(MYSQL *mysql)
{
    std::vector<black_list_type> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_black_list");
    }
    catch(...)
    {
        finish_with_error(mysql, -5008);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5008);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5009);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5009);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            black_list_type current_black_list(mysql);
            current_black_list.id = std::stoi(row[0]);
            current_black_list.gid = std::stoi(row[1]);
            strcpy(current_black_list.description, row[2]);
            strcpy(current_black_list.ticket, row[3]);
            current_black_list.ticket_type = std::stoi(row[4]);
            strcpy(current_black_list.plate, row[5]);
            current_black_list._operator = std::stoi(row[6]);
            current_black_list.create_time = string_to_time_t(row[7]);
            readed_data.push_back(current_black_list);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5010);
    }
    return readed_data;
}

std::vector<rule_name_hourly_type> read_db_rule_name_hourly(MYSQL *mysql)
{
    std::vector<rule_name_hourly_type> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_rule_name_hourly");
    }
    catch(...)
    {
        finish_with_error(mysql, -5011);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5011);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5012);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5012);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            rule_name_hourly_type current_rule_name_hourly(mysql);
            current_rule_name_hourly.aid = std::stoi(row[0]);
            current_rule_name_hourly.gid = std::stoi(row[1]);
            current_rule_name_hourly.rule_serial = std::stoi(row[2]);
            strcpy(current_rule_name_hourly.fixed_time, row[3]);
            current_rule_name_hourly.limit_enable = std::stoi(row[4]);
            current_rule_name_hourly.limit_sum = std::stoi(row[5]);
            strcpy(current_rule_name_hourly.name, row[6]);
            current_rule_name_hourly.within_duration = std::stoi(row[7]);
            strcpy(current_rule_name_hourly.remark, row[8]);
            current_rule_name_hourly.tolerance = std::stoi(row[9]);
            current_rule_name_hourly._operator = std::stoi(row[10]);
            current_rule_name_hourly.flag = std::stoi(row[11]);
            current_rule_name_hourly.create_time = string_to_time_t(row[12]);
            readed_data.push_back(current_rule_name_hourly);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5013);
    }
    return readed_data;
}

std::vector<Zone> read_db_Zone(MYSQL *mysql)
{
    std::vector<Zone> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_lot_num");
    }
    catch(...)
    {
        finish_with_error(mysql, -5014);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5014);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5015);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5015);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            Zone current_Zone(mysql);
            current_Zone.aid = std::stoi(row[0]);
            current_Zone.gid = std::stoi(row[1]);
            current_Zone.serial = std::stoi(row[2]);
            strcpy(current_Zone.name, row[3]);
            current_Zone.asofficial = std::stoi(row[4]);
            current_Zone.cover_pgm_id = std::stoi(row[5]);
            current_Zone.align_pgm_id = std::stoi(row[6]);
            current_Zone.vacantSpacesHourly = std::stoi(row[7]);
            current_Zone.vacantSpacesSeason = std::stoi(row[8]);
            current_Zone.vacantSpaces = std::stoi(row[9]);
            current_Zone.totalSpaces = std::stoi(row[10]);
            current_Zone.totalSpacesHourly = std::stoi(row[11]);
            current_Zone.totalSpacesSeason = std::stoi(row[12]);
            strcpy(current_Zone.insites_list, row[13]);
            strcpy(current_Zone.outsites_list, row[14]);
            current_Zone.parking_Guidance_Available_Space = std::stoi(row[15]);
            current_Zone.parking_Guidance_Total_Space = std::stoi(row[16]);
            current_Zone.flag = std::stoi(row[17]);
            current_Zone._operator = std::stoi(row[18]);
            current_Zone.createtime = string_to_time_t(row[19]);
            //
            int counter = 0;
            char sites_stroke_list[100] = "";
            strcpy(sites_stroke_list, current_Zone.insites_list);
            char * pch = strtok (sites_stroke_list,",");
            while (pch != NULL)
            {
                current_Zone.entry_address[counter] = atoi(pch);
                pch = strtok (NULL, ",");
                counter++;
            }
            counter = 0;
            char sites_stroke_list2[100] = "";
            strcpy(sites_stroke_list2, current_Zone.outsites_list);
            pch = strtok (sites_stroke_list2,",");
            while (pch != NULL)
            {
                current_Zone.exit_address[counter] = atoi(pch);
                pch = strtok (NULL, ",");
                counter++;
            }
            readed_data.push_back(current_Zone);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5016);
    }
    return readed_data;
}

std::vector<monthly_to_hourly_type> read_db_monthly_to_hourly(MYSQL *mysql)
{
    std::vector<monthly_to_hourly_type> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_monthly_to_hourly");
    }
    catch(...)
    {
        finish_with_error(mysql, -5017);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5017);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5018);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5018);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            monthly_to_hourly_type current_monthly_to_hourly_type(mysql);
            current_monthly_to_hourly_type.id = std::stoi(row[0]);
            current_monthly_to_hourly_type.gid = std::stoi(row[1]);
            strcpy(current_monthly_to_hourly_type.name, row[2]);
            strcpy(current_monthly_to_hourly_type.hour_charge_type, row[3]);
            current_monthly_to_hourly_type.flag = std::stoi(row[4]);
            current_monthly_to_hourly_type._operator = std::stoi(row[5]);
            current_monthly_to_hourly_type.create_time = string_to_time_t(row[6]);
            readed_data.push_back(current_monthly_to_hourly_type);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5019);
    }
    return readed_data;
}

std::vector<Camera_type> read_db_camera(MYSQL *mysql)
{
    std::vector<Camera_type> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_camerato_site");
    }
    catch(...)
    {
        finish_with_error(mysql, -5020);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5020);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5021);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5021);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            Camera_type current_Camera_type(mysql);
            current_Camera_type.gid = std::stoi(row[0]);
            strcpy(current_Camera_type.ip, row[1]);
            strcpy(current_Camera_type.Camera_name, row[2]);
            strcpy(current_Camera_type.user_name, row[3]);
            strcpy(current_Camera_type.password, row[4]);
            strcpy(current_Camera_type.site_Addresses, row[5]);
            current_Camera_type._operator = std::stoi(row[6]);
            current_Camera_type.create_time = string_to_time_t(row[7]);
            memset(current_Camera_type.sites_binded, 0, sizeof(current_Camera_type.sites_binded));
            current_Camera_type.cam_address = std::stoi(std::string(current_Camera_type.ip));
            int counter = 0;
            char sites_stroke_list[100] = "";
            strcpy(sites_stroke_list, current_Camera_type.site_Addresses);
            char * pch = strtok (sites_stroke_list,",");
            while (pch != NULL)
            {
                current_Camera_type.sites_binded[counter] = atoi(pch);
                pch = strtok (NULL, ",");
                counter++;
            }
            readed_data.push_back(current_Camera_type);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5022);
    }
    return readed_data;
}

std::vector<accountInfo> read_db_accountInfo(MYSQL *mysql)
{
    std::vector<accountInfo> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_account_info");
    }
    catch(...)
    {
        finish_with_error(mysql, -5023);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5023);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5024);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5024);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            accountInfo current_account(mysql);
            current_account.id = std::stoi(row[0]);
            current_account.gid = std::stoi(row[1]);
            strcpy(current_account.tickets, row[2]);
            current_account.ticket_type = std::stoi(row[3]);
            strcpy(current_account.plate, row[4]);
            current_account.start_time = string_to_time_t(row[5]);
            current_account.end_time = string_to_time_t(row[6]);
            current_account.access_group = std::stoi(row[7]);
            current_account.inner_group = std::stoi(row[8]);
            current_account.time_group = std::stoi(row[9]);
            current_account.lots_group = std::stoi(row[10]);
            current_account.account_state = std::stoi(row[11]);
            current_account.parking_type = std::stoi(row[12]);
            strcpy(current_account.addr, row[13]);
            strcpy(current_account.description, row[14]);
            strcpy(current_account.email, row[15]);
            strcpy(current_account.phone, row[16]);
            strcpy(current_account.owner_name, row[17]);
            strcpy(current_account.hour_ticket_num, row[18]);
            current_account.hour_ticket_type = std::stoi(row[19]);
            current_account.lot_id = std::stoi(row[20]);
            strcpy(current_account.online_member, row[21]);
            current_account.prepaid_charge_rule = std::stoi(row[22]);
            current_account.monthly_charge_rule = std::stoi(row[23]);
            current_account.ticket_lpbind = std::stoi(row[24]);
            current_account.monthly_type = std::stoi(row[25]);
            current_account.limit_time = string_to_time_t(row[26]);
            current_account._operator = std::stoi(row[27]);
            current_account.create_time = string_to_time_t(row[28]);
            strcpy(current_account.photo_id, row[29]);
            strcpy(current_account.add_info1, row[30]);
            strcpy(current_account.add_info2, row[31]);
            readed_data.push_back(current_account);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5025);
    }
    return readed_data;
}

std::vector<account_state> read_db_account_state(MYSQL *mysql)
{
    std::vector<account_state> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_account_state");
    }
    catch(...)
    {
        finish_with_error(mysql, -5026);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5026);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5027);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5027);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            account_state current_account(mysql);
            current_account.aid = std::stoi(row[0]);
            current_account.gid = std::stoi(row[1]);
            current_account.ticket_type = std::stoi(row[2]);
            strcpy(current_account.ticket, row[3]);
            strcpy(current_account.plate, row[4]);
            current_account.create_time = string_to_time_t(row[5]);
            current_account.parking_type = std::stoi(row[6]);
            current_account.present_type = std::stoi(row[7]);
            current_account.intime = string_to_time_t(row[8]);
            current_account.inserial = std::stoi(row[9]);
            current_account.outtime = string_to_time_t(row[10]);
            current_account.outserial = std::stoi(row[11]);
            current_account.pay_time = string_to_time_t(row[12]);
            current_account.pay_serial = std::stoi(row[13]);
            current_account.paid_sum = std::stoi(row[14]);
            current_account.charge_type = std::stoi(row[15]);
            current_account.inner_intime = string_to_time_t(row[16]);
            current_account.inner_inserial = std::stoi(row[17]);
            current_account.inner_outtime = string_to_time_t(row[18]);
            current_account.inner_outserial = std::stoi(row[19]);
            current_account.limit_sum = std::stoi(row[20]);
            strcpy(current_account.online_order, row[21]);
            current_account.insite = std::stoi(row[22]);
            current_account.charge_site = std::stoi(row[23]);
            current_account.inner_insite = std::stoi(row[24]);
            current_account.inner_outsite = std::stoi(row[25]);
            current_account.prepaid_balance = std::stoi(row[26]);
            current_account.l2_id = std::stoi(row[27]);
            current_account.prepaid_account_id = std::stoi(row[28]);
            strcpy(current_account.hour_ticket_num, row[29]);
            current_account.hour_ticket_type = std::stoi(row[30]);
            current_account.coupon_total_sum = std::stoi(row[31]);
            current_account.coupon_total_time = std::stoi(row[32]);
            current_account.total_sum = std::stoi(row[33]);
            readed_data.push_back(current_account);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5028);
    }
    return readed_data;
}

std::vector<event_in> read_db_event_in(MYSQL *mysql)
{
    std::vector<event_in> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_event_in");
    }
    catch(...)
    {
        finish_with_error(mysql, -5029);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5029);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5030);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5030);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            event_in current_event_in(mysql);
            current_event_in.aid = std::stoi(row[0]);
            current_event_in.gid = std::stoi(row[1]);
            current_event_in.inTime = string_to_time_t(row[2]);
            current_event_in.inSerial = std::stoi(row[3]);
            current_event_in.receTime = string_to_time_t(row[4]);
            current_event_in.inType = std::stoi(row[5]);
            strcpy(current_event_in.ticket, row[6]);
            current_event_in.ticketType = std::stoi(row[7]);
            strcpy(current_event_in.plate, row[8]);
            current_event_in.totalLots = std::stoi(row[9]);
            current_event_in.monthlyLots = std::stoi(row[10]);
            current_event_in.hourlyLots = std::stoi(row[11]);
            current_event_in.freeTotalLots = std::stoi(row[12]);
            current_event_in.freeMonthlyLots = std::stoi(row[13]);
            current_event_in.freeHourlyLots = std::stoi(row[14]);
            current_event_in.site = std::stoi(row[15]);
            current_event_in.realIntime = string_to_time_t(row[16]);
            strcpy(current_event_in.orderNum, row[17]);
            strcpy(current_event_in.photoID, row[18]);
            current_event_in.isNotUp = std::stoi(row[19]);
            current_event_in.lotsGroupId = std::stoi(row[20]);
            current_event_in.lotsGroupUsed = std::stoi(row[21]);
            current_event_in._operator = std::stoi(row[22]);
            current_event_in.lotID = std::stoi(row[23]);
            current_event_in.monthlyType = std::stoi(row[24]);
            readed_data.push_back(current_event_in);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5031);
    }
    return readed_data;
    
}

std::vector<event_out> read_db_event_out(MYSQL *mysql)
{
    std::vector<event_out> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_event_out");
    }
    catch(...)
    {
        finish_with_error(mysql, -5032);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5032);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5033);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5033);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            event_out current_event_out(mysql);
            current_event_out.aid = std::stoi(row[0]);
            current_event_out.gid = std::stoi(row[1]);
            current_event_out.out_time = string_to_time_t(row[2]);
            current_event_out.out_serial = std::stoi(row[3]);
            current_event_out.out_type = std::stoi(row[4]);
            current_event_out.rece_time = string_to_time_t(row[5]);
            strcpy(current_event_out.ticket, row[6]);
            current_event_out.ticket_type = std::stoi(row[7]);
            strcpy(current_event_out.plate, row[8]);
            current_event_out.total_paid = std::stoi(row[9]);
            current_event_out.in_time = string_to_time_t(row[10]);
            current_event_out.in_serial = std::stoi(row[11]);
            current_event_out.total_lots = std::stoi(row[12]);
            current_event_out.monthly_lots = std::stoi(row[13]);
            current_event_out.hourly_lots = std::stoi(row[14]);
            current_event_out.free_total_lots = std::stoi(row[15]);
            current_event_out.free_monthly_lots = std::stoi(row[16]);
            current_event_out.free_hourly_lots = std::stoi(row[17]);
            current_event_out.site = std::stoi(row[18]);
            strcpy(current_event_out.order_num, row[19]);
            strcpy(current_event_out.photo_id, row[20]);
            current_event_out.isnotup = std::stoi(row[21]);
            current_event_out.lots_group_id = std::stoi(row[22]);
            current_event_out.lots_group_occupied = std::stoi(row[23]);
            current_event_out.park_duration = std::stoi(row[24]);
            current_event_out._operator = std::stoi(row[25]);
            current_event_out.total_should = std::stoi(row[26]);
            current_event_out.coupon_total_sum = std::stoi(row[27]);
            current_event_out.coupon_total_time = std::stoi(row[28]);
            current_event_out.coupon_real_sum = std::stoi(row[29]);
            current_event_out.coupon_real_time = std::stoi(row[30]);
            current_event_out.charge_type = std::stoi(row[31]);
            current_event_out.lotID = std::stoi(row[32]);
            current_event_out.monthlyType = std::stoi(row[33]);
            readed_data.push_back(current_event_out);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5034);
    }
    return readed_data;
}

std::vector<event_payment> read_db_event_payment(MYSQL *mysql)
{
    std::vector<event_payment> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_event_payment");
    }
    catch(...)
    {
        finish_with_error(mysql, -5035);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5035);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5036);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5036);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            event_payment current_event_payment(mysql);
            current_event_payment.aid = std::stoi(row[0]);
            current_event_payment.gid = std::stoi(row[1]);
            current_event_payment.event_time = string_to_time_t(row[2]);
            current_event_payment.serial = std::stoi(row[3]);
            current_event_payment.rece_time = string_to_time_t(row[4]);
            current_event_payment.type = std::stoi(row[5]);
            strcpy(current_event_payment.ticket, row[6]);
            current_event_payment.ticket_type = std::stoi(row[7]);
            strcpy(current_event_payment.plate, row[8]);
            current_event_payment.currency_sum = std::stoi(row[9]);
            current_event_payment.coin_sum = string_to_time_t(row[10]);
            current_event_payment.currency_balance = std::stoi(row[11]);
            current_event_payment.coin_balance = std::stoi(row[12]);
            current_event_payment._operator = std::stoi(row[13]);
            current_event_payment.site = std::stoi(row[14]);
            readed_data.push_back(current_event_payment);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5037);
    }
    return readed_data;
    
}

std::vector<event_charge> read_db_event_charge(MYSQL *mysql)
{
    std::vector<event_charge> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_event_charge");
    }
    catch(...)
    {
        finish_with_error(mysql, -5038);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5038);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5039);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5039);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        int i = 0;
        while ((row = mysql_fetch_row(result)))
        {
            event_charge current_event_charge(mysql);
            current_event_charge.aid = std::stol(row[0]);
            current_event_charge.gid = std::stoi(row[1]);
            current_event_charge.charge_time = string_to_time_t(row[2]);
            current_event_charge.charge_serial = std::stoi(row[3]);
            current_event_charge.actually_pay = std::stoi(row[4]);
            current_event_charge.charge_type = std::stoi(row[5]);
            current_event_charge.payment_type = std::stoi(row[6]);
            current_event_charge.start_time = string_to_time_t(row[7]);
            current_event_charge.end_time = string_to_time_t(row[8]);
            current_event_charge.in_serial = std::stoi(row[9]);
            current_event_charge.in_time = string_to_time_t(row[10]);
            current_event_charge.isnotup = std::stoi(row[11]);
            strcpy(current_event_charge.ticket ,row[12]);
            current_event_charge.ticket_type = std::stoi(row[13]);
            strcpy(current_event_charge.plate, row[14]);
            strcpy(current_event_charge.online_member_id, row[15]);
            strcpy(current_event_charge.order_num, row[16]);
            strcpy(current_event_charge.other_order_num, row[17]);
            current_event_charge.park_duration = std::stoll(row[18]);
            strcpy(current_event_charge.photo_id, row[19]);
            current_event_charge.should_pay = std::stoi(row[20]);
            current_event_charge.site = std::stoi(row[21]);
            current_event_charge.group_prepaid_serial = std::stoi(row[22]);
            current_event_charge.balance = std::stoll(row[23]);
            current_event_charge.coupon_type = std::stoi(row[24]);
            current_event_charge._operator = std::stoi(row[25]);
            current_event_charge.rece_time = string_to_time_t(row[26]);
            current_event_charge.reserve_state = std::stoi(row[27]);
            current_event_charge.warn = std::stoi(row[28]);
            current_event_charge.pcode = std::stoi(row[29]);
            current_event_charge.invoiced = std::stoi(row[30]);
            current_event_charge.tpid = std::stoi(row[31]);
            current_event_charge.coupon_out_id = std::stoll(row[32]);
            current_event_charge.lotid = std::stol(row[33]);
            strcpy(current_event_charge.phone, row[34]);
            strcpy(current_event_charge.owner_name, row[35]);

            readed_data.push_back(current_event_charge);

        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5040);
    }
    return readed_data;
}

std::vector<temp_card> read_db_temp_card(MYSQL *mysql)
{
    std::vector<temp_card> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_tmp_cards_130000");
    }
    catch(...)
    {
        finish_with_error(mysql, -5041);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5041);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5042);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5042);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            temp_card current_temp_card(mysql);
            current_temp_card.id = std::stoi(row[0]);
            current_temp_card.operate_type = std::stoi(row[1]);
            current_temp_card.ticket_type = std::stoi(row[2]);
            strcpy(current_temp_card.ticket, row[3]);
            strcpy(current_temp_card.plate, row[4]);
            current_temp_card.account_state = std::stoi(row[5]);
            current_temp_card.parking_type = std::stoi(row[6]);
            current_temp_card.present_type = std::stoi(row[7]);
            current_temp_card.in_time = string_to_time_t(row[8]);
            current_temp_card.pay_time = string_to_time_t(row[9]);
            current_temp_card.inner_intime = string_to_time_t(row[10]);
            current_temp_card.inner_outtime = string_to_time_t(row[11]);
            current_temp_card.insite = std::stoi(row[12]);
            current_temp_card.charge_site = std::stoi(row[13]);
            current_temp_card.inner_insite = std::stoi(row[14]);
            current_temp_card.inner_outsite = std::stoi(row[15]);
            current_temp_card.coupon_total_time = std::stoi(row[16]);
            current_temp_card.coupon_total_sum = std::stoi(row[17]);
            current_temp_card.limit_sum = std::stoi(row[18]);
            current_temp_card.limit_time = string_to_time_t(row[19]);
            current_temp_card.paid_sum = std::stoi(row[20]);
            strcpy(current_temp_card.online_order, row[21]);
            current_temp_card.hour_ticket_type = std::stoi(row[22]);
            strcpy(current_temp_card.hour_ticket_num, row[23]);
            current_temp_card.charge_type = std::stoi(row[24]);
            current_temp_card.access_group = std::stoi(row[25]);
            current_temp_card.start_time = string_to_time_t(row[26]);
            current_temp_card.end_time = string_to_time_t(row[27]);
            current_temp_card.prepaid_balance = std::stoi(row[28]);
            current_temp_card.prepaid_account_id = std::stoi(row[29]);
            current_temp_card.monthly_type = std::stoi(row[30]);
            current_temp_card.lots_group = std::stoi(row[31]);
            current_temp_card.ticket_lpbind = std::stoi(row[32]);
            current_temp_card.inner_group = std::stoi(row[33]);
            current_temp_card.time_group = std::stoi(row[34]);
            strcpy(current_temp_card.lot_name, row[35] ? row[35] : "");
            current_temp_card.prepaid_charge_rule = std::stoi(row[36]);
            current_temp_card.monthly_charge_rule = std::stoi(row[37]);
            strcpy(current_temp_card.photo_id, row[38]);
            strcpy(current_temp_card.owner_name, row[39]);
            strcpy(current_temp_card.phone, row[40]);
            strcpy(current_temp_card.email, row[41]);
            strcpy(current_temp_card.addr, row[42]);
            strcpy(current_temp_card.description, row[43]);
            strcpy(current_temp_card.add_info1, row[44]);
            strcpy(current_temp_card.add_info2, row[45]);
            current_temp_card.has_downloaded = std::stoi(row[46]);
            readed_data.push_back(current_temp_card);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5043);
    }
    return readed_data;
    
}

std::vector<group_inner> read_db_group_inner(MYSQL *mysql)
{
    std::vector<group_inner> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_group_inner");
    }
    catch(...)
    {
        finish_with_error(mysql, -5044);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5044);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5045);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5045);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            group_inner current_group_inner(mysql);
            current_group_inner.id = std::stoi(row[0]);
            current_group_inner.gid = std::stoi(row[1]);
            current_group_inner.inner_charge = std::stoi(row[2]);
            strcpy(current_group_inner.name, row[3]);
            strcpy(current_group_inner.sites_list, row[4]);
            current_group_inner.outer_charge = std::stoi(row[5]);
            current_group_inner.flag = std::stoi(row[6]);
            current_group_inner._operator = std::stoi(row[7]);
            current_group_inner.createtime = string_to_time_t(row[8]);
            readed_data.push_back(current_group_inner);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5046);
    }
    return readed_data;
}

std::vector<monthly_type> read_db_monthly_type(MYSQL *mysql)
{
    std::vector<monthly_type> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_monthly_type");
    }
    catch(...)
    {
        finish_with_error(mysql, -5047);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5047);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5048);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5048);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            monthly_type current_monthly_type(mysql);
            current_monthly_type.aid = std::stoi(row[0]);
            current_monthly_type.id = std::stoi(row[1]);
            current_monthly_type.gid = std::stoi(row[2]);
            current_monthly_type.type = std::stoi(row[3]);
            current_monthly_type.access_group_id = std::stoi(row[4]);
            current_monthly_type.time_group_id = std::stoi(row[5]);
            current_monthly_type.inner_group_id = std::stoi(row[6]);
            current_monthly_type.monthly_charge_rule = std::stoi(row[7]);
            current_monthly_type.prepaid_charge_rule = std::stoi(row[8]);
            current_monthly_type.vip_flag = std::stoi(row[9]);
            current_monthly_type.reserved = std::stoi(row[10]);
            strcpy(current_monthly_type.name, row[11]);
            strcpy(current_monthly_type.description, row[12]);
            current_monthly_type.flag = std::stoi(row[13]);
            current_monthly_type._operator = std::stoi(row[14]);
            current_monthly_type.createtime = string_to_time_t(row[15]);
            current_monthly_type.lotgroup_countingtype = std::stoi(row[16]);
            current_monthly_type.expires = std::stoi(row[17]);
            readed_data.push_back(current_monthly_type);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5049);
    }
    return readed_data;
}

std::vector<rule_name_monthly> read_db_rule_name_monthly(MYSQL *mysql)
{
    std::vector<rule_name_monthly> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_rule_name_monthly");
    }
    catch(...)
    {
        finish_with_error(mysql, -5050);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5050);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5051);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5051);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
        rule_name_monthly current_rule_name_monthly(mysql);
        current_rule_name_monthly.gid = std::stoi(row[0]);
        current_rule_name_monthly.rule_serial = std::stoi(row[1]);
        strcpy(current_rule_name_monthly.name, row[2]);
        strcpy(current_rule_name_monthly.remark, row[3]);
        current_rule_name_monthly.flag = std::stoi(row[4]);
        current_rule_name_monthly._operator = std::stoi(row[5]);
        current_rule_name_monthly.createtime = string_to_time_t(row[6]);
        readed_data.push_back(current_rule_name_monthly);
    }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5052);
    }
    return readed_data;
}

std::vector<rule_step_monthly> read_db_rule_step_monthly(MYSQL *mysql)
{
    std::vector<rule_step_monthly> readed_data;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT * FROM v32_rule_step_monthly");
    }
    catch(...)
    {
        finish_with_error(mysql, -5053);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5053);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5054);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5054);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            rule_step_monthly current_rule_step_monthly(mysql);
            current_rule_step_monthly.gid = std::stoi(row[0]);
            current_rule_step_monthly.rule_serial = std::stoi(row[1]);
            current_rule_step_monthly.step_serial = std::stoi(row[2]);
            current_rule_step_monthly.max_units = std::stoi(row[3]);
            current_rule_step_monthly.duration = std::stoi(row[4]);
            current_rule_step_monthly.unit_sum = std::stoi(row[5]);
            current_rule_step_monthly.flag = std::stoi(row[6]);
            current_rule_step_monthly._operator = std::stoi(row[7]);
            current_rule_step_monthly.createtime = string_to_time_t(row[8]);
            readed_data.push_back(current_rule_step_monthly);
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5055);
    }
    return readed_data;
}

int get_account_info_insert_aid()
{
    int max_id = -1;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT MAX(aid) AS Max FROM v32_account_info");
    }
    catch(...)
    {
        finish_with_error(mysql, -5056);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5056);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5057);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5057);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            max_id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5058);
    }
    return ++max_id;
}

int get_account_state_insert_aid()
{
    int max_id = -1;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT MAX(aid) AS Max FROM v32_account_state");
    }
    catch(...)
    {
        finish_with_error(mysql, -5059);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5059);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5060);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5060);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            max_id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5061);
    }
    return ++max_id;    
}

int get_event_in_insert_aid()
{
    int max_id = -1;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT MAX(aid) AS Max FROM v32_event_in");
    }
    catch(...)
    {
        finish_with_error(mysql, -5062);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5062);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5063);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5063);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            max_id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5064);
    }
    return ++max_id; 
}

int get_event_out_insert_aid()
{
    int max_id = -1;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT MAX(aid) AS Max FROM v32_event_out");
    }
    catch(...)
    {
        finish_with_error(mysql, -5065);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5065);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5066);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5066);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            max_id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5067);
    }
    return ++max_id; 
}

int get_event_payment_insert_aid()
{
    int max_id = -1;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT MAX(aid) AS Max FROM v32_event_payment");
    }
    catch(...)
    {
        finish_with_error(mysql, -5068);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5068);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5069);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5069);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            max_id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5070);
    }
    return ++max_id; 
}

int get_event_charge_insert_aid()
{
    int max_id = -1;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT MAX(aid) AS Max FROM v32_event_charge");
    }
    catch(...)
    {
        finish_with_error(mysql, -5071);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5071);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5072);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5072);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            max_id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5073);
    }
    return ++max_id; 
}

int get_temp_card_insert_id()
{
    int max_id = -1;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT MAX(id) AS Max FROM v32_tmp_cards_130000");
    }
    catch(...)
    {
        finish_with_error(mysql, -5074);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5074);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5075);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5075);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            max_id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5076);
    }
    return ++max_id;
}

int get_aid_monthly_type_from_id(int id)
{
    int aid = -1;
    int execute = 0;
    std::string stmt = "SELECT aid FROM v32_monthly_type WHERE id = " + std::to_string(id);
    try
    {
        execute = mysql_query(mysql, stmt.c_str());
    }
    catch(...)
    {
        finish_with_error(mysql, -5077);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5077);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5078);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5078);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            aid = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5079);
    }
    return aid;
}

int get_monthly_type_insert_aid()
{
    int max_id = -1;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT MAX(aid) AS Max FROM v32_monthly_type");
        
    }
    catch(...)
    {
        finish_with_error(mysql, -5080);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5080);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5081);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5081);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            max_id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5082);
    }
    return ++max_id;
}

int get_server_error_log_insert_aid()
{
    int max_id = -1;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT MAX(id) + 1 AS Max FROM server_errors_log;");
    }
    catch(...)
    {
        finish_with_error(mysql, -5083);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5083);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5084);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5084);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            max_id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5085);
    }
    return max_id;
}

int get_photo_insert_aid()
{
    int max_id = -1;
    int execute = 0;
    try
    {
        execute = mysql_query(mysql, "SELECT MAX(id) AS Max FROM v32_photo");
    }
    catch(...)
    {
        finish_with_error(mysql, -5086);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5086);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5087);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5087);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            max_id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5088);
    }
    return ++max_id;
}

int search_for_account(std::string ticket, std::string plate)
{
    if(plate == "" || plate[0] == 0)
    {
        accountInfo current_accountInfo(mysql);
        current_accountInfo.Select_account_by_ticket(ticket);
        if(current_accountInfo.id > 0 && current_accountInfo.gid > 0)
        {
            return current_accountInfo.id;
        }
    }
    else if(ticket == "" || ticket[0] == 0)
    {
        accountInfo current_accountInfo(mysql);
        current_accountInfo.Select_account_by_plate(plate, Current_Settings.plate_match_level);
        if(current_accountInfo.id > 0 && current_accountInfo.gid > 0)
        {
            return current_accountInfo.id;
        }
    }
    return -1;
}

int search_for_camera(int site_id)
{
    for(int i = 0; i < All_Cameras.size(); i++)
    {
        int j = 0;
        for(j = 0; All_Cameras[i].sites_binded[j] != 0; j++)
        {
            if(site_id == All_Cameras[i].sites_binded[j])
            {
                return std::stoi(std::string(All_Cameras[i].ip));
            }
        }
    }
    return -1;
}

void make_event_in(event_in &current_event_in, int site_id, camera_event current_camera_event)
{
    current_event_in.aid = get_event_in_insert_aid();
    current_event_in.gid = Current_garage.gid;
    current_event_in.inTime = time(0);
    current_event_in.inSerial = gen_Entry_serial;
    current_event_in.receTime = time(0);
    strcpy(current_event_in.ticket, "");
    strcpy(current_event_in.plate, current_camera_event.current_TrafficCar.PlateNumber);
    int zone_id = -1;
    zone_id = get_zone_id_by_site(site_id);
    Zone zone(mysql); 
    if(zone_id >= 0)
    {
        zone.select_Zone(zone_id);
        current_event_in.totalLots = zone.totalSpaces;
        current_event_in.monthlyLots = zone.totalSpacesSeason;
        current_event_in.hourlyLots = zone.totalSpacesHourly;
        current_event_in.freeTotalLots = zone.vacantSpaces;
        current_event_in.freeMonthlyLots = zone.vacantSpacesSeason;
        current_event_in.freeHourlyLots = zone.vacantSpacesHourly;
    }
    else
    {
        current_event_in.totalLots = 0xff7f;
        current_event_in.monthlyLots = 0xff7f;
        current_event_in.hourlyLots = 0xff7f;
        current_event_in.freeTotalLots = 0xff7f;
        current_event_in.freeMonthlyLots = 0xff7f;
        current_event_in.freeHourlyLots = 0xff7f;
    }
    current_event_in.site = site_id;
    current_event_in.realIntime = dashou.char_to_time_t(0,1,1,0,0,0);
    current_event_in.isNotUp = 0;
    current_event_in.lotsGroupId = 0xffff;
    current_event_in.lotsGroupUsed = 0xffff;
    current_event_in._operator = 1;
    current_event_in.lotID = 0;
    current_event_in.monthlyType = 0xff;
}

void make_event_charge(accountInfo current_accountInfo, account_state current_account_state, event_charge &current_event_charge)
{
    current_event_charge.charge_time = time(0);
    current_event_charge.charge_serial = current_account_state.pay_serial;
    current_event_charge.charge_type = current_account_state.charge_type;
    current_event_charge.start_time = current_accountInfo.start_time;
    current_event_charge.end_time = current_accountInfo.end_time;
    current_event_charge.in_serial = current_account_state.inserial;
    current_event_charge.in_time = current_account_state.intime;
    strcpy(current_event_charge.ticket, current_account_state.ticket);
    current_event_charge.ticket_type = current_account_state.ticket_type;
    strcpy(current_event_charge.plate, current_account_state.plate);
    strcpy(current_event_charge.online_member_id, current_accountInfo.online_member);
    strcpy(current_event_charge.order_num, current_account_state.online_order);
    current_account_state.pay_time = current_event_charge.charge_time;
    current_event_charge.park_duration = std::difftime(current_event_charge.charge_time, current_account_state.intime);
    std::cout << "current_event_charge.park_duration = " << current_event_charge.park_duration << "\n";
    strcpy(current_event_charge.photo_id, current_accountInfo.photo_id);
    Proof cost_calculator(mysql, current_account_state.charge_type, current_account_state.insite);
    current_event_charge.should_pay = cost_calculator.get_parking_cost( current_account_state.intime, current_account_state.pay_time);
    current_event_charge.should_pay -= current_event_charge.actually_pay;
    std::cout << "current_event_charge.should_pay = " << current_event_charge.should_pay << "\n";
    current_event_charge.site = current_account_state.charge_site;
    current_event_charge.balance = current_account_state.prepaid_balance;
    //current_event_charge.coupon_type = ???
    current_event_charge._operator = current_accountInfo._operator;
    current_event_charge.rece_time = time(0);
    //current_event_charge.reserve_state = ???
    //current_event_charge.warn = ???      
    //current_event_charge.pcode = ???
    //current_event_charge.invoiced = ???
    //current_event_charge.tpid = ???
    //current_event_charge.coupon_out_id = ???
    current_event_charge.lotid = current_accountInfo.lot_id;
    strcpy(current_event_charge.phone, current_accountInfo.phone);
    strcpy(current_event_charge.owner_name, current_accountInfo.owner_name);
    std::cout << "end_function_make_event_charge" << "\n";
}

void make_event_out(accountInfo current_accountInfo, account_state current_account_state, event_out &current_event_out, int site_id)
{
    current_event_out.aid = get_event_out_insert_aid();
    current_event_out.gid = Current_garage.gid;
    current_event_out.out_time = current_account_state.outtime;
    current_event_out.out_serial = current_account_state.outserial;
    current_event_out.rece_time = time(0);
    strcpy(current_event_out.ticket, "");
    current_event_out.ticket_type = current_account_state.ticket_type;
    strcpy(current_event_out.plate, current_account_state.plate);
    current_event_out.total_paid = current_account_state.paid_sum;
    current_event_out.in_time = current_account_state.intime;
    current_event_out.in_serial = current_account_state.inserial;
    int zone_id = -1;
    zone_id = get_zone_id_by_site(current_event_out.site);
    if(zone_id > 0)
    {
        Zone zone(mysql); 
        zone.select_Zone(zone_id);
        current_event_out.total_lots = zone.totalSpaces;
        current_event_out.monthly_lots = zone.totalSpacesSeason;
        current_event_out.hourly_lots = zone.totalSpacesHourly;
        current_event_out.free_total_lots = zone.vacantSpaces;
        current_event_out.free_monthly_lots = zone.vacantSpacesSeason;
        current_event_out.free_hourly_lots = zone.vacantSpacesHourly;
    }
    else
    {
        current_event_out.total_lots = 0xff7f;
        current_event_out.monthly_lots = 0xff7f;
        current_event_out.hourly_lots = 0xff7f;
        current_event_out.free_total_lots = 0xff7f;
        current_event_out.free_monthly_lots = 0xff7f;
        current_event_out.free_hourly_lots = 0xff7f;
    }
    current_event_out.site = sites[site_id].id;           
    strcpy(current_event_out.order_num, current_account_state.online_order);
    strcpy(current_event_out.photo_id, current_accountInfo.photo_id);
//    if(out_type == tablet_reads_QR_code)
//    {
//        current_event_charge.Select_charge_event_by_ticket(current_account_state.ticket);
//    }
//    else if (out_type == tablet_input_license_plate_number)
//    {
//        current_event_charge.Select_charge_event_by_plate(current_account_state.plate, Current_Settings.plate_match_level);
//    }
    Site_type out_site(mysql);
    out_site.Select_Site_type_by_address(current_event_out.site);
    int auto_open_free = out_site.exitFreeLetPass % 128;
//    if(current_accountInfo.parking_type == hourly_parker)
//    {
//        Let_pass_or_not = ((current_account_state.paid_sum == current_account_state.limit_sum) && (current_event_charge.aid > 0) && current_event_charge.park_duration != 0);
//        if(Let_pass_or_not)
//        {
//            current_event_out.out_type = current_accountInfo.parking_type;
//        }
//        else
//        {
//            current_event_out.out_type = out_prices;
//        }
//        std::cout << "current_event_out.out_type = " << dashou.ENTRY_EXIT_TYPE_To_string(current_event_out.out_type) << "\n" ;
//        Proof cost_calculator(mysql, current_account_state.charge_type, current_account_state.insite);
//        current_event_charge.should_pay = cost_calculator.get_parking_cost( current_account_state.intime, time(0));
//        current_event_charge.should_pay -= current_event_charge.actually_pay;
//        current_event_charge.park_duration = std::difftime(time(0), current_account_state.intime);
//        current_event_out.park_duration = current_event_charge.park_duration;
//        std::cout << "current_event_out.park_duration = " << current_event_out.park_duration << "\n";
//        current_event_out.total_should = current_event_charge.should_pay;
//        std::cout << "current_event_out.total_should = " << current_event_out.total_should << "\n" ;
//    }
//    else
//    {
//        Let_pass_or_not = (current_account_state.outtime >= current_accountInfo.start_time && current_account_state.outtime <= current_accountInfo.end_time);
//        if(Let_pass_or_not)
//        {
//            current_event_out.out_type = current_accountInfo.parking_type;
//            current_account_state.present_type = 0;
//        }
//        else
//        {
//            current_event_out.out_type = out_prices;
//        }
//        std::cout << "current_event_out.out_type = " << dashou.ENTRY_EXIT_TYPE_To_string(current_event_out.out_type) << "\n" ;
//        current_event_charge.should_pay = 0;
//        current_event_charge.park_duration = std::difftime(time(0), current_account_state.intime);
//        current_event_out.park_duration = current_event_charge.park_duration;
//        std::cout << "current_event_out.park_duration = " << current_event_out.park_duration << "\n";
//        current_event_out.total_should = current_event_charge.should_pay;
//        std::cout << "current_event_out.total_should = " << current_event_out.total_should << "\n" ;
//    }
}

void make_accountInfo(accountInfo &current_accountInfo, DashouParser *parser)
{
    current_accountInfo.id = get_account_info_insert_aid();
    current_accountInfo.gid = Current_garage.gid;
    strcpy(current_accountInfo.tickets, parser->ticket.c_str());
    strcpy(current_accountInfo.plate, parser->plate.c_str());
    current_accountInfo.start_time = Reference_date;
    current_accountInfo.end_time = Reference_date;
    current_accountInfo.access_group = 0xff;
    current_accountInfo.inner_group = 0xff;
    current_accountInfo.time_group = 0xff;
    current_accountInfo.lots_group = 0xffff;
    current_accountInfo.hour_ticket_type = 0;
    current_accountInfo.lot_id = 0;
    current_accountInfo.prepaid_charge_rule = 0xff;
    current_accountInfo.monthly_charge_rule = 0xff;
    current_accountInfo.ticket_lpbind = 0;
    current_accountInfo.monthly_type = 0xff;
    current_accountInfo.limit_time = Reference_date;
    current_accountInfo._operator = 1;
    current_accountInfo.create_time = time(0);
}

void make_account_state(account_state &current_account_state, int site_id, DashouParser *parser)
{
    current_account_state.aid = get_account_state_insert_aid();
    current_account_state.gid = Current_garage.gid;
    strcpy(current_account_state.ticket, parser->ticket.c_str());
    strcpy(current_account_state.plate, parser->plate.c_str());
    current_account_state.create_time = time(0);
    current_account_state.insite = sites[site_id].id;
    Site_type entry_site(mysql);
    entry_site.Select_Site_type_by_id(current_account_state.insite);
    current_account_state.charge_type = entry_site.id_PresetType_id;
}

void temp_card_to_account(std::vector<temp_card> _temp_card_list)
{
    //print_temp_card_list(mysql, _temp_card_list);
    //for(int i = 0; i < _temp_card_list.size(); i++)
    //{
    //    _temp_card_list[i].Insert_Update_Temp_Account();
    //}
    _temp_card_list.clear();
    _temp_card_list = read_db_temp_card(mysql);
    //print_temp_card_list(mysql, _temp_card_list);
    for(int i = 0; i < _temp_card_list.size(); i++)
    {
        accountInfo current_accountInfo(mysql);
        account_state current_account_state(mysql);
        if(_temp_card_list[i].operate_type == 0)
        {
            if(_temp_card_list[i].ticket[0] == 0x00)
            {
                current_accountInfo.Select_account_by_plate(_temp_card_list[i].plate, Current_Settings.plate_match_level);
                current_account_state.Select_account_state_by_plate(_temp_card_list[i].plate, Current_Settings.plate_match_level);
            }
            else
            {
                current_accountInfo.Select_account_by_ticket(_temp_card_list[i].ticket);
                current_account_state.Select_account_state_by_ticket(_temp_card_list[i].ticket);
            }
            current_accountInfo.gid = Current_garage.gid;
            strcpy(current_accountInfo.tickets, _temp_card_list[i].ticket);
            current_accountInfo.ticket_type = _temp_card_list[i].ticket_type;
            strcpy(current_accountInfo.plate, _temp_card_list[i].plate);
            current_accountInfo.start_time = _temp_card_list[i].start_time;
            current_accountInfo.end_time = _temp_card_list[i].end_time;
            current_accountInfo.access_group = _temp_card_list[i].access_group;
            current_accountInfo.inner_group = _temp_card_list[i].inner_group;
            current_accountInfo.time_group = _temp_card_list[i].time_group;
            current_accountInfo.lots_group = _temp_card_list[i].lots_group;
            current_accountInfo.account_state = _temp_card_list[i].account_state;
            current_accountInfo.parking_type = _temp_card_list[i].parking_type;
            strcpy(current_accountInfo.addr, _temp_card_list[i].addr);
            strcpy(current_accountInfo.description, _temp_card_list[i].description);
            strcpy(current_accountInfo.email, _temp_card_list[i].email);
            strcpy(current_accountInfo.phone, _temp_card_list[i].phone);
            strcpy(current_accountInfo.owner_name, _temp_card_list[i].owner_name);
            strcpy(current_accountInfo.hour_ticket_num, _temp_card_list[i].hour_ticket_num);
            current_accountInfo.hour_ticket_type = _temp_card_list[i].hour_ticket_type;
            current_accountInfo.lot_id = 0;//_temp_card_list[i].???;
            strcpy(current_accountInfo.online_member, _temp_card_list[i].online_order);
            current_accountInfo.prepaid_charge_rule = _temp_card_list[i].prepaid_charge_rule;
            current_accountInfo.monthly_charge_rule = _temp_card_list[i].monthly_charge_rule;
            current_accountInfo.ticket_lpbind = _temp_card_list[i].ticket_lpbind;
            current_accountInfo.monthly_type = _temp_card_list[i].monthly_type;
            current_accountInfo.limit_time = _temp_card_list[i].limit_time;
            current_accountInfo._operator = 1;
            current_accountInfo.create_time = time(0);
            strcpy(current_accountInfo.photo_id, _temp_card_list[i].photo_id);
            strcpy(current_accountInfo.add_info1, _temp_card_list[i].add_info1);
            strcpy(current_accountInfo.add_info2, _temp_card_list[i].add_info2);
            //
            current_account_state.gid = Current_garage.gid;
            current_account_state.ticket_type = _temp_card_list[i].ticket_type;
            strcpy(current_account_state.ticket, _temp_card_list[i].ticket);
            strcpy(current_account_state.plate, _temp_card_list[i].plate);
            current_account_state.create_time = time(0);
            current_account_state.parking_type = _temp_card_list[i].parking_type;
            current_account_state.present_type = _temp_card_list[i].present_type;
            current_account_state.intime = _temp_card_list[i].in_time;
            current_account_state.inserial = 0;
            current_account_state.outtime = Reference_date;
            current_account_state.outserial = 0;
            current_account_state.pay_time = _temp_card_list[i].pay_time;
            current_account_state.pay_serial = 0;
            current_account_state.paid_sum = _temp_card_list[i].paid_sum;
            current_account_state.charge_type = _temp_card_list[i].charge_type;
            current_account_state.inner_intime = _temp_card_list[i].inner_intime;
            current_account_state.inner_inserial = 0;
            current_account_state.inner_outtime = _temp_card_list[i].inner_outtime;
            current_account_state.inner_outserial = 0;
            current_account_state.limit_sum = _temp_card_list[i].limit_sum;
            strcpy(current_account_state.online_order, _temp_card_list[i].online_order);
            current_account_state.insite = _temp_card_list[i].insite;
            current_account_state.charge_site = _temp_card_list[i].charge_site;
            current_account_state.inner_insite = _temp_card_list[i].inner_insite;
            current_account_state.inner_outsite = _temp_card_list[i].inner_outsite;
            current_account_state.prepaid_balance = _temp_card_list[i].prepaid_balance;
            current_account_state.l2_id = 0;
            current_account_state.prepaid_account_id = _temp_card_list[i].prepaid_account_id;
            strcpy(current_account_state.hour_ticket_num, _temp_card_list[i].hour_ticket_num);
            current_account_state.hour_ticket_type = _temp_card_list[i].hour_ticket_type;
            current_account_state.coupon_total_sum = _temp_card_list[i].coupon_total_sum;
            current_account_state.coupon_total_time = _temp_card_list[i].coupon_total_time;
            current_account_state.total_sum = 0;
            if(current_accountInfo.id > 0 && current_account_state.aid > 0)
            {
                std::cout << "car is exist\n";
                current_accountInfo.Insert_update_accountInfo();
                current_account_state.Insert_update_account_state();
                char buffer[BUFFER_SIZE];
                int byte_rec = 0;
                for(int i = 0; i < All_Cameras.size(); i++)
                {
                    std::string camera_address = std::string(Current_Settings.site_prefix) + "." +std::string(All_Cameras[i].ip);
                    std::string find_white_list = build_find_white_list_uri(current_accountInfo);
                    std::string find_car_white_list = HTTP_request_URL_HEADER + find_white_list + OPTION_HTTP_request_PREV_HOST + camera_address + OPTION_HTTP_request_APRE_HOST;
                    byte_rec = send_http_request(camera_address.c_str(), find_car_white_list + HTTP_request_TAIL, buffer);
                    response_header response = get_response_info(std::string(buffer));
                    std::string authorized_find_car_white_list = find_car_white_list + struct_response_to_string(response, "admin", "admin123", find_white_list) + HTTP_request_TAIL;
                    byte_rec = send_http_request(camera_address.c_str(), authorized_find_car_white_list, buffer);
                    int record_num = get_record_Number(get_response_CONTENT(std::string(buffer), byte_rec));
                    std::string update_white_list = build_update_white_list_uri(current_accountInfo, record_num);
                    std::string update_car_white_list = HTTP_request_URL_HEADER + update_white_list + OPTION_HTTP_request_PREV_HOST + camera_address + OPTION_HTTP_request_APRE_HOST;
                    byte_rec = send_http_request(camera_address.c_str(), update_car_white_list + HTTP_request_TAIL, buffer);
                    response = get_response_info(std::string(buffer));
                    std::string authorized_update_car_white_list = update_car_white_list + struct_response_to_string(response, "admin", "admin123", update_white_list) + HTTP_request_TAIL;
                    byte_rec = send_http_request(camera_address.c_str(), authorized_update_car_white_list, buffer);
                    std::cout << get_response_CONTENT(std::string(buffer), byte_rec) << "\n";
                }
            }
            else
            {
                std::cout << "car is not exist\n";
                current_accountInfo.id = get_account_info_insert_aid();
                current_account_state.aid = get_account_state_insert_aid();
                current_accountInfo.Insert_accountInfo();
                current_account_state.Insert_account_state();
                char buffer[BUFFER_SIZE];
                int byte_rec = 0;
                for(int i = 0; i < All_Cameras.size(); i++)
                {
                    std::string camera_address = std::string(Current_Settings.site_prefix) + "." +std::string(All_Cameras[i].ip);
                    std::string insert_white_list = build_insert_white_list_uri(current_accountInfo);
                    std::string insert_car_white_list = HTTP_request_URL_HEADER + insert_white_list + OPTION_HTTP_request_PREV_HOST + camera_address + OPTION_HTTP_request_APRE_HOST;
                    byte_rec = send_http_request(camera_address.c_str(), insert_car_white_list + HTTP_request_TAIL, buffer);
                    response_header response = get_response_info(std::string(buffer));
                    std::string authorized_insert_car_white_list = insert_car_white_list + struct_response_to_string(response, "admin", "admin123", insert_white_list) + HTTP_request_TAIL;
                    byte_rec = send_http_request(camera_address.c_str(), authorized_insert_car_white_list, buffer);
                    std::cout << get_response_CONTENT(std::string(buffer), byte_rec) << "\n";
                }
            }
        }
        else if(_temp_card_list[i].operate_type == 2)
        {
            if(_temp_card_list[i].ticket[0] == 0x00)
            {
                current_accountInfo.Select_account_by_plate(_temp_card_list[i].plate, Current_Settings.plate_match_level);
                current_account_state.Select_account_state_by_plate(_temp_card_list[i].plate, Current_Settings.plate_match_level);
            }
            else
            {
                current_accountInfo.Select_account_by_ticket(_temp_card_list[i].ticket);
                current_account_state.Select_account_state_by_ticket(_temp_card_list[i].ticket);
            }
            std::cout << "current_accountInfo.id = " << current_accountInfo.id << "\n";
            std::cout << "current_account_state.aid = " << current_account_state.aid << "\n";
            current_accountInfo.Delete_accountInfo();
            current_account_state.Delete_account_state();
            char buffer[BUFFER_SIZE];
            int byte_rec = 0;
            for(int i = 0; i < All_Cameras.size(); i++)
            {
                std::string camera_address = std::string(Current_Settings.site_prefix) + "." +std::string(All_Cameras[i].ip);
                std::string remove_white_list = build_remove_white_list_uri(17);
                std::string remove_car_white_list = HTTP_request_URL_HEADER + remove_white_list + OPTION_HTTP_request_PREV_HOST + camera_address + OPTION_HTTP_request_APRE_HOST;
                byte_rec = send_http_request(camera_address.c_str(), remove_car_white_list + HTTP_request_TAIL, buffer);
                response_header response = get_response_info(std::string(buffer));
                std::string authorized_remove_car_white_list = remove_car_white_list + struct_response_to_string(response, "admin", "admin123", remove_white_list) + HTTP_request_TAIL;
                byte_rec = send_http_request(camera_address.c_str(), authorized_remove_car_white_list, buffer);
                std::cout << get_response_CONTENT(std::string(buffer), byte_rec) << "\n";
            }
        }
    }
    _temp_card_list[0].Delete_All_Temp_Accounts();
}

bool check_blacklist_exist(std::string plate)
{
    int id = -1;
    int execute = 0;
    std::string query = "select COUNT(id) from v32_black_list where plate='" + plate + "'";
    try
    {
        execute = mysql_query(mysql, query.c_str());
    }
    catch(...)
    {
        finish_with_error(mysql, -5089);
    }
    if (execute != 0)
    {
        finish_with_error(mysql, -5089);
    }
    MYSQL_RES *result = NULL;
    try
    {
        result = mysql_store_result(mysql);
    }
    catch(...)
    {
        finish_with_error(mysql, -5090);
    }
    if (result == NULL)
    {
        finish_with_error(mysql, -5090);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    try
    {
        while ((row = mysql_fetch_row(result)))
        {
            id = row[0] ? std::stoi(row[0]) : 0;
        }
        mysql_free_result(result);
    }
    catch(...)
    {
        finish_with_error(mysql, -5091);
    }
    return true ? (id > 0) : false;
}

int get_zone_id_by_site(int site_id)
{
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            if(site_id == Zones[i].entry_address[j])
            {
                return i;
            }
        }
        for(int j = 0; j < 100; j++)
        {
            if(site_id == Zones[i].exit_address[j])
            {
                return i;
            }
        }
    }
    return -1;
}

std::vector <std::pair<std::string, std::vector<std::string>>> read_site(std::string filename)
{
	std::vector <std::pair<std::string, std::vector<std::string>>> result;
	std::ifstream myFile(filename, std::ios::in);
	if (!myFile.is_open())
	{
		std::cout << "Error open file";
	}
	std::string line, colname, val;
	if (myFile.good())
	{
		std::getline(myFile, line);
		std::stringstream ss(line);
		while (std::getline(ss, colname, ','))
		{
			result.push_back({ colname,std::vector<std::string> {} });
		}
	}
	while (std::getline(myFile, line))
	{
            std::stringstream ss(line);
            int colidx = 0;
            char *token = std::strtok((char *)line.c_str(), ","); 
            while (token != NULL) 
            { 
                result.at(colidx).second.push_back(token);
                token = strtok(NULL, ","); 
                colidx++;
            }
	}
	myFile.close();
	return result;
}

std::vector <std::pair<std::string, std::vector<std::string>>> read_csv(std::string filename)
{
	std::vector <std::pair<std::string, std::vector<std::string>>> result;
	std::ifstream myFile(filename, std::ios::in);
	if (!myFile.is_open())
	{
		std::cout << "Error open file";
	}
	std::string line, colname, val;
	if (myFile.good())
	{
		std::getline(myFile, line);
		std::stringstream ss(line);
		while (std::getline(ss, colname, ','))
		{
			result.push_back({ colname,std::vector<std::string> {} });
		}
	}
	while (std::getline(myFile, line))
	{
		std::stringstream ss(line);
		int colidx = 0;
		while (ss >> val)
		{
			result.at(colidx).second.push_back(val);
			if (ss.peek() == ',') ss.ignore();
			colidx++;
		}
	}
	myFile.close();
	return result;
}

int searchProof(Proof &proof, int REQUEST_TYPE)
{
    int match_plate = 0;
    int match_ticket = 0;
    for (int i = 0; i < all_proof.size(); i++)
    {
        for(int j = 0; all_proof[i].plate[j] != '\0'; j++)
        {
            if (all_proof[i].plate[j] == proof.plate[j])   
            {
                match_plate++; 
            }
        }
        for(int j = 0; all_proof[i].ticket[j] != '\0'; j++)
        {
            if (all_proof[i].ticket[j] == proof.ticket[j])   
            {
                match_ticket++; 
            }
        }
        if (match_ticket == 16 || match_plate == 7)
        {
            if (REQUEST_TYPE == tablet_scans_ticket || REQUEST_TYPE == central_pay_system_tablet_payment_confirm || tablet_input_license_plate_number)
            {
                return i; 
            }
            else if (REQUEST_TYPE == CONTROL_EXIT_REQUEST_RESPONSE)
            {
                return i;
            }
            else if (REQUEST_TYPE == CONTROL_ENTRY_REQUEST_RESPONSE)
            {
                if(all_proof[i].Status == "In")
                {
                    return -1;
                }
            }
        }
    }
	return -1;
}

int calculate_address_from_IP(char * IP)
{
    int address = 0;
    char *s = new char [50];
    strcpy(s, IP);
    char *token = std::strtok(s, "."); 
    token = strtok(NULL, "."); 
    token = strtok(NULL, "."); 
    token = strtok(NULL, "."); 
    std::istringstream(token) >> address;
    return address;
}

int find_site_by_address(int site_address)
{
    for (int i = 0; i < sites.size(); i++)
    {
        if (sites[i].address == site_address)
        {
            return i;
        }
    }
    return -1;
}

int find_car_by_plate(int function, std::string plate)
{
    int match = 0;
    if(function == CONTROL_ENTRY_REQUEST_RESPONSE)
    {
        for (int i = 0; i < cars_Registered.size(); i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if (cars_Registered[i][j] == plate[j])
                   match++; 
            }
            if (match == 7)
            {
                return i;
            }
        }
    }
    return -1;
}

std::string get_site_Type(int type)
{
	if (type == SITE_TYPE_ENTRY_BOARD)
		return "in board";
	else if (type == SITE_TYPE_EXIT_BOARD)
		return "out board";
	else if (type == SITE_TYPE_TABLET_APP)
		return "app board";
	else
		return "not defined";
}

std::string get_site_Address(int address)
{
	std::string s = "172.16.57." + std::to_string(address);
	return s;
}

std::string get_site_Status(int status)
{
    if (status == 1)
        return "online";
    else
        return "offline";
}

int get_int_from_string (std::string number)
{
    int integer = -1;
    std::istringstream(number) >> integer;
    return integer;
}

int get_address_from_name (std::string name)
{
    for(int i = 0; i< MAX_SITES; i++)
    {
        if(sites[i].db_name == name)
        {
            return sites[i].address;
        }
    }
    return -1;
}

void print_screen_report(Proof proof)
{
    std::string report = "";
    report += "Proof Serial is: " + std::to_string(proof.serial) + ".\n";
    report += "Proof Control is: " + dashou.functions_codes_To_string(proof.control) + ".\n";
    report += "Proof Entry Exit Type is: " + dashou.ENTRY_EXIT_TYPE_To_string(proof.proof_entry_exit_type) + ".\n";
    report += "Proof Ticket Type is: "+ dashou.ticket_types_To_string(proof.ticket_type) + ".\n";
    report += "the ticket is: " + proof.ticket + "\n";
    report += "the plate is: " + proof.plate + "\n";
    report += "Proof Account Type is: " + dashou.account_types_To_string(proof.account_type) + ".\n";
    report += "Proof Presence Sign is: " + dashou.account_types_To_string(proof.Presence_Sign) + ".\n";
    report += "Event serial number is: " + std::to_string(proof.event_serial_number) + ".\n";
    report += "Event Time is: " + dashou.Print_time(proof.event_time) + ".\n";
    report += "Entry serial number is: " + std::to_string(proof.Entry_serial) + ".\n";
    report += "Entry Time is: " + dashou.Print_time(proof.entryTime) + ".\n";
    report += "Exit serial number is: " + std::to_string(proof.Exit_serial) + ".\n";
    report += "Exit Time is: " + dashou.Print_time(proof.exitTime) + ".\n";
    report += "Pay serial number is: " + std::to_string(proof.APPpay_serial) + ".\n";
    report += "Pay Time is: " + dashou.Print_time(proof.payappTime) + ".\n";
    report += "Amount Received = " + std::to_string(proof.Amount_Received) + ".\n";
    report += "Charge Type (Charging Standard) is: " + std::to_string(proof.Charge_Type_Charging_Standard) + ".\n";
    report += "Start Time is: " + dashou.Print_time(proof.Start_Time) + ".\n";
    report += "End Time is: " + dashou.Print_time(proof.End_Time) + ".\n";
    report += "Prepay Account Balance is: " + dashou.to_String_X8(proof.Prepay_Account_Balance) + ".\n";
    report += "Access Control Group Number is: " + dashou.to_String_X2(proof.Access_Control_Group_Number) + ".\n";
    report += "Parking Space Group Number is: " + dashou.to_String_X4(proof.Parking_Space_Group_Number) + ".\n";
    report += "Time Group is: " + dashou.to_String_X2(proof.Time_Group) + ".\n";
    report += "Site in Site Area Group Number is: " + dashou.to_String_X2(proof.Site_in_Site_Area_Group_Number) + ".\n";
    report += "Current Parking Time (" + 
        dashou.to_String_00(proof.seconds_To_duration(proof.Current_Parking_Time).hour) + ":" + 
        dashou.to_String_00(proof.seconds_To_duration(proof.Current_Parking_Time).min) + ":" + 
        dashou.to_String_00(proof.seconds_To_duration(proof.Current_Parking_Time).sec) + ").\n";
    report += "Current Parking Fee = " + std::to_string(proof.Current_Parking_Fee) + ".\n"; 
    report += "Let Pass byte is: " + std::to_string(proof.Let_pass_or_not) + ".\n";
    report += "the zone is: Zone " + std::to_string(proof.zone_id) + ".\n";
    report += "==================================================================================================\n";
    std::cout << report;
}
#endif

#ifndef Webhost_Setting_response_functions

void setDateTime(int day, int month, int year,int hour, int min, int sec)
{
	//buffer to format command
	unsigned char buff[32]={0};
	//formatting command with the given parameters
	sprintf((char*)buff,(const char *)"date -s \"%02d/%02d/%04d %02d:%02d:%02d\"",month,day,year,hour,min,sec);
	//execute formatted command using system()
        int adjust = system((const char *)buff);
	if(adjust == -1)
        {
            std::cout << "Time Adjust failed.\n";
        }
}

std::string genSysParam_response_garage_info_to_webhost(garage_info Current_garage, int Setting_type)
{
	int inner_function = 132;    // 0x84
	int length = 190 + strlen(Current_garage.description) + strlen(Current_garage.notice) + strlen(Current_garage.share_brief) + strlen(Current_garage.share_brief);
	int serial = (++localSerialUpLink);
	int serial_setting = (++localSerialSetting);
	std::string s = "";
	time_t datetime = time(0);
	tm *now = localtime(&datetime);
	s += HEADER;
	s += dashou.calcLength(length);
	s += dashou.calcSerial(serial);
	s += Garage_ID;
	s += CITY_ID;
	s += dashou.to_String_X2(inner_function);
	s += dashou.calcCurrentTime(datetime);
	s += dashou.to_String_X4(serial_setting);
	s += dashou.to_String_X4(Setting_type);
        for(int i = 0; i < 64; i++)
        {
            s += dashou.to_String_X2(Current_garage.name[i]);
        }
        for(int i = 0; i < 104; i++)
        {
            s += dashou.to_String_X2(Current_garage.addr[i]);
        }
        for(int i = 0; Current_garage.description[i] != 0; i++)
        {
            s += dashou.to_String_X2(Current_garage.description[i]);
        }
        s += "2323";
        for(int i = 0; Current_garage.notice[i] != 0; i++)
        {
            s += dashou.to_String_X2(Current_garage.notice[i]);
        }
        s += "2323";
        for(int i = 0; Current_garage.reservation_brief[i] != 0; i++)
        {
            s += dashou.to_String_X2(Current_garage.reservation_brief[i]);
        }
        s += "2323";
        for(int i = 0; Current_garage.share_brief[i] != 0; i++)
        {
            s += dashou.to_String_X2(Current_garage.share_brief[i]);
        }
        s += "01";
	s += dashou.to_String_X2(server_site.address);
	s += "ffffff";
	s += dashou.to_String_X2(server_site.type);
	s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
	s += TAIL;
	return s;
}

std::string genSysParam_response_proofmodel_to_webhost(int site_to_change[], int Setting_type, int site_count)
{
    int inner_function = 132;    // 0x84
    int length = 17 + (3 * site_count);
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(site_count);
    for(int i = 0; i < site_count; i++)
    {
        s += dashou.to_String_X2(sites[site_to_change[i]].address);
        s += dashou.to_String_X2(sites[site_to_change[i]].credentialMode);
        s += dashou.to_String_X2(sites[site_to_change[i]].season_to_hourly_swich);
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_onecaroneproof_to_webhost(int site_to_change[], int Setting_type, int site_count)
{
    int inner_function = 132;    // 0x84
    int length = 17 + (2 * site_count);
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(site_count);
    for(int i = 0; i < site_count; i++)
    {
        s += dashou.to_String_X2(sites[site_to_change[i]].address);
        s += dashou.to_String_X2(sites[site_to_change[i]].oneCard_oneCar);
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_confirm_plate_to_webhost(int site_to_change[], int Setting_type, int site_count)
{
    int inner_function = 132;    // 0x84
    int length = 17 + (2 * site_count);
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(site_count);
    for(int i = 0; i < site_count; i++)
    {
        s += dashou.to_String_X2(sites[site_to_change[i]].address);
        s += dashou.to_String_X2(sites[site_to_change[i]].entryPresetLicensePlateNumber);
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_id_PresetType_to_webhost(int site_to_change[], int Setting_type, int site_count)
{
    int inner_function = 132;    // 0x84
    int length = 17 + (2 * site_count);
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(site_count);
    for(int i = 0; i < site_count; i++)
    {
        s += dashou.to_String_X2(sites[site_to_change[i]].address);
        s += dashou.to_String_X2(sites[site_to_change[i]].id_PresetType_id);
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_black_list_to_webhost(int Setting_type, int count, bool add_to_black_list, black_list_type tmp_black_account)
{
    int inner_function = 132;    // 0x84
    int length = 84;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(count);
    s += dashou.to_String_X4(tmp_black_account.id);
    s += dashou.to_String_X2(tmp_black_account.ticket_type);
    for(int i = 0; i < 19; i++)
    {
        s += dashou.to_String_X2(tmp_black_account.ticket[i]);
    }
    for(int i = 0; i < 12; i++)
    {
        s += dashou.to_String_X2(tmp_black_account.plate[i]);
    }
    for(int i = 0; i < 32; i++)
    {
        s += dashou.to_String_X2(tmp_black_account.description[i]);
    }
    s += dashou.to_String_X2(add_to_black_list);
    s += dashou.to_String_X2(tmp_black_account._operator);
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_exitFreeLetPass_to_webhost(int site_to_change[], int Setting_type, int site_count)
{
    int inner_function = 132;    // 0x84
    int length = 17 + (2 * site_count);
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(site_count);
    for(int i = 0; i < site_count; i++)
    {
        s += dashou.to_String_X2(sites[site_to_change[i]].address);
        s += dashou.to_String_X2(sites[site_to_change[i]].exitFreeLetPass);
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_plate_match_level_to_webhost(int Setting_type, int plate_match_level)
{
    int inner_function = 132;    // 0x84
    int length = 17;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(8 - plate_match_level);
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
    
}

std::string genSysParam_response_mobile_charge_standard_to_webhost(int Setting_type, int mobile_charge_standard)
{
    int inner_function = 132;    // 0x84
    int length = 17;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(mobile_charge_standard);
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_user_auth_to_webhost(int Setting_type, sys_user Current_sys_user)
{
    int inner_function = 132;    // 0x84
    int length = 196 + strlen(Current_sys_user.full_name);
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    for(int i = 0; i < strlen(Current_sys_user.full_name); i++)
    {
        s += dashou.to_String_X2(Current_sys_user.full_name[i]);
    }
    s += "2323";
    for(int i = 0; i < strlen(Current_sys_user.username); i++)
    {
        s += dashou.to_String_X2(Current_sys_user.username[i]);
    }
    s += "2323";
    for(int i = 0; i < strlen(Current_sys_user.password_hash); i++)
    {
        s += dashou.to_String_X2(Current_sys_user.password_hash[i]);
    }
    s += "2323";
    s += dashou.calcCurrentTime(Current_sys_user.dob_time);
    for(int i = 0; i < strlen(Current_sys_user.mobile); i++)
    {
        s += dashou.to_String_X2(Current_sys_user.mobile[i]);
    }
    s += "2323";
    for(int i = 0; i < strlen(Current_sys_user.phone); i++)
    {
        s += dashou.to_String_X2(Current_sys_user.phone[i]);
    }
    s += "2323";
    for(int i = 0; i < strlen(Current_sys_user.email); i++)
    {
        s += dashou.to_String_X2(Current_sys_user.email[i]);
    }
    s += "2323";
    for(int i = 0; i < strlen(Current_sys_user.login_from_ip); i++)
    {
        s += dashou.to_String_X2(Current_sys_user.login_from_ip[i]);
    }
    s += "2323";
    s += dashou.calcCurrentTime(Current_sys_user.last_login_time);
    s += dashou.to_String_X2(Current_sys_user.is_blocked);
    s += dashou.calcCurrentTime(Current_sys_user.block_time);
    s += dashou.to_String_X2(Current_sys_user.is_locked);
    s += dashou.calcCurrentTime(Current_sys_user.lock_time);
    s += dashou.to_String_X8(Current_sys_user.password_try_counter);
    s += dashou.to_String_X2(Current_sys_user.first_login_success);
    for(int i = 1; i < 44; i++)
    {
        s += dashou.to_String_X2(Current_sys_user.authorities[i]);
        s += dashou.to_String_X2(Current_sys_user.authorities[i + 1]);
        i += 3;
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_Full_no_entry_to_webhost(int site_to_change[], int Setting_type, int site_count)
{
    int inner_function = 132;    // 0x84
    int length = 17 + (3 * site_count);
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(site_count);
    for(int i = 0; i < site_count; i++)
    {
        s += dashou.to_String_X2(sites[site_to_change[i]].address);
        s += dashou.to_String_X2(sites[site_to_change[i]].monthlyParkingFullAccessDeny);
        s += dashou.to_String_X2(sites[site_to_change[i]].hourlyParkingFullAccessDeny);
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_balanceNotificationThreshold_to_webhost(int Setting_type, int balanceNotificationThreshold)
{
    int inner_function = 132;    // 0x84
    int length = 20;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X8(balanceNotificationThreshold);
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_expireForecastThreshold_to_webhost(int Setting_type, int expireForecastThreshold)
{
    int inner_function = 132;    // 0x84
    int length = 20;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X8(expireForecastThreshold);
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_monthly_to_hourly_to_webhost(int Setting_type, int count, monthly_to_hourly_type tmp_montohour)
{
    int inner_function = 132;    // 0x84
    int length = 19;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(count);
    s += dashou.to_String_X2(tmp_montohour.id);
    int hour_charge_type = -1;
    sscanf(tmp_montohour.hour_charge_type, "%d", &hour_charge_type);
    s += dashou.to_String_X2(hour_charge_type);
    s += dashou.to_String_X2(tmp_montohour._operator);
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genSysParam_response_CameraSite_to_webhost(int Setting_type, int cam_count, int camera_to_change[], int camera_bind[])
{
    int inner_function = 132;    // 0x84
    int length = 17 + cam_count * 75;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    tm *now = localtime(&datetime);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(cam_count);
    Camera_type Camera_new_config(mysql);
    for(int i = 0; i < cam_count; i++)
    {
        Camera_new_config.Select_Camera_type_by_address(camera_to_change[i]);
        int j = 0;
        for(j = 0; Camera_new_config.sites_binded[j] != 0; j++)
        {
            s += dashou.to_String_X2(std::stoi(Camera_new_config.ip));
            for(int k = 0; k < 32; k++)
            {
                s += dashou.to_String_X2(Camera_new_config.Camera_name[k]);
            }
            for(int k = 0; k < 20; k++)
            {
                s += dashou.to_String_X2(Camera_new_config.user_name[k]); 
            }
            for(int k = 0; k < 20; k++)
            {
                s += dashou.to_String_X2(Camera_new_config.password[k]); 
            }
            s += dashou.to_String_X2(Camera_new_config.sites_binded[j]);
            s += dashou.to_String_X2(camera_bind[i]); 
        }
        if(camera_bind[i] == 0)
        {
            Camera_new_config.Delete_Camera_type();
        }
        i += j - 1;
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_server(length, serial, CONTROL_Sys_PARAM_FRAME, now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour);
    s += TAIL;
    return s;
}

std::string genspace_Counting_response_to_webhost(time_t time, int setting_Type, int zone_serial)
{
    int inner_function = 138;    // 0x8a
    int length = 330;
    int serial = ++localSerialUpLink;
    int enabled_zone = 0;
    std::string s = "";
    time_t now = time;
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(time);
    s += dashou.to_String_X4(setting_Type);
    for(int i = 0; i < 16; i++)
    {
        if(Zones[i].flag)
        {
            enabled_zone++;
        }
    }
    s += dashou.to_String_X2(enabled_zone);
    Zone zone(mysql);
    for(int i = 0; i < Zones_Number; i++)
    {
        zone.select_Zone(i);
        if(zone.flag)
        {
            s += dashou.to_String_X4(i);
            s += zone.get_TotalSpaces() + zone.get_TotalSpacesSeason() + zone.get_TotalSpacesHourly() + zone.get_VacantSpaces() + zone.get_VacantSpacesSeason() + zone.get_VacantSpacesHourly();
            s += "ffff";
            s += "0000";                                       
            s += "0000";   
        }
    }
    for(int i = 0; i < Zones_Number; i++)
    {
        zone.select_Zone(i);
        if(!zone.flag)
        {
            s += dashou.to_String_X4(i);
            s += zone.get_TotalSpaces() + zone.get_TotalSpacesSeason() + zone.get_TotalSpacesHourly() + zone.get_VacantSpaces() + zone.get_VacantSpacesSeason() + zone.get_VacantSpacesHourly();
            s += "ffff";
            s += "0000";                                       
            s += "0000";   
        }
    }
    s += dashou.to_String_X2(CONTROL_TYPE_SITE_SETTING);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function); 
    s += TAIL;

    return s;
}

std::string genspace_Counting_confirm_to_webhost(time_t time, int setting_Type, int zone_serial)
{
    int inner_function = 138;    // 0x8a
    int length = 11;
    int serial = ++localSerialUpLink;
    std::string s = "";
    time_t now = time;
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(time);
    s += dashou.to_String_X4(setting_Type);
    s += "0000";
    s += dashou.to_String_X2(CONTROL_TYPE_SITE_SETTING);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string Enable_diasble_zone_confirm_to_webhost(int Setting_type, int zone_count, int zone_serial[])
{
    int inner_function = 132;    // 0x84
    int length = 69;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(time(0));
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(zone_count);
    for(int i = 0; i < zone_count; i++)
    {
        Zone zone(mysql);
        zone.select_Zone(zone_serial[i]);
        s += dashou.to_String_X2(zone.serial);
        std::string zone_name = dashou.get_STRINGASCIIHEX(zone.name);
        for(int j = 0; j < zone_name.length() / 2; j++)
        {
            s += dashou.to_String_X2(zone.name[j]);
        }
        for(int j = 0; j < (32 - (zone_name.length() / 2)); j++)
        {
            s += "00";
        }
        s += dashou.to_String_X2(Zone_as_official);
        s += dashou.to_String_X4(zone.totalSpaces);                         
        s += dashou.to_String_X4(zone.totalSpacesSeason);
        s += dashou.to_String_X4(zone.totalSpacesHourly);
        s += dashou.to_String_X4(zone.vacantSpaces);
        s += dashou.to_String_X4(zone.vacantSpacesSeason);
        s += dashou.to_String_X4(zone.vacantSpacesHourly);
        s += dashou.to_String_X4(zone.parking_Guidance_Available_Space);
        s += dashou.to_String_X4(zone.parking_Guidance_Total_Space);
        s += "0000";
    }
    Zone zone(mysql);
    zone.select_Zone(zone_serial[0]);
    s += dashou.to_String_X2(zone._operator);
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string Entry_Exit_zone_confirm_to_webhost(time_t time, int setting_Type, int entry_site_count, int exit_site_count, Zone zone)
{
    int inner_function = 132;    // 0x84
    int length = 18 + (2 * (entry_site_count + exit_site_count + 2));
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    std::string info = "";
    info += dashou.to_String_X2(entry_site_count + exit_site_count + 2);
    for(int i = 0; i <= entry_site_count; i++)
    {
        info += dashou.to_String_X2(zone.entry_address[i]);
        info += "00";
    }
    for(int i = 0; i <= exit_site_count; i++)
    {
        info += dashou.to_String_X2(zone.exit_address[i]);
        info += "01";
    }
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(time);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(setting_Type);
    s += dashou.to_String_X2(zone.serial);            
    s += info;
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string genSysParam_response_SiteName_to_webhost(int site_to_change[], int Setting_type, int site_count)
{
    int inner_function = 132;    // 0x84
    int length = 17 + 33 * site_count;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(site_count);
    Site_type current_site(mysql);
    for(int i = 0; i < site_count; i++)
    {
        current_site.Select_Site_type_by_id(site_to_change[i]);
        s += dashou.to_String_X2(current_site.id);
        for(int j = 0; j < 32; j++)
        {
            s += dashou.to_String_X2(current_site.db_name[j]);
        }
        if(strlen(current_site.db_name) == 0)
        {
            current_site.Delete_Site_type();
        }
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string genSysParam_response_Hourly_Charging_STD_to_webhost(int Setting_type, int rule_serial, bool non_step_rules)
{
    int inner_function = 132;    // 0x84
    int length = 354;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(rule_serial);
    if(non_step_rules)
    {
        for(int j = 0; j < 50; j++)
        {
            if(j == 0 || j == 1)
            {
                s += "ff";
            }
            else
            {
                s += "00";
            }
        }
    }
    else
    {
        for(int j = 0; j < 50; j++)
        {
            s += dashou.to_String_X2(rule_name_hourly_list[rule_serial].name[j]);
        }
    }  
    s += "0000000000000000000000000000";
    s += dashou.to_String_X2(rule_name_hourly_list[rule_serial].limit_enable);
    s += dashou.to_String_X8(rule_name_hourly_list[rule_serial].limit_sum);
    s += "ffffff";
    char fixed_time[20] = "";
    strcpy(fixed_time, rule_name_hourly_list[rule_serial].fixed_time);
    fixed_time[13] = '\0';
    fixed_time[16] = '\0';
    for(int j = 0; j < 9; j+=3)
    {
        s += dashou.to_String_X2(atoi(&fixed_time[11 + j]));
    }
    s += dashou.to_String_X8(rule_name_hourly_list[rule_serial].within_duration);
    s += dashou.to_String_X4(rule_name_hourly_list[rule_serial].tolerance);
    for(int j = 0; j < 256; j++)
    {
        s += dashou.to_String_X2(rule_name_hourly_list[rule_serial].remark[j]);
    }
    s += dashou.to_String_X2(rule_name_hourly_list[rule_serial]._operator);
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string genSysParam_response_Hourly_Charging_STD_step_to_webhost(int Setting_type, int rule_serial, int block_serial)
{
    int inner_function = 132;    // 0x84
    int length = 116;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    rule_step_hourly_type rule_step_hourly(mysql);
    rule_step_hourly.Select_rule_step_hourly_type_by_rule_block_serial(rule_serial, block_serial);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(rule_step_hourly.rule_serial);
    s += dashou.to_String_X2(rule_step_hourly.block_serial);
    s += dashou.to_String_X2(rule_step_hourly.type);
    std::string start = dashou.calcCurrentTime(rule_step_hourly.starttime);
    if(start[0] == '0' && start[1] == '0')
    {
        start[0] = 'f';
        start[1] = 'f';
        if(start[2] == '0' && start[3] == '1' && start[4] == '0' && start[5] == '1')
        {
            for(int i = 2; i < 6; i++) 
                start[i] = 'f';
        }
    }
    s += start;
    std::string end = dashou.calcCurrentTime(rule_step_hourly.endtime);
    if(end[0] == '0' && end[1] == '0')
    {
        end[0] = 'f';
        end[1] = 'f';
        if(end[2] == '0' && end[3] == '1' && end[4] == '0' && end[5] == '1')
        {
            for(int i = 2; i < 6; i++) 
            end[i] = 'f';
        }
    }
    s += end;
    s += dashou.to_String_X8(rule_step_hourly.duration);
    s += dashou.to_String_X4(rule_step_hourly.relation);
    s += dashou.to_String_X2(rule_step_hourly.cross_period);
    s += dashou.to_String_X2(rule_step_hourly.deduct);
    s += dashou.to_String_X8(rule_step_hourly.sum);
    s += dashou.to_String_X8(rule_step_hourly.max_sum);
    s += dashou.to_String_X2(rule_step_hourly.next_serial);
    s += dashou.to_String_X2(rule_step_hourly.start_week);
    s += dashou.to_String_X2(rule_step_hourly.end_week);
    s += dashou.to_String_X2(rule_step_hourly.reserve[0]);
    s += dashou.to_String_X2(rule_step_hourly.reserve[1]);
    for(int i = 0; i < 64; i++)
    {
        s += dashou.to_String_X2(rule_step_hourly.brief[i]);
    }
    s += dashou.to_String_X2(rule_step_hourly._operator);
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string genSysParam_response_download_account_to_webhost(int Setting_type, temp_card current_temp_card)
{
    int inner_function = 132;    // 0x84
    int length = 514;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(current_temp_card.operate_type);
    s += dashou.to_String_X2(current_temp_card.ticket_type);
    for(int i = 0; i < 19; i++)
    {
        s += dashou.to_String_X2(current_temp_card.ticket[i]);
    }
    for(int i = 0; i < 12; i++)
    {
        s += dashou.to_String_X2(current_temp_card.plate[i]);
    }
    s += dashou.to_String_X2(current_temp_card.account_state);
    s += dashou.to_String_X2(current_temp_card.parking_type);
    s += dashou.to_String_X2(current_temp_card.present_type);
    s += dashou.calcCurrentTime(current_temp_card.in_time);
    s += dashou.calcCurrentTime(current_temp_card.pay_time);
    s += dashou.calcCurrentTime(current_temp_card.inner_intime);
    s += dashou.calcCurrentTime(current_temp_card.inner_outtime);
    s += dashou.to_String_X2(current_temp_card.insite);
    s += dashou.to_String_X2(current_temp_card.charge_site);
    s += dashou.to_String_X2(current_temp_card.inner_insite);
    s += dashou.to_String_X2(current_temp_card.inner_outsite);
    s += dashou.to_String_X8(current_temp_card.coupon_total_time);
    s += dashou.to_String_X8(current_temp_card.coupon_total_sum);
    s += dashou.to_String_X8(current_temp_card.limit_sum);
    s += dashou.calcCurrentTime(current_temp_card.limit_time);
    s += dashou.to_String_X8(current_temp_card.paid_sum);
    for(int i = 0; i < 12; i++)
    {
        s += dashou.to_String_X2(current_temp_card.online_order[i]);
    }
    s += dashou.to_String_X2(current_temp_card.hour_ticket_type); 
    for(int i = 0; i < 19; i++)
    {
        s += dashou.to_String_X2(current_temp_card.hour_ticket_num[i]);
    }
    s += dashou.to_String_X4(current_temp_card.access_group);
    s += dashou.calcCurrentTime(current_temp_card.start_time);
    s += dashou.calcCurrentTime(current_temp_card.end_time);
    s += dashou.to_String_X8(current_temp_card.prepaid_balance);
    s += dashou.to_String_X4(current_temp_card.prepaid_account_id);
    s += dashou.to_String_X2(current_temp_card.monthly_type);     
    s += dashou.to_String_X4(current_temp_card.lots_group);
    s += dashou.to_String_X2(current_temp_card.ticket_lpbind);
    s += dashou.to_String_X2(current_temp_card.inner_group);
    s += dashou.to_String_X2(current_temp_card.time_group);
    for(int i = 0; i < 16; i++)
    {
        s += dashou.to_String_X2(current_temp_card.lot_name[i]);
    }
    s += dashou.to_String_X2(current_temp_card.prepaid_charge_rule);
    s += dashou.to_String_X2(current_temp_card.monthly_charge_rule);
    for(int i = 0; i < 16; i++)
    {
        s += dashou.to_String_X2(current_temp_card.photo_id[i]);
    }
    for(int i = 0; i < 16; i++)
    {
        s += dashou.to_String_X2(current_temp_card.owner_name[i]);
    }
    for(int i = 0; i < 16; i++)
    {
        s += dashou.to_String_X2(current_temp_card.phone[i]);
    }
    for(int i = 0; i < 32; i++)
    {
        s += dashou.to_String_X2(current_temp_card.email[i]);
    }
    for(int i = 0; i < 64; i++)
    {
        s += dashou.to_String_X2(current_temp_card.addr[i]);
    }
    for(int i = 0; i < 64; i++)
    {
        s += dashou.to_String_X2(current_temp_card.description[i]);
    }
    for(int i = 0; i < 64; i++)
    {
        s += dashou.to_String_X2(current_temp_card.add_info1[i]);
    }
    for(int i = 0; i < 64; i++)
    {
        s += dashou.to_String_X2(current_temp_card.add_info2[i]);
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string genSysParam_response_retainingdays_webhost(int Setting_type)
{
    int inner_function = 132;    // 0x84
    int length = 23;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X4(Current_Settings.events_retainingdays);
    s += dashou.to_String_X4(Current_Settings.photos_retainingdays);
    s += dashou.to_String_X4(30);//  several IN/OUT Max. charge A/C
    s += dashou.to_String_X2(Current_Settings.clear_time);
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string genSysParam_response_group_inner_to_webhost(int Setting_type, int count, int sites_count[], int inner_group_serial[])
{
    int inner_function = 132;    // 0x84
    int length = 17;
    for(int i = 0; i < count; i++)
    {
        length += 36 + sites_count[i];
    }
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(count);
    for(int j = 0; j < count; j++)
    {
        group_inner current_group_inner(mysql);
        current_group_inner.Select_group_inner_by_ID(inner_group_serial[j]);
        s += dashou.to_String_X2(current_group_inner.id);
        if(current_group_inner.flag == 1)
        {
            for(int i = 0; i < 32; i++)
            {
                s += dashou.to_String_X2(current_group_inner.name[i]);
            }
        }
        else
        {
            s += "ff";
            for(int i = 0; i < 31; i++)
            {
                s += dashou.to_String_X2(0);
            }
        }
        s += dashou.to_String_X2(current_group_inner.inner_charge);
        s += dashou.to_String_X2(current_group_inner.outer_charge);
        s += dashou.to_String_X2(sites_count[j]);
        for(int i = 0; i < sites_count[j]; i++)
        {
            s += dashou.to_String_X2(current_group_inner._sites_list[i]);
        }
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string genSysParam_response_id_PresetSite_in_Site_Group_to_webhost(int site_to_change[], int Setting_type, int site_count)
{
    int inner_function = 132;    // 0x84
    int length = 17 + (2 * site_count);
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(site_count);
    for(int i = 0; i < site_count; i++)
    {
        s += dashou.to_String_X2(sites[site_to_change[i]].address);
        s += dashou.to_String_X2(sites[site_to_change[i]].id_PresetSite_in_Site_Group);
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string genSysParam_response_rule_name_monthly_to_webhost(int Setting_type, rule_name_monthly current_rule_name_monthly)
{
    int inner_function = 132;    // 0x84
    int length = 337;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(current_rule_name_monthly.rule_serial);
    for(int i = 0; i < 64; i++)
    {
        s += dashou.to_String_X2(current_rule_name_monthly.name[i]);
    }
    for(int i = 0; i < 256; i++)
    {
        s += dashou.to_String_X2(current_rule_name_monthly.remark[i]);
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string genSysParam_response_rule_step_monthly_to_webhost(int Setting_type, rule_step_monthly current_rule_step_monthly)
{
    int inner_function = 132;    // 0x84
    int length = 29;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(current_rule_step_monthly.rule_serial);
    s += dashou.to_String_X2(current_rule_step_monthly.step_serial);
    s += dashou.to_String_X2(current_rule_step_monthly.flag);
    s += dashou.to_String_X4(current_rule_step_monthly.max_units);
    s += dashou.to_String_X8(current_rule_step_monthly.duration);
    s += dashou.to_String_X8(current_rule_step_monthly.unit_sum);
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}

std::string genSysParam_response_monthly_type_to_webhost(int Setting_type, monthly_type current_monthly_type)
{
    int inner_function = 132;    // 0x84
    int length = 346;
    int serial = (++localSerialUpLink);
    int serial_setting = (++localSerialSetting);
    std::string s = "";
    time_t datetime = time(0);
    s += HEADER;
    s += dashou.calcLength(length);
    s += dashou.calcSerial(serial);
    s += Garage_ID;
    s += CITY_ID;
    s += dashou.to_String_X2(inner_function);
    s += dashou.calcCurrentTime(datetime);
    s += dashou.to_String_X4(serial_setting);
    s += dashou.to_String_X4(Setting_type);
    s += dashou.to_String_X2(current_monthly_type.id);
    s += dashou.to_String_X2(((current_monthly_type.flag) ? current_monthly_type.type : 0xff));
    s += dashou.to_String_X2(current_monthly_type.access_group_id);
    s += dashou.to_String_X2(current_monthly_type.time_group_id);
    s += dashou.to_String_X2(current_monthly_type.inner_group_id);
    s += dashou.to_String_X2(current_monthly_type.monthly_charge_rule);
    s += dashou.to_String_X2(current_monthly_type.prepaid_charge_rule);
    s += dashou.to_String_X2(current_monthly_type.vip_flag);
    s += dashou.to_String_X2(current_monthly_type.lotgroup_countingtype);
    s += dashou.to_String_X2(current_monthly_type.expires);
    for(int i = 0; i < 64; i++)
    {
        s += dashou.to_String_X2(current_monthly_type.name[i]);
    }
    for(int i = 0; i < 256; i++)
    {
        s += dashou.to_String_X2(current_monthly_type.description[i]);
    }
    s += "01";
    s += dashou.to_String_X2(server_site.address);
    s += "ffffff";
    s += dashou.to_String_X2(server_site.type);
    s += dashou.calcChecksum_client(length, serial, CONTROL_TYPE_SITE_SETTING, inner_function);
    s += TAIL;
    return s;
}
#endif

int main()
{
    SSL_library_init();
    ctx = InitCTX();
    try
    {
        mysql = mysql_init(NULL);
    }
    catch(...)
    {
        fprintf(stderr, "mysql init : %s\n", mysql_error(mysql));
        finish_with_error(mysql, -5001);
        return 0;
    }
    if(mysql == NULL)
    {
        fprintf(stderr, "mysql init : %s\n", mysql_error(mysql));
        finish_with_error(mysql, -5001);
        return 0;
    }
    try
    {
        my_bool reconnect= 1;
        unsigned int timeout= 10;
        std::cout << "MYSQL_OPT_RECONNECT set option = " << mysql_options(mysql, MYSQL_OPT_RECONNECT, (void *)&reconnect) << "\n";
        std::cout << "MYSQL_OPT_CONNECT_TIMEOUT set option = " << mysql_options(mysql, MYSQL_OPT_CONNECT_TIMEOUT, (void *)&timeout) << "\n";
        std::cout << "MYSQL_OPT_READ_TIMEOUT set option = " << mysql_options(mysql, MYSQL_OPT_READ_TIMEOUT, (void *)&timeout) << "\n";
        std::cout << "MYSQL_OPT_WRITE_TIMEOUT set option = " << mysql_options(mysql, MYSQL_OPT_WRITE_TIMEOUT, (void *)&timeout) << "\n";
        real_connect = mysql_real_connect(mysql, "localhost", DATABASE_USERNAME, DATABASE_PASSWORD, DATABASE_NAME, 0, NULL, 0);
    }
    catch(...)
    {
        fprintf(stderr, "mysql real connect : %s\n", mysql_error(mysql));
        finish_with_error(mysql, -5002);
        return 0;
    }
    if(real_connect == NULL)
    {
        fprintf(stderr, "mysql real connect : %s\n", mysql_error(mysql));
        finish_with_error(mysql, -5002);
        return 0;
    }
    else
    {
        fprintf(stderr, "Database connection successful\n");
    }
    
    Current_garage.mysql = mysql;
    Current_Settings.mysql = mysql;
    int execute = Current_Settings.select_Setting(813);
    if(execute == 0)
    {
        fprintf(stderr, "Settings read is Ok..!\n");
        execute = Current_Settings.print_Setting();
        if(execute == 0)
        {
            fprintf(stderr, "Settings print is Ok..!\n");
        }
        else
        {
            finish_with_error(mysql, execute);
            fprintf(stderr, "Settings print faild..!\n");
        }
    }
    else
    {
        finish_with_error(mysql, execute);
        fprintf(stderr, "Error Settings Read..!");
    }
    execute = Current_garage.select_garage_info(239);   
    if(execute == 0)
    {
        fprintf(stderr, "Info read is Ok..!\n");
        execute = Current_garage.print_garage_info();
        if(execute == 0)
        {
            fprintf(stderr, "Info print is Ok..!\n");
        }
        else
        {
            finish_with_error(mysql, execute);
            fprintf(stderr, "Info print failed..!\n");
        }
    }
    else
    {
        finish_with_error(mysql, execute);
        fprintf(stderr, "Error Read info..!\n");
    }
    
    execute = pthread_create(&config_thread, NULL, process_config, NULL);
    if(execute == 0)
    {
        fprintf(stderr, "configuration thread created..!\n");
    }
    else
    {
        finish_with_error(mysql, -5003);
        fprintf(stderr, "Error configuration thread..!\n");
    }
    

    sleep(1);
    
    if (!initialize(My_local_IP))
    {
        fprintf(stderr, "Error initialize..!\n");
        finish_with_error(mysql, -5004);
        return 0;
    }
    
    sleep(1);

    pthread_create(&main_Camera_Thread, NULL , main_Camera_Process, NULL);
    
    
//    log_udp.initilize_UDP_Logger(mysql, (const char*)My_local_IP);
//    log_udp.create_UDP_Logger_Server();
    
    char WebHost_IP_PORT[25] = "";
    strcpy(WebHost_IP_PORT, Current_Settings.online_minor_ip);
    WebHost_IP = strtok (WebHost_IP_PORT,":");
    WebHost_PORT = strtok (NULL, ":");
    
    create_Client(WebHost_IP, WebHost_PORT, My_Online_IP);
    
    sleep(1);
    
    if(!create_Server(My_local_IP, OPTION_VALUE))
    {
        fprintf(stderr, "Can't Create Server!..\n");
        finish_with_error(mysql, -5005);
        return 0;
    }

    create_UDP_Server(My_local_IP, default_port);
    
    while (true)
    {
        if(webHost_Client_socket == INVALID_SOCKET && webhost_reconnect_try)
        {
            std::cout << "try to connect server.." << std::endl;
            char WebHost_IP_PORT[25] = "";
            strcpy(WebHost_IP_PORT, Current_Settings.online_minor_ip);
            WebHost_IP = strtok (WebHost_IP_PORT,":");
            WebHost_PORT = strtok (NULL, ":");
            create_Client(WebHost_IP, WebHost_PORT, My_Online_IP);
            sleep(1);
            
        }
        if(conf_has_changed && !webhost_reconnect_try)
        {
            webhost_reconnect_try = true;
            conf_has_changed = false;
            site_ACK_setting = false;
            site_ACK_setting_serial = -1;
            site_ACK_setting_type = -1;

            OPTION_VALUE = 1;
            msg = "";            
            heartbeatIndex = 0;

            web_host_locked = false;
            web_host_client_send_confirm_data = false;
            
            close(webHost_Client_socket);
            webHost_Client_socket = INVALID_SOCKET;
            
            close(log_udp.UDP_Logger_socket);
            close(UDP_server_socket);
            close(server_socket);
            
            unsigned char buff[1024]={0};
            sprintf((char*)buff,(const char *)"ifconfig interface down");
            int ifconfig = system((const char *)buff);
            if(ifconfig == -1)
            {
                std::cout << "ifconfig interface down failed.\n";
            }
            sleep(3);
            buff[32]={0};
            sprintf((char*)buff,(const char *)"eth0 172.16.57.20 netmask 255.255.255.0 up");
            ifconfig = system((const char *)buff);
            if(ifconfig == -1)
            {
                std::cout << "ifconfig interface up failed.\n";
            }
            sleep(4);
            
            log_udp.initilize_UDP_Logger(mysql, (const char*)My_local_IP);
            log_udp.create_UDP_Logger_Server();
            
            if (!create_Server(My_local_IP, OPTION_VALUE))
            {
                std::cout << "Can't Create Server!.." << std::endl;
                return 0;
            }
            create_UDP_Server(My_local_IP, default_port);
        }
        sleep(3);
    }

    return 0;
}