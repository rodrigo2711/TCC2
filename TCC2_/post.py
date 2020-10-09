from flask import Flask, render_template, request,jsonify
import queue as Queue
app = Flask(__name__)

@app.route("/",  methods=['GET', 'POST'])
def index():

	return render_template('index.html')

@app.route ("/<deviceName>/<action>") 
def action (deviceName, action): 
	if deviceName == 'ar1': 
		return render_template('index.html')

@app.route ("/", methods=['GET', 'POST'])
def result():
	a = 0
	if action == 'onoff':
		print("OK")
		a= 1
		os.system('cd /etc/lirc/lircd.conf.d/')
		os.system('irsend SEND_ONCE LG KEY_VOLUMEUP')
	elif action == 'temp-':
                a = 2
	elif action == 'temp+':
                a = 3
	
	ok = [
		{
		"status": a
		}
	]

	return jsonify(ok)
	
@app.route("/",  methods=['GET', 'POST'])
def index1():

        return render_template('index.html')



	

if __name__ == "__main__":
   app.run(host='192.168.15.111', port=80, debug=True)
