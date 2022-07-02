#include "monthly_type.h"

monthly_type::monthly_type(MYSQL *_mysql)
{
    mysql = _mysql;
    memset(bind_param, 0, sizeof(bind));
    memset(bind, 0, sizeof(bind));
    memset(is_null, 0, sizeof(is_null));
    memset(length, 0, sizeof(length));
}

monthly_type::~monthly_type()
{
    
}

int monthly_type::print_monthly_type()
{
    try
    {
        printf("%ld %d %ld %d %d %d %d %d %d %d %ld %s %s %d %d %ld %d %d\n",
                aid,
                id,
                gid,
                type,
                access_group_id,
                time_group_id,
                inner_group_id,
                monthly_charge_rule,
                prepaid_charge_rule, 
                vip_flag,
                reserved,
                name,
                description,
                flag,
                _operator,
                createtime,
                lotgroup_countingtype,
                expires);
    }
    catch(...)
    {
        return 0;
    }
    return 0;
}

int monthly_type::Select_monthly_type_by_id(int index, int garage_id)
{
    int idx;
    int _gid;
    std::string statment = "SELECT * ,Unix_Timestamp(createtime) FROM v32_monthly_type WHERE id = ? and gid = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2002;
        }
        if (!stmt)
        {
            return -2002;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2003;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&idx;
                bind_param[1].buffer_type= MYSQL_TYPE_LONG;
                bind_param[1].buffer= (char *)&_gid;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2004;
            }
            if (stmt_bind_param)
            {
                return -2004;
            }
                   
            idx = index;
            _gid = garage_id;

            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2005;
            }
            if (param_count != 2)
            {
                return -2005;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -2006;
            }
            if (!prepare_meta_result)
            {
                return -2006;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -2007;
            }
            if (column_count != 19) /* validate column count */
            {
                return -2007;
            }
            
            bool stmt_execute = 0;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2008;
            }
            if (mysql_stmt_execute(stmt))
            {
                return -2008;
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
                bind[1].buffer= (char *)&id;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&gid;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_SHORT;
                bind[3].buffer= (char *)&type;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&access_group_id;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&time_group_id;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&inner_group_id;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&monthly_charge_rule;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_SHORT;
                bind[8].buffer= (char *)&prepaid_charge_rule;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&vip_flag;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&reserved;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_STRING;
                bind[11].buffer= (char *)name;
                bind[11].buffer_length= 64;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)description;
                bind[12].buffer_length= 255;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&flag;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&_operator;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* TIMESTAMP COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[15].buffer= (char *)&crt;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_SHORT;
                bind[16].buffer= (char *)&lotgroup_countingtype;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&expires;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* INTEGER COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&createtime;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];
            }
            catch(...)
            {
                return -2031;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -2009;
            }
            if (stmt_bind_result)
            {
                return -2009;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -2010;
            }
            if (stmt_store_result)
            {
                return -2010;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -2011;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -2012;
            }
        }
        else
        {
            return -2003;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2013;
        }
    }
    else
    {
        return -2001;
    }
    return 0;
}

int monthly_type::Insert_Update_monthly_type()
{
    std::string statment = "INSERT INTO `v32_monthly_type` (`aid`, `id`, `gid`, `type`, `access_group_id`, `time_group_id`, `inner_group_id`, `monthly_charge_rule`, `prepaid_charge_rule`, `vip_flag`, `reserved`, `name`, `description`, `flag`, `operator`, `createtime`, `lotgroup_countingtype`, `expires`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?) ON DUPLICATE KEY UPDATE aid=VALUES(aid), id=VALUES(id), gid=VALUES(gid), type=VALUES(type), access_group_id=VALUES(access_group_id), time_group_id=VALUES(time_group_id), inner_group_id=VALUES(inner_group_id), monthly_charge_rule=VALUES(monthly_charge_rule), prepaid_charge_rule=VALUES(prepaid_charge_rule), vip_flag=VALUES(vip_flag), reserved=VALUES(reserved), name=VALUES(name), description=VALUES(description), flag=VALUES(flag), operator=VALUES(operator), createtime=VALUES(createtime), lotgroup_countingtype=VALUES(lotgroup_countingtype), expires=VALUES(expires)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2015;
        }
        if (!stmt)
        {
            return -2015;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2016;
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
                bind[1].buffer= (char *)&id;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&gid;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_SHORT;
                bind[3].buffer= (char *)&type;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&access_group_id;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&time_group_id;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&inner_group_id;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&monthly_charge_rule;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_SHORT;
                bind[8].buffer= (char *)&prepaid_charge_rule;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&vip_flag;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&reserved;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_STRING;
                bind[11].buffer= (char *)name;
                bind[11].buffer_length= 64;
                bind[11].is_null= &is_null[11];
                length[11] = strlen(name);
                bind[11].length= &length[11];

                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)description;
                bind[12].buffer_length= 255;
                bind[12].is_null= &is_null[12];
                length[12] = strlen(description);
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&flag;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&_operator;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* TIMESTAMP COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&createtime;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_SHORT;
                bind[16].buffer= (char *)&lotgroup_countingtype;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&expires;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];
            }
            catch(...)
            {
                return -2032;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -2017;
            }
            if (stmt_bind_param)
            {
                return -2017;
            }
            int param_count = 0;
            try
            {
                mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2018;
            }
            if (param_count != 18) /* validate parameter count */
            {
                return -2018;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2019;
            }
            if (stmt_execute)
            {
                return -2019;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2020;
            }
            if (stmt_affected_rows == 1)
            {
                fprintf(stderr, "monthly type is inserted\n");
            }
            else
            {
                fprintf(stderr, "monthly type is updated\n");
            }
        }
        else
        {
            return -2016;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2021;
        }
    }
    else
    {
        return -2014;
    }
    return 0;
}

int monthly_type::Delete_monthly_type()
{
    try
    {
        type = 0xff;
        access_group_id = 0xffff;
        time_group_id = 0xff;
        inner_group_id = 0xff;
        monthly_charge_rule = 0xff;
        prepaid_charge_rule = 0xff;
        vip_flag = 0xff;
        reserved = 0;
        strcpy(name, "");
        strcpy(description, "");
        flag = 0;
        _operator = 0;
        createtime = 0;
        lotgroup_countingtype = 0;
        expires = 0xff;
    }
    catch(...)
    {
        return -2033;
    }
    std::string statment = "DELETE FROM `v32_monthly_type` WHERE `id`= ? and `gid` = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2023;
        }
        if (!stmt)
        {
            return -2023;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2024;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind_param));        
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&id;

                bind_param[1].buffer_type= MYSQL_TYPE_LONG;
                bind_param[1].buffer= (char *)&gid;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2025;
            }
            if (stmt_bind_param)
            {
                return -2025;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2026;
            }
            if (param_count != 2)
            {
                return -2026;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2027;
            }
            if (stmt_execute)
            {
                return -2027;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }               
            catch(...)
            {
                return -2028;
            }                  
            if (stmt_affected_rows < 1)
            {
                return -2028;
            }    
        }
        else
        {
            return -2024;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2029;
        }
    }
    else
    {
        return -2022;
    }
    id = -1;
    gid = 0;
    return 0;
}
