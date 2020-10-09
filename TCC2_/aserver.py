from flask import Flask, render_template, request,jsonify
import queue as Queue
import socket
import numpy as np
import os

HOST = '192.168.15.111'  # Standard loopback interface address (localhost)
PORT = 2000        # Port to listen on (non-privileged ports are > 1023)

app = Flask(__name__)

@app.route("/",  methods=['GET', 'POST'])
def index():

        return render_template('index.html')

@app.route ("/<deviceName>/<action>")
def action (deviceName, action):
        a = 0
        if action == 'onoff':
                print("OK")
                a = "a1f1"
                os.system('cd /etc/lirc/lircd.conf.d/')
                os.system('irsend SEND_ONCE LG KEY_VOLUMEUP')
        elif action == 'tempmais':
                a = "a1f2"
        elif action == 'tempmenos':
                a = "a1f3"

        
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            print("Server Started waiting for client to connect ")
            s.bind((HOST, PORT))
            s.listen(1)
            conn, addr = s.accept()

            with conn:
                print('Connected by', addr)
                print("Ok Sending data ")
                my_data = a       
                x_encoded_data = my_data.encode('utf-8')
                conn.sendall(x_encoded_data)
                print(x_encoded_data)
                s.close()
        return render_template('index.html')


if __name__ == "__main__":
   app.run(host='192.168.15.111', port=80, debug=True)

