from multiprocessing import context
from django.shortcuts import render, redirect
from django.http import HttpResponse
from .models import Article 
from .forms import ArticleForm


def about(reqest):
    return render(reqest, 'about.html')

def author(reqest):
    return render(reqest, 'author.html')

def index(reqest):
    art_list = Article.objects.all()
    return render(reqest, 'list.html', {'art_list': art_list})

def page_not_found_view(request, exception):
    return render(request, '404.html', status=404)

def create(reqest):
    error = ""
    if (reqest.method == "POST"):
        form = ArticleForm(reqest.POST)
        if form.is_valid():
            form.save()
            return redirect('/articles/list')
        else:
            error = "форма не валидна"
    form = ArticleForm
    context = {'form' : form, 'error':error}
    return render(reqest, 'createForm.html', context)