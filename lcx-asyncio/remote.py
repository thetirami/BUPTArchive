import socket
import time


from init import TIMES, BUF_SIZE

obj = socket.socket()
obj.connect(("127.0.0.1", 8001))
i = 1

print('\nReady to send data to local server...\n')

while i <= TIMES:
    time.sleep(1.5)
    msg = "abcdefg"
    obj.sendall(msg.encode('utf-8'))
    print("'%s' sent" % msg)
    i = i + 1

print('\nData tranfer from Remote Clinet to Local Server test accomplished!')
print('Waiting for data from Local Server...\n')
i = 1

while i <= TIMES:
    recvData = obj.recv(BUF_SIZE).decode('utf-8')
    time.sleep(1)
    print('# Received Message: "%s"' % recvData)
    i = i + 1

print('\nData tranfer from Local Server to Remote Clinet test accomplished!\n')
print('TCP connection closing...\n')

obj.close()
print('# TCP connection closed\n')
