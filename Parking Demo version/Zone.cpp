#include "Zone.h"

Zone::Zone(MYSQL *_mysql)
{
    mysql = _mysql;
}

Zone::~Zone()
{

}

int Zone::print_Zone()
{
    try
    {
        printf("%d %s %d %d %d %d %d %d %d %d %d %s %s %d %d %d %d {",
            serial,
            name,
            asofficial,
            cover_pgm_id,
            align_pgm_id,
            vacantSpacesHourly,
            vacantSpacesSeason,
            vacantSpaces,
            totalSpaces,
            totalSpacesHourly,
            totalSpacesSeason,
            insites_list,
            outsites_list,
            parking_Guidance_Available_Space,
            parking_Guidance_Total_Space,
            flag,
            _operator);
        int i = 0;
        while(entry_address[i] != 0)
        {
            if(entry_address[i + 1] != 0)
            {
                printf("%d, ", entry_address[i]);
            }
            else
            {
                printf("%d", entry_address[i]);
            }
            i++;
        }
        printf("} {");
        i = 0;
        while(exit_address[i] != 0)
        {
            if(exit_address[i + 1] != 0)
            {
                printf("%d, ", exit_address[i]);
                }
            else
            {
                printf("%d", exit_address[i]);
            }
            i++;
        }
        printf("}\n");
    }
    catch(...)
    {
        return -1130;
    }
    return 0;
}

int Zone::select_Zone(int _serial)
{
    short area_serial;
    std::string statment = "SELECT * ,Unix_Timestamp(createtime) FROM v32_lot_num WHERE area=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1102;
        }
        if (!stmt)
        {
            return -1102;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1103;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_SHORT;
                bind_param[0].buffer= (char *)&area_serial;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -1104;
            }
            if (stmt_bind_param)
            {
                return -1104;
            }
            area_serial = _serial;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1105;
            }
            if (param_count != 1)
            {
                return -1105;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -1106;
            }
            if (!prepare_meta_result)
            {
                return -1106;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -1107;
            }
            if (column_count != 21) /* validate column count */
            {
                return -1107;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1108;
            }
            if (stmt_execute)
            {
                return -1108;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&serial;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)name;
                bind[3].buffer_length= 50;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&asofficial;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&cover_pgm_id;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&align_pgm_id;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&vacantSpacesHourly;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&vacantSpacesSeason;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&vacantSpaces;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&totalSpaces;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&totalSpacesHourly;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&totalSpacesSeason;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)insites_list;
                bind[13].buffer_length= 255;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)outsites_list;
                bind[14].buffer_length= 50;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&parking_Guidance_Available_Space;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&parking_Guidance_Total_Space;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&flag;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                bind[18].buffer_type= MYSQL_TYPE_SHORT;
                bind[18].buffer= (char *)&_operator;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                bind[19].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[19].buffer= (char *)&crt;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&createtime;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];
            }
            catch(...)
            {
                return -1131;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -1109;
            }
            if (stmt_bind_result)
            {
                return -1109;            
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -1110;
            }
            if (stmt_store_result)
            {
                return -1110;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -1111;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -1112;
            }
            try
            {
                int counter = 0;
                char sites_stroke_list[100] = "";
                strcpy(sites_stroke_list, insites_list);
                char * pch = strtok (sites_stroke_list,",");
                while (pch != NULL)
                {
                    entry_address[counter] = atoi(pch);
                    pch = strtok (NULL, ",");
                    counter++;
                }
                counter = 0;
                char sites_stroke_list2[100] = "";
                strcpy(sites_stroke_list2, outsites_list);
                pch = strtok (sites_stroke_list2,",");
                while (pch != NULL)
                {
                    exit_address[counter] = atoi(pch);
                    pch = strtok (NULL, ",");
                    counter++;
                }
                counter = 0;
            }
            catch(...)
            {
                return -1134;
            }
        }
        else
        {
            return -1103;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1113;
        }
    }
    else
    {
        return -1101;
    }
    return 0;
}

int Zone::insert_update_Zone()
{
    //INSERT INTO v32_lots_info(gid, total_lots, monthly_lots,hourly_lots, free_total_lots,free_monthly_lots, free_hourly_lots, update_time) VALUE(?,?,?,?,?,?,?,?) ON DUPLICATE KEY UPDATE  total_lots=VALUES(total_lots), monthly_lots=VALUES(monthly_lots), hourly_lots=VALUES(hourly_lots), free_total_lots=VALUES(free_total_lots),free_monthly_lots=VALUES(free_monthly_lots),free_hourly_lots=VALUES(free_hourly_lots), update_time=VALUES(update_time)
    std::string statment = "INSERT INTO `v32_lot_num` (`aid`, `gid`, `area`, `area_name`, `asofficial`, `cover_pgm_id`, `align_pgm_id`, `free_hourly_lots`, `free_monthly_lots`, `free_total_lots`, `total_lots`, `hourly_lots`, `monthly_lots`, `insites_list`, `outsites_list`, `pgm_free_total_lots`, `pgm_total_lots`, `flag`, `operator`, `createtime`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?)) ON DUPLICATE KEY UPDATE aid=VALUES(aid), gid=VALUES(gid), area=VALUES(area), area_name=VALUES(area_name), asofficial=VALUES(asofficial), cover_pgm_id=VALUES(cover_pgm_id), align_pgm_id=VALUES(align_pgm_id), free_hourly_lots=VALUES(free_hourly_lots), free_monthly_lots=VALUES(free_monthly_lots), free_total_lots=VALUES(free_total_lots), total_lots=VALUES(total_lots), hourly_lots=VALUES(hourly_lots), monthly_lots=VALUES(monthly_lots), insites_list=VALUES(insites_list), outsites_list=VALUES(outsites_list), pgm_free_total_lots=VALUES(pgm_free_total_lots), pgm_total_lots=VALUES(pgm_total_lots), flag=VALUES(flag), operator=VALUES(operator), createtime=VALUES(createtime)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1115;
        }
        if (!stmt)
        {
            return -1115;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1116;
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

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&serial;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)name;
                bind[3].buffer_length= 50;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(name);
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&asofficial;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&cover_pgm_id;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&align_pgm_id;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&vacantSpacesHourly;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&vacantSpacesSeason;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&vacantSpaces;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&totalSpaces;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&totalSpacesHourly;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&totalSpacesSeason;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)insites_list;
                bind[13].buffer_length= 255;
                bind[13].is_null= &is_null[13];
                length[13] = strlen(insites_list);
                bind[13].length= &length[13];

                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)outsites_list;
                bind[14].buffer_length= 50;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(outsites_list);
                bind[14].length= &length[14];

                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&parking_Guidance_Available_Space;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&parking_Guidance_Total_Space;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&flag;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                bind[18].buffer_type= MYSQL_TYPE_SHORT;
                bind[18].buffer= (char *)&_operator;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                bind[19].buffer_type= MYSQL_TYPE_LONG;
                bind[19].buffer= (char *)&createtime;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];
            }
            catch(...)
            {
                return -1132;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -1117;
            }
            if (stmt_bind_param)
            {
                return -1117;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1118;
            }
            if (param_count != 20) /* validate parameter count */
            {
                return -1118;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1119;
            }
            if (stmt_execute)
            {
                return -1119;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1120;
            }
            if (stmt_affected_rows == 1)
            {
                printf("%s inserted\n", name);
            }
            else
            {
                printf("%s updated\n", name);
            }
            try
            {
                int counter = 0;
                char sites_stroke_list[100] = "";
                strcpy(sites_stroke_list, insites_list);
                char * pch = strtok (sites_stroke_list,",");
                while (pch != NULL)
                {
                    entry_address[counter] = atoi(pch);
                    pch = strtok (NULL, ",");
                    counter++;
                }
                counter = 0;
                char sites_stroke_list2[100] = "";
                strcpy(sites_stroke_list2, outsites_list);
                pch = strtok (sites_stroke_list2,",");
                while (pch != NULL)
                {
                    exit_address[counter] = atoi(pch);
                    pch = strtok (NULL, ",");
                    counter++;
                }
                counter = 0;
            }
            catch(...)
            {
                return -1135;
            }
        }
        else
        {
            return -1116;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1121;
        }
    }
    else
    {
        return -1114;
    }
    return 0;
}

int Zone::delete_Zone()
{
    int id_;
    std::string statment = "DELETE FROM `v32_lot_num` WHERE `aid`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1123;
        }
        if (!stmt)
        {
            return -1123;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1124;
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
                return -1125;
            }
            if (stmt_bind_param)
            {
                return -1125;
            }
            id_ = aid;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1126;
            }
            if (param_count != 1)
            {
                return -1126;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1027;
            }
            if (stmt_execute)
            {
                return -1027;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1028;
            }
            if (stmt_affected_rows < 1)
            {
                return -1028;
            }
        }
        else
        {
            return -1124;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1029;
        }
    }
    else
    {
        return -1122;
    }
    return 0;
}

std::string Zone::get_Serial()
{
    return to_String_X2(serial);
}

std::string Zone::get_TotalSpaces()
{
    return to_String_X4(totalSpaces);
}

std::string Zone::get_TotalSpacesSeason()
{
    return to_String_X4(totalSpacesSeason);
}

std::string Zone::get_TotalSpacesHourly()
{
	return to_String_X4(totalSpacesHourly);
}

std::string Zone::get_VacantSpaces()
{
	return to_String_X4(vacantSpaces);
}

std::string Zone::get_VacantSpacesSeason()
{
    return to_String_X4(vacantSpacesSeason);
}

std::string Zone::get_VacantSpacesHourly()
{
    return to_String_X4(vacantSpacesHourly);
}

void Zone::entryHourly()
{
    vacantSpacesHourly--;
    vacantSpaces--;
    insert_update_Zone();
}

void Zone::exitHourly()
{
    vacantSpacesHourly++;
    vacantSpaces++;
    insert_update_Zone();
}

void Zone::entrySeason()
{
    vacantSpacesSeason--;
    vacantSpaces--;
    insert_update_Zone();
}

void Zone::exitSeason()
{
    vacantSpacesSeason++;
    vacantSpaces++;
    insert_update_Zone();
}

std::string Zone::to_String_X4(int v)
{
    v &= 0xffff;
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2 * sizeof(short))
            << std::hex << v;
    std::string v_temp_string = stream.str();
    std::string v_ = "    ";
    // s.Substring(2, 2) + s.Substring(0, 2
    v_[0] = toupper(v_temp_string[2]);
    v_[1] = toupper(v_temp_string[3]);
    //
    v_[2] = toupper(v_temp_string[0]);
    v_[3] = toupper(v_temp_string[1]);
    return v_;
}

std::string Zone::to_String_X2(int v)
{
    v &= 0xff;
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(sizeof(short))
            << std::hex << v;
    std::string v_temp_string = stream.str();
    std::string v_ = "  ";
    for (int i = 0; v_temp_string[i] != '\0'; i++)
    {
        v_[i] = toupper(v_temp_string[i]);
    }
    return v_;
}
