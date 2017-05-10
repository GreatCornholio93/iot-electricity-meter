import time

class CData:

	  def __init__(self, deviceID,time,data,snr,linkQuality,regularTime):
	  	self.deviceID=deviceID
	  	self.UnixTime = time
	  	self.data = data
	  	self.snr = snr
	  	self.linkQuality = linkQuality
	  	self.regularTime = regularTime

	  