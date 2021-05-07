
#ifndef __CONNECTION_META_H__
#define __CONNECTION_META_H__

#define GPRSType "AT+SAPBR=3,1,\"Contype\",\"GPRS\"\n"
#define query1 "AT+SAPBR=1,1\n"
#define checkIP "AT+SAPBR=2,1\n"
#define APN "AT+CSTT=\"zain\",\"zain\",\"zain\"\n"
#define HTTPInit "AT+HTTPINIT\n"
#define HTTPSSL "AT+HTTPSSL=1\n"
#define SgnlStr "AT+CSQ\n"
#define Provider "AT+COPS?\n"

#define __Para_Userdata "USERDATA"
#define __hdr_x_aio_key "X-AIO-Key"
#define x_aio_key "4a2bddfff2b046caaa34a042ace1bba2"

#define __Para_content "CONTENT"
#define content_value "application/json"

#define __Para_CID "CID"
#define CID_value "1"

#define __feeds_console "laser-feeds.console"
#define __feeds_lsrDist "laser-feeds.laser-dist"
#define __feeds_lsrSigQ "laser-feeds.laser-sq"
#define __feeds_OPModes "laser-feeds.operation-mode"
#define __feeds_reqTime "laser-feeds.request-time"
#define __feeds_temprtr "laser-feeds.temperature"

//## check the content here
#define respOk "OK"
#define respError "ERROR"
#define respDownload "DOWNLOAD"

#endif