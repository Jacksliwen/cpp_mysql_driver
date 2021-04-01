/**
* @file             CCdrBatchInsert.cc
* @author           sujw
* @date             2016/04/06
* @version          0.01
* @description     批量入库类(话单工作表、下发接口表和错单接口表)
* @modify history
*/
#include "CCdrBatchInsert.h"

char g_sUser[128]={0};
char g_sPass[128]={0};
char g_sDbSid[256]={0};
/*=================================================
                     特殊国际货币汇率表批量入库类
=================================================*/
CSpeRtBatchInsert::CSpeRtBatchInsert()
{
}

CSpeRtBatchInsert::~CSpeRtBatchInsert()
{
}

//初始化函数
bool CSpeRtBatchInsert::Init()
{
    DBMSG(cout<< "enter CSpeRtBatchInsert::Init..." <<endl);
    m_stSpeExchRateArr.clear();
    return  true;
}

//连接数据库
int CSpeRtBatchInsert::ConnectToDB( CMySqlOcciConn *pm_pOcciConn)
{
    DBMSG( cout<<"["<<__FILE__<<"]"<<"["<<__LINE__<<"]:"<<"Enter CDbProc::ConnectToDB"<<endl );
    int iRetCode= AttachConnection(pm_pOcciConn);
    if ( iRetCode != 0)
    {
        g_objLog.WriteLog(SERIOUS,__FUNCTION__, ALERT,DB_CONN_ERR,"关联数据库失败");
        return iRetCode;
    }

    DBMSG( cout<<"["<<__FILE__<<"]"<<"["<<__LINE__<<"]:"<<"Exit CDbProc::ConnectToDB"<<endl );
    return 0;
}

//拷贝外部入库结构数据
int CSpeRtBatchInsert::AddRecord(const SSpeExchRateInfo *pInsValue )
{
    DBMSG(cout<< "enter CSpeRtBatchInsert::AddRecord" <<endl);
    int iRet = 0;
    if( pInsValue )
    {
        return 0;
    }
	sprintf(m_skey,"%s%d%s%s%d",pInsValue->carrier_cd,pInsValue->biz_pkg,pInsValue->currency1,
		pInsValue->currency2,pInsValue->month);
    m_stSpeExchRateArr.insert( make_pair(m_skey, *pInsValue) );
    if( m_stSpeExchRateArr.size() >= MAX_INSERT_NUM )
    {
        iRet = Flush();
        if(iRet == 0)
        {
            m_stSpeExchRateArr.clear();
        }
        else
        {
            return iRet;
        }
    }

    return 0;
}

//批量入库操作
int CSpeRtBatchInsert::Flush()
{
    DBMSG(cout<< "enter CSpeRtBatchInsert::Flush..." <<endl);
    int l_iRet = 0;
    char BulkInsertSql[1024];

    if(m_stSpeExchRateArr.size() > 0)
    {
        try{
            /* turn off the autocommit */
            m_pOcciConn -> setAutoCommit(0);
            /* '?' is the supported placeholder syntax */
            sprintf(BulkInsertSql,"%s",
            "INSERT INTO pubdba.spe_exch_rt (carrier_cd,biz_pkg,currency1,currency2,month,exch_rate,file_name) \
            VALUES( ?,?,?,?,?,?,? ) ");
            DBMSG(cout<<"BulkInsertSql:"<<BulkInsertSql<<endl);
            pstmt = m_pOcciConn->createStatement(BulkInsertSql);
            for (map<string,SSpeExchRateInfo>::iterator it = m_stSpeExchRateArr.begin(); it != m_stSpeExchRateArr.end(); ++it) {
                pstmt->setString(1 ,it->second.carrier_cd);
                pstmt->setInt(2 ,it->second.biz_pkg);
                pstmt->setString(3 ,it->second.currency1);
                pstmt->setString(4 ,it->second.currency2);
                pstmt->setInt(5 ,it->second.month);
                pstmt->setDouble(6 ,it->second.exch_rate);
                pstmt->setString(7 ,it->second.file_name);
                pstmt->executeUpdate();
            }
            m_pOcciConn->terminateStatement(l_objStmt);
            l_objStmt = NULL;
            m_pOcciConn->commit();
        }catch (CMySqlOcciConnException &ex) {
            m_pOcciConn->terminateStatement(l_objStmt);
            l_objStmt = NULL;
            return ex.getErrorCode();
        }
        m_pOcciConn -> setAutoCommit(1);
    }
    m_stSpeExchRateArr.clear();

    return 0;
}