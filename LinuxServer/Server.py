import socket

UDP_IP = "192.168.1.109"
UDP_PORT = 4444
 
sock = socket.socket(
	socket.AF_INET, socket.SOCK_DGRAM) 
#sock.bind((UDP_IP, UDP_PORT))
sock.bind(('', UDP_PORT))

while True:
	data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
	print("received message: %s" % data)
  
