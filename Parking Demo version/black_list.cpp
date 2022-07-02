#include "black_list.h"

black_list_type::black_list_type(MYSQL *_mysql)
{
    mysql = _mysql;
    memset(bind_param, 0, sizeof(bind));
    memset(bind, 0, sizeof(bind));
    memset(is_null, 0, sizeof(is_null));
    memset(length, 0, sizeof(length));
}

black_list_type::~black_list_type()
{
    
}

int black_list_type::print_black_list()
{
    try
    {
        printf("%d\t%d\t%s\t%s\t%d\t%s\t%d\t%ld\n", 
            id, 
            gid, 
            description, 
            ticket, 
            ticket_type, 
            plate, 
            _operator, 
            create_time);
    }
    catch(...)
    {
        return -2730;
    }
    return 0;
}

int black_list_type::Select_black_list_type_by_id(int index)
{
    int idx;
    std::string statment = "SELECT * ,Unix_Timestamp(createtime) FROM v32_black_list WHERE id = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2702;
        }
        if (!stmt)
        {
            return -2702;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2703;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&idx;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2704;
            }
            if (stmt_bind_param)
            {
                return -2704;
            }
            
            idx = index;
            
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2705;
            }
            if (param_count != 1)
            {
                return -2705;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -2706;
            }
            if (!prepare_meta_result)
            {
                return -2706;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -2707;
            }
            if (column_count != 9)
            {
                return -2707;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2708;
            }
            if (stmt_execute)
            {
                return -2708;
            }
            
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                memset(length, 0, sizeof(length));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)description;
                bind[2].buffer_length= 200;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&ticket_type;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_STRING;
                bind[5].buffer= (char *)plate;
                bind[5].buffer_length= 12;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&_operator;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* TIMESTAMP COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[7].buffer= (char *)&crt;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* INTEGER COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&create_time;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];
            }
            catch(...)
            {
                return -2731;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -2709;
            }
            if (stmt_bind_result)
            {
                return -2709;
            }

            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -2710;
            }
            if (stmt_store_result)
            {
                return -2710;
            }
            
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -2711;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -2712;
            }
        }
        else
        {
            return -2703;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2713;
        }
    }
    else
    {
        return -2701;
    }
    return true;
}

int black_list_type::Insert_Update_black_list_type()
{
    std::string statment = "INSERT INTO `v32_black_list` (`id`, `gid`, `description`, `ticket`, `ticket_type`, `plate`, `operator`, `createtime`) VALUES (?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?)) ON DUPLICATE KEY UPDATE id=VALUES(id), gid=VALUES(gid), description=VALUES(description), ticket=VALUES(ticket), ticket_type=VALUES(ticket_type), operator=VALUES(operator), plate=VALUES(plate), createtime=VALUES(createtime)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2715;
        }
        if (!stmt)
        {
            return -2715;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2716;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                memset(length, 0, sizeof(length));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)description;
                bind[2].buffer_length= 200;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(description);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(ticket);
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&ticket_type;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_STRING;
                bind[5].buffer= (char *)plate;
                bind[5].buffer_length= 12;
                bind[5].is_null= &is_null[5];
                length[5] = strlen(plate);
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&_operator;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* INTEGER COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&create_time;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];
            }
            catch(...)
            {
                return -2732;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -2717;
            }
            if (stmt_bind_param)
            {
                return -2717;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2718;
            }
            if (param_count != 8) /* validate parameter count */
            {
                return -2718;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2719;
            }
            if (stmt_execute)
            {
                return -2719;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2720;
            }
            if (stmt_affected_rows == 1)
            {
                printf("black list is inserted\n");
            }
            else
            {
                printf("black list is updated\n");
            }
        }
        else
        {
            return -2716;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2721;
        }
    }
    else
    {
        return -2714;
    }
    return true;
}

int black_list_type::Delete_black_list_type()
{
    try
    {
        gid = 0;
        strcpy(description , "");
        strcpy(ticket, "");
        ticket_type = 255;
        strcpy(plate, "");
        _operator = 0;
        create_time = 0;
    }
    catch(...)
    {
        return -2733;
    }
    std::string statment = "DELETE FROM `v32_black_list` WHERE `id`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2723;
        }
        if (!stmt)
        {
            return -2723;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2724;
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
                return -2725;
            }
            if (stmt_bind_param)
            {
                return -2725;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2726;
            }
            if (param_count != 1)
            {
                return -2726;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2727;
            }
            if (stmt_execute)
            {
                return -2727;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2728;
            }
            if (stmt_affected_rows < 1)
            {
                return -2728;
            }    
        }
        else
        {
            return -2724;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2729;
        }
    }
    else
    {
        return -2722;
    }
    id = 0;
    return 0;
    
}


