#include "event_out.h"

event_out::event_out(MYSQL *_mysql)
{
    mysql = _mysql;
}

event_out::~event_out()
{
    
}

int event_out::print_event_out()
{
    try
    {
        printf("%ld %d %ld %d %d %ld %s %d %s %d %ld %d %d %d %d %d %d %d %d %s %s %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
            aid,
            gid,
            out_time,
            out_serial,
            out_type,
            rece_time,
            ticket,
            ticket_type,
            plate,
            total_paid,
            in_time,
            in_serial,
            total_lots,
            monthly_lots,
            hourly_lots,
            free_total_lots,
            free_monthly_lots,
            free_hourly_lots,
            site,
            order_num,
            photo_id,
            isnotup,
            lots_group_id,
            lots_group_occupied,
            park_duration,
            _operator,
            total_should,
            coupon_total_sum,
            coupon_total_time,
            coupon_real_sum,
            coupon_real_time,
            charge_type,
            lotID,
            monthlyType
            );
    }
    catch(...)
    {
        return -3236;
    }
    return 0;
}

int event_out::Select_exit_event_by_id(int index)
{
    int id_;
    std::string statment = "SELECT *,UNIX_TIMESTAMP(out_time),UNIX_TIMESTAMP(rece_time),UNIX_TIMESTAMP(in_time) FROM v32_event_out WHERE aid=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3202;
        }
        if (!stmt)
        {
            return -3202;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3203;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3204;
            }
            if (stmt_bind_param)
            {
                return -3204;
            }
            
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3205;
            }
            if (param_count != 1)
            {
                return -3205;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3206;
            }
            if (!prepare_meta_result)
            {
                return -3206;
            }
            
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3207;
            }
            if (column_count != 37) /* validate column count */
            {
                return -3207;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3208;
            }
            if(stmt_execute)
            {
                return -3208;
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

                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&out_time;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&out_serial;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&out_type;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_LONG;
                bind[35].buffer= (char *)&rece_time;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_STRING;
                bind[6].buffer= (char *)ticket;
                bind[6].buffer_length= 20;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&ticket_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_STRING;
                bind[8].buffer= (char *)plate;
                bind[8].buffer_length= 12;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&total_paid;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&in_time;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&in_serial;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&total_lots;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&monthly_lots;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&hourly_lots;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&free_total_lots;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* STRING COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&free_monthly_lots;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* INTEGER COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&free_hourly_lots;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_SHORT;
                bind[18].buffer= (char *)&site;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_STRING;
                bind[19].buffer= (char *)order_num;
                bind[19].buffer_length= 22;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_STRING;
                bind[20].buffer= (char *)photo_id;
                bind[20].buffer_length= 64;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_SHORT;
                bind[21].buffer= (char *)&isnotup;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* TIMESTAMP COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&lots_group_id;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&lots_group_occupied;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&park_duration;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&_operator;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&total_should;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_LONG;
                bind[27].buffer= (char *)&coupon_total_sum;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];


                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&coupon_total_time;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];


                /* SHORT COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_LONG;
                bind[29].buffer= (char *)&coupon_real_sum;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];


                /* SHORT COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_LONG;
                bind[30].buffer= (char *)&coupon_real_time;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];


                /* SHORT COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&charge_type;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];


                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&lotID;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];


                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_SHORT;
                bind[33].buffer= (char *)&monthlyType;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];
            }
            catch(...)
            {
                return -3237;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3209;
            }
            if (stmt_bind_result)
            {
                return -3209;
            }
            bool stmt_store_result = true;
            
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3210;
            }
            if (stmt_store_result)
            {
                return -3210;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3211;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3212;
            }
        }
        else
        {
            return -3203;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3213;
        }
    }
    else
    {
        return -3201;
    }
    return 0;
}

int event_out::Insert_exit_event()
{
    std::string statment = "INSERT INTO `v32_event_out` (`aid`, `gid`, `out_time`, `out_serial`, `out_type`, `rece_time`, `ticket`, `ticket_type`, `plate`, `total_paid`, `in_time`, `in_serial`, `total_lots`, `monthly_lots`, `hourly_lots`, `free_total_lots`, `free_monthly_lots`, `free_hourly_lots`, `site`, `order_num`, `photo_id`, `isnotup`, `lots_group_id`, `lots_group_occupied`, `park_duration`, `operator`, `total_should`, `coupon_total_sum`, `coupon_total_time`, `coupon_real_sum`, `coupon_real_time`, `charge_type`, `lotid`, `monthly_type`) VALUES ( ?, ?, FROM_UNIXTIME(?), ?, ?,FROM_UNIXTIME(?), ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3215;
        }
        if (!stmt)
        {
            return -3215;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3216;
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
                bind[2].buffer= (char *)&out_time;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&out_serial;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&out_type;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&rece_time;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_STRING;
                bind[6].buffer= (char *)ticket;
                bind[6].buffer_length= 20;
                bind[6].is_null= &is_null[6];
                length[6] = strlen(ticket);
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&ticket_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_STRING;
                bind[8].buffer= (char *)plate;
                bind[8].buffer_length= 12;
                bind[8].is_null= &is_null[8];
                length[8] = strlen(plate);
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&total_paid;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&in_time;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&in_serial;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&total_lots;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&monthly_lots;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&hourly_lots;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&free_total_lots;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* STRING COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&free_monthly_lots;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* INTEGER COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&free_hourly_lots;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_SHORT;
                bind[18].buffer= (char *)&site;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_STRING;
                bind[19].buffer= (char *)order_num;
                bind[19].buffer_length= 22;
                bind[19].is_null= &is_null[19];
                length[19] = strlen(order_num);
                bind[19].length= &length[19];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_STRING;
                bind[20].buffer= (char *)photo_id;
                bind[20].buffer_length= 64;
                bind[20].is_null= &is_null[20];
                length[20] = strlen(photo_id);
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_SHORT;
                bind[21].buffer= (char *)&isnotup;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* TIMESTAMP COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&lots_group_id;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&lots_group_occupied;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&park_duration;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&_operator;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&total_should;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_LONG;
                bind[27].buffer= (char *)&coupon_total_sum;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];


                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&coupon_total_time;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];


                /* SHORT COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_LONG;
                bind[29].buffer= (char *)&coupon_real_sum;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];


                /* SHORT COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_LONG;
                bind[30].buffer= (char *)&coupon_real_time;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];


                /* SHORT COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&charge_type;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];


                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&lotID;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];


                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_SHORT;
                bind[33].buffer= (char *)&monthlyType;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];
            }
            catch(...)
            {
                return -3238;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -3217;
            }
            if (stmt_bind_param)
            {
                return -3217;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3218;
            }
            if (param_count != 34)
            {
                return -3218;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3219;
            }
            if (stmt_execute)
            {
                return -3219;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3220;
            }
            if (stmt_affected_rows != 1)
            {
                return -3220;
            }
        }
        else
        {
            return -3216;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3221;
        }
    }
    else
    {
        return -3214;
    }
    return 0;
}

int event_out::Delete_Exit_event()
{
    try
    {
        gid = 13000;
        _operator = 0;
        out_serial = 0;
        out_type = 0;
        strcpy(ticket, "");
        ticket_type = 0;
        strcpy(plate, "");
        total_paid = 0;
        in_serial = 0;
        total_lots = 0;
        monthly_lots = 0;
        hourly_lots = 0;
        free_total_lots = 0;
        free_monthly_lots = 0;
        free_hourly_lots = 0;
        site = 0;
        strcpy(order_num, "");
        strcpy(photo_id, "");
        isnotup = 0;
        lots_group_id = 65535;
        lots_group_occupied = 0;
        park_duration = 0;
        total_should = 0;
        coupon_total_sum = 0;
        coupon_total_time = 0;
        coupon_real_sum = 0;
        coupon_real_time = 0;
        charge_type = 0;
        lotID = 0;
        monthlyType = 255;



        out_time = 0;
        in_time = 0;
        rece_time = 0;
    }
    catch(...)
    {
        return -3239;
    }
    long id_;
    std::string statment = "DELETE FROM `v32_event_out` WHERE `aid`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3223;
        }
        if (!stmt)
        {
            return -3223;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3224;
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
                return -3225;
            }
            if (stmt_bind_param)
            {
                return -3225;
            }
            id_ = aid;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3226;
            }
            if (param_count != 1)
            {
                return -3226;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3227;
            }
            if (stmt_execute)
            {
                return -3227;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3228;
            }
            if (stmt_affected_rows < 1)
            {
                return -3228;
            }    
        }
        else
        {
            return -3224;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3229;
        }
    }
    else
    {
        return -3222;
    }
    aid = 0;
    return true;
    
}

int event_out::Delete_All_Exit_Events()
{
    std::string statment = "DELETE FROM `v32_event_out`";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3231;
        }
        if (!stmt)
        {
            return -3231;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3232;
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
                return -3233;
            }
            if (stmt_execute)
            {
                return -3233;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3234;
            }
            if (stmt_affected_rows < 1)
            {
                return -3234;
            }    
        }
        else
        {
            return -3232;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3235;
        }
    }
    else
    {
        return -3230;
    }
    return 0;
}