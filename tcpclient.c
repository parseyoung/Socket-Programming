/*tcp사용해서 원하는 네트워크 정보 서버에 요청하고 서버로부터 응답 받음*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "192.168.1.62" // 서버의 IP 주소를 적절한 값으로 변경
#define PORT 9899
#define BUFFER_SIZE 1067

void error_handling(char *message);

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 소켓 생성
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        error_handling("소켓 생성 오류");
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 서버와 연결
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error_handling("연결 오류");
    }

    // 사용자로부터 메시지 입력받음
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        printf("필요한 네트워크 정보를 입력하세요 (ip, mac, gw, subnet, dns): ");
        fgets(buffer, sizeof(buffer), stdin);

        // 개행 문자(엔터) 제거
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // 서버에 메시지 전송
        if (send(client_socket, buffer, strlen(buffer), 0) == -1) {
            error_handling("메시지 전송 오류");
        }

    

        // 서버로부터 응답 받음
        memset(buffer, 0, sizeof(buffer));
        int recv_len = read(client_socket, buffer, sizeof(buffer) - 1);

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