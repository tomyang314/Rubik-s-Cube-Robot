from command import get_command
from esp8266 import *


if __name__ == '__main__':
    conn = esp8266_init()
    while True:
        val = conn.recv(1024)
        if val == b"Success!":
            print(val)
            break

    m_code = get_command()
    if m_code:
        print(' '.join(m_code))

    while True:
        string = m_code.encode()
        conn.send(string)

        val = conn.recv(10)
        if val == b"End...":
            break
        else:
            print(val.decode())

    print("end...")

# D2R2B'R U2B'L U B2R2U F2U2R2U2R2F2

