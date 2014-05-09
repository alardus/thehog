#!/usr/bin/python

import urllib2
import xml.etree.ElementTree as ET

sensor = {}
urllist = ['http://192.168.0.200/']

with open('index.html', 'w') as html:
	html.write('')

def getdata(url):
	query = urllib2.urlopen(url)
	result = query.read()

	root = ET.fromstring(result)

	for child in root:
		sensor[child.tag] = child.text

	with open('index.html', 'a') as html:
		html.write("""
			<html>
			<head><title></title></head>
			<body>
			<h2>%s</h2>
			<p>Temperature: %s</p>
			<p>Humidity: %s</p>
			</body>
			</html>
			""" %(sensor['place'], sensor['temp'], sensor['hum']))

for url in urllist:
	getdata(url)