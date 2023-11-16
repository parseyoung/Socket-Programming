## Socket-Programming & Cross Compilation
### tcp,udp(브로드캐스트)사용하여 네트워크 정보 얻기
### TCP
![image](https://github.com/parseyoung/Socket-Programming/assets/104110839/c050b6d5-e721-4cef-93a4-ad2337ab8faa)
![image](https://github.com/parseyoung/Socket-Programming/assets/104110839/20300b29-1bb1-4663-a270-012f6968e638)

### UDP
![image](https://github.com/parseyoung/Socket-Programming/assets/104110839/84b5e4ac-db60-4810-b888-dea3cad83854)
![image](https://github.com/parseyoung/Socket-Programming/assets/104110839/f1e7940d-06b0-4418-8297-f7b024e9288d)

### Cross Compilation
1. ./buildroot/package/rockchip 폴더에 신규 폴더(어플명) 생성 후  Config.in , 어플명.mk 파일 생성  <br>
 ![image](https://github.com/parseyoung/Socket-Programming-Cross/assets/104110839/32307e79-d626-4673-9cd2-0879f87a468d)   <br>
- 추가 라이브러리들이 있으면 "어플명_DEPENDENCIES =" 에 추가 하시면 됩니다. <br>
- 어플명.mk 파일에 어플명_SITE 에 실제 소스의 위치를 설정 합니다. ** app/어플명 으로 하시면 됩니다. <br>
2. CMakeLists.txt 작성 <br>
3. rv1126_sdk의 app에 sy_ipinstall 폴더 생성 후 소스코드와, CMakeLists.txt 파일 복사해서 넣음  <br>
4. build 디렉토리 생성 <br>
$ mkdir build <br>
$ cd build <br>
  - cmake 빌드를 소스와 같은 경로에서 해도 되지만 관리를 위해 따로 디렉토리를 생성합니다. <br>
5. cmake 실행 <br>
$ cmake .. <br>
![image](https://github.com/parseyoung/Socket-Programming-Cross/assets/104110839/68b28c26-4413-4c19-802c-1ed81d74da9a) <br>
- cmake 명령후 에러없이 Makefile 이 생성되었다면 정상적으로 실행된것입니다. <br>
6. Makefile로 빌드  <br>
$ make <br>
![image](https://github.com/parseyoung/Socket-Programming-Cross/assets/104110839/98329c25-c34f-4cd8-aac7-cc8b15a6ac1c)  <br>
7. sdk 루트 폴더에서 ./envsetup.sh 실행<br>
- Which would you like? [0]: 78 선택<br>
![image](https://github.com/parseyoung/Socket-Programming-Cross/assets/104110839/97b72ebd-9a65-4632-bba3-8e43743f8811) <br>
8. make 실행 <br>
$ make sy_ipinstall  <br>
- make가 안되면, make clean 하거나 make sy_ipinstall-rebuild
9. 실행파일생성 확인(맨 아래) <br>
![image](https://github.com/parseyoung/Socket-Programming-Cross/assets/104110839/268d733d-2158-43db-96d0-14f204bead95) <br>
10. winscp에 접속 -없으면 윈도우용 설치 <br>
![image](https://github.com/parseyoung/Socket-Programming-Cross/assets/104110839/479dbc03-7c8f-45ff-a426-c13b0dc68e72) <br>
11. 실행파일 추가<br>
![image](https://github.com/parseyoung/Socket-Programming-Cross/assets/104110839/ed8c9f06-00ed-4e28-aeca-8da54545ef42)<br>
12. chmod로 실행 권한 부여<br>
![image](https://github.com/parseyoung/Socket-Programming-Cross/assets/104110839/c6e097b7-c5f2-45fd-90cc-d4f57c1f43aa)<br>
13. 실행 결과 <br>
![image](https://github.com/parseyoung/Socket-Programming-Cross/assets/104110839/b66a6123-9cdc-48a7-9eb1-a2141f6ab306) <br>





 






  

   
    
