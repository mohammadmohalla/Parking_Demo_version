#include "temp_card.h"

temp_card::temp_card(MYSQL *_mysql)
{
    mysql = _mysql;
}

temp_card::~temp_card()
{
    
}

int temp_card::print_Temp_Account()
{
    try
    {
        printf("%ld %d %d %s %s %d %d %d %ld %ld %ld %ld %d %d %d %d %d %d %d %ld %d %s %d %s %d %d %ld %ld %d %d %d %d %d %d %d %s %d %d %s %s %s %s %s %s %s %s %d",
            id,
            parking_type,
            ticket_type,
            ticket,
            plate,
            account_state,
            parking_type,
            present_type,
            in_time,
            pay_time,
            inner_intime,
            inner_outtime,
            insite,
            charge_site,
            inner_insite,
            inner_outsite,
            coupon_total_time,
            coupon_total_sum,
            limit_sum,
            limit_time,
            paid_sum,
            online_order,
            hour_ticket_type,
            hour_ticket_num,
            charge_type,
            access_group,
            start_time,
            end_time,
            prepaid_balance,
            prepaid_account_id,
            monthly_type,
            lots_group,
            ticket_lpbind,
            inner_group,
            time_group,
            lot_name,
            prepaid_charge_rule,
            monthly_charge_rule,
            photo_id,
            owner_name,
            phone,
            email,
            addr,
            description,
            add_info1,
            add_info2,
            has_downloaded
            );
    }
    catch(...)
    {
        return -4157;
    }
    return 0;
}

int temp_card::Select_Temp_Account_id(int index)
{
    short id_;
    std::string statment = "SELECT *,UNIX_TIMESTAMP(in_time),UNIX_TIMESTAMP(pay_time),UNIX_TIMESTAMP(inner_intime),UNIX_TIMESTAMP(inner_outtime),UNIX_TIMESTAMP(limit_time),UNIX_TIMESTAMP(start_time),UNIX_TIMESTAMP(end_time) FROM v32_tmp_cards_130000 WHERE id=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4102;
        }
        if (!stmt)
        {
            return -4102;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4103;
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
                return -4104;
            }
            if (stmt_bind_param)
            {
                return -4104;
            }
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4105;
            }
            if (param_count != 1)
            {
                return -4105;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -4106;
            }
            if (!prepare_meta_result)
            {
                return -4106;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -4107;
            }
            if (column_count != 54)
            {
                return -4107;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4108;
            }
            if (stmt_execute)
            {
                return -4108;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_SHORT;
                bind[1].buffer= (char *)&operate_type;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&ticket_type;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&account_state;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&parking_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&present_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[47].buffer_type= MYSQL_TYPE_LONG;
                bind[47].buffer= (char *)&in_time;
                bind[47].is_null= &is_null[47];
                bind[47].length= &length[47];

                /* SHORT COLUMN */
                bind[48].buffer_type= MYSQL_TYPE_LONG;
                bind[48].buffer= (char *)&pay_time;
                bind[48].is_null= &is_null[48];
                bind[48].length= &length[48];

                /* SHORT COLUMN */
                bind[49].buffer_type= MYSQL_TYPE_LONG;
                bind[49].buffer= (char *)&inner_intime;
                bind[49].is_null= &is_null[49];
                bind[49].length= &length[49];

                /* SHORT COLUMN */
                bind[50].buffer_type= MYSQL_TYPE_LONG;
                bind[50].buffer= (char *)&inner_outtime;
                bind[50].is_null= &is_null[50];
                bind[50].length= &length[50];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&insite;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&charge_site;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&inner_insite;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* SHORT COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&inner_outsite;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&coupon_total_time;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&coupon_total_sum;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&limit_sum;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[51].buffer_type= MYSQL_TYPE_LONG;
                bind[51].buffer= (char *)&limit_time;
                bind[51].is_null= &is_null[51];
                bind[51].length= &length[51];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&paid_sum;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* SHORT COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)&online_order;
                bind[21].buffer_length= 255;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&hour_ticket_type;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_STRING;
                bind[23].buffer= (char *)&hour_ticket_num;
                bind[23].buffer_length= 20;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&charge_type;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&access_group;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[52].buffer_type= MYSQL_TYPE_LONG;
                bind[52].buffer= (char *)&start_time;
                bind[52].is_null= &is_null[52];
                bind[52].length= &length[52];

                /* SHORT COLUMN */
                bind[53].buffer_type= MYSQL_TYPE_LONG;
                bind[53].buffer= (char *)&end_time;
                bind[53].is_null= &is_null[53];
                bind[53].length= &length[53];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&prepaid_balance;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* SHORT COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_LONG;
                bind[29].buffer= (char *)&prepaid_account_id;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* SHORT COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_LONG;
                bind[30].buffer= (char *)&monthly_type;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* SHORT COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&lots_group;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&ticket_lpbind;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&inner_group;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&time_group;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_STRING;
                bind[35].buffer= (char *)&lot_name;
                bind[35].buffer_length= 50;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];

                /* SHORT COLUMN */
                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&prepaid_charge_rule;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                /* SHORT COLUMN */
                bind[37].buffer_type= MYSQL_TYPE_LONG;
                bind[37].buffer= (char *)&monthly_charge_rule;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37];

                /* SHORT COLUMN */
                bind[38].buffer_type= MYSQL_TYPE_STRING;
                bind[38].buffer= (char *)&photo_id;
                bind[38].buffer_length= 255;
                bind[38].is_null= &is_null[38];
                bind[38].length= &length[38];

                /* SHORT COLUMN */
                bind[39].buffer_type= MYSQL_TYPE_STRING;
                bind[39].buffer= (char *)&owner_name;
                bind[39].buffer_length= 20;
                bind[39].is_null= &is_null[39];
                bind[39].length= &length[39];

                /* SHORT COLUMN */
                bind[40].buffer_type= MYSQL_TYPE_STRING;
                bind[40].buffer= (char *)&phone;
                bind[40].buffer_length= 255;
                bind[40].is_null= &is_null[40];
                bind[40].length= &length[40];

                /* SHORT COLUMN */
                bind[41].buffer_type= MYSQL_TYPE_STRING;
                bind[41].buffer= (char *)&email;
                bind[41].buffer_length= 65;
                bind[41].is_null= &is_null[41];
                bind[41].length= &length[41];

                /* SHORT COLUMN */
                bind[42].buffer_type= MYSQL_TYPE_STRING;
                bind[42].buffer= (char *)&addr;
                bind[42].buffer_length= 100;
                bind[42].is_null= &is_null[42];
                bind[42].length= &length[42];

                /* SHORT COLUMN */
                bind[43].buffer_type= MYSQL_TYPE_STRING;
                bind[43].buffer= (char *)&description;
                bind[43].buffer_length= 64;
                bind[43].is_null= &is_null[43];
                bind[43].length= &length[43];

                /* SHORT COLUMN */
                bind[44].buffer_type= MYSQL_TYPE_STRING;
                bind[44].buffer= (char *)&add_info1;
                bind[44].buffer_length= 255;
                bind[44].is_null= &is_null[44];
                bind[44].length= &length[44];

                /* SHORT COLUMN */
                bind[45].buffer_type= MYSQL_TYPE_STRING;
                bind[45].buffer= (char *)&add_info2;
                bind[45].buffer_length= 255;
                bind[45].is_null= &is_null[45];
                bind[45].length= &length[45];

                /* SHORT COLUMN */
                bind[46].buffer_type= MYSQL_TYPE_SHORT;
                bind[46].buffer= (char *)&has_downloaded;
                bind[46].is_null= &is_null[46];
                bind[46].length= &length[46];
            }
            catch(...)
            {
                return -4158;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -4109;
            }
            if (stmt_bind_result)
            {
                return -4109;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -4110;
            }
            if (stmt_store_result)
            {
                return -4110;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -4111;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -4112;
            }
        }
        else
        {
            return -4103;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4113;
        }
    }
    else
    {
        return -4101;
    }
    return 0;
}

int temp_card::Select_Temp_Account_by_plate(std::string curr_plate, int match_plate)
{
    char plate_[20];
    std::string statment = "SELECT *,UNIX_TIMESTAMP(in_time),UNIX_TIMESTAMP(pay_time),UNIX_TIMESTAMP(inner_intime),UNIX_TIMESTAMP(inner_outtime),UNIX_TIMESTAMP(limit_time),UNIX_TIMESTAMP(start_time),UNIX_TIMESTAMP(end_time) FROM v32_tmp_cards_130000 WHERE SUBSTR(plate,1," + std::to_string(match_plate) +")=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4115;
        }
        if (!stmt)
        {
            return -4115;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4116;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_STRING;
                bind_param[0].buffer= (char *)plate_;
                bind_param[0].buffer_length= strlen(curr_plate.c_str());
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -4117;
            }
            if (stmt_bind_param)
            {
                return -4117;
            }
            int param_count = 0;
            try
            {
                strncpy( plate_, curr_plate.c_str(), match_plate);
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4118;
            }
            if (param_count != 1)
            {
                return -4118;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -4119;
            }
            if (!prepare_meta_result)
            {
                return -4119;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -4120;
            }
            if (column_count != 54)
            {
                return -4120;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4121;
            }
            if (stmt_execute)
            {
                return -4121;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_SHORT;
                bind[1].buffer= (char *)&operate_type;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&ticket_type;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&account_state;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&parking_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&present_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[47].buffer_type= MYSQL_TYPE_LONG;
                bind[47].buffer= (char *)&in_time;
                bind[47].is_null= &is_null[47];
                bind[47].length= &length[47];

                /* SHORT COLUMN */
                bind[48].buffer_type= MYSQL_TYPE_LONG;
                bind[48].buffer= (char *)&pay_time;
                bind[48].is_null= &is_null[48];
                bind[48].length= &length[48];

                /* SHORT COLUMN */
                bind[49].buffer_type= MYSQL_TYPE_LONG;
                bind[49].buffer= (char *)&inner_intime;
                bind[49].is_null= &is_null[49];
                bind[49].length= &length[49];

                /* SHORT COLUMN */
                bind[50].buffer_type= MYSQL_TYPE_LONG;
                bind[50].buffer= (char *)&inner_outtime;
                bind[50].is_null= &is_null[50];
                bind[50].length= &length[50];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&insite;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&charge_site;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&inner_insite;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* SHORT COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&inner_outsite;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&coupon_total_time;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&coupon_total_sum;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&limit_sum;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[51].buffer_type= MYSQL_TYPE_LONG;
                bind[51].buffer= (char *)&limit_time;
                bind[51].is_null= &is_null[51];
                bind[51].length= &length[51];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&paid_sum;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* SHORT COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)&online_order;
                bind[21].buffer_length= 255;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&hour_ticket_type;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_STRING;
                bind[23].buffer= (char *)&hour_ticket_num;
                bind[23].buffer_length= 20;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&charge_type;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&access_group;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[52].buffer_type= MYSQL_TYPE_LONG;
                bind[52].buffer= (char *)&start_time;
                bind[52].is_null= &is_null[52];
                bind[52].length= &length[52];

                /* SHORT COLUMN */
                bind[53].buffer_type= MYSQL_TYPE_LONG;
                bind[53].buffer= (char *)&end_time;
                bind[53].is_null= &is_null[53];
                bind[53].length= &length[53];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&prepaid_balance;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* SHORT COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_LONG;
                bind[29].buffer= (char *)&prepaid_account_id;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* SHORT COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_LONG;
                bind[30].buffer= (char *)&monthly_type;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* SHORT COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&lots_group;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&ticket_lpbind;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&inner_group;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&time_group;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_STRING;
                bind[35].buffer= (char *)&lot_name;
                bind[35].buffer_length= 50;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];

                /* SHORT COLUMN */
                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&prepaid_charge_rule;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                /* SHORT COLUMN */
                bind[37].buffer_type= MYSQL_TYPE_LONG;
                bind[37].buffer= (char *)&monthly_charge_rule;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37];

                /* SHORT COLUMN */
                bind[38].buffer_type= MYSQL_TYPE_STRING;
                bind[38].buffer= (char *)&photo_id;
                bind[38].buffer_length= 255;
                bind[38].is_null= &is_null[38];
                bind[38].length= &length[38];

                /* SHORT COLUMN */
                bind[39].buffer_type= MYSQL_TYPE_STRING;
                bind[39].buffer= (char *)&owner_name;
                bind[39].buffer_length= 20;
                bind[39].is_null= &is_null[39];
                bind[39].length= &length[39];

                /* SHORT COLUMN */
                bind[40].buffer_type= MYSQL_TYPE_STRING;
                bind[40].buffer= (char *)&phone;
                bind[40].buffer_length= 255;
                bind[40].is_null= &is_null[40];
                bind[40].length= &length[40];

                /* SHORT COLUMN */
                bind[41].buffer_type= MYSQL_TYPE_STRING;
                bind[41].buffer= (char *)&email;
                bind[41].buffer_length= 65;
                bind[41].is_null= &is_null[41];
                bind[41].length= &length[41];

                /* SHORT COLUMN */
                bind[42].buffer_type= MYSQL_TYPE_STRING;
                bind[42].buffer= (char *)&addr;
                bind[42].buffer_length= 100;
                bind[42].is_null= &is_null[42];
                bind[42].length= &length[42];

                /* SHORT COLUMN */
                bind[43].buffer_type= MYSQL_TYPE_STRING;
                bind[43].buffer= (char *)&description;
                bind[43].buffer_length= 64;
                bind[43].is_null= &is_null[43];
                bind[43].length= &length[43];

                /* SHORT COLUMN */
                bind[44].buffer_type= MYSQL_TYPE_STRING;
                bind[44].buffer= (char *)&add_info1;
                bind[44].buffer_length= 255;
                bind[44].is_null= &is_null[44];
                bind[44].length= &length[44];

                /* SHORT COLUMN */
                bind[45].buffer_type= MYSQL_TYPE_STRING;
                bind[45].buffer= (char *)&add_info2;
                bind[45].buffer_length= 255;
                bind[45].is_null= &is_null[45];
                bind[45].length= &length[45];

                /* SHORT COLUMN */
                bind[46].buffer_type= MYSQL_TYPE_SHORT;
                bind[46].buffer= (char *)&has_downloaded;
                bind[46].is_null= &is_null[46];
                bind[46].length= &length[46];
            }
            catch(...)
            {
                return -4159;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -4122;
            }
            if (stmt_bind_result)
            {
                return -4122;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -4123;
            }
            if (stmt_store_result)
            {
                return -4123;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -4124;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -4125;
            }
        }
        else
        {
            return -4116;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4126;
        }
    }
    else
    {
        return -4114;
    }
    return 0;
}

int temp_card::Insert_Temp_Account()
{
    std::string statment = "INSERT INTO `v32_tmp_cards_130000` (`id`, `operate_type`, `ticket_type`, `ticket`, `plate`, `account_state`, `parking_type`, `present_type`, `in_time`, `pay_time`, `inner_intime`, `inner_outtime`, `insite`, `charge_site`, `inner_insite`, `inner_outsite`, `coupon_total_time`, `coupon_total_sum`, `limit_sum`, `limit_time`, `paid_sum`, `online_order`, `hour_ticket_type`, `hour_ticket_num`, `charge_type`, `access_group`, `start_time`, `end_time`, `prepaid_balance`, `prepaid_account_id`, `monthly_type`, `lots_group`, `ticket_lpbind`, `inner_group`, `time_group`, `lot_name`, `prepaid_charge_rule`, `monthly_charge_rule`, `photo_id`, `owner_name`, `phone`, `email`, `addr`, `description`, `add_info1`, `add_info2`, `has_download`) VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), FROM_UNIXTIME(?), FROM_UNIXTIME(?), FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4128;
        }
        if (!stmt)
        {
            return -4128;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4129;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_SHORT;
                bind[1].buffer= (char *)&operate_type;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&ticket_type;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(ticket);
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(plate);
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&account_state;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&parking_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&present_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&in_time;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&pay_time;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&inner_intime;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&inner_outtime;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&insite;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&charge_site;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&inner_insite;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* SHORT COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&inner_outsite;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&coupon_total_time;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&coupon_total_sum;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&limit_sum;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_LONG;
                bind[19].buffer= (char *)&limit_time;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&paid_sum;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* SHORT COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_order;
                bind[21].buffer_length= 255;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(online_order);
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&hour_ticket_type;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_STRING;
                bind[23].buffer= (char *)hour_ticket_num;
                bind[23].buffer_length= 20;
                bind[23].is_null= &is_null[23];
                length[23] = strlen(hour_ticket_num);
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&charge_type;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&access_group;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&start_time;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_LONG;
                bind[27].buffer= (char *)&end_time;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&prepaid_balance;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* SHORT COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_LONG;
                bind[29].buffer= (char *)&prepaid_account_id;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* SHORT COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_LONG;
                bind[30].buffer= (char *)&monthly_type;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* SHORT COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&lots_group;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&ticket_lpbind;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&inner_group;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&time_group;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_STRING;
                bind[35].buffer= (char *)&lot_name;
                bind[35].buffer_length= 50;
                bind[35].is_null= &is_null[35];
                length[35] = strlen(lot_name);
                bind[35].length= &length[35];

                /* SHORT COLUMN */
                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&prepaid_charge_rule;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                /* SHORT COLUMN */
                bind[37].buffer_type= MYSQL_TYPE_LONG;
                bind[37].buffer= (char *)&monthly_charge_rule;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37];

                /* SHORT COLUMN */
                bind[38].buffer_type= MYSQL_TYPE_STRING;
                bind[38].buffer= (char *)photo_id;
                bind[38].buffer_length= 255;
                bind[38].is_null= &is_null[38];
                length[38] = strlen(photo_id);
                bind[38].length= &length[38];

                /* SHORT COLUMN */
                bind[39].buffer_type= MYSQL_TYPE_STRING;
                bind[39].buffer= (char *)owner_name;
                bind[39].buffer_length= 20;
                bind[39].is_null= &is_null[39];
                length[39] = strlen(owner_name);
                bind[39].length= &length[39];

                /* SHORT COLUMN */
                bind[40].buffer_type= MYSQL_TYPE_STRING;
                bind[40].buffer= (char *)phone;
                bind[40].buffer_length= 255;
                bind[40].is_null= &is_null[40];
                length[40] = strlen(phone);
                bind[40].length= &length[40];

                /* SHORT COLUMN */
                bind[41].buffer_type= MYSQL_TYPE_STRING;
                bind[41].buffer= (char *)email;
                bind[41].buffer_length= 65;
                bind[41].is_null= &is_null[41];
                length[41] = strlen(email);
                bind[41].length= &length[41];

                /* SHORT COLUMN */
                bind[42].buffer_type= MYSQL_TYPE_STRING;
                bind[42].buffer= (char *)addr;
                bind[42].buffer_length= 100;
                bind[42].is_null= &is_null[42];
                length[42] = strlen(addr);
                bind[42].length= &length[42];

                /* SHORT COLUMN */
                bind[43].buffer_type= MYSQL_TYPE_STRING;
                bind[43].buffer= (char *)description;
                bind[43].buffer_length= 64;
                bind[43].is_null= &is_null[43];
                length[43] = strlen(description);
                bind[43].length= &length[43];

                /* SHORT COLUMN */
                bind[44].buffer_type= MYSQL_TYPE_STRING;
                bind[44].buffer= (char *)add_info1;
                bind[44].buffer_length= 255;
                bind[44].is_null= &is_null[44];
                length[44] = strlen(add_info1);
                bind[44].length= &length[44];

                /* SHORT COLUMN */
                bind[45].buffer_type= MYSQL_TYPE_STRING;
                bind[45].buffer= (char *)add_info2;
                bind[45].buffer_length= 255;
                bind[45].is_null= &is_null[45];
                length[45] = strlen(add_info2);
                bind[45].length= &length[45];

                /* SHORT COLUMN */
                bind[46].buffer_type= MYSQL_TYPE_SHORT;
                bind[46].buffer= (char *)&has_downloaded;
                bind[46].is_null= &is_null[46];
                bind[46].length= &length[46];
            }
            catch(...)
            {
                return -4160;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -4130;
            }
            if (stmt_bind_param)
            {
                return -4130;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4131;
            }
            if (param_count != 47)
            {
                return -4131;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4132;
            }
            if (stmt_execute)
            {
                return -4132;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -4133;
            }
            if (stmt_affected_rows != 1)
            {
                return -4133;
            }
        }
        else
        {
            return -4129;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4134;
        }
    }
    else
    {
        return -4127;
    }
    return 0;
}

int temp_card::Insert_Update_Temp_Account()
{
    std::string statment = "INSERT INTO `v32_tmp_cards_130000` (`id`, `operate_type`, `ticket_type`, `ticket`, `plate`, `account_state`, `parking_type`, `present_type`, `in_time`, `pay_time`, `inner_intime`, `inner_outtime`, `insite`, `charge_site`, `inner_insite`, `inner_outsite`, `coupon_total_time`, `coupon_total_sum`, `limit_sum`, `limit_time`, `paid_sum`, `online_order`, `hour_ticket_type`, `hour_ticket_num`, `charge_type`, `access_group`, `start_time`, `end_time`, `prepaid_balance`, `prepaid_account_id`, `monthly_type`, `lots_group`, `ticket_lpbind`, `inner_group`, `time_group`, `lot_name`, `prepaid_charge_rule`, `monthly_charge_rule`, `photo_id`, `owner_name`, `phone`, `email`, `addr`, `description`, `add_info1`, `add_info2`, `has_download`) VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), FROM_UNIXTIME(?), FROM_UNIXTIME(?), FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE id=VALUES(id), operate_type=VALUES(operate_type), ticket_type=VALUES(ticket_type), ticket=VALUES(ticket), plate=VALUES(plate), account_state=VALUES(account_state), parking_type=VALUES(parking_type), present_type=VALUES(present_type), in_time=VALUES(in_time), pay_time=VALUES(pay_time), inner_intime=VALUES(inner_intime), inner_outtime=VALUES(inner_outtime), insite=VALUES(insite), charge_site=VALUES(charge_site), inner_insite=VALUES(inner_insite), inner_outsite=VALUES(inner_outsite), coupon_total_time=VALUES(coupon_total_time), coupon_total_sum=VALUES(coupon_total_sum), limit_sum=VALUES(limit_sum), limit_time=VALUES(limit_time), paid_sum=VALUES(paid_sum), online_order=VALUES(online_order), hour_ticket_type=VALUES(hour_ticket_type), hour_ticket_num=VALUES(hour_ticket_num), charge_type=VALUES(charge_type), access_group=VALUES(access_group), start_time=VALUES(start_time), end_time=VALUES(online_order), prepaid_balance=VALUES(prepaid_balance), prepaid_account_id=VALUES(prepaid_account_id), monthly_type=VALUES(monthly_type), lots_group=VALUES(lots_group), ticket_lpbind=VALUES(ticket_lpbind), inner_group=VALUES(inner_group), time_group=VALUES(time_group), lot_name=VALUES(lot_name), prepaid_charge_rule=VALUES(prepaid_charge_rule), monthly_charge_rule=VALUES(monthly_charge_rule), photo_id=VALUES(photo_id), owner_name=VALUES(owner_name), phone=VALUES(phone), email=VALUES(email), addr=VALUES(addr), description=VALUES(description), add_info1=VALUES(add_info1), add_info2=VALUES(add_info2), has_download=VALUES(has_download)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4136;
        }
        if (!stmt)
        {
            return -4136;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4137;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_SHORT;
                bind[1].buffer= (char *)&operate_type;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&ticket_type;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(ticket);
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(plate);
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&account_state;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&parking_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&present_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&in_time;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&pay_time;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&inner_intime;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&inner_outtime;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&insite;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&charge_site;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&inner_insite;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* SHORT COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&inner_outsite;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&coupon_total_time;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&coupon_total_sum;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&limit_sum;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_LONG;
                bind[19].buffer= (char *)&limit_time;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&paid_sum;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* SHORT COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)&online_order;
                bind[21].buffer_length= 255;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(online_order);
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&hour_ticket_type;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_STRING;
                bind[23].buffer= (char *)&hour_ticket_num;
                bind[23].buffer_length= 20;
                bind[23].is_null= &is_null[23];
                length[23] = strlen(hour_ticket_num);
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&charge_type;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&access_group;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&start_time;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_LONG;
                bind[27].buffer= (char *)&end_time;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&prepaid_balance;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* SHORT COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_LONG;
                bind[29].buffer= (char *)&prepaid_account_id;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* SHORT COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_LONG;
                bind[30].buffer= (char *)&monthly_type;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* SHORT COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&lots_group;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&ticket_lpbind;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&inner_group;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&time_group;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_STRING;
                bind[35].buffer= (char *)&lot_name;
                bind[35].buffer_length= 50;
                bind[35].is_null= &is_null[35];
                length[35] = strlen(lot_name);
                bind[35].length= &length[35];

                /* SHORT COLUMN */
                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&prepaid_charge_rule;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                /* SHORT COLUMN */
                bind[37].buffer_type= MYSQL_TYPE_LONG;
                bind[37].buffer= (char *)&monthly_charge_rule;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37];

                /* SHORT COLUMN */
                bind[38].buffer_type= MYSQL_TYPE_STRING;
                bind[38].buffer= (char *)&photo_id;
                bind[38].buffer_length= 255;
                bind[38].is_null= &is_null[38];
                length[38] = strlen(photo_id);
                bind[38].length= &length[38];

                /* SHORT COLUMN */
                bind[39].buffer_type= MYSQL_TYPE_STRING;
                bind[39].buffer= (char *)&owner_name;
                bind[39].buffer_length= 20;
                bind[39].is_null= &is_null[39];
                length[39] = strlen(owner_name);
                bind[39].length= &length[39];

                /* SHORT COLUMN */
                bind[40].buffer_type= MYSQL_TYPE_STRING;
                bind[40].buffer= (char *)&phone;
                bind[40].buffer_length= 255;
                bind[40].is_null= &is_null[40];
                length[40] = strlen(phone);
                bind[40].length= &length[40];

                /* SHORT COLUMN */
                bind[41].buffer_type= MYSQL_TYPE_STRING;
                bind[41].buffer= (char *)&email;
                bind[41].buffer_length= 65;
                bind[41].is_null= &is_null[41];
                length[41] = strlen(email);
                bind[41].length= &length[41];

                /* SHORT COLUMN */
                bind[42].buffer_type= MYSQL_TYPE_STRING;
                bind[42].buffer= (char *)&addr;
                bind[42].buffer_length= 100;
                bind[42].is_null= &is_null[42];
                length[42] = strlen(addr);
                bind[42].length= &length[42];

                /* SHORT COLUMN */
                bind[43].buffer_type= MYSQL_TYPE_STRING;
                bind[43].buffer= (char *)&description;
                bind[43].buffer_length= 64;
                bind[43].is_null= &is_null[43];
                length[43] = strlen(description);
                bind[43].length= &length[43];

                /* SHORT COLUMN */
                bind[44].buffer_type= MYSQL_TYPE_STRING;
                bind[44].buffer= (char *)&add_info1;
                bind[44].buffer_length= 255;
                bind[44].is_null= &is_null[44];
                length[44] = strlen(add_info1);
                bind[44].length= &length[44];

                /* SHORT COLUMN */
                bind[45].buffer_type= MYSQL_TYPE_STRING;
                bind[45].buffer= (char *)&add_info2;
                bind[45].buffer_length= 255;
                bind[45].is_null= &is_null[45];
                length[45] = strlen(add_info2);
                bind[45].length= &length[45];

                /* SHORT COLUMN */
                bind[46].buffer_type= MYSQL_TYPE_SHORT;
                bind[46].buffer= (char *)&has_downloaded;
                bind[46].is_null= &is_null[46];
                bind[46].length= &length[46];
            }
            catch(...)
            {
                return -4161;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -4138;
            }
            if (stmt_bind_param)
            {
                return -4138;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4139;
            }
            if (param_count != 47)
            {
                return -4139;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4140;
            }
            if (stmt_execute)
            {
                return -4140;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -4141;
            }
            if (stmt_affected_rows == 1)
            {
                printf("Temp card is inserted\n");
            }
            else
            {
                printf("Temp card is updated\n");
            }
        }
        else
        {
            return -4137;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4142;
        }
    }
    else
    {
        return -4135;
    }
    return 0;
}

int temp_card::Delete_Temp_Account()
{
    try
    {
        operate_type = 0;
        ticket_type = 0;
        strcpy(ticket, "");
        strcpy(plate, "");
        account_state = 0;
        parking_type  = 0;
        present_type = 0;
        insite = 0;
        charge_site = 0;
        inner_insite = 0;
        inner_outsite = 0;
        coupon_total_time = 0;
        coupon_total_sum = 0;
        limit_sum = 0;
        paid_sum = 0;
        strcpy(online_order, "");
        hour_ticket_type = 0;
        strcpy(hour_ticket_num, "");
        charge_type = 0;
        access_group = 0;
        prepaid_balance = 0;
        prepaid_account_id = 0;
        monthly_type = 0;
        lots_group = 0;
        ticket_lpbind = 0;
        inner_group = 0;
        time_group = 0;
        strcpy(lot_name, "");
        prepaid_charge_rule = 0;
        monthly_charge_rule = 0;
        strcpy(photo_id, "");
        strcpy(owner_name, "");
        strcpy(phone, "");
        strcpy(email, "");
        strcpy(addr, "");
        strcpy(description, "");
        strcpy(add_info1, "");
        strcpy(add_info2, "");
        has_downloaded = 0;
        in_time = 0;
        pay_time = 0;
        inner_intime = 0;
        inner_outtime = 0;
        limit_time = 0;
        start_time = 0;
        end_time = 0;
    }
    catch(...)
    {
        return -4162;
    }
    short id_;
    std::string statment = "DELETE FROM `v32_tmp_cards_130000` WHERE `id`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4144;
        }
        if (!stmt)
        {
            return -4144;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4145;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type = MYSQL_TYPE_SHORT;
                bind_param[0].buffer = (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -4146;
            }
            if (stmt_bind_param)
            {
                return -4146;
            }
            id_ = id;
            int param_count = 0;
            try
            {
                mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4147;
            }
            if (param_count != 1)
            {
                return -4147;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4148;
            }
            if (stmt_execute)
            {
                return -4148;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -4149;
            }
            if (stmt_affected_rows < 1)
            {
                return -4149;
            }    
        }
        else
        {
            return -4145;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4150;
        }
    }
    else
    {
        return -4143;
    }
    id = 0;
    return 0;
    
}

int temp_card::Delete_All_Temp_Accounts()
{
    std::string statment = "DELETE FROM `v32_tmp_cards_130000`";
    if(mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4152;
        }
        if (!stmt)
        {
            return -4152;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4153;
        }
        if (!stmt_prepare)
        {    
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4154;
            }
            if (stmt_execute)
            {
                return -4154;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
                printf("Delete (%d) Records\n", stmt_affected_rows);
            }
            catch(...)
            {
                return -4155;
            }
            if (stmt_affected_rows < 1)
            {
                return -4155;
            }
        }
        else
        {
            return -4153;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4156;
        }
    }
    else
    {
        return -4151;
    }
    return 0;
}