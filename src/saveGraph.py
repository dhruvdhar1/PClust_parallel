import matplotlib.pyplot as plt; plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plt
def saveGraph3():
    f = open('src/vertexCustomClustSize')
    line = f.readline()
    clusterNumber=[]
    clusterSize=[]
    objects=[]
    performance=[]
    tokens=[]
    while line:
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
    plt.savefig('outputFiles/graph1.png')
    f = open('src/vertexDensity.SGL')
    line = f.readline()
    singleMemberCluster=0
    multiMemberCluster=0
    tokens=[]
    while line:
        tokens = line.split(":")
        multiMemberCluster=int(tokens[0])
        singleMemberCluster=int(tokens[1])
        line = f.readline()
    f.close()
    label = singleMemberCluster, multiMemberCluster
    sizes = [singleMemberCluster, multiMemberCluster]
    explode = (0, 0.05)  # only "explode" the 2nd slice (i.e. 'Hogs')
    fig1, ax1 = plt.subplots()
    ax1.pie(sizes, explode=explode, labels=label, autopct='%1.1f%%',
                shadow=True, startangle=180)
    plt.title('PClust Density Graph')
    labels=['Clusters with 1 member','Clusters with > 1 member']
    ax1.legend(labels, loc="lower left")
    plt.savefig('outputFiles/graph2.png')
    ax1.axis('equal')  # Equal aspect ratio ensures that pie is drawn as a circle.s
#saveGraph3()
