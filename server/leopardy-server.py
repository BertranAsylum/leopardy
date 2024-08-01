import sys
import socket
import threading

server_host = '0.0.0.0'
server_port = 50000
mutex = threading.Lock()


class Client(threading.Thread):
    def __init__(self, conn, data_callback, close_callback):
        self.id = hash(conn)
        self.conn = conn
        self.data_callback = data_callback
        self.close_callback = close_callback
        super().__init__()

    def __hash__(self):
        return self.id

    def __eq__(self, other):
        return self.id == other.id

    def run(self):
        while True:
            try:
                data = self.conn.recv(1024)
                if data:
                    self.data_callback(self, data)
                else:
                    self.close_callback(self)
                    break
            except socket.error:
                print('Recv failed')
                self.close_callback(self)
                break

    def send_msg(self,msg):
        try:
            self.conn.send(msg)
        except socket.error:
            print('Send failed')

    def close(self):
        try:
            self.conn.close()
        except socket.error:
            print('Close failed')


class ConnectionThread(threading.Thread):
    def __init__(self, host, port):
        super(ConnectionThread, self).__init__()
        try:
            self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.s.bind((host,port))
            self.s.listen(5)
        except socket.error:
            print('Failed to create socket')
            sys.exit()
        self.clients = set()

    def echo(self, client, data):
        with mutex:
            for c in self.clients:
                if c != client:
                    c.send_msg(data)

    def remove(self, client):
        with mutex:
            self.clients.remove(client)
            print('[-] Client disconnected: {0}'.format(client.id))

    def run(self):
        while True:
            conn, address = self.s.accept()
            c = Client(conn, self.echo, self.remove)
            c.start()
            with mutex:
                self.clients.add(c)
                print('[+] Client connected: {0} {1}'.format(address[0], c.id))


def main():
    get_conns = ConnectionThread(server_host, server_port)
    get_conns.start()


if __name__ == '__main__':
    main()
