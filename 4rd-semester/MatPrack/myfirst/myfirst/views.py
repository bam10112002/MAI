from multiprocessing import context
from django.shortcuts import render, redirect
from django.http import HttpResponse
from .models import Article 
from .forms import ArticleForm

def page_not_found_view(request, exception):
    return render(request, '404.html', status=404)
