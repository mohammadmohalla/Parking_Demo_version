#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>


class Setting
{
public:
    
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[30];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[30];
    my_bool       is_null[30];
    
    int aid = 0;
    int gid = 0;
    short plate_match_level = 7;                                //License plate fuzzy matching level
    int alarm_balance = 100;                                    //Balance notification threshold
    int alarm_enddata = 30;                                     //Expiration forecast threshold
    int align_lots_time = 3;                                    //Automatically calibrate parking time
    int events_retainingdays = 60;                              //Case preservation numerology
    int photos_retainingdays = 30;                              //Image storage days
    int clear_time = 3;                                         //What time do you clean up stale data every day
    int auto_prepaidlimit = 5000;                               //Maximum amount of stored value automatic deduction
    char invite_code[10] = "12345678";                          //12345678
    char site_prefix[20] = "172.16.57";                         //Prefix of site IP
    char online_marjor_ip[255] = "61.131.122.254:28890";         //Online main IP
    char online_minor_ip[255] = "172.16.57.201.18890";           //Online vice IP
    char qrcode_url[255] = "www.urbanparking.cn";               //Scan code IP(URL)
    char etrecord_ip[25] = "120.42.51.148 :18892";              //Electronic transaction upload IP
    char uploadip[255] = "61.131.122.254:20000";                //Upload image to the cloud IP
    char uploadurl[255] = "/w1/pri/pic/event";                  //Upload the image to the cloud URL
    int photo_upload_mode = 2;                                  //Picture upload mode 0 no upload 1, entry pictures 2, all pictures
    char led_content[512] = "";                                 //LED display custom content
    char ticket_title[512] = "<b>[W Welcome] [N Dashou Control Technology Co., Ltd.] [Tonglong 2nd Road No. 882][T400-661-8765] [C Xiamen Dashou Control Technology Co., Ltd. built]</b>";            //Customized content of the receipt
    char receipt_templete[1024] = "";                           //Invoice format customization content
    int order_index = 0;                                        //Online parking lot invitation code
    short ignore_hourly_in = 0;
    char image_root[256] = "";
    char image_dir[256] = "";
    int coupon_use_limit = 0;
    char coupon_using_url[255] = "http://www.urbanparking.cn/Q";//Scan the parking ticket online to jump to the address
    int mobile_charge_standard = 255;
    int mobile_reservation_tolerance = 0;
    Setting(MYSQL *_mysql);

    ~Setting();
    
    int print_Setting();

    int select_Setting(int aidx);
    
    int update_Setting();
};