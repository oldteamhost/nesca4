
#ifndef DHNETSDK_H
#define DHNETSDK_H


#if (defined(WIN32) || defined(WIN64))
#include <windows.h>
#ifdef DHNETSDK_EXPORTS

#ifndef CLIENT_API
#define CLIENT_API  __declspec(dllexport)
#endif

#else

#ifndef CLIENT_API
#define CLIENT_API  __declspec(dllimport)
#endif

#endif

#define CALLBACK __stdcall
#define CALL_METHOD  __stdcall  //__cdecl

#define INT64 __int64

#ifndef LLONG
#ifdef WIN64
#define LLONG INT64
#else 
#define LLONG LONG
#endif
#endif

#ifndef LDWORD
#ifdef WIN64
#define LDWORD INT64
#else 
#define LDWORD DWORD
#endif
#endif

#else	//linux

#define CLIENT_API	extern "C"
#define CALL_METHOD
#define CALLBACK

#ifndef INTERNAL_COMPILE
#define RELEASE_HEADER //����ͷ�ļ�
#endif
 
#ifdef RELEASE_HEADER

#define WORD	unsigned short
#define DWORD	unsigned int
#define LONG	int
#define LPDWORD	DWORD*
#define BOOL	int
#define TRUE	1
#define FALSE	0
#define BYTE	unsigned char
#define UINT	unsigned int
#define HDC		void*
#define HWND	void*
#define LPVOID	void*
// #define NULL 0   NESCA4 edit
#define LLONG	long
#define INT64   long long
#define LDWORD	long 

#ifndef MAX_PATH
#define MAX_PATH	260
#endif

typedef struct  tagRECT
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT;

#else	//�ڲ�����
#include "../Platform/osIndependent.h"
#endif

#endif
#include "dhassistant.h"

#ifndef LDWORD
#if (defined(WIN32) || defined(WIN64))
#ifdef WIN64
#define LDWORD __int64
#else //WIN32 
#define LDWORD DWORD
#endif
#else	//linux
#define LDWORD long 
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 ** ��������
 ***********************************************************************/
#define DH_SERIALNO_LEN 			48			// �豸���к��ַ�����
#define DH_MAX_DISKNUM 				256			// ���Ӳ�̸���
#define DH_MAX_SDCARDNUM			32			// ���SD������
#define DH_MAX_BURNING_DEV_NUM		32			// ����¼�豸����
#define DH_BURNING_DEV_NAMELEN		32			// ��¼�豸������󳤶�
#define DH_MAX_LINK 				6
#define DH_MAX_CHANNUM 				16			// ���ͨ������
#define DH_MAX_DECODER_CHANNUM		64			// ���������ͨ����
#define DH_MAX_ALARMIN 				128			// ��󱨾��������
#define DH_MAX_ALARMOUT 			64			// ��󱨾��������
#define DH_MAX_RIGHT_NUM			100			// �û�Ȩ�޸�������
#define DH_MAX_GROUP_NUM			20			// �û����������
#define DH_MAX_USER_NUM				200			// �û���������
#define DH_RIGHT_NAME_LENGTH		32			// Ȩ��������
#define DH_USER_NAME_LENGTH			8			// �û�������
#define DH_USER_PSW_LENGTH			8			// �û����볤��
#define DH_MEMO_LENGTH				32			// ��ע����
#define DH_MAX_STRING_LEN			128
#define MAX_STRING_LINE_LEN			6			// �������
#define MAX_PER_STRING_LEN			20			// ÿ����󳤶�
#define DH_MAX_MAIL_NAME_LEN		64			// �µ��ʼ��ṹ��֧�ֵ��û�������
#define DH_MAX_MAIL_PSW_LEN			64			// �µ��ʼ��ṹ��֧�ֵ����볤��
#define DH_SPEEDLIMIT_TYPE_LEN      32          // ���������ַ�������
#define DH_VEHICLE_TYPE_LEN         32          // �����Զ�����Ϣ�����ַ�������
#define DH_VEHICLE_INFO_LEN         32          // �����Զ�����Ϣ�ַ�������
#define DH_VEHICLE_DRIVERNO_LEN     32          // �����Զ�����Ϣ˾�������ַ�������
#define DH_MAX_CROSSING_NUM         128         // ����λ
#define DH_MAX_CROSSING_ID          32          // ·�����к���󳤶�
#define DH_MAX_CARD_INFO_LEN		256			// ������Ϣ��󳤶�
#define DH_MAX_CHANNUM_EX           32          // ���ͨ������չ  
#define DH_MAX_SAERCH_IP_NUM        256         // �������IP����
#define DH_MAX_HARDDISK_TYPE_LEN	32			// Ӳ���ͺ���󳤶�
#define DH_MAX_HARDDISK_SERIAL_LEN	32			// Ӳ�����к���󳤶�
#define DH_MAX_SIM_LEN				16			// SIM����ֵ����󳤶�
#define DH_MAX_SIM_NUM				10			// ����SIM��������
#define DH_MAX_VERSION_LEN			32			// �����汾����󳤶�
#define DH_MAX_MDN_LEN				36			// MDN��ֵ����󳤶�
#define DH_MAX_NETINTERFACE_NUM     64          // ֧�ֵ���������
#define DH_EVENT_NAME_LEN			128			// �¼����Ƴ���
#define DH_STORAGE_NAME_LEN			128			// �洢�豸���Ƴ���
#define DH_MAX_CARPORTLIGHT_NUM     4           // ���λ�Ƹ���
#define DH_STATION_NAME_LEN         32          // ��վվ�����Ƴ���   


// Զ�����ýṹ����س���
#define DH_MAX_MAIL_ADDR_LEN		128			// �ʼ���(��)��ַ��󳤶�
#define DH_MAX_MAIL_SUBJECT_LEN		64			// �ʼ�������󳤶�
#define DH_MAX_IPADDR_LEN			16			// IP��ַ�ַ�������
#define DH_MACADDR_LEN				40			// MAC��ַ�ַ�������
#define DH_MAX_URL_LEN				128			// URL�ַ�������
#define DH_MAX_DEV_ID_LEN			48			// ���������󳤶�
#define	DH_MAX_HOST_NAMELEN			64			// ���������ȣ�
#define DH_MAX_HOST_PSWLEN			32			// ���볤��
#define DH_MAX_NAME_LEN				16			// ͨ�������ַ�������
#define DH_MAX_ETHERNET_NUM			2			// ��̫����������
#define DH_MAX_ETHERNET_NUM_EX	    10			// ��չ��̫����������
#define	DH_DEV_SERIALNO_LEN			48			// ���к��ַ�������
#define DH_DEV_TYPE_LEN				32			// �豸�����ַ�������
#define DH_N_WEEKS					7			// һ�ܵ�����	
#define DH_N_TSECT					6			// ͨ��ʱ��θ���
#define DH_N_REC_TSECT				6			// ¼��ʱ��θ���
#define DH_N_COL_TSECT				2			// ��ɫʱ��θ���	
#define DH_CHAN_NAME_LEN			32			// ͨ�������ȣ�DVR DSP�������ƣ����32�ֽ�		
#define DH_N_ENCODE_AUX				3			// ��չ��������	
#define DH_N_TALK					1			// ���Խ�ͨ������
#define DH_N_COVERS					1			// �ڵ��������	
#define DH_N_CHANNEL				16			// ���ͨ������	
#define DH_N_ALARM_TSECT			2			// ������ʾʱ��θ���
#define DH_MAX_ALARMOUT_NUM			16			// ��������ڸ�������
#define DH_MAX_AUDIO_IN_NUM			16			// ��Ƶ����ڸ�������
#define DH_MAX_VIDEO_IN_NUM			16			// ��Ƶ����ڸ�������
#define DH_MAX_ALARM_IN_NUM			16			// ��������ڸ�������
#define DH_MAX_DISK_NUM				16			// Ӳ�̸������ޣ��ݶ�Ϊ16
#define DH_MAX_DECODER_NUM			16			// ������(485)��������	
#define DH_MAX_232FUNCS				10			// 232���ڹ��ܸ�������
#define DH_MAX_232_NUM				2			// 232���ڸ�������
#define DH_MAX_232_NUM_EX           16          // ��չ�������ø�������          
#define DH_MAX_DECPRO_LIST_SIZE		100			// ������Э���б���������
#define DH_FTP_MAXDIRLEN			240			// FTP�ļ�Ŀ¼��󳤶�
#define DH_MATRIX_MAXOUT			16			// ���������������
#define DH_TOUR_GROUP_NUM			6			// ���������������
#define DH_MAX_DDNS_NUM				10			// �豸֧�ֵ�ddns������������
#define DH_MAX_SERVER_TYPE_LEN		32			// ddns���������ͣ�����ַ�������
#define DH_MAX_DOMAIN_NAME_LEN		256			// ddns����������ַ�������
#define DH_MAX_DDNS_ALIAS_LEN		32			// ddns����������������ַ�������
#define DH_MAX_DEFAULT_DOMAIN_LEN	60			// ddnsĬ������������ַ������� 	
#define DH_MOTION_ROW				32			// ��̬������������
#define DH_MOTION_COL				32			// ��̬������������
#define DH_STATIC_ROW				32			// ��̬������������
#define DH_STATIC_COL			    32			// ��̬������������
#define	DH_FTP_USERNAME_LEN			64			// FTP���ã��û�����󳤶�
#define	DH_FTP_PASSWORD_LEN			64			// FTP���ã�������󳤶�
#define	DH_TIME_SECTION				2			// FTP���ã�ÿ��ʱ��θ���
#define DH_FTP_MAX_PATH				240			// FTP���ã��ļ�·������󳤶�
#define DH_FTP_MAX_SUB_PATH			128 		// FTP���ã��ļ�·������󳤶�
#define DH_INTERVIDEO_UCOM_CHANID	32			// ƽ̨�������ã�U��ͨͨ��ID
#define DH_INTERVIDEO_UCOM_DEVID	32			// ƽ̨�������ã�U��ͨ�豸ID
#define DH_INTERVIDEO_UCOM_REGPSW	16			// ƽ̨�������ã�U��ͨע������
#define DH_INTERVIDEO_UCOM_USERNAME	32			// ƽ̨�������ã�U��ͨ�û���
#define DH_INTERVIDEO_UCOM_USERPSW	32			// ƽ̨�������ã�U��ͨ����
#define DH_INTERVIDEO_NSS_IP		32			// ƽ̨�������ã�������άIP
#define DH_INTERVIDEO_NSS_SERIAL	32			// ƽ̨�������ã�������άserial
#define DH_INTERVIDEO_NSS_USER		32			// ƽ̨�������ã�������άuser
#define DH_INTERVIDEO_NSS_PWD		50			// ƽ̨�������ã�������άpassword
#define DH_MAX_VIDEO_COVER_NUM		16			// �ڵ�����������
#define DH_MAX_WATERMAKE_DATA		4096		// ˮӡͼƬ������󳤶�
#define DH_MAX_WATERMAKE_LETTER		128			// ˮӡ������󳤶�
#define DH_MAX_WLANDEVICE_NUM		10			// ����������������豸����
#define DH_MAX_WLANDEVICE_NUM_EX	32			// ����������������豸����
#define DH_MAX_ALARM_NAME			64			// ��ַ����
#define DH_MAX_REGISTER_SERVER_NUM	10			// ����ע�����������
#define DH_SNIFFER_FRAMEID_NUM		6			// 6��FRAME ID ѡ��
#define DH_SNIFFER_CONTENT_NUM		4			// ÿ��FRAME��Ӧ��4��ץ������
#define DH_SNIFFER_CONTENT_NUM_EX	8			// ÿ��FRAME��Ӧ��8��ץ������
#define DH_SNIFFER_PROTOCOL_SIZE	20			// Э�����ֳ���
#define DH_MAX_PROTOCOL_NAME_LENGTH 20
#define DH_SNIFFER_GROUP_NUM		4			// 4��ץ������
#define MAX_PATH_STOR				240			// Զ��Ŀ¼�ĳ���
#define DH_ALARM_OCCUR_TIME_LEN		40			// �µı����ϴ�ʱ��ĳ���
#define DH_VIDEO_OSD_NAME_NUM		64			// ���ӵ����Ƴ��ȣ�Ŀǰ֧��32��Ӣ�ģ�16������
#define DH_VIDEO_CUSTOM_OSD_NUM		8			// ֧�ֵ��Զ�����ӵ���Ŀ��������ʱ���ͨ��
#define DH_CONTROL_AUTO_REGISTER_NUM 100        // ֧�ֶ�������ע��������ĸ���
#define DH_MMS_RECEIVER_NUM          100        // ֧�ֶ��Ž����ߵĸ���
#define DH_MMS_SMSACTIVATION_NUM     100        // ֧�ֶ��ŷ����ߵĸ���
#define DH_MMS_DIALINACTIVATION_NUM  100        // ֧�ֲ��ŷ����ߵĸ���
#define DH_MAX_ALARMOUT_NUM_EX		 32			// ��������ڸ���������չ
#define DH_MAX_VIDEO_IN_NUM_EX		 32			// ��Ƶ����ڸ���������չ
#define DH_MAX_ALARM_IN_NUM_EX		 32			// ��������ڸ�������
#define DH_MAX_IPADDR_OR_DOMAIN_LEN	 64			// IP��ַ�ַ�������
#define DH_MAX_OBJECT_LIST			 16			// ���ܷ����豸��⵽������ID��������	
#define DH_MAX_RULE_LIST			 16			// ���ܷ����豸�����������
#define DH_MAX_POLYGON_NUM			 16			// �������󶥵����
#define DH_MAX_DETECT_LINE_NUM       20         // ����������󶥵���
#define DH_MAX_DETECT_REGION_NUM     20         // ������������󶥵���
#define DH_MAX_TRACK_LINE_NUM        20         // �����˶��켣��󶥵���
#define DH_MAX_CANDIDATE_NUM         50         // ����ʶ�����ƥ����
#define DH_MAX_PERSON_IMAGE_NUM      48         // ÿ����Ա��Ӧ���������ͼƬ��
#define DH_MAX_FENCE_LINE_NUM        2          // Χ�����������
#define MAX_SMART_VALUE_NUM          30         // ����smart��Ϣ����
#define DH_MACHINE_NAME_NUM			 64         // �������Ƴ���
#define DH_INTERVIDEO_AMP_DEVICESERIAL    48    // ƽ̨�������ã�������� �豸���к��ַ�������
#define DH_INTERVIDEO_AMP_DEVICENAME      16    // ƽ̨�������ã�������� �豸�����ַ�������
#define DH_INTERVIDEO_AMP_USER            32    // ƽ̨�������ã�������� ע���û����ַ�������
#define DH_INTERVIDEO_AMP_PWD             32    // ƽ̨�������ã�������� ע�������ַ�������
#define MAX_SUBMODULE_NUM            32         // �����ģ����Ϣ����
#define DH_MAX_CARWAY_NUM            8          // ��ͨץ�ģ���󳵵���
#define DH_MAX_SNAP_SIGNAL_NUM       3          // һ�����������ץ������
#define DH_MAX_CARD_NUM              128        // ���ŵ�������
#define DH_MAX_CARDINFO_LEN          32         // ÿ��������ַ���
#define DH_MAX_CONTROLER_NUM         64         // ���֧�ֿ�������Ŀ
#define DH_MAX_LIGHT_NUM             32         // �����Ƶ�����
#define DH_MAX_SNMP_COMMON_LEN       64         // snmp ��д���ݳ���
#define DH_MAX_DDNS_STATE_LEN        128        // DDNS ״̬��Ϣ����
#define DH_MAX_PHONE_NO_LEN          16         // �绰���볤��
#define DH_MAX_MSGTYPE_LEN           32         // �������ͻ����Ϣ���ͳ���
#define DH_MAX_MSG_LEN               256        // �����Ͷ���Ϣ����
#define DH_MAX_DRIVINGDIRECTION      256        // ��ʻ�����ַ�������
#define DH_MAX_GRAB_INTERVAL_NUM     4	        // ����ͼƬץ�ĸ���
#define DH_MAX_FLASH_NUM			 5			// ���֧������Ƹ���
#define DH_MAX_LANE_NUM              8          // ��Ƶ�����豸ÿ��ͨ����Ӧ����������
#define DH_MAX_ISCSI_PATH_NUM		 64			// ISCSIԶ��Ŀ¼�������
#define DH_MAX_WIRELESS_CHN_NUM		 256		// ����·������ŵ���
#define DH_PROTOCOL3_BASE			 100		// ����Э��汾����
#define DH_PROTOCOL3_SUPPORT		 11			// ֻ֧��3��Э��
#define DH_MAX_CHANMASK              64         // ͨ���������ֵ
#define DH_MAX_STAFF_NUM			 20			// Ũ����Ƶ������Ϣ�б��������
#define DH_MAX_CALIBRATEBOX_NUM		 10			// Ũ����Ƶ������Ϣ�б궨����������
#define DH_MAX_EXCLUDEREGION_NUM	 10			// Ũ����Ƶ������Ϣ���ų�����������
#define DH_MAX_POLYLINE_NUM			 20			// Ũ����Ƶ������Ϣ�б������
#define	DH_MAX_COLOR_NUM			 16			// �����ɫ��Ŀ
#define MAX_OBJFILTER_NUM			 16			// �������������
#define DH_MAX_SYNOPSIS_STATE_NAME   64         // ��ƵŨ��״̬�ַ�������
#define DH_MAX_SYNOPSIS_QUERY_FILE_COUNT	10	// ��ƵŨ�����ԭʼ�ļ�����·������ʱ�ļ���������
#define DH_MAX_SSID_LEN              36         // SSID����
#define DH_MAX_APPIN_LEN             16         // PIN�볤��
#define DH_NETINTERFACE_NAME_LEN     260        // �������Ƴ���
#define DH_NETINTERFACE_TYPE_LEN     260        // �������ͳ���
#define DH_MAX_CONNECT_STATUS_LEN    260        // ����״̬�ַ�������
#define DH_MAX_MODE_LEN              64         // 3G֧�ֵ�����ģʽ����
#define DH_MAX_MODE_NUM              64         // 3G֧�ֵ�����ģʽ����
#define DH_MAX_CAPTURE_SIZE_NUM      64         // ��Ƶ�ֱ��ʸ���
#define DH_NODE_NAME_LEN			 64			// ��֯�ṹ�ڵ����Ƴ���
#define MAX_CALIBPOINTS_NUM          256        // ֧�����궨����
#define DH_MAX_ATTR_NUM				 32			// ��ʾ��Ԫ�����������
#define DH_MAX_CLOUDCONNECT_STATE_LEN 128       // ��ע������״̬��Ϣ����
#define DH_MAX_IPADDR_EX_LEN         128        // ��չIP��ַ��󳤶�

// ��ѯ���ͣ���ӦCLIENT_QueryDevState�ӿ�
#define DH_DEVSTATE_COMM_ALARM		0x0001		// ��ѯ��ͨ����״̬(�����ⲿ��������Ƶ��ʧ����̬���)
#define DH_DEVSTATE_SHELTER_ALARM	0x0002		// ��ѯ�ڵ�����״̬
#define DH_DEVSTATE_RECORDING		0x0003		// ��ѯ¼��״̬
#define DH_DEVSTATE_DISK			0x0004		// ��ѯӲ����Ϣ
#define DH_DEVSTATE_RESOURCE		0x0005		// ��ѯϵͳ��Դ״̬
#define DH_DEVSTATE_BITRATE			0x0006		// ��ѯͨ������
#define DH_DEVSTATE_CONN			0x0007		// ��ѯ�豸����״̬
#define DH_DEVSTATE_PROTOCAL_VER	0x0008		// ��ѯ����Э��汾�ţ�pBuf = int*
#define DH_DEVSTATE_TALK_ECTYPE		0x0009		// ��ѯ�豸֧�ֵ������Խ���ʽ�б������ṹ��DHDEV_TALKFORMAT_LIST
#define DH_DEVSTATE_SD_CARD			0x000A		// ��ѯSD����Ϣ(IPC���Ʒ)
#define DH_DEVSTATE_BURNING_DEV		0x000B		// ��ѯ��¼����Ϣ
#define DH_DEVSTATE_BURNING_PROGRESS 0x000C		// ��ѯ��¼����
#define DH_DEVSTATE_PLATFORM		0x000D		// ��ѯ�豸֧�ֵĽ���ƽ̨
#define DH_DEVSTATE_CAMERA			0x000E		// ��ѯ����ͷ������Ϣ(IPC���Ʒ)��pBuf = DHDEV_CAMERA_INFO *�������ж���ṹ��
#define DH_DEVSTATE_SOFTWARE		0x000F		// ��ѯ�豸�����汾��Ϣ
#define DH_DEVSTATE_LANGUAGE        0x0010		// ��ѯ�豸֧�ֵ���������
#define DH_DEVSTATE_DSP				0x0011		// ��ѯDSP��������(��Ӧ�ṹ��DHDEV_DSP_ENCODECAP)
#define	DH_DEVSTATE_OEM				0x0012		// ��ѯOEM��Ϣ
#define	DH_DEVSTATE_NET				0x0013		// ��ѯ��������״̬��Ϣ
#define DH_DEVSTATE_TYPE			0x0014		// ��ѯ�豸����
#define DH_DEVSTATE_SNAP			0x0015		// ��ѯ��������(IPC���Ʒ)
#define DH_DEVSTATE_RECORD_TIME		0x0016		// ��ѯ����¼��ʱ������¼��ʱ��
#define DH_DEVSTATE_NET_RSSI        0x0017      // ��ѯ���������ź�ǿ�ȣ����ṹ��DHDEV_WIRELESS_RSS_INFO
#define DH_DEVSTATE_BURNING_ATTACH	0x0018		// ��ѯ������¼ѡ��
#define DH_DEVSTATE_BACKUP_DEV		0x0019		// ��ѯ�����豸�б�
#define DH_DEVSTATE_BACKUP_DEV_INFO	0x001a		// ��ѯ�����豸��ϸ��Ϣ
#define DH_DEVSTATE_BACKUP_FEEDBACK	0x001b		// ���ݽ��ȷ���
#define DH_DEVSTATE_ATM_QUERY_TRADE  0x001c		// ��ѯATM��������
#define DH_DEVSTATE_SIP				0x001d		// ��ѯsip״̬
#define DH_DEVSTATE_VICHILE_STATE	0x001e		// ��ѯ����wifi״̬
#define DH_DEVSTATE_TEST_EMAIL      0x001f      // ��ѯ�ʼ������Ƿ�ɹ�
#define DH_DEVSTATE_SMART_HARD_DISK 0x0020      // ��ѯӲ��smart��Ϣ
#define DH_DEVSTATE_TEST_SNAPPICTURE 0x0021     // ��ѯץͼ�����Ƿ�ɹ�
#define DH_DEVSTATE_STATIC_ALARM    0x0022      // ��ѯ��̬����״̬
#define DH_DEVSTATE_SUBMODULE_INFO  0x0023      // ��ѯ�豸��ģ����Ϣ
#define DH_DEVSTATE_DISKDAMAGE      0x0024      // ��ѯӲ�̻������� 
#define DH_DEVSTATE_IPC             0x0025      // ��ѯ�豸֧�ֵ�IPC����, ���ṹ��DH_DEV_IPC_INFO
#define DH_DEVSTATE_ALARM_ARM_DISARM 0x0026     // ��ѯ����������״̬
#define DH_DEVSTATE_ACC_POWEROFF_ALARM 0x0027   // ��ѯACC�ϵ籨��״̬(����һ��DWORD, 1��ʾ�ϵ磬0��ʾͨ��)
#define DH_DEVSTATE_TEST_FTP_SERVER 0x0028      // ����FTP����������
#define DH_DEVSTATE_3GFLOW_EXCEED   0x0029      // ��ѯ3G����������ֵ״̬,(���ṹ��DHDEV_3GFLOW_EXCEED_STATE_INFO)
#define DH_DEVSTATE_3GFLOW_INFO     0x002a      // ��ѯ3G����������Ϣ,���ṹ��DH_DEV_3GFLOW_INFO
#define DH_DEVSTATE_VIHICLE_INFO_UPLOAD  0x002b // �����Զ�����Ϣ�ϴ�(���ṹ��ALARM_VEHICLE_INFO_UPLOAD)
#define DH_DEVSTATE_SPEED_LIMIT     0x002c      // ��ѯ���ٱ���״̬(���ṹ��ALARM_SPEED_LIMIT)
#define DH_DEVSTATE_DSP_EX          0x002d      // ��ѯDSP��չ��������(��Ӧ�ṹ��DHDEV_DSP_ENCODECAP_EX)
#define DH_DEVSTATE_3GMODULE_INFO    0x002e     // ��ѯ3Gģ����Ϣ(��Ӧ�ṹ��DH_DEV_3GMODULE_INFO)
#define DH_DEVSTATE_MULTI_DDNS      0x002f      // ��ѯ��DDNS״̬��Ϣ(��Ӧ�ṹ��DH_DEV_MULTI_DDNS_INFO)
#define DH_DEVSTATE_CONFIG_URL      0x0030      // ��ѯ�豸����URL��Ϣ(��Ӧ�ṹ��DH_DEV_URL_INFO)
#define DH_DEVSTATE_HARDKEY        0x0031       // ��ѯHardKey״̬����Ӧ�ṹ��DHDEV_HARDKEY_STATE)
#define DH_DEVSTATE_ISCSI_PATH		0x0032		// ��ѯISCSI·���б�(��Ӧ�ṹ��DHDEV_ISCSI_PATHLIST)
#define DH_DEVSTATE_DLPREVIEW_SLIPT_CAP   0x0033      // ��ѯ�豸����Ԥ��֧�ֵķָ�ģʽ(��Ӧ�ṹ��DEVICE_LOCALPREVIEW_SLIPT_CAP)
#define DH_DEVSTATE_WIFI_ROUTE_CAP	0x0034		// ��ѯ����·��������Ϣ(��Ӧ�ṹ��DHDEV_WIFI_ROUTE_CAP)
#define DH_DEVSTATE_ONLINE          0x0035      // ��ѯ�豸������״̬(����һ��DWORD, 1��ʾ����, 0��ʾ����)
#define DH_DEVSTATE_PTZ_LOCATION    0x0036      // ��ѯ��̨״̬��Ϣ(��Ӧ�ṹ��DH_PTZ_LOCATION_INFO)
#define DH_DEVSTATE_MONITOR_INFO    0x0037      // �����ظ�����Ϣ(��Ӧ�ṹ��DHDEV_MONITOR_INFO)
#define DH_DEVSTATE_SUBDEVICE		0x0300		// ��ѯ���豸(��Դ, ���ȵ�)״̬(��Ӧ�ṹ��CFG_DEVICESTATUS_INFO)
#define DH_DEVSTATE_RAID_INFO       0x0038      // ��ѯRAID״̬(��Ӧ�ṹ��ALARM_RAID_INFO)  
#define DH_DEVSTATE_TEST_DDNSDOMAIN 0x0039      // ����DDNS�����Ƿ����
#define DH_DEVSTATE_VIRTUALCAMERA   0x003a      // ��ѯ��������ͷ״̬(��ӦDHDEV_VIRTUALCAMERA_STATE_INFO)
#define DH_DEVSTATE_TRAFFICWORKSTATE 0x003b     // ��ȡ�豸������Ƶ/��Ȧģʽ״̬��(��ӦDHDEV_TRAFFICWORKSTATE_INFO)
#define DH_DEVSTATE_ALARM_CAMERA_MOVE 0x003c    // ��ȡ�������λ�����¼�״̬(��ӦALARM_CAMERA_MOVE_INFO)
#define DH_DEVSTATE_ALARM           0x003e      // ��ȡ�ⲿ����״̬(��Ӧ NET_CLIENT_ALARM_STATE) 
#define DH_DEVSTATE_VIDEOLOST       0x003f      // ��ȡ��Ƶ��ʧ����״̬(��Ӧ NET_CLIENT_VIDEOLOST_STATE) 
#define DH_DEVSTATE_MOTIONDETECT   0x0040       // ��ȡ��̬��ⱨ��״̬(��Ӧ NET_CLIENT_MOTIONDETECT_STATE)
#define DH_DEVSTATE_DETAILEDMOTION 0x0041       // ��ȡ��ϸ�Ķ�̬��ⱨ��״̬(��Ӧ NET_CLIENT_DETAILEDMOTION_STATE)
#define DH_DEVSTATE_VEHICLE_INFO   0x0042		// ��ȡ������������Ӳ����Ϣ(��Ӧ DHDEV_VEHICLE_INFO)
#define DH_DEVSTATE_VIDEOBLIND     0x0043       // ��ȡ��Ƶ�ڵ�����״̬(��Ӧ NET_CLIENT_VIDEOBLIND_STATE)
#define DH_DEVSTATE_3GSTATE_INFO   0x0044       // ��ѯ3Gģ�������Ϣ(��Ӧ�ṹ��DHDEV_VEHICLE_3GMODULE)
#define DH_DEVSTATE_NETINTERFACE   0x0045       // ��ѯ����ӿ���Ϣ(��Ӧ DHDEV_NETINTERFACE_INFO)
#define DH_DEVSTATE_PICINPIC_CHN	0x0046		// ��ѯ���л�ͨ����(��ӦDWORD����)
#define DH_DEVSTATE_COMPOSITE_CHN	0x0047		// ��ѯ�ں���ͨ����Ϣ(��ӦDH_COMPOSITE_CHANNEL����)
#define DH_DEVSTATE_WHOLE_RECORDING	0x0048		// ��ѯ�豸����¼��״̬(��ӦBOOL), ֻҪ��һ��ͨ����¼�񣬼�Ϊ�豸����״̬Ϊ¼��
#define DH_DEVSTATE_WHOLE_ENCODING	0x0049		// ��ѯ�豸�������״̬(��ӦBOOL), ֻҪ��һ��ͨ���ڱ��룬��Ϊ�豸����״̬Ϊ����
#define DH_DEVSTATE_DISK_RECORDE_TIME 0x004a      // ��ѯ�豸Ӳ��¼��ʱ����Ϣ(pBuf = DEV_DISK_RECORD_TIME*�������ж���ṹ��)
#define DH_DEVSTATE_BURNER_DOOR     0x004b      // �Ƿ��ѵ�����¼��������(��Ӧ�ṹ�� NET_DEVSTATE_BURNERDOOR)
#define DH_DEVSTATE_GET_DATA_CHECK  0x004c      // ��ѯ��������У�����(��Ӧ NET_DEVSTATE_DATA_CHECK)

// ��ѯ���ͣ���ӦCLIENT_QueryRemotDevState�ӿ�
#define DH_DEVSTATE_ALARM_REMOTE   0x1000        // ��ȡԶ���豸�ⲿ����(��Ӧ ALARM_REMOTE_ALARM_INFO)
#define DH_DEVSTATE_ALARM_FRONTDISCONNECT 0x1001 // ��ȡǰ��IPC��������(��Ӧ�ṹ��ALARM_FRONTDISCONNET_INFO)

// �������ͣ���ӦCLIENT_GetDevConfig��CLIENT_SetDevConfig�ӿ�
#define DH_DEV_DEVICECFG			0x0001		// �豸��������
#define DH_DEV_NETCFG				0x0002		// ��������
#define DH_DEV_CHANNELCFG			0x0003		// ͼ��ͨ������
#define DH_DEV_PREVIEWCFG 			0x0004		// Ԥ����������
#define DH_DEV_RECORDCFG			0x0005		// ¼������
#define DH_DEV_COMMCFG				0x0006		// ������������
#define DH_DEV_ALARMCFG 			0x0007		// ������������
#define DH_DEV_TIMECFG 				0x0008		// DVRʱ������
#define DH_DEV_TALKCFG				0x0009		// �Խ���������
#define DH_DEV_AUTOMTCFG			0x000A		// �Զ�ά������		
#define	DH_DEV_VEDIO_MARTIX			0x000B		// ����������Ʋ�������	
#define DH_DEV_MULTI_DDNS			0x000C		// ��ddns����������
#define DH_DEV_SNAP_CFG				0x000D		// ץͼ�������
#define DH_DEV_WEB_URL_CFG			0x000E		// HTTP·������
#define DH_DEV_FTP_PROTO_CFG		0x000F		// FTP�ϴ�����
#define DH_DEV_INTERVIDEO_CFG		0x0010		// ƽ̨�������ã���ʱchannel��������ƽ̨���ͣ�
												// channel=4�� ���������������أ�channel=10������������ά��channel=11������U��ͨ��channel=51�������������
#define DH_DEV_VIDEO_COVER			0x0011		// �����ڵ�����
#define DH_DEV_TRANS_STRATEGY		0x0012		// ����������ã���������\����������
#define DH_DEV_DOWNLOAD_STRATEGY	0x0013		// ¼�����ز������ã���������\��ͨ����
#define DH_DEV_WATERMAKE_CFG		0x0014		// ͼ��ˮӡ����
#define DH_DEV_WLAN_CFG				0x0015		// ������������
#define DH_DEV_WLAN_DEVICE_CFG		0x0016		// ���������豸����
#define DH_DEV_REGISTER_CFG			0x0017		// ����ע���������
#define DH_DEV_CAMERA_CFG			0x0018		// ����ͷ��������
#define DH_DEV_INFRARED_CFG 		0x0019		// ���ⱨ������
#define DH_DEV_SNIFFER_CFG			0x001A		// Snifferץ������
#define DH_DEV_MAIL_CFG				0x001B		// �ʼ�����
#define DH_DEV_DNS_CFG				0x001C		// DNS����������
#define DH_DEV_NTP_CFG				0x001D		// NTP����
#define DH_DEV_AUDIO_DETECT_CFG		0x001E		// ��Ƶ�������
#define DH_DEV_STORAGE_STATION_CFG  0x001F      // �洢λ������
#define DH_DEV_PTZ_OPT_CFG			0x0020		// ��̨��������(�Ѿ��ϳ�����ʹ��CLIENT_GetPtzOptAttr��ȡ��̨��������)
#define DH_DEV_DST_CFG				0x0021      // ����ʱ����
#define DH_DEV_ALARM_CENTER_CFG		0x0022		// ������������
#define DH_DEV_VIDEO_OSD_CFG        0x0023		// ��ƵOSD��������
#define DH_DEV_CDMAGPRS_CFG         0x0024		// CDMA\GPRS��������

#define DH_DEV_IPFILTER_CFG         0x0025		// IP��������
#define DH_DEV_TALK_ENCODE_CFG      0x0026      // �����Խ���������
#define DH_DEV_RECORD_PACKET_CFG    0X0027      // ¼������������
#define DH_DEV_MMS_CFG              0X0028		// ����MMS���� 
#define DH_DEV_SMSACTIVATION_CFG	0X0029		// ���ż���������������
#define DH_DEV_DIALINACTIVATION_CFG	0X002A		// ���ż���������������
#define DH_DEV_SNIFFER_CFG_EX		0x0030		// ����ץ������
#define DH_DEV_DOWNLOAD_RATE_CFG	0x0031		// �����ٶ�����
#define DH_DEV_PANORAMA_SWITCH_CFG	0x0032		// ȫ���л���������
#define DH_DEV_LOST_FOCUS_CFG		0x0033		// ʧȥ���㱨������
#define DH_DEV_ALARM_DECODE_CFG		0x0034		// ��������������
#define DH_DEV_VIDEOOUT_CFG         0x0035      // ��Ƶ�����������
#define DH_DEV_POINT_CFG			0x0036		// Ԥ�Ƶ�ʹ������
#define DH_DEV_IP_COLLISION_CFG     0x0037      // Ip��ͻ��ⱨ������
#define DH_DEV_OSD_ENABLE_CFG		0x0038		// OSD����ʹ������
#define DH_DEV_LOCALALARM_CFG 		0x0039		// ���ر�������(�ṹ��DH_ALARMIN_CFG_EX)
#define DH_DEV_NETALARM_CFG 		0x003A		// ���籨������(�ṹ��DH_ALARMIN_CFG_EX)
#define DH_DEV_MOTIONALARM_CFG 		0x003B		// ���챨������(�ṹ��DH_MOTION_DETECT_CFG_EX)
#define DH_DEV_VIDEOLOSTALARM_CFG 	0x003C		// ��Ƶ��ʧ��������(�ṹ��DH_VIDEO_LOST_CFG_EX)
#define DH_DEV_BLINDALARM_CFG 		0x003D		// ��Ƶ�ڵ���������(�ṹ��DH_BLIND_CFG_EX)
#define DH_DEV_DISKALARM_CFG 		0x003E		// Ӳ�̱�������(�ṹ��DH_DISK_ALARM_CFG_EX)
#define DH_DEV_NETBROKENALARM_CFG 	0x003F		// �����жϱ�������(�ṹ��DH_NETBROKEN_ALARM_CFG_EX)
#define DH_DEV_ENCODER_CFG          0x0040      // ����ͨ����ǰ�˱�������Ϣ�����DVRʹ�ã��ṹ��DEV_ENCODER_CFG��
#define DH_DEV_TV_ADJUST_CFG        0x0041      // TV�������ã�channel����TV��(0��ʼ)�����ͽṹ�壩
#define DH_DEV_ABOUT_VEHICLE_CFG	0x0042		// ����������ã���������ʹ��
#define DH_DEV_ATM_OVERLAY_ABILITY	0x0043		// ��ȡatm����֧��������Ϣ
#define DH_DEV_ATM_OVERLAY_CFG		0x0044		// atm�������ã���atm����
#define DH_DEV_DECODER_TOUR_CFG		0x0045		// ������������Ѳ����
#define DH_DEV_SIP_CFG				0x0046		// SIP����
#define DH_DEV_VICHILE_WIFI_AP_CFG	0x0047		// wifi ap����
#define DH_DEV_STATICALARM_CFG      0x0048      // ��̬�������� 
#define DH_DEV_DECODE_POLICY_CFG    0x0049      // �豸�Ľ����������(�ṹ��DHDEV_DECODEPOLICY_CFG��channelΪ����ͨ��0��ʼ) 
#define DH_DEV_MACHINE_CFG			0x004A		// ������ص�����(�ṹ��DHDEV_MACHINE_CFG)
#define DH_DEV_MAC_COLLISION_CFG    0x004B      // MAC��ͻ�������(�ṹ��ALARM_MAC_COLLISION_CFG)
#define DH_DEV_RTSP_CFG             0x004C      // RTSP����(��Ӧ�ṹ��DHDEV_RTSP_CFG)
#define DH_DEV_232_COM_CARD_CFG     0x004E      // 232���ڿ����ź��¼�����(��Ӧ�ṹ��COM_CARD_SIGNAL_LINK_CFG)
#define DH_DEV_485_COM_CARD_CFG     0x004F      // 485���ڿ����ź��¼�����(��Ӧ�ṹ��COM_CARD_SIGNAL_LINK_CFG)
#define DH_DEV_FTP_PROTO_CFG_EX		0x0050		// FTP�ϴ���չ����(��Ӧ�ṹ��DHDEV_FTP_PROTO_CFG_EX)
#define DH_DEV_SYSLOG_REMOTE_SERVER	0x0051		// SYSLOG Զ�̷���������(��Ӧ�ṹ��DHDEV_SYSLOG_REMOTE_SERVER)
#define DH_DEV_COMMCFG_EX           0x0052      // ��չ������������(��Ӧ�ṹ��DHDEV_COMM_CFG_EX)            
#define DH_DEV_NETCARD_CFG          0x0053      // ������Ϣ����(��Ӧ�ṹ��DHDEV_NETCARD_CFG)
#define DH_DEV_BACKUP_VIDEO_FORMAT  0x0054		// ��Ƶ���ݸ�ʽ����(��Ӧ�ṹ��DHDEV_BACKUP_VIDEO_FORMAT)
#define DH_DEV_STREAM_ENCRYPT_CFG   0x0055      // ������������(��Ӧ�ṹ��DHEDV_STREAM_ENCRYPT)
#define DH_DEV_IPFILTER_CFG_EX      0x0056		// IP����������չ(��Ӧ�ṹ��DHDEV_IPIFILTER_CFG_EX)
#define DH_DEV_CUSTOM_CFG           0x0057      // �û��Զ�������(��Ӧ�ṹ��DHDEV_CUSTOM_CFG)
#define DH_DEV_WLAN_DEVICE_CFG_EX   0x0058      // ���������豸��չ����(��Ӧ�ṹ��DHDEV_WLAN_DEVICE_LIST_EX)
#define DH_DEV_ACC_POWEROFF_CFG     0x0059      // ACC�����¼�����(��Ӧ�ṹ��DHDEV_ACC_POWEROFF_CFG)
#define DH_DEV_EXPLOSION_PROOF_CFG  0x005a      // �����б����¼�����(��Ӧ�ṹ��DHDEV_EXPLOSION_PROOF_CFG)
#define DH_DEV_NETCFG_EX			0x005b		// ������չ����(��Ӧ�ṹ��DHDEV_NET_CFG_EX)
#define DH_DEV_LIGHTCONTROL_CFG     0x005c      // �ƹ��������(��Ӧ�ṹ��DHDEV_LIGHTCONTROL_CFG)
#define DH_DEV_3GFLOW_CFG           0x005d      // 3G������Ϣ����(��Ӧ�ṹ��DHDEV_3GFLOW_INFO_CFG)
#define DH_DEV_IPV6_CFG             0x005e      // IPv6����(��Ӧ�ṹ��DHDEV_IPV6_CFG)
#define DH_DEV_SNMP_CFG             0X005f      // Snmp����(��Ӧ�ṹ��DHDEV_NET_SNMP_CFG), ������ɺ���Ҫ�����豸
#define DH_DEV_SNAP_CONTROL_CFG     0x0060      // ץͼ��������(��Ӧ�ṹ��DHDEV_SNAP_CONTROL_CFG)
#define DH_DEV_GPS_MODE_CFG         0X0061      // GPS��λģʽ����(��Ӧ�ṹ��DHDEV_GPS_MODE_CFG)
#define DH_DEV_SNAP_UPLOAD_CFG      0X0062      // ͼƬ�ϴ�������Ϣ(��Ӧ�ṹ�� DHDEV_SNAP_UPLOAD_CFG)
#define DH_DEV_SPEED_LIMIT_CFG      0x0063      // ����������Ϣ(��Ӧ�ṹ��DHDEV_SPEED_LIMIT_CFG)
#define DH_DEV_ISCSI_CFG			0x0064		// iSCSI����(��Ӧ�ṹ��DHDEV_ISCSI_CFG), ������ɺ���Ҫ�����豸
#define DH_DEV_WIRELESS_ROUTING_CFG	0x0065		// ����·������(��Ӧ�ṹ��DHDEV_WIRELESS_ROUTING_CFG)
#define DH_DEV_ENCLOSURE_CFG        0x0066      // ����Χ������(��Ӧ�ṹ��DHDEV_ENCLOSURE_CFG)
#define DH_DEV_ENCLOSURE_VERSION_CFG 0x0067     // ����Χ���汾������(��Ӧ�ṹ��DHDEV_ENCLOSURE_VERSION_CFG)
#define DH_DEV_RIAD_EVENT_CFG        0x0068     // Raid�¼�����(��Ӧ�ṹ��DHDEV_RAID_EVENT_CFG)
#define DH_DEV_FIRE_ALARM_CFG        0x0069     // �𾯱�������(��Ӧ�ṹ��DHDEV_FIRE_ALARM_CFG)
#define DH_DEV_LOCALALARM_NAME_CFG   0x006a     // �������Ʊ�������(��ӦName1&&name2&&name3...��ʽ�ַ���)
#define DH_DEV_URGENCY_RECORD_CFG    0x0070     // �����洢����(��Ӧ�ṹ��DHDEV_URGENCY_RECORD_CFG)
#define DH_DEV_ELEVATOR_ATTRI_CFG    0x0071     // �������в�������(��Ӧ�ṹ��DHDEV_ELEVATOR_ATTRI_CFG)
#define DH_DEV_ATM_OVERLAY_CFG_EX	 0x0072		// atm�������ã���atm����,֧�ִ���32ͨ�����豸(��Ӧ�ṹ��DHDEV_ATM_OVERLAY_CONFIG_EX)
#define DH_DEV_MACFILTER_CFG		 0x0073		// MAC��������(��Ӧ�ṹ��DHDEV_MACFILTER_CFG)
#define DH_DEV_MACIPFILTER_CFG		 0x0074		// MAC,IP����(Ҫ��ip,mac��һһ��Ӧ��)����(��Ӧ�ṹ��DHDEV_MACIPFILTER_CFG)
#define DH_DEV_STREAM_ENCRYPT_TIME_CFG 0x0075   // ��������(���ܼƻ�)����(��Ӧ�ṹ��DHEDV_STREAM_ENCRYPT)
#define DH_DEV_LIMIT_BIT_RATE_CFG    0x0076     // ����������(��Ӧ�ṹ�� DHDEV_LIMIT_BIT_RATE) 
#define DH_DEV_SNAP_CFG_EX			 0x0077		// ץͼ���������չ(��Ӧ�ṹ�� DHDEV_SNAP_CFG_EX)
#define DH_DEV_DECODER_URL_CFG		0x0078		// ������url����(��Ӧ�ṹ��DHDEV_DECODER_URL_CFG)
#define DH_DEV_TOUR_ENABLE_CFG		0x0079		// ��Ѳʹ������(��Ӧ�ṹ��DHDEV_TOUR_ENABLE_CFG)
#define DH_DEV_VICHILE_WIFI_AP_CFG_EX 0x007a    // wifi ap������չ(��Ӧ�ṹ��DHDEV_VEHICLE_WIFI_AP_CFG_EX)
#define DH_DEV_ENCODER_CFG_EX         0x007b    // ����ͨ����ǰ�˱�������Ϣ��չ��(��Ӧ�ṹ��DEV_ENCODER_CFG_EX)
#define DH_DEV_USER_END_CFG			1000

// �������ͣ���ӦCLIENT_StartListen�ӿ�
#define DH_COMM_ALARM				0x1100		// ���汨��(�����ⲿ��������Ƶ��ʧ����̬���)
#define DH_SHELTER_ALARM			0x1101		// ��Ƶ�ڵ�����
#define DH_DISK_FULL_ALARM			0x1102		// Ӳ��������
#define DH_DISK_ERROR_ALARM			0x1103		// Ӳ�̹��ϱ���
#define DH_SOUND_DETECT_ALARM		0x1104		// ��Ƶ��ⱨ��
#define DH_ALARM_DECODER_ALARM		0x1105		// ��������������

// ��չ�������ͣ���ӦCLIENT_StartListenEx�ӿ�
#define DH_ALARM_ALARM_EX			0x2101		// �ⲿ����
#define DH_MOTION_ALARM_EX			0x2102		// ��̬��ⱨ��
#define DH_VIDEOLOST_ALARM_EX		0x2103		// ��Ƶ��ʧ����
#define DH_SHELTER_ALARM_EX			0x2104		// ��Ƶ�ڵ�����
#define DH_SOUND_DETECT_ALARM_EX	0x2105		// ��Ƶ��ⱨ��
#define DH_DISKFULL_ALARM_EX		0x2106		// Ӳ��������
#define DH_DISKERROR_ALARM_EX		0x2107		// ��Ӳ�̱���
#define DH_ENCODER_ALARM_EX			0x210A		// ����������
#define DH_URGENCY_ALARM_EX			0x210B		// ��������
#define DH_WIRELESS_ALARM_EX		0x210C		// ���߱���
#define DH_NEW_SOUND_DETECT_ALARM_EX 0x210D		// ����Ƶ��ⱨ����������Ϣ�Ľṹ���DH_NEW_SOUND_ALARM_STATE��
#define DH_ALARM_DECODER_ALARM_EX	0x210E		// ��������������
#define DH_DECODER_DECODE_ABILITY	0x210F		// ��������������������
#define DH_FDDI_DECODER_ABILITY		0x2110		// ���˱�����״̬����
#define DH_PANORAMA_SWITCH_ALARM_EX	0x2111		// �л���������
#define DH_LOSTFOCUS_ALARM_EX		0x2112		// ʧȥ���㱨��
#define DH_OEMSTATE_EX				0x2113		// oem��ͣ״̬
#define DH_DSP_ALARM_EX				0x2114		// DSP����
#define DH_ATMPOS_BROKEN_EX			0x2115		// atm��pos���Ͽ������� 0�����ӶϿ� 1����������
#define DH_RECORD_CHANGED_EX		0x2116		// ¼��״̬�仯����
#define DH_CONFIG_CHANGED_EX		0x2117		// ���÷����仯����
#define DH_DEVICE_REBOOT_EX			0x2118		// �豸��������
#define DH_WINGDING_ALARM_EX        0x2119      // ��Ȧ/���������ϱ���
#define DH_TRAF_CONGESTION_ALARM_EX 0x211A      // ��ͨ��������(���������쳣ֹͣ�����Ŷ�)
#define DH_TRAF_EXCEPTION_ALARM_EX  0x211B      // ��ͨ�쳣����(��ͨ��������0���쳣����)
#define DH_EQUIPMENT_FILL_ALARM_EX  0x211C      // �����豸���ϱ���
#define DH_ALARM_ARM_DISARM_STATE	0x211D		// ����������״̬
#define DH_ALARM_ACC_POWEROFF       0x211E      // ACC�ϵ籨��
#define DH_ALARM_3GFLOW_EXCEED      0x211F      // 3G����������ֵ����(������Ϣ�Ľṹ����ṹ��DHDEV_3GFLOW_EXCEED_STATE_INFO)
#define DH_ALARM_SPEED_LIMIT        0x2120      // ���ٱ���
#define DH_ALARM_VEHICLE_INFO_UPLOAD  0x2121    // �����Զ�����Ϣ�ϴ� 
#define DH_STATIC_ALARM_EX          0x2122      // ��̬��ⱨ��
#define DH_PTZ_LOCATION_EX          0x2123      // ��̨��λ��Ϣ
#define DH_ALARM_CARD_RECORD_UPLOAD	0x2124		// ����¼����Ϣ�ϴ�(��Ӧ�ṹ�� ALARM_CARD_RECORD_INFO_UPLOAD)
#define DH_ALARM_ATM_INFO_UPLOAD	0x2125		// ATM������Ϣ�ϴ�(��Ӧ�ṹ�� ALARM_ATM_INFO_UPLOAD)
#define DH_ALARM_ENCLOSURE          0x2126      // ����Χ������(��Ӧ�ṹ��ALARM_ENCLOSURE_INFO)
#define DH_ALARM_SIP_STATE          0x2127      // SIP״̬����(��Ӧ�ṹ��ALARM_SIP_STATE)
#define DH_ALARM_RAID_STATE         0x2128      // RAID�쳣����(��Ӧ�ṹ��ALARM_RAID_INFO)
#define DH_ALARM_CROSSING_SPEED_LIMIT 0x2129	// ·�����ٱ���(��Ӧ�ṹ��ALARM_SPEED_LIMIT)
#define DH_ALARM_OVER_LOADING         0x212A      // ���ر���(��Ӧ�ṹ��ALARM_OVER_LOADING)
#define DH_ALARM_HARD_BRAKING         0x212B      // ��ɲ������(��Ӧ������ALARM_HARD_BRAKING)
#define DH_ALARM_SMOKE_SENSOR         0x212C      // �̸б���(��Ӧ�ṹ��ALARM_SMOKE_SENSOR)
#define DH_ALARM_TRAFFIC_LIGHT_FAULT 0x212D     // ��ͨ�ƹ��ϱ���(��Ӧ�ṹ��ALARM_TRAFFIC_LIGHT_FAULT) 
#define DH_ALARM_TRAFFIC_FLUX_STAT   0x212E     // ��ͨ����ͳ�Ʊ���(��Ӧ�ṹ��ALARM_TRAFFIC_FLUX_LANE_INFO)
#define DH_ALARM_CAMERA_MOVE         0x212F     // �������λ�����¼�(��Ӧ�ṹ��ALARM_CAMERA_MOVE_INFO)
#define DH_ALARM_DETAILEDMOTION      0x2130     // ��ϸ���챨���ϱ���Ϣ(��Ӧ�ṹ��ALARM_DETAILEDMOTION_CHNL_INFO)
#define DH_ALARM_STORAGE_FAILURE      0x2131     // �洢�쳣����(��Ӧ�ṹ��ALARM_STORAGE_FAILURE����)
#define DH_ALARM_FRONTDISCONNECT     0x2132     // ǰ��IPC��������(��Ӧ�ṹ��ALARM_FRONTDISCONNET_INFO)
#define DH_ALARM_ALARM_EX_REMOTE     0x2133     // Զ���ⲿ����(��Ӧ�ṹ�� ALARM_REMOTE_ALARM_INFO)
#define DH_ALARM_BATTERYLOWPOWER     0x2134     // ��ص����ͱ���(��Ӧ�ṹ��ALARM_BATTERYLOWPOWER_INFO)
#define DH_ALARM_TEMPERATURE         0x2135     // �¶ȹ��߱���(��Ӧ�ṹ��ALARM_TEMPERATURE_INFO)
#define DH_ALARM_TIREDDRIVE          0x2136     // ƣ�ͼ�ʻ����(��Ӧ�ṹ��ALARM_TIREDDRIVE_INFO)
#define DH_ALARM_LOST_RECORD         0x2137     // ��¼���¼�����(��Ӧ�ṹ��ALARM_LOST_RECORD)
#define DH_ALARM_HIGH_CPU            0x2138     // CPUռ���ʹ����¼�����(��Ӧ�ṹ��ALARM_HIGH_CPU)
#define DH_ALARM_LOST_NETPACKET      0x2139     // ���緢�����ݶ����¼�����(��Ӧ�ṹ��ALARM_LOST_NETPACKET)
#define DH_ALARM_HIGH_MEMORY         0x213A     // �ڴ�ռ���ʹ����¼�����(��Ӧ�ṹ��ALARM_HIGH_MEMORY)
#define DH_LONG_TIME_NO_OPERATION	 0x213B	    // WEB�û���ʱ���޲����¼�������չ��Ϣ��
#define DH_BLACKLIST_SNAP            0x213C     // ����������ץ���¼�(��Ӧ�ṹ��DH_BLACKLIST_SNAP_INFO)         
#define DH_ALARM_DISK				 0x213E		// Ӳ�̱���(��ӦALARM_DISK_INFO����)
#define	DH_ALARM_FILE_SYSTEM		 0x213F		// �ļ�ϵͳ����(��ӦALARM_FILE_SYSTEM_INFO����)
#define DH_ALARM_IVS                 0x2140     // ���ܱ����¼�(��Ӧ�ṹ��ALARM_IVS_INFO)
#define DH_ALARM_GOODS_WEIGHT_UPLOAD 0x2141		// ������Ϣ�ϱ�(��ӦALARM_GOODS_WEIGHT_UPLOAD_INFO)
#define DH_ALARM_GOODS_WEIGHT		 0x2142		// ������Ϣ����(��ӦALARM_GOODS_WEIGHT_INFO)
#define DH_GPS_STATUS                0x2143     // GPS��λ��Ϣ(��Ӧ NET_GPS_STATUS_INFO)
#define DH_ALARM_DISKBURNED_FULL     0x2144     // Ӳ�̿�¼������(��Ӧ ALARM_DISKBURNED_FULL_INFO)
#define DH_ALARM_STORAGE_LOW_SPACE	 0x2145		// �洢���������¼�(��ӦALARM_STORAGE_LOW_SPACE_INFO)
#define DH_ALARM_DISK_FLUX			 0x2160		// Ӳ�������쳣�¼�(��ӦALARM_DISK_FLUX)
#define DH_ALARM_NET_FLUX			 0x2161		// ���������쳣�¼�(��ӦALARM_NET_FLUX)
#define	DH_ALARM_FAN_SPEED			 0x2162		// ����ת���쳣�¼�(��ӦALARM_FAN_SPEED)
#define DH_ALARM_STORAGE_FAILURE_EX  0x2163     // �洢���󱨾�(��Ӧ�ṹ��ALARM_STORAGE_FAILURE_EX)
#define	DH_ALARM_RECORD_FAILED		 0x2164		// ¼���쳣����(��Ӧ�ṹ��ALARM_RECORD_FAILED_INFO)
#define DH_ALARM_STORAGE_BREAK_DOWN	 0x2165		// �洢�����¼�(��Ӧ�ṹ��ALARM_STORAGE_BREAK_DOWN_INFO)
#define DH_ALARM_VIDEO_ININVALID     0x2166     // ��Ƶ����ͨ��ʧЧ�¼����������õ���Ƶ����ͨ�������������豸����������ALARM_VIDEO_ININVALID_INFO


// �¼�����
#define DH_CONFIG_RESULT_EVENT_EX	0x3000		// �޸����õķ����룻���ؽṹ��DEV_SET_RESULT
#define DH_REBOOT_EVENT_EX			0x3001		// �豸�����¼������δ�������������ǰ�޸ĵ����ò���������Ч
#define DH_AUTO_TALK_START_EX		0x3002		// �豸�������뿪ʼ�����Խ�
#define DH_AUTO_TALK_STOP_EX		0x3003		// �豸����ֹͣ�����Խ�
#define DH_CONFIG_CHANGE_EX			0x3004		// �豸���÷����ı�
#define DH_IPSEARCH_EVENT_EX        0x3005      // IP�����¼�, �����ַ�����ʽ����:DevName::Manufacturer::MAC::IP::Port::DevType::POEPort::SubMask::GateWay&&DevName::Manufacturer::MAC::IP::Port::DevType::POEPort::SubMask::GateWay &&��
#define DH_AUTO_RECONNECT_FAILD     0x3006      // �Զ�����ʧ���¼�
#define DH_REALPLAY_FAILD_EVENT     0x3007      // ����ʧ���¼�,���ؽṹ��DEV_PLAY_RESULT
#define DH_PLAYBACK_FAILD_EVENT     0x3008      // �ط�ʧ���¼�,���ؽṹ��DEV_PLAY_RESULT   
#define DH_IVS_TRAFFIC_REALFLOWINFO 0x3009      // ��ͨʵʱ������Ϣ�¼�ALARM_IVS_TRAFFIC_REALFLOW_INFO


// �����ϴ����ܵı������ͣ���ӦCLIENT_StartService�ӿڡ�NEW_ALARM_UPLOAD�ṹ��.
#define DH_UPLOAD_ALARM				0x4000		// �ⲿ����		
#define DH_UPLOAD_MOTION_ALARM		0x4001		// ��̬��ⱨ��
#define DH_UPLOAD_VIDEOLOST_ALARM	0x4002		// ��Ƶ��ʧ����
#define DH_UPLOAD_SHELTER_ALARM		0x4003		// ��Ƶ�ڵ�����
#define DH_UPLOAD_SOUND_DETECT_ALARM 0x4004		// ��Ƶ��ⱨ��
#define DH_UPLOAD_DISKFULL_ALARM	0x4005		// Ӳ��������
#define DH_UPLOAD_DISKERROR_ALARM	0x4006		// ��Ӳ�̱���
#define DH_UPLOAD_ENCODER_ALARM		0x4007		// ����������
#define DH_UPLOAD_DECODER_ALARM		0x400B		// ��������������
#define DH_UPLOAD_EVENT				0x400C		// ��ʱ�ϴ���
#define DH_UPLOAD_IVS				0x400D		// ���ܱ���, �Խ��ṹ��ALARM_UPLOAD_IVS_INFO

// �첽�ӿڻص�����
#define RESPONSE_DECODER_CTRL_TV	0x00000001	// ��ӦCLIENT_CtrlDecTVScreen�ӿ�
#define RESPONSE_DECODER_SWITCH_TV	0x00000002	// ��ӦCLIENT_SwitchDecTVEncoder�ӿ�
#define RESPONSE_DECODER_PLAYBACK	0x00000003	// ��ӦCLIENT_DecTVPlayback�ӿ�

// CLIENT_FileTransmit�ӿڴ����ļ�����
#define DH_DEV_UPGRADEFILETRANS_START 0x0000    // ��ʼ�����ļ��ϴ�(��Ӧ�ṹ�� DHDEV_UPGRADE_FILE_INFO)
#define DH_DEV_UPGRADEFILETRANS_SEND  0x0001    // ���������ļ�  
#define DH_DEV_UPGRADEFILETRANS_STOP  0x0002    // ֹͣ���������ļ�
#define DH_DEV_BLACKWHITETRANS_START  0x0003    // ��ʼ���ͺڰ�����(��Ӧ�ṹ��DHDEV_BLACKWHITE_LIST_INFO)
#define DH_DEV_BLACKWHITETRANS_SEND   0x0004    // ���ͺڰ�����
#define DH_DEV_BLACKWHITETRANS_STOP   0x0005    // ֹͣ���ͺڰ����� 
#define DH_DEV_BLACKWHITE_LOAD        0x0006    // ���غڰ�����(��Ӧ�ṹ��DHDEV_LOAD_BLACKWHITE_LIST_INFO)
#define DH_DEV_BLACKWHITE_LOAD_STOP   0x0007    // ֹͣ���غڰ�����
#define DH_DEV_FILETRANS_STOP		  0x002B	// ֹͣ�ļ��ϴ�
#define DH_DEV_FILETRANS_BURN		  0x002C	// ��¼�ļ��ϴ�


// �ֱ����б���������ֱ�����������롢�����
#define	DH_CAPTURE_SIZE_D1			0x00000001
#define DH_CAPTURE_SIZE_HD1			0x00000002
#define DH_CAPTURE_SIZE_BCIF		0x00000004
#define DH_CAPTURE_SIZE_CIF			0x00000008
#define DH_CAPTURE_SIZE_QCIF		0x00000010	
#define DH_CAPTURE_SIZE_VGA			0x00000020	
#define DH_CAPTURE_SIZE_QVGA		0x00000040
#define DH_CAPTURE_SIZE_SVCD		0x00000080
#define DH_CAPTURE_SIZE_QQVGA		0x00000100
#define DH_CAPTURE_SIZE_SVGA		0x00000200
#define DH_CAPTURE_SIZE_XVGA		0x00000400
#define DH_CAPTURE_SIZE_WXGA		0x00000800
#define DH_CAPTURE_SIZE_SXGA		0x00001000
#define DH_CAPTURE_SIZE_WSXGA		0x00002000   
#define DH_CAPTURE_SIZE_UXGA		0x00004000
#define DH_CAPTURE_SIZE_WUXGA       0x00008000
#define DH_CAPTURE_SIZE_LFT         0x00010000
#define DH_CAPTURE_SIZE_720		    0x00020000
#define DH_CAPTURE_SIZE_1080		0x00040000
#define DH_CAPTURE_SIZE_1_3M		0x00080000
#define DH_CAPTURE_SIZE_2M			0x00100000
#define DH_CAPTURE_SIZE_5M			0x00200000
#define DH_CAPTURE_SIZE_3M			0x00400000				
#define DH_CAPTURE_SIZE_5_0M        0x00800000
#define DH_CPTRUTE_SIZE_1_2M 		0x01000000	
#define DH_CPTRUTE_SIZE_1408_1024   0x02000000	
#define DH_CPTRUTE_SIZE_8M	        0x04000000	
#define DH_CPTRUTE_SIZE_2560_1920   0x08000000
#define DH_CAPTURE_SIZE_960H        0x10000000
#define DH_CAPTURE_SIZE_960_720     0x20000000

// ����ģʽ�б������������ģʽ��������롢�����
#define DH_CAPTURE_COMP_DIVX_MPEG4	0x00000001
#define DH_CAPTURE_COMP_MS_MPEG4 	0x00000002
#define DH_CAPTURE_COMP_MPEG2		0x00000004
#define DH_CAPTURE_COMP_MPEG1		0x00000008
#define DH_CAPTURE_COMP_H263		0x00000010
#define DH_CAPTURE_COMP_MJPG		0x00000020
#define DH_CAPTURE_COMP_FCC_MPEG4	0x00000040
#define DH_CAPTURE_COMP_H264		0x00000080

// �������������������뱨������������������롢�����
#define DH_ALARM_UPLOAD				0x00000001
#define DH_ALARM_RECORD				0x00000002
#define DH_ALARM_PTZ				0x00000004
#define DH_ALARM_MAIL				0x00000008
#define DH_ALARM_TOUR				0x00000010
#define DH_ALARM_TIP				0x00000020
#define DH_ALARM_OUT				0x00000040
#define DH_ALARM_FTP_UL				0x00000080
#define DH_ALARM_BEEP				0x00000100
#define DH_ALARM_VOICE				0x00000200
#define DH_ALARM_SNAP				0x00000400

// "�ָ�Ĭ������"���룬�ɽ����롢�����
#define DH_RESTORE_COMMON			0x00000001	// ��ͨ����
#define DH_RESTORE_CODING			0x00000002	// ��������
#define DH_RESTORE_VIDEO			0x00000004	// ¼������
#define DH_RESTORE_COMM				0x00000008	// ��������
#define DH_RESTORE_NETWORK			0x00000010	// ��������
#define DH_RESTORE_ALARM			0x00000020	// ��������
#define DH_RESTORE_VIDEODETECT		0x00000040	// ��Ƶ���
#define DH_RESTORE_PTZ				0x00000080	// ��̨����
#define DH_RESTORE_OUTPUTMODE		0x00000100	// ���ģʽ
#define DH_RESTORE_CHANNELNAME		0x00000200	// ͨ������
#define DH_RESTORE_VIDEOINOPTIONS   0x00000400  // ����ͷ����
#define DH_RESTORE_CPS              0x00000800  // ���ܽ�ͨ
#define DH_RESTORE_INTELLIGENT      0x00001000  // ��Ƶ����
#define DH_RESTORE_REMOTEDEVICE     0x00002000  // Զ���豸����
#define DH_RESTORE_DECODERVIDEOOUT  0x00004000  // ������Ѳ
#define DH_RESTORE_LINKMODE         0x00008000  // ����ģʽ
#define DH_RESTORE_COMPOSITE        0x00010000  // �ں���    
#define DH_RESTORE_ALL				0x80000000	// ȫ������

// ��̨�����б�
// ���ĸ��ֽ�����
#define PTZ_DIRECTION				0x00000001	// ����
#define PTZ_ZOOM					0x00000002	// �䱶
#define PTZ_FOCUS					0x00000004	// �۽�
#define PTZ_IRIS					0x00000008	// ��Ȧ
#define PTZ_ALARM					0x00000010	// ��������
#define PTZ_LIGHT					0x00000020	// �ƹ�
#define PTZ_SETPRESET				0x00000040	// ����Ԥ�õ�
#define PTZ_CLEARPRESET				0x00000080	// ���Ԥ�õ�
#define PTZ_GOTOPRESET				0x00000100	// ת��Ԥ�õ�
#define PTZ_AUTOPANON				0x00000200	// ˮƽ��ʼ
#define PTZ_AUTOPANOFF				0x00000400	// ˮƽ����
#define PTZ_SETLIMIT				0x00000800	// ���ñ߽�
#define PTZ_AUTOSCANON				0x00001000	// �Զ�ɨ�迪ʼ
#define PTZ_AUTOSCANOFF				0x00002000	// �Զ�ɨ�迪ֹͣ
#define PTZ_ADDTOUR					0x00004000	// ����Ѳ����
#define PTZ_DELETETOUR				0x00008000	// ɾ��Ѳ����
#define PTZ_STARTTOUR				0x00010000	// ��ʼѲ��
#define PTZ_STOPTOUR				0x00020000	// ����Ѳ��
#define PTZ_CLEARTOUR				0x00040000	// ɾ��Ѳ��
#define PTZ_SETPATTERN				0x00080000	// ����ģʽ
#define PTZ_STARTPATTERN			0x00100000	// ��ʼģʽ
#define PTZ_STOPPATTERN				0x00200000	// ֹͣģʽ
#define PTZ_CLEARPATTERN			0x00400000	// ���ģʽ
#define PTZ_POSITION				0x00800000	// ���ٶ�λ
#define PTZ_AUX						0x01000000	// ��������
#define PTZ_MENU					0x02000000	// ����˵�
#define PTZ_EXIT					0x04000000	// �˳�����˵�
#define PTZ_ENTER					0x08000000	// ȷ��
#define PTZ_ESC						0x10000000	// ȡ��
#define PTZ_MENUUPDOWN				0x20000000	// �˵����²���
#define PTZ_MENULEFTRIGHT			0x40000000	// �˵����Ҳ���
#define PTZ_OPT_NUM					0x80000000	// �����ĸ���
// ���ĸ��ֽ�����
#define PTZ_DEV						0x00000001	// ��̨����
#define PTZ_MATRIX					0x00000002	// �������

// ץͼ��Ƶ��������
#define CODETYPE_MPEG4				0
#define CODETYPE_H264				1
#define CODETYPE_JPG				2

// ���������б�
#define DH_CAPTURE_BRC_CBR			0
#define DH_CAPTURE_BRC_VBR			1
//#define DH_CAPTURE_BRC_MBR		2

// ���ܷ����¼�����
#define EVENT_IVS_ALL						0x00000001		// ���������¼�
#define EVENT_IVS_CROSSLINEDETECTION		0x00000002		// �������¼�
#define EVENT_IVS_CROSSREGIONDETECTION		0x00000003		// �������¼�
#define EVENT_IVS_PASTEDETECTION			0x00000004		// �����¼�
#define EVENT_IVS_LEFTDETECTION				0x00000005		// ��Ʒ�����¼�
#define EVENT_IVS_STAYDETECTION				0x00000006		// ͣ���¼�
#define EVENT_IVS_WANDERDETECTION			0x00000007		// �ǻ��¼�
#define EVENT_IVS_PRESERVATION				0x00000008		// ��Ʒ��ȫ�¼�
#define EVENT_IVS_MOVEDETECTION				0x00000009		// �ƶ��¼�
#define EVENT_IVS_TAILDETECTION				0x0000000A		// β���¼�
#define EVENT_IVS_RIOTERDETECTION			0x0000000B		// �����¼�
#define EVENT_IVS_FIREDETECTION				0x0000000C		// ���¼�
#define EVENT_IVS_SMOKEDETECTION			0x0000000D		// ���������¼�
#define EVENT_IVS_FIGHTDETECTION			0x0000000E		// ��Ź�¼�
#define EVENT_IVS_FLOWSTAT					0x0000000F		// ����ͳ���¼�
#define EVENT_IVS_NUMBERSTAT				0x00000010		// ����ͳ���¼�
#define EVENT_IVS_CAMERACOVERDDETECTION		0x00000011		// ����ͷ�����¼�
#define EVENT_IVS_CAMERAMOVEDDETECTION		0x00000012		// ����ͷ�ƶ��¼�
#define EVENT_IVS_VIDEOABNORMALDETECTION	0x00000013		// ��Ƶ�쳣�¼�
#define EVENT_IVS_VIDEOBADDETECTION			0x00000014		// ��Ƶ���¼�
#define EVENT_IVS_TRAFFICCONTROL			0x00000015		// ��ͨ�����¼�
#define EVENT_IVS_TRAFFICACCIDENT			0x00000016		// ��ͨ�¹��¼�
#define EVENT_IVS_TRAFFICJUNCTION			0x00000017		// ��ͨ·���¼�----�Ϲ���
#define EVENT_IVS_TRAFFICGATE				0x00000018		// ��ͨ�����¼�----�Ϲ���
#define EVENT_TRAFFICSNAPSHOT				0x00000019		// ��ͨץ���¼�
#define EVENT_IVS_FACEDETECT                0x0000001A      // ��������¼� 
#define EVENT_IVS_TRAFFICJAM                0x0000001B      // ��ͨӵ���¼�
#define EVENT_IVS_TRAFFIC_RUNREDLIGHT		0x00000100		// ��ͨΥ��-������¼�
#define EVENT_IVS_TRAFFIC_OVERLINE			0x00000101		// ��ͨΥ��-ѹ�������¼�
#define EVENT_IVS_TRAFFIC_RETROGRADE		0x00000102		// ��ͨΥ��-�����¼�
#define EVENT_IVS_TRAFFIC_TURNLEFT			0x00000103		// ��ͨΥ��-Υ����ת
#define EVENT_IVS_TRAFFIC_TURNRIGHT			0x00000104		// ��ͨΥ��-Υ����ת
#define EVENT_IVS_TRAFFIC_UTURN				0x00000105		// ��ͨΥ��-Υ�µ�ͷ
#define EVENT_IVS_TRAFFIC_OVERSPEED			0x00000106		// ��ͨΥ��-����
#define EVENT_IVS_TRAFFIC_UNDERSPEED		0x00000107		// ��ͨΥ��-����
#define EVENT_IVS_TRAFFIC_PARKING           0x00000108      // ��ͨΥ��-Υ��ͣ��
#define EVENT_IVS_TRAFFIC_WRONGROUTE        0x00000109      // ��ͨΥ��-����������ʻ
#define EVENT_IVS_TRAFFIC_CROSSLANE         0x0000010A      // ��ͨΥ��-Υ�±��
#define EVENT_IVS_TRAFFIC_OVERYELLOWLINE    0x0000010B      // ��ͨΥ��-ѹ���� 
#define EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER 0x0000010C      // ��ͨΥ��-·����ʻ�¼�   
#define EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE 0x0000010E      // ��ͨΥ��-���Ƴ�ռ���¼�
#define EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY 0x0000010F		// ��ͨΥ��-���������������¼�
#define EVENT_IVS_CROSSFENCEDETECTION       0x0000011F      // ��ԽΧ���¼�
#define EVENT_IVS_ELECTROSPARKDETECTION     0X00000110      // ����¼�
#define EVENT_IVS_TRAFFIC_NOPASSING         0x00000111      // ��ͨΥ��-��ֹͨ���¼�
#define EVENT_IVS_ABNORMALRUNDETECTION      0x00000112      // �쳣�����¼�
#define EVENT_IVS_RETROGRADEDETECTION       0x00000113      // ��Ա�����¼�
#define EVENT_IVS_INREGIONDETECTION         0x00000114      // �����ڼ���¼�
#define EVENT_IVS_TAKENAWAYDETECTION        0x00000115      // ��Ʒ�����¼�
#define EVENT_IVS_PARKINGDETECTION          0x00000116      // �Ƿ�ͣ���¼�
#define EVENT_IVS_FACERECOGNITION			0x00000117		// ����ʶ���¼�
#define EVENT_IVS_TRAFFIC_MANUALSNAP        0x00000118      // ��ͨ�ֶ�ץ���¼�
#define EVENT_IVS_TRAFFIC_FLOWSTATE			0x00000119		// ��ͨ����ͳ���¼�
#define EVENT_IVS_TRAFFIC_STAY				0x0000011A		// ��ͨ�����¼�
#define EVENT_IVS_TRAFFIC_VEHICLEINROUTE	0x0000011B		// �г�ռ���¼�
#define EVENT_ALARM_MOTIONDETECT            0x0000011C      // ��Ƶ�ƶ�����¼�
#define EVENT_ALARM_LOCALALARM              0x0000011D      // �ⲿ�����¼�
#define EVENT_IVS_PRISONERRISEDETECTION		0X0000011E		// ���������������¼�
#define EVENT_IVS_TRAFFIC_TOLLGATE			0X00000120		// ��ͨΥ��-�����¼�----�¹���
#define EVENT_IVS_DENSITYDETECTION			0x00000121      // ��Ա�ܼ��ȼ��
#define EVENT_IVS_VIDEODIAGNOSIS            0X00000122		// ��Ƶ��Ͻ���¼�
#define EVENT_IVS_QUEUEDETECTION            0x00000123      // �ŶӼ�ⱨ���¼�
#define EVENT_IVS_TRAFFIC_VEHICLEINBUSROUTE 0x00000124      // ռ�ù��������¼�
#define EVENT_IVS_TRAFFIC_BACKING           0x00000125      // Υ�µ����¼�
#define EVENT_IVS_AUDIO_ABNORMALDETECTION   0x00000126      // �����쳣���
#define EVENT_IVS_TRAFFIC_RUNYELLOWLIGHT    0x00000127      // ��ͨΥ��-���Ƶ��¼�
#define EVENT_IVS_CLIMBDETECTION            0x00000128      // �ʸ߼���¼�
#define EVENT_IVS_LEAVEDETECTION            0x00000129      // ��ڼ���¼�
#define EVENT_IVS_TRAFFIC_PARKINGONYELLOWBOX 0x0000012A	    // ��������ץ���¼�
#define EVENT_IVS_TRAFFIC_PARKINGSPACEPARKING 0x0000012B	// ��λ�г��¼�
#define EVENT_IVS_TRAFFIC_PARKINGSPACENOPARKING 0x0000012C	// ��λ�޳��¼�	
#define EVENT_IVS_TRAFFIC_PEDESTRAIN        0x0000012D      // ��ͨ�����¼�
#define EVENT_IVS_TRAFFIC_THROW             0x0000012E      // ��ͨ������Ʒ�¼�
#define EVENT_IVS_TRAFFIC_IDLE              0x0000012F      // ��ͨ�����¼�

//
#define EVENT_IVS_TRAFFIC_ALL				0x000001FF		// ������traffic��ͷ���¼���Ŀǰָ����
															// EVENT_IVS_TRAFFICCONTROL -> EVENT_TRAFFICSNAPSHOT
															// EVENT_IVS_TRAFFIC_RUNREDLIGHT -> EVENT_IVS_TRAFFIC_UNDERSPEED
// �������ʹ��ţ���ӦCLIENT_GetLastError�ӿڵķ���ֵ
#define _EC(x)						(0x80000000|x)
#define NET_NOERROR 				0			// û�д���
#define NET_ERROR					-1			// δ֪����
#define NET_SYSTEM_ERROR			_EC(1)		// Windowsϵͳ����
#define NET_NETWORK_ERROR			_EC(2)		// ������󣬿�������Ϊ���糬ʱ
#define NET_DEV_VER_NOMATCH			_EC(3)		// �豸Э�鲻ƥ��
#define NET_INVALID_HANDLE			_EC(4)		// �����Ч
#define NET_OPEN_CHANNEL_ERROR		_EC(5)		// ��ͨ��ʧ��
#define NET_CLOSE_CHANNEL_ERROR		_EC(6)		// �ر�ͨ��ʧ��
#define NET_ILLEGAL_PARAM			_EC(7)		// �û��������Ϸ�
#define NET_SDK_INIT_ERROR			_EC(8)		// SDK��ʼ������
#define NET_SDK_UNINIT_ERROR		_EC(9)		// SDK��������
#define NET_RENDER_OPEN_ERROR		_EC(10)		// ����render��Դ����
#define NET_DEC_OPEN_ERROR			_EC(11)		// �򿪽�������
#define NET_DEC_CLOSE_ERROR			_EC(12)		// �رս�������
#define NET_MULTIPLAY_NOCHANNEL		_EC(13)		// �໭��Ԥ���м�⵽ͨ����Ϊ0
#define NET_TALK_INIT_ERROR			_EC(14)		// ¼�����ʼ��ʧ��
#define NET_TALK_NOT_INIT			_EC(15)		// ¼����δ����ʼ��
#define	NET_TALK_SENDDATA_ERROR		_EC(16)		// ������Ƶ���ݳ���
#define NET_REAL_ALREADY_SAVING		_EC(17)		// ʵʱ�����Ѿ����ڱ���״̬
#define NET_NOT_SAVING				_EC(18)		// δ����ʵʱ����
#define NET_OPEN_FILE_ERROR			_EC(19)		// ���ļ�����
#define NET_PTZ_SET_TIMER_ERROR		_EC(20)		// ������̨���ƶ�ʱ��ʧ��
#define NET_RETURN_DATA_ERROR		_EC(21)		// �Է������ݵ�У�����
#define NET_INSUFFICIENT_BUFFER		_EC(22)		// û���㹻�Ļ���
#define NET_NOT_SUPPORTED			_EC(23)		// ��ǰSDKδ֧�ָù���
#define NET_NO_RECORD_FOUND			_EC(24)		// ��ѯ����¼��
#define NET_NOT_AUTHORIZED			_EC(25)		// �޲���Ȩ��
#define NET_NOT_NOW					_EC(26)		// ��ʱ�޷�ִ��
#define NET_NO_TALK_CHANNEL			_EC(27)		// δ���ֶԽ�ͨ��
#define NET_NO_AUDIO				_EC(28)		// δ������Ƶ
#define NET_NO_INIT					_EC(29)		// ����SDKδ����ʼ��
#define NET_DOWNLOAD_END			_EC(30)		// �����ѽ���
#define NET_EMPTY_LIST				_EC(31)		// ��ѯ���Ϊ��
#define NET_ERROR_GETCFG_SYSATTR	_EC(32)		// ��ȡϵͳ��������ʧ��
#define NET_ERROR_GETCFG_SERIAL		_EC(33)		// ��ȡ���к�ʧ��
#define NET_ERROR_GETCFG_GENERAL	_EC(34)		// ��ȡ��������ʧ��
#define NET_ERROR_GETCFG_DSPCAP		_EC(35)		// ��ȡDSP��������ʧ��
#define NET_ERROR_GETCFG_NETCFG		_EC(36)		// ��ȡ��������ʧ��
#define NET_ERROR_GETCFG_CHANNAME	_EC(37)		// ��ȡͨ������ʧ��
#define NET_ERROR_GETCFG_VIDEO		_EC(38)		// ��ȡ��Ƶ����ʧ��
#define NET_ERROR_GETCFG_RECORD		_EC(39)		// ��ȡ¼������ʧ��
#define NET_ERROR_GETCFG_PRONAME	_EC(40)		// ��ȡ������Э������ʧ��
#define NET_ERROR_GETCFG_FUNCNAME	_EC(41)		// ��ȡ232���ڹ�������ʧ��
#define NET_ERROR_GETCFG_485DECODER	_EC(42)		// ��ȡ����������ʧ��
#define NET_ERROR_GETCFG_232COM		_EC(43)		// ��ȡ232��������ʧ��
#define NET_ERROR_GETCFG_ALARMIN	_EC(44)		// ��ȡ�ⲿ������������ʧ��
#define NET_ERROR_GETCFG_ALARMDET	_EC(45)		// ��ȡ��̬��ⱨ��ʧ��
#define NET_ERROR_GETCFG_SYSTIME	_EC(46)		// ��ȡ�豸ʱ��ʧ��
#define NET_ERROR_GETCFG_PREVIEW	_EC(47)		// ��ȡԤ������ʧ��
#define NET_ERROR_GETCFG_AUTOMT		_EC(48)		// ��ȡ�Զ�ά������ʧ��
#define NET_ERROR_GETCFG_VIDEOMTRX	_EC(49)		// ��ȡ��Ƶ��������ʧ��
#define NET_ERROR_GETCFG_COVER		_EC(50)		// ��ȡ�����ڵ�����ʧ��
#define NET_ERROR_GETCFG_WATERMAKE	_EC(51)		// ��ȡͼ��ˮӡ����ʧ��
#define NET_ERROR_SETCFG_GENERAL	_EC(55)		// �޸ĳ�������ʧ��
#define NET_ERROR_SETCFG_NETCFG		_EC(56)		// �޸���������ʧ��
#define NET_ERROR_SETCFG_CHANNAME	_EC(57)		// �޸�ͨ������ʧ��
#define NET_ERROR_SETCFG_VIDEO		_EC(58)		// �޸���Ƶ����ʧ��
#define NET_ERROR_SETCFG_RECORD		_EC(59)		// �޸�¼������ʧ��
#define NET_ERROR_SETCFG_485DECODER	_EC(60)		// �޸Ľ���������ʧ��
#define NET_ERROR_SETCFG_232COM		_EC(61)		// �޸�232��������ʧ��
#define NET_ERROR_SETCFG_ALARMIN	_EC(62)		// �޸��ⲿ���뱨������ʧ��
#define NET_ERROR_SETCFG_ALARMDET	_EC(63)		// �޸Ķ�̬��ⱨ������ʧ��
#define NET_ERROR_SETCFG_SYSTIME	_EC(64)		// �޸��豸ʱ��ʧ��
#define NET_ERROR_SETCFG_PREVIEW	_EC(65)		// �޸�Ԥ������ʧ��
#define NET_ERROR_SETCFG_AUTOMT		_EC(66)		// �޸��Զ�ά������ʧ��
#define NET_ERROR_SETCFG_VIDEOMTRX	_EC(67)		// �޸���Ƶ��������ʧ��
#define NET_ERROR_SETCFG_COVER		_EC(68)		// �޸������ڵ�����ʧ��
#define NET_ERROR_SETCFG_WATERMAKE	_EC(69)		// �޸�ͼ��ˮӡ����ʧ��
#define NET_ERROR_SETCFG_WLAN		_EC(70)		// �޸�����������Ϣʧ��
#define NET_ERROR_SETCFG_WLANDEV	_EC(71)		// ѡ�����������豸ʧ��
#define NET_ERROR_SETCFG_REGISTER	_EC(72)		// �޸�����ע���������ʧ��
#define NET_ERROR_SETCFG_CAMERA		_EC(73)		// �޸�����ͷ��������ʧ��
#define NET_ERROR_SETCFG_INFRARED	_EC(74)		// �޸ĺ��ⱨ������ʧ��
#define NET_ERROR_SETCFG_SOUNDALARM	_EC(75)		// �޸���Ƶ��������ʧ��
#define NET_ERROR_SETCFG_STORAGE    _EC(76)		// �޸Ĵ洢λ������ʧ��
#define NET_AUDIOENCODE_NOTINIT		_EC(77)		// ��Ƶ����ӿ�û�гɹ���ʼ��
#define NET_DATA_TOOLONGH			_EC(78)		// ���ݹ���
#define NET_UNSUPPORTED				_EC(79)		// �豸��֧�ָò���
#define NET_DEVICE_BUSY				_EC(80)		// �豸��Դ����
#define NET_SERVER_STARTED			_EC(81)		// �������Ѿ�����
#define NET_SERVER_STOPPED			_EC(82)		// ��������δ�ɹ�����
#define NET_LISTER_INCORRECT_SERIAL	_EC(83)		// �������к�����
#define NET_QUERY_DISKINFO_FAILED	_EC(84)		// ��ȡӲ����Ϣʧ��
#define NET_ERROR_GETCFG_SESSION	_EC(85)		// ��ȡ����Session��Ϣ
#define NET_USER_FLASEPWD_TRYTIME	_EC(86)		// ����������󳬹����ƴ���
#define NET_LOGIN_ERROR_PASSWORD	_EC(100)	// ���벻��ȷ
#define NET_LOGIN_ERROR_USER		_EC(101)	// �ʻ�������
#define NET_LOGIN_ERROR_TIMEOUT		_EC(102)	// �ȴ���¼���س�ʱ
#define NET_LOGIN_ERROR_RELOGGIN	_EC(103)	// �ʺ��ѵ�¼
#define NET_LOGIN_ERROR_LOCKED		_EC(104)	// �ʺ��ѱ�����
#define NET_LOGIN_ERROR_BLACKLIST	_EC(105)	// �ʺ��ѱ���Ϊ������
#define NET_LOGIN_ERROR_BUSY		_EC(106)	// ��Դ���㣬ϵͳæ
#define NET_LOGIN_ERROR_CONNECT		_EC(107)	// ��¼�豸��ʱ���������粢����
#define NET_LOGIN_ERROR_NETWORK		_EC(108)	// ��������ʧ��
#define NET_LOGIN_ERROR_SUBCONNECT	_EC(109)	// ��¼�豸�ɹ������޷�������Ƶͨ������������״��
#define NET_LOGIN_ERROR_MAXCONNECT  _EC(110)    // �������������
#define NET_LOGIN_ERROR_PROTOCOL3_ONLY _EC(111)	// ֻ֧��3��Э��
#define NET_LOGIN_ERROR_UKEY_LOST	_EC(112)	// δ����U�ܻ�U����Ϣ����
#define NET_LOGIN_ERROR_NO_AUTHORIZED _EC(113)  // �ͻ���IP��ַû�е�¼Ȩ��  
#define NET_RENDER_SOUND_ON_ERROR	_EC(120)	// Render�����Ƶ����
#define NET_RENDER_SOUND_OFF_ERROR	_EC(121)	// Render��ر���Ƶ����
#define NET_RENDER_SET_VOLUME_ERROR	_EC(122)	// Render�������������
#define NET_RENDER_ADJUST_ERROR		_EC(123)	// Render�����û����������
#define NET_RENDER_PAUSE_ERROR		_EC(124)	// Render����ͣ���ų���
#define NET_RENDER_SNAP_ERROR		_EC(125)	// Render��ץͼ����
#define NET_RENDER_STEP_ERROR		_EC(126)	// Render�ⲽ������
#define NET_RENDER_FRAMERATE_ERROR	_EC(127)	// Render������֡�ʳ���
#define NET_RENDER_DISPLAYREGION_ERROR	_EC(128)// Render��������ʾ�������
#define NET_RENDER_CHOOSEAUDIO_ERROR	_EC(129)// Render��������Ƶͨ������
#define NET_RENDER_GETAUDIOSTATE_ERROR	_EC(130)// Render�����û�ȡ��Ƶͨ��״̬����
#define NET_GROUP_EXIST				_EC(140)	// �����Ѵ���
#define	NET_GROUP_NOEXIST			_EC(141)	// ����������
#define NET_GROUP_RIGHTOVER			_EC(142)	// ���Ȩ�޳���Ȩ���б���Χ
#define NET_GROUP_HAVEUSER			_EC(143)	// �������û�������ɾ��
#define NET_GROUP_RIGHTUSE			_EC(144)	// ���ĳ��Ȩ�ޱ��û�ʹ�ã����ܳ���
#define NET_GROUP_SAMENAME			_EC(145)	// ������ͬ���������ظ�
#define	NET_USER_EXIST				_EC(146)	// �û��Ѵ���
#define NET_USER_NOEXIST			_EC(147)	// �û�������
#define NET_USER_RIGHTOVER			_EC(148)	// �û�Ȩ�޳�����Ȩ��
#define NET_USER_PWD				_EC(149)	// �����ʺţ��������޸�����
#define NET_USER_FLASEPWD			_EC(150)	// ���벻��ȷ
#define NET_USER_NOMATCHING			_EC(151)	// ���벻ƥ��
#define NET_USER_INUSE				_EC(152)	// �˺�����ʹ����
#define NET_ERROR_GETCFG_ETHERNET	_EC(300)	// ��ȡ��������ʧ��
#define NET_ERROR_GETCFG_WLAN		_EC(301)	// ��ȡ����������Ϣʧ��
#define NET_ERROR_GETCFG_WLANDEV	_EC(302)	// ��ȡ���������豸ʧ��
#define NET_ERROR_GETCFG_REGISTER	_EC(303)	// ��ȡ����ע�����ʧ��
#define NET_ERROR_GETCFG_CAMERA		_EC(304)	// ��ȡ����ͷ����ʧ��
#define NET_ERROR_GETCFG_INFRARED	_EC(305)	// ��ȡ���ⱨ������ʧ��
#define NET_ERROR_GETCFG_SOUNDALARM	_EC(306)	// ��ȡ��Ƶ��������ʧ��
#define NET_ERROR_GETCFG_STORAGE    _EC(307)	// ��ȡ�洢λ������ʧ��
#define NET_ERROR_GETCFG_MAIL		_EC(308)	// ��ȡ�ʼ�����ʧ��
#define NET_CONFIG_DEVBUSY			_EC(309)	// ��ʱ�޷�����
#define NET_CONFIG_DATAILLEGAL		_EC(310)	// �������ݲ��Ϸ�
#define NET_ERROR_GETCFG_DST        _EC(311)    // ��ȡ����ʱ����ʧ��
#define NET_ERROR_SETCFG_DST        _EC(312)    // ��������ʱ����ʧ��
#define NET_ERROR_GETCFG_VIDEO_OSD  _EC(313)    // ��ȡ��ƵOSD��������ʧ��
#define NET_ERROR_SETCFG_VIDEO_OSD  _EC(314)    // ������ƵOSD��������ʧ��
#define NET_ERROR_GETCFG_GPRSCDMA   _EC(315)    // ��ȡCDMA\GPRS��������ʧ��
#define NET_ERROR_SETCFG_GPRSCDMA   _EC(316)    // ����CDMA\GPRS��������ʧ��
#define NET_ERROR_GETCFG_IPFILTER   _EC(317)    // ��ȡIP��������ʧ��
#define NET_ERROR_SETCFG_IPFILTER   _EC(318)    // ����IP��������ʧ��
#define NET_ERROR_GETCFG_TALKENCODE _EC(319)    // ��ȡ�����Խ���������ʧ��
#define NET_ERROR_SETCFG_TALKENCODE _EC(320)    // ���������Խ���������ʧ��
#define NET_ERROR_GETCFG_RECORDLEN  _EC(321)    // ��ȡ¼������������ʧ��
#define NET_ERROR_SETCFG_RECORDLEN  _EC(322)    // ����¼������������ʧ��
#define	NET_DONT_SUPPORT_SUBAREA	_EC(323)	// ��֧������Ӳ�̷���
#define	NET_ERROR_GET_AUTOREGSERVER	_EC(324)	// ��ȡ�豸������ע���������Ϣʧ��
#define	NET_ERROR_CONTROL_AUTOREGISTER		_EC(325)	// ����ע���ض���ע�����
#define	NET_ERROR_DISCONNECT_AUTOREGISTER	_EC(326)	// �Ͽ�����ע�����������
#define NET_ERROR_GETCFG_MMS				_EC(327)	// ��ȡmms����ʧ��
#define NET_ERROR_SETCFG_MMS				_EC(328)	// ����mms����ʧ��
#define NET_ERROR_GETCFG_SMSACTIVATION      _EC(329)	// ��ȡ���ż���������������ʧ��
#define NET_ERROR_SETCFG_SMSACTIVATION      _EC(330)	// ���ö��ż���������������ʧ��
#define NET_ERROR_GETCFG_DIALINACTIVATION	_EC(331)	// ��ȡ���ż���������������ʧ��
#define NET_ERROR_SETCFG_DIALINACTIVATION	_EC(332)	// ���ò��ż���������������ʧ��
#define NET_ERROR_GETCFG_VIDEOOUT           _EC(333)    // ��ѯ��Ƶ�����������ʧ��
#define NET_ERROR_SETCFG_VIDEOOUT			_EC(334)	// ������Ƶ�����������ʧ��
#define NET_ERROR_GETCFG_OSDENABLE			_EC(335)	// ��ȡosd����ʹ������ʧ��
#define NET_ERROR_SETCFG_OSDENABLE			_EC(336)	// ����osd����ʹ������ʧ��
#define NET_ERROR_SETCFG_ENCODERINFO        _EC(337)    // ��������ͨ��ǰ�˱����������ʧ��
#define NET_ERROR_GETCFG_TVADJUST		    _EC(338)	// ��ȡTV��������ʧ��
#define NET_ERROR_SETCFG_TVADJUST			_EC(339)	// ����TV��������ʧ��

#define NET_ERROR_CONNECT_FAILED			_EC(340)	// ����������ʧ��
#define NET_ERROR_SETCFG_BURNFILE			_EC(341)	// �����¼�ļ��ϴ�ʧ��
#define NET_ERROR_SNIFFER_GETCFG			_EC(342)	// ��ȡץ��������Ϣʧ��
#define NET_ERROR_SNIFFER_SETCFG			_EC(343)	// ����ץ��������Ϣʧ��
#define NET_ERROR_DOWNLOADRATE_GETCFG		_EC(344)	// ��ѯ����������Ϣʧ��
#define NET_ERROR_DOWNLOADRATE_SETCFG		_EC(345)	// ��������������Ϣʧ��
#define NET_ERROR_SEARCH_TRANSCOM			_EC(346)	// ��ѯ���ڲ���ʧ��
#define NET_ERROR_GETCFG_POINT				_EC(347)	// ��ȡԤ�Ƶ���Ϣ����
#define NET_ERROR_SETCFG_POINT				_EC(348)	// ����Ԥ�Ƶ���Ϣ����
#define NET_SDK_LOGOUT_ERROR				_EC(349)    // SDKû�������ǳ��豸
#define NET_ERROR_GET_VEHICLE_CFG			_EC(350)	// ��ȡ��������ʧ��
#define NET_ERROR_SET_VEHICLE_CFG			_EC(351)	// ���ó�������ʧ��
#define NET_ERROR_GET_ATM_OVERLAY_CFG		_EC(352)	// ��ȡatm��������ʧ��
#define NET_ERROR_SET_ATM_OVERLAY_CFG		_EC(353)	// ����atm��������ʧ��
#define NET_ERROR_GET_ATM_OVERLAY_ABILITY	_EC(354)	// ��ȡatm��������ʧ��
#define NET_ERROR_GET_DECODER_TOUR_CFG		_EC(355)	// ��ȡ������������Ѳ����ʧ��
#define NET_ERROR_SET_DECODER_TOUR_CFG		_EC(356)	// ���ý�����������Ѳ����ʧ��
#define NET_ERROR_CTRL_DECODER_TOUR			_EC(357)	// ���ƽ�����������Ѳʧ��
#define NET_GROUP_OVERSUPPORTNUM			_EC(358)	// �����豸֧������û�����Ŀ
#define NET_USER_OVERSUPPORTNUM				_EC(359)	// �����豸֧������û���Ŀ
#define NET_ERROR_GET_SIP_CFG				_EC(368)	// ��ȡSIP����ʧ��
#define NET_ERROR_SET_SIP_CFG				_EC(369)	// ����SIP����ʧ��
#define NET_ERROR_GET_SIP_ABILITY			_EC(370)	// ��ȡSIP����ʧ��
#define NET_ERROR_GET_WIFI_AP_CFG			_EC(371)	// ��ȡWIFI ap����ʧ��
#define NET_ERROR_SET_WIFI_AP_CFG			_EC(372)	// ����WIFI ap����ʧ��
#define NET_ERROR_GET_DECODE_POLICY		    _EC(373)	// ��ȡ�����������ʧ��
#define NET_ERROR_SET_DECODE_POLICY			_EC(374)	// ���ý����������ʧ��
#define NET_ERROR_TALK_REJECT				_EC(375)	// �ܾ��Խ�
#define NET_ERROR_TALK_OPENED				_EC(376)	// �Խ��������ͻ��˴�
#define NET_ERROR_TALK_RESOURCE_CONFLICIT   _EC(377)	// ��Դ��ͻ
#define NET_ERROR_TALK_UNSUPPORTED_ENCODE   _EC(378)	// ��֧�ֵ����������ʽ
#define NET_ERROR_TALK_RIGHTLESS			_EC(379)	// ��Ȩ��
#define NET_ERROR_TALK_FAILED				_EC(380)	// ����Խ�ʧ��
#define NET_ERROR_GET_MACHINE_CFG			_EC(381)	// ��ȡ�����������ʧ��
#define NET_ERROR_SET_MACHINE_CFG			_EC(382)	// ���û����������ʧ��
#define NET_ERROR_GET_DATA_FAILED			_EC(383)	// �豸�޷���ȡ��ǰ��������
#define NET_ERROR_MAC_VALIDATE_FAILED       _EC(384)    // MAC��ַ��֤ʧ�� 
#define NET_ERROR_GET_INSTANCE              _EC(385)    // ��ȡ������ʵ��ʧ��
#define NET_ERROR_JSON_REQUEST              _EC(386)    // ���ɵ�jason�ַ�������
#define NET_ERROR_JSON_RESPONSE             _EC(387)    // ��Ӧ��jason�ַ�������
#define NET_ERROR_VERSION_HIGHER            _EC(388)    // Э��汾���ڵ�ǰʹ�õİ汾
#define NET_SPARE_NO_CAPACITY				_EC(389)	// �ȱ�����ʧ��, ��������
#define NET_ERROR_SOURCE_IN_USE				_EC(390)	// ��ʾԴ���������ռ��
#define NET_ERROR_REAVE                     _EC(391)    // �߼��û���ռ�ͼ��û���Դ
#define NET_ERROR_NETFORBID                 _EC(392)    // ��ֹ���� 
#define NET_ERROR_GETCFG_MACFILTER			_EC(393)    // ��ȡMAC��������ʧ��
#define NET_ERROR_SETCFG_MACFILTER			_EC(394)    // ����MAC��������ʧ��
#define NET_ERROR_GETCFG_IPMACFILTER		_EC(395)    // ��ȡIP/MAC��������ʧ��
#define NET_ERROR_SETCFG_IPMACFILTER		_EC(396)    // ����IP/MAC��������ʧ��
#define NET_ERROR_OPERATION_OVERTIME        _EC(397)    // ��ǰ������ʱ 
#define NET_ERROR_SENIOR_VALIDATE_FAILED    _EC(398)    // �߼�У��ʧ�� 
 
#define NET_ERROR_DEVICE_ID_NOT_EXIST		_EC(399)	// �豸ID������
#define NET_ERROR_UNSUPPORTED               _EC(400)    // ��֧�ֵ�ǰ����

#define NET_ERROR_PROXY_DLLLOAD				_EC(401)	// ���������ʧ��
#define NET_ERROR_PROXY_ILLEGAL_PARAM		_EC(402)	// �����û��������Ϸ�
#define NET_ERROR_PROXY_INVALID_HANDLE		_EC(403)	// ���������Ч
#define NET_ERROR_PROXY_LOGIN_DEVICE_ERROR	_EC(404)	// ��������ǰ���豸ʧ��
#define NET_ERROR_PROXY_START_SERVER_ERROR	_EC(405)	// ������������ʧ��
#define NET_ERROR_SPEAK_FAILED				_EC(406)	// ���󺰻�ʧ��
#define NET_ERROR_NOT_SUPPORT_F6            _EC(407)    // �豸��֧�ִ�F6�ӿڵ���

/************************************************************************
 ** ö�ٶ���
 ***********************************************************************/
// �豸����
enum NET_DEVICE_TYPE 
{
	NET_PRODUCT_NONE = 0,
	NET_DVR_NONREALTIME_MACE,					// ��ʵʱMACE
	NET_DVR_NONREALTIME,						// ��ʵʱ
	NET_NVS_MPEG1,								// ������Ƶ������
	NET_DVR_MPEG1_2,							// MPEG1��·¼���
	NET_DVR_MPEG1_8,							// MPEG1��·¼���
	NET_DVR_MPEG4_8,							// MPEG4��·¼���
	NET_DVR_MPEG4_16,							// MPEG4ʮ��·¼���
	NET_DVR_MPEG4_SX2,							// LBϵ��¼���
	NET_DVR_MEPG4_ST2,							// GBϵ��¼���
	NET_DVR_MEPG4_SH2,							// HBϵ��¼���
	NET_DVR_MPEG4_GBE,							// GBEϵ��¼���
	NET_DVR_MPEG4_NVSII,						// II��������Ƶ������
	NET_DVR_STD_NEW,							// �±�׼����Э��
	NET_DVR_DDNS,								// DDNS������
	NET_DVR_ATM,								// ATM��
	NET_NB_SERIAL,								// ������ʵʱNBϵ�л���
	NET_LN_SERIAL,								// LNϵ�в�Ʒ
	NET_BAV_SERIAL,								// BAVϵ�в�Ʒ
	NET_SDIP_SERIAL,							// SDIPϵ�в�Ʒ
	NET_IPC_SERIAL,								// IPCϵ�в�Ʒ
	NET_NVS_B,									// NVS Bϵ��
	NET_NVS_C,									// NVS Hϵ��
	NET_NVS_S,									// NVS Sϵ��
	NET_NVS_E,									// NVS Eϵ��
	NET_DVR_NEW_PROTOCOL,						// ��QueryDevState�в�ѯ�豸����,���ַ�����ʽ
	NET_NVD_SERIAL,								// ������
	NET_DVR_N5,									// N5
	NET_DVR_MIX_DVR,							// ���DVR
	NET_SVR_SERIAL,								// SVRϵ��
	NET_SVR_BS,									// SVR-BS
	NET_NVR_SERIAL,								// NVRϵ��
	NET_DVR_N51,                                // N51
	NET_ITSE_SERIAL,							// ITSE ���ܷ�����
    NET_ITC_SERIAL,                             // ���ܽ�ͨ����豸
	NET_HWS_SERIAL,                             // �״������HWS
	NET_PVR_SERIAL,                             // ��Яʽ����Ƶ¼���
	NET_IVS_SERIAL,                             // IVS��������Ƶ������ϵ�У�
	NET_IVS_B,                                  // ͨ��������Ƶ��������
	NET_IVS_F,                                  // ����ʶ�������
	NET_IVS_V,                                  // ��Ƶ������Ϸ�����
	NET_MATRIX_SERIAL,							// ����
	NET_DVR_N52,								// N52
	NET_DVR_N56,								// N56
	NET_ESS_SERIAL,                             // ESS
	NET_IVS_PC,                                 // ����ͳ�Ʒ�����
	NET_PC_NVR,                                 // pc-nvr
	NET_DSCON,									// ����������
	NET_EVS,									// ������Ƶ�洢������
	NET_EIVS,									// Ƕ��ʽ���ܷ�����Ƶϵͳ
};

// ��������
typedef enum __LANGUAGE_TYPE
{
	DH_LANGUAGE_ENGLISH,						// Ӣ��	
	DH_LANGUAGE_CHINESE_SIMPLIFIED,				// ��������	
	DH_LANGUAGE_CHINESE_TRADITIONAL,			// ��������	
	DH_LANGUAGE_ITALIAN,						// �������	
	DH_LANGUAGE_SPANISH,						// ��������
	DH_LANGUAGE_JAPANESE,						// ���İ�	
	DH_LANGUAGE_RUSSIAN,						// ���İ�		
	DH_LANGUAGE_FRENCH,							// ���İ�		
	DH_LANGUAGE_GERMAN, 						// ���İ�		
	DH_LANGUAGE_PORTUGUESE,						// ��������	
	DH_LANGUAGE_TURKEY,							// ��������	
	DH_LANGUAGE_POLISH,							// ������	
	DH_LANGUAGE_ROMANIAN,						// ��������	
	DH_LANGUAGE_HUNGARIAN,						// ��������	
	DH_LANGUAGE_FINNISH,						// ������	
	DH_LANGUAGE_ESTONIAN,						// ��ɳ������	
	DH_LANGUAGE_KOREAN,							// ����	
	DH_LANGUAGE_FARSI,							// ��˹�� 	
	DH_LANGUAGE_DANSK,							// ������
	DH_LANGUAGE_CZECHISH,						// �ݿ���
	DH_LANGUAGE_BULGARIA,						// ����������
	DH_LANGUAGE_SLOVAKIAN,						// ˹�工����
	DH_LANGUAGE_SLOVENIA,						// ˹����������
	DH_LANGUAGE_CROATIAN,						// ���޵�����
	DH_LANGUAGE_DUTCH,							// ������
	DH_LANGUAGE_GREEK,							// ϣ����
	DH_LANGUAGE_UKRAINIAN,						// �ڿ�����
	DH_LANGUAGE_SWEDISH,						// �����
	DH_LANGUAGE_SERBIAN,						// ����ά����
	DH_LANGUAGE_VIETNAMESE,						// Խ����
	DH_LANGUAGE_LITHUANIAN,						// ��������
	DH_LANGUAGE_FILIPINO,						// ���ɱ���
	DH_LANGUAGE_ARABIC,							// ��������
	DH_LANGUAGE_CATALAN,						// ��̩��������
	DH_LANGUAGE_LATVIAN,						// ����ά����
	DH_LANGUAGE_THAI,							// ̩��
	DH_LANGUAGE_HEBREW,							// ϣ������
	DH_LANGUAGE_Bosnian,						// ��˹������
} DH_LANGUAGE_TYPE;

// ��������
typedef enum __EM_UPGRADE_TYPE
{
	DH_UPGRADE_BIOS_TYPE = 1,					// BIOS����
	DH_UPGRADE_WEB_TYPE,						// WEB����
	DH_UPGRADE_BOOT_YPE,						// BOOT����
	DH_UPGRADE_CHARACTER_TYPE,					// ���ֿ�
	DH_UPGRADE_LOGO_TYPE,						// LOGO
	DH_UPGRADE_EXE_TYPE,						// EXE�����粥������
} EM_UPGRADE_TYPE;

// ¼������(��ʱ����̬��⡢����)
typedef enum __REC_TYPE
{
	DH_REC_TYPE_TIM = 0,
	DH_REC_TYPE_MTD,
	DH_REC_TYPE_ALM,
	DH_REC_TYPE_NUM,
} REC_TYPE;

// �������� 
typedef enum __GPRSCDMA_NETWORK_TYPE
{
	DH_TYPE_AUTOSEL = 0,						// �Զ�ѡ��
	DH_TYPE_TD_SCDMA,							// TD-SCDMA���� 
	DH_TYPE_WCDMA,								// WCDMA����
	DH_TYPE_CDMA_1x,							// CDMA 1.x����
	DH_TYPE_EDGE,								// GPRS����
	DH_TYPE_EVDO,								// EVDO����
	DH_TYPE_WIFI,								// ����
} EM_GPRSCDMA_NETWORK_TYPE;

// �ӿ����ͣ���ӦCLIENT_SetSubconnCallBack�ӿ�
typedef enum __EM_INTERFACE_TYPE
{
	DH_INTERFACE_OTHER = 0x00000000,			// δ֪�ӿ�
	DH_INTERFACE_REALPLAY,						// ʵʱ���ӽӿ�
	DH_INTERFACE_PREVIEW,						// �໭��Ԥ���ӿ�
	DH_INTERFACE_PLAYBACK,						// �طŽӿ�
	DH_INTERFACE_DOWNLOAD,						// ���ؽӿ�
	DH_INTERFACE_REALLOADPIC,                   // ��������ͼƬ�ӿ�
} EM_INTERFACE_TYPE;

// ��Ƶ���ӶϿ��¼�����
typedef enum _EM_REALPLAY_DISCONNECT_EVENT_TYPE
{
	DISCONNECT_EVENT_REAVE,                     // ��ʾ�߼��û���ռ�ͼ��û���Դ
	DISCONNECT_EVENT_NETFORBID,                 // ��ֹ����
	DISCONNECT_EVENT_SUBCONNECT,                // ��̬�����ӶϿ�
}EM_REALPLAY_DISCONNECT_EVENT_TYPE;

// �¼��ļ����ļ���ǩ����
typedef enum __EM_EVENT_FILETAG
{
	DH_ATMBEFOREPASTE = 1,                      // ATM����ǰ
	DH_ATMAFTERPASTE,                           // ATM������
}EM_EVENT_FILETAG;

// IPC����
typedef enum __EM_IPC_TYPE
{
	DH_IPC_PRIVATE,                                 // ��
	DH_IPC_AEBELL,                                  // ���籴��
	DH_IPC_PANASONIC,                               // ����
	DH_IPC_SONY,                                    // ����
	DH_IPC_DYNACOLOR,                               // Dynacolor
	DH_IPC_TCWS = 5,                                // �������
	DH_IPC_SAMSUNG,                                 // ����
	DH_IPC_YOKO,                                    // YOKO
	DH_IPC_AXIS,                                    // ��Ѷ��
	DH_IPC_SANYO,									// ����       
	DH_IPC_BOSH = 10,								// Bosch
	DH_IPC_PECLO,									// Peclo
	DH_IPC_PROVIDEO,								// Provideo
	DH_IPC_ACTI,									// ACTi
	DH_IPC_VIVOTEK,									// Vivotek
	DH_IPC_ARECONT = 15,                            // Arecont
	DH_IPC_PRIVATEEH,			                    // PrivateEH	
	DH_IPC_IMATEK,					                // IMatek
	DH_IPC_SHANY,                                   // Shany
	DH_IPC_VIDEOTREC,                               // ����ӯ��
	DH_IPC_URA = 20,                                // Ura
	DH_IPC_BITICINO,                                // Bticino 
	DH_IPC_ONVIF,                                   // OnvifЭ������
	DH_IPC_SHEPHERD,                                // �Ӱ�
	DH_IPC_YAAN,                                    // �ǰ�
	DH_IPC_AIRPOINT = 25,                           // Airpop
	DH_IPC_TYCO,                                    // TYCO
	DH_IPC_XUNMEI,                                  // Ѷ��
	DH_IPC_HIKVISION,                               // ����
	DH_IPC_LG,                                      // LG
	DH_IPC_AOQIMAN = 30,                            // ������
	DH_IPC_BAOKANG,                                 // ����    
	DH_IPC_WATCHNET,                                // Watchnet
	DH_IPC_XVISION,                                 // Xvision
	DH_IPC_FUSITSU,                                 // ��ʿͨ
	DH_IPC_CANON = 35,								// Canon
	DH_IPC_GE,										// GE
	DH_IPC_Basler,									// ��˹��
	DH_IPC_Patro,							        // ������
	DH_IPC_CPKNC,									// CPPLUS Kϵ��
	DH_IPC_CPRNC = 40,								// CPPLUS Rϵ��
	DH_IPC_CPUNC,									// CPPLUS Uϵ��
	DH_IPC_CPPLUS,									// cpplus oem �󻪵�ipc
	DH_IPC_XunmeiS,									// Ѷ��s,ʵ��Э��ΪOnvif
	DH_IPC_GDDW,									// �㶫����
	DH_IPC_PSIA = 45,                               // PSIA
	DH_IPC_GB2818,                                  // GB2818	
	DH_IPC_GDYX,                                    // GDYX
	DH_IPC_OTHER,                                   // ���û��Զ���
	DH_IPC_CPUNR,									// CPPLUS OEM DAHUA NVR
	DH_IPC_CPUAR = 50,								// CPPLUS OEM DAHUA  DVR
	DH_IPC_AIRLIVE,                                 // Airlive	
	DH_IPC_HYUNDAI = 56,							// HYUNDAI OEM DAHUA DVR
	DH_IPC_NPE,										// NPE	
	DH_IPC_AXVIEW,									// AXVIEW
}EM_IPC_TYPE;

// H264 ���뼶��
typedef enum __EM_H264_PROFILE_RANK
{
	DH_PROFILE_BASELINE = 1,                       // �ṩI/P֡����֧��progressive(����ɨ��)��CAVLC
	DH_PROFILE_MAIN,                               // �ṩI/P/B֡��֧��progressiv��interlaced���ṩCAVLC��CABAC
	DH_PROFILE_EXTENDED,                           // �ṩI/P/B/SP/SI֡����֧��progressive(����ɨ��)��CAVLC
	DH_PROFILE_HIGH,                               // ��FRExt��Main_Profile������������8x8 intra prediction(8x8 ֡��Ԥ��), custom 
		                                           // quant(�Զ�������), lossless video coding(������Ƶ����), �����yuv��ʽ
}EM_H264_PROFILE_RANK;

typedef enum __EM_DISK_TYPE
{
    DH_DISK_READ_WRITE,                         // ��д������
	DH_DISK_READ_ONLY,                          // ֻ��������
	DH_DISK_BACKUP,	                            // ������������ý��������
	DH_DISK_REDUNDANT,                          // ����������
	DH_DISK_SNAPSHOT,	                        // ����������
}EM_DISK_TYPE;

// ���������㷨����ģʽ
typedef enum  __EM_ENCRYPT_ALOG_WORKMODE
{
	ENCRYPT_ALOG_WORKMODE_ECB,     // ECBģʽ
	ENCRYPT_ALOG_WORKMODE_CBC,     // CBCģʽ
	ENCRYPT_ALOG_WORKMODE_CFB,     // CFBģʽ
	ENCRYPT_ALOG_WORKMODE_OFB,     // OFBģʽ
}EM_ENCRYPT_ALOG_WORKMODE;

typedef enum __EM_MOBILE_PPP_STATE
{
	MOBILE_PPP_UP = 0,         // �����Ѿ�����
	MOBILE_PPP_DOWN,           // ppp���ӶϿ�		
	MOBILE_PPP_CONNECTING,     // ���ڴ�������		
	MOBILE_PPP_CLOSEING,       // ���ڹر�PPP����
} EM_MOBILE_PPP_STATE;

typedef enum __EM_3GMOBILE_STATE
{
    MOBILE_MODULE_OFF,          // ��ʾ3g����ģ��ر�   		
	MOBILE_MODULE_STARTING,     // ��ʾ3g����ģ����������	
	MOBILE_MODULE_WORKING,      // ��ʾ3g����ģ�����ڹ�����
}EM_3GMOBILE_STATE;

/////////////////////////////////�������/////////////////////////////////

// Ԥ�����ͣ���ӦCLIENT_RealPlayEx�ӿ�
typedef enum _RealPlayType
{
	DH_RType_Realplay = 0,						// ʵʱԤ��
	DH_RType_Multiplay,							// �໭��Ԥ��
		
	DH_RType_Realplay_0,						// ʵʱ����-����������ͬ��DH_RType_Realplay
	DH_RType_Realplay_1,						// ʵʱ����-������1
	DH_RType_Realplay_2,						// ʵʱ����-������2
	DH_RType_Realplay_3,						// ʵʱ����-������3
		
	DH_RType_Multiplay_1,						// �໭��Ԥ����1����
	DH_RType_Multiplay_4,						// �໭��Ԥ����4����
	DH_RType_Multiplay_8,						// �໭��Ԥ����8����
	DH_RType_Multiplay_9,						// �໭��Ԥ����9����
	DH_RType_Multiplay_16,						// �໭��Ԥ����16����
	DH_RType_Multiplay_6,						// �໭��Ԥ����6����
	DH_RType_Multiplay_12,						// �໭��Ԥ����12����
} DH_RealPlayType;

/////////////////////////////////��̨���/////////////////////////////////

// ͨ����̨��������
typedef enum _PTZ_ControlType
{
	DH_PTZ_UP_CONTROL = 0,						// ��
	DH_PTZ_DOWN_CONTROL,						// ��
	DH_PTZ_LEFT_CONTROL,						// ��
	DH_PTZ_RIGHT_CONTROL,						// ��
	DH_PTZ_ZOOM_ADD_CONTROL,					// �䱶+
	DH_PTZ_ZOOM_DEC_CONTROL,					// �䱶-
	DH_PTZ_FOCUS_ADD_CONTROL,					// ����+
	DH_PTZ_FOCUS_DEC_CONTROL,					// ����-
	DH_PTZ_APERTURE_ADD_CONTROL,				// ��Ȧ+
	DH_PTZ_APERTURE_DEC_CONTROL,				// ��Ȧ-
    DH_PTZ_POINT_MOVE_CONTROL,					// ת��Ԥ�õ�
    DH_PTZ_POINT_SET_CONTROL,					// ����
    DH_PTZ_POINT_DEL_CONTROL,					// ɾ��
    DH_PTZ_POINT_LOOP_CONTROL,					// ���Ѳ��
    DH_PTZ_LAMP_CONTROL							// �ƹ���ˢ
} DH_PTZ_ControlType;

// ��̨������չ����
typedef enum _EXTPTZ_ControlType
{
	DH_EXTPTZ_LEFTTOP = 0x20,					// ����
	DH_EXTPTZ_RIGHTTOP,							// ����
	DH_EXTPTZ_LEFTDOWN,							// ����
	DH_EXTPTZ_RIGHTDOWN,						// ����
	DH_EXTPTZ_ADDTOLOOP,						// ����Ԥ�õ㵽Ѳ�� Ѳ����· Ԥ�õ�ֵ
	DH_EXTPTZ_DELFROMLOOP,						// ɾ��Ѳ����Ԥ�õ� Ѳ����· Ԥ�õ�ֵ
    DH_EXTPTZ_CLOSELOOP,						// ���Ѳ�� Ѳ����·
	DH_EXTPTZ_STARTPANCRUISE,					// ��ʼˮƽ��ת
	DH_EXTPTZ_STOPPANCRUISE,					// ֹͣˮƽ��ת
	DH_EXTPTZ_SETLEFTBORDER,					// ������߽�
	DH_EXTPTZ_SETRIGHTBORDER,					// �����ұ߽�
	DH_EXTPTZ_STARTLINESCAN,					// ��ʼ��ɨ
    DH_EXTPTZ_CLOSELINESCAN,					// ֹͣ��ɨ
    DH_EXTPTZ_SETMODESTART,						// ����ģʽ��ʼ	ģʽ��·
    DH_EXTPTZ_SETMODESTOP,						// ����ģʽ����	ģʽ��·
	DH_EXTPTZ_RUNMODE,							// ����ģʽ	ģʽ��·
	DH_EXTPTZ_STOPMODE,							// ֹͣģʽ	ģʽ��·
	DH_EXTPTZ_DELETEMODE,						// ���ģʽ	ģʽ��·
	DH_EXTPTZ_REVERSECOMM,						// ��ת����
	DH_EXTPTZ_FASTGOTO,							// ���ٶ�λ ˮƽ����(8192) ��ֱ����(8192) �䱶(4)
	DH_EXTPTZ_AUXIOPEN,							// �������ؿ� ������
	DH_EXTPTZ_AUXICLOSE,						// �������ع� ������
	DH_EXTPTZ_OPENMENU = 0x36,					// ������˵�
	DH_EXTPTZ_CLOSEMENU,						// �رղ˵�
	DH_EXTPTZ_MENUOK,							// �˵�ȷ��
	DH_EXTPTZ_MENUCANCEL,						// �˵�ȡ��
	DH_EXTPTZ_MENUUP,							// �˵���
	DH_EXTPTZ_MENUDOWN,							// �˵���
	DH_EXTPTZ_MENULEFT,							// �˵���
	DH_EXTPTZ_MENURIGHT,						// �˵���
	DH_EXTPTZ_ALARMHANDLE = 0x40,				// ����������̨ parm1����������ͨ����parm2��������������1-Ԥ�õ�2-��ɨ3-Ѳ����parm3������ֵ����Ԥ�õ��
	DH_EXTPTZ_MATRIXSWITCH = 0x41,				// �����л� parm1����������(��Ƶ�����)��parm2����Ƶ����ţ�parm3�������
	DH_EXTPTZ_LIGHTCONTROL,						// �ƹ������
	DH_EXTPTZ_EXACTGOTO,						// ��ά��ȷ��λ parm1��ˮƽ�Ƕ�(0~3600)��parm2����ֱ����(0~900)��parm3���䱶(1~128)
	DH_EXTPTZ_RESETZERO,                        // ��ά��λ������λ
	DH_EXTPTZ_UP_TELE = 0x70,					// �� + TELE param1=�ٶ�(1-8)����ͬ
	DH_EXTPTZ_DOWN_TELE,						// �� + TELE
	DH_EXTPTZ_LEFT_TELE,						// �� + TELE
	DH_EXTPTZ_RIGHT_TELE,						// �� + TELE
	DH_EXTPTZ_LEFTUP_TELE,						// ���� + TELE
	DH_EXTPTZ_LEFTDOWN_TELE,					// ���� + TELE
	DH_EXTPTZ_TIGHTUP_TELE,						// ���� + TELE
	DH_EXTPTZ_RIGHTDOWN_TELE,					// ���� + TELE
	DH_EXTPTZ_UP_WIDE,							// �� + WIDE param1=�ٶ�(1-8)����ͬ
	DH_EXTPTZ_DOWN_WIDE,						// �� + WIDE
	DH_EXTPTZ_LEFT_WIDE,						// �� + WIDE
	DH_EXTPTZ_RIGHT_WIDE,						// �� + WIDE
	DH_EXTPTZ_LEFTUP_WIDE,						// ���� + WIDE
	DH_EXTPTZ_LEFTDOWN_WIDE,					// ���� + WIDE
	DH_EXTPTZ_TIGHTUP_WIDE,						// ���� + WIDE
	DH_EXTPTZ_RIGHTDOWN_WIDE,					// ���� + WIDE
	DH_EXTPTZ_TOTAL,							// �������ֵ
} DH_EXTPTZ_ControlType;

/////////////////////////////////��־���/////////////////////////////////

// ��־��ѯ����
typedef enum _DH_LOG_QUERY_TYPE
{
	DHLOG_ALL = 0,								// ������־
	DHLOG_SYSTEM,								// ϵͳ��־
	DHLOG_CONFIG,								// ������־
	DHLOG_STORAGE,								// �洢���
	DHLOG_ALARM,								// ������־
	DHLOG_RECORD,								// ¼�����
	DHLOG_ACCOUNT,								// �ʺ����
	DHLOG_CLEAR,								// �����־
	DHLOG_PLAYBACK,								// �ط����
	DHLOG_MANAGER                               // ǰ�˹����������
} DH_LOG_QUERY_TYPE;

// ��־����
typedef enum _DH_LOG_TYPE
{
	DH_LOG_REBOOT = 0x0000,						// �豸����
	DH_LOG_SHUT,								// �豸�ػ�
	DH_LOG_UPGRADE = 0x0004,					// �豸����
	DH_LOG_SYSTIME_UPDATE = 0x0005,             // ϵͳʱ�����
	DH_LOG_GPS_TIME_UPDATE = 0x0006,			// GPSʱ�����
	DH_LOG_CONFSAVE = 0x0100,					// ��������
	DH_LOG_CONFLOAD,							// ��ȡ����
	DH_LOG_FSERROR = 0x0200,					// �ļ�ϵͳ����
	DH_LOG_HDD_WERR,							// Ӳ��д����
	DH_LOG_HDD_RERR,							// Ӳ�̶�����
	DH_LOG_HDD_TYPE,							// ����Ӳ������
	DH_LOG_HDD_FORMAT,							// ��ʽ��Ӳ��
	DH_LOG_HDD_NOSPACE,							// ��ǰ�����̿ռ䲻��
	DH_LOG_HDD_TYPE_RW,							// ����Ӳ������Ϊ��д��
	DH_LOG_HDD_TYPE_RO,							// ����Ӳ������Ϊֻ����	
	DH_LOG_HDD_TYPE_RE,							// ����Ӳ������Ϊ������
	DH_LOG_HDD_TYPE_SS,							// ����Ӳ������Ϊ������
	DH_LOG_HDD_NONE,							// ��Ӳ�̼�¼
	DH_LOG_HDD_NOWORKHDD,						// �޹�����(û�ж�д��)
	DH_LOG_HDD_TYPE_BK,							// ����Ӳ������Ϊ������
	DH_LOG_HDD_TYPE_REVERSE,					// ����Ӳ������Ϊ��������
	DH_LOG_HDD_START_INFO = 0x200 +14,          // ��¼����ʱ��Ӳ����Ϣ
	DH_LOG_HDD_WORKING_DISK,                    // ��¼���̺�Ĺ����̺�
	DH_LOG_HDD_OTHER_ERROR,                     // ��¼Ӳ����������
	DH_LOG_HDD_SLIGHT_ERR,						// Ӳ�̴�����΢����
	DH_LOG_HDD_SERIOUS_ERR,                     // Ӳ�̴�����������
	DH_LOG_HDD_NOSPACE_END,                     // ��ǰ�����̿ռ䲻�㱨������
	DH_LOG_HDD_TYPE_RAID_CONTROL,               // Raid����
	DH_LOG_ALM_IN = 0x0300,						// �ⲿ���뱨����ʼ
	DH_LOG_NETALM_IN,							// ���籨������
	DH_LOG_ALM_END = 0x0302,					// �ⲿ���뱨��ֹͣ
	DH_LOG_LOSS_IN,								// ��Ƶ��ʧ������ʼ
	DH_LOG_LOSS_END,							// ��Ƶ��ʧ��������
	DH_LOG_MOTION_IN,							// ��̬��ⱨ����ʼ
	DH_LOG_MOTION_END,							// ��̬��ⱨ������
	DH_LOG_ALM_BOSHI,							// ��������������
	DH_LOG_NET_ABORT = 0x0308,					// ����Ͽ�
	DH_LOG_NET_ABORT_RESUME,					// ����ָ�
	DH_LOG_CODER_BREAKDOWN,						// ����������
	DH_LOG_CODER_BREAKDOWN_RESUME,				// ���������ϻָ�
	DH_LOG_BLIND_IN,							// ��Ƶ�ڵ�
	DH_LOG_BLIND_END,							// ��Ƶ�ڵ��ָ�
	DH_LOG_ALM_TEMP_HIGH,						// �¶ȹ���
	DH_LOG_ALM_VOLTAGE_LOW,						// ��ѹ����
	DH_LOG_ALM_BATTERY_LOW,						// �����������
	DH_LOG_ALM_ACC_BREAK,						// ACC�ϵ�
	DH_LOG_GPS_SIGNAL_LOST,						// GPS���ź�
	DH_LOG_GPS_SIGNAL_RESUME,					// GPS�źŻָ�
	DH_LOG_3G_SIGNAL_LOST,						// 3G���ź�
	DH_LOG_3G_SIGNAL_RESUME,					// 3G�źŻָ�
	DH_LOG_INFRAREDALM_IN = 0x03a0,				// ���߱�����ʼ
	DH_LOG_INFRAREDALM_END,						// ���߱�������
	DH_LOG_IPCONFLICT,							// IP��ͻ
	DH_LOG_IPCONFLICT_RESUME,					// IP�ָ�
	DH_LOG_SDPLUG_IN,							// SD������(DH_LOG_ITEM�е�reservedֵΪ3��ʾU�̲���)
	DH_LOG_SDPLUG_OUT,							// SD���γ�(DH_LOG_ITEM�е�reservedֵΪ3��ʾU�̰γ�)
	DH_LOG_NET_PORT_BIND_FAILED,				// ����˿ڰ�ʧ��
	DH_LOG_HDD_BEEP_RESET,                      // Ӳ�̴��󱨾���������
	DH_LOG_MAC_CONFLICT,                        // MAC��ͻ
	DH_LOG_MAC_CONFLICT_RESUME,                 // MAC��ͻ�ָ�
	DH_LOG_ALARM_OUT,							// �������״̬
	DH_LOG_ALM_RAID_STAT_EVENT,                 // RAID״̬�仯�¼� 
	DH_LOG_ABLAZE_ON,				            // �𾯱������̸л��¶�
	DH_LOG_ABLAZE_OFF,			                // �𾯱��� �ָ�
	DH_LOG_INTELLI_ALARM_PLUSE,					// ���������ͱ���
	DH_LOG_INTELLI_ALARM_IN,					// ���ܱ�����ʼ
	DH_LOG_INTELLI_ALARM_END,					// ���ܱ�������
	DH_LOG_3G_SIGNAL_SCAN,						// 3G�źż��
	DH_LOG_GPS_SIGNAL_SCAN,						// GPS�źż��
	DH_LOG_AUTOMATIC_RECORD = 0x0400,	 		// �Զ�¼��
	DH_LOG_MANUAL_RECORD = 0x0401,				// �ֶ�¼��
	DH_LOG_CLOSED_RECORD,						// ֹͣ¼��
	DH_LOG_LOGIN = 0x0500,						// ��¼
	DH_LOG_LOGOUT,								// ע��
	DH_LOG_ADD_USER,							// �����û�
	DH_LOG_DELETE_USER,							// ɾ���û�
	DH_LOG_MODIFY_USER,							// �޸��û�
	DH_LOG_ADD_GROUP,							// �����û���
	DH_LOG_DELETE_GROUP,						// ɾ���û���
	DH_LOG_MODIFY_GROUP,						// �޸��û���
	DH_LOG_NET_LOGIN = 0x0508,					// �����û���¼
	DH_LOG_MODIFY_PASSWORD,						// �޸�����
	DH_LOG_CLEAR = 0x0600,						// �����־
	DH_LOG_SEARCHLOG,							// ��ѯ��־
	DH_LOG_SEARCH = 0x0700,						// ¼���ѯ
	DH_LOG_DOWNLOAD,							// ¼������
	DH_LOG_PLAYBACK,							// ¼��ط�
	DH_LOG_BACKUP,								// ����¼���ļ�
	DH_LOG_BACKUPERROR,							// ����¼���ļ�ʧ��
	DH_LOG_TIME_UPDATE  = 0x0800,               // ʱ��ͬ��

	DH_LOG_TYPE_NR = 8,
} DH_LOG_TYPE;

// ��չ��־���ͣ���ӦCLIENT_QueryLogEx�ӿڣ�����(int nType = 1������reserved = &nType)
typedef enum _DH_NEWLOG_TYPE
{
	DH_NEWLOG_REBOOT = 0x0000,					// �豸����
	DH_NEWLOG_SHUT,								// �豸�ػ�
	DH_NEWLOG_UPGRADE = 0x0004,					// �豸����
	DH_NEWLOG_SYSTIME_UPDATE = 0x0005,          // ϵͳʱ�����
	DH_NEWLOG_GPS_TIME_UPDATE = 0x0006,			// GPSʱ�����
	DH_NEWLOG_CONFSAVE = 0x0100,				// ��������
	DH_NEWLOG_CONFLOAD,							// ��ȡ����
	DH_NEWLOG_FSERROR = 0x0200,					// �ļ�ϵͳ����
	DH_NEWLOG_HDD_WERR,							// Ӳ��д����
	DH_NEWLOG_HDD_RERR,							// Ӳ�̶�����
	DH_NEWLOG_HDD_TYPE,							// ����Ӳ������
	DH_NEWLOG_HDD_FORMAT,						// ��ʽ��Ӳ��
	DH_NEWLOG_HDD_NOSPACE,						// ��ǰ�����̿ռ䲻��
	DH_NEWLOG_HDD_TYPE_RW,						// ����Ӳ������Ϊ��д��
	DH_NEWLOG_HDD_TYPE_RO,						// ����Ӳ������Ϊֻ����	
	DH_NEWLOG_HDD_TYPE_RE,						// ����Ӳ������Ϊ������
	DH_NEWLOG_HDD_TYPE_SS,						// ����Ӳ������Ϊ������
	DH_NEWLOG_HDD_NONE,							// ��Ӳ�̼�¼��־
	DH_NEWLOG_HDD_NOWORKHDD,					// �޹�����(û�ж�д��)
	DH_NEWLOG_HDD_TYPE_BK,						// ����Ӳ������Ϊ������
	DH_NEWLOG_HDD_TYPE_REVERSE,					// ����Ӳ������Ϊ��������
	DH_NEWLOG_HDD_START_INFO = 0x200 +14,       // ��¼����ʱ��Ӳ����Ϣ
	DH_NEWLOG_HDD_WORKING_DISK,                 // ��¼���̺�Ĺ����̺�
	DH_NEWLOG_HDD_OTHER_ERROR,                  // ��¼Ӳ����������
	DH_NEWLOG_HDD_SLIGHT_ERR,				    // Ӳ�̴�����΢����
	DH_NEWLOG_HDD_SERIOUS_ERR,                  // Ӳ�̴�����������
	DH_NEWLOG_HDD_NOSPACE_END,                  // ��ǰ�����̿ռ䲻�㱨������
	DH_NEWLOG_ALM_IN = 0x0300,					// �ⲿ���뱨����ʼ
	DH_NEWLOG_NETALM_IN,						// ���籨��
	DH_NEWLOG_ALM_END = 0x0302,					// �ⲿ���뱨��ֹͣ
	DH_NEWLOG_LOSS_IN,							// ��Ƶ��ʧ������ʼ
	DH_NEWLOG_LOSS_END,							// ��Ƶ��ʧ��������
	DH_NEWLOG_MOTION_IN,						// ��̬��ⱨ����ʼ
	DH_NEWLOG_MOTION_END,						// ��̬��ⱨ������
	DH_NEWLOG_ALM_BOSHI,						// ��������������
	DH_NEWLOG_NET_ABORT = 0x0308,				// ����Ͽ�
	DH_NEWLOG_NET_ABORT_RESUME,					// ����ָ�
	DH_NEWLOG_CODER_BREAKDOWN,					// ����������
	DH_NEWLOG_CODER_BREAKDOWN_RESUME,			// ���������ϻָ�
	DH_NEWLOG_BLIND_IN,							// ��Ƶ�ڵ�
	DH_NEWLOG_BLIND_END,						// ��Ƶ�ڵ��ָ�
	DH_NEWLOG_ALM_TEMP_HIGH,					// �¶ȹ���
	DH_NEWLOG_ALM_VOLTAGE_LOW,					// ��ѹ����
	DH_NEWLOG_ALM_BATTERY_LOW,					// �����������
	DH_NEWLOG_ALM_ACC_BREAK,					// ACC�ϵ�
	DH_NEWLOG_GPS_SIGNAL_LOST,					// GPS���ź�
	DH_NEWLOG_GPS_SIGNAL_RESUME,				// GPS�źŻָ�
	DH_NEWLOG_3G_SIGNAL_LOST,					// 3G���ź�
	DH_NEWLOG_3G_SIGNAL_RESUME,					// 3G�źŻָ�
	DH_NEWLOG_INFRAREDALM_IN = 0x03a0,			// ���߱�����ʼ
	DH_NEWLOG_INFRAREDALM_END,					// ���߱�������
	DH_NEWLOG_IPCONFLICT,						// IP��ͻ
	DH_NEWLOG_IPCONFLICT_RESUME,				// IP�ָ�
	DH_NEWLOG_SDPLUG_IN,						// SD������
	DH_NEWLOG_SDPLUG_OUT,						// SD���γ�
	DH_NEWLOG_NET_PORT_BIND_FAILED,				// ����˿ڰ�ʧ��
	DH_NEWLOG_HDD_BEEP_RESET,                   // Ӳ�̴��󱨾���������
	DH_NEWLOG_MAC_CONFLICT,                     // MAC��ͻ
	DH_NEWLOG_MAC_CONFLICT_RESUME,              // MAC��ͻ�ָ�
	DH_NEWLOG_ALARM_OUT,						// �������״̬
	DH_NEWLOG_ALM_RAID_STAT_EVENT,              // RAID״̬�仯�¼� 
	DH_NEWLOG_ABLAZE_ON,				        // �𾯱������̸л��¶�
	DH_NEWLOG_ABLAZE_OFF,			            // �𾯱��� �ָ�
	DH_NEWLOG_INTELLI_ALARM_PLUSE,				// ���������ͱ���
	DH_NEWLOG_INTELLI_ALARM_IN,					// ���ܱ�����ʼ
	DH_NEWLOG_INTELLI_ALARM_END,				// ���ܱ�������
	DH_NEWLOG_3G_SIGNAL_SCAN,					// 3G�źż��
	DH_NEWLOG_GPS_SIGNAL_SCAN,					// GPS�źż��
	DH_NEWLOG_AUTOMATIC_RECORD = 0x0400,		// �Զ�¼��
	DH_NEWLOG_MANUAL_RECORD,					// �ֶ�¼��
	DH_NEWLOG_CLOSED_RECORD,					// ֹͣ¼��
	DH_NEWLOG_LOGIN = 0x0500,					// ��¼
	DH_NEWLOG_LOGOUT,							// ע��
	DH_NEWLOG_ADD_USER,							// �����û�
	DH_NEWLOG_DELETE_USER,						// ɾ���û�
	DH_NEWLOG_MODIFY_USER,						// �޸��û�
	DH_NEWLOG_ADD_GROUP,						// �����û���
	DH_NEWLOG_DELETE_GROUP,						// ɾ���û���
	DH_NEWLOG_MODIFY_GROUP,						// �޸��û���
	DH_NEWLOG_NET_LOGIN = 0x0508,				// �����û���¼
	DH_NEWLOG_CLEAR = 0x0600,					// �����־
	DH_NEWLOG_SEARCHLOG,						// ��ѯ��־
	DH_NEWLOG_SEARCH = 0x0700,					// ¼���ѯ
	DH_NEWLOG_DOWNLOAD,							// ¼������
	DH_NEWLOG_PLAYBACK,							// ¼��ط�
	DH_NEWLOG_BACKUP,							// ����¼���ļ�
	DH_NEWLOG_BACKUPERROR,						// ����¼���ļ�ʧ��
	DH_NEWLOG_TIME_UPDATE  = 0x0800,            // ʱ�����

	DH_NEWLOG_TYPE_NR = 8,		
} DH_NEWLOG_TYPE;

///////////////////////////////�����Խ����///////////////////////////////

// ������������
typedef enum __TALK_CODING_TYPE
{
	DH_TALK_DEFAULT = 0,						// ��ͷPCM
	DH_TALK_PCM = 1,							// ��ͷPCM
	DH_TALK_G711a,								// G711a
	DH_TALK_AMR,								// AMR
	DH_TALK_G711u,								// G711u
	DH_TALK_G726,								// G726
	DH_TALK_G723_53,							// G723_53
	DH_TALK_G723_63,							// G723_63
	DH_TALK_AAC,								// AAC
} DH_TALK_CODING_TYPE;

// �Խ���ʽ
typedef enum __EM_USEDEV_MODE
{
	DH_TALK_CLIENT_MODE,						// ���ÿͻ��˷�ʽ���������Խ�
	DH_TALK_SERVER_MODE,						// ���÷�������ʽ���������Խ�
	DH_TALK_ENCODE_TYPE,						// ���������Խ������ʽ
	DH_ALARM_LISTEN_MODE,						// ���ñ������ķ�ʽ
	DH_CONFIG_AUTHORITY_MODE,					// ����ͨ��Ȩ�޽������ù���
	DH_TALK_TALK_CHANNEL,						// ���öԽ�ͨ��(0~MaxChannel-1)
	DH_RECORD_STREAM_TYPE,                      // ���ô���ѯ����ʱ��طŵ�¼����������(0-��������,1-������,2-������)  
	DH_TALK_SPEAK_PARAM,                        // ���������Խ�������������Ӧ�ṹ�� NET_SPEAK_PARAM
} EM_USEDEV_MODE;

// AMR��������
typedef enum __EM_ARM_ENCODE_MODE
{
	DH_TALK_AMR_AMR475 = 1,						// AMR475����
	DH_TALK_AMR_AMR515,							// AMR515����
	DH_TALK_AMR_AMR59,							// AMR59����
	DH_TALK_AMR_AMR67,							// AMR67����
	DH_TALK_AMR_AMR74,							// AMR74����
	DH_TALK_AMR_AMR795,							// AMR795����
	DH_TALK_AMR_AMR102,							// AMR102����
	DH_TALK_AMR_AMR122,							// AMR122����
} EM_ARM_ENCODE_MODE;

typedef struct __NET_SPEAK_PARAM
{
	DWORD           dwSize;                     // �ṹ���С
	int             nMode;                      // 0���Խ���Ĭ��ģʽ����1���������Ӻ����л����Խ�Ҫ��������
	int             nSpeakerChannel;            // ������ͨ���ţ�����ʱ��Ч
} NET_SPEAK_PARAM;

/////////////////////////////////�������/////////////////////////////////

// �������ͣ���ӦCLIENT_ControlDevice�ӿ�
typedef enum _CtrlType
{
	DH_CTRL_REBOOT = 0,							// �����豸	
	DH_CTRL_SHUTDOWN,							// �ر��豸
	DH_CTRL_DISK,								// Ӳ�̹���
	DH_KEYBOARD_POWER = 3,						// �������
	DH_KEYBOARD_ENTER,
	DH_KEYBOARD_ESC,
	DH_KEYBOARD_UP,
	DH_KEYBOARD_DOWN,
	DH_KEYBOARD_LEFT,
	DH_KEYBOARD_RIGHT,
	DH_KEYBOARD_BTN0,
	DH_KEYBOARD_BTN1,
	DH_KEYBOARD_BTN2,
	DH_KEYBOARD_BTN3,
	DH_KEYBOARD_BTN4,
	DH_KEYBOARD_BTN5,
	DH_KEYBOARD_BTN6,
	DH_KEYBOARD_BTN7,
	DH_KEYBOARD_BTN8,
	DH_KEYBOARD_BTN9,
	DH_KEYBOARD_BTN10,
	DH_KEYBOARD_BTN11,
	DH_KEYBOARD_BTN12,
	DH_KEYBOARD_BTN13,
	DH_KEYBOARD_BTN14,
	DH_KEYBOARD_BTN15,
	DH_KEYBOARD_BTN16,
	DH_KEYBOARD_SPLIT,
	DH_KEYBOARD_ONE,
	DH_KEYBOARD_NINE,
	DH_KEYBOARD_ADDR,
	DH_KEYBOARD_INFO,
	DH_KEYBOARD_REC,
	DH_KEYBOARD_FN1,
	DH_KEYBOARD_FN2,
	DH_KEYBOARD_PLAY,
	DH_KEYBOARD_STOP,
	DH_KEYBOARD_SLOW,
	DH_KEYBOARD_FAST,
	DH_KEYBOARD_PREW,
	DH_KEYBOARD_NEXT,
	DH_KEYBOARD_JMPDOWN,
	DH_KEYBOARD_JMPUP,
	DH_TRIGGER_ALARM_IN = 100,					// ������������
	DH_TRIGGER_ALARM_OUT,						// �����������
	DH_CTRL_MATRIX,								// �������
	DH_CTRL_SDCARD,								// SD������(IPC��Ʒ)����ͬӲ�̿���
	DH_BURNING_START,							// ��¼�����ƣ���ʼ��¼
	DH_BURNING_STOP,							// ��¼�����ƣ�������¼
	DH_BURNING_ADDPWD,							// ��¼�����ƣ���������(��'\0'Ϊ��β���ַ�������󳤶�8λ)
	DH_BURNING_ADDHEAD,							// ��¼�����ƣ�����Ƭͷ(��'\0'Ϊ��β���ַ�������󳤶�1024�ֽڣ�֧�ַ��У��зָ���'\n')
	DH_BURNING_ADDSIGN,							// ��¼�����ƣ����Ӵ�㵽��¼��Ϣ(������)
	DH_BURNING_ADDCURSTOMINFO,					// ��¼�����ƣ��Զ������(��'\0'Ϊ��β���ַ�������󳤶�1024�ֽڣ�֧�ַ��У��зָ���'\n')
	DH_CTRL_RESTOREDEFAULT,						// �ָ��豸��Ĭ������
	DH_CTRL_CAPTURE_START,						// �����豸ץͼ
	DH_CTRL_CLEARLOG,							// �����־
	DH_TRIGGER_ALARM_WIRELESS = 200,			// �������߱���(IPC��Ʒ)
	DH_MARK_IMPORTANT_RECORD,					// ��ʶ��Ҫ¼���ļ�
	DH_CTRL_DISK_SUBAREA, 						// ����Ӳ�̷���	
	DH_BURNING_ATTACH,							// ��¼�����ƣ�������¼.
	DH_BURNING_PAUSE,							// ��¼��ͣ
	DH_BURNING_CONTINUE,						// ��¼����
	DH_BURNING_POSTPONE,						// ��¼˳��
	DH_CTRL_OEMCTRL,							// ��ͣ����
	DH_BACKUP_START,							// �豸���ݿ�ʼ
	DH_BACKUP_STOP,								// �豸����ֹͣ
	DH_VIHICLE_WIFI_ADD,						// �����ֶ�����WIFI����
	DH_VIHICLE_WIFI_DEC,						// �����ֶ�ɾ��WIFI����
	DH_BUZZER_START,                            // ���������ƿ�ʼ
	DH_BUZZER_STOP,                             // ���������ƽ���
	DH_REJECT_USER,                             // �޳��û�
	DH_SHIELD_USER,                             // �����û�
	DH_RAINBRUSH,                               // ���ܽ�ͨ, ��ˢ���� 
	DH_MANUAL_SNAP,                             // ���ܽ�ͨ, �ֶ�ץ�� (��Ӧ�ṹ��MANUAL_SNAP_PARAMETER)
	DH_MANUAL_NTP_TIMEADJUST,                   // �ֶ�NTPУʱ
	DH_NAVIGATION_SMS,                          // ������Ϣ�Ͷ���Ϣ
	DH_CTRL_ROUTE_CROSSING,                     // ·�ߵ�λ��Ϣ
	DH_BACKUP_FORMAT,							// ��ʽ�������豸
	DH_DEVICE_LOCALPREVIEW_SLIPT,               // �����豸�˱���Ԥ���ָ�(��Ӧ�ṹ��DEVICE_LOCALPREVIEW_SLIPT_PARAMETER)    
	DH_CTRL_INIT_RAID,							// RAID��ʼ��
	DH_CTRL_RAID,								// RAID����
	DH_CTRL_SAPREDISK,							// �ȱ��̲���
	DH_WIFI_CONNECT,							// �ֶ�����WIFI����(��Ӧ�ṹ��WIFI_CONNECT)
	DH_WIFI_DISCONNECT,							// �ֶ��Ͽ�WIFI����(��Ӧ�ṹ��WIFI_CONNECT)
	DH_CTRL_ARMED,                              // ����������
	DH_CTRL_IP_MODIFY,                          // �޸�ǰ��IP(��Ӧ�ṹ��DHCTRL_IPMODIFY_PARAM)                     
	DH_CTRL_WIFI_BY_WPS,                        // wps����wifi(��Ӧ�ṹ��DHCTRL_CONNECT_WIFI_BYWPS)
	DH_CTRL_FORMAT_PATITION,					// ��ʽ������(��Ӧ�ṹ��DH_FORMAT_PATITION)
	DH_CTRL_EJECT_STORAGE,						// �ֶ�ж���豸(��Ӧ�ṹ��DH_EJECT_STORAGE_DEVICE)
	DH_CTRL_LOAD_STORAGE,						// �ֶ�װ���豸(��Ӧ�ṹ��DH_LOAD_STORAGE_DEVICE)
	DH_CTRL_CLOSE_BURNER,                       // �رտ�¼��������(��Ӧ�ṹ�� NET_CTRL_BURNERDOOR) һ����Ҫ��6��
	DH_CTRL_EJECT_BURNER,                       // ������¼��������(��Ӧ�ṹ�� NET_CTRL_BURNERDOOR) һ����Ҫ��4��
} CtrlType;

// IO���������ӦCLIENT_QueryIOControlState�ӿ�
typedef enum _IOTYPE
{
	DH_ALARMINPUT = 1,							// ���Ʊ�������
	DH_ALARMOUTPUT = 2,							// ���Ʊ������
	DH_DECODER_ALARMOUT = 3,					// ���Ʊ������������
	DH_WIRELESS_ALARMOUT = 5,					// �������߱������
	DH_ALARM_TRIGGER_MODE = 7,					// ����������ʽ���ֶ�,�Զ�,�رգ���ʹ��TRIGGER_MODE_CONTROL�ṹ��
} DH_IOTYPE;

/////////////////////////////////�������/////////////////////////////////

// �ֱ���ö�٣���DH_DSP_ENCODECAPʹ��
typedef enum _CAPTURE_SIZE
{
	CAPTURE_SIZE_D1,							// 704*576(PAL)  704*480(NTSC)
	CAPTURE_SIZE_HD1,							// 352*576(PAL)  352*480(NTSC)
	CAPTURE_SIZE_BCIF,							// 704*288(PAL)  704*240(NTSC)
	CAPTURE_SIZE_CIF,							// 352*288(PAL)  352*240(NTSC)
	CAPTURE_SIZE_QCIF,							// 176*144(PAL)  176*120(NTSC)
	CAPTURE_SIZE_VGA,							// 640*480
	CAPTURE_SIZE_QVGA,							// 320*240
	CAPTURE_SIZE_SVCD,							// 480*480
	CAPTURE_SIZE_QQVGA,							// 160*128
	CAPTURE_SIZE_SVGA,							// 800*592
	CAPTURE_SIZE_XVGA,							// 1024*768
	CAPTURE_SIZE_WXGA,							// 1280*800
	CAPTURE_SIZE_SXGA,							// 1280*1024  
	CAPTURE_SIZE_WSXGA,							// 1600*1024  
	CAPTURE_SIZE_UXGA,							// 1600*1200
	CAPTURE_SIZE_WUXGA,							// 1920*1200
	CAPTURE_SIZE_LTF,							// 240*192
	CAPTURE_SIZE_720,							// 1280*720
	CAPTURE_SIZE_1080,							// 1920*1080
	CAPTURE_SIZE_1_3M,							// 1280*960
	CAPTURE_SIZE_2M,							// 1872*1408
	CAPTURE_SIZE_5M,							// 3744*1408
	CAPTURE_SIZE_3M,							// 2048*1536
	CAPTURE_SIZE_5_0M,                          // 2432*2050
	CPTRUTE_SIZE_1_2M,							// 1216*1024
	CPTRUTE_SIZE_1408_1024,                     // 1408*1024
	CPTRUTE_SIZE_8M,                            // 3296*2472
	CPTRUTE_SIZE_2560_1920,                     // 2560*1920(5M)
	CAPTURE_SIZE_960H,                          // 960*576(PAL) 960*480(NTSC)
	CAPTURE_SIZE_960_720,                       // 960*720
	CAPTURE_SIZE_NHD,							// 640*360
	CAPTURE_SIZE_QNHD,							// 320*180
	CAPTURE_SIZE_QQNHD,							// 160*90
	CAPTURE_SIZE_NR=255  
} CAPTURE_SIZE;

// �����ļ����ͣ���CLIENT_ExportConfigFile�ӿ�ʹ��
typedef enum __DH_CONFIG_FILE_TYPE
{
	DH_CONFIGFILE_ALL = 0,						// ȫ�������ļ�
	DH_CONFIGFILE_LOCAL,						// ���������ļ�
	DH_CONFIGFILE_NETWORK,						// ���������ļ�
	DH_CONFIGFILE_USER,							// �û������ļ�
} DH_CONFIG_FILE_TYPE;

// NTP
typedef enum __DH_TIME_ZONE_TYPE
{
	DH_TIME_ZONE_0,								// {0, 0*3600,"GMT+00:00"}
	DH_TIME_ZONE_1,								// {1, 1*3600,"GMT+01:00"}
	DH_TIME_ZONE_2,								// {2, 2*3600,"GMT+02:00"}
	DH_TIME_ZONE_3,								// {3, 3*3600,"GMT+03:00"}
	DH_TIME_ZONE_4,								// {4, 3*3600+1800,"GMT+03:30"}
	DH_TIME_ZONE_5,								// {5, 4*3600,"GMT+04:00"}
	DH_TIME_ZONE_6,								// {6, 4*3600+1800,"GMT+04:30"}
	DH_TIME_ZONE_7,								// {7, 5*3600,"GMT+05:00"}
	DH_TIME_ZONE_8,								// {8, 5*3600+1800,"GMT+05:30"}
	DH_TIME_ZONE_9,								// {9, 5*3600+1800+900,"GMT+05:45"}
	DH_TIME_ZONE_10,							// {10, 6*3600,"GMT+06:00"}
	DH_TIME_ZONE_11,							// {11, 6*3600+1800,"GMT+06:30"}
	DH_TIME_ZONE_12,							// {12, 7*3600,"GMT+07:00"}
	DH_TIME_ZONE_13,							// {13, 8*3600,"GMT+08:00"}
	DH_TIME_ZONE_14,							// {14, 9*3600,"GMT+09:00"}
	DH_TIME_ZONE_15,							// {15, 9*3600+1800,"GMT+09:30"}
	DH_TIME_ZONE_16,							// {16, 10*3600,"GMT+10:00"}
	DH_TIME_ZONE_17,							// {17, 11*3600,"GMT+11:00"}
	DH_TIME_ZONE_18,							// {18, 12*3600,"GMT+12:00"}
	DH_TIME_ZONE_19,							// {19, 13*3600,"GMT+13:00"}
	DH_TIME_ZONE_20,							// {20, -1*3600,"GMT-01:00"}
	DH_TIME_ZONE_21,							// {21, -2*3600,"GMT-02:00"}
	DH_TIME_ZONE_22,							// {22, -3*3600,"GMT-03:00"}
	DH_TIME_ZONE_23,							// {23, -3*3600-1800,"GMT-03:30"}
	DH_TIME_ZONE_24,							// {24, -4*3600,"GMT-04:00"}
	DH_TIME_ZONE_25,							// {25, -5*3600,"GMT-05:00"}
	DH_TIME_ZONE_26,							// {26, -6*3600,"GMT-06:00"}
	DH_TIME_ZONE_27,							// {27, -7*3600,"GMT-07:00"}
	DH_TIME_ZONE_28,							// {28, -8*3600,"GMT-08:00"}
	DH_TIME_ZONE_29,							// {29, -9*3600,"GMT-09:00"}
	DH_TIME_ZONE_30,							// {30, -10*3600,"GMT-10:00"}
	DH_TIME_ZONE_31,							// {31, -11*3600,"GMT-11:00"}
	DH_TIME_ZONE_32,							// {32, -12*3600,"GMT-12:00"}
} DH_TIME_ZONE_TYPE;

typedef enum _SNAP_TYPE
{
	SNAP_TYP_TIMING = 0,
	SNAP_TYP_ALARM,
	SNAP_TYP_NUM,
} SNAP_TYPE;

typedef enum _CONNECT_STATE
{
	CONNECT_STATE_UNCONNECT  = 0,
	CONNECT_STATE_CONNECTING,
	CONNECT_STATE_CONNECTED,
	CONNECT_STATE_ERROR = 255,
} CONNECT_STATE;

// ץ��ģʽ
typedef enum tagDH_TRAFFIC_SNAP_MODE
{	
	DH_TRAFFIC_SNAP_MODE_COIL = 1,				       // ��Ȧץ��
	DH_TRAFFIC_SNAP_MODE_COIL_PICANALYSIS,		       // ��Ȧץ��, ͼƬ����
	DH_TRAFFIC_SNAP_MODE_STREAM,				       // ��Ƶץ��
	DH_TRAFFIC_SNAP_MODE_STREAM_IDENTIFY,		       // ��Ƶץ��, ����ʶ��
} DH_TRAFFIC_SNAP_MODE;

// ��λ������
typedef enum 
{
	NET_CARPORTLIGHT_TYPE_RED,                           // ���
	NET_CARPORTLIGHT_TYPE_GREEN,                         // �̵�
}NET_CARPORTLIGHT_TYPE;

// ��λ�����Ʒ�ʽ
typedef enum
{
	NET_CARPORTLIGHT_MODE_OFF,                           // �� 
	NET_CARPORTLIGHT_MODE_ON,                            // ��
	NET_CARPORTLIGHT_MODE_GLINT,                         // ��˸
}NET_CARPORTLIGHT_MODE;
/////////////////////////////////��̭����/////////////////////////////////

// �������ͣ�Ŀǰʹ�ø�ö�ٵĽӿ�����̭���벻Ҫʹ��
typedef enum _CFG_INDEX
{
    CFG_GENERAL = 0,							// ��ͨ
	CFG_COMM,									// ����
	CFG_NET,									// ����
	CFG_RECORD,									// ¼��
	CFG_CAPTURE,								// ͼ������
	CFG_PTZ,									// ��̨
	CFG_DETECT,									// ��̬���
	CFG_ALARM,									// ����
	CFG_DISPLAY,								// ��ʾ
	CFG_RESERVED,								// ������ʹ��������
	CFG_TITLE = 10,								// ͨ������
	CFG_MAIL = 11,								// �ʼ�����
	CFG_EXCAPTURE = 12,							// Ԥ��ͼ������
	CFG_PPPOE = 13,								// pppoe����
	CFG_DDNS = 14,								// DDNS����
	CFG_SNIFFER	= 15,							// ������Ӳ�������
	CFG_DSPINFO	= 16,							// ����������Ϣ
	CFG_COLOR = 126,							// ��ɫ������Ϣ
	CFG_ALL,									// ����
} CFG_INDEX;

/************************************************************************
 ** �ṹ�嶨��
 ***********************************************************************/
//��ʾ���������ԭ��ʾ���ڵ�����
typedef struct
{
    double				dleft;					//��ʾ���������ԭ��ʾ���ڵ������� 
	double				dright;					//��ʾ���������ԭ��ʾ���ڵ�������
	double				dtop;					//��ʾ���������ԭ��ʾ���ڵ�������
	double				dbottom;				//��ʾ���������ԭ��ʾ���ڵ�������
} DH_DISPLAYRREGION;
// ʱ��
typedef struct 
{
	DWORD				dwYear;					// ��
	DWORD				dwMonth;				// ��
	DWORD				dwDay;					// ��
	DWORD				dwHour;					// ʱ
	DWORD				dwMinute;				// ��
	DWORD				dwSecond;				// ��
} NET_TIME,*LPNET_TIME;

typedef struct 
{
	DWORD				dwYear;					// ��
	DWORD				dwMonth;				// ��
	DWORD				dwDay;					// ��
	DWORD				dwHour;					// ʱ
	DWORD				dwMinute;				// ��
	DWORD				dwSecond;				// ��
	DWORD               dwMillisecond;          // ����
	DWORD               dwReserved[2];          // �����ֶ�
} NET_TIME_EX,*LPNET_TIME_EX;

// ��־��Ϣ���ʱ�䶨��
typedef struct _DHDEVTIME
{
	DWORD				second		:6;			// ��	1-60		
	DWORD				minute		:6;			// ��	1-60		
	DWORD				hour		:5;			// ʱ	1-24		
	DWORD				day			:5;			// ��	1-31		
	DWORD				month		:4;			// ��	1-12		
	DWORD				year		:6;			// ��	2000-2063	
} DHDEVTIME, *LPDHDEVTIME;

// �ص�����(�첽�ӿ�)
typedef struct __NET_CALLBACK_DATA 
{
	int					nResultCode;			// �����룻0���ɹ�
	char				*pBuf;					// �������ݣ����������û����ٵģ��ӽӿ��βδ���
	int					nRetLen;				// ���ճ���
	LLONG				lOperateHandle;			// �������
	void*				userdata;				// ������Ӧ�û�����
	char				reserved[16];
} NET_CALLBACK_DATA, *LPNET_CALLBACK_DATA;

///////////////////////////////������ض���///////////////////////////////

// �ص���Ƶ����֡��֡�����ṹ��
typedef struct _tagVideoFrameParam
{
	BYTE				encode;					// ��������
	BYTE				frametype;				// I = 0, P = 1, B = 2...
	BYTE				format;					// PAL - 0, NTSC - 1
	BYTE				size;					// CIF - 0, HD1 - 1, 2CIF - 2, D1 - 3, VGA - 4, QCIF - 5, QVGA - 6 ,
												// SVCD - 7,QQVGA - 8, SVGA - 9, XVGA - 10,WXGA - 11,SXGA - 12,WSXGA - 13,UXGA - 14,WUXGA - 15, LFT - 16, 720 - 17, 1080 - 18
	DWORD				fourcc;					// �����H264��������Ϊ0��MPEG4����������дFOURCC('X','V','I','D');
	DWORD				reserved;				// ����
	NET_TIME			struTime;				// ʱ����Ϣ
} tagVideoFrameParam;

// �ص���Ƶ����֡��֡�����ṹ��
typedef struct _tagCBPCMDataParam
{
	BYTE				channels;				// ������
	BYTE				samples;				// ���� 0 - 8000, 1 - 11025, 2 - 16000, 3 - 22050, 4 - 32000, 5 - 44100, 6 - 48000
	BYTE				depth;					// ������� ȡֵ8����16�ȡ�ֱ�ӱ�ʾ
	BYTE				param1;					// 0 - ָʾ�޷��ţ�1-ָʾ�з���
	DWORD				reserved;				// ����
} tagCBPCMDataParam;

// ͨ��������Ļ���ӵ����ݽṹ
typedef struct _DH_CHANNEL_OSDSTRING
{
	BOOL				bEnable;				// ʹ��
	DWORD				dwPosition[MAX_STRING_LINE_LEN];	//�����ַ���λ�á���1-9������ʾ����С����λ�ö�Ӧ
												//		7����	8��		9����
												//		4��		5��		6��
												//		1����	2��		3����
	char				szStrings[MAX_STRING_LINE_LEN][MAX_PER_STRING_LEN];	// ��������ַ���ÿ�����20���ֽ�
} DH_CHANNEL_OSDSTRING;

//�ص�YUV���ݵĲ����ṹ��
typedef struct _tagCBYUVDataParam
{
	long				nWidth;                 // ͼ��Ŀ�
	long				nHeight;				// ͼ��ĸ�
	DWORD				reserved[8];			// ����
} tagCBYUVDataParam;

///////////////////////////////�ط���ض���///////////////////////////////

// ¼���ļ���Ϣ
typedef struct
{
    unsigned int		ch;						// ͨ����
    char				filename[128];			// �ļ���
    unsigned int		size;					// �ļ�����
    NET_TIME			starttime;				// ��ʼʱ��
    NET_TIME			endtime;				// ����ʱ��
    unsigned int		driveno;				// ���̺�(��������¼��ͱ���¼������ͣ�0��127��ʾ����¼��,����64��ʾ����1��128��ʾ����¼��)
    unsigned int		startcluster;			// ��ʼ�غ�
	BYTE				nRecordFileType;		// ¼���ļ�����  0����ͨ¼��1������¼��2���ƶ���⣻3������¼��4��ͼƬ
	BYTE                bImportantRecID;		// 0:��ͨ¼�� 1:��Ҫ¼��
	BYTE                bHint;					// �ļ���λ����
	BYTE                bRecType;               // 0-������¼�� 1-����1��¼�� 2-������2 3-������3¼��
} NET_RECORDFILE_INFO, *LPNET_RECORDFILE_INFO;

// Ũ��¼���ļ���Ϣ
typedef struct tagNET_SynopsisFileInfo
{
	DWORD				dwSize;					// �ýṹ���С
    char				szFileName[MAX_PATH];	// �ļ���������C:\a.dav
    NET_TIME			stuStartTime;			// ��ʼʱ��
    NET_TIME			stuEndTime;				// ����ʱ��
	unsigned int		nTaskID;				// �ڷ�������ı�ʾ�����ļ���2ѡ1ʹ��
	BYTE				bFileType;				// 1-��ƵŨ��¼���ļ���2-��ƵŨ��Դ�ļ�
	BYTE				bReserved[3];
	unsigned int		nFileLength;			// �ļ���С����λ:�ֽ�
}NET_SYNOPSISFILE_INFO, *LPNET_SYNOPSISFILE_INFO;

// ĳ�µĸ����Ƿ����¼���״̬��Ϣ
typedef struct
{
	BYTE 	    flag[32];      //ĳ���ڵĸ����Ƿ����¼���״̬���룬0��ʾû�У�1��ʾ�С�
	BYTE		Reserved[64];  //����
}NET_RECORD_STATUS, *LPNET_RECORD_STATUS;

typedef struct
{
	unsigned short      left;                        // 0~8192
    unsigned short      right;                       // 0~8192
    unsigned short      top;                         // 0~8192
    unsigned short      bottom;                      // 0~8192
} MotionDetectRect;

// ���ܻط���Ϣ
typedef struct 
{
	MotionDetectRect    motion_rect;               // ����֡��������
    NET_TIME            stime;                     // �طŵĿ�ʼʱ��
    NET_TIME            etime;                     // �طŵĽ���ʱ��
	BYTE                bStart;                    // ��ʼֹͣ����: 1,��ʼ,2:ֹͣ
    BYTE                reserved[116];
} IntelligentSearchPlay, *LPIntelligentSearchPlay;

// ����¼��ʱ��
typedef struct  
{
	int					nChnCount;				// ͨ����Ŀ
	NET_TIME			stuFurthestTime[16];	// ����¼��ʱ��,��ЧֵΪǰ��0 �� (nChnCount-1)��.���ĳͨ��û��¼��Ļ�������¼��ʱ��ȫΪ0
	DWORD				dwFurthestTimeAllSize;	// ��ͨ����������16ʱ��ʹ�á���ʾ����pStuFurthestTimeAll����ڴ��С��
	NET_TIME*			pStuFurthestTimeAll;	// ��ͨ����������16ʱ��ʹ�á��˲����ڴ���Ҫ�û�����,�����СΪ(ͨ������*sizeof(NET_TIME))��
	BYTE				bReserved[376];			// �����ֶ�
} NET_FURTHEST_RECORD_TIME;

///////////////////////////////������ض���///////////////////////////////

// ��ͨ������Ϣ
typedef struct
{
	int					channelcount;
	int					alarminputcount;
	unsigned char		alarm[16];				// �ⲿ����
	unsigned char		motiondection[16];		// ��̬���
	unsigned char		videolost[16];			// ��Ƶ��ʧ
} NET_CLIENT_STATE;

// ��ͨ������Ϣ
typedef struct
{
	int					channelcount;
	int					alarminputcount;
	unsigned char		alarm[32];				// �ⲿ����
	unsigned char		motiondection[32];		// ��̬���
	unsigned char		videolost[32];			// ��Ƶ��ʧ
	BYTE                bReserved[32];
} NET_CLIENT_STATE_EX;

// �ⲿ����״̬��Ϣ��Ӧ�ṹ��
typedef struct
{
	DWORD              dwSize;
	int				   alarminputcount;
	DWORD              dwAlarmState[DH_MAX_CHANMASK]; //ÿһ��DWORD��λ��ʾ32ͨ���ı���״̬, 0-��ʾ�ޱ���, 1-��ʾ�б���
}NET_CLIENT_ALARM_STATE;

// ��Ƶ��ʧ����״̬��Ϣ��Ӧ�ṹ��
typedef struct
{
	DWORD              dwSize;
	int				   channelcount;
	DWORD              dwAlarmState[DH_MAX_CHANMASK]; //ÿһ��DWORD��λ��ʾ32ͨ���ı���״̬, 0-��ʾ�ޱ���, 1-��ʾ�б���
}NET_CLIENT_VIDEOLOST_STATE;

// ��̬��ⱨ��״̬��Ϣ��Ӧ�ṹ��
typedef struct
{
	DWORD              dwSize;
	int				   channelcount;
	DWORD              dwAlarmState[DH_MAX_CHANMASK]; //ÿһ��DWORD��λ��ʾ32ͨ���ı���״̬, 0-��ʾ�ޱ���, 1-��ʾ�б���
}NET_CLIENT_MOTIONDETECT_STATE;

// ��Ƶ�ڵ�����״̬��Ϣ��Ӧ�ṹ��
typedef struct
{
	DWORD              dwSize;
	int				   channelcount;
	DWORD              dwAlarmState[DH_MAX_CHANMASK]; //ÿһ��DWORD��λ��ʾ32ͨ���ı���״̬, 0-��ʾ�ޱ���, 1-��ʾ�б���
}NET_CLIENT_VIDEOBLIND_STATE;

// ��ѯ ��̬��ⱨ��״̬��ϸ��Ϣ��Ӧ�ṹ��
typedef struct
{
	DWORD              dwSize;
	int                nChannelID;    // ͨ����
	BOOL               bAlarm;        // �Ƿ񱨾� TRUE/FALSE
	int                nLevel;        // �������𣬵�λǧ��֮���Զ��췢��С����������С��������
}NET_CLIENT_DETAILEDMOTION_STATE;

// ����IO����
typedef struct 
{
	unsigned short		index;					// �˿����
	unsigned short		state;					// �˿�״̬
} ALARM_CONTROL;

// ������ʽ
typedef struct
{
	unsigned short		index;					// �˿����
	unsigned short		mode;					// ������ʽ(0�ر�1�ֶ�2�Զ�);�����õ�ͨ����sdkĬ�Ͻ�����ԭ�������á�
	BYTE				bReserved[28];			
} TRIGGER_MODE_CONTROL;

// ��������������
typedef struct 
{
	int					decoderNo;				// �����������ţ���0��ʼ
	unsigned short		alarmChn;				// ��������ڣ���0��ʼ
	unsigned short		alarmState;				// �������״̬��1���򿪣�0���ر�
} DECODER_ALARM_CONTROL;

// �����ϴ����ܵı�����Ϣ
typedef struct  
{
	DWORD				dwAlarmType;			// �������ͣ�dwAlarmType = DH_UPLOAD_EVENTʱ��dwAlarmMask��bAlarmDecoderIndex����Ч��
	DWORD				dwAlarmMask;			// ������Ϣ���룬��λ��ʾ������ͨ��״̬
	char				szGlobalIP[DH_MAX_IPADDR_LEN];	// �ͻ���IP��ַ
	char				szDomainName[DH_MAX_DOMAIN_NAME_LEN];	// �ͻ�������
	int					nPort;					// �����ϴ�ʱ�ͻ������ӵĶ˿�
	char				szAlarmOccurTime[DH_ALARM_OCCUR_TIME_LEN];	// ����������ʱ��
	BYTE				bAlarmDecoderIndex;		// ��ʾ�ڼ���������������dwAlarmType = DH_UPLOAD_DECODER_ALARM ����Ч.
	BYTE				bReservedSpace[15];
} NEW_ALARM_UPLOAD;

// �����������ܱ����¼�
typedef struct __ALARM_UPLOAD_IVS_INFO
{
	DWORD				dwSize;
	NET_TIME			stuTime;                                  // �¼�����ʱ��	
	char				szDomainName[DH_MAX_DOMAIN_NAME_LEN];	  // �ͻ�������
	int					nChannelID;                               // ͨ���ţ���0��ʼ
	char				szType[MAX_PATH];                         // ��������, ������
	int					nState;                                   // ����״̬��0-������λ��1-������λ, 2-����ʽ����
} ALARM_UPLOAD_IVS_INFO;

// ¼��״̬�仯������Ϣ
typedef struct
{
	int					nChannel;				// ¼��ͨ����
	char				reserved[12];
} ALARM_RECORDING_CHANGED;

// ��Ȧ/����������
typedef struct __ALARM_WINGDING_INFO
{
	int                 nDriveWayID;            // ������
	int                 nWindingID;             // ��ȦID
	NET_TIME            stuTime;                // ��������ʱ��
	int                 nState;                 // �豸״̬��0��ʾ���ϻָ���1��ʾ��������
	DWORD				dwChannel;				// ������ͨ����
	char                reserve[28];
} ALARM_WINGDING_INFO;

// ��ͨӵ������
typedef struct __ALARM_TRAF_CONGESTION_INFO
{
	int                 nDriveWayID;            // ������
	int                 nCongestionLevel;       // ��ͨӵ���ȼ�:1,2,3,4,5,6;1��������
	NET_TIME            stuTime;                // ��������ʱ��
	int                 nState;                 // �豸״̬��0��ʾ���ϻָ���1��ʾ��������
	DWORD				dwChannel;				// ������ͨ����
	char                reserve[28];
} ALARM_TRAF_CONGESTION_INFO;

// ��ͨ�쳣����
typedef struct __ALARM_TRAF_EXCEPTION_INFO
{
	int                 nDriveWayID;            // ������
	NET_TIME            stuTime;                // ��������ʱ��
	int                 nState;                 // �豸״̬��0��ʾ���ϻָ���1��ʾ��������
	DWORD				dwChannel;				// ������ͨ����
	char                reserve[28];
} ALARM_TRAF_EXCEPTION_INFO;

// �����豸���ϱ���
typedef struct __ALARM_EQUIPMENT_FILL_INFO
{
	int                 nDriveWayID;            // ������
	NET_TIME            stuTime;                // ��������ʱ��
	int                 nState;                 // �豸״̬��0��ʾ���ϻָ���1��ʾ��������
	DWORD				dwChannel;				// ������ͨ����
	char                reserve[28];
} ALARM_EQUIPMENT_FILL_INFO;

// ����������״̬��Ϣ
typedef struct __ALARM_ARM_DISARM_STATE_INFO
{
	BYTE                bState;                 // ������״̬��0��ʾ������1��ʾ������2��ʾǿ�Ʋ���
	char                reserve[31];
} ALARM_ARM_DISARM_STATE_INFO;

// 3G����������ֵ״̬��Ϣ 
typedef struct __DHDEV_3GFLOW_EXCEED_STATE_INFO
{
	BYTE                bState;                 // 3G����������ֵ״̬��0��ʾδ������ֵ��1��ʾ������ֵ
	char                reserve[31];
} DHDEV_3GFLOW_EXCEED_STATE_INFO;

// ���ٱ�����·�����ٱ��� (DH_DEVSTATE_SPEED_LIMIT)
typedef struct __ALARM_SPEED_LIMIT
{
	char                szType[DH_SPEEDLIMIT_TYPE_LEN];     // ���ٱ������LowerSpeed, UpperSpeed
	int                 iSpeedLimit;            // ���� ��λKM/H 
	int                 iSpeed;                 // �ٶ� ��λKM/H
	char                szCrossingID[DH_MAX_CROSSING_ID];         // ·�����к�
	DWORD				dwLongitude;			// ����(��λ�ǰ����֮�ȣ���Χ0-360��)�綫��120.178274�ȱ�ʾΪ300178274
    DWORD				dwLatidude;				// γ��(��λ�ǰ����֮�ȣ���Χ0-180��)�籱γ30.183382�ȱ�ʾΪ120183382
	DHDEVTIME           stTime;                 // ��������ʱ��
	BYTE                bOffline;               // 0-ʵʱ 1-���� 
	char				reserve[19];
}ALARM_SPEED_LIMIT;
// ���ٱ���

// ���ر���
typedef struct __ALARM_OVER_LOADING
{
    NET_TIME        stuCurTime;             // ��ǰʱ��
    DWORD		    dwLatidude;				// γ��(��λ�ǰ����֮�ȣ���Χ0-180��)�籱γ30.183382�ȱ�ʾΪ120183382
    DWORD		    dwLongitude;			// ����(��λ�ǰ����֮�ȣ���Χ0-360��)�綫��120.178274�ȱ�ʾΪ300178274
    char            szDriverNo[DH_VEHICLE_DRIVERNO_LEN];    // ��ʻԱID
    DWORD           dwCurSpeed;             // ��ǰ�ٶ�
    BYTE          byReserved[128]; 
}ALARM_OVER_LOADING;

// ��ɲ������
typedef struct __ALARM_HARD_BRAKING
{
    NET_TIME        stuCurTime;             // ��ǰʱ��
    DWORD		    dwLatidude;				// γ��(��λ�ǰ����֮�ȣ���Χ0-180��)�籱γ30.183382�ȱ�ʾΪ120183382
    DWORD		    dwLongitude;			// ����(��λ�ǰ����֮�ȣ���Χ0-360��)�綫��120.178274�ȱ�ʾΪ300178274
    char            szDriverNo[DH_VEHICLE_DRIVERNO_LEN];    // ��ʻԱID
    DWORD           dwCurSpeed;             // ��ǰ�ٶ�
    BYTE            byReserved[128]; 
}ALARM_HARD_BRAKING;

// �̸б���
typedef struct __ALARM_SMOKE_SENSOR
{
	NET_TIME        stuCurTime;             // ��ǰʱ��
	int             nChannel;               // ����ͨ��
	BYTE            byHighTemperature;      // 1:���±�����ʼ��0�����±�������
	BYTE            bySmoke;                // 1:�̸б�����ʼ��0���̸б�������
	BYTE            byReservrd[126];
}ALARM_SMOKE_SENSOR;

// ��ͨ�ƹ��ϱ���
typedef struct _LIGHT_INFO
{
	BYTE               byDirection;            // ��ͨ�Ʒ���: 1-���У�2-���У�3-ֱ��, 4-��ͷ
	BYTE               byState;                // ��ͨ��״̬: 1-���ϣ�2-����
	BYTE               byReserved[62];         // �����ֽ� 
}LIGHT_INFO;

typedef struct __ALARM_TRAFFIC_LIGHT_FAULT 
{
	NET_TIME           stTime;                 // ��������ʱ��
	int                nInfoNumber;            // ������Ϣ��
	LIGHT_INFO         stLightInfo[8];         // ��ͨ�ƹ�����Ϣ
	BYTE               byReserved[128];        // �����ֶ�
}ALARM_TRAFFIC_LIGHT_FAULT;

// ����ͳ�Ʊ���ͨ����Ϣ
typedef struct __ALARM_TRAFFIC_FLUX_LANE_INFO
{
	NET_TIME            stuCurTime;            // ��ǰʱ��
	int                 nLane;                 // ������
	int                 nState;                // ״ֵ̬��1-��ʾӵ��, 2-��ʾӵ�»ָ�, 3-��ʾ����, 4-��ʾ�ж�, 5-��ʾ�жϻָ�
	int                 nFlow;                 // ����ֵ����λ����/��
	BYTE                byReserved[124];       // ����
}ALARM_TRAFFIC_FLUX_LANE_INFO;

// SIP״̬�ı䱨��()
typedef struct __ALARM_SIP_STATE
{
	int     nChannelID;
	BYTE    byStatus;                       //0:ע��ɹ�,1:δע��,2:��Ч,3:ע����,4:ͨ����
	BYTE	bReserved[63];			        //����
}ALARM_SIP_STATE;

// �����Զ�����Ϣ�ϴ�(DH_DEVSTATE_VIHICLE_INFO_UPLOAD)
typedef struct __ALARM_VEHICLE_INFO_UPLOAD
{
    char                szType[DH_VEHICLE_TYPE_LEN];                 // ��Ϣ���: DriverCheck��˾��ǩ��ǩ��
	char                szCheckInfo[DH_VEHICLE_INFO_LEN];            // ǩ�룺CheckIn��ǩ����CheckOut  
    char                szDirverNO[DH_VEHICLE_DRIVERNO_LEN];         // ˾�������ַ���
	DHDEVTIME           stTime;                                      // ��������ʱ��
	BYTE                bOffline;                                    // 0-ʵʱ 1-���� 
	char                reserved[59];                     
}ALARM_VEHICLE_INFO_UPLOAD;
// �����Զ�����Ϣ�ϴ�

// ����¼����Ϣ�ϴ�
typedef struct __ALARM_CARD_RECORD_INFO_UPLOAD
{
	int					nChannel;				// ͨ����
	BOOL				bEnable;				// �Ƿ����ڿ���¼��
	char				szCardInfo[DH_MAX_CARD_INFO_LEN];	// ������Ϣ
	NET_TIME			stuTime;				// �ÿ�����Ч��ʼʱ��
	BOOL                bPreviewOverlayEn;      // Ԥ������ʹ��
	BYTE                byOverlayPos;           // ����λ��,1-���ϣ�2-���£�3-���ϣ�4-����
	char				reserved[59];
}ALARM_CARD_RECORD_INFO_UPLOAD;



typedef enum __ATMTradeTypes{
	TRADE_TYPE_INC = 0,		//�忨INSERTCARD
	TRADE_TYPE_WDC,			//�˿�WITHDRAWCARD
	TRADE_TYPE_CKT,			//УʱCHECKTIME
	TRADE_TYPE_INQ,			//��ѯ
	TRADE_TYPE_CWD,			//ȡ��
	TRADE_TYPE_PIN,			//����
	TRADE_TYPE_TFR,			//ת��
	TRADE_TYPE_DEP,			//���
	TRADE_TYPE_NCINQ,		//�޿���ѯ
	TRADE_TYPE_NCDEP,		//�޿����
	TRADE_TYPE_OTHERS,		//����
	TRADE_TYPE_ALL,			//��
}DH_eATMTradeTypes;

typedef struct __ALARM_ATM_INFO_UPLOAD_CHNL
{
	int					nChannel;				// ��ѯ�ĵڼ�ͨ��ATM������Ϣ,��Χ0-N-1��N��ʾͨ������
	char				szATMID[32];			// ATM�ն˺�
	char				szCardNo[32];			// ����	����6222421541208230456 
	char				szTradetime[32];		// ����ʱ��	����20111118112200��ʾ2011-11-18 11:22:00
	DH_eATMTradeTypes	emTradeType;			// ��������	��Χ: ATMTradeTypes
	int					nAmount;				// ���׽��	0-4294967296
	BYTE				byRerved[32];			// ����
}ALARM_ATM_INFO_UPLOAD_CHNL;

// ATM������Ϣ�ϴ�(DH_ALARM_ATM_INFO_UPLOAD)�¼���Ӧ�ṹ��
typedef struct __ALARM_ATM_INFO_UPLOAD
{
	int							nCnt;
	ALARM_ATM_INFO_UPLOAD_CHNL	m_stAtmInfo[DH_MAX_CHANNUM];
}ALARM_ATM_INFO_UPLOAD;

// �������λ�����¼�
typedef struct __ALARM_CAMERA_MOVE_INFO
{
	int                         nChannelNum;                     // ��������ͨ����
	unsigned char               alarmChannels[DH_MAX_CHANNUM_EX];   // ��������ͨ������Ϣ
	BYTE                        byReserved[128];
}ALARM_CAMERA_MOVE_INFO;

// ��ϸ���챨����Ϣ
typedef struct __ALARM_DETAILEDMOTION_CHNL_INFO
{
	DWORD              dwSize;
	int                nChannelID;    // ͨ����
	BOOL               bAlarm;        // �Ƿ񱨾� TRUE/FALSE
	int                nLevel;        // �������𣬵�λǧ��֮���Զ��췢��С����������С��������
}ALARM_DETAILEDMOTION_CHNL_INFO;

/// �洢�쳣����
typedef struct __ALARM_STORAGE_FAILURE
{
	DWORD     dwSize;                                     // �ṹ���С
	UINT      ActionType;                                 // 0��ֹͣ�� 1����ʼ
	char      szProtocol[DH_MAX_STRING_LEN];              // Э�����ͣ�Ŀǰֻ֧��FTP
	char      szServerAddr[DH_MAX_IPADDR_OR_DOMAIN_LEN];  // ������IP��ַ
	DWORD     dwPort;                                     // �˿ں�
	NET_TIME  stuTime;                                    // �¼�����ʱ��
	int		  nChannel;									  // ͨ����, ��1��ʼ, 0��ʾ������ͨ��
}ALARM_STORAGE_FAILURE;

// ǰ�˶���������Ϣ
typedef struct __ALARM_FRONTDISCONNET_INFO
{
	DWORD              dwSize;                           // �ṹ���С
	int                nChannelID;                       // ͨ����
	int                nAction;                          // 0:��ʼ 1:ֹͣ
	NET_TIME           stuTime;                          // �¼�����ʱ��
	char               szIpAddress[MAX_PATH];            // ǰ��IPC��IP��ַ
}ALARM_FRONTDISCONNET_INFO;

// ��ص�ѹ���ͱ���
typedef struct __ALARM_BATTERYLOWPOWER_INFO
{
	DWORD             dwSize;                            // �ṹ���С
	int               nAction;                           // 0:��ʼ 1:ֹͣ
	int               nBatteryLeft;                      // ʣ������ٷֱȣ���λ%
	NET_TIME          stTime;                            // �¼�����ʱ��

}ALARM_BATTERYLOWPOWER_INFO;

// �¶ȹ��߱���
typedef struct __ALARM_TEMPERATURE_INFO
{
	DWORD              dwSize;                           // �ṹ���С
	char               szSensorName[DH_MACHINE_NAME_NUM];// �¶ȴ���������
	int                nChannelID;                       // ͨ����
	int                nAction;                          // 0:��ʼ 1:ֹͣ
	float              fTemperature;                     // ��ǰ�¶�ֵ, ��λ���϶�
	NET_TIME           stTime;                           // �¼�����ʱ��
}ALARM_TEMPERATURE_INFO;

// ƣ�ͼ�ʻ����
typedef struct __ALARM_TIREDDRIVE_INFO
{
	DWORD             dwSize;                            // �ṹ���С
	int               nAction;                           // 0:��ʼ 1:ֹͣ
	int               nDriveTime;                        // ������ʻʱ�䣬��λ����
	NET_TIME          stTime;                            // �¼�����ʱ��
}ALARM_TIREDDRIVE_INFO;

// ��¼���¼�����
typedef struct __ALARM_LOST_RECORD
{
	DWORD     dwSize;                                     //�ṹ���С
	UINT      ActionType;                                 // 0��ֹͣ�� 1����ʼ
	UINT      nChannelID;                                 // ͨ���ţ���1��ʼ
	UINT      nStreamType;                                // �������ͣ�0����������1��������1��2��������2��3��������3��4��ץͼ����
	NET_TIME  stuTime;                                    // �¼�����ʱ��	
}ALARM_LOST_RECORD;

// CPUռ���ʹ����¼��������ݶ�����95%��
typedef struct __ALARM_HIGH_CPU
{
	DWORD     dwSize;                                     //�ṹ���С
	UINT      ActionType;                                 // 0��ֹͣ�� 1����ʼ
	UINT      nUsed;                                      // CPUռ���ʵ�1000��
	NET_TIME  stuTime;                                    // �¼�����ʱ��	
}ALARM_HIGH_CPU;

// ���緢�����ݶ����¼�����
typedef struct __ALARM_LOST_NETPACKET
{
	DWORD     dwSize;                                     //�ṹ���С
	UINT      ActionType;                                 // 0��ֹͣ�� 1����ʼ
	UINT      nChannelID;                                 // ͨ���ţ���1��ʼ
	UINT      nStreamType;                                // �������ͣ�0����������1��������1��2��������2��3��������3��4��ץͼ����
	char      szRemoteIP[DH_MAX_IPADDR_LEN];              // ���Ͷ�IP��ַ
	DWORD     dwRemotePort;                               // ���Ͷ˵Ķ˿ڵ�ַ
	NET_TIME  stuTime;                                    // �¼�����ʱ��	
}ALARM_LOST_NETPACKET;

// �ڴ�ռ���ʹ����¼��������ݶ�����95%��
typedef struct __ALARM_HIGH_MEMORY
{
	DWORD     dwSize;                                     //�ṹ���С
	UINT      ActionType;                                 // 0��ֹͣ�� 1����ʼ
	UINT      nUsed;                                      // �ڴ�ռ���ʵ�1000��
	NET_TIME  stuTime;                                    // �¼�����ʱ��	
}ALARM_HIGH_MEMORY;

// ����������ץ���¼�
typedef struct __DH_BLACKLIST_SNAP_INFO
{
	DWORD     dwSize;
	char      szPlateNumber[32];                          // ���ƺ�
	NET_TIME  stuTime;                                    // �¼�����ʱ��
}DH_BLACKLIST_SNAP_INFO;

// Ӳ�������쳣�¼�
typedef struct __ALARM_DISK_FLUX
{
	DWORD				dwSize;	
	DWORD				dwAction;							// 0-��ʼ, 1-ֹͣ
	DWORD				dwDataFlux;							// ��ǰ��������, KB			
	NET_TIME			stuTime;							// �¼�����ʱ��
} ALARM_DISK_FLUX;

// ���������쳣�¼�
typedef struct __ALARM_NET_FLUX
{
	DWORD				dwSize;	
	DWORD				dwAction;							// 0-��ʼ, 1-ֹͣ
	DWORD				dwDataFlux;							// ��ǰ��������, KB
	NET_TIME			stuTime;							// �¼�����ʱ��
} ALARM_NET_FLUX;

// ����ת���쳣�¼�
typedef struct __ALARM_FAN_SPEED
{
	DWORD				dwSize;	
	DWORD				dwAction;							// 0-��ʼ, 1-ֹͣ
	DWORD				dwIndex;							// �������
	char				szName[DH_MACHINE_NAME_NUM];		// ����������
	NET_TIME			stuTime;							// �¼�����ʱ��
	DWORD				dwCurrent;							// ��ǰת��
} ALARM_FAN_SPEED;

// Ӳ�̱���
typedef struct __ALARM_DISK_INFO 
{
	DWORD				dwSize;
	DWORD				nChannel;							// Ӳ��ͨ����
	DWORD				nHDDNumber;							// ���������, 0: ����1: ��չ��1,  2: ��չ��2 
	DWORD				nHDDState;							// Ӳ��״̬, 0: Unknown, 1: Running, 2: Offline, 3: Warning, 4: Failed
} ALARM_DISK_INFO;

// �ļ�ϵͳ�澯
typedef struct __ALARM_FILE_SYSTEM_INFO 
{
	DWORD				dwSize;
	char				szMountDir[MAX_PATH];				// �ļ�ϵͳ������
	DWORD				nState;								// �ļ�ϵͳ״̬, 0: Unkown, 1: Normal, 2: Error
} ALARM_FILE_SYSTEM_INFO;

// Զ���ⲿ������Ϣ
typedef struct __ALARM_REMOTE_ALARM_INFO
{
	DWORD      dwSize;
	int        nChannelID;                               // ͨ���ţ���1��ʼ
	int        nState;                                   // ����״̬��0-������λ��1-������λ
}ALARM_REMOTE_ALARM_INFO;

// ���ܱ����¼�
typedef struct __ALARM_IVS_INFO
{
	DWORD      dwSize;
	NET_TIME   stuTime;                                  // �¼�����ʱ��	
	int        nChannelID;                               // ͨ���ţ���0��ʼ
	char	   szType[MAX_PATH];                         // ��������
	int        nState;                                   // ����״̬��0-������λ��1-������λ, 2-����ʽ����
}ALARM_IVS_INFO;

// ���ػ��ر���
typedef struct __ALARM_GOODS_WEIGHT_INFO
{
	DWORD		dwSize;
	int			nAction;							// 0-��ʼ, 1-ֹͣ
	int			nAlarmType;							// 0-����������, 1-С����С����, 2-���ر仯����������ֵ
	DWORD		dwGoodsWeight;						// ��ǰ����(kg)
	DWORD		dwSelfWeight;						// ����(kg)
	DWORD		dwTotalWeight;						// ����(kg)
	DWORD		dwStandardWeight;					// �˶�����(kg)
	DWORD		dwWeightScale;						// ���ر���
	DWORD		dwMaxGoodsWeight;					// ������(kg)
	DWORD		dwMinGoodsWeight;					// ��С����(kg)
	DWORD		dwAlarmWeight;						// ������ֵ(kg)
	int			nWeightChange;						// �ɼ�ʱ�����ڻ��ر仯(kg)
	int			nCheckTime;							// ��ֹ�ɼ�ʱ��(s)
} ALARM_GOODS_WEIGHT_INFO;

// ���ػ�����Ϣ�ϴ�
typedef struct __ALARM_GOODS_WEIGHT_UPLOAD_INFO 
{
	DWORD		dwSize;
	DWORD		dwGoodsWeight;						// ��ǰ����(kg)
	DWORD		dwSelfWeight;						// ����(kg)
	DWORD		dwTotalWeight;						// ����(kg)
	DWORD		dwStandardWeight;					// �˶�����(kg)
	DWORD		dwWeightScale;						// ���ر���	
} ALARM_GOODS_WEIGHT_UPLOAD_INFO;

// GPS״̬��Ϣ
typedef struct _NET_GPS_STATUS_INFO
{
    NET_TIME			revTime;				    // ��λʱ��
	char				DvrSerial[50];			    // �豸���к�
    double				longitude;				    // ����(��λ�ǰ����֮�ȣ���Χ0-360��)
    double				latidude;				    // γ��(��λ�ǰ����֮�ȣ���Χ0-180��)
    double				height;					    // �߶�(��)
    double				angle;					    // �����(��������Ϊԭ�㣬˳ʱ��Ϊ��)
    double				speed;					    // �ٶ�(��λ�Ǻ��speed/1000*1.852����/Сʱ)
    WORD				starCount;				    // ��λ����
    BOOL				antennaState;			    // ����״̬(true �ã�false ��)
    BOOL				orientationState;		    // ��λ״̬(true ��λ��false ����λ)
	BOOL                workStae;                   // ����״̬(true ������false�쳣)
	int                 nAlarmCount;                 // �����ı����¼�����
	int                 nAlarmState[128];            // �����ı����¼�����
	BYTE                bOffline;                    // 0-ʵʱ 1-���� 
	BYTE                byRserved[127];              // �����ֽ�
} NET_GPS_STATUS_INFO,*LPNET_GPS_STATUS_INFO;

// Ӳ�̿�¼�������¼�
typedef struct __ALARM_DISKBURNED_FULL_INFO
{
	DWORD		dwSize;
	int         nIndex;                             //���̺�
}ALARM_DISKBURNED_FULL_INFO;

// �洢���������¼�
typedef struct tagALARM_STORAGE_LOW_SPACE_INFO 
{
	DWORD				dwSize;
	int					nAction;						// 0:��ʼ 1:ֹͣ
	char				szName[DH_EVENT_NAME_LEN];		// �¼�����
	char				szDevice[DH_STORAGE_NAME_LEN];	// �洢�豸����
	char				szGroup[DH_STORAGE_NAME_LEN];	// �洢������
	INT64				nTotalSpace;					// ������, byte
	INT64				nFreeSpace;						// ʣ������, byte
	int					nPercent;						// �Ѿ�ʹ�õİٷֱ�
} ALARM_STORAGE_LOW_SPACE_INFO;

// �洢��������
typedef enum __EM_STORAGE_ERROR
{
	STORAGE_ERROR_NONE,							// ��
    STORAGE_ERROR_PATITION,						// ��������  		
	STORAGE_ERROR_INIT_FS,						// ��ʼ���ļ�ϵͳ����	
	STORAGE_ERROR_READ_DATA,					// ������ʧ��
	STORAGE_ERROR_WRITE_DATA,					// д����ʧ��
	STORAGE_ERROR_RAID_FAILED,					// RAID����
	STORAGE_ERROR_RAID_DEGRADED,				// RAID����
} EM_STORAGE_ERROR;

// �洢���󱨾�
typedef struct __ALARM_STORAGE_FAILURE_EX
{
	DWORD				dwSize;
	int					nAction;						// 0:��ʼ 1:ֹͣ
	char				szName[DH_EVENT_NAME_LEN];		// �¼�����
	char				szDevice[DH_STORAGE_NAME_LEN];	// �洢�豸����
	char				szGroup[DH_STORAGE_NAME_LEN];	// �洢������
	char				szPath[MAX_PATH];				// ·��
	EM_STORAGE_ERROR	emError;						// ��������
} ALARM_STORAGE_FAILURE_EX;

// ¼���쳣����
typedef struct __ALARM_RECORD_FAILED_INFO 
{
	DWORD				dwSize;
	int					nAction;						// 0:��ʼ 1:ֹͣ
	int					nIndex;							// ͨ����
} ALARM_RECORD_FAILED_INFO;

// �洢�����¼�
typedef struct __ALARM_STORAGE_BREAK_DOWN_INFO 
{
	DWORD				dwSize;
	int					nAction;						// 0:��ʼ 1:ֹͣ
} ALARM_STORAGE_BREAK_DOWN_INFO;

// ��Ƶ����ͨ��ʧЧ�¼����������õ���Ƶ����ͨ�������������豸����������DH_ALARM_VIDEO_ININVALID
typedef struct __ALARM_VIDEO_ININVALID_INFO 
{
	DWORD               dwSize;                         // �ṹ���С
	int                 nChannelID;                     // ͨ���ţ���0��ʼ
} ALARM_VIDEO_ININVALID_INFO;

///////////////////////// ���ܽ�ͨ�����¼�[CLIENT_StartListenEx] /////////////////////////////////////

//�¼����� DH_IVS_TRAFFIC_REALFLOWINFO(��ͨʵʱ������Ϣ�¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagALARM_IVS_TRAFFIC_REALFLOW_INFO
{
	int                 nChannelID;                       // ͨ����
	char                szName[128];                      // �¼�����
	char                bReserved1[4];                    // �ֽڶ���
	double              PTS;                              // ʱ���(��λ�Ǻ���)
	NET_TIME_EX         UTC;                              // �¼�������ʱ��
	int                 nEventID;                         // �¼�ID
	unsigned int        nSequence;                        // ���
	BYTE                bEventAction;                     // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	int                 nLane;                            // ��Ӧ������
	int                 nCount;                           // ��������
	int					nSpeed;							  // ���٣�km/h
	int                 nOverPercent;                     // ƽ�����ٰٷֱ�
	int                 nMetersUints;                     // �ٶȵ�λ��0�����1��Ӣ��
	BYTE                bReserved[1024];                  // �����ֽ�,������չ.
}ALARM_IVS_TRAFFIC_REALFLOW_INFO;

/////////////////////////////�����Խ���ض���/////////////////////////////

// ��Ƶ��ʽ��Ϣ
typedef struct
{
	BYTE				byFormatTag;			// �������ͣ���0��PCM
	WORD				nChannels;				// ������
	WORD				wBitsPerSample;			// �������			
	DWORD				nSamplesPerSec;			// ������
} DH_AUDIO_FORMAT, *LPDH_AUDIO_FORMAT;

/////////////////////////////�û�������ض���/////////////////////////////

// ֧���û�����󳤶�Ϊ8λ���豸����ӦCLIENT_QueryUserInfo��CLIENT_OperateUserInfo�ӿ�
// Ȩ����Ϣ
typedef struct _OPR_RIGHT
{
	DWORD				dwID;
	char				name[DH_RIGHT_NAME_LENGTH];
	char				memo[DH_MEMO_LENGTH];
} OPR_RIGHT;

// �û���Ϣ
typedef struct _USER_INFO
{
	DWORD				dwID;
	DWORD				dwGroupID;
	char				name[DH_USER_NAME_LENGTH];
	char				passWord[DH_USER_PSW_LENGTH];
	DWORD				dwRightNum;
	DWORD				rights[DH_MAX_RIGHT_NUM];
	char				memo[DH_MEMO_LENGTH];
	DWORD				dwReusable;				// �Ƿ��ã�1�����ã�0��������
} USER_INFO;

// �û�����Ϣ
typedef struct _USER_GROUP_INFO
{
	DWORD				dwID;
	char				name[DH_USER_NAME_LENGTH];
	DWORD				dwRightNum;
	DWORD				rights[DH_MAX_RIGHT_NUM];
	char				memo[DH_MEMO_LENGTH];
} USER_GROUP_INFO;

// �û���Ϣ��
typedef struct _USER_MANAGE_INFO
{
	DWORD				dwRightNum;				// Ȩ����Ϣ
	OPR_RIGHT			rightList[DH_MAX_RIGHT_NUM];
	DWORD				dwGroupNum;				// �û�����Ϣ
	USER_GROUP_INFO		groupList[DH_MAX_GROUP_NUM];
	DWORD				dwUserNum;				// �û���Ϣ
	USER_INFO			userList[DH_MAX_USER_NUM];
	DWORD				dwSpecial;				// �û�����������1��֧���û����ã�0����֧���û�����
} USER_MANAGE_INFO;

// ֧���û�����󳤶�Ϊ8λ��16λ���豸����Ӧ��չ�ӿ�CLIENT_QueryUserInfoEx��CLIENT_OperateUserInfoEx
#define DH_USER_NAME_LENGTH_EX		16			// �û�������
#define DH_USER_PSW_LENGTH_EX		16			// ����

// Ȩ����Ϣ
typedef struct _OPR_RIGHT_EX
{
	DWORD				dwID;
	char				name[DH_RIGHT_NAME_LENGTH];
	char				memo[DH_MEMO_LENGTH];
} OPR_RIGHT_EX;

// �û���Ϣ
typedef struct _USER_INFO_EX
{
	DWORD				dwID;
	DWORD				dwGroupID;
	char				name[DH_USER_NAME_LENGTH_EX];
	char				passWord[DH_USER_PSW_LENGTH_EX];
	DWORD				dwRightNum;
	DWORD				rights[DH_MAX_RIGHT_NUM];
	char				memo[DH_MEMO_LENGTH];
	DWORD				dwFouctionMask;			// ���룬0x00000001 - ֧���û�����
	BYTE				byReserve[32];
} USER_INFO_EX;

// �û�����Ϣ
typedef struct _USER_GROUP_INFO_EX
{
	DWORD				dwID;
	char				name[DH_USER_NAME_LENGTH_EX];
	DWORD				dwRightNum;
	DWORD				rights[DH_MAX_RIGHT_NUM];
	char				memo[DH_MEMO_LENGTH];
} USER_GROUP_INFO_EX;

// �û���Ϣ��
typedef struct _USER_MANAGE_INFO_EX
{
	DWORD				dwRightNum;				// Ȩ����Ϣ
	OPR_RIGHT_EX		rightList[DH_MAX_RIGHT_NUM];
	DWORD				dwGroupNum;				// �û�����Ϣ
	USER_GROUP_INFO_EX  groupList[DH_MAX_GROUP_NUM];
	DWORD				dwUserNum;				// �û���Ϣ
	USER_INFO_EX		userList[DH_MAX_USER_NUM];
	DWORD				dwFouctionMask;			// ���룻0x00000001 - ֧���û����ã�0x00000002 - �����޸���ҪУ��
	BYTE				byNameMaxLength;		// ֧�ֵ��û�����󳤶�
	BYTE				byPSWMaxLength;			// ֧�ֵ�������󳤶�
	BYTE				byReserve[254];
} USER_MANAGE_INFO_EX;

// ���֧��64ͨ�����豸����Ӧ��չ�ӿ�CLIENT_QueryUserInfoNew��CLIENT_OperateUserInfoNew
#define  DH_NEW_MAX_RIGHT_NUM    320
#define DH_NEW_USER_NAME_LENGTH	 128			// �û�������
#define DH_NEW_USER_PSW_LENGTH	 128			// ����
// Ȩ����Ϣ
typedef struct _OPR_RIGHT_NEW
{
	DWORD               dwSize;
	DWORD				dwID;
	char				name[DH_RIGHT_NAME_LENGTH];
	char				memo[DH_MEMO_LENGTH];
} OPR_RIGHT_NEW;

// �û���Ϣ
typedef struct _USER_INFO_NEW
{
	DWORD               dwSize;
	DWORD				dwID;
	DWORD				dwGroupID;
	char				name[DH_NEW_USER_NAME_LENGTH];
	char				passWord[DH_NEW_USER_PSW_LENGTH];
	DWORD				dwRightNum;
	DWORD				rights[DH_NEW_MAX_RIGHT_NUM];
	char				memo[DH_MEMO_LENGTH];
	DWORD				dwFouctionMask;			// ���룬0x00000001 - ֧���û�����
	BYTE				byReserve[32];
} USER_INFO_NEW;

// �û�����Ϣ
typedef struct _USER_GROUP_INFO_NEW
{
	DWORD               dwSize;
	DWORD				dwID;
	char				name[DH_USER_NAME_LENGTH_EX];
	DWORD				dwRightNum;
	DWORD				rights[DH_NEW_MAX_RIGHT_NUM];
	char				memo[DH_MEMO_LENGTH];
} USER_GROUP_INFO_NEW;

// �û���Ϣ��
typedef struct _USER_MANAGE_INFO_NEW
{
	DWORD               dwSize;
	DWORD				dwRightNum;				// Ȩ����Ϣ
	OPR_RIGHT_NEW		rightList[DH_NEW_MAX_RIGHT_NUM];
	DWORD				dwGroupNum;				// �û�����Ϣ
	USER_GROUP_INFO_NEW  groupList[DH_MAX_GROUP_NUM];
	DWORD				dwUserNum;				// �û���Ϣ
	USER_INFO_NEW		userList[DH_MAX_USER_NUM];
	DWORD				dwFouctionMask;			// ���룻0x00000001 - ֧���û����ã�0x00000002 - �����޸���ҪУ��
	BYTE				byNameMaxLength;		// ֧�ֵ��û�����󳤶�
	BYTE				byPSWMaxLength;			// ֧�ֵ�������󳤶�
	BYTE				byReserve[254];
} USER_MANAGE_INFO_NEW;

///////////////////////////////��ѯ��ض���///////////////////////////////

// �豸֧����������
typedef struct _DH_LANGUAGE_DEVINFO
{
	DWORD				dwLanguageNum;			// ֧�����Ը���
	BYTE				byLanguageType[252];	// ö��ֵ�����DH_LANGUAGE_TYPE
} DH_DEV_LANGUAGE_INFO, *LPDH_DEV_LANGUAGE_INFO;

// ��ѯ�豸֧�ֵ�IPC������Ϣ
typedef struct
{
	int                 nTypeCount;              // ֧�ֵ�IPC����
	BYTE                bSupportTypes[128];      // ö��ֵ�����EM_IPC_TYPE
}DH_DEV_IPC_INFO;

//3G����������Ϣ
typedef struct
{
	int                nStrategy;              // ���²���,0-����������,1-��ʱ�����
	int                nUplimit;               // ��������, ����Զ�Ӧ, ������, ��λMB; ��ʱ�䣬��λСʱ
	int                nUsed;                  // ��ʹ����������λ��nUplimit��ͬ
	BYTE               bReserved[64];          // �����ֶ�
}DH_DEV_3GFLOW_INFO;

// 3Gģ����Ϣ
typedef struct
{
	BYTE       byEthNum;                    // 3Gģ����
	BYTE       byReserved[255];             // �����ֽ�
}DH_DEV_3GMODULE_INFO;

typedef struct
{
	DWORD      dwId;                                    // ddns ������id��
	char	   szState[DH_MAX_DDNS_STATE_LEN];	        // ddns ״̬
	BYTE       bReserved[512];                          // �����ֶ�
}DH_DEV_DNS_INFO;
typedef struct
{
	DWORD				dwDdnsServerNum;	
	DH_DEV_DNS_INFO     stDdns[DH_MAX_DDNS_NUM];
}DH_DEV_MULTI_DDNS_INFO;

// �豸URL��Ϣ
typedef struct
{
	char               szURLInfo[512];                //�豸URL��Ϣ, ���ַ������
	BYTE               bReserved[512];
}DH_DEV_URL_INFO;
// Ӳ����Ϣ
typedef struct
{
	DWORD				dwVolume;				// Ӳ�̵�����, ��λMB(B��ʾ�ֽ�)
	DWORD				dwFreeSpace;			// Ӳ�̵�ʣ��ռ�, ��λMB(B��ʾ�ֽ�)
	BYTE				dwStatus;				// ����λ��ֵ��ʾӲ�����ͣ������ö������EM_DISK_TYPE������λ��ֵ��ʾӲ�̵�״̬��0-����,1-�,2-���ϵȣ���DWORD����ĸ�BYTE
	BYTE				bDiskNum;				// Ӳ�̺�
	BYTE				bSubareaNum;			// ������
	BYTE				bSignal;				// ��ʶ��0Ϊ���� 1ΪԶ��
} NET_DEV_DISKSTATE,*LPNET_DEV_DISKSTATE;

// �豸Ӳ����Ϣ
typedef struct _DH_HARDDISK_STATE
{
	DWORD				dwDiskNum;				// ����
	NET_DEV_DISKSTATE	stDisks[DH_MAX_DISKNUM];// Ӳ�̻������Ϣ
} DH_HARDDISK_STATE, *LPDH_HARDDISK_STATE;

typedef DH_HARDDISK_STATE	DH_SDCARD_STATE;	// SD�������ݽṹͬӲ����Ϣ

// ����������Ϣ
typedef struct  
{
	DH_TALK_CODING_TYPE	encodeType;				// ��������
	int					nAudioBit;				// λ������8��16
	DWORD				dwSampleRate;			// �����ʣ���8000��16000
	char				reserved[64];
} DHDEV_TALKDECODE_INFO;

// �豸֧�ֵ������Խ�����
typedef struct 
{
	int					nSupportNum;			// ����
	DHDEV_TALKDECODE_INFO type[64];				// ��������
	char				reserved[64];
} DHDEV_TALKFORMAT_LIST;

// ��̨������Ϣ
#define  NAME_MAX_LEN 16
typedef struct 
{
	DWORD				dwHighMask;				// �����������λ
	DWORD				dwLowMask;				// �����������λ
	char				szName[NAME_MAX_LEN];	// ������Э����
	WORD				wCamAddrMin;			// ͨ����ַ����Сֵ
	WORD				wCamAddrMax;			// ͨ����ַ�����ֵ
	WORD				wMonAddrMin;			// ���ӵ�ַ����Сֵ
	WORD				wMonAddrMax;			// ���ӵ�ַ�����ֵ
	BYTE				bPresetMin;				// Ԥ�õ����Сֵ
	BYTE				bPresetMax;				// Ԥ�õ�����ֵ
	BYTE				bTourMin;				// �Զ�Ѳ����·����Сֵ
	BYTE				bTourMax;				// �Զ�Ѳ����·�����ֵ
	BYTE				bPatternMin;			// �켣��·����Сֵ
	BYTE				bPatternMax;			// �켣��·�����ֵ
	BYTE				bTileSpeedMin;			// ��ֱ�ٶȵ���Сֵ
	BYTE				bTileSpeedMax;			// ��ֱ�ٶȵ����ֵ
	BYTE				bPanSpeedMin;			// ˮƽ�ٶȵ���Сֵ
	BYTE				bPanSpeedMax;			// ˮƽ�ٶȵ����ֵ
	BYTE				bAuxMin;				// �������ܵ���Сֵ
	BYTE				bAuxMax;				// �������ܵ����ֵ
	int					nInternal;				// ���������ʱ����
	char				cType;					// Э�������
	BYTE				bReserved_1;			// ����
	BYTE				bFuncMask;				// Э�鹦������,��λ��ʾ,�ã���ʾ֧��,��һλ��ʾ������̨���ܣ�������λ��ʱ����
	BYTE				bReserved_2;
	char				Reserved[4];
} PTZ_OPT_ATTR;

// ��¼����Ϣ
typedef struct _NET_DEV_BURNING
{
	DWORD				dwDriverType;			// ��¼���������ͣ�0��DHFS��1��DISK��2��CDRW
	DWORD				dwBusType;				// �������ͣ�0��USB��1��1394��2��IDE
	DWORD				dwTotalSpace;			// ������(KB)
	DWORD				dwRemainSpace;			// ʣ������(KB)
	BYTE				dwDriverName[DH_BURNING_DEV_NAMELEN];	// ��¼����������
} NET_DEV_BURNING, *LPNET_DEV_BURNING;

// �豸��¼����Ϣ
typedef struct _DH_BURNING_DEVINFO
{
	DWORD				dwDevNum;				// ��¼�豸����
	NET_DEV_BURNING		stDevs[DH_MAX_BURNING_DEV_NUM];	// ����¼�豸��Ϣ
} DH_BURNING_DEVINFO, *LPDH_BURNING_DEVINFO;

// ��¼����
typedef struct _DH_BURNING_PROGRESS
{
	BYTE				bBurning;				// ��¼��״̬��0�����Կ�¼��1����¼�����Ͳ��ԣ���һ���ǹ����豸��
												// 2��δ�ҵ���¼����3�������������ڿ�¼��4����¼�����ڷǿ���״̬�����ڱ��ݡ���¼��ط���
	BYTE				bRomType;				// ��Ƭ���ͣ�0�����ļ�ϵͳ��1���ƶ�Ӳ�̻�U�̣�2������
	BYTE				bOperateType;			// �������ͣ�0�����У�1�����ڱ����У�2�����ڿ�¼�У�3�����ڽ��й��̻ط�
	BYTE				bType;					// ���ݻ��¼����״̬��0-ֹͣ 1-��ʼ 2-���� 3-�� 4-���� 5-���ڳ�ʼ�� 6-��ͣ 7-�ȴ�����
	NET_TIME			stTimeStart;			// ��ʼʱ�䡡
	DWORD				dwTimeElapse;			// �ѿ�¼ʱ��(��)
	DWORD				dwTotalSpace;			// ����������
	DWORD				dwRemainSpace;			// ����ʣ������
	DWORD				dwBurned;				// �ѿ�¼����
	WORD				dwStatus;				// ����
	WORD				wChannelMask;			// ���ڿ�¼��ͨ������
} DH_BURNING_PROGRESS, *LPDH_BURNING_PROGRESS;

// ��־��Ϣ����Ӧ�ӿ�CLIENT_QueryLog�ӿ�
typedef struct _DH_LOG_ITEM
{
    DHDEVTIME			time;					// ����
    unsigned short		type;					// ����
    unsigned char		reserved;				// ����
    unsigned char		data;					// ����
    unsigned char		context[8];				// ����
} DH_LOG_ITEM, *LPDH_LOG_ITEM;

// ��־��Ϣ����Ӧ��չ�ӿ�CLIENT_QueryLogEx������reserved(int nType=1;reserved=&nType;)
typedef struct _DH_NEWLOG_ITEM
{
	DHDEVTIME			time;					// ����
	WORD				type;					// ����
	WORD				data;					// ����
	char				szOperator[8]; 			// �û���
	BYTE				context[16];		    // ����	
} DH_NEWLOG_ITEM, *LPDH_NEWLOG_ITEM;

// ��־��Ϣ����Ӧ�ӿ�CLIENT_QueryDeviceLog�ӿ�
typedef struct _DH_DEVICE_LOG_ITEM
{
	int					nLogType;				// ��־����
	DHDEVTIME			stuOperateTime;			// ����
	char				szOperator[16]; 		// ������
	BYTE				bReserved[3];
	BYTE				bUnionType;				//  union�ṹ����,0:szLogContext��1:stuOldLog��
	union
	{
		char			szLogContext[64];		// ��־��ע��Ϣ
		struct 
		{
			DH_LOG_ITEM		stuLog;				// �ɵ���־�ṹ��
			BYTE			bReserved[48];		// ����
		}stuOldLog;
	};
	char				reserved[16];
} DH_DEVICE_LOG_ITEM, *LPDH_DEVICE_LOG_ITEM;

// ����־��Ϣ�ṹ����Ӧ�ӿ�CLIENT_QueryDeviceLog�ӿ�
typedef struct _DH_DEVICE_LOG_ITEM_EX
{
	int					nLogType;				// ��־����
	DHDEVTIME			stuOperateTime;			// ����
	char				szOperator[16]; 		// ������
	BYTE				bReserved[3];
	BYTE				bUnionType;				//  union�ṹ����,0:szLogContext��1:stuOldLog��
	union
	{
		char			szLogContext[64];		// ��־��ע��Ϣ
		struct 
		{
			DH_LOG_ITEM		stuLog;				// �ɵ���־�ṹ��
			BYTE			bReserved[48];		// ����
		}stuOldLog;
	};
	char                szOperation[32];        // ����Ĳ�������
	char				szDetailContext[4*1024];  // ��ϸ��־��Ϣ����
} DH_DEVICE_LOG_ITEM_EX, *LPDH_DEVICE_LOG_ITEM_EX;

// ¼����־��Ϣ����Ӧ��־�ṹ�����context
typedef struct _LOG_ITEM_RECORD
{
	DHDEVTIME			time;					// ʱ��
	BYTE				channel;				// ͨ��
	BYTE				type;					// ¼������
	BYTE				reserved[2];
} LOG_ITEM_RECORD, *LPLOG_ITEM_RECORD;

typedef struct _QUERY_DEVICE_LOG_PARAM
{
	DH_LOG_QUERY_TYPE	emLogType;				// ��ѯ��־����
	NET_TIME			stuStartTime;			// ��ѯ��־�Ŀ�ʼʱ��
	NET_TIME			stuEndTime;				// ��ѯ��־�Ľ���ʱ��
	int					nStartNum;				// ��ʱ����дӵڼ�����־��ʼ��ѯ����ʼ��һ�β�ѯ����Ϊ0
	int					nEndNum;				// һ�β�ѯ�е��ڼ�����־����,��־�������������ֵΪ1024
	BYTE                nLogStuType;            // ��־���ݽṹ������,0:��ʾDH_DEVICE_LOG_ITEM��1:��ʾDH_DEVICE_LOG_ITEM_EX
	BYTE                reserved[3];            // ���� ����
	unsigned int        nChannelID;             // ͨ����,0:����֮ǰ��ʾ����ͨ���ţ�����ͨ���Ŵ�1��ʼ; 1:��һ��ͨ��
	BYTE				bReserved[40];
} QUERY_DEVICE_LOG_PARAM;

// �豸Ӳ�����¼����Ϣ
typedef struct __DEV_DISK_RECORD_INFO 
{
	NET_TIME			stuBeginTime;			// ����¼��ʱ��
	NET_TIME			stuEndTime;				// ���¼��ʱ��
	char				reserved[128];
} DEV_DISK_RECORD_INFO;

// �豸Ӳ��¼��ʱ����Ϣ
typedef struct __DEV_DISK_RECORD_TIME
{
	NET_TIME             stuStartTime1;		    // ¼��ʱ���1��ʼʱ��
	NET_TIME	         stuEndTime1;			// ¼��ʱ���1����ʱ��
	BOOL	             bTwoPart;			    // �Ƿ��еڶ���
	NET_TIME	         stuStartTime2;		    // ¼��ʱ���2��ʼʱ��
	NET_TIME	         stuEndTime2;			// ¼��ʱ���2����ʱ��
	BYTE			  	 bDiskNum;				// Ӳ�̺�
	BYTE				 bSubareaNum;			// ������
	BYTE                 byReserved[62];        // �����ֽ�  

}DEV_DISK_RECORD_TIME;

///////////////////////////////������ض���///////////////////////////////

// Ӳ�̲���
typedef struct _DISKCTRL_PARAM
{
	DWORD				dwSize;					// �ṹ���С���汾������
	int					nIndex;					// ΪӲ����Ϣ�ṹ��DH_HARDDISK_STATE�������stDisks�±꣬��0��ʼ
	int					ctrlType;				// �������ͣ�
												// 0 - �������, 1 - ��Ϊ��д��, 2 - ��Ϊֻ����
												// 3 - ��Ϊ������, 4 - �ָ�����, 5 - ��Ϊ�����̣�7 - ����SD������SD��������Ч��
	NET_DEV_DISKSTATE	stuDisk;				// ������Ϣ, ���ڴ���˳����ܸı䵼���±겻׼, ���������±�
} DISKCTRL_PARAM;

typedef struct  
{
	BYTE				bSubareaNum;			// Ԥ�����ĸ���
	BYTE				bIndex;					// ΪӲ����Ϣ�ṹ��DH_HARDDISK_STATE�������stDisks�±꣬��0��ʼ
	BYTE				bSubareaSize[32];		// ������С���ٷֱȣ�
	BYTE				bReserved[30];			// ����
} DISKCTRL_SUBAREA;

// ����״̬
typedef struct _ALARMCTRL_PARAM
{
	DWORD				dwSize;
	int					nAlarmNo;				// ����ͨ���ţ���0��ʼ
	int					nAction;				// 1������������0��ֹͣ����
} ALARMCTRL_PARAM;

// �������
typedef struct _MATRIXCTRL_PARAM
{
	DWORD				dwSize;
	int					nChannelNo;				// ��Ƶ����ţ���0��ʼ
	int					nMatrixNo;				// ��������ţ���0��ʼ
} MATRIXCTRL_PARAM;

// ��¼����
typedef struct _BURNING_PARM
{
	int					channelMask;			// ͨ�����룬��λ��ʾҪ��¼��ͨ��
//  int			    	devMask;                // ��¼�����룬���ݲ�ѯ���Ŀ�¼���б�����λ��ʾ
	BYTE				devMask;				// ��¼�����룬���ݲ�ѯ���Ŀ�¼���б�����λ��ʾ
	BYTE                bySpicalChannel;        // ���л�ͨ��(ͨ����+32)
	BYTE                byReserved[2];          // �����ֶ�
} BURNNG_PARM;

// ������¼
typedef struct _BURNING_PARM_ATTACH
{
	BOOL				bAttachBurn;			// �Ƿ�Ϊ������¼��0:����; 1:��
	BYTE				bReserved[12];			// �����ֶ�
} BURNING_PARM_ATTACH;

// �ֶ�ץ�Ĳ���
typedef struct  _MANUAL_SNAP_PARAMETER{
	int                 nChannel;               // ץͼͨ��,��0��ʼ
	BYTE                bySequence[64];	        // ץͼ���к��ַ���
	BYTE                byReserved[60];         // �����ֶ�
}MANUAL_SNAP_PARAMETER;

// �����豸�˱���Ԥ���ָ����
typedef struct _DEVICE_LOCALPREVIEW_SLIPT_PARAMETER
{
	int                 nSliptMode;            // �ָ�ģʽ�����豸�˱���Ԥ��֧�ֵķָ�ģʽ
	int                 nSubSliptNum;          // ��ǰҪԤ�����ӷָ�,��1��ʼ
	BYTE                byReserved[64];        // �����ֶ�
}DEVICE_LOCALPREVIEW_SLIPT_PARAMETER;

// �豸�˱���Ԥ��֧�ֵķָ�ģʽ
typedef struct _DEVICE_LOCALPREVIEW_SLIPT_CAP
{
	int                 nModeNumber;
	int                 nSliptMode[36];        // ֧�ֵķָ�ģʽ��
	BYTE                byReserved[64];        // �����ֶ�
}DEVICE_LOCALPREVIEW_SLIPT_CAP;

// ·����Ϣ
typedef struct  _CROSSING_INFO{
	char				szCrossingID[DH_MAX_CROSSING_ID]; // ·�����к�
	DWORD				dwLatitude; // γ��(��λ�ǰ����֮�ȣ���Χ0-180��)�籱γ30��.��183382�ȱ�ʾΪ120183382)
	DWORD				dwLongitude;// ����(��λ�ǰ����֮�ȣ���Χ0-360��) �綫��120��.��178274�ȱ�ʾΪ300178274��
	WORD				wSpeedLimit;// ·������ֵ,��λKm/h 0��ʾ������,������ʾ����ֵ����
	BYTE 				byReserved[22];
}CROSSING_INFO;

// ·�ߵ�λ��Ϣ
typedef struct  _ROUTE_CROSSING_INFO{
	BYTE 			    byCrossingNum;              // ·����Ч������Χ1~DH_MAX_CROSSING_NUM
	BYTE			    byReserved1;
	WORD                wCrossingRange;             // ��λ���ȷ�Χ��λm
	CROSSING_INFO 	    stCrossingInfo[DH_MAX_CROSSING_NUM];        // ·����Ϣ���֧��128��·��
    BYTE			    byReserved2[2044];
}ROUTE_CROSSING_INFO;

// raid����
typedef struct _CTRL_RAID_INFO
{
	char				szAction[16];						// Add���ӣ�Deleteɾ��
	char				szName[16];							// Raid����
	int					nType;								// ���� 1:Jbod     2:Raid0      3:Raid1     4:Raid5
	int					nStatus;							// ״̬ 0:unknown ��1:active��2:degraded��3:inactive��4:recovering
	int					nCntMem;							// nMember�������Ч���ݸ���
	int					nMember[32];						// 1,2,3,... ��ɴ���ͨ��,�Ǹ�����
	int					nCapacity;							// ����,��λG
	int					nRemainSpace;						// ʣ����������λM
	int					nTank;								// ��չ�� 0:������1:��չ��1��2:��չ��2������
	char				reserved[128];
}CTRL_RAID_INFO;

// �ȱ�����
typedef struct _CTRL_SPARE_DISK_INFO
{
	char				szAction[16];						// Enable��ʹ�ܣ�Disable����ʹ��
	char				szScope[16];						// Global��ȫ���ȱ���Local����ȫ���ȱ�
	char				szName[16];							// �ȱ����֣���ScopeΪGlobal����Ϊ�ȱ��ص����ƣ������ʾRaid�������
	unsigned int        nIndex;								// �������
	char				reserved[128];
}CTRL_SPARE_DISK_INFO;

typedef struct _CTRL_SPARE_DISK_INFO_A
{
	int						nCnt;							// �ȱ��̵ĸ���
	CTRL_SPARE_DISK_INFO	stSpaceDiskInfo[32];
}CTRL_SPARE_DISK_INFO_A;

// ��������������
typedef struct __CTRL_ARM_DISARM_PARAM
{
	BYTE                bState;                 // ������״̬��0��ʾ������1��ʾ������2��ʾǿ�Ʋ���
	char                reserve[31];
} CTRL_ARM_DISARM_PARAM;


typedef struct tagDHCTRL_CONNECT_WIFI_BYWPS_IN
{
	DWORD				dwSize;
	int                 nType;                         // WPS��������,0:���ⰴť��ʽ; 1:(�豸��)pin�뷽ʽ; 2:(wifi�ȵ��)pin�뷽ʽ
	char                szSSID[DH_MAX_SSID_LEN];       // SSID��nTypeΪ1��2ʱ��Ч�����֧��32λ
	char                szApPin[DH_MAX_APPIN_LEN];     // APPIN��, nTypeΪ2ʱ��Ч��PIN��Ϊ8λ���֣����pin���Ǵ�wifi�ȵ���õ���
	char                szWLanPin[DH_MAX_APPIN_LEN];   // �豸pin��,nTypeΪ1ʱ��Ч:Ϊ��ʱ���豸����;��Ϊ��ʱ����ʾ���û��趨�����֧��8λ���֣����pin��Ҫ��WIFI�ȵ������
}DHCTRL_CONNECT_WIFI_BYWPS_IN;

typedef struct tagDHCTRL_CONNECT_WIFI_BYWPS_OUT
{
	DWORD				dwSize;
	char                szRetWLanPin[DH_MAX_APPIN_LEN];// �����豸PIN�룬��WPS��������Ϊ(�豸��)pin�뷽ʽʱ�����������Ч
}DHCTRL_CONNECT_WIFI_BYWPS_OUT;

// CLIENT_ControlDevice�ӿڵ�DH_CTRL_WIFI_BY_WPS�������(WPS��������WIFI)
typedef struct tagDHCTRL_CONNECT_WIFI_BYWPS
{
	DWORD				dwSize;
	DHCTRL_CONNECT_WIFI_BYWPS_IN     stuWpsInfo;         // ���Ӳ���(���û���д)
	DHCTRL_CONNECT_WIFI_BYWPS_OUT    stuWpsResult;       // ��������(���豸����)
} DHCTRL_CONNECT_WIFI_BYWPS;

// CLIENT_ControlDevice�ӿڵ� DH_CTRL_CLOSE_BURNER �� �������
typedef struct tagNET_CTRL_BURNERDOOR
{
	DWORD		        dwSize;
	const char*         szBurnerName;                  // �������ƣ��硰/dev/sda��
	BOOL                bResult;                       // �������
}NET_CTRL_BURNERDOOR;

// CLIENT_QueryDevState�ӿڵ� DH_DEVSTATE_BURNERDOOR �������
typedef struct tagNET_DEVSTATE_BURNERDOOR
{
	DWORD		        dwSize;
	const char*         szBurnerName;                  // �������ƣ��硰/dev/sda��
	bool                bEjected;                      // �Ƿ��Ѿ�����
	BYTE				Reserved[3];			       // ����
}NET_DEVSTATE_BURNERDOOR;

// CLIENT_QueryDevState�ӿڵ� DH_DEVSTATE_GET_DATA_CHECK �������
typedef struct tagNET_DEVSTATE_DATA_CHECK
{
    DWORD		        dwSize;                     // �ṹ���С
    const char*         szBurnerName;               // �������ƣ��硰/dev/s",����Ƕ���̵Ļ����κ�һ�����̶�����
    char                szState[DH_MAX_STRING_LEN]; // "NotStart":��δ��ʼ,"Verifying":У����,"Failed":ʧ��,"Successed":�ɹ�
    int                 nPercent;                   // У��ٷֱ�:0-100��state��Verifyingʱ����Ч
}NET_DEVSTATE_DATA_CHECK;

// CLIENT_ListenServer �ӿڻص�fServiceCallBack����֧�ֵ���������
enum { 
	DH_DVR_DISCONNECT=-1,	                        // ��֤�ڼ��豸���߻ص�
	DH_DVR_SERIAL_RETURN=1,                         // �豸ע��Я�����к� ��Ӧ char* szDevSerial
	NET_DEV_AUTOREGISTER_RETURN,                    // �豸ע��Я�����кź����� ��ӦNET_CB_AUTOREGISTER
};
typedef struct tagNET_CB_AUTOREGISTER
{
	DWORD			dwSize;                          // �ṹ���С
	char            szDevSerial[DH_DEV_SERIALNO_LEN];// ���к�
	char            szToken[MAX_PATH];               // ����
}NET_CB_AUTOREGISTER;

// ��������ע����ؽṹ��
typedef struct tagCLOUDSERVICE_CONNECT_PARAM
{
	DWORD               dwSize;   
	char                szDstIp[DH_MAX_IPADDR_EX_LEN];    // ������IP
	int                 nDstPort;                         // �������˿ں� 
	DWORD               dwConnectType;                    // �������ͣ�0��ʾ�����ӣ�1��ʾ�������ӣ�2��������, 3��̬ע�������ӣ�ʹ��0Xb4ע�ᣩ  
	char                szToken[MAX_PATH];                // ʹ�����Զ����豸ͨ��ΨһID����
}NET_CLOUDSERVICE_CONNECT_PARAM;

typedef struct tagCLOUDSERVICE_CONNECT_RESULT
{
	DWORD               dwSize;  
	DWORD               dwConnectState;                   // ��ǰ����״̬��1�ɹ���0ʧ��
	char                szMessage[DH_MAX_CLOUDCONNECT_STATE_LEN]; // ����״̬��Ϣ,"Success","Password Error","Network Error","Timeout"
}NET_CLOUDSERVICE_CONNECT_RESULT;
///////////////////////////////������ض���///////////////////////////////

//-------------------------------�豸����---------------------------------
// �豸��Ϣ
typedef struct
{
	BYTE				sSerialNumber[DH_SERIALNO_LEN];	// ���к�
	BYTE				byAlarmInPortNum;		// DVR�����������
	BYTE				byAlarmOutPortNum;		// DVR�����������
	BYTE				byDiskNum;				// DVRӲ�̸���
	BYTE				byDVRType;				// DVR����, ��ö��DHDEV_DEVICE_TYPE
	BYTE				byChanNum;				// DVRͨ������
} NET_DEVICEINFO, *LPNET_DEVICEINFO;

// �豸��Ϣ��չ
typedef struct
{
	BYTE				sSerialNumber[DH_SERIALNO_LEN];	// ���к�
	int					nAlarmInPortNum;		// DVR�����������
	int					nAlarmOutPortNum;		// DVR�����������
	int					nDiskNum;				// DVRӲ�̸���
	int					nDVRType;				// DVR����, ��ö��DHDEV_DEVICE_TYPE
	int					nChanNum;				// DVRͨ������
	char				Reserved[32];			// ����
} NET_DEVICEINFO_Ex, *LPNET_DEVICEINFO_Ex;

// �豸�����汾��Ϣ����16λ��ʾ���汾�ţ���16λ��ʾ�ΰ汾��
typedef struct 
{
	DWORD				dwSoftwareVersion;
	DWORD				dwSoftwareBuildDate;
	DWORD				dwDspSoftwareVersion;
	DWORD				dwDspSoftwareBuildDate;
	DWORD				dwPanelVersion;
	DWORD				dwPanelSoftwareBuildDate;
	DWORD				dwHardwareVersion;
	DWORD				dwHardwareDate;
	DWORD				dwWebVersion;
	DWORD				dwWebBuildDate;
} DH_VERSION_INFO, *LPDH_VERSION_INFO;

// �豸�����汾��Ϣ����ӦCLIENT_QueryDevState�ӿ�
typedef struct  
{
	char				szDevSerialNo[DH_DEV_SERIALNO_LEN];	// ���к�
	char				byDevType;				// �豸���ͣ���ö��DHDEV_DEVICE_TYPE
	char				szDevType[DH_DEV_TYPE_LEN];	// �豸��ϸ�ͺţ��ַ�����ʽ������Ϊ��
	int					nProtocalVer;			// Э��汾��
	char				szSoftWareVersion[DH_MAX_URL_LEN];
	DWORD				dwSoftwareBuildDate;
	char				szDspSoftwareVersion[DH_MAX_URL_LEN];
	DWORD				dwDspSoftwareBuildDate;
	char				szPanelVersion[DH_MAX_URL_LEN];
	DWORD				dwPanelSoftwareBuildDate;
	char				szHardwareVersion[DH_MAX_URL_LEN];
	DWORD				dwHardwareDate;
	char				szWebVersion[DH_MAX_URL_LEN];
	DWORD				dwWebBuildDate;
	char				reserved[256];
} DHDEV_VERSION_INFO;

// DSP������������ӦCLIENT_GetDevConfig�ӿ�
typedef struct 
{
	DWORD				dwVideoStandardMask;	// ��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ
	DWORD				dwImageSizeMask;		// �ֱ������룬��λ��ʾ�豸�ܹ�֧�ֵķֱ�������
	DWORD				dwEncodeModeMask;		// ����ģʽ���룬��λ��ʾ�豸�ܹ�֧�ֵı���ģʽ����	
	DWORD				dwStreamCap;			// ��λ��ʾ�豸֧�ֵĶ�ý�幦�ܣ�
												// ��һλ��ʾ֧��������
												// �ڶ�λ��ʾ֧�ָ�����1
												// ����λ��ʾ֧�ָ�����2
												// ����λ��ʾ֧��jpgץͼ
	DWORD				dwImageSizeMask_Assi[8];// ��ʾ������Ϊ���ֱ���ʱ��֧�ֵĸ������ֱ������롣
	DWORD				dwMaxEncodePower;		// DSP֧�ֵ���߱������� 
	WORD				wMaxSupportChannel;		// ÿ��DSP֧�����������Ƶͨ���� 
	WORD				wChannelMaxSetSync;		// DSPÿͨ���������������Ƿ�ͬ����0����ͬ����1��ͬ��
} DH_DSP_ENCODECAP, *LPDH_DSP_ENCODECAP;

// DSP������������չ���ͣ���ӦCLIENT_QueryDevState�ӿ�
typedef struct 
{
	DWORD				dwVideoStandardMask;	// ��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ
	DWORD				dwImageSizeMask;		// �ֱ������룬��λ��ʾ�豸�ܹ�֧�ֵķֱ���
	DWORD				dwEncodeModeMask;		// ����ģʽ���룬��λ��ʾ�豸�ܹ�֧�ֵı���ģʽ
	DWORD				dwStreamCap;			// ��λ��ʾ�豸֧�ֵĶ�ý�幦�ܣ�
												// ��һλ��ʾ֧��������
												// �ڶ�λ��ʾ֧�ָ�����1
												// ����λ��ʾ֧�ָ�����2
												// ����λ��ʾ֧��jpgץͼ
	DWORD				dwImageSizeMask_Assi[32];// ��ʾ������Ϊ���ֱ���ʱ��֧�ֵĸ������ֱ������롣
	DWORD				dwMaxEncodePower;		// DSP֧�ֵ���߱������� 
	WORD				wMaxSupportChannel;		// ÿ��DSP֧�����������Ƶͨ���� 
	WORD				wChannelMaxSetSync;		// DSPÿͨ���������������Ƿ�ͬ����0����ͬ����1��ͬ��
	BYTE				bMaxFrameOfImageSize[32];// ��ͬ�ֱ����µ����ɼ�֡�ʣ���dwVideoStandardMask��λ��Ӧ
	BYTE				bEncodeCap;				// ��־������ʱҪ����������������������ò�����Ч��
												// 0���������ı�������+�������ı������� <= �豸�ı���������
												// 1���������ı�������+�������ı������� <= �豸�ı���������
												// �������ı������� <= �������ı���������
												// �������ķֱ��� <= �������ķֱ��ʣ�
												// �������͸�������֡�� <= ǰ����Ƶ�ɼ�֡��
												// 2��N5�ļ��㷽��
												// �������ķֱ��� <= �������ķֱ���
												// ��ѯ֧�ֵķֱ��ʺ���Ӧ���֡��
	char				reserved[95];
} DHDEV_DSP_ENCODECAP, *LPDHDEV_DSP_ENCODECAP;

// DSP��չ������������ӦCLIENT_QueryDevState�ӿ�
typedef struct 
{
	DWORD				dwVideoStandardMask;	// ��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ
	DWORD				dwImageSizeMask;		// �ֱ������룬��λ��ʾ�豸�ܹ�֧�ֵķֱ���
	DWORD				dwEncodeModeMask;		// ����ģʽ���룬��λ��ʾ�豸�ܹ�֧�ֵı���ģʽ
	DWORD				dwStreamCap;			// ��λ��ʾ�豸֧�ֵĶ�ý�幦�ܣ�
												// ��һλ��ʾ֧��������
												// �ڶ�λ��ʾ֧�ָ�����1
											    // ����λ��ʾ֧�ָ�����2
												// ����λ��ʾ֧�ָ�����3
												// ����λ��ʾ֧��jpgץͼ
	DWORD				dwImageSizeMask_Assi[3][64];// ��ʾ������Ϊ���ֱ���ʱ��֧�ֵĸ������ֱ�������, �����е�0,1,2Ԫ�طֱ����������1,2,3
	DWORD				dwMaxEncodePower;		// DSP֧�ֵ���߱������� 
	WORD				wMaxSupportChannel;		// ÿ��DSP֧�����������Ƶͨ���� 
	WORD				wChannelMaxSetSync;		// DSPÿͨ���������������Ƿ�ͬ����0����ͬ����1��ͬ��
	BYTE				bMaxFrameOfImageSize[32];// ��ͬ�ֱ����µ����ɼ�֡�ʣ���dwVideoStandardMask��λ��Ӧ
	BYTE				bEncodeCap;				// ��־������ʱҪ����������������������ò�����Ч��
												// 0���������ı�������+�������ı������� <= �豸�ı���������
												// 1���������ı�������+�������ı������� <= �豸�ı���������
												// �������ı������� <= �������ı���������
												// �������ķֱ��� <= �������ķֱ��ʣ�
												// �������͸�������֡�� <= ǰ����Ƶ�ɼ�֡��
												// 2��N5�ļ��㷽��
												// �������ķֱ��� <= �������ķֱ���
												// ��ѯ֧�ֵķֱ��ʺ���Ӧ���֡��
	BYTE				btReserve1[3];			// �ֽڶ���

	DWORD				dwExtraStream;			// ��0λ��ʾ������, ������λ���α�ʾ������, ���һλ��ʾ������1,�ڶ��Ǳ�ʾ������2
	DWORD				dwCompression[3];		// ÿһ��ֵ��ʾ��Ӧ�������ı����ʽ֧��
	
	char				reserved[108];
} DHDEV_DSP_ENCODECAP_EX, *LPDHDEV_DSP_ENCODECAP_EX;

// ϵͳ��Ϣ
typedef struct 
{
	DWORD				dwSize;
	/* �������豸��ֻ������ */
	DH_VERSION_INFO		stVersion;
	DH_DSP_ENCODECAP	stDspEncodeCap;			// DSP��������
	BYTE				szDevSerialNo[DH_DEV_SERIALNO_LEN];	// ���к�
	BYTE				byDevType;				// �豸���ͣ���ö��DHDEV_DEVICE_TYPE
	BYTE				szDevType[DH_DEV_TYPE_LEN];	// �豸��ϸ�ͺţ��ַ�����ʽ������Ϊ��
	BYTE				byVideoCaptureNum;		// ��Ƶ������
	BYTE				byAudioCaptureNum;		// ��Ƶ������
	BYTE				byTalkInChanNum;		// �Խ�����ӿ�����
	BYTE				byTalkOutChanNum;		// �Խ�����ӿ�����
	BYTE				byDecodeChanNum;		// NSP
	BYTE				byAlarmInNum;			// �����������
	BYTE				byAlarmOutNum;			// �����������
	BYTE				byNetIONum;				// �������
	BYTE				byUsbIONum;				// USB������
	BYTE				byIdeIONum;				// IDE����
	BYTE				byComIONum;				// ��������
	BYTE				byLPTIONum;				// ��������
	BYTE				byVgaIONum;				// NSP
	BYTE				byIdeControlNum;		// NSP
	BYTE				byIdeControlType;		// NSP
	BYTE				byCapability;			// NSP����չ����
	BYTE				byMatrixOutNum;			// ��Ƶ�����������
	/* �������豸�Ŀ�д���� */
	BYTE				byOverWrite;			// Ӳ����������ʽ(���ǡ�ֹͣ)
	BYTE				byRecordLen;			// ¼��������
	BYTE				byDSTEnable;			// �Ƿ�ʵ������ʱ 1-ʵ�� 0-��ʵ��
	WORD				wDevNo;					// �豸��ţ�����ң��
	BYTE				byVideoStandard;		// ��Ƶ��ʽ:0-PAL,1-NTSC
	BYTE				byDateFormat;			// ���ڸ�ʽ
	BYTE				byDateSprtr;			// ���ڷָ��(0��"."��1��"-"��2��"/")
	BYTE				byTimeFmt;				// ʱ���ʽ (0-24Сʱ��1��12Сʱ)
	BYTE				byLanguage;				// ö��ֵ���DH_LANGUAGE_TYPE
} DHDEV_SYSTEM_ATTR_CFG, *LPDHDEV_SYSTEM_ATTR_CFG;

// �޸��豸���÷�����Ϣ
typedef struct
{
	DWORD				dwType;					// ����(��GetDevConfig��SetDevConfig������)
	WORD				wResultCode;			// �����룻0���ɹ���1��ʧ�ܣ�2�����ݲ��Ϸ���3����ʱ�޷����ã�4��û��Ȩ��
	WORD   				wRebootSign;			// ������־��0������Ҫ������1����Ҫ��������Ч
	DWORD				dwReserved[2];			// ����	
} DEV_SET_RESULT;

// ������ӻ�طŵĴ��󷵻���Ϣ
typedef struct
{
	DWORD              dwResultCode;            // ���󷵻��룬1:��Ȩ�ޣ�2:�豸��֧�ִ˲�����3:��Դ���㣬4:�豸�޷���ȡ��ǰ��������, 11:��ʾ�߼��û���ռ�ͼ��û���Դ, 12:��ֹ����
	LLONG               lPlayHandle;             // ��Ӧ���ֵ
	BYTE               byReserved[32];            // �����ֽ�                         
}DEV_PLAY_RESULT;

//DST(����ʱ)����
typedef struct  
{
	int					nYear;					// ��[200 - 2037]
	int					nMonth;					// ��[1 - 12]
	int					nHour;					// Сʱ [0 - 23]
	int					nMinute;				// ���� [0 - 59]
	int					nWeekOrDay;				// [-1 - 4]0:��ʾʹ�ð����ڼ���ķ���
												// 1: ���ܼ���: ��һ��,2: �ڶ���,3: ������,4: ������,-1: ���һ��
	union
	{
		int				iWeekDay;				// ��[0 - 6](nWeekOrDay�����ܼ���ʱ)0:������, 1:����һ, 2:���ڶ�,3:������,4:������,5:������,6:������
		int				iDay;					// ����[1 - 31] (nWeekOrDay�������ڼ���)
	};
	
	DWORD				dwReserved[8];			// ����	
}DH_DST_POINT;

typedef struct  
{
	DWORD				dwSize;
	int					nDSTType;				// ����ʱ��λ��ʽ 0:�����ڶ�λ��ʽ, 1:���ܶ�λ��ʽ
	DH_DST_POINT        stDSTStart;             // ��ʼ����ʱ
	DH_DST_POINT        stDSTEnd;				// ��������ʱ
	DWORD				dwReserved[16];			// ����	
}DHDEV_DST_CFG;


// �Զ�ά������
typedef struct
{
	DWORD				dwSize;
	BYTE				byAutoRebootDay;		// �Զ�������0���Ӳ�, 1��ÿ�죬2��ÿ�����գ�3��ÿ����һ��......
	BYTE				byAutoRebootTime;		// 0��0:00��1��1:00��......23��23:00
	BYTE				byAutoDeleteFilesTime;	// �Զ�ɾ���ļ���0���Ӳ���1��24H��2��48H��3��72H��4��96H��5��ONE WEEK��6��ONE MONTH
	BYTE				reserved[13];			// ����λ
} DHDEV_AUTOMT_CFG;

// ������Ӳ����Ϣ
typedef struct  
{
	DWORD				dwSize;										// �ṹ���С,�����Ա����ʼ��
	DWORD				dwVolume;									// Ӳ������
	DWORD				dwFreeSpace;								// Ӳ�̵�ʣ��ռ�, ��λMB(B��ʾ�ֽ�)
	BYTE				byModle[DH_MAX_HARDDISK_TYPE_LEN];			// Ӳ���ͺ�
	BYTE				bySerialNumber[DH_MAX_HARDDISK_SERIAL_LEN];	// Ӳ�����к�
}DHDEV_VEHICLE_DISK;

// ������ص�3Gģ����Ϣ�����֧��DH_MAX_SIM_NUM��ģ��
typedef struct
{
	DWORD				dwSize;						// �ṹ���С,�����Ա����ʼ��
	BYTE				szIMSI[DH_MAX_SIM_LEN];		// SIM����ֵ����460012002778636 ��ǰ3λΪ���Ҵ���MCC��4-6λΪ�������MNC,�����Ϊ�ƶ��û����ݱ�ʶMSIN���ܹ����ᳬ��15���ַ�
	BYTE				szMDN[DH_MAX_MDN_LEN];		// SIM��MDNֵ
}DHDEV_VEHICLE_3GMODULE;

// ���صĻ�����Ϣ
typedef struct 
{
	DWORD					dwSize;								// �ṹ���С,�����Ա����ʼ��
	DWORD					dwSoftwareBuildDate;				// ������������
	char					szVersion[DH_MAX_VERSION_LEN];		// �����汾
	char					szDevSerialNo[DH_DEV_SERIALNO_LEN];	// �������к�
	char					szDevType[DH_DEV_TYPE_LEN];			// �豸��ϸ�ͺţ��ַ�����ʽ������Ϊ��
	DWORD					dwDiskNum;							// Ӳ�̸���
	DHDEV_VEHICLE_DISK		stuHarddiskInfo[DH_MAX_DISKNUM];	// Ӳ�������Ϣ
	DWORD					dw3GModuleNum;						// 3Gģ�����
	DHDEV_VEHICLE_3GMODULE	stu3GModuleInfo[DH_MAX_SIM_NUM];	// 3Gģ�������Ϣ
}DHDEV_VEHICLE_INFO;

// ����ӿڣ����֧��DH_MAX_NETINTERFACE_NUM������
typedef struct tagDHDEV_NETINTERFACE_INFO
{
	int             dwSize;
	BOOL			bValid;								// �Ƿ���Ч
	BOOL			bVirtual;							// �Ƿ���������
	int             nSpeed;								// ���������ٶ�(Mbps)
	int             nDHCPState;							// 0-δʹ��, 1-���ڻ�ȡ, 2-��ȡ�ɹ�
	char			szName[DH_NETINTERFACE_NAME_LEN];	// ��������
	char			szType[DH_NETINTERFACE_TYPE_LEN];	// ��������
	char			szMAC[DH_MACADDR_LEN];			    // MAC��ַ
	char			szSSID[DH_MAX_SSID_LEN];			// SSID, ֻ������������Ч(szType == "Wireless")
	char            szConnStatus[DH_MAX_CONNECT_STATUS_LEN]; // Wifi��3G������״̬��"Inexistence" : ���粻���� "Down"���ر� "Disconn"��δ���� "Connecting"�������� "Connected"�� ������
	int             nSupportedModeNum;                  // ʵ��3G֧�ֵ�����ģʽ����
	char            szSupportedModes[DH_MAX_MODE_NUM][DH_MAX_MODE_LEN];// 3G֧�ֵ�����ģʽ	"TD-SCDMA", "WCDMA", "CDMA1x", "EDGE", "EVDO"
} DHDEV_NETINTERFACE_INFO;

//-----------------------------ͼ��ͨ������-------------------------------

// ʱ��νṹ															    
typedef struct 
{
	BOOL				bEnable;				// ����ʾ¼��ʱ���ʱ����λ��ʾ�ĸ�ʹ�ܣ��ӵ�λ����λ�ֱ��ʾ����¼�󡢱���¼����ͨ¼�󡢶���ͱ���ͬʱ������¼��
	int					iBeginHour;
	int					iBeginMin;
	int					iBeginSec;
	int					iEndHour;
	int					iEndMin;
	int					iEndSec;
} DH_TSECT, *LPDH_TSECT;

// ���򣻸��߾ఴ����8192�ı���
typedef struct {
   long					left;
   long					top;
   long					right;
   long					bottom;
} DH_RECT, *LPDH_RECT;

// ��ά�ռ��
typedef struct {
   short					nx;
   short					ny;
} DH_POINT, *LPDH_POINT;

// ��������߶�����Ϣ
typedef struct
{
	int        nPointNum;                           // ������
	DH_POINT   stuPoints[DH_MAX_DETECT_REGION_NUM];     // ������Ϣ
}DH_POLY_POINTS;

// OSD���Խṹ
typedef struct  tagENCODE_WIDGET
{
	DWORD				rgbaFrontground;		// �����ǰ�������ֽڱ�ʾ���ֱ�Ϊ�졢�̡�����͸����
	DWORD				rgbaBackground;			// ����ı��������ֽڱ�ʾ���ֱ�Ϊ�졢�̡�����͸����
	DH_RECT				rcRect;					// λ��
	BYTE				bShow;					// ��ʾʹ��
	BYTE                bExtFuncMask;           // ��չʹ�� ������ 
                                                // bit0 ��ʾ�Ƿ���ʾ���ڼ���0-����ʾ 1-��ʾ 
	BYTE				byReserved[2];
} DH_ENCODE_WIDGET, *LPDH_ENCODE_WIDGET;

// ͨ������Ƶ����
typedef struct 
{
	// ��Ƶ����
	BYTE				byVideoEnable;			// ��Ƶʹ�ܣ�1���򿪣�0���ر�
	BYTE				byBitRateControl;		// �������ƣ����ճ���"��������"����
	BYTE				byFramesPerSec;			// ֡��
	BYTE				byEncodeMode;			// ����ģʽ�����ճ���"����ģʽ"����
	BYTE				byImageSize;			// �ֱ��ʣ����ճ���"�ֱ���"����
	BYTE				byImageQlty:7;			// ��byImageQlty������չ����byImageQltyΪ0������֮ǰ��1-6���Σ���//ImgQltyTypeΪ1����ImgQlty��ΧΪ0~100
	BYTE                byImageQltyType:1;       
	WORD				wLimitStream;			// ����������
	// ��Ƶ����
	BYTE				byAudioEnable;			// ��Ƶʹ�ܣ�1���򿪣�0���ر�
	BYTE				wFormatTag;				// ��Ƶ��������: 0:G711A,1:PCM,2:G711U,3:AMR,4:AAC
	WORD				nChannels;				// ������
	WORD				wBitsPerSample;			// �������	
	BYTE				bAudioOverlay;			// ��Ƶ����ʹ��
    BYTE				bH264ProfileRank;       // H.264 Profile�ȼ�(������ģʽΪH264ʱ�˲���ֵ��Ч),����ö������EM_H264_PROFILE_RANK����0��������ǰ����ʾ���ֶ���Ч������Ҫ���Ǽ���
	DWORD				nSamplesPerSec;			// ������
	BYTE				bIFrameInterval;		// I֡���֡��������������I֮֡���P֡������0-149
	BYTE				bScanMode;				// NSP
	BYTE				bReserved_3;
	BYTE				bReserved_4;
} DH_VIDEOENC_OPT, *LPDH_VIDEOENC_OPT;

// ������ɫ����
typedef struct 
{
	DH_TSECT			stSect;
	BYTE				byBrightness;			// ���ȣ�0-100
	BYTE				byContrast;				// �Աȶȣ�0-100
	BYTE				bySaturation;			// ���Ͷȣ�0-100
	BYTE				byHue;					// ɫ�ȣ�0-100
	BYTE				byGainEn;				// ����ʹ��
	BYTE				byGain;					// ���棻0-100
	BYTE				byGamma;                // ٤��ֵ 0-100
	BYTE				byReserved[1];
} DH_COLOR_CFG, *LPDH_COLOR_CFG;

// ͼ��ͨ�����Խṹ��
typedef struct 
{
	//DWORD				dwSize;
	WORD				dwSize;
	BYTE				bNoise;
	BYTE				bMode;                 // (������������)ģʽһ(��������):¼��ֱ��ʲ���4·D1��֡��2fps������128kbps(ÿСʱ225MB)
		                                       // ģʽ��(��������):¼��ֱ��ʲ���4·CIF��֡��12fps������256kbps(ÿСʱ550MB)
		                                       // ģʽ��(�Զ���)¼��ֱ��ʿ������û��Զ��壬�޶��������Ϊ4CIF/25fps
	char				szChannelName[DH_CHAN_NAME_LEN];
	DH_VIDEOENC_OPT		stMainVideoEncOpt[DH_REC_TYPE_NUM];
	DH_VIDEOENC_OPT		stAssiVideoEncOpt[DH_N_ENCODE_AUX];		
	DH_COLOR_CFG		stColorCfg[DH_N_COL_TSECT];
	DH_ENCODE_WIDGET	stTimeOSD;
	DH_ENCODE_WIDGET	stChannelOSD;
	DH_ENCODE_WIDGET	stBlindCover[DH_N_COVERS];	// �������ڵ�
	BYTE				byBlindEnable;			// �����ڸǿ��أ�0x00����ʹ���ڸǣ�0x01�����ڸ��豸����Ԥ����0x10�����ڸ�¼������Ԥ����0x11�����ڸ�
	BYTE				byBlindMask;			// �����ڸ����룻��һλ���豸����Ԥ�����ڶ�λ��¼��(������Ԥ��) */
	BYTE				bVolume;				// ������ֵ(0~100�ɵ�)
	BYTE				bVolumeEnable;			// ������ֵʹ��
} DHDEV_CHANNEL_CFG, *LPDHDEV_CHANNEL_CFG;

// Ԥ��ͼ�����
typedef struct 
{
	DWORD				dwSize;
	DH_VIDEOENC_OPT		stPreView;
	DH_COLOR_CFG		stColorCfg[DH_N_COL_TSECT];
}DHDEV_PREVIEW_CFG;

// ץͼ��������
typedef struct _config_snap_control
{
	BYTE               bySnapState[32];           // ÿ��ͨ����Ӧץͼ���� 0:�Զ�(���ʾ�Ƿ�ץͼ�����������ú��¼�����); 1:ץͼ����; 2:ץͼ�ر�
    BYTE               byReserved[480];
}DHDEV_SNAP_CONTROL_CFG;

enum _gps_mode
{
	GPS_OR_GLONASS_MODE,	// GPS��GLONASS���ģʽ(ģ�鶨λ���ݴ�GPS��GLONASS�����л�ȡ����������Դ���ĸ�ϵͳ����ȷ��,����ģ���ڲ��Զ��ᴦ��)
	GLONASS_MODE,			// GLONASSģʽ(��ģ��Ķ�λ���ݴӶ���˹��GLONASS��λϵͳ�л�ȡ)
	GPS_MODE,				// GPSģʽ(��ģ��Ķ�λ���ݴ�������GPSϵͳ�л�ȡ) 
};
// DH_DEV_GPS_MODE_CFG ���ýṹ
typedef struct tagDHDEV_GPS_MODE_CFG
{
	BYTE				byGPSMode; // GPS��λģʽ����
	BYTE				byRev[255];
}DHDEV_GPS_MODE_CFG;

// ͼƬ�ϴ�������Ϣ DH_DEV_SNAP_UPLOAD_CFG ���ýṹ
typedef struct tagDHDEV_SNAP_UPLOAD_CFG
{
	int					nUploadInterval;		//��ʱץͼͼƬ�ϴ��������λ��
	BYTE				byReserved[252];	
}DHDEV_SNAP_UPLOAD_CFG;


// DHDEV_SPEED_LIMIT_CFG ���ýṹ
typedef struct tagDHDEV_SPEED_LIMIT_CFG
{
	BYTE       byEnable;         // ����ʹ��1��ʹ�ܣ�0����ʹ�ܡ�
	BYTE       byReserved1;      // �����ֶ�
	WORD       wMaxSpeed;       // �ٶ�����ֵ����λKM/H 0��ʾ������,����0��ʾ����
	WORD       wMinSpeed;       // �ٶ�����ֵ����λKM/H 0��ʾ������,����0��ʾ����
	BYTE       byReserved2[122]; // �����ֶ�
}DHDEV_SPEED_LIMIT_CFG;

// ����·������
typedef struct
{
	BOOL		bEnable;						// ʹ��
	char		szSSID[36];						// SSID����
	BOOL		bHideSSID;						// �Ƿ�����SSID
	char		szIP[DH_MAX_IPADDR_LEN];		// IP
	char		szSubMark[DH_MAX_IPADDR_LEN];	// ��������
	char		szGateWay[DH_MAX_IPADDR_LEN];	// ����
	char		szCountry[32];					// ����, DefaultĬ�ϲ�ָ�������������б��ο�����·��������Ϣ
	int			nSafeType;						// ��Ȩģʽ: 1-������; 2-WEPģʽ; 2-WPA-PSKģʽ; 3-WPA2-PSKģʽ
	int			nEncryption;					// ���ܷ�ʽ: WEPģʽ(1-�Զ� 2-���� 3-����); WPA-PSKģʽ/WPA2-PSKģʽ(4-TKIP 5-AES)
	char		szKey[32];						// ������Կ
	int			nChannel;						// �ŵ�, ��Ч�ŵ��б��ο�����·��������Ϣ
	BOOL		bAutoChannelSelect;				// �Զ�ѡ���ŵ�	
}DHDEV_WIRELESS_ROUTING_CFG;

//-------------------------------��������---------------------------------

// ���ڻ�������
typedef struct
{
	BYTE				byDataBit;				// ����λ��0��5��1��6��2��7��3��8
	BYTE				byStopBit;				// ֹͣλ��0��1λ��1��1.5λ��2��2λ
	BYTE				byParity;				// У��λ��0����У�飬1����У�飻2��żУ��; 3:��־У��; 4:��У��
	BYTE				byBaudRate;				// �����ʣ�0��300��1��600��2��1200��3��2400��4��4800��
												// 5��9600��6��19200��7��38400��8��57600��9��115200
} DH_COMM_PROP;

// 485����������
typedef struct
{ 
	DH_COMM_PROP		struComm;
	BYTE				wProtocol;				// Э�����ͣ���Ӧ"Э�����б�"�±�
	BYTE				bPTZType;				// 0-���ݣ�������̨ 1-Զ��������̨,ͨ��������ѯ(��DEV_ENCODER_CFG)��
	BYTE				wDecoderAddress;		// ��������ַ��0 - 255
	BYTE 				byMartixID;				// �����
} DH_485_CFG;

// 232��������
typedef struct
{
	DH_COMM_PROP		struComm;
	BYTE				byFunction;				// ���ڹ��ܣ���Ӧ"�������б�"�±�
	BYTE				byReserved[3];
} DH_RS232_CFG;

// �������ýṹ��
typedef struct
{
	DWORD				dwSize;

	DWORD				dwDecProListNum;				// ������Э�����
	char				DecProName[DH_MAX_DECPRO_LIST_SIZE][DH_MAX_NAME_LEN]; // Э�����б�
	DH_485_CFG			stDecoder[DH_MAX_DECODER_NUM];	// ����������ǰ����

	DWORD				dw232FuncNameNum;		// 232���ܸ���
	char				s232FuncName[DH_MAX_232FUNCS][DH_MAX_NAME_LEN];	// �������б�
	DH_RS232_CFG		st232[DH_MAX_232_NUM];	// ��232���ڵ�ǰ����
} DHDEV_COMM_CFG;

// ��չ�������ýṹ��
typedef struct
{
	DWORD				dwSize;
	
	DWORD				dwDecProListNum;				// ������Э�����
	char				DecProName[DH_MAX_DECPRO_LIST_SIZE][DH_MAX_NAME_LEN]; // Э�����б�
	DH_485_CFG			stDecoder[DH_MAX_DECODER_NUM];	// ����������ǰ����
	
	DWORD				dw232FuncNameNum;		// 232���ܸ���
	char				s232FuncName[DH_MAX_232FUNCS][DH_MAX_NAME_LEN];	// �������б�
	DWORD               dw232ComNum;            // 232���ڸ���   
	DH_RS232_CFG		st232[DH_MAX_232_NUM_EX];	// ��232���ڵ�ǰ����
} DHDEV_COMM_CFG_EX;

// ����״̬
typedef struct
{
	unsigned int		uBeOpened;
	unsigned int		uBaudRate;
	unsigned int		uDataBites;
	unsigned int		uStopBits;
	unsigned int		uParity;
	BYTE				bReserved[32];
} DH_COMM_STATE;

//-------------------------------¼������---------------------------------

// ��ʱ¼��
typedef struct 
{
	DWORD				dwSize;
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];
	BYTE				byPreRecordLen;			// Ԥ¼ʱ�䣬��λ��s��0��ʾ��Ԥ¼
	BYTE				byRedundancyEn;			// ¼�����࿪��
	BYTE                byRecordType;           // ¼���������ͣ�0-������ 1-������1 2-������2 3-������3
	BYTE				byReserved;
} DHDEV_RECORD_CFG, *LPDH_RECORD_CFG;

// NTP����
typedef struct  
{
	BOOL				bEnable;				//	�Ƿ�����
	int					nHostPort;				//	NTP������Ĭ�϶˿�Ϊ123
	char				szHostIp[32];			//	����IP
	char				szDomainName[128];		//	����
	int					nType;					//	�������ã�0����ʾIP��1����ʾ������2����ʾIP������
	int					nUpdateInterval;		//	����ʱ��(����)
	int					nTimeZone;				//	��DH_TIME_ZONE_TYPE
	char				reserved[128];
} DHDEV_NTP_CFG;

// FTP�ϴ�����
typedef struct
{
	struct
	{
		DH_TSECT		struSect;				// ��ʱ����ڵġ�ʹ�ܡ���Ч���ɺ���
		BOOL			bMdEn;					// �ϴ���̬���¼��
		BOOL			bAlarmEn;				// �ϴ��ⲿ����¼��
		BOOL			bTimerEn;				// �ϴ���ͨ��ʱ¼��
		DWORD			dwRev[4];
	} struPeriod[DH_TIME_SECTION];
} DH_FTP_UPLOAD_CFG;

typedef struct
{
	DWORD				dwSize;
	BOOL				bEnable;							// �Ƿ�����
	char				szHostIp[DH_MAX_IPADDR_LEN];		// ����IP
	WORD				wHostPort;							// �����˿�
	char				szDirName[DH_FTP_MAX_PATH];			// FTPĿ¼·��
	char				szUserName[DH_FTP_USERNAME_LEN];	// �û���
	char				szPassword[DH_FTP_PASSWORD_LEN];	// ����
	int					iFileLen;							// �ļ�����
	int					iInterval;							// �����ļ�ʱ����(1~600),��λ�� 
	DH_FTP_UPLOAD_CFG	struUploadCfg[DH_MAX_CHANNUM][DH_N_WEEKS];
	char 				protocol;							// 0-FTP 1-SMB 2-NFS��3-ISCSI
	char				NASVer;								// ����洢�������汾0=�ϵ�FTP(��������ʾʱ���)��1=NAS�洢(����������ʱ���)
	DWORD				dwFunctionMask;						// �����������룬��λ��ʾ����16λ(����洢)���α�ʾFTP��SMB��NFS��ISCSI, ��16λ(���ش洢)����ΪDISK��U
	BYTE                bDataType;                          // ��������, 0-��������, 1-��Ƶ, 2-ͼƬ
	BYTE 				reserved[123];
} DHDEV_FTP_PROTO_CFG;

// FTP�ϴ���չ����(֧��ͨ����������FTP�洢·�������洢ͼƬ����)
typedef struct 
{
    int            nMaxPictures;                             // �ܴ洢������ÿһ��ͨ���ļ����е�ͼƬ�����������ƣ�
	                                                         // �������ƾ͸����ϵ��ļ�,0:��ʾ�����ƣ�д��Ϊֹ
    char           szPreChannelName[DH_FTP_MAX_SUB_PATH];    // ͼƬ�ļ���
    char           szFTPChannelPath[DH_FTP_MAX_SUB_PATH];    // ftp�洢·��(�洢��Ŀ¼)
    char           szRev[128];                               // �����ֶ�
}DHDEV_FTP_CHANNEL_CFG; 


typedef struct 
{ 
	DHDEV_FTP_PROTO_CFG       stuFtpNormalSet;                             // FTPԭ�й��ܣ���չͨ����
	DHDEV_FTP_CHANNEL_CFG     stuFtpChannelSet[DH_MAX_CHANNUM];           // FTP��չ����
	char                      szRev[128];                                 // �����ֶ�
}DHDEV_FTP_PROTO_CFG_EX;

//-------------------------------��������---------------------------------

// ��̫������
typedef struct 
{
	char				sDevIPAddr[DH_MAX_IPADDR_LEN];	// DVR IP ��ַ
	char				sDevIPMask[DH_MAX_IPADDR_LEN];	// DVR IP ��ַ����
	char				sGatewayIP[DH_MAX_IPADDR_LEN];	// ���ص�ַ

	/*
	 * 1��10Mbps ȫ˫��
	 * 2��10Mbps ����Ӧ
	 * 3��10Mbps ��˫��
	 * 4��100Mbps ȫ˫��
	 * 5��100Mbps ����Ӧ
	 * 6��100Mbps ��˫��
	 * 7������Ӧ
	 */
	// Ϊ����չ��DWORD����ĸ�
	BYTE				dwNetInterface;			// NSP
	BYTE				bTranMedia;				// 0�����ߣ�1������
	BYTE				bValid;					// ��λ��ʾ����һλ��1����Ч 0����Ч���ڶ�λ��0��DHCP�ر� 1��DHCPʹ�ܣ�����λ��0����֧��DHCP 1��֧��DHCP
	BYTE				bDefaultEth;			// �Ƿ���ΪĬ�ϵ����� 1��Ĭ�� 0����Ĭ��
	char				byMACAddr[DH_MACADDR_LEN];	// MAC��ַ��ֻ��
} DH_ETHERNET; 

// Զ����������
typedef struct 
{
	BYTE				byEnable;				// ����ʹ��
	BYTE				byAssistant;            // Ŀǰֻ����PPPoE���������ã�0���������������ţ�1�������������ϲ���
	WORD				wHostPort;				// Զ������ �˿�
	char				sHostIPAddr[DH_MAX_IPADDR_LEN];		// Զ������ IP ��ַ		
	char				sHostUser[DH_MAX_HOST_NAMELEN];		// Զ������ �û���
	char				sHostPassword[DH_MAX_HOST_PSWLEN];	// Զ������ ����
} DH_REMOTE_HOST;

// �ʼ�����
typedef struct 
{
	char				sMailIPAddr[DH_MAX_IPADDR_LEN];		// �ʼ�������IP��ַ
	WORD				wMailPort;							// �ʼ��������˿�
	WORD				wReserved;							// ����
	char				sSenderAddr[DH_MAX_MAIL_ADDR_LEN];	// ���͵�ַ
	char				sUserName[DH_MAX_NAME_LEN];			// �û���
	char				sUserPsw[DH_MAX_NAME_LEN];			// �û�����
	char				sDestAddr[DH_MAX_MAIL_ADDR_LEN];	// Ŀ�ĵ�ַ
	char				sCcAddr[DH_MAX_MAIL_ADDR_LEN];		// ���͵�ַ
	char				sBccAddr[DH_MAX_MAIL_ADDR_LEN];		// ������ַ
	char				sSubject[DH_MAX_MAIL_SUBJECT_LEN];	// ����
} DH_MAIL_CFG;

// �������ýṹ��
typedef struct
{ 
	DWORD				dwSize; 

	char				sDevName[DH_MAX_NAME_LEN];	// �豸������

	WORD				wTcpMaxConnectNum;		// TCP���������
	WORD				wTcpPort;				// TCP֡���˿�
	WORD				wUdpPort;				// UDP�����˿�
	WORD				wHttpPort;				// HTTP�˿ں�
	WORD				wHttpsPort;				// HTTPS�˿ں�
	WORD				wSslPort;				// SSL�˿ں�
	DH_ETHERNET			stEtherNet[DH_MAX_ETHERNET_NUM];	// ��̫����

	DH_REMOTE_HOST		struAlarmHost;			// ����������
	DH_REMOTE_HOST		struLogHost;			// ��־������
	DH_REMOTE_HOST		struSmtpHost;			// SMTP������
	DH_REMOTE_HOST		struMultiCast;			// �ಥ��
	DH_REMOTE_HOST		struNfs;				// NFS������
	DH_REMOTE_HOST		struPppoe;				// PPPoE������
	char				sPppoeIP[DH_MAX_IPADDR_LEN]; // PPPoEע�᷵�ص�IP
	DH_REMOTE_HOST		struDdns;				// DDNS������
	char				sDdnsHostName[DH_MAX_HOST_NAMELEN];	// DDNS������
	DH_REMOTE_HOST		struDns;				// DNS������
	DH_MAIL_CFG			struMail;				// �ʼ�����
} DHDEV_NET_CFG;

// ��̫����չ����
typedef struct 
{
	char				sDevIPAddr[DH_MAX_IPADDR_LEN];	// DVR IP ��ַ
	char				sDevIPMask[DH_MAX_IPADDR_LEN];	// DVR IP ��ַ����
	char				sGatewayIP[DH_MAX_IPADDR_LEN];	// ���ص�ַ

	/*
	 * 1��10Mbps ȫ˫��
	 * 2��10Mbps ����Ӧ
	 * 3��10Mbps ��˫��
	 * 4��100Mbps ȫ˫��
	 * 5��100Mbps ����Ӧ
	 * 6��100Mbps ��˫��
	 * 7������Ӧ
	 */
	// Ϊ����չ��DWORD����ĸ�
	BYTE				dwNetInterface;			// NSP
	BYTE				bTranMedia;				// 0�����ߣ�1������
	BYTE				bValid;					// ��λ��ʾ����һλ��1����Ч 0����Ч���ڶ�λ��0��DHCP�ر� 1��DHCPʹ�ܣ�����λ��0����֧��DHCP 1��֧��DHCP
	BYTE				bDefaultEth;			// �Ƿ���ΪĬ�ϵ����� 1��Ĭ�� 0����Ĭ��
	char				byMACAddr[DH_MACADDR_LEN];	// MAC��ַ��ֻ��
	BYTE                bMode;                  // ��������ģʽ, 0:��ģʽ, 1:���ؾ���ģʽ, 2:��ַģʽ, 3:�ݴ�ģʽ
	BYTE                bReserved[31];          // �����ֽ�   
} DH_ETHERNET_EX; 

// ��չ�������ýṹ��
typedef struct
{ 
	DWORD				dwSize; 
	
	char				sDevName[DH_MAX_NAME_LEN];	// �豸������
	
	WORD				wTcpMaxConnectNum;		// TCP���������
	WORD				wTcpPort;				// TCP֡���˿�
	WORD				wUdpPort;				// UDP�����˿�
	WORD				wHttpPort;				// HTTP�˿ں�
	WORD				wHttpsPort;				// HTTPS�˿ں�
	WORD				wSslPort;				// SSL�˿ں�
	int                 nEtherNetNum;           // ��̫������
	DH_ETHERNET_EX		stEtherNet[DH_MAX_ETHERNET_NUM_EX];	// ��̫����
	DH_REMOTE_HOST		struAlarmHost;			// ����������
	DH_REMOTE_HOST		struLogHost;			// ��־������
	DH_REMOTE_HOST		struSmtpHost;			// SMTP������
	DH_REMOTE_HOST		struMultiCast;			// �ಥ��
	DH_REMOTE_HOST		struNfs;				// NFS������
	DH_REMOTE_HOST		struPppoe;				// PPPoE������
	char				sPppoeIP[DH_MAX_IPADDR_LEN]; // PPPoEע�᷵�ص�IP
	DH_REMOTE_HOST		struDdns;				// DDNS������
	char				sDdnsHostName[DH_MAX_HOST_NAMELEN];	// DDNS������
	DH_REMOTE_HOST		struDns;				// DNS������
	DH_MAIL_CFG			struMail;				// �ʼ�����
	BYTE                bReserved[128];         // �����ֽ�
} DHDEV_NET_CFG_EX;

// ��ddns���ýṹ��
typedef struct
{
	DWORD				dwId;					// ddns������id��
	BOOL				bEnable;				// ʹ�ܣ�ͬһʱ��ֻ����һ��ddns����������ʹ��״̬
	char				szServerType[DH_MAX_SERVER_TYPE_LEN];	// ���������ͣ�ϣ��..
	char				szServerIp[DH_MAX_DOMAIN_NAME_LEN];		// ������ip��������
	DWORD				dwServerPort;			// �������˿�
	char				szDomainName[DH_MAX_DOMAIN_NAME_LEN];	// dvr��������jeckean.3322.org
	char				szUserName[DH_MAX_HOST_NAMELEN];		// �û���
	char				szUserPsw[DH_MAX_HOST_PSWLEN];			// ����
	char				szAlias[DH_MAX_DDNS_ALIAS_LEN];			// ��������������"dahua inter ddns"
	DWORD				dwAlivePeriod;							// DDNS ����ʱ��
	BYTE				ByMode;									// ����ģʽ:0-�ֶ���������,szDomainName��Ч; 1-Ĭ������szDefaultDomainName��Ч��
	char				szDefaultDomainName[DH_MAX_DEFAULT_DOMAIN_LEN];//Ĭ������,ֻ��
	char				reserved[195];
} DH_DDNS_SERVER_CFG;

typedef struct
{
	DWORD				dwSize;
	DWORD				dwDdnsServerNum;	
	DH_DDNS_SERVER_CFG	struDdnsServer[DH_MAX_DDNS_NUM];	
} DHDEV_MULTI_DDNS_CFG;

// �ʼ����ýṹ��
typedef struct 
{
	char				sMailIPAddr[DH_MAX_DOMAIN_NAME_LEN];	// �ʼ���������ַ(IP��������)
	char				sSubMailIPAddr[DH_MAX_DOMAIN_NAME_LEN];
	WORD				wMailPort;								// �ʼ��������˿�
	WORD				wSubMailPort;
	WORD				wReserved;								// ����
	char				sSenderAddr[DH_MAX_MAIL_ADDR_LEN];		// ���͵�ַ
	char				sUserName[DH_MAX_MAIL_NAME_LEN];		// �û���
	char				sUserPsw[DH_MAX_MAIL_NAME_LEN];			// �û�����
	char				sDestAddr[DH_MAX_MAIL_ADDR_LEN];		// Ŀ�ĵ�ַ
	char				sCcAddr[DH_MAX_MAIL_ADDR_LEN];			// ���͵�ַ
	char				sBccAddr[DH_MAX_MAIL_ADDR_LEN];			// ������ַ
	char				sSubject[DH_MAX_MAIL_SUBJECT_LEN];		// ����
	BYTE				bEnable;								// ʹ��0:false,	1:true
	BYTE				bSSLEnable;								// SSLʹ��
	WORD				wSendInterval;							// ����ʱ����,[0,3600]��
	BYTE				bAnonymous;								// ����ѡ��[0,1], 0��ʾFALSE,1��ʾTRUE.
	BYTE				bAttachEnable;							// ����ʹ��[0,1], 0��ʾFALSE,1��ʾTRUE.
	char				reserved[154];
} DHDEV_MAIL_CFG;

// DNS����������
typedef struct  
{
	char				szPrimaryIp[DH_MAX_IPADDR_LEN];
	char				szSecondaryIp[DH_MAX_IPADDR_LEN];
	char				reserved[256];
} DHDEV_DNS_CFG;

// ¼�����ز�������
typedef struct
{
	DWORD				dwSize;
	BOOL				bEnable;				// TRUE���������أ�FALSE����ͨ����
}DHDEV_DOWNLOAD_STRATEGY_CFG;

// ���紫���������
typedef struct
{
	DWORD				dwSize;
	BOOL				bEnable;
	int					iStrategy;				// 0���������ȣ�1�����������ȣ�2���Զ�
}DHDEV_TRANSFER_STRATEGY_CFG;

// ���õ���ʱ����ز���
typedef struct  
{
	int					nWaittime;				// �ȴ���ʱʱ��(����Ϊ��λ)��Ϊ0Ĭ��5000ms
	int					nConnectTime;			// ���ӳ�ʱʱ��(����Ϊ��λ)��Ϊ0Ĭ��1500ms
	int					nConnectTryNum;			// ���ӳ��Դ�����Ϊ0Ĭ��1��
	int					nSubConnectSpaceTime;	// ������֮��ĵȴ�ʱ��(����Ϊ��λ)��Ϊ0Ĭ��10ms
	int					nGetDevInfoTime;		// ��ȡ�豸��Ϣ��ʱʱ�䣬Ϊ0Ĭ��1000ms
	int					nConnectBufSize;		// ÿ�����ӽ������ݻ����С(�ֽ�Ϊ��λ)��Ϊ0Ĭ��250*1024
	int					nGetConnInfoTime;		// ��ȡ��������Ϣ��ʱʱ��(����Ϊ��λ)��Ϊ0Ĭ��1000ms
	int                 nSearchRecordTime;      // ��ʱ���ѯ¼���ļ��ĳ�ʱʱ��(����Ϊ��λ),Ϊ0Ĭ��Ϊ3000ms
	int                 nsubDisconnetTime;      // ��������Ӷ��ߵȴ�ʱ��(����Ϊ��λ)��Ϊ0Ĭ��Ϊ60000ms
	BYTE				byNetType;				// ��������, 0-LAN, 1-WAN
	BYTE                byPlaybackBufSize;      // �ط����ݽ��ջ����С��MΪ��λ����Ϊ0Ĭ��Ϊ4M
	BYTE                byReserved1[2];         // ����
	int                 nPicBufSize;            // ʵʱͼƬ���ջ����С���ֽ�Ϊ��λ����Ϊ0Ĭ��Ϊ2*1024*1024
	BYTE				bReserved[4];			// �����ֶ��ֶ�
} NET_PARAM;

// ��ӦCLIENT_SearchDevices�ӿ�
typedef struct 
{
	char				szIP[DH_MAX_IPADDR_LEN];		// IP
	int					nPort;							// tcp�˿�
	char				szSubmask[DH_MAX_IPADDR_LEN];	// ��������
	char				szGateway[DH_MAX_IPADDR_LEN];	// ����
	char				szMac[DH_MACADDR_LEN];			// MAC��ַ
	char				szDeviceType[DH_DEV_TYPE_LEN];	// �豸����
	BYTE                byManuFactory;				    // Ŀ���豸����������,����ο�EM_IPC_TYPE��
	BYTE                byIPVersion;                    // 4: IPv4, szXXXΪ����ַ�����ʽ;  6:IPv6, szXXXΪ128λ(16�ֽ�)��ֵ��ʽ
	BYTE				bReserved[30];					// �����ֽ�
} DEVICE_NET_INFO;

// ��ӦCLIENT_StartSearchDevices�ӿ�
typedef struct 
{
	int                 iIPVersion;                      // 4 for IPV4, 6 for IPV6
	char				szIP[64];		                 // IP IPV4����"192.168.0.1" IPV6����"2008::1/64"
	int				    nPort;		                     // tcp�˿�
	char				szSubmask[64];	                 // �������� IPV6����������
	char				szGateway[64];	                 // ����
	char				szMac[DH_MACADDR_LEN];           // MAC��ַ
	char				szDeviceType[DH_DEV_TYPE_LEN];	 // �豸����
	BYTE                byManuFactory;				     // Ŀ���豸����������,����ο�EM_IPC_TYPE��	
	BYTE                byDefinition;                    // 1-���� 2-����
	bool                bDhcpEn;                         // Dhcpʹ��״̬, true-��, false-��
	BYTE                byReserved1;                     // �ֽڶ���
	char                verifyData[88];                  // У������ ͨ���첽�����ص���ȡ(���޸��豸IPʱ���ô���Ϣ����У��)
	char                szSerialNo[DH_DEV_SERIALNO_LEN]; // ���к�
	char                szDevSoftVersion[DH_MAX_URL_LEN];// �豸�����汾��    
    char                szDetailType[DH_DEV_TYPE_LEN];   // �豸�ͺ�
	char                szVendor[DH_MAX_STRING_LEN];     // OEM�ͻ�����
	char                szDevName[DH_MACHINE_NAME_NUM];  // �豸����

	char                szUserName[DH_USER_NAME_LENGTH_EX];  // ��½�豸�û��������޸��豸IPʱ��Ҫ��д��
	char                szPassWord[DH_USER_NAME_LENGTH_EX];  // ��½�豸���루���޸��豸IPʱ��Ҫ��д��
	unsigned short		nHttpPort;							 // HTTP����˿ں�
	WORD                wVideoInputCh;                       // ��Ƶ����ͨ����
	WORD                wRemoteVideoInputCh;                 // Զ����Ƶ����ͨ����
	WORD                wVideoOutputCh;                      // ��Ƶ���ͨ����
	WORD                wAlarmInputCh;                       // ��������ͨ����
	WORD                wAlarmOutputCh;                      // �������ͨ����
	char                cReserved[244];
}DEVICE_NET_INFO_EX;

// ��ӦCLIENT_SearchDevicesByIPs�ӿ�
typedef struct
{
	DWORD               dwSize;                          // �ṹ���С
	int                 nIpNum;                          // ��ǰ������IP����
	char                szIP[DH_MAX_SAERCH_IP_NUM][64];  // �����������IP��Ϣ
}DEVICE_IP_SEARCH_INFO;

// struct SNMP���ýṹ
typedef struct
{
	BOOL                bEnable;                            // SNMPʹ��
	int                 iSNMPPort;                          // SNMP�˿�
	char                szReadCommon[DH_MAX_SNMP_COMMON_LEN];   // ����ͬ��
	char                szWriteCommon[DH_MAX_SNMP_COMMON_LEN];  // д��ͬ��
	char                szTrapServer[64];                   // trap��ַ
	int                 iTrapPort;                          // trap�˿�
	BYTE				bSNMPV1;							// �豸�Ƿ���֧�ְ汾1��ʽ��0��ʹ�ܣ�1ʹ��
	BYTE				bSNMPV2;							// �豸�Ƿ���֧�ְ汾2��ʽ��0��ʹ�ܣ�1ʹ��
	BYTE				bSNMPV3;							// �豸�Ƿ���֧�ְ汾3��ʽ��0��ʹ�ܣ�1ʹ��
	char                szReserve[125];
}DHDEV_NET_SNMP_CFG;

// ISCSI�������ṹ����
typedef struct
{
	char				szServerName[32];				// ����
	union
	{ 
		BYTE	c[4];
		WORD	s[2];
		DWORD	l;
	}					stuIP;							// IP��ַ
	int					nPort;							// �˿ں�
	char				szUserName[32];					// �û���
	char				szPassword[32];					// ����
	BOOL				bAnonymous;						// �Ƿ�������¼
}DHDEV_ISCSI_SERVER;

// ISCSI���ýṹ
typedef struct
{
	BOOL				bEnable;						// ʹ��
	DHDEV_ISCSI_SERVER	stuServer;						// ������
	char				szRemotePath[240];				// Զ��Ŀ¼
	BYTE				reserved[256];
}DHDEV_ISCSI_CFG;

//-------------------------------��������---------------------------------

// ��̨����
typedef struct 
{
	int					iType;
	int					iValue;
} DH_PTZ_LINK, *LPDH_PTZ_LINK;

// ���������ṹ��
typedef struct 
{
	/* ��Ϣ������ʽ������ͬʱ���ִ�����ʽ������
	 * 0x00000001 - �����ϴ�
	 * 0x00000002 - ����¼��
	 * 0x00000004 - ��̨����
	 * 0x00000008 - �����ʼ�
	 * 0x00000010 - ������Ѳ
	 * 0x00000020 - ������ʾ
	 * 0x00000040 - �������
	 * 0x00000080 - Ftp�ϴ�
	 * 0x00000100 - ����
	 * 0x00000200 - ������ʾ
	 * 0x00000400 - ץͼ
	*/

	/* ��ǰ������֧�ֵĴ�����ʽ����λ�����ʾ */
	DWORD				dwActionMask;

	/* ������������λ�����ʾ�����嶯������Ҫ�Ĳ����ڸ��Ե����������� */
	DWORD				dwActionFlag;
	
	/* �������������ͨ�������������������Ϊ1��ʾ��������� */ 
	BYTE				byRelAlarmOut[DH_MAX_ALARMOUT_NUM];
	DWORD				dwDuration;				/* ��������ʱ�� */

	/* ����¼�� */
	BYTE				byRecordChannel[DH_MAX_VIDEO_IN_NUM]; /* ����������¼��ͨ����Ϊ1��ʾ������ͨ�� */
	DWORD				dwRecLatch;				/* ¼�����ʱ�� */

	/* ץͼͨ�� */
	BYTE				bySnap[DH_MAX_VIDEO_IN_NUM];
	/* ��Ѳͨ�� */
	BYTE				byTour[DH_MAX_VIDEO_IN_NUM];

	/* ��̨���� */
	DH_PTZ_LINK			struPtzLink[DH_MAX_VIDEO_IN_NUM];
	DWORD				dwEventLatch;			/* ������ʼ��ʱʱ�䣬sΪ��λ����Χ��0~15��Ĭ��ֵ��0 */
	/* �����������������ͨ�������������������Ϊ1��ʾ��������� */ 
	BYTE				byRelWIAlarmOut[DH_MAX_ALARMOUT_NUM];
	BYTE				bMessageToNet;
	BYTE                bMMSEn;                /*���ű���ʹ��*/
	BYTE                bySnapshotTimes;       /*���ŷ���ץͼ���� */
	BYTE				bMatrixEn;				/*!< ����ʹ�� */
	DWORD				dwMatrix;				/*!< �������� */			
	BYTE				bLog;					/*!< ��־ʹ�ܣ�Ŀǰֻ����WTN��̬�����ʹ�� */
	BYTE				bSnapshotPeriod;		/*!<ץͼ֡�����ÿ������֡ץһ��ͼƬ��һ��ʱ����ץ�ĵ���������ץͼ֡���йء�0��ʾ����֡������ץ�ġ�*/
	BYTE                byEmailType;             /*<0��ͼƬ������1��¼�񸽼�>*/
	BYTE                byEmailMaxLength;        /*<����¼��ʱ����󳤶ȣ���λMB>*/
	BYTE                byEmailMaxTime;          /*<������¼��ʱ���ʱ�䳤�ȣ���λ��>*/
	BYTE				byReserved[99];   
} DH_MSG_HANDLE;

// �ⲿ����
typedef struct
{
	BYTE				byAlarmType;			// ���������ͣ�0�����գ�1������
	BYTE				byAlarmEn;				// ����ʹ��
	BYTE				byReserved[2];						
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE		struHandle;				// ������ʽ
} DH_ALARMIN_CFG, *LPDHDEV_ALARMIN_CFG; 

// ��̬��ⱨ��
typedef struct 
{
	BYTE				byMotionEn;				// ��̬��ⱨ��ʹ��
	BYTE				byReserved;
	WORD				wSenseLevel;			// ������
	WORD				wMotionRow;				// ��̬������������
	WORD				wMotionCol;				// ��̬������������
	BYTE				byDetected[DH_MOTION_ROW][DH_MOTION_COL]; // ����������32*32������
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE		struHandle;				//������ʽ
} DH_MOTION_DETECT_CFG;

// ��Ƶ��ʧ����
typedef struct
{
	BYTE				byAlarmEn;				// ��Ƶ��ʧ����ʹ��
	BYTE				byReserved[3];
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE		struHandle;				// ������ʽ
} DH_VIDEO_LOST_CFG;

// ͼ���ڵ�����
typedef struct
{
	BYTE				byBlindEnable;			// ʹ��
	BYTE				byBlindLevel;			// ������1-6
	BYTE				byReserved[2];
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE		struHandle;				// ������ʽ
} DH_BLIND_CFG;

// Ӳ����Ϣ(�ڲ�����)
typedef struct 
{
	BYTE				byNoDiskEn;				// ��Ӳ��ʱ����
	BYTE				byReserved_1[3];
	DH_TSECT			stNDSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE		struNDHandle;			// ������ʽ

	BYTE				byLowCapEn;				// Ӳ�̵�����ʱ����
	BYTE				byLowerLimit;			// ������ֵ��0-99
	BYTE				byReserved_2[2];
	DH_TSECT			stLCSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE		struLCHandle;			// ������ʽ

	BYTE				byDiskErrEn;			// Ӳ�̹��ϱ���
	BYTE				bDiskNum;
	BYTE				byReserved_3[2];
	DH_TSECT			stEDSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE		struEDHandle;			// ������ʽ
} DH_DISK_ALARM_CFG;

typedef struct
{
	BYTE				byEnable;
	BYTE				byReserved[3];
	DH_MSG_HANDLE		struHandle;
} DH_NETBROKEN_ALARM_CFG;

// ��������
typedef struct
{
	DWORD dwSize;
	DH_ALARMIN_CFG 		struLocalAlmIn[DH_MAX_ALARM_IN_NUM];
	DH_ALARMIN_CFG		struNetAlmIn[DH_MAX_ALARM_IN_NUM];
	DH_MOTION_DETECT_CFG struMotion[DH_MAX_VIDEO_IN_NUM];
	DH_VIDEO_LOST_CFG	struVideoLost[DH_MAX_VIDEO_IN_NUM];
	DH_BLIND_CFG		struBlind[DH_MAX_VIDEO_IN_NUM];
	DH_DISK_ALARM_CFG	struDiskAlarm;
	DH_NETBROKEN_ALARM_CFG	struNetBrokenAlarm;
} DHDEV_ALARM_SCHEDULE;

#define DECODER_OUT_SLOTS_MAX_NUM 		16
#define DECODER_IN_SLOTS_MAX_NUM 		16

// ��������������
typedef struct  
{
	DWORD				dwAddr;									// ������������ַ
	BOOL				bEnable;								// ����������ʹ��
	DWORD				dwOutSlots[DECODER_OUT_SLOTS_MAX_NUM];	// ����ֻ֧��8��.
	int					nOutSlotNum;							// dwOutSlots������ЧԪ�ظ���.
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];
	DH_MSG_HANDLE		struHandle[DECODER_IN_SLOTS_MAX_NUM];	// ����ֻ֧��8��.
	int					nMsgHandleNum;							// stuHandle������ЧԪ�ظ���.
	BYTE				bReserved[120];
} DH_ALARMDEC_CFG;

// �����ϴ�������
typedef struct  
{
	BYTE				byEnable;				// �ϴ�ʹ��
	BYTE				bReserverd;				// ����
	WORD				wHostPort;				// �������������˿�
	char				sHostIPAddr[DH_MAX_IPADDR_LEN];		// ��������IP

	int					nByTimeEn;				// ��ʱ�ϴ�ʹ�ܣ����������������ϴ�IP��������
	int					nUploadDay;				/* �����ϴ�����	
													"Never = 0", "Everyday = 1", "Sunday = 2", 
													"Monday = 3", Tuesday = 4", "Wednesday = 5",
													"Thursday = 6", "Friday = 7", "Saturday = 8"*/	
	int					nUploadHour;			// �����ϴ�ʱ�� ,[0~23]��
	
	DWORD				dwReserved[300]; 		// ��������չ��
} ALARMCENTER_UP_CFG;

// ȫ���л���������
typedef struct __DH_PANORAMA_SWITCH_CFG 
{
	BOOL				bEnable;				// ʹ��
	int					nReserved[5];			// ����
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];
	DH_MSG_HANDLE		struHandle;				// ��������
} DH_PANORAMA_SWITCH_CFG;

typedef struct __ALARM_PANORAMA_SWITCH_CFG 
{
	int					nAlarmChnNum;			// ����ͨ������
	DH_PANORAMA_SWITCH_CFG stuPanoramaSwitch[DH_MAX_VIDEO_IN_NUM];
} ALARM_PANORAMA_SWITCH_CFG;

// ʧȥ���㱨������
typedef struct __DH_LOST_FOCUS_CFG
{
	BOOL				bEnable;				// ʹ��
	int					nReserved[5];			// ����
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];
	DH_MSG_HANDLE		struHandle;				// ��������
} DH_LOST_FOCUS_CFG;

typedef struct __ALARM_LOST_FOCUS_CFG 
{
	int					nAlarmChnNum;			// ����ͨ������
	DH_LOST_FOCUS_CFG stuLostFocus[DH_MAX_VIDEO_IN_NUM];
} ALARM_LOST_FOCUS_CFG;

// IP��ͻ��ⱨ������
typedef struct __ALARM_IP_COLLISION_CFG
{
	BOOL				bEnable;				// ʹ��
	DH_MSG_HANDLE		struHandle;				// ��������
	int                 nReserved[300];			// ����
} ALARM_IP_COLLISION_CFG;

// MAC��ͻ�������
typedef struct __ALARM_MAC_COLLISION_CFG
{
	BOOL				bEnable;				// ʹ��
	DH_MSG_HANDLE		struHandle;				// ��������
	int                 nReserved[300];			// ����
} ALARM_MAC_COLLISION_CFG;

// 232���ڿ����źš�485���ڿ����ź��¼�����
typedef struct __COM_CARD_SIGNAL_INFO
{
	WORD                wCardStartPose;         // ������ʼλ
	WORD                wCardLenth;             // ���ų���
	char                cStartCharacter[32];        // ��ʼ��
	char                cEndCharacter[32];          // ������
	BYTE                byReserved[28];         // �����ֶ� 
}COM_CARD_SIGNAL_INFO;

// 232���ڿ����źš�485���ڿ����ź���������(�ڴ��ڷ������Ŀ�����Ϣ�������õĿ�����Ϣ�󣬽������豸ץͼ)
typedef struct __COM_CARD_SIGNAL_LINK_CFG
{
	COM_CARD_SIGNAL_INFO  struCardInfo;          // ������Ϣ
	DH_MSG_HANDLE         struHandle;            // �¼�����
	BYTE                  byReserved[24];       // �����ֶ�

}COM_CARD_SIGNAL_LINK_CFG;

//------------------------------�������ڵ�--------------------------------

// �ڵ���Ϣ
typedef struct __VIDEO_COVER_ATTR
{
	DH_RECT				rcBlock;				// ���ǵ���������
	int					nColor;					// ���ǵ���ɫ
	BYTE				bBlockType;				// ���Ƿ�ʽ��0���ڿ飬1��������
	BYTE				bEncode;				// ���뼶�ڵ���1����Ч��0������Ч
	BYTE				bPriview;				// Ԥ���ڵ��� 1����Ч��0������Ч
	char				reserved[29];			// ����
} VIDEO_COVER_ATTR;

// �������ڵ�����
typedef struct __DHDEV_VIDEOCOVER_CFG 
{
	DWORD				dwSize;
	char				szChannelName[DH_CHAN_NAME_LEN]; // ֻ��
	BYTE				bTotalBlocks;			// ֧�ֵ��ڵ�����
	BYTE				bCoverCount;			// �����õ��ڵ�����
	VIDEO_COVER_ATTR	CoverBlock[DH_MAX_VIDEO_COVER_NUM]; // ���ǵ�����	
	char				reserved[30];			// ����
}DHDEV_VIDEOCOVER_CFG;

// �豸�Ľ����������
typedef struct __DHDEV_DECODEPOLICY_CFG 
{
	int					nMinTime;				// �뻺��ʱ�䷶Χ(ֻ��)����С����ʱ��(��λ��ms)
	int					nMaxTime;				// �뻺��ʱ�䷶Χ(ֻ��)����󻺳�ʱ��(��λ��ms)
	int					nDeocdeBufTime;			// Ŀ���豸���뻺��ʱ��(��λ��ms)

	char				reserved[128];			// ����
}DHDEV_DECODEPOLICY_CFG;

// ������ص�����
typedef struct __DHDEV_MACHINE_CFG 
{
	char				szMachineName[DH_MACHINE_NAME_NUM];		// �������ƻ���
	char				szMachineAddress[DH_MACHINE_NAME_NUM];	// ��������ص�
	char				reserved[128];							// ����
}DHDEV_MACHINE_CFG;


////////////////////////////////IPC��Ʒ֧��////////////////////////////////

// ��������������Ϣ
typedef struct 
{
	int					nEnable;				// ����ʹ��
	char				szSSID[36];				// SSID
	int					nLinkMode;				// ����ģʽ��0��auto��1��adhoc��2��Infrastructure
	int					nEncryption;			// ���ܣ�0��off��2��WEP64bit��3��WEP128bit, 4:WPA-PSK-TKIP, 5: WPA-PSK-CCMP
	int					nKeyType;				// 0��Hex��1��ASCII
    int					nKeyID;					// ���
	union
	{
		char			szKeys[4][32];			// ��������
		char			szWPAKeys[128];			// nEncryptionΪ4��5ʱʹ�ã���128���ȣ����ý�������
	};
	int					nKeyFlag;
	BYTE                byConnectedFlag;        // 0: ������, 1: ���� 
	char				reserved[11];
} DHDEV_WLAN_INFO;

// ѡ��ʹ��ĳ�������豸
typedef struct  
{
	char				szSSID[36];
	int					nLinkMode;				// ����ģʽ��0��adhoc��1��Infrastructure
	int 				nEncryption;			// ���ܣ�0��off��2��WEP64bit��3��WEP128bit
	char				reserved[48];
} DHDEV_WLAN_DEVICE;

// �������������豸�б�
typedef struct  
{
	DWORD				dwSize;
	BYTE				bWlanDevCount;			// �������������豸����
	DHDEV_WLAN_DEVICE	lstWlanDev[DH_MAX_WLANDEVICE_NUM];
	char				reserved[255];
} DHDEV_WLAN_DEVICE_LIST;

// �����豸��չ����
typedef struct
{
	char                szSSID[36];                         // ��������
	char                szMacAddr[18];                      // mac��ַ
	BYTE                byApConnected;                      // �Ƿ����ӳɹ� 0:û�У�1: ���ӳɹ�
	BYTE                byLinkMode;                         // ����ģʽ 0:adhoc 1:Infrastructure;
	int                 nRSSIQuality;                       // �ź�ǿ��(dbm)
	unsigned int        unApMaxBitRate;                     // վ������������
	BYTE                byAuthMode;                         // ��֤ģʽ0:OPEN;1:SHARED;2:WPA;3:WPA-PSK;4:WPA2;5:WPA2-PSK;
															// 6:WPA-NONE(����adhoc����ģʽ),
															// 7-11�ǻ��ģʽ��ѡ�������κ�һ�ֶ����Խ������� 
															// 7:WPA-PSK | WPA2-PSK; 8:WPA | WPA2; 9:WPA | WPA-PSK;
															// 10:WPA2 | WPA2-PSK; 11:WPA | WPA-PSK |WPA2 |WPA2-PSK //12: UnKnown
	BYTE                byEncrAlgr;                         // ����ģʽ0:off; 2:WEP64bit; 3:WEP128bit; 4:WEP; 5:TKIP; 6:AES(CCMP)
															// 7: TKIP+AES(���ģʽ) 8: UnKnown
	BYTE                byLinkQuality;                      // ����ǿ�� 0~100(%)
    BYTE                byReserved[129];                     // Reserved 
}DHDEV_WLAN_DEVICE_EX;

// �������������豸��չ�����б�
typedef struct  
{
	DWORD				dwSize;
	BYTE				bWlanDevCount;			// �������������豸����
	DHDEV_WLAN_DEVICE_EX  lstWlanDev[DH_MAX_WLANDEVICE_NUM_EX];
	char				reserved[255];
} DHDEV_WLAN_DEVICE_LIST_EX;

//����������Ч��
typedef struct
{
	int                 nResult;                  // 0����ʾ���óɹ���1����ʾ����ʧ��
	BYTE                reserved[32];
} DHDEV_FUNC_TEST;

// FTP��������Ϣ
typedef struct
{
	char                szServerName[32];          // ��������
	char                szIp[16];                  // IP��ַ
	int                 nPort;                     // �˿ں�
	char                szUserName[32];            // �û���
	char                szPassword[32];	           // ����
	BOOL                bAnonymity;                // �Ƿ�������¼
	BYTE                byReserved[256];           // �����ֽ�
}FTP_SERVER_CFG;

// ftp���������Ӳ���
typedef struct
{
	FTP_SERVER_CFG     stuFtpServerInfo;           // ftp��������Ϣ�����û���д��
	DHDEV_FUNC_TEST    stuTestResult;              // ftp����������״̬(���豸����)
	BYTE               byReserved[64];
}DHDEV_FTP_SERVER_TEST;

// DDNS������Ϣ
typedef struct
{

	char				szServerType[DH_MAX_SERVER_TYPE_LEN];	// ���������ͣ�ϣ��..
	char				szServerIp[DH_MAX_DOMAIN_NAME_LEN];		// ������ip��������
	DWORD				dwServerPort;			// �������˿�
	char				szDomainName[DH_MAX_DOMAIN_NAME_LEN];	// dvr��������jeckean.3322.org
	char				szUserName[DH_MAX_HOST_NAMELEN];		// �û���
	char				szUserPsw[DH_MAX_HOST_PSWLEN];			// ����
	BYTE                byReserved[256];           // �����ֽ�
}DDNS_DOMAIN_INFO;


// DDNS�����Ƿ���ò���
typedef struct
{
	DDNS_DOMAIN_INFO   stuDomainInfo;				// DDNS������Ϣ�����û���д��
	DHDEV_FUNC_TEST    stuTestResult;				// ���Խ��
	char			   szMemo[128];					// ���Խ������
	BYTE               byReserved[64];
}DHDEV_DDNS_DOMAIN_TEST;


//��ʾӲ�̵Ļ�����Ϣ
typedef struct 
{
	BYTE                byModle[32];                  // �ͺ�
	BYTE                bySerialNumber[32];           // ���к�
	BYTE                byFirmWare[32];               // �̼���
	int                 nAtaVersion;                  // ATAЭ��汾��
	int                 nSmartNum ;                   // smart ��Ϣ��
	INT64				Sectors;	
	int                 nStatus;                      // ����״̬ 0-���� 1-�쳣
	int                 nReserved[33];                // �����ֽ�
} DHDEV_DEVICE_INFO;

//Ӳ�̵�smart��Ϣ�����ܻ��кܶ�������಻����30������
typedef struct
{
	BYTE    byId;		      // ID
	BYTE    byCurrent;         // ����ֵ
	BYTE    byWorst;           // ������ֵ
	BYTE    byThreshold;       // ��ֵ
	char    szName[64];	      // ������
	char    szRaw[8];         // ʵ��ֵ
	int     nPredict;         // ״̬
	char    reserved[128];
} DHDEV_SMART_VALUE;

//Ӳ��smart��Ϣ��ѯ
typedef struct
{
    BYTE                nDiskNum;       // Ӳ�̺�
	BYTE                byRaidNO;       // Raid���̣�0��ʾ����
	BYTE                byReserved[2];  // �����ֽ�
	DHDEV_DEVICE_INFO   deviceInfo;
	DHDEV_SMART_VALUE   smartValue[MAX_SMART_VALUE_NUM];
} DHDEV_SMART_HARDDISK;

// ����ģ����Ϣ
typedef struct
{
	char               szModuleName[64];      //  ��ģ������
	char               szHardWareVersion[32]; //  ��ģ��Ӳ���汾��
	char               szSoftwareVersion[32]; //  ��ģ�������汾��
	BYTE               reserved[128]; 
} DHDEV_SUBMODELE_VALUE;

// ��ѯ�豸��ģ����Ϣ
typedef struct
{
	int                    nSubModuleNum;                         //  ������ģ������
	DHDEV_SUBMODELE_VALUE  stuSubmoduleValue[MAX_SUBMODULE_NUM];   //  ��ģ����ϸ��Ϣ
	BYTE				   bReserved[256];
} DHDEV_SUBMODULE_INFO;

// ��ѯӲ�̻�������
typedef struct
{
	BYTE                bDiskDamageLevel[DH_MAX_DISK_NUM];  //�����̻����ȼ�
	BYTE                bReserved[128];
} DHDEV_DISKDAMAGE_INFO;


// syslog��Զ�̷���������
typedef struct 
{
	char szServerIp[DH_MAX_IPADDR_OR_DOMAIN_LEN];	//��������ַ
	int	 nServerPort;								//�������˿�
	BYTE bEnable;									//������ʹ��
	BYTE bReserved[255];							//�����ֽ�
}DHDEV_SYSLOG_REMOTE_SERVER;

// ��Ƶ��������
typedef struct
{
	BYTE backupVideoFormat; // �����ļ�����, 0:dav, 1:asf
	BYTE password[6];       // ��������
	BYTE reversed[505];
}DHDEV_BACKUP_VIDEO_FORMAT;


// ����ע���������
typedef struct  
{
	char				szServerIp[32];			// ע�������IP
	int					nServerPort;			// �˿ں�
	BYTE                byReserved[3];          // ����
	BYTE                bServerIpExEn;          // ע�������IP��չʹ��,0-��ʾ��Ч, 1-��ʾ��Ч
	char				szServerIpEx[60];       // ע�������IP��չ��֧��ipv4,ipv6,���������͵�IP
} DHDEV_SERVER_INFO;

typedef struct  
{
	DWORD				dwSize;
	BYTE				bServerNum;				// ֧�ֵ����ip��
	DHDEV_SERVER_INFO	lstServer[DH_MAX_REGISTER_SERVER_NUM];
	BYTE				bEnable;				// ʹ��
	char				szDeviceID[32];			// �豸id
	char				reserved[94];
} DHDEV_REGISTER_SERVER;

// ����ͷ����
typedef struct __DHDEV_CAMERA_INFO
{
	BYTE				bBrightnessEn;			// ���ȿɵ���1���ɣ�0������
	BYTE				bContrastEn;			// �Աȶȿɵ�
	BYTE				bColorEn;				// ɫ�ȿɵ�
	BYTE				bGainEn;				// ����ɵ�
	BYTE				bSaturationEn;			// ���Ͷȿɵ�
	BYTE				bBacklightEn;			// ���ⲹ�� 0��ʾ��֧�ֱ��ⲹ��,1��ʾ֧��һ����������,�أ���2��ʾ֧��������������,��,�ͣ���3��ʾ֧��������������,��,��,�ͣ�
	BYTE				bExposureEn;			// �ع�ѡ��: 0:��ʾ��֧���ع���� 1:��ʾֻ֧���Զ��ع� n:�ع�ĵȼ���(1��ʾ֧���Զ��ع� 2~n��ʾ֧�ֵ��ֶ������ع�ĵȼ�)
	BYTE				bColorConvEn;			// �Զ��ʺ�ת���ɵ�
	BYTE				bAttrEn;				// ����ѡ�1���ɣ�0������
	BYTE				bMirrorEn;				// ����1��֧�֣�0����֧��
    BYTE				bFlipEn;				// ��ת��1��֧�֣�0����֧��
	BYTE				iWhiteBalance;			// ��ƽ�� 0-��֧�ְ�ƽ�⣬1-֧���Զ���ƽ�⣬2-֧��Ԥ�ð�ƽ�⣨���龰ģʽ�� 3-֧���Զ����ƽ��
	BYTE				iSignalFormatMask;		// �źŸ�ʽ���룬��λ�ӵ͵���λ�ֱ�Ϊ��0-Inside(�ڲ�����) 1- BT656 2-720p 3-1080i  4-1080p  5-1080sF
	BYTE				bRotate90;				// 90����ת 0-��֧�� 1-֧��
    BYTE				bLimitedAutoExposure;   // �Ƿ�֧�ִ�ʱ�������޵��Զ��ع�
    BYTE				bCustomManualExposure;  // �Ƿ�֧���û��Զ����ֶ��ع�ʱ��
	BYTE				bFlashAdjustEn;         // �Ƿ�֧������Ƶ���
	BYTE				bNightOptions;			// �Ƿ�֧��ҹ��ѡ��
	BYTE                iReferenceLevel;    	// �Ƿ�֧�ֲο���ƽ����
	BYTE                bExternalSyncInput;     // �Ƿ�֧���ⲿͬ���ź����룬0-��֧�֣�1-֧��
    unsigned short      usMaxExposureTime;      // �Զ����ع���������ع�ʱ�䣬��λ����         
	unsigned short      usMinExposureTime;      // �Զ����ع�������С�ع�ʱ�䣬��λ����
	BYTE                bWideDynamicRange;      // ����̬������Χ,0-��ʾ��֧��,2~n��ʾ���ķ�Χֵ
	BYTE                bDoubleShutter;         // ˫����0��֧��,1-֧��˫����ȫ֡�ʣ���ͼ�����Ƶֻ�п��Ų�����ͬ��2-֧��˫���Ű�֡�ʣ���ͼ�����Ƶ���ż���ƽ���������ͬ��3-֧��˫����ȫ֡�ʺͰ�֡��
	BYTE				byExposureCompensation; // 1֧�֣� 0 ��֧��
	BYTE				bRev[109];				// ����
} DHDEV_CAMERA_INFO;

//ҹ����������ѡ������Ϲ��߽ϰ�ʱ�Զ��л���ҹ�������ò���
typedef struct __DHDEV_NIGHTOPTIONS 
{
	BYTE  bEnable;								// 0-���л���1-�л� 
												// �����ճ�������ʱ�䣬����֮���ճ�֮ǰ��������ҹ����������á�
												// 00:00:00 ~23:59:59
	BYTE  bSunriseHour;
	BYTE  bSunriseMinute;
	BYTE  bSunriseSecond;
	BYTE  bSunsetHour;
	BYTE  bSunsetMinute;
	BYTE  bSunsetSecond;  
	BYTE  bWhiteBalance ;						// ��ƽ�� 0:Disabled,1:Auto 2:sunny 3:cloudy 4:home 5:office 6:night 7: Custom
	BYTE  bGainRed;								// ��ɫ������ڣ���ƽ��Ϊ"Custom"ģʽ����Ч 0~100
	BYTE  bGainBlue;							// ��ɫ������ڣ���ƽ��Ϊ"Custom"ģʽ����Ч 0~100
	BYTE  bGainGreen;							// ��ɫ������ڣ���ƽ��Ϊ"Custom"ģʽ����Ч 0~100
	BYTE  bGain;								// 0~100
	BYTE  bGainAuto;							// 0-���Զ����� 1-�Զ�����
	BYTE  bBrightnessThreshold ;				// ����ֵ 0~100
	BYTE  ReferenceLevel;                       // ��ƽ�ο�ֵ 0~100   
	BYTE  bExposureSpeed;						// ȡֵ��Χȡ�����豸��������0-�Զ��ع� 1~n-1-�ֶ��ع�ȼ� n-��ʱ�������޵��Զ��ع� n+1-�Զ���ʱ���ֶ��ع� (n��ʾ֧�ֵ��ع�ȼ�����
	float ExposureValue1;						// �Զ��ع�ʱ�����޻����ֶ��ع��Զ���ʱ��,����Ϊ��λ��ȡֵ0.1ms~80ms
	float ExposureValue2;						// �Զ��ع�ʱ������,����Ϊ��λ��ȡֵ0.1ms~80ms
	BYTE  bAutoApertureEnable;                  // �Զ���Ȧʹ��,1����,0�ر�
	BYTE  bWideDynamicRange;                    // ����ֵ̬     ȡֵ��Χ����������
	WORD  wNightSyncValue;						// ҹ����λ 0~360
	WORD  wNightSyncValueMillValue;             // ҹ����λ0~999(ǧ��֮һ��),��wNightSyncValue��Ϲ���ҹ����λֵ
	BYTE res[10];								// ����
} DHDEV_NIGHTOPTIONS;

// ����ͷ��������
typedef struct __DHDEV_CAMERA_CFG 
{
	DWORD				dwSize;
	BYTE				bExposure;				// �ع�ģʽ��ȡֵ��Χȡ�����豸��������0-�Զ��ع⣬1-�ع�ȼ�1��2-�ع�ȼ�2��n-1����ع�ȼ��� n��ʱ�������޵��Զ��ع� n+1�Զ���ʱ���ֶ��ع� (n==bExposureEn��
	BYTE				bBacklight;				// ���ⲹ�������ⲹ���ȼ�ȡֵ��Χȡ�����豸��������0-�رգ�1-���ⲹ��ǿ��1��2-���ⲹ��ǿ��2��n-��󱳹ⲹ���ȼ��� 
	BYTE				bAutoColor2BW;			// ��/ҹģʽ��3-����ʱ���Զ��л� 2����(�ڰ�)��1���������������л���0����(��ɫ)
	BYTE				bMirror;				// ����1������0����
	BYTE				bFlip;					// ��ת��1������0����
	BYTE				bLensEn;				// �Զ���Ȧ��������: 1��֧�֣�0 ����֧��
	BYTE				bLensFunction;			// �Զ���Ȧ����: 1:�����Զ���Ȧ��0: �ر��Զ���Ȧ
	BYTE				bWhiteBalance;			// ��ƽ�� 0:Disabled,1:Auto 2:sunny 3:cloudy 4:home 5:office 6:night 7: Custom
	BYTE				bSignalFormat;			// �źŸ�ʽ0-Inside(�ڲ�����) 1- BT656 2-720p 3-1080i  4-1080p  5-1080sF
	BYTE				bRotate90;				// 0-����ת��1-˳ʱ��90�㣬2-��ʱ��90��
	BYTE                bReferenceLevel;         // ��ƽ�ο�ֵ 0~100  
	BYTE                byReserve;              // ����
	float				ExposureValue1;			// �Զ��ع�ʱ�����޻����ֶ��ع��Զ���ʱ��,����Ϊ��λ��ȡֵ0.1ms~80ms
	float				ExposureValue2;			// �Զ��ع�ʱ������,����Ϊ��λ��ȡֵ0.1ms~80ms	
	DHDEV_NIGHTOPTIONS	stuNightOptions;		// ҹ�����ò���ѡ�� 
	BYTE				bGainRed;				// ��ɫ������ڣ���ƽ��Ϊ"Custom"ģʽ����Ч 0~100
	BYTE				bGainBlue;				// ��ɫ������ڣ���ƽ��Ϊ"Custom"ģʽ����Ч 0~100
	BYTE				bGainGreen;				// ��ɫ������ڣ���ƽ��Ϊ"Custom"ģʽ����Ч 0~100
	BYTE				bFlashMode;				// ����ƹ���ģʽ��0-�رգ�1-ʼ�գ�2-�Զ�
	BYTE				bFlashValue;			// ����ƹ���ֵ, 0-0us, 1-64us, 2-128us,...15-960us
	BYTE				bFlashPole;				// ����ƴ���ģʽ0-�͵�ƽ 1-�ߵ�ƽ
	BYTE                bExternalSyncPhase;     // �ⲿͬ���ź�����,0-�ڲ�ͬ�� 1-�ⲿͬ��
	BYTE                bFlashInitValue;        // ���������Ԥ��ֵ  ����0~100
	WORD                wExternalSyncValue ;    // ��ͬ������λ���� 0~360(С�����3λ������Ч)
	WORD                wExternalSyncValueMillValue;//  ��ͬ������λ����0~999(ǧ��֮һ��),��wExternalSyncValue��Ϲ�����ͬ������λֵ
	BYTE                bWideDynamicRange;                //����ֵ̬     ȡֵ��Χ����������
	BYTE				byExposureCompensation;		// �عⲹ��ֵ��Ĭ��Ϊ7����Χ0~14
	char				bRev[54];					// ����
} DHDEV_CAMERA_CFG;

#define ALARM_MAX_NAME 64
// (����)���ⱨ������
typedef struct
{
	BOOL				bEnable;				// ��������ʹ��
	char				szAlarmName[DH_MAX_ALARM_NAME];	// ������������
	int					nAlarmInPattern;		// ���������벨��
	int					nAlarmOutPattern;		// �����������
	char				szAlarmInAddress[DH_MAX_ALARM_NAME];// ���������ַ
	int					nSensorType;			// �ⲿ�豸���������ͳ��� or ����
	int					nDefendEfectTime;		// ��������ʱʱ�䣬�ڴ�ʱ���ñ���������Ч
	int					nDefendAreaType;		// �������� 
	int					nAlarmSmoothTime;		// ����ƽ��ʱ�䣬���ڴ�ʱ�������ֻ��һ��������������������������Ե�����һ��
	char				reserved[128];
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];
	DH_MSG_HANDLE		struHandle;				// ������ʽ
} DH_INFRARED_INFO;

// ����ң��������
typedef struct 
{
	BYTE				address[ALARM_MAX_NAME];// ң������ַ
	BYTE				name[ALARM_MAX_NAME];	// ң��������
	BYTE				reserved[32];			// �����ֶ�
} DH_WI_CONFIG_ROBOT;

// ���߱����������
typedef struct 
{
	BYTE				address[ALARM_MAX_NAME];// ���������ַ
	BYTE				name[ALARM_MAX_NAME];	// �����������
	BYTE				reserved[32];			// �����ֶ�
} DH_WI_CONFIG_ALARM_OUT;

typedef struct  
{
	DWORD				dwSize;
	BYTE				bAlarmInNum;			// ���߱���������
	BYTE				bAlarmOutNum;			// ���߱��������
	DH_WI_CONFIG_ALARM_OUT AlarmOutAddr[16];	// ���������ַ
	BYTE				bRobotNum;				// ң��������
	DH_WI_CONFIG_ROBOT RobotAddr[16];			// ң������ַ
	DH_INFRARED_INFO	InfraredAlarm[16];
	char				reserved[256];
} DH_INFRARED_CFG;

// ����Ƶ��ⱨ����Ϣ
typedef struct
{
	int					channel;				// ����ͨ����
	int					alarmType;				// �������ͣ�0����Ƶֵ���ͣ�1����Ƶֵ����
	unsigned int		volume;					// ����ֵ
	BYTE                byState;                // ��Ƶ����״̬, 0: ��Ƶ��������, 1: ��Ƶ������ʧ
	char				reserved[255];
} NET_NEW_SOUND_ALARM_STATE;

typedef struct  
{
	int					channelcount;			// ������ͨ������
	NET_NEW_SOUND_ALARM_STATE SoundAlarmInfo[DH_MAX_ALARM_IN_NUM];
} DH_NEW_SOUND_ALARM_STATE;

// ץͼ�������Խṹ��
typedef struct 
{
	int					nChannelNum;			// ͨ����
	DWORD				dwVideoStandardMask;	// �ֱ���(��λ)������鿴ö��CAPTURE_SIZE						
	int					nFramesCount;			// Frequence[128]�������Ч����
	char				Frames[128];			// ֡��(����ֵ)
												// -25��25��1֡��-24��24��1֡��-23��23��1֡��-22��22��1֡
												// ����
												// 0����Ч��1��1��1֡��2��1��2֡��3��1��3֡
												// 4��1��4֡��5��1��5֡��17��1��17֡��18��1��18֡
												// 19��1��19֡��20��1��20֡
												// ����
												// 25: 1��25֡
	int					nSnapModeCount;			// SnapMode[16]�������Ч����
	char				SnapMode[16];			// (����ֵ)0����ʱ����ץͼ��1���ֶ�����ץͼ
	int					nPicFormatCount;		// Format[16]�������Ч����
	char 				PictureFormat[16];		// (����ֵ)0��BMP��ʽ��1��JPG��ʽ
	int					nPicQualityCount;		// Quality[32]�������Ч����
	char 				PictureQuality[32];		// ����ֵ
												// 100��ͼ������100%��80:ͼ������80%��60:ͼ������60%
												// 50:ͼ������50%��30:ͼ������30%��10:ͼ������10%
	char 				nReserved[128];			// ����
} DH_QUERY_SNAP_INFO;

typedef struct 
{
	int					nChannelCount;			// ͨ������
	DH_QUERY_SNAP_INFO  stuSnap[DH_MAX_CHANNUM];
} DH_SNAP_ATTR_EN;


/* IP���˹������� */
#define DH_IPIFILTER_NUM			200			// IP
#define DH_IPIFILTER_NUM_EX			512			// IP

// IP��Ϣ
typedef struct 
{
	DWORD				dwIPNum;				// IP����
	char				SZIP[DH_IPIFILTER_NUM][DH_MAX_IPADDR_LEN]; // IP
	char				byReserve[32];			// ����
} IPIFILTER_INFO;

// IP�������ýṹ��
typedef struct
{
	DWORD				dwSize;
	DWORD				dwEnable;				// ʹ��
	DWORD				dwType;					// ��ǰ�������ͣ�0�������� 1�����������豸ֻ��ʹһ��������Ч�������ǰ����������Ǻ�������
	IPIFILTER_INFO		BannedIP;				// ������
	IPIFILTER_INFO		TrustIP;				// ������
	char				byReserve[256];			// ����
} DHDEV_IPIFILTER_CFG;

// IP��Ϣ��չ
typedef struct 
{
	DWORD				dwIPNum;				// IP����
	char				SZIP[DH_IPIFILTER_NUM_EX][DH_MAX_IPADDR_LEN]; // IP
	char				byReserve[32];			// ����
} IPIFILTER_INFO_EX;

// IP�������ýṹ����չ
typedef struct
{
	DWORD				dwSize;
	DWORD				dwEnable;				// ʹ��
	DWORD				dwType;					// ��ǰ�������ͣ�0�������� 1�����������豸ֻ��ʹһ��������Ч�������ǰ����������Ǻ�������
	IPIFILTER_INFO_EX		BannedIP;			// ������
	IPIFILTER_INFO_EX		TrustIP;			// ������
	char				byReserve[256];			// ����
} DHDEV_IPIFILTER_CFG_EX;

/* MAC�������� */
#define DH_MACFILTER_NUM			512			// MAC

// MAC��Ϣ
typedef struct 
{
	DWORD				dwSize;					// ʹ��ʱ���ó�ʼ��Ϊ���ṹ���С
	DWORD				dwMacNum;				// MAC����
	char				szMac[DH_MACFILTER_NUM][DH_MACADDR_LEN]; // MAC
} MACFILTER_INFO;

// MAC�������ýṹ��
typedef struct
{
	DWORD					dwSize;				// ʹ��ʱ���ó�ʼ��Ϊ���ṹ���С
	DWORD					dwEnable;			// ʹ��
	DWORD					dwType;				// ��ǰ�������ͣ�0�������� 1�����������豸ֻ��ʹһ��������Ч�������ǰ����������Ǻ�������
	MACFILTER_INFO			stuBannedMac;		// ������Mac
	MACFILTER_INFO			stuTrustMac;		// ������Mac
} DHDEV_MACFILTER_CFG;

/* MAC,IP�������� */
#define DH_MACIPFILTER_NUM			512			// MAC,IP

// MAC��IP������Ϣ
typedef struct
{
	DWORD	dwSize;					// ʹ��ʱ���ó�ʼ��Ϊ���ṹ���С
	char	szMac[DH_MACADDR_LEN];	// mac
	char	szIp[DH_MAX_IPADDR_LEN];// ip
}MACIP_INFO;

// MAC,IP�������ýṹ��
typedef struct
{
	DWORD					dwSize;								// ʹ��ʱ���ó�ʼ��Ϊ���ṹ���С
	DWORD					dwEnable;							// ʹ��
	DWORD					dwType;								// ��ǰ�������ͣ�0�������� 1�����������豸ֻ��ʹһ��������Ч�������ǰ����������Ǻ�������
	DWORD					dwBannedMacIpNum;					// ������MAC,IP����(MAC,IPһһ��Ӧ)
	MACIP_INFO				stuBannedMacIp[DH_MACIPFILTER_NUM];	// ������Mac,IP
	DWORD					dwTrustMacIpNum;					// ������MAC,IP����(MAC,IPһһ��Ӧ)
	MACIP_INFO				stuTrustMacIp[DH_MACIPFILTER_NUM];	// ������Mac,IP
} DHDEV_MACIPFILTER_CFG;

typedef struct
{
	int                nCardNum;                // ��Ч������
	char 	           cardInfo [DH_MAX_CARD_NUM][DH_MAX_CARDINFO_LEN]; // ������Ϣ�ַ��� 
	BYTE               byReserve[32];           // �����ֶ�
}DHDEV_NETCARD_CFG;

// RTSP ����
typedef struct
{
	WORD               wPort;                  // �˿ں�
	BYTE               byReserved[62];         // �����ֶ�
}DHDEV_RTSP_CFG;

//-------------------------������������---------
// ������Կ��Ϣ36���ֽ�
typedef struct _ENCRYPT_KEY_INFO
{
	BYTE        byEncryptEnable;       //  �Ƿ����0:������, 1:����
	BYTE        byReserved[3]; 
	union
	{
		BYTE    byDesKey[8];           // des��Կ
		BYTE    by3DesKey[3][8];       // 3des��Կ
		BYTE    byAesKey[32];          // aes��Կ

	};
}ENCRYPT_KEY_INFO;

// �����㷨����
typedef struct _ALGO_PARAM_INFO
{
	WORD       wEncryptLenth;       // ��Կ���ȣ���ǰΪAES�㷨����ʱ����ʾ��Կλ��(Ŀǰ֧��128��192��256λ����, ��: wEncryptLenthΪ128������Կ��ϢENCRYPT_KEY_INFO���byAesKey[0]~[15])
								    // ΪDES�㷨����ʱ����Կ���ȹ̶�Ϊ64λ
							        // Ϊ3DES�㷨����ʱ����ʾ��Կ�ĸ���(2��3����Կ)
	BYTE       byAlgoWorkMode ;     // ����ģʽ,�ο�ö������ EM_ENCRYPT_ALOG_WORKMODE 
	BYTE       reserved[13];        // �����ֶ�
}ALGO_PARAM_INFO;

// ��������������Ϣ
typedef struct _DHEDV_STREAM_ENCRYPT
{
    BYTE                    byEncrptAlgoType;        // �����㷨���ͣ�00: AES��01:DES��02: 3DES
    BYTE                    byReserved1[3];
    ALGO_PARAM_INFO         stuEncrptAlgoparam;      // �����㷨����
    ENCRYPT_KEY_INFO        stuEncryptKeys[32];      // ��ͨ������Կ��Ϣ 
	BYTE					byEncrptPlanEnable;		 // ���ܼƻ�ʹ��
	BYTE					byReserved3[3];
	NET_TIME				stuPreTime;				 // ���ܼƻ��Ŀ�ʼʱ��
	BYTE					reserved2[1360];
}DHEDV_STREAM_ENCRYPT;

// ����������
typedef struct _DHDEV_BIT_RATE
{
	DWORD                   nExpectCodeRate;          // ������������λkps
	BYTE                    byReserved[64];           // �����ֽ�
}DHDEV_LIMIT_BIT_RATE;

// �û��Զ�������
typedef struct _DHDEV_CUSTOM_CFG
{
	char                   szData[1024];            // �û��Զ���������Ϣ
	char                   reserved[3072];          // �����ֶ�
}DHDEV_CUSTOM_CFG;

/*�����Խ���������*/
typedef struct
{
	DWORD				dwSize;
	int					nCompression;			// ѹ����ʽ��ö��ֵ�����DH_TALK_CODING_TYPE��������豸֧�ֵ������Խ���������ѹ����ʽ��
	int					nMode;					// ����ģʽ��ö��ֵ��Ϊ0ʱ��ʾ��ѹ����ʽ��֧�ֱ���ģʽ��
												// ����ѹ����ʽ�������ö�Ӧ�ı����ʽ����
												// AMR���EM_ARM_ENCODE_MODE
	char				byReserve[256];			// ����
} DHDEV_TALK_ENCODE_CFG;

// ������mobile�������
// (�¼�������ý�����/���ŷ���)MMS���ýṹ��
typedef struct
{
	DWORD				dwSize;
	DWORD				dwEnable;				// ʹ��
	DWORD				dwReceiverNum;			// ���Ž����߸���
	char				SZReceiver[DH_MMS_RECEIVER_NUM][32];	// ���Ž����ߣ�һ��Ϊ�ֻ�����
    BYTE                byType;					// ������Ϣ���� 0:MMS��1:SMS
	char                SZTitle[32];			// ������Ϣ����
	char				byReserve[223];			// ����
} DHDEV_MMS_CFG;

// (���ż���������������)
typedef struct  
{
	DWORD				dwSize;
	DWORD				dwEnable;				// ʹ��
	DWORD				dwSenderNum;			// ���ŷ����߸���
	char				SZSender[DH_MMS_SMSACTIVATION_NUM][32];	// ���ŷ����ߣ�һ��Ϊ�ֻ�����
 	char				byReserve[256];			// ����
}DHDEV_SMSACTIVATION_CFG;

// (���ż���������������)
typedef struct  
{
	DWORD				dwSize;
	DWORD				dwEnable;				// ʹ��
	DWORD				dwCallerNum;			// �����߸���
	char				SZCaller[DH_MMS_DIALINACTIVATION_NUM][32];	// ������, һ��Ϊ�ֻ�����
 	char				byReserve[256];			// ����
}DHDEV_DIALINACTIVATION_CFG;
// ������mobile�������


// ���������ź�ǿ�Ƚṹ��
typedef struct
{
	DWORD				dwSize;
	DWORD				dwTDSCDMA;				// TD-SCDMAǿ�ȣ���Χ��0��100
	DWORD				dwWCDMA;				// WCDMAǿ�ȣ���Χ��0��100
	DWORD				dwCDMA1x;				// CDMA1xǿ�ȣ���Χ��0��100
	DWORD				dwEDGE;					// EDGEǿ�ȣ���Χ��0��100
	DWORD				dwEVDO;					// EVDOǿ�ȣ���Χ��0��100
	int					nCurrentType;			// ��ǰ����
												// 0	�豸��֧����һ��
												// 1    TD_SCDMA
												// 2	WCDMA
												// 3	CDMA_1x
												// 4	EDGE
												// 5	EVDO
	char				byReserve[252];			// ����
} DHDEV_WIRELESS_RSS_INFO;

typedef struct _DHDEV_SIP_CFG
{
	BOOL	 bUnregOnBoot;						//Unregister on Reboot
	char	 szAccoutName[64];					//Account Name
	char	 szSIPServer[128];					//SIP Server
	char	 szOutBoundProxy[128];				//Outbound Proxy
	DWORD	 dwSIPUsrID;							//SIP User ID
	DWORD	 dwAuthID;							//Authenticate ID
	char	 szAuthPsw[64];						//Authenticate Password
	char	 szSTUNServer[128];					//STUN Server
	DWORD	 dwRegExp;							//Registration Expiration
	DWORD	 dwLocalSIPPort;						//Local SIP Port
	DWORD	 dwLocalRTPPort;						//Local RTP Port
	BOOL     bEnable;                            // ʹ��
	char     szNotifyID[128];                    // ����ID
	NET_TIME stuRegTime;                         // ע��ɹ���ʱ�䣻ֻ���ֶΣ��豸ָ����   
	BYTE	bReserved[868];					     //reserved
} DHDEV_SIP_CFG;

typedef struct _DHDEV_SIP_STATE
{
	int	    nStatusNum;							//״̬��Ϣ�ܵĸ���
	BYTE    byStatus[64];                       //0:ע��ɹ�,1:δע��,2:��Ч,3:ע����,4:ͨ����
	BYTE	bReserved[64];						//����
}DHDEV_SIP_STATE;

typedef struct _DHDEV_HARDKEY_STATE
{
	BOOL    bState;                             // 0:δ����HardKey, 1:�Ѳ���HardKey
	BYTE	bReserved[64];                      // ����
}DHDEV_HARDKEY_STATE;

typedef struct _DHDEV_ISCSI_PATHLIST
{
	int		nCount;
	char	szPaths[DH_MAX_ISCSI_PATH_NUM][MAX_PATH_STOR];	// Զ��Ŀ¼����
} DHDEV_ISCSI_PATHLIST;

// ����·��������Ϣ
typedef struct _DHDEV_WIFI_ROUTE_CAP_COUNTRY
{
	char	szCountry[32];						// ����
	int		nValidChnNum;						// ��Чͨ������
	int		nValideChannels[32];				// ��Чͨ���б�
	char	reserved[64];						// ����
} DHDEV_WIFI_ROUTE_CAP_COUNTRY;

typedef struct _DHDEV_WIFI_ROUTE_CAP
{
	int		nCountryNum;							// ��������
	DHDEV_WIFI_ROUTE_CAP_COUNTRY stuCountry[256];	// ��ͬ���ҵ�������Ϣ
	char	reserved[256];							// ����
} DHDEV_WIFI_ROUTE_CAP;

//  �����ظ�����Ϣ
typedef struct _MONITOR_INFO
{
	int    nPresetObjectNum;             // Ԥ��Ӧ��Ŀ����Ŀ
	int    nActualObjectNum;             // �ֳ�ʵ��Ŀ����Ŀ 
	char   reserved[64]; 
}MONITOR_INFO;

typedef struct _DHDEV_MONITOR_INFO
{
	int              nChannelNumber;
	MONITOR_INFO     stMonitorInfo[64];   //  �����ظ�����Ϣ
	char             reserved[128];
}DHDEV_MONITOR_INFO;
/***************************** ��̨Ԥ�Ƶ����� ***********************************/
typedef struct _POINTEANBLE
{
	BYTE				bPoint;	//Ԥ�Ƶ����Ч��Χ������[1,80]����Ч����Ϊ0��
	BYTE				bEnable;	//�Ƿ���Ч,0��Ч��1��Ч
	BYTE				bReserved[2];
} POINTEANBLE;

typedef struct _POINTCFG
{
	char				szIP[DH_MAX_IPADDR_LEN];// ip
	int					nPort;					// �˿�	
	POINTEANBLE			stuPointEnable[80];		// Ԥ�Ƶ�ʹ��
	BYTE				bReserved[256];
}POINTCFG;

typedef struct _DHDEV_POINT_CFG
{
	int					nSupportNum;			// ֻ�����������õ�ʱ����Ҫ���ظ�sdk����ʾ֧�ֵ�Ԥ�Ƶ���
	POINTCFG			stuPointCfg[16];		// ��ά�±��ʾͨ���š�Ҫ���õĵ���ֵ����ǰnSupportNum���±����档
	BYTE				bReserved[256];			// ����
}DHDEV_POINT_CFG;
////////////////////////////////����DVR֧��////////////////////////////////

// GPS��Ϣ(�����豸)
typedef struct _GPS_Info
{
    NET_TIME			revTime;				// ��λʱ��
	char				DvrSerial[50];			// �豸���к�
    double				longitude;				// ����(��λ�ǰ����֮�ȣ���Χ0-360��)
    double				latidude;				// γ��(��λ�ǰ����֮�ȣ���Χ0-180��)
    double				height;					// �߶�(��)
    double				angle;					// �����(��������Ϊԭ�㣬˳ʱ��Ϊ��)
    double				speed;					// �ٶ�(��λ�Ǻ��speed/1000*1.852����/Сʱ)
    WORD				starCount;				// ��λ����
    BOOL				antennaState;			// ����״̬(true �ã�false ��)
    BOOL				orientationState;		// ��λ״̬(true ��λ��false ����λ)
} GPS_Info,*LPGPS_Info;

// ����״̬��Ϣ
typedef struct 
{
	int                nAlarmCount;             // �����ı����¼�����
	int                nAlarmState[128];        // �����ı����¼�����
	BYTE               byRserved[128];          // �����ֽ�
}ALARM_STATE_INFO;

// ץͼ�����ṹ��
typedef struct _snap_param
{
	unsigned int		Channel;				// ץͼ��ͨ��
	unsigned int		Quality;				// ���ʣ�1~6
	unsigned int		ImageSize;				// �����С��0��QCIF��1��CIF��2��D1
	unsigned int		mode;					// ץͼģʽ��0����ʾ����һ֡��1����ʾ��ʱ��������2����ʾ��������
	unsigned int		InterSnap;				// ʱ�䵥λ�룻��mode=1��ʾ��ʱ��������ʱ����ʱ����Ч
	unsigned int		CmdSerial;				// �������к�
	unsigned int		Reserved[4];
} SNAP_PARAMS, *LPSNAP_PARAMS;

// ץͼ��������
typedef struct 
{
	DWORD				dwSize;
	BYTE				bTimingEnable;				// ��ʱץͼ����(����ץͼ�����ڸ�������������������)
	BYTE                bPicIntervalHour;           // ��ʱץͼʱ����Сʱ��
	short	            PicTimeInterval;			// ��ʱץͼʱ��������λΪ��,Ŀǰ�豸֧������ץͼʱ����Ϊ30����                           
	DH_VIDEOENC_OPT		struSnapEnc[SNAP_TYP_NUM]; // ץͼ�������ã���֧�����еķֱ��ʡ����ʡ�֡�����ã�֡���������Ǹ�������ʾһ��ץͼ�Ĵ�����
} DHDEV_SNAP_CFG;

// ץͼ����������չ
typedef struct 
{
	DWORD				dwSize;
	BYTE				bTimingEnable;				// ��ʱץͼ����(����ץͼ�����ڸ�������������������)
	BYTE                bPicIntervalHour;           // ��ʱץͼʱ����Сʱ��
	short	            PicTimeInterval;			// ��ʱץͼʱ��������λΪ��,Ŀǰ�豸֧������ץͼʱ����Ϊ30����                           
	DH_VIDEOENC_OPT		struSnapEnc[SNAP_TYP_NUM];  // ץͼ�������ã���֧�����еķֱ��ʡ����ʡ�֡�����ã�֡���������Ǹ�������ʾһ��ץͼ�Ĵ�����
	DWORD               dwTrigPicIntervalSecond;    // ����������ÿ��ץͼʱ����ʱ�� ��λ��
	BYTE                byRserved[256];             // �����ֽ�
} DHDEV_SNAP_CFG_EX;


//����wifi״̬
typedef struct  
{
	char	szSSID[128];							//SSID
	BOOL	bEnable;								//�Ƿ�����wifi����, 0:��ʹ�� 1:ʹ��
	int		nSafeType;								//У������
													//0:OPEN 
													//1:RESTRICTE
													//2:WEP
													//3:WPA
													//4:WPA2
													//5:WPA-PSK
													//6:WPA2-PSK
	int		nEncryprion;							//���ܷ�ʽ
													//0:OPEN
													//1:TKIP
													//2:WEP
													//3:AES
													//4:NONE(��У��)
													//5:AUTO
	                                                //6:SHARED
	int		nStrength;								//APվ���ź�
	char	szHostIP[128];							//������ַ
	char	szHostNetmask[128];						//��������
	char	szHostGateway[128];						//��������
	int		nPriority;								//���ȼ�,(1-32)
	int     nEnDHCP;                                //0����ʹ��	1��ʹ��(ɨ�赽��dhcpĬ��ʹ�ܴ�)
	BYTE	bReserved[1016];
} DHDEV_VEHICLE_WIFI_STATE;

typedef struct
{
	char	szSSID[128];							//SSID
	int		nPriority;								//���ȼ�,(1-32)
	int		nSafeType;								//У������
													//0:OPEN 
													//1:RESTRICTE
													//2:WEP
													//3:WPA
													//4:WPA2
													//5:WPA-PSK
													//6:WPA2-PSK
	int		nEncryprion;							//���ܷ�ʽ
													//0:OPEN
													//1:TKIP
													//2:WEP
													//3:AES
													//4:NONE(��У��)
													//5:AUTO
	                                                //6:SHARED
	char	szKey[128];								//������Կ
	char	szHostIP[128];							//������ַ
	char	szHostNetmask[128];						//��������
	char	szHostGateway[128];						//��������
	int     nEnDHCP;                                //0����ʹ��	1��ʹ��(ɨ�赽��dhcpĬ��ʹ�ܴ�)
	BYTE    byKeyIndex;                             //WEPУ�������µ���Կ����,0����֧����Կ���� >0:��Կ����ֵ����Χ1-4
	BYTE	bReserved[1019];
} DHDEV_VEHICLE_WIFI_CONFIG;

typedef struct
{
	char    szSSID[128];                            // SSID   
	BYTE    bReserved[256];                         // �����ֽ�
}WIFI_CONNECT;

// IP�޸�����
typedef struct __DHCTRL_IPMODIFY_PARAM
{
	int                 nStructSize;
	char				szRemoteIP[DH_MAX_IPADDR_OR_DOMAIN_LEN];		// ǰ���豸IP
	char				szSubmask[DH_MAX_IPADDR_LEN];	                // ��������
	char				szGateway[DH_MAX_IPADDR_OR_DOMAIN_LEN];	        // ����
	char				szMac[DH_MACADDR_LEN];			                // MAC��ַ
	char				szDeviceType[DH_DEV_TYPE_LEN];	                // �豸����
}DHCTRL_IPMODIFY_PARAM;

typedef struct 
{
	BOOL	bIsScan;								//0:��ɨ��wifi (�ֶ����ӵ�), 1ɨ�赽��wifi
	char	szSSID[128];							//SSID
	int		nSafeType;								//У������
													//0:OPEN 
													//1:RESTRICTE
													//2:WEP
													//3:WPA
													//4:WPA2
													//5:WPA-PSK
													//6:WPA2-PSK
	int		nEncryprion;							//���ܷ�ʽ
													//0:OPEN
													//1:TKIP
													//2:WEP
													//3:AES
													//4:NONE(��У��)
													//5:AUTO
	                                                //6:SHARED
	char	szKey[128];								//������Կ
	int		nStrength;								//APվ���ź�
	int		nMaxBitRate;							//APվ������������,����λ ֻ��
	int		nIsCnnted;								//�Ƿ����ӳɹ�ֻ��
	int		nIsSaved;								//�Ƿ��Ѿ�����ֻ��
	int		nPriority;								//���ȼ�,(1-32)
	char	szHostIP[128];							//������ַ
	char	szHostNetmask[128];						//��������
	char	szHostGateway[128];						//��������
	int		nWifiFreq;								//����Ƶ�ʣ�����ͨ����ʶ
	int     nEnDHCP;                                //0����ʹ�� 1��ʹ��(ɨ�赽��dhcpĬ��ʹ�ܴ�)
	BYTE    byKeyIndex;                             //WEPУ�������µ���Կ����,0����֧����Կ���� >0:��Կ����ֵ����Χ1-4
	BYTE	bReserved[1019];
}DHDEV_VEHICLE_SINGLE_WIFI_AP_CFG;

typedef struct 
{
	BOOL	bEnable;								//�Ƿ�����wifi����, 0:��ʹ�� 1:ʹ��
	int		nWifiApNum;								//DHDEV_VEHICLE_WIFI_AP_CFG�ṹ����Ч����
	DHDEV_VEHICLE_SINGLE_WIFI_AP_CFG struWifiAp[64];//����WIFI AP����
	int	nReserved[512];								//����
}DHDEV_VEHICLE_WIFI_AP_CFG;

typedef struct  
{	
	BOOL   bEnable;									//�Ƿ�����wifi����, 0:��ʹ�� 1:ʹ��
	int    nRetWifiApNum;							//�����õ���DHDEV_VEHICLE_WIFI_AP_CFG�ṹ����Ч����
	int    nMaxWifiApNum;							//�����DHDEV_VEHICLE_SINGLE_WIFI_AP_CFG����
	DHDEV_VEHICLE_SINGLE_WIFI_AP_CFG* pWifiAp;		//����WIFI AP����
	int nReserved[512];								//����
}DHDEV_VEHICLE_WIFI_AP_CFG_EX;

// GPS��־��Ϣ�ṹ��
typedef struct _DH_DEVICE_GPS_LOG_ITEM
{
	DHDEVTIME       stuDevTime;             // �豸ʱ��  
	DWORD		    dwLatidude;				// γ��(��λ�ǰ����֮�ȣ���Χ0-180��)�籱γ30.183382�ȱ�ʾΪ120183382
	DWORD		    dwLongitude;			// ����(��λ�ǰ����֮�ȣ���Χ0-360��)�綫��120.178274�ȱ�ʾΪ300178274
	DWORD           dwSpeed;                // �ٶ�,��λ�Ǻ���,speed/1000*1.852����/Сʱ
	DWORD           dwHight;                // �߶�,��
	DWORD           dwAngle;                // ���򣬽Ƕ�0~360,��������Ϊԭ�㣬˳ʱ��Ϊ��
	DHDEVTIME       stuGpsTime;             // GPSʱ��
	BYTE            bAntStatus; 		    // GPS����״̬,Ϊ0��ʾ��;��Ϊ0��ʾ�쳣 
	BYTE            bOriStatus; 			// ��λ״̬����Ϊ0��ʾ��λ�ɹ�
	BYTE            bSatCount; 				// ��������
	BYTE            bGPSStatus; 			// GPS״̬,0,δ��λ 1,�޲�ֶ�λ��Ϣ 2,����ֶ�λ��Ϣ
	DWORD           dwTemp;                 // �¶�ֵ(���϶�),ʵ��ֵ��1000��,��30.0���϶ȱ�ʾΪ30000
	DWORD           dwHumidity;             // ʪ��ֵ(%),ʵ��ֵ��1000��,��30.0%��ʾΪ30000
	BYTE            bReserved[24];          // �����ֽ�
    
}DH_DEVICE_GPS_LOG_ITEM;

// GPS ��־��ѯ�����ṹ��
typedef struct _QUERY_GPS_LOG_PARAM
{
	NET_TIME			stuStartTime;			// ��ѯ��־�Ŀ�ʼʱ��
	NET_TIME			stuEndTime;				// ��ѯ��־�Ľ���ʱ��
	int					nStartNum;				// ��ʱ����дӵڼ�����־��ʼ��ѯ����ʼ��һ�β�ѯ����Ϊ0
	BYTE				bReserved[20];
} QUERY_GPS_LOG_PARAM;

typedef struct _GPS_TEMP_HUMIDITY_INFO
{
	double              dTemperature;          // �¶�ֵ(���϶�),ʵ��ֵ��1000��,��30.0���϶ȱ�ʾΪ30000
	double              dHumidity;             // ʪ��ֵ(%),ʵ��ֵ��1000��,��30.0%��ʾΪ30000
	BYTE                bReserved[128];        // �����ֽ�
}GPS_TEMP_HUMIDITY_INFO;

// ����Χ������ö��
typedef enum
{
	ENCLOSURE_LIMITSPEED = 0x01,	                      // ������
	ENCLOSURE_DRIVEALLOW = 0x02,						  // ��ʻ��
	ENCLOSURE_FORBIDDRIVE = 0x04,						  // ��ֹ��
	ENCLOSURE_LOADGOODS = 0x08,					          // װ����
	ENCLOSURE_UPLOADGOODS = 0x10,						  // ж����
}ENCLOSURE_TYPE;

typedef enum
{
	 ENCLOSURE_ALARM_DRIVEIN ,	                   // ʻ��
	 ENCLOSURE_ALARM_DRIVEOUT,	                   // ʻ��
	 ENCLOSURE_ALARM_OVERSPEED,				       // ����
	 ENCLOSURE_ALARM_SPEEDCLEAR,				   // ������ʧ
}ENCLOSURE_ALARM_TYPE;

typedef struct 
{
	DWORD				dwLongitude;			// ����(��λ�ǰ����֮�ȣ���Χ0-360��)�綫��120.178274�ȱ�ʾΪ300178274
    DWORD				dwLatidude;				// γ��(��λ�ǰ����֮�ȣ���Χ0-180��)�籱γ30.183382�ȱ�ʾΪ120183382
}GPS_POINT;

// ����Χ������
typedef struct _DHDEV_ENCLOSURE_CFG
{
	UINT	      unType;                              // ����Χ���������룬�� ENCLOSURE_TYPE 
	BYTE	      bRegion[8];                          // ǰ��λ�ֱ�������ҡ�ʡ���л�������(0-255)����4bytes����
	UINT          unId;                                // һ��������һ��ID��ʶ
	UINT          unSpeedLimit;                        // ���٣���λkm/h
	UINT          unPointNum;                          // ����Χ�����򶥵���
	GPS_POINT     stPoints[128];	                   // ����Χ��������Ϣ
	char          szStationName[DH_STATION_NAME_LEN];  // ����Χ����Χ�ĳ�վվ������
	BYTE		  reserved[32];                        // ����
}DHDEV_ENCLOSURE_CFG;

// ����Χ���汾������
typedef struct _DHDEV_ENCLOSURE_VERSION_CFG
{
	UINT          unType;                              // Χ���������룬��LIMITSPEED | DRIVEALLOW
    UINT          unVersion[32];                       // ÿ������һ���汾��,����ͳһƽ̨���豸�ϵ�Χ������
    int           nReserved;                           // ����    
}DHDEV_ENCLOSURE_VERSION_CFG;

// ����Χ������
typedef struct __ALARM_ENCLOSURE_INFO
{
	int           nTypeNumber;                    // ��Ч����Χ�����͸���
	BYTE          bType[16];	                  // ����Χ������, ��ENCLOSURE_TYPE
	int           nAlarmTypeNumber;               // ��Ч�������͸���
	BYTE          bAlarmType[16];                 // �������ͣ���ENCLOSURE_ALARM_TYPE
	char          szDriverId[DH_VEHICLE_DRIVERNO_LEN];  // ˾������
	UINT          unEnclosureId;      	          // ����Χ��ID
	UINT		  unLimitSpeed;	                  // ���٣���λkm/h
	UINT          unCurrentSpeed;                 // ��ǰ�ٶ�
	NET_TIME      stAlarmTime;                    // ��������ʱ��
	DWORD		  dwLongitude;					  // ����(��λ�ǰ����֮�ȣ���Χ0-360��)�綫��120.178274�ȱ�ʾΪ300178274
	DWORD         dwLatidude;					  // γ��(��λ�ǰ����֮�ȣ���Χ0-180��)�籱γ30.183382�ȱ�ʾΪ120183382
	BYTE          bOffline;                       // 0-ʵʱ 1-���� 
	BYTE          byReserved[119];                // �����ֽ�
}ALARM_ENCLOSURE_INFO;

// RAID�쳣��Ϣ
#define DH_MAX_RAID_NUM  16
typedef struct __RAID_STATE_INFO
{
	char				szName[16];							// Raid����
	BYTE				byType;								// ���� 1:Jbod     2:Raid0      3:Raid1     4:Raid5
	BYTE				byStatus;							// ״̬ 0:unknown ��1:active��2:degraded��3:inactive��4:recovering
	BYTE                byReserved[2];
	int					nCntMem;							// nMember�������Ч���ݸ���
	int					nMember[32];						// 1,2,3,... ��ɴ���ͨ��,�Ǹ�����
	int					nCapacity;							// ����,��λG
	int					nRemainSpace;						// ʣ����������λM
	int					nTank;								// ��չ�� 0:������1:��չ��1��2:��չ��2������
	char				reserved[32];
}RAID_STATE_INFO;

typedef struct __ALARM_RAID_INFO
{
	int              nRaidNumber;                     // �ϱ���RAID����   
	RAID_STATE_INFO  stuRaidInfo[DH_MAX_RAID_NUM];    // �쳣��RAID��Ϣ
	char             reserved[128];
}ALARM_RAID_INFO;

//////////////////////////////////ATM֧��//////////////////////////////////

typedef struct
{
	int					Offset;					// ��־λ��λƫ��
	int					Length;					// ��־λ�ĳ���
	char				Key[16];				// ��־λ��ֵ
} DH_SNIFFER_FRAMEID;

typedef struct 
{
	int					Offset;					// ��־λ��λƫ��
	int					Offset2;				// Ŀǰû��Ӧ��
	int					Length;					// ��־λ�ĳ���
	int					Length2;				// Ŀǰû��Ӧ��
	char				Title[12];		    	// �����ֵ
	char                Key[12];                // �ؼ��ֵ�ֵ
} DH_SNIFFER_CONTENT;

// ����ץ������
typedef struct 
{
	DH_SNIFFER_FRAMEID	snifferFrameId;			// ÿ��FRAME ID ѡ��
	DH_SNIFFER_CONTENT	snifferContent[DH_SNIFFER_CONTENT_NUM];	// ÿ��FRAME��Ӧ��4��ץ������
} DH_SNIFFER_FRAME;

// ÿ��ץ����Ӧ�����ýṹ
typedef struct
{
	char				SnifferSrcIP[DH_MAX_IPADDR_LEN];	// ץ��Դ��ַ		
	int					SnifferSrcPort;			// ץ��Դ�˿�
	char				SnifferDestIP[DH_MAX_IPADDR_LEN];	// ץ��Ŀ���ַ
	int					SnifferDestPort;		// ץ��Ŀ��˿�
	char				reserved[28];			// �����ֶ�
	DH_SNIFFER_FRAME	snifferFrame[DH_SNIFFER_FRAMEID_NUM];	// 6��FRAME ѡ��
	int					displayPosition;		// ��ʾλ��
	int					recdChannelMask;		// ͨ������
} DH_ATM_SNIFFER_CFG;

typedef struct  
{
	DWORD				dwSize;
	DH_ATM_SNIFFER_CFG	SnifferConfig[4];
	char				reserved[256];			// �����ֶ�
} DHDEV_SNIFFER_CFG;

typedef DH_SNIFFER_FRAMEID DH_SNIFFER_FRAMEID_EX;
typedef DH_SNIFFER_CONTENT DH_SNIFFER_CONTENT_EX;

// ����ץ������
typedef struct  
{
	DH_SNIFFER_FRAMEID	snifferFrameId;								// ÿ��FRAME ID ѡ��
	DH_SNIFFER_CONTENT	snifferContent[DH_SNIFFER_CONTENT_NUM_EX];	// ÿ��FRAME��Ӧ��8��ץ������	
} DH_SNIFFER_FRAME_EX;

// ÿ��ץ����Ӧ�����ýṹ
typedef struct
{
	char				SnifferSrcIP[DH_MAX_IPADDR_LEN];					// ץ��Դ��ַ		
	int					SnifferSrcPort;										// ץ��Դ�˿�
	char				SnifferDestIP[DH_MAX_IPADDR_LEN];					// ץ��Ŀ���ַ
	int					SnifferDestPort;									// ץ��Ŀ��˿�
	DH_SNIFFER_FRAME_EX	snifferFrame[DH_SNIFFER_FRAMEID_NUM];				// 6��FRAME ѡ��
	int					displayPosition;									// ��ʾλ��
	int					recdChannelMask;									// ͨ������  0  ~ 31 ͨ��
	BOOL				bDateScopeEnable;									// ������Դʹ��
	BOOL				bProtocolEnable;									// Э��ʹ��
	char				szProtocolName[DH_SNIFFER_PROTOCOL_SIZE];			// Э������
	int					nSnifferMode;										// ץ����ʽ��0:net,1:232.
	int					recdChannelMask1;									// ͨ������  32 ~ 63 ͨ��
	char				reserved[252];
} DH_ATM_SNIFFER_CFG_EX;

// Atm�������Ͳ�ѯ���ؽṹ��
#define ATM_MAX_TRADE_TYPE_NAME	64
#define ATM_MAX_TRADE_NUM		1024

typedef struct __DH_ATM_QUERY_TRADE   
{
	int					nTradeTypeNum;										// ʵ�ʽ�����������
	int					nExceptionTypeNum;									// ʵ���쳣�¼�����
	char				szSupportTradeType[ATM_MAX_TRADE_NUM][ATM_MAX_TRADE_TYPE_NAME];    // �����¼�������
	char				szSupportExceptionType[ATM_MAX_TRADE_NUM][ATM_MAX_TRADE_TYPE_NAME];// �쳣�¼�������
} DH_ATM_QUERY_TRADE, *LPDH_ATM_QUERY_TRADE;

/////////////////////////////////������֧��/////////////////////////////////
#define nEncoderID nDecoderID
#define byEncoderID byDecoderID

// ��������Ϣ
typedef struct __DEV_DECODER_INFO 
{
	char			szDecType[64];			// ����
	int				nMonitorNum;			// TV����
	int				nEncoderNum;			// ����ͨ������
	BYTE			szSplitMode[16];		// ֧�ֵ�TV����ָ�������������ʽ��ʾ��0Ϊ��β
	BYTE            bMonitorEnable[16];		// ��TVʹ��
	BYTE            bTVTipDisplay;          // ָʾ�Ƿ�֧��TV��ʾ��Ϣ��������, 0:��֧�� 1:֧��.
	BYTE            reserved1[3];
	BYTE            byLayoutEnable[48];     // ������ͨ����ʾ������Ϣʹ��
	char			reserved[12];
} DEV_DECODER_INFO, *LPDEV_DECODER_INFO;

//#define NANJINGDITIE_NVD
#ifndef NANJINGDITIE_NVD
// ���ӵı�������Ϣ
typedef struct __DEV_ENCODER_INFO 
{
	char			szDevIp[DH_MAX_IPADDR_LEN];			// ǰ��DVR��IP��ַ
	WORD			wDevPort;							// ǰ��DVR�Ķ˿ں�
	BYTE			bDevChnEnable;                      // ����ͨ��ʹ��
	BYTE			byDecoderID;						// ��Ӧ����ͨ����
	char			szDevUser[DH_USER_NAME_LENGTH_EX];	// �û���
	char			szDevPwd[DH_USER_PSW_LENGTH_EX];	// ����
	int				nDevChannel;						// ͨ����
	int				nStreamType;						// �������ͣ�0����������1��������; 2:snap
	BYTE			byConnType;							// -1: auto, 0��TCP��1��UDP��2���鲥
	BYTE			byWorkMode;							// 0��ֱ����1��ת��
	WORD			wListenPort;						// ָʾ��������Ķ˿ڣ�ת��ʱ��Ч
	DWORD			dwProtoType;						// Э������,
														// 0:������ǰ
														// 1:�󻪶���Э��
														// 2:��ϵͳ����Э��
														// 3:��DSSЭ��
														// 4:��rtspЭ��
	char			szDevName[64];						// ǰ���豸����
	BYTE            byVideoInType;                      // �ý���ͨ����ǰ��ƵԴ����:0-����(SD),1-����(HD),ע:�豸֧�ָ���ͨ������Ч		
	char			szDevIpEx[DH_MAX_IPADDR_OR_DOMAIN_LEN];// szDevIp��չ��ǰ��DVR��IP��ַ(������������)
	BYTE            bySnapMode;                         //ץͼģʽ(nStreamType==2ʱ��Ч) 0����ʾ����һ֡,1����ʾ��ʱ��������
	BYTE            byManuFactory;						//Ŀ���豸����������,����ο�EM_IPC_TYPE��
	BYTE            byDeviceType;                       //Ŀ���豸���豸����,0:IPC
	BYTE            byDecodePolicy;                     //Ŀ���豸�Ľ������,0:������ǰ
														// 1:ʵʱ�ȼ��� 2:ʵʱ�ȼ���
														// 3:ʵʱ�ȼ��� 4:Ĭ�ϵȼ�
														// 5:�����ȼ��� 6:�����ȼ���
														// 7:�����ȼ���
	BYTE            bReserved[3];                       // �����ֽ�
	DWORD           dwHttpPort;                         // Http�˿ں�,0-65535
	DWORD           dwRtspPort;                         // Rtsp�˿ں�,0-65535
	char			szChnName[32];						// Զ��ͨ������, ֻ�ж�ȡ�������Ʋ�Ϊ��ʱ�ſ����޸ĸ�ͨ��������
	char			reserved[4];
} DEV_ENCODER_INFO, *LPDEV_ENCODER_INFO;

#else

// ���ӵı�������Ϣ
typedef struct __DEV_ENCODER_INFO 
{
	char			szDevIp[DH_MAX_IPADDR_LEN];			// ǰ��DVR��IP��ַ
	WORD			wDevPort;							// ǰ��DVR�Ķ˿ں�
	BYTE			bDevChnEnable;                      // ����ͨ��ʹ��
	BYTE			byDecoderID;						// ��Ӧ����ͨ����
	char			szDevUser[DH_USER_NAME_LENGTH_EX];	// �û���
	char			szDevPwd[DH_USER_PSW_LENGTH_EX];	// ����
	int				nDevChannel;						// ͨ����
	int				nStreamType;						// �������ͣ�0����������1��������; 2:snap
	BYTE			byConnType;							// -1: auto, 0��TCP��1��UDP��2���鲥
	BYTE			byWorkMode;							// 0��ֱ����1��ת��
	WORD			wListenPort;						// ָʾ��������Ķ˿ڣ�ת��ʱ��Ч;byConnTypeΪ�鲥ʱ������Ϊ�ಥ�˿�
	DWORD			dwProtoType;						// Э������,
														// 0:������ǰ
														// 1:�󻪶���Э��
														// 2:��ϵͳ����Э��
														// 3:��DSSЭ��
														// 4:��rtspЭ��
														// 5:��׼TS��
	char			szDevName[32];						// ǰ���豸����
	BYTE            byVideoInType;                      // �ý���ͨ����ǰ��ƵԴ����:0-����(SD),1-����(HD),ע:�豸֧�ָ���ͨ������Ч		
	char			szDevIpEx[DH_MAX_IPADDR_OR_DOMAIN_LEN];// szDevIp��չ��ǰ��DVR��IP��ַ(������������)
	BYTE            bySnapMode;                         //ץͼģʽ(nStreamType==2ʱ��Ч) 0����ʾ����һ֡,1����ʾ��ʱ��������
	BYTE            byManuFactory;						//Ŀ���豸����������,����ο�EM_IPC_TYPE��
	BYTE            byDeviceType;                       //Ŀ���豸���豸����,0:IPC
	BYTE            byDecodePolicy;                     //Ŀ���豸�Ľ������,0:������ǰ
														// 1:ʵʱ�ȼ��� 2:ʵʱ�ȼ���
														// 3:ʵʱ�ȼ��� 4:Ĭ�ϵȼ�
														// 5:�����ȼ��� 6:�����ȼ���
														// 7:�����ȼ���
	BYTE            bReserved[3];                       // �����ֽ�
	DWORD           dwHttpPort;                         // Http�˿ں�,0-65535
	DWORD           dwRtspPort;                         // Rtsp�˿ں�,0-65535
	char			szChnName[32];						// Զ��ͨ������, ֻ�ж�ȡ�������Ʋ�Ϊ��ʱ�ſ����޸ĸ�ͨ��������
	char			szMcastIP[DH_MAX_IPADDR_LEN];       // �ಥIP��ַ,byConnTypeΪ�鲥ʱ��Ч
	char            reserved[128];
} DEV_ENCODER_INFO, *LPDEV_ENCODER_INFO;

#endif

// ������rtsp url����
typedef struct __DHDEV_DECODER_URL_CFG
{
	DWORD			dwSize;
	char			szMainStreamUrl[MAX_PATH];			// ������url
	char			szExtraStreamUrl[MAX_PATH];			// ������url
} DHDEV_DECODER_URL_CFG;

// TV������Ϣ
typedef struct __DEV_DECODER_TV 
{
	int				nID;								// TV��
	BOOL			bEnable;							// ʹ�ܣ�������ر�
	int				nSplitType;							// ����ָ���
	DEV_ENCODER_INFO stuDevInfo[16];					// �������������Ϣ
	BYTE			bySupportSplit[10];					// ֧�ֵķָ�ģʽ
	char			reserved[6];
} DEV_DECODER_TV, *LPDEV_DECODER_TV;

// ���������������Ϣ
typedef struct __DEC_COMBIN_INFO
{
	int				nCombinID;							// ���ID
	int             nSplitType;							// ����ָ��� 
	BYTE            bDisChn[16];						// ��ʾͨ��
	char			reserved[16];
} DEC_COMBIN_INFO, *LPDEC_COMBIN_INFO;

// ��������Ѳ��Ϣ
#define DEC_COMBIN_NUM 			32						// ��Ѳ��ϸ���
typedef struct __DEC_TOUR_COMBIN 
{
	int				nTourTime;							// ��Ѳ���(��)
	int				nCombinNum;							// ��ϸ���
	BYTE			bCombinID[DEC_COMBIN_NUM];			// ��ϱ�
	char			reserved1[32];
	BYTE			bCombinState[DEC_COMBIN_NUM];		// ������ʹ��״̬��0���أ�1����
	char			reserved2[32];
} DEC_TOUR_COMBIN, *LPDEC_TOUR_COMBIN;

// �������ط�����
typedef enum __DEC_PLAYBACK_MODE
{
	Dec_By_Device_File = 0,								// ǰ���豸�����ļ���ʽ
	Dec_By_Device_Time,									// ǰ���豸����ʱ�䷽ʽ
} DEC_PLAYBACK_MODE;

// �������طſ�������
typedef enum __DEC_CTRL_PLAYBACK_TYPE
{
	Dec_Playback_Seek = 0,								// �϶�
	Dec_Playback_Play,									// ����
	Dec_Playback_Pause,									// ��ͣ
	Dec_Playback_Stop,									// ֹͣ
} DEC_CTRL_PLAYBACK_TYPE;

//��Ѳ��������
typedef enum __DEC_CTRL_TOUR_TYPE
{
	Dec_Tour_Stop = 0,									// ֹͣ
	Dec_Tour_Start,										// ��ʼ
	Dec_Tour_Pause,										// ��ͣ
	Dec_Tour_Resume,									// �ָ�
} DEC_CTRL_TOUR_TYPE;

// ���ļ��ط�ǰ���豸����
typedef struct __DEC_PLAYBACK_FILE_PARAM 
{
	char			szDevIp[DH_MAX_IPADDR_LEN];			// ǰ��DVR��IP��ַ
	WORD			wDevPort;							// ǰ��DVR�Ķ˿ں�
	BYTE			bDevChnEnable;                      // ����ͨ��ʹ��
	BYTE			byDecoderID;						// ��Ӧ����ͨ����
	char			szDevUser[DH_USER_NAME_LENGTH_EX];	// �û���
	char			szDevPwd[DH_USER_PSW_LENGTH_EX];	// ����
	NET_RECORDFILE_INFO stuRecordInfo;					// ¼���ļ���Ϣ
	char			reserved[12];
} DEC_PLAYBACK_FILE_PARAM, *LPDEC_PLAYBACK_FILE_PARAM;

// ��ʱ��ط�ǰ���豸����
typedef struct __DEC_PLAYBACK_TIME_PARAM 
{
	char			szDevIp[DH_MAX_IPADDR_LEN];			// ǰ��DVR��IP��ַ
	WORD			wDevPort;							// ǰ��DVR�Ķ˿ں�
	BYTE			bDevChnEnable;                      // ����ͨ��ʹ��
	BYTE			byDecoderID;						// ��Ӧ����ͨ����
	char			szDevUser[DH_USER_NAME_LENGTH_EX];	// �û���
	char			szDevPwd[DH_USER_PSW_LENGTH_EX];	// ����
	int				nChannelID;
	NET_TIME		startTime;
	NET_TIME		endTime;
	char			reserved[12];
} DEC_PLAYBACK_TIME_PARAM, *LPDEC_PLAYBACK_TIME_PARAM;

// ��ǰ����ͨ��״̬��Ϣ(����ͨ��״̬����������Ϣ��)
typedef struct __DEV_DECCHANNEL_STATE
{
	BYTE			byDecoderID;						// ��Ӧ����ͨ����
	BYTE            byChnState;                         // ��ǰ����ͨ�����ڲ���״̬:0�����У�1��ʵʱ���ӣ�2���ط� 3 - ��Ѳ
	BYTE			byFrame;                            // ��ǰ����֡��
	BYTE            byReserved;                         // ����
	int				nChannelFLux;						// ����ͨ����������
	int             nDecodeFlux;						// ����������
	char            szResolution[16];                   // ��ǰ���ݷֱ���
	char			reserved[256];
} DEV_DECCHANNEL_STATE, *LPDEV_DECCHANNEL_STATE;

// �豸TV���������Ϣ
typedef struct __DEV_VIDEOOUT_INFO
{
	DWORD				dwVideoStandardMask;			// NSP,��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ(�ݲ�֧��)
	int					nVideoStandard;                 // NSP,��ǰ����ʽ(�ݲ�֧�֣���ʹ��DHDEV_SYSTEM_ATTR_CFG��byVideoStandard����ʽ��ȡ������)
	DWORD				dwImageSizeMask;				// �ֱ������룬��λ��ʾ�豸�ܹ�֧�ֵķֱ���
	int                 nImageSize;                     // ��ǰ�ķֱ���
	char				reserved[256];
}DEV_VIDEOOUT_INFO, *LPDEV_VIDEOOUT_INFO;

// ����TV���
typedef struct __DEV_TVADJUST_CFG
{
	int					nTop;							// �ϲ�߾ࣨ0��100��
	int					nBotton;						// �²�߾ࣨ0��100��
	int					nLeft;							// ���߾ࣨ0��100��
	int                 nRight;							// �Ҳ�߾ࣨ0��100��
	int					reserved[32];
}DHDEV_TVADJUST_CFG, *LPDHDEV_TVADJUST_CFG;

// ������Ѳ����
typedef struct __DEV_DECODER_TOUR_SINGLE_CFG
{
	char		szIP[128];								// ǰ���豸ip.����"10.7.5.21". ������������֧��.��Ҫ��'\0'����.
	int			nPort;									// ǰ���豸�˿�.(0, 65535).
	int			nPlayChn;								// ����ǰ���豸ͨ��[1, 16].
	int			nPlayType;								// ����ǰ����������, 0:������; 1:������.
	char		szUserName[32];							// ��½ǰ���豸���û���,��Ҫ��'\0'����.
	char		szPassword[32];							// ��½ǰ���豸������,��Ҫ��'\0'����.
	int			nInterval;								// ��Ѳ���ʱ��[10, 120],��λ��.
	DWORD		nManuFactory;							// Ŀ���豸����(ö�� ���IPC_TYPE)
	UINT		nHttpPport;								// Ŀ���豸�Ķ˿�(Http�˿�)
	UINT		nRtspPort;								// Ŀ���豸�Ķ˿�(Rtsp�˿�)
	BYTE		byServiceType;							// ��������, -1: auto, 0��TCP��1��UDP��2���鲥
	BYTE		bReserved[51];							// �����ֽ�,������չ.
}DHDEV_DECODER_TOUR_SINGLE_CFG;

typedef struct __DEV_DECODER_TOUR_CFG
{
	int								nCfgNum;			// ���ýṹ����Ŀ. �������֧��32��.����֧����Ŀ����ͨ��������ѯ.
	DHDEV_DECODER_TOUR_SINGLE_CFG	tourCfg[64];		// ��ѯ��������,��Ч�ṹ������ɳ�Ա"nCfgNum"ָ��. ����32��������չ.
	BYTE							bReserved[256];		// �����ֽ�,������չ.
}DHDEV_DECODER_TOUR_CFG;

/////////////////////////////////����֧��/////////////////////////////////
// �����ӦͼƬ�ļ���Ϣ
typedef struct  
{
	DWORD                dwOffSet;                       // �ļ��ڶ��������ݿ��е�ƫ��λ��, ��λ:�ֽ�
	DWORD                dwFileLenth;                    // �ļ���С, ��λ:�ֽ�
	WORD                 wWidth;                         // ͼƬ����, ��λ:����
	WORD                 wHeight;                        // ͼƬ�߶�, ��λ:����
	BYTE                 bReserved[16];                 
}DH_PIC_INFO;

// ��Ƶ����������Ϣ�ṹ��
typedef struct 
{
	int					nObjectID;						// ����ID,ÿ��ID��ʾһ��Ψһ������
	char				szObjectType[128];				// ��������
	int					nConfidence;					// ���Ŷ�(0~255)��ֵԽ���ʾ���Ŷ�Խ��
	int					nAction;						// ���嶯��:1:Appear 2:Move 3:Stay 4:Remove 5:Disappear 6:Split 7:Merge 8:Rename
	DH_RECT				BoundingBox;					// ��Χ��
	DH_POINT			Center;							// ��������
	int					nPolygonNum;					// ����ζ������
	DH_POINT			Contour[DH_MAX_POLYGON_NUM];	// �Ͼ�ȷ�����������
	DWORD				rgbaMainColor;					// ��ʾ���ơ�������������Ҫ��ɫ�����ֽڱ�ʾ���ֱ�Ϊ�졢�̡�����͸����,����:RGBֵΪ(0,255,0),͸����Ϊ0ʱ, ��ֵΪ0x00ff0000.
    char				szText[128];					// ��������صĴ�0�������ı������糵�ƣ���װ��ŵȵ�
														// "ObjectType"Ϊ"Vehicle"����"Logo"ʱ������ʹ��Logo��Vehicle��Ϊ�˼����ϲ�Ʒ����ʾ���֧꣬�֣�
														// "Unknown"δ֪ 
														// "Audi" �µ�
														// "Honda" ����
														// "Buick" ���
														// "Volkswagen" ����
														// "Toyota" ����
														// "BMW" ����
														// "Peugeot" ����
														// "Ford" ����
														// "Mazda" ���Դ�
														// "Nissan" ��ɣ
														// "Hyundai" �ִ�
														// "Suzuki" ��ľ
														// "Citroen" ѩ����
														// "Benz" ����
														// "BYD" ���ǵ�
														// "Geely" ����
														// "Lexus" �׿���˹
														// "Chevrolet" ѩ����
														// "Chery" ����
														// "Kia" ����
														// "Charade" ����
														// "DF" ����
														// "Naveco" ��ά��
														// "SGMW" ����
														// "Jinbei" ��

	char                szObjectSubType[64];            // ��������𣬸��ݲ�ͬ���������ͣ�����ȡ���������ͣ�
														// Vehicle Category:"Unknown"  δ֪,"Motor" ������,"Non-Motor":�ǻ�����,"Bus": ������,"Bicycle" ���г�,"Motorcycle":Ħ�г�,"PassengerCar":�ͳ�,
														// "LargeTruck":�����,	"MidTruck":�л���,"SaloonCar":�γ�,"Microbus":�����,"MicroTruck":С����,"Tricycle":���ֳ�,	"Passerby":����													
														// Plate Category��"Unknown" δ֪,"Normal" ���ƺ���,"Yellow" ����,"DoubleYellow" ˫���β��,"Police" ����"Armed" �侯��,
														// "Military" ���Ӻ���,"DoubleMilitary" ����˫��,"SAR" �۰���������,"Trainning" ����������
														// "Personal" ���Ժ���,"Agri" ũ����,"Embassy" ʹ�ݺ���,"Moto" Ħ�г�����,"Tractor" ����������,"Other" ��������
														// HumanFace Category:"Normal" ��ͨ����,"HideEye" �۲��ڵ�,"HideNose" �����ڵ�,"HideMouth" �첿�ڵ�
	BYTE                byReserved1[3];
	bool                bPicEnble;                      // �Ƿ��������ӦͼƬ�ļ���Ϣ
	DH_PIC_INFO         stPicInfo;                      // �����ӦͼƬ��Ϣ
	bool				bShotFrame;						// �Ƿ���ץ���ŵ�ʶ����
	bool				bColor;							// ������ɫ(rgbaMainColor)�Ƿ����
	BYTE				byReserved2[2];
	NET_TIME_EX			stuCurrentTime;					// �����ƵŨ������ǰʱ���������ץ�Ļ�ʶ��ʱ���Ὣ��ʶ������֡����һ����Ƶ֡��jpegͼƬ�У���֡����ԭʼ��Ƶ�еĳ���ʱ�䣩
	NET_TIME_EX			stuStartTime;					// ��ʼʱ��������忪ʼ����ʱ��
	NET_TIME_EX			stuEndTime;						// ����ʱ���������������ʱ��
	DH_RECT				stuOriginalBoundingBox;			// ��Χ��(��������)
	DH_RECT             stuSignBoundingBox;             // ���������Χ��
	BYTE				byReserved[78];
} DH_MSG_OBJECT;

// ץ����Ϣ
typedef struct
{
	short              snSpeed;                          // ��ǰ�����ٶȣ�km/h
	short              snCarLength;                      // ��ǰ����,����Ϊ��λ
	float              fRedTime;                        // ��ǰ�������ʱ��,��.����
	float              fCapTime;                        // ��ǰ����ץ��ʱ��,��.���� 
	BYTE               bSigSequence;                    // ��ǰץ�����
	BYTE               bType;                           // ��ǰ������ץ������
														// 0: �״������;1: �״������;2: ������������;3:������������
		                                                // 4: ����;5: �����;6: �����;7: �����;8: ȫ��ץ�Ļ��߿���
	BYTE               bDirection;                      // ���������:01:��ת���;02:ֱ�к��;03:��ת���
	BYTE               bLightColor;                     // ��ǰ�����ĺ��̵�״̬��0: �̵�, 1: ���, 2: �Ƶ�
	BYTE               bSnapFlag[16];                   // �豸������ץ�ı�ʶ
}DH_SIG_CARWAY_INFO;

// ������������Ϣ
typedef struct
{
	BYTE                byRedundance[8];                // �ɳ���������ץ���ź�������Ϣ
	BYTE                bReserved[120];                  // �����ֶ�
}DH_SIG_CARWAY_INFO_EX;

// ÿ�������������Ϣ
typedef struct  
{
	BYTE                bCarWayID;                           // ��ǰ������ 
	BYTE                bReserve[2];                         // �����ֶ�
	BYTE                bSigCount;                           // ������ץ�ĵĸ���
	DH_SIG_CARWAY_INFO  stuSigInfo[DH_MAX_SNAP_SIGNAL_NUM];  // ��ǰ�����ϣ�������ץ�Ķ�Ӧ��ץ����Ϣ	
	BYTE                bReserved[12];                       // �����ֶ�
}DH_CARWAY_INFO;

// �¼���Ӧ�ļ���Ϣ
typedef struct  
{
	BYTE               bCount;                               // ��ǰ�ļ������ļ����е��ļ�����
	BYTE               bIndex;                               // ��ǰ�ļ����ļ����е��ļ����
	BYTE               bFileTag;                             // �ļ���ǩ������˵����ö������EM_EVENT_FILETAG
	BYTE               bFileType;                            // �ļ����ͣ�0-��ͨ 1-�ϳ� 2-��ͼ
	NET_TIME_EX        stuFileTime;                          // �ļ�ʱ��
	DWORD              nGroupId;                             // ͬһ��ץ���ļ���Ψһ��ʶ
}DH_EVENT_FILE_INFO;

// ͼƬ�ֱ���
typedef struct
{
	unsigned short   snWidth;    // ��
 	unsigned short   snHight;    // ��
}DH_RESOLUTION_INFO;

// ��Ա��Ϣ
typedef struct
{
	char                szPersonName[DH_MAX_NAME_LEN];					// ����                 
	WORD				wYear;											// ������
	BYTE				byMonth;										// ������
	BYTE				byDay;											// ������
	char                szID[32];										// ��ԱΨһ��ʾ(����֤���룬���ţ����������)
	BYTE                bImportantRank;									// ��Ա��Ҫ�ȼ�,1~10����ֵԽ��Խ��Ҫ
	BYTE                bySex;											// �Ա�0-�У�1-Ů 
	WORD                wFacePicNum;									// ͼƬ����
	DH_PIC_INFO         szFacePicInfo[DH_MAX_PERSON_IMAGE_NUM];         // ��ǰ��Ա��Ӧ��ͼƬ��Ϣ
	BYTE                bReserved[256];
}FACERECOGNITION_PERSON_INFO;

// ��ѡ��Ա��Ϣ
typedef struct
{
	FACERECOGNITION_PERSON_INFO  stPersonInfo;            // ��Ա��Ϣ
	BYTE                         bySimilarity;            // �Ͳ�ѯͼƬ�����ƶ�
	BYTE                         byReserved[127];         // �����ֽ�
}CANDIDATE_INFO;

// TrafficCar ��ͨ������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_TRAFFICCAR_INFO
{
	char               szPlateNumber[32];               // ���ƺ���
	char               szPlateType[32];                 // ��������	�μ�VideoAnalyseRule�г������Ͷ���
	char               szPlateColor[32];                // ������ɫ	"Blue","Yellow", "White","Black"
	char               szVehicleColor[32];              // ������ɫ	"White", "Black", "Red", "Yellow", "Gray", "Blue","Green"
	int                nSpeed;                          // �ٶ�	��λKm/H
	char               szEvent[64];                     // ����������¼�	�μ��¼��б�Event List��ֻ������ͨ����¼���
	char               szViolationCode[32];             // Υ�´���	���TrafficGlobal.ViolationCode
	char               szViolationDesc[64];             // Υ������
	int                nLowerSpeedLimit;                // �ٶ�����
	int                nUpperSpeedLimit;                // �ٶ�����
	int                nOverSpeedMargin;                // �޸��ٿ���ֵ	��λ��km/h 
	int                nUnderSpeedMargin;               // �޵��ٿ���ֵ	��λ��km/h 
	int                nLane;                           // ����	�μ��¼��б�Event List�п��ں�·���¼���
	int                nVehicleSize;                    // ������С,-1��ʾδ֪������λ��0λ:"Light-duty",��1λ:"Medium",��2λ:"Oversize"
	float              fVehicleLength;                  // ��������	��λ��
	int                nSnapshotMode;                   // ץ�ķ�ʽ	0-δ���࣬1-ȫ����2-������4-ͬ��ץ�ģ�8-����ץ�ģ�16-����ͼ��
	char               szChannelName[32];               // ���ػ�Զ�̵�ͨ�����ƣ������ǵص���Ϣ	��Դ��ͨ����������ChannelTitle.Name 
	char               szMachineName[256];              // ���ػ�Զ���豸����	��Դ����ͨ����General.MachineName
	char               szMachineGroup[256];             // �����������豸������λ	Ĭ��Ϊ�գ��û����Խ���ͬ���豸��Ϊһ�飬���ڹ��������ظ���
	char               szRoadwayNo[64];                 // ��·���
	char               szDrivingDirection[3][DH_MAX_DRIVINGDIRECTION];      // 
	                                                                        // "DrivingDirection" : ["Approach", "�Ϻ�", "����"],��ʻ����
	                                                                        // "Approach"-���У����������豸�����Խ��Խ����"Leave"-���У�
	                                                                        // ���������豸�����Խ��ԽԶ���ڶ��͵����������ֱ�������к�
	                                                                        // ���е������ص�
	char              *szDeviceAddress;                 // �豸��ַ,OSD���ӵ�ͼƬ�ϵ�,��Դ������TrafficSnapshot.DeviceAddress,'\0'����
 
	BYTE               bReserved[1024];                 // �����ֽ�,������չ.
}DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO;

// �¼�����EVENT_IVS_CROSSLINEDETECTION(�������¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_CROSSLINE_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	DH_POINT            DetectLine[DH_MAX_DETECT_LINE_NUM];    // ��������
	int                 nDetectLineNum;                        // �������߶�����
	DH_POINT            TrackLine[DH_MAX_TRACK_LINE_NUM];      // �����˶��켣
	int                 nTrackLineNum;                         // �����˶��켣������
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                bDirection;                     // ��ʾ���ַ���, 0-��������, 1-��������
	BYTE                byReserved[2];
	DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[612];					// �����ֽ�,������չ.

} DEV_EVENT_CROSSLINE_INFO;

// �¼�����EVENT_IVS_CROSSREGIONDETECTION(�������¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_CROSSREGION_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved2[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	int                 nDetectRegionNum;                          // ���������򶥵���
	DH_POINT            TrackLine[DH_MAX_TRACK_LINE_NUM];          // �����˶��켣
	int                 nTrackLineNum;                             // �����˶��켣������
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                bDirection;                     // ��ʾ���ַ���, 0-����, 1-�뿪��2-���֣�3-�뿪
	BYTE                bActionType;                    // ��ʾ��⶯������,0-���� 1-��ʧ 2-�������� 3-��Խ����
	BYTE				bReserved1[1];					// �����ֽ�
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[540];					// �����ֽ�,������չ.
	int                 nObjectNum;                     // ��⵽���������
	DH_MSG_OBJECT		stuObjectIDs[DH_MAX_OBJECT_LIST];	// ��⵽������
	int                 nTrackNum;                          // �켣��(���⵽�����������Ӧ)
	DH_POLY_POINTS      stuTrackInfo[DH_MAX_OBJECT_LIST];   // �켣��Ϣ(���⵽�������Ӧ)
} DEV_EVENT_CROSSREGION_INFO;

// �¼�����EVENT_IVS_PASTEDETECTION(�����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_PASTE_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	BYTE				bReserved[888];			    	// �����ֽ�,������չ.

} DEV_EVENT_PASTE_INFO;

// �¼�����EVENT_IVS_LEFTDETECTION(��Ʒ�����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_LEFT_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[624];			    	// �����ֽ�,������չ.

} DEV_EVENT_LEFT_INFO;

// �¼�����EVENT_IVS_PRESERVATION(��Ʒ��ȫ�¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_PRESERVATION_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[624];			    	// �����ֽ�,������չ.

} DEV_EVENT_PRESERVATION_INFO;

// �¼�����EVENT_IVS_STAYDETECTION(ͣ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_STAY_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[624];			    	// �����ֽ�,������չ.

} DEV_EVENT_STAY_INFO;

// �¼�����EVENT_IVS_WANDERDETECTION(�ǻ��¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_WANDER_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];                  // �����ֽ�
	int                 nObjectNum;                     // ��⵽���������
	DH_MSG_OBJECT		stuObjectIDs[DH_MAX_OBJECT_LIST];	// ��⵽������
	int                 nTrackNum;                      // �켣��(���⵽�����������Ӧ)
	DH_POLY_POINTS      stuTrackInfo[DH_MAX_OBJECT_LIST];// �켣��Ϣ(���⵽�������Ӧ)
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[760];					// �����ֽ�,������չ.

} DEV_EVENT_WANDER_INFO;

// �¼�����EVENT_IVS_MOVEDETECTION(�ƶ��¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_MOVE_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[624];					// �����ֽ�,������չ.

} DEV_EVENT_MOVE_INFO;

// �¼�����EVENT_IVS_TAILDETECTION(β���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TAIL_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[624];					// �����ֽ�,������չ.

} DEV_EVENT_TAIL_INFO;

// �¼�����EVENT_IVS_RIOTERDETECTION(�����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_RIOTER_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nObjectNum;						// ��⵽���������
	DH_MSG_OBJECT		stuObjectIDs[DH_MAX_OBJECT_LIST];	// ��⵽�������б�
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];                  // �����ֽ�
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������

    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[628];					// �����ֽ�,������չ.

} DEV_EVENT_RIOTERL_INFO;

// �¼�����EVENT_IVS_FIGHTDETECTION(��Ź�¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_FIGHT_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nObjectNum;						// ��⵽���������
	DH_MSG_OBJECT		stuObjectIDs[DH_MAX_OBJECT_LIST];	// ��⵽�������б�
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];                  // �����ֽ�
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[628];					// �����ֽ�,������չ.

} DEV_EVENT_FIGHT_INFO;

// �¼�����EVENT_IVS_FIREDETECTION(���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_FIRE_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];                  // �����ֽ�
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[624];					// �����ֽ�,������չ.

} DEV_EVENT_FIRE_INFO;

// �¼����� EVENT_IVS_FIREDETECTION(����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_ELECTROSPARK_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	BYTE				bReserved[972];					// �����ֽ�,������չ.
	
} DEV_EVENT_ELECTROSPARK_INFO;

// �¼�����EVENT_IVS_SMOKEDETECTION(���������¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_SMOKE_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	BYTE				bReserved[972];					// �����ֽ�,������չ.

} DEV_EVENT_SMOKE_INFO;

// �¼�����EVENT_IVS_FLOWSTAT(����ͳ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_FLOWSTAT_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nNumberLeft;					// ����ߴ�Խ���˵ĸ���
	int					nNumberRight;					// ���ұߴ�Խ���˵ĸ���
	int					nUpperLimit;					// ���õ�����
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	BYTE				bReserved[976];					// �����ֽ�,������չ.

} DEV_EVENT_FLOWSTAT_INFO;

// �¼�����EVENT_IVS_NUMBERSTAT(����ͳ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_NUMBERSTAT_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved2[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nNumber;						// ����������ĸ���
	int					nUpperLimit;					// ���õ�����
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE				bReserved1[3];					// �ֽڶ���
	int                 nEnteredNumber;                 // ��ʾ����������߳���ڵ�������ĸ���
	int                 nExitedNumber;                  // ��ʾ����������߳���ڵ�������ĸ���
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	BYTE				bReserved[964];					// �����ֽ�,������չ.

} DEV_EVENT_NUMBERSTAT_INFO;

// �¼�����EVENT_IVS_CROSSFENCEDETECTION(��ԽΧ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_CROSSFENCEDETECTION_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	int					nUpstairsLinePointNumber;		               // Χ���ϱ��߶�����
	DH_POINT		    stuUpstairsLine[DH_MAX_DETECT_LINE_NUM];	   // Χ���ϱ�����Ϣ
	int					nDownstairsLinePointNumber;		               // Χ���±��߶�����
	DH_POINT		    stuDownstairsLine[DH_MAX_DETECT_LINE_NUM];     // Χ���±�����Ϣ  
	int                 nTrackLineNum;                                 // �����˶��켣������                 
	DH_POINT            TrackLine[DH_MAX_TRACK_LINE_NUM];              // �����˶��켣
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                bDirection;                     // ��ʾ���ַ���, 0-��������, 1-��������
	BYTE                byReserved[2];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[752];				    // �����ֽ�,������չ.
	
} DEV_EVENT_CROSSFENCEDETECTION_INFO;

// �¼�����EVENT_IVS_INREGIONDETECTION(�����ڼ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_INREGIONDETECTION_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int                 nObjectNum;                     // ��⵽���������
	DH_MSG_OBJECT		stuObjectIDs[DH_MAX_OBJECT_LIST];	// ��⵽������
	int                 nTrackNum;                      // �켣��(���⵽�����������Ӧ)
	DH_POLY_POINTS      stuTrackInfo[DH_MAX_OBJECT_LIST];// �켣��Ϣ(���⵽�������Ӧ)
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	BYTE				bReserved[1016];				// �����ֽ�,������չ.
	
} DEV_EVENT_INREGIONDETECTION_INFO;

// �¼�����EVENT_IVS_TAKENAWAYDETECTION(��Ʒ�����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TAKENAWAYDETECTION_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[752];                 // �����ֽ�,������չ.
	
} DEV_EVENT_TAKENAWAYDETECTION_INFO;

// �¼�����EVENT_IVS_VIDEOABNORMALDETECTION(��Ƶ�쳣�¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_VIDEOABNORMALDETECTION_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                bType;                          // �쳣����, 0-��Ƶ��ʧ, 1-��Ƶ����, 2-����ͷ�ڵ�, 3-����ͷ�ƶ�, 4-����, 5-����
	BYTE                byReserved[2];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[756];				    // �����ֽ�,������չ.
	
} DEV_EVENT_VIDEOABNORMALDETECTION_INFO;

// �¼�����EVENT_IVS_PARKINGDETECTION(�Ƿ�ͣ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_PARKINGDETECTION_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[752];                 // �����ֽ�,������չ.
	
} DEV_EVENT_PARKINGDETECTION_INFO;

// �¼�����EVENT_IVS_ABNORMALRUNDETECTION(�쳣�����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_ABNORMALRUNDETECTION 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	double              dbSpeed;                        // �����˶��ٶ�,km/h
	double              dbTriggerSpeed;                 // �����ٶ�,km/h
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	int                 nTrackLineNum;                         // �����˶��켣������                 
	DH_POINT            TrackLine[DH_MAX_TRACK_LINE_NUM];      // �����˶��켣
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                bRunType;                       // �쳣��������, 0-���ٱ���, 1-ͻȻ����, 2-ͻȻ����
	BYTE                byReserved[2];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[752];				    // �����ֽ�,������չ.
	
} DEV_EVENT_ABNORMALRUNDETECTION_INFO;

// �¼�����EVENT_IVS_RETROGRADEDETECTION(��Ա�����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_RETROGRADEDETECTION_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	int                 nTrackLineNum;                           // �����˶��켣������                 
	DH_POINT            TrackLine[DH_MAX_TRACK_LINE_NUM];        // �����˶��켣
	int                 nDirectionPointNum;                      // ������涨�ķ��򶥵���
	DH_POINT            stuDirections[DH_MAX_DETECT_LINE_NUM];   // ������涨�ķ���
	int                 nDetectRegionNum;				         // ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];  // ����������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[752];				    // �����ֽ�,������չ.
	
} DEV_EVENT_RETROGRADEDETECTION_INFO;

// �¼�����EVENT_IVS_FACERECOGNITION(����ʶ��)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_FACERECOGNITION_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	int                 nCandidateNum;                  // ��ǰ����ƥ�䵽�ĺ�ѡ��������
    CANDIDATE_INFO      stuCandidates[DH_MAX_CANDIDATE_NUM]; // ��ǰ����ƥ�䵽�ĺ�ѡ������Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE				bReserved[1023];				// �����ֽ�,������չ.
}DEV_EVENT_FACERECOGNITION_INFO;

// �¼�����EVENT_IVS_DENSITYDETECTION(��Ա�ܶȼ��)��Ӧ���ݿ�������Ϣ
typedef struct tagDEV_EVENT_DENSITYDETECTTION_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nObjectNum;						// ��⵽���������
	DH_MSG_OBJECT		stuObjectIDs[DH_MAX_OBJECT_LIST];	// ��⵽�������б�
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];                  // �����ֽ�
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[756];					// �����ֽ�,������չ.
}DEV_EVENT_DENSITYDETECTION_INFO;

// �¼����� EVENT_IVS_QUEUEDETECTION(�ŶӼ�ⱨ���¼�)��Ӧ���ݿ�������Ϣ
typedef struct tagDEV_EVENT_QUEUEDETECTION_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved2[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE				bReserved1[3];				    // �����ֽ�,������չ.
	DH_POINT            stuDetectLine[2];               // ��������
	BYTE				bReserved[1016];				// �����ֽ�,������չ.
}DEV_EVENT_QUEUEDETECTION_INFO;

// �¼�����EVENT_IVS_TRAFFICCONTROL(��ͨ�����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFICCONTROL_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	BYTE				bReserved[972];					// �����ֽ�,������չ.

} DEV_EVENT_TRAFFICCONTROL_INFO;

// �¼�����EVENT_IVS_TRAFFICACCIDENT(��ͨ�¹��¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFICACCIDENT_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nObjectNum;						// ��⵽���������
	DH_MSG_OBJECT		stuObjectIDs[DH_MAX_OBJECT_LIST];	// ��⵽�������б�
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	BYTE				bReserved[976];					// �����ֽ�,������չ.

} DEV_EVENT_TRAFFICACCIDENT_INFO;

// �¼�����EVENT_IVS_TRAFFICJUNCTION(��ͨ·���Ϲ����¼�/��Ƶ�羯�ϵĽ�ͨ�����Ϲ����¼�)��Ӧ�����ݿ�������Ϣ
// ������ʷԭ�����Ҫ���������¼���DEV_EVENT_TRAFFICJUNCTION_INFO��EVENT_IVS_TRAFFICGATEҪһ�������Է�ֹ����Ƶ�羯����Ȧ�羯ͬʱ����ƽ̨���������
// ����EVENT_IVS_TRAFFIC_TOLLGATEֻ֧���¿����¼�������
typedef struct tagDEV_EVENT_TRAFFICJUNCTION_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	int					nLane;							// ��Ӧ������
	DWORD				dwBreakingRule;					// Υ����������,��һλ:�����; 
	                                                    // �ڶ�λ:�����涨������ʻ;
	                                                    // ����λ:����; ����λ��Υ�µ�ͷ;
														// ����λ:��ͨ����; ����λ:��ͨ�쳣����
                                                        // ����λ:ѹ����ʻ; ����Ĭ��Ϊ:��ͨ·���¼�
	NET_TIME_EX			RedLightUTC;					// ��ƿ�ʼUTCʱ��
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	int                 nSequence;                      // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	int                 nSpeed;                         // ����ʵ���ٶ�Km/h                 
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];                  // �����ֽ�
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[472];				    // �����ֽ�,������չ.
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ

} DEV_EVENT_TRAFFICJUNCTION_INFO;


// �¼�����EVENT_IVS_TRAFFICGATE(��ͨ�����Ϲ����¼�/��Ȧ�羯�ϵĽ�ͨ�����Ϲ����¼�)��Ӧ�����ݿ�������Ϣ
// ������ʷԭ�����Ҫ���������¼���DEV_EVENT_TRAFFICJUNCTION_INFO��EVENT_IVS_TRAFFICGATEҪһ�������Է�ֹ����Ƶ�羯����Ȧ�羯ͬʱ����ƽ̨���������
// ����EVENT_IVS_TRAFFIC_TOLLGATEֻ֧���¿����¼�������
typedef struct tagDEV_EVENT_TRAFFICGATE_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	int					nLane;							// ��Ӧ������
	int					nSpeed;							// ����ʵ���ٶ�Km/h
	int					nSpeedUpperLimit;				// �ٶ����� ��λ��km/h
	int					nSpeedLowerLimit;				// �ٶ����� ��λ��km/h 
	DWORD				dwBreakingRule;					// Υ����������,��һλ:����; 
	                                                    // �ڶ�λ:ѹ����ʻ; ����λ:������ʻ; 
	                                                    // ����λ��Ƿ����ʻ; ����λ:�����;����λ:����·��(�����¼�)
	                                                    // ����λ: ѹ����; �ڰ�λ: �г�ռ��; �ھ�λ: ����ռ��;����Ĭ��Ϊ:��ͨ�����¼�
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ    
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	BYTE                szManualSnapNo[64];             // �ֶ�ץ�����                
	int                 nSequence;                      // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����; 
	BYTE                byReserved[3];                  // �����ֽ�
	BYTE                szSnapFlag[16];                 // �豸������ץ�ı�ʶ
	BYTE                bySnapMode;                     // ץ�ķ�ʽ��0-δ���� 1-ȫ�� 2-���� 4-ͬ��ץ�� 8-����ץ�� 16-����ͼ��
	BYTE                byOverSpeedPercentage;          // ���ٰٷֱ�
	BYTE                byUnderSpeedingPercentage;      // Ƿ�ٰٷֱ�
	BYTE                byRedLightMargin;               // ����������ʱ��,��λ����
	BYTE                byDriveDirection;               // ��ʻ����0-����(���������豸�����Խ��Խ��)��1-����(���������豸�����Խ��ԽԶ)
	char                szRoadwayNo[32];                // ��·���
	char                szViolationCode[16];            // Υ�´���
	char                szViolationDesc[128];           // Υ������
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	char                szVehicleType[32];              // ������С���ͣ�"Motor" Ħ�г��� "Light-duty" С�ͳ� "Medium" ���ͳ� "Oversize" ���ͳ� "Huge" ���� "Other" ��������
	BYTE                byVehicleLenth;                 // ��������, ��λ��
	BYTE                byReserved1[3];                 // �����ֽ�,������չ
	int                 nOverSpeedMargin;               // �޸��ٿ���ֵ	��λ��km/h 
	int                 nUnderSpeedMargin;              // �޵��ٿ���ֵ	��λ��km/h 
	char                szDrivingDirection[3][DH_MAX_DRIVINGDIRECTION]; //
                                                      	// "DrivingDirection" : ["Approach", "�Ϻ�", "����"],��ʻ����
	                                                  	// "Approach"-���У����������豸�����Խ��Խ����"Leave"-���У�
	                                                  	// ���������豸�����Խ��ԽԶ���ڶ��͵����������ֱ�������к�
	                                                  	// ���е������ص㣬UTF-8����
	char                szMachineName[256];             // ���ػ�Զ���豸����
	char                szMachineAddress[256];          // ��������ص㡢��·����
	char                szMachineGroup[256];            // �������顢�豸������λ
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_SIG_CARWAY_INFO_EX stuSigInfo;                   // �ɳ���������ץ���ź�������Ϣ
	char                szFilePath[MAX_PATH];           // �ļ�·��
	NET_TIME_EX			RedLightUTC;					// ��ƿ�ʼUTCʱ��
	char              * szDeviceAddress;                // �豸��ַ,OSD���ӵ�ͼƬ�ϵ�,��Դ������TrafficSnapshot.DeviceAddress,'\0'����
	BYTE				bReserved[3664];				// �����ֽ�,������չ.
} DEV_EVENT_TRAFFICGATE_INFO;

//�¼�����EVENT_TRAFFICSNAPSHOT(��ͨץ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFICSNAPSHOT_INFO 
{
	int					nChannelID;						  // ͨ����
	char				szName[128];					  // �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							  // ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;						   	  // �¼�������ʱ��
	int					nEventID;					      // �¼�ID
	BYTE                bReserv[3];                       // �����ֽ� 
	BYTE                bCarWayCount;                     // ����ץ�ĵĳ�������
	DH_CARWAY_INFO      stuCarWayInfo[DH_MAX_CARWAY_NUM]; // ����ץ�ĵĳ��������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;					  // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;					  // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                  // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	BYTE				bReserved[344];		    		  // �����ֽ�,������չ
} DEV_EVENT_TRAFFICSNAPSHOT_INFO;

//�¼�����EVENT_IVS_TRAFFIC_RUNREDLIGHT(��ͨ-������¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_RUNREDLIGHT_INFO
{
	int					nChannelID;						  // ͨ����
	char				szName[128];					  // �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							  // ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;				              // �¼�������ʱ��
	int					nEventID;			              // �¼�ID
	int					nLane;				              // ��Ӧ������
	DH_MSG_OBJECT		stuObject;	              	      // ������Ϣ
	DH_MSG_OBJECT       stuVehicle;                       // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;                      // �¼���Ӧ�ļ���Ϣ 
	int					nLightState;	              	  // ���̵�״̬ 0:δ֪ 1���̵� 2:��� 3:�Ƶ�
	int					nSpeed;			              	  // ����,km/h
	int                 nSequence;                        // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	BYTE                bEventAction;					  // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                  // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	NET_TIME_EX         stRedLightUTC;                    // ��ƿ�ʼʱ��
	DH_RESOLUTION_INFO  stuResolution;                    // ��ӦͼƬ�ķֱ���
	BYTE                byRedLightMargin;                 // ����������ʱ��,��λ����
	BYTE				bReserved[975];	                  // �����ֽ�
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;       // ��ͨ������Ϣ
} DEV_EVENT_TRAFFIC_RUNREDLIGHT_INFO;

//�¼�����EVENT_IVS_TRAFFIC_OVERLINE(��ͨ-ѹ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_OVERLINE_INFO
{
	int					nChannelID;			// ͨ����
	char				szName[128];		// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;				// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;				// �¼�������ʱ��
	int					nEventID;			// �¼�ID
	int					nLane;				// ��Ӧ������
	DH_MSG_OBJECT		stuObject;			// ������Ϣ
	DH_MSG_OBJECT       stuVehicle;         // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;        // �¼���Ӧ�ļ���Ϣ
	int                 nSequence;          // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	int                 nSpeed;             // ����ʵ���ٶ�,Km/h
	BYTE                bEventAction;		// �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	    // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;      // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[1008];	// �����ֽ�
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;       // ��ͨ������Ϣ
} DEV_EVENT_TRAFFIC_OVERLINE_INFO;


//�¼�����EVENT_IVS_TRAFFIC_RETROGRADE(��ͨ-�����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_RETROGRADE_INFO
{
	int					nChannelID;			// ͨ����
	char				szName[128];		// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;				// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;				// �¼�������ʱ��
	int					nEventID;			// �¼�ID
	int					nLane;				// ��Ӧ������
	DH_MSG_OBJECT		stuObject;			// ������Ϣ
	DH_MSG_OBJECT       stuVehicle;         // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;        // �¼���Ӧ�ļ���Ϣ
	int                 nSequence;          // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	int                 nSpeed;             // ����ʵ���ٶ�,Km/h
	BYTE                bEventAction;		// �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	    // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;      // ��ӦͼƬ�ķֱ���

	BYTE				bReserved[920];	// �����ֽ�
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ
	int                 nDetectNum;				  // ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������

} DEV_EVENT_TRAFFIC_RETROGRADE_INFO;

//�¼�����EVENT_IVS_TRAFFIC_TURNLEFT(��ͨ-Υ����ת)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_TURNLEFT_INFO
{
	int					nChannelID;			// ͨ����
	char				szName[128];		// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;				// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;				// �¼�������ʱ��
	int					nEventID;			// �¼�ID
	int					nLane;				// ��Ӧ������
	DH_MSG_OBJECT		stuObject;			// ������Ϣ
	DH_MSG_OBJECT       stuVehicle;         // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;        // �¼���Ӧ�ļ���Ϣ
	int                 nSequence;          // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	int                 nSpeed;             // ����ʵ���ٶ�,Km/h
	BYTE                bEventAction;		// �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	    // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;      // ��ӦͼƬ�ķֱ���

	BYTE				bReserved[1008];	// �����ֽ�
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ

} DEV_EVENT_TRAFFIC_TURNLEFT_INFO;


//�¼�����EVENT_IVS_TRAFFIC_TURNRIGHT(��ͨ-Υ����ת)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_TURNRIGHT_INFO
{
	int					nChannelID;			// ͨ����
	char				szName[128];		// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;				// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;				// �¼�������ʱ��
	int					nEventID;			// �¼�ID
	int					nLane;				// ��Ӧ������
	DH_MSG_OBJECT		stuObject;			// ������Ϣ
	DH_MSG_OBJECT       stuVehicle;         // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;        // �¼���Ӧ�ļ���Ϣ
	int                 nSequence;          // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	int                 nSpeed;             // ����ʵ���ٶ�,Km/h
	BYTE                bEventAction;		// �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	    // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;      // ��ӦͼƬ�ķֱ���

	BYTE				bReserved[1008];	// �����ֽ�
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ
} DEV_EVENT_TRAFFIC_TURNRIGHT_INFO;

//�¼�����EVENT_IVS_TRAFFIC_UTURN(Υ�µ�ͷ�¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_UTURN_INFO 
{
	int					nChannelID;						  // ͨ����
	char				szName[128];					  // �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							  // ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;						   	  // �¼�������ʱ��
	int					nEventID;					      // �¼�ID
	int					nLane;							  // ��Ӧ������
	DH_MSG_OBJECT		stuObject;						  // ��⵽������
	DH_MSG_OBJECT       stuVehicle;                       // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;					  // �¼���Ӧ�ļ���Ϣ
	int                 nSequence;                        // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	int                 nSpeed;                           // ����ʵ���ٶ�,Km/h
	BYTE                bEventAction;		              // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                  // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                    // ��ӦͼƬ�ķֱ���
	
	BYTE                bReserved[1008];				  // �����ֽ�
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;       // ��ͨ������Ϣ
}DEV_EVENT_TRAFFIC_UTURN_INFO;

//�¼�����EVENT_IVS_TRAFFIC_OVERSPEED(��ͨ�����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_OVERSPEED_INFO 
{
	int					nChannelID;						  // ͨ����
	char				szName[128];					  // �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							  // ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;						   	  // �¼�������ʱ��
	int					nEventID;					      // �¼�ID
	int					nLane;							  // ��Ӧ������
	DH_MSG_OBJECT		stuObject;						  // ��⵽������
	DH_MSG_OBJECT       stuVehicle;                       // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;					  // �¼���Ӧ�ļ���Ϣ
    int                 nSpeed;                           // ����ʵ���ٶ�Km/h
	int					nSpeedUpperLimit;			      // �ٶ����� ��λ��km/h
	int					nSpeedLowerLimit;				  // �ٶ����� ��λ��km/h 
	int                 nSequence;                        // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	BYTE                bEventAction;	                  // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;	
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                  // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                    // ��ӦͼƬ�ķֱ���

	BYTE                bReserved[1008];				  // �����ֽ�
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;       // ��ͨ������Ϣ
}DEV_EVENT_TRAFFIC_OVERSPEED_INFO;

//�¼�����EVENT_IVS_TRAFFIC_UNDERSPEED(��ͨǷ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_UNDERSPEED_INFO 
{
	int					nChannelID;						  // ͨ����
	char				szName[128];					  // �¼�����
	char                bReserved2[4];                    // �ֽڶ���
	double				PTS;							  // ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;						   	  // �¼�������ʱ��
	int					nEventID;					      // �¼�ID
	int					nLane;							  // ��Ӧ������
	DH_MSG_OBJECT		stuObject;						  // ��⵽������
	DH_MSG_OBJECT       stuVehicle;                       // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;					  // �¼���Ӧ�ļ���Ϣ
    int                 nSpeed;                           // ����ʵ���ٶ�Km/h
	int					nSpeedUpperLimit;			      // �ٶ����� ��λ��km/h
	int					nSpeedLowerLimit;				  // �ٶ����� ��λ��km/h 
	int                 nSequence;                        // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	BYTE                bEventAction;	 	              // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
    BYTE                bReserved1[3];                    // ����
	int                 nUnderSpeedingPercentage;         // Ƿ�ٰٷֱ�
    DWORD               dwSnapFlagMask;	                  // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                    // ��ӦͼƬ�ķֱ���
	
	BYTE                bReserved[1004];				  // �����ֽ�
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;       // ��ͨ������Ϣ

}DEV_EVENT_TRAFFIC_UNDERSPEED_INFO;

//�¼�����EVENT_IVS_FACEDETECT(��������¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_FACEDETECT_INFO 
{
	int					nChannelID;						  // ͨ����
	char				szName[128];				 	  // �¼�����
	char                bReserved1[4];                    // �ֽڶ���
	double				PTS;							  // ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;						   	  // �¼�������ʱ��
	int					nEventID;					      // �¼�ID
	DH_MSG_OBJECT		stuObject;						  // ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;					  // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                     // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                reserved[3];                      // �����ֽ�
	int                 nDetectRegionNum;				  // ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
    DWORD               dwSnapFlagMask;	                  // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	BYTE				bReserved[936];					  // �����ֽ�,������չ
} DEV_EVENT_FACEDETECT_INFO;

// �¼�����EVENT_IVS_TRAFFICJAM(��ͨӵ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFICJAM_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nLane;							// ��Ӧ������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ               
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                reserved[3];                    // �����ֽ�
	NET_TIME_EX         stuStartJamTime;				// ��ʼͣ��ʱ��
	int                 nSequence;                      // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����(bEventAction=2ʱ�˲�����Ч)
	int                 nAlarmIntervalTime;             // ����ʱ��������λ:�롣(���¼�Ϊ�������¼������յ���һ�����¼�֮�����ڳ������ʱ���δ�յ����¼��ĺ����¼�������Ϊ���¼��쳣������)
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[1012];				// �����ֽ�,������չ.
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ	
} DEV_EVENT_TRAFFICJAM_INFO;

// �¼�����EVENT_IVS_TRAFFIC_PARKING(��ͨΥ��ͣ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_PARKING_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	int					nLane;							// ��Ӧ������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ               
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                reserved[3];                    // �����ֽ�
	NET_TIME_EX         stuStartParkingTime;            // ��ʼͣ��ʱ��
	int                 nSequence;                      // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����(bEventAction=2ʱ�˲�����Ч)
	int                 nAlarmIntervalTime;             // ����ʱ��������λ:�롣(���¼�Ϊ�������¼������յ���һ�����¼�֮�����ڳ������ʱ���δ�յ����¼��ĺ����¼�������Ϊ���¼��쳣������)
	int                 nParkingAllowedTime;            // ����ͣ��ʱ������λ���롣
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[924];				    // �����ֽ�,������չ.
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ
	
} DEV_EVENT_TRAFFIC_PARKING_INFO;

//�¼�����EVENT_IVS_TRAFFIC_WRONGROUTE(��ͨΥ��-����������ʻ)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_WRONGROUTE_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	int					nLane;							// ��Ӧ������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ               
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];           
	int                 nSpeed;                         // ����ʵ���ٶȣ�km/h
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[1012];				// �����ֽ�,������չ.
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ

} DEV_EVENT_TRAFFIC_WRONGROUTE_INFO;

//�¼�����EVENT_IVS_TRAFFIC_CROSSLANE(��ͨΥ��-Υ�±��)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_CROSSLANE_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	int					nLane;							// ��Ӧ������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ               
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];           
	int                 nSpeed;                         // ����ʵ���ٶȣ�km/h
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[1008];				// �����ֽ�,������չ.������չ.
	
} DEV_EVENT_TRAFFIC_CROSSLANE_INFO;

//�¼�����EVENT_IVS_TRAFFIC_OVERYELLOWLINE(��ͨΥ��-ѹ����)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_OVERYELLOWLINE_INFO 
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	int					nLane;							// ��Ӧ������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ               
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];           
	int                 nSpeed;                         // ����ʵ���ٶȣ�km/h
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[928];				// �����ֽ�,������չ.
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ

	int                 nDetectNum;				                   // ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������	
} DEV_EVENT_TRAFFIC_OVERYELLOWLINE_INFO;

//�¼�����EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER(��ͨΥ��-·����ʻ�¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_DRIVINGONSHOULDER_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	int					nLane;							// ��Ӧ������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ               
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];           
	int                 nSpeed;                         // ����ʵ���ٶȣ�km/h
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[1008];				// �����ֽ�,������չ.
	
} DEV_EVENT_TRAFFIC_DRIVINGONSHOULDER_INFO;

//�¼�����EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE(��ͨΥ��-���Ƴ�ռ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_YELLOWPLATEINLANE_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	int					nLane;							// ��Ӧ������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ               
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];           
	int                 nSpeed;                         // ����ʵ���ٶȣ�km/h
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[1016];				// �����ֽ�,������չ.
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ
	
} DEV_EVENT_TRAFFIC_YELLOWPLATEINLANE_INFO;

//�¼�����EVENT_IVS_TRAFFIC_NOPASSING(��ͨΥ��-��ֹͨ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_NOPASSING_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int                 UTCMS;                          // 
	int                 nMark;                          // 
	int                 nSequence;                      // ��ʾץ����ţ���3-2-1/0��1��ʾץ������������0��ʾץ���쳣����
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // TrafficCar��ʾ��ͨ���������ݿ��¼
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[1016];				// �����ֽ�,������չ.
}DEV_EVENT_TRAFFIC_NOPASSING_INFO;

typedef struct tagDH_TRAFFICFLOWSTAT
{
	char				szMachineAddress[256];			// ͬDEV_EVENT_TRAFFIC_TRAFFICCAR_INFO.MachineGroup
	char				szMachineName[256];				// ͬDEV_EVENT_TRAFFIC_TRAFFICCAR_INFO.MachineName
	char				szDrivingDirection[3][32];		// ��ʻ����"Approach"-���У����������豸�����Խ��Խ����"Leave"-���У����������豸�����Խ��ԽԶ���ڶ��͵����������ֱ�������к����е������ص㣬UTF-8����
	int					nLane;							// ������ ʹ���û����õĳ������
	NET_TIME_EX			UTC;							// ͳ��ʱ�䣬ת����UTC
	int					nPeriod;						// ͳ�����ڣ���λ����
	int					nVehicles;						// ͨ����������
	float				fAverageSpeed;					// ƽ�����٣���λkm/h
	float				fAverageLength;					// ƽ����������λ��
	float				fTimeOccupyRatio;				// ʱ��ռ���ʣ�����λʱ����ͨ������ĳ�������ʱ����ܺ�ռ��λʱ��ı���
	float				fSpaceOccupyRatio;				// �ռ�ռ���ʣ������ٷ��ʼ����ĳ��������ܺͳ���ʱ�����ڳ���ƽ����ʻ����
	float				fSpaceHeadway;					// ��ͷ��࣬���ڳ���֮��ľ��룬��λ��/��
	float				fTimeHeadway;					// ��ͷʱ�࣬��λ��/��
	float				fDensity;						// �����ܶȣ�ÿ����ĳ���������λ��/km
	int					nOverSpeedVehicles;				// ���ٳ�����
	int					nUnderSpeedVehicles;			// ���ٳ�����
	int					nLargeVehicles;					// ������  ���������жϱ�׼�μ�TrafficSnapshot���ñ�
	int					nMediumVehicles;				// ���ͳ�����
	int					nSmallVehicles;					// С������
	int					nMotoVehicles;					// Ħ�г�����
	int					nLongVehicles;					// ����������
}DH_TRAFFICFLOWSTAT;
// �¼����� EVENT_IVS_TRAFFIC_FLOWSTATE(��ͨ����ͳ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_FLOWSTAT_INFO
{
	char				szName[128];					// �¼�����
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nLaneCnt;						// ͨ������
	DH_TRAFFICFLOWSTAT	stTrafficFlowStats[DH_MAX_LANE_NUM];//����ͳ�Ƽ�¼����һ������
	char				Reserved[4];					// �����ֽڶ���
}DEV_EVENT_TRAFFIC_FLOWSTAT_INFO;

//�¼�����EVENT_IVS_TRAFFIC_MANUALSNAP(��ͨ�ֶ�ץ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_MANUALSNAP_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nLane;							// ��Ӧ������
	BYTE                szManualSnapNo[64];             // �ֶ�ץ����� 
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ��⵽�ĳ�����Ϣ
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ʾ��ͨ���������ݿ��¼
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE				bReserved[1016];				// �����ֽ�,������չ.
}DEV_EVENT_TRAFFIC_MANUALSNAP_INFO;

//�¼����� EVENT_IVS_TRAFFIC_STAY(��ͨ�����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_STAY_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	int					nLane;							// ��Ӧ������
	int					nSequence;						// ץ����ţ���3-2-1/0��1��ʾץ������������0��ʾץ���쳣����
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ʾ��ͨ���������ݿ��¼
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ               
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved0[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE                byReserved[1012];           
}DEV_EVENT_TRAFFIC_STAY_INFO;

//�¼����� EVENT_IVS_TRAFFIC_VEHICLEINROUTE(�г�ռ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_VEHICLEINROUTE_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	int					nLane;							// ��Ӧ������
	int					nSequence;						// ץ����ţ���3-2-1/0��1��ʾץ������������0��ʾץ���쳣����
	int					nSpeed;							// ����
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ʾ��ͨ���������ݿ��¼
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ               
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved0[3];
    DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	BYTE                byReserved[1016];           
}DEV_EVENT_TRAFFIC_VEHICLEINROUTE_INFO;

// �����¼����� EVENT_ALARM_LOCALALARM(�ⲿ����)��EVENT_ALARM_MOTIONALARM(���챨��)
typedef struct tagDEV_EVENT_ALARM_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char				Reserved[4];					// �����ֽڶ���	
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID                                                                                                                                                                                                                                                                         
}DEV_EVENT_ALARM_INFO;

// �¼����� EVENT_IVS_PRISONERRISEDETECTION (���������������¼�) ��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_PRISONERRISEDETECTION_INFO
{
	int					nChannelID;						  // ͨ����
	char				szName[128];					  // �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							  // ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;						   	  // �¼�������ʱ��
	int					nEventID;					      // �¼�ID
	DH_MSG_OBJECT		stuObject;						  // ��⵽������
	int                 nDetectRegionNum;				  // ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	DH_EVENT_FILE_INFO  stuFileInfo;                      // �¼���Ӧ�ļ���Ϣ
	double				dInitialUTC;			  		  // �¼���ʼUTCʱ��	UTCΪ�¼���UTC (1970-1-1 00:00:00)������
	BYTE                bEventAction;                     // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                  // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	int                 nSourceIndex;                   // �¼�Դ�豸�ϵ�index,-1��ʾ������Ч
	char                szSourceDevice[MAX_PATH];       // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	BYTE				bReserved[752];				    // �����ֽ�,������չ.
}DEV_EVENT_PRISONERRISEDETECTION_INFO;

//�¼����� EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY(���������������¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_PEDESTRAINPRIORITY_INFO
{
	int                 nChannelID;                       // ͨ����
	char                szName[128];                      // �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double              PTS;                              // ʱ���(��λ�Ǻ���)
	NET_TIME_EX         UTC;                              // �¼�������ʱ��
	int                 nEventID;                         // �¼�ID
	DH_MSG_OBJECT       stuObject;                        // ��⵽������
	DH_MSG_OBJECT       stuVehicle;                       // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;                      // �¼���Ӧ�ļ���Ϣ
	int                 nLane;                            // ��Ӧ������
	double				dInitialUTC;			  		  // �¼���ʼUTCʱ��	UTCΪ�¼���UTC (1970-1-1 00:00:00)������
	BYTE                bEventAction;                     // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	DWORD               dwSnapFlagMask;                   // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;       // ��ʾ��ͨ���������ݿ��¼
	DH_RESOLUTION_INFO  stuResolution;                    // ��ӦͼƬ�ķֱ���
	BYTE                bReserved[1024];                  // �����ֽ�,������չ.
}DEV_EVENT_TRAFFIC_PEDESTRAINPRIORITY_INFO;

//�¼����� EVENT_IVS_TRAFFIC_VEHICLEINBUSROUTE(ռ�ù��������¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_VEHICLEINBUSROUTE_INFO
{
	int                 nChannelID;                       // ͨ����
	char                szName[128];                      // �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double              PTS;                              // ʱ���(��λ�Ǻ���)
	NET_TIME_EX         UTC;                              // �¼�������ʱ��
	int                 nEventID;                         // �¼�ID
	DH_MSG_OBJECT       stuObject;                        // ��⵽������
	DH_MSG_OBJECT       stuVehicle;                       // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;                      // �¼���Ӧ�ļ���Ϣ
	int                 nLane;                            // ��Ӧ������
	int					nSequence;						  // ץ����ţ���3-2-1/0��1��ʾץ������������0��ʾץ���쳣����
	int					nSpeed;							  // ���٣�km/h
	BYTE                bEventAction;                     // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	DWORD               dwSnapFlagMask;                   // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;       // ��ʾ��ͨ���������ݿ��¼
	DH_RESOLUTION_INFO  stuResolution;                    // ��ӦͼƬ�ķֱ���
	BYTE                bReserved[1020];                  // �����ֽ�,������չ.
}DEV_EVENT_TRAFFIC_VEHICLEINBUSROUTE_INFO;

//�¼����� EVENT_IVS_TRAFFIC_BACKING(Υ�µ����¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_IVS_TRAFFIC_BACKING_INFO
{
	int                 nChannelID;                       // ͨ����
	char                szName[128];                      // �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double              PTS;                              // ʱ���(��λ�Ǻ���)
	NET_TIME_EX         UTC;                              // �¼�������ʱ��
	int                 nEventID;                         // �¼�ID
	DH_MSG_OBJECT       stuObject;                        // ��⵽������
	DH_MSG_OBJECT       stuVehicle;                       // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;                      // �¼���Ӧ�ļ���Ϣ
	int                 nLane;                            // ��Ӧ������
	int					nSequence;						  // ץ����ţ���3-2-1/0��1��ʾץ������������0��ʾץ���쳣����
	int					nSpeed;							  // ���٣�km/h
	BYTE                bEventAction;                     // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	DWORD               dwSnapFlagMask;                   // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;       // ��ʾ��ͨ���������ݿ��¼
	DH_RESOLUTION_INFO  stuResolution;                    // ��ӦͼƬ�ķֱ���
	BYTE                bReserved[1020];                  // �����ֽ�,������չ.
}DEV_EVENT_IVS_TRAFFIC_BACKING_INFO;

//�¼�����EVENT_IVS_AUDIO_ABNORMALDETECTION(�����쳣���)��Ӧ���ݿ�������Ϣ
typedef struct tagDEV_EVENT_IVS_AUDIO_ABNORMALDETECTION_INFO
{
	int                 nChannelID;                       // ͨ����
	char                szName[128];                      // �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double              PTS;                              // ʱ���(��λ�Ǻ���)
	NET_TIME_EX         UTC;                              // �¼�������ʱ��
	int                 nEventID;                         // �¼�ID
	DH_EVENT_FILE_INFO  stuFileInfo;                      // �¼���Ӧ�ļ���Ϣ
	int                 nDecibel;                         // ����ǿ��
	int                 nFrequency;                       // ����Ƶ��
	BYTE                bEventAction;                     // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	DWORD               dwSnapFlagMask;                   // ץͼ��־(��λ)�������NET_RESERVED_COMMON
	DH_RESOLUTION_INFO  stuResolution;                    // ��ӦͼƬ�ķֱ���
	BYTE                bReserved[1024];                  // �����ֽ�,������չ.
}DEV_EVENT_IVS_AUDIO_ABNORMALDETECTION_INFO;

//�¼����� EVENT_IVS_TRAFFIC_RUNYELLOWLIGHT(��ͨΥ��-���Ƶ��¼�)��Ӧ���ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_RUNYELLOWLIGHT_INFO
{
	int					nChannelID;						  // ͨ����
	char				szName[128];					  // �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							  // ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;				              // �¼�������ʱ��
	int					nEventID;			              // �¼�ID
	int					nLane;				              // ��Ӧ������
	DH_MSG_OBJECT		stuObject;	              	      // ������Ϣ
	DH_MSG_OBJECT       stuVehicle;                       // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;                      // �¼���Ӧ�ļ���Ϣ 
	int					nLightState;	              	  // ���̵�״̬ 0:δ֪ 1���̵� 2:��� 3:�Ƶ�
	int					nSpeed;			              	  // ����,km/h
	int                 nSequence;                        // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	BYTE                bEventAction;					  // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
    DWORD               dwSnapFlagMask;	                  // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	NET_TIME_EX         stYellowLightUTC;                 // �Ƶƿ�ʼʱ��
	unsigned int        nYellowLightPeriod;               // �Ƶ����ڼ��ʱ��,��λ��
	DH_RESOLUTION_INFO  stuResolution;                    // ��ӦͼƬ�ķֱ���
 	BYTE                byRedLightMargin;                 // �Ƶ��������ʱ��,��λ����
	char                szSourceDevice[MAX_PATH];         // �¼�Դ�豸Ψһ��ʶ,�ֶβ����ڻ���Ϊ�ձ�ʾ�����豸
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;       // ��ͨ������Ϣ
	BYTE				bReserved[1024];	              // �����ֽ�
} DEV_EVENT_TRAFFIC_RUNYELLOWLIGHT_INFO;

//�¼����� EVENT_IVS_LEAVEDETECTION(��ڼ���¼�)��Ӧ���ݿ�������Ϣ
typedef struct tagDEV_EVENT_IVS_LEAVE_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	int                 nDetectRegionNum;				// ���������򶥵���
	DH_POINT            DetectRegion[DH_MAX_DETECT_REGION_NUM];    // ����������
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;	
	BYTE				bReserved[1027];	            // �����ֽ�
} DEV_EVENT_IVS_LEAVE_INFO;

//�¼����� EVENT_IVS_CLIMBDETECTION(�ʸ߼���¼�)��Ӧ���ݿ�������Ϣ
typedef struct tagDEV_EVENT_IVS_CLIMB_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[4];                  // �ֽڶ���
	double				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	int                 nDetectLineNum;                        // �������߶�����
	DH_POINT            DetectLine[DH_MAX_DETECT_LINE_NUM];    // ��������
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE				bReserved[1027];	            // �����ֽ�
}DEV_EVENT_IVS_CLIMB_INFO;

//�¼����� EVENT_IVS_TRAFFIC_PARKINGONYELLOWBOX(��������ץ���¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_PARKINGONYELLOWBOX_INFO
{
	int					nChannelID;						// ͨ����
	char				szName[128];					// �¼�����
	char                bReserved1[8];                  // �ֽڶ���
	DWORD				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nLane;							// ��Ӧ������
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ

	int					nInterval1;						// �ڶ��ź͵�һ�ŵ���ʱʱ�䣬��λ��
	int					nInterval2;						// �����ź͵ڶ��ŵ���ʱʱ�䣬��λ��
	int					nFollowTime;					// ����ʱ�䣬���һ������ǰһ��������������ʱ���С�ڴ�ֵ������Ϊ�Ǹ������룬����������������ͣ������Υ��

	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ
	BYTE				bReserved[1024];	            // �����ֽ�

}DEV_EVENT_TRAFFIC_PARKINGONYELLOWBOX_INFO;

//�¼����� EVENT_IVS_TRAFFIC_PARKINGSPACEPARKING(��λ�г��¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_PARKINGSPACEPARKING_INFO
{
	int					nChannelID;						// ͨ����
    char                szName[DH_EVENT_NAME_LEN];      // �¼�����
	char                bReserved1[8];                  // �ֽڶ���
	DWORD				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nLane;							// ��Ӧ������
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	
	int                 nSequence;                      // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����	
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ
	BYTE				bReserved[1024];	            // �����ֽ�
	
}DEV_EVENT_TRAFFIC_PARKINGSPACEPARKING_INFO;

//�¼����� EVENT_IVS_TRAFFIC_PARKINGSPACENOPARKING(��λ�޳��¼�)��Ӧ�����ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_PARKINGSPACENOPARKING_INFO
{
	int					nChannelID;						// ͨ����
    char                szName[DH_EVENT_NAME_LEN];      // �¼�����
	char                bReserved1[8];                  // �ֽڶ���
	DWORD				PTS;							// ʱ���(��λ�Ǻ���)
	NET_TIME_EX			UTC;							// �¼�������ʱ��
	int					nEventID;						// �¼�ID
	int					nLane;							// ��Ӧ������
	DH_MSG_OBJECT		stuObject;						// ��⵽������
	DH_MSG_OBJECT       stuVehicle;                     // ������Ϣ
	DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
	
	int                 nSequence;                       // ��ʾץ����ţ���3,2,1,1��ʾץ�Ľ���,0��ʾ�쳣����
	BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
	BYTE                byReserved[3];
	DWORD               dwSnapFlagMask;	                // ץͼ��־(��λ)�������NET_RESERVED_COMMON	
	DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;     // ��ͨ������Ϣ
	BYTE				bReserved[1024];	            // �����ֽ�
	
}DEV_EVENT_TRAFFIC_PARKINGSPACENOPARKING_INFO;

//�¼����� EVENT_IVS_TRAFFIC_PEDESTRAIN(��ͨ�����¼�)��Ӧ���ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_PEDESTRAIN_INFO
{
    int                 nChannelID;                     // ͨ����
    char                szName[DH_EVENT_NAME_LEN];      // �¼�����
    char                bReserved1[8];                  // �ֽڶ���
    DWORD               PTS;                            // ʱ���(��λ�Ǻ���)
    NET_TIME_EX         UTC;                            // �¼�������ʱ��
    int                 nEventID;                       // �¼�ID
    DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
    DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
    DWORD               dwSnapFlagMask;                 // ץͼ��־(��λ)��0λ:"*",1λ:"Timing",2λ:"Manual",3λ:"Marked",4λ:"Event",5λ:"Mosaic",6λ:"Cutout" 
    BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
    BYTE                bReserved2[3];
    int                 nLane;                          // ��Ӧ������
    DH_MSG_OBJECT       stuObject;                      // ��⵽������
    BYTE                bReserved[1024];                // �����ֽ�
}DEV_EVENT_TRAFFIC_PEDESTRAIN_INFO;

//�¼����� EVENT_IVS_TRAFFIC_THROW(��ͨ������Ʒ�¼�)��Ӧ���ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_THROW_INFO
{
    int                 nChannelID;                     // ͨ����
    char                szName[DH_EVENT_NAME_LEN];      // �¼�����
    char                bReserved1[8];                  // �ֽڶ���
    DWORD               PTS;                            // ʱ���(��λ�Ǻ���)
    NET_TIME_EX         UTC;                            // �¼�������ʱ��
    int                 nEventID;                       // �¼�ID
    DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
    DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
    DWORD               dwSnapFlagMask;                 // ץͼ��־(��λ)��0λ:"*",1λ:"Timing",2λ:"Manual",3λ:"Marked",4λ:"Event",5λ:"Mosaic",6λ:"Cutout" 
    BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
    BYTE                bReserved2[3];
    int                 nLane;                          // ��Ӧ������
    DH_MSG_OBJECT       stuObject;                      // ��⵽������
    BYTE                bReserved[1024];                // �����ֽ�
}DEV_EVENT_TRAFFIC_THROW_INFO;

//�¼����� EVENT_IVS_TRAFFIC_IDLE(��ͨ�����¼�)��Ӧ���ݿ�������Ϣ
typedef struct tagDEV_EVENT_TRAFFIC_IDLE_INFO
{
    int                 nChannelID;                     // ͨ����
    char                szName[DH_EVENT_NAME_LEN];      // �¼�����
    char                bReserved1[8];                  // �ֽڶ���
    DWORD               PTS;                            // ʱ���(��λ�Ǻ���)
    NET_TIME_EX         UTC;                            // �¼�������ʱ��
    int                 nEventID;                       // �¼�ID
    DH_EVENT_FILE_INFO  stuFileInfo;                    // �¼���Ӧ�ļ���Ϣ
    DH_RESOLUTION_INFO  stuResolution;                  // ��ӦͼƬ�ķֱ���
    DWORD               dwSnapFlagMask;                 // ץͼ��־(��λ)��0λ:"*",1λ:"Timing",2λ:"Manual",3λ:"Marked",4λ:"Event",5λ:"Mosaic",6λ:"Cutout" 
    BYTE                bEventAction;                   // �¼�������0��ʾ�����¼�,1��ʾ�������¼���ʼ,2��ʾ�������¼�����;
    BYTE                bReserved2[3];
    int                 nLane;                          // ��Ӧ������
    BYTE                bReserved[1024];                // �����ֽ�
}DEV_EVENT_TRAFFIC_IDLE_INFO;

// media�ļ���ѯ����
typedef enum __EM_FILE_QUERY_TYPE
{
	DH_FILE_QUERY_TRAFFICCAR,							// ��ͨ������Ϣ
	DH_FILE_QUERY_ATM,									// ATM��Ϣ
	DH_FILE_QUERY_ATMTXN,								// ATM������Ϣ
	DH_FILE_QUERY_FACE,  								// ������Ϣ
    DH_FILE_QUERY_FILE,                                 // �ļ���Ϣ��Ӧ NET_IN_MEDIA_QUERY_FILE �� NET_OUT_MEDIAFILE_FILE
} EM_FILE_QUERY_TYPE;

// ¼����Ϣ��Ӧ CLIENT_FindFileEx�ӿڵ� DH_FILE_QUERY_FILE ���� ��ѯ����
// Ŀǰ֧��ͨ��·����ѯ
typedef struct  
{
    DWORD               dwSize;                 // �ṹ���С
    char*               szDirs;                 // ����Ŀ¼�б�,һ�οɲ�ѯ���Ŀ¼,Ϊ�ձ�ʾ��ѯ����Ŀ¼��Ŀ¼֮���Էֺŷָ����硰/mnt/dvr/sda0;/mnt/dvr/sda1��,szDirs==null ��"" ��ʾ��ѯ����
    int					nMediaType;		        // �ļ����ͣ�0:��ѯ��������,1:��ѯjpgͼƬ,2:��ѯdav
}NET_IN_MEDIA_QUERY_FILE;

// ¼����Ϣ��Ӧ CLIENT_FindFileEx�ӿڵ� DH_FILE_QUERY_FILE ���� ��ѯ���
typedef struct  
{
    DWORD               dwSize;                 // �ṹ���С
    int					nChannelID;				// ͨ���Ŵ�0��ʼ��-1��ʾ��ѯ����ͨ��
    NET_TIME			stuStartTime;			// ��ʼʱ��	
    NET_TIME			stuEndTime;				// ����ʱ��
    unsigned int		nFileSize;				// �ļ�����
    BYTE				byFileType;				// �ļ����� 1:jpgͼƬ, 2: dav
    BYTE                byDriveNo;              // ���̺�
    BYTE                byReserved1[2];         // �����ֶ�
    unsigned int        nCluster;               // �غ�
}NET_OUT_MEDIA_QUERY_FILE;

// DH_MEDIA_QUERY_TRAFFICCAR��Ӧ�Ĳ�ѯ����
typedef struct  
{
	int					nChannelID;						// ͨ���Ŵ�0��ʼ��-1��ʾ��ѯ����ͨ��
	NET_TIME			StartTime;						// ��ʼʱ��	
	NET_TIME			EndTime;						// ����ʱ��
	int					nMediaType;						// �ļ����ͣ�0:��ѯ��������,1:��ѯjpgͼƬ
	int					nEventType;						// �¼����ͣ����"���ܷ����¼�����", 0:��ʾ��ѯ�����¼�
	char				szPlateNumber[32];				// ���ƺ�, "\0"���ʾ��ѯ���⳵�ƺ�
	int					nSpeedUpperLimit;				// ��ѯ�ĳ��ٷ�Χ; �ٶ����� ��λ: km/h
	int					nSpeedLowerLimit;				// ��ѯ�ĳ��ٷ�Χ; �ٶ����� ��λ: km/h 
	BOOL				bSpeedLimit;					// �Ƿ��ٶȲ�ѯ; TRUE:���ٶȲ�ѯ,nSpeedUpperLimit��nSpeedLowerLimit��Ч��
    DWORD				dwBreakingRule;					// Υ�����ͣ�
														// ���¼�����Ϊ EVENT_IVS_TRAFFICGATEʱ
														//		��һλ:����;  �ڶ�λ:ѹ����ʻ; ����λ:������ʻ; 
														//		����λ��Ƿ����ʻ; ����λ:�����;
														// ���¼�����Ϊ EVENT_IVS_TRAFFICJUNCTION
														//		��һλ:�����;  �ڶ�λ:�����涨������ʻ;  
														//		����λ:����; ����λ��Υ�µ�ͷ;
														//		����λ:ѹ����ʻ;

	char                szPlateType[32];                // �������ͣ�"Unknown" δ֪,"Normal" ���ƺ���,"Yellow" ����,"DoubleYellow" ˫���β��,"Police" ����"Armed" �侯��,
												 	    // "Military" ���Ӻ���,"DoubleMilitary" ����˫��,"SAR" �۰���������,"Trainning" ����������
														// "Personal" ���Ժ���,"Agri" ũ����,"Embassy" ʹ�ݺ���,"Moto" Ħ�г�����,"Tractor" ����������,"Other" ��������
	char                szPlateColor[16];               // ������ɫ, "Blue"��ɫ,"Yellow"��ɫ, "White"��ɫ,"Black"��ɫ
	char				szVehicleColor[16];		        // ������ɫ:"White"��ɫ, "Black"��ɫ, "Red"��ɫ, "Yellow"��ɫ, "Gray"��ɫ, "Blue"��ɫ,"Green"��ɫ
	char				szVehicleSize[16];		        // ������С����:"Light-duty":С�ͳ�;"Medium":���ͳ�; "Oversize":���ͳ�; "Unknown": δ֪
	int                 nGroupID;                       // �¼�����(��ֵ>=0ʱ��Ч)
	short               byLane;                         // ������(��ֵ>=0ʱ��ʾ���峵����-1��ʾ���г����������·����ֶ�)
	BYTE				byFileFlag;						// �ļ���־, 0xFF-ʹ��nFileFlagEx, 0-��ʾ����¼��, 1-��ʱ�ļ�, 2-�ֶ��ļ�, 3-�¼��ļ�, 4-��Ҫ�ļ�, 5-�ϳ��ļ�
	BYTE				reserved;
	int					nFileFlagEx;					// �ļ���־, ��λ��ʾ: bit0-��ʱ�ļ�, bit1-�ֶ��ļ�, bit2-�¼��ļ�, bit3-��Ҫ�ļ�, bit4-�ϳ��ļ�, bit5-������ͼƬ 0xFFFFFFFF-����¼��
	int					nDirection;				        // �������򣨳������ķ���	0-�� 1-���� 2-�� 3-���� 4-�� 5-���� 6-�� 7-���� 8-δ֪ -1-���з���
	char*               szDirs;                         // ����Ŀ¼�б�,һ�οɲ�ѯ���Ŀ¼,Ϊ�ձ�ʾ��ѯ����Ŀ¼��Ŀ¼֮���Էֺŷָ����硰/mnt/dvr/sda0;/mnt/dvr/sda1��,szDirs==null ��"" ��ʾ��ѯ����
	int					bReserved[37];					// �����ֶ�
} MEDIA_QUERY_TRAFFICCAR_PARAM;

// DH_MEDIA_QUERY_TRAFFICCAR��ѯ������media�ļ���Ϣ
typedef struct
{
    unsigned int		ch;						// ͨ����
    char				szFilePath[128];		// �ļ�·��
    unsigned int		size;					// �ļ�����
    NET_TIME			starttime;				// ��ʼʱ��
    NET_TIME			endtime;				// ����ʱ��
    unsigned int		nWorkDirSN;				// ����Ŀ¼���									
	BYTE				nFileType;				// �ļ�����  1��jpgͼƬ
	BYTE                bHint;					// �ļ���λ����
	BYTE                bDriveNo;               // ���̺�
	BYTE                bReserved2;
	unsigned int        nCluster;               // �غ�
	BYTE				byPictureType;			// ͼƬ����, 0-��ͨ, 1-�ϳ�, 2-��ͼ
	BYTE                bReserved[3];           // �����ֶ�

	//�����ǽ�ͨ������Ϣ
	char				szPlateNumber[32];		// ���ƺ���
	char				szPlateType[32];		// ��������"Unknown" δ֪; "Normal" ���ƺ���; "Yellow" ����; "DoubleYellow" ˫���β��
												// "Police" ����; "Armed" �侯��; "Military" ���Ӻ���; "DoubleMilitary" ����˫��
												// "SAR" �۰���������; "Trainning" ����������; "Personal" ���Ժ���; "Agri" ũ����
												// "Embassy" ʹ�ݺ���; "Moto" Ħ�г�����; "Tractor" ����������; "Other" ��������
	char				szPlateColor[16];		// ������ɫ:"Blue","Yellow", "White","Black"
	char				szVehicleColor[16];		// ������ɫ:"White", "Black", "Red", "Yellow", "Gray", "Blue","Green"
	int					nSpeed;					// ����,��λKm/H
	int					nEventsNum;				// �������¼�����
	int					nEvents[32];			// �������¼��б�,����ֵ��ʾ��Ӧ���¼������"���ܷ����¼�����"		
	DWORD				dwBreakingRule;			// ����Υ����������,��һλ:�����; �ڶ�λ:�����涨������ʻ;
	                                            // ����λ:����; ����λ��Υ�µ�ͷ;����Ĭ��Ϊ:��ͨ·���¼�
	char				szVehicleSize[16];		// ������С����:"Light-duty":С�ͳ�;"Medium":���ͳ�; "Oversize":���ͳ�
	char				szChannelName[DH_CHAN_NAME_LEN];// ���ػ�Զ�̵�ͨ������
	char				szMachineName[DH_MAX_NAME_LEN];	// ���ػ�Զ���豸����

	int					nSpeedUpperLimit;	    // �ٶ����� ��λ: km/h
	int					nSpeedLowerLimit;		// �ٶ����� ��λ: km/h	
	int                 nGroupID;               // �¼��������
	BYTE                byCountInGroup;         // һ���¼����ڵ�ץ������
	BYTE                byIndexInGroup;         // һ���¼����ڵ�ץ�����
	BYTE                byLane;                 // ����,�μ�MEDIA_QUERY_TRAFFICCAR_PARAM
	BYTE                bReserved1[45];			// ����
	int					nDirection;				// ��������,�μ�MEDIA_QUERY_TRAFFICCAR_PARAM
	char                szMachineAddress[MAX_PATH]; // ��������ص�
} MEDIAFILE_TRAFFICCAR_INFO, *LPMEDIAFILE_TRAFFICCAR_INFO;
// FINDNEXT��ѯ�������
typedef struct __NET_FINDNEXT_RESERVED
{
	DWORD               dwSize;                 // �ṹ���С
	
	unsigned int        nBeginNumber;           // ��ѯ��ʼ��ţ���ʾ��beginNumber����¼��ʼ�� 0<=beginNumber<= totalCount-1
}NET_FINDNEXT_RESERVED;

// DH_FILE_QUERY_FACE��Ӧ������ʶ������ѯ����
typedef struct __MEDIAFILE_FACERECOGNITION_PARAM
{
	DWORD               dwSize;                 // �ṹ���С

	FACERECOGNITION_PERSON_INFO stPersion;      // ��Ա��Ϣ

	// ����ƥ��ѡ��
	unsigned int        nMatchImportant;        // ��Ա��Ҫ�ȼ�	1~10����ֵԽ��Խ��Ҫ
	char                szMode[MAX_PATH];       // �����ȶ�ģʽ��֧�֣�Normal(����) Area(ָ�����������������) Auto(����ģʽ���㷨��������������������Զ�ѡȡ���)	
	char                szAreas[MAX_PATH];      // ֧�����¼��������������ϣ�Eyebrow üë Eye �۾� Nose ���� Mouth ��� Cheek ���� ����Զ��ŷָ��"Eyebrow,	char                szAreas[MAX_PATH];      // ֧�����¼��������������ϣ� Eyebrow üë Eye �۾� Nose ���� Mouth ��� Cheek ���� ����Զ��ŷָ��"Eyebrow,	char                szAreas[MAX_PATH];      // ֧�����¼��������������ϣ� Eyebrow üë Eye �۾� Nose ���� Mouth ��� Cheek ���� ����Զ��ŷָ��"Eyebrow,Eye"	
	unsigned int        nAccuracy;              // ʶ�𾫶�(ȡֵ1~10������ֵ���󣬼�⾫����ߣ�����ٶ��½�����СֵΪ1 ��ʾ����ٶ����ȣ����ֵΪ10��ʾ��⾫�����ȡ� ��ʱֻ�����������Ч)
	unsigned int        nSimilarity;            // ���ƶ�(������ڸ���ʶ�Ȳű���;�ٷֱȱ�ʾ��1~100)
	unsigned int        nMaxCandidate;          // ���������ѡ����(�������ƶȽ�������ȡ���ƶ����ĺ�ѡ��������)

	// ��ѯ��������
    NET_TIME			stStartTime;			// ��ʼʱ��
    NET_TIME			stEndTime;				// ����ʱ��
	char                szMachineAddress[MAX_PATH]; // �ص�	֧��ģ��ƥ��	
	char                szRange[MAX_PATH];      // "HistoryDB",��ʷ���ݿ� "BlackListDB",���������ݿ⣻�ֶ�֮���Զ��ŷָ���"HistoryDB,BlackListDB"

	// ͼƬ����������
	char              * pBuffer;                // �����ַ
	int                 nBufferLen;             // �������ݳ���

	// �������
	unsigned int        nTotalCount;            // ���ϴ˴β�ѯ�����Ľ��������
}MEDIAFILE_FACERECOGNITION_PARAM;

// DH_FILE_QUERY_FACE��Ӧ������ʶ�����FINDNEXT��ѯ���ز���
typedef struct __MEDIAFILE_FACERECOGNITION_INFO
{
	DWORD               dwSize;                 // �ṹ���С
	
	FACERECOGNITION_PERSON_INFO pstPersion;    // ��Ա��Ϣ��
	unsigned int        nSimilarity;            // �Ͳ�ѯͼƬ�����ƶ�	�ٷֱȱ�ʾ��1~100
	char                szRange[MAX_PATH];      // "HistoryDB",��ʷ���ݿ� "BlackListDB",���������ݿ⣻�ֶ�֮���Զ��ŷָ���"HistoryDB,BlackListDB"

	// ���صĴ�ͼ��Ϣ
	char                szFilePath[MAX_PATH];   // �ļ�·��

	// ͼƬ����������
	char              * pBuffer;                // �����ַ
	int                 nBufferLen;             // �������ݳ���
}MEDIAFILE_FACERECOGNITION_INFO;

// ��ƵŨ������ļ���ѯ����
typedef struct __MEDIA_QUERY_VIDEOSYNOPSIS_PARAM
{
	DWORD               dwSize;
	NET_TIME			StartTime;						// ��ʼʱ��	
	NET_TIME			EndTime;						// ����ʱ��
	int					nMediaType;						// �ļ����ͣ�0:��ѯ��������,1:ͼƬ,2:¼��
	int                 nQueryType;                     // ��ѯ���ͣ�1:ԭʼ��Ƶ�ļ� 2:Ũ�������Ƶ�ļ�
}MEDIA_QUERY_VIDEOSYNOPSIS_PARAM;

typedef struct __MEDIAFILE_VIDEOSYNOPSIS_INFO
{
    char				szFilePath[128];		// �ļ�·��
    unsigned int		size;					// �ļ�����
    NET_TIME			starttime;				// ��ʼʱ��
    NET_TIME			endtime;				// ����ʱ��
    unsigned int		nWorkDirSN;				// ����Ŀ¼���									
	BYTE				nFileType;				// �ļ�����  1��jpgͼƬ
	BYTE                bHint;					// �ļ���λ����
	BYTE                bDriveNo;               // ���̺�
	BYTE                bReserved2;
	unsigned int        nCluster;               // �غ�
	BYTE				byPictureType;			// ͼƬ����, 0-��ͨ, 1-�ϳ�, 2-��ͼ
	BYTE                bReserved[3];           // �����ֶ�

	// ��ƵԴ�ļ������Ϣ
	int                nTaskID;                 // ����ID
	char               szCurrentState[DH_MAX_SYNOPSIS_STATE_NAME]; // ��ƵŨ��״̬
	int                nProgress;               // ��ӦŨ��״̬
	int                nObjectNum;              // Ũ���õ����������

	// Ũ�������Ƶ�ļ������Ϣ
	int                nDurationTime;          // ����ʱ��,��λs
}MEDIAFILE_VIDEOSYNOPSIS_INFO;

// �ṹ��(NET_IN_SNAPSHOT)��Ա ���صƵ��ڿ��� 	��һ�����飬ÿ��Ԫ�ض�Ӧһ�����������
typedef struct __NET_FLASHCONTROL
{
	DWORD				dwSize;					// �˽ṹ���С
	int					nMode;					// ����ģʽ	0-��ֹ���⣬1-ʼ�����⣬2-�Զ�����
}NET_FLASHCONTROL;

// nTriggerType==2ʱ �ͻ��˴���ץ�Ĳ���
typedef struct _NET_CLIENT_SNAP_INFO
{
	DWORD				dwSize;					// �˽ṹ���С
	unsigned int        nFrameSequence;         // ֡���
	double              PTS;                    // ʱ���,64λ����ʱ���
}NET_CLIENT_SNAP_INFO;

// �ӿ�(CLIENT_TrafficSnapByNetwork)�������
typedef struct __NET_IN_SNAPSHOT
{
	DWORD				dwSize;					// �˽ṹ���С
	int					nTriggerType;			// ��������	0-δ֪	1-�������紥�� 2-�ͻ��˴�������ʱֻ��Ҫ��дstClientInfo������
	int					nLaneID;				// ������
	int					nGroupID;				// �����
	int					nGrabTimes;				// ץ��ͼƬ����
	int					nStartPicNum;			// ��һ��ͼƬ��ʼ���
	int					nDirection;				// �������򣨳������ķ���	0-�� 1-���� 2-�� 3-���� 4-�� 5-���� 6-�� 7-���� 8-δ֪
	//NET_GRAB_WAITTIME   stGrabWaitTime;			// ����ͼƬ֮��ץ�ļ��
	int					nGrabWaitTime;			// pGrabWaitTime�����Ա����
	DWORD*				pGrabWaitTime;			// ����ͼƬ֮��ץ�ļ��
	int					nLowerSpeedLimit;		// �ٶ����ޣ���λkm/h
	int					nUpperSpeedLimit;		// �ٶ����ޣ���λkm/h
	int					nSpeed;					// ���٣���λkm/h
	int					nViolationNo;			// Υ�����	0-δΥ��
	// 1-������
	// 2-���ٲ�����50% 
	// 3-������50%��100%֮��
	// 4-���ٳ���100%
	// 5-����
	// 6-�����
	// 7-��������
	// 8-���У�����������ʻ
	int					nRedLightTime;			// ���ʱ�䣬����Ƶ�������ʱ��󴥷�ץ�ģ���λ��
	//NET_FLASHCONTROL	stFlashControl;			// ���صƵ��ڿ���
	int					nFlashControl;			// pFlashControl�������
	NET_FLASHCONTROL*   pFlashControl;			// ���صƵ��ڿ���
	DWORD				dwUser;					// �û����� NSP
	NET_CLIENT_SNAP_INFO stClientInfo;          // �ͻ��˴���ʱ�����ץ�Ĳ���
}NET_IN_SNAPSHOT;

// �ӿ�(CLIENT_TrafficSnapByNetwork)�������
typedef struct __NET_OUT_SNAPSHOT
{
	DWORD				dwSize;					// �˽ṹ���С
}NET_OUT_SNAPSHOT;

// �ӿ�(CLIENT_TrafficForceLightState)�������
typedef struct __NET_IN_FORCELIGHTSTATE
{
	DWORD				dwSize;					// �˽ṹ���С
	unsigned int        nDirection;             // ��λ��ʾ��0λ��"Straight",1λ��"TurnLeft",2λ��"TurnRight",3λ��"U-Turn"
}NET_IN_FORCELIGHTSTATE;

// �ӿ�(CLIENT_TrafficForceLightState)�������
typedef struct __NET_OUT_FORCELIGHTSTATE
{
	DWORD				dwSize;					// �˽ṹ���С
}NET_OUT_FORCELIGHTSTATE;

// �ӿ�(CLIENT_StartTrafficFluxStat)�ص�
typedef int  (CALLBACK *fFluxStatDataCallBack)(LLONG lFluxStatHandle, DWORD dwEventType, void* pEventInfo, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser, int nSequence, void *reserved);

// �ӿ�(CLIENT_StartTrafficFluxStat)�������
typedef struct __NET_IN_TRAFFICFLUXSTAT
{
	DWORD				dwSize;					// �˽ṹ���С
	fFluxStatDataCallBack		cbData;			// �ص�����ָ��
	DWORD				dwUser;					// �û�����
}NET_IN_TRAFFICFLUXSTAT;

// �ӿ�(CLIENT_StartTrafficFluxStat)�������
typedef struct __NET_OUT_TRAFFICFLUXSTAT
{
	DWORD				dwSize;					// �˽ṹ���С	
}NET_OUT_TRAFFICFLUXSTAT;

// �ӿ�(CLIENT_StartFindFluxStat)�������
typedef struct __NET_IN_TRAFFICSTARTFINDSTAT
{
	DWORD				dwSize;					// �˽ṹ���С
	NET_TIME			stStartTime;			// ��ʼʱ�� ��ʱ��ȷ��Сʱ
	NET_TIME			stEndTime;				// ����ʱ�� ��ʱ��ȷ��Сʱ
	int					nWaittime;				// �ȴ��������ݵĳ�ʱʱ��
}NET_IN_TRAFFICSTARTFINDSTAT;

// �ӿ�(CLIENT_StartFindFluxStat)�������
typedef struct __NET_OUT_TRAFFICSTARTFINDSTAT
{
	DWORD				dwSize;					// �˽ṹ���С
	DWORD               dwTotalCount;           // ���ϴ˴β�ѯ�����Ľ��������                 
}NET_OUT_TRAFFICSTARTFINDSTAT;

// �ӿ�(CLIENT_DoFindFluxStat)�������
typedef struct __NET_IN_TRAFFICDOFINDSTAT
{
	DWORD				dwSize;					// �˽ṹ���С
	unsigned int		nCount;					// ÿ�β�ѯ������ͳ������
	int					nWaittime;				// �ȴ��������ݵĳ�ʱʱ��
}NET_IN_TRAFFICDOFINDSTAT;

typedef struct
{
	DWORD				dwSize;					// �˽ṹ���С

	int					nStatInfo;				// ͳ����Ϣ����
	DH_TRAFFICFLOWSTAT *pStatInfo;				// ͳ����Ϣָ��
}DH_TRAFFICFLOWSTAT_OUT;

// �ӿ�(CLIENT_DoFindFluxStat)�������
typedef struct __NET_OUT_TRAFFICDOFINDSTAT
{
	DWORD				dwSize;					// �˽ṹ���С
	
	DH_TRAFFICFLOWSTAT_OUT stStatInfo;			// ͳ����Ϣָ��
}NET_OUT_TRAFFICDOFINDSTAT;

// �ӿ�(CLIENT_StartFindNumberStat)�������
typedef struct __NET_IN_FINDNUMBERSTAT
{
	DWORD				dwSize;					// �˽ṹ���С
	int                 nChannelID;             // Ҫ���в�ѯ��ͨ����
	NET_TIME			stStartTime;			// ��ʼʱ�� ��ʱ��ȷ��Сʱ
	NET_TIME			stEndTime;				// ����ʱ�� ��ʱ��ȷ��Сʱ
	int                 nGranularityType;       // ��ѯ����0:���ӣ�1:Сʱ,2:��,3:��,4:��,5:��,6:��
	int					nWaittime;				// �ȴ��������ݵĳ�ʱʱ��
}NET_IN_FINDNUMBERSTAT;

// �ӿ�(CLIENT_StartFindNumberStat)�������
typedef struct __NET_OUT_FINDNUMBERSTAT
{
	DWORD				dwSize;					// �˽ṹ���С
	DWORD               dwTotalCount;           // ���ϴ˴β�ѯ�����Ľ��������
}NET_OUT_FINDNUMBERSTAT;

// �ӿ�(CLIENT_DoFindNumberStat)�������
typedef struct __NET_IN_DOFINDNUMBERSTAT
{
	DWORD				dwSize;					// �˽ṹ���С
	unsigned int        nBeginNumber;           // [0, totalCount-1], ��ѯ��ʼ��ţ���ʾ��beginNumber����¼��ʼ��ȡcount����¼����; 
	unsigned int		nCount;					// ÿ�β�ѯ������ͳ������
	int					nWaittime;				// �ȴ��������ݵĳ�ʱʱ��	        
}NET_IN_DOFINDNUMBERSTAT;

typedef struct __DH_NUMBERSTAT
{
	DWORD    dwSize;
	int      nChannelID;                           //ͳ��ͨ����
	char     szRuleName[DH_CHAN_NAME_LEN];         //��������
	NET_TIME stuStartTime;                         //��ʼʱ��
	NET_TIME stuEndTime;                           //����ʱ��
    int      nEnteredSubTotal;                     //��������С��
	int      nExitedSubtotal;                      //��ȥ����С��
    int      nAvgInside;                           //ƽ����������(��ȥ��ֵ)
	int      nMaxInside;                           //���������
}DH_NUMBERSTAT;
// �ӿ�(CLIENT_DoFindNumberStat)�������
typedef struct __NET_OUT_DOFINDNUMBERSTAT
{
	DWORD				dwSize;					             // �˽ṹ���С
	int                 nCount;                              // ��ѯ��������ͳ����Ϣ����
	DH_NUMBERSTAT       *pstuNumberStat;                     // ��������ͳ����Ϣ����
    int                 nBufferLen;                          // �û�������ڴ��С,��DH_NUMBERSTAT�е�dwsize��СΪ��λ
}NET_OUT_DOFINDNUMBERSTAT;

/////����ʶ����ؽṹ��

// �����ԱȲ���ѡ��
typedef struct
{
	BYTE                 bySimilarity;                   // ���ƶȣ�������ڸ���ʶ�Ȳű���(1~100)
	BYTE                 byAccuracy;                     // ʶ�𾫶�(ȡֵ1~10������ֵ���󣬼�⾫����ߣ�����ٶ��½�����СֵΪ1 ��ʾ����ٶ����ȣ����ֵΪ10��ʾ��⾫������)
	BYTE                 byMode;                         // �Ա�ģʽ, 0-����, 1-ָ�������������, 2-����ģʽ(�㷨��������������������Զ�ѡȡ���)
	BYTE                 byAreaNum;                      // ������  
	BYTE                 byAreas[8];                     // �����������, 0-üë��1-�۾���2-���ӣ�3-��ͣ�4-����(�˲�����)
	WORD                 wMaxCandidate;                  // ���������ѡ����
	BYTE                 byReserved[126];                // �����ֽ�
}FACERECOGNITION_OPTION_INFO;

//// ���ܽ�ͨ��������ؽӿڲ���

// �ӿ� CLIENT_GetParkingSpaceStatus ���������
typedef struct tagNET_IN_GET_PARKINGSPACE_STATUS
{
	DWORD                dwSize;                         // �˽ṹ���С
	DWORD                dwWaitTime;                     // �ӿڳ�ʱ�ȴ�ʱ��
	int                  nChannelID;                     // ͨ����
	int *                pLaneID;                        // ȡֵ��Χ[0,255], pLaneID==NULL��ʾ���г�λ,��λ�����ͬDH_PRODUCTION_DEFNITION.nMaxRoadWays
	int                  nLaneCount;                     // ������ڴ�Ϊsizeof(int)*nLaneCount
} NET_IN_GET_PARKINGSPACE_STATUS;

typedef struct tagNET_LANE_PARKINGSPACE_STATUS
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nLaneID;                        // ��λ��
	unsigned int         nPictureId;                     // ͼƬID,���ڻ�ȡͼƬ����
	DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;      // ��ͨ������Ϣ
} NET_LANE_PARKINGSPACE_STATUS;

// �ӿ� CLIENT_GetParkingSpaceStatus ���������
typedef struct tagNET_OUT_GET_PARKINGSPACE_STATUS
{
	DWORD                dwSize;                         // �˽ṹ���С
	NET_LANE_PARKINGSPACE_STATUS* pStatus;               // ���صĳ�λ״̬
	int                  nMaxStatus;                     // ��Ҫ����������ڴ�Ϊsizeof(NET_LANE_PARKINGSPACE_STATUS)*nMaxStatus����nMaxStatus == DH_PRODUCTION_DEFNITION.nMaxRoadWays
	int                  nRetStatus;                     // ʵ�ʷ��صĳ�λ״̬��
} NET_OUT_GET_PARKINGSPACE_STATUS;

// �ӿ� CLIENT_AttachParkingSpaceData ���������
typedef struct tagNET_CB_PARKINGSPACE_DATA
{
	DWORD                dwSize;                         // �˽ṹ���С
	void*                pPicBuffer;                     // ͼƬ����������
	unsigned int         nPicLength;                     // ͼƬ�ܳ���
} NET_CB_PARKINGSPACE_DATA;

// �ӿ� CLIENT_AttachParkingSpaceData �ص�������pBuf��json��ͼƬ���ݣ�nBufLen��pBuf��Ӧ���ȣ�����ת������
typedef int (CALLBACK *fNotifySnapData)(LLONG lParkingHandle, NET_CB_PARKINGSPACE_DATA* pDiagnosisInfo, void* pBuf, int nBufLen, LDWORD dwUser);

// �ӿ� CLIENT_AttachParkingSpaceData ���������
typedef struct tagNET_IN_ATTACH_PARKINGSPACE
{
	DWORD                dwSize;                         // �˽ṹ���С
	DWORD                dwWaitTime;                     // �ӿڳ�ʱ�ȴ�ʱ��
	int                  nChannelID;                     // ͨ����
	unsigned int         nPictureId;                     // ͼƬID,��NET_LANE_PARKINGSPACE_STATUS.nPictureId
	
	fNotifySnapData      cbNotifySnapData;               // �ص�����
	LDWORD               dwUser;                         // �û��Զ������
} NET_IN_ATTACH_PARKINGSPACE;

// �ӿ� CLIENT_AttachParkingSpaceData ���������
typedef struct tagNET_OUT_ATTACH_PARKINGSPACE
{
	DWORD                dwSize;                         // �˽ṹ���С
} NET_OUT_ATTACH_PARKINGSPACE;

// �ӿ� CLIENT_DetachParkingSpaceData ���������
typedef struct tagNET_IN_DETACH_PARKINGSPACE
{
	DWORD                dwSize;                         // �˽ṹ���С
	DWORD                dwWaitTime;                     // �ӿڳ�ʱ�ȴ�ʱ��
	LLONG                lParkingHandle;                 // CLIENT_AttachParkingSpaceData���صľ��
} NET_IN_DETACH_PARKINGSPACE;
// �ӿ� CLIENT_DetachParkingSpaceData ���������
typedef struct tagNET_OUT_DETACH_PARKINGSPACE
{
	DWORD                dwSize;                         // �˽ṹ���С
} NET_OUT_DETACH_PARKINGSPACE;

///////////////////////////////// IVS ��������Ƶ���ģ�� /////////////////////////////////
// ��Ƶ����ϱ����������Ͷ���
#define NET_DIAGNOSIS_DITHER                    "VideoDitherDetection"                       // ��Ƶ������� ��Ӧ�ṹ��(NET_VIDEO_DITHER_DETECTIONRESULT)
#define NET_DIAGNOSIS_STRIATION                 "VideoStriationDetection"                    // ��Ƶ���Ƽ�� ��Ӧ�ṹ��(NET_VIDEO_STRIATION_DETECTIONRESULT)
#define NET_DIAGNOSIS_LOSS                      "VideoLossDetection"                         // ��Ƶ��ʧ��� ��Ӧ�ṹ��(NET_VIDEO_LOSS_DETECTIONRESULT)
#define NET_DIAGNOSIS_COVER                     "VideoCoverDetection"                        // ��Ƶ�ڵ���� ��Ӧ�ṹ��(NET_VIDEO_COVER_DETECTIONRESULT)
#define NET_DIAGNOSIS_FROZEN                    "VideoFrozenDetection"                       // ��Ƶ������ ��Ӧ�ṹ��(NET_VIDEO_FROZEN_DETECTIONRESULT)
#define NET_DIAGNOSIS_BRIGHTNESS                "VideoBrightnessDetection"                   // ��Ƶ�����쳣��� ��Ӧ�ṹ��(NET_VIDEO_BRIGHTNESS_DETECTIONRESULT)
#define NET_DIAGNOSIS_CONTRAST                  "VideoContrastDetection"                     // ��Ƶ�Աȶ��쳣��� ��Ӧ�ṹ��(NET_VIDEO_CONTRAST_DETECTIONRESULT)
#define NET_DIAGNOSIS_UNBALANCE                 "VideoUnbalanceDetection"                    // ��Ƶƫɫ��� ��Ӧ�ṹ��(NET_VIDEO_UNBALANCE_DETECTIONRESULT)
#define NET_DIAGNOSIS_NOISE                     "VideoNoiseDetection"                        // ��Ƶ������� ��Ӧ�ṹ��(NET_VIDEO_NOISE_DETECTIONRESULT)
#define NET_DIAGNOSIS_BLUR                      "VideoBlurDetection"                         // ��Ƶģ����� ��Ӧ�ṹ��(NET_VIDEO_BLUR_DETECTIONRESULT)
#define NET_DIAGNOSIS_SCENECHANGE               "VideoSceneChangeDetection"                  // ��Ƶ�����仯��� ��Ӧ�ṹ��(NET_VIDEO_SCENECHANGE_DETECTIONRESULT)

enum NET_STATE_TYPE
{
	NET_EM_STATE_ERR,        // ����
	NET_EM_STATE_NORMAL,     // "Normal" ���� 
	NET_EM_STATE_WARNING,    // "Warning" ����
	NET_EM_STATE_ABNORMAL,   // "Abnormal" �쳣
};
// ��Ƶ��������
enum NET_STREAM_TYPE
{
	NET_EM_STREAM_ERR,                  // ����
	NET_EM_STREAM_MAIN,					// "Main"-������
	NET_EM_STREAM_EXTRA_1,				// "Extra1"-������1
	NET_EM_STREAM_EXTRA_2,				// "Extra2"-������2
	NET_EM_STREAM_EXTRA_3,				// "Extra3"-������3
	NET_EM_STREAM_SNAPSHOT,				// "Snapshot"-ץͼ����
	NET_EM_STREAM_OBJECT,				// "Object"-������
	NET_EM_STREAM_AUTO,                 // "Auto"-�Զ�ѡ���������
	NET_EM_STREAM_PREVIEW,              // "Preview"-Ԥ������������
};
// ͨ�ñ䳤�ַ����ԡ�\0������
typedef struct tagNET_ARRAY
{
	DWORD                dwSize;                         // �˽ṹ���С
	char*                pArray;                         // ������ Ŀǰ��С260�ֽڣ������������ڴ� ������ݱ�֤��'\0'����
	DWORD                dwArrayLen;                     // ����ռ䳤��
}NET_ARRAY;

// ��Ƶ��Ͻ���ϱ�ͨ������
typedef struct tagNET_VIDEODIAGNOSIS_COMMON_INFO
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nDiagnosisID;                   // ���ͨ��
	NET_ARRAY            stProject;                      // �ƻ�����
	NET_ARRAY            stTask;                         // ��������
	NET_ARRAY            stProfile;                      // ����������
	NET_ARRAY            stDeviceID;                     // �豸Ψһ��־
	NET_TIME             stStartTime;                    // ��ʼʱ��
	NET_TIME             stEndTime;                      // ����ʱ��
	int                  nVideoChannelID;                // ��Ƶͨ���� ǰ���豸����DVR,IPC��ͨ��
	NET_STREAM_TYPE      emVideoStream;                  // ��Ƶ����
}NET_VIDEODIAGNOSIS_COMMON_INFO;

// ��Ӧ�������(NET_DIAGNOSIS_DITHER) ��Ƶ��������� -- ����仯 �紵���ζ���ת��������̨ת��
typedef struct tagNET_VIDEO_DITHER_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nValue;                         // ���������ֵ
	NET_STATE_TYPE       emState;                        // �����״̬  һ��С�����������������쳣���м��Ǿ���
	int                  nDuration;                      // ״̬����ʱ��  �����������ʱ�� ��ʱ����
}NET_VIDEO_DITHER_DETECTIONRESULT;
// ��Ӧ�������(NET_DIAGNOSIS_STRIATION)��Ƶ���Ƽ���� -- ����ܵ����ų����쳣����
typedef struct tagNET_VIDEO_STRIATION_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nValue;                         // ���������ֵ
	NET_STATE_TYPE       emState;                        // �����״̬
	int                  nDuration;                      // ״̬����ʱ��
}NET_VIDEO_STRIATION_DETECTIONRESULT;
// ��Ӧ�������(NET_DIAGNOSIS_LOSS)��Ƶ��ʧ����� -- �ϵ� ���ߵ���ɵ�
typedef struct tagNET_VIDEO_LOSS_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	NET_STATE_TYPE       emState;                        // �����״̬
	int                  nDuration;                      // ״̬����ʱ��
}NET_VIDEO_LOSS_DETECTIONRESULT;
// ��Ӧ�������(NET_DIAGNOSIS_COVER)��Ƶ�ڵ������ -- ������ڵ���
typedef struct tagNET_VIDEO_COVER_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nValue;                         // ���������ֵ
	NET_STATE_TYPE       emState;                        // �����״̬
	int                  nDuration;                      // ״̬����ʱ��
}NET_VIDEO_COVER_DETECTIONRESULT;
// ��Ӧ�������(NET_DIAGNOSIS_FROZEN)��Ƶ�������� -- ���治�����Ϊ����
typedef struct tagNET_VIDEO_FROZEN_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	NET_STATE_TYPE       emState;                        // �����״̬
	int                  nDuration;                      // ״̬����ʱ��
}NET_VIDEO_FROZEN_DETECTIONRESULT;
// ��Ӧ�������(NET_DIAGNOSIS_BRIGHTNESS)��Ƶ�����쳣����� --������������ò���ȷ��һЩ������
typedef struct tagNET_VIDEO_BRIGHTNESS_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nValue;                         // ���������ֵ
	NET_STATE_TYPE       emState;                        // �����״̬
	int                  nDuration;                      // ״̬����ʱ��
}NET_VIDEO_BRIGHTNESS_DETECTIONRESULT;
// ��Ӧ�������(NET_DIAGNOSIS_CONTRAST)��Ƶ�Աȶ��쳣�����
typedef struct tagNET_VIDEO_CONTRAST_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nValue;                         // ���������ֵ
	NET_STATE_TYPE       emState;                        // �����״̬
	int                  nDuration;                      // ״̬����ʱ��
}NET_VIDEO_CONTRAST_DETECTIONRESULT;
// ��Ӧ�������(NET_DIAGNOSIS_UNBALANCE)��Ƶƫɫ�쳣�����
typedef struct tagNET_VIDEO_UNBALANCE_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nValue;                         // ���������ֵ
	NET_STATE_TYPE       emState;                        // �����״̬
	int                  nDuration;                      // ״̬����ʱ��
}NET_VIDEO_UNBALANCE_DETECTIONRESULT;
// ��Ӧ�������(NET_DIAGNOSIS_NOISE)��Ƶ�����쳣�����
typedef struct tagNET_VIDEO_NOISE_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nValue;                         // ���������ֵ
	NET_STATE_TYPE       emState;                        // �����״̬
	int                  nDuration;                      // ״̬����ʱ��
}NET_VIDEO_NOISE_DETECTIONRESULT;
// ��Ӧ�������(NET_DIAGNOSIS_BLUR)��Ƶģ���쳣�����
typedef struct tagNET_VIDEO_BLUR_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nValue;                         // ���������ֵ
	NET_STATE_TYPE       emState;                        // �����״̬
	int                  nDuration;                      // ״̬����ʱ��
}NET_VIDEO_BLUR_DETECTIONRESULT;
// ��Ӧ�������(NET_DIAGNOSIS_SCENECHANGE)��Ƶ�����仯�����
typedef struct tagNET_VIDEO_SCENECHANGE_DETECTIONRESULT
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nValue;                         // ���������ֵ
	NET_STATE_TYPE       emState;                        // �����״̬
	int                  nDuration;                      // ״̬����ʱ��
}NET_VIDEO_SCENECHANGE_DETECTIONRESULT;

typedef struct tagNET_DIAGNOSIS_RESULT_HEADER
{
	DWORD                dwSize;                         // �˽ṹ���С

	char                 szDiagnosisType[MAX_PATH];      // ������ͣ����dhnetsdk.h��"��Ƶ����ϱ����������Ͷ���" ��NET_DIAGNOSIS_DITHER
	int                  nDiagnosisTypeLen;              // ��������ͽṹ���С
}NET_DIAGNOSIS_RESULT_HEADER;

// cbVideoDiagnosis �ص���������
typedef struct tagNET_REAL_DIAGNOSIS_RESULT
{
	DWORD                dwSize;                         // �˽ṹ���С

    NET_VIDEODIAGNOSIS_COMMON_INFO* pstDiagnosisCommonInfo;  //��Ƶ���ͨ����Ϣ
	
	int					 nTypeCount;					 // ��Ͻ������������͸���
	void*                pDiagnosisResult;               // һ����Ͻ�����ݣ���ʽ��NET_DIAGNOSIS_RESULT_HEADER+�������1+NET_DIAGNOSIS_RESULT_HEADER+�������2+...
	DWORD                dwBufSize;                      // ���峤��
}NET_REAL_DIAGNOSIS_RESULT;

//��Ƶ��Ͻ���ϱ��ص�����
typedef int (CALLBACK *fRealVideoDiagnosis)(LLONG lDiagnosisHandle, NET_REAL_DIAGNOSIS_RESULT* pDiagnosisInfo, void* pBuf, int nBufLen, LDWORD dwUser);

// �ӿ� CLIENT_StartVideoDiagnosis ���������
typedef struct tagNET_IN_VIDEODIAGNOSIS
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nDiagnosisID;                   // ��Ƶ���ID����0��ʼ
	DWORD                dwWaitTime;                     // �ӿڳ�ʱ�ȴ�ʱ��

	fRealVideoDiagnosis  cbVideoDiagnosis;               // ��Ƶ��Ͻ���ص�����
	LDWORD                dwUser;                         // �û��Զ������
}NET_IN_VIDEODIAGNOSIS;

// �ӿ� CLIENT_StartVideoDiagnosis ���������
typedef struct tagNET_OUT_ATTACH_REALDIAGNOSIS
{
	DWORD                dwSize;                         // �˽ṹ���С
	LLONG                lDiagnosisHandle;               // ���ľ��
}NET_OUT_VIDEODIAGNOSIS;

// �ӿ� CLIENT_StartFindDiagnosisResult ���������
typedef struct tagNET_IN_FIND_DIAGNOSIS
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nDiagnosisID;                   // ��Ƶ���ID����0��ʼ
	DWORD                dwWaitTime;                     // �ӿڳ�ʱ�ȴ�ʱ��

	NET_ARRAY            stuDeviceID;                    // �豸Ψһ��־,pArray:NULL��ʾ��ʹ���豸ID��ѯ
	NET_TIME             stuStartTime;                   // ��ʼʱ��
	NET_TIME             stuEndTime;                     // ����ʱ��
	int                  nVideoChannel;                  // ��Ƶͨ����,-1:����ͨ����
	int                  nTypeCount;                     // ������͸���,0:��ʹ��������Ͳ�ѯ
	NET_ARRAY*           pstDiagnosisTypes;              // ����������飬��ʾ��Ҫ��ѯ���������
	char                 szProjectName[MAX_PATH];        // �ƻ�����
} NET_IN_FIND_DIAGNOSIS;

// �ӿ� CLIENT_StartFindDiagnosisResult ���������
typedef struct tagNET_OUT_FIND_DIAGNOSIS
{
	DWORD                dwSize;                         // �˽ṹ���С
	LLONG                 lFindHandle;                    // ��ѯ���
	DWORD                dwTotalCount;                   // �����������ܸ���
}NET_OUT_FIND_DIAGNOSIS;

// �ӿ� CLIENT_DoFindDiagnosisResult ���������
typedef struct tagNET_IN_DIAGNOSIS_INFO
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nDiagnosisID;                   // ��Ƶ���ID����0��ʼ
	DWORD                dwWaitTime;                     // �ӿڳ�ʱ�ȴ�ʱ��

	int                  nFindCount;                     // ÿ�β�ѯ����Ƶ��Ͻ������
	int                  nBeginNumber;                   // ��ѯ��ʼ��� 0<=beginNumber<= totalCount-1
}NET_IN_DIAGNOSIS_INFO;

// ��λ����Ϣ
typedef struct tagNET_CARPORTLIGHT_INFO
{
	DWORD               dwSize;  
	NET_CARPORTLIGHT_TYPE emType;                        // ��λ������
	NET_CARPORTLIGHT_MODE emMode;                        // ��λ�����Ʒ�ʽ
}NET_CARPORTLIGHT_INFO;

// ��λ��״̬
typedef struct tagNET_CARPORTLIGHT_STATUS
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nLightNum;                      // ��λ���� 
	NET_CARPORTLIGHT_INFO stuLights[DH_MAX_CARPORTLIGHT_NUM]; // ��λ����Ϣ,������emType�����ظ���һ����ƺ�һ���̵�
	int                  nFiringTime;                   // ״̬����ʱ��,��λ��
	int                  nHoldTime;                     // ״̬����ʱ��,��λ�룬-1��ʾ���ޱ��֣�0��ʾ���п���
}NET_CARPORTLIGHT_STATUS;

// �ӿ�CLIENT_GetCarPortLightStatus���������
typedef struct tagNET_IN_GET_CARPORTLIGHT_STATUS
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nChannelId;                     // ͨ����
}NET_IN_GET_CARPORTLIGHT_STATUS;

// �ӿ�CLIENT_GetCarPortLightStatus���������
typedef struct tagNET_OUT_GET_CARPORTLIGHT_STATUS
{
	DWORD                dwSize;                         // �˽ṹ���С
	NET_CARPORTLIGHT_STATUS stuLightStatus;              // ��λ��״̬
}NET_OUT_GET_CARPORTLIGHT_STATUS;

// �ӿ� CLIENT_SetCarPortLightStatus ���������
typedef struct tagNET_IN_SET_CARPORTLIGHT_STATUS
{
	DWORD                dwSize;                         // �˽ṹ���С
	int                  nChannelId;
	NET_CARPORTLIGHT_STATUS stuLightStatus;              // ��λ��״̬
}NET_IN_SET_CARPORTLIGHT_STATUS;

// �ӿ� CLIENT_SetCarPortLightStatus ���������
typedef struct tagNET_OUT_SET_CARPORTLIGHT_STATUS
{
	DWORD                dwSize;                         // �˽ṹ���С
	
}NET_OUT_SET_CARPORTLIGHT_STATUS;


typedef struct tagNET_DEV_VIDEODIAGNOSIS_MULTI_INFO
{
	DWORD                dwSize;                         // �˽ṹ���С

    NET_VIDEODIAGNOSIS_COMMON_INFO*          pstDiagnosisCommonInfo;  //��Ƶ���ͨ����Ϣ  ���½ṹ��ָ����Ҫ�����߷���
	
	BOOL                 abDither;           // ���ڱ�ʾ�˴ν�������������Ƿ���Ч
	NET_VIDEO_DITHER_DETECTIONRESULT*        pstDither;  // ��Ƶ�������
	
	BOOL                 abStration;
	NET_VIDEO_STRIATION_DETECTIONRESULT*     pstStration;// ��Ƶ���Ƽ��
	
	BOOL                 abLoss;
	NET_VIDEO_LOSS_DETECTIONRESULT*          pstLoss;    // ��Ƶ��ʧ���
	
	BOOL                 abCover;
	NET_VIDEO_COVER_DETECTIONRESULT*         pstCover;   // ��Ƶ�ڵ����
	
	BOOL                 abFrozen;
	NET_VIDEO_FROZEN_DETECTIONRESULT*        pstFrozen;  // ��Ƶ������
	
	BOOL                 abBrightness;
	NET_VIDEO_BRIGHTNESS_DETECTIONRESULT*    pstBrightness;// ��Ƶ�����쳣���
	
	BOOL                 abContrast;
	NET_VIDEO_CONTRAST_DETECTIONRESULT*      pstContrast;// ��Ƶ�Աȶ��쳣���
	
	BOOL                 abUnbalance;
	NET_VIDEO_UNBALANCE_DETECTIONRESULT*     pstUnbalance;// ��Ƶƫɫ���
	
	BOOL                 abNoise;
	NET_VIDEO_NOISE_DETECTIONRESULT*         pstNoise;   // ��Ƶ�������
	
	BOOL                 abBlur;
	NET_VIDEO_BLUR_DETECTIONRESULT*          pstBlur;    // ��Ƶģ�����
	
	BOOL                 abSceneChange;
	NET_VIDEO_SCENECHANGE_DETECTIONRESULT*   pstSceneChange;// ��Ƶ�����仯���
}NET_VIDEODIAGNOSIS_RESULT_INFO;

// �ӿ� CLIENT_DoFindDiagnosisResult ���������
typedef struct tagNET_OUT_DIAGNOSIS_INFO
{
	DWORD                dwSize;                         // �˽ṹ���С

	int                  nInputNum;                      // �û������NET_DEV_RESULT_VIDEODIAGNOSIS_INFO����
	int                  nReturnNum;                     // ���ؽ������
	NET_VIDEODIAGNOSIS_RESULT_INFO*  pstDiagnosisResult; // �������  �ṹ��ָ����Ҫ�����߷���
}NET_OUT_DIAGNOSIS_INFO;

///////////////////////////////// ����ʽ�豸����ģ�� //////////////////////////////////////////////////////
///////////////////////////////// CLIENT_OperateMasterSlaveDevice�ӿڲ������� /////////////////////////////////
#define        MASTERSLAVE_CMD_START                   "masterSlaveTracker.start"                   // ��������ʽ����������
#define        MASTERSLAVE_CMD_STOP                    "masterSlaveTracker.stop"                    // ֹͣ����ʽ����������
#define        MASTERSLAVE_CMD_MANUALTRACK             "masterSlaveTracker.manualSelectObjectTrack" // �ֶ�ѡ��Ŀ�����
#define        MASTERSLAVE_CMD_POINTTRACK              "masterSlaveTracker.selectPointTrack"        // �������
#define        MASTERSLAVE_CMD_GETCALIBPOINTS          "masterSlaveTracker.getCalibratePoints"      // �õ����б궨��
#define        MASTERSLAVE_CMD_CALIBRATE               "masterSlaveTracker.calibrate"               // ����궨��
#define        MASTERSLAVE_CMD_ADDCALIBPOINT           "masterSlaveTracker.addCalibratePoint"       // ���ӱ궨��
#define        MASTERSLAVE_CMD_REMOVECALIBPOINT        "masterSlaveTracker.removeCalibratePoint"    // ɾ���궨��
#define        MASTERSLAVE_CMD_MARKMAXZOOM             "masterSlaveTracker.markSceneMaxZoom"        // �궨���������ٱ���, �ѵ�ǰ������Ϊ�����

// ����ʽ�豸���
typedef struct __NET_MS_PAIRPOINTS
{
	int                nStructSize;
    DH_POINT           stMasterPoint;    // ������궨�㣬��������һ����[0,8192]����
    DH_POINT           stSlavePoint;     // ������궨�㣬��������һ����[0,8192]����
}NET_MS_PAIRPOINTS;
//MASTERSLAVE_CMD_START���������ṹ��
typedef struct __NET_IN_MS_START
{
	int                nStructSize;
}NET_IN_MS_START;

//MASTERSLAVE_CMD_START���������ṹ��
typedef struct __NET_OUT_MS_START
{
	int                nStructSize;
}NET_OUT_MS_START;

//MASTERSLAVE_CMD_STOP���������ṹ��
typedef struct __NET_IN_MS_STOP
{
	int                nStructSize;
}NET_IN_MS_STOP;

//MASTERSLAVE_CMD_STOP���������ṹ��
typedef struct __NET_OUT_MS_STOP
{
	int                nStructSize;
}NET_OUT_MS_STOP;

//MASTERSLAVE_CMD_MANUALTRACK���������ṹ��
typedef struct __NET_IN_MS_MANUALTRACK
{
	int                nStructSize;
	DWORD              dwObject;          // -1 ��ʾ�������������λ������, >=0��ʾָ�������壨���Դ��豸��������֡�õ���
}NET_IN_MS_MANUALTRACK;

//MASTERSLAVE_CMD_MANUALTRACK���������ṹ��
typedef struct __NET_OUT_MS_MANUALTRACK
{
	int                nStructSize;
}NET_OUT_MS_MANUALTRACK;

//MASTERSLAVE_CMD_POINTTRACK���������ṹ��
typedef struct __NET_IN_MS_POINTTRACK
{
	int                nStructSize;
	DH_POINT           stTrackerPoint;    // ���ٵ㣬��������һ����[0,8192]���� 
}NET_IN_MS_POINTTRACK;

//MASTERSLAVE_CMD_POINTTRACK���������ṹ��
typedef struct __NET_OUT_MS_POINTTRACK
{
	int                nStructSize;
}NET_OUT_MS_POINTTRACK;

//MASTERSLAVE_CMD_GETCALIBPOINTS���������ṹ��
typedef struct __NET_IN_MS_GETCALIBPOINTS
{
	int                nStructSize;
}NET_IN_MS_GETCALIBPOINTS;

//MASTERSLAVE_CMD_GETCALIBPOINTS���������ṹ��
typedef struct __NET_OUT_MS_GETCALIBPOINTS
{
	int                        nStructSize;
	int                        nPointsNum;                           // ʵ�ʱ궨����
	NET_MS_PAIRPOINTS          stPairPoints[MAX_CALIBPOINTS_NUM];    // �궨�������
}NET_OUT_MS_GETCALIBPOINTS;

//MASTERSLAVE_CMD_CALIBRATE���������ṹ��
typedef struct __NET_IN_MS_CALIBRATE
{
	int                nStructSize;
}NET_IN_MS_CALIBRATE;

//MASTERSLAVE_CMD_CALIBRATE���������ṹ��
typedef struct __NET_OUT_MS_CALIBRATE
{
	int                nStructSize;      
}NET_OUT_MS_CALIBRATE;

//MASTERSLAVE_CMD_ADDCALIBPOINT���������ṹ��
typedef struct __NET_IN_MS_ADDCALIBPOINT
{
	int                        nStructSize;
	BOOL                       bSlavePointEn;        // ������궨��ʹ��λ, TURE���ô�����궨����Ч��FASLE����Ч, �豸�Լ���ȡ��ǰ�Ĵ�����궨�㡣
	NET_MS_PAIRPOINTS          stPairPoints;         // �������������
}NET_IN_MS_ADDCALIBPOINT;

//MASTERSLAVE_CMD_ADDCALIBPOINT���������ṹ��
typedef struct __NET_OUT_MS_ADDCALIBPOINT
{
	int                nStructSize;
	DH_POINT           stPoint;      // �ӱ궨��
}NET_OUT_MS_ADDCALIBPOINT;


//MASTERSLAVE_CMD_REMOVECALIBPOINT���������ṹ��
typedef struct __NET_IN_MS_REMOVECALIBPOINT
{
	int                nStructSize;
	DH_POINT           stPoint;      // ���궨��
}NET_IN_MS_REMOVECALIBPOINT;

//MASTERSLAVE_CMD_REMOVECALIBPOINT���������ṹ��
typedef struct __NET_OUT_MS_REMOVECALIBPOINT
{
	int                nStructSize;      
}NET_OUT_MS_REMOVECALIBPOINT;

//MASTERSLAVE_CMD_MARKMAXZOOM��������ṹ��
typedef struct __NET_IN_MS_MARKMAXZOOM
{
	int                nStructSize; 
}NET_IN_MS_MARKMAXZOOM;

//MASTERSLAVE_CMD_MARKMAXZOOM��������ṹ��
typedef struct __NET_OUT_MS_MARKMAXZOOM
{
	int                nStructSize; 
}NET_OUT_MS_MARKMAXZOOM;

///////////////////////////////// CLIENT_OperateVideoAnalyseDevice �ӿڲ������� /////////////////////////////////
#define     NET_SET_MODULESTATE                         "devVideoAnalyse.setModuleState"                        // ����ģ��״̬
#define		NET_TEST_WITH_SCREENPOINTS					"devVideoAnalyse.testCalibrateWithScreenPoints"			// ������Ļ������Ծ���������õ���������֮���ʵ�ʾ��롣�ڲ���֮ǰ����Ҫ����ɲ������á�
#define		NET_TEST_WITH_METRICLENGTH					"devVideoAnalyse.testCalibrateWithMetricLength"		    // ����ʵ�ʳ��ȡ���ʼ�㼰��������꣬���Ծ������
#define		NET_GET_INTERNALOPTIONS						"devVideoAnalyse.getInternalOptions"					// ��ȡ�ڲ�ѡ��
#define		NET_TUNE_INTERNALOPTIONS					"devVideoAnalyse.tuneInternalOptions"					// �����ڲ�ѡ��
#define		NET_RESET_INTERNALOPTIONS					"devVideoAnalyse.resetInternalOptions"					// ��λ���е����ڲ�ѡ��

// �߶�����
enum NET_EM_LINETYPE
{
	NET_EM_HORIZONTAL,
	NET_EM_VERTICAL,
};

// NET_TEST_WITH_SCREENPOINTS
typedef struct __NET_IN_CALIBRATE_BY_POINTS
{
	DWORD               dwSize;                 // �˽ṹ���С

	DH_POINT            stStartPoint;           // �߶��������	������������һ����[0,8191]���䡣
	DH_POINT            stEndPoint;             // ��ֹ������	������������һ����[0,8191]���䡣	
	NET_EM_LINETYPE     emType;                 // �߶�����	em_Horizontal("Horizontal") ˮƽ�߶� em_Vertical("Vertical")��ֱ�߶�
}NET_IN_CALIBRATE_BY_POINTS;
typedef struct __NET_OUT_CALIBRATE_BY_POINTS
{
	DWORD               dwSize;                 // �˽ṹ���С

	double              dlength;                // ����֮���ʵ�ʳ���	��λΪ��
}NET_OUT_CALIBRATE_BY_POINTS;

// NET_TEST_WITH_METRICLENGTH
typedef struct __NET_IN_CALIBRATE_BY_LENGTH
{
	DWORD               dwSize;                 // �˽ṹ���С

	double				nLength;				// ����֮���ʵ�ʳ���	��Ϊ��λ
	DH_POINT			stStartPoint;			// �߶��������	������������һ����[0,8191]���䡣
	DH_POINT			stDirection;			// �߶η��������	ֻ�Դ�ֱ�߶���Ч��������������һ����[0,8191]���䡣
	NET_EM_LINETYPE		emType;					// �߶�����	em_Horizontal("Horizontal") ˮƽ�߶� em_Vertical("Vertical")��ֱ�߶�				
}NET_IN_CALIBRATE_BY_LENGTH;

typedef struct __NET_OUT_CALIBRATE_BY_LENGTH
{
	DWORD               dwSize;                 // �˽ṹ���С
	
	DH_POINT			stEndPoint;				// �߶��յ���Ļ����	������������һ����[0,8191]���䡣	
}NET_OUT_CALIBRATE_BY_LENGTH;

typedef struct __NET_INTERNAL_OPTION
{
	DWORD               dwSize;                 // �˽ṹ���С

	int					nIndex;					// ѡ�����
	NET_ARRAY           stKey;				    // ѡ�����ƣ�������\0����256�ֽ�,��������
	int					nValue;					// ѡ��ȡֵ
	int					nMinValue;				// ��Сֵ
	int					nMaxValue;				// ���ֵ
}NET_INTERNAL_OPTION;

// �����ڲ�ѡ�� NET_GET_INTERNALOPTIONS
typedef struct __NET_IN_GETINTERNAL_OPTIONS
{
	DWORD               dwSize;                 // �˽ṹ���С
}NET_IN_GETINTERNAL_OPTIONS;

typedef struct __NET_OUT_GETINTERNAL_OPTIONS
{
	DWORD               dwSize;                 // �˽ṹ���С

	int					nTotalOptionNum;		// ѡ����� ���ֵ��ѯ����
	int					nReturnOptionNum;		// ���ص�ʵ��ѡ�����
	NET_INTERNAL_OPTION* pstInternalOption;	    // ѡ���б� �����߷����ַ
}NET_OUT_GETINTERNAL_OPTIONS;

// NET_TUNE_INTERNALOPTIONS
typedef struct __NET_IN_TUNEINTERNAL_OPTION
{
	DWORD               dwSize;                 // �˽ṹ���С
	int					nOptionCount;	    	// ѡ�����
	NET_INTERNAL_OPTION* pstInternalOption;	    // ѡ���б� ���������ָ���
}NET_IN_TUNEINTERNAL_OPTION;
typedef struct __NET_OUT_TUNEINTERNAL_OPTION
{
	DWORD               dwSize;                 // �˽ṹ���С
}NET_OUT_TUNEINTERNAL_OPTION;

// NET_RESET_INTERNALOPTIONS
typedef struct __NET_IN_RESETINTERNAL_OPTION
{
	DWORD               dwSize;                 // �˽ṹ���С
}NET_IN_RESETINTERNAL_OPTION;
typedef struct __NET_OUT_RESETINTERNAL_OPTION
{
	DWORD               dwSize;                 // �˽ṹ���С
}NET_OUT_RESETINTERNAL_OPTION;

// NET_SET_MODULESTATE
enum NET_EM_MODULESTATE
{
	NET_EM_MODULESTATE_OK,
	NET_EM_MODULESTATE_PAUSE,
};
typedef struct __NET_IN_SETMODULESTATE
{
	DWORD				dwSize;					// �˽ṹ���С
	NET_EM_MODULESTATE  emState;				// 0-����������1-��ͣ���ٴ��л���������������Ѿ������仯����Ҫ�ؽ�������
	int                 nIndex;                 // ģ����	-1ָ����ģ��
}NET_IN_SETMODULESTATE;
typedef struct __NET_OUT_SETMODULESTATE
{
	DWORD				dwSize;					// �˽ṹ���С
}NET_OUT_SETMODULESTATE;

/////////////////////////////////CLIENT_DeleteDevConfig �ӿڲ���/////////////////////////////////
/*
 * CLIENT_DeleteDevConfig �����������
 */

enum NET_EM_CONFIGOPTION
{
	NET_EM_CONFIGOPTION_OK,
	NET_EM_CONFIGOPTION_NEEDRESTART,
	NET_EM_CONFIGOPTION_NEEDREBOOT=2,
	NET_EM_CONFIGOPTION_WRITEFILEERROR=4,
	NET_EM_CONFIGOPTION_CAPSNOTSUPPORT=8,
	NET_EM_CONFIGOPTION_VALIDATEFAILED=16,
};

typedef struct tagNET_IN_DELETECFG
{
	DWORD         dwSize;                 // �ṹ���С

	char*         szCommand;                    // ��������
}NET_IN_DELETECFG;
typedef struct tagNET_OUT_DELETECFG
{
	DWORD         dwSize;                       // �ṹ���С

    int           nError;                       // �豸���صĴ�����
    int           nRestart;                     // �豸�Ƿ�����

	DWORD         dwOptionMask;                 // ѡ�� �����ö��NET_EM_CONFIGOPTION
}NET_OUT_DELETECFG;

/////////////////////////////////CLIENT_GetMemberNames �ӿڲ���/////////////////////////////////
/*
 * CLIENT_GetMemberNames �����������
 */
typedef struct tagNET_IN_MEMBERNAME
{
	DWORD         dwSize;                       // �ṹ���С
	char*         szCommand;                    // ��������
}NET_IN_MEMBERNAME;
typedef struct tagNET_OUT_MEMBERNAME
{
	DWORD         dwSize;                       // �ṹ���С
    
	int           nError;                       // �豸���صĴ�����
    int           nRestart;                     // �豸�Ƿ�����

	int           nTotalNameCount;              // ���Ƹ��� ͨ���������õ�����������д
	int           nRetNameCount;                // ���ص�ʵ�����Ƹ���
	NET_ARRAY*    pstNames;                     // �������� �����������ڴ棬������nTotalNameCount��
}NET_OUT_MEMBERNAME;

////////////////////////////////////��ƵŨ����ؽṹ��//////////////////////////////////////
// �������
enum NET_EM_STAFF_TYPE
{
	NET_EM_STAFF_TYPE_ERR,
	NET_EM_STAFF_TYPE_HORIZONTAL,                       // "Horizontal" ˮƽ�߶�
	NET_EM_STAFF_TYPE_VERTICAL,                         // "Vertical" ��ֱ�߶�
	NET_EM_STAFF_TYPE_ANY,                              // "Any" �����߶�
	NET_EM_STAFF_TYPE_CROSS,                            // "Cross" ��ֱ�潻�߶�
};

// ��������
enum NET_EM_CALIBRATEAREA_TYPE
{
	NET_EM_CALIBRATEAREA_TYPE_ERR,
	NET_EM_CALIBRATEAREA_TYPE_GROUD,		            // "Groud" : ���棬��ҪN����ֱ�߶�+M��ˮƽ�߶Σ���N=3��M=1������N=2��M=2���������չ����
	NET_EM_CALIBRATEAREA_TYPE_HORIZONTAL,	            // "Horizontal"  : ˮƽ�棬��Ҫˮƽ����һ�㵽������ͶӰ��ֱ�߶Ρ�		
	NET_EM_CALIBRATEAREA_TYPE_VERTICAL,		            // "Vertical" : ��ֱ�棬��Ҫ��ֱ�������Ľ��ߡ�
	NET_EM_CALIBRATEAREA_TYPE_ANY,			            // "Any" ����ƽ�棬N����ֱ�߶Σ���ÿ�����ȣ�N=3���������չ����
};

// �����Ϣ
typedef struct tagNET_STAFF_INFO
{
	DH_POINT	        stuStartLocation;	            // ��ʼ�����
	DH_POINT	        stuEndLocation;		            // ��ֹ�����
	float			    nLenth;				            // ʵ�ʳ���,��λ��
	NET_EM_STAFF_TYPE	emType;			                // �������
}NET_STAFF_INFO;

// �궨����,��ͨ����ʹ��
typedef struct tagNET_CALIBRATEAREA_INFO
{
	int				    nLinePoint;					    // ˮƽ�������߶�����
	DH_POINT	        stuLine[DH_MAX_POLYLINE_NUM];	// ˮƽ��������
	float			    fLenth;						    // ʵ�ʳ���
	DH_POLY_POINTS	    stuArea;					    // ����
	int				    nStaffNum;					    // ��ֱ�����
	NET_STAFF_INFO	    stuStaffs[DH_MAX_STAFF_NUM];    // ��ֱ���         
	NET_EM_CALIBRATEAREA_TYPE emType;			        // ��������
}NET_CALIBRATEAREA_INFO;

typedef struct tagNET_LOCALFILE_INFO
{
	DWORD			    dwSize;
	char			    szFilePath[MAX_PATH];	        // �ļ�����·��
}NET_LOCALFILE_INFO;

typedef struct tagNET_REMOTEFILE_INFO
{
	DWORD			    dwSize;
	char			    szIP[MAX_PATH];	                // Զ���豸IP
	unsigned int	    nPort;				            // Զ���豸�˿�
	char			    szName[DH_MAX_NAME_LEN];        // ��½Զ���豸�û���
	char			    szPassword[DH_MAX_NAME_LEN];    // ��½Զ���豸����
	BYTE			    byProtocolType;			        // Զ���豸ʹ�õ�Э�����ͣ�2-�󻪶�����3-������
	BYTE			    byReserved[3];			        // �ֽڶ���
	char			    szFilePath[MAX_PATH];           // �ļ�����·����byProtocolTypeΪ3ʱ��Ч
	int				    nStartCluster;		  	        // ��ʼ�غţ�byProtocolTypeΪ2ʱ��Ч
	int				    nDriverNo;				        // �̺ţ�byProtocolTypeΪ2ʱ��Ч
	
}NET_REMOTEFILE_INFO;

// �ļ�λ����Ϣ
typedef struct tagNET_FILEPATH_INFO
{
	DWORD				dwSize;
	BOOL				bFileType;			            // TRUE: �����������ļ�; FALSE: Զ���豸�ļ�
	NET_LOCALFILE_INFO	stuLocalFile;		            // �����ļ���Ϣ, bFileType==TRUE��Ч
	NET_REMOTEFILE_INFO	stuRemoteFile;		            // Զ���ļ���Ϣ, bFileType==FALSE��Ч
}NET_FILEPATH_INFO;

// ȫ�ֲ���
typedef struct tagNET_GLOBAL_INFO
{
	DWORD			    dwSize;
	char			    szSceneType[DH_MAX_NAME_LEN];	// Ӧ�ó�����ֻ֧��"Normal"
	int				    nStaffNum;						// �����
	NET_STAFF_INFO	    stuStaffs[DH_MAX_STAFF_NUM];	// ���	
	int				    nCalibrateAreaNum;				// �궨������
	NET_CALIBRATEAREA_INFO stuCalibrateArea[DH_MAX_CALIBRATEBOX_NUM]; // �궨����(�����ֶβ����ڣ�������������Ϊ�궨����)
	int				    nJitter;		                // ����������� : ����������ʣ�ȡֵ0-100����Ӧ��ֹ����������̶ȣ�����Խ������ֵԽ��
	BOOL			    bDejitter;		                // �Ƿ���ȥ����ģ��
}NET_GLOBAL_INFO;

// ģ�����
typedef struct tagNET_MODULE_INFO
{
	DWORD			    dwSize;							// �ýṹ���С
	BYTE			    bSensitivity;					// ������,ȡֵ1-10��ֵԽС������Խ��
	BYTE			    bReserved[3];
	int				    nDetectRegionPoint;				// ������򶥵���
	DH_POINT		    stuDetectRegion[DH_MAX_POLYGON_NUM]; // �������
	int				    nExcludeRegionNum;				// �ų�������
	DH_POLY_POINTS	    stuExcludeRegion[DH_MAX_EXCLUDEREGION_NUM];	// �ų�����
}NET_MODULE_INFO;

// ���������Ϣ
typedef struct tagNET_OBJFILTER_INFO
{
	DWORD		        dwSize;						    // �ýṹ���С
	NET_TIME	        stuStartTime;				    // ��ʼʱ��
	NET_TIME	        stuEndTime;					    // ����ʱ��
	char		        szObjectType[DH_MAX_NAME_LEN];	// ��������,֧������:
											            //"Unknown", "Human", "Vehicle",
											            //"Fire", "Smoke", "Plate", "HumanFace", "Container", "Animal", "TrafficLight", "PastePaper", "HumanHead", "Entity"
	char		        szObjectSubType[64];		    // ��������𣬸��ݲ�ͬ���������ͣ�����ȡ���������ͣ�
											            // Vehicle Category:"Unknown"  δ֪,"Motor" ������,"Non-Motor":�ǻ�����,"Bus": ������,"Bicycle" ���г�,"Motorcycle":Ħ�г�
											            // Plate Category��"Unknown" δ֪,"Normal" ���ƺ���,"Yellow" ����,"DoubleYellow" ˫���β��,"Police" ����"Armed" �侯��,
											            // "Military" ���Ӻ���,"DoubleMilitary" ����˫��,"SAR" �۰���������,"Trainning" ����������
											            // "Personal" ���Ժ���,"Agri" ũ����,"Embassy" ʹ�ݺ���,"Moto" Ħ�г�����,"Tractor" ����������,"Other" ��������
											            // HumanFace Category:"Normal" ��ͨ����,"HideEye" �۲��ڵ�,"HideNose" �����ڵ�,"HideMouth" �첿�ڵ�
	DWORD		        dwRGBMainColor[DH_MAX_COLOR_NUM];	// ������Ҫ��ɫ������Ϊ��ʱ��ʾ�ϰ�����ɫ�����ֽڱ�ʾ���ֱ�Ϊ�졢�̡�����͸����,����:RGBֵΪ(0,255,0),͸����Ϊ0ʱ, ��ֵΪ0x00ff0000
	DWORD		        dwLowerBodyColor[DH_MAX_COLOR_NUM];	// ����Ϊ��ʱ��ʾ�°�����ɫ�����ֽڱ�ʾ���ֱ�Ϊ�졢�̡�����͸����,����:RGBֵΪ(0,255,0),͸����Ϊ0ʱ, ��ֵΪ0x00ff0000
	int			        nMinSize;					    // ������С�ߴ�, m
	int			        nMaxSize;					    // �������ߴ�, m
	int			        nMinSpeed;					    // ��С�ٶ�, km/h
	int			        nMaxSpeed;					    // ����ٶ�, km/h
	DWORD		        dwRGBMainColorNum;			    // ����������Ϊ�ˣ���־dwRGBMainColor��Ч����ɫ������
	DWORD		        dwLowerBodyColorNum;		    // ����������Ϊ����bRGBMainColor==true����־�°�����Ч����ɫ������
	BOOL		        bRGBMainColor;				    // true-dwRGBMainColor��ʾ�ϰ�����ɫ,dwLowerBodyColor��ʾ�°�����ɫ; false-dwRGBMainColor��ʾ����Ҫ��ɫ,dwLowerBodyColor��Ч
}NET_OBJFILTER_INFO;

// �������
typedef struct tagNET_VIDEOSYNOPSISRULE_INFO
{
	DWORD				dwSize;				            // �ýṹ���С
	BYTE				byOutputType;		            // Ũ����������ϵ�����,1-��Ƶ���(һ�����);2-Ũ����Ƶ;3-���п���������Ƶ
	BYTE				byDensity;			            // �ܶ�, 1-10, ֵԽ��, Ũ���ܶ�Խ��
	bool				bShowTime;			            // Ũ������Ƿ���ʾʱ��
	bool				bShowBox;			            // Ũ������Ƿ���ʾ���
	bool				bEnableRecordResult;            // Ũ������Ƿ��¼�����ݿ�
	BYTE				byReserved[3];
	NET_OBJFILTER_INFO	stuFilter[MAX_OBJFILTER_NUM];   // ���������Ϣ
	DWORD				dwObjFilterNum;		            // ���������Ϣ��Ŀ

	// NET_OUT_QUERY_VIDEOSYNOPSIS�У�����CFG_CMD_ANALYSERULE�������dhconfigsdk.dll�нӿ�CLIENT_ParseData�������õ���Ӧ�Ľṹ�壬��ʱҪ�ȷ����㹻�ڴ�
	// NET_IN_ADD_VIDEOSYNOPSIS�У�����CFG_CMD_ANALYSERULE�������dhconfigsdk.dll�нӿ�CLIENT_PacketData��װ���õ�����Ϣ
	char*		        szAnalyseRuleInfo;				// JSON��װ������Ϣ
	int                 nBufferLen;                     // NET_OUT_QUERY_VIDEOSYNOPSIS��ʱ�������szAnalyseRuleInfo����
}NET_VIDEOSYNOPSISRULE_INFO;

// ����Ũ����Ƶ�����������
typedef struct tagNET_IN_ADD_VIDEOSYNOPSIS
{
	DWORD			    dwSize;			                // �ýṹ���С
	NET_FILEPATH_INFO*	pFilePathInfo;	                // �ļ�λ����Ϣ���û�����ռ�
	DWORD				dwFileCount;	                // ��Ч�ļ�����
	NET_GLOBAL_INFO		stuGlobalInfo;	                // ȫ����Ϣ
	NET_MODULE_INFO		stuModuleInfo;	                // ģ����Ϣ
	NET_VIDEOSYNOPSISRULE_INFO	stuRuleInfo;	        // ������Ϣ
	unsigned int		nWaitTime;		                // �ȴ���ʱʱ�䣬��λms
}NET_IN_ADD_VIDEOSYNOPSIS;

// ����Ũ����Ƶ�����������
typedef struct tagNET_OUT_ADD_VIDEOSYNOPSIS
{
	DWORD	            dwSize;			                // �ýṹ���С
	DWORD*	            pnTaskID;		                // TaskID���飬�û�����ռ�.��˳��һһ��Ӧ����������ļ�;����0��ʾ��Ӧ��������ʧ��
	DWORD	            nTaskIDCount;	                // TaskID����
}NET_OUT_ADD_VIDEOSYNOPSIS;

// ��ͣ��ƵŨ�������������
typedef struct tagNET_IN_PAUSE_VIDEOSYNOPSIS
{
	DWORD	            dwSize;			                // �ýṹ���С
	BOOL                bPause;                         // TRUE-��ʾ��ͣ����   FALSE-��ʾ�ָ����� 
	DWORD*	            pnTaskID;		                // TaskID���飬�û�����ռ�
	DWORD	            nTaskIDCount;	                // TaskID����
	DWORD	            nWaitTime;		                // �ȴ���ʱʱ�䣬��λms
}NET_IN_PAUSE_VIDEOSYNOPSIS;

// �Ƴ���ƵŨ�������������
typedef struct tagNET_IN_REMOVE_VIDEOSYNOPSIS
{
	DWORD	            dwSize;			                // �ýṹ���С
	DWORD*	            pnTaskID;		                // TaskID���飬�û�����ռ�
	DWORD	            nTaskIDCount;	                // TaskID����
	DWORD	            nWaitTime;		                // �ȴ���ʱʱ�䣬��λms
}NET_IN_REMOVE_VIDEOSYNOPSIS;

// ��ƵŨ�����ص�������Ϣ
typedef struct tagNET_REAL_SYNOPSIS_OBJECT_INFO
{
	DWORD               dwSize;
	
	DWORD               dwTaskID;                       // ��ǰ�����Ӧ������ID
	DH_MSG_OBJECT       stuObjectInfo;                  // ���������Ϣ
}NET_REAL_SYNOPSIS_OBJECT_INFO;

typedef struct tagNET_REAL_SYNOPSIS_STATE_INFO
{
	DWORD               dwSize;
	
	DWORD               dwTaskID;                       // ����ID   
	int                 nObjectNum;                     // ĿǰŨ���������ѷ��ֵ���������
	int                 nTaolProgress;                  // ��ǰŨ��Դ���������̵ģ������ء�׼����Ũ��������ɽ���,0~100
	char                szState[DH_MAX_SYNOPSIS_STATE_NAME]; // ��Ӧ��ƵŨ��״̬,"Downloading"-��������","Synopsising"-����Ũ��",
                                                        // "DownloadFailed"-����ʧ��","DownloadSucceeded"-���سɹ�
	                                                  	// "SynopsisFailed"-Ũ��ʧ��","Succeeded"-Ũ���ɹ�
		                                                // "DownloadPause"-������ͣ,"SynopsisPause"-Ũ����ͣ
	int           nProgressOfCurrentState;              //  ��ǰŨ�������Ӧ����ɽ��ȣ�0~100
}NET_REAL_SYNOPSIS_STATE_INFO;

//��ƵŨ��������Ϣʵʱ�ص�����
typedef int (CALLBACK *fVideoSynopsisObjData)(LLONG lRealLoadHandle, NET_REAL_SYNOPSIS_OBJECT_INFO* pSynopsisObjectInfo, void* pBuf, int nBufLen, LDWORD dwUser, void* pReserved);

//��ƵŨ������״̬ʵʱ�ص�����
typedef int (CALLBACK *fVideoSynopsisState)(LLONG lRealLoadHandle, NET_REAL_SYNOPSIS_STATE_INFO* pSynopsisStateInfos, int nInfoCount, LDWORD dwUser, void* pReserved);

// CLIENT_RealLoadObjectData�ӿڲ�������
typedef struct tagNET_IN_REALLOAD_OBJECTDATA
{
	DWORD               dwSize;                         // �ṹ���С
	
	int                 nTaskIDNum;                     // ����ID����
	DWORD               *pTaskIDs;                      // ��������ID
	BOOL                bNeedPicFile;                   // �Ƿ����ض�Ӧ��ͼƬ�ļ� 
	int                 nWaitTime;                      // �ȴ�ʱ�䣬��λms
	fVideoSynopsisObjData cbVideoSynopsisObjData;       // ��ƵŨ��������Ϣʵʱ�ص�����ָ��
	LDWORD         dwUser;
}NET_IN_REALLOAD_OBJECTDATA;

typedef struct tagNET_OUT_REALLOAD_OBJECTDATA
{
	DWORD               dwSize;                         // �ṹ���С

	LLONG               lRealLoadHandle;                // �ӿڷ��صĶ��ľ������Ψһ��ʶĳ������
}NET_OUT_REALLOAD_OBJECTDATA;

// CLIENT_StopLoadObjectData�ӿڲ�������
typedef struct tagNET_IN_STOPLOAD_OBJECTDATA
{
	DWORD               dwSize;

	int                 nTackIDNum;                     // ����ID����
	DWORD               *pTaskIDs;                      // ��������ID  
}NET_IN_STOPLOAD_OBJECTDATA;

// CLIENT_RealLoadSynopsisState�ӿڲ�������
typedef struct tagNET_IN_REALLAOD_SYNOPSISSTATE
{
	DWORD               dwSize;                         // �ṹ���С
	
	int                 nTaskIDNum;                     // ����ID����
	DWORD               *pTaskIDs;                      // ��������ID
	int                 nWaitTime;                      // �ȴ�ʱ�䣬��λms
	fVideoSynopsisState cbVideoSynopsisState;           // ��ƵŨ��������Ϣʵʱ�ص�����ָ��
	LDWORD         dwUser;
}NET_IN_REALLAOD_SYNOPSISSTATE;

typedef struct tagNET_OUT_REALLOAD_SYNOPSISSTATE
{
	DWORD               dwSize;                         // �ṹ���С
	
	LLONG               lRealLoadHandle;                // �ӿڷ��ص����ؾ������Ψһ��ʶĳ������
}NET_OUT_REALLOAD_SYNOPSISSTATE;

// CLIENT_StopLoadSynopsisState�ӿڲ�������
typedef struct tagNET_IN_STOPLOAD_SYNOPSISSTATE
{
	DWORD               dwSize;
	
	int                 nTackIDNum;                     // ����ID����
	DWORD               *pTaskIDs;                      // ��������ID  
}NET_IN_STOPLOAD_SYNOPSISSTATE;

// Ũ����Ƶ��Ϣ�Ĳ�������
typedef enum tagEM_VIDEOSYNOPSIS_QUERY_TYPE
{
	EM_VIDEOSYNOPSIS_TASK,	                            // ������Ϣ
	EM_VIDEOSYNOPSIS_OBJ,	                            // �����Ӧ�Ŀ���
}EM_VIDEOSYNOPSIS_QUERY_TYPE;

// ��ѯŨ����Ƶ��������Ϣ������
typedef struct tagNET_QUERY_VSTASK_INFO
{
	DWORD	            dwSize;			                // �ýṹ���С
	DWORD	            dwTaskID;		                // ������ID��Ϊ0ʱ��ʾ��ѯ��������
}NET_QUERY_VSTASK_INFO;

// ��ѯŨ����Ƶ������������Ϣ������
typedef struct tagNET_QUERY_VSOBJECT_INFO
{
	DWORD			    dwSize;			                // �ýṹ���С
	DWORD*			    pdwTaskID;                		// �������������ID��Ϊ-1��ʾ��ѯ��������
	DWORD			    dwTaskIDCount;                	// ��Ч��������Ŀ
	DH_MSG_OBJECT	    stuObjInfo;	                	// ������Ϣ��objectIDΪ��0ʱ��ʾ��ѯ����������������
}NET_QUERY_VSOBJECT_INFO;

//--CLIENT_QueryVideoSynopsisInfo�ӿ������������
typedef struct tagNET_IN_QUERY_VIDEOSYNOPSIS
{
	DWORD	            dwSize;							// �ýṹ���С
	EM_VIDEOSYNOPSIS_QUERY_TYPE emQueryType;            // ��������
	DWORD	            dwCount;						// ��ѯ������
	DWORD	            dwBeginNumber;					// ��ѯ��ʼ���	
	void*	            pQueryInfo;						// ��ѯ������Ϣ���û�����ռ䣻
											            // ���emQueryType==EM_VIDEOSYNOPSIS_TASK����ӦNET_QUERY_VSTASK_INFO
											            // ���emQueryType==EM_VIDEOSYNOPSIS_OBJ����ӦNET_QUERY_VSOBJECT_INFO

	DWORD	            dwWaitTime;						// �ȴ���ʱʱ�䣬��λms
}NET_IN_QUERY_VIDEOSYNOPSIS;

// ��ѯ����ÿ��Ũ����Ƶ�������Ϣ
typedef struct tagNET_VSTASK_INFO
{
	DWORD		        dwSize;			                // �ýṹ���С
	DWORD				dwTaskID;		                // ����ID
	NET_MODULE_INFO		stuModuleInfo;                	// ģ����Ϣ
	NET_VIDEOSYNOPSISRULE_INFO	stuRuleInfo;           	// ����Ĺ�����Ϣ
	NET_GLOBAL_INFO		stuGlobalInfo;	                // ȫ�ֲ���
	NET_TIME			stuCreateTime;	                // ����Ĵ���ʱ��
	char				szCurrState[DH_MAX_SYNOPSIS_STATE_NAME];  // ��ǰ��ƵŨ��״̬,"Downloading"-��������","Synopsising"-����Ũ��",
																  // "DownloadFailed"-����ʧ��","DownloadSucceeded"-���سɹ�
																  // "SynopsisFailed"-Ũ��ʧ��","Succeeded"-Ũ���ɹ�
																  // "DownloadPause"-������ͣ,"SynopsisPause"-Ũ����ͣ
	char				szCreateUser[DH_MAX_NAME_LEN];	// ����������û�
	int					nProgressOfCurrentState;		// ��ǰŨ�������Ӧ����ɽ��ȣ�0~100
	char				szLocalFilePath[MAX_PATH];		// �����ļ�·����Զ����ƵԴ�ļ����غ��ڱ��ص�·��
	int					nObjectNum;						// ĿǰŨ���������ѷ��ֵ���������
	NET_FILEPATH_INFO	stuVideoSourceFilePath;			// Դ��Ƶ�ļ�·��
	NET_FILEPATH_INFO	stuSynopsisVideoFilePath;		// Ũ����Ƶ�ļ�·��
}NET_VSTASK_INFO;

// Ũ����Ƶ������ÿ��������Ϣ
typedef struct tagNET_VSOBJECT_INFO
{
	DWORD				dwSize;			                // �ýṹ���С
	DWORD				dwTaskID;		                // �����Ӧ����ID
	DH_MSG_OBJECT		stuObjInfo;		                // ������Ϣ
	NET_FILEPATH_INFO	stuFilePathInfo;                // �����Ӧ���ļ���Ϣ
	DWORD				dwFileLength;	                // �����ļ����ֽ�����С
}NET_VSOBJECT_INFO;

//--CLIENT_QueryVideoSynopsisInfo�ӿ������������
typedef struct tagNET_OUT_QUERY_VIDEOSYNOPSIS
{
	DWORD	            dwSize;			                // �ýṹ���С
	DWORD	            dwTotalCount;	                // ���ϴ˴β�ѯ�����Ľ��������
	DWORD            	dwFoundCount;	                // ���β�ѯ���ص�����
	void*	            pResult;                		// ���ص���Ϣ���û�����ռ�
					                		            // ���emQueryType==EM_VIDEOSYNOPSIS_TASK����ӦNET_VSTASK_INFO
							                            // ���emQueryType==EM_VIDEOSYNOPSIS_OBJ����ӦNET_VSOBJECT_INFO
	DWORD	            dwMaxCount;		                // �û�ϣ���Ľ���ĸ���
}NET_OUT_QUERY_VIDEOSYNOPSIS;

// CLIENT_FindSynopsisFile�ӿڲ������� 
// Ũ������ļ���ѯ����
enum NET_EM_QUERY_SYNOPSIS_FILE
{
	DH_FILE_QUERY_VIDEO,                                // ��ͨ¼���ļ���Ϣ����Ӧ��ѯ�ṹ��:NET_SYNOPSIS_QUERY_VIDEO_PARAM, ���ؽ���ṹ��:NET_SYNOPSISFILE_VIDEO_INFO
	DH_FILE_QUERY_SYNOPSISVIDEO,                        // Ũ����Ƶ��Ϣ, ��Ӧ��ѯ�ṹ��:NET_QUERY_SYNOPSISVIDEO_PARAM,���ؽ���ṹ��:NET_QUERY_SYNOPSISVIDEO_INFO
};

typedef struct __NET_SYNOPSIS_QUERY_VIDEO_PARAM
{
	DWORD               dwSize;
	DWORD				dwQueryMask;					// ��ѯ��������, ���մӵ͵���λ����һλ��ʱ��Ρ��ڶ�λ���ļ�·�� 
	NET_TIME			stuStartTime;					// ��ʼʱ��	
	NET_TIME			stuEndTime;						// ����ʱ��
	char				szFilePath[DH_MAX_SYNOPSIS_QUERY_FILE_COUNT][MAX_PATH];	// ����ѯ�ļ��ľ���·��
	DWORD				dwFileCount;					// ����ѯ�ļ��ĸ���
}NET_SYNOPSIS_QUERY_VIDEO_PARAM;

typedef struct  
{
	DWORD               dwSize;
	int                 nTaskId;                        // ����ID
	DWORD               dwOutPutTypeMask;               // ��ǰ�����������ͣ���1λ.��Ƶ���(һ�����);��2λŨ����Ƶ    
	char                szCurrentState[DH_MAX_SYNOPSIS_STATE_NAME]; // ��ǰŨ��״̬
}NET_VIDEOSYNOPSIS_TASK_INFO;

// DH_FILE_QUERY_VIDEO ���ص�¼���ļ���Ϣ
typedef struct
{
	DWORD               dwSize;
    unsigned int		nchannelId;						// ͨ����
    char				szFilePath[MAX_PATH];		    // �ļ�·��
    unsigned int		nFileLenth;					    // �ļ����ȣ��ֽ�Ϊ��λ
    NET_TIME			stuStarttime;				    // ��ʼʱ��
    NET_TIME			stuEndtime;				        // ����ʱ��
    unsigned int		nWorkDirSN;				        // ����Ŀ¼���	
	unsigned int        nCluster;                       // �غ�						
	BYTE                bHint;					        // �ļ���λ����
	BYTE                bDriveNo;                       // ���̺�
	BYTE                bReserved[18];                  // �����ֶ�
	
	int                 nTaskInfoNum;                   // ¼���ļ���Ӧ��Ũ���������
	NET_VIDEOSYNOPSIS_TASK_INFO stuTaskInfo[16];        // ����Ũ��������Ϣ
}NET_SYNOPSISFILE_VIDEO_INFO;

// DH_FILE_QUERY_SYNOPSISVIDEO Ũ����Ƶ�ļ���ѯ����
typedef struct __NET_QUERY_SYNOPSISVIDEO_PARAM
{
	DWORD               dwSize;
	int                 nTaskID;                        // ����ID
}NET_QUERY_SYNOPSISVIDEO_PARAM;

// DH_FILE_QUERY_SYNOPSISVIDEOŨ����Ƶ��ѯ���
typedef struct __NET_QUERY_SYNOPSISVIDEO_INFO
{
	DWORD               dwSize;
    char				szFilePath[MAX_PATH];        	// �ļ�·��
    unsigned int		nFileLenth;					    // �ļ�����
	int                 nDurationTime;                  // ����ʱ��,��λs
}NET_QUERY_SYNOPSISVIDEO_INFO;

// CLIENT_FindSynopsisFile �ӿڲ���
typedef struct tagNET_IN_FIND_SYNOPSISFILE
{
	DWORD               dwSize;                          
	NET_EM_QUERY_SYNOPSIS_FILE emQueryType;             // ��ѯ����
	void*               pQueryCondition;                // ��ѯ���� 
	int                 nWaitTime;                      // �ȴ���ʱʱ�䣬��λms
}NET_IN_FIND_SYNOPSISFILE;

typedef struct tagNET_OUT_FIND_SYNOPSISFILE
{
	DWORD               dwSize;
	LLONG               lFindHandle;                    // ��ѯ���         
}NET_OUT_FIND_SYNOPSISFILE;

// CLIENT_FindNextSynopsisFile �ӿڲ���
typedef struct tagNET_IN_FINDNEXT_SYNOPSISFILE
{
	DWORD               dwSize;
    int                 nFileCount;                     // ����ѯ���ļ�����
	NET_EM_QUERY_SYNOPSIS_FILE emQueryType;             // ��ѯ����
	void*               pSynopsisFileInfo;              // �ļ���Ϣ��Ż��� 
	int                 nMaxlen;                        // ��������С
	int                 nWaitTime;                      // �ȴ���ʱʱ�䣬��λms
}NET_IN_FINDNEXT_SYNOPSISFILE;

typedef struct tagNET_OUT_FINDNEXT_SYNOPSISFILE
{
	DWORD               dwSize;
	int                 nRetFileCount;                  // �ӿ�ʵ�ʷ��ص���Ϣ����������ֵ<nFileCount(�������)����Ӧʱ����ڵ��ļ���ѯ���
}NET_OUT_FINDNEXT_SYNOPSISFILE;

// ���ؽ��Ȼص�����ԭ��, nError��ʾ�����ع��̳��ֵĴ���1-���治�㣬2-�Է������ݵ�У�������3-���ص�ǰ�ļ�ʧ�ܣ�4-������Ӧ�����ļ�ʧ��
typedef void (CALLBACK *fSynopsisFileDownLoadPosCB)(LLONG lDownLoadHandle, DWORD dwFileID, DWORD dwFileTotalSize, DWORD dwDownLoadSize, int nError, LDWORD dwUser, void* pReserved);

// CLIENT_DownLoadSynosisFile �ӿڲ���
typedef struct tagNET_SYNOPSISFILE_INFO
{
	DWORD               dwSize;
	DWORD               dwFileID;                       // �ļ�ID, ���û��Լ�����
	int                 nFileSize;                      // ��ѯ�����ļ���С
	char                szSourceFilePath[MAX_PATH];     // ��ѯ�����ļ�·��   
	
	char                szSavedFileName[MAX_PATH];      // �ļ�����·��
}NET_SYNOPSIS_DOWNLOADFILE_INFO;

typedef struct tagNET_IN_DOWNLOAD_SYNOPSISFILE
{
	DWORD               dwSize;
    int                 nFileCount;                     // �������ļ���
	NET_SYNOPSIS_DOWNLOADFILE_INFO* pFileInfos;         // �������ļ���Ϣ
	fSynopsisFileDownLoadPosCB cbPosCallBack;           // ���Ȼص�����
	LDWORD              dwUserData;                     // �û�����
	int                 nWaitTime;                      // �ȴ���ʱʱ�䣬��λms
}NET_IN_DOWNLOAD_SYNOPSISFILE;

typedef struct tagNET_OUT_DOWNLOAD_SYNOPSISFILE
{
	DWORD               dwSize;
	LLONG               lDownLoadHandle;                // ���ؾ��
}NET_OUT_DOWNLOAD_SYNOPSISFILE;

// �ļ�(��)·����Ϣ
typedef struct	tagNET_SET_FILEPATH_INFO
{
	DWORD		        dwSize;
	char		        szFilePath[MAX_PATH];	        // �������ļ���·����Ҳ�������ļ�·����ĿǰŨ����Ƶ������ֻ֧��dav��ʽ���ļ�
}NET_SET_FILEPATH_INFO;

// CLIENT_SetFilePathInfo()�ӿ��������
typedef struct tagNET_IN_SET_FILEPATHINFO
{
	DWORD		        dwSize;
	DWORD		        dwCount;		                // ���ӵ��ļ�·����Ϣ����
	void*	        	pFilePathInfo;                	// ָ���ļ�·����ϢNET_SET_FILEPATH_INFO����
	DWORD		        dwWaitTime;		                // �ȴ���ʱʱ�䣬��λms
}NET_IN_SET_FILEPATHINFO;


// fAddFileStateCB ����
typedef struct tagNET_CB_ADDFILESTATE
{
	DWORD		        dwSize;
	const char*         szFileName;                     // �ļ�����
	const char*         szState;                        // �ļ�����״̬, "Successed",�ɹ�; "Failed"��ʧ�ܣ�
}NET_CB_ADDFILESTATE;

// ��¼�豸�ص�����ԭ��, ÿ��1����pBuf->dwSize == nBufLen
typedef void (CALLBACK *fAddFileStateCB) (LLONG lLoginID, LLONG lAttachHandle, NET_CB_ADDFILESTATE* pBuf,  int nBufLen, LDWORD dwUser);

// CLIENT_AttacAddFileState()�ӿ��������
typedef struct tagNET_IN_ADDFILE_STATE
{
	DWORD		        dwSize;
	fAddFileStateCB     cbAttachState;                 // ���������ļ�״̬�ص�
	DWORD               dwUser;                        // �û�����
}NET_IN_ADDFILE_STATE;
typedef struct tagNET_OUT_ADDFILE_STATE
{
	DWORD		        dwSize;
}NET_OUT_ADDFILE_STATE;

///////////////////////////////// ��¼�ϴ� /////////////////////////////////

// fAttachBurnStateCB ����
typedef struct tagNET_CB_BURNSTATE
{
	DWORD		        dwSize;
	const char*         szState;                        // ��Ϣ,"UploadFileStart"�����Կ�ʼ�����ϴ�;"BurnExtraFileStop"�������ϴ���ֹ
	const char*         szFileName;                     // ��ǰ��¼�����ļ���,����"UploadFileStart"��ʼ�����ϴ���Ϣ
}NET_CB_BURNSTATE;

// ��¼�豸�ص�����ԭ�Σ�lAttachHandle��CLIENT_AttachBurnState����ֵ, ÿ��1����pBuf->dwSize == nBufLen
typedef void (CALLBACK *fAttachBurnStateCB) (LLONG lLoginID, LLONG lAttachHandle, NET_CB_BURNSTATE* pBuf, int nBufLen, LDWORD dwUser);

// CLIENT_AttachBurnState()�������
typedef struct tagNET_IN_ATTACH_STATE
{
	DWORD		        dwSize;
	const char*         szDeviceName;                  // �������ƣ��硰/dev/sda��
	fAttachBurnStateCB  cbAttachState;                 // ��¼�����ص�
	DWORD               dwUser;                        // �û�����
}NET_IN_ATTACH_STATE;
typedef struct tagNET_OUT_ATTACH_STATE
{
	DWORD		        dwSize;
}NET_OUT_ATTACH_STATE;

// ��¼�豸�ص�����ԭ�Σ�lUploadHandle��CLIENT_StartUploadFileBurned����ֵ
typedef void (CALLBACK *fBurnFileCallBack) (LLONG lLoginID, LLONG lUploadHandle, int nTotalSize, int nSendSize, LDWORD dwUser);

// CLIENT_StartUploadFileBurned()�������
typedef struct tagNET_IN_FILEBURNED_START
{
	DWORD		        dwSize;
	const char*         szMode;                        // �ļ��ϴ���ʽ"append",׷��ģʽ,��ʱ��¼�ļ����̶�Ϊ" FILE.zip ",filename������
	const char*         szDeviceName;                  // �������ƣ��硰/dev/sda��
	const char*         szFilename;                    // �����ļ�����
	fBurnFileCallBack   cbBurnPos;                     // ��¼���Ȼص�
	LDWORD				dwUser;                        // �û�����
}NET_IN_FILEBURNED_START;
typedef struct tagNET_OUT_FILEBURNED_START
{
	DWORD		        dwSize;
	char                szState[DH_MAX_NAME_LEN];         // "start"��ϵͳ׼������,���Կ�ʼ�ϴ�; "busy"��ϵͳæ,�Ժ����ԡ�"error"��ϵͳδ�ڿ�¼��,���س���,����ʧ��
}NET_OUT_FILEBURNED_START;

///////////////////////////////// �߼��豸 /////////////////////////////////

typedef struct tagNET_CB_CAMERASTATE
{
	DWORD		        dwSize;
	int                 nChannel;             // ͨ��
	CONNECT_STATE       emConnectState;       // ����״̬
}NET_CB_CAMERASTATE;

// CLIENT_AttachCameraState()�ص�����ԭ��, ÿ��1����pBuf->dwSize == nBufLen
typedef void (CALLBACK *fCameraStateCallBack) (LLONG lLoginID, LLONG lAttachHandle, const NET_CB_CAMERASTATE *pBuf, int nBufLen, LDWORD dwUser);

// CLIENT_AttachCameraState()�������
typedef struct tagNET_IN_CAMERASTATE
{
	DWORD		        dwSize;
	int *               pChannels;             // �۲��ͨ����,����Ԫ���У���һ����-1����۲�����ͨ��
	int                 nChannels;             // pChannelsָ�볤��
    fCameraStateCallBack cbCamera;             // ״̬�ص�����
	DWORD				dwUser;                // �û�����
}NET_IN_CAMERASTATE;
typedef struct tagNET_OUT_CAMERASTATE
{
	DWORD		        dwSize;
}NET_OUT_CAMERASTATE;

/////////////////////////////////����汾/////////////////////////////////

// �����豸ץͼ�����ӿ�����Ϣ
typedef struct __NET_SNAP_COMMANDINFO 
{
	char				szCardInfo[16];			// ������Ϣ
	char				reserved[64];			// ����
} NET_SNAP_COMMANDINFO, LPNET_SNAP_COMMANDINFO;

typedef struct
{
	int					nChannelNum;			// ͨ����
	char				szUseType[32];			// ͨ����;
	DWORD				dwStreamSize;			// ������С(��λ��kb/s)
	char				reserved[32];			// ����
} DHDEV_USE_CHANNEL_STATE;

typedef struct 
{
	char				szUserName[32];			// �û���
	char				szUserGroup[32];		// �û���
	NET_TIME			time;					// ����ʱ��
	int					nOpenedChannelNum;		// ������ͨ������
	DHDEV_USE_CHANNEL_STATE	channelInfo[DH_MAX_CHANNUM];
	char                szIpAddress[DH_MAX_IPADDR_LEN];  // ip��ַ
	char				reserved[48];
} DHDEV_USER_NET_INFO;

// ��������״̬��Ϣ
typedef	struct 
{
	int					nUserCount;				// �û�����
	DHDEV_USER_NET_INFO	stuUserInfo[32];
	char				reserved[256];
}DHDEV_TOTAL_NET_STATE;

typedef struct
{
    char                szIpAddress[DH_MAX_IPADDR_LEN];  //ip��ַ
	char                szUserGroup[32];                 // �û���
	char                szUserName[32];                  // �û���
	char                reserved[64];
}DHDEV_USER_REJECT_INFO;

// �޳��û�
typedef struct
{ 
	int                       nUserCount;          // �û�����
	DHDEV_USER_REJECT_INFO    stuUserInfo[10];     
	char				      reserved[256];
}DHDEV_REJECT_USER;

typedef struct
{
	char                szIpAddress[DH_MAX_IPADDR_LEN];  //ip��ַ
	char                szUserGroup[32];                 // �û���
	char                szUserName[32];                  // �û���
	int                 nForbiddenTime;                  // ����ʱ��
	char                reserved[64];
}DHDEV_USER_SHIELD_INFO;

// �����û�
typedef struct
{ 
	int                       nUserCount;          // �û�����
	DHDEV_USER_SHIELD_INFO    stuUserInfo[10];     
	char				      reserved[256];
}DHDEV_SHIELD_USER;

// ��γ��
typedef struct
{//  ������ǰ��ά���ں�
	char                chPreLogi;        // ����ǰ�ñ�־��N��S��W��E���ֱ��ʾ�����ϡ���������
	char                chPreLati;        // γ��ǰ�ñ�־��N��S��W��E���ֱ��ʾ�����ϡ���������
	BYTE                reserved[6];      // �����ֽ�,����
	double              dbLongitude;      // ����
	double              dbLatitude;       // γ��
}DHDEV_LONGI_LATI;
// ������Ϣ�Ͷ���Ϣ
typedef struct
{
	char                szPhoneNum[DH_MAX_PHONE_NO_LEN];    // �绰����
	NET_TIME            stMsgTime;                          // ��Ϣ����ʱ��
	char                szMsgType[DH_MAX_MSGTYPE_LEN];      // ��Ϣ���ͣ�������Ϣ-Navigation�� ����Ϣ--SMS��
	char                szSmsContext[DH_MAX_MSG_LEN];       // ���͵���Ϣ����

	DHDEV_LONGI_LATI    stLogiLati;                         // ��ʼ��γ��
	unsigned int        uFlag;                              // 01����־����������ʵ��γ��
	char                szNavigationType[16];               // TNC,Ϊ�����µ�ͼ���ĵ�����ʽ��TXZ,Ϊ�����ߵ�ͼ���ĵ�����ʽ
	char                szAddress[32];                      // �ص���Ϣ
	char                szNavigationMode[32];               // ����ģʽ ��Recommend�Ƽ���Economical�����ͣ�Fastest ��죻Shortest ��̣�
	DHDEV_LONGI_LATI    stPassLogiLati[5];                  // ���ɵ�
	DHDEV_LONGI_LATI    stNoPassLogiLati[5];                // �����ɵ�
	BYTE				reserved[256];
}DHDEV_NAVIGATION_SMSS;

// ͼ��ˮӡ����
typedef struct __DHDEV_WATERMAKE_CFG 
{
	DWORD				dwSize;
	int					nEnable;				// ʹ��
	int					nStream;				// ����(1��n)0-��������
	int					nKey;					// ��������(1-���֣�2-ͼƬ)
	char				szLetterData[DH_MAX_WATERMAKE_LETTER];	//	����
	char				szData[DH_MAX_WATERMAKE_DATA]; // ͼƬ����
	BYTE				bReserved[512];			// ����
} DHDEV_WATERMAKE_CFG;

// �洢λ�����ýṹ�壬ÿͨ����������,ÿͨ������ѡ����ִ洢����, Ŀǰ��������, ���ƶ�, Զ�̴洢.
typedef struct 
{
	DWORD				dwSize;
	DWORD				dwLocalMask;			// ���ش洢���룻��λ��ʾ��
												// ��һλ��ϵͳԤ¼���ڶ�λ����ʱ¼�񣬵���λ������¼��
												// ����λ������¼�񣬵���λ������¼�񣬵���λ���ֶ�¼��
	DWORD				dwMobileMask;			// ���ƶ��洢���� �洢�����籾�ش洢����
	int					RemoteType;				// Զ�̴洢���� 0: Ftp  1: Smb 
	DWORD				dwRemoteMask;			// Զ�̴洢���� �洢�����籾�ش洢����
	DWORD				dwRemoteSecondSelLocal;	// Զ���쳣ʱ���ش洢����
	DWORD				dwRemoteSecondSelMobile;// Զ���쳣ʱ���ƶ��洢����
	char				SubRemotePath[MAX_PATH_STOR]; // Զ��Ŀ¼, ���г���Ϊ240
	DWORD				dwFunctionMask;			// ��������λ����λ��ʾ��bit0 = 1:����ץͼ�¼������洢λ�ù���
	DWORD				dwAutoSyncMask;			// �Ƿ�ͬ������;Զ�̴洢������ϻָ����Զ������ش洢������ͬ����Զ�̴洢��
	BYTE				bAutoSyncRange;			// ������ָ���ʱ�̿�ʼ����Ҫ��ǰͬ��������ʱ�䷶Χ��СʱΪ��λ��0:ͬ����������  1:1Сʱ�ڵ����� n:nСʱ�ڵ�����
	char				reserved[119];
} DH_STORAGE_STATION_CFG;

#define MAX_ALARM_DECODER_NUM 16
typedef struct  
{
	DWORD				dwAlarmDecoder;			// �������֧��8����������ڣ���8λ���Ժ���չ
	BYTE				bDecoderIndex;			// ��ʾ�ڼ�������������
	BYTE				bReserved[3];
} ALARM_DECODER;

// ��������������
typedef struct
{
	int					nAlarmDecoderNum;
	ALARM_DECODER		stuAlarmDecoder[MAX_ALARM_DECODER_NUM];
	BYTE				bReserved[32];
} ALARM_DECODER_ALARM;

//DSP����
typedef struct  
{
	BOOL				bError;			//0,DSP���� 1,DSP�쳣
	DWORD				dwErrorMask;	//��λ��ʾ����0��ʾ�д˴���0��ʾû�С�(Ŀǰÿ�α���ֻ��һλ��Ч)
										//bit		DSP����
										//1			DSP����ʧ�� 
										//2			DSP����
										//3			��ʽ���� 
										//4			�ֱ��ʲ�֧��
										//5			���ݸ�ʽ��֧��
										//6			�Ҳ���I֡
	DWORD               dwDecChnnelMask;//��λ��ʾ�������Ľ���ͨ���ţ�dwErrorMaskΪDSP������ʽ���ԣ��ֱ��ʲ�֧�֣����ݸ�ʽ��֧��ʱ������Ч
	DWORD               dwDecChnnelMask1;//��λ��ʾ,33-64ͨ���ı����Ľ���ͨ����, dwErrorMaskΪDSP������ʽ���ԣ��ֱ��ʲ�֧�֣����ݸ�ʽ��֧��ʱ������Ч
	BYTE				bReserved[24];
}DSP_ALARM;

// ���˱�����������
typedef struct  
{
	int		nFDDINum;
	BYTE	bAlarm[256];
} ALARM_FDDI_ALARM;

#define ALARM_PTZ_LOCATION_INFO DH_PTZ_LOCATION_INFO

//��̨��λ��Ϣ����
typedef struct
{
	int     nChannelID;             // ͨ���� 
	int     nPTZPan;                // ��̨ˮƽ����
	int     nPTZTilt;               // ��̨��ֱ����
	int     nPTZZoom;               // ��̨�䱶
	BYTE    bState;                 // ��̨״̬��0-δ֪��1-�˶���2-����
	BYTE    bAction;                // ��̨������0-Ԥ�õ㣬1-��ɨ��2-Ѳ����3-Ѳ����4-ˮƽ��ת
	BYTE    bReserved[2];           // ����
	int     reserved[255];          // �����ֶ�
}DH_PTZ_LOCATION_INFO;

// ����Ƶ��ⱨ������
typedef struct
{
	BOOL				bEnable;				// ��������ʹ��
	int					Volume_min;				// ��������Сֵ
	int					Volume_max;				// ���������ֵ
	char				reserved[128];	
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	
	DH_MSG_HANDLE		struHandle;				// ������ʽ
} DH_AUDIO_DETECT_INFO;

typedef struct  
{
	DWORD				dwSize;
	int					AlarmNum;
	DH_AUDIO_DETECT_INFO AudioDetectAlarm[DH_MAX_AUDIO_IN_NUM];
	char				reserved[256];
} DH_AUDIO_DETECT_CFG;

typedef struct
{
	BOOL				bTourEnable;			// ��Ѳʹ��
	int					nTourPeriod;			// ��Ѳ�������λ��, 5-300 
	DWORD				dwChannelMask;			// ��Ѳ��ͨ����������ʽ��ʾ
	char				reserved[64];
}DH_VIDEOGROUP_CFG;

// ����������Ʋ�������
typedef struct
{
	DWORD				dwSize;
	int					nMatrixNum;				// �������(ע���������޸�)
	DH_VIDEOGROUP_CFG	struVideoGroup[DH_MATRIX_MAXOUT];
	char				reserved[32];
} DHDEV_VIDEO_MATRIX_CFG;   

// WEB·������
typedef struct 
{
	DWORD				dwSize;
	BOOL				bSnapEnable;			// �Ƿ�ץͼ
	int					iSnapInterval;			// ץͼ����
	char				szHostIp[DH_MAX_IPADDR_LEN]; // HTTP����IP
	WORD				wHostPort;
	int					iMsgInterval;			// ״̬��Ϣ���ͼ��
	char				szUrlState[DH_MAX_URL_LEN];	// ״̬��Ϣ�ϴ�URL
	char				szUrlImage[DH_MAX_URL_LEN];	// ͼƬ�ϴ�Url
	char				szDevId[DH_MAX_DEV_ID_LEN];	// ������web���
	BYTE				byReserved[2];
} DHDEV_URL_CFG;

// OEM��ѯ
typedef struct  
{
	char				szVendor[DH_MAX_STRING_LEN];
	char				szType[DH_MAX_STRING_LEN];
	char				reserved[128];
} DHDEV_OEM_INFO;


//��ƵOSD��������
typedef struct 
{ 
	DWORD	rgbaFrontground;		// �����ǰ�������ֽڱ�ʾ���ֱ�Ϊ�졢�̡�����͸����
	DWORD	rgbaBackground;			// ����ı��������ֽڱ�ʾ���ֱ�Ϊ�졢�̡�����͸����	
	RECT	rcRelativePos;			// λ��,����߾��������ı���*8191	
	BOOL	bPreviewBlend;			// Ԥ������ʹ��	
	BOOL	bEncodeBlend;			// �������ʹ��
	BYTE    bReserved[4];           // ����
} DH_DVR_VIDEO_WIDGET;

typedef struct 
{
	DH_DVR_VIDEO_WIDGET	StOSD_POS; 								// OSD���ӵ�λ�úͱ���ɫ
	char 				SzOSD_Name[DH_VIDEO_OSD_NAME_NUM]; 		// OSD���ӵ�����
}DH_DVR_VIDEOITEM;
 
// ÿ��ͨ����OSD��Ϣ
typedef struct 
{
	DWORD 				dwSize;
	DH_DVR_VIDEOITEM 	StOSDTitleOpt [DH_VIDEO_CUSTOM_OSD_NUM]; 	// ÿ��ͨ����OSD��Ϣ
	BYTE    			bReserved[16];                  		  // ����
} DH_DVR_VIDEOOSD_CFG;

// ����CDMA/GPRS������Ϣ
// ʱ��νṹ															    
typedef struct 
{
	BYTE				bEnable;				  // ʱ���ʹ�ܣ�1��ʾ��ʱ�����Ч��0��ʾ��ʱ�����Ч��
	BYTE				bBeginHour;
	BYTE				bBeginMin;
	BYTE				bBeginSec;
	BYTE				bEndHour;
	BYTE				bEndMin;
	BYTE				bEndSec;
	BYTE    			bReserved;                //����
} DH_3G_TIMESECT, *LPDH_3G_TIMESECT;

typedef struct 
{
	DWORD 				dwSize;
	BOOL				bEnable;					// ����ģ��ʹ�ܱ�־
	DWORD               dwTypeMask;                 // �豸֧��������������;��λ��ʾ,��һλ;�Զ�ѡ��;
													// �ڶ�λ��TD-SCDMA���磻����λ��WCDMA����;
													// ����λ��CDMA 1.x����;����λ��CDMA2000����;����λ��GPRS����;
													// ����λ��EVDO����;�ڰ�λ��WIFI
	DWORD               dwNetType;                  // ��ǰ�������������ͣ�ΪEM_GPRSCDMA_NETWORK_TYPEֵ
	char				szAPN[128];					// ���������
	char				szDialNum[128];				// ���ź���
	char				szUserName[128];			// �����û���
	char				szPWD[128];					// ��������
	
	/* �������豸��ֻ������ */
	BOOL				iAccessStat;				// ��������ע��״̬
    char				szDevIP[16];				// ǰ���豸����IP���ַ���, ����'\0'��������16byte  
	char				szSubNetMask [16];			// ǰ���豸�����������룬�ַ���, ����'\0'��������16byte 
	char				szGateWay[16];				// ǰ���豸�������أ��ַ���, ����'\0'��������16byte 
	/* �������豸��ֻ������ */
	int                 iKeepLive;					// ����ʱ��
	DH_3G_TIMESECT		stSect[DH_N_WEEKS][DH_N_TSECT];// 3G����ʱ��Σ���Чʱ���֮�ڣ��������ţ���Чʱ���֮�⣬�رղ��š�
	BYTE                byActivate;                 // �Ƿ���Ҫ����������ż���

	BYTE                bySimStat;                   // SIM(UIM)״̬:����1,������0  (ֻ������) ռ��Reserved��1���ֽ�
	char                szIdentify[128];             // ��Ȩ��ʽ
	bool                bPPPEnable;                  // PPP����,0-�Ͽ�ppp���ӣ�1-ppp����
	BYTE                bPPPState;                   // PPP����״̬(ֻ��)�����庬���EM_MOBILE_PPP_STATE
	BYTE                bNetCardState;               // ��������״̬(ֻ��)�����庬���EM_3GMOBILE_STATE
	char				szPhyCardNo[32];			 // ��������
	char				Reserved[4];				 // �����ֽڣ�������չ
	BYTE				byPinShow;					// PIN���Ƿ���ʾ(ֻ��), 0-��֧��, 1-��ʾ, 2-����ʾ
	BYTE				byPinEnable;				// PIN������ʹ��(ֻ��), 0-��ʹ��, 1-ʹ��
	BYTE				byPinCount;					// PIN��ʣ�����ô���(ֻ��), 0~3
	//-------------------------------�����ֶ�����dwSize�����Ч------------------------------------
	char				szPinNo[16];				// PIN��ֵ, ��ĸ�����ֵ��������
} DHDEV_CDMAGPRS_CFG;

// ¼������������
typedef struct  
{
	DWORD 				dwSize;
	int					nType;						// 0:��ʱ�䣬1������С
	int					nValue;						// nType = 0ʱ:��λ���ӣ�nType = 1ʱ:��λKB
	char				Reserved[128];				// �����ֽڣ�������չ
} DHDEV_RECORD_PACKET_CFG;

// (����)����ע���������Ϣ
typedef struct __DEV_AUTOREGISTER_INFO 
{
	LONG			lConnectionID;						// ����ID
	char			szServerIp[DH_MAX_IPADDR_LEN];		// ����ע���������IP
	int				nPort;								// ����ע��������˿�0- 65535
	int             nState;                             // ��������״̬��0��ע��ʧ�ܣ�1-ע��ɹ�; 2-����ʧ��
	char			reserved[16];
} DEV_AUTOREGISTER_INFO;

typedef struct __DEV_SERVER_AUTOREGISTER 
{
	DWORD					dwSize;
	int						nRegisterSeverCount;											// ����ע�����������
	DEV_AUTOREGISTER_INFO	stuDevRegisterSeverInfo[DH_CONTROL_AUTO_REGISTER_NUM];			// ������ע���������Ϣ
	char					reserved[256];
} DEV_SERVER_AUTOREGISTER, *LPDEV_SERVER_AUTOREGISTER;

// ������¼�����ϴ�
typedef struct
{
	DWORD				dwSize;		
	char				szSourFile[MAX_PATH_STOR];	// Դ�ļ�·��
	int					nFileSize;					// Դ�ļ���С�����С�ڵ���0��sdk���м����ļ���С.
	char				szBurnFile[MAX_PATH_STOR];	// ��¼����ļ���
	BYTE				bReserved[64];
} DHDEV_BURNFILE_TRANS_CFG;

// �����ļ��ϴ�
typedef struct
{
	char                 szFile[MAX_PATH_STOR];      // �����ļ�·��
	int                  nFileSize;                  // �����ļ���С 
	BYTE                 byChannelId;                // ͨ����
	BYTE                 byManufactryType;           // �������ͣ����EM_IPC_TYPE

	BYTE                 byReserved[126];            // ����      
}DHDEV_UPGRADE_FILE_INFO;

// �ڰ������ϴ�
typedef struct  
{
	char                 szFile[MAX_PATH_STOR];     // �ڰ������ļ�·��
	int                  nFileSize;                 // �����ļ���С
	BYTE                 byFileType;                // ��ǰ�ļ����ͣ�0-��������1-������ 
	BYTE                 byAction;                  // ������0-���ǣ�1-׷��

	BYTE                 byReserved[126];           // ����
}DHDEV_BLACKWHITE_LIST_INFO;

// �ڰ���������
typedef struct
{
	char                 szFile[MAX_PATH_STOR];     // �ڰ������ļ�����·��
	BYTE                 byFileType;                // ��ǰ�ļ����ͣ�0-��������1-������
	BYTE                 byReserved[127];           // ����
}DHDEV_LOAD_BLACKWHITE_LIST_INFO;

// ֣������ķEC_U��Ƶ���ݵ���ʹ������
typedef struct 
{
	BOOL				bEnable;					// ʹ��
	int					nPort;						// �˿�
	BYTE				bReserved[64];
} DHDEV_OSD_ENABLE_CFG;

// �����������:��������ʹ������
typedef struct	
{
	BOOL				bAutoBootEnable;				//�Զ�����ʹ��
	DWORD				dwAutoBootTime;					//ÿ���Զ�����ʱ���, ��λ��,��0����.[0,82800]
	BOOL				bAutoShutDownEnable;			//�Զ��ػ�ʹ��
	DWORD				dwAutoShutDownTime;				//ÿ���Զ��ػ�ʱ���, ��λ��,��0����.[0,82800]
	DWORD				dwShutDownDelayTime;			//��ʱ�ػ�ʱ��,��λ��.
	BYTE				bEventNoDisk;					//1,(Ignore:����); 2,(Reboot:����ϵͳ)
	BYTE				bWifiEnable;					//�Ƿ�֧�ֳ�������ģ��.
	BYTE				bUpperSpeedEnable;				//�Ƿ�ʹ�ó����ж�
	BYTE				bLowerSpeedEnable;				//�Ƿ�ʹ�õ����ж�
	DWORD				dwUpperSpeedValue;				//����ֵ������(1,1000).����/Сʱ
	DWORD               dwLowerSpeedValue;              //����ֵ������(1,1000).����/Сʱ
    DWORD               dwUpperSpeedDelayTime;          //���ó��ٳ���ֵ
	DWORD               dwLowerSpeedDelayTime;          //���õ��ٳ���ֵ
	DWORD               dwAlarmMaskEnable;              //��ѯ/���õ��ӱ�����Ϣʹ��,0:�ر�,1:��, ÿһλ�ӵ͵��߱�ʾ�����ⲿ����ͨ��0-Nʹ��
	BOOL                bSpeedOverAlarmRecordEnable;    // ���ٱ�������¼��ʹ��
	BOOL                bSpeedLowAlarmRecordEnable;     // ���ٱ�������¼��ʹ�� 
	BYTE				bReserved[480];					//reserved byte.
} DHDEV_ABOUT_VEHICLE_CFG;

// atm:��ѯ�������������Ϣ
typedef struct  
{
	DWORD				dwDataSource;					//��λ, λ0:Net(����), λ1:Com(����), λ2:Com422(����422)
	char				szProtocol[32][33];				//Э������,��󳤶�32(����һ��������).
	BYTE				bReserved[256];
} DHDEV_ATM_OVERLAY_GENERAL;
 
// atm:���õ�������
typedef struct 
{
	DWORD				dwDataSource;					// 1:Net(����), 2:Com(����), 3:Com422(����422)
	char				szProtocol[33];					// Э�����֣���DHDEV_ATM_OVERLAY_GENERAL����
	BYTE				bReserved_1[3];
	DWORD				dwChannelMask;					// ���ӵ�ͨ���ţ������ʾ��
	BYTE				bMode;							// 1:Preview(Ԥ������), 2:Encode(�������), 3:Preview&Encode(Ԥ���ͱ������)
	BYTE				bLocation;						// 1:LeftTop(����), 2:LeftBottom(����), 3:RightTop(����), 4:RightBottom(����)
	BYTE                bReserved_3[2];           
	int                 nLatchTime;                     // ������ʾ�ӳ�ʱ��,����¼����ʱ�ر�ʱ��,0~65535s
	BYTE                bReserved_4[3];
	BYTE                bRecordSrcKeyNum;               // �ؼ��ָ���  
	int                 nRecordSrcKey[32];              // ����Ƶͨ����Ӧ����Դ�ؼ���(��ͬͨ�����Զ�Ӧ��ͬ������Դ)  
	BYTE				bReserved_2[120];
} DHDEV_ATM_OVERLAY_CONFIG;


// atm:���õ�������
typedef struct 
{
	DWORD               dwSize;                         // �ṹ���С
	DWORD				dwDataSource;					// 1:Net(����), 2:Com(����), 3:Com422(����422)
	char				szProtocol[33];					// Э�����֣�
	BYTE				bReserved_1[3];
	DWORD				dwChannelMask[8];				// ���ӵ�ͨ���ţ������ʾ, dwChannelMask[0]��ʾ0-31ͨ�����������ơ�
	BYTE				bMode;							// 1:Preview(Ԥ������), 2:Encode(�������), 3:Preview&Encode(Ԥ���ͱ������)
	BYTE				bLocation;						// 1:LeftTop(����), 2:LeftBottom(����), 3:RightTop(����), 4:RightBottom(����)
	BYTE                bReserved_3[2];           
	int                 nLatchTime;                     // ������ʾ�ӳ�ʱ��,����¼����ʱ�ر�ʱ��,0~65535s
	BYTE                bReserved_4[3];
	BYTE                bRecordSrcKeyNum;               // �ؼ��ָ���  
	int                 nRecordSrcKey[256];             // ����Ƶͨ����Ӧ����Դ�ؼ���(��ͬͨ�����Զ�Ӧ��ͬ������Դ)  
} DHDEV_ATM_OVERLAY_CONFIG_EX;

#define DH_MAX_BACKUPDEV_NUM			16
#define DH_MAX_BACKUP_NAME				32

// �����豸�б�
typedef struct 
{
	int					nBackupDevNum;								// ʵ�ʵı����豸����
	char				szBackupDevNames[DH_MAX_BACKUPDEV_NUM][DH_MAX_BACKUP_NAME]; // �����豸������
} DHDEV_BACKUP_LIST, *LPDHDEV_BACKUP_LIST;

// �����豸��������
typedef enum __BACKUP_TYPE
{
	BT_DHFS = 0,							// ���ļ�ϵͳ
	BT_DISK,								// �ƶ�Ӳ��
	BT_CDRW									// ���̿�¼
} DHDEV_BACKUP_TYPE;	

// �����豸�ӿ�����
typedef enum __BACKUP_BUS
{
	BB_USB = 0,								// usb�ӿ�
	BB_1394,								// 1394�ӿ�
	BB_IDE,									// ide�ӿ�
	BB_ESATA,								// esata�ӿ�
} DHDEV_BACKUP_BUS;	

typedef struct 
{
	char				szName[32];						// �豸�� 
	BYTE				byType;							// �����豸�Ľ������� ö��ֵ��BACKUP_TYPE
	BYTE				byBus;							// �����豸�Ľӿ����� ö��ֵ��BACKUP_BUS
	UINT				nCapability;					// ������, ��kBytesΪ��λ
	UINT				nRemain;						// ʣ������,��kBytesΪ��λ
	char				szDirectory[128];				// Զ�̱��ݵ�Ŀ¼
} DHDEV_BACKUP_INFO, *LPDHDEV_BACKUP_INFO;

typedef struct 
{
	char				szName[32];						// �豸�� 
	UINT				nCapability;					// ������, ��kBytesΪ��λ
	UINT				nRemain;						// ��ǰ����ʣ������,��kBytesΪ��λ
} DHDEV_BACKUP_FEEDBACK, *LPDHDEV_BACKUP_FEEDBACK;

#define  DH_MAX_BACKUPRECORD_NUM 1024

typedef struct  
{
	char				szDeviceName[DH_MAX_BACKUP_NAME];			//�����豸����
	int					nRecordNum;									//���ݼ�¼����
	NET_RECORDFILE_INFO	stuRecordInfo[DH_MAX_BACKUPRECORD_NUM];		//���ݼ�¼��Ϣ
} BACKUP_RECORD, *LPBACKUP_RECORD;

// ��ͨ������Ƶ����
typedef struct
{
	int                 iChannelID;      // ͨ����
	DH_RealPlayType     realplayType;    // ��Ƶ����
	char                reserve[32];
}DHDEV_IN_MULTIPLAY_PARAM;

// ��ͨ������Ƶ���
typedef struct
{
	int                 iChannelID;      // ͨ����
	LLONG               lRealHandle;     // ʵʱ���Ӿ��
	char                reserve[32];
}DHDEV_OUT_MULTIPLAY_PARAM;


/////////////////////////////////ƽ̨����/////////////////////////////////

// ƽ̨�������� �� U��ͨ
typedef struct
{
    BOOL				bChnEn;
    char				szChnId[DH_INTERVIDEO_UCOM_CHANID];
} DH_INTERVIDEO_UCOM_CHN_CFG;

typedef struct
{
	DWORD				dwSize;
	BOOL				bFuncEnable;			// ���빦��ʹ��
	BOOL				bAliveEnable;			// ����ʹ��
	DWORD				dwAlivePeriod;			// �������ڣ���λ�룬0-3600
	char				szServerIp[DH_MAX_IPADDR_LEN]; // CMS��IP
	WORD				wServerPort;			// CMS��Port
    char				szRegPwd[DH_INTERVIDEO_UCOM_REGPSW]; // ע������
	char				szDeviceId[DH_INTERVIDEO_UCOM_DEVID];// �豸id
	char				szUserName[DH_INTERVIDEO_UCOM_USERNAME];
	char				szPassWord[DH_INTERVIDEO_UCOM_USERPSW];
    DH_INTERVIDEO_UCOM_CHN_CFG  struChnInfo[DH_MAX_CHANNUM]; // ͨ��id,en
} DHDEV_INTERVIDEO_UCOM_CFG;

// ƽ̨�������� �� ��������
typedef struct
{
	DWORD				dwSize;
    unsigned short		usCompanyID[2];			// ��˾ID����ֵ����ͬ�ĵ���������˾������4�ֽڶ��룬Ŀǰֻ�������һ��
    char				szDeviceNO[32];			// ǰ���豸���кţ��ַ���������'\0'��������32byte
    char				szVSName[32];			// ǰ���豸���ƣ��ַ���������'\0'��������16byte
    char				szVapPath[32];			// VAP·��
    unsigned short		usTcpPort;				// TCP�˿ڣ���ֵ����ֵ 1~65535 
    unsigned short		usUdpPort;				// UDP�˿ڣ���ֵ����ֵ 1~65535
    bool				bCsEnable[4];			// ���ķ�����ʹ�ܱ�־����ֵ��trueʹ�ܣ�false��ʹ�ܣ�����4�ֽڶ��룬Ŀǰֻ�������һ��
    char				szCsIP[16];				// ���ķ�����IP��ַ���ַ���������'\0'��������16byte
    unsigned short		usCsPort[2];			// ���ķ������˿ڣ���ֵ����ֵ 1~65535������4�ֽڶ��룬Ŀǰֻ�������һ��
    bool				bHsEnable[4];			// ����������ʹ�ܱ�־����ֵ��trueʹ�ܣ�false��ʹ�ܣ�����4�ֽڶ��룬Ŀǰֻ�������һ��
    char				szHsIP[16];				// ����������IP��ַ���ַ���������'\0'��������16byte
    unsigned short		usHsPort[2];			// �����������˿ڣ���ֵ����ֵ 1~65535������4�ֽڶ��룬Ŀǰֻ�������һ��
    int					iHsIntervalTime;		// ����������������ڣ���ֵ(��λ:��)
    bool				bRsEnable[4];			// ע�������ʹ�ܱ�־����ֵ��trueʹ�ܣ�false��ʹ�ܣ�����4�ֽڶ��룬Ŀǰֻ�������һ��
    char				szRsIP[16];				// ע�������IP��ַ���ַ���������'\0'��������16byte
    unsigned short		usRsPort[2];			// ע��������˿ڣ���ֵ����ֵ 1~65535������4�ֽڶ��룬Ŀǰֻ�������һ��
    int					iRsAgedTime;			// ע���������Чʱ�䣬��ֵ(��λ:Сʱ)
    char				szAuthorizeServerIp[16];// ��Ȩ������IP
    unsigned short		usAuthorizePort[2];		// ��Ȩ�������˿ڣ�����4�ֽڶ��룬Ŀǰֻ�������һ��
    char				szAuthorizeUsername[32];// ��Ȩ�������ʺ�
    char				szAuthorizePassword[36];// ��Ȩ����������
    
    char				szIpACS[16];			// ACS(�Զ�ע�������) IP
    unsigned short		usPortACS[2];			// ACS Port������4�ֽڶ��룬Ŀǰֻ�������һ��
    char				szUsernameACS[32];		// ACS�û���
    char				szPasswordACS[36];		// ACS����
    bool				bVideoMonitorEnabled[4];// DVS�Ƿ����ϱ�ǰ����Ƶ�źż����Ϣ����ֵ��trueʹ�ܣ�false��ʹ��
    int					iVideoMonitorInterval;	// �ϱ�����(����)
    
    char				szCoordinateGPS[64];	// GPS����
    char				szPosition[32];			// �豸λ��
    char				szConnPass[36];			// �豸������
} DHDEV_INTERVIDEO_BELL_CFG;

// ƽ̨�������� �� ������ά
typedef struct  
{
	DWORD				dwSize;
	unsigned short		nSevPort;				// �������˿ڣ���ֵ����ֵ1~65535
    char				szSevIp[DH_INTERVIDEO_NSS_IP]; // ������IP��ַ���ַ���������'\0'��������32byte
    char				szDevSerial[DH_INTERVIDEO_NSS_SERIAL]; // ǰ���豸���кţ��ַ���������'\0'��������32byte
    char				szUserName[DH_INTERVIDEO_NSS_USER];
    char				szPwd[DH_INTERVIDEO_NSS_PWD];
} DHDEV_INTERVIDEO_NSS_CFG;

// ƽ̨�������� �� �������
typedef struct  
{
	char               szDevSerial[DH_INTERVIDEO_AMP_DEVICESERIAL];                  //ǰ���豸���к�,�������������к�,�ò���ֻ��
	char               szDevName[DH_INTERVIDEO_AMP_DEVICENAME];                      //ǰ���豸����,������������,�ò���ֻ��
	char               szRegUserName[DH_INTERVIDEO_AMP_USER];                        //ע��������û���
	char               szRegPwd[DH_INTERVIDEO_AMP_PWD];                              //ע�����������
    BYTE			   bReserved[128];
} DHDEV_INTERVIDEO_AMP_CFG;  
////////////////////////////////HDVRר��//////////////////////////////////
// ����������չ�ṹ��
typedef struct 
{
	/* ��Ϣ������ʽ������ͬʱ���ִ�����ʽ������
	 * 0x00000001 - �����ϴ�
	 * 0x00000002 - ����¼��
	 * 0x00000004 - ��̨����
	 * 0x00000008 - �����ʼ�
	 * 0x00000010 - ������Ѳ
	 * 0x00000020 - ������ʾ
	 * 0x00000040 - �������
	 * 0x00000080 - Ftp�ϴ�
	 * 0x00000100 - ����
	 * 0x00000200 - ������ʾ
	 * 0x00000400 - ץͼ
	*/

	/* ��ǰ������֧�ֵĴ�����ʽ����λ�����ʾ */
	DWORD				dwActionMask;

	/* ������������λ�����ʾ�����嶯������Ҫ�Ĳ����ڸ��Ե����������� */
	DWORD				dwActionFlag;
	
	/* �������������ͨ�������������������Ϊ1��ʾ��������� */ 
	BYTE				byRelAlarmOut[DH_MAX_ALARMOUT_NUM_EX];
	DWORD				dwDuration;				/* ��������ʱ�� */

	/* ����¼�� */
	BYTE				byRecordChannel[DH_MAX_VIDEO_IN_NUM_EX]; /* ����������¼��ͨ����Ϊ1��ʾ������ͨ�� */
	DWORD				dwRecLatch;				/* ¼�����ʱ�� */

	/* ץͼͨ�� */
	BYTE				bySnap[DH_MAX_VIDEO_IN_NUM_EX];
	/* ��Ѳͨ�� */
	BYTE				byTour[DH_MAX_VIDEO_IN_NUM_EX];/* ��Ѳͨ�� 0-31·*/

	/* ��̨���� */
	DH_PTZ_LINK			struPtzLink[DH_MAX_VIDEO_IN_NUM_EX];
	DWORD				dwEventLatch;			/* ������ʼ��ʱʱ�䣬sΪ��λ����Χ��0~15��Ĭ��ֵ��0 */
	/* �����������������ͨ�������������������Ϊ1��ʾ��������� */ 
	BYTE				byRelWIAlarmOut[DH_MAX_ALARMOUT_NUM_EX];
	BYTE				bMessageToNet;
	BYTE                bMMSEn;                /*���ű���ʹ��*/
	BYTE                bySnapshotTimes;       /*���ŷ���ץͼ���� */
	BYTE				bMatrixEn;				/*!< ����ʹ�� */
	DWORD				dwMatrix;				/*!< �������� */			
	BYTE				bLog;					/*!< ��־ʹ�ܣ�Ŀǰֻ����WTN��̬�����ʹ�� */
	BYTE				bSnapshotPeriod;		/*!<ץͼ֡�����ÿ������֡ץһ��ͼƬ��һ��ʱ����ץ�ĵ���������ץͼ֡���йء�0��ʾ����֡������ץ�ġ�*/
	BYTE				byTour2[DH_MAX_VIDEO_IN_NUM_EX];/* ��Ѳͨ�� 32-63·*/
	BYTE                byEmailType;             /*<0��ͼƬ������1��¼�񸽼�>*/
	BYTE                byEmailMaxLength;        /*<����¼��ʱ����󳤶ȣ���λMB>*/
	BYTE                byEmailMaxTime;          /*<������¼��ʱ���ʱ�䳤�ȣ���λ��>*/
	BYTE				byReserved[475];   
} DH_MSG_HANDLE_EX;

// �ⲿ������չ
typedef struct
{
	BYTE				byAlarmType;			// ���������ͣ�0�����գ�1������
	BYTE				byAlarmEn;				// ����ʹ��
	BYTE				byReserved[2];						
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE_EX	struHandle;				// ������ʽ
} DH_ALARMIN_CFG_EX, *LPDHDEV_ALARMIN_CFG_EX; 

// ��̬��ⱨ��
typedef struct 
{
	BYTE				byMotionEn;				// ��̬��ⱨ��ʹ��
	BYTE				byReserved;
	WORD				wSenseLevel;			// ������
	WORD				wMotionRow;				// ��̬������������
	WORD				wMotionCol;				// ��̬������������
	BYTE				byDetected[DH_MOTION_ROW][DH_MOTION_COL]; // ����������32*32������
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE_EX		struHandle;				//������ʽ
} DH_MOTION_DETECT_CFG_EX;


// �𾯱���
typedef struct
{
	BOOL                byFireEn;              // �𾯱���ʱ�ܣ�
	DH_MSG_HANDLE_EX    struHandle;            // ������ʽ
	BYTE                byReserved[128];
}DHDEV_FIRE_ALARM_CFG;

// ��̬��ⱨ�� 
typedef struct 
{
	BYTE				byStaticEn;				// ��̬��ⱨ��ʹ��
	BYTE				byLatch;                // �����ʱ(��Χ0-127����������Χ����nLatch)    
	WORD				wSenseLevel;			// ������
	WORD				wStaticRow;				// ��̬������������
	WORD				wStaticCol;				// ��̬������������
	BYTE				byDetected[DH_STATIC_ROW][DH_STATIC_COL]; // ����������32*32������
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE_EX	struHandle;				// ������ʽ
	int                 nLatch;                 // �����ʱ
	BYTE                bReserved[64];          // �����ֶ�
} DH_STATIC_DETECT_CFG_EX;

// ACC���߱����¼�����
typedef struct _DHDEV_ACC_POWEROFF_CFG
{
	BOOL                bEnable;               // ACC���߱���ʹ��
	int                 nDelayTime;            // ACC���߱�����ʱʱ��,��λ����
	DH_MSG_HANDLE_EX    struHandle;            // ������ʽ
	BYTE                Reserved[128];         // �����ֶ�
}DHDEV_ACC_POWEROFF_CFG;

// �����б����¼�����
typedef struct _DHDEV_EXPLOSION_PROOF_CFG
{
	BOOL                bEnable;               // �����б���ʹ��
	DH_MSG_HANDLE_EX    struHandle;            // ������ʽ
	BYTE                Reserved[128];         // �����ֶ�
}DHDEV_EXPLOSION_PROOF_CFG;

// Raid�¼�����
typedef struct _DHDEV_RAID_EVENT_CFG
{
	BOOL                bEnable;               // Raid�¼�ʹ��
	DH_MSG_HANDLE_EX    struHandle;            // ������ʽ
	BYTE                Reserved[128];         // �����ֶ�
}DHDEV_RAID_EVENT_CFG;

// ��Ƶ��ʧ����
typedef struct
{
	BYTE				byAlarmEn;				// ��Ƶ��ʧ����ʹ��
	BYTE				byReserved[3];
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE_EX	struHandle;				// ������ʽ
} DH_VIDEO_LOST_CFG_EX;

// ͼ���ڵ�����
typedef struct
{
	BYTE				byBlindEnable;			// ʹ��
	BYTE				byBlindLevel;			// ������1-6
	BYTE				byReserved[2];
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE_EX	struHandle;				// ������ʽ
} DH_BLIND_CFG_EX;

// Ӳ����Ϣ(�ڲ�����)
typedef struct 
{
	BYTE				byNoDiskEn;				// ��Ӳ��ʱ����
	BYTE				byReserved_1[3];
	DH_TSECT			stNDSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE_EX	struNDHandle;			// ������ʽ
	
	BYTE				byLowCapEn;				// Ӳ�̵�����ʱ����
	BYTE				byLowerLimit;			// ������ֵ��0-99
	BYTE				byReserved_2[2];
	DH_TSECT			stLCSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE_EX	struLCHandle;			// ������ʽ
	
	BYTE				byDiskErrEn;			// Ӳ�̹��ϱ���
	BYTE				bDiskNum;
	BYTE				byReserved_3[2];
	DH_TSECT			stEDSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE_EX	struEDHandle;			// ������ʽ
} DH_DISK_ALARM_CFG_EX;

typedef struct
{
	BYTE				byEnable;
	BYTE				byReserved[3];
	DH_MSG_HANDLE_EX	struHandle;
} DH_NETBROKEN_ALARM_CFG_EX;

// ǰ�˽������ò�����Ϣ
typedef struct __DEV_ENCODER_CFG 
{
	int					nChannels;				// ����ͨ������
	DEV_ENCODER_INFO	stuDevInfo[32];			// ������ͨ����ǰ�˱�������Ϣ
	BYTE				byHDAbility;			// ����ͨ��������֧�ָ�����Ƶ����(Ϊ0��ʾ��֧�ָ�������)
												// ע�����֧�ָ������ã�����ͨ��Ϊ0~N-1������N֮�������ͨ������Ϊ���壬�п��ܱ��治�ɹ�
	BYTE				bTVAdjust;				// �豸�Ƿ�֧��TV����, 0:��֧�� 1:֧��.
	BYTE				bDecodeTour;			// �豸�Ƿ�֧�ֽ�����Ѳ, 0:��֧�� ����0:��ʾǰ��֧����Ѳ����豸��.
	BYTE				bRemotePTZCtl;			// ָʾ�Ƿ�֧��Զ����̨���ơ�

	char				reserved[12];
} DEV_ENCODER_CFG, *LPDEV_ENCODER_CFG;

// ǰ�˽������ò�����Ϣ��չ
typedef struct __DEV_ENCODER_CFG_EX 
{
	int					nChannels;				// ����ͨ������
	DEV_ENCODER_INFO	stuDevInfo[128];	    // ������ͨ����ǰ�˱�������Ϣ
	BYTE				byHDAbility;			// ����ͨ��������֧�ָ�����Ƶ����(Ϊ0��ʾ��֧�ָ�������)
	// ע�����֧�ָ������ã�����ͨ��Ϊ0~N-1������N֮�������ͨ������Ϊ���壬�п��ܱ��治�ɹ�
	BYTE				bTVAdjust;				// �豸�Ƿ�֧��TV����, 0:��֧�� 1:֧��.
	BYTE				bDecodeTour;			// �豸�Ƿ�֧�ֽ�����Ѳ, 0:��֧�� ����0:��ʾǰ��֧����Ѳ����豸��.
	BYTE				bRemotePTZCtl;			// ָʾ�Ƿ�֧��Զ����̨���ơ�
	char				reserved[256];
} DEV_ENCODER_CFG_EX, *LPDEV_ENCODER_CFG_EX;

// struct ������
typedef struct tagDHCONFIG_CONTROLER{
	DH_COMM_PROP        struComm;	                     // ��������
	BYTE                bLightGroup[DH_MAX_LIGHT_NUM];   // �ܿص����飨����Ŵ�1��ʼ����������[1,3,8,0��0]��ʾ�������Ϊ1,3,8�ĵ�
	BYTE	            bDeviceAddr;	                 // ��������ַ
	BYTE                bComPortType;                    // �������� 0:485����, 1:232����
	BYTE                bReserved[6];		             // ����
} DH_CONFIG_CONTROLER;

// �ƹ��������
typedef struct __DHDEV_LIGHTCONTROL_CFG
{
	DH_CONFIG_CONTROLER    struControlers[DH_MAX_CONTROLER_NUM];  // ��������
	BYTE                   bControlerNum;                         // ��Ч��������Ŀ
	BYTE                   bReserved[1023];                       // ����
} DHDEV_LIGHTCONTROL_CFG, *LPDHDEV_LIGHTCONTROL_CFG;

// 3G������Ϣ����
typedef struct
{
	int                 nStrategy;       //����ʹ�ò���, 0:���������� 1:��ʱ�����
	int                 nUpLimit;        //����ʹ������, ������: ��λMB ��ʱ��: ��λСʱ
	int                 nreserved[22];   //�����ֽ�
}DHDEV_3GFLOW_INFO_CFG;

// IPv6����
typedef struct 
{
	char               szLinkAddr[44];	 // ��·��ַ: �ַ���, ����Ϊ44;(��������ÿ̨����ӵ��Ψһ����·��ַ��ֻ��)
	char               szHostIP[40]; 	 // ����IP
	DWORD              dwPreFix;		 // ����ǰ׺����Χ��1-128���ɶ���д��
	char               szGateWay[40];	 // Ĭ������
	BOOL               bAutoGet;		 // �Զ���ȡʹ��
	char               szPrimaryDns[40]; // ��ѡDNS
	char               szSecondDns[40];	 // ��ѡDNS
    char               cReserved[256];   // �����ֶ�
}DHDEV_IPV6_CFG;

//�����洢����
typedef struct __DEV_URGENCY_RECORD_CFG
{
	DWORD dwSize;           // �ṹ���С
	BOOL bEnable;           // �Ƿ�ʹ�ܣ�1ʹ�ܣ�0��ʹ��
	UINT nMaxRecordTime;    // ���¼��ʱ�䣬��λ��
}DHDEV_URGENCY_RECORD_CFG;

// �������в�������
typedef struct __DEV_ELEVATOR_ATTRI_CFG
{
	DWORD dwSize;           // �ṹ���С
	UINT   nMAXFloorNum;     //���¥�� ��С2
	UINT   nFloorDelayTime;  //ͣ���ж�ʱ��,5-60�����ִ�ʱ�䳤����Ϊ�ǵ���ͣ����¥�㡣
	UINT   nIntervalTime;    //�������л����о���һ������ʱ�䣬���������ʱ�䣬����Ϊ���ݹ��ϣ�����ֹͣ������֮�䡣
}DHDEV_ELEVATOR_ATTRI_CFG;

// ��������ͷ״̬��ѯ
typedef struct tagDHDEV_VIRTUALCAMERA_STATE_INFO
{
	DWORD              nStructSize;                  // �ṹ���С
	int                nChannelID;                   // ͨ����
	CONNECT_STATE      emConnectState;               // ����״̬
	UINT               uiPOEPort;                    // ����������ͷ�����ӵ�POE�˿ںţ�0��ʾ����POE���� 
	char               szDeviceName[64];             // �豸����
	char               szDeviceType[128];            // �豸����
	char               szSystemType[128];            // ϵͳ�汾
	char               szSerialNo[DH_SERIALNO_LEN];  // ���к�
	int                nVideoInput;                  // ��Ƶ����
	int                nAudioInput;                  // ��Ƶ����
	int                nAlarmOutput;                 // �ⲿ����
}DHDEV_VIRTUALCAMERA_STATE_INFO;

// �豸������Ƶ/��Ȧģʽ״̬����Ϣ��ѯ
typedef struct tagDHDEV_TRAFFICWORKSTATE_INFO
{
	DWORD                nStructSize;      // �ṹ���С
	int                  nChannelID;       // ͨ����
	DH_TRAFFIC_SNAP_MODE emSnapMode;       // ץ��ģʽ
}DHDEV_TRAFFICWORKSTATE_INFO;

/////////////////////////////////���ܽ�ͨͼƬ���Ľӿڲ���/////////////////////////////////
typedef struct RESERVED_DATA_INTEL_BOX
{
	DWORD  dwEventCount;	 //�¼�����
	DWORD* dwPtrEventType;	 //ָ���������¼����͵�ֵ���ռ����û��Լ����롣
	BYTE   bReserved[1024];	 //�����ֽ�
}ReservedDataIntelBox;

#define RESERVED_TYPE_FOR_INTEL_BOX 0x00000001
typedef struct RESERVED_PARA
{
	DWORD 	dwType;	//pData����������
	//��[dwType]ΪRESERVED_TYPE_FOR_INTEL_BOX ʱ��pData ��ӦΪ�ṹ��ReservedDataIntelBox�ĵ�ַ					
	//��[dwType]Ϊ...ʱ��[pData]��Ӧ...
	void*	pData;	//����
}ReservedPara;

#define RESERVED_TYPE_FOR_COMMON   0x00000010
typedef struct tagNET_RESERVED_COMMON
{
	DWORD            dwStructSize;
	ReservedDataIntelBox* pIntelBox;    // ����RESERVED_TYPE_FOR_INTEL_BOX
	DWORD            dwSnapFlagMask;	// ץͼ��־(��λ)��0λ:"*",1λ:"Timing",2λ:"Manual",3λ:"Marked",4λ:"Event",5λ:"Mosaic",6λ:"Cutout"
}NET_RESERVED_COMMON;

/////////////////////////////////��������ƽӿڲ���/////////////////////////////////
// �����ṹ��Ϣ
typedef struct 
{
	DWORD       dwSize;
	int         nScene;   //�������
}DHDEV_INTELLI_SCENE_INFO;
// �����߽���λ��Ϣ
typedef struct 
{
	DWORD       dwSize;
	int         nScene;   //�������
	int         nType;    //0:�ϱ߽���λ��1:�±߽���λ��2:��߽磬3:�ұ߽�
}DHDEV_INTELLI_SCENELIMIT_INFO;
// �ֶ�����Ŀ��ṹ����Ϣ
typedef struct
{
	DWORD       dwSize;
	int         nObjectID;   // ����ID��-1 ��ʾweb�Ͽ�ѡ��������֡�ϴ���������λ�����壬>=0��ʾ��ѡ��������֡�ϴ�������
	RECT        stuBound;    // ���η�Χ����������һ����[0,8192]����
}DHDEV_INTELLI_TRACKOBJECT_INFO;

typedef enum __TRACKCONTROL_TYPE
{
	    DH_TRACK_MARKSCENE,        // �궨����, ��Ӧ��DHDEV_INTELLI_SCENE_INFO�ṹ��
		DH_TRACK_GOTOSCENE,        // ת��������,��Ӧ��DHDEV_INTELLI_SCENE_INFO�ṹ��
		DH_TRACK_MARKSCENELIMIT,   // �궨�����߽���λ,��Ӧ��DHDEV_INTELLI_SCENELIMIT_INFO�ṹ��
		DH_TRACK_GOTOSCENELIMIT,   // ת���������߽���λ��,��Ӧ��DHDEV_INTELLI_SCENELIMIT_INFO�ṹ��
		DH_TRACK_MARKSCENEMAXZOOM, // �궨���������ٱ���, ��Ӧ��DHDEV_INTELLI_SCENE_INFO�ṹ��
		DH_TRACK_OBJECT,           // ѡ�г����еĸ���Ŀ��,��Ӧ��DHDEV_INTELLI_TRACKOBJECT_INFO������
		DH_TRACK_START,            // ��ʼ���ܸ��٣�����ָ��������Ϣ
		DH_TRACK_STOP,             // ֹͣ���ܸ��٣�����ָ��������Ϣ
		DH_TRACK_TYPE_NUM,
}DH_TRACKCONTROL_TYPE;
//������������������
typedef struct tagNET_IN_CONTROL_INTELLITRACKER
{
    DWORD       dwSize;
    int         nChannelID;            // ͨ��ID
    DH_TRACKCONTROL_TYPE emCtrlType;   // ��������
    void*       pCtrlInfo;             // �������Ͷ�Ӧ������Ϣ�ṹ��ָ�룬�μ�DH_TRACKCONTROL_TYPE���塣
    int         nMaxLen;               // ������Ϣ�ṹ���С
	int         nWaittime;             // �ȴ���ʱʱ��
}NET_IN_CONTROL_INTELLITRACKER;
//������������������
typedef struct tagNET_OUT_CONTROL_INTELLITRACKER
{
    DWORD       dwSize;
}NET_OUT_CONTROL_INTELLITRACKER;

/////////////////////////////////��̭����/////////////////////////////////

// ��ѯ�豸����״̬ͨ����Ϣ����ؽӿ�����̭���벻Ҫʹ��
typedef struct
{
	BYTE				byRecordStatic;			// ͨ���Ƿ���¼��0����¼��1���ֶ�¼��2���Զ�¼��
	BYTE				bySignalStatic;			// ���ӵ��ź�״̬��0��������1���źŶ�ʧ
	BYTE				byHardwareStatic;		// ͨ��Ӳ��״̬��0��������1���쳣������DSP����
	char				reserve;
	DWORD				dwBitRate;				// ʵ������
	DWORD				dwLinkNum;				// �ͻ������ӵĸ���
	DWORD				dwClientIP[DH_MAX_LINK];// �ͻ��˵�IP��ַ
} NET_DEV_CHANNELSTATE, *LPNET_DEV_CHANNELSTATE;

// ��ѯ�豸����״̬����ؽӿ�����̭���벻Ҫʹ��
typedef struct
{
	DWORD				dwDeviceStatic;			// �豸��״̬��0x00��������0x01��CPUռ�ù��ߣ�0x02��Ӳ������
	NET_DEV_DISKSTATE	stHardDiskStatic[DH_MAX_DISKNUM]; 
	NET_DEV_CHANNELSTATE stChanStatic[DH_MAX_CHANNUM];	//ͨ����״̬
	BYTE				byAlarmInStatic[DH_MAX_ALARMIN];//�����˿ڵ�״̬��0��û�б�����1���б���
	BYTE				byAlarmOutStatic[DH_MAX_ALARMOUT]; //��������˿ڵ�״̬��0��û�������1���б������
	DWORD				dwLocalDisplay;			// ������ʾ״̬��0��������1��������
} NET_DEV_WORKSTATE, *LPNET_DEV_WORKSTATE;

// Э����Ϣ
typedef struct 
{
	char				protocolname[12];		// Э����
	unsigned int		baudbase;				// ������
	unsigned char		databits;				// ����λ
	unsigned char		stopbits;				// ֹͣλ
	unsigned char		parity;					// У��λ
	unsigned char		reserve;
} PROTOCOL_INFO, *LPPROTOCOL_INFO;

// �����Խ���������
typedef struct 
{
	// ��Ƶ�������
	BYTE				byInFormatTag;			// �������ͣ���PCM
	BYTE				byInChannels;			// ������
	WORD				wInBitsPerSample;		// �������					
	DWORD				dwInSamplesPerSec;		// ������

	// ��Ƶ�������
	BYTE				byOutFormatTag;			// �������ͣ���PCM
	BYTE				byOutChannels;			// ������
	WORD				wOutBitsPerSample;		// �������				
	DWORD				dwOutSamplesPerSec;		// ������
} DHDEV_TALK_CFG, *LPDHDEV_TALK_CFG;


/////////////////////////////////// ���� ///////////////////////////////////////

#define DH_MATRIX_INTERFACE_LEN		16		// �źŽӿ����Ƴ���
#define DH_MATRIX_MAX_CARDS			128		// �����ӿ��������
#define DH_SPLIT_PIP_BASE			1000	// �ָ�ģʽ���л��Ļ���ֵ
#define	DH_MAX_SPLIT_MODE_NUM		64		// ���ָ�ģʽ��
#define DH_MATRIX_MAX_CHANNEL_IN	1500	// �����������ͨ����
#define DH_MATRIX_MAX_CHANNEL_OUT	256		// ����������ͨ����
#define DH_DEVICE_NAME_LEN			64		// �豸���Ƴ���
#define DH_MAX_CPU_NUM				16		// ���CPU����
#define DH_MAX_FAN_NUM				16		// ����������
#define DH_MAX_POWER_NUM			16		// ����Դ����
#define DH_MAX_TEMPERATURE_NUM		16		// ����¶ȴ���������
#define DH_MAX_ISCSI_NAME_LEN		128		// ISCSI���Ƴ���
#define DH_VERSION_LEN				64		// �汾��Ϣ����
#define DH_MAX_STORAGE_PARTITION_NUM 32		// �洢�����������
#define DH_STORAGE_MOUNT_LEN		64		// ���ص㳤��
#define DH_STORAGE_FILE_SYSTEM_LEN	16		// �ļ�ϵͳ���Ƴ���
#define DH_MAX_MEMBER_PER_RAID		32		// RAID��Ա�������
#define DH_DEV_ID_LEN_EX			128		// �豸ID��󳤶�
#define DH_MAX_BLOCK_NUM			32		// �����������
#define DH_MAX_SPLIT_WINDOW			128		// ���ָ������
#define DH_FILE_TYPE_LEN			64		// �ļ����ͳ���
#define DH_DEV_ID_LEN				128		// �豸ID��󳤶�
#define DH_DEV_NAME_LEN				128		// �豸������󳤶�
#define DH_TSCHE_DAY_NUM			8		// ʱ�����һά��С, ��ʾ����
#define DH_TSCHE_SEC_NUM			6		// ʱ����ڶ�ά��С, ��ʾʱ����

#define DH_DEVICE_ID_LOCAL		"Local"		// �����豸ID
#define DH_DEVICE_ID_REMOTE		"Remote"	// Զ���豸ID
#define DH_DEVICE_ID_UNIQUE		"Unique"	// �豸��ͳһ���

// �ָ�ģʽ
typedef enum tagDH_SPLIT_MODE
{
	DH_SPLIT_1 = 1,							// 1����
	DH_SPLIT_2 = 2, 						// 2����
	DH_SPLIT_4 = 4, 						// 4����
	DH_SPLIT_6 = 6, 						// 6����
	DH_SPLIT_8 = 8, 						// 8����
	DH_SPLIT_9 = 9, 						// 9����
	DH_SPLIT_12 = 12, 						// 12����
	DH_SPLIT_16 = 16, 						// 16����
	DH_SPLIT_20 = 20, 						// 20����
	DH_SPLIT_25 = 25, 						// 25����
	DH_SPLIT_36 = 36, 						// 36����
	DH_SPLIT_64 = 64, 						// 64����
	DH_SPLIT_144 = 144, 					// 144����
	DH_PIP_1 = DH_SPLIT_PIP_BASE + 1,		// ���л�ģʽ, 1��ȫ������+1��С���洰��
	DH_PIP_3 = DH_SPLIT_PIP_BASE + 3,		// ���л�ģʽ, 1��ȫ������+3��С���洰��
	DH_SPLIT_FREE = DH_SPLIT_PIP_BASE * 2,	// ���ɿ���ģʽ���������ɴ������رմ��ڣ��������ô���λ�ú�Z�����
	DH_COMPOSITE_SPLIT_1 = DH_SPLIT_PIP_BASE * 3 + 1,	// �ں�����Ա1�ָ�
	DH_COMPOSITE_SPLIT_4 = DH_SPLIT_PIP_BASE * 3 + 4,	// �ں�����Ա4�ָ�
} DH_SPLIT_MODE;

// �豸Э������
typedef enum tagDH_DEVICE_PROTOCOL
{
	DH_PROTOCOL_DAHUA2,						// ��2��Э��
	DH_PROTOCOL_DAHUA3,						// ��3��Э��
	DH_PROTOCOL_ONVIF,						// Onvif	
	DH_PROTOCOL_VNC,						// ������������
	
	DH_PROTOCOL_PRIVATE = 100,              // ��˽��Э��        
	DH_PROTOCOL_AEBELL,                     // ���籴��        
	DH_PROTOCOL_PANASONIC,                  // ����        
	DH_PROTOCOL_SONY,                       // ����        
	DH_PROTOCOL_DYNACOLOR,                  // Dynacolor        
	DH_PROTOCOL_TCWS,						// �������        
	DH_PROTOCOL_SAMSUNG,                    // ����        
	DH_PROTOCOL_YOKO,                       // YOKO        
	DH_PROTOCOL_AXIS,                       // ��Ѷ��        
	DH_PROTOCOL_SANYO,						// ����       		
	DH_PROTOCOL_BOSH,						// Bosch		
	DH_PROTOCOL_PECLO,						// Peclo		
	DH_PROTOCOL_PROVIDEO,					// Provideo		
	DH_PROTOCOL_ACTI,						// ACTi		
	DH_PROTOCOL_VIVOTEK,					// Vivotek		
	DH_PROTOCOL_ARECONT,					// Arecont        
	DH_PROTOCOL_PRIVATEEH,			        // PrivateEH	        
	DH_PROTOCOL_IMATEK,					    // IMatek        
	DH_PROTOCOL_SHANY,                      // Shany        
	DH_PROTOCOL_VIDEOTREC,                  // ����ӯ��        
	DH_PROTOCOL_URA,						// Ura        
	DH_PROTOCOL_BITICINO,                   // Bticino         
	DH_PROTOCOL_ONVIF2,                     // OnvifЭ������, ͬDH_PROTOCOL_ONVIF    
	DH_PROTOCOL_SHEPHERD,                   // �Ӱ�        
	DH_PROTOCOL_YAAN,                       // �ǰ�        
	DH_PROTOCOL_AIRPOINT,					// Airpop        
	DH_PROTOCOL_TYCO,                       // TYCO        
	DH_PROTOCOL_XUNMEI,                     // Ѷ��        
	DH_PROTOCOL_HIKVISION,                  // ����        
	DH_PROTOCOL_LG,                         // LG        
	DH_PROTOCOL_AOQIMAN,					// ������        
	DH_PROTOCOL_BAOKANG,                    // ����            
	DH_PROTOCOL_WATCHNET,                   // Watchnet        
	DH_PROTOCOL_XVISION,                    // Xvision        
	DH_PROTOCOL_FUSITSU,                    // ��ʿͨ        
	DH_PROTOCOL_CANON,						// Canon		
	DH_PROTOCOL_GE,							// GE		
	DH_PROTOCOL_Basler,						// ��˹��		
	DH_PROTOCOL_Patro,						// ������	    
	DH_PROTOCOL_CPKNC,						// CPPLUS Kϵ��		
	DH_PROTOCOL_CPRNC,						// CPPLUS Rϵ��		
	DH_PROTOCOL_CPUNC,						// CPPLUS Uϵ��		
	DH_PROTOCOL_CPPLUS,						// cpplus oem �󻪵�ipc		
	DH_PROTOCOL_XunmeiS,					// Ѷ��s,ʵ��Э��ΪOnvif		
	DH_PROTOCOL_GDDW,						// �㶫����		
	DH_PROTOCOL_PSIA,                       // PSIA        
	DH_PROTOCOL_GB2818,                     // GB2818	        
	DH_PROTOCOL_GDYX,                       // GDYX        
	DH_PROTOCOL_OTHER,                      // ���û��Զ���   
	
} DH_DEVICE_PROTOCOL;

// �ָ�ģʽ��Ϣ
typedef struct tagDH_SPLIT_MODE_INFO
{
	DWORD				dwSize;
	DH_SPLIT_MODE		emSplitMode;			// �ָ�ģʽ
	int					nGroupID;				// �������
} DH_SPLIT_MODE_INFO;

// �ָ�����
typedef struct tagDH_SPLIT_CAPS 
{
	DWORD				dwSize;
	int					nModeCount;				// ֧�ֵķָ�ģʽ����
	DH_SPLIT_MODE		emSplitMode[DH_MAX_SPLIT_MODE_NUM];	// ֧�ֵķָ�ģʽ
	int				    nMaxSourceCount;		// �����ʾԴ������
	int					nFreeWindowCount;		// ֧�ֵ�������ɿ�����Ŀ
	BOOL				bCollectionSupported;	// �Ƿ�֧�������ղ�
} DH_SPLIT_CAPS;

// ����Ȩ����֤��Ϣ
typedef struct tagDH_CASCADE_AUTHENTICATOR
{
	DWORD				dwSize;
	char				szUser[DH_NEW_USER_NAME_LENGTH];		// �û���
	char				szPwd[DH_NEW_USER_PSW_LENGTH];			// ����
	char				szSerialNo[DH_SERIALNO_LEN];			// �豸���к�
} DH_CASCADE_AUTHENTICATOR;

// ��ʾԴ
typedef struct tagDH_SPLIT_SOURCE
{
	DWORD				dwSize;
	BOOL			    bEnable;						    // ʹ��
	char			    szIp[DH_MAX_IPADDR_LEN];		    // IP, �ձ�ʾû������
	char			    szUser[DH_USER_NAME_LENGTH];	    // �û���
	char			    szPwd[DH_USER_PSW_LENGTH];	    	// ����
	int			    	nPort;							    // �˿�
	int				    nChannelID;						    // ͨ����
	int				    nStreamType;					    // ��Ƶ����, -1-�Զ�, 0-������, 1-������1, 2-������2, 3-������3, 4-snap, 5-Ԥ��
	int				    nDefinition;					    // ������, 0-����, 1-����
	DH_DEVICE_PROTOCOL  emProtocol;							// Э������
	char			    szDevName[DH_DEVICE_NAME_LEN];		// �豸����
	int					nVideoChannel;						// ��Ƶ����ͨ����
	int					nAudioChannel;						// ��Ƶ����ͨ����
	//--------------------------------------------------------------------------------------
	// ����ֻ�Խ�������Ч
	BOOL				bDecoder;							// �Ƿ��ǽ�����
	BYTE				byConnType;							// -1: auto, 0��TCP��1��UDP��2���鲥
	BYTE				byWorkMode;							// 0��ֱ����1��ת��
	WORD				wListenPort;						// ָʾ��������Ķ˿ڣ�ת��ʱ��Ч; byConnTypeΪ�鲥ʱ������Ϊ�ಥ�˿�
	char				szDevIpEx[DH_MAX_IPADDR_OR_DOMAIN_LEN];// szDevIp��չ��ǰ��DVR��IP��ַ(������������)
	BYTE				bySnapMode;                         // ץͼģʽ(nStreamType==4ʱ��Ч) 0����ʾ����һ֡,1����ʾ��ʱ��������
	BYTE				byManuFactory;						// Ŀ���豸����������, ����ο�EM_IPC_TYPE��
	BYTE				byDeviceType;                       // Ŀ���豸���豸����, 0:IPC
	BYTE				byDecodePolicy;                     // Ŀ���豸�Ľ������, 0:������ǰ
															// 1:ʵʱ�ȼ��� 2:ʵʱ�ȼ���
															// 3:ʵʱ�ȼ��� 4:Ĭ�ϵȼ�
															// 5:�����ȼ��� 6:�����ȼ���
															// 7:�����ȼ���
	//--------------------------------------------------------------------------------------
	DWORD				dwHttpPort;                         // Http�˿ں�, 0-65535
	DWORD				dwRtspPort;                         // Rtsp�˿ں�, 0-65535
	char				szChnName[DH_DEVICE_NAME_LEN];		// Զ��ͨ������, ֻ�ж�ȡ�������Ʋ�Ϊ��ʱ�ſ����޸ĸ�ͨ��������
	char				szMcastIP[DH_MAX_IPADDR_LEN];       // �ಥIP��ַ, byConnTypeΪ�鲥ʱ��Ч
	char				szDeviceID[DH_DEV_ID_LEN_EX];		// �豸ID, ""-null, "Local"-����ͨ��, "Remote"-Զ��ͨ��, ������������RemoteDevice�е��豸ID
	BOOL				bRemoteChannel;						// �Ƿ�Զ��ͨ��(ֻ��)
	unsigned int		nRemoteChannelID;					// Զ��ͨ��ID(ֻ��), bRemoteChannel=TRUEʱ��Ч
	char				szDevClass[DH_DEV_TYPE_LEN];		// �豸����, ��IPC, DVR, NVR��
	char				szDevType[DH_DEV_TYPE_LEN];			// �豸�����ͺ�, ��IPC-HF3300
	char				szMainStreamUrl[MAX_PATH];			// ������url��ַ, byManuFactoryΪDH_IPC_OTHERʱ��Ч
	char				szExtraStreamUrl[MAX_PATH];			// ������url��ַ, byManuFactoryΪDH_IPC_OTHERʱ��Ч
	int					nUniqueChannel;						// �豸��ͳһ��ŵ�Ψһͨ����, ֻ��
	DH_CASCADE_AUTHENTICATOR stuCascadeAuth;				// ������֤��Ϣ, �豸IDΪ"Local/Cascade/SerialNo"ʱ��Ч, ����SerialNo���豸���к�
} DH_SPLIT_SOURCE;

// ��Ƶ���������
typedef struct tagDH_VIDEO_OUT_CAPS 
{
	DWORD				dwSize;
	BOOL				bColor;							// �Ƿ�֧�������ɫ����
	BOOL				bMargin;						// �Ƿ�֧�ֱ߽�����
	int					nLayers;						// ֧��ͬʱ��ʾ��ͼ����
	BOOL				bPowerMode;						// �Ƿ�֧�ֵ�Դ����
	int					bSplitMode;						// ֧�ֵĻ���ָ�ģʽ, 0-������, 1-'#'����ģʽ(����������), 2-����ģʽ
} DH_VIDEO_OUT_CAPS;

// ��ɫRGBA
typedef struct tagDH_COLOR_RGBA
{
	int					nRed;							// ��
	int					nGreen;							// ��
	int					nBlue;							// ��
	int					nAlpha;							// ͸��
} DH_COLOR_RGBA;

// ��ɫBCSH
typedef struct tagDH_COLOR_BCSH 
{
	int					nBirghtness;					// ����
	int					nContrast;						// �Աȶ�
	int			        nSaturation;					// ���Ͷ�
	int					nHue;							// ɫ��
} DH_COLOR_BCSH;

// �ߴ�
typedef struct tagDH_SIZE 
{
	int					nWidth;							// ����
	int					nHeight;						// �߶�
} DH_SIZE;

// �Ȱβ�ģʽ
typedef struct tagDH_HOT_PLUG_MODE
{
	DWORD				dwSize;
	int					nMode;							// �Ȱβ�ģʽ, 0-�Ȳ��ģʽ, 1-ǿ�����ģʽ
} DH_HOT_PLUG_MODE;

// ��Ƶ���ѡ��
typedef struct tagDH_VIDEO_OUT_OPT
{
	DWORD				dwSize;
	DH_RECT*			pstuMargin;						// �߽緶Χ
	DH_COLOR_BCSH*		pstuColor;						// �����ɫ
	DH_COLOR_RGBA*		pstuBackground;					// ����ɫ
	DH_SIZE*			pstuSize;						// ����ߴ�
	DH_HOT_PLUG_MODE*	pstuHotPlugMode;				// �Ȱβ�ģʽ
} DH_VIDEO_OUT_OPT;

// ��Ʒ����
typedef struct tagDH_PRODUCTION_DEFNITION
{
	DWORD				dwSize;
	int					nVideoInChannel;				// ��Ƶ����ͨ����
	int					nVideoOutChannel;				// ��Ƶ���ͨ����
	int					nRemoteDecChannel;				// Զ�̽���ͨ����
	char				szDevType[DH_DEV_TYPE_LEN];		// �豸����
	char				szVendor[DH_MAX_NAME_LEN];		// OEM�ͻ�
	int					nOEMVersion;					// OEM�汾
	int					nMajorVerion;					// ���汾��
	int					nMinorVersion;					// �ΰ汾��
	int					nRevision;						// �޶��汾
	char				szWebVerion[DH_MAX_NAME_LEN];	// Web�汾
	char				szDefLanguage[DH_MAX_NAME_LEN];	// Ĭ������
	NET_TIME			stuBuildDateTime;				// ����ʱ��, ��ȷ����
	int					nAudioInChannel;				// ��Ƶ����ͨ����
	int					nAudioOutChannel;				// ��Ƶ���ͨ����
	BOOL				bGeneralRecord;					// �Ƿ�֧�ֶ�ʱ�洢
	BOOL				bLocalStore;					// �Ƿ�֧�ֱ��ش洢
	BOOL				bRemoteStore;					// �Ƿ�֧������洢
	BOOL				bLocalurgentStore;				// �Ƿ�֧�ֽ����洢������
	BOOL				bRealtimeCompress;				// �Ƿ�֧��ʵʱѹ���洢
	DWORD				dwVideoStandards;				// ֧�ֵ���Ƶ��ʽ�б�, bit0-PAL, bit1-NTSC
	int					nDefVideoStandard;				// Ĭ����Ƶ��ʽ, 0-PAL, 1-NTSC
	int					nMaxExtraStream;				// �������·��
	int					nRemoteRecordChannel;			// Զ��¼��ͨ����
	int					nRemoteSnapChannel;				// Զ��ץͼͨ����
	int					nRemoteVideoAnalyseChannel;		// Զ����Ƶ����ͨ����
	int					nRemoteTransmitChannel;			// Զ��ʵʱ��ת�����ͨ����
	int					nRemoteTransmitFileChannel;		// Զ���ļ���ת��ͨ��ͨ����
	int					nStreamTransmitChannel;			// ������紫��ͨ������
	int					nStreamReadChannel;				// �����ļ���ͨ������
	int					nMaxStreamSendBitrate;			// ����������緢������, kbps
	int					nMaxStreamRecvBitrate;			// �����������ӿ�����, kbps
	BOOL				bCompressOldFile;				// �Ƿ�ѹ�����ļ�, ȥ��P֡, ����I֡
	BOOL				bRaid;							// �Ƿ�֧��RAID
	int					nMaxPreRecordTime;				// ���Ԥ¼ʱ��, s
	BOOL				bPtzAlarm;						// �Ƿ�֧����̨����
	BOOL				bPtz;							// �Ƿ�֧����̨
	BOOL				bATM;							// �Ƿ���ʾATM��ع���
	BOOL				b3G;							// �Ƿ�֧��3Gģ��
	BOOL				bNumericKey;					// �Ƿ�����ּ�
	BOOL				bShiftKey;						// �Ƿ��Shift��
	BOOL				bCorrectKeyMap;					// ������ĸӳ����Ƿ���ȷ
	BOOL				bNewATM;						// �µĶ���ATMǰ���
	BOOL				bDecoder;						// �Ƿ��ǽ�����
	DEV_DECODER_INFO	stuDecoderInfo;					// ��������Ϣ, bDecoder=trueʱ��Ч
	int					nVideoOutputCompositeChannels;	// �ں������ͨ������
	BOOL                bSupportedWPS;                  // �Ƿ�֧��WPS����
	int					nVGAVideoOutputChannels;		// VGA��Ƶ���ͨ����
	int					nTVVideoOutputChannels;			// TV��Ƶ���ͨ����
	int					nMaxRemoteInputChannels;			// ���Զ��ͨ����
	int					nMaxMatrixInputChannels;			// ������ͨ����
	int                 nMaxRoadWays;                   // ���ܽ�ͨ��󳵵��� 1~6
	int                 nMaxParkingSpaceScreen;         // ������Խ����֧�ֵ����������� 0~20
} DH_PRODUCTION_DEFNITION;

// �����ӿ�����, �������Ϳ������
#define DH_MATRIX_CARD_MAIN				0x10000000		// ����
#define DH_MATRIX_CARD_INPUT			0x00000001		// ���뿨
#define DH_MATRIX_CARD_OUTPUT			0x00000002		// �����
#define DH_MATRIX_CARD_ENCODE			0x00000004		// ���뿨
#define DH_MATRIX_CARD_DECODE			0x00000008		// ���뿨
#define DH_MATRIX_CARD_CASCADE			0x00000010		// ������
#define DH_MATRIX_CARD_INTELLIGENT		0x00000020		// ���ܿ�

// �����ӿ���Ϣ
typedef struct tagDH_MATRIX_CARD
{
	DWORD				dwSize;
	BOOL				bEnable;					// �Ƿ���Ч
	DWORD				dwCardType;					// �ӿ�����
	char		    	szInterface[DH_MATRIX_INTERFACE_LEN];	// �źŽӿ�����, "CVBS", "VGA", "DVI"...
	char		    	szAddress[DH_MAX_IPADDR_OR_DOMAIN_LEN];	// �豸ip������, ������ӿڵ��ӿ�����Ϊ��
	int			    	nPort;						// �˿ں�, ������ӿڵ��ӿ�����Ϊ0
	int					nDefinition;				// ������, 0=����, 1=����
	int					nVideoInChn;				// ��Ƶ����ͨ����
	int					nAudioInChn;				// ��Ƶ����ͨ����
	int					nVideoOutChn;				// ��Ƶ���ͨ����
	int				    nAudioOutChn;				// ��Ƶ���ͨ����
	int			    	nVideoEncChn;				// ��Ƶ����ͨ����
	int				    nAudioEncChn;				// ��Ƶ����ͨ����
	int			    	nVideoDecChn;				// ��Ƶ����ͨ����
	int			    	nAudioDecChn;				// ��Ƶ����ͨ����
	int					nStauts;					// ״̬: 0-����, 1-����Ӧ, 2-�������, 3-��ͻ, 4-��������
	int					nCommPorts;					// ������
	int					nVideoInChnMin;				// ��Ƶ����ͨ������Сֵ
	int					nVideoInChnMax;				// ��Ƶ����ͨ�������ֵ
	int					nAudioInChnMin;				// ��Ƶ����ͨ������Сֵ
	int					nAudioInChnMax;				// ��Ƶ����ͨ�������ֵ
	int					nVideoOutChnMin;			// ��Ƶ���ͨ������Сֵ
	int					nVideoOutChnMax;			// ��Ƶ���ͨ�������ֵ
	int					nAudioOutChnMin;			// ��Ƶ���ͨ������Сֵ
	int					nAudioOutChnMax;			// ��Ƶ���ͨ�������ֵ	
	int					nVideoEncChnMin;			// ��Ƶ����ͨ������Сֵ
	int					nVideoEncChnMax;			// ��Ƶ����ͨ�������ֵ
	int					nAudioEncChnMin;			// ��Ƶ����ͨ������Сֵ
	int					nAudioEncChnMax;			// ��Ƶ����ͨ�������ֵ
	int					nVideoDecChnMin;			// ��Ƶ����ͨ������Сֵ
	int					nVideoDecChnMax;			// ��Ƶ����ͨ�������ֵ
	int					nAudioDecChnMin;			// ��Ƶ����ͨ������Сֵ
	int					nAudioDecChnMax;			// ��Ƶ����ͨ�������ֵ
	int					nCascadeChannels;			// ����ͨ����
	int					nCascadeChannelBitrate;		// ����ͨ������, ��λMbps
} DH_MATRIX_CARD;

// �����ӿ��б�
typedef struct tagDH_MATRIX_CARD_LIST 
{
	DWORD				dwSize;
	int					nCount;							// �ӿ�����
	DH_MATRIX_CARD		stuCards[DH_MATRIX_MAX_CARDS];	// �ӿ��б�
} DH_MATRIX_CARD_LIST;

// ��Ƶ�������
typedef struct tagDH_VIDEO_OUT_WINDOW
{
	DWORD				dwSize;
	int					nBackboardID;				// �����
	int					nScreenID;					// ��Ļ��
	int					nWindowID;					// ���ں�
} DH_VIDEO_OUT_WINDOW;

// CLIENT_GetISCSITargets�ӿ��������
typedef struct tagDH_IN_ISCSI_TARGETS
{
	DWORD				dwSize;
	const char*			pszAddress;					// ��������ַ
	int					nPort;						// �˿�
	const char*			pszUser;					// �û���
	const char*			pszPwd;						// ����
} DH_IN_ISCSI_TARGETS;

// ISCSI Target��Ϣ
typedef struct tagDH_ISCSI_TARGET 
{
	DWORD				dwSize;
	char				szName[DH_MAX_ISCSI_NAME_LEN];	// ����
	char				szAddress[DH_MAX_IPADDR_OR_DOMAIN_LEN];	// ��������ַ
	char				szUser[DH_NEW_USER_NAME_LENGTH];// �û���
	int					nPort;							// �˿�
	UINT				nStatus;						// ״̬, 0-δ֪, 1-������, 2-δ����, 3-����ʧ��, 4-��֤ʧ��, 5-���ӳ�ʱ	
} DH_ISCSI_TARGET;

// CLIENT_GetISCSITargets�ӿ��������
typedef struct tagDH_OUT_ISCSI_TARGETS
{
	DWORD				dwSize;
	DH_ISCSI_TARGET*	pstuTargets;				// iscsi����
	int					nMaxCount;					// iscsi�����С
	int					nRetCount;					// ��ȡ����iscsi��Ϣ��
} DH_OUT_ISCSI_TARGETS;

// �洢�豸����
typedef struct tagDH_STORAGE_DEVICE_NAME 
{
	DWORD				dwSize;
	char				szName[DH_STORAGE_NAME_LEN];
} DH_STORAGE_DEVICE_NAME;

// RAID״̬
#define DH_RAID_STATE_ACTIVE		0x00000001
#define DH_RAID_STATE_INACTIVE		0x00000002
#define DH_RAID_STATE_CLEAN			0x00000004
#define DH_RAID_STATE_FAILED		0x00000008
#define DH_RAID_STATE_DEGRADED		0x00000010
#define DH_RAID_STATE_RECOVERING	0x00000020
#define DH_RAID_STATE_RESYNCING		0x00000040
#define DH_RAID_STATE_RESHAPING		0x00000080
#define DH_RAID_STATE_CHECKING		0x00000100
#define DH_RAID_STATE_NOTSTARTED	0x00000200

// RAID��Ϣ
typedef struct tagDH_STORAGE_RAID
{
	DWORD				dwSize;
	int					nLevel;										// �ȼ�	
	int					nState;										// RAID״̬���, ��DH_RAID_STATE_ACTIVE | DH_RAID_STATE_DEGRADED
	int					nMemberNum;									// ��Ա����
	char				szMembers[DH_MAX_MEMBER_PER_RAID][DH_STORAGE_NAME_LEN];	// RAID��Ա
} DH_STORAGE_RAID;

// �洢������Ϣ
typedef struct tagDH_STORAGE_PARTITION
{
	DWORD				dwSize;
	char				szName[DH_STORAGE_NAME_LEN];				// ����
	INT64				nTotalSpace;								// �ܿռ�, byte
	INT64				nFreeSpace;									// ʣ��ռ�, byte
	char				szMountOn[DH_STORAGE_MOUNT_LEN];			// ���ص�
	char				szFileSystem[DH_STORAGE_FILE_SYSTEM_LEN];	// �ļ�ϵͳ
	int					nStatus;									// ����״̬, 0-LV������, 1-LV����
} DH_STORAGE_PARTITION;

// ��չ����Ϣ
typedef struct tagDH_STORAGE_TANK 
{
	DWORD				dwSize;
	int					nLevel;										// ����, �����ǵ�0��������������������
	int					nTankNo;									// ͬһ����չ���ڵ���չ�ڱ��, ��0��ʼ
} DH_STORAGE_TANK;

// �洢�豸��Ϣ
typedef struct tagDH_STORAGE_DEVICE 
{
	DWORD				dwSize;
	char				szName[DH_STORAGE_NAME_LEN];				// ����
	INT64				nTotalSpace;								// �ܿռ�, byte
	INT64				nFreeSpace;									// ʣ��ռ�, byte
	BYTE				byMedia;									// ����, 0-DISK, 1-CDROM, 2-FLASH
	BYTE				byBUS;										// ����, 0-ATA, 1-SATA, 2-USB, 3-SDIO, 4-SCSI
	BYTE				byVolume;									// ������, 0-������, 1-Raid��, 2-VG�����, 3-ISCSI
	BYTE				byState;									// ����Ӳ��״̬, 0-����Ӳ���ѻ�״̬ 1-����Ӳ������״̬ 2-RAID� 3-RAIDͬ�� 4-RAID�ȱ� 5-RAIDʧЧ 6-RAID�ؽ� 7-RAID�Ƴ�
	int					nPhysicNo;									// ͬ���豸�洢�ӿڵ��������
	int					nLogicNo;									// ͬ���豸�洢�ӿڵ��߼����
	char				szParent[DH_STORAGE_NAME_LEN];				// �ϼ��洢������
	char				szModule[DH_STORAGE_NAME_LEN];				// �豸ģ��
	char				szSerial[DH_SERIALNO_LEN];					// �豸���к�
	char				szFirmware[DH_VERSION_LEN];					// �̼��汾
	int					nPartitionNum;								// ������
	DH_STORAGE_PARTITION stuPartitions[DH_MAX_STORAGE_PARTITION_NUM];// ������Ϣ
	DH_STORAGE_RAID		stuRaid;									// RAID��Ϣ, ֻ��RAID��Ч(byVolume == 1)
	DH_ISCSI_TARGET		stuISCSI;									// ISCSI��Ϣ, ֻ��ISCSI����Ч(byVolume == 3)
	BOOL				abTank;										// ��չ��ʹ��
	DH_STORAGE_TANK		stuTank;									// Ӳ��������չ����Ϣ, abTankΪTRUEʱ��Ч
} DH_STORAGE_DEVICE;

// OSDͨ����Ϣ
typedef struct tagDH_OSD_CHANNEL_TITLE 
{
	DWORD					dwSize;
	BOOL					bEnable;					// ʹ��
	DH_COLOR_RGBA			stuFontColor;				// ǰ��ɫ
	DH_COLOR_RGBA			stuBackColor;				// ����ɫ
	DH_RECT					stuRect;					// ����
} DH_OSD_CHANNEL_TITLE;

// OSDͼ��
typedef struct tagDH_OSD_LOGO_ICON
{
	DWORD					dwSize;
	BOOL					bEnable;					// ʹ��
	DH_COLOR_RGBA			stuFontColor;				// ǰ��ɫ
	DH_COLOR_RGBA			stuBackColor;				// ����ɫ
	DH_RECT					stuRect;					// ����
	char					szIconName[MAX_PATH];		// ·��
} DH_OSD_LOGO_ICON;

// CLIENT_GetSplitOSD �ӿ��������(��ȡ���봰�����OSD��Ϣ)
typedef struct tagDH_IN_SPLIT_GET_OSD
{
	DWORD					dwSize;
	int						nChannel;				// ͨ����
	int						nWindow;				// ���ں�
} DH_IN_SPLIT_GET_OSD;

// CLIENT_GetSplitOSD �ӿ��������(��ȡ���봰�����OSD��Ϣ)
typedef struct tagDH_OUT_SPLIT_GET_OSD
{
	DWORD					dwSize;
	DH_OSD_CHANNEL_TITLE	stuChannelTitle;		// ͨ������
	DH_OSD_LOGO_ICON		stuLogoIcon;			// ͼ��
} DH_OUT_SPLIT_GET_OSD;

// CLIENT_SetSplitOSD �ӿ��������(���ý��봰�����OSD��Ϣ)
typedef struct tagDH_IN_SPLIT_SET_OSD
{
	DWORD					dwSize;
	int						nChannel;				// ͨ����
	int						nWindow;				// ���ں�
	DH_OSD_CHANNEL_TITLE	stuChannelTitle;		// ͨ������
	DH_OSD_LOGO_ICON		stuLogoIcon;			// ͼ��
} DH_IN_SPLIT_SET_OSD;

// CLIENT_SetSplitOSD �ӿ��������(���ý��봰�����OSD��Ϣ)
typedef struct tagDH_OUT_SPLIT_SET_OSD
{
	DWORD					dwSize;
} DH_OUT_SPLIT_SET_OSD;

////////////////////////////////// ϵͳ״̬ ////////////////////////////////////////

// CPU��Ϣ
typedef struct tagDH_CPU_INFO
{
	DWORD				dwSize;
	int					nUsage;						// CPU������
} DH_CPU_INFO;

// CPU״̬
typedef struct tagDH_CPU_STATUS
{
	DWORD				dwSize;
	BOOL				bEnable;					// ��ѯ�Ƿ�ɹ�
	int					nCount;						// CPU����
	DH_CPU_INFO			stuCPUs[DH_MAX_CPU_NUM];	// CPU��Ϣ
} DH_CPU_STATUS;

// �ڴ���Ϣ
typedef struct tagDH_MEMORY_INFO
{
	DWORD				dwSize;
	DWORD				dwTotal;					// ���ڴ�, M
	DWORD				dwFree;						// ʣ���ڴ�, M
} DH_MEMORY_INFO;

// �ڴ�״̬
typedef struct tagDH_MEMORY_STATUS 
{
	DWORD				dwSize;
	BOOL				bEnable;					// ��ѯ�Ƿ�ɹ�
	DH_MEMORY_INFO		stuMemory;					// �ڴ���Ϣ
} DH_MEMORY_STATUS;

// ������Ϣ
typedef struct tagDH_FAN_INFO
{
	DWORD				dwSize;
	char				szName[DH_DEVICE_NAME_LEN];	// ����
	DWORD				nSpeed;						// �ٶ�
} DH_FAN_INFO;

// ����״̬
typedef struct tagDH_FAN_STATUS
{
	DWORD				dwSize;
	BOOL				bEnable;					// ��ѯ�Ƿ�ɹ�
	int					nCount;						// ��������
	DH_FAN_INFO			stuFans[DH_MAX_FAN_NUM];	// ����״̬
} DH_FAN_STATUS;

// ��Դ��Ϣ
typedef struct tagDH_POWER_INFO
{
	DWORD				dwSize;
	BOOL				bPowerOn;					// ��Դ�Ƿ��
} DH_POWER_INFO;

// ��Դ״̬
typedef struct tagDH_POWER_STATUS
{
	DWORD				dwSize;
	BOOL				bEnable;					// ��ѯ�Ƿ�ɹ�
	int					nCount;						// ��Դ����
	DH_POWER_INFO		stuPowers[DH_MAX_POWER_NUM];// ��Դ״̬
} DH_POWER_STATUS;

// �¶���Ϣ
typedef struct tagDH_TEMPERATURE_INFO
{
	DWORD				dwSize;
	char				szName[DH_DEVICE_NAME_LEN];	// ����������
	float				fTemperature;				// �¶�
} DH_TEMPERATURE_INFO;

// �¶�״̬
typedef struct tagDH_TEMPERATURE_STATUS
{
	DWORD				dwSize;
	BOOL				bEnable;							// ��ѯ�Ƿ�ɹ�
	int					nCount;								// �¶�����
	DH_TEMPERATURE_INFO	stuTemps[DH_MAX_TEMPERATURE_NUM];	// �¶���Ϣ 
} DH_TEMPERATURE_STATUS;

// ϵͳ״̬
typedef struct tagDH_SYSTEM_STATUS
{
	DWORD				dwSize;
	DH_CPU_STATUS*		pstuCPU;					// CPU״̬
	DH_MEMORY_STATUS*	pstuMemory;					// �ڴ�״̬
	DH_FAN_STATUS*		pstuFan;					// ����״̬
	DH_POWER_STATUS*	pstuPower;					// ��Դ״̬
	DH_TEMPERATURE_STATUS*	pstuTemp;				// �¶�״̬
} DH_SYSTEM_STATUS;

////////////////////////////////// �������� ////////////////////////////////////////
// CLIENT_OpenSplitWindow�ӿ��������(����)
typedef struct tagDH_IN_SPLIT_OPEN_WINDOW
{
	DWORD				dwSize;
	int					nChannel;					// ͨ����(����)
	DH_RECT				stuRect;					// ����λ��, 0~8192
	BOOL				bDirectable;				// �����Ƿ�����ֱͨ����, ֱͨ��ָƴ������ʽ�£��˴�����������Ϊ����������
} DH_IN_SPLIT_OPEN_WINDOW;

// CLIENT_OpenSplitWindow�ӿ��������(����)
typedef struct tagDH_OUT_SPLIT_OPEN_WINDOW
{
	DWORD				dwSize;
	unsigned int		nWindowID;					// �������
	unsigned int		nZOrder;					// ���ڴ���		
} DH_OUT_SPLIT_OPEN_WINDOW;

// CLIENT_CloseSplitWindow�ӿ��������(�ش�)
typedef struct tagDH_IN_SPLIT_CLOSE_WINDOW
{
	DWORD				dwSize;
	int					nChannel;					// ͨ����(����)
	UINT				nWindowID;					// �������
} DH_IN_SPLIT_CLOSE_WINDOW;

// CLIENT_CloseSplitWindow�ӿ��������(�ش�)
typedef struct tagDH_OUT_SPLIT_CLOSE_WINDOW
{
	DWORD				dwSize;
} DH_OUT_SPLIT_CLOSE_WINDOW;

// CLIENT_SetSplitWindowRect�������(���ô���λ��)
typedef struct tagDH_IN_SPLIT_SET_RECT
{
	DWORD				dwSize;
	int					nChannel;					// ͨ����(����)
	UINT				nWindowID;					// �������
	DH_RECT				stuRect;					// ����λ��, 0~8192
	BOOL				bDirectable;				// �����Ƿ�����ֱͨ����, ֱͨ��ָƴ������ʽ�£��˴�����������Ϊ����������
} DH_IN_SPLIT_SET_RECT;

// CLIENT_SetSplitWindowRect�ӿ��������(���ô���λ��)
typedef struct tagDH_OUT_SPLIT_SET_RECT
{
	DWORD				dwSize;
} DH_OUT_SPLIT_SET_RECT;

// CLIENT_GetSplitWindowRect�ӿ��������(��ȡ����λ��)
typedef struct tagDH_IN_SPLIT_GET_RECT
{
	DWORD				dwSize;
	int					nChannel;					// ͨ����(����)
	UINT				nWindowID;					// �������
} DH_IN_SPLIT_GET_RECT;

// CLIENT_GetSplitWindowRect�ӿ��������(��ȡ����λ��)
typedef struct tagDH_OUT_SPLIT_GET_RECT
{
	DWORD				dwSize;	
	DH_RECT				stuRect;					// ����λ��, 0~8192
} DH_OUT_SPLIT_GET_RECT;

// ���ڲ������
typedef struct tagDH_WND_ZORDER
{
	DWORD				dwSize;
	unsigned int		nWindowID;					// �������
	unsigned int		nZOrder;					// Z����
} DH_WND_ZORDER;

// CLIENT_SetSplitTopWindow�ӿ��������(���ô��ڴ���)
typedef struct tagDH_IN_SPLIT_SET_TOP_WINDOW
{
	DWORD				dwSize;
	int					nChannel;					// ͨ����(����)
	int					nWindowID;					// �������
} DH_IN_SPLIT_SET_TOP_WINDOW;

// CLIENT_SetSplitTopWindow�ӿ��������(���ô��ڴ���)
typedef struct tagDH_OUT_SPLIT_SET_TOP_WINDOW
{
	DWORD				dwSize;
	DH_WND_ZORDER*		pZOders;					// ���ڴ�������
	int					nMaxWndCount;				// ���ڴ��������С
	int					nWndCount;					// ���صĴ�������
} DH_OUT_SPLIT_SET_TOP_WINDOW;

// CLIENT_SetDisplayMode�ӿ��������(����ǽ��ʾģʽ����)
typedef struct tagDH_IN_WM_SET_DISPLAY_MODE 
{
	DWORD				dwSize;
	int					nMonitorWallID;				// ����ǽ���
	const char*			pszBlockID;					// ����ID, NULL/""-��������
	int					nTVID;						// ��ʾ��Ԫ���, -1��ʾ������������ʾ��Ԫ
	UINT				nDisplayMode;				// ��ʾģʽ, 0-��׼, 1-����, 2-����
} DH_IN_WM_SET_DISPLAY_MODE;

// CLIENT_SetDisplayMode�ӿ��������(����ǽ��ʾģʽ����)
typedef struct tagDH_OUT_WM_SET_DISPLAY_MODE
{
	DWORD				dwSize;
} DH_OUT_WM_SET_DISPLAY_MODE;

// ������������ʾ��Ԫ����ʾģʽ
typedef struct tagDH_BLOCK_DISPLAY_MODE
{
	DWORD				dwSize;
	int*				pTVModes;					// TV��ʾģʽ����
	int					nMaxTVCount;				// TV��ʾģʽ�����С
	int					nRetTVCount;				// ʵ��TV����
} DH_BLOCK_DISPLAY_MODE;

// CLIENT_GetDisplayMode�ӿڵ��������(��ȡ����ǽ��ʾģʽ)
typedef struct tagDH_IN_WM_GET_DISPLAY_MODE 
{
	DWORD				dwSize;
	int					nMonitorWallID;				// ����ǽ���
	const char*			pszBlockID;					// ����ID, NULL/""-��������
	int					nTVID;						// ��ʾ��Ԫ���, -1��ʾ������������ʾ��Ԫ
} DH_IN_WM_GET_DISPLAY_MODE;

// CLIENT_GetDisplayMode�ӿڵ��������(��ȡ����ǽ��ʾģʽ)
typedef struct tagDH_OUT_WM_GET_DISPLAY_MODE
{
	DWORD				dwSize;
	DH_BLOCK_DISPLAY_MODE* pBlockModes;				// ������ʾģʽ����
	int					nMaxBlockCount;				// ������ʾģʽ�����С
	int					nRetBlockCount;				// ʵ����������
} DH_OUT_WM_GET_DISPLAY_MODE;

// CLIENT_PowerControl�ӿ��������(����ǽ��Դ����)
typedef struct tagDH_IN_WM_POWER_CTRL 
{
	DWORD				dwSize;
	int					nMonitorWallID;				// ����ǽ���
	const char*			pszBlockID;					// ����ID, NULL/""-��������
	int					nTVID;						// ��ʾ��Ԫ���, -1��ʾ������������ʾ��Ԫ
	BOOL				bPowerOn;					// �Ƿ�򿪵�Դ
} DH_IN_WM_POWER_CTRL;

// CLIENT_PowerControl�ӿ��������(����ǽ��Դ����)
typedef struct tagDH_OUT_WM_POWER_CTRL
{
	DWORD				dwSize;
} DH_OUT_WM_POWER_CTRL;

// CLIENT_LoadMonitorWallCollection�ӿ��������(�������ǽԤ��)
typedef struct tagDH_IN_WM_LOAD_COLLECTION 
{
	DWORD				dwSize;
	int					nMonitorWallID;				// ����ǽ���
	const char*			pszName;					// Ԥ������
} DH_IN_WM_LOAD_COLLECTION;

// CLIENT_LoadMonitorWallCollection�ӿ��������(�������ǽԤ��)
typedef struct tagDH_OUT_WM_LOAD_COLLECTION 
{
	DWORD				dwSize;
} DH_OUT_WM_LOAD_COLLECTION;

// CLIENT_SaveMonitorWallCollection�ӿ��������(�������ǽԤ��)
typedef struct tagDH_IN_WM_SAVE_COLLECTION 
{
	DWORD				dwSize;
	int					nMonitorWallID;				// ����ǽ���
	const char*			pszName;					// Ԥ������
} DH_IN_WM_SAVE_COLLECTION;

// CLIENT_SaveMonitorWallCollection�ӿ��������(�������ǽԤ��)
typedef struct tagDH_OUT_WM_SAVE_COLLECTION 
{
	DWORD				dwSize;
} DH_OUT_WM_SAVE_COLLECTION;

// CLIENT_RenameMonitorWallCollection�ӿ��������(Ԥ��������)
typedef struct tagDH_IN_WM_RENAME_COLLECTION 
{
	DWORD				dwSize;
	int					nMonitorWallID;				// ����ǽ���
	const char*			pszOldName;					// ԭ����
	const char*			pszNewName;					// ������
} DH_IN_WM_RENAME_COLLECTION;

// CLIENT_RenameMonitorWallCollection�ӿ��������(Ԥ��������)
typedef struct tagDH_OUT_WM_RENAME_COLLECTION
{
	DWORD				dwSize;
} DH_OUT_WM_RENAME_COLLECTION;

// ���鴰����Ϣ
typedef struct tagDH_WINDOW_COLLECTION
{
	DWORD				dwSize;
	int					nWindowID;					// ����ID
	BOOL				bWndEnable;					// �����Ƿ���Ч
	DH_RECT				stuRect;					// ��������, ���ɷָ�ģʽ����Ч
	BOOL				bDirectable;				// �����Ƿ�����ֱͨ����
	int					nZOrder;					// ����Z����
	BOOL				bSrcEnable;					// ��ʾԴ�Ƿ���Ч
	char				szDeviceID[DH_DEV_ID_LEN_EX]; // �豸ID
	int					nVideoChannel;				// ��Ƶͨ����
	int					nVideoStream;				// ��Ƶ��������
	int					nAudioChannel;				// ��Ƶͨ��
	int					nAudioStream;				// ��Ƶ��������
	int					nUniqueChannel;				// �豸��ͳһ��ŵ�Ψһͨ����
} DH_WINDOW_COLLECTION;

// �����ղ�
typedef struct tagDH_BLOCK_COLLECTION 
{
	DWORD				dwSize;
	DH_SPLIT_MODE		emSplitMode;				// �ָ�ģʽ
	DH_WINDOW_COLLECTION stuWnds[DH_MAX_SPLIT_WINDOW];// ������Ϣ����
	int					nWndsCount;					// ��������
	char				szName[DH_DEVICE_NAME_LEN];	// �ղؼ�����
} DH_BLOCK_COLLECTION;

// ����ǽԤ��
typedef struct tagDH_MONITORWALL_COLLECTION 
{
	DWORD				dwSize;
	char				szName[DH_DEVICE_NAME_LEN];	// ����ǽԤ������
	DH_BLOCK_COLLECTION	stuBlocks[DH_MAX_BLOCK_NUM];// ��������
	int					nBlocksCount;				// ��������
	char				szControlID[DH_DEV_ID_LEN_EX];	// ����ID
} DH_MONITORWALL_COLLECTION;

// CLIENT_GetMonitorWallCollections�ӿ��������(��ȡ����ǽԤ����Ϣ)
typedef struct tagDH_IN_WM_GET_COLLECTIONS 
{
	DWORD				dwSize;
	int					nMonitorWallID;				// ����ǽID
} DH_IN_WM_GET_COLLECTIONS;

// CLIENT_GetMonitorWallCollections�ӿ��������(��ȡ����ǽԤ����Ϣ)
typedef struct tagDH_OUT_WM_GET_COLLECTIONS 
{
	DWORD				dwSize;	
	DH_MONITORWALL_COLLECTION* pCollections;		// ����ǽԤ������
	int					nMaxCollectionsCount;		// ����ǽԤ�������С
	int					nCollectionsCount;			// ����ǽԤ������
} DH_OUT_WM_GET_COLLECTIONS;

// CLIENT_GetSplitWindowsInfo�ӿ��������
typedef struct tagDH_IN_SPLIT_GET_WINDOWS 
{
	DWORD				dwSize;
	int					nChannel;					// ͨ����
} DH_IN_SPLIT_GET_WINDOWS;

// CLIENT_GetSplitWindowsInfo�ӿ��������
typedef struct tagDH_OUT_SPLIT_GET_WINDOWS 
{
	DWORD				dwSize;
	DH_BLOCK_COLLECTION	stuWindows;					// ������Ϣ
} DH_OUT_SPLIT_GET_WINDOWS;

// CLIENT_LoadSplitCollection�ӿ��������(�����ղ�)
typedef struct tagDH_IN_SPLIT_LOAD_COLLECTION 
{
	DWORD				dwSize;
	int					nChannel;					// ���ͨ����
	const char*			pszName;					// �ղؼ�����
} DH_IN_SPLIT_LOAD_COLLECTION;

// CLIENT_LoadSplitCollection�ӿ��������(�����ղ�)
typedef struct tagDH_OUT_SPLIT_LOAD_COLLECTION 
{
	DWORD				dwSize;
} DH_OUT_SPLIT_LOAD_COLLECTION;

// CLIENT_SaveSplitCollection�ӿ��������(�����ղ�)
typedef struct tagDH_IN_SPLIT_SAVE_COLLECTION 
{
	DWORD				dwSize;
	int					nChannel;					// ���ͨ����
	const char*			pszName;					// �ղؼ�����
} DH_IN_SPLIT_SAVE_COLLECTION;

// CLIENT_SaveSplitCollection�ӿ��������(�����ղ�)
typedef struct tagDH_OUT_SPLIT_SAVE_COLLECTION 
{
	DWORD				dwSize;
} DH_OUT_SPLIT_SAVE_COLLECTION;

// CLIENT_RenameSplitCollection�ӿ��������(�ղ�������)
typedef struct tagDH_IN_SPLIT_RENAME_COLLECTION 
{
	DWORD				dwSize;
	int					nChannel;					// ���ͨ����
	const char*			pszOldName;					// ԭ����
	const char*			pszNewName;					// ������
} DH_IN_SPLIT_RENAME_COLLECTION;

// CLIENT_RenameSplitCollection�ӿ��������(�ղ�������)
typedef struct tagDH_OUT_SPLIT_RENAME_COLLECTION
{
	DWORD				dwSize;
} DH_OUT_SPLIT_RENAME_COLLECTION;

// CLIENT_GetSplitCollections�ӿ��������(��ȡ�ղؼ���Ϣ)
typedef struct tagDH_IN_SPLIT_GET_COLLECTIONS 
{
	DWORD				dwSize;
	int					nChannel;					// ���ͨ����
} DH_IN_SPLIT_GET_COLLECTIONS;

// CLIENT_GetSplitCollections�ӿ��������(��ȡ�ղؼ���Ϣ)
typedef struct tagDH_OUT_SPLIT_GET_COLLECTIONS 
{
	DWORD				dwSize;	
	DH_BLOCK_COLLECTION* pCollections;				// �ղؼ�����
	int					nMaxCollectionsCount;		// �ղؼ������С
	int					nCollectionsCount;			// ���ص��ղؼ�����
} DH_OUT_SPLIT_GET_COLLECTIONS;

// CLIENT_DeleteSplitCollection�ӿڵ��������(ɾ���ղؼ�)
typedef struct tagDH_IN_SPLIT_DELETE_COLLECTION 
{
	DWORD				dwSize;
	int					nChannel;					// ���ͨ����
	const char**		ppszNames;					// �ղؼ���������
	int					nNameCount;					// �ղؼ����������С
} DH_IN_SPLIT_DELETE_COLLECTION;

// CLIENT_DeleteSplitCollection�ӿڵ��������(ɾ���ղؼ�)
typedef struct tagDH_OUT_SPLIT_DELETE_COLLECTION 
{
	DWORD				dwSize;
} DH_OUT_SPLIT_DELETE_COLLECTION;

// �ں���ͨ����Ϣ
typedef struct tagDH_COMPOSITE_CHANNEL
{
	DWORD				dwSize;
	char				szMonitorWallName[DH_DEVICE_NAME_LEN];	// ����ǽ����
	char				szCompositeID[DH_DEV_ID_LEN_EX];		// �ں���ID
	int					nVirtualChannel;						// ����ͨ����
} DH_COMPOSITE_CHANNEL;

// ��Ѳʹ������
typedef struct tagDHDEV_TOUR_ENABLE
{
	DWORD				dwSize;
	BOOL				bEnable;					// ��Ѳʹ��
	BOOL				bStart;						// �Ƿ�������Ѳ(ֻ��). ��Ѳʹ�ܴ򿪵�û��������Ѳ����Դʱ, bStart=FALSE
} DHDEV_TOUR_ENABLE_CFG;

// CLIENT_SetDecodePolicy�ӿ��������(���ý������)
typedef struct tagDH_IN_SET_DEC_POLICY 
{
	DWORD				dwSize;
	int					nChannel;			// ͨ����
	int					nWindow;			// ���ں�, -1��ʾͨ�������д���
	int					nPolicyLevel;		// ������Եȼ�, ��5��(-2, -1, 0, 1, 2), ֵԽ��Խ�������ӳ�Խ��
											// -2��ʾʵʱ�����, 2��ʾ���������, 0Ĭ��
} DH_IN_SET_DEC_POLICY;

// CLIENT_SetDecodePolicy�ӿ��������(���ý������)
typedef struct tagDH_OUT_SET_DEC_POLICY 
{
	DWORD				dwSize;
} DH_OUT_SET_DEC_POLICY;

// CLIENT_GetDecodePolicy�ӿ��������(��ȡ�������)
typedef struct tagDH_IN_GET_DEC_POLICY 
{
	DWORD				dwSize;
	int					nChannel;			// ͨ����
	int					nWindow;			// ���ں�, -1��ʾͨ�������д���
} DH_IN_GET_DEC_POLICY;

// CLIENT_GetDecodePolicy�ӿ��������(��ȡ�������)
typedef struct tagDH_OUT_GET_DEC_POLICY 
{
	DWORD				dwSize;
	int					nPolicyLevel;		// ������Եȼ�, ��5��(-2, -1, 0, 1, 2), ֵԽ��Խ�������ӳ�Խ��
											// -2��ʾʵʱ�����, 2��ʾ���������, 0Ĭ��
} DH_OUT_GET_DEC_POLICY;

// ��Ƶ���ģʽ
typedef enum
{
	DH_AUDIO_AUTO,							// �Զ��л���Ƶ���
	DH_AUDIO_DISABLE,						// ��ֹ������Ƶ��� 
	DH_AUDIO_FORCE,							// ǿ������û�ָ����ĳ�����ڵ���Ƶ
} DH_AUDIO_OUTPUT_MODE;

// CLIENT_SetSplitAudioOuput�ӿ��������(������Ƶ���ģʽ)
typedef struct tagDH_IN_SET_AUDIO_OUTPUT 
{
	DWORD				dwSize;
	int					nChannel;			// ͨ����
	DH_AUDIO_OUTPUT_MODE emMode;			// ��Ƶ���ģʽ
	int					nWindow;			// ������ں�, emModeΪDH_AUDIO_FORCEʱ��Ч
} DH_IN_SET_AUDIO_OUTPUT;

// CLIENT_SetSplitAudioOuput�ӿ��������(������Ƶ���ģʽ)
typedef struct tagDH_OUT_SET_AUDIO_OUTPUT
{
	DWORD				dwSize;
} DH_OUT_SET_AUDIO_OUTPUT;

// CLIENT_GetSplitAudioOuput�ӿ��������(��ȡ��Ƶ���ģʽ)
typedef struct tagDH_IN_GET_AUDIO_OUTPUT
{
	DWORD				dwSize;
	int					nChannel;			// ͨ����
} DH_IN_GET_AUDIO_OUTPUT;

// CLIENT_GetSplitAudioOuput�ӿ��������(��ȡ��Ƶ���ģʽ)
typedef struct tagDH_OUT_GET_AUDIO_OUTPUT
{
	DWORD				dwSize;
	DH_AUDIO_OUTPUT_MODE emMode;			// ��Ƶ���ģʽ
	int					nWindow;			// ������ں�, emModeΪDH_AUDIO_FORCEʱ��Ч
} DH_OUT_GET_AUDIO_OUTPUT;

// CLIENT_GetEncodePlan �ӿ��������(��ȡ��¼����ʱʹ�õı������)
typedef struct tagDH_IN_GET_ENCODE_PLAN
{
	DWORD				dwSize;
	unsigned int        nChannel;          // ָ��Ҫ��ȡ�ı���ͨ����
	unsigned int        nExpectTime;       // ҵ��Ԥ��ʱ��	 ����,��λ������
	unsigned int        nCapacity;         // ���õ��豸����,����,��λ:M
}DH_IN_GET_ENCODE_PLAN;
// CLIENT_GetEncodePlan �ӿ��������(��ȡ��¼����ʱʹ�õı������)
typedef struct tagDH_OUT_GET_ENCODE_PLAN
{
	DWORD				dwSize;
	int                 nResolutionType;    // emResolutionTypes��Ա���� 
	CAPTURE_SIZE        emResolutionTypes[DH_MAX_CAPTURE_SIZE_NUM];// ��Ƶ�ֱ��ʷ�Χ
	CAPTURE_SIZE        emResolution;       // �Ƽ���Ƶ�ֱ���
	unsigned int        nBitRate;           // ��Ƶ�̶�����ֵ
}DH_OUT_GET_ENCODE_PLAN;

// ��֯Ŀ¼�߼�����
typedef struct tagDH_ORGANIZATION_NODE_LOGIC_OBJECT 
{
	DWORD				dwSize;
	char				szName[DH_NODE_NAME_LEN];	// ����
	char				szType[DH_DEV_TYPE_LEN];	// ����
	char				szDevID[DH_DEV_ID_LEN_EX];	// �豸ID
	char				szControlID[DH_DEV_ID_LEN_EX]; // ����ID, ֻ��
	int					nChannel;					// ͨ����
} DH_ORGANIZATION_NODE_LOGIC_OBJECT;

// ��֯Ŀ¼
typedef struct tagDH_ORGANIZATION_NODE_DIRECTORY
{
	DWORD				dwSize;
	char				szName[DH_NODE_NAME_LEN];		// ����
	char				szControlID[DH_DEV_ID_LEN_EX];	// ����ID
} DH_ORGANIZATION_NODE_DIRECTORY;

// ��֯Ŀ¼�ڵ���Ϣ
typedef struct tagDH_ORGANIZATION_NODE 
{
	DWORD				dwSize;
	int					nNodeType;						// �ڵ�����, 0-�߼�����, 1-Ŀ¼
	DH_ORGANIZATION_NODE_LOGIC_OBJECT	stuLogicObject;	// �߼�����, nNodeType==0ʱ��Ч
	DH_ORGANIZATION_NODE_DIRECTORY		stuDirectory;	// Ŀ¼, nNodeType==1ʱ��Ч		
} DH_ORGANIZATION_NODE;

// ���ӽڵ����
typedef struct tagDH_ORGANIZATION_ADD_NODE_PARAM
{
	DWORD				dwSize;
	int					nPosition;					// ����λ��, -1-��ʼ, -2-ĩβ, 0~n
	DH_ORGANIZATION_NODE stuNode;					// �ڵ���Ϣ
} DH_ORGANIZATION_ADD_NODE_PARAM;

// CLIENT_OrganizationAddNodes�ӿڵ��������(���ӽڵ�)
typedef struct tagDH_IN_ORGANIZATION_ADD_NODES
{
	DWORD				dwSize;
	char*				pszPath;					// ·��
	DH_ORGANIZATION_ADD_NODE_PARAM* pstuNodes;		// �ڵ���Ϣ����ָ��
	int					nNodeCount;					// �ڵ�����
} DH_IN_ORGANIZATION_ADD_NODES;

// ���ӽڵ�Ľ��
typedef struct tagDH_ORGANIZATION_ADD_NODE_RESULT
{
	DWORD				dwSize;
	BOOL				bResult;					// ���
	char				szPath[MAX_PATH];			// ·��, �ɹ�����node·����ʧ�ܷ�������nodeʱ��·��
} DH_ORGANIZATION_ADD_NODE_RESULT;

// CLIENT_OrganizationAddNodes�ӿڵ��������(���ӽڵ�)
typedef struct tagDH_OUT_ORGANIZATION_ADD_NODES
{
	DWORD				dwSize;
	DH_ORGANIZATION_ADD_NODE_RESULT* pstuResults;	// �������ָ��
	int					nMaxResultCount;			// ��������С
	int					nRetResultCount;			// ���صĽ������
} DH_OUT_ORGANIZATION_ADD_NODES;

// �ڵ�·��
typedef struct tagDH_ORGANIZATION_NODE_PATH 
{
	DWORD				dwSize;
	char				szPath[MAX_PATH];			// ·��
} DH_ORGANIZATION_NODE_PATH;

// CLIENT_OrganizationDeleteNodes�ӿڵ��������(ɾ���ڵ�)
typedef struct tagDH_IN_ORGANIZATION_DELETE_NODES
{
	DWORD				dwSize;
	DH_ORGANIZATION_NODE_PATH*	pstuPath;			// �ڵ�·������
	int					nPathCount;					// �ڵ�����
} DH_IN_ORGANIZATION_DELETE_NODES;

// CLIENT_OrganizationDeleteNodes�ӿڵ��������(ɾ���ڵ�)
typedef struct tagDH_OUT_ORGANIZATION_DELETE_NODES 
{
	DWORD				dwSize;
} DH_OUT_ORGANIZATION_DELETE_NODES;

// CLIENT_OrganizationGetNodes�ӿڵ��������(��ȡ�ڵ���Ϣ)
typedef struct tagDH_IN_ORGANIZATION_GET_NODES 
{
	DWORD				dwSize;
	char*				pszPath;					// ·��
	int					nLevel;						// ����, 0-����, 1-��һ��
} DH_IN_ORGANIZATION_GET_NODES;

// CLIENT_OrganizationGetNodes�ӿڵ��������(��ȡ�ڵ���Ϣ)
typedef struct tagDH_OUT_ORGANIZATION_GET_NODES 
{
	DWORD				dwSize;
	DH_ORGANIZATION_NODE*	pstuNodes;				// �ڵ�����, �û������ڴ�
	int					nMaxNodeCount;				// �ڵ������С
	int					nRetNodeCount;				// ���صĽڵ�����
} DH_OUT_ORGANIZATION_GET_NODES;

// CLIENT_OrganizationSetNode�ӿڵ��������(���ýڵ�)
typedef struct tagDH_IN_ORGANIZATION_SET_NODE 
{
	DWORD				dwSize;
	char*				pszPath;					// ·��
	DH_ORGANIZATION_NODE stuNode;					// �ڵ���Ϣ
} DH_IN_ORGANIZATION_SET_NODE;

// CLIENT_OrganizationSetNode�ӿڵ��������(���ýڵ�)
typedef struct tagDH_OUT_ORGANIZATION_SET_NODE 
{
	DWORD				dwSize;
} DH_OUT_ORGANIZATION_SET_NODE;

// ��Ƶ����ͨ����Ϣ
typedef struct tagDH_VIDEO_INPUTS
{
	DWORD				dwSize;
	char				szChnName[DH_DEVICE_NAME_LEN];		// ͨ������
	BOOL				bEnable;							// ʹ��
	char				szControlID[DH_DEV_ID_LEN_EX];		// ����ID
	char				szMainStreamUrl[MAX_PATH];			// ������url��ַ 
	char				szExtraStreamUrl[MAX_PATH];			// ������url��ַ
} DH_VIDEO_INPUTS;

typedef struct tagDH_REMOTE_DEVICE 
{
	DWORD				dwSize;
	BOOL				bEnable;							// ʹ��
	char			    szIp[DH_MAX_IPADDR_LEN];		    // IP
	char			    szUser[DH_USER_NAME_LENGTH];	    // �û���
	char			    szPwd[DH_USER_PSW_LENGTH];	    	// ����
	int			    	nPort;							    // �˿�
	int				    nDefinition;					    // ������, 0-����, 1-����
	DH_DEVICE_PROTOCOL  emProtocol;							// Э������
	char			    szDevName[DH_DEVICE_NAME_LEN];		// �豸����
	int					nVideoInputChannels;				// ��Ƶ����ͨ����
	int					nAudioInputChannels;				// ��Ƶ����ͨ����
	char				szDevClass[DH_DEV_TYPE_LEN];		// �豸����, ��IPC, DVR, NVR��
	char				szDevType[DH_DEV_TYPE_LEN];			// �豸�����ͺ�, ��IPC-HF3300
	int					nHttpPort;							// Http�˿�
	int					nMaxVideoInputCount;				// ��Ƶ����ͨ�������
	int					nRetVideoInputCount;				// ����ʵ��ͨ������
	DH_VIDEO_INPUTS*	pstuVideoInputs;					// ��Ƶ����ͨ����Ϣ
	char				szMachineAddress[DH_MAX_CARD_INFO_LEN];	// �豸�����
	char				szSerialNo[DH_SERIALNO_LEN];		// �豸���к�
} DH_REMOTE_DEVICE;

// ���õ���ʾԴ��Ϣ
typedef struct tagDH_MATRIX_CAMERA_INFO
{
	DWORD				dwSize;
	char				szName[DH_DEV_ID_LEN_EX];		// ����
	char				szDevID[DH_DEV_ID_LEN_EX];		// �豸ID
	char				szControlID[DH_DEV_ID_LEN_EX];	// ����ID
	int					nChannelID;						// ͨ����, DeviceID�豸��Ψһ
	int					nUniqueChannel;					// �豸��ͳһ��ŵ�Ψһͨ����
	BOOL				bRemoteDevice;					// �Ƿ�Զ���豸
	DH_REMOTE_DEVICE	stuRemoteDevice;				// Զ���豸��Ϣ
	NET_STREAM_TYPE     emStreamType;                   // ��Ƶ��������
} DH_MATRIX_CAMERA_INFO;

// CLIENT_MatrixGetCameras�ӿڵ��������
typedef struct tagDH_IN_MATRIX_GET_CAMERAS 
{
	DWORD				dwSize;
} DH_IN_MATRIX_GET_CAMERAS;

// CLIENT_MatrixGetCameras�ӿڵ��������
typedef struct tagDH_OUT_MATRIX_GET_CAMERAS 
{
	DWORD				dwSize;
	DH_MATRIX_CAMERA_INFO* pstuCameras;					// ��ʾԴ��Ϣ����, �û������ڴ�
	int					nMaxCameraCount;				// ��ʾԴ�����С
	int					nRetCameraCount;				// ���ص���ʾԴ����
} DH_OUT_MATRIX_GET_CAMERAS;

// CLIENT_MatrixSetCameras�ӿڵ��������
typedef struct tagDH_IN_MATRIX_SET_CAMERAS 
{
	DWORD				dwSize;
	DH_MATRIX_CAMERA_INFO* pstuCameras;					// ��ʾԴ��Ϣ����, �û������ڴ�
	int					nCameraCount;				    // ��ʾԴ�����С
} DH_IN_MATRIX_SET_CAMERAS;

// CLIENT_MatrixSetCameras�ӿڵ��������
typedef struct tagDH_OUT_MATRIX_SET_CAMERAS 
{
	DWORD				dwSize;
} DH_OUT_MATRIX_SET_CAMERAS;

// ����ǽ��ʾ��Ԫ
typedef struct tagDH_MONITORWALL_OUTPUT 
{
	DWORD				dwSize;
	char				szDeviceID[DH_DEV_ID_LEN];		// �豸ID, ����ʱΪ""
	int					nChannel;						// ͨ����
	char				szName[DH_DEV_NAME_LEN];		// ��Ļ����
} DH_MONITORWALL_OUTPUT;

// ����ǽ��ʾ����
typedef struct tagDH_MONITORWALL_BLOCK
{
	DWORD				dwSize;
	char				szName[DH_DEV_NAME_LEN];		// ��������
	char				szCompositeID[DH_DEV_ID_LEN];	// ƴ����ID
	char				szControlID[DH_DEV_ID_LEN];		// ����ID
	int					nSingleOutputWidth;				// ������ʾ��Ԫ��ռ����������
	int					nSingleOutputHeight;			// ������ʾ��Ԫ��ռ����������
	DH_RECT				stuRect;						// ��������
	DH_TSECT			stuPowerSchedule[DH_TSCHE_DAY_NUM][DH_TSCHE_SEC_NUM];	// ����ʱ���, ��һά��Ԫ�ر�ʾ����~�����ͽڼ���
	DH_MONITORWALL_OUTPUT* pstuOutputs;					// ��ʾ��Ԫ����, �û������ڴ�
	int					nMaxOutputCount;				// ��ʾ��Ԫ�����С, �û���д
	int					nRetOutputCount;				// ���ص���ʾ��Ԫ����
} DH_MONITORWALL_BLOCK;

// ����ǽ����
typedef struct tagDH_MONITORWALL 
{
	DWORD				dwSize;
	char				szName[DH_DEV_NAME_LEN];		// ����
	int					nGridLine;						// ��������
	int					nGridColume;					// ��������
	DH_MONITORWALL_BLOCK* pstuBlocks;					// ��ʾ��������, �û������ڴ�
	int					nMaxBlockCount;					// ��ʾ���������С, �û���д
	int					nRetBlockCount;					// ���ص���ʾ��������
} DH_MONITORWALL;

// ������ʾԴ��Ϣ
typedef struct tagDH_SPLIT_WND_SOURCE 
{
	DWORD				dwSize;
	BOOL				bEnable;						// ��ʾԴ�Ƿ���Ч
	char				szDeviceID[DH_DEV_ID_LEN];		// �豸ID
	char				szControlID[DH_DEV_ID_LEN];		// ����ID
	int					nVideoChannel;					// ��Ƶͨ����
	int					nVideoStream;					// ��Ƶ��������
	int					nAudioChannel;					// ��Ƶͨ��
	int					nAudioStream;					// ��Ƶ��������
	int					nUniqueChannel;					// �豸��ͳһ��ŵ�Ψһͨ����, ֻ��
	BOOL				bRemoteDevice;					// �Ƿ�Զ���豸
	DH_REMOTE_DEVICE	stuRemoteDevice;				// Զ���豸��Ϣ
} DH_SPLIT_WND_SOURCE;

// �ָ����Ϣ
typedef struct tagDH_SPLIT_WINDOW 
{
	DWORD				dwSize;
	BOOL				bEnable;						// �����Ƿ�����ƵԴ
	int					nWindowID;						// ����ID
	char				szControlID[DH_DEV_ID_LEN];		// ����ID
	DH_RECT				stuRect;						// ��������, ���ɷָ�ģʽ����Ч
	BOOL				bDirectable;					// �����Ƿ�����ֱͨ����
	int					nZOrder;						// ����Z����
	DH_SPLIT_WND_SOURCE stuSource;						// ��ʾ��Ϣ
} DH_SPLIT_WINDOW;

// ƴ��������
typedef struct tagDH_SPLIT_SCENE 
{
	DWORD				dwSize;
	char				szCompositeID[DH_DEV_ID_LEN];	// ƴ����ID
	char				szControlID[DH_DEV_ID_LEN];		// ����ID
	DH_SPLIT_MODE		emSplitMode;					// �ָ�ģʽ
	DH_SPLIT_WINDOW*	pstuWnds;						// ������Ϣ����, �û������ڴ�
	int					nMaxWndCount;					// ������Ϣ�����С, �û���д
	int					nRetWndCount;					// ���صĴ�������
} DH_SPLIT_SCENE;

// ����ǽ����
typedef struct tagDH_MONITORWALL_SCENE
{
	DWORD				dwSize;
	char				szName[DH_DEV_NAME_LEN];		// ��ǰԤ������
	char				szControlID[DH_DEV_ID_LEN];		// ����ID
	DH_MONITORWALL		stuMonitorWall;					// ����ǽ����	
	DH_SPLIT_SCENE*		pstuSplitScene;					// ƴ����������Ϣ����, �û������ڴ�
	int					nMaxSplitSceneCount;			// ƴ�������������С, �û���д
	int					nRetSplitSceneCount;			// ���ص�ƴ������������
} DH_MONITORWALL_SCENE;

// CLIENT_MonitorWallGetScene�ӿ��������(��ȡ����ǽ����)
typedef struct tagDH_IN_MONITORWALL_GET_SCENE 
{
	DWORD				dwSize;
	int					nMonitorWallID;					// ����ǽ���
} DH_IN_MONITORWALL_GET_SCENE;

// CLIENT_MonitorWallGetScene�ӿ��������(��ȡ����ǽ����)
typedef struct tagDH_OUT_MONITORWALL_GET_SCENE 
{
	DWORD				dwSize;
	char				szName[DH_DEV_NAME_LEN];		// ��ǰԤ������, ����Ϊ��
	DH_MONITORWALL_SCENE stuScene;						// ����ǽ����
} DH_OUT_MONITORWALL_GET_SCENE;

// CLIENT_MonitorWallSetScene�ӿ��������(���õ���ǽ����)
typedef struct tagDH_IN_MONITORWALL_SET_SCENE 
{
	DWORD				dwSize;
	int					nMonitorWallID;					// ����ǽ���
	DH_MONITORWALL_SCENE stuScene;						// ����ǽ����
} DH_IN_MONITORWALL_SET_SCENE;

// CLIENT_MonitorWallSetScene�ӿ��������(���õ���ǽ����)
typedef struct tagDH_OUT_MONITORWALL_SET_SCENE 
{
	DWORD				dwSize;
} DH_OUT_MONITORWALL_SET_SCENE;

// �����ź�����
#define DH_VIDEO_SIGNAL_CVBS	0x0001
#define DH_VIDEO_SIGNAL_SDI		0x0002
#define DH_VIDEO_SIGNAL_VGA		0x0004 
#define DH_VIDEO_SIGNAL_DVI		0x0008
#define DH_VIDEO_SIGNAL_HDMI	0x0010 
#define DH_VIDEO_SIGNAL_YPBPR	0x0020 
#define DH_VIDEO_SIGNAL_SFP		0x0040 

// ��Ƶ����������
typedef struct tagDH_VIDEO_IN_CAPS 
{
	DWORD					dwSize;
	DWORD					dwSignalType;				// �����ź�����
	BOOL					bAutoFocusPeak;				// �Ƿ�֧�־۽���ֵ����
	BOOL					bElectricFocus;				// �Ƿ�֧�ֵ綯����
	BOOL					bSyncFocus;					// �Ƿ�֧��ͬ���Խ�
} DH_VIDEO_IN_CAPS;

// CLIENT_GetVideoInCaps�ӿ��������
typedef struct tagDH_IN_GET_VIDEO_IN_CAPS 
{
	DWORD			dwSize;
	int				nChannel;							// ��Ƶ����ͨ����
} DH_IN_GET_VIDEO_IN_CAPS;

// CLIENT_GetVideoInCaps�ӿ��������
typedef struct tagDH_OUT_GET_VIDEO_IN_CAPS 
{
	DWORD			dwSize;
	DH_VIDEO_IN_CAPS stuCaps;							// ����
} DH_OUT_GET_VIDEO_IN_CAPS;

// ��Ƶ���ģʽ
typedef struct tagDH_VIDEO_OUT_MODE 
{
	DWORD			dwSize;
	int				nWidth;								// ˮƽ�ֱ���
	int				nHeight;							// ��ֱ�ֱ���
	int				nBPP;								// ��ɫ���
	int				nFormat;							// ����ź�ģʽ, 0-Auto, 1-TV, 2-VGA, 3-DVI
	int				nRefreshRate;						// ˢ��Ƶ��
	int				nPhysicalPort;						// ���������, VGA, TV, DVI���Զ������, ���Դ�0��ʼ
} DH_VIDEO_OUT_MODE;

// CLIENT_EnumVideoOutModes�ӿ��������
typedef struct tagDH_IN_ENUM_VIDEO_OUT_MODES 
{
	DWORD			dwSize;
	int				nChannel;
} DH_IN_ENUM_VIDEO_OUT_MODES;

// CLIENT_EnumVideoOutModes�ӿ��������
typedef struct tagDH_OUT_ENUM_VIDEO_OUT_MODES 
{
	DWORD			dwSize;
	DH_VIDEO_OUT_MODE* pstuModes;						// ģʽ����, �û������ڴ�
	int				nMaxModeCount;						// ģʽ�����С, �û���д
	int				nRetModeCount;						// ���ص�ģʽ����
} DH_OUT_ENUM_VIDEO_OUT_MODES;

// ����ǽ��Ļ��������
typedef enum tagDH_OUTPUT_ATTRIBUTE_TYPE
{
	DH_OUTPUT_ATTRIBUTE_VIDEO, 
	DH_OUTPUT_ATTRIBUTE_YPBPR, 
	DH_OUTPUT_ATTRIBUTE_VGA, 
	DH_OUTPUT_ATTRIBUTE_DVI, 
	DH_OUTPUT_ATTRIBUTE_MENU, 
} DH_OUTPUT_ATTRIBUTE_TYPE;

// ����ǽ��ʾ��Ԫ��Ļ����������(DH_OUTPUT_ATTRIBUTE_CAPS) Video����
#define	DH_ATTR_VIDEO_BRIGHTNESS	0X00000001
#define	DH_ATTR_VIDEO_CONTRAST		0X00000002
#define	DH_ATTR_VIDEO_SATURATION	0X00000004
#define	DH_ATTR_VIDEO_SHAPENESS		0X00000008
#define	DH_ATTR_VIDEO_DENOISE		0X00000010

// ����ǽ��ʾ��Ԫ��Ļ����������(DH_OUTPUT_ATTRIBUTE_CAPS) YPbPr����
#define	DH_ATTR_YPBPR_BRIGHTNESS	0X00000001
#define	DH_ATTR_YPBPR_CONTRAST		0X00000002
#define	DH_ATTR_YPBPR_SATURATION	0X00000004
#define	DH_ATTR_YPBPR_SHAPENESS		0X00000008
#define	DH_ATTR_YPBPR_DENOISE		0X00000010

// ����ǽ��ʾ��Ԫ��Ļ����������(DH_OUTPUT_ATTRIBUTE_CAPS) VGA����
#define	DH_ATTR_VGA_BRIGHTNESS		0X00000001
#define	DH_ATTR_VGA_CONTRAST		0X00000002
#define	DH_ATTR_VGA_HORPOSITION		0X00000004
#define	DH_ATTR_VGA_VERPOSITION		0X00000008
#define	DH_ATTR_VGA_CLOCK			0X00000010

// ����ǽ��ʾ��Ԫ��Ļ����������(DH_OUTPUT_ATTRIBUTE_CAPS) DVI����
#define	DH_ATTR_DVI_BRIGHTNESS		0X00000001
#define	DH_ATTR_DVI_CONTRAST		0X00000002
#define	DH_ATTR_DVI_HORPOSITION		0X00000004
#define	DH_ATTR_DVI_VERPOSITION		0X00000008
#define	DH_ATTR_DVI_CLOCK			0X00000010

// ����ǽ��ʾ��Ԫ��Ļ����������(DH_OUTPUT_ATTRIBUTE_CAPS) Menu����
#define	DH_ATTR_MENU_MENU			0X00000001
#define	DH_ATTR_MENU_UP				0X00000002
#define	DH_ATTR_MENU_DOWN			0X00000004
#define	DH_ATTR_MENU_LEFT			0X00000008
#define	DH_ATTR_MENU_RIGHT			0X00000010
#define	DH_ATTR_MENU_FACTORYMENU	0X00000020

// ����ǽ��ʾ��Ԫ��Ļ����������
typedef struct tagDH_OUTPUT_ATTRIBUTE_CAPS
{
	DWORD			dwSize;
	BOOL			abVideo;			// Video�����Ƿ���Ч
	DWORD			dwVideo;			// Video����, ��λ��ʾ, �����DH_ATTR_VIDEO_BRIGHTNESS��
	BOOL			abYPbPr;			// YPbPr�����Ƿ���Ч
	DWORD			dwYPbPr;			// YPbPr����, ��λ��ʾ, �����DH_ATTR_VGA_BRIGHTNESS��
	BOOL			abVGA;				// VGA�����Ƿ���Ч
	DWORD			dwVGA;				// VGA����, ��λ��ʾ, �����DH_ATTR_VGA_BRIGHTNESS��
	BOOL			abDVI;				// DVI�����Ƿ���Ч
	DWORD			dwDVI;				// DVI����, ��λ��ʾ, �����DH_ATTR_DVI_BRIGHTNESS
	BOOL			abMenu;				// Menu�����Ƿ���Ч
	DWORD			dwMemu;				// Menu����, ��λ��ʾ, �����DH_ATTR_MENU_MENU��
} DH_OUTPUT_ATTRIBUTE_CAPS;

// CLIENT_MonitorWallGetAttributeCaps �ӿ��������
typedef struct tagDH_IN_MONITORWALL_GET_ARRT_CAPS
{
	DWORD			dwSize;
	int				nMonitorWallID;			// ����ǽ���
	const char*		pszCompositeID;			// ƴ����ID
	int				nOutputID;				// ��ʾ��Ԫ���
} DH_IN_MONITORWALL_GET_ARRT_CAPS;

// CLIENT_MonitorWallGetAttributeCaps �ӿ��������
typedef struct tagDH_OUT_MONITORWALL_GET_ARRT_CAPS
{
	DWORD			dwSize;
	DH_OUTPUT_ATTRIBUTE_CAPS stuCaps;		// ����������
} DH_OUT_MONITORWALL_GET_ARRT_CAPS;


// CLIENT_MonitorWallAutoAdjust �ӿ��������
typedef struct tagDH_IN_MONITORWALL_AUTO_ADJUST
{
	DWORD			dwSize;
	int				nMonitorWallID;			// ����ǽ���
	const char*		pszCompositeID;			// ƴ����ID
	int*			pOutputs;				// ��ʾ��Ԫ�������ָ��, ����Ԫ������ʾ��ԪID, �û������ڴ�
	int				nOutputCount;			// ��ʾ��Ԫ����, pOutputsԪ������
} DH_IN_MONITORWALL_AUTO_ADJUST;

// CLIENT_MonitorWallAutoAdjust �ӿ��������
typedef struct tagDH_OUT_MONITORWALL_AUTO_ADJUST
{
	DWORD			dwSize;
} DH_OUT_MONITORWALL_AUTO_ADJUST;

// ��ʾ��Ԫ���Լ�ֵ��
typedef struct tagDH_ATTR_PAIR
{
	DWORD	dwKey;					// ���Լ�
									// ����ΪDH_OUTPUT_ATTRIBUTE_VIDEOʱ, ʹ�ú�DH_ATTR_VIDEO_BRIGHTNESS��
									// ����ΪDH_OUTPUT_ATTRIBUTE_YPBPRʱ, ʹ�ú�DH_ATTR_YPBPR_BRIGHTNESS��
									// �����������Դ�����
	int		nValue;					// ����ֵ, 0-���� 1-����, 2-����
} DH_ATTR_PAIR;

// CLIENT_MonitorWallSetAttribute �ӿ��������
typedef struct tagDH_IN_MONITORWALL_SET_ATTR
{
	DWORD					dwSize;
	int						nMonitorWallID;					// ����ǽ���
	const char*				pszCompositeID;					// ƴ����ID
	int						nOutputID;						// ��ʾ��Ԫ���
	DH_OUTPUT_ATTRIBUTE_TYPE emAttrType;					// ��������, ���Ͳ�ͬʱ, ��Ӧ������(stuAttrs)Ҳ��ͬ
	DH_ATTR_PAIR			stuAttrs[DH_MAX_ATTR_NUM];		// ����ֵ
} DH_IN_MONITORWALL_SET_ATTR;

// CLIENT_MonitorWallSetAttribute �ӿ��������
typedef struct tagDH_OUT_MONITORWALL_SET_ATTR
{
	DWORD			dwSize;
} DH_OUT_MONITORWALL_SET_ATTR;

// CLIENT_MonitorWallSetBackLight �ӿ��������
typedef struct tagDH_IN_MONITORWALL_SET_BACK_LIGHT
{
	DWORD					dwSize;
	int						nMonitorWallID;					// ����ǽ���
	const char*				pszCompositeID;					// ƴ����ID
	int						nOutputID;						// ��ʾ��Ԫ���
	int						nMode;							// ����ģʽ, 0-ѭ�����ñ���ģʽ��1-��ѭ��ģʽ
} DH_IN_MONITORWALL_SET_BACK_LIGHT;

// CLIENT_MonitorWallSetBackLight �ӿ��������
typedef struct tagDH_OUT_MONITORWALL_SET_BACK_LIGHT
{
	DWORD			dwSize;
} DH_OUT_MONITORWALL_SET_BACK_LIGHT;

// CLIENT_StartSniffer �ӿ��������
typedef struct tagDH_IN_START_SNIFFER 
{
	DWORD		dwSize;
	const char*	pszNetInterface;				// ��������
	const char*	pszPath;						// ץ���洢�ļ���, �ձ�ʾ���浽Ĭ��·��
	int			nSaveType;						// �ļ�����, 0-Wireshark/Tcpdump
} DH_IN_START_SNIFFER;

// CLIENT_StartSniffer �ӿ��������
typedef struct tagDH_OUT_START_SNIFFER 
{
	DWORD		dwSize;
} DH_OUT_START_SNIFFER;

// ץ����Ϣ
typedef struct tagDH_SNIFFER_INFO
{
	DWORD		dwSize;
	DWORD		nSnifferID;					// ץ��ID
} DH_SNIFFER_INFO;

// CLIENT_GetSnifferInfo �ӿ��������
typedef struct tagDH_IN_GET_SNIFFER_INFO
{
	DWORD		dwSize;
	const char*	pszNetInterface;
} DH_IN_GET_SNIFFER_INFO;

// CLIENT_GetSnifferInfo �ӿ��������
typedef struct tagDH_OUT_GET_SNIFFER_INFO
{
	DWORD		dwSize;
	DH_SNIFFER_INFO	* pstuSniffers;			// ץ����Ϣ����, �û������ڴ�
	int			nMaxSnifferCount;			// ץ����Ϣ�����С, �û���д
	int			nRetSnifferCount;			// ���ص�ץ����Ϣ����
} DH_OUT_GET_SNIFFER_INFO;

// ��ʽ��������Ϣ
typedef struct tagDH_FORMAT_PATITION 
{
	DWORD			dwSize;
	const char*		pszStorageName;							// �洢�豸����
	const char*		pszPatitionName;						// ������
} DH_FORMAT_PATITION;

// CLIENT_CreateRemoteFile �ӿ��������
typedef struct tagDH_IN_CREATE_REMOTE_FILE
{
	DWORD			dwSize;
	const char*		pszPath;								// �ļ���
	BOOL			bDirectory;								// �Ƿ��ļ���
} DH_IN_CREATE_REMOTE_FILE;

// CLIENT_CreateRemoteFile �ӿ��������
typedef struct tagDH_OUT_CREATE_REMOTE_FILE 
{
	DWORD			dwSize;
} DH_OUT_CREATE_REMOTE_FILE;

// CLIENT_RemoveRemoteFiles �ӿ��������
typedef struct tagDH_IN_REMOVE_REMOTE_FILES
{
	DWORD			dwSize;
	const char**	pszPath;								// �ļ�·������ָ��
	int				nFileCount;								// �ļ�·������
} DH_IN_REMOVE_REMOTE_FILES;

// CLIENT_RemoveRemoteFiles �ӿ��������
typedef struct tagDH_OUT_REMOVE_REMOTE_FILES 
{
	DWORD		dwSize;
} DH_OUT_REMOVE_REMOTE_FILES;

// CLIENT_RenameRemoteFile �ӿ��������
typedef struct tagDH_IN_RENAME_REMOTE_FILE
{
	DWORD			dwSize;
	const char*		pszOldPath;								// ���ļ���
	const char*		pszNewPath;								// ���ļ���
} DH_IN_RENAME_REMOTE_FILE;

// CLIENT_RenameRemoteFile �ӿ��������
typedef struct tagDH_OUT_RENAME_REMOTE_FILE 
{
	DWORD			dwSize;
} DH_OUT_RENAME_REMOTE_FILE;

// �ļ�/Ŀ¼��Ϣ
typedef struct tagDH_REMOTE_FILE_INFO 
{
	DWORD			dwSize;
	BOOL			bDirectory;								// �Ƿ��ļ���
	char			szPath[MAX_PATH];						// ·��
	NET_TIME		stuCreateTime;							// ����ʱ��
	NET_TIME		stuModifyTime;							// �޸�ʱ��
	INT64			nFileSize;								// �ļ���С
	char			szFileType[DH_FILE_TYPE_LEN];			// �ļ�����
} DH_REMOTE_FILE_INFO;

// CLIENT_ListRemoteFile �ӿ��������
typedef struct tagDH_IN_LIST_REMOTE_FILE
{
	DWORD			dwSize;
	const char*		pszPath;								// ·��
	BOOL			bFileNameOnly;							// ֻ��ȡ�ļ�����, �������ļ�����Ϣ, �ļ���Ϣ��ֻ���ļ�����Ч
} DH_IN_LIST_REMOTE_FILE;

// CLIENT_ListRemoteFile �ӿ��������
typedef struct tagDH_OUT_LIST_REMOTE_FILE 
{
	DWORD			dwSize;
	DH_REMOTE_FILE_INFO*	pstuFiles;						// �ļ���Ϣ����, �û������ڴ�
	int						nMaxFileCount;					// �ļ���Ϣ�����С, �û���д
	int						nRetFileCount;					// ���ص��ļ�����
} DH_OUT_LIST_REMOTE_FILE;

// �ֶ������洢�豸
typedef struct tagDH_EJECT_STORAGE_DEVICE
{
	DWORD				dwSize;	
	const char*			pszStorageName;						// �洢�豸����
} DH_EJECT_STORAGE_DEVICE;

// �ֶ�װ�ش洢�豸
typedef struct tagDH_LOAD_STORAGE_DEVICE 
{
	DWORD				dwSize;
	const char*			pszStorageName;						// �洢�豸����
} DH_LOAD_STORAGE_DEVICE;

// CLIENT_UploadRemoteFile �ӿ��������(�ϴ��ļ����豸)
typedef struct tagDH_IN_UPLOAD_REMOTE_FILE
{
	DWORD					dwSize;
	const char*				pszFileSrc;			// Դ�ļ�·��
	const char*				pszFileDst;			// Ŀ���ļ�·��
} DH_IN_UPLOAD_REMOTE_FILE;

// CLIENT_UploadRemoteFile �ӿ��������(�ϴ��ļ����豸)
typedef struct tagDH_OUT_UPLOAD_REMOTE_FILE
{
	DWORD					dwSize;
} DH_OUT_UPLOAD_REMOTE_FILE;

// �����豸��������
typedef struct tagDH_IN_SEARCH_CONDITON
{
	DWORD					dwSize;
	const char*				pMachineName;					// �豸���ƻ���
	const char*				pMachineAddr;					// �豸����ص�(�磺������.���ϴ��.ΰҵ·��)
	const char*				pSerialNo;						// �豸���к�
	const char*				pChannelName;					// ��Ƶ����ͨ����
} DH_MATRIX_SEARCH_CONDITON;

// CLIENT_MatrixSearch �ӿ��������(���������豸)
typedef struct tagDH_IN_MATIRX_SEARCH
{
	DWORD					dwSize;
	const char*				pSerialNo;						// �����豸���к�,"Local"-���豸��"Root"-���豸�������豸���豸�����кű�ʾ
	DH_MATRIX_SEARCH_CONDITON stuCondition;					// ��������, ����Ϊ��һ���������
} DH_IN_MATRIX_SEARCH;

// CLIENT_MatrixSearch �ӿ��������(���������豸)
typedef struct tagDH_OUT_MATRIX_SEARCH
{
	DWORD					dwSize;
	DH_REMOTE_DEVICE*		pstuRemoteDevices;				// �豸�б�, �û������ڴ�
	int						nMaxDeviceCount;				// �豸�б����ֵ, �û���д
	int						nRetDeviceCount;				// ʵ�ʷ����豸����
} DH_OUT_MATRIX_SEARCH;

// CLIENT_GetMatrixTree �ӿ��������
typedef struct tagDH_IN_GET_MATRIX_TREE
{
	DWORD					dwSize;
	const char*				pSerialNo;						// �����豸���к�,"Local"-���豸��"Root"-���豸�������豸���豸�����кű�ʾ
	int						nLevel;							// ��ü����豸��Ϣ��0-�����豸����1-�����豸��2-�����豸+���豸������һ���豸��
															// 3-�����豸+���豸������һ���豸+��һ���豸����һ���豸
} DH_IN_GET_MATRIX_TREE;

// �����豸��Ϣ
typedef struct tagDH_CASCADE_DEVICE_INFO
{
	DWORD					dwSize;
	int						nLevel;							// ��ǰ�豸��������
	char					szPath[MAX_PATH];				// �豸����·������ʽ��name1.name2.name3...
	DH_REMOTE_DEVICE		stuDeviceInfo;					// �豸��ϸ��Ϣ
} DH_CASCADE_DEVICE_INFO;

// CLIENT_GetMatrixTree �ӿ��������
typedef struct tagDH_OUT_GET_MATRIX_TREE
{
	DWORD					dwSize;
	DH_CASCADE_DEVICE_INFO*	pstuRemoteDevices;				// �����豸��Ϣ
	int						nMaxDeviceCount;				// �����豸��Ϣ���ֵ
	int						nRetDeviceCount;				// ���ص�ʵ���豸����
} DH_OUT_GET_MATRIX_TREE;

// CLIENT_GetSuperiorMatrixList �ӿ��������
typedef struct tagDH_IN_GET_SUPERIOR_MATRIX_LIST
{
	DWORD					dwSize;
} DH_IN_GET_SUPERIOR_MATRIX_LIST;

// CLIENT_GetSuperiorMatrixList �ӿ��������
typedef struct tagDH_OUT_GET_SUPERIOR_MATRIX_LIST
{
	DWORD					dwSize;
	DH_REMOTE_DEVICE*		pstuRemoteDevices;				// �豸�б�, �û������ڴ�
	int						nMaxDeviceCount;				// �豸�б����ֵ, �û���д
	int						nRetDeviceCount;				// ʵ�ʷ����豸����
} DH_OUT_GET_SUPERIOR_MATRIX_LIST;

////////////////////////////////////¼�񱸷ݻָ�//////////////////////////////////////

// ¼�񱸷ݻָ�������Ϣ
typedef struct tagDH_RECORD_BACKUP_RESTORE_TASK
{
    DWORD				dwSize;
    unsigned int		nTaskID;                        // ����ID
    char				szDeviceID[DH_DEV_ID_LEN_EX];   // �豸ID
    int			        nChannelID;                     // ͨ����
    NET_TIME			stuStartTime;                   // ��ʼʱ��
    NET_TIME			stuEndTime;                     // ����ʱ��
    int			        nState;                         // ��ǰ����״̬, 0-�ȴ�, 1-������, 2-���, 3-ʧ��
} DH_REC_BAK_RST_TASK;

// CLIENT_AddRecordBackupRestoreTask�ӿ��������
typedef struct tagDH_IN_ADD_RECORD_BACKUP_RESTORE_TASK
{
    DWORD				dwSize;
    const char*			pszDeviceID;					// �豸ID
    int*		        pnChannels;						// ͨ������
	int					nChannelCount;					// ͨ�������С
    NET_TIME			stuStartTime;					// ��ʼʱ��
    NET_TIME			stuEndTime;						// ����ʱ��
} DH_IN_ADD_REC_BAK_RST_TASK;

// CLIENT_RemoveRecordBackupRestoreTask�ӿ��������
typedef struct tagDH_IN_REMOVE_RECORD_BACKUP_RESTORE_TASK
{
    DWORD				dwSize;
    unsigned int*		pnTaskIDs;						// ����ID����
	int					nTaskCount;						// ��������
} DH_IN_REMOVE_REC_BAK_RST_TASK;

// CLIENT_QueryRecordBackupRestoreTask�ӿ��������
typedef struct tagDH_IN_QUERY_RECORD_BACKUP_RESTORE_TASK
{
    DWORD		        dwSize;
} DH_IN_QUERY_REC_BAK_RST_TASK;

// CLIENT_QueryRecordBackupRestoreTask�ӿ��������
typedef struct tagDH_OUT_QUERY_RECORD_BACKUP_RESTORE_TASK
{
    DWORD				 dwSize;
    DH_REC_BAK_RST_TASK* pTasks;						// ��������
    int					 nMaxCount;						// �����С
    int					 nReturnCount;					// ���ص���������
} DH_OUT_QUERY_REC_BAK_RST_TASK;

typedef struct tagDH_LOGIC_DEVICE_ADD_CAMERA_PARAM
{
	DWORD			dwSize;
	const char*		pszDeviceID;			// �豸ID
	int				nChannel;				// ͨ����
} DH_LOGIC_DEVICE_ADD_CAMERA_PARAM;

typedef struct tagDH_LOGIC_DEVICE_ADD_CAMERA_RESULT
{
	DWORD			dwSize;
	char			szDeviceID[DH_DEV_ID_LEN];	// �豸ID
	int				nChannel;					// ͨ����
	int				nUniqueChannel;				// ͳһ���
	int				nFailedCode;				// ʧ����, 0-�ɹ���1-Unique��ַ�ռ����� 2-�Ѿ�����
} DH_LOGIC_DEVICE_ADD_CAMERA_RESULT;

// CLIENT_AddLogicDeviceCamera �ӿ��������
typedef struct tagDH_IN_ADD_LOGIC_DEVICE_CAMERA
{
	DWORD			dwSize;
	DH_LOGIC_DEVICE_ADD_CAMERA_PARAM*	pCameras;	// ��ƵԴ��Ϣ����
	int				nCameraCount;					// ��ƵԴ��Ϣ����
} DH_IN_ADD_LOGIC_DEVICE_CAMERA;

// CLIENT_AddLogicDeviceCamera �ӿ��������
typedef struct tagDH_OUT_ADD_LOGIC_DEVICE_CAMERA 
{
	DWORD			dwSize;
	DH_LOGIC_DEVICE_ADD_CAMERA_RESULT* pResults;	// ������ƵԴ�������, �û������ڴ�
	int				nMaxResultCount;				// ��������С, �û���д
	int				nRetResultCount;				// ʵ�ʽ������
} DH_OUT_ADD_LOGIC_DEVICE_CAMERA;



/***********************************************************************
 ** �ص���������
 ***********************************************************************/

// �������ӶϿ��ص�����ԭ��
typedef void (CALLBACK *fDisConnect)(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

// �������ӻָ��ص�����ԭ��
typedef void (CALLBACK *fHaveReConnect)(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

// ��̬�����ӶϿ��ص�����ԭ��
typedef void (CALLBACK *fSubDisConnect)(EM_INTERFACE_TYPE emInterfaceType, BOOL bOnline, LLONG lOperateHandle, LLONG lLoginID, LDWORD dwUser);

// ��Ƶ���ӶϿ��ص�����ԭ��, 
typedef void (CALLBACK *fRealPlayDisConnect)(LLONG lOperateHandle, EM_REALPLAY_DISCONNECT_EVENT_TYPE dwEventType, void* param, LDWORD dwUser);

// ʵʱ�������ݻص�����ԭ��
typedef void (CALLBACK *fRealDataCallBack)(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser);

// ʵʱ�������ݻص�����ԭ��--��չ
typedef void (CALLBACK *fRealDataCallBackEx)(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, LDWORD dwUser);

// ��Ļ���ӻص�����ԭ��
typedef void (CALLBACK *fDrawCallBack)(LLONG lLoginID, LLONG lPlayHandle, HDC hDC, LDWORD dwUser);

// �ط����ݻص�����ԭ��
typedef int (CALLBACK *fDataCallBack)(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser);

// �طŽ��Ȼص�����ԭ��
typedef void (CALLBACK *fDownLoadPosCallBack)(LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, LDWORD dwUser);

// ��ʱ��طŽ��Ȼص�����ԭ��
typedef void (CALLBACK *fTimeDownLoadPosCallBack) (LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, LDWORD dwUser);

// ��Ϣ�ص�����ԭ��
typedef BOOL (CALLBACK *fMessCallBack)(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

// �����������ص�����ԭ��
typedef int (CALLBACK *fServiceCallBack)(LLONG lHandle, char *pIp, WORD wPort, LONG lCommand, void *pParam, DWORD dwParamLen, LDWORD dwUserData);

// �����Խ�����Ƶ���ݻص�����ԭ��
typedef void (CALLBACK *pfAudioDataCallBack)(LLONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, LDWORD dwUser);

// �����豸����ص�����ԭ��
typedef void (CALLBACK *fUpgradeCallBack) (LLONG lLoginID, LLONG lUpgradechannel, int nTotalSize, int nSendSize, LDWORD dwUser);

// ͸�����ڻص�����ԭ��
typedef void (CALLBACK *fTransComCallBack) (LLONG lLoginID, LLONG lTransComChannel, char *pBuffer, DWORD dwBufSize, LDWORD dwUser);

// ��ѯ�豸��־���ݻص�����ԭ��
typedef void (CALLBACK *fLogDataCallBack)(LLONG lLoginID, char *pBuffer, DWORD dwBufSize, DWORD nTotalSize, BOOL bEnd, LDWORD dwUser);

// ץͼ�ص�����ԭ��
typedef void (CALLBACK *fSnapRev)(LLONG lLoginID, BYTE *pBuf, UINT RevLen, UINT EncodeType, DWORD CmdSerial, LDWORD dwUser);

// GPS��Ϣ���Ļص�
typedef void (CALLBACK *fGPSRev)(LLONG lLoginID, GPS_Info GpsInfo, LDWORD dwUserData);

// GPS��Ϣ���Ļص�--��չ
typedef void (CALLBACK *fGPSRevEx)(LLONG lLoginID, GPS_Info GpsInfo, ALARM_STATE_INFO stAlarmInfo, LDWORD dwUserData, void *reserved);

// GPS��ʪ����Ϣ���Ļص�
typedef void (CALLBACK *fGPSTempHumidityRev)(LLONG lLoginID, GPS_TEMP_HUMIDITY_INFO GpsTHInfo, LDWORD dwUserData);

// �첽���ݻص�
typedef void (CALLBACK *fMessDataCallBack)(LLONG lCommand, LPNET_CALLBACK_DATA lpData, LDWORD dwUser);

// �ļ�����ص�
typedef void (CALLBACK *fTransFileCallBack)(LLONG lHandle, int nTransType, int nState, int nSendSize, int nTotalSize, LDWORD dwUser);

// ���ܷ������ݻص�;nSequence��ʾ�ϴ�����ͬͼƬ�����Ϊ0ʱ��ʾ�ǵ�һ�γ��֣�Ϊ2��ʾ���һ�γ��ֻ������һ�Σ�Ϊ1��ʾ�˴�֮����
// int nState = (int*) reserved ��ʾ��ǰ�ص����ݵ�״̬, Ϊ0��ʾ��ǰ����Ϊʵʱ���ݣ�Ϊ1��ʾ��ǰ�ص��������������ݣ�Ϊ2ʱ��ʾ�������ݴ��ͽ���
typedef int  (CALLBACK *fAnalyzerDataCallBack)(LLONG lAnalyzerHandle, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser, int nSequence, void *reserved);

// �첽�����豸�ص�
typedef void (CALLBACK *fSearchDevicesCB)(DEVICE_NET_INFO_EX *pDevNetInfo, void* pUserData);

// �첽ע���豸�ص�����ԭ��
typedef void (CALLBACK *fHaveLogin)(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, BOOL bOnline, NET_DEVICEINFO_Ex stuDeviceInfo, int nError, LDWORD dwUser, void *reserved);

// �ط�YUV���ݻص�����
typedef void (CALLBACK *fYUVDataCallBack)(LLONG lPlaybackHandle, BYTE *pBuffer, DWORD dwBufSize, LONG param, LDWORD dwUser, void *reserved);

/************************************************************************
 ** �ӿڶ���
 ***********************************************************************/

// SDK��ʼ��
CLIENT_API BOOL CALL_METHOD CLIENT_Init(fDisConnect cbDisConnect, LDWORD dwUser);

// SDK�˳�����
CLIENT_API void CALL_METHOD CLIENT_Cleanup();

//------------------------------------------------------------------------

// ���ö��������ɹ��ص����������ú�SDK�ڲ������Զ�����
CLIENT_API void CALL_METHOD CLIENT_SetAutoReconnect(fHaveReConnect cbAutoConnect, LDWORD dwUser);

// ���ö�̬�����Ӷ��߻ص�������ĿǰSVR�豸�ļ��Ӻͻط��Ƕ����ӵġ�
CLIENT_API void CALL_METHOD CLIENT_SetSubconnCallBack(fSubDisConnect cbSubDisConnect, LDWORD dwUser);

// ���غ���ִ��ʧ�ܴ���
CLIENT_API DWORD CALL_METHOD CLIENT_GetLastError(void);

// ���������豸��ʱʱ��ͳ��Դ���
CLIENT_API void CALL_METHOD CLIENT_SetConnectTime(int nWaitTime, int nTryTimes);

// ���õ�½���绷��
CLIENT_API void CALL_METHOD CLIENT_SetNetworkParam(NET_PARAM *pNetParam);

// ��ȡSDK�İ汾��Ϣ
CLIENT_API DWORD CALL_METHOD CLIENT_GetSDKVersion();

//------------------------------------------------------------------------

// ���豸ע��
CLIENT_API LLONG CALL_METHOD CLIENT_Login(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, LPNET_DEVICEINFO lpDeviceInfo, int *error = 0);

// ��չ�ӿڣ�nSpecCap = 0ΪTCP��ʽ�µĵ��룬nSpecCap = 2Ϊ����ע��ĵ��룬nSpecCap = 3Ϊ�鲥��ʽ�µĵ��룬
//			 nSpecCap = 4ΪUDP��ʽ�µĵ��룬nSpecCap = 6Ϊֻ���������µĵ��룬nSpecCap = 7ΪSSL����
//			 nSpecCap = 8Ϊ�ɶ��ѷ���½
//			 nSpecCap = 9Ϊ��¼Զ���豸�����ʱ��void* pCapParam����Զ���豸�����ֵ��ַ���
//           nSpecCap = 12ΪLDAP��ʽ��¼
//           nSpecCap = 13ΪAD��ʽ��¼
//           nSpecCap = 14ΪRadius��¼��ʽ 
//			 nSpecCap = 15ΪSocks5��½��ʽ�����ʱ��void* pCapParam����Socks5��������IP&&port&&ServerName&&ServerPassword�ַ���
//			 nSpecCap = 16Ϊ������½��ʽ�����ʱ��void* pCapParam����SOCKETֵ
CLIENT_API LLONG CALL_METHOD CLIENT_LoginEx(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, int nSpecCap, void* pCapParam, LPNET_DEVICEINFO lpDeviceInfo, int *error = 0);

// �첽���豸ע�� 
// nSpecCap = 0ΪTCP��ʽ�µĵ���,nSpecCap = 6Ϊֻ���������µĵ���
CLIENT_API LLONG CALL_METHOD CLIENT_StartLogin(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, int nSpecCap, void* pCapParam, fHaveLogin cbLogin, LDWORD dwUser);

// ֹͣ���豸ע��
CLIENT_API BOOL CALL_METHOD CLIENT_StopLogin(LLONG lLoginID);

// ���豸ע��
CLIENT_API BOOL CALL_METHOD CLIENT_Logout(LLONG lLoginID);


//------------------------------------------------------------------------

// ��ʼʵʱ����
CLIENT_API LLONG CALL_METHOD CLIENT_RealPlay(LLONG lLoginID, int nChannelID, HWND hWnd);

// ��ʼʵʱ����--��չ
CLIENT_API LLONG CALL_METHOD CLIENT_RealPlayEx(LLONG lLoginID, int nChannelID, HWND hWnd, DH_RealPlayType rType = DH_RType_Realplay);

//��ʵʱ���ӣ�������0��ʾ��ʧ��
CLIENT_API LLONG CALL_METHOD CLIENT_StartRealPlay(LLONG lLoginID, int nChannelID, HWND hWnd, DH_RealPlayType rType, fRealDataCallBackEx cbRealData, fRealPlayDisConnect cbDisconnect, LDWORD dwUser, DWORD dwWaitTime = 10000);

// �໭��ʵʱԤ��
CLIENT_API LLONG CALL_METHOD CLIENT_MultiPlay(LLONG lLoginID, HWND hWnd);

// ֹͣ�໭��ʵʱԤ��
CLIENT_API BOOL CALL_METHOD CLIENT_StopMultiPlay(LLONG lMultiHandle);

// ץͼ��hPlayHandleΪ���ӻ�طž��
CLIENT_API BOOL CALL_METHOD CLIENT_CapturePicture(LLONG hPlayHandle, const char *pchPicFileName);

// ����ʵʱ�������ݻص�
CLIENT_API BOOL CALL_METHOD CLIENT_SetRealDataCallBack(LLONG lRealHandle, fRealDataCallBack cbRealData, LDWORD dwUser);

// ����ʵʱ�������ݻص�--��չ
CLIENT_API BOOL CALL_METHOD CLIENT_SetRealDataCallBackEx(LLONG lRealHandle, fRealDataCallBackEx cbRealData, LDWORD dwUser, DWORD dwFlag);

// ����ͼ��������
CLIENT_API BOOL	CALL_METHOD CLIENT_AdjustFluency(LLONG lRealHandle, int nLevel);

// ��������Ϊ�ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_SaveRealData(LLONG lRealHandle, const char *pchFileName);

// ������������Ϊ�ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_StopSaveRealData(LLONG lRealHandle);

// ����ͼ������
CLIENT_API BOOL CALL_METHOD CLIENT_ClientSetVideoEffect(LLONG lPlayHandle, unsigned char nBrightness, unsigned char nContrast, unsigned char nHue, unsigned char nSaturation);

// ��ȡͼ������
CLIENT_API BOOL CALL_METHOD CLIENT_ClientGetVideoEffect(LLONG lPlayHandle, unsigned char *nBrightness, unsigned char *nContrast, unsigned char *nHue, unsigned char *nSaturation);

// ������Ļ���ӻص�
CLIENT_API void CALL_METHOD CLIENT_RigisterDrawFun(fDrawCallBack cbDraw, LDWORD dwUser);

// ������
CLIENT_API BOOL CALL_METHOD CLIENT_OpenSound(LLONG hPlayHandle);

// ѡ����Ƶͨ��
// ����: hPlayHandle,���ž��
//       nAudioChannelID, ��Ƶͨ����0��ʼ.
//       nFlag,TRUE��,FALSE�ر�
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
CLIENT_API BOOL CALL_METHOD CLIENT_ChooseAudio(LLONG hPlayHandle, int nAudioChannelID, int nFlag);

// ��ȡ��Ƶͨ���򿪹ر�״̬
// ����: hPlayHandle,���ž��
//       nAudioChannelID, ��Ƶͨ��.
//       pFlag,TRUE��,FALSE�ر�
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
CLIENT_API BOOL CALL_METHOD CLIENT_GetAudioChooseState(LLONG hPlayHandle, int nAudioChannelID, int* pFlag);

// ����������lPlayHandleΪ���ӻ�طž��
CLIENT_API BOOL CALL_METHOD CLIENT_SetVolume(LLONG lPlayHandle, int nVolume);

// �ر�����
CLIENT_API BOOL CALL_METHOD CLIENT_CloseSound();

// ֹͣʵʱԤ��
CLIENT_API BOOL CALL_METHOD CLIENT_StopRealPlay(LLONG lRealHandle);

// ֹͣʵʱԤ��--��չ
CLIENT_API BOOL CALL_METHOD CLIENT_StopRealPlayEx(LLONG lRealHandle);

//------------------------------------------------------------------------

// ͨ����̨����
CLIENT_API BOOL CALL_METHOD CLIENT_PTZControl(LLONG lLoginID, int nChannelID, DWORD dwPTZCommand, DWORD dwStep, BOOL dwStop);

// ����̨����
CLIENT_API BOOL CALL_METHOD CLIENT_DHPTZControl(LLONG lLoginID, int nChannelID, DWORD dwPTZCommand, unsigned char param1, unsigned char param2, unsigned char param3, BOOL dwStop,void* param4=NULL);

// ����̨������չ�ӿڣ�֧����ά���ٶ�λ
CLIENT_API BOOL CALL_METHOD CLIENT_DHPTZControlEx(LLONG lLoginID, int nChannelID, DWORD dwPTZCommand, LONG lParam1, LONG lParam2, LONG lParam3, BOOL dwStop);

//------------------------------------------------------------------------
// ��ѯĳ�µĸ����Ƿ����¼���ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordStatus(LLONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmMonth, char* pchCardid, LPNET_RECORD_STATUS pRecordStatus, int waittime=1000);
// ��ѯʱ������Ƿ���¼���ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordTime(LLONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, BOOL *bResult, int waittime=1000);
// ��ѯʱ����ڵ�����¼���ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordFile(LLONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, LPNET_RECORDFILE_INFO nriFileinfo, int maxlen, int *filecount, int waittime=1000, BOOL bTime = FALSE);

// ���ٲ�ѯʱ����ڵ�¼���ļ������ʱ�����¼�񳬹�16��ʱ��ֻ����ʱ�������16��¼��
CLIENT_API BOOL CALL_METHOD CLIENT_QuickQueryRecordFile(LLONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, LPNET_RECORDFILE_INFO nriFileinfo, int maxlen, int *filecount, int waittime=1000, BOOL bTime = FALSE);

// ��ѯ����¼��ʱ��
CLIENT_API BOOL CALL_METHOD CLIENT_QueryFurthestRecordTime(LLONG lLoginID, int nRecordFileType, char *pchCardid, NET_FURTHEST_RECORD_TIME* pFurthrestTime, int nWaitTime);

// ��ʼ����¼���ļ�
CLIENT_API LLONG	CALL_METHOD CLIENT_FindFile(LLONG lLoginID, int nChannelId, int nRecordFileType, char* cardid, LPNET_TIME time_start, LPNET_TIME time_end, BOOL bTime, int waittime);

// ����¼���ļ�
CLIENT_API int	CALL_METHOD CLIENT_FindNextFile(LLONG lFindHandle,LPNET_RECORDFILE_INFO lpFindData);

// ����¼���ļ�����
CLIENT_API BOOL CALL_METHOD CLIENT_FindClose(LLONG lFindHandle);

// ���ļ���ʽ�ط�
CLIENT_API LLONG CALL_METHOD CLIENT_PlayBackByRecordFile(LLONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, LDWORD dwUserData);

// ���ļ���ʽ�ط�--��չ
CLIENT_API LLONG CALL_METHOD CLIENT_PlayBackByRecordFileEx(LLONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, LDWORD dwPosUser, fDataCallBack fDownLoadDataCallBack, LDWORD dwDataUser);

// ���ļ���ʽ�ط�--�ص��ط��ж��¼�
CLIENT_API LLONG CALL_METHOD CLIENT_StartPlayBackByRecordFile(LLONG lLoginID,  LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, 
															 fDownLoadPosCallBack cbDownLoadPos, LDWORD dwPosUser, 
															 fDataCallBack fDownLoadDataCallBack, LDWORD dwDataUser, 
															 fRealPlayDisConnect fDisConnectCallBack, LDWORD dwDisUser, DWORD dwWaitTime = 10000);

//���ļ���ʽ�ط�--��֡����(��������ʱ����ʹ��)
CLIENT_API LLONG CALL_METHOD CLIENT_FramCotrolPlayBackByRecordFile(LLONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, 
																   fDownLoadPosCallBack cbDownLoadPos, LDWORD dwPosUser, 
																   fDataCallBack fDownLoadDataCallBack, LDWORD dwDataUser, unsigned int nCutFrameRate);

// ��ʱ�䷽ʽ�ط�
CLIENT_API LLONG CALL_METHOD CLIENT_PlayBackByTime(LLONG lLoginID, int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, LDWORD dwPosUser);

// ��ʱ�䷽ʽ�ط�--��չ
CLIENT_API LLONG CALL_METHOD CLIENT_PlayBackByTimeEx(LLONG lLoginID, int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, 
													 fDownLoadPosCallBack cbDownLoadPos, LDWORD dwPosUser, 
													 fDataCallBack fDownLoadDataCallBack, LDWORD dwDataUser);

// ��ʱ�䷽ʽ�ط�--�ص��ط��ж��¼�
CLIENT_API LLONG CALL_METHOD CLIENT_StartPlayBackByTime(LLONG lLoginID, int nChannelID, 
													   LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, 
													   fDownLoadPosCallBack cbDownLoadPos, LDWORD dwPosUser,
													   fDataCallBack fDownLoadDataCallBack, LDWORD dwDataUser, 
													   fRealPlayDisConnect fDisConnectCallBack, LDWORD dwDisUser, DWORD dwWaitTime = 10000);

//��ʱ�䷽ʽ�ط�--��֡����(��������ʱ����ʹ��)
CLIENT_API LLONG CALL_METHOD CLIENT_FramCotrolPlayBackByTime(LLONG lLoginID, int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, 
															 fDownLoadPosCallBack cbDownLoadPos, LDWORD dwPosUser, 
															 fDataCallBack fDownLoadDataCallBack, LDWORD dwDataUser, unsigned int nCutFrameRate);

//��ƵŨ���ļ��ط�
CLIENT_API LLONG CALL_METHOD CLIENT_PlayBackBySynopsisFile(LLONG lLoginID, 
															LPNET_SYNOPSISFILE_INFO lpRecordFile, 
															HWND hWnd, 
															fDownLoadPosCallBack cbDownLoadPos,
															LDWORD dwPosUser, 
															fDataCallBack fDownLoadDataCallBack,
															LDWORD dwDataUser,
															LDWORD dwUser);
															
// ��λ¼��ط���ʼ��
CLIENT_API BOOL CALL_METHOD CLIENT_SeekPlayBack(LLONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);

// ��ͣ��ָ�¼��ط�
CLIENT_API BOOL CALL_METHOD CLIENT_PausePlayBack(LLONG lPlayHandle, BOOL bPause);

// ���¼��ط�
CLIENT_API BOOL CALL_METHOD CLIENT_FastPlayBack(LLONG lPlayHandle);

// ����¼��ط�
CLIENT_API BOOL CALL_METHOD CLIENT_SlowPlayBack(LLONG lPlayHandle);

// ����¼��ط�
CLIENT_API BOOL CALL_METHOD CLIENT_StepPlayBack(LLONG lPlayHandle, BOOL bStop);

// ���Ʋ��ŷ���--���Ż��ߵ���
CLIENT_API BOOL CALL_METHOD CLIENT_PlayBackControlDirection(LLONG lPlayHandle, BOOL bBackward);

// ���ûط�֡��
CLIENT_API BOOL CALL_METHOD CLIENT_SetFramePlayBack(LLONG lPlayHandle, int framerate);

// ��ȡ�ط�֡��
CLIENT_API BOOL CALL_METHOD CLIENT_GetFramePlayBack(LLONG lPlayHandle, int *fileframerate, int *playframerate);

// �ָ������ط��ٶ�
CLIENT_API BOOL CALL_METHOD CLIENT_NormalPlayBack(LLONG lPlayHandle);

// ���ܼ����ط�
CLIENT_API BOOL CALL_METHOD CLIENT_SmartSearchPlayBack(LLONG lPlayHandle, LPIntelligentSearchPlay lpPlayBackParam);

// ��ȡ�ط�OSDʱ��
CLIENT_API BOOL CALL_METHOD CLIENT_GetPlayBackOsdTime(LLONG lPlayHandle, LPNET_TIME lpOsdTime, LPNET_TIME lpStartTime, LPNET_TIME lpEndTime);

// ֹͣ¼��ط�
CLIENT_API BOOL CALL_METHOD CLIENT_StopPlayBack(LLONG lPlayHandle);

// ����¼���ļ�
CLIENT_API LLONG CALL_METHOD CLIENT_DownloadByRecordFile(LLONG lLoginID,LPNET_RECORDFILE_INFO lpRecordFile, char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, LDWORD dwUserData);

// ͨ��ʱ������¼��
CLIENT_API LLONG CALL_METHOD CLIENT_DownloadByTime(LLONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, fTimeDownLoadPosCallBack cbTimeDownLoadPos, LDWORD dwUserData);

// ��ѯ¼�����ؽ���
CLIENT_API BOOL CALL_METHOD CLIENT_GetDownloadPos(LLONG lFileHandle, int *nTotalSize, int *nDownLoadSize);

// ֹͣ¼������
CLIENT_API BOOL CALL_METHOD CLIENT_StopDownload(LLONG lFileHandle);

//�ֲ��Ŵ�
CLIENT_API BOOL CALL_METHOD CLIENT_SetDisplayRegion(LLONG lPlayHandle,DWORD nRegionNum, DH_DISPLAYRREGION *pSrcRect, HWND hDestWnd, BOOL bEnable);

//------------------------------------------------------------------------

// ���ñ����ص�����
CLIENT_API void CALL_METHOD CLIENT_SetDVRMessCallBack(fMessCallBack cbMessage,LDWORD dwUser);

// ���豸���ı���
CLIENT_API BOOL CALL_METHOD CLIENT_StartListen(LLONG lLoginID);

// ���豸���ı���--��չ
CLIENT_API BOOL CALL_METHOD CLIENT_StartListenEx(LLONG lLoginID);

// ֹͣ���ı���
CLIENT_API BOOL CALL_METHOD CLIENT_StopListen(LLONG lLoginID);

// ������λ
CLIENT_API BOOL CALL_METHOD CLIENT_AlarmReset(LLONG lLoginID, DWORD dwAlarmType, int nChannel, void* pReserved = NULL, int nWaitTime = 1000);

//------------------------------------------------------------------------
 
// ����ע�Ṧ�ܣ���������nTimeout��������Ч
CLIENT_API LLONG CALL_METHOD CLIENT_ListenServer(char* ip, WORD port, int nTimeout, fServiceCallBack cbListen, LDWORD dwUserData);

// ֹͣ����
CLIENT_API BOOL CALL_METHOD CLIENT_StopListenServer(LLONG lServerHandle);

// ��Ӧ�豸��ע������
CLIENT_API BOOL CALL_METHOD CLIENT_ResponseDevReg(char *devSerial, char* ip, WORD port, BOOL bAccept);

//------------------------------------------------------------------------

// �����ϴ����ܣ���������dwTimeOut��������Ч
CLIENT_API LLONG CALL_METHOD CLIENT_StartService(WORD wPort, char *pIp = NULL, fServiceCallBack pfscb = NULL, DWORD dwTimeOut = 0xffffffff, LDWORD dwUserData = 0);

// ֹͣ����
CLIENT_API BOOL CALL_METHOD CLIENT_StopService(LLONG lHandle);

//------------------------------------------------------------------------

// ���������Խ�ģʽ���ͻ��˷�ʽ���Ƿ�������ʽ
CLIENT_API BOOL CALL_METHOD CLIENT_SetDeviceMode(LLONG lLoginID, EM_USEDEV_MODE emType, void* pValue);

// �������Խ�
CLIENT_API LLONG CALL_METHOD CLIENT_StartTalkEx(LLONG lLoginID, pfAudioDataCallBack pfcb, LDWORD dwUser);

// ��ʼPC��¼��
CLIENT_API BOOL CALL_METHOD CLIENT_RecordStart();

// ����PC��¼��
CLIENT_API BOOL CALL_METHOD CLIENT_RecordStop();

// �����������ݵ��豸
CLIENT_API LONG  CALL_METHOD CLIENT_TalkSendData(LLONG lTalkHandle, char *pSendBuf, DWORD dwBufSize);

// ������Ƶ����
CLIENT_API void CALL_METHOD CLIENT_AudioDec(char *pAudioDataBuf, DWORD dwBufSize);

// ���������Խ�������
CLIENT_API BOOL CALL_METHOD CLIENT_SetAudioClientVolume(LLONG lTalkHandle, WORD wVolume);

// ֹͣ�����Խ�
CLIENT_API BOOL CALL_METHOD CLIENT_StopTalkEx(LLONG lTalkHandle);

// �����豸���㲥��
CLIENT_API BOOL CALL_METHOD CLIENT_AudioBroadcastAddDev(LLONG lLoginID);

// �ӹ㲥����ɾ���豸
CLIENT_API BOOL CALL_METHOD CLIENT_AudioBroadcastDelDev(LLONG lLoginID);

// ��Ƶ����--��ʼ��(�ض���׼��ʽ->�󻪸�ʽ)
CLIENT_API int  CALL_METHOD CLIENT_InitAudioEncode(DH_AUDIO_FORMAT aft);

// ��Ƶ����--���ݱ���
CLIENT_API int	CALL_METHOD	CLIENT_AudioEncode(LLONG lTalkHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen);

// ��Ƶ����--����˳�
CLIENT_API int	CALL_METHOD	CLIENT_ReleaseAudioEncode();

//------------------------------------------------------------------------

// ��ѯ�豸��־
CLIENT_API BOOL CALL_METHOD CLIENT_QueryLog(LLONG lLoginID, char *pLogBuffer, int maxlen, int *nLogBufferlen, int waittime=3000);

// ��ѯ�豸��־���Է�ҳ��ʽ��ѯ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDeviceLog(LLONG lLoginID, QUERY_DEVICE_LOG_PARAM *pQueryParam, char *pLogBuffer, int nLogBufferLen, int *pRecLogNum, int waittime=3000);

// ���ͨ��¼��״̬
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordState(LLONG lLoginID, char *pRSBuffer, int maxlen, int *nRSBufferlen, int waittime=1000);

// ���������ͨ��¼��״̬�������ֽ�����ͨ������Ӧ, ÿ���ֽڱ�ʾ��Ӧͨ���ĸ�����¼�����״̬��0-�ر�,1-�ֶ�,2-�Զ���
CLIENT_API BOOL CALL_METHOD CLIENT_QueryExtraRecordState(LLONG lLoginID, char *pRSBuffer, int maxlen, int *nRSBufferlen, void *pReserved, int waittime=1000);

// ��ѯ�豸״̬
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDevState(LLONG lLoginID, int nType, char *pBuf, int nBufLen, int *pRetLen, int waittime=1000);

// ��ѯԶ���豸״̬,nTypeΪDH_DEVSTATE_ALARM_FRONTDISCONNECTʱ��ͨ���Ŵ�1��ʼ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRemotDevState(LLONG lLoginID, int nType, int nChannelID, char *pBuf, int nBufLen, int *pRetLen, int waittime=1000);

// ��ѯϵͳ������Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_QuerySystemInfo(LLONG lLoginID, int nSystemType, char *pSysInfoBuffer, int maxlen, int *nSysInfolen, int waittime=1000);

// ��ϵͳ������ѯ�ӿڣ���ѯϵͳ������Ϣ(��Json��ʽ�����������SDK)
CLIENT_API BOOL CALL_METHOD CLIENT_QueryNewSystemInfo(LLONG lLoginID, char* szCommand, int nChannelID, char* szOutBuffer, DWORD dwOutBufferSize, int *error, int waittime=1000);

// ��ȡͨ������
CLIENT_API LONG  CALL_METHOD CLIENT_GetStatiscFlux(LLONG lLoginID, LLONG  lPlayHandle);

// ��ȡ��̨��Ϣ
CLIENT_API BOOL  CALL_METHOD CLIENT_GetPtzOptAttr(LLONG lLoginID,DWORD dwProtocolIndex,LPVOID lpOutBuffer,DWORD dwBufLen,DWORD *lpBytesReturned,int waittime=500);

//------------------------------------------------------------------------

// �����豸
CLIENT_API BOOL CALL_METHOD CLIENT_RebootDev(LLONG lLoginID);

// �ر��豸
CLIENT_API BOOL CALL_METHOD CLIENT_ShutDownDev(LLONG lLoginID);

// �豸����
CLIENT_API BOOL CALL_METHOD CLIENT_ControlDevice(LLONG lLoginID, CtrlType type, void *param, int waittime = 1000);

// ����ͨ��¼��״̬
CLIENT_API BOOL CALL_METHOD CLIENT_SetupRecordState(LLONG lLoginID, char *pRSBuffer, int nRSBufferlen);

// ����ͨ��������¼��״̬
CLIENT_API BOOL CALL_METHOD CLIENT_SetupExtraRecordState(LLONG lLoginID, char *pRSBuffer, int nRSBufferlen, void* pReserved);

// ��ѯIO״̬
CLIENT_API BOOL CALL_METHOD CLIENT_QueryIOControlState(LLONG lLoginID, DH_IOTYPE emType, 
                                           void *pState, int maxlen, int *nIOCount, int waittime=1000);

// IO����
CLIENT_API BOOL CALL_METHOD CLIENT_IOControl(LLONG lLoginID, DH_IOTYPE emType, void *pState, int maxlen);

// ǿ��I֡��nChannelID��ͨ���ţ�nSubChannel����������(0������1��������1)
CLIENT_API BOOL CALL_METHOD CLIENT_MakeKeyFrame(LLONG lLoginID, int nChannelID, int nSubChannel=0);

// ��������ע��
typedef void (CALLBACK *fConnectMessCallBack)(LLONG lConnectHandle, NET_CLOUDSERVICE_CONNECT_RESULT* pConnectResult, void* pReserved, LDWORD dwUser);

CLIENT_API LLONG CALL_METHOD CLIENT_ConnectCloudService(LLONG lLoginID, NET_CLOUDSERVICE_CONNECT_PARAM* pConnectParm, fConnectMessCallBack pConnectMessCB, LDWORD dwUser, void* pReserved);
//------------------------------------------------------------------------

// ��ѯ�û���Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfo(LLONG lLoginID, USER_MANAGE_INFO *info, int waittime=1000);

// ��ѯ�û���Ϣ--��չ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfoEx(LLONG lLoginID, USER_MANAGE_INFO_EX *info, int waittime=1000);

// ��ѯ�û���Ϣ--���֧��64ͨ���豸
CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfoNew(LLONG lLoginID, USER_MANAGE_INFO_NEW *info, void* pReserved, int waittime = 1000);

// �����豸�û�
CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfo(LLONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime=1000);

// �����豸�û�--��չ
CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfoEx(LLONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime=1000);

// �����豸�û�--���֧��64ͨ���豸
CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfoNew(LLONG lLoginID, int nOperateType, void *opParam, void *subParam, void* pReserved, int waittime = 1000);

//------------------------------------------------------------------------

// ����͸������ͨ��,TransComType��2���ֽڱ�ʾ������ţ���2���ֽڱ�ʾ�������ͣ�Ŀǰ����֧��0�����ڣ�1:485
CLIENT_API LLONG CALL_METHOD CLIENT_CreateTransComChannel(LLONG lLoginID, int TransComType, unsigned int baudrate, unsigned int databits, unsigned int stopbits, unsigned int parity, fTransComCallBack cbTransCom, LDWORD dwUser);

// ͸�����ڷ�������
CLIENT_API BOOL CALL_METHOD CLIENT_SendTransComData(LLONG lTransComChannel, char *pBuffer, DWORD dwBufSize);

// �ͷ�ͨ������ͨ��
CLIENT_API BOOL CALL_METHOD CLIENT_DestroyTransComChannel(LLONG lTransComChannel);

// ��ѯ͸������״̬
CLIENT_API BOOL   CALL_METHOD CLIENT_QueryTransComParams(LLONG lLoginID, int TransComType, DH_COMM_STATE* pCommState, int nWaitTime = 500);

//------------------------------------------------------------------------

// ��ʼ�����豸����
CLIENT_API LLONG CALL_METHOD CLIENT_StartUpgrade(LLONG lLoginID, char *pchFileName, fUpgradeCallBack cbUpgrade, LDWORD dwUser);

// ��ʼ�����豸����--��չ
CLIENT_API LLONG CALL_METHOD CLIENT_StartUpgradeEx(LLONG lLoginID, EM_UPGRADE_TYPE emType, char *pchFileName, fUpgradeCallBack cbUpgrade, LDWORD dwUser);

// ��������
CLIENT_API BOOL CALL_METHOD CLIENT_SendUpgrade(LLONG lUpgradeID);

// ���������豸����
CLIENT_API BOOL CALL_METHOD CLIENT_StopUpgrade(LLONG lUpgradeID);

//------------------------------------------------------------------------

// ��ѯ������Ϣ
CLIENT_API BOOL  CALL_METHOD CLIENT_GetDevConfig(LLONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime=500);

// ����������Ϣ
CLIENT_API BOOL  CALL_METHOD CLIENT_SetDevConfig(LLONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime=500);

// �����ýӿڣ���ѯ������Ϣ(��Json��ʽ�����������SDK)
CLIENT_API BOOL CALL_METHOD CLIENT_GetNewDevConfig(LLONG lLoginID, char* szCommand, int nChannelID, char* szOutBuffer, DWORD dwOutBufferSize, int *error, int waittime=500);

// �����ýӿڣ�����������Ϣ(��Json��ʽ�����������SDK)
CLIENT_API BOOL CALL_METHOD CLIENT_SetNewDevConfig(LLONG lLoginID, char* szCommand, int nChannelID, char* szInBuffer, DWORD dwInBufferSize, int *error, int *restart, int waittime=500);

// ɾ�����ýӿ�(Json��ʽ)
CLIENT_API BOOL CALL_METHOD CLIENT_DeleteDevConfig(LLONG lLoginID, NET_IN_DELETECFG* pInParam, NET_OUT_DELETECFG* pOutParam, int waittime=500);

// ��ȡ���ó�Ա���ƽӿ�(Json��ʽ)
CLIENT_API BOOL CALL_METHOD CLIENT_GetMemberNames(LLONG lLoginID, NET_IN_MEMBERNAME* pInParam, NET_OUT_MEMBERNAME* pOutParam, int waittime=500);

//------------------------------------------------------------------------

// ��ѯ�豸ͨ������
CLIENT_API BOOL CALL_METHOD CLIENT_QueryChannelName(LLONG lLoginID, char *pChannelName, int maxlen, int *nChannelCount, int waittime=1000);

// �����豸ͨ������
CLIENT_API BOOL  CALL_METHOD CLIENT_SetupChannelName(LLONG lLoginID,char *pbuf, int nbuflen);

// �����豸ͨ���ַ�����
CLIENT_API BOOL  CALL_METHOD CLIENT_SetupChannelOsdString(LLONG lLoginID, int nChannelNo, DH_CHANNEL_OSDSTRING* struOsdString, int nbuflen);

// ��ѯ�豸��ǰʱ��
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDeviceTime(LLONG lLoginID, LPNET_TIME pDeviceTime, int waittime=1000);

// �����豸��ǰʱ��
CLIENT_API BOOL CALL_METHOD CLIENT_SetupDeviceTime(LLONG lLoginID, LPNET_TIME pDeviceTime);

// �����豸��������
CLIENT_API BOOL CALL_METHOD CLIENT_SetMaxFlux(LLONG lLoginID, WORD wFlux);

//------------------------------------------------------------------------

// ���������ļ�
CLIENT_API LLONG CALL_METHOD CLIENT_ImportConfigFile(LLONG lLoginID, char *szFileName, fDownLoadPosCallBack cbUploadPos, LDWORD dwUserData, DWORD param=0);

// ֹͣ���������ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_StopImportCfgFile(LLONG lImportHandle);

// ���������ļ�
CLIENT_API LLONG CALL_METHOD CLIENT_ExportConfigFile(LLONG lLoginID, DH_CONFIG_FILE_TYPE emConfigFileType, char *szSavedFilePath, fDownLoadPosCallBack cbDownLoadPos, LDWORD dwUserData);

// ֹͣ���������ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_StopExportCfgFile(LLONG lExportHandle);

//------------------------------------------------------------------------

// ͨ���豸���ֻ����豸���к���DDNS��������ѯ�豸IP
CLIENT_API BOOL CALL_METHOD CLIENT_GetDVRIPByResolveSvr(char *pchDVRIP, WORD wDVRPort, BYTE *sDVRName, WORD wDVRNameLen, BYTE *sDVRSerialNumber, WORD wDVRSerialLen, char* sGetIP);

// ������������IPC��NVS���豸
CLIENT_API BOOL CALL_METHOD CLIENT_SearchDevices(char* szBuf, int nBufLen, int* pRetLen, DWORD dwSearchTime, char* szLocalIp=NULL);

// �첽������������IPC��NVS���豸
CLIENT_API LLONG CALL_METHOD CLIENT_StartSearchDevices(fSearchDevicesCB cbSearchDevices, void* pUserData, char* szLocalIp=NULL);

// ֹͣ�첽������������IPC��NVS���豸
CLIENT_API BOOL CALL_METHOD CLIENT_StopSearchDevices(LLONG lSearchHandle);

// �޸��豸IP
CLIENT_API BOOL CALL_METHOD CLIENT_ModifyDevice(DEVICE_NET_INFO_EX *pDevNetInfo, DWORD dwWaitTime, int *iError = NULL, char* szLocalIp = NULL, void *reserved = NULL);

// �����������豸IP
CLIENT_API BOOL CALL_METHOD CLIENT_SearchDevicesByIPs(DEVICE_IP_SEARCH_INFO* pIpSearchInfo, fSearchDevicesCB cbSearchDevices, LDWORD dwUserData, char* szLocalIp, DWORD dwWaitTime);
//------------------------------------------------------------------------

// ƽ̨����ӿ�
CLIENT_API BOOL CALL_METHOD CLIENT_GetPlatFormInfo(LLONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime=500);
CLIENT_API BOOL CALL_METHOD CLIENT_SetPlatFormInfo(LLONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime=500);

// ��ͷ�۽�����
//	dwFocusCommand = 0Ϊ�۽�����
//	dwFocusCommand = 1Ϊ�����۽�����
//	dwFocusCommand = 2Ϊ�Զ��۽����ڣ����ڽ��������λ�á�nFocus��nZoom��Ч��
CLIENT_API BOOL CALL_METHOD CLIENT_FocusControl(LLONG lLoginID, int nChannelID, DWORD dwFocusCommand, double nFocus, double nZoom, void *reserved = NULL, int waittime=500);

///////////////////////////////�����豸�ӿ�///////////////////////////////

// ����ץͼ�ص�����
CLIENT_API void CALL_METHOD CLIENT_SetSnapRevCallBack(fSnapRev OnSnapRevMessage, LDWORD dwUser);

// ץͼ����
CLIENT_API BOOL CALL_METHOD CLIENT_SnapPicture(LLONG lLoginID, SNAP_PARAMS par);

// ץͼ������չ�ӿ�
CLIENT_API BOOL CALL_METHOD CLIENT_SnapPictureEx(LLONG lLoginID, SNAP_PARAMS *par, int *reserved = 0);

// ����GPS���Ļص�����
CLIENT_API void CALL_METHOD CLIENT_SetSubcribeGPSCallBack(fGPSRev OnGPSMessage, LDWORD dwUser);

// ����GPS���Ļص�����--��չ
CLIENT_API void CALL_METHOD CLIENT_SetSubcribeGPSCallBackEX(fGPSRevEx OnGPSMessage, LDWORD dwUser);

// GPS��Ϣ����
CLIENT_API BOOL CALL_METHOD CLIENT_SubcribeGPS (LLONG lLoginID, BOOL bStart, LONG KeepTime, LONG InterTime);

// ����GPS��ʪ�ȶ��Ļص�����
CLIENT_API void CALL_METHOD CLIENT_SetSubcribeGPSTHCallBack(fGPSTempHumidityRev OnGPSMessage, LDWORD dwUser);

// GPS��ʪ����Ϣ����
CLIENT_API BOOL CALL_METHOD CLIENT_SubcribeGPSTempHumidity (LLONG lLoginID, BOOL bStart,	int InterTime, void* Reserved);

//GPS��־��Ϣ��ѯ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryGPSLog(LLONG lLoginID,QUERY_GPS_LOG_PARAM *pQueryParam, char *pLogBuffer, int nLogBufferLen, int *pRecLogNum, BOOL *bContinue, int waittime);

//////////////////////////////�������豸�ӿ�//////////////////////////////

// ��ѯ��������Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDecoderInfo(LLONG lLoginID, LPDEV_DECODER_INFO lpDecInfo, int waittime=1000);

// ��ѯ��������ǰTV��Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDecoderTVInfo(LLONG lLoginID, int nMonitorID, LPDEV_DECODER_TV lpMonitorInfo, int waittime=1000);

// ��ѯ����ͨ����Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDecEncoderInfo(LLONG lLoginID, int nDecoderID, LPDEV_ENCODER_INFO lpEncoderInfo, int waittime=1000);

// ���ý�����TV���ʹ��
CLIENT_API BOOL CALL_METHOD CLIENT_SetDecTVOutEnable(LLONG lLoginID, BYTE *pDecTVOutEnable, int nBufLen, int waittime=1000);

// ���ý�������ʾ������Ϣʹ�ܣ�ͨ���Ŵ�0��ʼ
CLIENT_API BOOL CALL_METHOD CLIENT_SetDecLayOutEnable(LLONG lLoginID, BYTE bDecLayOutEnable, int nChannel, int waittime=1000);
//------------------------------------------------------------------------

// �����첽�ص�����
CLIENT_API BOOL CALL_METHOD CLIENT_SetOperateCallBack(LLONG lLoginID, fMessDataCallBack cbMessData, LDWORD dwUser);

// ���ƽ�����TV����ָ�ӿ�Ϊ�첽��ʽ
CLIENT_API LLONG CALL_METHOD CLIENT_CtrlDecTVScreen(LLONG lLoginID, int nMonitorID, BOOL bEnable, int nSplitType, BYTE *pEncoderChannel, int nBufLen, void* userdata=NULL);

// ������TV�����л����ӿ�Ϊ�첽��ʽ
//   
CLIENT_API LLONG CALL_METHOD CLIENT_SwitchDecTVEncoder(LLONG lLoginID, int nDecoderID, LPDEV_ENCODER_INFO lpEncoderInfo, void* userdata=NULL);

//------------------------------------------------------------------------

// ���ӻ������
CLIENT_API int CALL_METHOD CLIENT_AddTourCombin(LLONG lLoginID, int nMonitorID, int nSplitType, BYTE *pEncoderChannnel, int nBufLen, int waittime=1000);

// ɾ���������
CLIENT_API BOOL CALL_METHOD CLIENT_DelTourCombin(LLONG lLoginID, int nMonitorID, int nCombinID, int waittime=1000);

// �޸Ļ������
CLIENT_API BOOL CALL_METHOD CLIENT_SetTourCombin(LLONG lLoginID, int nMonitorID, int nCombinID, int nSplitType, BYTE *pEncoderChannel, int nBufLen, int waittime=1000);

// ��ѯ������ϣ�nCombinID��Χ0��32
CLIENT_API BOOL CALL_METHOD CLIENT_QueryTourCombin(LLONG lLoginID, int nMonitorID, int nCombinID, LPDEC_COMBIN_INFO lpDecCombinInfo, int waittime=1000);

// ������Ѳ����
CLIENT_API BOOL CALL_METHOD CLIENT_SetDecoderTour(LLONG lLoginID, int nMonitorID, LPDEC_TOUR_COMBIN lpDecTourInfo, int waittime=1000);

// ��ѯ��Ѳ����
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDecoderTour(LLONG lLoginID, int nMonitorID, LPDEC_TOUR_COMBIN lpDecTourInfo, int waittime=1000);

// ��ѯ��ǰ����ͨ������Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDecChannelFlux(LLONG lLoginID, int nDecoderID, LPDEV_DECCHANNEL_STATE lpChannelStateInfo, int waittime=1000);

// ������������Ѳ
CLIENT_API BOOL CALL_METHOD CLIENT_CtrlDecoderTour(LLONG lLoginID, int nMonitorID, DEC_CTRL_TOUR_TYPE emActionParam, int waittime = 1000);
//------------------------------------------------------------------------

typedef void (CALLBACK *fDecPlayBackPosCallBack)(LLONG lLoginID, int nEncoderID, DWORD dwTotalSize, DWORD dwPlaySize, LDWORD dwUser);

// ���ûطŽ��Ȼص�����
CLIENT_API BOOL CALL_METHOD CLIENT_SetDecPlaybackPos(LLONG lLoginID, fDecPlayBackPosCallBack cbPlaybackPos, LDWORD dwUser);

// ������TV����طţ��ӿ�Ϊ�첽��ʽ
CLIENT_API LLONG CALL_METHOD CLIENT_DecTVPlayback(LLONG lLoginID, int nDecoderID, DEC_PLAYBACK_MODE emPlaybackMode, LPVOID lpInBuffer, DWORD dwInBufferSize, void* userdata=NULL);

// ������TV����طſ���
CLIENT_API BOOL CALL_METHOD CLIENT_CtrlDecPlayback(LLONG lLoginID, int nDecoderID, DEC_CTRL_PLAYBACK_TYPE emCtrlType, int nValue, int waittime=1000);

///////////////////////////////�����豸�ӿ�///////////////////////////////

// ʵʱ�ϴ����ܷ������ݣ�ͼƬ
CLIENT_API LLONG CALL_METHOD CLIENT_RealLoadPicture(LLONG lLoginID, int nChannelID, DWORD dwAlarmType, fAnalyzerDataCallBack cbAnalyzerData, LDWORD dwUser);

// ʵʱ�ϴ����ܷ������ݣ�ͼƬ(��չ�ӿڣ�bNeedPicFile��ʾ�Ƿ���ͼƬ�ļ�,Reserved����ΪRESERVED_PARA) 
CLIENT_API LLONG CALL_METHOD CLIENT_RealLoadPictureEx(LLONG lLoginID, int nChannelID, 
													 DWORD dwAlarmType, 
													 BOOL bNeedPicFile, 
													 fAnalyzerDataCallBack cbAnalyzerData, 
													 LDWORD dwUser, 
													 void* Reserved);

// ֹͣ�ϴ����ܷ������ݣ�ͼƬ
CLIENT_API BOOL CALL_METHOD CLIENT_StopLoadPic(LLONG lAnalyzerHandle);

// ����ѯ������ѯ�ļ�
CLIENT_API LLONG	CALL_METHOD CLIENT_FindFileEx(LLONG lLoginID, EM_FILE_QUERY_TYPE emType, void* pQueryCondition, void *reserved, int waittime=1000);	

// �����ļ�:nFilecount:��Ҫ��ѯ������, ����ֵΪý���ļ����� ����ֵ<nFilecount����Ӧʱ����ڵ��ļ���ѯ���
CLIENT_API int	CALL_METHOD CLIENT_FindNextFileEx(LLONG lFindHandle, int nFilecount, void* pMediaFileInfo, int maxlen, void *reserved, int waittime=1000);

// ����¼���ļ�����
CLIENT_API BOOL CALL_METHOD CLIENT_FindCloseEx(LLONG lFindHandle);

// ����ָ�������ܷ������� - ͼƬ
CLIENT_API LLONG CALL_METHOD CLIENT_DownloadMediaFile(LLONG lLoginID,EM_FILE_QUERY_TYPE emType, void* lpMediaFileInfo, char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, LDWORD dwUserData,  void *reserved);

// ֹͣ��������
CLIENT_API BOOL CALL_METHOD CLIENT_StopDownloadMediaFile(LLONG lFileHandle);

// �����������ܷ������ݣ�ͼƬ
CLIENT_API LLONG CALL_METHOD CLIENT_LoadOffLineFile(LLONG lLoginID, int nChannelID, DWORD dwAlarmType, LPNET_TIME_EX lpStartTime, LPNET_TIME_EX lpEndTime, fAnalyzerDataCallBack cbAnalyzerData, LDWORD dwUser);

//��ͣ���ܷ�����������(bPause=TRUE ��ʾ��ͣ����, bPause=FALSE ��ʾ�ָ�����)
CLIENT_API BOOL CALL_METHOD CLIENT_PauseLoadPic(LLONG lLoadHadle, BOOL bPause);

// ��ͨץ��--���紥����ʽ
CLIENT_API BOOL CALL_METHOD CLIENT_TrafficSnapByNetwork(LLONG lLoginID, int nChannelID, NET_IN_SNAPSHOT* pstInParam, NET_OUT_SNAPSHOT* pstOutParam);

// ��ͨ����--ǿ�ƺ��
CLIENT_API BOOL CALL_METHOD CLIENT_TrafficForceLightState(LLONG lLoginID, int nChannelID, NET_IN_FORCELIGHTSTATE* pstInParam, NET_OUT_FORCELIGHTSTATE* pstOutParam, int waittime=1000);

// ��ͨ����ͳ��
CLIENT_API LLONG CALL_METHOD CLIENT_StartTrafficFluxStat(LLONG lLoginID, NET_IN_TRAFFICFLUXSTAT* pstInParam,NET_OUT_TRAFFICFLUXSTAT* pstOutParam);

// ��������ͳ��
CLIENT_API BOOL CALL_METHOD CLIENT_StopTrafficFluxStat(LLONG lFluxStatHandle);

// ��ȡ����ͳ����Ϣ
CLIENT_API LLONG CALL_METHOD CLIENT_StartFindFluxStat(LLONG lLoginID, NET_IN_TRAFFICSTARTFINDSTAT* pstInParam, NET_OUT_TRAFFICSTARTFINDSTAT* pstOutParam);

// ������ѯ����ͳ��
CLIENT_API int	CALL_METHOD CLIENT_DoFindFluxStat(LLONG lFindHandle, NET_IN_TRAFFICDOFINDSTAT* pstInParam,NET_OUT_TRAFFICDOFINDSTAT* pstOutParam);

// ������ѯ����ͳ��
CLIENT_API BOOL CALL_METHOD CLIENT_StopFindFluxStat(LLONG lFindHandle);

// ��ȡ����ͳ����Ϣ
CLIENT_API LLONG CALL_METHOD CLIENT_StartFindNumberStat(LLONG lLoginID, NET_IN_FINDNUMBERSTAT* pstInParam, NET_OUT_FINDNUMBERSTAT* pstOutParam);

// ������ѯ����ͳ��
CLIENT_API int	CALL_METHOD CLIENT_DoFindNumberStat(LLONG lFindHandle, NET_IN_DOFINDNUMBERSTAT* pstInParam, NET_OUT_DOFINDNUMBERSTAT* pstOutParam);

// ������ѯ����ͳ��
CLIENT_API BOOL CALL_METHOD CLIENT_StopFindNumberStat(LLONG lFindHandle);
// ��Ƶ�����豸�ķ�������
CLIENT_API BOOL CALL_METHOD CLIENT_OperateVideoAnalyseDevice(LLONG lLoginID, int nChannelID, char* szCmd, void *pstInParam, void *pstOutParam, int waittime=1000);

// ���ܸ�������ƽӿ�
CLIENT_API BOOL CALL_METHOD CLIENT_ControlIntelliTracker(LLONG lLoginID, NET_IN_CONTROL_INTELLITRACKER* pstInParam, NET_OUT_CONTROL_INTELLITRACKER* pstOutParam);

// ����ʽ�豸�ķ�������,��������μ����涨��CLIENT_OperateMasterSlaveDevice�ӿڲ�������
CLIENT_API BOOL CALL_METHOD CLIENT_OperateMasterSlaveDevice(LLONG lLoginID, int nChannelID, char* szCmd, void *pstInParam, void *pstOutParam, int waittime=1000);

////  ��Ƶ���

// ʵʱ��ȡ��Ƶ��Ͻ��
CLIENT_API BOOL CALL_METHOD CLIENT_StartVideoDiagnosis(LLONG lLoginID, NET_IN_VIDEODIAGNOSIS *pstInParam, NET_OUT_VIDEODIAGNOSIS *pstOutParam);

// ֹͣ��Ƶ��Ͻ���ϱ�
CLIENT_API BOOL CALL_METHOD CLIENT_StopVideoDiagnosis(LLONG hDiagnosisHandle);

// ��ʼ��Ƶ��Ͻ����ѯ
CLIENT_API BOOL CALL_METHOD CLIENT_StartFindDiagnosisResult(LLONG lLoginID, NET_IN_FIND_DIAGNOSIS* pstInParam, NET_OUT_FIND_DIAGNOSIS* pstOutParam);

// ��ȡ��Ƶ��Ͻ����Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_DoFindDiagnosisResult(LLONG hFindHandle,NET_IN_DIAGNOSIS_INFO* pstInParam, NET_OUT_DIAGNOSIS_INFO* pstOutParam);

// ������Ƶ��Ͻ����ѯ
CLIENT_API BOOL CALL_METHOD CLIENT_StopFindDiagnosis(LLONG hFindHandle);

// ��ȡ���ܽ�ͨ��λ״̬
CLIENT_API BOOL CALL_METHOD CLIENT_GetParkingSpaceStatus(LLONG lLoginID, NET_IN_GET_PARKINGSPACE_STATUS* pstInParam, NET_OUT_GET_PARKINGSPACE_STATUS* pstOutParam);

// ����ָ���ĳ�λͼƬ��Ϣ
CLIENT_API LLONG CALL_METHOD CLIENT_AttachParkingSpaceData(LLONG lLoginID, NET_IN_ATTACH_PARKINGSPACE* pstInParam, NET_OUT_ATTACH_PARKINGSPACE* pstOutParam);

// ȡ������ָ���ĳ�λͼƬ��Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_DetachParkingSpaceData(NET_IN_DETACH_PARKINGSPACE* pstInParam, NET_OUT_DETACH_PARKINGSPACE* pstOutParam);

// ��ȡ��λ��״̬
CLIENT_API BOOL CALL_METHOD CLIENT_GetCarPortLightStatus(LLONG lLoginID, NET_IN_GET_CARPORTLIGHT_STATUS* pstInParam, NET_OUT_GET_CARPORTLIGHT_STATUS* pstOutParam, int waittime=1000);

// ���ó�λ��״̬
CLIENT_API BOOL CALL_METHOD CLIENT_SetCarPortLightStatus(LLONG lLoginID, NET_IN_SET_CARPORTLIGHT_STATUS* pstInParam, NET_OUT_SET_CARPORTLIGHT_STATUS* pstOutParam, int waittime=1000);

////////////////////////////////��ƵŨ���ӿ�////////////////////////////////

// ������ƵŨ������
CLIENT_API BOOL CALL_METHOD CLIENT_AddVideoSynopsisTask(LLONG lLoginID,	NET_IN_ADD_VIDEOSYNOPSIS* pstInParam, NET_OUT_ADD_VIDEOSYNOPSIS* pstOutParam);

// ��ͣ��ƵŨ������
CLIENT_API BOOL CALL_METHOD CLIENT_PauseVideoSynopsisTask(LLONG lLoginID, NET_IN_PAUSE_VIDEOSYNOPSIS* pstInParam);

// �Ƴ���ƵŨ������
CLIENT_API BOOL CALL_METHOD CLIENT_RemoveVideoSynopsisTask(LLONG lLoginID, NET_IN_REMOVE_VIDEOSYNOPSIS* pstInParam);

// ����ʵʱŨ����Ƶ������Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_RealLoadObjectData(LLONG lLoginID, NET_IN_REALLOAD_OBJECTDATA* pstInParam, NET_OUT_REALLOAD_OBJECTDATA* pstOutParam);

// ֹͣ����ʵʱŨ����Ƶ������Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_StopLoadObjectData(LLONG lRealLoadHandle, NET_IN_STOPLOAD_OBJECTDATA* pstInParam);

// ����ʵʱŨ����Ƶ������Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_RealLoadSynopsisState(LLONG lLoginID, NET_IN_REALLAOD_SYNOPSISSTATE* pstInParam, NET_OUT_REALLOAD_SYNOPSISSTATE* pstOutParam);

// ֹͣ����ʵʱŨ����Ƶ������Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_StopLoadSynopsisState(LLONG lRealLoadHandle, NET_IN_STOPLOAD_SYNOPSISSTATE* pstInParam);

// ��ѯŨ����Ƶ���������Ϣ�ӿ�
CLIENT_API BOOL CALL_METHOD CLIENT_QueryVideoSynopsisInfo(LLONG lLoginID, NET_IN_QUERY_VIDEOSYNOPSIS* pstInParam, NET_OUT_QUERY_VIDEOSYNOPSIS* pstuOutParam);

// ����ѯ������ѯ��ƵŨ���ļ�
CLIENT_API BOOL	CALL_METHOD CLIENT_FindSynopsisFile(LLONG lLoginID, NET_IN_FIND_SYNOPSISFILE *pstInParam, NET_OUT_FIND_SYNOPSISFILE *pstOutParam);	

// ������ƵŨ���ļ�
CLIENT_API BOOL	CALL_METHOD CLIENT_FindNextSynopsisFile(LLONG lFindHandle, NET_IN_FINDNEXT_SYNOPSISFILE *pstInParam, NET_OUT_FINDNEXT_SYNOPSISFILE *pstOutParam);

// ������ƵŨ���ļ�����
CLIENT_API BOOL CALL_METHOD CLIENT_SynopsisFindClose(LLONG lFindHandle);

// ������ƵŨ������ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_DownLoadSynosisFile(LLONG lLoginID, NET_IN_DOWNLOAD_SYNOPSISFILE *pstInParam, NET_OUT_DOWNLOAD_SYNOPSISFILE *pstOutParam);

// ֹͣ����
CLIENT_API BOOL CALL_METHOD CLIENT_StopLoadSynosisFile(LLONG lDownLoadHandle);

// ����Ũ����Ƶ�����������ļ�(��)·���������ļ���Ϣ
CLIENT_API BOOL	CALL_METHOD	CLIENT_SetFilePathInfo(LLONG lLoginID, NET_IN_SET_FILEPATHINFO* pstInParam);

// ���������ļ���Ϣ״̬
CLIENT_API LLONG CALL_METHOD CLIENT_AttachAddFileState(LLONG lLoginID, const NET_IN_ADDFILE_STATE* pstInParam, NET_OUT_ADDFILE_STATE *pstOutParam, int nWaitTime = 1000);

// ȡ�����������ļ���Ϣ״, lAttachHandle��CLIENT_AttacAddFileState����ֵ
CLIENT_API LLONG CALL_METHOD CLIENT_DetachAddFileState(LLONG lAttachHandle);

//////////////////////////////// ��¼�ϴ��ӿ� /////////////////////////////////
// ������¼״̬
CLIENT_API LLONG CALL_METHOD CLIENT_AttachBurnState(LLONG lLoginID, const NET_IN_ATTACH_STATE* pstInParam, NET_OUT_ATTACH_STATE *pstOutParam, int nWaitTime = 1000);

// ��¼�ϴ���ʼ ���ش˴��ϴ��������, ע�����½ӿڲ�����fAttachBurnStateCB�ص������������
CLIENT_API LLONG CALL_METHOD CLIENT_StartUploadFileBurned(LLONG lLoginID, const NET_IN_FILEBURNED_START* pstInParam, NET_OUT_FILEBURNED_START *pstOutParam, int nWaitTime = 1000);

// ��¼�ϴ��ļ���lUploadHandle��CLIENT_StartUploadFileBurned����ֵ
CLIENT_API BOOL	CALL_METHOD	CLIENT_SendFileBurned(LLONG lUploadHandle);

// ��¼�ϴ�ֹͣ��lUploadHandle��CLIENT_StartUploadFileBurned����ֵ,�˽ӿڲ�����fBurnFileCallBack�ص������е���
CLIENT_API BOOL	CALL_METHOD	CLIENT_StopUploadFileBurned(LLONG lUploadHandle);

// ȡ��������¼״̬��lAttachHandle��CLIENT_AttachBurnState����ֵ
CLIENT_API BOOL CALL_METHOD CLIENT_DetachBurnState(LLONG lAttachHandle);

//////////////////////////////// �߼��豸 /////////////////////////////////////////

// ��������ͷ״̬
CLIENT_API LLONG CALL_METHOD CLIENT_AttachCameraState(LLONG lLoginID, const NET_IN_CAMERASTATE* pstInParam, NET_OUT_CAMERASTATE *pstOutParam, int nWaitTime = 3000);

// ֹͣ��������ͷ״̬��lAttachHandle��CLIENT_AttachCameraState����ֵ
CLIENT_API BOOL	CALL_METHOD	CLIENT_DetachCameraState(LLONG lAttachHandle);

// ��ȡ������Ч��ʾԴ
CLIENT_API BOOL CALL_METHOD CLIENT_MatrixGetCameras(LLONG lLoginID, const DH_IN_MATRIX_GET_CAMERAS* pInParam, DH_OUT_MATRIX_GET_CAMERAS* pOutParam, int nWaitTime = 1000);

// �����߼��豸
CLIENT_API BOOL CALL_METHOD CLIENT_MatrixAddCameras(LLONG lLoginID, const DH_IN_ADD_LOGIC_DEVICE_CAMERA* pInParam, DH_OUT_ADD_LOGIC_DEVICE_CAMERA* pOutParam, int nWaitTime = 1000);

//////////////////////////////// ����ӿ� /////////////////////////////////

// ��ѯ��Ʒ����
CLIENT_API BOOL CALL_METHOD CLIENT_QueryProductionDefinition(LLONG lLoginID, DH_PRODUCTION_DEFNITION* pstuProdDef, int nWaitTime = 1000);

// ��ѯ�����ӿ���Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryMatrixCardInfo(LLONG lLoginID, DH_MATRIX_CARD_LIST* pstuCardList, int nWaitTime = 1000);

// ��ѯϵͳ״̬
CLIENT_API BOOL CALL_METHOD	CLIENT_QuerySystemStatus(LLONG lLoginID, DH_SYSTEM_STATUS* pstuStatus, int nWaitTime = 1000);

// ��ѯ�ָ�����
CLIENT_API BOOL CALL_METHOD CLIENT_GetSplitCaps(LLONG lLoginID, int nChannel, DH_SPLIT_CAPS* pstuCaps, int nWaitTime = 1000);

// ��ѯ/������ʾԴ
CLIENT_API BOOL CALL_METHOD CLIENT_GetSplitSource(LLONG lLoginID, int nChannel, int nWindow, DH_SPLIT_SOURCE* pstuSplitSrc, int nMaxCount, int* pnRetCount, int nWaitTime = 1000);
CLIENT_API BOOL CALL_METHOD CLIENT_SetSplitSource(LLONG lLoginID, int nChannel, int nWindow, const DH_SPLIT_SOURCE* pstuSplitSrc, int nSrcCount, int nWaitTime = 1000);

// ��ѯ/���÷ָ�ģʽ
CLIENT_API BOOL CALL_METHOD CLIENT_GetSplitMode(LLONG lLoginID, int nChannel, DH_SPLIT_MODE_INFO* pstuSplitInfo, int nWaitTime = 1000);
CLIENT_API BOOL CALL_METHOD CLIENT_SetSplitMode(LLONG lLoginID, int nChannel, const DH_SPLIT_MODE_INFO* pstuSplitInfo, int nWaitTime = 1000);

// ��ѯ�ָ��������
CLIENT_API BOOL CALL_METHOD CLIENT_GetSplitGroupCount(LLONG lLoginID, int nChannel, DH_SPLIT_MODE emSplitMode, int* pnGroupCount, int nWaitTime = 1000);

// ��ѯ��Ƶ�������
CLIENT_API BOOL CALL_METHOD CLIENT_GetVideoOutCaps(LLONG lLoginID, int nChannel, DH_VIDEO_OUT_CAPS* pstuCaps, int nWaitTime = 1000);

// ������Ƶ���ѡ��
CLIENT_API BOOL CALL_METHOD CLIENT_SetVideoOutOption(LLONG lLoginID, int nChannel, const DH_VIDEO_OUT_OPT* pstuVideoOut, int nWaitTime = 1000);

// ��ѯ��Ƶ����ͨ��Ŀǰ���ĸ����������ʾ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryVideoOutWindows(LLONG lLoginID, int nChannel, DH_VIDEO_OUT_WINDOW* pstuWnds, int nMaxWndCount, int* pnRetWndCount, int nWaitTime = 1000);

// ���ô���λ��
CLIENT_API BOOL CALL_METHOD	CLIENT_SetSplitWindowRect(LLONG lLoginID, const DH_IN_SPLIT_SET_RECT* pInParam, DH_OUT_SPLIT_SET_RECT* pOutParam, int nWaitTime = 1000);
CLIENT_API BOOL	CALL_METHOD	CLIENT_GetSplitWindowRect(LLONG lLoginID, const DH_IN_SPLIT_GET_RECT* pInParam, DH_OUT_SPLIT_GET_RECT* pOutParam, int nWaitTime = 1000);

// ����/�ش�
CLIENT_API BOOL CALL_METHOD CLIENT_OpenSplitWindow(LLONG lLoginID, const DH_IN_SPLIT_OPEN_WINDOW* pInParam, DH_OUT_SPLIT_OPEN_WINDOW* pOutParam, int nWaitTime = 1000);
CLIENT_API BOOL CALL_METHOD CLIENT_CloseSplitWindow(LLONG lLoginID, const DH_IN_SPLIT_CLOSE_WINDOW* pInParam, DH_OUT_SPLIT_CLOSE_WINDOW* pOutParam, int nWaitTime = 1000);

// ���ô��ڴ���
CLIENT_API BOOL CALL_METHOD CLIENT_SetSplitTopWindow(LLONG lLoginID, const DH_IN_SPLIT_SET_TOP_WINDOW* pInParam, DH_OUT_SPLIT_SET_TOP_WINDOW* pOutParam, int nWaitTime = 1000);

// ��ȡ��ǰ��ʾ�Ĵ�����Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_GetSplitWindowsInfo(LLONG lLoginID, const DH_IN_SPLIT_GET_WINDOWS* pInParam, DH_OUT_SPLIT_GET_WINDOWS* pOutParam, int nWaitTime = 1000);

// ����/�����ղؼ�
CLIENT_API BOOL CALL_METHOD	CLIENT_LoadSplitCollection(LLONG lLoginID, const DH_IN_SPLIT_LOAD_COLLECTION* pInParam, DH_OUT_SPLIT_LOAD_COLLECTION* pOutParam, int nWaitTime = 1000);
CLIENT_API BOOL CALL_METHOD	CLIENT_SaveSplitCollection(LLONG lLoginID, const DH_IN_SPLIT_SAVE_COLLECTION* pInParam, DH_OUT_SPLIT_SAVE_COLLECTION* pOutParam, int nWaitTime = 1000);

// ��ȡ�ղؼ���Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_GetSplitCollections(LLONG lLoginID, const DH_IN_SPLIT_GET_COLLECTIONS* pInParam, DH_OUT_SPLIT_GET_COLLECTIONS* pOutParam, int nWaitTime = 1000);

// �������ղؼ�
CLIENT_API BOOL	CALL_METHOD CLIENT_RenameSplitCollection(LLONG lLoginID, const DH_IN_SPLIT_RENAME_COLLECTION* pInParam, DH_OUT_SPLIT_RENAME_COLLECTION* pOutParam, int nWaitTime = 1000);

// ɾ���ղؼ�
CLIENT_API BOOL CALL_METHOD CLIENT_DeleteSplitCollection(LLONG lLoginID, const DH_IN_SPLIT_DELETE_COLLECTION* pInParam, DH_OUT_SPLIT_DELETE_COLLECTION* pOutParam, int nWaitTime = 1000);

// �������
CLIENT_API BOOL CALL_METHOD CLIENT_SetDecodePolicy(LLONG lLoginID, const DH_IN_SET_DEC_POLICY* pInParam, DH_OUT_SET_DEC_POLICY* pOutParam, int nWaitTime = 1000);
CLIENT_API BOOL CALL_METHOD CLIENT_GetDecodePolicy(LLONG lLoginID, const DH_IN_GET_DEC_POLICY* pInParam, DH_OUT_GET_DEC_POLICY* pOutParam, int nWaitTime = 1000);

// ��Ƶ���ģʽ
CLIENT_API BOOL CALL_METHOD CLIENT_SetSplitAudioOuput(LLONG lLoginID, const DH_IN_SET_AUDIO_OUTPUT* pInParam, DH_OUT_SET_AUDIO_OUTPUT* pOutParam, int nWaitTime = 1000);
CLIENT_API BOOL CALL_METHOD CLIENT_GetSplitAudioOuput(LLONG lLoginID, const DH_IN_GET_AUDIO_OUTPUT* pInParam, DH_OUT_GET_AUDIO_OUTPUT* pOutParam, int nWaitTime = 1000);

// ������ʾԴ
CLIENT_API BOOL CALL_METHOD CLIENT_MatrixSetCameras(LLONG lLoginID, const DH_IN_MATRIX_SET_CAMERAS* pInParam, DH_OUT_MATRIX_SET_CAMERAS* pOutParam, int nWaitTime = 1000);

// ��ȡ��Ƶ��������
CLIENT_API BOOL CALL_METHOD CLIENT_GetVideoInCaps(LLONG lLoginID, const DH_IN_GET_VIDEO_IN_CAPS* pInParam, DH_OUT_GET_VIDEO_IN_CAPS* pOutParam, int nWaitTime = 1000);

// ��ȡ��Ƶ���ģʽ
CLIENT_API BOOL CALL_METHOD CLIENT_EnumVideoOutModes(LLONG lLoginID, const DH_IN_ENUM_VIDEO_OUT_MODES* pInParam, DH_OUT_ENUM_VIDEO_OUT_MODES* pOutParam, int nWaitTime = 1000);

// ��ȡ/���ý��봰�����OSD��Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_GetSplitOSD(LLONG lLoginID, const DH_IN_SPLIT_GET_OSD* pInParam, DH_OUT_SPLIT_GET_OSD* pOutParam, int nWaitTime = 1000);
CLIENT_API BOOL CALL_METHOD CLIENT_SetSplitOSD(LLONG lLoginID, const DH_IN_SPLIT_SET_OSD* pInParam, DH_OUT_SPLIT_SET_OSD* pOutParam, int nWaitTime = 1000);

//////////////////////////////////// ����ǽ���� //////////////////////////////////////

// ��Դ����
CLIENT_API BOOL CALL_METHOD CLIENT_PowerControl(LLONG lLoginID, const DH_IN_WM_POWER_CTRL* pInParam, DH_OUT_WM_POWER_CTRL* pOutParam, int nWaitTime = 1000);

// ��ȡ/������ʾģʽ
CLIENT_API BOOL CALL_METHOD CLIENT_SetDisplayMode(LLONG lLoginID, const DH_IN_WM_SET_DISPLAY_MODE* pInParam, DH_OUT_WM_SET_DISPLAY_MODE* pOutParam, int nWaitTime = 1000);
CLIENT_API BOOL CALL_METHOD CLIENT_GetDisplayMode(LLONG lLoginID, const DH_IN_WM_GET_DISPLAY_MODE* pInParam, DH_OUT_WM_GET_DISPLAY_MODE* pOutParam, int nWaitTime = 1000);

// ����/����Ԥ��
CLIENT_API BOOL CALL_METHOD	CLIENT_LoadMonitorWallCollection(LLONG lLoginID, const DH_IN_WM_LOAD_COLLECTION* pInParam, DH_OUT_WM_LOAD_COLLECTION* pOutParam, int nWaitTime = 1000);
CLIENT_API BOOL CALL_METHOD	CLIENT_SaveMonitorWallCollection(LLONG lLoginID, const DH_IN_WM_SAVE_COLLECTION* pInParam, DH_OUT_WM_SAVE_COLLECTION* pOutParam, int nWaitTime = 1000);

// ��ȡ����ǽԤ��
CLIENT_API BOOL CALL_METHOD CLIENT_GetMonitorWallCollections(LLONG lLoginID, const DH_IN_WM_GET_COLLECTIONS* pInParam, DH_OUT_WM_GET_COLLECTIONS* pOutParam, int nWaitTime = 1000);

// ����ǽԤ��������
CLIENT_API BOOL	CALL_METHOD CLIENT_RenameMonitorWallCollection(LLONG lLoginID, const DH_IN_WM_RENAME_COLLECTION* pInParam, DH_OUT_WM_RENAME_COLLECTION* pOutParam, int nWaitTime = 1000);

// ��ȡ/���õ���ǽ����
CLIENT_API BOOL CALL_METHOD CLIENT_MonitorWallGetScene(LLONG lLoginID, const DH_IN_MONITORWALL_GET_SCENE* pInParam, DH_OUT_MONITORWALL_GET_SCENE* pOutParam, int nWaitTime = 1000);
CLIENT_API BOOL CALL_METHOD CLIENT_MonitorWallSetScene(LLONG lLoginID, const DH_IN_MONITORWALL_SET_SCENE* pInParam, DH_OUT_MONITORWALL_SET_SCENE* pOutParam, int nWaitTime = 1000);

// ��ȡ����ǽ��ʾ��Ԫ������
CLIENT_API BOOL CALL_METHOD CLIENT_MonitorWallGetAttributeCaps(LLONG lLoginID, const DH_IN_MONITORWALL_GET_ARRT_CAPS* pInParam, DH_OUT_MONITORWALL_GET_ARRT_CAPS* pOutParam, int nWaitTime = 1000);

// ����ǽ��ʾ��Ԫ�Զ�����
CLIENT_API BOOL CALL_METHOD CLIENT_MonitorWallAutoAdjust(LLONG lLoginID, const DH_IN_MONITORWALL_AUTO_ADJUST* pInParam, DH_OUT_MONITORWALL_AUTO_ADJUST* pOutParam, int nWaitTime = 1000);

// ���õ���ǽ��ʾ��Ԫ����
CLIENT_API BOOL CALL_METHOD CLIENT_MonitorWallSetAttribute(LLONG lLoginID, const DH_IN_MONITORWALL_SET_ATTR* pInParam, DH_OUT_MONITORWALL_SET_ATTR* pOutParam, int nWaitTime = 1000);

// ���ñ���ģʽ
CLIENT_API BOOL CALL_METHOD CLIENT_MonitorWallSetBackLight(LLONG lLoginID, const DH_IN_MONITORWALL_SET_BACK_LIGHT* pInParam, DH_OUT_MONITORWALL_SET_BACK_LIGHT* pOutParam, int nWaitTime = 1000);

///////////////////////////////// ��֯Ŀ¼���� /////////////////////////////////////////

// ��֯Ŀ¼����-���ӽڵ�
CLIENT_API BOOL CALL_METHOD CLIENT_OrganizationAddNodes(LLONG lLoginID, const DH_IN_ORGANIZATION_ADD_NODES* pInParam, DH_OUT_ORGANIZATION_ADD_NODES* pOutParam, int nWaitTime = 1000);

// ��֯Ŀ¼����-ɾ���ڵ�
CLIENT_API BOOL CALL_METHOD CLIENT_OrganizationDeleteNodes(LLONG lLoginID, const DH_IN_ORGANIZATION_DELETE_NODES* pInParam, DH_OUT_ORGANIZATION_DELETE_NODES* pOutParam, int nWaitTime = 1000);

// ��֯Ŀ¼����-��ȡ�ڵ���Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_OrganizationGetNodes(LLONG lLoginID, const DH_IN_ORGANIZATION_GET_NODES* pInParam, DH_OUT_ORGANIZATION_GET_NODES* pOutParam, int nWaitTime = 1000);

// ��֯Ŀ¼����-���ýڵ�
CLIENT_API BOOL CALL_METHOD CLIENT_OrganizationSetNode(LLONG lLoginID, const DH_IN_ORGANIZATION_SET_NODE* pInParam, DH_OUT_ORGANIZATION_SET_NODE* pOutParam, int nWaitTime = 1000);


//////////////////////////////// ����ץ�� /////////////////////////////////

// ��ʼץ��
CLIENT_API LLONG CALL_METHOD CLIENT_StartSniffer(LLONG lLoginID, const DH_IN_START_SNIFFER* pInParam, DH_OUT_START_SNIFFER* pOutParam, int nWaitTime = 1000);

// ֹͣץ��
CLIENT_API BOOL CALL_METHOD CLIENT_StopSniffer(LLONG lLoginID, LLONG lSnifferID);

// ��ȡץ��״̬
CLIENT_API BOOL CALL_METHOD CLIENT_GetSnifferInfo(LLONG lLoginID, const DH_IN_GET_SNIFFER_INFO* pInParam, DH_OUT_GET_SNIFFER_INFO* pOutParam, int nWaitTime = 1000);


//////////////////////////////// Զ���ļ����� /////////////////////////////////

// �½��ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_CreateRemoteFile(LLONG lLoginID, const DH_IN_CREATE_REMOTE_FILE* pInParam, DH_OUT_CREATE_REMOTE_FILE* pOutParam, int nWaitTime = 1000);

// ɾ���ļ���Ŀ¼
CLIENT_API BOOL CALL_METHOD CLIENT_RemoveRemoteFiles(LLONG lLoginID, const DH_IN_REMOVE_REMOTE_FILES* pInParam, DH_OUT_REMOVE_REMOTE_FILES* pOutParam, int nWaitTime = 1000);

// ������
CLIENT_API BOOL CALL_METHOD CLIENT_RenameRemoteFile(LLONG lLoginID, const DH_IN_RENAME_REMOTE_FILE* pInParam, DH_OUT_RENAME_REMOTE_FILE* pOutParam, int nWaitTime = 1000);

// ��ʾĿ¼���ļ�����Ŀ¼
CLIENT_API BOOL CALL_METHOD CLIENT_ListRemoteFile(LLONG lLoginID, const DH_IN_LIST_REMOTE_FILE* pInParam, DH_OUT_LIST_REMOTE_FILE* pOutParam, int nWaitTime = 1000);

// ͬ���ļ��ϴ�, ֻ������С�ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_UploadRemoteFile(LLONG lLoginID, const DH_IN_UPLOAD_REMOTE_FILE* pInParam, DH_OUT_UPLOAD_REMOTE_FILE* pOutParam, int nWaitTime = 1000);

////////////////////////////////// �洢�豸���� ////////////////////////////////////////

// ��ȡISCSI Target�б�, pInParam == NULL��ȡ����targets
CLIENT_API BOOL CALL_METHOD	CLIENT_GetISCSITargets(LLONG lLoginID, const DH_IN_ISCSI_TARGETS* pInParam, DH_OUT_ISCSI_TARGETS* pOutParam, int nWaitTime = 1000);

// ��ȡ�洢�豸�����б�
CLIENT_API BOOL CALL_METHOD	CLIENT_GetStorageDeviceNames(LLONG lLoginID, DH_STORAGE_DEVICE_NAME* pstuNames, int nMaxCount, int* pnRetCount, int nWaitTime = 1000);

// ��ȡ�洢�豸��Ϣ
CLIENT_API BOOL CALL_METHOD	CLIENT_GetStorageDeviceInfo(LLONG lLoginID, const char* pszDevName, DH_STORAGE_DEVICE* pDevice, int nWaitTime = 1000);

/////////////////////////////////// �����豸 ///////////////////////////////////////

// ����������ƵԴ
CLIENT_API BOOL CALL_METHOD CLIENT_MatrixSearch(LLONG lLoginID, const DH_IN_MATRIX_SEARCH* pInParam, DH_OUT_MATRIX_SEARCH* pOutParam, int nWaitTime = 1000);

// ��ȡ�����������б�
CLIENT_API BOOL CALL_METHOD CLIENT_GetMatrixTree(LLONG lLoginID, const DH_IN_GET_MATRIX_TREE* pInParam, DH_OUT_GET_MATRIX_TREE* pOutParam, int nWaitTime = 1000);

// ��ȡ�����ϼ��豸�б���Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_GetSuperiorMatrixList(LLONG lLoginID, const DH_IN_GET_SUPERIOR_MATRIX_LIST* pInParam, DH_OUT_GET_SUPERIOR_MATRIX_LIST* pOutParam, int nWaitTime = 1000);

// ��ʼ¼�񱸷ݻָ�
CLIENT_API LLONG CALL_METHOD CLIENT_StartRecordBackupRestore(LLONG lLoginID);

// ֹͣ¼�񱸷ݻָ�
CLIENT_API void CALL_METHOD CLIENT_StopRecordBackupRestore(LLONG lRestoreID);

// ����¼�񱸷ݻָ�����
CLIENT_API BOOL CALL_METHOD CLIENT_AddRecordBackupRestoreTask(LLONG lRestoreID, const DH_IN_ADD_REC_BAK_RST_TASK* pInParam, int nWaitTime = 1000);

// ɾ��¼�񱸷ݻָ�����
CLIENT_API BOOL CALL_METHOD CLIENT_RemoveRecordBackupRestoreTask(LLONG lRestoreID, const DH_IN_REMOVE_REC_BAK_RST_TASK* pInParam, int nWaitTime = 1000);

// ��ȡ¼�񱸷ݻָ�������Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordBackupRestoreTask(LLONG lRestoreID, const DH_IN_QUERY_REC_BAK_RST_TASK* pInParam, DH_OUT_QUERY_REC_BAK_RST_TASK* pOutParam, int nWaitTime = 1000);

//////////////////////////////// Encode Manager  ////////////////////////////////
// ˾����¼�л�ȡ����ƻ�����
CLIENT_API BOOL CALL_METHOD CLIENT_GetEncodePlan(LLONG lLoginID, const DH_IN_GET_ENCODE_PLAN* pInParam, DH_OUT_GET_ENCODE_PLAN* pOutParam, int nWaitTime = 1000);


///////////////////////////////����汾�ӿ�///////////////////////////////

// ��ѯ�豸��־--��չ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryLogEx(LLONG lLoginID, DH_LOG_QUERY_TYPE logType, char *pLogBuffer, int maxlen, int *nLogBufferlen, void* reserved, int waittime=3000);

// ����ע���ض����ܣ�������������
CLIENT_API LONG CALL_METHOD CLIENT_ControlConnectServer(LLONG lLoginID, char* RegServerIP, WORD RegServerPort, int TimeOut=3000);

// ��������ע��
CLIENT_API BOOL CALL_METHOD CLIENT_ControlRegisterServer(LLONG lLoginID, LONG ConnectionID, int waittime=1000);

// �Ͽ���������
CLIENT_API BOOL CALL_METHOD CLIENT_ControlDisconnectRegServer(LLONG lLoginID, LONG ConnectionID);

// ��ѯ�豸������ע���������Ϣ
CLIENT_API BOOL CALL_METHOD CLIENT_QueryControlRegServerInfo(LLONG lLoginID, LPDEV_SERVER_AUTOREGISTER lpRegServerInfo, int waittime=2000);

// �ļ��ϴ��ӿ�
CLIENT_API LLONG CALL_METHOD CLIENT_FileTransmit(LLONG lLoginID, int nTransType, char* szInBuf, int nInBufLen, fTransFileCallBack cbTransFile, LDWORD dwUserData, int waittime);

// web��Ϣ�ϴ��ӿ�
CLIENT_API BOOL  CALL_METHOD CLIENT_TransmitInfoForWeb(LLONG lLoginID, char* szInBuffer, DWORD dwInBufferSize, char* szOutBuffer, DWORD dwOutBufferSize, void* pReserved, int waittime=500);

// ˮӡ���, *nResult = 0-��ʾ��ǰͼƬδ���޸� *nResult = 1-��ʾ��ǰͼƬ�ѱ��޸�
CLIENT_API BOOL  CALL_METHOD CLIENT_WatermarkVerifyForPicture(char* szFilePath, int* nResult, void* pReserved);

// ��ͨ����ϴ򿪼���
CLIENT_API BOOL  CALL_METHOD CLIENT_MultiRealPlay(LLONG lLoginID, DHDEV_IN_MULTIPLAY_PARAM* pInBuf, int nInBufLen, DHDEV_OUT_MULTIPLAY_PARAM* pOutBuf, int nOutBufLen, int* pRetLen);
 
// ��ͨ��ֹͣ����
CLIENT_API BOOL  CALL_METHOD CLIENT_StopMultiRealPlay(LLONG* lRealHandles, int nNumOfHandles);

// ���ûطŵ�YUV���ݻص��ӿڣ���hwnd��Ϊ��ʱ��Ч
CLIENT_API BOOL CALL_METHOD CLIENT_SetPlaybackYUVCallBack(LLONG lPlayHandle, fYUVDataCallBack cYUVData, LDWORD dwUser);

// web��ȡ����
CLIENT_API BOOL CALL_METHOD CLIENT_GetNewDevConfigForWeb(LLONG lLoginID, char* szCommand, int nChannelID, char* szOutBuffer, DWORD dwOutBufferSize, int *error, int waittime=500);

// web��������
CLIENT_API BOOL CALL_METHOD CLIENT_SetNewDevConfigForWeb(LLONG lLoginID, char* szCommand, int nChannelID, char* szInBuffer, DWORD dwInBufferSize, int *error, int *restart, int waittime=500);

/////////////////////////////////��̭�ӿ�/////////////////////////////////

// ��ѯϵͳ���������ã��ýӿ�����̭����ʹ��CLIENT_GetDevConfig
CLIENT_API BOOL CALL_METHOD CLIENT_QueryConfig(LLONG lLoginID, int nConfigType, char *pConfigbuf, int maxlen, int *nConfigbuflen, int waittime=1000);

// ����ϵͳ���������ã��ýӿ�����̭����ʹ��CLIENT_SetDevConfig
CLIENT_API BOOL CALL_METHOD CLIENT_SetupConfig(LLONG lLoginID, int nConfigType, char *pConfigbuf, int nConfigbuflen, int waittime=1000);

// �ýӿ�����̭���벻Ҫʹ��
CLIENT_API BOOL CALL_METHOD CLIENT_Reset(LLONG lLoginID, BOOL bReset);

// ��ѯ����Э�� �� �ýӿ�����̭����ʹ��CLIENT_GetDevConfig
CLIENT_API BOOL CALL_METHOD CLIENT_QueryComProtocol(LLONG lLoginID, int nProtocolType, char *pProtocolBuffer, int maxlen, int *nProtocollen, int waittime=1000);

// ��ʼ�Խ����ýӿ�����̭����ʹ��CLIENT_StartTalkEx
CLIENT_API BOOL CALL_METHOD CLIENT_StartTalk(LLONG lRealHandle, BOOL bCustomSend=false);

// �����Խ����ýӿ�����̭����ʹ��CLIENT_StopTalkEx
CLIENT_API BOOL CALL_METHOD CLIENT_StopTalk(LLONG lRealHandle);

// �����Զ���Խ����ݣ��ýӿ�����̭����ʹ��CLIENT_TalkSendData
CLIENT_API BOOL CALL_METHOD CLIENT_SendTalkData_Custom(LLONG lRealHandle, char *pBuffer, DWORD dwBufSize);

// ����ʵʱԤ�������С
CLIENT_API BOOL CALL_METHOD CLIENT_SetPlayerBufNumber(LLONG lRealHandle, DWORD dwBufNum);

// ͨ��ʱ�������ļ�
CLIENT_API BOOL CALL_METHOD CLIENT_GetFileByTime(LLONG lLoginID, int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, char *sSavedFileName);

// ����طſ���
CLIENT_API BOOL CALL_METHOD CLIENT_PlayBackControl(LLONG lPlayHandle, DWORD dwControlCode, DWORD dwInValue, DWORD *lpOutValue);

// ��ѯ�豸����״̬ �ýӿ�����̭����ʹ��CLIENT_QueryDevState
CLIENT_API BOOL CALL_METHOD CLIENT_GetDEVWorkState(LLONG lLoginID, LPNET_DEV_WORKSTATE lpWorkState, int waittime=1000);

// �첽��ѯ�豸��־
CLIENT_API BOOL CALL_METHOD CLIENT_QueryLogCallback(LLONG lLoginID, fLogDataCallBack cbLogData, LDWORD dwUser);



#ifdef __cplusplus
}
#endif

#endif // 
