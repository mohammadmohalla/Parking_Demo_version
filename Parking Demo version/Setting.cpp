#include "Setting.h"

Setting::Setting(MYSQL *_mysql)
{
    mysql = _mysql;
}

Setting::~Setting()
{
    
}

int Setting::print_Setting()
{
    try
    {
        printf("value of aid = %d\n", aid);
        printf("value of gid = %d\n", gid);
        printf("value of plate_match_level = %d\n", plate_match_level);
        printf("value of alarm_balance = %d\n", alarm_balance);
        printf("value of alarm_enddata = %d\n", alarm_enddata);
        printf("value of align_lots_time = %d\n", align_lots_time);
        printf("value of events_retainingdays = %d\n", events_retainingdays);
        printf("value of photos_retainingdays = %d\n", photos_retainingdays);
        printf("value of clear_time = %d\n", clear_time);
        printf("value of auto_prepaidlimit = %d\n", auto_prepaidlimit);
        printf("value of invite_code = %s\n", invite_code);
        printf("value of site_prefix = %s\n", site_prefix);
        printf("value of online_marjor_ip = %s\n", online_marjor_ip);
        printf("value of online_minor_ip = %s\n", online_minor_ip);
        printf("value of qrcode_url = %s\n", qrcode_url);
        printf("value of etrecord_ip = %s\n", etrecord_ip);
        printf("value of uploadip = %s\n", uploadip);
        printf("value of uploadurl = %s\n", uploadurl);
        printf("value of photo_upload_mode = %d\n", photo_upload_mode);
        printf("value of led_content = %s\n", led_content);
        printf("value of ticket_title = %s\n", ticket_title);
        printf("value of receipt_templete = %s\n", receipt_templete);
        printf("value of order_index = %d\n", order_index);
        printf("value of ignore_hourly_in = %d\n", ignore_hourly_in);
        printf("value of image_root = %s\n", image_root);
        printf("value of image_dir = %s\n", image_dir);
        printf("value of coupon_use_limit = %d\n", coupon_use_limit);
        printf("value of coupon_using_url = %s\n", coupon_using_url);
        printf("value of mobile_charge_standard = %d\n", mobile_charge_standard);
        printf("value of mobile_reservation_tolerance = %d\n", mobile_reservation_tolerance);
    }
    catch(...)
    {
        return -1430;
    }
    return 0;
}

int Setting::select_Setting(int aidx)
{
    int id_;
    std::string statment = "SELECT * FROM v32_setting WHERE aid=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1402;
        }
        if (!stmt)
        {
            return -1402;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1403;
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
                return -1404;
            }
            if (stmt_bind_param)
            {
                return -1404;
            }
            
            id_ = aidx;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1405;
            }
            if (param_count != 1)
            {
                return -1405;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -1406;
            }
            if (!prepare_meta_result)
            {
                return -1406;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -1407;
            }
            if (column_count != 30)
            {
                return -1407;
            }
            bool stmt_execute;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1408;
            }
            if (stmt_execute)
            {
                return -1408;
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

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&plate_match_level;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&alarm_balance;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&alarm_enddata;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&align_lots_time;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&events_retainingdays;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&photos_retainingdays;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&clear_time;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&auto_prepaidlimit;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_STRING;
                bind[10].buffer= (char *)invite_code;
                bind[10].buffer_length= 10;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_STRING;
                bind[11].buffer= (char *)site_prefix;
                bind[11].buffer_length= 20;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)online_marjor_ip;
                bind[12].buffer_length= 255;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)online_minor_ip;
                bind[13].buffer_length= 255;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)qrcode_url;
                bind[14].buffer_length= 255;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)etrecord_ip;
                bind[15].buffer_length= 25;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)uploadip;
                bind[16].buffer_length= 255;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)uploadurl;
                bind[17].buffer_length= 255;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&photo_upload_mode;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_STRING;
                bind[19].buffer= (char *)led_content;
                bind[19].buffer_length= 512;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_STRING;
                bind[20].buffer= (char *)ticket_title;
                bind[20].buffer_length= 512;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)receipt_templete;
                bind[21].buffer_length= 1024;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type = MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&order_index;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* INTEGER COLUMN */
                bind[23].buffer_type = MYSQL_TYPE_SHORT;
                bind[23].buffer= (char *)&ignore_hourly_in;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* INTEGER COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_STRING;
                bind[24].buffer= (char *)image_root;
                bind[24].buffer_length= 256;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* INTEGER COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_STRING;
                bind[25].buffer= (char *)image_dir;
                bind[25].buffer_length= 256;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&coupon_use_limit;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* TIMESTAMP COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_STRING;
                bind[27].buffer= (char *)coupon_using_url;
                bind[27].buffer_length= 255;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];
                
                /* TIMESTAMP COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&mobile_charge_standard;
                bind[28].buffer_length= 255;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];
                
                /* TIMESTAMP COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_LONG;
                bind[29].buffer= (char *)&mobile_charge_standard;
                bind[29].buffer_length= 255;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];
            }
            catch(...)
            {
                return -1431;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -1409;
            }
            if (stmt_bind_result)
            {
                return -1409;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -1410;
            }
            if (stmt_store_result)
            {
                return -1410;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -1411;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -1412 ;
            }
        }
        else
        {
            return -1403;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1413;
        }
    }
    else
    {
        return -1401;
    }
    return 0;
}
    
int Setting::update_Setting()
{
    int id_;
    std::string statment = "UPDATE `v32_setting` SET `aid` = ? , `gid` = ? , `plate_match_level` = ? , `alarm_balance` = ? , `alarm_enddata` = ? , `align_lots_time` = ? , `events_retainingdays` = ? , `photos_retainingdays` = ? , `clear_time` = ? , `auto_prepaidlimit` = ? , `invite_code` = ? , `site_prefix` = ? , `online_marjor_ip` = ? , `online_minor_ip` = ? , `qrcode_url` = ? , `etrecord_ip` = ? , `uploadip` = ? , `uploadurl` = ? , `photo_upload_mode` = ? , `led_content` = ? , `ticket_title` = ? , `receipt_templete` = ? , `order_index` = ? , `ignore_hourly_in` = ? , `image_root` = ? , `image_dir` = ? , `coupon_use_limit` = ? , `coupon_using_url` = ? , mobile_charge_standard = ? , mobile_reservation_tolerance = ? WHERE `aid` = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt= mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1415;
        }
        
        if (!stmt)
        {
            return -1415;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1416;
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

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&plate_match_level;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&alarm_balance;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&alarm_enddata;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&align_lots_time;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&events_retainingdays;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&photos_retainingdays;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&clear_time;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&auto_prepaidlimit;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_STRING;
                bind[10].buffer= (char *)invite_code;
                bind[10].buffer_length= 10;
                bind[10].is_null= &is_null[10];
                length[10] = strlen(invite_code);
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_STRING;
                bind[11].buffer= (char *)site_prefix;
                bind[11].buffer_length= 20;
                bind[11].is_null= &is_null[11];
                length[11] = strlen(site_prefix);
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)online_marjor_ip;
                bind[12].buffer_length= 255;
                bind[12].is_null= &is_null[12];
                length[12] = strlen(online_marjor_ip);
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)online_minor_ip;
                bind[13].buffer_length= 255;
                bind[13].is_null= &is_null[13];
                length[13] = strlen(online_minor_ip);
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)qrcode_url;
                bind[14].buffer_length= 255;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(qrcode_url);
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)etrecord_ip;
                bind[15].buffer_length= 25;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(etrecord_ip);
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)uploadip;
                bind[16].buffer_length= 255;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(uploadip);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)uploadurl;
                bind[17].buffer_length= 255;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(uploadurl);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&photo_upload_mode;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_STRING;
                bind[19].buffer= (char *)led_content;
                bind[19].buffer_length= 512;
                bind[19].is_null= &is_null[19];
                length[19] = strlen(led_content);
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_STRING;
                bind[20].buffer= (char *)ticket_title;
                bind[20].buffer_length= 512;
                bind[20].is_null= &is_null[20];
                length[20] = strlen(ticket_title);
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)receipt_templete;
                bind[21].buffer_length= 1024;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(receipt_templete);
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type = MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&order_index;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* INTEGER COLUMN */
                bind[23].buffer_type = MYSQL_TYPE_SHORT;
                bind[23].buffer= (char *)&ignore_hourly_in;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* INTEGER COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_STRING;
                bind[24].buffer= (char *)image_root;
                bind[24].buffer_length= 256;
                bind[24].is_null= &is_null[24];
                length[24] = strlen(image_root);
                bind[24].length= &length[24];

                /* INTEGER COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_STRING;
                bind[25].buffer= (char *)image_dir;
                bind[25].buffer_length= 256;
                bind[25].is_null= &is_null[25];
                length[25] = strlen(image_dir);
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&coupon_use_limit;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* TIMESTAMP COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_STRING;
                bind[27].buffer= (char *)coupon_using_url;
                bind[27].buffer_length= 255;
                bind[27].is_null= &is_null[27];
                length[27] = strlen(coupon_using_url);
                bind[27].length= &length[27];
                
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&mobile_charge_standard;
                bind[28].buffer_length= 255;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];
                
                bind[29].buffer_type= MYSQL_TYPE_LONG;
                bind[29].buffer= (char *)&mobile_reservation_tolerance;
                bind[29].buffer_length= 255;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];
                
                bind[30].buffer_type = MYSQL_TYPE_LONG;
                bind[30].buffer= (char *)&id_;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];
            }
            catch(...)
            {
                return -1432;
            }
            
            bool bind_param = true;
            try
            {
                bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -1417;
            }
            if(bind_param)
            {
                return -1417;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1418;
            }
            if (param_count != 31)
            {
                return -1418;
            }
            id_ = aid;
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1419;
            }
            if (stmt_execute)
            {
                return -1419;
            }
            
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1420;
            }
            if (stmt_affected_rows == 1)
            {
                printf("Settings is inserted\n");
            }
            else
            {
                printf("Settings is updated\n");
            }
        }
        else
        {
            return -1416;
        }
        
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1421;
        }
    }
    return 0;
}