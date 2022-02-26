import socket

UDP_PORT = 4444
 
sock = socket.socket(
	socket.AF_INET, socket.SOCK_DGRAM) 
#bind to whatever IP address we have)
sock.bind(('', UDP_PORT))

class Message:
	room = ""
	dateTime = ""
	temperature = ""
	humidity = ""

def writeLog(message):
	logstr = 'd,{m.dateTime},n,{m.roomName},t,{m.temperature},h,{m.humidity}\n'.format(m = message)
	f = open("/home/pi/temperature.log", "a")
	f.write(logstr)
	f.close()


def createHtml(message):

	html_string = """
	<!DOCTYPE html>
	<html>
	    <head>
		<title>>Temperature</title>
	    </head>
	    <body>
		<p>Datum: {m.dateTime} Raum: {m.roomName} Temperatur: {m.temperature} Luftfeuchte: {m.humidity}</p>
	    </body>
	</html>
	""".format(m = message)
	#print(html_string)

	f = open("/home/pi/website/index.html", "w")
	f.write(html_string)
	f.close()

#############################################

def parseData(data):
	print(data)
	message = Message()
	dataArr = str(data).split(',')
	if len(dataArr) > 10:
            message.roomName = dataArr[0]
            message.temperature = dataArr[8]
            message.humidity = dataArr[10]
            message.dateTime = str(dataArr[3]) + "."+ str(dataArr[2])+ "." + str(dataArr[1]) +" "+ str(dataArr[4]) + ":" + str(dataArr[5])
            createHtml(message)
            writeLog(message)
            print("received a message: From {m.roomName} at {m.dateTime}".format(m=message))
	else:
            print("message bad length")

#############################################

while True:
	data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
	parseData(data)


