# Generated by Django 4.0.4 on 2022-05-31 16:59

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('articles', '0003_article_chapter'),
    ]

    operations = [
        migrations.AlterField(
            model_name='article',
            name='chapter',
            field=models.TextField(verbose_name='chapter'),
        ),
    ]
