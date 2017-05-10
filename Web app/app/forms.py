from django import forms

class PostForm(forms.Form):
     class Meta:
        device_description = forms.CharField(label='device_description', max_length=300)