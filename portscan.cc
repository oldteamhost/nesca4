/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/portscan.h"
#include "ncsock/include/readpkt.h"

/*
 * Обработка пакета, писалась используя эти статьи:
 * https://nmap.org/book/synscan.html
 * https://nmap.org/man/ru/man-port-scanning-techniques.html
 * https://nmap.org/book/scan-methods-window-scan.html
 * https://nmap.org/book/scan-methods-maimon-scan.html
 *
 * get_port_status - функция для получения статуса порта,
 * при сканированях SYN, NULL, XMAS, FIN, MAIMON, WINDOW, ACK.
*/
int get_port_status(unsigned char* buffer, uint8_t scan_type)
{
  const struct ip_header *iph = ext_iphdr(buffer);
  const struct tcp_header *tcph = ext_tcphdr(buffer);

  /*Если пакет именно TCP.*/
  if (iph->protocol != 6) {
    return PORT_ERROR;
  }

  switch (scan_type)
  {
    case MAIMON_SCAN: {
      if (tcph->th_flags == 0x04)
        return PORT_CLOSED;

      return PORT_OPEN_OR_FILTER;
    }
    case FIN_SCAN:
    case XMAS_SCAN:
    case NULL_SCAN: {
      if (tcph->th_flags == 0x04)
        return PORT_CLOSED;

      return PORT_OPEN;
    }
    case WINDOW_SCAN: {
      if (tcph->th_flags == 0x04) {
        if (tcph->th_win > 0)
          return PORT_OPEN;
        else
          return PORT_CLOSED;

        return PORT_FILTER;
      }
    }
    case ACK_SCAN: {
      if (tcph->th_flags == 0x04)
        return PORT_NO_FILTER;

      return PORT_FILTER;
    }
    default: {
      switch (tcph->th_flags) {
        case 0x12: {
          /* SYN + ACK
          * Если хост ответил флагом ack и послал syn
          * значит порт считаеться открытым.*/
          return PORT_OPEN;
        }
        case 0x1A: {
          /* SYN + ACK + PSH
          * Если хост ответил флагом ack и psh затем  послал syn
          * значит порт считаеться открытым, и готовым для
          * передач>и данных*/
          return PORT_OPEN;
        }
        case 0x04: {
          /* RST
          * Если хост послал только флаг rst
          * aka сброс соеденения, то считаеться что порт
          * закрыт.*/
          return PORT_CLOSED;
        }
        default:{
          /*Если ответа от хоста вообще не было то считаеться
          что подлкючение не удалось, порт фильтруеться.*/
          return PORT_FILTER;
        }
      }
    }
  }
  return PORT_ERROR;
}

std::string return_port_status(uint8_t type)
{
  switch (type)
  {
    case PORT_OPEN:            return "open";
    case PORT_CLOSED:          return "closed";
    case PORT_FILTER:          return "filtered";
    case PORT_OPEN_OR_FILTER:  return "open/filtered";
    case PORT_NO_FILTER:       return "unfiltered";
  }
  return "error";
}

std::string get_type(uint8_t type)
{
  switch (type)
  {
    case SYN_SCAN:    return "SYN_SCAN";
    case ACK_SCAN:    return "ACK_SCAN";
    case XMAS_SCAN:   return "XMAS_SCAN";
    case FIN_SCAN:    return "FIN_SCAN";
    case WINDOW_SCAN: return "WINDOW_SCAN";
    case NULL_SCAN:   return "NULL_SCAN";
    case MAIMON_SCAN: return "MAIMON_SCAN";
  }

  return "-1";
}
