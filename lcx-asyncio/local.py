import socket
import time


from init import TIMES, BUF_SIZE


sk = socket.socket()
sk.bind(("127.0.0.1", 8002))
sk.listen(5)

conn, address = sk.accept()

i = 1

print('\nWaiting for data from remote client...\n')

while i <= TIMES:
    recvData = conn.recv(BUF_SIZE).decode('utf-8')
    time.sleep(1)
    print('# Received Message: "%s"' % recvData)
    i = i + 1

print('\nData tranfer from Remote Clinet to Local Server test accomplished!')
print('Ready to send data to remote client...\n')
i = 1

while i <= TIMES:
    time.sleep(1.5)
    msg = "1234567"
    conn.sendall(msg.encode('utf-8'))
    print("'%s' sent" % msg)
    i = i + 1

print('\nData tranfer from Local Server to Remote Clinet test accomplished!\n')

conn.close()
