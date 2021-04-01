#ifndef OCCICOMM_DEFS_H
#define OCCICOMM_DEFS_H

//Common
const int OCCICOMM_SUCCESS     =   0;
const int OCCICOMM_PARAM_ERR   =   -100001;
const int OCCICOMM_UNKNOWN_ERR =   -100099;

//COcciConn   
const int OCCICOMM_ALREADY_CREATED_CONN = -100101;
const int OCCICOMM_CONN_NOT_INITED      = -100102;

//COcciConn exception instances params
const int OCCICOMM_CONN_NOT_INITED_ID          = OCCICOMM_CONN_NOT_INITED;
const char* const OCCICOMM_CONN_NOT_INITED_MSG =   "Database connection is not valid";
    
//COcciOper 
const int OCCICOMM_ALREADY_ATTACHED_CONN = -100201;
const int OCCICOMM_NOT_ATTACHED_CONN     = -100202;


#endif  /* OCCICOMM_DEFS_H */


