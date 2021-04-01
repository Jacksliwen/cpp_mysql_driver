/**
* @file             CCdrBatchInsert.h
* @author           郑伟光
* @date             2006/11/25
* @version          0.01b
* @description      批量入库类(话单工作表、下发接口表和错单接口表)
* @modify history
*/
#ifndef    _DB_CDR_BATCH_INSERT_HEAD
#define    _DB_CDR_BATCH_INSERT_HEAD

#include <assert.h>
#include <map>
#include "common.h"
#include "COcciConn.h"

using namespace std;
const int MAX_INSERT_NUM=5000;           //一批插入最大记录数

/**
* @brief CSpeRtBatchInsert class,特殊国际货币汇率表批量入库类
*/
class CSpeRtBatchInsert
{

public:
    /**
     *@brief 构造函数
     */
    CSpeRtBatchInsert();

    /**
     *@brief 析构函数
     */
    virtual ~CSpeRtBatchInsert();

    /**
     *@brief 初始化函数
     */
    bool Init();

    /**
    *@brief 设置数据库连接
    */
    int ConnectToDB(CMySqlOcciConn *pm_pOcciConn);

    /**
    *@brief 获取错误信息
    */
    string GetErrorMsg()    
    {
        return m_sMsg;
    }

    /**
     *@brief 拷贝外部入库结构数据
     */
    int  AddRecord( const SSpeExchRateInfo *pInsValue );

    /**
     *@brief 批量入库操作
     */
    int Flush();

private:
    map<string,SSpeExchRateInfo> m_stSpeExchRateArr;//结构数组
    char m_sMsg[1024];
	char m_skey[128];

};

#endif
