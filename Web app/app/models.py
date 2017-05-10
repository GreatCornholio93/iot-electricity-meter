from django.db import models


class Question(models.Model):
    question_text = models.CharField(max_length=200)
    pub_date = models.DateTimeField('date published')
    def __str__(self):
    	return self.question_text


class Choice(models.Model):
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    choice_text = models.CharField(max_length=200)
    votes = models.IntegerField(default=0)
    def __str__(self):
    	return self.choice_text

class Library(models.Model):
	library_name = models.CharField(max_length=200)
	library_author = models.CharField(max_length=200)
	library_description = models.CharField(max_length=900)
	def __str__(self):
		return self.library_name

class Function(models.Model):
    belongs_to_library = models.ForeignKey(Library, on_delete=models.CASCADE)
    function_name = models.CharField(max_length=200)
    function_description = models.CharField(max_length=999)
    def __str__(self):
    	return self.function_name

class Datatest(models.Model):
    deviceID = models.IntegerField(default=0)
    value = models.IntegerField(default=0)
    dateTime = models.DateTimeField()
    def __int__(self):
        return self.deviceID

class Device(models.Model):
    sigfoxID = models.CharField(max_length=20)
    apiLogin = models.CharField(max_length=100)
    apiPassword = models.CharField(max_length=150)
    description = models.CharField(max_length=900)


class Data(models.Model):
    Device = models.ForeignKey(Device, on_delete = models.CASCADE)
    UnixTime = models.CharField(max_length=39)
    data = models.CharField(max_length=901)
    snr = models.CharField(max_length=39)
    linkQuality = models.CharField(max_length=39)
    regularTime = models.DateTimeField()


