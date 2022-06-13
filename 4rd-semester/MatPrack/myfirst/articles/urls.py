from django.contrib import admin
from django.urls import path
from . import views

urlpatterns = [
    path('list/', views.index, name="articles"),
    path('create/', views.create, name="create"),
    path('about/', views.about, name="about"),
    path('author/', views.author, name="author"),
    path('list1/', views.list1, name="list1"),
    path('list2/', views.list2, name="list2"),
    path('', views.index)
]
