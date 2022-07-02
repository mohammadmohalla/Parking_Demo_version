#include "event_in.h"

event_in::event_in(MYSQL *_mysql)
{
    mysql = _mysql;
}

event_in::~event_in()
{
    
}

int event_in::print_event_in()
{
    try
    {
        printf("%ld %d %ld %d %ld %d %s %d %s %d %d %d %d %d %d %d %ld %s %s %d %d %d %d %d %d\n",
            aid,
            gid,
            inTime,
            inSerial,
            receTime,
            inType,
            ticket,
            ticketType,
            plate,
            totalLots,
            monthlyLots,
            hourlyLots,
            freeTotalLots,
            freeMonthlyLots,
            freeHourlyLots,
            site,
            realIntime,
            orderNum,
            photoID,
            isNotUp,
            lotsGroupId,
            lotsGroupUsed,
            _operator,
            lotID,
            monthlyType);
    }
    catch(...)
    {
        return -3136;
    }
    return 0;
}

int event_in::Select_entry_event_by_id(int index)
{
    short id_;
    std::string statment = "SELECT *,UNIX_TIMESTAMP(in_time),UNIX_TIMESTAMP(rece_time),UNIX_TIMESTAMP(real_intime) FROM v32_event_in WHERE aid=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3102;
        }
        if (!stmt)
        {
            return -3102;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3103;
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
                return -3104;
            }
            if (stmt_bind_param)
            {
                return -3104;
            }
            
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3105;
            }
            if (param_count != 1)
            {
                return -3105;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3106;
            }
            if (!prepare_meta_result)
            {
                return -3106;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3107;
            }
            if (column_count != 28) /* validate column count */
            {
                return -3107;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3108;
            }
            if (stmt_execute)
            {
                return -3108;
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

                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&inTime;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&inSerial;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&receTime;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&inType;
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
                bind[7].buffer= (char *)&ticketType;
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
                bind[9].buffer= (char *)&totalLots;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&monthlyLots;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&hourlyLots;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&freeTotalLots;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&freeMonthlyLots;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&freeHourlyLots;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_SHORT;
                bind[15].buffer= (char *)&site;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_LONG;
                bind[27].buffer= (char *)&realIntime;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)orderNum;
                bind[17].buffer_length= 22;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(orderNum);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_STRING;
                bind[18].buffer= (char *)photoID;
                bind[18].buffer_length= 64;
                bind[18].is_null= &is_null[18];
                length[18] = strlen(photoID);
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&isNotUp;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&lotsGroupId;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_LONG;
                bind[21].buffer= (char *)&lotsGroupUsed;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&_operator;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&lotID;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_SHORT;
                bind[24].buffer= (char *)&monthlyType;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];
            }
            catch(...)
            {
                return -3137;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3109;
            }
            if (stmt_bind_result)
            {
                return -3109;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3110;
            }
            if (stmt_store_result)
            {
                return -3110;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3111;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3112;
            }
        }
        else
        {
            return -3103;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3113;
        }
    }
    else
    {
        return -3101;
    }
    return 0;
}

int event_in::Insert_entry_event()
{
    std::string statment = "INSERT INTO `v32_event_in` (`aid`, `gid`, `in_time`, `in_serial`, `rece_time`, `in_type`, `ticket`, `ticket_type`, `plate`, `total_lots`, `monthly_lots`, `hourly_lots`, `free_total_lots`, `free_monthly_lots`, `free_hourly_lots`, `site`, `real_intime`, `order_num`, `photo_id`, `isnotup`, `lots_group_id`, `lots_group_used`, `operator`, `lotid`, `monthly_type`) VALUES ( ?, ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3115;
        }
        if (!stmt)
        {
            return -3115;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3116;
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
                bind[2].buffer= (char *)&inTime;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&inSerial;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&receTime;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&inType;
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
                bind[7].buffer= (char *)&ticketType;
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
                bind[9].buffer= (char *)&totalLots;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&monthlyLots;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&hourlyLots;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&freeTotalLots;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&freeMonthlyLots;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&freeHourlyLots;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_SHORT;
                bind[15].buffer= (char *)&site;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&realIntime;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)orderNum;
                bind[17].buffer_length= 22;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(orderNum);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_STRING;
                bind[18].buffer= (char *)photoID;
                bind[18].buffer_length= 64;
                bind[18].is_null= &is_null[18];
                length[18] = strlen(photoID);
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&isNotUp;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&lotsGroupId;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_LONG;
                bind[21].buffer= (char *)&lotsGroupUsed;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&_operator;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&lotID;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_SHORT;
                bind[24].buffer= (char *)&monthlyType;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];
            }
            catch(...)
            {
                return -3138;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -3117;
            }
            if (stmt_bind_param)
            {
                return -3117;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3118;
            }
            if (param_count != 25)
            {
                return -3118;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3119;
            }
            if (stmt_execute)
            {
                return -3119;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3120;
            }
            if (stmt_affected_rows != 1)
            {
                return -3120;
            }
        }
        else
        {
            return -3116;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3121;
        }
    }
    else
    {
        return -3114;
    }
    return 0;
}

int event_in::Delete_Entry_event()
{
    try
    {
        gid = 0;
        _operator = 0;
        inSerial = 0;
        inType = 0;
        strcpy(ticket, "");
        ticketType = 0;
        strcpy(plate, "");
        totalLots = 0;
        monthlyLots = 0;
        hourlyLots = 0;
        freeTotalLots = 0;
        freeMonthlyLots = 0;
        freeHourlyLots = 0;
        site = 0;
        strcpy(orderNum, "");
        strcpy(photoID, "");
        isNotUp = 0;
        lotsGroupId = 65535;
        lotsGroupUsed = 0;
        lotID = 0;
        monthlyType = 255;
        inTime = 0;
        receTime = 0;
        realIntime = 0;
    }
    catch(...)
    {
        return -3139;
    }
    short id_;
    std::string statment = "DELETE FROM `v32_event_in` WHERE `aid`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3123;
        }
        if (!stmt)
        {
            return -3123;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3124;
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
                return -3125;
            }
            if (stmt_bind_param)
            {
                return -3125;
            }
            id_ = aid;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3126;
            }
            if (param_count != 1)
            {
                return -3126;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3127;
            }
            if (stmt_execute)
            {
                return -3127;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3128;
            }
            if (stmt_affected_rows < 1)
            {
                return -3128;
            }    
        }
        else
        {
            return -3124;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3129;
        }
    }
    else
    {
        return -3122;
    }
    aid = 0;
    return 0;
}

int event_in::Delete_All_Entry_Events()
{
    std::string statment = "DELETE FROM `v32_event_in`";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3131;
        }
        if (!stmt)
        {
            return -3131;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3132;
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
                return -3133;
            }
            if (stmt_execute)
            {
                return -3133;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3134;
            }
            if (stmt_affected_rows < 1)
            {
                return -3134;
            }    
        }
        else
        {
            return -3132;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3135;
        }
    }
    else
    {
        return -3130;
    }
    return 0;
}