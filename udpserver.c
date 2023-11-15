/*udp, 브로드캐스트를 사용하여 클라이언트가 서버에 필요한 네트워크 정보를 요청받고,
서버의 해당 네트워크 정보를 클라이언트에게 전송하는 예제*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define PORT 9886
#define BUFFER_SIZE 1067

void get_server_ip(char *server_ip);
void error_handling(char *message);
void get_gateway_info(char *gateway_ip);
void get_subnet_mask(char *subnet_mask);
void get_dns_address(char *dns_address);

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    char mac_addr[18];
    char gateway_ip[INET_ADDRSTRLEN];
    char subnet_mask[INET_ADDRSTRLEN];
    char dns_address[INET_ADDRSTRLEN];
    char server_ip[INET_ADDRSTRLEN];

    // 서버 소켓 생성
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        error_handling("소켓 생성 오류");
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 서버 소켓 바인딩
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error_handling("바인딩 오류");
    }

    printf("서버가 실행되었습니다. 클라이언트의 연결을 기다리는 중...\n");

    while (1) {
        // 클라이언트로부터 메시지 수신
        memset(buffer, 0, sizeof(buffer));
        int recv_len = recvfrom(server_socket, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)&client_addr, &client_addr_len);

        if (recv_len <= 0) {
            perror("수신 실패");
            continue;
        }

        // 클라이언트로부터 받은 메시지를 분석하여 응답 전송
        if (strcmp(buffer, "ip") == 0) {

            get_server_ip(server_ip);
            printf("서버의 IP 주소: %s\n", server_ip);

            if (sendto(server_socket, server_ip, strlen(server_ip), 0, (struct sockaddr *)&client_addr, client_addr_len) == -1) {
                perror("IP 정보 전송 실패");
                continue;
            }
        }
        else if (strcmp(buffer, "mac") == 0) {
            // 클라이언트가 "mac"을 보냈을 때, 서버의 MAC 정보 전송
            struct ifreq ifr;
            strcpy(ifr.ifr_name, "ens33"); // 인터페이스 이름은 ens33으로 가정, 환경에 따라 변경해야 함

            if (ioctl(server_socket, SIOCGIFHWADDR, &ifr) == -1) {
                error_handling("MAC 주소 가져오기 오류");
            }

            // MAC 주소를 문자열로 변환하여 저장
            sprintf(mac_addr, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
                    (unsigned char)ifr.ifr_hwaddr.sa_data[0],
                    (unsigned char)ifr.ifr_hwaddr.sa_data[1],
                    (unsigned char)ifr.ifr_hwaddr.sa_data[2],
                    (unsigned char)ifr.ifr_hwaddr.sa_data[3],
                    (unsigned char)ifr.ifr_hwaddr.sa_data[4],
                    (unsigned char)ifr.ifr_hwaddr.sa_data[5]);

            printf("서버의 MAC 주소: %s\n", mac_addr);
        
            if (sendto(server_socket, mac_addr, strlen(mac_addr), 0, (struct sockaddr *)&client_addr, client_addr_len) == -1) {
                perror("MAC 정보 전송 실패");
                continue;
            }
        }
        else if (strcmp(buffer, "gw") == 0) {
            
            get_gateway_info(gateway_ip);

            printf("서버의 게이트웨이 주소: %s\n", gateway_ip);
            if (sendto(server_socket, gateway_ip, strlen(gateway_ip), 0, (struct sockaddr *)&client_addr, client_addr_len) == -1) {
                perror("게이트웨이 IP 정보 전송 실패");
                continue;
            }


        }
        else if (strcmp(buffer, "subnet") == 0){
            
            get_subnet_mask(subnet_mask);

            printf("서버의 서브넷마스크 주소: %s\n", subnet_mask);
        
            if (sendto(server_socket, subnet_mask, strlen(subnet_mask), 0, (struct sockaddr *)&client_addr, client_addr_len) == -1) {
                perror("서브넷마스크 정보 전송 실패");
                continue;
            }
        }

        else if (strcmp(buffer, "dns") == 0){
            
            get_dns_address(dns_address);

            printf("서버의 DNS 주소: %s\n", dns_address);
        
            if (sendto(server_socket, dns_address, strlen(dns_address), 0, (struct sockaddr *)&client_addr, client_addr_len) == -1) {
                perror("DNS 정보 전송 실패");
                continue;
            }
        }
        
        else {
            // 잘못된 요청일 경우 에러 메시지 전송
            char error_msg[] = "잘못된 요청입니다. ip, mac, gw, subnet, dns 를 입력하세요.";

            if (sendto(server_socket, error_msg, strlen(error_msg), 0, (struct sockaddr *)&client_addr, client_addr_len) == -1) {
                perror("에러 메시지 전송 실패");
                continue;
            }
        }
    }

    // 서버 소켓 닫음
    close(server_socket);
    return 0;
}

void get_server_ip(char *server_ip) {
    int sockfd;
    struct ifreq ifr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("소켓 생성 오류");
        exit(EXIT_FAILURE);
    }

    strncpy(ifr.ifr_name, "ens33", IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = '\0';

    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == -1) {
        perror("인터페이스 정보 가져오기 오류");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    close(sockfd);

    // IP 주소를 문자열로 변환하여 저장
    inet_ntop(AF_INET, &((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr, server_ip, INET_ADDRSTRLEN);
}

void get_gateway_info(char *gateway_ip) {
    FILE *fp;
    char line[256];
    char *keyword = "default via ";
    int len = strlen(keyword);

    fp = popen("ip route show", "r");
    if (fp == NULL) {
        error_handling("Failed to execute command");
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strncmp(line, keyword, len) == 0) {
            // Found the line with the gateway IP address
            strcpy(gateway_ip, line + len);
            strtok(gateway_ip, " \t\n"); // Remove trailing whitespace and newline
            pclose(fp);
            return;
        }
    }

    pclose(fp);
    error_handling("Failed to get the gateway IP address");
}

void get_subnet_mask(char *subnet_mask) {
    FILE *fp;
    char line[256];
    char *keyword = "inet ";
    int len = strlen(keyword);

    fp = popen("ip addr show ens33", "r");
    if (fp == NULL) {
        error_handling("Failed to execute command");
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, keyword) != NULL) {
            // Found the line with the inet and subnet mask
            char *mask = strchr(line, '/');
            if (mask != NULL) {
                char *end = strchr(mask + 1, ' '); // Find the space after subnet mask
                if (end != NULL) {
                    *end = '\0'; // Replace space with null terminator to extract only the subnet mask
                    int bits = atoi(mask + 1); // Convert subnet mask bits to integer
                    if (bits >= 0 && bits <= 32) {
                        // Apply bitmask to get the subnet mask in binary format
                        unsigned int bitmask = (0xFFFFFFFF << (32 - bits));
                        // Convert the binary subnet mask to "255.255.255.0" format
                        sprintf(subnet_mask, "%d.%d.%d.%d", (bitmask >> 24) & 0xFF, (bitmask >> 16) & 0xFF, (bitmask >> 8) & 0xFF, bitmask & 0xFF);
                        pclose(fp);
                        return;
                    }
                }
            }
        }
    }

    pclose(fp);
    error_handling("Failed to get the subnet mask");
}

void get_dns_address(char *dns_address) {
    FILE *fp;
    char line[256];
    char *keyword = "nameserver ";
    int len = strlen(keyword);

    fp = fopen("/etc/resolv.conf", "r");
    if (fp == NULL) {
        error_handling("Failed to open /etc/resolv.conf");
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strncmp(line, keyword, len) == 0) {
            // Found the line with the DNS address
            strcpy(dns_address, line + len);
            strtok(dns_address, " \t\n"); // Remove trailing whitespace and newline
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    error_handling("Failed to get the DNS address");
}

void error_handling(char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}