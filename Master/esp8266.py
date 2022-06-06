import socket


def esp8266_init():
    # 创建socket对象
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 将socket绑定到本机IP地址和端口
    server.bind(('0.0.0.0', 8090))
    # 服务器端开始监听来自客户端的连接
    server.listen(5)
    conn, address = server.accept()
    print(address)
    return conn


if __name__ == '__main__':
    conn = esp8266_init()

    while True:
        val = conn.recv(1024)
        if val == b"Success!":
            print(val)
            break

    while True:
        string = input("Enter: ").encode()
        conn.send(string)

        val = conn.recv(10)
        if val == b"End...":
            break
        else:
            print(val.decode())

    print("end...")

