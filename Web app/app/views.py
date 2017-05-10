from django.shortcuts import get_object_or_404, render
from django.template.defaulttags import register
from menu import Menu, MenuItem
from django.http import Http404
from .models import Question
from .models import Library
from .models import Function
from .models import Datatest
from .models import Device
from .forms import PostForm
from .data_parsing import *
from .models import Data
from django.urls import reverse
from django.http import HttpResponse, HttpResponseRedirect
from django.views.decorators.csrf import csrf_exempt
import json
import cgi
from datetime import datetime, timezone, timedelta


@register.filter
def get_item(dictionary, key):
    return dictionary.get(key)


def index(request):
    latest_question_list = Question.objects.order_by('-pub_date')[:5]
    context = {'latest_question_list': latest_question_list}
    return render(request, 'app/index.html', context)

def detail(request, question_id):
    question = get_object_or_404(Question, pk=question_id)
    return render(request, 'app/detail.html', {'question': question})

def results(request, question_id):
    response = "You're looking at the results of question %s."
    return HttpResponse(response % question_id)

def vote(request, question_id):
    return HttpResponse("You're voting on question %s." % question_id)

def documentation(request):
	library_list = Library.objects.order_by('library_name')
	function_list = Function.objects.order_by('function_name')
	deviceList = Datatest.objects.order_by('dateTime')
	output = []
	
	for lib in library_list:
		lib_out = {}
		lib_out['name'] = lib.library_name
		func_out = []
		for func in function_list:
			if str(func.belongs_to_library) == str(lib.library_name):
				func_out.append({'func_name': str(func.function_name), 'desc': str(func.function_description)})
		lib_out['func'] = func_out
		output.append(lib_out)

	dateTime_out=[]
	values_out=[]
	for dev in deviceList:
		dateTime_out.append(str(dev.dateTime))
		values_out.append(str(dev.value))

	context = {'output': output,'dates': dateTime_out,'values':values_out}
	print (output)
	return render(request,'app/doc.html', context)


def devices(request):
	devices_list = [d.__dict__ for d in Device.objects.order_by('sigfoxID')]
	for dev in devices_list:
		DataObject = Data.objects.filter(Device_id=dev['id']).last()
		dev['regularTime'] = str(DataObject.regularTime) if DataObject else "None data"

	context = {'devices_list': devices_list}
	return render(request,'app/devices.html',context)

def device_detail(request, sigfoxID):
	test = sigfoxID
	testid = Device.objects.get(sigfoxID=test)
	dataset = Data.objects.filter(Device_id=testid.id)
	device = Device.objects.get(id=testid.id)
	isNull = False
	dateTime_out=[]
	values_out=[]
	values_out2=[]
	values_out3=[]

	for dev in dataset:
		testing = dev.data.replace("[","")
		testing = testing.replace("]","")
		testing = testing.split(',')
		
		

		testing = list(map(int, testing))
		testing = [x / 1000 for x in testing]

		dev.data1 = testing[0]
		dev.data2 = testing[1]
		dev.data3 = testing[2]
		
		time = dev.regularTime + timedelta(hours=2)

		dateTime_out.append(str(time.strftime("%Y-%m-%d %H:%M")))
		dev.regularTime = str(time.strftime("%Y-%m-%d %H:%M"))
		values_out.append(testing[0])
		values_out2.append(testing[1])
		values_out3.append(testing[2])

	return render(request, 'app/dev_detail.html', {'dataset': dataset, 'dev_id':device.sigfoxID,'dates': dateTime_out,'values1':values_out,'values2':values_out2,'values3':values_out3})

	
	

@csrf_exempt
def get_data_from_post(request, sigfoxID):
    if request.method == 'POST':
       
       print(request.body)
       body_unicode = request.body.decode('utf-8')
       body = json.loads(body_unicode)
       print(body['data'])
       print(body['device'])
       device = Device.objects.get(sigfoxID=str(body['device']))
       dats = convert_12byte_to_ints(str(body['data']))
       print(dats)
       #dats=bytearray.fromhex(str(body['data'])).decode()
       dataset = Data(Device=device, UnixTime=body['time'], data=dats, snr=body['snr'], linkQuality=body['linkQuality'], regularTime=datetime.fromtimestamp(body['time'], timezone.utc))
       dataset.save()

       #user_obj = User(username=username, email=email, password=password)
       # received_json_data=json.loads(request.readall().decode('utf-8'))
       #test=request.POST.get("title", "")
       #print (received_json_data)
    return HttpResponse('result')


def add_device(request):
    if request.method == 'POST':
        # create a form instance and populate it with data from the request:
        # form = NameForm(request.POST)
        device_description = request.POST.get('device_description')
        sigfox_id = request.POST.get('sigfox_id')
        api_login = request.POST.get('api_login')
        api_password = request.POST.get('api_password')

        dataset = Device(sigfoxID=sigfox_id, apiLogin=api_login, apiPassword=api_password, description=device_description)
       	dataset.save()

        print(device_description, sigfox_id, api_login, api_password)

        return HttpResponseRedirect('/devices')

    # if a GET (or any other method) we'll create a blank form
    else:
        return render(request, 'app/add_device.html')




def delete_device(request):
    if request.method == 'POST':
        sigfoxID = request.POST.get('delete_device_id')
        instance = Device.objects.get(sigfoxID=sigfoxID)
        instance.delete()

        return HttpResponseRedirect('/devices')
    else:
        return 'deny'


def query_data(request):
	if request.method == 'POST':
        # create a form instance and populate it with data from the request:
        # form = NameForm(request.POST)
        #device_description = request.POST.get('device_description')
        #sigfox_id = request.POST.get('sigfox_id')
        #api_login = request.POST.get('api_login')
        #api_password = request.POST.get('api_password')

        #dataset = Device(sigfoxID=sigfox_id, apiLogin=api_login, apiPassword=api_password, description=device_description)
       	#dataset.save()

        #print(device_description, sigfox_id, api_login, api_password)
		sigfox_id = request.POST.get('query_data')
		return render(request, 'app/query_data.html',{'sigfoxid': sigfox_id})

    # if a GET (or any other method) we'll create a blank form
		
	#return render(request, 'app/add_device.html')



def query_data_a(request):
	print("DEBUG1666666")
	if request.method == 'POST':


		data_query_device = request.POST.get('data_query_device')
		data_query_from = request.POST.get('data_query_from')
		data_query_to = request.POST.get('data_query_to')
		
		testid = Device.objects.get(sigfoxID=data_query_device)
		#2017-05-08T08:00
		data_query_from = datetime.strptime(data_query_from, '%Y-%m-%dT%H:%M')
		data_query_to = datetime.strptime(data_query_to, '%Y-%m-%dT%H:%M')
		
		data_query_from =  str(data_query_from - timedelta(hours=2))
		data_query_to = str(data_query_to - timedelta(hours=2)) 

		dataset = Data.objects.filter(regularTime__range=[str(data_query_from), str(data_query_to)])
		device = Device.objects.get(id=testid.id)

		dateTime_out=[]
		values_out=[]
		values_out2=[]
		values_out3=[]
		for dev in dataset:
			testing = dev.data.replace("[","")
			testing = testing.replace("]","")
			testing = testing.split(',')
		
		

			testing = list(map(int, testing))
			testing = [x / 1000 for x in testing]

			dev.data1 = testing[0]
			dev.data2 = testing[1]
			dev.data3 = testing[2]
		
			time = dev.regularTime + timedelta(hours=2)

			dateTime_out.append(str(time.strftime("%Y-%m-%d %H:%M")))
			dev.regularTime = str(time.strftime("%Y-%m-%d %H:%M"))
			values_out.append(testing[0])
			values_out2.append(testing[1])
			values_out3.append(testing[2])

		return render(request, 'app/dev_detail.html', {'dataset': dataset, 'dev_id':device.sigfoxID,'dates': dateTime_out,'values1':values_out,'values2':values_out2,'values3':values_out3})

	else:
		return HttpResponseRedirect('/devices')

    # if a GET (or any other method) we'll create a blank form
	
	
		
	#return render(request, 'app/add_device.html')
