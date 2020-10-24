import matplotlib.pyplot as plt; plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plt

def showGraph1():
    f = open('src/vertexCustomClustSize')
    line = f.readline()
    clusterNumber=[]
    clusterSize=[]
    objects=[]
    performance=[]
    tokens=[]
    while line:
        #print line
        tokens = line.split(":")
        objects.append(int(tokens[0]))
        performance.append(int(tokens[1]))
        line = f.readline()
    f.close()
    ###################################################################################
    y_pos = np.arange(len(objects))
    plt.bar(y_pos, performance, width=0.8,align='center',color=['#FF5A5A','#B05AFF','#5AFF73','#FFE75A','#FAB44B','#4BE0FA'], alpha=1)
    plt.xticks(y_pos, objects,rotation=90)
    plt.ylabel('Number of members')
    plt.xlabel('Cluster number')
    plt.title('PClust Output Graph')
    mng = plt.get_current_fig_manager()
    mng.resize(*mng.window.maxsize())
    #plt.savefig('foo.png')
    plt.show()
    #print objects
