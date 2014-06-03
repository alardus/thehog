#!/usr/bin/python

import urllib2, time
import xml.etree.ElementTree as ET

sensor = {}
time = time.strftime("%H:%M")
urllist = ['http://192.168.0.200/', 'http://192.168.0.201/', 'http://192.168.0.202/']

with open('sensor.html', 'w') as html:
	html.write("""
		<html>
		<head>
		<meta http-equiv="refresh" content="60" />
		<title></title>
		</head>
		<body>
		<h1>Time %s</h1>\n
		""" %(time))

def getdata(url):
	query = urllib2.urlopen(url)
	result = query.read()

	root = ET.fromstring(result)

	for child in root:
		sensor[child.tag] = child.text

	with open('sensor.html', 'a') as html:
		html.write("""
			<h2>%s</h2>
			<p>Temperature: %s</p>
			<p>Humidity: %s</p>
			""" %(sensor['place'], sensor['temp'], sensor['hum']))

for url in urllist:
	getdata(url)

with open('sensor.html', 'a') as html:
	html.write("""
		</body>
		</html>
		""")