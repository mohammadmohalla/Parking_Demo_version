#include "rule_step_hourly.h"

rule_step_hourly_type::rule_step_hourly_type(MYSQL *_mysql)
{
    mysql = _mysql;
    memset(bind_param, 0, sizeof(bind));
    memset(bind, 0, sizeof(bind));
    memset(is_null, 0, sizeof(is_null));
    memset(length, 0, sizeof(length));
}

rule_step_hourly_type::~rule_step_hourly_type()
{
    
}

int rule_step_hourly_type::print_rule_step_hourly_type()
{
    try
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%ld\t%ld\t%d\t%d\t%s\t%d\t%d\t%d\t%d", 
            rule_serial,
            block_serial,
            type,
            cross_period,
            deduct, 
            duration, 
            starttime,
            endtime, 
            max_sum,
            relation, 
            reserve,  
            is_integer, 
            sum, 
            next_serial, 
            flag);
    }
    catch(...)
    {
        return -2238;
    }
    return 0;
}

int rule_step_hourly_type::Select_rule_step_hourly_type_by_rule_block_serial(int _rule_serial, int _block_serial)
{
    int r_serial, b_serial;
    std::string statment = "SELECT * ,Unix_Timestamp(starttime),Unix_Timestamp(endtime),Unix_Timestamp(createtime) FROM v32_rule_step_hourly WHERE rule_serial = ? and block_serial = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2202;
        }
        if (!stmt)
        {
            return -2202;
        }
        
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2203;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&r_serial;
                bind_param[1].buffer_type= MYSQL_TYPE_LONG;
                bind_param[1].buffer= (char *)&b_serial;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2204;
            }
            if (stmt_bind_param)
            {
                return -2204;
            }
            int param_count = 0;
            try
            {
                r_serial = _rule_serial;
                b_serial = _block_serial;
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2205;
            }
            if (param_count != 2)
            {
                return -2205;
            }

            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -2206;
            }
            if (!prepare_meta_result)
            {
                return -2206;
            }
            int column_count = 0;
            
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -2207;
            }
            if (column_count != 24) /* validate column count */
            {
                return -2207;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2208;
            }
            if (stmt_execute)
            {
                return -2208;
            }
            
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                memset(length, 0, sizeof(length));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&gid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&rule_serial;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&block_serial;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)brief;
                bind[3].buffer_length= 255;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&type;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&cross_period;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&deduct;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&duration;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                bind[8].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[8].buffer= (char *)&sttime;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                bind[9].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[9].buffer= (char *)&entime;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&max_sum;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&relation;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)reserve;
                bind[12].buffer_length= 50;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&is_integer;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&sum;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                bind[15].buffer_type= MYSQL_TYPE_SHORT;
                bind[15].buffer= (char *)&next_serial;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                bind[16].buffer_type= MYSQL_TYPE_SHORT;
                bind[16].buffer= (char *)&flag;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&_operator;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                bind[18].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[18].buffer= (char *)&crt;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&start_week;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                bind[20].buffer_type= MYSQL_TYPE_SHORT;
                bind[20].buffer= (char *)&end_week;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                bind[21].buffer_type= MYSQL_TYPE_LONG;
                bind[21].buffer= (char *)&starttime;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                bind[22].buffer_type= MYSQL_TYPE_LONG;
                bind[22].buffer= (char *)&endtime;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&createtime;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];
            }
            catch(...)
            {
                return -2239;
            }
            
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -2209;
            }
            if (stmt_bind_result)
            {
                return -2209;
            }
            
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -2210;
            }
            if (stmt_store_result)
            {
                return -2210;
            }
            
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -2211;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -2212;
            }
        }
        else
        {
            return -2203;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2213;
        }
    }
    else
    {
        return -2201;
    }
    return 0;
}

int rule_step_hourly_type::Update_rule_step_hourly_type()
{
    std::string statment = "INSERT INTO `v32_rule_step_hourly` (`gid`, `rule_serial`, `block_serial`, `brief`, `type`, `cross_period`, `deduct`, `duration`, `starttime`, `endtime`, `max_sum`, `relation`, `reserve`, `is_integer`, `sum`, `next_serial`, `flag`, `operator`, `createtime`, `start_week`, `end_week`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?) ON DUPLICATE KEY UPDATE gid=VALUES(gid), rule_serial=VALUES(rule_serial), block_serial=VALUES(block_serial), brief=VALUES(brief), type=VALUES(type), cross_period=VALUES(cross_period), deduct=VALUES(deduct), duration=VALUES(duration), starttime=VALUES(starttime), endtime=VALUES(endtime), max_sum=VALUES(max_sum), relation=VALUES(relation), reserve=VALUES(reserve), is_integer=VALUES(is_integer), sum=VALUES(sum), next_serial=VALUES(next_serial), flag=VALUES(flag), operator=VALUES(operator), createtime=VALUES(createtime), start_week=VALUES(start_week), end_week=VALUES(end_week)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2215;
        }
        if (!stmt)
        {
            return -2215;
        }
        
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2216;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                memset(length, 0, sizeof(length));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&gid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&rule_serial;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&block_serial;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)brief;
                bind[3].buffer_length= 255;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(brief);
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&type;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&cross_period;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&deduct;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&duration;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&starttime;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&endtime;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&max_sum;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&relation;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)reserve;
                bind[12].buffer_length= 50;
                bind[12].is_null= &is_null[12];
                length[12] = strlen(reserve);
                bind[12].length= &length[12];

                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&is_integer;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&sum;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                bind[15].buffer_type= MYSQL_TYPE_SHORT;
                bind[15].buffer= (char *)&next_serial;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                bind[16].buffer_type= MYSQL_TYPE_SHORT;
                bind[16].buffer= (char *)&flag;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&_operator;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&createtime;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&start_week;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                bind[20].buffer_type= MYSQL_TYPE_SHORT;
                bind[20].buffer= (char *)&end_week;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];
            }
            catch(...)
            {
                return -2240;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -2217;
            }
            if (stmt_bind_param)
            {
                return -2217;
            }
            
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2218;
            }
            if (param_count != 21) /* validate parameter count */
            {
                return -2218;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2219;
            }
            if (stmt_execute)
            {
                return -2219;
            }
            
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2220;
            }
            if (stmt_affected_rows == 1)
            {
                fprintf(stderr, "rule step hourly is inserted\n");
            }
            else
            {
                fprintf(stderr, "rule step hourly is updated\n");
            }
        }
        else
        {
            return -2216;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2221;
        }
    }
    else
    {
        return -2214;
    }
    return 0;
}

int rule_step_hourly_type::Delete_rule_step_hourly_type()
{
    try
    {
        gid = 0;
        type = 0;
        cross_period = 0;
        deduct = 0;
        duration = 0;
        max_sum = 0;
        relation = 0;
        is_integer = 0;
        sum = 0;
        next_serial = 0;
        flag = 0;
        _operator = 0;
        start_week = 0;
        end_week = 0;
        strcpy(brief, "");
        strcpy(reserve, "");
        starttime = 0;
        endtime = 0;
        createtime = 0;
    }
    catch(...)
    {
        return -2241;
    }
    std::string statment = "DELETE FROM `v32_rule_step_hourly` WHERE `rule_serial`= ? and `block_serial`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2223;
        }
        if (!stmt)
        {
            return -2223;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2224;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&rule_serial;

                bind_param[1].buffer_type= MYSQL_TYPE_LONG;
                bind_param[1].buffer= (char *)&block_serial;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2225;
            }
            if (stmt_bind_param)
            {
                return -2225;
            }
            int param_count = 0;
            try
            {
                mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2226;
            }
            if (param_count != 2)
            {
                return -2226;
            }

            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2227;
            }
            if(stmt_execute)
            {
                return -2227;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2228;
            }
            if (stmt_affected_rows < 1)
            {
                return -2228;
            }    
        }
        else
        {
            return -2224;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2229;
        }
    }
    else
    {
        return -2222;
    }
    rule_serial = 0;
    block_serial = 0;
    return 0;
    
}

int rule_step_hourly_type::Delete_all_rule_step_hourly_type_by_rule_serial(int garage_id, int _rule_serial)
{
    int _gid;
    int _rule_ser;
    std::string statment = "DELETE FROM `v32_rule_step_hourly` WHERE `gid`= ? and `rule_serial` = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2231;
        }
        if (!stmt)
        {
            return -2231;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2232;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind_param));        
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&_gid;

                bind_param[1].buffer_type= MYSQL_TYPE_LONG;
                bind_param[1].buffer= (char *)&_rule_ser;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2233;
            }
            if (stmt_bind_param)
            {
                return -2233;
            }
            
            _gid = garage_id;
            _rule_ser = _rule_serial;
            
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2234;
            }
            if (param_count != 2)
            {
                return -2234;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2235;
            }
            if (stmt_execute)
            {
                return -2235;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2236;
            }
            if(stmt_affected_rows < 1)
            {
                return -2236;
            }
            else
            {
                printf("Delete (%d) Records\n", stmt_affected_rows);
            }
        }
        else
        {
            return -2232;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2238;
        }
    }
    else
    {
        return -2230;
    }
    return 0;
}
