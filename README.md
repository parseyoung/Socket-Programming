# Socket-Programming
## tcp,udp(브로드캐스트)사용하여 네트워크 정보 얻기
## TCP
![image](https://github.com/parseyoung/Socket-Programming/assets/104110839/c050b6d5-e721-4cef-93a4-ad2337ab8faa)
![image](https://github.com/parseyoung/Socket-Programming/assets/104110839/20300b29-1bb1-4663-a270-012f6968e638)

## UDP
![image](https://github.com/parseyoung/Socket-Programming/assets/104110839/84b5e4ac-db60-4810-b888-dea3cad83854)
![image](https://github.com/parseyoung/Socket-Programming/assets/104110839/f1e7940d-06b0-4418-8297-f7b024e9288d)

# TCP (Transmission Control Protocol)와 UDP (User Datagram Protocol)는 인터넷 프로토콜 스위트의 두 가지 주요 전송 계층 프로토콜입니다. 이 둘은 네트워크 통신에서 데이터를 전송하는 데 사용되며, 각각의 특성과 장단점이 있습니다.

1. TCP (Transmission Control Protocol):<br>
    - 연결 지향 프로토콜: 통신하기 전에 연결을 설정하고, 데이터를 전송한 후에 연결을 종료하는 방식으로 동작합니다.<br>
    - 신뢰성: 데이터 전송 시 데이터의 손실이나 순서의 변경을 방지하기 위해 확인 응답과 재전송 등의 메커니즘을 지원하여 신뢰성 있는 통신을 제공합니다.<br>
    - 흐름 제어: 수신자가 데이터를 처리할 수 있는 속도에 맞춰 송신자의 데이터 전송 속도를 제어하여 데이터 오버플로우를 방지합니다.<br>
    - 혼잡 제어: 네트워크 내 혼잡을 방지하기 위해 데이터 전송 속도를 조절합니다.<br>
    - 가상 회선 방식: 데이터를 전송하기 전에 가상의 연결을 설정하여 데이터를 주고받습니다.<br>
    <br>
    TCP는 신뢰성과 데이터의 정확성을 보장하는데 적합하며, 웹 브라우징, 파일 전송, 이메일 등과 같은 어플리케이션에 주로 사용됩니다.<br>
    <br>
2. UDP (User Datagram Protocol):<br>
    - 비연결성 프로토콜: 데이터를 전송하기 전에 연결을 설정하지 않고, 연결을 종료하지 않고도 데이터를 전송할 수 있습니다.<br>
    - 비신뢰성: 데이터를 전송할 때 확인 응답과 재전송 메커니즘이 없어서 데이터의 손실이나 순서의 변경을 감지하거나 복구하지 않습니다.<br>
    - 흐름 제어 및 혼잡 제어 없음: UDP는 데이터 전송 속도를 제어하지 않고 네트워크 혼잡도에 대해 관심이 없습니다.<br>
    - 데이터그램 방식: 데이터를 작은 패킷으로 나누어 전송합니다. 각각의 패킷은 독립적으로 처리됩니다.<br>
    <br>
    UDP는 신속한 데이터 전송이 필요하거나 데이터의 손실이나 순서의 변경이 큰 문제가 되지 않는 경우에 주로 사용됩니다. 예를 들어, 온라인 게임, 동영상 스트리밍, DNS(Domain Name System) 등이 UDP를 활용한 예시입니다.<br>
    <br>
    
