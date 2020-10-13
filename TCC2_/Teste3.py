from flask import Flask, render_template, request
import socket
import numpy as np
import os

HOST = '192.168.15.111'

app = Flask(__name__)

@app.route("/", methods=('GET','POST'))
def index():
	global select
	global retorno
	select = request.form.get('sala')
	print (select)

	if(select == 'none'):
		retorno = "teste3.html"
		return render_template(retorno)
	elif(select == "s101"):
		retorno = "s101.html"
		return render_template(retorno)
	elif(select == 's201'):
		retorno = "s201.html"
		return render_template(retorno)
	elif(select == "s201"):
		retorno = "s301.html"
		return render_template(retorno)
	elif(select == 's401'):
		retorno = "s401.html"
		return render_template(retorno)
	elif(select == "s501"):
		retorno = "s501.html"
		return render_template(retorno)
	elif(select == 'status'):
		retorno = "status.html"
		return render_template(retorno)
	return render_template("teste3.html")

@app.route("/<deviceName>/<action>")
def action (deviceName, action):
	sala = select
	print (sala)
	a = 0
	if(sala == 'none'):
		PORT = 2000
	elif(sala == 's101'):
		PORT = 2000
		if (action == 'onoff'):
			a = "a1f1"
		if (action == 'tempmais'):
			a = "a1f2"
		if (action == 'tempmenos'):
			a = "a1f3"

	elif(sala == 's201'):
		PORT = 2001
		if (action == 'onoff'):
			a = "a1f1"
		if (action == 'tempmais'):
			a = "a1f2"
		if (action == 'tempmenos'):
			a = "a1f3"

	elif(sala == 's301'):
		PORT = 2003
		if (action == 'onoff'):
			a = "a1f1"
		if (action == 'tempmais'):
			a = "a1f2"
		if (action == 'tempmenos'):
			a = "a1f3"

	elif(sala == 's401'):
		PORT = 2004
		if (action == 'onoff'):
			a = "a1f1"
		if (action == 'tempmais'):
			a = "a1f2"
		if (action == 'tempmenos'):
			a = "a1f3"

	elif(sala == 's501'):
		PORT = 2005
		if (action == 'onoff'):
			a = "a1f1"
		if (action == 'tempmais'):
 			a = "a1f2"
		if (action == 'tempmenos'):
			a = "a1f3"

	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		print("Servidor Iniciado. Esperando pelo cliente..")
		s.bind((HOST, PORT))
		s.listen(1)
		conn, addr = s.accept()

	with conn:
		print ("Conectado: ", addr)
		print ("Enviando dados")
		print (a)
		my_data = a
		x_encoded_data = my_data.encode('utf-8')
		conn.sendall(x_encoded_data)
		print (x_encoded_data)
		s.close()
		return render_template(retorno)

if __name__ == "__main__":
	app.run(host='192.168.15.111', port=1000, debug = True)


