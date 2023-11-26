from flask import Flask, render_template, request, redirect, url_for
from influxdb_client import InfluxDBClient, Point, WriteOptions

main = Flask(__name__)

# InfluxDB connection details

influx_url = 'http://localhost:8086'
influx_token = 'x6YgE9kiefT0eo2wQvulslD6CTEpTalUZOQYSCCk-fNf3wujkn3BPGubhp8GTHjX60IpJOottnqIN-e1SzzghA=='
influx_org = 'Clockhacks'
influx_bucket = 'final'

@main.route('/')
def index():
    return render_template('website.html')

@main.route('/submit', methods=['GET','POST'])
def submit():
    Jclient = InfluxDBClient(url=influx_url, token=influx_token, org=influx_org)
    if request.method == 'POST' or request.method == 'GET':
        data = request.get_json()  
        dropdown_value = data.get('dropdown')
        print(dropdown_value)#why doesnt thus fircken take in the new list values 
        
        write_api = Jclient.write_api(write_options=WriteOptions(batch_size=1))
        point = Point("rgb").field("dropdownrgb", dropdown_value) 
        write_api.write(bucket=influx_bucket, record=point)

        return redirect(url_for('index'))

if __name__ == '__main__':
    main.run(debug=True)
