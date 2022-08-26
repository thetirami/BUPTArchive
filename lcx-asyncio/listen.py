import asyncio
import getopt
import time
import random
import socket
import sys

from init import (BUF_SIZE, bind_response, chap_hash, genearteMD5,
                  hashFailedErrorMsg, hashSuccessMsg, noSuchUserErrorMsg,
                  resolve, connect_request, data, TIMES, disconnect)

userInfo = []


async def handle_echo(reader, writer):
    print("# Slave: TCP connect...\n\n# CHAP Authentication BEGIN \n")
    ########
    # CHAP #
    ########
    receiveCHAPSalt = await reader.read(BUF_SIZE)
    receiveCHAPSalt = receiveCHAPSalt.decode('utf-8')
    print('# CHAP Challenge message received')
    originMsg = resolve(receiveCHAPSalt)
    receiveUUID = originMsg[1][:36]
    receiveUsername = originMsg[1][36:]
    flag = 0
    for i in userInfo:
        if i['username'] == receiveUsername:
            tempPswd = i['password']
            flag = 1
            break
    if flag == 0:
        print(noSuchUserErrorMsg)
        await writer.write(noSuchUserErrorMsg.encode('utf-8'))
    else:
        rawHash = genearteMD5(receiveUUID + tempPswd)
        chap2 = chap_hash(
            len(receiveUsername), receiveUsername, len(rawHash), rawHash)
        writer.write(chap2.tostring().encode('utf-8'))
        print('# CHAP Hash message sent')
        receiveCHAPResult = await reader.read(BUF_SIZE)
        receiveCHAPResult = receiveCHAPResult.decode('utf-8')
        receiveCHAPResult = resolve(receiveCHAPResult)[1]
        if receiveCHAPResult != "True":
            print(hashFailedErrorMsg)
        else:
            print(hashSuccessMsg)
        ########
        # BIND #
        ########
        bind1 = await reader.read(BUF_SIZE)
        bind1 = bind1.decode('utf-8')
        bind1 = resolve(bind1)
        lisPort = int(bind1[2])
        if lisPort == 0:
            lisPort = random.randint(10000, 65535)  # +端口检测
        print("# Bind Request No.%s message received\n# Ready to listen Port: "
              % bind1[1] + str(lisPort))
        res = True
        try:
            sk = socket.socket()
            sk.bind(("127.0.0.1", lisPort))
            sk.listen(20)
            print("# Able to listen Port: " + str(lisPort))
        except Exception:
            print("# Unable to listen Port: " + str(lisPort))
            res = False
        bind2 = bind_response(bind1[1], res, lisPort)
        writer.write(bind2.tostring().encode('utf-8'))
        print("# Bind Response No.%s message sent\n" % bind1[1])
        if res:
            print('# Waiting for connection request...\n')

            # ###

            conn = sk.accept()[0]

            # ###
            conn1 = connect_request(random.randint(10000, 99999), bind1[2])
            writer.write(conn1.tostring().encode('utf-8'))
            print('# Connection Request No. %d sent' % conn1.requestID)
            recvConn2 = await reader.read(BUF_SIZE)
            recvConn2 = resolve(recvConn2.decode('utf-8'))
            print('# Connection Response No. %d received' % conn1.requestID)
            if recvConn2[2] == 'False':
                print("# Error: Unable to connect")
            else:
                print(
                    '\n# IMPORTANT # Data tranfer begin\n# CONNECTION_ID = %s\n'
                    % recvConn2[3])
                ###

                CONNID = recvConn2[3]

                # data trans
                i = 1
                while i <= TIMES:
                    recvDataR = conn.recv(BUF_SIZE)
                    recvDataR = recvDataR.decode('utf-8')
                    toSlave = data(CONNID, 0, recvDataR)
                    time.sleep(1)
                    writer.write(toSlave.tostring().encode('utf-8'))
                    await writer.drain()
                    print('# CONNECTION ID: %s # "%s" reposted!' % (CONNID, recvDataR))
                    i += 1

                i = 1
                while i <= TIMES:
                    recvDataL = await reader.read(BUF_SIZE)
                    recvDataL = recvDataL.decode('utf-8')
                    recvDataL = resolve(recvDataL)
                    content = recvDataL[2]
                    time.sleep(1)
                    conn.sendall(content.encode('utf-8'))
                    print('# CONNECTION ID: %s # "%s" reposted!' % (CONNID, content))
                    i += 1

                print('\n# Tranfer Accomplished!\n')

            disconnectMsg = disconnect(CONNID)
            writer.write(disconnectMsg.tostring().encode('utf-8'))
            print('# Disconnection Message sent!')


def resolveError():
    print('Command Error!')
    print('Format: listen.py -p <portnumber> -u <u1:p1><u2:p2>...')


def main(argv):
    try:
        opts, args = getopt.getopt(argv, "hp:u:")
    except getopt.GetoptError:
        resolveError()
        sys.exit(2)
    if opts[0][0] == '-h' and len(opts) == 1:
        print('Format: listen.py -p <portnumber> -u <u1:p1><u2:p2>...')
        sys.exit()
    elif opts[0][0] == '-h' and len(opts) != 1:
        resolveError()
        sys.exit(2)
    else:
        if len(args) == 0:
            usrpswd = opts[1][1].split(',')
            for i in usrpswd:
                if i.find(':') == -1:
                    resolveError()

            port = opts[0][1]
            for i in usrpswd:
                temp = i.split(':')
                tempUsr = {}
                tempUsr['username'] = temp[0]
                tempUsr['password'] = temp[1]
                userInfo.append(tempUsr)
            # print(userInfo)
            print('\n# 向内监听端口为' + port)
            HOST = '127.0.0.1'
            PORT = int(port)

            #########
            # BEGIN #
            #########

            loop = asyncio.get_event_loop()
            coro = asyncio.start_server(handle_echo, HOST, PORT, loop=loop)
            server = loop.run_until_complete(coro)

            # Serve requests until Ctrl+C is pressed
            try:
                loop.run_forever()
            except KeyboardInterrupt:
                pass

            # Close the server
            server.close()
            loop.run_until_complete(server.wait_closed())
            loop.close()

        else:
            resolveError()
            sys.exit(2)


if __name__ == "__main__":
    main(sys.argv[1:])
