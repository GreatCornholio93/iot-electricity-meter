from django.contrib import admin

from .models import Question
from .models import Library
from .models import Function
from .models import Datatest
from .models import Device
from .models import Data

admin.site.register(Question)
admin.site.register(Library)
admin.site.register(Function)
admin.site.register(Datatest)
admin.site.register(Device)
admin.site.register(Data)