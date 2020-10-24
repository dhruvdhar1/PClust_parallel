import boto3;
from botocore.client import Config;
from zipfile import *;
import random;
import getpass;
import os;
def compress():
    file_name="pclust_"+getpass.getuser()+"_"+str(random.randint(0,10000))+".zip"
    zip_archive=ZipFile(file_name,"w")
    zip_archive.write("outputFiles/graph1.png")
    zip_archive.write("outputFiles/graph2.png")
    zip_archive.write("outputFiles/vertexClust.2230.SGL")
    zip_archive.write("outputFiles/vertexClustSize.2230.SGL")
    zip_archive.close()
    upload(file_name)

def upload(file_name):
    ACCESS_KEY_ID = 'AKIAIZQGUBZJ656RT4MHLQ3'
    ACCESS_SECRET_KEY = 'XYv30wXpglnMuWmT56vhjfvFOzyE52wKJV/1VLUALSgDrd'
    BUCKET_NAME = 'pclust-output-files'
    data = open(file_name, 'rb')
    s3 = boto3.resource('s3',aws_access_key_id=ACCESS_KEY_ID,aws_secret_access_key=ACCESS_SECRET_KEY,config=Config(signature_version='s3v4'))
    s3.Bucket(BUCKET_NAME).put_object(Key=file_name, ACL='public-read', Body=data)
    print "\nFile "+file_name+" uploaded to AWS S3\n"
    print "File can be downloaded at : https://s3.ap-south-1.amazonaws.com/pclust-output-files/"+file_name;
    os.remove(file_name)
