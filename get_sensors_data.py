#!/usr/bin/python

import urllib2, time
import xml.etree.ElementTree as ET

sensor = {}
time = time.strftime("%H:%M")
urllist = ['http://192.168.1.200/', 'http://192.168.1.201/', 'http://192.168.1.202/']

forecast = 'http://api.openweathermap.org/data/2.5/weather?q=Moscow&mode=xml&units=metric'
current_temp = ''
max_temp = ''
clouds = ''

with open('sensor.html', 'w') as html:
	html.write("""
		<html>
		<head>
		<meta http-equiv="refresh" content="60" />
		<link rel="stylesheet" type="text/css" href="./sensor.css">
		<title></title>
		</head>
		<body>
		<h1>Moscow</h1>\n
		<div id="main">

		<div id="div1">
		""")

def getdata(url):
	query = urllib2.urlopen(url)
	result = query.read()

	root = ET.fromstring(result)

	for child in root:
		sensor[child.tag] = child.text

	with open('sensor.html', 'a') as html:
		html.write("""
			<h1>%s</h1>
			<p><h2>Temperature: %s</h2></p>
			<p><h2>Humidity: %s</h2></p>
			""" %(sensor['place'], sensor['temp'], sensor['hum']))

def getweather(url):
	query = urllib2.urlopen(url)
	result = query.read()

	root = ET.fromstring(result)

	for child in root:
		if 'temperature' in child.tag:
			current_temp = child.attrib['value']
			max_temp = child.attrib['max']
		elif 'weather' in child.tag:
			clouds = child.attrib['value']
		else:
			pass

	with open('sensor.html', 'a') as html:
		html.write("""
			<br>
			<p>Last update: %s</p>
			</div>

			<div id="div2">
			<h1>Weather forecast</h1>
			<p><h2>Current: %s</h2></p>
			<p><h2>Max: %s</h2></p>
			<p><h2>%s%s</h2></p>
			</div>
			""" %(time, current_temp, max_temp, clouds[0].upper(), clouds[1:]))

# call for sensors
for url in urllist:
	getdata(url)

# call for weather forecast
getweather(forecast)

with open('sensor.html', 'a') as html:
	html.write("""
		</div>
		</body>
		</html>
		""")