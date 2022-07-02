std::string to_String_X3_err(int v)
{
    v %= 999;
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(3) << v;
    std::string v_temp_string = stream.str();
    std::string v_ = "   ";
    for (int i = 0; v_temp_string[i] != '\0'; i++)
    {
        v_[i] = toupper(v_temp_string[i]);
    }
    return v_;
}

std::string to_String_X4_err(int v)
{
    v %= 9999;
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(4) << v;
    std::string v_temp_string = stream.str();
    std::string v_ = "    ";
    for (int i = 0; v_temp_string[i] != '\0'; i++)
    {
        v_[i] = toupper(v_temp_string[i]);
    }
    return v_;
}

std::string Off000DB_err_message(int err_number)
{
    std::string s = "";
    switch(err_number)
    {
        case -1001:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -1002:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -1003:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -1004:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -1005:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -1006:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -1007:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -1008:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -1009:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -1010:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -1011:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -1012:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -1013:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -1014:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -1015:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -1016:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -1017:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -1018:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -1019:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -1020:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -1021:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -1022:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -1023:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -1024:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -1025:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -1026:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -1027:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -1028:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -1029:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -1030:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -1031:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -1032:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -1033:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -1101:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -1102:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -1103:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -1104:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -1105:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -1106:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -1107:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -1108:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -1109:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -1110:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -1111:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -1112:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -1113:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -1114:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -1115:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -1116:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -1117:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -1118:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -1119:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -1120:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -1121:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -1122:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -1123:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -1124:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -1125:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -1126:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -1127:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -1128:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -1129:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -1130:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -1131:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -1132:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -1133:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -1134:
        {
            s = "Error while get inside outside sites variables addresses values during SELECT query";
        } 
        break;
        case -1135:
        {
            s = "Error while get inside outside sites variables addresses values during INSERT UPDATE query";
        } 
        break;
        case -1201:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -1202:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -1203:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -1204:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -1205:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -1206:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -1207:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -1208:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -1209:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -1210:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -1211:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -1212:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -1213:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -1214:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -1215:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -1216:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -1217:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -1218:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -1219:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -1220:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -1221:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -1222:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -1223:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -1224:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -1225:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -1226:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -1227:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -1228:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -1229:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -1230:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -1231:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -1232:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -1233:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -1401:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -1402:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -1403:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -1404:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -1405:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -1406:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -1407:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -1408:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -1409:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -1410:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -1411:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -1412:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -1413:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -1414:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -1415:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -1416:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -1417:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -1418:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -1419:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -1420:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -1421:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -1422:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -1423:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -1424:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -1425:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -1426:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -1427:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -1428:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -1429:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -1430:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -1431:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -1432:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -1433:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -1501:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -1502:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -1503:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -1504:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -1505:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -1506:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -1507:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -1508:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -1509:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -1510:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -1511:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -1512:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -1513:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -1514:
        {
            s = "mysql pointer is NULL during SELECT by address query";
        } 
        break;
        case -1515:
        {
            s = "mysql_stmt_init out of memory during SELECT by address query";
        } 
        break;
        case -1516:
        {
            s = "mysql_stmt_prepare faild during SELECT by address query";
        } 
        break;
        case -1517:
        {
            s = "mysql_stmt_bind_param failed during SELECT by address query";
        } 
        break;
        case -1518:
        {
            s = "invalid parameter count returned by MySQL during SELECT by address query";
        } 
        break;
        case -1519:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT by address query";
        } 
        break;
        case -1520:
        {
            s = "invalid column count returned by MySQL during SELECT by address query";
        } 
        break;
        case -1521:
        {
            s = "mysql_stmt_execute failed during SELECT by address query";
        } 
        break;
        case -1522:
        {
            s = "mysql_stmt_bind_result failed during SELECT by address query";
        } 
        break;
        case -1523:
        {
            s = "mysql_stmt_store_result failed during SELECT by address query";
        } 
        break;
        case -1524:
        {
            s = "mysql_stmt_fetch failed during SELECT by address query";
        } 
        break;
        case -1525:
        {
            s = "mysql_free_result failed during SELECT by address query";
        } 
        break;
        case -1526:
        {
            s = "mysql_stmt_close failed during SELECT by address query";
        } 
        break;
        case -1527:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -1528:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -1529:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -1530:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -1531:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -1532:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -1533:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -1534:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -1535:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -1536:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -1537:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -1538:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -1539:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -1540:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -1541:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -1542:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -1543:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -1544:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -1545:
        {
            s = "Error while get class variables values during SELECT by address query";
        } 
        break;
        case -1546:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -1547:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -1601:
        {
            s = "mysql pointer is NULL during SELECT by address query";
        } 
        break;
        case -1602:
        {
            s = "mysql_stmt_init out of memory during SELECT by address query";
        } 
        break;
        case -1603:
        {
            s = "mysql_stmt_prepare faild during SELECT by address query";
        } 
        break;
        case -1604:
        {
            s = "mysql_stmt_bind_param failed during SELECT by address query";
        } 
        break;
        case -1605:
        {
            s = "invalid parameter count returned by MySQL during SELECT by address query";
        } 
        break;
        case -1606:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT by address query";
        } 
        break;
        case -1607:
        {
            s = "invalid column count returned by MySQL during SELECT by address query";
        } 
        break;
        case -1608:
        {
            s = "mysql_stmt_execute failed during SELECT by address query";
        } 
        break;
        case -1609:
        {
            s = "mysql_stmt_bind_result failed during SELECT by address query";
        } 
        break;
        case -1610:
        {
            s = "mysql_stmt_store_result failed during SELECT by address query";
        } 
        break;
        case -1611:
        {
            s = "mysql_stmt_fetch failed during SELECT by address query";
        } 
        break;
        case -1612:
        {
            s = "mysql_free_result failed during SELECT by address query";
        } 
        break;
        case -1613:
        {
            s = "mysql_stmt_close failed during SELECT by address query";
        } 
        break;
        case -1614:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -1615:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -1616:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -1617:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -1618:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -1619:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -1620:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -1621:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -1622:
        {
            s = "mysql pointer is NULL during INSERT UPDATE site query";
        } 
        break;
        case -1623:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE site query";
        } 
        break;
        case -1624:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE site query";
        } 
        break;
        case -1625:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE site query";
        } 
        break;
        case -1626:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE site query";
        } 
        break;
        case -1627:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE site query";
        } 
        break;
        case -1628:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE site query";
        } 
        break;
        case -1629:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE site query";
        } 
        break;
        case -1630:
        {
            s = "mysql pointer is NULL during CLEAR sites query";
        } 
        break;
        case -1631:
        {
            s = "mysql_stmt_init out of memory during CLEAR sites query";
        } 
        break;
        case -1632:
        {
            s = "mysql_stmt_prepare faild during CLEAR sites query";
        } 
        break;
        case -1633:
        {
            s = "mysql_stmt_bind_param failed during CLEAR sites query";
        } 
        break;
        case -1634:
        {
            s = "invalid parameter count returned by MySQL during CLEAR sites query";
        } 
        break;
        case -1635:
        {
            s = "mysql_stmt_execute failed during CLEAR sites query";
        } 
        break;
        case -1636:
        {
            s = "mysql_stmt_affected_rows failed during CLEAR sites query";
        } 
        break;
        case -1637:
        {
            s = "mysql_stmt_close failed during CLEAR sites query";
        } 
        break;
        case -1638:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -1639:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -1640:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -1641:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -1642:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -1643:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -1644:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -1645:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -1646:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -1647:
        {
            s = "Error while get class variables values during SELECT by address query";
        } 
        break;
        case -1648:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -1649:
        {
            s = "Error while get class variables values during UPDATE sites query";
        } 
        break;
        case -1650:
        {
            s = "Error while get class variables values during CLEAR sites query";
        } 
        break;
        case -1651:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -1652:
        {
            s = "Error while get binded sites variables addresses values during SELECT query";
        } 
        break;
        case -1653:
        {
            s = "Error while get binded sites variables addresses values during INSERT UPDATE query";
        } 
        break;
        case -1654:
        {
            s = "Error while Clear binded sites variables addresses values during CLEAR query";
        } 
        break;
        case -1655:
        {
            s = "Error while Clear binded sites variables addresses values during UPDATE sites query";
        } 
        break;
        case -1656:
        {
            s = "mysql pointer is NULL during UPDATE sites query";
        } 
        break;
        case -1657:
        {
            s = "mysql_stmt_init out of memory during UPDATE sites query";
        } 
        break;
        case -1658:
        {
            s = "mysql_stmt_prepare faild during UPDATE sites query";
        } 
        break;
        case -1659:
        {
            s = "mysql_stmt_bind_param failed during UPDATE sites query";
        } 
        break;
        case -1660:
        {
            s = "invalid parameter count returned by MySQL during UPDATE sites query";
        } 
        break;
        case -1661:
        {
            s = "mysql_stmt_execute failed during UPDATE sites query";
        } 
        break;
        case -1662:
        {
            s = "mysql_stmt_affected_rows failed during UPDATE sites query";
        } 
        break;
        case -1663:
        {
            s = "mysql_stmt_close failed during UPDATE sites query";
        } 
        break;
        case -1801:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -1802:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -1803:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -1804:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -1805:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -1806:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -1807:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -1808:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -1809:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -1810:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -1811:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -1812:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -1813:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -1814:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -1815:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -1816:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -1817:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -1818:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -1819:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -1820:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -1821:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -1822:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -1823:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -1824:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -1825:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -1826:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -1827:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -1828:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -1829:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -1830:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -1831:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -1832:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -1833:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -1834:
        {
            s = "Error while get binded sites list values during SELECT query";
        } 
        break;
        case -1835:
        {
            s = "Error while get binded sites list values during INSERT UPDATE query";
        } 
        break;
        case -1901:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -1902:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -1903:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -1904:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -1905:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -1906:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -1907:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -1908:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -1909:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -1910:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -1911:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -1912:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -1913:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -1914:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -1915:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -1916:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -1917:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -1918:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -1919:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -1920:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -1921:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -1922:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -1923:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -1924:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -1925:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -1926:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -1927:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -1928:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -1929:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -1930:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -1931:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -1932:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -1933:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -2001:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -2002:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -2003:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -2004:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -2005:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -2006:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -2007:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -2008:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -2009:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -2010:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -2011:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -2012:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -2013:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -2014:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -2015:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -2016:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -2017:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -2018:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -2019:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -2020:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -2021:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -2022:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -2023:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -2024:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -2025:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -2026:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -2027:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -2028:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -2029:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -2030:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -2031:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -2032:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -2033:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -2101:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -2102:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -2103:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -2104:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -2105:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -2106:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -2107:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -2108:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -2109:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -2110:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -2111:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -2112:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -2113:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -2114:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -2115:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -2116:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -2117:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -2118:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -2119:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -2120:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -2121:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -2122:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -2123:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -2124:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -2125:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -2126:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -2127:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -2128:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -2129:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -2130:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -2131:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -2132:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -2133:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -2201:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -2202:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -2203:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -2204:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -2205:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -2206:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -2207:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -2208:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -2209:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -2210:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -2211:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -2212:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -2213:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -2214:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -2215:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -2216:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -2217:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -2218:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -2219:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -2220:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -2221:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -2222:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -2223:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -2224:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -2225:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -2226:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -2227:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -2228:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -2229:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -2230:
        {
            s = "mysql pointer is NULL during DELETE by rule name id query";
        } 
        break;
        case -2231:
        {
            s = "mysql_stmt_init out of memory during DELETE by rule name id query";
        } 
        break;
        case -2232:
        {
            s = "mysql_stmt_prepare faild during DELETE by rule name id query";
        } 
        break;
        case -2233:
        {
            s = "mysql_stmt_bind_param failed during DELETE by rule name id query";
        } 
        break;
        case -2234:
        {
            s = "invalid parameter count returned by MySQL during DELETE by rule name id query";
        } 
        break;
        case -2235:
        {
            s = "mysql_stmt_execute failed during DELETE by rule name id query";
        } 
        break;
        case -2236:
        {
            s = "mysql_stmt_affected_rows failed during DELETE by rule name id query";
        } 
        break;
        case -2237:
        {
            s = "mysql_stmt_close failed during DELETE by rule name id query";
        } 
        break;
        case -2238:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -2239:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -2240:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -2241:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -2401:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -2402:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -2403:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -2404:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -2405:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -2406:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -2407:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -2408:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -2409:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -2410:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -2411:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -2412:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -2413:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -2414:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -2415:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -2416:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -2417:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -2418:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -2419:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -2420:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -2421:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -2422:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -2423:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -2424:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -2425:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -2426:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -2427:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -2428:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -2429:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -2430:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -2431:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -2432:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -2433:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -2501:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -2502:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -2503:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -2504:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -2505:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -2506:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -2507:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -2508:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -2509:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -2510:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -2511:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -2512:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -2513:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -2514:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -2515:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -2516:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -2517:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -2518:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -2519:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -2520:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -2521:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -2522:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -2523:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -2524:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -2525:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -2526:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -2527:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -2528:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -2529:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -2530:
        {
            s = "mysql pointer is NULL during DELETE by rule name id query";
        } 
        break;
        case -2531:
        {
            s = "mysql_stmt_init out of memory during DELETE by rule name id query";
        } 
        break;
        case -2532:
        {
            s = "mysql_stmt_prepare faild during DELETE by rule name id query";
        } 
        break;
        case -2533:
        {
            s = "mysql_stmt_bind_param failed during DELETE by rule name id query";
        } 
        break;
        case -2534:
        {
            s = "invalid parameter count returned by MySQL during DELETE by rule name id query";
        } 
        break;
        case -2535:
        {
            s = "mysql_stmt_execute failed during DELETE by rule name id query";
        } 
        break;
        case -2536:
        {
            s = "mysql_stmt_affected_rows failed during DELETE by rule name id query";
        } 
        break;
        case -2537:
        {
            s = "mysql_stmt_close failed during DELETE by rule name id query";
        } 
        break;
        case -2538:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -2539:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -2540:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -2541:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -2701:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -2702:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -2703:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -2704:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -2705:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -2706:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -2707:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -2708:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -2709:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -2710:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -2711:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -2712:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -2713:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -2714:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -2715:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -2716:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -2717:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -2718:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -2719:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -2720:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -2721:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -2722:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -2723:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -2724:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -2725:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -2726:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -2727:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -2728:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -2729:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -2730:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -2731:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -2732:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -2733:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -2901:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -2902:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -2903:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -2904:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -2905:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -2906:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -2907:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -2908:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -2909:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -2910:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -2911:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -2912:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -2913:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -2914:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -2915:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -2916:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -2917:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -2918:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -2919:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -2920:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -2921:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -2922:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -2923:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -2924:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -2925:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -2926:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -2927:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -2928:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -2929:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -2930:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -2931:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -2932:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -2933:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -3001:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -3002:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -3003:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -3004:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -3005:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -3006:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -3007:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -3008:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -3009:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -3010:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -3011:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -3012:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -3013:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -3014:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -3015:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -3016:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -3017:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -3018:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -3019:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -3020:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -3021:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -3022:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -3023:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -3024:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -3025:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -3026:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -3027:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -3028:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -3029:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -3030:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -3031:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -3032:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -3033:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -3101:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -3102:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -3103:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -3104:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -3105:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -3106:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -3107:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -3108:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -3109:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -3110:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -3111:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -3112:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -3113:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -3114:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -3115:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -3116:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -3117:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -3118:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -3119:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -3120:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -3121:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -3122:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -3123:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -3124:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -3125:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -3126:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -3127:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -3128:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -3129:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -3130:
        {
            s = "mysql pointer is NULL during DELETE ALL query";
        } 
        break;
        case -3131:
        {
            s = "mysql_stmt_init out of memory during DELETE ALL query";
        } 
        break;
        case -3132:
        {
            s = "mysql_stmt_prepare faild during DELETE ALL query";
        } 
        break;
        case -3133:
        {
            s = "mysql_stmt_execute failed during DELETE ALL query";
        } 
        break;
        case -3134:
        {
            s = "mysql_stmt_affected_rows failed during DELETE ALL query";
        } 
        break;
        case -3135:
        {
            s = "mysql_stmt_close failed during DELETE ALL query";
        } 
        break;
        case -3136:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -3137:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -3138:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -3139:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -3140:
        {
            s = "Error while get class variables values during DELETE ALL query";
        } 
        break;
        case -3201:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -3202:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -3203:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -3204:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -3205:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -3206:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -3207:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -3208:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -3209:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -3210:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -3211:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -3212:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -3213:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -3214:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -3215:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -3216:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -3217:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -3218:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -3219:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -3220:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -3221:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -3222:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -3223:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -3224:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -3225:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -3226:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -3227:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -3228:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -3229:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -3230:
        {
            s = "mysql pointer is NULL during DELETE ALL query";
        } 
        break;
        case -3231:
        {
            s = "mysql_stmt_init out of memory during DELETE ALL query";
        } 
        break;
        case -3232:
        {
            s = "mysql_stmt_prepare faild during DELETE ALL query";
        } 
        break;
        case -3233:
        {
            s = "mysql_stmt_execute failed during DELETE ALL query";
        } 
        break;
        case -3234:
        {
            s = "mysql_stmt_affected_rows failed during DELETE ALL query";
        } 
        break;
        case -3235:
        {
            s = "mysql_stmt_close failed during DELETE ALL query";
        } 
        break;
        case -3236:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -3237:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -3238:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -3239:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -3301:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -3302:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -3303:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -3304:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -3305:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -3306:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -3307:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -3308:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -3309:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -3310:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -3311:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -3312:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -3313:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -3314:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -3315:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -3316:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -3317:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -3318:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -3319:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -3320:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -3321:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -3322:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -3323:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -3324:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -3325:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -3326:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -3327:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -3328:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -3329:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -3330:
        {
            s = "mysql pointer is NULL during DELETE ALL query";
        } 
        break;
        case -3331:
        {
            s = "mysql_stmt_init out of memory during DELETE ALL query";
        } 
        break;
        case -3332:
        {
            s = "mysql_stmt_prepare faild during DELETE ALL query";
        } 
        break;
        case -3333:
        {
            s = "mysql_stmt_execute failed during DELETE ALL query";
        } 
        break;
        case -3334:
        {
            s = "mysql_stmt_affected_rows failed during DELETE ALL query";
        } 
        break;
        case -3335:
        {
            s = "mysql_stmt_close failed during DELETE ALL query";
        } 
        break;
        case -3336:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -3337:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -3338:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -3339:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -3401:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -3402:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -3403:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -3404:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -3405:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -3406:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -3407:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -3408:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -3409:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -3410:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -3411:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -3412:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -3413:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -3414:
        {
            s = "mysql pointer is NULL during SELECT TICKET query";
        } 
        break;
        case -3415:
        {
            s = "mysql_stmt_init out of memory during SELECT TICKET query";
        } 
        break;
        case -3416:
        {
            s = "mysql_stmt_prepare faild during SELECT TICKET query";
        } 
        break;
        case -3417:
        {
            s = "mysql_stmt_bind_param failed during SELECT TICKET query";
        } 
        break;
        case -3418:
        {
            s = "invalid parameter count returned by MySQL during SELECT TICKET query";
        } 
        break;
        case -3419:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT TICKET query";
        } 
        break;
        case -3420:
        {
            s = "invalid column count returned by MySQL during SELECT TICKET query";
        } 
        break;
        case -3421:
        {
            s = "mysql_stmt_execute failed during SELECT TICKET query";
        } 
        break;
        case -3422:
        {
            s = "mysql_stmt_bind_result failed during SELECT TICKET query";
        } 
        break;
        case -3423:
        {
            s = "mysql_stmt_store_result failed during SELECT TICKET query";
        } 
        break;
        case -3424:
        {
            s = "mysql_stmt_fetch failed during SELECT TICKET query";
        } 
        break;
        case -3425:
        {
            s = "mysql_free_result failed during SELECT TICKET query";
        } 
        break;
        case -3426:
        {
            s = "mysql_stmt_close failed during SELECT TICKET query";
        } 
        break;
        case -3427:
        {
            s = "mysql pointer is NULL during SELECT PLATE query";
        } 
        break;
        case -3428:
        {
            s = "mysql_stmt_init out of memory during SELECT PLATE query";
        } 
        break;
        case -3429:
        {
            s = "mysql_stmt_prepare faild during SELECT PLATE query";
        } 
        break;
        case -3430:
        {
            s = "mysql_stmt_bind_param failed during SELECT PLATE query";
        } 
        break;
        case -3431:
        {
            s = "invalid parameter count returned by MySQL during SELECT PLATE query";
        } 
        break;
        case -3432:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT PLATE query";
        } 
        break;
        case -3433:
        {
            s = "invalid column count returned by MySQL during SELECT PLATE query";
        } 
        break;
        case -3434:
        {
            s = "mysql_stmt_execute failed during SELECT PLATE query";
        } 
        break;
        case -3435:
        {
            s = "mysql_stmt_bind_result failed during SELECT PLATE query";
        } 
        break;
        case -3436:
        {
            s = "mysql_stmt_store_result failed during SELECT PLATE query";
        } 
        break;
        case -3437:
        {
            s = "mysql_stmt_fetch failed during SELECT PLATE query";
        } 
        break;
        case -3438:
        {
            s = "mysql_free_result failed during SELECT PLATE query";
        } 
        break;
        case -3439:
        {
            s = "mysql_stmt_close failed during SELECT PLATE query";
        } 
        break;
        case -3440:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -3441:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -3442:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -3443:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -3444:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -3445:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -3446:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -3447:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -3448:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -3449:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -3450:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -3451:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -3452:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -3453:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -3454:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -3455:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -3456:
        {
            s = "mysql pointer is NULL during DELETE ALL query";
        } 
        break;
        case -3457:
        {
            s = "mysql_stmt_init out of memory during DELETE ALL query";
        } 
        break;
        case -3458:
        {
            s = "mysql_stmt_prepare faild during DELETE ALL query";
        } 
        break;
        case -3459:
        {
            s = "mysql_stmt_execute failed during DELETE ALL query";
        } 
        break;
        case -3460:
        {
            s = "mysql_stmt_affected_rows failed during DELETE ALL query";
        } 
        break;
        case -3461:
        {
            s = "mysql_stmt_close failed during DELETE ALL query";
        } 
        break;
        case -3462:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -3463:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -3464:
        {
            s = "Error while get class variables values during SELECT TICKET query";
        } 
        break;
        case -3465:
        {
            s = "Error while get class variables values during SELECT PLATE query";
        } 
        break;
        case -3466:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -3467:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -3601:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -3602:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -3603:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -3604:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -3605:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -3606:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -3607:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -3608:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -3609:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -3610:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -3611:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -3612:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -3613:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -3614:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -3615:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -3616:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -3617:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -3618:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -3619:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -3620:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -3621:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -3622:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -3623:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -3624:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -3625:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -3626:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -3627:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -3628:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -3629:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -3630:
        {
            s = "mysql pointer is NULL during DELETE ALL query";
        } 
        break;
        case -3631:
        {
            s = "mysql_stmt_init out of memory during DELETE ALL query";
        } 
        break;
        case -3632:
        {
            s = "mysql_stmt_prepare faild during DELETE ALL query";
        } 
        break;
        case -3633:
        {
            s = "mysql_stmt_execute failed during DELETE ALL query";
        } 
        break;
        case -3634:
        {
            s = "mysql_stmt_affected_rows failed during DELETE ALL query";
        } 
        break;
        case -3635:
        {
            s = "mysql_stmt_close failed during DELETE ALL query";
        } 
        break;
        case -3636:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -3637:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -3638:
        {
            s = "Error while get class variables values during SELECT by id and gid query";
        } 
        break;
        case -3639:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -3640:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -3701:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -3702:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -3703:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -3704:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -3705:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -3706:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -3707:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -3708:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -3709:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -3710:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -3711:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -3712:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -3713:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -3714:
        {
            s = "mysql pointer is NULL during SELECT TICKET query";
        } 
        break;
        case -3715:
        {
            s = "mysql_stmt_init out of memory during SELECT TICKET query";
        } 
        break;
        case -3716:
        {
            s = "mysql_stmt_prepare faild during SELECT TICKET query";
        } 
        break;
        case -3717:
        {
            s = "mysql_stmt_bind_param failed during SELECT TICKET query";
        } 
        break;
        case -3718:
        {
            s = "invalid parameter count returned by MySQL during SELECT TICKET query";
        } 
        break;
        case -3719:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT TICKET query";
        } 
        break;
        case -3720:
        {
            s = "invalid column count returned by MySQL during SELECT TICKET query";
        } 
        break;
        case -3721:
        {
            s = "mysql_stmt_execute failed during SELECT TICKET query";
        } 
        break;
        case -3722:
        {
            s = "mysql_stmt_bind_result failed during SELECT TICKET query";
        } 
        break;
        case -3723:
        {
            s = "mysql_stmt_store_result failed during SELECT TICKET query";
        } 
        break;
        case -3724:
        {
            s = "mysql_stmt_fetch failed during SELECT TICKET query";
        } 
        break;
        case -3725:
        {
            s = "mysql_free_result failed during SELECT TICKET query";
        } 
        break;
        case -3726:
        {
            s = "mysql_stmt_close failed during SELECT TICKET query";
        } 
        break;
        case -3727:
        {
            s = "mysql pointer is NULL during SELECT PLATE query";
        } 
        break;
        case -3728:
        {
            s = "mysql_stmt_init out of memory during SELECT PLATE query";
        } 
        break;
        case -3729:
        {
            s = "mysql_stmt_prepare faild during SELECT PLATE query";
        } 
        break;
        case -3730:
        {
            s = "mysql_stmt_bind_param failed during SELECT PLATE query";
        } 
        break;
        case -3731:
        {
            s = "invalid parameter count returned by MySQL during SELECT PLATE query";
        } 
        break;
        case -3732:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT PLATE query";
        } 
        break;
        case -3733:
        {
            s = "invalid column count returned by MySQL during SELECT PLATE query";
        } 
        break;
        case -3734:
        {
            s = "mysql_stmt_execute failed during SELECT PLATE query";
        } 
        break;
        case -3735:
        {
            s = "mysql_stmt_bind_result failed during SELECT PLATE query";
        } 
        break;
        case -3736:
        {
            s = "mysql_stmt_store_result failed during SELECT PLATE query";
        } 
        break;
        case -3737:
        {
            s = "mysql_stmt_fetch failed during SELECT PLATE query";
        } 
        break;
        case -3738:
        {
            s = "mysql_free_result failed during SELECT PLATE query";
        } 
        break;
        case -3739:
        {
            s = "mysql_stmt_close failed during SELECT PLATE query";
        } 
        break;
        case -3740:
        {
            s = "mysql pointer is NULL during INSERT query";
        } 
        break;
        case -3741:
        {
            s = "mysql_stmt_init out of memory during INSERT query";
        } 
        break;
        case -3742:
        {
            s = "mysql_stmt_prepare faild during INSERT query";
        } 
        break;
        case -3743:
        {
            s = "mysql_stmt_bind_param failed during INSERT query";
        } 
        break;
        case -3744:
        {
            s = "invalid parameter count returned by MySQL during INSERT query";
        } 
        break;
        case -3745:
        {
            s = "mysql_stmt_execute failed during INSERT query";
        } 
        break;
        case -3746:
        {
            s = "mysql_stmt_affected_rows failed during INSERT query";
        } 
        break;
        case -3747:
        {
            s = "mysql_stmt_close failed during INSERT query";
        } 
        break;
        case -3748:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -3749:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -3750:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -3751:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -3752:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -3753:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -3754:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -3755:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -3756:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -3757:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -3758:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -3759:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -3760:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -3761:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -3762:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -3763:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -3764:
        {
            s = "mysql pointer is NULL during DELETE ALL query";
        } 
        break;
        case -3765:
        {
            s = "mysql_stmt_init out of memory during DELETE ALL query";
        } 
        break;
        case -3766:
        {
            s = "mysql_stmt_prepare faild during DELETE ALL query";
        } 
        break;
        case -3767:
        {
            s = "mysql_stmt_execute failed during DELETE ALL query";
        } 
        break;
        case -3768:
        {
            s = "mysql_stmt_affected_rows failed during DELETE ALL query";
        } 
        break;
        case -3769:
        {
            s = "mysql_stmt_close failed during DELETE ALL query";
        } 
        break;
        case -3770:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -3771:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -3772:
        {
            s = "Error while get class variables values during SELECT TICKET query";
        } 
        break;
        case -3773:
        {
            s = "Error while get class variables values during SELECT PLATE query";
        } 
        break;
        case -3774:
        {
            s = "Error while get class variables values during INSERT query";
        } 
        break;
        case -3775:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -3776:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -3801:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -3802:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -3803:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -3804:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -3805:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -3806:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -3807:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -3808:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -3809:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -3810:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -3811:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -3812:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -3813:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -3814:
        {
            s = "mysql pointer is NULL during SELECT TICKET query";
        } 
        break;
        case -3815:
        {
            s = "mysql_stmt_init out of memory during SELECT TICKET query";
        } 
        break;
        case -3816:
        {
            s = "mysql_stmt_prepare faild during SELECT TICKET query";
        } 
        break;
        case -3817:
        {
            s = "mysql_stmt_bind_param failed during SELECT TICKET query";
        } 
        break;
        case -3818:
        {
            s = "invalid parameter count returned by MySQL during SELECT TICKET query";
        } 
        break;
        case -3819:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT TICKET query";
        } 
        break;
        case -3820:
        {
            s = "invalid column count returned by MySQL during SELECT TICKET query";
        } 
        break;
        case -3821:
        {
            s = "mysql_stmt_execute failed during SELECT TICKET query";
        } 
        break;
        case -3822:
        {
            s = "mysql_stmt_bind_result failed during SELECT TICKET query";
        } 
        break;
        case -3823:
        {
            s = "mysql_stmt_store_result failed during SELECT TICKET query";
        } 
        break;
        case -3824:
        {
            s = "mysql_stmt_fetch failed during SELECT TICKET query";
        } 
        break;
        case -3825:
        {
            s = "mysql_free_result failed during SELECT TICKET query";
        } 
        break;
        case -3826:
        {
            s = "mysql_stmt_close failed during SELECT TICKET query";
        } 
        break;
        case -3827:
        {
            s = "mysql pointer is NULL during SELECT PLATE query";
        } 
        break;
        case -3828:
        {
            s = "mysql_stmt_init out of memory during SELECT PLATE query";
        } 
        break;
        case -3829:
        {
            s = "mysql_stmt_prepare faild during SELECT PLATE query";
        } 
        break;
        case -3830:
        {
            s = "mysql_stmt_bind_param failed during SELECT PLATE query";
        } 
        break;
        case -3831:
        {
            s = "invalid parameter count returned by MySQL during SELECT PLATE query";
        } 
        break;
        case -3832:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT PLATE query";
        } 
        break;
        case -3833:
        {
            s = "invalid column count returned by MySQL during SELECT PLATE query";
        } 
        break;
        case -3834:
        {
            s = "mysql_stmt_execute failed during SELECT PLATE query";
        } 
        break;
        case -3835:
        {
            s = "mysql_stmt_bind_result failed during SELECT PLATE query";
        } 
        break;
        case -3836:
        {
            s = "mysql_stmt_store_result failed during SELECT PLATE query";
        } 
        break;
        case -3837:
        {
            s = "mysql_stmt_fetch failed during SELECT PLATE query";
        } 
        break;
        case -3838:
        {
            s = "mysql_free_result failed during SELECT PLATE query";
        } 
        break;
        case -3839:
        {
            s = "mysql_stmt_close failed during SELECT PLATE query";
        } 
        break;
        case -3840:
        {
            s = "mysql pointer is NULL during INSERT query";
        } 
        break;
        case -3841:
        {
            s = "mysql_stmt_init out of memory during INSERT query";
        } 
        break;
        case -3842:
        {
            s = "mysql_stmt_prepare faild during INSERT query";
        } 
        break;
        case -3843:
        {
            s = "mysql_stmt_bind_param failed during INSERT query";
        } 
        break;
        case -3844:
        {
            s = "invalid parameter count returned by MySQL during INSERT query";
        } 
        break;
        case -3845:
        {
            s = "mysql_stmt_execute failed during INSERT query";
        } 
        break;
        case -3846:
        {
            s = "mysql_stmt_affected_rows failed during INSERT query";
        } 
        break;
        case -3847:
        {
            s = "mysql_stmt_close failed during INSERT query";
        } 
        break;
        case -3848:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -3849:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -3850:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -3851:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -3852:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -3853:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -3854:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -3855:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -3856:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -3857:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -3858:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -3859:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -3860:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -3861:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -3862:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -3863:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -3864:
        {
            s = "mysql pointer is NULL during DELETE ALL query";
        } 
        break;
        case -3865:
        {
            s = "mysql_stmt_init out of memory during DELETE ALL query";
        } 
        break;
        case -3866:
        {
            s = "mysql_stmt_prepare faild during DELETE ALL query";
        } 
        break;
        case -3867:
        {
            s = "mysql_stmt_execute failed during DELETE ALL query";
        } 
        break;
        case -3868:
        {
            s = "mysql_stmt_affected_rows failed during DELETE ALL query";
        } 
        break;
        case -3869:
        {
            s = "mysql_stmt_close failed during DELETE ALL query";
        } 
        break;
        case -3870:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -3871:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -3872:
        {
            s = "Error while get class variables values during SELECT TICKET query";
        } 
        break;
        case -3873:
        {
            s = "Error while get class variables values during SELECT PLATE query";
        } 
        break;
        case -3874:
        {
            s = "Error while get class variables values during INSERT query";
        } 
        break;
        case -3875:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -3876:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -3901:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -3902:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -3903:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -3904:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -3905:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -3906:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -3907:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -3908:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -3909:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -3910:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -3911:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -3912:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -3913:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -3914:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -3915:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -3916:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -3917:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -3918:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -3919:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -3920:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -3921:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -3922:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -3923:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -3924:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -3925:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -3926:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -3927:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -3928:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -3929:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -3930:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -3931:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -3932:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -3933:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -4001:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -4002:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -4003:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -4004:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -4005:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -4006:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -4007:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -4008:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -4009:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -4010:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -4011:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -4012:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -4013:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -4014:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -4015:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -4016:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -4017:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -4018:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -4019:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -4020:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -4021:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -4022:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -4023:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -4024:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -4025:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -4026:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -4027:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -4028:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -4029:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -4030:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -4031:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -4032:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -4033:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -4101:
        {
            s = "mysql pointer is NULL during SELECT query";
        } 
        break;
        case -4102:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        } 
        break;
        case -4103:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        } 
        break;
        case -4104:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        } 
        break;
        case -4105:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        } 
        break;
        case -4106:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        } 
        break;
        case -4107:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        } 
        break;
        case -4108:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        } 
        break;
        case -4109:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        } 
        break;
        case -4110:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        } 
        break;
        case -4111:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        } 
        break;
        case -4112:
        {
            s = "mysql_free_result failed during SELECT query";
        } 
        break;
        case -4113:
        {
            s = "mysql_stmt_close failed during SELECT query";
        } 
        break;
        case -4114:
        {
            s = "mysql pointer is NULL during SELECT PLATE query";
        } 
        break;
        case -4115:
        {
            s = "mysql_stmt_init out of memory during SELECT PLATE query";
        } 
        break;
        case -4116:
        {
            s = "mysql_stmt_prepare faild during SELECT PLATE query";
        } 
        break;
        case -4117:
        {
            s = "mysql_stmt_bind_param failed during SELECT PLATE query";
        } 
        break;
        case -4118:
        {
            s = "invalid parameter count returned by MySQL during SELECT PLATE query";
        } 
        break;
        case -4119:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT PLATE query";
        } 
        break;
        case -4120:
        {
            s = "invalid column count returned by MySQL during SELECT PLATE query";
        } 
        break;
        case -4121:
        {
            s = "mysql_stmt_execute failed during SELECT PLATE query";
        } 
        break;
        case -4122:
        {
            s = "mysql_stmt_bind_result failed during SELECT PLATE query";
        } 
        break;
        case -4123:
        {
            s = "mysql_stmt_store_result failed during SELECT PLATE query";
        } 
        break;
        case -4124:
        {
            s = "mysql_stmt_fetch failed during SELECT PLATE query";
        } 
        break;
        case -4125:
        {
            s = "mysql_free_result failed during SELECT PLATE query";
        } 
        break;
        case -4126:
        {
            s = "mysql_stmt_close failed during SELECT PLATE query";
        } 
        break;
        case -4127:
        {
            s = "mysql pointer is NULL during INSERT query";
        } 
        break;
        case -4128:
        {
            s = "mysql_stmt_init out of memory during INSERT query";
        } 
        break;
        case -4129:
        {
            s = "mysql_stmt_prepare faild during INSERT query";
        } 
        break;
        case -4130:
        {
            s = "mysql_stmt_bind_param failed during INSERT query";
        } 
        break;
        case -4131:
        {
            s = "invalid parameter count returned by MySQL during INSERT query";
        } 
        break;
        case -4132:
        {
            s = "mysql_stmt_execute failed during INSERT query";
        } 
        break;
        case -4133:
        {
            s = "mysql_stmt_affected_rows failed during INSERT query";
        } 
        break;
        case -4134:
        {
            s = "mysql_stmt_close failed during INSERT query";
        } 
        break;
        case -4135:
        {
            s = "mysql pointer is NULL during INSERT UPDATE query";
        } 
        break;
        case -4136:
        {
            s = "mysql_stmt_init out of memory during INSERT UPDATE query";
        } 
        break;
        case -4137:
        {
            s = "mysql_stmt_prepare faild during INSERT UPDATE query";
        } 
        break;
        case -4138:
        {
            s = "mysql_stmt_bind_param failed during INSERT UPDATE query";
        } 
        break;
        case -4139:
        {
            s = "invalid parameter count returned by MySQL during INSERT UPDATE query";
        } 
        break;
        case -4140:
        {
            s = "mysql_stmt_execute failed during INSERT UPDATE query";
        } 
        break;
        case -4141:
        {
            s = "mysql_stmt_affected_rows failed during INSERT UPDATE query";
        } 
        break;
        case -4142:
        {
            s = "mysql_stmt_close failed during INSERT UPDATE query";
        } 
        break;
        case -4143:
        {
            s = "mysql pointer is NULL during DELETE query";
        } 
        break;
        case -4144:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        } 
        break;
        case -4145:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        } 
        break;
        case -4146:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        } 
        break;
        case -4147:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        } 
        break;
        case -4148:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        } 
        break;
        case -4149:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        } 
        break;
        case -4150:
        {
            s = "mysql_stmt_close failed during DELETE query";
        } 
        break;
        case -4151:
        {
            s = "mysql pointer is NULL during DELETE ALL query";
        } 
        break;
        case -4152:
        {
            s = "mysql_stmt_init out of memory during DELETE ALL query";
        } 
        break;
        case -4153:
        {
            s = "mysql_stmt_prepare faild during DELETE ALL query";
        } 
        break;
        case -4154:
        {
            s = "mysql_stmt_execute failed during DELETE ALL query";
        } 
        break;
        case -4155:
        {
            s = "mysql_stmt_affected_rows failed during DELETE ALL query";
        } 
        break;
        case -4156:
        {
            s = "mysql_stmt_close failed during DELETE ALL query";
        } 
        break;
        case -4157:
        {
            s = "Error while get class variables values during PRINT function";
        } 
        break;
        case -4158:
        {
            s = "Error while get class variables values during SELECT query";
        } 
        break;
        case -4159:
        {
            s = "Error while get class variables values during SELECT PLATE query";
        } 
        break;
        case -4160:
        {
            s = "Error while get class variables values during INSERT query";
        } 
        break;
        case -4161:
        {
            s = "Error while get class variables values during INSERT UPDATE query";
        } 
        break;
        case -4162:
        {
            s = "Error while get class variables values during DELETE query";
        } 
        break;
        case -4201:
        {
            s = "mysql pointer is NULL during SELECT query";
        }
        break;
        case -4202:
        {
            s = "mysql_stmt_init out of memory during SELECT query";
        }
        break;
        case -4203:
        {
            s = "mysql_stmt_prepare faild during SELECT query";
        }
        break;
        case -4204:
        {
            s = "mysql_stmt_bind_param failed during SELECT query";
        }
        break;
        case -4205:
        {
            s = "invalid parameter count returned by MySQL during SELECT query";
        }
        break;
        case -4206:
        {
            s = "mysql_stmt_result_metadata returned no meta information during SELECT query";
        }
        break;
        case -4207:
        {
            s = "invalid column count returned by MySQL during SELECT query";
        }
        break;
        case -4208:
        {
            s = "mysql_stmt_execute failed during SELECT query";
        }
        break;
        case -4209:
        {
            s = "mysql_stmt_bind_result failed during SELECT query";
        }
        break;
        case -4210:
        {
            s = "mysql_stmt_store_result failed during SELECT query";
        }
        break;
        case -4211:
        {
            s = "mysql_stmt_fetch failed during SELECT query";
        }
        break;
        case -4212:
        {
            s = "mysql_free_result failed during SELECT query";
        }
        break;
        case -4213:
        {
            s = "mysql_stmt_close failed during SELECT query";
        }
        break;
        case -4214:
        {
            s = "mysql pointer is NULL during INSERT query";
        }
        break;
        case -4215:
        {
            s = "mysql_stmt_init out of memory during INSERT query";
        }
        break;
        case -4216:
        {
            s = "mysql_stmt_prepare faild during INSERT query";
        }
        break;
        case -4217:
        {
            s = "mysql_stmt_bind_param failed during INSERT query";
        }
        break;
        case -4218:
        {
            s = "invalid parameter count returned by MySQL during INSERT query";
        }
        break;
        case -4219:
        {
            s = "mysql_stmt_execute failed during INSERT query";
        }
        break;
        case -4220:
        {
            s = "mysql_stmt_affected_rows failed during INSERT query";
        }
        break;
        case -4221:
        {
            s = "mysql_stmt_close failed during INSERT query";
        }
        break;
        case -4222:
        {
            s = "mysql pointer is NULL during DELETE query";
        }
        break;
        case -4223:
        {
            s = "mysql_stmt_init out of memory during DELETE query";
        }
        break;
        case -4224:
        {
            s = "mysql_stmt_prepare faild during DELETE query";
        }
        break;
        case -4225:
        {
            s = "mysql_stmt_bind_param failed during DELETE query";
        }
        break;
        case -4226:
        {
            s = "invalid parameter count returned by MySQL during DELETE query";
        }
        break;
        case -4227:
        {
            s = "mysql_stmt_execute failed during DELETE query";
        }
        break;
        case -4228:
        {
            s = "mysql_stmt_affected_rows failed during DELETE query";
        }
        break;
        case -4229:
        {
            s = "mysql_stmt_close failed during DELETE query";
        }
        break;
        case -4230:
        {
            s = "mysql pointer is NULL during DELETE ALL query";
        }
        break;
        case -4231:
        {
            s = "mysql_stmt_init out of memory during DELETE ALL query";
        }
        break;
        case -4232:
        {
            s = "mysql_stmt_prepare faild during DELETE ALL query";
        }
        break;
        case -4233:
        {
            s = "mysql_stmt_execute failed during DELETE ALL query";
        }
        break;
        case -4234:
        {
            s = "mysql_stmt_affected_rows failed during DELETE ALL query";
        }
        break;
        case -4235:
        {
            s = "mysql_stmt_close failed during DELETE ALL query";
        }
        break;
        case -4236:
        {
            s = "Error while get class variables values during PRINT function";
        }
        break;
        case -4237:
        {
            s = "Error while get class variables values during SELECT query";
        }
        break;
        case -4238:
        {
            s = "Error while get class variables values during INSERT query";
        }
        break;
        case -4239:
        {
            s = "Error while get class variables values during DELETE query";
        }
        break;
        case -4240:
        {
            s = "Error while get class variables values during DELETE ALL query";
        }
        break;
        case -5001:
        {
            s = "mysql init failed";
        }
        break;
        case -5002:
        {
            s = "mysql real connect failed or database not exist";
        }
        break;
        case -5003:
        {
            s = "thread config_thread creation failed";
        }
        break;
        case -5004:
        {
            s = "Error initialize..!";
        }
        break;
        case -5005:
        {
            s = "Can't Create Server!..";
        }
        break;
        case -5006:
        {
            s = "The Server Can't Start Listening..";
        }
        break;
        case -5007:
        {
            s = "Error process_server thread..!";
        }
        break;
        case -5008:
        {
            s = "Error at mysql_query while reading black_list table";
        }
        break;
        case -5009:
        {
            s = "mysql_store_result faild while reading black_list table";
        }
        break;
        case -5010:
        {
            s = "mysql_fetch_row faild while reading black_list table";
        }
        break;
        case -5011:
        {
            s = "Error at mysql_query while reading rule_name_hourly table";
        }
        break;
        case -5012:
        {
            s = "mysql_store_result faild while reading rule_name_hourly table";
        }
        break;
        case -5013:
        {
            s = "mysql_fetch_row faild while reading rule_name_hourly table";
        }
        break;
        case -5014:
        {
            s = "Error at mysql_query while reading Zone table";
        }
        break;
        case -5015:
        {
            s = "mysql_store_result faild while reading Zone table";
        }
        break;
        case -5016:
        {
            s = "mysql_fetch_row faild while reading Zone table";
        }
        break;
        case -5017:
        {
            s = "Error at mysql_query while reading monthly_to_hourly table";
        }
        break;
        case -5018:
        {
            s = "mysql_store_result faild while reading monthly_to_hourly table";
        }
        break;
        case -5019:
        {
            s = "mysql_fetch_row faild while reading monthly_to_hourly table";
        }
        break;
        case -5020:
        {
            s = "Error at mysql_query while reading camera table";
        }
        break;
        case -5021:
        {
            s = "mysql_store_result faild while reading camera table";
        }
        break;
        case -5022:
        {
            s = "mysql_fetch_row faild while reading camera table";
        }
        break;
        case -5023:
        {
            s = "Error at mysql_query while reading account_info table";
        }
        break;
        case -5024:
        {
            s = "mysql_store_result faild while reading account_info table";
        }
        break;
        case -5025:
        {
            s = "mysql_fetch_row faild while reading account_info table";
        }
        break;
        case -5026:
        {
            s = "Error at mysql_query while reading account_state table";
        }
        break;
        case -5027:
        {
            s = "mysql_store_result faild while reading account_state table";
        }
        break;
        case -5028:
        {
            s = "mysql_fetch_row faild while reading account_state table";
        }
        break;
        case -5029:
        {
            s = "Error at mysql_query while reading event_in table";
        }
        break;
        case -5030:
        {
            s = "mysql_store_result faild while reading event_in table";
        }
        break;
        case -5031:
        {
            s = "mysql_fetch_row faild while reading event_in table";
        }
        break;
        case -5032:
        {
            s = "Error at mysql_query while reading event_out table";
        }
        break;
        case -5033:
        {
            s = "mysql_store_result faild while reading event_out table";
        }
        break;
        case -5034:
        {
            s = "mysql_fetch_row faild while reading event_out table";
        }
        break;
        case -5035:
        {
            s = "Error at mysql_query while reading event_payment table";
        }
        break;
        case -5036:
        {
            s = "mysql_store_result faild while reading event_payment table";
        }
        break;
        case -5037:
        {
            s = "mysql_fetch_row faild while reading event_payment table";
        }
        break;
        case -5038:
        {
            s = "Error at mysql_query while reading event_charge table";
        }
        break;
        case -5039:
        {
            s = "mysql_store_result faild while reading event_charge table";
        }
        break;
        case -5040:
        {
            s = "mysql_fetch_row faild while reading event_charge table";
        }
        break;
        case -5041:
        {
            s = "Error at mysql_query while reading temp_card table";
        }
        break;
        case -5042:
        {
            s = "mysql_store_result faild while reading temp_card table";
        }
        break;
        case -5043:
        {
            s = "mysql_fetch_row faild while reading temp_card table";
        }
        break;
        case -5044:
        {
            s = "Error at mysql_query while reading group_inner table";
        }
        break;
        case -5045:
        {
            s = "mysql_store_result faild while reading group_inner table";
        }
        break;
        case -5046:
        {
            s = "mysql_fetch_row faild while reading group_inner table";
        }
        break;
        case -5047:
        {
            s = "Error at mysql_query while reading monthly_type table";
        }
        break;
        case -5048:
        {
            s = "mysql_store_result faild while reading monthly_type table";
        }
        break;
        case -5049:
        {
            s = "mysql_fetch_row faild while reading monthly_type table";
        }
        break;
        case -5050:
        {
            s = "Error at mysql_query while reading rule_name_monthly table";
        }
        break;
        case -5051:
        {
            s = "mysql_store_result faild while reading rule_name_monthly table";
        }
        break;
        case -5052:
        {
            s = "mysql_fetch_row faild while reading rule_name_monthly table";
        }
        break;
        case -5053:
        {
            s = "Error at mysql_query while reading rule_step_monthly table";
        }
        break;
        case -5054:
        {
            s = "mysql_store_result faild while reading rule_step_monthly table";
        }
        break;
        case -5055:
        {
            s = "mysql_fetch_row faild while reading rule_step_monthly table";
        }
        break;
        case -5056:
        {
            s = "Error at mysql_query while getting account_info insert id";
        }
        break;
        case -5057:
        {
            s = "mysql_store_result faild while getting account_info insert id";
        }
        break;
        case -5058:
        {
            s = "mysql_fetch_row faild while getting account_info insert id";
        }
        break;
        case -5059:
        {
            s = "Error at mysql_query while getting account_state insert id";
        }
        break;
        case -5060:
        {
            s = "mysql_store_result faild while getting account_state insert id";
        }
        break;
        case -5061:
        {
            s = "mysql_fetch_row faild while getting account_state insert id";
        }
        break;
        case -5062:
        {
            s = "Error at mysql_query while getting event_in insert id";
        }
        break;
        case -5063:
        {
            s = "mysql_store_result faild while getting event_in insert id";
        }
        break;
        case -5064:
        {
            s = "mysql_fetch_row faild while getting event_in insert id";
        }
        break;
        case -5065:
        {
            s = "Error at mysql_query while getting event_out insert id";
        }
        break;
        case -5066:
        {
            s = "mysql_store_result faild while getting event_out insert id";
        }
        break;
        case -5067:
        {
            s = "mysql_fetch_row faild while getting event_out insert id";
        }
        break;
        case -5068:
        {
            s = "Error at mysql_query while getting event_payment insert id";
        }
        break;
        case -5069:
        {
            s = "mysql_store_result faild while getting event_payment insert id";
        }
        break;
        case -5070:
        {
            s = "mysql_fetch_row faild while getting event_payment insert id";
        }
        break;
        case -5071:
        {
            s = "Error at mysql_query while getting event_charge insert id";
        }
        break;
        case -5072:
        {
            s = "mysql_store_result faild while getting event_charge insert id";
        }
        break;
        case -5073:
        {
            s = "mysql_fetch_row faild while getting event_charge insert id";
        }
        break;
        case -5074:
        {
            s = "Error at mysql_query while getting temp_card insert id";
        }
        break;
        case -5075:
        {
            s = "mysql_store_result faild while getting temp_card insert id";
        }
        break;
        case -5076:
        {
            s = "mysql_fetch_row faild while getting temp_card insert id";
        }
        break;
        case -5077:
        {
            s = "Error at mysql_query while getting monthly_type aid";
        }
        break;
        case -5078:
        {
            s = "mysql_store_result faild while getting monthly_type aid";
        }
        break;
        case -5079:
        {
            s = "mysql_fetch_row faild while getting monthly_type aid";
        }
        break;
        case -5080:
        {
            s = "Error at mysql_query while getting monthly_type insert id";
        }
        break;
        case -5081:
        {
            s = "mysql_store_result faild while getting monthly_type insert id";
        }
        break;
        case -5082:
        {
            s = "mysql_fetch_row faild while getting monthly_type insert id";
        }
        break;
        case -5083:
        {
            s = "Error at mysql_query while getting server_error_log insert id";
        }
        break;
        case -5084:
        {
            s = "mysql_store_result faild while getting server_error_log insert id";
        }
        break;
        case -5085:
        {
            s = "mysql_fetch_row faild while getting server_error_log insert id";
        }
        break;
        case -5086:
        {
            s = "Error at mysql_query while getting photo insert id";
        }
        break;
        case -5087:
        {
            s = "mysql_store_result faild while getting photo insert id";
        }
        break;
        case -5088:
        {
            s = "mysql_fetch_row faild while getting photo insert id";
        }
        break;
        case -5089:
        {
            s = "Error at mysql_query while checking blacklist exist";
        }
        break;
        case -5090:
        {
            s = "mysql_store_result faild while checking blacklist exist";
        }
        break;
        case -5091:
        {
            s = "mysql_fetch_row faild while checking blacklist exist";
        }
        break;
    }
    return s;
}

std::string Off000DB_err_position(int err_number)
{
    switch(err_number / 100)
    {
        case 10:
        {
            return "Garage Info";
        }
        break;
        case 11:
        {
            return "Zone";
        }
        break;
        case 12:
        {
            return "Parking_slot";
        }
        break;
        case 14:
        {
            return "Setting";
        }
        break;
        case 15:
        {
            return "Site";
        }
        break;
        case 16:
        {
            return "Camera";
        }
        break;
        case 18:
        {
            return "Group_Inner";
        }
        break;
        case 19:
        {
            return "Monthly to hourly";
        }
        break;
        case 20:
        {
            return "Monthly Type";
        }
        break;
        case 21:
        {
            return "Rule Name Hourly";
        }
        break;
        case 22:
        {
            return "Rule Step Hourly";
        }
        break;
        case 24:
        {
            return "Rule Name Monthly";
        }
        break;
        case 25:
        {
            return "Rule Step Monthly";
        }
        break;
        case 27:
        {
            return "Black List";
        }
        break;
        case 29:
        {
            return "Server Errors Log";
        }
        break;
        case 30:
        {
            return "Kiosk Log";
        }
        break;
        case 31:
        {
            return "Event in";
        }
        break;
        case 32:
        {
            return "Event out";
        }
        break;
        case 33:
        {
            return "Event Payment";
        }
        break;
        case 34:
        {
            return "Event Charge";
        }
        break;
        case 36:
        {
            return "Event System";
        }
        break;
        case 37:
        {
            return "Account Info";
        }
        break;
        case 38:
        {
            return "Account State";
        }
        break;
        case 39:
        {
            return "Kiosk Machine";
        }
        break;
        case 40:
        {
            return "Kiosk Payment";
        }
        break;
        case 41:
        {
            return "Temp Card";
        }
        break;
        case 42:
        {
            return "photo";
        }
        break;
        case 50:
        {
            return "main";
        }
        break;
        default: 
        {
            return "Unknown error position ...!!!";
        }
        break;
    }
}

std::string Off000UN_err_message(int err_number)
{
    switch(err_number)
    {
        case 101:
        {
            return "alarm is null event camera";
        }
        break;
        case 102:
        {
            return "pEventParam is null in alarm event camera";
        }
        break;
        case 103:
        {
            return "pEventParam pBuffer is NULL or pEventParam dwBufSize equals to 0.... No Picture data";
        }
        break;
        case 104:
        {
            return "Save picture failed!!!";
        }
        break;
        case 105:
        {
            return "curl_easy_perform() failed";
        }
        break;
        case 106:
        {
            return "curl_easy_init() failed";
        }
        break;
        case 107:
        {
            return "Unknown error during while in main thread..!";
        }
        break;
        case 108:
        {
            return "Unknown error during initilize UDP Logger";
        }
        break;
        case 109:
        {
            return "Error in setting Broadcast UDP Log Socket";
        }
        break;
        case 110:
        {
            return "Error in BINDING PORT (port) for UDP Log";
        }
        break;
        case 111:
        {
            return "Error in setsockopt UDP Log Socket";
        }
        break;
        case 112:
        {
            return "Error in create client for webhost";
        }
        break;
        default: 
        {
            return "Unknown error ...!!!";
        }
        break;
    }
}