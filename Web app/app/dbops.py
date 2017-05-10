from polls.models import Data



def getLastDate():
	lastDBEntry = Data.objects.last('UnixTime')
	return lastDBEntry.UnixTime