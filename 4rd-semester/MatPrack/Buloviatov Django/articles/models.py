from django.db import models

class Article(models.Model):
    art_name = models.TextField('art_name')
    body = models.TextField('body')
    pub_date = models.DateField('date', auto_now_add=True)