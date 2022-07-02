#include <iostream>
#include <time.h>
#include <string.h>
#include <sstream>
#include <iomanip> 
#include <vector>
#include <mysql/mysql.h>


class garage_info
{
public:
    
    MYSQL         *mysql;
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind_param[1];
    MYSQL_BIND    bind[73];
    MYSQL_RES     *prepare_meta_result;
    unsigned long length[73];
    my_bool       is_null[73];
    
    MYSQL_TIME    crt;
    MYSQL_TIME    last_link_t;
    
    int aid = 0;
    int gid = 0;
    char name[200] = "";
    char addr[200] = "";
    char garage_cbd[255] = "";
    float longitude = 0.0000000;
    float latitude = 0.0000000;
    char description[255] = "";
    char photo_id[255] = "";
    char zip_code[6] = "";
    char province[2] = "";
    char city[2] = "";
    char district[2] = "";
    char im1[20] = "";
    char im2[30] = "";
    char im_pwd1[20] = "";
    char im_pwd2[30] = "";
    short garage_state = 0;
    short et_3g_state = 0;
    short online_main_3g_state = 0;
    short online_sub_3g_state = 0;
    short online_main_bb_state = 0;
    short online_sub_bb_state = 0;
    short pos_state = 0;
    short qr_3g_state = 0;
    char reservation_brief[255] = "";
    char share_brief[255] = "";
    char notice[255] = "";
    char regist_code[25] = "";
    int company_serial = 1;
    time_t createtime = 0;
    int access_type = 0;
    int create_id = 0;
    char park_info[100] = "";
    char contract_num[50] = "";
    double poundage = 0;
    double data_percent = 0;
    double interleaved_percent = 0;
    double tenement_percent = 0;
    char lots_description[255] = "";
    char qrcode[255] = "";
    char alipay_parkid[255] = "";
    char phone[20] = "";
    char payee_alipay[32] = "";
    char payee_weixin[32] = "";
    char payee_netunion[32] = "";
    char payee_unionpay[32] = "";
    char payee_jiaotong[32] = "";
    double rate_alipay = 0;
    double rate_weixin = 0;
    double rate_netunion = 0;
    double rate_unionpay = 0;
    double rate_jiaotong = 0;
    short enable_alipay = 0;
    short enable_weixin = 0;
    short enable_netunion = 0;
    short enable_unionpay = 0;
    short enable_jiaotong = 0;
    short einvoice_enable = 0;
    time_t last_link_time = 0;
    char taxpayer_code[64] = "";
    char taxpayer_name[200] = "";
    char taxpayer_addr_phone[200] = "";
    char taxpayer_bank[200] = ""; 
    short alipay_daikou = 0;
    short weixin_daikou = 0;
    short bussiness_weixin = 0;
    short bussiness_alipay = 0;
    char offline_version[32] = "";

    
    garage_info(MYSQL *_mysql);

    ~garage_info();
    
    int print_garage_info();
    
    int select_garage_info(int _serial);
    
    int insert_update_garage_info();
    
    int delete_garage_info();

};
