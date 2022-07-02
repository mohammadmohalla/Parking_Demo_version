#include "rule_name_hourly.h"

rule_name_hourly_type::rule_name_hourly_type(MYSQL *_mysql)
{
    mysql = _mysql;
    memset(bind_param, 0, sizeof(bind));
    memset(bind, 0, sizeof(bind));
    memset(is_null, 0, sizeof(is_null));
    memset(length, 0, sizeof(length));
}

rule_name_hourly_type::~rule_name_hourly_type()
{
    
}

int rule_name_hourly_type::print_rule_name_hourly_type()
{
    try
    {
        printf("%d\t%d\t%d\t%s\t%d\t%d\t%s\t%d\t%s%d\t%d\t%d\t%ld\n", 
            aid, 
            gid, 
            rule_serial,
            fixed_time, 
            limit_enable, 
            limit_sum,
            name, 
            within_duration, 
            remark,
            tolerance, 
            _operator, 
            flag, 
            create_time);
    }
    catch(...)
    {
        return -2130;
    }
    return 0;
}

int rule_name_hourly_type::Select_rule_name_hourly_type_by_rule_serial(int serial)
{
    int _rule_serial;
    std::string statment = "SELECT * ,Unix_Timestamp(createtime) FROM v32_rule_name_hourly WHERE rule_serial = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2102;
        }
        if (!stmt)
        {
            return -2102;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2103;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&_rule_serial;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2104;
            }
            if (stmt_bind_param)
            {
                return -2104;
            }
            
            int param_count = 0;
            try
            {
                _rule_serial = serial;
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2105;
            }
            if (param_count != 1) /* validate parameter count */
            {
                return -2105;
            }

            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -2106;
            }
            if (!prepare_meta_result)
            {
                return -2106;
            }
            int column_count = 0;
            
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -2107;
            }
            if (column_count != 14)
            {
                return -2107;
            }
            
            bool stmt_execute = true;
            
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2108;
            }
            if (stmt_execute)
            {
                return -2108;
            }
            
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

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&rule_serial;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)fixed_time;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&limit_enable;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&limit_sum;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_STRING;
                bind[6].buffer= (char *)name;
                bind[6].buffer_length= 50;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* TIMESTAMP COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&within_duration;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* INTEGER COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_STRING;
                bind[8].buffer= (char *)remark;
                bind[8].buffer_length= 255;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&tolerance;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                bind[10].buffer_type= MYSQL_TYPE_SHORT;
                bind[10].buffer= (char *)&_operator;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&flag;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* TIMESTAMP COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[12].buffer= (char *)&crt;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* INTEGER COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&create_time;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];
            }
            catch(...)
            {
                return -2131;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -2109;
            }
            if (stmt_bind_result)
            {
                return -2109;
            }
            
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -2110;
            }
            if (stmt_store_result)
            {
                return -2110;
            }
            
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -2111;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -2112;
            }
        }
        else
        {
            return -2103;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2113;
        }
    }
    else
    {
        return -2101;
    }
    return 0;
}

int rule_name_hourly_type::Update_rule_name_hourly_type()
{
    std::string statment = "INSERT INTO `v32_rule_name_hourly` (`aid`, `gid`, `rule_serial`, `fixed_time`, `limit_enable`, `limit_sum`, `name`, `within_duration`, `remark`, `tolerance`, `flag`, `operator`, `createtime`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?)) ON DUPLICATE KEY UPDATE aid=VALUES(aid), gid=VALUES(gid), rule_serial=VALUES(rule_serial), fixed_time=VALUES(fixed_time), limit_enable=VALUES(limit_enable), limit_sum=VALUES(limit_sum), name=VALUES(name), within_duration=VALUES(within_duration), remark=VALUES(remark), tolerance=VALUES(tolerance), flag=VALUES(flag), operator=VALUES(operator), createtime=VALUES(createtime)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2115;
        }
        if (!stmt)
        {
            return -2115;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2116;
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

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&rule_serial;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)fixed_time;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(fixed_time);
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&limit_enable;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&limit_sum;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_STRING;
                bind[6].buffer= (char *)name;
                bind[6].buffer_length= 50;
                bind[6].is_null= &is_null[6];
                length[6] = strlen(name);
                bind[6].length= &length[6];

                /* TIMESTAMP COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&within_duration;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* INTEGER COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_STRING;
                bind[8].buffer= (char *)remark;
                bind[8].buffer_length= 255;
                bind[8].is_null= &is_null[8];
                length[8] = strlen(remark);
                bind[8].length= &length[8];

                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&tolerance;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                bind[10].buffer_type= MYSQL_TYPE_SHORT;
                bind[10].buffer= (char *)&_operator;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&flag;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* INTEGER COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&create_time;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];
            }
            catch(...)
            {
                return -2132;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -2117;
            }
            if (stmt_bind_param)
            {
                return -2117;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2118;
            }
            if (param_count != 13) /* validate parameter count */
            {
                return -2118;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2119;
            }
            if (stmt_execute)
            {
                return -2119;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2120;
            }
            if (stmt_affected_rows == 1)
            {
                fprintf(stderr, "rule name hourly %s is inserted\n", name);
            }
            else
            {
                fprintf(stderr, "rule name hourly %s is updated\n", name);
            }
        }
        else
        {
            return -2116;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2121;
        }
    }
    else
    {
        return -2114;
    }
    return 0;
}

int rule_name_hourly_type::Delete_rule_name_hourly_type()
{
    try
    {
        aid = 0;
        gid = 0;
        limit_enable = 0;
        limit_sum = 0;
        within_duration = 0;
        tolerance = 0;
        flag = 0;
        _operator = 0;
        strcpy(name, "");
        strcpy(fixed_time, "");
        strcpy(remark, "");
        create_time = 0;
    }
    catch(...)
    {
        return -2133;
    }
    std::string statment = "DELETE FROM `v32_rule_name_hourly` WHERE `rule_serial`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2123;
        }
        if (!stmt)
        {
            return -2123;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2124;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&rule_serial;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2125;
            }
            if (stmt_bind_param)
            {
                return -2125;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2126;
            }
            if (param_count != 1)
            {
                return -2126;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2127;
            }
            if (stmt_execute)
            {
                return -2127;
            }
            
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2128;
            }
            if (stmt_affected_rows < 1)
            {
                return -2128;
            }    
        }
        else
        {
            return -2124;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2129;
        }
    }
    else
    {
        return -2122;
    }
    rule_serial = 255;
    return 0;
    
}