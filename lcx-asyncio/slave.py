import asyncio
import getopt
import random
import socket
import sys
import uuid
import time

from init import (BUF_SIZE, TIMES, bind_request, chap_result, chap_salt,
                  connect_response, data, genearteMD5, hashFailedErrorMsg,
                  hashSuccessMsg, noSuchUserErrorMsg, resolve)


def isColonin(string):
    if string.find(':') == -1:
        return False
    else:
        return True


def resolveError():
    print('Command Error!')
    print('Format: slave.py -r <ip:port1> -u <u1:p1> -p port2 -l <ip:port3>')


async def tcp_echo_client(host, port, rmtLisPort, localServerLisPort, user, loop):
    try:
        reader, writer = await asyncio.open_connection(host=host, port=port, loop=loop)
        print('# Connected with server\n\n# CHAP Authentication BEGIN\n')

        ########
        # CHAP #
        ########

        user = user
        randomUUID = str(uuid.uuid1())  # len = 36
        saltstr = randomUUID + user['username']
        chap1 = chap_salt(len(saltstr), saltstr)
        writer.write(chap1.tostring().encode('utf-8'))
        print('# CHAP Challenge message sent')

        recvChap2 = await reader.read(BUF_SIZE)
        recvChap2 = recvChap2.decode('utf-8')
        if recvChap2 == noSuchUserErrorMsg:
            print(noSuchUserErrorMsg)
            print('# Closing...')
            sys.exit(2)
        print('# CHAP Hash message received')
        if resolve(recvChap2)[2] == genearteMD5(randomUUID + user['password']):
            print('# Hash configuration passed')
            chap3 = chap_result(True)
            writer.write(chap3.tostring().encode('utf-8'))
            print('# CHAP Result message sent')
        else:
            print(hashFailedErrorMsg)
            chap3 = chap_result(False)
            writer.write(chap3.tostring().encode('utf-8'))
            print('# CHAP Result message sent')
            print('# Closing...')
            sys.exit(2)
        print(hashSuccessMsg)

        ########
        # BIND #
        ########

        rID = str(random.randint(10000, 99999))
        remoteListenPort = rmtLisPort
        writer.write(bind_request(rID, remoteListenPort).tostring().encode('utf-8'))
        print("# Bind Request No.%s message sent" % rID)
        recvBind2 = await reader.read(BUF_SIZE)
        recvBind2 = recvBind2.decode('utf-8')
        recvBind2 = resolve(recvBind2)
        if recvBind2[2] == "True":
            print("# Bind Request No.%s accepted!\n# Remote Listen server is ready to listen Port: %s\n" % (recvBind2[1], recvBind2[3]))
        else:
            print("# Bind Request No.%s denied!\n# Error: Remote Listen server is unable to listen Port: %s" % (recvBind2[1], recvBind2[3]))
            print("# Connection refused!\n# Closing...")
            sys.exit(2)
        print('# Waiting for connection request...\n')

        ###########
        # Connect #
        ###########

        recvConn1 = await reader.read(BUF_SIZE)
        recvConn1 = resolve(recvConn1.decode('utf-8'))
        print("# Connection Request No. %s received" % recvConn1[1])
        print('# Connecting PORT:%s...' % rmtLisPort)
        obj = socket.socket()
        try:
            ###

            # readerL, writerL = await asyncio.open_connection("127.0.0.1", int(rmtLisPort))
            obj.connect(('127.0.0.1', int(localServerLisPort)))

            ###
        except Exception:
            print("# Error: Connection failed")
            # huisong
            conn2 = connect_response(recvConn1[1], False, '00000')
            writer.write(conn2.tostring().encode('utf-8'))
            # print(conn2.tostring())
            print('# Closing...')
            sys.exit(2)
        print("# Connection success")
        # huisong
        CONNID = random.randint(10000, 99999)
        conn2 = connect_response(recvConn1[1], True, CONNID)
        writer.write(conn2.tostring().encode('utf-8'))
        print('# Connect Response No. %s sent' % recvConn1[1])
        print('\n# IMPORTANT # Data tranfer begin\n# CONNECTION_ID = %d\n' % CONNID)

        # data trans
        i = 1
        while i <= TIMES:
            recvDataR = await reader.read(BUF_SIZE)
            recvDataR = resolve(recvDataR.decode('utf-8'))
            connID = recvDataR[1]
            content = recvDataR[2]
            time.sleep(1)
            print('# CONNECTION ID: %s # "%s" reposted!' % (connID, content))
            obj.sendall(content.encode('utf-8'))
            # writerL.write(content.encode('utf-8'))
            # await writerL.drain()
            i += 1

        i = 1
        while i <= TIMES:
            recvDataL = obj.recv(BUF_SIZE).decode('utf-8')
            toLocal = data(CONNID, 0, recvDataL)
            time.sleep(1)
            writer.write(toLocal.tostring().encode('utf-8'))
            await writer.drain()
            print('# CONNECTION ID: %s # "%s" reposted!' % (CONNID, recvDataL))
            i += 1

        print('\n# Transfer Accomplished!\n')

        recvDisc = await reader.read(BUF_SIZE)
        recvDisc = resolve(recvDisc.decode('utf-8'))
        print('# CONNECTION ID = %s closed\n' % recvDisc[1])
        obj.close()

    except Exception:
        print('# Error\n')
        sys.exit()


def main(argv):
    try:
        opts, args = getopt.getopt(argv, "hr:u:p:l:")
        # print(opts)
        # print(args)
    except getopt.GetoptError:
        resolveError()
        sys.exit(2)
    if opts[0][0] == '-h' and len(opts) == 1:
        print('Format: slave.py -r <ip:port1> -u <u1:p1> -p port2 -l <ip:port3>')
        sys.exit()
    elif opts[0][0] == '-h' and len(opts) != 1:
        resolveError()
        sys.exit(2)
    else:
        if len(args) == 0:
            if isColonin(opts[0][1]) and isColonin(opts[1][1]) and isColonin(opts[3][1]):
                ###
                # Go
                ###
                print("\n# Start TCP connection...")

                remoteListenInternalLocation = {}
                temp = opts[0][1].split(':')
                remoteListenInternalLocation['ip'] = temp[0]
                remoteListenInternalLocation['port'] = temp[1]
                # print(remoteListenInternalLocation)

                user = {}
                temp = opts[1][1].split(':')
                user['username'] = temp[0]
                user['password'] = temp[1]
                # print(user)

                remoteListenPort = opts[2][1]
                # print(remoteListenPort)

                localServerListenLocation = {}
                temp = opts[3][1].split(':')
                localServerListenLocation['ip'] = temp[0]
                localServerListenLocation['port'] = temp[1]
                # print(localServerListenLocation)
                HOST = remoteListenInternalLocation['ip']
                PORT = int(remoteListenInternalLocation['port'])
                loop = asyncio.get_event_loop()
                loop.run_until_complete(tcp_echo_client(HOST, PORT, remoteListenPort, localServerListenLocation['port'], user, loop))
                loop.close()

            else:
                resolveError()
        else:
            resolveError()
            sys.exit(2)


if __name__ == "__main__":
    main(sys.argv[1:])
