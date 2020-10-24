import matplotlib.pyplot as plt
def showGraph2():
    f = open('src/vertexDensity.SGL')
    line = f.readline()
    singleMemberCluster=0
    multiMemberCluster=0
    tokens=[]
    while line:
        #print line
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
    #plt.savefig('outputFiles/graph2.png')
    ax1.axis('equal')  # Equal aspect ratio ensures that pie is drawn as a circle.s
    plt.show()
