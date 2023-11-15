/*udp, 브로드캐스트를 사용하여 클라이언트가 서버에 필요한 네트워크 정보를 요청하고,
응답받는 예제*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

//#define SERVER_IP "192.168.1.62" UDP만 사용 할 경우
#define SERVER_IP "192.168.1.255"
#define PORT 9886
#define BUFFER_SIZE 1067

void error_handling(char *message);

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 소켓 생성
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        error_handling("소켓 생성 오류");
    }

    // 브로드캐스트 옵션 설정, uDP인 경우 주석 처리 필요
    int broadcast_enable = 1;
    if (setsockopt(client_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0) {
        error_handling("브로드캐스트 소켓 옵션 설정 오류");
    }


    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(INADDR_ANY);//모든네트워크인터페이스 연결 수락

    // 사용자로부터 메시지 입력받음
    while(1) {

        printf("필요한 네트워크 정보를 입력하세요 (ip, mac, gw, subnet, dns): ");
        fgets(buffer, sizeof(buffer), stdin);

        // 개행 문자(엔터) 제거
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // 서버에 메시지 전송
        if (sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            error_handling("메시지 전송 오류");
        }

        // 서버로부터 응답 받음
        memset(buffer, 0, sizeof(buffer));
        int recv_len = recvfrom(client_socket, buffer, BUFFER_SIZE - 1, 0, NULL, NULL);

        if (recv_len <= 0) {
            perror("수신 실패");
            close(client_socket);
            return 1;
        }

        // 서버로부터 받은 응답 출력
        printf("서버로부터 받은 응답: %s\n", buffer);

    }
        // 클라이언트 소켓 닫음
    close(client_socket);
    return 0;
}

void error_handling(char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}