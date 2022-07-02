#include "group_inner.h"

group_inner::group_inner(MYSQL *_mysql)
{
    mysql = _mysql;
}

group_inner::~group_inner()
{
    
}

int group_inner::print_group_inner()
{
    try
    {
        printf("%ld %ld %d %s %s %d %d %d %ld",
            id,
            gid,
            inner_charge,
            name,
            sites_list,
            outer_charge,
            flag,
            _operator,
            createtime);
        printf("\n");
    }
    catch(...)
    {
        return -1830;
    }
    return 0;
}

int group_inner::Select_group_inner_by_ID(int index)
{
    int idx;
    std::string statment = "SELECT *, Unix_Timestamp(createtime) FROM v32_group_inner WHERE id=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1802;
        }
        if (!stmt)
        {
            return -1802;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1803;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&index;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -1804;
            }
            if (stmt_bind_param)
            {
                return -1804;
            }
            
            idx = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1805;
            }
            if (param_count != 1)
            {
                return -1805;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -1806;
            }
            if (!prepare_meta_result)
            {
                return -1806;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -1807;
            }
            if (column_count != 10)
            {
                return -1807;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1808;
            }
            if (stmt_execute)
            {
                return -1808;
            }
            
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                memset(length,0,sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&inner_charge;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)name;
                bind[3].buffer_length= 50;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)sites_list;
                bind[4].buffer_length= 100;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&outer_charge;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&flag;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&_operator;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                bind[8].buffer_type = MYSQL_TYPE_TIMESTAMP;
                bind[8].buffer= (char *)&crt;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&createtime;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];
            }
            catch(...)
            {
                return -1831;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -1809;
            }
            if (stmt_bind_result)
            {
                return -1809;
            }

            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -1810;
            }
            if (stmt_store_result)
            {
                return -1810;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -1811;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -1812;
            }
            try
            {
                int counter = 0;
                char * pch = strtok (sites_list,",");
                while (pch != NULL)
                {
                    _sites_list[counter] = atoi(pch);
                    pch = strtok (NULL, ",");
                    counter++;
                }
            }
            catch(...)
            {
                return -1834;
            }
            
        }
        else
        {
            return -1803;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1813;
        }
    }
    else
    {
        return -1801;
    }
    return 0;
}
    
int group_inner::Insert_update_group_inner()
{
    std::string statment = "INSERT INTO `v32_group_inner` (`id`, `gid`, `inner_charge`, `name`, `sites_list`, `outer_charge`, `flag`, `operator`, `createtime`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?)) ON DUPLICATE KEY UPDATE id=VALUES(id), gid=VALUES(gid), inner_charge=VALUES(inner_charge), name=VALUES(name), sites_list=VALUES(sites_list), outer_charge=VALUES(outer_charge), flag=VALUES(flag), operator=VALUES(operator), createtime=VALUES(createtime)";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1815;
        }
        if (!stmt)
        {
            return -1815;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1816;
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

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&inner_charge;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)name;
                bind[3].buffer_length= 50;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(name);
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)sites_list;
                bind[4].buffer_length= 100;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(sites_list);
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&outer_charge;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&flag;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&_operator;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&createtime;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];
            }
            catch(...)
            {
                return -1832;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -1817;
            }
            if (stmt_bind_param)
            {
                return -1817;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1818;
            }
            if (param_count != 9) /* validate parameter count */
            {
                return -1818;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1819;
            }
            if (stmt_execute)
            {
                return -1819;
            }
            int stmt_affected_rows = 0; 
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1820;
            }
            if (stmt_affected_rows == 1)
            {
                fprintf(stderr, "Group Inner is inserted\n");
            }
            else
            {
                fprintf(stderr, "Group Inner is updated\n");
            }
            try
            {
                int counter = 0;
                char sites_stroke_list[100] = "";
                strcpy(sites_stroke_list, sites_list);
                char * pch = strtok (sites_stroke_list,",");
                while (pch != NULL)
                {
                    _sites_list[counter] = atoi(pch);
                    pch = strtok (NULL, ",");
                    counter++;
                }
            }
            catch(...)
            {
                return -1835;
            }
        }
        else
        {
            return -1816;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1821;
        }
    }
    else
    {
        return -1814;
    }
    return 0;
}

int group_inner::Delete_group_inner()
{
    try
    {
        gid = 0;
        strcpy(name , "");
        strcpy(sites_list, "");
        inner_charge = 255;
        outer_charge = 255;
        flag = 0;
        _operator = 0;
    }
    catch(...)
    {
        return -1833;
    }
    std::string statment = "DELETE FROM `v32_group_inner` WHERE `id`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1823;
        }
        if (!stmt)
        {
            return -1823;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare  = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1824;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&id;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -1825;
            }
            if (stmt_bind_param)
            {
                return -1825;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1826;
            }
            if (param_count != 1)
            {
                return -1826;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1827;
            }
            if (stmt_execute)
            {
                return -1827;
            }
            bool stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1828;
            }
            if (stmt_affected_rows < 1)
            {
                return -1828;
            }    
        }
        else
        {
            return -1824;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1829;
        }
    }
    else
    {
        return -1822;
    }
    id = 0;
    return 0;
}