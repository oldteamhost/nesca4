
#ifndef DHSYSABLE_H
#define DHSYSABLE_H


//////////////////////////////////////////////////////////////////////////
//	查询类型
typedef enum
{
	ABILITY_DYNAMIC_CONNECT = 1,        // 查询动态多连接能力
	ABILITY_WATERMARK_CFG = 17,			// 水印配置能力
	ABILITY_WIRELESS_CFG = 18,			// wireless配置能力
	ABILITY_DEVALL_INFO = 26,			// 设备的能力列表
	ABILITY_CARD_QUERY = 0x0100,		// 卡号查询能力
	ABILITY_MULTIPLAY = 0x0101,			// 多画面预览能力
	ABILITY_QUICK_QUERY_CFG = 0x0102,	// 快速查询配置能力
	ABILITY_INFRARED = 0x0121,			// 无线报警能力
	ABILITY_TRIGGER_MODE = 0x0131,		// 报警输出触发方式能力
	ABILITY_DISK_SUBAREA = 0x0141,		// 网络硬盘分区能力
	ABILITY_DSP_CFG = 0x0151,			// 查询DSP能力
	ABILITY_STREAM_MEDIA = 0x0161,		// 查询SIP,RTSP能力
	ABILITY_INTELLI_TRACKER = 0x0171,   // 查询智能跟踪能力
} DH_SYS_ABILITY;

//////////////////////////////////////////////////////////////////////////
//	设备支持功能列表
enum 
{
	EN_FTP = 0,							// FTP 按位，1：传送录像文件 2：传送抓图文件
	EN_SMTP,							// SMTP 按位，1：报警传送文本邮件 2：报警传送图片 3:支持健康邮件功能
	EN_NTP,								// NTP	按位：1：调整系统时间
	EN_AUTO_MAINTAIN,					// 自动维护 按位：1：重启 2：关闭 3:删除文件
	EN_VIDEO_COVER,						// 区域遮挡 按位：1：多区域遮挡
	EN_AUTO_REGISTER,					// 主动注册	按位：1：注册后sdk主动登陆
	EN_DHCP,							// DHCP	按位：1：DHCP
	EN_UPNP,							// UPNP	按位：1：UPNP
	EN_COMM_SNIFFER,					// 串口抓包 按位：1:CommATM
	EN_NET_SNIFFER,						// 网络抓包 按位： 1：NetSniffer
	EN_BURN,							// 刻录功能 按位：1：查询刻录状态
	EN_VIDEO_MATRIX,					// 视频矩阵 按位：1：是否支持视频矩阵 2:是否支持SPOT视频矩阵 3:是否支持HDMI视频矩阵
	EN_AUDIO_DETECT,					// 音频检测 按位：1：是否支持音频检测
	EN_STORAGE_STATION,					// 存储位置 按位：1：Ftp服务器(Ips) 2：SMB 3：NFS 4：ISCSI 16：DISK 17：U盘
	EN_IPSSEARCH,						// IPS存储查询 按位：1：IPS存储查询	
	EN_SNAP,							// 抓图  按位：1：分辨率2：帧率3：抓图方式4：抓图文件格式5：图画质量
	EN_DEFAULTNIC,						// 支持默认网卡查询 按位 1：支持
	EN_SHOWQUALITY,						// CBR模式下显示画质配置项 按位 1:支持
	EN_CONFIG_IMEXPORT,					// 配置导入导出功能能力 按位 1:支持
	EN_LOG,								// 是否支持分页方式的日志查询 按位 1：支持
	EN_SCHEDULE,						// 录像设置的一些能力 按位 1:冗余 2:预录 3:录像时间段
	EN_NETWORK_TYPE,					// 网络类型按位表示 1:以态网 2:无线局域 3:CDMA/GPRS 4:CDMA/GPRS多网卡配置
	EN_MARK_IMPORTANTRECORD,			// 标识重要录像 按位:1：设置重要录像标识
	EN_ACFCONTROL,						// 活动帧率控制 按位：1：支持活动帧率控制, 2:支持定时报警类型活动帧率控制(不支持动检),该能力与ACF能力互斥
	EN_MULTIASSIOPTION,					// 多路辅码流 按位：1：支持三路辅码流, 2:支持辅码流编码压缩格式独立设置
	EN_DAVINCIMODULE,					// 组件化模块 按位：1，时间表分开处理 2:标准I帧间隔设置
	EN_GPS,                             // GPS功能 按位：1：Gps定位功能
	EN_MULTIETHERNET,					// 支持多网卡查询 按位 1：支持
	EN_LOGIN_ATTRIBUTE,                 // Login属性 按位：1：支持Login属性查询
	EN_RECORD_GENERAL,					// 录像相关 按位：1，普通录像；2：报警录像；3：动态检测录像；4：本地存储；5：远程存储；6：冗余存储；7：本地紧急存储；8：支持区分主辅码流的远程存储
	EN_JSON_CONFIG,						// Json格式配置:按位：1支持Json格式, 2: 使用F6的NAS配置, 3: 使用F6的Raid配置, 4：使用F6的MotionDetect配置, 5：完整支持三代配置(V3)，通过F6命令访问
	EN_HIDE_FUNCTION,					// 屏蔽功能：按位：1，屏蔽PTZ云台功能, 2: 屏蔽3G的保活时段功能
	EN_DISK_DAMAGE,                     // 硬盘坏道信息支持能力: 按位：1，硬盘坏道信息查询支持能力
	EN_PLAYBACK_SPEED_CTRL,				// 支持回放网传速度控制:按位:1，支持回放加速
	EN_HOLIDAYSCHEDULE,					// 支持假期时间段配置:按位:1，支持假期时间段配置
	EN_FETCH_MONEY_TIMEOUT,				// ATM取钱超时
	EN_BACKUP_VIDEO_FORMAT,				// 备份支持的格式，按位：1:DAV, 2:ASF
	EN_QUERY_DISK_TYPE,                 // 支持硬盘类型查询
	EN_CONFIG_DISPLAY_OUTPUT,           // 支持设备显示输出（VGA等）配置,按位: 1:画面分割轮巡配置
	EN_SUBBITRATE_RECORD_CTRL,          // 支持扩展码流录像控制设置, 按位：1-辅码流录像控制设置
	EN_IPV6,                            // 支持IPV6设置, 按位：1-IPV6配置
	EN_SNMP,                            // SNMP（简单网络管理协议）
	EN_QUERY_URL,                       // 支持获取设备URL地址, 按位: 1-查询配置URL地址
	EN_ISCSI,							// ISCSI（Internet小型计算机系统接口配置）
	EN_RAID,							// 支持Raid功能
	EN_HARDDISK_INFO,					// 支持磁盘信息F5查询
	EN_PICINPIC,                        // 支持画中画功能 按位:1,画中画设置; 2,画中画预览、录像存储、查询、下载;3,支持画中画编码配置，同时支持画中画通道查询
	EN_PLAYBACK_SPEED_CTRL_SUPPORT,     // 同 EN_PLAYBACK_SPEED_CTRL ，只为了兼容协议
	EN_LF_XDEV,							// 支持24、32、64路LF-X系列，标注这类设备特殊的编码能力计算方式
	EN_DSP_ENCODE_CAP,					// F5 DSP编码能力查询
	EN_MULTICAST,                       // 组播能力查询
	EM_NET_LIMIT,                       // 网络限制能力查询，按位，1-网络发送码流大小限                          
	EM_COM422,                          // 串口422
	EM_PROTOCAL_FRAMEWORK,				// 是否支持三代协议框架（需要实现listMethod(),listService()），通过F6命令访问
	EM_WRITE_DISK_OSD,					// 刻录OSD叠加, 按位, 1-刻录OSD叠加配置
	EM_DYNAMIC_MULTI_CONNECT,			// 动态多连接, 按位, 1-请求视频数据应答
	EM_CLOUDSERVICE,                    // 云服务,按位，1-支持大华云服务
};

typedef struct 
{
	DWORD IsFucEnable[512];				// 功能列表能力集,下标对应上述的枚举值,按位表示子功能
} DH_DEV_ENABLE_INFO;

//////////////////////////////////////////////////////////////////////////
//	卡号查询能力结构体
typedef struct 
{
	char		IsCardQueryEnable;
	char		iRev[3];
} DH_CARD_QUERY_EN;

//////////////////////////////////////////////////////////////////////////
//	wireless能力结构体
typedef struct 
{
	char		IsWirelessEnable;
	char		iRev[3];
} DH_WIRELESS_EN;

//////////////////////////////////////////////////////////////////////////
//	图象水印能力结构体
typedef struct 
{
	char		isSupportWM;			// 1 支持；0 不支持
	char		supportWhat;			// 0：文字水印；1：图片水印；2：同时支持文字水印和图片水印
	char		reserved[2];
} DH_WATERMAKE_EN;

//////////////////////////////////////////////////////////////////////////
//	多画面预览能力结构体
typedef struct  
{
	int			nEnable;				// 1 支持；0 不支持
	DWORD		dwMultiPlayMask;		// 多画面预览掩码
	char		reserved[4];			// 保留
} DH_MULTIPLAY_EN;

//////////////////////////////////////////////////////////////////////////
//	无线报警能力结构体
typedef struct  
{
	BOOL		bSupport;				// 是否支持
	int			nAlarmInCount;			// 输入个数
	int			nAlarmOutCount;			// 输出个数
	int			nRemoteAddrCount;		// 遥控器个数
	BYTE		reserved[32];
} DH_WIRELESS_ALARM_INFO;

//////////////////////////////////////////////////////////////////////////
//	网络硬盘分区能力结构体
typedef struct 
{
	BOOL		bSupported;				// 是否支持网络硬盘分区
	int			nSupportNum;			// 支持分区的数目
	BYTE		bReserved[32];			// 保留字节
} DH_DISK_SUBAREA_EN;

//	DSP能力查询，当DSP能力算法标识为2时使用。
typedef struct  
{
	BYTE		bMainFrame[32];			// 以分辨率枚举值(CAPTURE_SIZE)为索引,主码流分辨率对应支持的最大帧率,如果不支持此分辨率,则值为0.
	BYTE		bExtraFrame_1[32];		// 辅码流1,使用同bMainFrame
	BYTE		bReserved[128];			// 预留给辅码流2和3.		
} DH_DSP_CFG_ITEM;

typedef struct  
{
	int			nItemNum;				// DH_DSP_CFG_ITEM的有效个数,等于通道数
	DH_DSP_CFG_ITEM	stuDspCfgItem[32];	// 主码流的信息
	BYTE		bReserved[128];			// 保留
} DH_DSP_CFG; 

//////////////////////////////////////////////////////////////////////////
//	快速查询配置能力结构体
typedef struct 
{
	char		IsQuickQueryEnable;		// 1是设备支持配置命令快速返回，请设置配置时间足够长以保证窄带下配置的正常读取。建议设置60S
	char		iRev[3];
} DH_QUICK_QUERY_CFG_EN;

typedef struct  
{
	int			nStreamType;			// 0,无 1,SIP 2,RTSP
	BYTE		bReserved[16];			// 保留
} DH_STREAM_MEDIA_EN;

//智能球跟踪能力查询
typedef struct
{
	char		IsIntelliTrackerEnable;		// 大于0表示具有智能球跟踪能力
	BYTE		bReserved[3];
}DH_INTELLI_TRACKER_EN;


#endif // DHSYSABLE_H

