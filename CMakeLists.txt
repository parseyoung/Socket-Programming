
cmake_minimum_required(VERSION 3.0) //cmake 최소 버전 3.0이상
project (sy_ipinstall) //프로젝트 이름 설정
add_executable(sy_ipinstall server.c)//server.c 컴파일하여 sy_ipinstall 실행 파일을 생성
INSTALL(TARGETS uart_test RUNTIME DESTINATION bin)