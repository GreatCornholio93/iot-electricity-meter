from django.conf.urls import url

from . import views

urlpatterns = [
    # ex: /polls/
    url(r'^$', views.index, name='index'),
    # ex: /polls/5/
    url(r'^(?P<question_id>[0-9]+)/$', views.detail, name='detail'),
    # ex: /polls/5/results/
    url(r'^(?P<question_id>[0-9]+)/results/$', views.results, name='results'),
    # ex: /polls/5/vote/
    url(r'^(?P<question_id>[0-9]+)/vote/$', views.vote, name='vote'),

    url(r'^doc/$', views.documentation, name='doc'),

    url(r'^devices/$', views.devices, name='devices'),

    url(r'^devices/(?P<sigfoxID>[\w\-]+)/$', views.device_detail, name='device_detail'),

    url(r'^manage/(?P<sigfoxID>[\w\-]+)/postdatafromcallback', views.get_data_from_post, name='get_data_from_post'),

    url(r'^devices/new/add/$', views.add_device, name='add_device'),

    url(r'^devices/device/delete/$', views.delete_device, name='delete_device'),

    url(r'^devices/data/query/$', views.query_data, name='query_data'),

    url(r'^devices/data/query/a$', views.query_data_a, name='query_data_a'),


    #url(r'^menu/$', menus, name='menu'),
]
