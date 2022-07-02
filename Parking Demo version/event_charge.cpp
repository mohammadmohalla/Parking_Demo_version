#include "event_charge.h"

event_charge::event_charge(MYSQL *_mysql)
{
    mysql = _mysql;
}

event_charge::~event_charge()
{
    
}

int event_charge::print_charge_event()
{
    try
    {
        printf("%ld %d %ld %d %d %d %d %ld %ld %d %ld %d %s %d %s %s %s %s %d %s %d %d %d %d %d %d %ld %d %d %d %d %d %d %d %s %s\n",
                aid,
                gid,
                charge_time,
                charge_serial,
                actually_pay,
                charge_type,
                payment_type,
                start_time,
                end_time,
                in_serial,
                in_time,
                isnotup,
                ticket,
                ticket_type,
                plate,
                online_member_id,
                order_num,
                other_order_num,
                park_duration,
                photo_id,
                should_pay,
                site,
                group_prepaid_serial,
                balance,
                coupon_type,
                _operator,
                rece_time,
                reserve_state,
                warn,
                pcode,
                invoiced,
                tpid,
                coupon_out_id,
                lotid,
                phone,
                owner_name
            );
    }
    catch(...)
    {
        return -3462;
    }
    return 0;
}

int event_charge::Select_charge_event_by_id(int index)
{
    int id_;
    std::string statment = "SELECT *,UNIX_TIMESTAMP(charge_time),UNIX_TIMESTAMP(start_time),UNIX_TIMESTAMP(end_time),UNIX_TIMESTAMP(in_time),UNIX_TIMESTAMP(rece_time) FROM v32_event_charge WHERE aid=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3402;
        }
        if (!stmt)
        {
            return -3402;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3403;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = 0;
            try
            {
                memset(bind_param, 0, sizeof(bind));

                bind_param[0].buffer_type = MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3404;
            }
            if (stmt_bind_param)
            {
                return -3404;
            }
            
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3405;
            }
            if (param_count != 1)
            {
                return -3405;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3406;
            }
            if (!prepare_meta_result)
            {
                return -3406;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3407;
            }
            if (column_count != 41) /* validate column count */
            {
                return -3407;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3408;
            }
            if (stmt_execute)
            {
                return -3408;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&charge_time;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&charge_serial;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&actually_pay;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&charge_type;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&payment_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[37].buffer_type= MYSQL_TYPE_LONG;
                bind[37].buffer= (char *)&start_time;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37];

                /* SHORT COLUMN */
                bind[38].buffer_type= MYSQL_TYPE_LONG;
                bind[38].buffer= (char *)&end_time;
                bind[38].is_null= &is_null[38];
                bind[38].length= &length[38];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&in_serial;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[39].buffer_type= MYSQL_TYPE_LONG;
                bind[39].buffer= (char *)&in_time;
                bind[39].is_null= &is_null[39];
                bind[39].length= &length[39];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&isnotup;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)ticket;
                bind[12].buffer_length= 20;
                bind[12].is_null= &is_null[12];
                length[12] = strlen(ticket);
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&ticket_type;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)plate;
                bind[14].buffer_length= 12;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(plate);
                bind[14].length= &length[14];

                /* SHORT COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)online_member_id;
                bind[15].buffer_length= 22;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(online_member_id);
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)order_num;
                bind[16].buffer_length= 255;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(order_num);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)other_order_num;
                bind[17].buffer_length= 255;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(other_order_num);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&park_duration;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_STRING;
                bind[19].buffer= (char *)photo_id;
                bind[19].buffer_length= 64;
                bind[19].is_null= &is_null[19];
                length[19] = strlen(photo_id);
                bind[19].length= &length[19];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&should_pay;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                 /* SHORT COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_SHORT;
                bind[21].buffer= (char *)&site;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&group_prepaid_serial;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&balance;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&coupon_type;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&_operator;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[40].buffer_type= MYSQL_TYPE_LONG;
                bind[40].buffer= (char *)&rece_time;
                bind[40].is_null= &is_null[40];
                bind[40].length= &length[40];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_SHORT;
                bind[27].buffer= (char *)&reserve_state;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_SHORT;
                bind[28].buffer= (char *)&warn;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* SHORT COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_SHORT;
                bind[29].buffer= (char *)&pcode;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* SHORT COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_SHORT;
                bind[30].buffer= (char *)&invoiced;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* SHORT COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&tpid;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&coupon_out_id;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&lotid;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_STRING;
                bind[34].buffer= (char *)phone;
                bind[34].buffer_length= 12;
                bind[34].is_null= &is_null[34];
                length[34] = strlen(phone);
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_STRING;
                bind[35].buffer= (char *)owner_name;
                bind[35].buffer_length= 20;
                bind[35].is_null= &is_null[35];
                length[35] = strlen(owner_name);
                bind[35].length= &length[35];
            }
            catch(...)
            {
                return -3463;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3409;
            }
            if (stmt_bind_result)
            {
                return -3409;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3410;
            }
            if (stmt_store_result)
            {
                return -3410;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3411;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3412;
            }
        }
        else
        {
            return -3403;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3413;
        }
    }
    else
    {
        return -3401;
    }
    return 0;
}

int event_charge::Select_charge_event_by_ticket(std::string _ticket)
{
    char ticket_[20];
    std::string statment = "SELECT *,UNIX_TIMESTAMP(charge_time),UNIX_TIMESTAMP(start_time),UNIX_TIMESTAMP(end_time),UNIX_TIMESTAMP(in_time),UNIX_TIMESTAMP(rece_time) FROM v32_event_charge WHERE ticket=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3415;
        }
        if (!stmt)
        {
            return -3415;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3416;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));

                bind_param[0].buffer_type= MYSQL_TYPE_STRING;
                bind_param[0].buffer= (char *)ticket_;
                bind_param[0].buffer_length= strlen(_ticket.c_str());
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3417;
            }
            if (stmt_bind_param)
            {
                return -3417;
            }
            int param_count = 0;
            try
            {
                strcpy(ticket_, _ticket.c_str());
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3418;
            }
            if (param_count != 1)
            {
                return -3418;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3419;
            }
            if (!prepare_meta_result)
            {
                return -3419;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3420;
            }
            if (column_count != 41)
            {
                return -3420;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3421;
            }
            if (stmt_execute)
            {
                return -3421;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&charge_time;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&charge_serial;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&actually_pay;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&charge_type;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&payment_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[37].buffer_type= MYSQL_TYPE_LONG;
                bind[37].buffer= (char *)&start_time;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37];

                /* SHORT COLUMN */
                bind[38].buffer_type= MYSQL_TYPE_LONG;
                bind[38].buffer= (char *)&end_time;
                bind[38].is_null= &is_null[38];
                bind[38].length= &length[38];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&in_serial;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[39].buffer_type= MYSQL_TYPE_LONG;
                bind[39].buffer= (char *)&in_time;
                bind[39].is_null= &is_null[39];
                bind[39].length= &length[39];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&isnotup;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)ticket;
                bind[12].buffer_length= 20;
                bind[12].is_null= &is_null[12];
                length[12] = strlen(ticket);
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&ticket_type;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)plate;
                bind[14].buffer_length= 12;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(plate);
                bind[14].length= &length[14];

                /* SHORT COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)online_member_id;
                bind[15].buffer_length= 22;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(online_member_id);
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)order_num;
                bind[16].buffer_length= 255;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(order_num);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)other_order_num;
                bind[17].buffer_length= 255;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(other_order_num);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&park_duration;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_STRING;
                bind[19].buffer= (char *)photo_id;
                bind[19].buffer_length= 64;
                bind[19].is_null= &is_null[19];
                length[19] = strlen(photo_id);
                bind[19].length= &length[19];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&should_pay;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* SHORT COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_SHORT;
                bind[21].buffer= (char *)&site;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&group_prepaid_serial;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&balance;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&coupon_type;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&_operator;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[40].buffer_type= MYSQL_TYPE_LONG;
                bind[40].buffer= (char *)&rece_time;
                bind[40].is_null= &is_null[40];
                bind[40].length= &length[40];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_SHORT;
                bind[27].buffer= (char *)&reserve_state;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_SHORT;
                bind[28].buffer= (char *)&warn;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* SHORT COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_SHORT;
                bind[29].buffer= (char *)&pcode;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* SHORT COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_SHORT;
                bind[30].buffer= (char *)&invoiced;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* SHORT COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&tpid;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&coupon_out_id;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&lotid;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_STRING;
                bind[34].buffer= (char *)phone;
                bind[34].buffer_length= 12;
                bind[34].is_null= &is_null[34];
                length[34] = strlen(phone);
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_STRING;
                bind[35].buffer= (char *)owner_name;
                bind[35].buffer_length= 20;
                bind[35].is_null= &is_null[35];
                length[35] = strlen(owner_name);
                bind[35].length= &length[35];
            }
            catch(...)
            {
                return -3464;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3422;
            }
            if (stmt_bind_result)
            {
                return -3422;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3423;
            }
            if (stmt_store_result)
            {
                return -3423;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3424;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3425;
            }
        }
        else
        {
            return -3416;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3426;
        }
    }
    else
    {
        return -3414;
    }
    return 0;
}

int event_charge::Select_charge_event_by_plate(std::string curr_plate, int match_plate)
{
    char plate_[12];
    std::string statment = "SELECT *,UNIX_TIMESTAMP(charge_time),UNIX_TIMESTAMP(start_time),UNIX_TIMESTAMP(end_time),UNIX_TIMESTAMP(in_time),UNIX_TIMESTAMP(rece_time) FROM v32_event_charge WHERE SUBSTR(plate,1," + std::to_string(match_plate) +")=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3428;
        }
        if (!stmt)
        {
            return -3428;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3429;
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
                return -3430;
            }
            if (stmt_bind_param)
            {
                return -3430;
            }
            int param_count = 0;
            try
            {
                strncpy( plate_, curr_plate.c_str(), match_plate);
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3431;
            }
            if (param_count != 1)
            {
                return -3431;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3432;
            }
            if (!prepare_meta_result)
            {
                return -3432;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3433;
            }
            if (column_count != 41)
            {
                return -3433;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3434;
            }
            if(stmt_execute)
            {
                return -3434;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&charge_time;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&charge_serial;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&actually_pay;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&charge_type;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&payment_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[37].buffer_type= MYSQL_TYPE_LONG;
                bind[37].buffer= (char *)&start_time;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37];

                /* SHORT COLUMN */
                bind[38].buffer_type= MYSQL_TYPE_LONG;
                bind[38].buffer= (char *)&end_time;
                bind[38].is_null= &is_null[38];
                bind[38].length= &length[38];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&in_serial;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[39].buffer_type= MYSQL_TYPE_LONG;
                bind[39].buffer= (char *)&in_time;
                bind[39].is_null= &is_null[39];
                bind[39].length= &length[39];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&isnotup;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)ticket;
                bind[12].buffer_length= 20;
                bind[12].is_null= &is_null[12];
                length[12] = strlen(ticket);
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&ticket_type;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)plate;
                bind[14].buffer_length= 12;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(plate);
                bind[14].length= &length[14];

                /* SHORT COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)online_member_id;
                bind[15].buffer_length= 22;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(online_member_id);
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)order_num;
                bind[16].buffer_length= 255;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(order_num);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)other_order_num;
                bind[17].buffer_length= 255;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(other_order_num);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&park_duration;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_STRING;
                bind[19].buffer= (char *)photo_id;
                bind[19].buffer_length= 64;
                bind[19].is_null= &is_null[19];
                length[19] = strlen(photo_id);
                bind[19].length= &length[19];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&should_pay;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                 /* SHORT COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_SHORT;
                bind[21].buffer= (char *)&site;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&group_prepaid_serial;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&balance;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&coupon_type;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&_operator;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[40].buffer_type= MYSQL_TYPE_LONG;
                bind[40].buffer= (char *)&rece_time;
                bind[40].is_null= &is_null[40];
                bind[40].length= &length[40];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_SHORT;
                bind[27].buffer= (char *)&reserve_state;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_SHORT;
                bind[28].buffer= (char *)&warn;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* SHORT COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_SHORT;
                bind[29].buffer= (char *)&pcode;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* SHORT COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_SHORT;
                bind[30].buffer= (char *)&invoiced;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* SHORT COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&tpid;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&coupon_out_id;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&lotid;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_STRING;
                bind[34].buffer= (char *)phone;
                bind[34].buffer_length= 12;
                bind[34].is_null= &is_null[34];
                length[34] = strlen(phone);
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_STRING;
                bind[35].buffer= (char *)owner_name;
                bind[35].buffer_length= 20;
                bind[35].is_null= &is_null[35];
                length[35] = strlen(owner_name);
                bind[35].length= &length[35];
            }
            catch(...)
            {
                return -3465;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3435;
            }
            if (stmt_bind_result)
            {
                return -3435;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3436;
            }
            if (stmt_store_result)
            {
                return -3436;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3437;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3438;
            }
        }
        else
        {
            return -3429;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3439;
        }
    }
    else
    {
        return -3427;
    }
    return 0;
}

int event_charge::Insert_update_charge_event()
{
    std::string statment = "INSERT INTO `v32_event_charge` (`aid`, `gid`, `charge_time`, `charge_serial`, `actually_pay`, `charge_type`, `payment_type`, `start_time`, `end_time`, `in_serial`, `in_time`, `isnotup`, `ticket`, `ticket_type`, `plate`, `online_member_id`, `order_num`, `other_order_num`, `park_duration`, `photo_id`, `should_pay`, `site`, `group_prepaid_serial`, `balance`, `coupon_type`, `operator`, `rece_time`, `reserve_state`, `warn`, `pcode`, `invoiced`, `tpid`, `coupon_out_id`, `lotid`, `phone`, `owner_name`) VALUES (?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?, FROM_UNIXTIME(?), FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE aid=VALUES(aid), gid=VALUES(gid), charge_time=VALUES(charge_time), charge_serial=VALUES(charge_serial), actually_pay=VALUES(actually_pay), charge_type=VALUES(charge_type), payment_type=VALUES(payment_type), start_time=VALUES(start_time), end_time=VALUES(end_time), in_serial=VALUES(in_serial), in_time=VALUES(in_time), isnotup=VALUES(isnotup), ticket=VALUES(ticket), ticket_type=VALUES(ticket_type), plate=VALUES(plate), online_member_id=VALUES(online_member_id), order_num=VALUES(order_num), other_order_num=VALUES(other_order_num), park_duration=VALUES(park_duration), photo_id=VALUES(photo_id), should_pay=VALUES(should_pay), site=VALUES(site), group_prepaid_serial=VALUES(group_prepaid_serial), balance=VALUES(balance), coupon_type=VALUES(coupon_type), operator=VALUES(operator), rece_time=VALUES(rece_time), reserve_state=VALUES(reserve_state), warn=VALUES(warn), pcode=VALUES(pcode), invoiced=VALUES(invoiced), tpid=VALUES(tpid),  coupon_out_id=VALUES(coupon_out_id),  lotid=VALUES(lotid), phone=VALUES(phone), owner_name=VALUES(owner_name)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3441;
        }
        if (!stmt)
        {
            return -3441;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3442;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&charge_time;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&charge_serial;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&actually_pay;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&charge_type;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&payment_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&start_time;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&end_time;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&in_serial;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&in_time;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&isnotup;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)ticket;
                bind[12].buffer_length= 20;
                bind[12].is_null= &is_null[12];
                length[12] = strlen(ticket);
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&ticket_type;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)plate;
                bind[14].buffer_length= 12;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(plate);
                bind[14].length= &length[14];

                /* SHORT COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)online_member_id;
                bind[15].buffer_length= 22;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(online_member_id);
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)order_num;
                bind[16].buffer_length= 255;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(order_num);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)other_order_num;
                bind[17].buffer_length= 255;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(other_order_num);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&park_duration;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_STRING;
                bind[19].buffer= (char *)photo_id;
                bind[19].buffer_length= 64;
                bind[19].is_null= &is_null[19];
                length[19] = strlen(photo_id);
                bind[19].length= &length[19];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&should_pay;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                 /* SHORT COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_SHORT;
                bind[21].buffer= (char *)&site;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&group_prepaid_serial;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&balance;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&coupon_type;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&_operator;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&rece_time;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_SHORT;
                bind[27].buffer= (char *)&reserve_state;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_SHORT;
                bind[28].buffer= (char *)&warn;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* SHORT COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_SHORT;
                bind[29].buffer= (char *)&pcode;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* SHORT COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_SHORT;
                bind[30].buffer= (char *)&invoiced;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* SHORT COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&tpid;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&coupon_out_id;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&lotid;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_STRING;
                bind[34].buffer= (char *)phone;
                bind[34].buffer_length= 12;
                bind[34].is_null= &is_null[34];
                length[34] = strlen(phone);
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_STRING;
                bind[35].buffer = (char *)owner_name;
                bind[35].buffer_length= 20;
                bind[35].is_null= &is_null[35];
                length[35] = strlen(owner_name);
                bind[35].length= &length[35];
            }
            catch(...)
            {
                return -3466;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -3443;
            }
            if (stmt_bind_param)
            {
                return -3443;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3444;
            }
            if (param_count != 36) /* validate parameter count */
            {
                return -3444;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3445;
            }
            if (stmt_execute)
            {
                return -3445;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3446;
            }
            if (stmt_affected_rows == 1)
            {
                printf("event charge is inserted\n");
            }
            else
            {
                printf("event charge is updated\n");
            }
        }
        else
        {
            return -3442;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3447;
        }
    }
    else
    {
        return -3440;
    }
    return 0;
    
}

int event_charge::Delete_charge_event()
{
    try
    {
        gid = 13000;
        charge_serial = 0;
        actually_pay = 0;
        charge_type = 255;
        payment_type = 255;
        in_serial = 0;
        isnotup = 0;
        strcpy(ticket, "");
        ticket_type = 0;
        strcpy(plate, "");
        strcpy(online_member_id,"");
        strcpy(order_num, "");
        strcpy(other_order_num, "");
        park_duration = 0;
        strcpy(photo_id, "");
        should_pay = 0;
        site = 255;
        group_prepaid_serial = 65535;
        balance = 0;
        coupon_type = 0;
        _operator = 0;
        reserve_state = 0;
        warn = 0;
        pcode = 0;
        invoiced = 0;
        tpid = 65535;
        coupon_out_id = 0;
        lotid = 0;
        strcpy(phone, "");
        strcpy(owner_name,"");
        time_t charge_time = 0;
        time_t start_time = 0;
        time_t end_time = 0;
        time_t in_time = 0;
        time_t rece_time = 0;
    }
    catch(...)
    {
        return -3467;
    }
    
    int id_;
    std::string statment = "DELETE FROM `v32_event_charge` WHERE `aid`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3449;
        }
        if (!stmt)
        {
            return -3449;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3450;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type = MYSQL_TYPE_LONG;
                bind_param[0].buffer = (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3451;
            }
            if (stmt_bind_param)
            {
                return -3451;
            }
            id_ = aid;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3452;
            }
            if (param_count != 1)
            {
                return -3452;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3453;
            }
            if (stmt_execute)
            {
                return -3453;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3454;
            }
            if (stmt_affected_rows < 1)
            {
                return -3454;
            }
        }
        else
        {
            return -3450;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3455;
        }
    }
    else
    {
        return -3448;
    }
    aid = 0;
    return 0;
    
}

int event_charge::Delete_All_charge_Events()
{
    std::string statment = "DELETE FROM `v32_event_charge`";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3457;
        }
        if (!stmt)
        {
            return -3457;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3458;
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
                return -3459;
            }
            if (stmt_execute)
            {
                return -3459;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3460;
            }
            if (stmt_affected_rows < 1)
            {
                return -3460;
            }
        }
        else
        {
            return -3458;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3461;
        }
    }
    else
    {
        return -3456;
    }
    return 0;
}