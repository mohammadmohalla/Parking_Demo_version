#include "garage_info.h"

garage_info::garage_info(MYSQL *_mysql)
{
    mysql = _mysql;
}

garage_info::~garage_info()
{

}

int garage_info::print_garage_info()
{
    try
    {
        printf("value of aid = %d\n", aid);
        printf("value of gid = %d\n", gid);
        printf("value of name = %s\n", name);
        printf("value of addr = %s\n", addr);
        printf("value of garage_cbd = %s\n", garage_cbd);
        printf("value of longitude = %f\n", longitude);
        printf("value of latitude = %f\n", latitude);
        printf("value of description = %s\n", description);
        printf("value of photo_id = %s\n", photo_id);
        printf("value of zip_code = %s\n", zip_code);
        printf("value of province = %s\n", province);
        printf("value of city = %s\n", city);
        printf("value of district = %s\n", district);
        printf("value of im1 = %s\n", im1);
        printf("value of im2 = %s\n", im2);
        printf("value of im_pwd1 = %s\n", im_pwd1);
        printf("value of im_pwd2 = %s\n", im_pwd2);
        printf("value of garage_state = %d\n", garage_state);
        printf("value of et_3g_state = %d\n", et_3g_state);
        printf("value of online_main_3g_state = %d\n", online_main_3g_state);
        printf("value of online_sub_3g_state = %d\n", online_sub_3g_state);
        printf("value of online_main_bb_state = %d\n", online_main_bb_state);
        printf("value of online_sub_bb_state = %d\n", online_sub_bb_state);
        printf("value of pos_state = %d\n", pos_state);
        printf("value of qr_3g_state = %d\n", qr_3g_state);
        printf("value of reservation_brief = %s\n", reservation_brief);
        printf("value of share_brief = %s\n", share_brief);
        printf("value of notice = %s\n", notice);
        printf("value of regist_code = %s\n", regist_code);
        printf("value of company_serial = %d\n", company_serial);
        printf("value of createtime = %ld\n", createtime);
        printf("value of access_type = %d\n", access_type);
        printf("value of create_id = %d\n", create_id);
        printf("value of park_info = %s\n", park_info);
        printf("value of contract_num = %s\n", contract_num);
        printf("value of poundage = %f\n", poundage);
        printf("value of data_percent = %f\n", data_percent);
        printf("value of interleaved_percent = %f\n", interleaved_percent);
        printf("value of tenement_percent = %f\n", tenement_percent);
        printf("value of lots_description = %s\n", lots_description);
        printf("value of qrcode = %s\n", qrcode);
        printf("value of alipay_parkid = %s\n", alipay_parkid);
        printf("value of phone = %s\n", phone);
        printf("value of payee_alipay = %s\n", payee_alipay);
        printf("value of payee_weixin = %s\n", payee_weixin);
        printf("value of payee_netunion = %s\n", payee_netunion);
        printf("value of payee_unionpay = %s\n", payee_unionpay);
        printf("value of payee_jiaotong = %s\n", payee_jiaotong);
        printf("value of rate_alipay = %f\n", rate_alipay);
        printf("value of rate_weixin = %f\n", rate_weixin);
        printf("value of rate_netunion = %f\n", rate_netunion);
        printf("value of rate_unionpay = %f\n", rate_unionpay);
        printf("value of rate_jiaotong = %f\n", rate_jiaotong);
        printf("value of enable_alipay = %d\n", enable_alipay);
        printf("value of enable_weixin = %d\n", enable_weixin);
        printf("value of enable_netunion = %d\n", enable_netunion);
        printf("value of enable_unionpay = %d\n", enable_unionpay);
        printf("value of enable_jiaotong = %d\n", enable_jiaotong);
        printf("value of einvoice_enable = %d\n", einvoice_enable);
        printf("value of last_link_time = %ld\n", last_link_time);
        printf("value of taxpayer_code = %s\n", taxpayer_code);
        printf("value of taxpayer_name = %s\n", taxpayer_name);
        printf("value of taxpayer_addr_phone = %s\n", taxpayer_addr_phone);
        printf("value of taxpayer_bank = %s\n", taxpayer_bank);
        printf("value of alipay_daikou = %d\n", alipay_daikou);
        printf("value of weixin_daikou = %d\n", weixin_daikou);
        printf("value of bussiness_weixin = %d\n", bussiness_weixin);
        printf("value of bussiness_alipay = %d\n", bussiness_alipay);
        printf("value of offline_version = %s\n", offline_version);
    }
    catch(...)
    {
        return -1030;
    }
    return 0;
}

int garage_info::select_garage_info(int index)
{
    short id_;
    std::string statment = "SELECT * ,Unix_Timestamp(createtime), Unix_Timestamp(last_link_time) FROM v32_garage_info WHERE aid=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt= mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1002;
        }
        if (!stmt)
        {
            return -1002;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1003;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_SHORT;
                bind_param[0].buffer= (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -1004;
            }
            if (stmt_bind_param)
            {
                return -1004;
            }
            id_ = index;
            int param_count = 0;
            try
            {
                param_count= mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1005;
            }
            if (param_count != 1) /* validate parameter count */
            {
                return -1005;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -1006;
            }
            if (!prepare_meta_result)
            {
                return -1006;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -1007;
            }
            if (column_count != 71)
            {
                return -1007;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1008;
            }
            if (mysql_stmt_execute(stmt))
            {
                return -1008;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)name;
                bind[2].buffer_length= 200;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)addr;
                bind[3].buffer_length= 200;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)garage_cbd;
                bind[4].buffer_length= 255;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_FLOAT;
                bind[5].buffer= (char *)&longitude;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_FLOAT;
                bind[6].buffer= (char *)&longitude;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                bind[7].buffer_type= MYSQL_TYPE_STRING;
                bind[7].buffer= (char *)description;
                bind[7].buffer_length = 255;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                bind[8].buffer_type= MYSQL_TYPE_STRING;
                bind[8].buffer= (char *)photo_id;
                bind[8].buffer_length = 255;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                bind[9].buffer_type= MYSQL_TYPE_STRING;
                bind[9].buffer= (char *)zip_code;
                bind[9].buffer_length= 6;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                bind[10].buffer_type= MYSQL_TYPE_STRING;
                bind[10].buffer= (char *)province;
                bind[10].buffer_length= 2;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                bind[11].buffer_type= MYSQL_TYPE_STRING;
                bind[11].buffer= (char *)city;
                bind[11].buffer_length= 2;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)district;
                bind[12].buffer_length= 2;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)im1;
                bind[13].buffer_length= 20;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)im2;
                bind[14].buffer_length= 30;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)im_pwd1;
                bind[15].buffer_length= 20;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)im_pwd2;
                bind[16].buffer_length= 30;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&garage_state;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                bind[18].buffer_type= MYSQL_TYPE_SHORT;
                bind[18].buffer= (char *)&et_3g_state;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&online_main_3g_state;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                bind[20].buffer_type= MYSQL_TYPE_SHORT;
                bind[20].buffer= (char *)&online_sub_3g_state;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                bind[21].buffer_type= MYSQL_TYPE_SHORT;
                bind[21].buffer= (char *)&online_main_bb_state;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&online_sub_bb_state;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                bind[23].buffer_type= MYSQL_TYPE_SHORT;
                bind[23].buffer= (char *)&pos_state;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                bind[24].buffer_type= MYSQL_TYPE_SHORT;
                bind[24].buffer= (char *)&qr_3g_state;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                bind[25].buffer_type= MYSQL_TYPE_STRING;
                bind[25].buffer= (char *)reservation_brief;
                bind[25].buffer_length = 255;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                bind[26].buffer_type= MYSQL_TYPE_STRING;
                bind[26].buffer= (char *)share_brief;
                bind[26].buffer_length = 255;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                bind[27].buffer_type= MYSQL_TYPE_STRING;
                bind[27].buffer= (char *)notice;
                bind[27].buffer_length= 255;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                bind[28].buffer_type= MYSQL_TYPE_STRING;
                bind[28].buffer= (char *)regist_code;
                bind[28].buffer_length= 25;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                bind[29].buffer_type= MYSQL_TYPE_LONG;
                bind[29].buffer= (char *)&company_serial;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                bind[30].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[30].buffer= (char *)&crt;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&access_type;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&create_id;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                bind[33].buffer_type= MYSQL_TYPE_STRING;
                bind[33].buffer= (char *)park_info;
                bind[33].buffer_length= 100;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                bind[34].buffer_type= MYSQL_TYPE_STRING;
                bind[34].buffer= (char *)contract_num;
                bind[34].buffer_length= 50;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                bind[35].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[35].buffer= (char *)&poundage;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];        

                bind[36].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[36].buffer= (char *)&data_percent;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36]; 

                bind[37].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[37].buffer= (char *)&interleaved_percent;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37]; 

                bind[38].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[38].buffer= (char *)&tenement_percent;
                bind[38].is_null= &is_null[38];
                bind[38].length= &length[38]; 

                bind[39].buffer_type= MYSQL_TYPE_STRING;
                bind[39].buffer= (char *)lots_description;
                bind[39].buffer_length= 255;
                bind[39].is_null= &is_null[39];
                bind[39].length= &length[39];

                bind[40].buffer_type= MYSQL_TYPE_STRING;
                bind[40].buffer= (char *)qrcode;
                bind[40].buffer_length= 255;
                bind[40].is_null= &is_null[40];
                bind[40].length= &length[40];

                bind[41].buffer_type= MYSQL_TYPE_STRING;
                bind[41].buffer= (char *)alipay_parkid;
                bind[41].buffer_length= 255;
                bind[41].is_null= &is_null[41];
                bind[41].length= &length[41];

                bind[42].buffer_type= MYSQL_TYPE_STRING;
                bind[42].buffer= (char *)phone;
                bind[42].buffer_length= 20;
                bind[42].is_null= &is_null[42];
                bind[42].length= &length[42];

                bind[43].buffer_type= MYSQL_TYPE_STRING;
                bind[43].buffer= (char *)payee_alipay;
                bind[43].buffer_length= 32;
                bind[43].is_null= &is_null[43];
                bind[43].length= &length[43];

                bind[44].buffer_type= MYSQL_TYPE_STRING;
                bind[44].buffer= (char *)payee_weixin;
                bind[44].buffer_length= 32;
                bind[44].is_null= &is_null[44];
                bind[44].length= &length[44];

                bind[45].buffer_type= MYSQL_TYPE_STRING;
                bind[45].buffer= (char *)payee_netunion;
                bind[45].buffer_length= 32;
                bind[45].is_null= &is_null[45];
                bind[45].length= &length[45];

                bind[46].buffer_type= MYSQL_TYPE_STRING;
                bind[46].buffer= (char *)payee_unionpay;
                bind[46].buffer_length= 32;
                bind[46].is_null= &is_null[46];
                bind[46].length= &length[46];

                bind[47].buffer_type= MYSQL_TYPE_STRING;
                bind[47].buffer= (char *)payee_jiaotong;
                bind[47].buffer_length= 32;
                bind[47].is_null= &is_null[47];
                bind[47].length= &length[47];

                bind[48].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[48].buffer= (char *)&rate_alipay;
                bind[48].is_null= &is_null[48];
                bind[48].length= &length[48];        

                bind[49].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[49].buffer= (char *)&rate_weixin;
                bind[49].is_null= &is_null[49];
                bind[49].length= &length[49]; 

                bind[50].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[50].buffer= (char *)&rate_netunion;
                bind[50].is_null= &is_null[50];
                bind[50].length= &length[50]; 

                bind[51].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[51].buffer= (char *)&rate_unionpay;
                bind[51].is_null= &is_null[51];
                bind[51].length= &length[51]; 

                bind[52].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[52].buffer= (char *)&rate_jiaotong;
                bind[52].is_null= &is_null[52];
                bind[52].length= &length[52];

                bind[53].buffer_type= MYSQL_TYPE_SHORT;
                bind[53].buffer= (char *)&enable_alipay;
                bind[53].is_null= &is_null[53];
                bind[53].length= &length[53];        

                bind[54].buffer_type= MYSQL_TYPE_SHORT;
                bind[54].buffer= (char *)&enable_weixin;
                bind[54].is_null= &is_null[54];
                bind[54].length= &length[54]; 

                bind[55].buffer_type= MYSQL_TYPE_SHORT;
                bind[55].buffer= (char *)&enable_netunion;
                bind[55].is_null= &is_null[55];
                bind[55].length= &length[55]; 

                bind[56].buffer_type= MYSQL_TYPE_SHORT;
                bind[56].buffer= (char *)&enable_unionpay;
                bind[56].is_null= &is_null[56];
                bind[56].length= &length[56]; 

                bind[57].buffer_type= MYSQL_TYPE_SHORT;
                bind[57].buffer= (char *)&enable_jiaotong;
                bind[57].is_null= &is_null[57];
                bind[57].length= &length[57];

                bind[58].buffer_type= MYSQL_TYPE_SHORT;
                bind[58].buffer= (char *)&einvoice_enable;
                bind[58].is_null= &is_null[58];
                bind[58].length= &length[58];

                bind[59].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[59].buffer= (char *)&last_link_t;
                bind[59].is_null= &is_null[59];
                bind[59].length= &length[59];

                bind[60].buffer_type= MYSQL_TYPE_STRING;
                bind[60].buffer= (char *)taxpayer_code;
                bind[60].buffer_length= 64;
                bind[60].is_null= &is_null[60];
                bind[60].length= &length[60];

                bind[61].buffer_type= MYSQL_TYPE_STRING;
                bind[61].buffer= (char *)taxpayer_name;
                bind[61].buffer_length= 200;
                bind[61].is_null= &is_null[61];
                bind[61].length= &length[61];

                bind[62].buffer_type= MYSQL_TYPE_STRING;
                bind[62].buffer= (char *)taxpayer_addr_phone;
                bind[62].buffer_length= 200;
                bind[62].is_null= &is_null[62];
                bind[62].length= &length[62];

                bind[63].buffer_type= MYSQL_TYPE_STRING;
                bind[63].buffer= (char *)taxpayer_bank;
                bind[63].buffer_length= 200;
                bind[63].is_null= &is_null[63];
                bind[63].length= &length[63];

                bind[64].buffer_type= MYSQL_TYPE_SHORT;
                bind[64].buffer= (char *)&alipay_daikou;
                bind[64].is_null= &is_null[64];
                bind[64].length= &length[64]; 

                bind[65].buffer_type= MYSQL_TYPE_SHORT;
                bind[65].buffer= (char *)&weixin_daikou;
                bind[65].is_null= &is_null[65];
                bind[65].length= &length[65]; 

                bind[66].buffer_type= MYSQL_TYPE_SHORT;
                bind[66].buffer= (char *)&bussiness_weixin;
                bind[66].is_null= &is_null[66];
                bind[66].length= &length[66]; 

                bind[67].buffer_type= MYSQL_TYPE_SHORT;
                bind[67].buffer= (char *)&bussiness_alipay;
                bind[67].is_null= &is_null[67];
                bind[67].length= &length[67];

                bind[68].buffer_type= MYSQL_TYPE_STRING;
                bind[68].buffer= (char *)offline_version;
                bind[68].buffer_length= 32;
                bind[68].is_null= &is_null[68];
                bind[68].length= &length[68];

                bind[69].buffer_type= MYSQL_TYPE_LONG;
                bind[69].buffer= (char *)&createtime;
                bind[69].is_null= &is_null[69];
                bind[69].length= &length[69];

                bind[70].buffer_type= MYSQL_TYPE_LONG;
                bind[70].buffer= (char *)&last_link_time;
                bind[70].is_null= &is_null[70];
                bind[70].length= &length[70];
            }
            catch(...)
            {
                return -1031;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -1009;
            }
            if (stmt_bind_result)
            {
                return -1009;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -1010;
            }
            if (stmt_store_result)
            {
                return -1010;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -1011;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -1012;
            }
        }
        else
        {
            return -1003;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1013;
        }
    }
    else
    {
        return -1001;
    }
    return 0;
}
    
int garage_info::insert_update_garage_info()
{
    std::string statment = "INSERT INTO `v32_garage_info` (`aid`, `gid`, `name`, `addr`, `garage_cbd`, `longitude`, `latitude`, `description`, `photo_id`, `zip_code`, `province`, `city`, `district`, `im1`, `im2`, `im_pwd1`, `im_pwd2`, `garage_state`, `et_3g_state`, `online_main_3g_state`, `online_sub_3g_state`, `online_main_bb_state`, `online_sub_bb_state`, `pos_state`, `qr_3g_state`, `reservation_brief`, `share_brief`, `notice`, `regist_code`, `company_serial`, `createtime`, `access_type`, `create_id`, `park_info`, `contract_num`, `poundage`, `data_percent`, `interleaved_percent`, `tenement_percent`, `lots_description`, `qrcode`, `alipay_parkid`, `phone`, `payee_alipay`, `payee_weixin`, `payee_netunion`, `payee_unionpay`, `payee_jiaotong`, `rate_alipay`, `rate_weixin`, `rate_netunion`, `rate_unionpay`, `rate_jiaotong`, `enable_alipay`, `enable_weixin`, `enable_netunion`, `enable_unionpay`, `enable_jiaotong`, `einvoice_enable`, `last_link_time`, `taxpayer_code`, `taxpayer_name`, `taxpayer_addr_phone`, `taxpayer_bank`, `alipay_daikou`, `weixin_daikou`, `bussiness_weixin`, `bussiness_alipay`, `offline_version`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE aid=VALUES(aid), gid=VALUES(gid), name=VALUES(name), addr=VALUES(addr), garage_cbd=VALUES(garage_cbd), longitude=VALUES(longitude), latitude=VALUES(latitude), description=VALUES(description), photo_id=VALUES(photo_id), zip_code=VALUES(zip_code), province=VALUES(province), city=VALUES(city), district=VALUES(district), im1=VALUES(im1), im2=VALUES(im2), im_pwd1=VALUES(im_pwd1), im_pwd2=VALUES(im_pwd2), garage_state=VALUES(garage_state), et_3g_state=VALUES(et_3g_state), online_main_3g_state=VALUES(online_main_3g_state), online_sub_3g_state=VALUES(online_sub_3g_state), online_main_bb_state=VALUES(online_main_bb_state), online_sub_bb_state=VALUES(online_sub_bb_state), pos_state=VALUES(pos_state), qr_3g_state=VALUES(qr_3g_state), reservation_brief=VALUES(reservation_brief), share_brief=VALUES(share_brief), notice=VALUES(notice), regist_code=VALUES(regist_code), company_serial=VALUES(company_serial), createtime=VALUES(createtime), access_type=VALUES(access_type), create_id=VALUES(create_id), park_info=VALUES(park_info), contract_num=VALUES(contract_num), poundage=VALUES(poundage), data_percent=VALUES(data_percent), interleaved_percent=VALUES(interleaved_percent), tenement_percent=VALUES(tenement_percent), lots_description=VALUES(lots_description), qrcode=VALUES(qrcode), alipay_parkid=VALUES(alipay_parkid), phone=VALUES(phone), payee_alipay=VALUES(payee_alipay), payee_weixin=VALUES(payee_weixin), payee_netunion=VALUES(payee_netunion), payee_unionpay=VALUES(payee_unionpay), payee_jiaotong=VALUES(payee_jiaotong), rate_alipay=VALUES(rate_alipay), rate_weixin=VALUES(rate_weixin), rate_netunion=VALUES(rate_netunion), rate_unionpay=VALUES(rate_unionpay), rate_jiaotong=VALUES(rate_jiaotong), enable_alipay=VALUES(enable_alipay), enable_weixin=VALUES(enable_weixin), enable_netunion=VALUES(enable_netunion), enable_unionpay=VALUES(enable_unionpay), enable_jiaotong=VALUES(enable_jiaotong), einvoice_enable=VALUES(einvoice_enable), last_link_time=VALUES(last_link_time), taxpayer_code=VALUES(taxpayer_code), taxpayer_name=VALUES(taxpayer_name), taxpayer_addr_phone=VALUES(taxpayer_addr_phone), taxpayer_bank=VALUES(taxpayer_bank), alipay_daikou=VALUES(alipay_daikou), weixin_daikou=VALUES(weixin_daikou), bussiness_weixin=VALUES(bussiness_weixin), bussiness_alipay=VALUES(bussiness_alipay), offline_version=VALUES(offline_version)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1015;
        }
        if (!stmt)
        {
            return -1015;
        }
        bool stmt_prepare = false;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1016;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                memset(length, 0, sizeof(length));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)name;
                bind[2].buffer_length= 200;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(name);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)addr;
                bind[3].buffer_length= 200;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(addr);
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)garage_cbd;
                bind[4].buffer_length= 255;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(garage_cbd);
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_FLOAT;
                bind[5].buffer= (char *)&longitude;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_FLOAT;
                bind[6].buffer= (char *)&longitude;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                bind[7].buffer_type= MYSQL_TYPE_STRING;
                bind[7].buffer= (char *)description;
                bind[7].buffer_length = 255;
                bind[7].is_null= &is_null[7];
                length[7] = strlen(description);
                bind[7].length= &length[7];

                bind[8].buffer_type= MYSQL_TYPE_STRING;
                bind[8].buffer= (char *)photo_id;
                bind[8].buffer_length = 255;
                bind[8].is_null= &is_null[8];
                length[8] = strlen(photo_id);
                bind[8].length= &length[8];

                bind[9].buffer_type= MYSQL_TYPE_STRING;
                bind[9].buffer= (char *)zip_code;
                bind[9].buffer_length= 6;
                bind[9].is_null= &is_null[9];
                length[9] = strlen(zip_code);
                bind[9].length= &length[9];

                bind[10].buffer_type= MYSQL_TYPE_STRING;
                bind[10].buffer= (char *)province;
                bind[10].buffer_length= 2;
                bind[10].is_null= &is_null[10];
                length[10] = strlen(province);
                bind[10].length= &length[10];

                bind[11].buffer_type= MYSQL_TYPE_STRING;
                bind[11].buffer= (char *)city;
                bind[11].buffer_length= 2;
                bind[11].is_null= &is_null[11];
                length[11] = strlen(city);
                bind[11].length= &length[11];

                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)district;
                bind[12].buffer_length= 2;
                bind[12].is_null= &is_null[12];
                length[12] = strlen(district);
                bind[12].length= &length[12];

                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)im1;
                bind[13].buffer_length= 20;
                bind[13].is_null= &is_null[13];
                length[13] = strlen(im1);
                bind[13].length= &length[13];

                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)im2;
                bind[14].buffer_length= 30;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(im2);
                bind[14].length= &length[14];

                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)im_pwd1;
                bind[15].buffer_length= 20;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(im_pwd1);
                bind[15].length= &length[15];

                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)im_pwd2;
                bind[16].buffer_length= 30;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(im_pwd2);
                bind[16].length= &length[16];

                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&garage_state;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                bind[18].buffer_type= MYSQL_TYPE_SHORT;
                bind[18].buffer= (char *)&et_3g_state;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&online_main_3g_state;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                bind[20].buffer_type= MYSQL_TYPE_SHORT;
                bind[20].buffer= (char *)&online_sub_3g_state;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                bind[21].buffer_type= MYSQL_TYPE_SHORT;
                bind[21].buffer= (char *)&online_main_bb_state;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&online_sub_bb_state;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                bind[23].buffer_type= MYSQL_TYPE_SHORT;
                bind[23].buffer= (char *)&pos_state;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                bind[24].buffer_type= MYSQL_TYPE_SHORT;
                bind[24].buffer= (char *)&qr_3g_state;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                bind[25].buffer_type= MYSQL_TYPE_STRING;
                bind[25].buffer= (char *)reservation_brief;
                bind[25].buffer_length = 255;
                bind[25].is_null= &is_null[25];
                length[25] = strlen(reservation_brief);
                bind[25].length= &length[25];

                bind[26].buffer_type= MYSQL_TYPE_STRING;
                bind[26].buffer= (char *)share_brief;
                bind[26].buffer_length = 255;
                bind[26].is_null= &is_null[26];
                length[26] = strlen(share_brief);
                bind[26].length= &length[26];

                bind[27].buffer_type= MYSQL_TYPE_STRING;
                bind[27].buffer= (char *)notice;
                bind[27].buffer_length= 255;
                bind[27].is_null= &is_null[27];
                length[27] = strlen(notice);
                bind[27].length= &length[27];

                bind[28].buffer_type= MYSQL_TYPE_STRING;
                bind[28].buffer= (char *)regist_code;
                bind[28].buffer_length= 25;
                bind[28].is_null= &is_null[28];
                length[28] = strlen(regist_code);
                bind[28].length= &length[28];

                bind[29].buffer_type= MYSQL_TYPE_LONG;
                bind[29].buffer= (char *)&company_serial;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                bind[30].buffer_type= MYSQL_TYPE_LONG;
                bind[30].buffer= (char *)&createtime;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&access_type;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&create_id;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                bind[33].buffer_type= MYSQL_TYPE_STRING;
                bind[33].buffer= (char *)park_info;
                bind[33].buffer_length= 100;
                bind[33].is_null= &is_null[33];
                length[33] = strlen(park_info);
                bind[33].length= &length[33];

                bind[34].buffer_type= MYSQL_TYPE_STRING;
                bind[34].buffer= (char *)contract_num;
                bind[34].buffer_length= 50;
                bind[34].is_null= &is_null[34];
                length[34] = strlen(contract_num);
                bind[34].length= &length[34];

                bind[35].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[35].buffer= (char *)&poundage;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];        

                bind[36].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[36].buffer= (char *)&data_percent;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36]; 

                bind[37].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[37].buffer= (char *)&interleaved_percent;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37]; 

                bind[38].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[38].buffer= (char *)&tenement_percent;
                bind[38].is_null= &is_null[38];
                bind[38].length= &length[38]; 

                bind[39].buffer_type= MYSQL_TYPE_STRING;
                bind[39].buffer= (char *)lots_description;
                bind[39].buffer_length= 255;
                bind[39].is_null= &is_null[39];
                length[39] = strlen(lots_description);
                bind[39].length= &length[39];

                bind[40].buffer_type= MYSQL_TYPE_STRING;
                bind[40].buffer= (char *)qrcode;
                bind[40].buffer_length= 255;
                bind[40].is_null= &is_null[40];
                length[40] = strlen(qrcode);
                bind[40].length= &length[40];

                bind[41].buffer_type= MYSQL_TYPE_STRING;
                bind[41].buffer= (char *)alipay_parkid;
                bind[41].buffer_length= 255;
                bind[41].is_null= &is_null[41];
                length[41] = strlen(alipay_parkid);
                bind[41].length= &length[41];

                bind[42].buffer_type= MYSQL_TYPE_STRING;
                bind[42].buffer= (char *)phone;
                bind[42].buffer_length= 20;
                bind[42].is_null= &is_null[42];
                length[42] = strlen(phone);
                bind[42].length= &length[42];

                bind[43].buffer_type= MYSQL_TYPE_STRING;
                bind[43].buffer= (char *)payee_alipay;
                bind[43].buffer_length= 32;
                bind[43].is_null= &is_null[43];
                length[43] = strlen(payee_alipay);
                bind[43].length= &length[43];

                bind[44].buffer_type= MYSQL_TYPE_STRING;
                bind[44].buffer= (char *)payee_weixin;
                bind[44].buffer_length= 32;
                bind[44].is_null= &is_null[44];
                length[44] = strlen(payee_weixin);
                bind[44].length= &length[44];

                bind[45].buffer_type= MYSQL_TYPE_STRING;
                bind[45].buffer= (char *)payee_netunion;
                bind[45].buffer_length= 32;
                bind[45].is_null= &is_null[45];
                length[45] = strlen(payee_netunion);
                bind[45].length= &length[45];

                bind[46].buffer_type= MYSQL_TYPE_STRING;
                bind[46].buffer= (char *)payee_unionpay;
                bind[46].buffer_length= 32;
                bind[46].is_null= &is_null[46];
                length[46] = strlen(payee_unionpay);
                bind[46].length= &length[46];

                bind[47].buffer_type= MYSQL_TYPE_STRING;
                bind[47].buffer= (char *)payee_jiaotong;
                bind[47].buffer_length= 32;
                bind[47].is_null= &is_null[47];
                length[47] = strlen(payee_jiaotong);
                bind[47].length= &length[47];

                bind[48].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[48].buffer= (char *)&rate_alipay;
                bind[48].is_null= &is_null[48];
                bind[48].length= &length[48];        

                bind[49].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[49].buffer= (char *)&rate_weixin;
                bind[49].is_null= &is_null[49];
                bind[49].length= &length[49]; 

                bind[50].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[50].buffer= (char *)&rate_netunion;
                bind[50].is_null= &is_null[50];
                bind[50].length= &length[50]; 

                bind[51].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[51].buffer= (char *)&rate_unionpay;
                bind[51].is_null= &is_null[51];
                bind[51].length= &length[51]; 

                bind[52].buffer_type= MYSQL_TYPE_DOUBLE;
                bind[52].buffer= (char *)&rate_jiaotong;
                bind[52].is_null= &is_null[52];
                bind[52].length= &length[52];

                bind[53].buffer_type= MYSQL_TYPE_SHORT;
                bind[53].buffer= (char *)&enable_alipay;
                bind[53].is_null= &is_null[53];
                bind[53].length= &length[53];        

                bind[54].buffer_type= MYSQL_TYPE_SHORT;
                bind[54].buffer= (char *)&enable_weixin;
                bind[54].is_null= &is_null[54];
                bind[54].length= &length[54]; 

                bind[55].buffer_type= MYSQL_TYPE_SHORT;
                bind[55].buffer= (char *)&enable_netunion;
                bind[55].is_null= &is_null[55];
                bind[55].length= &length[55]; 

                bind[56].buffer_type= MYSQL_TYPE_SHORT;
                bind[56].buffer= (char *)&enable_unionpay;
                bind[56].is_null= &is_null[56];
                bind[56].length= &length[56]; 

                bind[57].buffer_type= MYSQL_TYPE_SHORT;
                bind[57].buffer= (char *)&enable_jiaotong;
                bind[57].is_null= &is_null[57];
                bind[57].length= &length[57];

                bind[58].buffer_type= MYSQL_TYPE_SHORT;
                bind[58].buffer= (char *)&einvoice_enable;
                bind[58].is_null= &is_null[58];
                bind[58].length= &length[58];

                bind[59].buffer_type= MYSQL_TYPE_LONG;
                bind[59].buffer= (char *)&last_link_time;
                bind[59].is_null= &is_null[59];
                bind[59].length= &length[59];

                bind[60].buffer_type= MYSQL_TYPE_STRING;
                bind[60].buffer= (char *)taxpayer_code;
                bind[60].buffer_length= 64;
                bind[60].is_null= &is_null[60];
                length[60] = strlen(taxpayer_code);
                bind[60].length= &length[60];

                bind[61].buffer_type= MYSQL_TYPE_STRING;
                bind[61].buffer= (char *)taxpayer_name;
                bind[61].buffer_length= 200;
                bind[61].is_null= &is_null[61];
                length[61] = strlen(taxpayer_name);
                bind[61].length= &length[61];

                bind[62].buffer_type= MYSQL_TYPE_STRING;
                bind[62].buffer= (char *)taxpayer_addr_phone;
                bind[62].buffer_length= 200;
                bind[62].is_null= &is_null[62];
                length[62] = strlen(taxpayer_addr_phone);
                bind[62].length= &length[62];

                bind[63].buffer_type= MYSQL_TYPE_STRING;
                bind[63].buffer= (char *)taxpayer_bank;
                bind[63].buffer_length= 200;
                bind[63].is_null= &is_null[63];
                length[63] = strlen(taxpayer_bank);
                bind[63].length= &length[63];

                bind[64].buffer_type= MYSQL_TYPE_SHORT;
                bind[64].buffer= (char *)&alipay_daikou;
                bind[64].is_null= &is_null[64];
                bind[64].length= &length[64]; 

                bind[65].buffer_type= MYSQL_TYPE_SHORT;
                bind[65].buffer= (char *)&weixin_daikou;
                bind[65].is_null= &is_null[65];
                bind[65].length= &length[65]; 

                bind[66].buffer_type= MYSQL_TYPE_SHORT;
                bind[66].buffer= (char *)&bussiness_weixin;
                bind[66].is_null= &is_null[66];
                bind[66].length= &length[66]; 

                bind[67].buffer_type= MYSQL_TYPE_SHORT;
                bind[67].buffer= (char *)&bussiness_alipay;
                bind[67].is_null= &is_null[67];
                bind[67].length= &length[67];

                bind[68].buffer_type= MYSQL_TYPE_STRING;
                bind[68].buffer= (char *)offline_version;
                bind[68].buffer_length= 32;
                bind[68].is_null= &is_null[68];
                length[68] = strlen(offline_version);
                bind[68].length= &length[68];
            }
            catch(...)
            {
                return -1031;
            }
            bool bind_param = true;
            try
            {
                bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -1017;
            }
            if (bind_param)
            {
                return -1017;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1018;
            }
            if (param_count != 69) /* validate parameter count */
            {
                return -1018;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1019;
            }
            if (mysql_stmt_execute(stmt))
            {
                return -1019;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1020;
            }
            if (stmt_affected_rows == 1)
            {
                printf("garage_info is inserted\n");
            }
            else
            {
                printf("garage_info is updated\n");
            }
        }
        else
        {
            return -1016;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1021;
        }
    }
    else
    {
        return -1014;
    }
    return 0;
}
    
int garage_info::delete_garage_info()
{
    try
    {
        strcpy(name, "");
        strcpy(addr ,"");
        strcpy(garage_cbd, "");
        longitude = 0;
        latitude = 0;
        strcpy(description, "");
        strcpy(photo_id, "");
        strcpy(zip_code, "");
        strcpy(province, "");
        strcpy(city, "");
        strcpy(district, "");
        strcpy(im1, "");
        strcpy(im2, "");
        strcpy(im_pwd1, "");
        strcpy(im_pwd2, "");
        garage_state = 0;
        et_3g_state = 0;
        online_main_3g_state = 0;
        online_sub_3g_state = 0;
        online_main_bb_state = 0;
        online_sub_bb_state = 0;
        pos_state = 0;
        qr_3g_state = 0;
        strcpy(reservation_brief, "");
        strcpy(share_brief, "");
        strcpy(notice, "");
        strcpy(regist_code, "");
        company_serial = 1;
        createtime = 0;
        access_type = 0;
        create_id = 0;
        strcpy(park_info, "");
        strcpy(contract_num, "");
        poundage = 0;
        data_percent = 0;
        interleaved_percent = 0;
        tenement_percent = 0;
        strcpy(lots_description, "");
        strcpy(qrcode, "");
        strcpy(alipay_parkid, "");
        strcpy(phone, "");
        strcpy(payee_alipay, "");
        strcpy(payee_weixin, "");
        strcpy(payee_netunion, "");
        strcpy(payee_unionpay, "");
        strcpy(payee_jiaotong, "");
        rate_alipay = 0;
        rate_weixin = 0;
        rate_netunion = 0;
        rate_unionpay = 0;
        rate_jiaotong = 0;
        enable_alipay = 0;
        enable_weixin = 0;
        enable_netunion = 0;
        enable_unionpay = 0;
        enable_jiaotong = 0;
        einvoice_enable = 0;
        last_link_time = 0;
        strcpy(taxpayer_code, "");
        strcpy(taxpayer_name, "");
        strcpy(taxpayer_addr_phone, "");
        strcpy(taxpayer_bank, "");
        alipay_daikou = 0;
        weixin_daikou = 0;
        bussiness_weixin = 0;
        bussiness_alipay = 0;
        strcpy(offline_version, "");
    }
    catch(...)
    {
        return -1033;
    }
    short id_;
    std::string statment = "DELETE FROM `v32_garage_info` WHERE `aid`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1023;
        }
        if (!stmt)
        {
            return -1023;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1024;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_SHORT;
                bind_param[0].buffer= (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -1025;
            }
            if (stmt_bind_param)
            {
                return -1025;
            }
            id_ = aid;
            int param_count = 0;
            try
            {
                mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1026;
            }
            if (param_count != 1) /* validate parameter count */
            {
                return -1026;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1027;
            }
            if (stmt_execute)
            {
                return -1027;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1028;
            }
            if (stmt_affected_rows < 1)
            {
                return -1028;
            }    
        }
        else
        {
            return -1024;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1029;
        }
    }
    else
    {
        return -1022;
    }
    return 0;
}