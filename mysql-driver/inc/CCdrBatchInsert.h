/**
* @file             CCdrBatchInsert.h
* @author           ֣ΰ��
* @date             2006/11/25
* @version          0.01b
* @description      ���������(�����������·��ӿڱ�ʹ��ӿڱ�)
* @modify history
*/
#ifndef    _DB_CDR_BATCH_INSERT_HEAD
#define    _DB_CDR_BATCH_INSERT_HEAD

#include <assert.h>
#include <map>
#include "common.h"
#include "COcciConn.h"

using namespace std;
const int MAX_INSERT_NUM=5000;           //һ����������¼��

/**
* @brief CSpeRtBatchInsert class,������ʻ��һ��ʱ����������
*/
class CSpeRtBatchInsert
{

public:
    /**
     *@brief ���캯��
     */
    CSpeRtBatchInsert();

    /**
     *@brief ��������
     */
    virtual ~CSpeRtBatchInsert();

    /**
     *@brief ��ʼ������
     */
    bool Init();

    /**
    *@brief �������ݿ�����
    */
    int ConnectToDB(CMySqlOcciConn *pm_pOcciConn);

    /**
    *@brief ��ȡ������Ϣ
    */
    string GetErrorMsg()    
    {
        return m_sMsg;
    }

    /**
     *@brief �����ⲿ���ṹ����
     */
    int  AddRecord( const SSpeExchRateInfo *pInsValue );

    /**
     *@brief ����������
     */
    int Flush();

private:
    map<string,SSpeExchRateInfo> m_stSpeExchRateArr;//�ṹ����
    char m_sMsg[1024];
	char m_skey[128];

};

#endif
