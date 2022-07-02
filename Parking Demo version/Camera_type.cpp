#include "Camera_type.h"

Camera_type::Camera_type(MYSQL *_mysql)
{
    mysql = _mysql;
}

Camera_type::~Camera_type()
{
    
}

int Camera_type::print_camera()
{
    try
    {
        printf("%d\t%s\t%s\t%s\t%s\t%s\t%d\t%ld\n", 
            gid, 
            ip, 
            Camera_name, 
            user_name,
            password,
            site_Addresses, 
            _operator, 
            create_time);
    }
    catch(...)
    {
        return -1646;
    }
    return 0;
}

int Camera_type::Select_Camera_type_by_address(int _address)
{
    char site_ip[22] = "";
    std::string site_address = "" + std::to_string(_address);
    std::string statment = "SELECT * ,Unix_Timestamp(createtime) FROM v32_camerato_site WHERE ip = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1602;
        }
        if (!stmt)
        {
            return -1602;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1603;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind_param));
                bind_param[0].buffer_type= MYSQL_TYPE_STRING;
                bind_param[0].buffer= (char *)site_ip;
                bind_param[0].buffer_length= strlen(site_address.c_str());
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -1604;
            }
            if (stmt_bind_param)
            {
                return -1604;
            }
            int param_count = 0;
            try
            {
                strcpy( site_ip, site_address.c_str());
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1605;
            }
            if (param_count != 1) /* validate parameter count */
            {
                return -1605;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -1606;
            }
            if (!prepare_meta_result)
            {
                return -1606;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -1607;
            }
            if (column_count != 9)
            {
                return -1607;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1608;
            }
            if (stmt_execute)
            {
                return -1608;
            }
            
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&gid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_STRING;
                bind[1].buffer= (char *)ip;
                bind[1].buffer_length= 22;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)Camera_name;
                bind[2].buffer_length= 50;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];
                
                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)user_name;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];
                
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)password;
                bind[4].buffer_length= 20;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_STRING;
                bind[5].buffer= (char *)site_Addresses;
                bind[5].buffer_length= 16;
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
                return -1647;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -1609;
            }
            if (stmt_bind_result)
            {
                return -1609;
            }
            
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -1610;
            }
            if (stmt_store_result)
            {
                return -1610;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -1611;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -1612;
            }
            try
            {
                cam_address = std::stoi(std::string(ip));
                memset(sites_binded, 0, sizeof(sites_binded));
                int counter = 0;
                char sites_stroke_list[100] = "";
                strcpy(sites_stroke_list, site_Addresses);
                char * pch = strtok (sites_stroke_list,",");
                while (pch != NULL)
                {
                    sites_binded[counter] = atoi(pch);
                    pch = strtok (NULL, ",");
                    counter++;
                }
            }
            catch(...)
            {
                return -1652;
            }
        }
        else
        {
            return -1603;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1613;
        }
        
    }
    else
    {
        return -1601;
    }
    return 0;
}

int Camera_type::Insert_Update_Camera_type()
{
    std::string statment = "INSERT INTO v32_camerato_site (`gid`, ip, name, user_name, password, site, operator, `createtime`) VALUES (?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?)) ON DUPLICATE KEY UPDATE gid=VALUES(gid), ip=VALUES(ip), name=VALUES(name), user_name=VALUES(user_name), password=VALUES(password), site=VALUES(site), operator=VALUES(operator), createtime=VALUES(createtime)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1615;
        }
        if (!stmt)
        {
            return -1615;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1616;
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

                /* STRING COLUMN */
                bind[1].buffer_type= MYSQL_TYPE_STRING;
                bind[1].buffer= (char *)ip;
                bind[1].buffer_length= 22;
                bind[1].is_null= &is_null[1];
                length[1] = strlen(ip);
                bind[1].length= &length[1];

                /* STRING COLUMN */
                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)Camera_name;
                bind[2].buffer_length= 50;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(Camera_name);
                bind[2].length= &length[2];
                
                /* STRING COLUMN */
                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)user_name;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(user_name);
                bind[3].length= &length[3];
                
                /* STRING COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)password;
                bind[4].buffer_length= 20;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(password);
                bind[4].length= &length[4];
                
                //std::cout << "site_Addresses = " << site_Addresses << "\n";
                /* STRING COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_STRING;
                bind[5].buffer= (char *)site_Addresses;
                bind[5].buffer_length= 16;
                bind[5].is_null= &is_null[5];
                length[5] = strlen(site_Addresses);
                bind[5].length= &length[5];

                /* INTEGER COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&_operator;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* TIMESTAMP COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&create_time;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];
            }
            catch(...)
            {
                return -1648;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -1625;
            }
            if (stmt_bind_param)
            {
                return -1625;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1626;
            }
            if (param_count != 8)
            {
                std::cout << "param_count = " << param_count << "\n";
                return -1626;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1627;
            }
            if (stmt_execute)
            {
                return -1627;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1628;
            }
            if (stmt_affected_rows == 1)
            {
                printf("Camera is inserted\n");
            }
            else
            {
                printf("Camera is updated\n");
            }
            try
            {
                int counter = 0;
                char sites_stroke_list[100] = "";
                strcpy(sites_stroke_list, site_Addresses);
                char * pch = strtok (sites_stroke_list,",");
                while (pch != NULL)
                {
                    sites_binded[counter] = atoi(pch);
                    pch = strtok (NULL, ",");
                    counter++;
                }
            }
            catch(...)
            {
                return -1653;
            }
        }
        else
        {
            return -1616;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1629;
        }
    }
    else
    {
        return -1614;
    }
    return 0;
}

int Camera_type::Clear_Camera_type_sites(int _address)
{
    char site_ip[22] = "";
    std::string site_address = "" + std::to_string(_address);
    std::string statment = "update v32_camerato_site set site='' WHERE ip=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1631;
        }
        if (!stmt)
        {
            return -1631;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1632;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type = MYSQL_TYPE_STRING;
                bind_param[0].buffer = (char *)site_ip;
                bind_param[0].buffer_length = strlen(site_address.c_str());
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -1633;
            }
            if (stmt_bind_param)
            {
                return -1633;
            }
            int param_count = 0;
            try
            {
                strcpy(site_ip, site_address.c_str());
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1634;
            }
            if (param_count != 1)
            {
                return -1634;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1635;
            }
            if (stmt_execute)
            {
                return -1635;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1636;
            }
            if (stmt_affected_rows == 1)
            {
                printf("Binded Sites is not Cleared\n");
            }
            else
            {
                printf("Binded Sites is Cleared\n");
            }
            memset(site_Addresses, 0, sizeof(bind));
            memset(sites_binded, 0, sizeof(bind));
        }
        else
        {
            return -1632;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1637;
        }
    }
    else
    {
        return -1630;
    }
    return 0;
}

int Camera_type::Insert_Update_Camera_type_binded_site()
{
    std::string statment = "INSERT INTO v32_camerato_site (`gid`, `ip`, `name`, `user_name`, `password`, `site`, `operator`, `createtime`) VALUES (?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?)) ON DUPLICATE KEY UPDATE gid=VALUES(gid), ip=VALUES(ip), name=VALUES(name), user_name=VALUES(user_name), password=VALUES(password), site=CONCAT(site,',',VALUES(site)), operator=VALUES(operator), createtime=VALUES(createtime)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1657;
        }
        if (!stmt)
        {
            return -1657;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1658;
        }
        if (!stmt_prepare)
        {
            memset(bind, 0, sizeof(bind));
            memset(is_null, 0, sizeof(is_null));
            memset(length, 0, sizeof(length));

            bind[0].buffer_type= MYSQL_TYPE_LONG;
            bind[0].buffer= (char *)&gid;
            bind[0].is_null= &is_null[0];
            bind[0].length= &length[0];
            
            /* STRING COLUMN */
            bind[1].buffer_type= MYSQL_TYPE_STRING;
            bind[1].buffer= (char *)ip;
            bind[1].buffer_length= 22;
            bind[1].is_null= &is_null[1];
            length[1] = strlen(ip);
            bind[1].length= &length[1];
            
            /* STRING COLUMN */
            bind[2].buffer_type= MYSQL_TYPE_STRING;
            bind[2].buffer= (char *)Camera_name;
            bind[2].buffer_length= 50;
            bind[2].is_null= &is_null[2];
            length[2] = strlen(Camera_name);
            bind[2].length= &length[2];
            
            /* STRING COLUMN */
            bind[3].buffer_type= MYSQL_TYPE_STRING;
            bind[3].buffer= (char *)user_name;
            bind[3].buffer_length= 20;
            bind[3].is_null= &is_null[3];
            length[3] = strlen(user_name);
            bind[3].length= &length[3];
            
            /* STRING COLUMN */
            bind[4].buffer_type= MYSQL_TYPE_STRING;
            bind[4].buffer= (char *)password;
            bind[4].buffer_length= 20;
            bind[4].is_null= &is_null[4];
            length[4] = strlen(password);
            bind[4].length= &length[4];
            
            /* STRING COLUMN */
            bind[5].buffer_type= MYSQL_TYPE_STRING;
            bind[5].buffer= (char *)site_Addresses;
            bind[5].buffer_length= 16;
            bind[5].is_null= &is_null[5];
            length[5] = strlen(site_Addresses);
            bind[5].length= &length[5];
            
            /* INTEGER COLUMN */
            bind[6].buffer_type= MYSQL_TYPE_SHORT;
            bind[6].buffer= (char *)&_operator;
            bind[6].is_null= &is_null[6];
            bind[6].length= &length[6];
            
            /* TIMESTAMP COLUMN */
            bind[7].buffer_type= MYSQL_TYPE_LONG;
            bind[7].buffer= (char *)&create_time;
            bind[7].is_null= &is_null[7];
            bind[7].length= &length[7];
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -1659;
            }
            if (stmt_bind_param)
            {
                return -1659;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1660;
            }
            if (param_count != 8) /* validate parameter count */
            {
                return -1660;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1661;
            }
            if (stmt_execute)
            {
                return -1661;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1662;
            }
            if (stmt_affected_rows == 1)
            {
                fprintf(stderr, "Camera is inserted\n");
            }
            else
            {
                fprintf(stderr, "Camera is updated\n");
            }
            try
            {
                int counter = 0;
                char sites_stroke_list[100] = "";
                strcpy(sites_stroke_list, site_Addresses);
                char * pch = strtok (sites_stroke_list,",");
                while (pch != NULL)
                {
                    sites_binded[counter] = atoi(pch);
                    pch = strtok (NULL, ",");
                    counter++;
                }
            }
            catch(...)
            {
                return -1650;
            }
        }
        else
        {
            return -1658;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1663;
        }
    }
    else
    {
        return -1656;
    }
    return true;
}

int Camera_type::Delete_Camera_type()
{
    try
    {
        gid = 0;
        _operator = 0;
        cam_address = 0;
        strcpy(site_Addresses, "");
        strcpy(Camera_name, "");
        create_time = 0;
    }
    catch(...)
    {
        return -1651;
    }
    std::string statment = "DELETE FROM `v32_camerato_site` WHERE `ip`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1639;
        }
        if (!stmt)
        {
            return -1639;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1640;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_STRING;
                bind_param[0].buffer= (char *)ip;
                bind_param[0].buffer_length= strlen(ip);
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -1641;
            }
            if (stmt_bind_param)
            {
                return -1641;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1642;
            }
            if (param_count != 1)
            {
                return -1642;
            }

            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1643;
            }
            if (stmt_execute)
            {
                return -1644;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1644;
            }
            if (stmt_affected_rows < 1)
            {
                return -1644;
            }    
        }
        else
        {
            return -1640;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1645;
        }
    }
    else
    {
        return -1638;
    }
    strcpy(ip, "");
    return 0;
}