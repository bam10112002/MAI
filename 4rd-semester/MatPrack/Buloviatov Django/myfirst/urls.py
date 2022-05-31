from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path('admin/', admin.site.urls),
    path('articles/', include('articles.urls')),
    path('', include('articles.urls')),
]

handler404 = "articles.views.page_not_found_view"