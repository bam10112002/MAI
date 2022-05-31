from .models import Article
from django.forms import ModelForm, Textarea

class ArticleForm(ModelForm):
    class Meta:
        model = Article
        fields = ["art_name", "body"]
        widgets = {
            "art_name": Textarea(attrs={"placeholder" : "Введите название"}),
            "body": Textarea(attrs={"placeholder" : "Введите статью"})
        }